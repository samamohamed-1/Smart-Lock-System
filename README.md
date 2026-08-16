Smart Lock System



A password-based smart lock system implemented using ATmega32, designed to demonstrate password authentication, access control, password management, and security handling in an embedded system environment.



The system uses a 4×4 matrix keypad for user input, a 16×2 LCD for user interaction, a servo motor to simulate the locking mechanism, EEPROM for password storage, and a buzzer for security alerts.



Features

&#x09;•	Password-based access authentication

&#x09;•	4-digit password input through a 4×4 matrix keypad

&#x09;•	Password masking during entry

&#x09;•	Delete functionality during password input

&#x09;•	Password change functionality

&#x09;•	Password storage using ATmega32 EEPROM

&#x09;•	Maximum of 3 incorrect password attempts

&#x09;•	30-second lockout after 3 failed attempts

&#x09;•	One additional attempt after the lockout period

&#x09;•	Forgot Password option using the stored EEPROM password

&#x09;•	Buzzer and security alert after all attempts are exhausted

&#x09;•	Servo motor control to simulate door locking and unlocking

&#x09;•	LCD-based system feedback and status messages



Simulation Components

&#x09;•	ATmega32 Microcontroller

&#x09;•	4×4 Matrix Keypad

&#x09;•	16×2 LCD

&#x09;•	Servo Motor

&#x09;•	Buzzer



Software \& Tools

&#x09;•	Embedded C

&#x09;•	Eclipse IDE

&#x09;•	Proteus 8 Professional

&#x09;•	AVR ATmega32

&#x09;•	AVR EEPROM Library



System Workflow



1\. Password Authentication



The system starts with the default password:



1234



The user enters the password through the keypad. The entered digits are displayed as \* on the LCD.



If the password is correct, the system displays:



Access Granted



The servo motor then moves to simulate unlocking the door.



2\. Password Change



After successful authentication, the system provides the option to change the password.

&#x09;•	1 → Change Password

&#x09;•	Any other key → Continue



The new password is stored in the ATmega32 EEPROM and becomes the active password during the current simulation.



3\. Failed Attempts \& Lockout



The system allows a maximum of 3 incorrect password attempts.



After the third failed attempt, the system enters a 30-second lockout period.



After the lockout, the user can choose:

&#x09;•	1 → Retry

&#x09;•	2 → Forgot Password



4\. Retry



Selecting Retry gives the user one additional password attempt.

&#x09;•	Correct password → Access Granted

&#x09;•	Incorrect password → Security alert is triggered



5\. Forgot Password



Selecting Forgot Password retrieves the stored password from the ATmega32 EEPROM and displays it on the LCD.



6\. Security Alert



If the additional attempt is incorrect, the system activates the buzzer and displays:



ALERT!



All attempts used



The system then stops to prevent further unauthorized attempts.



Project Structure
Smart-Lock-System/

│

├── Code/

│   ├── Application/

│   │   └── main.c

│   │

│   ├── Common/

│   │   ├── STD\_TYPES.h

│   │   └── BIT\_MATH.h

│   │

│   └── Drivers/

│       ├── DIO/

│       ├── KPD/

│       ├── LCD/

│       └── TIMER1/

│

├── Images/

│   └── smart-lock-circuit.png

│

├── Demo/

│   └── smart-lock-demo.mp4

│

├── lock system.pdsprj

└── README.md
How to Run

&#x09;1.	Open lock system.pdsprj using Proteus 8 Professional.

&#x09;2.	Run the simulation.

&#x09;3.	The default password is 1234.

&#x09;4.	Enter the password using the keypad.

&#x09;5.	Explore the authentication, password management, lockout, password recovery, servo control, and security alert features.



Drivers Attribution



The project uses pre-existing embedded drivers for DIO, Keypad, LCD, and Timer1.



These drivers were provided as part of the development environment and are included as dependencies required to build and run the system. They are not original implementations of this project.



Demo



The demo video demonstrates the complete system workflow, including:

&#x09;•	Password authentication

&#x09;•	Password change

&#x09;•	Incorrect password attempts

&#x09;•	30-second lockout

&#x09;•	Retry option

&#x09;•	Forgot Password

&#x09;•	Servo motor movement

&#x09;•	Buzzer and security alert

