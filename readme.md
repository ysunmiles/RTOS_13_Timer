# RTOS_01_LED_UART_OLED

## Introduction

This project is based on the STM32F103 series MCU, STM32 HAL library, and **FreeRTOS** (CMSIS-RTOS v2) real-time operating system. It demonstrates a classic multi-tasking concurrent execution application.
The system features three concurrent tasks: LED toggling, UART string transmission, and OLED display updating, configured using STM32CubeMX and built with CMake.

## Key Features

- **FreeRTOS Multi-Tasking**: Manages and schedules concurrent tasks using the CMSIS-RTOS v2 API.
- **LED Task (`LEDTask`)**: Controls the onboard LED on pin `PC13`, toggling its state every 1000ms (Priority: Normal).
- **UART Task (`UARTTask`)**: Transmits `"UART Sending...\r\n"` via USART1 every 2000ms (Priority: Low).
- **OLED Task (`OLEDTask`)**: Uses software I2C to drive the OLED display (`PB9`=SCL, `PB8`=SDA), dynamically updating an incrementing hex counter and blinking status text (Priority: Low).
- **Modular Software Architecture**: Seamlessly integrates STM32CubeMX HAL/FreeRTOS code with custom user drivers.

## Key Files

- `CMakeLists.txt`: Root CMake build script.
- `CMakePresets.json`: Configuration and build presets supporting `Debug` and `Release`.
- `config.ioc`: STM32CubeMX project configuration file.
- `Core/Src/main.c`: Main entry point initializing HAL, system clock, peripherals, and starting the FreeRTOS scheduler.
- `Core/Src/freertos.c`: FreeRTOS task definitions and entry functions (`EntryLEDTask`, `EntryUARTTask`, `EntryOLEDTask`).
- `Core/Src/OLED.c`: OLED display control logic and software I2C driver implementation.
- `Core/Inc/OLED.h`: Header file declaring OLED functions.
- `Core/Inc/OLED_Font.h`: Font library data for ASCII character display.
- `cmake/user_sources.cmake`: Registration script for custom user source files and include directories.
- `Middlewares/Third_Party/FreeRTOS/`: FreeRTOS kernel source code and CMSIS-RTOS v2 wrapper layer.
- `Drivers/`: STM32 HAL drivers and CMSIS headers.

## Build Environment & Dependencies

- CMake 3.22 or higher
- Ninja build tool
- ARM GCC Cross Compiler (e.g., `arm-none-eabi-gcc`)
- STM32 HAL Library & FreeRTOS (included in `Drivers/` and `Middlewares/`)

## Build Instructions

Recommended using VS Code CMake Tools or executing commands in terminal:

```bash
cd d:/Electronics/RTOS/RTOS_Projects/RTOS_01_LED_UART_OLED
cmake --preset Debug
cmake --build --preset Debug
```

## Flashing & Running

1. After a successful build, flash the generated binary file (`.elf`, `.hex`, or `.bin`) to the target board using ST-Link, DAP-Link, or J-Link.
2. Upon system reset or power-up:
   - Onboard LED (`PC13`) toggles every 1 second.
   - Serial terminal connected to USART1 (115200 8N1) receives `"UART Sending...\r\n"` every 2 seconds.
   - OLED screen displays an incrementing hexadecimal value with blinking status text.

## Hardware Specification

- **Target MCU**: STM32F103 series (e.g., STM32F103C8T6)
- **LED Pin**: `PC13`
- **USART1 Pins**: `PA9` (TX), `PA10` (RX)
- **OLED (Software I2C)**:
  - `PB9`: SCL (Clock)
  - `PB8`: SDA (Data)

## License

MIT License
