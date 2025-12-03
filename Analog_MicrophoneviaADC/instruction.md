 # STM32H755 + MAX9814 Analog Microphone Capture

This project samples audio from a MAX9814 microphone amplifier module using the ADC of an STM32H755ZIQ and stores the samples into a RAM buffer for later processing or streaming.

---

## 1. Hardware

### 1.1 Parts

- STM32H755ZIQ board (for example NUCLEO‑H755ZIQ)
- MAX9814 microphone amplifier module (electret mic + AGC)
- Jumper wires

### 1.2 Connections

- MAX9814 **VCC** → STM32 **3V3** (or 5 V if your module supports it)  
- MAX9814 **GND** → STM32 **GND**  
- MAX9814 **OUT** → STM32 **PA6** (configured as `ADC1_IN3`)  
- MAX9814 **GAIN**→leave floating (40dB) or tie to VCC(50dB) or to GND(60dB)
- MAX9814 **AR** → leave floating (default AGC timing)  

The MAX9814 output is an AC audio signal of about 2 Vpp centered at around 1.25 V, which sits safely inside the STM32 0–3.3 V ADC input range.

---

## 2. STM32CubeIDE / CubeMX Configuration

### 2.1 Enabling Clock

1. Open: Pinout & Configuration → System Core → RCC.  
2. In the “Mode” tab, set:
   - High Speed Clock (HSE) = Crystal/Ceramic Resonator.

### 2.2 ADC1: PA6 as analog input

1. **Pinout**

   - In **Pinout & Configuration**, set pin **PA6** to **ADC1_IN3**.

2. **ADC1 Mode**

   - Runtime context: **Cortex‑M7** checked  
   - Enable **IN3 Single‑ended** (all other INx disabled)

3. **ADC1 Parameter Settings**

   **ADC_Settings**

   - Mode: **Independent mode**  
   - Clock Prescaler: **Asynchronous clock /2** (`ADC_CLOCK_ASYNC_DIV2`)  
   - Resolution: **12‑bit** (`ADC_RESOLUTION_12B`)  
   - Scan Conversion Mode: **Disabled**  
   - Continuous Conversion Mode: **Disabled**  
   - Discontinuous Conversion Mode: **Disabled**  
   - End Of Conversion Selection: **End of single conversion**  
   - Overrun behaviour: **Overrun data preserved**
   - Left Bit Shift:**No bit shift**
   - Conversion Data Management Mode: **Regular Conversion data stored in DR register only**  
   - Low Power Auto Wait: **Disabled**

   **Regular Conversion**

   - Enable Regular Conversions: **Enable**  
   - Enable Regular Oversampling: **Disable**  
   - Number Of Conversion: **1**  
   - External Trigger Conversion Source: **Regular Conversion launched by software**  
   - External Trigger Conversion Edge: **None**
     <img width="1709" height="725" alt="image" src="https://github.com/user-attachments/assets/bfbd4971-5b02-4fb4-ac4b-d559f3bd99ac" />


   **Analog Watchdogs**

   - Disable Analog WatchDog1 / 2 / 3.

### 3. Clock configuration  
  (set as default) 
- System Clock Source: **HSI** (internal)  
- SYSCLK: **64 MHz**  
- AHB: **64 MHz**  
- APB1 Peripheral clock: **64 MHz**  
- APB1 Timer clocks: **64 MHz**

In the **Clock Configuration** view, verify that “To APB1 Timer clocks (MHz)” shows **64**.
<img width="1492" height="740" alt="Screenshot 2025-12-03 191154" src="https://github.com/user-attachments/assets/c624e12b-2d63-475c-94eb-2b056d9a9bdb" />


## 4. TIM3 Configuration (8 kHz sample rate)

### 4.1 Enable TIM3

- In **Pinout & Configuration → Timers**, enable **TIM3** as a basic timer (no channels).

### 4.2 TIM3 Mode

- Runtime context: **Cortex‑M7** checked  
- Slave Mode: **Disable**  
- Trigger Source: **Disable**  
- Clock Source: **Internal Clock**  
- Channel1–4: **Disable**

### 4.3 TIM3 Parameter Settings

**Counter Settings**

- Prescaler (PSC): **799**  
- Counter Mode: **Up**  
- Counter Period (ARR): **999**  
- Internal Clock Division: **No Division**  
- Auto‑reload preload: **Disable**

  General formula for timer frequency is:
  

