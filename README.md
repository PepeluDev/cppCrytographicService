# CPP Cryptographic service

I wanted to improve my CPP and Cryptography skills, so here is a POC for a CPP HTTP2 service that offers functionality for text messages encryption and decryption leveraging well known cryptographic algorithms.

## Supported Algorithms

Currently only the *Caesar* algorithm is supported, it was used to bootstrap the project. Soon more algorithms will be implemented such as DES, AES, etc.

## Used Technologies

* Docker: As platform tool.
* CPP: The project uses *Boost*, *Nghttp2* as underlying HTTP/2 server and *Google Test* as unit test engine.
* CMAKE: As building tool.

## How To:

### Build it

You need to have docker installed on your machine.

Steps:
* scripts/buildBase.sh: It builds de cppcryptographicservicebase image, do it only once.
* scripts/build.sh: It will compile the code and build the cppcryptographicservice docker image that can be used to run the server.

### Run and test it

Once that the image is build, you can run it with:

```bash
docker run -d -p 3000:3000 cppcryptographicservice:latest
```

And test the Caesar cipher encryption with:

```bash
curl -d '{"message":"This is a plain text message","key":"3"}' --http2-prior-knowledge localhost:3000/api/crypto/caesar/encrypt
```

And decryption:

```bash
curl -d '{"message":"Wklv lv d sodlq whaw phvvdjh","key":"3"}' --http2-prior-knowledge localhost:3000/api/crypto/caesar/decrypt
``` 

