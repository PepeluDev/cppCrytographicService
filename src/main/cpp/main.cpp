// Server libs
#include <nghttp2/asio_http2_server.h>

// Json handling libs
#include "rapidjson/document.h"
// Standard libs
#include <memory>
#include <iostream>
#include <sstream>

// Own libs
#include "cryptographic_algorithm_if.hpp"
#include "caesar/caesar.hpp"

// namespaces
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

nghttp2::asio_http2::header_map getHeaders(){
  nghttp2::asio_http2::header_map headers;
  headers.insert(
    std::make_pair<std::string, nghttp2::asio_http2::header_value>("content-type", {"application/json; charset=utf-8",false}));
  return headers;
}

std::function<void(const request &, const response &)> getCryptographicHandler(std::function<std::string(std::string,std::string)> encryptionFunc){
  return [encryptionFunc](const request &req, const response &res) {
      auto sharedStream = std::make_shared<std::stringstream>();
      req.on_data([&res,sharedStream,encryptionFunc](const uint8_t * data, std::size_t size){
        
        if(size > 0) {
          *sharedStream << data;
          return;
        }

        rapidjson::Document document;
        document.Parse(sharedStream->str().c_str());
        if(!document.HasMember("message") || !document.HasMember("key") ){
          res.write_head(400);
          res.end();
          return;
        }

        try {
          auto encryptedMessage = encryptionFunc(
            document["message"].GetString(),
            document["key"].GetString());
          res.write_head(200,getHeaders());
          res.end("{\"message\":\""+encryptedMessage+"\"}");
        } catch (const std::invalid_argument& ia) {
            res.write_head(400,getHeaders());
            std::stringstream sstream;
            sstream << "{\"cause\":\"" << ia.what() << "\"}";
            res.end(sstream.str());
        }
      });
    };
}

std::function<void(const request &, const response &)> getCipherHandler(std::shared_ptr<algorithms::cryptographic_algorithm_if> cryptographic_algorithm){
  std::function<std::string(std::string,std::string)> encryptionFunc = [cryptographic_algorithm](std::string message,std::string key){
    return cryptographic_algorithm->encrypt(message,key);
  };
  return getCryptographicHandler(encryptionFunc);
}

std::function<void(const request &, const response &)> getDecipherHandler(std::shared_ptr<algorithms::cryptographic_algorithm_if> cryptographic_algorithm){
  std::function<std::string(std::string,std::string)> decryptionFunc = [cryptographic_algorithm](std::string message,std::string key){
    return cryptographic_algorithm->decrypt(message,key);
  };
  return getCryptographicHandler(decryptionFunc);
}

int main(int argc, char *argv[]) {

  // Crypto Algorithms
  std::shared_ptr<algorithms::caesar> caesarAlgorithm = std::make_shared<algorithms::caesar>();

  http2 server;
  // Server Handlers
  server.handle("/system/health", [](const request &req, const response &res) {
    res.write_head(200,getHeaders());
    res.end("{\"SERVER\":\"UP\"}");
  });

  // Crypto Handlers
  server.handle("/api/crypto/caesar/encrypt", getCipherHandler(caesarAlgorithm));
  server.handle("/api/crypto/caesar/decrypt", getDecipherHandler(caesarAlgorithm));

  // Start server
  boost::system::error_code ec;
  const std::string SERVER_PORT = "3000";
  std::cout << "SERVER STARTING IN PORT: " << SERVER_PORT <<  std::endl;
  if (server.listen_and_serve(ec, "0.0.0.0", SERVER_PORT)) {
    std::cerr << "error: " << ec.message() << std::endl;
  }
}