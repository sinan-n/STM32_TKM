# STM32H755 + SSD1306 0.96" I2C OLED

Simple example project showing how to drive a 0.96" SSD1306 I2C OLED (128×64) from an STM32H755ZI (NUCLEO‑H755ZI‑Q) using STM32CubeIDE and HAL.

The OLED module used here has 4 pins in this order:

- GND  
- VCC  
- SCL  
- SDA  

The SSD1306 I2C address is 0x3C (HAL 8‑bit address 0x78).

---

## 1. CubeMX / STM32CubeIDE configuration

### 1.1 RCC and clocks

1. Open the `.ioc` file.  
2. Go to “Clock Configuration”.  
3. Enable HSE as “Crystal/Ceramic Resonator”.  
4. Keep the default HSI‑based 64 MHz system clock (no PLL needed for this demo).

### 1.2 I2C1 peripheral

1. In “Pinout & Configuration → Connectivity”, enable I2C1 in I2C mode for Cortex‑M7.  
2. In the pinout view, Cube will assign:
   - PB8 → I2C1_SCL  
   - PB9 → I2C1_SDA  

3. In “I2C1 → Parameter Settings” set:
   - I2C Speed Mode: Fast Mode  
   - I2C Speed Frequency (KHz): 400  

Fast Mode at 400 kHz is used because, with this STM32H755 + OLED module + SSD1306 library combination, the display only updated reliably when using 400 kHz and refreshing the screen in the main loop. Standard Mode at 100 kHz with a single update sometimes left the screen blank.

### 1.3 I2C1 GPIO settings

When I2C1 is enabled on PB8/PB9, STM32CubeMX automatically configures:

- GPIO mode: Alternate Function Open Drain  
- GPIO pull: No pull-up / no pull-down  
- Speed: Low  

These defaults are fine for this project, so no manual GPIO changes are required.

### 1.4 Generate code

Click “Generate Code” to update `main.c`, `i2c.c`, etc.

---

## 2. Hardware connections

Wire the OLED to the NUCLEO‑H755ZI‑Q as follows:

- OLED GND → Nucleo GND  
- OLED VCC → Nucleo 3V3  
- OLED SCL → Nucleo PB8 (I2C1_SCL)  
- OLED SDA → Nucleo PB9 (I2C1_SDA)

Make sure the board is powered from USB and that 3.3 V is present between VCC and GND on the OLED.

---

## 3. Adding the SSD1306 library

This project uses the Tilen Majerle SSD1306 I2C library with HAL.

### 3.1 Add source and header files

Create the four SSD1306 library files inside the STM32CubeIDE project:

1. Header files in `Core/Inc`:
   - In the Project Explorer, right‑click on `Core/Inc` → `New` → `File`.
   - Enter `fonts.h` as the file name → `Finish`.
   - Open `fonts.h` and paste the `fonts.h` content from this repository.

   - Again right‑click on `Core/Inc` → `New` → `File`.
   - Enter `ssd1306.h` as the file name → `Finish`.
   - Open `ssd1306.h` and paste the `ssd1306.h` content from this repository.

2. Source files in `Core/Src`:
   - Right‑click on `Core/Src` → `New` → `File`.
   - Enter `fonts.c` as the file name → `Finish`.
   - Open `fonts.c` and paste the `fonts.c` code from this repository.

   - Right‑click on `Core/Src` → `New` → `File`.
   - Enter `ssd1306.c` as the file name → `Finish`.
   - Open `ssd1306.c` and paste the `ssd1306.c` code from this repository.

After these steps you should see:
- `fonts.h`, `ssd1306.h` under `Core/Inc`
- `fonts.c`, `ssd1306.c` under `Core/Src`
and the project will compile with `#include "fonts.h"` and `#include "ssd1306.h"` in `main.c`.

## 4. Application code (main.c)

Include the SSD1306 and fonts headers at the top of `main.c`:
```c
#include "fonts.h"
#include "ssd1306.h"
```
In main loop after
```c
MX_GPIO_Init();
MX_I2C1_Init();
```
add
```c
SSD1306_Init();
```
inside the /* USER CODE BEGIN 2 */ add:
```c
 SSD1306_Init();
  SSD1306_GotoXY (0,0);
  SSD1306_Puts ("HELLO", &Font_11x18, 1);
  SSD1306_GotoXY (0, 30);
  SSD1306_Puts ("TKM", &Font_11x18, 1);
  SSD1306_UpdateScreen();
  HAL_Delay (1000);
  SSD1306_ScrollRight(0,7);
  HAL_Delay(3000);
  SSD1306_ScrollLeft(0,7);
  HAL_Delay(3000);
  SSD1306_Stopscroll();
  SSD1306_Clear();

  int num=2025;
  char snum[5];
  SSD1306_GotoXY (30,20);
  itoa(num, snum, 10);
  SSD1306_Puts (snum, &Font_16x26, 1);
  SSD1306_UpdateScreen();

  //SSD1306_DrawLine(POINT1 X, POINT1 Y, POINT2 X, POINT2 Y, 1);
  SSD1306_DrawLine(1,54,126,54,1);
  SSD1306_UpdateScreen();
  HAL_Delay (5000);
  SSD1306_Clear();

  // For Rectangle, we need to use two corner points
  // SSD1306_DrawRectangle(POINT1 X, POINT1 Y, POINT2 X, POINT2 Y, 1);
  SSD1306_DrawRectangle(17,1,115,14,1);
  // SSD1306_DrawTriangle(POINT1X, POINT1Y, POINT2X, POINT2Y, POINT3X, POINT3Y, 1);
  SSD1306_DrawTriangle(73,22,124,62,74,54,1);
  // SSD1306_DrawCircle(CENTER POINT X, CENTER POINT Y, RADIUS, 1);
  SSD1306_DrawCircle(34,50,13,1);
  SSD1306_UpdateScreen();
```
## 5. Building and flashing

1. Select the CM7 project (for example `OLED_2_CM7`) in STM32CubeIDE.  
2. Build the project.  
3. Start a debug/run session using the CM7 `.elf`.  
4. After clicking on resume 
- “HELLO” appears at the top-left of the screen, and “TKM” appears below it.
- the whole display content moves right, then left, then the screen is cleared.
- “2025” appears roughly centered, with a horizontal line drawn near the bottom of the screen and held for 5 seconds.
- A rectangle near the top (y ≈ 1–14) between x = 17 and x = 115  
- A triangle on the right side of the display  
- A circle near the bottom-left

- I2C Configuration:
<img width="1917" height="909" alt="Screenshot 2025-11-28 161335" src="https://github.com/user-attachments/assets/914cb1f6-dcd2-41f5-8ef5-5225c52014f5" />
- RCC Configuration:
<img width="1917" height="831" alt="Screenshot 2025-11-28 191856" src="https://github.com/user-attachments/assets/b9677bbc-1860-4a2c-9120-7a5b1c14b8c6" />






 

