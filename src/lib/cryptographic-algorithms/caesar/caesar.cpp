#include "caesar.hpp"

#include <cctype>
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

std::string caesar::encrypt(std::string message, std::string key) const {
    int number_of_shifts = std::stoi(key);
    if(number_of_shifts < 0){
        throw std::invalid_argument("The key should be an integer greater than 0");
    }
    
    std::stringstream sstream;
    for(std::string::size_type i = 0; i < message.length(); i++){
        sstream << (isspace(message[i]) ? message[i] : shiftChar(message[i],number_of_shifts));
    }

    return sstream.str();
}

}