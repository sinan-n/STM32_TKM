# LAB EXPERIMENT: 7-SEGMENT DISPLAY COUNTER LOOP

## EXPERIMENT OBJECTIVE
To configure the Cortex-M7 core of the STM32H755ZI-Q Nucleo board to drive a Common Anode 7-segment display, creating a counter that loops from digits 1 to 9.

---

# STEP 1: HARDWARE IDENTIFICATION

Identify the output components on the NUCLEO-H755ZI-Q board and the 7-segment display.

- Microcontroller: STM32H755ZI-Q
- Output Device: 7-Segment Display (Common Anode)
- Wiring:
  - Common Anode → 3.3V
  - Segments A–G → Port E pins via 220Ω resistors

## PIN MAPPING TABLE

```txt
+---------+------------+------------+-----------------+
| Segment | Nucleo Pin | User Label | Connector       |
+---------+------------+------------+-----------------+
|    A    |    PE2     |   SEG_A    | CN11 (Pin 54)   |
|    B    |    PE3     |   SEG_B    | CN11 (Pin 56)   |
|    C    |    PE4     |   SEG_C    | CN11 (Pin 58)   |
|    D    |    PE5     |   SEG_D    | CN11 (Pin 60)   |
|    E    |    PE6     |   SEG_E    | CN11 (Pin 62)   |
|    F    |    PE7     |   SEG_F    | CN11 (Pin 29)   |
|    G    |    PE8     |   SEG_G    | CN11 (Pin 31)   |
+---------+------------+------------+-----------------+
```


---

# STEP 2: CREATE PROJECT

1. Open STM32CubeIDE  
2. File → New → STM32 Project  
3. Select Board Selector → search **NUCLEO-H755ZI-Q**  
4. Click Next  
5. Name the project (`SevenSeg_Loop_Lab`)  
6. Initialize peripherals with default mode → Yes  

---

# STEP 3: CONFIGURE PINOUT (.ioc FILE)

Goal: Configure PE2 → PE8 as GPIO_Output and assign to Cortex-M7 core.

Steps:
- Open `.ioc` file  
- Search **PE2**, set as `GPIO_Output`

<img width="2557" height="1495" alt="image" src="https://github.com/user-attachments/assets/9397a3df-4d0a-4dbd-9d58-76c41a15ea2f" />

- Pin Reservation → assign to **Cortex-M7**

<img width="2554" height="1489" alt="image" src="https://github.com/user-attachments/assets/83a35de2-635d-41c7-bc27-6e83136e7b94" />

- User Label → SEG_A

<img width="2559" height="1489" alt="image" src="https://github.com/user-attachments/assets/858fa817-1c37-43e6-ac17-17d551303962" />

- Repeat for all: SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G

---

# STEP 4: IMPLEMENT CODE (CORTEX-M7)

Navigate to:
```
CM7 → Core → Src → main.c
```

## 4.1 Add Lookup Table

Inside:
```
/* USER CODE BEGIN 0 */
```

```c
// Pattern for Common Anode (0 = ON, 1 = OFF)
const uint8_t anode_patterns[10][7] = {
    {0,0,0,0,0,0,1}, // 0
    {1,0,0,1,1,1,1}, // 1
    {0,0,1,0,0,1,0}, // 2
    {0,0,0,0,1,1,0}, // 3
    {1,0,0,1,1,0,0}, // 4
    {0,1,0,0,1,0,0}, // 5
    {0,1,0,0,0,0,0}, // 6
    {0,0,0,1,1,1,1}, // 7
    {0,0,0,0,0,0,0}, // 8
    {0,0,0,0,1,0,0}  // 9
};
```

## 4.2 Set Display Settings

```c
// Update display segments
void set_display_anode(int number) {
    HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, anode_patterns[number][0]);
    HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, anode_patterns[number][1]);
    HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, anode_patterns[number][2]);
    HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, anode_patterns[number][3]);
    HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, anode_patterns[number][4]);
    HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, anode_patterns[number][5]);
    HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, anode_patterns[number][6]);
}
```
---

## 4.3 Add Counter Loop (1 → 9)

Inside the main loop:

```c
while (1)
{
    for (int i = 1; i <= 9; i++) {
        set_display_anode(i);
        HAL_Delay(1000); // 1 second delay
    }
}
```

---

# STEP 5: BUILD AND RUN

1. Plug in the Nucleo board  
2. Build (Hammer Icon)  
3. Run (Green Play Button)  
4. The display cycles:  

```
1 → 2 → 3 → ... → 9 → repeat
```

---

![PXL_20251127_102506105~2](https://github.com/user-attachments/assets/4b70dfde-e3a4-4401-aead-712944e177c9)

The 7-segment display now continuously counts from **1 to 9** using STM32H755 Cortex-M7.
