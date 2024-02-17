# Add set(CONFIG_USE_driver_swm true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC824) AND CONFIG_USE_driver_common AND CONFIG_USE_driver_swm_connections)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
${CMAKE_CURRENT_LIST_DIR}/fsl_swm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_LIST_DIR}/
)

else()

message(SEND_ERROR "driver_swm.LPC824 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
