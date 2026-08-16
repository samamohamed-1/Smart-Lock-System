# Smart Lock System

A password-based smart lock system implemented using **ATmega32**, designed to demonstrate password authentication, access control, password management, and security handling in an embedded system environment.

The system uses a **4×4 matrix keypad** for user input, a **16×2 LCD** for user interaction, a **servo motor** to simulate the locking mechanism, **EEPROM** for password storage, and a **buzzer** for security alerts.

## Features

- Password-based access authentication
- 4-digit password input through a 4×4 matrix keypad
- Password masking during entry
- Delete functionality during password input
- Password change functionality
- Password storage using ATmega32 EEPROM
- Maximum of 3 incorrect password attempts
- 30-second lockout after 3 failed attempts
- One additional attempt after the lockout period
- Forgot Password option using the stored EEPROM password
- Buzzer and security alert after all attempts are exhausted
- Servo motor control to simulate door locking and unlocking
- LCD-based system feedback and status messages

## Simulation Components

- ATmega32 Microcontroller
- 4×4 Matrix Keypad
- 16×2 LCD
- Servo Motor
- Buzzer

## Software & Tools

- Embedded C
- Eclipse IDE
- Proteus 8 Professional
- AVR ATmega32
- AVR EEPROM Library

## System Workflow

### 1. Password Authentication

The system starts with the default password:

`1234`

The user enters the password through the keypad. The entered digits are displayed as `*` on the LCD.

If the password is correct, the system displays:

`Access Granted`

The servo motor then moves to simulate unlocking the door.

### 2. Password Change

After successful authentication, the system provides the option to change the password.

- `1` → Change Password
- Any other key → Continue

The new password is stored in the ATmega32 EEPROM and becomes the active password during the current simulation.

### 3. Failed Attempts & Lockout

The system allows a maximum of **3 incorrect password attempts**.

After the third failed attempt, the system enters a **30-second lockout period**.

After the lockout, the user can choose:

- `1` → Retry
- `2` → Forgot Password

### 4. Retry

Selecting **Retry** gives the user one additional password attempt.

- Correct password → Access Granted
- Incorrect password → Security alert is triggered

### 5. Forgot Password

Selecting **Forgot Password** retrieves the stored password from the ATmega32 EEPROM and displays it on the LCD.

### 6. Security Alert

If the additional attempt is incorrect, the system activates the buzzer and displays:

`ALERT!`

`All attempts used`

The system then stops to prevent further unauthorized attempts.

## How to Run

1. Open `lock system.pdsprj` using **Proteus 8 Professional**.
2. Run the simulation.
3. The default password is `1234`.
4. Enter the password using the keypad.
5. Explore the authentication, password management, lockout, password recovery, servo control, and security alert features.

## Drivers Attribution

The project uses pre-existing embedded drivers for **DIO, Keypad, LCD, and Timer1**.

These drivers were provided as part of the development environment and are included as dependencies required to build and run the system. They are **not original implementations of this project**.

## Demo

The demo video demonstrates the complete system workflow, including:

- Password authentication
- Password change
- Incorrect password attempts
- 30-second lockout
- Retry option
- Forgot Password
- Servo motor movement
- Buzzer and security alert
