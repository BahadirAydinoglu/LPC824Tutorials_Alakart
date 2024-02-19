# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
return()
endif()


# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(UsartTx)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME UsartTx.elf)

if (NOT DEFINED SdkRootDirPath)
SET(SdkRootDirPath ${ProjDirPath}/)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME}
"${ProjDirPath}/board/board.c"
"${ProjDirPath}/board/board.h"
"${ProjDirPath}/board/clock_config.c"
"${ProjDirPath}/board/clock_config.h"
"${ProjDirPath}/board/pin_mux.c"
"${ProjDirPath}/board/pin_mux.h"
"${ProjDirPath}/source/main.c"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
${ProjDirPath}/board
${ProjDirPath}/lpcxpresso824max/demo_apps/hello_world
)


include(${ProjDirPath}/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)
SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")
ENDIF()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map")

add_custom_target(CreateHex ALL DEPENDS ${ProjDirPath}/release/${CMAKE_PROJECT_NAME}.elf)
add_custom_command(TARGET CreateHex
COMMAND bash "-c" "arm-none-eabi-objcopy -O ihex ${ProjDirPath}/release/${CMAKE_PROJECT_NAME}.elf ${ProjDirPath}/release/${CMAKE_PROJECT_NAME}.hex")

add_custom_target(flash DEPENDS ${ProjDirPath}/release/${CMAKE_PROJECT_NAME}.hex)
add_custom_command(TARGET flash
COMMAND bash "-c" "lpc21isp -control ${ProjDirPath}/release/${CMAKE_PROJECT_NAME}.hex /dev/ttyUSB0 115200 12000")