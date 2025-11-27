# INMP441 + STM32H755 (CM7) – SAI1, 48 kHz

This project shows how to connect an INMP441 I²S MEMS microphone to an STM32H755ZI (Cortex‑M7 core) using the SAI1 peripheral in master‑receive mode, capturing 24‑bit audio at 48 kHz into a RAM buffer using polling (no DMA).

---

## Hardware

- MCU board: STM32H755ZI‑based Nucleo/Discovery (CM7 core used)
- Microphone: INMP441 I²S MEMS microphone (3.3 V)

### Wiring

INMP441 → STM32H755 board:

- `VDD` → `3V3`
- `GND` → `GND`
- `L/R` → `GND` (select left channel)
- `WS`  → `PE4` (SAI1_FS_A – LRCLK)
- `SCK` → `PE5` (SAI1_SCK_A – bit clock)
- `SD`  → `PE6` (SAI1_SD_A – data in)

Notes:

- Keep wires short.

---

## STM32CubeMX / STM32CubeIDE Configuration

### 1. RCC – enable HSE

1. Open **System Core → RCC**.
2. Set:
   - **High Speed Clock (HSE)** = `Crystal/Ceramic Resonator`.
   - Leave LSE disabled.

### 2. System clock 

In the **Clock Configuration** tab:

- Set **SYSCLK source** = `HSE` (25 MHz on the STM32H755 Nucleo/Discovery).
- Keep AHB/APB dividers at `/1` for simplicity.

### 3. Enable SAI1 (first)

1. Open **Pinout & Configuration → Multimedia → SAI1**.
2. Enable **SAI1_A** for the **Cortex‑M7** runtime context.
3. Cube will map:
   - `PE4` → `SAI1_FS_A`
   - `PE5` → `SAI1_SCK_A`
   - `PE6` → `SAI1_SD_A`

### 4. SAI1 mode and protocol

Go to **SAI1 → Parameter Settings → SAI A**:

1. Set the core mode/protocol first:
   - **Audio Mode** = `Master Receive`
   - **Protocol** = `I2S Standard`

2. Then configure parameters:

   - **Synchronization Inputs** = `Asynchronous`
   - **Output Mode** = `Mono`
   - **Data Size** = `24 Bits`
   - **Number of Slots (only even values)** = `2`

(Clock source and frequency will be set correctly after PLL2 is configured.)

### 5. SAI clock via PLL2

Still in **Clock Configuration**:

1. Configure **PLL2** (assuming HSE = 25 MHz) to output 48 MHz on PLL2P:

   - `DIVM2 = 25`
   - `DIVN2 = 384`
   - `DIVP2 = 8`

   This yields:  
   `PLL2P = 25 MHz / 25 * 384 / 8 = 48 MHz`.

2. Under **SAI1 Clock Mux**, select **PLL2P**.  
   The label “To SAI1 (MHz)” should show `48`.

### 6. Final SAI1 parameters

Return to **Pinout & Configuration → SAI1 → Parameter Settings (SAI A)**:

- **Clock Source** = `SAI PLL Clock`
- **Audio Frequency** = `48 kHz`
- Confirm that:
  - **Real Audio Frequency** ≈ `48 kHz`
  - **Error between selected** is close to `0 %`

Other fields:

- **FIFO Threshold** = `Empty`
- **Master Clock No Divider** = `Enabled`
- **Master Clock Over Sampling** = `Enabled`
- **Mono/Stereo** = `Mono`
- **Companding Mode** = `No companding`



### 7. Generate code

- Click **Generate Code** to create the project for the CM7 core.

---

## Application Code 

In `main.c`, user variables:

```c
#define MIC_BUF_LEN 512u

uint32_t MicBuf[MIC_BUF_LEN]; // raw 32‑bit words from SAI (24‑bit audio)
int32_t MicSamples[MIC_BUF_LEN]; // converted signed samples
HAL_StatusTypeDef sai_status;
```

