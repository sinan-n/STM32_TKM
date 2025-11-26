Experiment: Control LED with Inbuilt Switch (User Button)

Experiment Objective: To configure the Cortex-M7 core of the STM32H755ZIQ to turn on the Green LED (LD1) when the User Button (Blue Button) is pressed.

Procedure:

Step 1: Hardware Identification

Identify the input and output components on the NUCLEO-H755ZI-Q board.

Input (Switch): Blue User Button (B1) -> Connected to Pin PC13.

Output (LED): Green LED (LD1) -> Connected to Pin PB0.

Step 2: Create Project

Launch STM32CubeIDE.

Create a new STM32 Project for board NUCLEO-H755ZI-Q.

Initialize peripherals with default mode: Yes.

Step 3: Configure Pinout (.ioc file)

We need to configure one pin as Input (Button) and one as Output (LED), and assign both to the Cortex-M7 core.

Open the .ioc file.

Configure LED (PB0):

Locate PB0.

Set to GPIO_Output.

Right-click PB0 > Pin Reservation > Cortex-M7.

Configure Button (PC13):

Locate PC13.

Set to GPIO_Input.

Right-click PC13 > Pin Reservation > Cortex-M7.

Save the .ioc file to generate the code.

Step 4: Implement Code (Cortex-M7)

Follow these specific points to implement the logic:

Locate the File: In the Project Explorer on the left, expand the CM7 project folder.

Navigate: Go to CM7 > Core > Src.

Open Editor: Double-click on main.c to open it.

Clear Default Code: Delete the existing main() function (or the entire file contents if you want to paste the complete file below).

Copy & Paste: Copy the complete code block provided below and paste it into your main.c file.

Verify Logic: Ensure the while(1) loop contains the HAL_GPIO_ReadPin check for the button state.
