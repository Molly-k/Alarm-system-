# Motion Detection Handler

This project contains the implementation of a motion detection handler using an STM32 microcontroller. The handler activates a buzzer for 60 seconds when motion is detected via a PIR sensor.

## Files
- `motion_detection.c`: Contains the main function to handle motion detection and buzzer activation.

## Components
- **STM32 Nucleo-F446RE**: The development board used for the project.
- **PIR Motion Sensor**: Detects motion and triggers the alarm.
- **Buzzer**: Provides audible alerts for detected motion.
- **GPIO Pins**: Used for interfacing with the PIR sensor and the buzzer.

## Functionality
The motion detection handler continuously monitors the state of a PIR sensor. When motion is detected, it activates a buzzer for a specified duration (60 seconds in this case) and then deactivates the buzzer. The process is repeated each time motion is detected.


### Additional Notes
1. **Wiring and Pin Configuration**: Ensure the PIR sensor and buzzer are connected correctly to the GPIO pins as defined in the code (`GPIOC, GPIO_PIN_12` for the PIR sensor and `GPIOC, GPIO_PIN_9` for the buzzer).
2. **ARM and Disarm Functionality**: The `armed` variable is assumed to be managed elsewhere in the application to control when the motion detection is active.

This README should help users understand the purpose, functionality, and usage of the motion detection handler code. Feel free to adjust any details to better fit your project specifics.
