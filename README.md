# Door Locking App using Arduino and ThinkerCAD
This project involves building a door locking system using an Arduino board, a servo motor, a buzzer, a keypad, and an LCD display. The system allows users to input a password via the keypad to either lock or unlock the door.

## Features
- **Password Management**: Users can set a password of up to 6 characters.
- **Door Locking/Unlocking**: The system controls a servo motor to lock or unlock the door based on the entered password.
- **Feedback**: Provides visual and audible feedback based on the entered password's correctness.

## Components Used
- Arduino Uno
- Servo Motor
- Buzzer
- 16x2 LCD Display
- Keypad (4x4)
- Resistors
- Jumper Wires

## Installation
1. Clone the repository:
   ```
   git clone https://github.com/username/repo-name.git
   ```
2. Connect the Arduino board to your computer via USB.
3. Open the Arduino IDE.
4. Upload the code (`door_locking_app.ino`) to your Arduino board.
5. Connect the components as per the circuit diagram.
6. Power on the Arduino board.

## Usage
1. Upon powering on, the LCD displays a welcome message.
2. The user is prompted to enter the password via the keypad.
3. Press the appropriate keys to enter the password. Press 'C' to reset the input.
4. Press 'D' to either lock or unlock the door, based on its current state.
5. Upon successful entry of the password, the door unlocks, and the LCD displays a corresponding message. If the password is incorrect, an error message is displayed.
6. After a delay, the system resets, ready for the next input.

## Circuit Diagram
You can find the diagram of the circut board [`here`](images/Board.png)

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributors
This project was developed by:
- [`Deyan Sirakov`](https://github.com/Deyan2306)
- [`Borislav Chernev`](https://github.com/BorislavChernev)
- [`George Pachedjiev`](https://github.com/GeorgePachedjiev)

## Feedback

For any suggestions, improvements, or issues, please [open an issue](https://github.com/4LG0R1THMS/PasswordDoorLock/issues).
