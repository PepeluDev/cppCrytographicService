FROM cppcryptographicservicebase:latest as builder

COPY . /code
WORKDIR /code/build
RUN  cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make -j4 && mkdir -p /cppcryptographicservice \
    && cp /code/build/src/main/cpp/cppcryptographicservice /cppcryptographicservice/cppcryptographicservice \
    && rm -rf /code

WORKDIR /cppcryptographicservice
CMD ["./cppcryptographicservice"]
EXPOSE 3000

