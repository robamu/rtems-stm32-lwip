target_sources(${TARGET_NAME} PRIVATE
	stm32h7xx_nucleo.c
	hardware_init.c
)

target_include_directories(${TARGET_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)