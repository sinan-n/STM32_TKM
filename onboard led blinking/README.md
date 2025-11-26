# STM32H755ZIQ LED Blink Example

This repository contains a simple LED blink example for the **STM32H755ZIQ Nucleo Board** using **STM32CubeIDE**.

---

## Requirements

- STM32CubeIDE installed
- STM32H755ZIQ Nucleo board
- USB cable for programming/debugging

---

## Steps to Run

### 1. Open STM32CubeIDE
Launch **STM32CubeIDE** and select your workspace.

### 2. Create a New Project
1. Go to: `File → New → STM32 Project`  
2. Select the **Board Selector** tab  
3. Search for: `NUCLEO-H755ZIQ`  
4. Select the board → click **Next → Finish**

### 3. Save the Default Configuration
CubeMX will open automatically.  
Save the configuration:  
`File → Save`

**User LEDs on STM32H755ZIQ:**  
You may use **PB0, PE1, or PB14**

### 4. Add LED Blink Code (CM7 Project)
Open:  
`CM7/Core/Src/main.c`  

Inside the `while(1)` loop, add:

```c
HAL_GPIO_WritePin(GPIOx, GPIO_PIN_y, GPIO_PIN_SET);
HAL_Delay(1000);
HAL_GPIO_WritePin(GPIOx, GPIO_PIN_y, GPIO_PIN_RESET);
HAL_Delay(1000);
```
Replace x and y with the port and pin of the LED  

Example: Blink LED on PB0:
```c
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
HAL_Delay(1000);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
HAL_Delay(1000);
```
Now you are ready to Debugg and Run the code