After `HAL_Init();`, `SystemClock_Config();`, `MX_GPIO_Init();`, and `MX_SAI1_Init();` in `main()`:

```c
while (1)
{
// Blocking receive of MIC_BUF_LEN 32‑bit words from SAI1
sai_status = HAL_SAI_Receive(&hsai_BlockA1,
(uint8_t *)MicBuf,
MIC_BUF_LEN,
0xFFFFFF); // large timeout
if (sai_status == HAL_OK)
{
    // Convert raw 32‑bit words (top 24 bits used) to signed samples
    for (uint32_t i = 0; i < MIC_BUF_LEN; i++)
    {
        MicSamples[i] = ((int32_t)MicBuf[i]) >> 8;
    }

    // MicSamples[] now holds one block of audio samples.
    // You can inspect them in Live Expressions or transmit via UART.
}
else
{
    Error_Handler();
}
}
```

Key parts of the auto‑generated `MX_SAI1_Init` (for reference):

```c
static void MX_SAI1_Init(void)
{
hsai_BlockA1.Instance = SAI1_Block_A;
hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_RX;
hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
hsai_BlockA1.Init.NoDivider = SAI_MCK_OVERSAMPLING_DISABLE;
hsai_BlockA1.Init.MckOverSampling = SAI_MCK_OVERSAMPLING_DISABLE;
hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
hsai_BlockA1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_48K;
hsai_BlockA1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
hsai_BlockA1.Init.MonoStereoMode = SAI_MONOMODE;
hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;

if (HAL_SAI_InitProtocol(&hsai_BlockA1,
SAI_I2S_STANDARD,
SAI_PROTOCOL_DATASIZE_24BIT,
2) != HAL_OK)
{
Error_Handler();
}
}
```

---

## How to Use

1. Build and flash the CM7 application to the STM32H755 board.
2. In STM32CubeIDE, open **Live Expressions** and add:
   - `MicBuf[0] .. MicBuf[10]`
   - `MicSamples[0] .. MicSamples[10]`
3. Run the program. Each time `HAL_SAI_Receive` completes, the buffers update.
4. Speak or clap near the INMP441; you should see `MicSamples[]` change around zero.

---
### Viewing samples in Live Expressions (STM32CubeIDE)

1. Start a **Debug** session for the CM7 project.
2. Open the Live Expressions view:
   - In the menu bar, go to **Window → Show View → Other…**
   - Expand **Debug** and select **Live Expressions**, then click **Open**.
3. Add variables to watch:
   - In the Live Expressions view, click the **“Add new expression”** line.
   - Type `MicBuf[0]`, press **Enter**.
   - Repeat for `MicBuf[1]`, `MicBuf[2]`, or add a range like `MicBuf[0..31]` if your IDE supports it.
   - Add `MicSamples[0]`, `MicSamples[1]`, etc. the same way.
4. Run the program:
   - Click **Resume** (green play button).
   - After a moment, pause execution; the values in `MicBuf[]` and `MicSamples[]` will update each time `HAL_SAI_Receive` finishes.
   - Speak or clap near the microphone and watch the numbers change around zero.



- SAI configuration:
<img width="1699" height="882" alt="Screenshot 2025-11-27 213639" src="https://github.com/user-attachments/assets/75a54ee5-b5ff-4fd6-8bb1-0900e3484b3a" />

- RCC:
<img width="1708" height="909" alt="Screenshot 2025-11-27 213712" src="https://github.com/user-attachments/assets/0525b3f9-3593-496c-888b-c2a49337936f" />

- Clock configuration:
<img width="1677" height="820" alt="image" src="https://github.com/user-attachments/assets/2ec06628-2b3f-4eda-a672-3813f9f6cd56" />

- Expected result:
<img width="1444" height="672" alt="Screenshot 2025-11-27 204541" src="https://github.com/user-attachments/assets/4700b885-d93e-45d4-976b-7403cc0d41ae" />



