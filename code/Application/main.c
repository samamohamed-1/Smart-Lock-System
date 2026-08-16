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

u8 defaultPassword[PASSWORD_LENGTH] = {'1', '2', '3', '4'};
u8 eepromAddress = 0;
u8 enteredPassword[PASSWORD_LENGTH];


/* =========================================================
 *                      Buzzer
 * ========================================================= */

void ActivateBuzzer(void)
{
    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);

    for (u8 i = 0; i < 100; i++)
    {
        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_HIGH);
        _delay_us(5000);

        DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, PIN_LOW);
        _delay_us(5000);
    }
}


/* =========================================================
 *                    EEPROM Functions
 * ========================================================= */

void ReadPasswordFromEEPROM(u8 *pass)
{
    for (u8 i = 0; i < PASSWORD_LENGTH; i++)
    {
        pass[i] = eeprom_read_byte((u8 *)(eepromAddress + i));

        /* If EEPROM contains invalid data, use default password */
        if (pass[i] > '9' || pass[i] < '0')
        {
            pass[i] = defaultPassword[i];
        }
    }
}


void SavePasswordToEEPROM(u8 *pass)
{
    for (u8 i = 0; i < PASSWORD_LENGTH; i++)
    {
        eeprom_write_byte((u8 *)(eepromAddress + i), pass[i]);
    }
}


/* =========================================================
 *                Password Input Functions
 * ========================================================= */

/*
 * Keypad:
 * 'c' = Delete / Backspace
 *
 * Example:
 * 1 2 3 c 4
 * Result = 124
 */

void GetPasswordFromUser(u8 *buffer)
{
    u8 key = 0;
    u8 i = 0;

    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Enter Pass:");
    LCD_voidGoToXY(1, 0);

    while (i < PASSWORD_LENGTH)
    {
        key = KPD_voidGetPressedKey();

        if (key != 0xFF)
        {
            /* Delete / Backspace */
            if (key == 'c')
            {
                if (i > 0)
                {
                    i--;

                    buffer[i] = 0;

                    /* Remove last '*' from LCD */
                    LCD_voidGoToXY(1, i);
                    LCD_voidWriteData(' ');

                    /* Return cursor to deleted position */
                    LCD_voidGoToXY(1, i);
                }
            }

            /* Numeric input */
            else if (key >= '0' && key <= '9')
            {
                buffer[i] = key;

                LCD_voidWriteData('*');

                i++;
            }
        }
    }
}


void GetNEWPasswordFromUser(u8 *buffer)
{
    u8 key = 0;
    u8 i = 0;

    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Enter NEW Pass:");
    LCD_voidGoToXY(1, 0);

    while (i < PASSWORD_LENGTH)
    {
        key = KPD_voidGetPressedKey();

        if (key != 0xFF)
        {
            /* Delete / Backspace */
            if (key == 'c')
            {
                if (i > 0)
                {
                    i--;

                    buffer[i] = 0;

                    /* Remove last '*' from LCD */
                    LCD_voidGoToXY(1, i);
                    LCD_voidWriteData(' ');

                    /* Return cursor to deleted position */
                    LCD_voidGoToXY(1, i);
                }
            }

            /* Numeric input */
            else if (key >= '0' && key <= '9')
            {
                buffer[i] = key;

                LCD_voidWriteData('*');

                i++;
            }
        }
    }
}


/* =========================================================
 *                    Password Checking
 * ========================================================= */

u8 CheckPassword(u8 *entered, u8 *stored)
{
    for (u8 i = 0; i < PASSWORD_LENGTH; i++)
    {
        if (entered[i] != stored[i])
        {
            return 0;
        }
    }

    return 1;
}


/* =========================================================
 *                     Delay Function
 * ========================================================= */

void Delay30Seconds(void)
{
    for (u8 i = 0; i < 30; i++)
    {
        _delay_ms(1000);
    }
}


/* =========================================================
 *                  Change Password
 * ========================================================= */

void ChangePassword(void)
{
    u8 newPassword[PASSWORD_LENGTH];

    GetNEWPasswordFromUser(newPassword);

    SavePasswordToEEPROM(newPassword);

    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Password Updated");

    _delay_ms(1500);
}


/* =========================================================
 *                  Show Saved Password
 * ========================================================= */

void ShowSavedPassword(void)
{
    u8 saved[PASSWORD_LENGTH];

    ReadPasswordFromEEPROM(saved);

    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Saved Pass:");

    LCD_voidGoToXY(1, 0);

    for (u8 i = 0; i < PASSWORD_LENGTH; i++)
    {
        LCD_voidWriteData(saved[i]);
    }

    _delay_ms(4000);
}


/* =========================================================
 *                     Servo Functions
 * ========================================================= */

void Servo_Init(void)
{
    M_TIMER1_voidPwm1Init();
    M_TIMER1_voidPwm1SetTop();
    M_TIMER1_voidPwm1Start();
}


