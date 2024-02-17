# Add set(CONFIG_USE_driver_lpc_iocon_lite true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC824) AND CONFIG_USE_driver_common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_LIST_DIR}/
)

else()

message(SEND_ERROR "driver_lpc_iocon_lite.LPC824 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
