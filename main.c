//#include "STD_TYPES.h"
//#include "DIO_Interface.h"
//#include "LCD_Interface.h"
//#include "KPD_Interface.h"
//#include <avr/eeprom.h>
//#include <util/delay.h>
//
///* === Configurations === */
//#define PASSWORD_LENGTH 4
//#define MAX_TRIES       3
//
//#define BUZZER_PORT     PORTA_ID
//#define BUZZER_PIN      PIN0
//
//#define LED_PORT        PORTA_ID
//#define LED_PIN         PIN1
//
//u8 defaultPassword[PASSWORD_LENGTH] = {'1','2','3','4'};
//u8 eepromAddress = 0;
//u8 enteredPassword[PASSWORD_LENGTH];
//
///* === LED Functions === */
//void LED_voidInit() {
//    DIO_voidSetPinDirection(LED_PORT, LED_PIN, PIN_OUTPUT);
//}
//
//void LED_voidOn() {
//    DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_HIGH);
//}
//
//void LED_voidOff() {
//    DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_LOW);
//}
//
///* === Buzzer Function (for piezo) === */
//void ActivateBuzzer(void) {
//    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
//    for (u8 i = 0; i < 100; i++) {
//        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
//        _delay_us(5000);
//        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_LOW);
//        _delay_us(5000);
//    }
//}
//
///* === EEPROM Functions === */
//void ReadPasswordFromEEPROM(u8 *pass) {
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        pass[i] = eeprom_read_byte((u8*)(eepromAddress + i));
//        if (pass[i] > '9' || pass[i] < '0') {
//            pass[i] = defaultPassword[i];
//        }
//    }
//}
//
//void SavePasswordToEEPROM(u8 *pass) {
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        eeprom_write_byte((u8*)(eepromAddress + i), pass[i]);
//    }
//}
//
///* === Password Input === */
//void GetPasswordFromUser(u8 *buffer) {
//    u8 key = 0;
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Enter Pass:");
//    LCD_voidGoToXY(1, 0);
//    for (u8 i = 0; i < PASSWORD_LENGTH;) {
//        key = KPD_voidGetPressedKey();
//        if (key != 0xFF && key >= '0' && key <= '9') {
//            buffer[i] = key;
//            LCD_voidWriteData('*');
//            i++;
//            while (KPD_voidGetPressedKey() != 0xFF);
//        }
//    }
//}
//void GetNEWPasswordFromUser(u8 *buffer) {
//    u8 key = 0;
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Enter NEW Pass:");
//    LCD_voidGoToXY(1, 0);
//    for (u8 i = 0; i < PASSWORD_LENGTH;) {
//        key = KPD_voidGetPressedKey();
//        if (key != 0xFF && key >= '0' && key <= '9') {
//            buffer[i] = key;
//            LCD_voidWriteData('*');
//            i++;
//            while (KPD_voidGetPressedKey() != 0xFF);
//        }
//    }
//}
//
//u8 CheckPassword(u8 *entered, u8 *stored) {
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        if (entered[i] != stored[i])
//            return 0;
//    }
//    return 1;
//}
//
//void Delay30Seconds(void) {
//    for (u8 i = 0; i < 30; i++)
//        _delay_ms(1000);
//}
//
//void ChangePassword() {
//    u8 newPassword[PASSWORD_LENGTH];
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Enter NEW Pass:");
//    LCD_voidGoToXY(1, 0);
//    GetNEWPasswordFromUser(newPassword);
//    SavePasswordToEEPROM(newPassword);
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Password Updated");
//    _delay_ms(1500);
//}
//
///* === Main === */
//int main(void) {
//    LCD_voidInit();
//    KPD_voidInit();
//    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
//    LED_voidInit();
//
//    u8 savedPassword[PASSWORD_LENGTH];
//    u8 tries = 0;
//
//    ReadPasswordFromEEPROM(savedPassword);
//
//    while (1) {
//        GetPasswordFromUser(enteredPassword);
//
//        if (CheckPassword(enteredPassword, savedPassword)) {
//            LCD_voidClear();
//            LCD_voidWriteString((u8*)"Access Granted");
//            LED_voidOn();
//            _delay_ms(2000);
//            LED_voidOff();
//            tries = 0;
//
//            LCD_voidClear();
//            LCD_voidWriteString((u8*)"Change Pass? 1=Y");
//
//            u8 opt = 0xFF;
//            for (u8 i = 0; i < 50; i++) { // 5 seconds
//                opt = KPD_voidGetPressedKey();
//                if (opt == '1') {
//                    ChangePassword();
//                    ReadPasswordFromEEPROM(savedPassword);
//                    break;
//                } else if (opt != 0xFF) {
//                    break;
//                }
//                _delay_ms(100);
//            }
//        } else {
//            tries++;
//            LCD_voidClear();
//            LCD_voidWriteString((u8*)"Wrong Password!");
//            _delay_ms(1500);
//
//            if (tries == MAX_TRIES) {
//                LCD_voidClear();
//                LCD_voidWriteString((u8*)"Wait 30 sec...");
//                Delay30Seconds();
//            } else if (tries > MAX_TRIES) {
//                if (CheckPassword(enteredPassword, savedPassword)) {
//                    LCD_voidClear();
//                    LCD_voidWriteString((u8*)"Access Granted");
//                    LED_voidOn();
//                    _delay_ms(2000);
//                    LED_voidOff();
//                    tries = 0;
//                } else {
//                    LCD_voidClear();
//                    LCD_voidWriteString((u8*)"ALERT!");
//                    ActivateBuzzer();
//                    _delay_ms(3000);
//                    LCD_voidClear();
//                    LCD_voidWriteString((u8*)"All attempts used");
//                    while(1);
//                }
//            }
//        }
//        _delay_ms(1000);
//    }
//}

