#include "caesar.hpp"

#include <cctype>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>

namespace algorithms
{

bool caesar::isCharInAlphabet(char c) const{
    return ALPHABET[0] <= c && c <= ALPHABET[ALPHABET_LEN-1];
}

char caesar::shiftChar(char c, int number_of_shifts) const {
    char lowerChar = std::tolower(c);
    if(!isCharInAlphabet(lowerChar)){
        std::stringstream exceptionStream;
        exceptionStream << "The " << c << " character is not in the defined alphabet";
        throw std::invalid_argument( exceptionStream.str());
    }
    auto shiftedLowerChar = ALPHABET[0]+((lowerChar-ALPHABET[0]+number_of_shifts)%ALPHABET_LEN);
    return  lowerChar != c ? std::toupper(shiftedLowerChar) : shiftedLowerChar;
}

char caesar::shiftCharWith(char c, int number_of_shifts,std::function<char(char,int)> shiftCharLambda) const {
    char lowerChar = std::tolower(c);
    if(!caesar::isCharInAlphabet(lowerChar)){
        std::stringstream exceptionStream;
        exceptionStream << "The " << c << " character is not in the defined alphabet";
        throw std::invalid_argument( exceptionStream.str());
    }
    auto shiftedLowerChar = shiftCharLambda(lowerChar,number_of_shifts);
    return  lowerChar != c ? std::toupper(shiftedLowerChar) : shiftedLowerChar;
}

std::string caesar::shiftStringWith(const std::string& message, const std::string& key,std::function<char(char,int)> shiftCharLambda) const{
    int number_of_shifts = std::stoi(key);
    if(number_of_shifts < 0){
        throw std::invalid_argument("The key should be an integer greater than 0");
    }
    
    std::stringstream sstream;
    for(std::string::size_type i = 0; i < message.length(); i++){
        sstream << (isspace(message[i]) ? message[i] : shiftCharWith(message[i],number_of_shifts,shiftCharLambda));
    }
    return sstream.str();
}

std::string caesar::encrypt(const std::string& message, const std::string& key) const {
    std::function<char(char,int)> encryptCharLambda = [this](char character,int number_of_shifts){
            return this->ALPHABET[0]+((character-this->ALPHABET[0]+number_of_shifts)%this->ALPHABET_LEN);
        };
    return shiftStringWith(message,key,encryptCharLambda);
}

std::string caesar::decrypt(const std::string& message, const std::string& key) const {
    std::function<char(char,int)> decryptCharLambda = [this](char character,int number_of_shifts){
            auto shiftedPosition = character-number_of_shifts-this->ALPHABET[0];
            if(shiftedPosition < 0){
                shiftedPosition +=this->ALPHABET_LEN;
            }
            return (shiftedPosition%this->ALPHABET_LEN)+this->ALPHABET[0];;
        };
    return shiftStringWith(message,key,decryptCharLambda);
}

}