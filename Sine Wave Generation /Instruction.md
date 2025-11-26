# Sine Wave Generation

 Microcontrollers are digital and  cannot directly generate analog signals, but they can **mimic analog waveforms** using **PWM (Pulse Width Modulation)**. To produce a sine wave, we make use of the PWM capability of the microcontroller.

To do this, we follow the same steps used for setting up a PWM signal. The idea is simple:  
we **change the CCR value at fixed intervals**, which changes the duty cycle. This produces an output whose effective amplitude varies with time. If the CCR values are changed in a pattern that resembles a sine curve, the resulting output will also resemble a **sine wave**.

We use a **lookup table with 256 values** to generate the sine wave. This table contains pre-calculated values that will be written into the CCR register at the required update rate so that the output waveform appears sinusoidal.

---

## Steps

1. **Choose a pin** and select the corresponding **TIMx CHx** function from the available options.  
2. **Configure the timer.**  
   In this example, **PA8** is used with **TIM1 Channel 1**.
   <img width="1896" height="782" alt="image" src="https://github.com/user-attachments/assets/eaa92125-151c-4378-bb3d-422fd0ed26d0" />
3. Now we have to set up the ARR register and the prescaler.

4. The frequency of the sine wave is determined by:

  $$
F_{\text{sin}} = \frac{F_{\text{update}}}{\text{Number of samples}}
$$

   Here we are updating with a frequency of **1 kHz**, since the delay time is fixed to **1 ms**.  
   The user will not have an option to change this update frequency once it is fixed in the code.

   We have **256 samples**, so in the overall picture the frequency of the generated sine wave will be:

   **3.9 Hz**
   
![WhatsApp Image 2025-11-26 at 17 20 34_bffc780d](https://github.com/user-attachments/assets/c8bc90ae-8f75-4c4d-bf01-9dc1bf249014)

## Conclusion

In this experiment, we successfully generated a sine wave using the PWM capability of a microcontroller. By varying the **CCR (Capture/Compare Register)** values according to a **256-value lookup table**, we were able to approximate a sine waveform.  

The frequency of the generated sine wave is determined by the formula:

**F<sub>sin</sub> = F<sub>update</sub> / Number of samples**

For our setup:  
- **Update frequency (F<sub>update</sub>)** = 1 kHz  
- **Number of samples** = 256  

This results in a sine wave frequency of approximately:

**F<sub>sin</sub> = 1000 / 256 ≈ 4 Hz**

**Conclusion:**  
Using PWM and a lookup table, a digital microcontroller can effectively approximate analog signals. By adjusting the CCR values at fixed intervals, the output waveform closely resembles a sine wave, demonstrating a simple and efficient method for generating low-frequency analog waveforms from digital hardware



