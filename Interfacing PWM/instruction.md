# External LED Dimming with PWM (STM32)

This guide explains how to set up PWM to dim an external LED using STM32 microcontrollers.

---

## Steps:

1. **Choose the GPIO pin**  
   - Refer to the user manual to select a GPIO pin to drive the external LED.  

2. **Select the Timer Channel**  
   - Choose `TIMx_CHx` from the options provided by the IDE.  
   - Example: `PA15` is used as the output pin.  

3. **Assign the Timer Core**  
   - Under the **Timers** section, assign the core to the timer you selected.  

4. **Open Timer Configuration**  
   - Click on the selected `TIMx` to see **Configuration** and **Mode** tabs.  

5. **Select Clock Source**  
   - In the **Mode** tab, select **Internal Clock** as the clock source.
   <img width="1552" height="785" alt="image" src="https://github.com/user-attachments/assets/e6eb0de5-8ad9-4709-9670-45d6f18d10ed" />

  

6. **Set PWM Frequency and Period**  
   - The frequency and period of the PWM are controlled in the **Configure** section.  
   - Registers such as `ARR` and `CCR` are listed here to manipulate the PWM signal.
  
7. **Set PWM Frequency for Experiment**  
   - For this experiment, we are making a PWM of frequency **1 kHz**.  
   - The **PSC** and **ARR** values are calculated using the PWM frequency equation:  

  $$
  f_{PWM} = \frac{f_{timer}}{(PSC + 1) \cdot (ARR + 1)}
  $$

8. **Timer Clock Frequency**  
   - The frequency of the timer, $f_{timer}$, can be found from the **Clock Configuration** section in your IDE.
   <img width="1895" height="741" alt="Screenshot 2025-11-26 122408" src="https://github.com/user-attachments/assets/d64d6eec-de89-47dd-99c9-52528cc83cf6" />


9. **Writing CCR Values to Dim the LED**  
   - In the code, we write values to the **CCR register** to control the LED brightness.  


---

## Register Functions

- **ARR (Auto-Reload Register):** Timer counts from 0 → ARR.  
- **CCR (Capture/Compare Register):** Output remains HIGH until counter reaches CCR. Logic can be inverted if needed.  
- After CCR, output goes LOW until ARR.  
- Then it repeats (PWM cycle).  

---

## Formulas

- **PWM Frequency:**  


$$
f_{PWM} = \frac{f_{timer}}{(PSC + 1) \cdot (ARR + 1)}
$$

- **Duty Cycle:**  

$$
\text{Duty \%)} = \frac{\text{CCR}}{\text{ARR}+1} \times 100\%
$$

Where:  
- **PSC** = Timer Prescaler  
- **ARR** = Auto-Reload Register value  
- **CCR** = Compare value  

---

> Adjusting `CCR` changes the LED brightness. Increasing `CCR` increases the duty cycle (LED stays ON longer), and vice versa.