f_{\text{update}} = \frac{f_{\text{timer\_clk}}}{(PSC + 1)(ARR + 1)}


Where:

- \(f_{\text{timer\_clk}}\) = timer input clock (Hz)  
- \(PSC\) = prescaler register value  
- \(ARR\) = auto‑reload register value  

With APB1 timer clocks at 64 MHz:
Example for this project (TIM3, 64 MHz timer clock, PSC = 799, ARR = 999):

\[
f_{\text{update}} = \frac{64\,000\,000}{(799+1)\times(999+1)} = 8000\ \text{Hz}
\]


**Trigger Output (TRGO)**

- Master/Slave Mode: **Disable**  
- Trigger Event Selection TRGO: **Reset**
<img width="1710" height="754" alt="image" src="https://github.com/user-attachments/assets/9b4ee705-61e3-455b-a261-0a215eadd905" />


### 3.4 TIM3 NVIC and DMA

- **NVIC Settings**: enable **TIM3 global interrupt**, default priority (0,0) is fine.
<img width="1703" height="719" alt="image" src="https://github.com/user-attachments/assets/f3b0b20e-7266-4812-8583-f3bf272c489f" />



## 4. User Code

Generate the code **“Project”** menu in the top bar and choose **“Generate Code”**
### Adding user code in `main.c`

1. **Add global buffer variables**

   - Find the block:

     ```
     /* USER CODE BEGIN PV */

     /* USER CODE END PV */
     ```

   - Replace it with:

     ```
     /* USER CODE BEGIN PV */
     #define BUF_LEN 1024

     uint16_t audio_buf[BUF_LEN];
     volatile uint32_t write_idx = 0;
     /* USER CODE END PV */
     ```

2. **Start peripherals in `main()`**

   - In `main()`, locate the “Initialize all configured peripherals” section:

     ```
     /* Initialize all configured peripherals */

     /* USER CODE BEGIN 2 */

     /* USER CODE END 2 */
     ```

   - Change it to:

     ```c
     /* Initialize all configured peripherals */
     MX_GPIO_Init();
     MX_ADC1_Init();
     MX_TIM3_Init();
     /* USER CODE BEGIN 2 */
     HAL_TIM_Base_Start_IT(&htim3);   // start TIM3 timer interrupts
     HAL_ADC_Start(&hadc1);           // optional initial ADC start
     /* USER CODE END 2 */
     ```

3. **Add the timer callback**

   - Scroll near the end of `main.c` and find:

     ```
     /* USER CODE BEGIN 4 */

     /* USER CODE END 4 */
     ```

   - Replace it with:

     ```c
     /* USER CODE BEGIN 4 */
     void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
     {
       if (htim->Instance == TIM3)
       {
         HAL_ADC_Start(&hadc1);
         HAL_ADC_PollForConversion(&hadc1, 1);
         uint16_t v = HAL_ADC_GetValue(&hadc1);

         audio_buf[write_idx] = v;
         write_idx = (write_idx + 1) % BUF_LEN;
       }
     }
     /* USER CODE END 4 */
     ```

4. **Build and flash**

   - Click **Project → Build Project** (or hammer icon).  
   - Start a debug session and run; `audio_buf` will now be filled with ADC samples from the MAX9814.
  <img width="1910" height="716" alt="image" src="https://github.com/user-attachments/assets/0cf700ce-294b-4001-b91b-726b6dcbd7b9" />

The STM32H755 is dual‑core (M7 + M4). CubeIDE can generate a **dual core boot synchronization** sequence guarded by `DUAL_CORE_BOOT_SYNC_SEQUENCE`. For this simple single‑core audio project, it is easier to disable that part.

5.**Disabling Dual core boot sinc**

  - in main.c locate the definition:
   ```c
   #define DUAL_CORE_BOOT_SYNC_SEQUENCE
   ```
   Comment it out (or delete it) so the dual‑core boot code is not compiled,Optionally remove or comment the boot‑sync code blocks wrapped with:
   ```c
   #if defined(DUAL_CORE_BOOT_SYNC_SEQUENCE)
   ...
   #endif /* DUAL_CORE_BOOT_SYNC_SEQUENCE */

   ```
Now you are ready to build And flash the code
### Expected Result
<img width="1910" height="747" alt="image" src="https://github.com/user-attachments/assets/c7668a0a-4a6c-48bd-8feb-0fc5aae86fdd" />