//#include "STD_TYPES.h"
//#include "DIO_Interface.h"
//#include "LCD_Interface.h"
//#include "KPD_Interface.h"
//#include "TIMER1_Interface.h"
//#include <avr/eeprom.h>
//#include <util/delay.h>
//
//#define PASSWORD_LENGTH 4
//#define MAX_TRIES       3
//
//#define BUZZER_PORT     PORTA_ID
//#define BUZZER_PIN      PIN0
//
//u8 defaultPassword[PASSWORD_LENGTH] = {'1','2','3','4'};
//u8 eepromAddress = 0;
//u8 enteredPassword[PASSWORD_LENGTH];
//
//void ActivateBuzzer(void) {
//    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
//    for (u8 i = 0; i < 100; i++) {
//        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
//        _delay_us(5000);
//        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_LOW);
//        _delay_us(5000);
//    }
//}
//
//void ReadPasswordFromEEPROM(u8 *pass) {
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        pass[i] = eeprom_read_byte((u8*)(eepromAddress + i));
//        if (pass[i] > '9' || pass[i] < '0') {
//            pass[i] = defaultPassword[i];
//        }
//    }
//}
//
//void SavePasswordToEEPROM(u8 *pass) {
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        eeprom_write_byte((u8*)(eepromAddress + i), pass[i]);
//    }
//}
//
//void GetPasswordFromUser(u8 *buffer) {
//    u8 key = 0;
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Enter Pass:");
//    LCD_voidGoToXY(1, 0);
//    for (u8 i = 0; i < PASSWORD_LENGTH;) {
//        key = KPD_voidGetPressedKey();
//        if (key != 0xFF && key >= '0' && key <= '9') {
//            buffer[i] = key;
//            LCD_voidWriteData('*');
//            i++;
//            while (KPD_voidGetPressedKey() != 0xFF);
//        }
//    }
//}
//
//void GetNEWPasswordFromUser(u8 *buffer) {
//    u8 key = 0;
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Enter NEW Pass:");
//    LCD_voidGoToXY(1, 0);
//    for (u8 i = 0; i < PASSWORD_LENGTH;) {
//        key = KPD_voidGetPressedKey();
//        if (key != 0xFF && key >= '0' && key <= '9') {
//            buffer[i] = key;
//            LCD_voidWriteData('*');
//            i++;
//            while (KPD_voidGetPressedKey() != 0xFF);
//        }
//    }
//}
//
//u8 CheckPassword(u8 *entered, u8 *stored) {
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        if (entered[i] != stored[i])
//            return 0;
//    }
//    return 1;
//}
//
//void Delay30Seconds(void) {
//    for (u8 i = 0; i < 30; i++)
//        _delay_ms(1000);
//}
//
//void ChangePassword() {
//    u8 newPassword[PASSWORD_LENGTH];
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Enter NEW Pass:");
//    LCD_voidGoToXY(1, 0);
//    GetNEWPasswordFromUser(newPassword);
//    SavePasswordToEEPROM(newPassword);
//    LCD_voidClear();
//    LCD_voidWriteString((u8*)"Password Updated");
//    _delay_ms(1500);
//}
//
//void ShowSavedPassword() {
//    u8 saved[PASSWORD_LENGTH];
//    ReadPasswordFromEEPROM(saved);
//    LCD_voidClear();
//    LCD_voidWriteString((u8 *)"Saved Pass:");
//    LCD_voidGoToXY(1, 0);
//    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
//        LCD_voidWriteData(saved[i]);
//    }
//    _delay_ms(4000);
//}
//
///* === Servo Functions === */
//void Servo_Init() {
//    M_TIMER1_voidPwm1Init();
//    M_TIMER1_voidPwm1SetTop();
//    M_TIMER1_voidPwm1Start();
//}
//
//void Servo_GotoAngle(u8 degree) {
//
//    u8 ocr_val = ((u32)degree * (25 - 5)) / 180 + 5;
//    for (u8 val = 5; val <= ocr_val; val++) {
//        M_TIMER1_voidPwm1SetDutyCycle(val);
//        _delay_ms(100);
//    }
//}
//
//void Servo_Reset() {
//    for (s8 val = 25; val >= 5; val--) {
//        M_TIMER1_voidPwm1SetDutyCycle(val);
//        _delay_ms(100);
//    }
//}
//
//int main(void) {
//    LCD_voidInit();
//    KPD_voidInit();
//    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
//    Servo_Init();
//
//    u8 savedPassword[PASSWORD_LENGTH];
//    u8 tries = 0;
//
//    ReadPasswordFromEEPROM(savedPassword);
//
//    while (1) {
//        GetPasswordFromUser(enteredPassword);
//
//        if (CheckPassword(enteredPassword, savedPassword)) {
//            LCD_voidClear();
//            LCD_voidWriteString((u8*)"Access Granted");
//
//            Servo_GotoAngle(90);
//            _delay_ms(2000);
//
//            tries = 0;
//
//            LCD_voidClear();
//            LCD_voidWriteString((u8*)"Change Pass? 1=Y");
//
//            u8 opt = 0xFF;
//            for (u8 i = 0; i < 50; i++) {
//                opt = KPD_voidGetPressedKey();
//                if (opt == '1') {
//                    ChangePassword();
//                    ReadPasswordFromEEPROM(savedPassword);
//                    break;
//                } else if (opt != 0xFF) {
//                    break;
//                }
//                _delay_ms(100);
//            }
//
//        } else {
//            tries++;
//            LCD_voidClear();
//            LCD_voidWriteString((u8*)"Wrong Password!");
//            _delay_ms(1500);
//
//            if (tries == MAX_TRIES) {
//                LCD_voidClear();
//                LCD_voidWriteString((u8*)"Wait 30 sec...");
//                Delay30Seconds();
//
//                LCD_voidClear();
//                LCD_voidWriteString((u8*)"1: Retry");
//                LCD_voidGoToXY(1, 0);
//                LCD_voidWriteString((u8*)"2: Forgot");
//
//                u8 opt = 0xFF;
//                while (opt == 0xFF) {
//                    opt = KPD_voidGetPressedKey();
//                }
//
//                if (opt == '2') {
//                    ShowSavedPassword();
//                    tries = 0;
//                }
//
//            } else if (tries > MAX_TRIES) {
//                if (CheckPassword(enteredPassword, savedPassword)) {
//                    LCD_voidClear();
//                    LCD_voidWriteString((u8*)"Access Granted");
//                    Servo_GotoAngle(90);
//                    _delay_ms(2000);
//                    tries = 0;
//                } else {
//                    LCD_voidClear();
//                    LCD_voidWriteString((u8*)"ALERT!");
//                    ActivateBuzzer();
//                    _delay_ms(3000);
//                    LCD_voidClear();
//                    LCD_voidWriteString((u8*)"All attempts used");
//                    while(1);
//                }
//            } else {
//                Servo_Reset();
//            }
//        }
//
//        _delay_ms(1000);
//    }
//}
//
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KPD_Interface.h"
#include "TIMER1_Interface.h"
#include <avr/eeprom.h>
#include <util/delay.h>

