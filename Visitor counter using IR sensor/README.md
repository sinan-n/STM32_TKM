# STM32H755ZIQ – IR Sensor Detection (PC6) + LED Blink (PB0)

This project demonstrates how to interface an **IR obstacle sensor** with the  
**Nucleo-H755ZIQ (STM32H755 dual-core)** board and blink the onboard LED when an object is detected.

# 1. Hardware Connections

| STM32 Pin | IR Sensor Pin | Description |
|----------|----------------|-------------|
| **PC6**  | OUT            | Digital output from IR sensor |
| **3.3V** | VCC            | Sensor power |
| **GND**  | GND            | Ground |

### LED Connected to PB0  
PB0 → On-board LED (Green LED)

---

#  2. IOC Configuration (STM32CubeMX)

Open the `.ioc` file and configure:

---

## **GPIO Configuration**
### **1. PC6 → GPIO_Input**
### **2. PB0 → LED Output**
file-save

# 3. Coding in `main.c`

Inside **main.c (CM7 core)**, modify as follows:

### Add global variables at the top:
```c
int status;
int count;
```
### Add the following code inside the `while(1)` loop:
```c
status=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6);

	    if(status==0)

	    {

	    	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,SET);
	    	HAL_Delay(500);
	    	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,RESET);

	    	count=count+1;
}
```
# Project → Build Project
#  Run → Debug Configurations




