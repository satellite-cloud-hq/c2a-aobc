cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

project(C2A_USER_IF_WRAPPER)

set(C2A_SRCS_COMMON
  if_list.c
)

if(USE_IFWRAPPER_SILS)
  set(C2A_SILS_SRCS
    Sils/uart_sils.c
    Sils/i2c_sils.c
    Sils/spi_sils.c
    Sils/adc_sils.c
    Sils/wdt_sils.c
    Sils/gpio_sils.c
    Sils/pwm_sils.c
  )

  if(USE_UART_COM)
    add_definitions(-DUSE_UART_COM)
    list(APPEND C2A_SILS_SRCS
      Sils/com_port.cpp
    )
    message("Use UART COM")
  endif()
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "pic32mx")
  # 実機 向け IfWrapper 実装
  set(C2A_PIC_SRCS
    COMMON/WDT_TEMP.c
    Arduino/CHIPKIT/ADC_CHIPKIT.cpp
    Arduino/CHIPKIT/GPIO_CHIPKIT.cpp
    Arduino/CHIPKIT/I2C_CHIPKIT.cpp
    Arduino/CHIPKIT/spi_chipkit.cpp
    Arduino/CHIPKIT/UART_CHIPKIT.cpp
    Arduino/ADC_ARDUINO.c
    Arduino/GPIO_ARDUINO.c
    Arduino/I2C_ARDUINO.c
    Arduino/spi_arduino.c
    Arduino/UART_ARDUINO.c
  )
endif()

set(C2A_SRCS
  ${C2A_SRCS_COMMON}
  ${C2A_SILS_SRCS}
  ${C2A_PIC_SRCS}
)

if(USE_KBLE_MOBC_UART)
  add_definitions(-DUSE_KBLE_MOBC_UART)

  # Use Rust library
  include(FetchContent)

  set(Rust_CARGO_TARGET "i686-unknown-linux-gnu")
  FetchContent_Declare(
      Corrosion
      GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
      GIT_TAG v0.5.0
  )
  FetchContent_MakeAvailable(Corrosion)

  corrosion_import_crate(MANIFEST_PATH ../../../../common/uart-kble-only-mobc/Cargo.toml CRATE_TYPES staticlib FLAGS --crate-type=staticlib)
endif()


if(BUILD_C2A_AS_CXX)
  set_source_files_properties(${C2A_SRCS} PROPERTIES LANGUAGE CXX)  # C++
endif()

if(USE_SCI_COM)
  add_definitions(-DUSE_SCI_COM)
  list(APPEND C2A_SRCS
    Sils/ccsds_sils_sci_if.c
  )
  message("USE SCI_COM")
endif()

if(USE_SCI_COM_UART)
  add_definitions(-DUSE_SCI_COM_UART)
  list(APPEND C2A_SRCS
    Sils/uart_sils_sci_if.cpp
  )
  message("USE SCI_COM")
endif()

add_library(${PROJECT_NAME} OBJECT ${C2A_SRCS})

if(USE_KBLE_MOBC_UART)
  target_link_libraries(${PROJECT_NAME} c2a_uart_kble_only_mobc)
endif()

include(${C2A_USER_DIR}/common.cmake)
