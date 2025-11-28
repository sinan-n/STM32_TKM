# Variable Frequency Sine Wave

We have already created a sine wave with fixed frequency. In real world applications we need more than that. The frequency of the wave should change as per the user requirement.

We are effectively implementing **DDS (Direct Digital Synthesis)**. Surely we will use a lookup table, the sampling rate is changed to get the required frequency.

The board we are using in the example is **H755ZI-Q**. Timer 1 Channel 1 is drawn to Pin **PA8**, we will be using this configuration to create the sine wave. We need another timer to update the duty cycle in the first timer. An interrupt will be called whenever the latter overflows. When the interrupt runs slow, the frequency will be low, and when the interrupt is called frequently, the frequency also increases.

So in conclusion there will be **two timers**:  
- one for creating the sine wave  
- another to update the duty cycle.

---

## Procedures

1) Select the pin with Timer capabilities and configure it to **TIMx CHx** in the given options. Also configure the core that controls the timer.
 <img width="1517" height="776" alt="Screenshot 2025-11-28 105708" src="https://github.com/user-attachments/assets/afd61510-287d-446f-9fc1-09e1ac4c6571" />


2) We need two timers, so repeat this process. Make sure to choose **another timer**. Changing the timer is different from changing the channel, so make sure you have chosen a different timer.

3) One of the timers is going to call an interrupt whenever it overflows. To enable that, we need to enable **NVIC** of that particular timer. You can find NVIC settings in the configuration tab.
   <img width="1204" height="668" alt="image" src="https://github.com/user-attachments/assets/6494aa6b-5dc2-4530-84d7-8b8625027398" />

4) Now we need to know how the interrupt is going to vary the frequency. We are using a lookup table with 256 values. Each time the second timer overflows it calls an interrupt, and whenever it does so, a value is incremented to a 16 bit long varaible which then vaires  the duty cycle according to the lookup table.

We initiate a variable to keep the index of the value to be loaded in the first timer to vary the duty cycle.

Suppose the interrupt is called 256 times in a second, then the first timer creates a sine wave with frequency 1 Hz. Whenever the 256 values are loaded into the first timer, a period will be completed in the sine wave.

Here you can see two sine waves: when the red one is halfway through the period, the yellow wave completes its period. This is because the rate of interrupt of the yellow wave is twice the rate of interrupt of the red wave.
<img width="1089" height="562" alt="Screenshot 2025-11-28 113703" src="https://github.com/user-attachments/assets/3325dbe1-5b18-449c-a04b-620d22ec21e4" />

5) We know the relation between the frequency of the sine wave and the update frequency from the previous experiment. That is given by this formula:

$$
F_{\text{sine}} = \frac{F_{\text{update}}}{No. of samples}
$$

6) The frequency of update is determined by the second timer. Whenever the second timer overflows it calls an interrupt, so the frequency of update is given by the equation:

$$
\mathcal{F}_{\text{update}} = 
\frac{\mathcal{F}_{\text{timerclk}}}
{\left(\text{Prescaler} + 1\right)\left(\text{ARR} + 1\right)}
$$

7) We employ another 16-bit long variable that is going to increment the index of the lookup table.  
We trim the 16-bit variable into 8 bits by considering only the 8 MSBs.

This changes the number of samples into:

**$$
\text{No of samples}_{\text{effective}} = \frac{256 \times 256}{\text{Increment Value}}
$$**

8) Factoring all these incorporations and using the equation we already know, we can derive the value to be incremented in the variable that carries the index of the lookup table.

So we get the equation:

$$
\text{Increment Value} =
\frac{
\mathcal{F}_{\text{sine}} \times (\text{Prescaler}+1) \times (\text{ARR}+1) \times 65536
}{
\mathcal{F}_{\text{timerclk}}
}
$$






