cmake_minimum_required(VERSION 3.15) 

set(RTEMS_CONFIG_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/../../../rtems-cmake" 
	CACHE FILEPATH 
	"Directory containing the RTEMS *.cmake files"
)

set(RTEMS_LWIP_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../rtems-lwip"
    CACHE FILEPATH
    "Directory containing the RTEMS lwIP library"
) 

set(LWIP_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR})

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

add_subdirectory(bsp_stm32)
add_subdirectory(${RTEMS_LWIP_DIR} ${CMAKE_CURRENT_BINARY_DIR}/lwip)

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

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
install(TARGETS ${TARGET_NAME} DESTINATION "bin")

include("${RTEMS_CONFIG_DIR}/BuildType.cmake")
set_build_type()

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

################################################################################
# Load RTEMS post-project configuration and checks
################################################################################
include("${RTEMS_CONFIG_DIR}/RTEMSPostProjectConfig.cmake")
rtems_post_project_config(${TARGET_NAME})