#define PASSWORD_LENGTH 4
#define MAX_TRIES       3

#define BUZZER_PORT     PORTA_ID
#define BUZZER_PIN      PIN0

u8 defaultPassword[PASSWORD_LENGTH] = {'1','2','3','4'};
u8 eepromAddress = 0;
u8 enteredPassword[PASSWORD_LENGTH];

void ActivateBuzzer(void) {
    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
    for (u8 i = 0; i < 100; i++) {
        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
        _delay_us(5000);
        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_LOW);
        _delay_us(5000);
    }
}

void ReadPasswordFromEEPROM(u8 *pass) {
    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
        pass[i] = eeprom_read_byte((u8*)(eepromAddress + i));
        if (pass[i] > '9' || pass[i] < '0') {
            pass[i] = defaultPassword[i];
        }
    }
}

void SavePasswordToEEPROM(u8 *pass) {
    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
        eeprom_write_byte((u8*)(eepromAddress + i), pass[i]);
    }
}

void GetPasswordFromUser(u8 *buffer) {
    u8 key = 0;
    LCD_voidClear();
    LCD_voidWriteString((u8*)"Enter Pass:");
    LCD_voidGoToXY(1, 0);
    for (u8 i = 0; i < PASSWORD_LENGTH;) {
        key = KPD_voidGetPressedKey();
        if (key != 0xFF && key >= '0' && key <= '9') {
            buffer[i] = key;
            LCD_voidWriteData('*');
            i++;
            while (KPD_voidGetPressedKey() != 0xFF);
        }
    }
}

