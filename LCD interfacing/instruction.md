## I2C LCD Interface Project

### Overview
This project demonstrates how to interface a 16x2 LCD display (based on PCF8574 I2C I/O expander) with the **STM32H755ZIQ (Cortex-M7 core)** using the HAL library.  
The LCD is controlled through I2C communication using `I2C1` peripheral.


### Step 1: Hardware Requirements
| Component | Details |
|----------|---------|
| MCU Board | STM32H755ZIQ (Nucleo-H755ZI-Q) |
| Display | 16x2 LCD with PCF8574 I2C Backpack |
| Communication | I2C Interface |
| Voltage Level | 3.3V |



### Step 2: Pin Configuration (CubeMX)
| LCD (PCF8574) | STM32 Pin |
|--------------|-----------|
| SDA | PB9 (I2C1 SDA - AF4) |
| SCL | PB8 (I2C1 SCL - AF4) |
| VCC | +3.3V |
| GND | GND |

Ensure internal pull-ups are enabled on SDA & SCL.
- Power: connect LCD VCC → 3.3 V on the board, GND → GND.

- I2C wires:

- LCD SDA → PB9 (I2C1 SDA, AF4)

- LCD SCL → PB8 (I2C1 SCL, AF4)

- Ensure the I2C backpack has pull-ups (4.7kΩ). Many modules already include them.

- Confirm the contrast potentiometer on the backpack — adjust if nothing appears.
  
### Step 3: Create Project
1. Launch STM32CubeIDE.
2. Go to **File > New > STM32 Project**.
3. Select **Board Selector** and search for **NUCLEO-H755ZI-Q**.
4. Select the board and click **Next**.
5. Name the project (e.g., `lcd_interface_Lab`).
6. Initialize peripherals with default mode: **Yes**.

### Step 4: Configure Pinout (.ioc file)

- Open STM32CubeIDE and create a new project for STM32H755ZIQ (or open your existing project).
- Peripherals:
- Enable I2C1
- Assign SCL = PB8, SDA = PB9. 
- Set I2C timing (100 kHz standard). If you use the timing word from your main.c, it was 0x00707CBB — default 100 kHz is fine.
- GPIO: leave PB8/PB9 pull-ups enabled (internal) or rely on external pull-ups.
- Clock: keep HSI (or your chosen clock). Ensure system clock and bus prescalers are set (CubeMX does this).
- Middleware / FreeRTOS: not required — keep empty unless you want it.
- Save the `.ioc` file to generate the code.

  ### Step 5: Implement Code (Cortex-M7)

1. In the Project Explorer, expand the **CM7** project folder.
2. Add LCD Driver Files 
3. Navigate: `CM7 > Core > inc` (Core/Inc/**lcd.h**)
<img width="1923" height="1083" alt="image" src="https://github.com/user-attachments/assets/668cfa19-293b-4acf-a548-f04986c27a86" />

4. place the code for hearder file: i2c-lcd.h
5.Navigate: `CM7 > Core > src` (Core/Inc/**lcd.c**).
<img width="1923" height="1083" alt="image" src="https://github.com/user-attachments/assets/c2c35266-37f8-4614-a038-397325951a9a" />

6.place the code for source file: i2c-lcd.c.

7. Open **main.c**

### Step 6: Build and Run
1. Build the **CM7** project.
2. Debug as **STM32 C/C++ Application**
3. Press **Resume (Play)**.


