# Introduction to DAC

Some microcontroller boards are equipped with a **DAC (Digital-to-Analog Converter)**.  
A DAC converts a given digital value into an analog voltage, using **3.3V as the reference**.

In this experiment, we are using the **Nucleo-H755ZI-Q** board, which is equipped with **2 DAC channels**.  
We are going to generate a **sine wave** using the DAC.

To create a sine wave, we will provide the DAC with values from a **lookup table**.  
The DAC on this board has a **12-bit resolution**, so the lookup table must also be designed using 12-bit values.

Since 12-bit is not a standard integer size, we use a **16-bit integer datatype** to store the lookup table values.

---

## Steps to Create the Lookup Table

- Since the maximum value supported by the DAC is **2¹²** (12-bit resolution),  
  the sine wave will reach its peak of **3.3V** when the DAC is given the digital value **4096**.
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
The table we are going to create will contain **4096 values**, mapping the entire **360°** of the sine wave into the range **0 to 4096**.  

Excel is employed to perform this otherwise tedious task efficiently.
<img width="915" height="727" alt="Screenshot 2025-11-27 115517" src="https://github.com/user-attachments/assets/2e5b2e2f-2d49-41b6-9966-59b608fc0669" />
We have limited the **maximum voltage to 3.1V** to provide a safety margin.

## Calculating DAC Values Using Excel

- We need to calculate the **DAC values** that produce the desired **V<sub>out</sub>**, such that it follows a sine curve.
- The table we create will contain **4096 values**, mapping the entire **360°** of the sine wave into the range **0 to 4096**.  
  Excel is used to perform this otherwise tedious task efficiently.
- We have limited the **maximum voltage to 3.1V** for a safety margin.
- Steps in Excel:
  1. Map **0° to 360°** into the range **0 to 4096**.
  2. Calculate **V<sub>out</sub>** for each degree using:

     ```
     f(x) = (3.3 / 2) * SIN(RADIANS(A2#)) + (3.3 / 2)
     ```

  3. Calculate the corresponding **DAC value** for each V<sub>out</sub>:

     ```
     DAC value = (Vout * 4095) / 3.3
     ```

  4. Round the values and add a **5% margin** for safety.