void GetNEWPasswordFromUser(u8 *buffer) {
    u8 key = 0;
    LCD_voidClear();
    LCD_voidWriteString((u8*)"Enter NEW Pass:");
    LCD_voidGoToXY(1, 0);
    for (u8 i = 0; i < PASSWORD_LENGTH;) {
        key = KPD_voidGetPressedKey();
        if (key != 0xFF && key >= '0' && key <= '9') {
            buffer[i] = key;
            LCD_voidWriteData('*');
            i++;
            while (KPD_voidGetPressedKey() != 0xFF);
        }
    }
}

u8 CheckPassword(u8 *entered, u8 *stored) {
    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
        if (entered[i] != stored[i])
            return 0;
    }
    return 1;
}

void Delay30Seconds(void) {
    for (u8 i = 0; i < 30; i++)
        _delay_ms(1000);
}

void ChangePassword() {
    u8 newPassword[PASSWORD_LENGTH];
    LCD_voidClear();
    LCD_voidWriteString((u8*)"Enter NEW Pass:");
    LCD_voidGoToXY(1, 0);
    GetNEWPasswordFromUser(newPassword);
    SavePasswordToEEPROM(newPassword);
    LCD_voidClear();
    LCD_voidWriteString((u8*)"Password Updated");
    _delay_ms(1500);
}

