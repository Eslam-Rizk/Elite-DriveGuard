# Elite Drive-guard
Technologies such as Advanced Driver Assistance Systems (ADAS) have proven to be effective in improving road safety by providing drivers with real-time information and assistance to avoid accidents. By working together to improve road safety, we can reduce the number of accidents and make our roads safer for everyone. Elite Drive-Guard aims to address this problem by developing and implementing a comprehensive ADAS system that incorporates several key features, including Adaptive Cruise Control (ACC), Automatic Emergency Braking (AEB), Lane Keeping Assist System (LKAS), Lane Departure Warning (LDW) and manage the update software remotely by including firmware over the air (FOTA). Our system will be designed to be reliable by using an operating system (free rtos), effective, and user-friendly, providing drivers with real-time information and assistance to reduce the risk of accidents caused by driver error. 

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
    - [Firmware Over-the-Air (FOTA) Update System](#firmware-over-the-air-fota-update-system)
    - [Adaptive Cruise Control (ACC)](#adaptive-cruise-control-acc)
    - [Automatic Emergency Braking (AEB)](#automatic-emergency-braking-aeb)
    - [Lane Keeping System (LKS)](#lane-keeping-system-lks)
    - [Adaptive Light Control (ALC)](#adaptive-light-control-alc)
    - [Remote Bluetooth Control](#remote-bluetooth-control)
3. [Hardware Components](#hardware-components)
4. [Schematic Layout and PCB](#schematic-layout-and-pcb)
5. [Finite State Machine](#finite-state-machine)
6. [1. Firmware Over-the-Air (FOTA) Update System](#1-firmware-over-the-air-fota-update-system)
7. [2. Adaptive Cruise Control (ACC)](#2-adaptive-cruise-control-acc)
8. [3. Automatic Emergency Braking (AEB)](#3-automatic-emergency-braking-aeb)
9. [4. Lane Keeping System (LKS)](#4-lane-keeping-system-lks)
10. [5. Adaptive Light Control (ALC)](#5-adaptive-light-control-alc)
11. [Remote Bluetooth Control](#remote-bluetooth-control-1)
12. [Installation](#installation)
13. [Usage](#usage)
14. [Contributing](#contributing)
15. [Acknowledgements](#acknowledgements)
16. [License](#license)
17. [Contact](#contact)

## Introduction
The Elite Drive-guard is an Advanced Driver Assistance System (ADAS) prototype designed to enhance driver safety and improve overall driving experience. This documentation provides an overview of its features and functionalities.

## Demo

[Demo.mp4](https://github.com/Eslam-Rizk/Elite-DriveGuard/assets/70345162/ff03d651-7cc1-480c-8376-18a8223640a6)

## Features

- ### Firmware Over-the-Air (FOTA) Update System
  The FOTA update system ensures that the ADAS remains up-to-date with the latest software enhancements and improvements.
  
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/FOTA.png" width=550>
- ### Adaptive Cruise Control (ACC)
  Adaptive Cruise Control (ACC) is a driver assistance feature that maintains a predetermined speed and safe following distance from preceding vehicles.
  
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/ACC.png" width=550>
- ### Automatic Emergency Braking (AEB)
  AEB is a critical safety feature designed to mitigate collision risks by autonomously applying brakes when an imminent collision is detected.
  
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/AEB.jpg" width=550>
- ### Lane Keeping System (LKS)
  LKS aids in maintaining proper lane positioning and preventing inadvertent lane departures.
  
   <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/LKS.png" width=550>
- ### Adaptive Light Control (ALC)
  Adaptive Light Control (ALC) optimizes visibility during varying lighting conditions by dynamically adjusting the intensity of the vehicle's lighting system.
  
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/ALC.png" width=550>
- ### Remote Bluetooth Control
  The Remote Bluetooth Control is acheived using a mobile application providing full control for the driver over the vehicle via Bluetooth connection.
  
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/Bluetooth.jpg" width=550>

## Hardware Components

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/components.png" width=700>

## Schematic Layout and PCB

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/schematic.png" width=700>
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/PCB.png" width=700>
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/PCB.jpeg" width=700>
refer to GERBER directory.

## Finite State Machine

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/FSM.jpg" width=700>

## 1. Firmware Over-the-Air (FOTA) Update System
- ### Operation:
  
  **a. OTA**:
  - The system utilizes a Raspberry Pi to actively monitor a designated server at predefined intervals, typically every 5 seconds, to check for available updates.
    
  - Upon detecting an update, the system automatically initiates the download process and activates an LED indicator, providing a visual prompt for the user.
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/checking%20updates.png" width=550>

  - Users can decide whether to proceed with the update or defer it for a later time, facilitated through a Bluetooth command interface.
  
  - Upon user confirmation, the raspberry pi sends commands to the STM32 via USB-ttl converter connected on the port "/dev/ttyUSB0" of the raspberry pi. Then, the STM32 system enters Bootloader mode, initiating a soft restart and commencing a 15-second countdown prior to executing the update procedure.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/sending%20to%20bootloader.png" width=550>
  
  - After installing the new update, the bootloader jumps to the main Application and the Raspberry pi starts checking for updates again.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/update%20finished.png" width=550>

  **b. BOOTLOADER**:
  
  Bootloaders are small programs typically stored in the memory of a microcontroller or embedded system that are designed to handle the loading and updating of application firmware. They play a crucial role in enabling firmware updates and ensuring the reliability and security of embedded systems.
  
Our Bootloader is stored in the first 2 sectors of the flash memory and has its own starup code and vector table. The application is stored in sectors 2, 3, 4, and 5 and also has its own starup code and vector table.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/flash%20architecture.png" width=550>

1. **Bootloader Working Steps**:
   - **Initialization**: On boot, The bootloader starts Timer3, to wait for a predefined period, typically 15 seconds, to check for available updates.
   - **Check for Update**: During the timer period, the bootloader monitors for incoming update requests or firmware packages. This can be done through various communication interfaces such as UART, SPI, or Ethernet but in our case we are using UART interface.
   - **Firmware Update Process**: If an update is detected, the bootloader utilizes Flash Memory Interface (FMI) to write the received firmware update to designated flash memory sectors reserved for application firmware which are sectors 2, 3, 4, and 5.
   - **Verify and Install Update**: Once each update record is received and before writting it to flash memory, the bootloader verifies the integrity of the record to ensure its validity and completeness via CRC encryption.
   - **Jump to Application**: If the update is successful, the bootloader deinitializes the system, switches the processor to execute the newly updated application firmware, and jumps to its entry point.
   - **Fallback Mechanism**: If no update is received within the specified timeout period, the bootloader proceeds to deinitialize the system and jumps to the entry point of the existing application firmware.
   
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/bootloader%20algorithm.jpg" width=550>
   
2. **Vector Table Offset**:
   - In the startup code of the application firmware, a new vector table is utilized by applying a vector table offset to the base address. This ensures that the application firmware uses the correct interrupt vector table, especially if the bootloader resides in a different memory region.

By following this process, bootloaders enable seamless firmware updates and maintain the reliability and performance of embedded systems, such as the Advanced Driver Assistance System (ADAS) described in this project.

## 2. Adaptive Cruise Control (ACC)
- ### Operation:
  - Ultrasonic sensor send the measured distance via UART to the MCU
  - When the freeRTOS schedular run the ACC task + ACC flag was set by bluetooth, If the distance is from 10cm to 50 cm, the car moves with adaptive speed, and If the distance is more than 50 cm, the car moves with maximum speed.
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/ACC%20Algorihm.png" width=550>
  

## 3. Automatic Emergency Braking (AEB)
- ### Operation:
  - AEB is triggered when the distance between the vehicle and an obstacle falls below a predefined threshold, typically 10 cm.
  - Upon activation, AEB promptly halts the vehicle's motion, simultaneously activating a distinct alarm for 3 seconds to alert surrounding individuals and illuminating a rear LED for enhanced visibility.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/AEB%20algorithm.png" width=550>
  

## 4. Lane Keeping System (LKS)
- ### Operation:
  - Implemented through infrared (IR) sensors, LKS continuously monitors lane boundaries.
  - When the right sensor detects a transition to a black surface (binary 1) and the left sensor detects a transition to a white surface (binary 0), the system prompts corrective action, such as steering left.
  - Conversely, if the left sensor detects a black surface and the right sensor detects a white surface, the system initiates corrective action to steer right, ensuring the vehicle remains within the designated lane.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/IR%20algorithm.png" width=550>



## 5. Adaptive Light Control (ALC)
- ### Operation:
  - LDR sensor sends the measured Value to the MCU.
  - When the freeRTOS schedular run the ALC task, If the value more than or equal to 93, head light on with maximum lighting.
  - If the value less than 20, head light off.
  - If the value more than or equal to 80 and less than 93, head light on with adaptive lighting.
  - If the value more than or equal to 20 and less than 80, head light on with adaptive with less lighting.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/LDR%20algorithm.png" width=550>



## Remote Bluetooth Control
- ### Operation:
The Elite Drive-guard system can be fully controlled via Bluetooth using the following commands:
- Send ‘J’ via UART to set ACC flag and activate ACC mode.
- Send ‘B’ via UART to set FOTA flag and install the software update.
- Send ‘H’ via UART to clear ACC flag and FOTA flag.
- Send ‘F’ via UART to MCU to make the car move forward.
- Send ‘L’ via UART to MCU to make the car move Right.
- Send ‘R’ via UART to MCU to make the car move Left.
- Send ‘S’ via UART to MCU to make the car stop.
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/Bluetooth2.jpg" width=700>


## Real Time Operating System (RTOS)

- ### Operation:
The RTOS employed in this project is freeRTOS and provides a robust framework for managing concurrent tasks in real-time embedded systems. By effectively prioritizing tasks and utilizing event flags for synchronization, the system ensures the timely and reliable execution of critical functionalities without compromising performance or safety

**Tasks Overview:**
1. **Bluetooth Task:** Handles Bluetooth communication functionalities.
2. **FOTA Task:** Manages Firmware Over-The-Air (FOTA) updates.
3. **ALC Task:** Controls Adaptive Lane Control functionalities.
4. **ACC Task:** Manages Adaptive Cruise Control functionalities.
5. **LKS Task:** Controls Lane Keeping System functionalities.
6. **AEB Task:** Manages Autonomous Emergency Braking functionalities.

**Task Prioritization:**
Tasks are prioritized based on their criticality and time sensitivity:
- **Lowest Priority:** Bluetooth, FOTA, and ALC tasks.
- **Medium Priority:** ACC Task.
- **Higher Priority:** LKS Task.
- **Highest Priority:** AEB task.

**Event Flags:**
Event flags are utilized within each task to facilitate inter-task communication and synchronization. These flags allow tasks to efficiently coordinate their activities and respond to events promptly. For instance, the ACC task may wait for a specific flag indicating the presence of an obstacle, while the Bluetooth task may wait for a flag indicating data reception.

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/RTOS.jpg" width=700>


## Installation

To install the Elite Drive-guard system, follow these steps:

1. Clone the repository to your local machine.
2. Configure the necessary hardware components according to the provided specifications.
3. Compile and upload the firmware to the target device.
4. Run the system and ensure proper functionality.


## Contributing

Contributions to the Elite Drive-guard project are welcome! If you'd like to contribute, please follow these guidelines:

1. Fork the repository and create a new branch for your feature or bug fix.
2. Make your changes and ensure they adhere to the project's coding standards.
3. Test your changes thoroughly to ensure they function as expected.
4. Submit a pull request, describing the changes you've made and the rationale behind them.

## Acknowledgements

Special thanks to Information Technololgy Institute (ITI) and to my group instructors: 
    
1. Eng. Mahmoud Sayed 
2. Eng. Sondos Ghieth 
3. Eng. Mohamed Haggag 
4. Eng. Yousef Ahmad

and to my team members: 

1. Mohammed Ammar 
2. Abdullah Ahmed 
3. Adham Fawzy 
4. Amr Ghalab


who've helped make this project possible, and also to Eng. Ahmed Abdelghafar whose FOTA code was customized to meet project's specifications.

## License

This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.


## Contact

For questions, feedback, or inquiries, please contact me at eslam.mahhmoud18130@gmail.com or [Linkedin profile](https://www.linkedin.com/in/eslam-rizk-6a029a145/).
