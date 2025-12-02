# Introduction to DAC

Some microcontroller boards are equipped with a **DAC (Digital-to-Analog Converter)**.  
A DAC converts a given digital value into an analog voltage, using **3.3V as the reference**.

In this experiment, we are using the **Nucleo-H755ZI-Q** board, which is equipped with **2 DAC channels**.  
We are going to generate a **sine wave** using the DAC.

To create a sine wave, we will provide the DAC with values from a **lookup table**.  
The DAC on this board has a **8-bit resolution**, so the lookup table must also be designed using 8-bit values.

Since 8-bit is  a standard integer size, we use a **8-bit integer datatype** to store the lookup table values.

---

## Steps to Create the Lookup Table

- Since the maximum value supported by the DAC at 8 bit resolution  is **2¹²** (12-bit resolution),  
  the sine wave will reach its peak of **3.3V** when the DAC is given the digital value **255**.
  <img width="1334" height="497" alt="Screenshot 2025-11-27 104618" src="https://github.com/user-attachments/assets/7746427b-b063-4778-a8d3-14cb0bfd2953" />


- The generated sine curve will have **no negative peaks** because the DAC cannot internally generate negative voltages.  
  Therefore, our sine wave will only exist in the **positive voltage range**, without negative half-cycles.

  - At point **B**, sin(0) = 0, but since we are shifting the wave upward, the value becomes **3.3 / 2**.

- At point **C**, sin(90°) = 1, which gives the maximum peak voltage of **3.3V**.

- At point **E**, sin(270°) = -1.  
  After shifting the wave upward by 3.3 units, the output at this point becomes **0V**.

So effectively, our sine wave can be expressed as:

**F(x) = 3.3 · sin(θ) + 3.3**
Now, we need to calculate the **DAC values** that must be assigned to produce the desired **V<sub>out</sub>**, such that it follows a sine curve.

We can use the capabilities of **Excel** to generate these values.  
The table we are going to create will contain **256 values**, mapping the entire **360°** of the sine wave into the range **0 to 255**.  

Excel is employed to perform this otherwise tedious task efficiently.
<img width="971" height="738" alt="image" src="https://github.com/user-attachments/assets/c185b332-f4ec-4361-817e-0bc264def4df" />

We have limited the **maximum voltage to 3.1V** to provide a safety margin.

## Calculating DAC Values Using Excel

- We need to calculate the **DAC values** that produce the desired **V<sub>out</sub>**, such that it follows a sine curve.
- The table we create will contain **256 values**, mapping the entire **360°** of the sine wave into the range **0 to 255**.  
  Excel is used to perform this otherwise tedious task efficiently.
- We have limited the **maximum voltage to 3.1V** for a safety margin.
- Steps in Excel:
  1. Map **0° to 360°** into the range **0 to 256**.
  2. Calculate **V<sub>out</sub>** for each degree using:
  
     ```
     V_out = (3.3 / 2) * SIN(RADIANS(A2#)) + (3.3 / 2)
     ```

  3. Calculate the corresponding **DAC value** for each V<sub>out</sub>:

     ```
     DAC value = (Vout * 255) / 3.3
     ```

  4. Round the values and add a **5% margin** for safety.
  5. You can find a copy of the Excel sheet containing the DAC values here:  
[ADC values.xlsx](https://github.com/sinan-n/STM32_TKM/blob/main/Introduction_To_DAC/ADC%20values%20(2).xlsx)

These values will be used in the **lookup table** for creating the sine wave.

---

## Configuration

1. The **H755ZI-Q board** has 2 DAC pins: **PA4** and **PA5**.  
   In this example, we are using **PA4**. Refer to the user manual to find the DAC pins on other boards.

2. Under the **Mode** tab, choose **"Only external pin"** in the **"OUT1 connected to"** option.

3. Generate the `main.c` file.

4. Insert the lookup table into the code between:

   ```c
   /* USER CODE BEGIN PV */
   ...
   /* USER CODE END PV */
5. These values will now be used to **create a sine curve** by varying the **amplitude of the output voltage** at **Pin PA4**.  

> Note: The **frequency** of this sine wave will **not** be calculated in this experiment. This will be covered in a separate experiment.

## Conclusion
![WhatsApp Image 2025-11-27 at 15 26 41_c86577d4](https://github.com/user-attachments/assets/e16fcacb-39d5-44b9-8b46-426245d6f26f)


In this experiment, we successfully generated a **DAC-based sine wave** using a lookup table with **8-bit resolution**. By assigning pre-calculated DAC values to the output pin (PA4), we were able to vary the amplitude to approximate a sine waveform.

The main formulas used were:

1. **Sine wave voltage (shifted upward):**

$$
V_{out} = \frac{V_{max}}{2} \cdot \sin(\theta) + \frac{V_{max}}{2}
$$

where $$\(V_{max} = 3.3V\).$$

2. **DAC value calculation from the desired output voltage:**

$$
DAC_{value} = \frac{V_{out} \cdot 255}{V_{max}}
$$

Since we are using **8-bit resolution**, the DAC can take values from 0 to 255.

> By using these formulas, we mapped the sine wave into **8-bit DAC values**, stored in a **lookup table**, and produced the analog output. The maximum voltage was limited to **3.1V** for safety.













