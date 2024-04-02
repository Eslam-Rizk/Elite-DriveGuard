# Elite Drive-guard

## Introduction
The Elite Drive-guard is an Advanced Driver Assistance System (ADAS) prototype designed to enhance driver safety and improve overall driving experience. This documentation provides an overview of its features and functionalities.

## Features

### 1. Firmware Over-the-Air (FOTA) Update System
- **Functionality**: The FOTA update system ensures that the ADAS remains up-to-date with the latest software enhancements and improvements.
- **Operation**:
  - The system utilizes a Raspberry Pi to actively monitor a designated server at predefined intervals, typically every 5 seconds, to check for available updates.
  - Upon detecting an update, the system automatically initiates the download process and activates an LED indicator, providing a visual prompt for the user.
  - Users can decide whether to proceed with the update or defer it for a later time, facilitated through a Bluetooth command interface.
  - Upon user confirmation, the system enters Bootloader mode, initiating a soft restart and commencing a 15-second countdown prior to executing the update procedure.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/FOTA.png" width=700>

### 2. Adaptive Cruise Control (ACC)
- **Functionality**: Adaptive Cruise Control (ACC) is a driver assistance feature that maintains a predetermined speed and safe following distance from preceding vehicles.
- **Operation**:
  - Ultrasonic sensor send the measured distance via UART to the MCU
  - When the FREE RTOS schedular run the ACC task + ACC flag was set by bluetooth
  - If the distance is from 10cm to 50 cm, the car moves with adaptive speed.
  - If the distance is more than 50 cm, the car moves with maximum speed.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/ACC.png" width=700>

### 3. Automatic Emergency Braking (AEB)
- **Functionality**: AEB is a critical safety feature designed to mitigate collision risks by autonomously applying brakes when an imminent collision is detected.
- **Operation**:
  - AEB is triggered when the distance between the vehicle and an obstacle falls below a predefined threshold, typically 10 cm.
  - Upon activation, AEB promptly halts the vehicle's motion, simultaneously activating a distinct alarm for 3 seconds to alert surrounding individuals and illuminating a rear LED for enhanced visibility.
  <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/AEB.jpg" width=700>

### 4. Lane Keeping System (LKS)
- **Functionality**: LKS aids in maintaining proper lane positioning and preventing inadvertent lane departures.
- **Operation**:
  - Implemented through infrared (IR) sensors, LKS continuously monitors lane boundaries.
  - When the right sensor detects a transition to a black surface (binary 1) and the left sensor detects a transition to a white surface (binary 0), the system prompts corrective action, such as steering left.
  - Conversely, if the left sensor detects a black surface and the right sensor detects a white surface, the system initiates corrective action to steer right, ensuring the vehicle remains within the designated lane.
 <img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/LKS.png" width=700>


### 5. Adaptive Light Control (ALC)
- **Functionality**: Adaptive Light Control (ALC) optimizes visibility during varying lighting conditions by dynamically adjusting the intensity of the vehicle's lighting system.
- **Operation**:
  - LDR sensor sends the measured Value to the MCU.
  - When the FREE RTOS schedular run the ALC task
  - If the value more than or equal to 93, head light on with maximum lighting
  - If the value less than 20, head light off
  - If the value more than or equal to 80 and less than 93, head light on with adaptive lighting
  - If the value more than or equal to 20 and less than 80, head light on with adaptive with less lighting
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/ALC.png" width=700>


## Bluetooth Control
The Elite Drive-guard system can be fully controlled via Bluetooth using the following commands:
- Send ‘J’ via UART to set ACC flag and activate ACC mode.
- Send ‘B’ via UART to set FOTA flag and install the software update.
- Send ‘H’ via UART to clear ACC flag and FOTA flag.
- Send ‘F’ via UART to MCU to make the car move forward.
- Send ‘L’ via UART to MCU to make the car move Right.
- Send ‘R’ via UART to MCU to make the car move Left.
- Send ‘S’ via UART to MCU to make the car stop.
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/Bluetooth.jpg" width=700><img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/Bluetooth2.jpg" width=700>

## Hardware Components

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/components.png" width=700>

## Schematic Layout and PCB

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/schematic.png" width=700>
<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/PCB.png" width=700>

## Finite State Machine

<img src="https://github.com/Eslam-Rizk/Elite-DriveGuard/blob/main/pictures/FSM.jpg" width=700>


## Installation

To install the Elite Drive-guard system, follow these steps:

1. Clone the repository to your local machine.
2. Configure the necessary hardware components according to the provided specifications.
3. Compile and upload the firmware to the target device.
4. Run the system and ensure proper functionality.

## Usage

To use the Elite Drive-guard system, follow these instructions:

1. Power on the device and ensure all components are properly connected.
2. Use the provided interface to interact with the system and access its features.
3. Refer to the user manual for detailed instructions on configuring and customizing the system settings.


## Contributing

Contributions to the Elite Drive-guard project are welcome! If you'd like to contribute, please follow these guidelines:

1. Fork the repository and create a new branch for your feature or bug fix.
2. Make your changes and ensure they adhere to the project's coding standards.
3. Test your changes thoroughly to ensure they function as expected.
4. Submit a pull request, describing the changes you've made and the rationale behind them.

## Acknowledgements

Special thanks to [contributors](CONTRIBUTORS.md) who have helped make this project possible.

## Contact

For questions, feedback, or inquiries, please contact [project maintainer](mailto:example@example.com).
