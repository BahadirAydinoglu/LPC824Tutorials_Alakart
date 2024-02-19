# Add set(CONFIG_USE_device_LPC824_startup true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_device_LPC824_system)

if(CONFIG_TOOLCHAIN STREQUAL iar)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/iar/startup_LPC824.s "" device_LPC824_startup.LPC824)
endif()

if(CONFIG_TOOLCHAIN STREQUAL armgcc)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/startup_LPC824.S "" device_LPC824_startup.LPC824)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mdk)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/arm/startup_LPC824.S "" device_LPC824_startup.LPC824)
endif()

if(CONFIG_TOOLCHAIN STREQUAL mcux)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_lpc824.c "" device_LPC824_startup.LPC824)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/mcuxpresso/startup_lpc824.cpp "" device_LPC824_startup.LPC824)
endif()

else()

message(SEND_ERROR "device_LPC824_startup.LPC824 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