void Servo_GotoAngle(u8 angle)
{
    if (angle > 180)
    {
        angle = 180;
    }

    angle = 180 - angle;

    u16 ocr_value = 31 + ((u32)angle * 32) / 180;

    M_TIMER1_voidPwm1SetDutyCycle(ocr_value);
}


void Servo_Reset(void)
{
    Servo_GotoAngle(0);
}


/* =========================================================
 *                    Open Door Function
 * ========================================================= */

void OpenDoor(void)
{
    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Access Granted");

    /*
     * Servo moves from 90 degrees to 0 degrees
     * to simulate opening the door.
     */
    for (u8 angle = 0; angle <= 90; angle += 10)
    {
        Servo_GotoAngle(angle);
        _delay_ms(200);
    }

    _delay_ms(2000);

    /*
     * Return the servo to its locked position.
     */
    Servo_Reset();
}


/* =========================================================
 *                    Change Password Prompt
 * ========================================================= */

void AskToChangePassword(u8 *savedPassword)
{
    LCD_voidClear();
    LCD_voidWriteString((u8 *)"Change Pass? 1=Y");

    u8 opt = 0xFF;

    for (u8 i = 0; i < 50; i++)
    {
        opt = KPD_voidGetPressedKey();

        if (opt == '1')
        {
            ChangePassword();

            /* Reload password from EEPROM */
            ReadPasswordFromEEPROM(savedPassword);

            break;
        }
        else if (opt != 0xFF)
        {
            break;
        }

        _delay_ms(100);
    }
}


/* =========================================================
 *                         MAIN
 * ========================================================= */

int main(void)
{
    LCD_voidInit();
    KPD_voidInit();

    DIO_voidSetPinDirection(
        BUZZER_PORT,
        BUZZER_PIN,
        PIN_OUTPUT
    );

    Servo_Init();

    /*
     * Initial locked position = 90 degrees.
     */
    Servo_Reset();

    u8 savedPassword[PASSWORD_LENGTH];

    /*
     * Number of normal failed attempts.
     */
    u8 tries = 0;

    /*
     * Indicates whether the user is allowed
     * to make the single extra attempt after
     * the 30-second lockout.
     */
    u8 extraAttempt = 0;

    /* Load saved password from EEPROM */
    ReadPasswordFromEEPROM(savedPassword);


    while (1)
    {
        /* =================================================
         *              Enter Password
         * ================================================= */

        GetPasswordFromUser(enteredPassword);


        /* =================================================
         *              Correct Password
         * ================================================= */

        if (CheckPassword(enteredPassword, savedPassword))
        {
            OpenDoor();

            /* Reset normal attempts */
            tries = 0;
            extraAttempt = 0;

            /* Ask user whether to change password */
            AskToChangePassword(savedPassword);
        }


        /* =================================================
         *              Wrong Password
         * ================================================= */

        else
        {
            tries++;

            LCD_voidClear();
            LCD_voidWriteString((u8 *)"Wrong Password!");

            _delay_ms(1500);


            /* =============================================
             *         Normal 3 Attempts Reached
             * ============================================= */

            if (tries == MAX_TRIES)
            {
                LCD_voidClear();
                LCD_voidWriteString((u8 *)"Wait 30 sec...");

                Delay30Seconds();


                /* =========================================
                 *        Options After 30 Seconds
                 * ========================================= */

                LCD_voidClear();
                LCD_voidWriteString((u8 *)"1: Retry");

                LCD_voidGoToXY(1, 0);
                LCD_voidWriteString((u8 *)"2: Forgot");


                u8 opt = 0xFF;

                while (opt == 0xFF)
                {
                    opt = KPD_voidGetPressedKey();
                }


                /* =========================================
                 *                Forgot Password
                 * ========================================= */

                if (opt == '2')
                {
                    ShowSavedPassword();

                    /*
                     * Reset attempts so the user can
                     * start entering the password again.
                     */
                    tries = 0;
                    extraAttempt = 0;
                }


                /* =========================================
                 *              Retry - One Attempt
                 * ========================================= */

                else if (opt == '1')
                {
                    /*
                     * User gets exactly one extra attempt.
                     */
                    extraAttempt = 1;
                }
            }


            /* =============================================
             *          Extra Attempt After Lockout
             * ============================================= */

            else if (extraAttempt == 1)
            {
                /*
                 * This was the single extra attempt.
                 * If the password is wrong, the system
                 * enters ALERT state and stops.
                 */

                LCD_voidClear();
                LCD_voidWriteString((u8 *)"ALERT!");

                ActivateBuzzer();

                _delay_ms(3000);

                LCD_voidClear();
                LCD_voidWriteString((u8 *)"All attempts used");

                /*
                 * Stop the system.
                 */
                while (1)
                {
                }
            }
        }

        _delay_ms(1000);
    }
}
