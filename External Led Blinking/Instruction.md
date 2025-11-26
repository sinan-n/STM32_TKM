# External LED Blinking Guide (STM32)

This guide explains how to configure and blink an external LED using an STM32 microcontroller.

---

## 1. Select the GPIO Pin  
Choose a suitable GPIO pin to drive the external LED.  
Refer to your board’s **User Manual** or **Pinout Diagram** to select the correct pin.

---

## 2. Configure the Pin as GPIO Output  
In STM32CubeIDE:  
- Locate your chosen pin (example: **PC6**)  
- Set its mode to **GPIO_Output**

---

## 3. Assign Pin to the Correct Cortex Core (For Dual-Core Boards Only)  
If your STM32 board has a dual-core processor (e.g., H755):  
1. Go to **System Core** → **GPIO**  
2. Select your chosen pin  
3. In the **Pin Configuration** tab, find **Pin Context Assignment**  
4. Choose the core (Cortex-M7 or Cortex-M4) that will control the pin  

If using a single-core board, **skip this step**.

---

## 4. Generate Initialization Code  
Click on **Device Configuration Tool → Code Generator**  
CubeIDE will auto-generate the setup code for GPIO.

---

## 5. For Dual-Core Boards – Disable Boot Sync (If Using Only One Core)  
If using only one core:  
- Locate the section of code wrapped under `DUAL_CORE_BOOT_SYNC_SEQUENCE`  
- Comment out this block (typically around line 39–45, may vary)  
- Ensure you write your application code in the **main file of the core you are using**

---

<img width="1692" height="756" alt="image" src="https://github.com/user-attachments/assets/d7c62dcd-5c62-465e-93b4-d288565beae4" />
## 6. Add LED Blinking Code  
Inside the `while(1)` loop, insert your code **between**:
```c
/* USER CODE BEGIN WHILE */
/* USER CODE END WHILE */


