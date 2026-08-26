# RTOS_13_Timer

## Introduction

This project is based on the STM32F103 series MCU, STM32 HAL library, and **FreeRTOS** (CMSIS-RTOS v2) real-time operating system. It demonstrates the integration of various FreeRTOS timer and synchronization mechanisms with hardware timers, displaying their activity on an OLED screen. The project is configured using STM32CubeMX and built with CMake.

## Key Features

- **FreeRTOS Multi-Tasking**: Manages and schedules concurrent tasks using the CMSIS-RTOS v2 API.
- **OLED Display**: Uses software I2C to drive the OLED display (`PB9`=SCL, `PB8`=SDA), showing the status of different timer-related tasks.
- **Modular Software Architecture**: Seamlessly integrates STM32CubeMX HAL/FreeRTOS code with custom user drivers.

| Task Name                 | Type             | Mechanism Used          | Description                                                                                             |
| :------------------------ | :--------------- | :---------------------- | :------------------------------------------------------------------------------------------------------ |
| `StartTaskSwTmr1`         | Software Timer   | Task Notifications      | Periodically displays "SwTmr 1 running." on the OLED.                                                   |
| `StartTaskSwTmr2`         | Software Timer   | Message Queue           | Periodically displays "SwTmr 2 running." on the OLED.                                                   |
| `StartTaskTIM1`           | Hardware Timer   | Event Flags             | Integrates STM32's TIM1 hardware timer with FreeRTOS event flags to periodically display "TIM 1 running." on the OLED. |
| `StartTaskTIM2`           | Hardware Timer   | Semaphores              | Integrates STM32's TIM2 hardware timer with FreeRTOS semaphores to periodically display "TIM 2 running." on the OLED. |

## Key Files

- `CMakeLists.txt`: Root CMake build script.
- `CMakePresets.json`: Configuration and build presets supporting `Debug` and `Release`.
- `config.ioc`: STM32CubeMX project configuration file.
- `Core/Src/main.c`: Main entry point initializing HAL, system clock, peripherals, and starting the FreeRTOS scheduler.
- `Core/Src/timertasks.c`: FreeRTOS task definitions and entry functions (`StartTaskSwTmr1`, `StartTaskSwTmr2`, `StartTaskTIM1`, `StartTaskTIM2`).
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
cd d:/Electronics/RTOS/RTOS_Projects/RTOS_13_Timer
cmake --preset Debug
cmake --build --preset Debug
```

## Flashing & Running

1. After a successful build, flash the generated binary file (`.elf`, `.hex`, or `.bin`) to the target board using ST-Link, DAP-Link, or J-Link.
2. Upon system reset or power-up:
   - The OLED screen will display the running status of the four timer tasks: "SwTmr 1 running.", "SwTmr 2 running.", "TIM 1 running.", and "TIM 2 running.", each appearing and disappearing periodically.

## Hardware Specification

- **Target MCU**: STM32F103 series (e.g., STM32F103C8T6)
- **USART1 Pins**: `PA9` (TX), `PA10` (RX)
- **OLED (Software I2C)**:
  - `PB9`: SCL (Clock)
  - `PB8`: SDA (Data)

## License

MIT License