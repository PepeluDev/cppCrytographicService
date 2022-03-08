# CPP Cryptographic service

I wanted to improve my CPP and Cryptography skills, so here is a POC for a CPP HTTP2 service that offers functionality for text messages encryption and decryption leveraging well known cryptographic algorithms.

## Build info

Steps:
    * scripts/buildBase.sh: It builds de cppserverbase image, do it only once.
    * scripts/build.sh: It will compile the code and build a docker image that can be used to run the server.

The project uses *Boost*, *Nghttp2* as underlying http server and *Google Test* as unit test engine.
