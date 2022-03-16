add_executable(cppcryptographicservice main.cpp)

target_link_libraries(cppcryptographicservice
PRIVATE
-static
    # Keep the list of files sorted from down to top.
    nghttp2_asio
    nghttp2
    boost_thread
    boost_filesystem
    boost_system
    ssl
    crypto
    dl
    pthread
    ciphers
)