void ShowSavedPassword() {
    u8 saved[PASSWORD_LENGTH];
    ReadPasswordFromEEPROM(saved);
    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Saved Pass:");
    LCD_voidGoToXY(1, 0);
    for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
        LCD_voidWriteData(saved[i]);
    }
    _delay_ms(4000);
}

/* === Servo Functions === */
void Servo_Init() {
    M_TIMER1_voidPwm1Init();
    M_TIMER1_voidPwm1SetTop();
    M_TIMER1_voidPwm1Start();
}
void Servo_GotoAngle(u8 angle) {
    if (angle > 180) angle = 180;
    angle=180 - angle;
    u16 ocr_value = 31 + ((u32)angle * 32) / 180;

    M_TIMER1_voidPwm1SetDutyCycle(ocr_value);
}




void Servo_Reset() {
    Servo_GotoAngle(0);
}

int main(void) {
    LCD_voidInit();
    KPD_voidInit();
    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
    Servo_Init();
    Servo_Reset();

    u8 savedPassword[PASSWORD_LENGTH];
    u8 tries = 0;

    ReadPasswordFromEEPROM(savedPassword);

    while (1) {
        GetPasswordFromUser(enteredPassword);

        if (CheckPassword(enteredPassword, savedPassword)) {
            LCD_voidClear();
            LCD_voidWriteString((u8*)"Access Granted");

            for (u8 angle = 0; angle <= 90; angle += 10) {
                Servo_GotoAngle(angle);
                _delay_ms(200);
            }

            _delay_ms(2000);
            Servo_Reset();

            tries = 0;

            LCD_voidClear();
            LCD_voidWriteString((u8*)"Change Pass? 1=Y");

            u8 opt = 0xFF;
            for (u8 i = 0; i < 50; i++) {
                opt = KPD_voidGetPressedKey();
                if (opt == '1') {
                    ChangePassword();
                    ReadPasswordFromEEPROM(savedPassword);
                    break;
                } else if (opt != 0xFF) {
                    break;
                }
                _delay_ms(100);
            }

        } else {
            tries++;
            LCD_voidClear();
            LCD_voidWriteString((u8*)"Wrong Password!");
            _delay_ms(1500);

            if (tries == MAX_TRIES) {
                LCD_voidClear();
                LCD_voidWriteString((u8*)"Wait 30 sec...");
                Delay30Seconds();

                LCD_voidClear();
                LCD_voidWriteString((u8*)"1: Retry");
                LCD_voidGoToXY(1, 0);
                LCD_voidWriteString((u8*)"2: Forgot");

                u8 opt = 0xFF;
                while (opt == 0xFF) {
                    opt = KPD_voidGetPressedKey();
                }

                if (opt == '2') {
                    ShowSavedPassword();
                    tries = 0;
                }

            } else if (tries > MAX_TRIES) {
                if (CheckPassword(enteredPassword, savedPassword)) {
                    LCD_voidClear();
                    LCD_voidWriteString((u8*)"Access Granted");

                    for (u8 angle = 0; angle <= 90; angle += 10) {
                        Servo_GotoAngle(angle);
                        _delay_ms(200);
                    }

                    _delay_ms(2000);
                    Servo_Reset();
                    tries = 0;

                } else {
                    LCD_voidClear();
                    LCD_voidWriteString((u8*)"ALERT!");
                    ActivateBuzzer();
                    _delay_ms(3000);
                    LCD_voidClear();
                    LCD_voidWriteString((u8*)"All attempts used");
                    while (1);
                }
            } else {
                Servo_Reset();
            }
        }

        _delay_ms(1000);
    }
}
