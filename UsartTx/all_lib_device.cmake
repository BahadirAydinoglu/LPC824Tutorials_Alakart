# Copy variable into project config.cmake to use software component
#set.board.lpcxpresso824max
#  # description: Board_project_template lpcxpresso824max
#  set(CONFIG_USE_BOARD_Project_Template_lpcxpresso824max true)

#set.device.LPC824
#  # description: Middleware baremetal
#  set(CONFIG_USE_middleware_baremetal true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Devices_project_template LPC824
#  set(CONFIG_USE_DEVICES_Project_Template_LPC824 true)

#  # description: Device LPC824_startup
#  set(CONFIG_USE_device_LPC824_startup true)

#  # description: Device LPC824_cmsis
#  set(CONFIG_USE_device_LPC824_CMSIS true)

#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: Component lpc_gpio_adapter
#  set(CONFIG_USE_component_lpc_gpio_adapter true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: Inputmux_connections Driver
#  set(CONFIG_USE_driver_inputmux_connections true)

#  # description: Swm_connections Driver
#  set(CONFIG_USE_driver_swm_connections true)

#  # description: Syscon_connections Driver
#  set(CONFIG_USE_driver_syscon_connections true)

#  # description: Power Driver
#  set(CONFIG_USE_driver_power_no_lib true)

#  # description: COMMON Driver
#  set(CONFIG_USE_driver_common true)

#  # description: Device LPC824_system
#  set(CONFIG_USE_device_LPC824_system true)

#  # description: Component button
#  set(CONFIG_USE_component_button true)

#  # description: Component lpc_crc_adapter
#  set(CONFIG_USE_component_lpc_crc_adapter true)

#  # description: Component software_crc_adapter
#  set(CONFIG_USE_component_software_crc_adapter true)

#  # description: Component lpc_i2c_adapter
#  set(CONFIG_USE_component_lpc_i2c_adapter true)

#  # description: Component led
#  set(CONFIG_USE_component_led true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Component mem_manager
#  set(CONFIG_USE_component_mem_manager true)

#  # description: Component mem_manager_light
#  set(CONFIG_USE_component_mem_manager_light true)

#  # description: Component panic
#  set(CONFIG_USE_component_panic true)

#  # description: Component reset_adapter
#  set(CONFIG_USE_component_reset_adapter true)

#  # description: Component software_rng_adapter
#  set(CONFIG_USE_component_software_rng_adapter true)

#  # description: Component mrt_adapter
#  set(CONFIG_USE_component_mrt_adapter true)

#  # description: Component timer_manager
#  set(CONFIG_USE_component_timer_manager true)

#  # description: Component miniusart_adapter
#  set(CONFIG_USE_component_miniusart_adapter true)

#  # description: CRC Driver
#  set(CONFIG_USE_driver_lpc_crc true)

#  # description: IAP Driver
#  set(CONFIG_USE_driver_iap true)

#  # description: INPUTMUX Driver
#  set(CONFIG_USE_driver_inputmux true)

#  # description: LPC_ACOMP Driver
#  set(CONFIG_USE_driver_lpc_acomp true)

#  # description: ADC Driver
#  set(CONFIG_USE_driver_lpc_adc true)

#  # description: DMA Driver
#  set(CONFIG_USE_driver_lpc_dma true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_lpc_gpio true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_lpc_i2c true)

#  # description: IOCON Driver
#  set(CONFIG_USE_driver_lpc_iocon_lite true)

#  # description: SPI Driver
#  set(CONFIG_USE_driver_lpc_minispi true)

#  # description: USART Driver
#  set(CONFIG_USE_driver_lpc_miniusart true)

#  # description: MRT Driver
#  set(CONFIG_USE_driver_mrt true)

#  # description: PINT Driver
#  set(CONFIG_USE_driver_pint true)

#  # description: Reset Driver
#  set(CONFIG_USE_driver_reset true)

#  # description: SCT Driver
#  set(CONFIG_USE_driver_sctimer true)

#  # description: SWM Driver
#  set(CONFIG_USE_driver_swm true)

#  # description: SYSCON Driver
#  set(CONFIG_USE_driver_syscon true)

#  # description: WKT Driver
#  set(CONFIG_USE_driver_wkt true)

#  # description: WWDT Driver
#  set(CONFIG_USE_driver_wwdt true)

#set.CMSIS
#  # description: CMSIS-CORE for Cortex-M, ARMv8-M, ARMv8.1-M
#  set(CONFIG_USE_CMSIS_Include_core_cm true)

#  # description: Access to #include Driver_USART.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USART true)

#  # description: Access to #include Driver_CAN.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_CAN true)

#  # description: Access to #include Driver_ETH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet true)

#  # description: Access to #include Driver_ETH_MAC.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_MAC true)

#  # description: Access to #include Driver_ETH_PHY.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_PHY true)

#  # description: Access to #include Driver_Flash.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Flash true)

#  # description: Access to #include Driver_I2C.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_I2C true)

#  # description: Access to #include Driver_MCI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_MCI true)

#  # description: Access to #include Driver_NAND.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_NAND true)

#  # description: Access to #include Driver_SAI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SAI true)

#  # description: Access to #include Driver_SPI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SPI true)

#  # description: Access to #include Driver_USBD.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Device true)

#  # description: Access to #include Driver_USBH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Host true)

#  # description: Access to #include Driver_WiFi.h file
#  set(CONFIG_USE_CMSIS_Driver_Include_WiFi true)

#  # description: Device interrupt controller interface
#  set(CONFIG_USE_CMSIS_Device_API_OSTick true)

#  # description: CMSIS-RTOS API for Cortex-M, SC000, and SC300
#  set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_Secure true)

