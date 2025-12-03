# Experiment: Analog-to-Digital Conversion (ADC) with STM32H7

## Step 1: Objective
To interface a 10kΩ potentiometer with the STM32H755ZI-Q microcontroller using the internal 12-bit ADC. The goal is to read the changing analog voltage, convert it to a digital value, and control an LED based on a specific voltage threshold.

## Step 2: Hardware Requirements
* **Microcontroller:** NUCLEO-H755ZI-Q
* **Input:** 10kΩ Potentiometer
* **Output:** On-board User LED (Green)
* **Connecting Wires**

## Step 3: Pinout Configuration

| Component | Pin Name | Port/Pin | Function |
| :--- | :--- | :--- | :--- |
| **Potentiometer (Wiper)** | A0 (Arduino Header) | PA3 | ADC1_IN15 |
| **Potentiometer (VCC)** | 3V3 | - | Power (Do NOT use 5V) |
| **Potentiometer (GND)** | GND | - | Ground |
| **User LED** | LD1 | PA5 | GPIO Output |

## Step 3: Theory
The STM32H7 features a high-precision Successive Approximation Register (SAR) ADC.
* **Voltage Divider:** The potentiometer acts as a voltage divider, outputting a voltage between 0V and 3.3V depending on the knob position.
* **ADC Resolution:** We are using **12-bit resolution**. This divides the 3.3V range into 65,536 discrete steps ($2^{12}$).
    * 0V = Digital Value `0`
    * 3.3V = Digital Value `4095`


## Step 4: STM32CubeIDE Configuration
1.  **Pin Setup:**
    * Set **PA3** to `ADC1_IN15`.
    * Set **PA5** to `GPIO_Output` (Label: LED_GREEN).
2.  **Clock Configuration:**
    * Ensure the ADC clock mux is connected to a valid source (e.g., PLL2) in the Clock Configuration tab.
### System Core
* **Core:** Cortex-M7 (CM7)
* **Power Supply:** Direct SMPS
* **Clock:** PLL enabled, peripheral clocks active.

### ADC1 Settings
* **Resolution:** 16-bit (0 - 65535)
* **Mode:** Independent
* **Scan Conversion:** Disabled
* **Continuous Conversion:** **DISABLED** (Crucial for manual polling stability)
* **Overrun Behavior:** Data Preserved


## Step 5: Code Implementation (main.c)

The logic uses a "Polling" method. We manually start the ADC, wait for it to finish, read the value, and then stop it to prevent overrun errors.

**Variable Declaration:**

uint32_t adc_value = 0;
int run = 0;



while (1)
{
    // 1. Start the ADC Conversion manually
    HAL_ADC_Start(&hadc1);

    // 2. Wait for conversion to complete (Poll)
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
    {
        // 3. Read the raw 16-bit value
        adc_value = HAL_ADC_GetValue(&hadc1);
    }

    // 4. Threshold Logic (Hysteresis/Control)
    // 30000 is approximately 1.5V (Midpoint of 3.3V)
    if (adc_value > 30000)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // LED ON
    }
    else
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // LED OFF
    }

    // 5. Stop ADC to reset state for next loop
    HAL_ADC_Stop(&hadc1);
    
    // 6. Loop Delay
    run++;
    HAL_Delay(50);
}

