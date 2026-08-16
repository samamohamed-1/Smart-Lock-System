#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "TIMER1_Interface.h"
#include "TIMER1_private.h"
#include "TIMER1_config.h"

void M_TIMER1_voidPwm1Init(void)
{
    DIO_voidSetPinDirection(PORTD_ID, PIN5, PIN_OUTPUT);

    CLR_BIT(TCCR1A_REG, WGM10);
    SET_BIT(TCCR1A_REG, WGM11);
    SET_BIT(TCCR1B_REG, WGM12);
    SET_BIT(TCCR1B_REG, WGM13);

    SET_BIT(TCCR1A_REG, COM1A1);
    CLR_BIT(TCCR1A_REG, COM1A0);
}

void M_TIMER1_voidPwm1SetTop(void)
{
    ICR1_REG = 4999;
}

void M_TIMER1_voidPwm1SetDutyCycle(u16 ocr_value)
{
    OCR1A_REG = ocr_value;
}


void M_TIMER1_voidPwm1Start(void)
{
#if TIMER1_PRESCALER == 1024
    SET_BIT(TCCR1B_REG, CS10);
    CLR_BIT(TCCR1B_REG, CS11);
    SET_BIT(TCCR1B_REG, CS12);
#elif TIMER1_PRESCALER == 256
    CLR_BIT(TCCR1B_REG, CS10);
    CLR_BIT(TCCR1B_REG, CS11);
    SET_BIT(TCCR1B_REG, CS12);
#endif
}

void M_TIMER1_voidPwm1Stop(void)
{
    CLR_BIT(TCCR1B_REG, CS10);
    CLR_BIT(TCCR1B_REG, CS11);
    CLR_BIT(TCCR1B_REG, CS12);
}