#  # description: CMSIS-RTOS2 RTX5 for Armv8-M Non-Secure Domain (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_NonSecure true)

#set.CMSIS_DSP_Lib
#  # description: CMSIS-DSP Library Header
#  set(CONFIG_USE_CMSIS_DSP_Include true)

#  # description: CMSIS-DSP Library
#  set(CONFIG_USE_CMSIS_DSP_Source true)

#  # description: CMSIS-NN Library
#  set(CONFIG_USE_CMSIS_NN_Source true)

#set.component.osa
#  # description: Component common_task
#  set(CONFIG_USE_component_common_task true)

#  # description: Component osa_bm
#  set(CONFIG_USE_component_osa_bm true)

#  # description: Component osa
#  set(CONFIG_USE_component_osa true)

#  # description: Component osa interface
#  set(CONFIG_USE_component_osa_interface true)

#set.middleware.rtcesl
#  # description: Real Time Control Embedded Software Library for CM0 core
#  set(CONFIG_USE_middleware_rtcesl_cm0AllLibs true)

list(APPEND CMAKE_MODULE_PATH
${CMAKE_CURRENT_LIST_DIR}/
${CMAKE_CURRENT_LIST_DIR}/CMSIS
${CMAKE_CURRENT_LIST_DIR}/component/uart
${CMAKE_CURRENT_LIST_DIR}/device
${CMAKE_CURRENT_LIST_DIR}/drivers
${CMAKE_CURRENT_LIST_DIR}/startup
${CMAKE_CURRENT_LIST_DIR}/utilities
)

include_if_use(BOARD_Project_Template_lpcxpresso824max)
include_if_use(CMSIS_DSP_Include)
include_if_use(CMSIS_DSP_Source)
include_if_use(CMSIS_Device_API_OSTick)
include_if_use(CMSIS_Device_API_RTOS2)
include_if_use(CMSIS_Driver_Include_CAN)
include_if_use(CMSIS_Driver_Include_Ethernet)
include_if_use(CMSIS_Driver_Include_Ethernet_MAC)
include_if_use(CMSIS_Driver_Include_Ethernet_PHY)
include_if_use(CMSIS_Driver_Include_Flash)
include_if_use(CMSIS_Driver_Include_I2C)
include_if_use(CMSIS_Driver_Include_MCI)
include_if_use(CMSIS_Driver_Include_NAND)
include_if_use(CMSIS_Driver_Include_SAI)
include_if_use(CMSIS_Driver_Include_SPI)
include_if_use(CMSIS_Driver_Include_USART)
include_if_use(CMSIS_Driver_Include_USB_Device)
include_if_use(CMSIS_Driver_Include_USB_Host)
include_if_use(CMSIS_Driver_Include_WiFi)
include_if_use(CMSIS_Include_core_cm)
include_if_use(CMSIS_NN_Source)
include_if_use(CMSIS_RTOS2_NonSecure)
include_if_use(CMSIS_RTOS2_Secure)
include_if_use(DEVICES_Project_Template_LPC824.LPC824)
include_if_use(component_button.LPC824)
include_if_use(component_common_task)
include_if_use(component_led.LPC824)
include_if_use(component_lists.LPC824)
include_if_use(component_lpc_crc_adapter.LPC824)
include_if_use(component_lpc_gpio_adapter.LPC824)
include_if_use(component_lpc_i2c_adapter.LPC824)
include_if_use(component_mem_manager.LPC824)
include_if_use(component_mem_manager_light.LPC824)
include_if_use(component_miniusart_adapter.LPC824)
include_if_use(component_mrt_adapter.LPC824)
include_if_use(component_osa)
include_if_use(component_osa_bm)
include_if_use(component_osa_interface)
include_if_use(component_panic.LPC824)
include_if_use(component_reset_adapter.LPC824)
include_if_use(component_software_crc_adapter.LPC824)
include_if_use(component_software_rng_adapter.LPC824)
include_if_use(component_timer_manager.LPC824)
include_if_use(device_LPC824_CMSIS.LPC824)
include_if_use(device_LPC824_startup.LPC824)
include_if_use(device_LPC824_system.LPC824)
include_if_use(driver_clock.LPC824)
include_if_use(driver_common.LPC824)
include_if_use(driver_iap.LPC824)
include_if_use(driver_inputmux.LPC824)
include_if_use(driver_inputmux_connections.LPC824)
include_if_use(driver_lpc_acomp.LPC824)
include_if_use(driver_lpc_adc.LPC824)
include_if_use(driver_lpc_crc.LPC824)
include_if_use(driver_lpc_dma.LPC824)
include_if_use(driver_lpc_gpio.LPC824)
include_if_use(driver_lpc_i2c.LPC824)
include_if_use(driver_lpc_iocon_lite.LPC824)
include_if_use(driver_lpc_minispi.LPC824)
include_if_use(driver_lpc_miniusart.LPC824)
include_if_use(driver_mrt.LPC824)
include_if_use(driver_pint.LPC824)
include_if_use(driver_power_no_lib.LPC824)
include_if_use(driver_reset.LPC824)
include_if_use(driver_sctimer.LPC824)
include_if_use(driver_swm.LPC824)
include_if_use(driver_swm_connections.LPC824)
include_if_use(driver_syscon.LPC824)
include_if_use(driver_syscon_connections.LPC824)
include_if_use(driver_wkt.LPC824)
include_if_use(driver_wwdt.LPC824)
include_if_use(middleware_baremetal.LPC824)
include_if_use(middleware_rtcesl_cm0AllLibs)
include_if_use(utilities_misc_utilities.LPC824)
include_if_use(utility_assert_lite.LPC824)
include_if_use(utility_debug_console_lite.LPC824)
