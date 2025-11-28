# LAB EXPERIMENT: 7-SEGMENT COUNTER WITH EXTERNAL PUSH BUTTON

## EXPERIMENT OBJECTIVE
To configure the Cortex-M7 core of the STM32H755ZI-Q Nucleo board to drive a 7-segment display, where the counter increments (0–9) only when an external push button is pressed. The experiment uses the internal Pull-Up resistor to simplify wiring.

---

# STEP 1: HARDWARE SETUP

## Components Used
- STM32H755ZI-Q Microcontroller
- 7-Segment Display (Common Anode)
- External Push Button (Tactile Switch)

## Wiring Details

### 7-Segment Display Connections
- Common Pin → 3.3V
- Segment Pins A–G → PE2–PE8 through 330Ω resistors

### External Push Button
- One leg → PD14 (CN12, Pin 46)
- Other leg → GND (CN12, Pin 20)

## PIN MAPPING TABLE

```text
+---------------+------------+-----------+----------------+
| Component     | Nucleo Pin | Label     | Configuration  |
+---------------+------------+-----------+----------------+
| Segment A     | PE2        | SEG_A     | Output         |
| Segment B     | PE3        | SEG_B     | Output         |
| Segment C     | PE4        | SEG_C     | Output         |
| Segment D     | PE5        | SEG_D     | Output         |
| Segment E     | PE6        | SEG_E     | Output         |
| Segment F     | PE7        | SEG_F     | Output         |
| Segment G     | PE8        | SEG_G     | Output         |
| External BTN  | PD14       | EXT_BTN   | Input Pull-Up  |
+---------------+------------+-----------+----------------+
```

---

# STEP 2: CREATE PROJECT

1. Open STM32CubeIDE  
2. File → New → STM32 Project  
3. Select “Board Selector”  
4. Search: NUCLEO-H755ZI-Q  
5. Click Next  
6. Name project  
7. Choose: Initialize peripherals with default mode = YES  

---

# STEP 3: CONFIGURE PINOUT (.ioc FILE)

## A. Configure 7-Segment Display Pins (PE2–PE8)
For each pin PE2 → PE8:
- Mode: GPIO_Output  
- Pin Reservation: Cortex-M7  
- User Label: SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G  

### Table:
```text
+-------+------+------------+
| Pin   | Port | User Label |
+-------+------+------------+
| PE2   |  E   | SEG_A      |
| PE3   |  E   | SEG_B      |
| PE4   |  E   | SEG_C      |
| PE5   |  E   | SEG_D      |
| PE6   |  E   | SEG_E      |
| PE7   |  E   | SEG_F      |
| PE8   |  E   | SEG_G      |
+-------+------+------------+
```

## B. Configure Push Button Pin (PD14)
- Mode → GPIO_Input  
- Pin Reservation → Cortex-M7  
- User Label → EXT_BTN

<img width="2551" height="1486" alt="image" src="https://github.com/user-attachments/assets/d4430934-ee9a-4cd6-bd60-a0efabd314a1" />


## C. Enable Internal Pull-Up
### System Core → GPIO → PD14 → Pull-up
<img width="2550" height="1482" alt="image" src="https://github.com/user-attachments/assets/cee56726-35a8-40c6-833a-6ac896326f42" />



---

# STEP 4: IMPLEMENT CODE (CORTEX-M7)

Open:
CM7 → Core → Src → main.c

## A. Add Segment Patterns & Helper Function
Paste inside /* USER CODE BEGIN 0 */:

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

// Helper function
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
## B. INITIALIZE COUNTER
Place inside /* USER CODE BEGIN 2 */:
```c
int counter = 0;
set_display_anode(counter);  // Show 0 on display
```

## C. ADD BUTTON CONTROLLED COUNTER LOGIC
Place inside while(1):

```c
while (1)
{
    // Button Active LOW
    if (HAL_GPIO_ReadPin(EXT_BTN_GPIO_Port, EXT_BTN_Pin) == GPIO_PIN_RESET)
    {
        counter++;
        if (counter > 9) counter = 0;

        set_display_anode(counter);

        HAL_Delay(250);  // Debounce

        while (HAL_GPIO_ReadPin(EXT_BTN_GPIO_Port, EXT_BTN_Pin) == GPIO_PIN_RESET) {
            HAL_Delay(10);
        }
    }
}
```

# STEP 4: BUILD AND RUN

- Connect Nucleo via USB
- Build project (Hammer Icon)
- Run (Green Play Button)
- Display shows 0
- Each button press increments the digit
- Sequence: 0 → 1 → 2 → … → 9 → 0 → repeat

![PXL_20251128_062047102~2](https://github.com/user-attachments/assets/e32ab96a-586b-412f-bcdc-5feab2c8cda5)

