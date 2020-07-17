#ifndef PIN_IO_SETUP
#define PIN_IO_SETUP

#include <msp430.h>

//P2.1 - bluetooth to bed sensor
#define BED_BIT					BIT1
#define BED_PORT				P2IN
#define	BED_PIN					P2IN & BED_BIT

//P3.1 - buzzer
#define BUZZER_BIT				BIT1
#define BUZZER_PORT				P3IN
#define BUZZER_DDR				P3DIR
#define SET_BUZZER_AS_OUTPUT	BUZZER_DDR |= BUZZER_BIT
#define	BUZZER_OFF				BUZZER_PORT &= ~BUZZER_BIT
#define BUZZER_ON				BUZZER_PORT |= BUZZER_BIT

//PJ.3 - snooze
#define SNOOZE_BIT				BIT3
#define SNOOZE_PORT				PJIN
#define	SNOOZE_PIN				SNOOZE_PORT&SNOOZE_BIT

//PJ.4 - alarm off
#define ALARM_BIT				BIT4
#define ALARM_PORT				PJIN
#define	ALARM_PIN				ALARM_PORT&ALARM_BIT

//PJ.4 - LFXIN
#define LFXIN_BIT				BIT4
#define LFXIN_DDR				PJDIR
#define SET_LFXIN_AS_OUTPUT		LFXIN_DDR |= LFXIN_BIT

#endif
