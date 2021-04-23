#if(LWIP_APP_API_STRING MATCHES "raw")
#    add_subdirectory(raw)
#elseif(LWIP_APP_API_STRING MATCHES "netcon")
#    message(STATUS "test")
#    add_subdirectory(netcon)
#endif()

add_subdirectory(raw)
add_subdirectory(netcon)