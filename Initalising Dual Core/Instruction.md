# STM32CubeMX Setup Guide

1. Choose the pins that need to be configured in **STM32CubeMX**.
 <img width="568" height="366" alt="image" src="https://github.com/user-attachments/assets/f0378420-a49a-485f-9bb9-f479c0cfab94" />

2. Assign the core that will control the selected pins:
   - Use the **left-side panel** in STM32CubeMX.
   - Under system core you can find GPIO , all the pins configured as gpio will be visible in the right side.
   - For example, if you selected a **GPIO** pin, navigate to the **GPIO** section to locate and configure the pin.
     <img width="1187" height="581" alt="image" src="https://github.com/user-attachments/assets/7797877e-d04a-4ab2-8b32-142095daac11" />


4. Click on any of the pin to assign the desired core (e.g., Cortex-M7 or Cortex-M4) to the selected peripheral or pin.Initially it will be free.
 <img width="1012" height="606" alt="image" src="https://github.com/user-attachments/assets/a6f7e798-30a3-4ba0-935c-41fd9638e336" />

  

5. Configure the project settings and generate the code.

6. Open the generated `main.c` file and write your application code in the appropriate **USER CODE** sections.

7. Select the appropriate debug configuration (e.g., **Cortex-M7**) before building and debugging the project.
<img width="1362" height="953" alt="image" src="https://github.com/user-attachments/assets/07321180-23a6-4037-9d57-1113c7578d4c" />
8.In debug configuration , under STM32 C/C++ application there will be list of project , choose your current project. Here the name of the project is Dual_core.
<img width="1191" height="688" alt="image" src="https://github.com/user-attachments/assets/11bb4601-11a1-4344-a880-1fa48fdb9dae" />
9. Choosing the M7 core ( Dual_core M7 ) to configure the debugging process.
10. In debugger section choose **halt all cores** and **shared st link**.
<img width="1150" height="647" alt="image" src="https://github.com/user-attachments/assets/c308af2e-6bb8-49fb-a5e9-ed0d2fdb45cc" />

<img width="1067" height="272" alt="image" src="https://github.com/user-attachments/assets/7e777a39-8c70-4312-8931-c16bcd9878ff" />

11.Choose the startup tab under that click on add and add the **CM4** file to debug . 
<img width="1280" height="802" alt="image" src="https://github.com/user-attachments/assets/afc931ef-de4e-451d-8686-92aa8076db6e" />
12. now we have to the same for CM4 but this time we have to check out the downloading under debugger option in **CM4** core. 
We have to change the port number such that the port on CM4 is different from CM7 by a factor of 4. 

13. set reset behaviour to none
14. Under cross trigger interface check all the tabs

<img width="842" height="657" alt="image" src="https://github.com/user-attachments/assets/6791ba5e-9aa0-42a6-8f5c-98987aebabfd" />

15.Now in the debugger section click on edit now check out the downlaod option , because core m7 's debugging process is already taking care of that. 
<img width="1260" height="722" alt="image" src="https://github.com/user-attachments/assets/1a61ce33-08b1-46f7-8a3b-7407d47f9174" />
16. Now debug Core M7 first then M4 .
17. Choose debug configuration choose core M7 and debug after that do the same for core m4.
<img width="1217" height="881" alt="image" src="https://github.com/user-attachments/assets/f8408408-7d28-4de0-9f94-07fa5a0250fc" />
18. After debugging both core you can see such a tab appearing in left side.
<img width="1307" height="913" alt="image" src="https://github.com/user-attachments/assets/3e1b45d8-3dc9-4990-9fe3-d2f3f667c738" />
19.Click while pressing ctrl to choose both the running threads and click on resume to run the cores at same time .
<img width="1837" height="602" alt="image" src="https://github.com/user-attachments/assets/d02250c8-1c2d-474d-9189-6bfef474f925" />
20. Now you can see both the cores at the debugging section.








