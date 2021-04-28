cmake_minimum_required(VERSION 3.15) 

set(RTEMS_CONFIG_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/rtems-cmake" 
	CACHE FILEPATH 
	"Directory containing the RTEMS *.cmake files"
)

set(LWIP_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(LWIP_APP_API_STRING "raw" CACHE STRING "lwIP API select")
set_property(CACHE LWIP_APP_API_STRING PROPERTY STRINGS raw netcon socket)

if(LWIP_APP_API_STRING MATCHES "raw")
    set(LWIP_APP_API_SELECT LWIP_APP_RAW_API)
elseif(LWIP_APP_API_STRING MATCHES "netcon")
    set(LWIP_APP_API_SELECT LWIP_APP_NETCON_API)
elseif(LWIP_APP_API_STRING MATCHES "socket")
    set(LWIP_APP_API_SELECT LWIP_APP_SOCKET_API)
endif()

set(LWIP_APP_STRING "udp" CACHE STRING "TCP/IP protocol select")
set_property(CACHE LWIP_APP_STRING PROPERTY STRINGS udp tcp)

if(LWIP_APP_STRING MATCHES "udp")
    set(LWIP_APP_SELECT LWIP_APP_UDP_ECHOSERVER)
elseif(LWIP_APP_STRING MATCHES "tcp")
    set(LWIP_APP_SELECT LWIP_APP_TCP_ECHOSERVER)
endif()

set(LWIP_APP_TCPIP_PORT 7)
set(LWIP_APP_LED_BLINK_INTERVAL 1000)
# RTEMS priorities ranging from 1 (highest) to 254 (lowest)
set(LWIP_APP_SERVER_THREAD_PRIO 50)

option(LWIP_APP_BLINK_LED_PERIODIC  "Blink LED periodically"    ON)
option(LWIP_APP_RECEIVE_WIRETAPPING "Reception wiretapping"     OFF)
option(LWIP_APP_USE_DHCP            "Use DHCP"                  ON)

configure_file(conf_app.h.in conf_app.h @ONLY)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

################################################################################
# Load RTEMS pre-project configuration and checks
################################################################################
# Sanity checks
if(NOT RTEMS_PREFIX)
	if(NOT DEFINED ENV{RTEMS_BSP})
		message(FATAL_ERROR "No RTEMS prefix supplied!")
	else()
		set(RTEMS_PREFIX $ENV{RTEMS_BSP})
	endif()
endif()

if(NOT DEFINED RTEMS_BSP)
	if(NOT DEFINED ENV{RTEMS_BSP})
		message(FATAL_ERROR "No RTEMS BSP pair name supplied!")
	else()
		set(RTEMS_BSP $ENV{RTEMS_BSP})
	endif()
endif()

include(${RTEMS_CONFIG_DIR}/RTEMSPreProjectConfig.cmake)
rtems_pre_project_config(${RTEMS_PREFIX} ${RTEMS_BSP})

set(CMAKE_TOOLCHAIN_FILE ${RTEMS_CONFIG_DIR}/RTEMSToolchain.cmake) 

project(stm32-lwip ASM C CXX)

set(TARGET_NAME ${CMAKE_PROJECT_NAME}) 
set(LIB_LWIP_NAME lwip)

add_executable(${TARGET_NAME})

################################################################################
# Application
################################################################################

if(RTEMS_BSP MATCHES "arm/nucleo-h743zi")
    add_subdirectory(bsp_stm32)
endif()

# RTMES lwIP is now installed like a BSP
# add_subdirectory(rtems-lwip)

add_subdirectory(echoserver)

target_sources(${TARGET_NAME} PRIVATE
    init.c
    main.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    ${LIB_LWIP_NAME}
)

target_include_directories(${TARGET_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(${TARGET_NAME} PRIVATE
        "-Wl,-Map=${TARGET_NAME}.map"
    )

    # Remove unused sections.
    target_compile_options(${TARGET_NAME} PRIVATE
        "-ffunction-sections"
        "-fdata-sections"
    )

    # Removed unused sections.
    if(NOT ${OS_FSFW} MATCHES rtems)
        target_link_options(${TARGET_NAME} PRIVATE
            "-Wl,--gc-sections"
        )
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
endif()

add_custom_command(
	TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND echo "Generating binary file ${TARGET_NAME}.bin"
	COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET_NAME} ${TARGET_NAME}.bin
)

string(CONCAT POST_BUILD_COMMENT
    "RTEMS version: ${RTEMS_VERSION}\n"
    "Built for RTEMS BSP: ${RTEMS_BSP}\n"
    "Target build type: ${CMAKE_BUILD_TYPE}\n"
)

add_custom_command(
   TARGET ${CMAKE_PROJECT_NAME}
   POST_BUILD
   COMMAND ${CMAKE_SIZE} ${TARGET_NAME}
   COMMENT ${POST_BUILD_COMMENT}
)

include("${RTEMS_CONFIG_DIR}/BuildType.cmake")
set_build_type()

################################################################################
# Load RTEMS post-project configuration and checks
################################################################################
include("${RTEMS_CONFIG_DIR}/RTEMSPostProjectConfig.cmake")
rtems_post_project_config(${TARGET_NAME})
