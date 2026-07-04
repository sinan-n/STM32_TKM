# UART Communication using STM32H755ZI-Q and PuTTY

## Objective
To transmit the message **"hello"** from the STM32H755ZI-Q Nucleo board to a PC using UART communication and display it on PuTTY.

---

# Step 1: Create a New Project

1. Open **STM32CubeIDE**.
2. Click:

```
File → New → STM32 Project
```

3. Select **MCU Selector**.
4. Search for:

```
STM32H755ZIT6
```

5. Click **Next** and create the project.

### Why did we use MCU Selector instead of Board Selector?

Initially, the Board Selector (`NUCLEO-H755ZI-Q`) project locked some UART settings and caused configuration issues. Therefore, we used the MCU Selector, which provides complete control over peripheral and pin configurations.

The microcontroller mounted on the NUCLEO-H755ZI-Q board is:

```
STM32H755ZIT6
```

Hence, selecting this MCU is equivalent to working with the Nucleo board.

---

# Step 2: Configure USART3

Go to:

```
Pinout & Configuration
```

Select:

```
USART3
```

Under **Runtime Context**, select:

```
Cortex-M7
```

Set the mode as:

```
Asynchronous
```

### Why Asynchronous Mode?

UART communication is asynchronous because no separate clock line is used between the transmitter and receiver. Instead, both devices communicate using a pre-agreed baud rate.

---

# Step 3: Configure UART Parameters

Go to:

```
USART3 → Parameter Settings
```

Set:

| Parameter | Value |
|-----------|--------|
| Baud Rate | 115200 |
| Word Length | 8 Bits |
| Parity | None |
| Stop Bits | 1 |

### Why 115200 Baud?

115200 is one of the most commonly used UART baud rates. Both the STM32 and PuTTY must use the same baud rate for successful communication.

---

# Step 4: Enable Interrupt

Go to:

```
USART3 → NVIC Settings
```

Enable:

```
USART3 Global Interrupt
```

> **Note:** Interrupts are not required for simple transmission using `HAL_UART_Transmit()`. However, they are useful for future applications involving UART reception.

---

# Step 5: Configure UART Pins

In the Pinout View, configure:

```
PD8 → USART3_TX
PD9 → USART3_RX
```

### Why did we use PD8 and PD9?

The NUCLEO-H755ZI-Q board has an onboard **ST-LINK Virtual COM Port (VCP)**.

The VCP is internally connected to:

| Pin | Function |
|------|-----------|
| PD8 | USART3_TX |
| PD9 | USART3_RX |

Since we are using only the ST-LINK USB cable and not an external USB-to-TTL converter, we must use PD8 and PD9. Otherwise, the data transmitted by the microcontroller will not appear on PuTTY.

---

# Step 6: Configure the Clock

Open:

```
Clock Configuration
```

If a clock issue appears:

1. Click:

```
Resolve Clock Issues
```

2. Click:

```
Yes
```

3. Save the project.

STM32CubeIDE will automatically configure the required clocks.

---

# Step 7: Generate the Code

Press:

```
Ctrl + S
```

or save the `.ioc` file.

The IDE will generate all the initialization code, including:

```c
MX_USART3_UART_Init();
```

This function automatically initializes USART3, so no manual UART initialization code is required.

---

# Step 8: Modify `main.c`

### Add the following header file

```c
#include <string.h>
```

Place it under:

```c
/* USER CODE BEGIN Includes */
```

---

### Declare the message

```c
char msg[] = "hello\r\n";
```

Place it just before the `while(1)` loop.

---

### Add the transmission code

```c
HAL_UART_Transmit(&huart3,
                  (uint8_t *)msg,
                  strlen(msg),
                  HAL_MAX_DELAY);

HAL_Delay(1000);
```

Place it inside the `while(1)` loop.

---

# Final Code Snippet

```c
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART3_UART_Init();

  char msg[] = "hello\r\n";

  while (1)
  {
      HAL_UART_Transmit(&huart3,
                        (uint8_t *)msg,
                        strlen(msg),
                        HAL_MAX_DELAY);

      HAL_Delay(1000);
  }
}
```

---

# Step 9: Build the Project

Click:

```
Project → Build Project
```

or press:

```
Ctrl + B
```

Ensure that the project builds successfully without errors.

---

# Step 10: Open PuTTY

1. Open **PuTTY**.
2. Select:

```
Connection Type → Serial
```

3. Set the baud rate:

```
115200
```

---

# Step 11: Find the COM Port

1. Open:

```
Device Manager
```

2. Expand:

```
Ports (COM & LPT)
```

3. Find:

```
STMicroelectronics STLink Virtual COM Port (COMx)
```

4. Note the COM number.

---

# Step 12: Configure PuTTY

Set:

```
Serial Line : COMx
Speed       : 115200
```

Click:

```
Open
```

---

# Step 13: Run the Program

Click:

```
Run → Debug
```

or press the green **Run** button.

---

# Output

The following message will continuously appear on the PuTTY terminal:

```text
hello
hello
hello
hello
...
```

---

# Conclusion

In this experiment, UART communication was established between the STM32H755ZI-Q Nucleo board and a PC using the onboard ST-LINK Virtual COM Port. The microcontroller continuously transmitted the string `"hello"` every second, and the data was successfully displayed on PuTTY. This demonstrates the basic implementation of UART communication using USART3 in asynchronous mode on the STM32H755ZI-Q.
