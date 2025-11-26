# Lab Experiment: Control LED with Inbuilt Switch (User Button)

### Experiment Objective
To configure the Cortex-M7 core of the STM32H755ZIQ to turn on the Green LED (LD1) when the User Button (Blue Button) is pressed.


### Step 1: Hardware Identification
Identify the input and output components on the NUCLEO-H755ZI-Q board.

- **Input (Switch):** Blue User Button (B1) → Connected to Pin **PC13**.
- **Output (LED):** Green LED (LD1) → Connected to Pin **PB0**.


### Step 2: Create Project
1. Launch STM32CubeIDE.
2. Go to **File > New > STM32 Project**.
3. Select **Board Selector** and search for **NUCLEO-H755ZI-Q**.
4. Select the board and click **Next**.
5. Name the project (e.g., `Button_LED_Lab`).
6. Initialize peripherals with default mode: **Yes**.


### Step 3: Configure Pinout (.ioc file)
Configure one pin as Input (Button) and one as Output (LED), assigning both to the Cortex-M7 core.

### Configure LED (PB0):
- Locate **PB0**
- Set to **GPIO_Output**
- Right-click PB0 > **Pin Reservation** > **Cortex-M7**
<img width="1567" height="829" alt="Screenshot 2025-11-26 121235" src="https://github.com/user-attachments/assets/03a7fe6e-b351-477b-bf7c-c733a4b491e9" />

### Configure Button (PC13):
- Locate **PC13**
- Set to **GPIO_Input**
- Right-click PC13 > **Pin Reservation** > **Cortex-M7**
<img width="1577" height="834" alt="image" src="https://github.com/user-attachments/assets/bd9ef21f-1539-4cd1-a61b-f8d1499f83c5" />

Save the `.ioc` file to generate the code.



### Step 4: Implement Code (Cortex-M7)
Follow these specific points to implement the logic:

1. In the Project Explorer, expand the **CM7** project folder.
2. Navigate: `CM7 > Core > Src`
3. Open **main.c**
4. Clear Default Code: Delete the existing `main()` function or replace the file contents.
5. Copy & Paste: Insert the code block below into the file.


### Step 5: Build and Run
1. Build the **CM7** project.
2. Debug as **STM32 C/C++ Application**
3. Press **Resume (Play)**.
4. Test: Press and hold the Blue Button to light up the Green LED.
