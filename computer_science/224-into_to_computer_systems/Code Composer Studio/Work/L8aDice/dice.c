//******************************************************************************
//  Lab 8a - Dice
//
//  Description:
//
//	"Write a dice roller C program that waits for a switch to be pressed and then
//	 displays two dice which randomly change values. The dice roll begins rapidly
//	 and progressively slows down until it stops (after approximately 3-5
//	 seconds). A congratulatory ditty is played when doubles are rolled. If
//	 doubles are rolled twice in a row, output a raspberry tone. Write an
//	 assembly language function which returns a random number from 1 to 6 and
//	 call this function from your C program." 
//
//  Origional Author:		Paul Roper, Brigham Young University
//	Current Author: 		Benjamin Thompson
//	Revisions:	March 2010	Original code
//				07/28/2011	Added doTone
//				11/09/2012	lcd_wordImage
//
//  Built with Code Composer Studio Version: 4.2.3.00004
//*******************************************************************************
//
//                            MSP430F2274
//                  .-----------------------------.
//            SW1-->|P1.0^                    P2.0|<->LCD_DB0
//            SW2-->|P1.1^                    P2.1|<->LCD_DB1
//            SW3-->|P1.2^                    P2.2|<->LCD_DB2
//            SW4-->|P1.3^                    P2.3|<->LCD_DB3
//       ADXL_INT-->|P1.4                     P2.4|<->LCD_DB4
//        AUX INT-->|P1.5                     P2.5|<->LCD_DB5
//        SERVO_1<--|P1.6 (TA1)               P2.6|<->LCD_DB6
//        SERVO_2<--|P1.7 (TA2)               P2.7|<->LCD_DB7
//                  |                             |
//         LCD_A0<--|P3.0                     P4.0|-->LED_1 (Green)
//        i2c_SDA<->|P3.1 (UCB0SDA)     (TB1) P4.1|-->LED_2 (Orange) / SERVO_3
//        i2c_SCL<--|P3.2 (UCB0SCL)     (TB2) P4.2|-->LED_3 (Yellow) / SERVO_4
//         LCD_RW<--|P3.3                     P4.3|-->LED_4 (Red)
//   TX/LED_5 (G)<--|P3.4 (UCA0TXD)     (TB1) P4.4|-->LCD_BL
//             RX-->|P3.5 (UCA0RXD)     (TB2) P4.5|-->SPEAKER
//           RPOT-->|P3.6 (A6)          (A15) P4.6|-->LED 6 (R)
//           LPOT-->|P3.7 (A7)                P4.7|-->LCD_E
//                  '-----------------------------'
//
//******************************************************************************
//******************************************************************************
// includes

#include "msp430x22x4.h"
#include <stdlib.h>
#include "RBX430-1.h"
#include "RBX430_lcd.h"
#include "dice.h"


// global variables ------------------------------------------------------------
volatile int WDT_Sec_Cnt;				// WDT second counter
volatile int WDT_Delay;					// WDT delay counter
volatile int WDT_Tone_Cnt;				// WDT tone counter

int rset;
int rset2;
int switches = 0;
int fives = WDT_1SEC_CNT*5;
int time = 0;
int doubles = 0;
int one = 0;
int two = 0;
int three = 0;
int four = 0;
int five = 0;
int six = 0;

void setCount(uint8 die);
void showHist();
// const images ----------------------------------------------------------------
const uint16 spot_image[] = { 15, 15,	// 15 x 15 spot image
  0x01ff,0xf800,0xffdf,0x001f,0x01ff,0x01ff,0x03fe,0x01ff,0xf800,0x03fe,0x001f,
  0xffc0,0x03fe,0x07df,0xffc0,0x03fe,0x07df,0x05fe,0x05fe,0x05fe,0x05fe,0x05fe,
  0xffc0,0x03fe,0x07df,0xffc0,0x03fe,0x07df,0xf800,0x03fe,0x001f,0x01ff,0x03fe,
  0x01ff,0x01ff,0xf800,0xffdf,0x001f,0x01ff
};

const uint16 byu4_image[] = { 75, 46,	// 75 x 46 BYU logo image
  0x06ff,0x8400,0x04f0,0x8410,0x0010,0x02ff,0x8000,0x04f0,0x8410,0x0410,0x05ff,
  0x06ff,0xfc00,0x04fe,0x039f,0x02ff,0xfb80,0x04fe,0x041f,0x05ff,0x06ff,0xfc00,
  0x04f0,0x8410,0x041f,0x02ff,0xfc00,0x04f0,0x8410,0x041f,0x05ff,0x06ff,0xfc00,
  0x0010,0x02ff,0x8000,0x459f,0x02ff,0xd7d0,0x000e,0x02ff,0x8000,0x041f,0x05ff,
  0x06ff,0xfc00,0x0010,0x02ff,0x7000,0x87df,0x01ff,0x8000,0x859f,0x03ff,0x8000,
  0x041f,0x05ff,0x06ff,0xfc00,0x0010,0x03ff,0xffce,0x000e,0xd400,0x7416,0x03ff,
  0x8000,0x041f,0x05ff,0x06ff,0xfc00,0x0010,0x03ff,0xfc00,0x0390,0xfc0e,0x041a,
  0x03ff,0x8000,0x041f,0x05ff,0x06ff,0xfc00,0x0010,0x03ff,0xfb80,0x741f,0xd7d0,
  0x000e,0x03ff,0x8000,0x041f,0x05ff,0x06ff,0xfc00,0x0010,0x03ff,0x8000,0x841f,
  0x87d0,0x04ff,0x8000,0x041f,0x05ff,0x06ff,0xfc00,0x0010,0x03ff,0x8000,0xd7da,
  0x741f,0x04ff,0x8000,0x041f,0x05ff,0x06f0,0x8410,0xfc10,0x0010,0x04ff,0xb7d0,
  0x041f,0x04ff,0x8000,0x841f,0x05f0,0x8410,0x07fe,0x8410,0x0410,0x03ff,0xfc00,
  0x0010,0x03ff,0x8400,0x8410,0x05fe,0x87df,0x841f,0x03f0,0x8410,0x87d0,0x8410,
  0xfc10,0x01fe,0x77df,0x03ff,0x8380,0x000e,0x03ff,0xffce,0x01fe,0x841f,0x04f0,
  0x8410,0x87d0,0x041f,0x03ff,0x87d0,0x01ff,0x8380,0x8410,0x87d0,0x07ff,0x8000,
  0x87da,0x8410,0x0390,0x04ff,0x87d0,0x041f,0x03ff,0x87d0,0x03ff,0xffc0,0x000e,
  0x06ff,0x8380,0x739f,0x06ff,0x87d0,0x041f,0x03ff,0x87d0,0x03ff,0xfc00,0x0010,
  0x06ff,0xfc00,0x000e,0x06ff,0x87d0,0x041f,0x03ff,0x87d0,0x03ff,0xfc00,0x039f,
  0x06ff,0x87ce,0x07ff,0x87d0,0x041f,0x03ff,0x87d0,0x03ff,0xfc00,0x041f,0x05ff,
  0x8000,0x77d0,0x07ff,0x87d0,0x041f,0x03ff,0x87d0,0x03ff,0xfc00,0x87df,0x05ff,
  0x8380,0x87df,0x07ff,0x87d0,0x041f,0x03ff,0x87d0,0x03ff,0xfc00,0x87df,0x000e,
  0x04ff,0xfc00,0x049f,0x02ff,0x8380,0x7410,0x03ff,0x87d0,0x841f,0x0010,0x02ff,
  0x87d0,0x02ff,0x8000,0xfc10,0x01fe,0x0010,0x04ff,0xffce,0x041f,0x02ff,0xfb80,
  0x769f,0x02ff,0x8400,0x87d0,0x01fe,0x0010,0x02ff,0x87d0,0x02ff,0x8000,0x01fe,
  0xffd6,0x039a,0x03ff,0x7000,0xb7d0,0x069f,0x02ff,0xd380,0x759f,0x02ff,0xfc00,
  0x87df,0xfc10,0x0010,0x02ff,0x87d0,0x02ff,0x8000,0xfd9f,0x01fe,0x041f,0x03ff,
  0x8000,0xfd9f,0x069f,0x02ff,0xe380,0x77df,0x02ff,0xfc00,0x8410,0xfc00,0x0010,
  0x02ff,0x87d0,0x02ff,0x8000,0x01fe,0xb7d6,0x041f,0x03ff,0x8000,0x01fe,0x07d6,
  0x02ff,0xfb80,0x769a,0x02ff,0xfc00,0x0010,0xfc00,0x0010,0x02ff,0x87d0,0x02ff,
  0x8000,0xb7df,0x01fe,0x041f,0x03ff,0x8000,0xfd9f,0x859f,0x02ff,0x7380,0x738e,
  0x02ff,0xfc00,0x0010,0xfc00,0x0010,0x02ff,0x87d0,0x02ff,0x8000,0x01fe,0xfd9f,
  0x041f,0x03ff,0x8000,0x02fe,0x000e,0x05ff,0xfc00,0x0010,0xfc00,0x0010,0x02ff,
  0x87d0,0x02ff,0x8000,0xfd9f,0xffd6,0x041f,0x03ff,0x8000,0xb7df,0xfd9f,0x741a,
  0x05ff,0xfc00,0x0010,0xfc00,0x0010,0x02ff,0x87d0,0x02ff,0x8000,0x01fe,0xb7df,
  0x041f,0x03ff,0x8000,0x02fe,0x7412,0x05ff,0xfc00,0x0010,0xfc00,0x0010,0x02ff,
  0x87d0,0x02ff,0x8000,0xfd9f,0xffd6,0x041f,0x03ff,0x8000,0xfd9f,0x97d6,0x0390,
  0x05ff,0xfc00,0x0010,0xfc00,0x0010,0x02ff,0x87d0,0x02ff,0x8000,0x01fe,0xfd9f,
  0x041f,0x03ff,0x8000,0xffd6,0x77df,0x000e,0x01ff,0x8380,0x7410,0x02ff,0xfc00,
  0x0010,0xfc00,0x0010,0x02ff,0x87d0,0x02ff,0x8000,0xb7df,0x01fe,0x041f,0x03ff,
  0x8000,0x01fe,0x87d6,0x02ff,0xd380,0x769f,0x02ff,0xfc00,0x8410,0xfc00,0x0010,
  0x02ff,0x87d0,0x02ff,0x8000,0x01fe,0xfd9f,0x041f,0x03ff,0x8000,0x01fe,0x041f,
  0x02ff,0xfb80,0x77df,0x02ff,0xfc00,0x87df,0xfc00,0x0010,0x02ff,0x87d0,0x02ff,
  0x8000,0xb7df,0x01fe,0x041f,0x03ff,0x8000,0xb7df,0x041f,0x02ff,0xd380,0x7696,
  0x02ff,0x8400,0x87d0,0xfc00,0x0010,0x02ff,0x8410,0x02ff,0x8000,0xfd9f,0x01fe,
  0x041f,0x03ff,0x8000,0x01fe,0x041f,0x02ff,0x8380,0x7410,0x03ff,0x87d0,0xfc00,
  0x0010,0x05ff,0x8000,0x01fe,0x841f,0x0410,0x03ff,0x8000,0x8410,0x041f,0x07ff,
  0x87d0,0xfc00,0x0010,0x05ff,0x8000,0xfd9f,0x041f,0x05ff,0x8000,0x769f,0x07ff,
  0x87d0,0xfc00,0x0010,0x05ff,0x8000,0xb7df,0x041f,0x05ff,0x8000,0x87df,0x07ff,
  0x87d0,0xfc00,0x039a,0x05ff,0xb400,0x01fe,0x041f,0x05ff,0x8000,0x87df,0x0010,
  0x06ff,0x87d0,0xd000,0x841f,0x05ff,0xffd0,0xfd9f,0x041f,0x05ff,0x8000,0x01fe,
  0x0390,0x06ff,0x87d0,0x8000,0x87d6,0x0410,0x03ff,0x8400,0xb7df,0x01fe,0x041f,
  0x05ff,0x8000,0x01fe,0x841f,0x06ff,0x87d0,0x01ff,0xffd0,0x869f,0x03f0,0x8410,
  0xfe90,0x01fe,0xfd9f,0x041f,0x05ff,0x8000,0xb7df,0x01fe,0x06f0,0x8410,0x87d0,
  0x01ff,0xd400,0xffd6,0x03fe,0xb7df,0xfd9f,0x01fe,0x041f,0x05ff,0x8000,0x01fe,
  0xffd6,0x06fe,0x87df,0x02ff,0x07f0,0x8410,0x041f,0x05ff,0x8000,0x841f,0x08f0,
  0x8410,0x08ff,0x8000,0x841f,0x06f0,0x8410,0x041f,0x08ff,0x08ff,0x8000,0x07fe,
  0x041f,0x08ff,0x08ff,0x8000,0x07f0,0x8410,0x0410,0x08ff
};


//------------------------------------------------------------------------------
// main ------------------------------------------------------------------------
	void main(void)

	{

	RBX430_init(_8MHZ);					// init board
	ERROR2(lcd_init());					// init LCD
	//ADXL345_init();						// init accelerometer

	// configure P1 ----------------------------------------------------
	   P1SEL = 0x00;	             // select GPIO
	   P1OUT = 0x0f;	             // turn off all output pins
	   P1REN = 0x0f;	             // pull-up P1.0-3
	   P1DIR = 0xc0;	             // P1.0-5 input, P1.6-7 output

	// configure Watchdog
	WDTCTL = WDT_CTL;					// Set Watchdog interval
	WDT_Sec_Cnt = WDT_1SEC_CNT;			// set WD 1 second counter
	WDT_Delay = 0;						// reset delay counter
	WDT_Tone_Cnt = 0;					// turn off tone
	IE1 |= WDTIE;						// enable WDT interrupt

	// configure h/w PWM for speaker
	P4SEL |= 0x20;						// P4.5 TB2 output
	TBR = 0;							// reset timer B
	TBCTL = TBSSEL_2 | ID_0 | MC_1;		// SMCLK, /1, UP (no interrupts)
	TBCCTL2 = OUTMOD_3;					// TB2 = set/reset

	__bis_SR_register(GIE);				// enable interrupts


	lcd_clear();
	lcd_mode(LCD_2X_FONT | LCD_PROPORTIONAL);
	lcd_backlight(ON);				// turn on LCD backlight
	lcd_cursor(15, 20);				// position message
	lcd_printf("Press Switch\n      To Roll Dice");
	while(get_switch(1)!= 1)
		{
		}

	uint8 myDie, oldDie = 0;
	uint8 myDie2, oldDie2 = 0;

	rset = ADC_read(6);
	rset2 = ADC_read(7);
	lcd_clear();						// clear LCD
	lcd_mode(LCD_2X_FONT | LCD_PROPORTIONAL);
	lcd_wordImage(byu4_image, (160-75)/2, 110, 1);
	lcd_rectangle(8, 45, 60, 60, 1);	// draw double die frame
	lcd_rectangle(9, 46, 58, 58, 1);
	lcd_rectangle(93, 45, 60, 60, 1);	// draw 2nd double die frame
	lcd_rectangle(94, 46, 58, 58, 1);

	int x = 0;

	while (1)							// repeat forever
	{
		lcd_cursor(15, 20);				// position message
		lcd_printf("                                \n                                         ");
		double i;
		for(i = 1; i < 800; i = ((i * 8)/5))
		{
			if ((P1IN & 0x0f) != 0x0f)
			{
				i = 1;
			}
			lcd_backlight(ON);				// turn on LCD backlight
			myDie = (random(rset,6));		// get a random die (1-6)

			lcd_cursor(20, 15);				// position message
			doTone(BEEP, BEEP_CNT);			// output BEEP
			drawDie(myDie, &oldDie, 15, 51);// draw a die
			myDie2 = (random(rset2,6));		// get a random die (1-6)
			drawDie(myDie2, &oldDie2, 100, 51);// draw 2nd die
			WDT_sleep(i);					// delay
			lcd_backlight(OFF);				// turn off LCD
			WDT_sleep(i);					// short delay
		}
		setCount(myDie);
		setCount(myDie2);

		doTone(BEEP*2, BEEP_CNT*2);
		WDT_sleep(200);
		time = 0;
		lcd_backlight(ON);
		x++;
		if (myDie == myDie2)
		{
			LED_1_TOGGLE;
			WDT_sleep(30);
			doTone(BEEP1, BEEP_CNT*8);
			WDT_sleep(30);
			LED_1_TOGGLE;

			WDT_sleep(60);
			LED_2_TOGGLE;
			WDT_sleep(30);
			doTone(BEEP2, BEEP_CNT*8);
			WDT_sleep(30);
			LED_2_TOGGLE;

			WDT_sleep(60);
			LED_3_TOGGLE;
			WDT_sleep(30);
			doTone(BEEP3, BEEP_CNT*8);
			WDT_sleep(30);
			LED_3_TOGGLE;

			WDT_sleep(60);
			LED_4_TOGGLE;
			WDT_sleep(30);
			doTone(BEEP4, BEEP_CNT*10);
			WDT_sleep(30);
			LED_4_TOGGLE;

			WDT_sleep(80);
			LED_3_TOGGLE;
			WDT_sleep(30);
			doTone(BEEP3, BEEP_CNT*10);
			WDT_sleep(30);
			LED_3_TOGGLE;

			WDT_sleep(30);
			LED_4_TOGGLE;
			WDT_sleep(30);
			doTone(BEEP4, BEEP_CNT*16);
			WDT_sleep(30);
			LED_4_TOGGLE;

			if ((doubles == (x-1)) && (doubles != 0))
			{
				WDT_sleep(90);
				doTone(BEEP*4, BEEP_CNT*20);
				WDT_sleep(90);
			}
			doubles = x;
			time = 0;
		}
		lcd_cursor(15, 20);				// position message
		lcd_printf("Press Switch\n      To Roll Dice");
		while(get_switch(1)!= 1)
		{

		}
	}
} // end main()

void setCount(uint8 die)
{
	if (die == 1)
		one++;
	else if(die == 2)
		two++;
	else if(die == 3)
		three++;
	else if(die == 4)
		four++;
	else if(die == 5)
		five++;
	else
		six++;
}

void showHist()
{

	while((time++) != WDT_1SEC_CNT);
	lcd_clear();
	lcd_mode(~LCD_2X_FONT);

	lcd_rectangle(0, 14, 160, 2, 1);
	lcd_cursor(0, 0);						// set display coordinates
	printf("1:%d", one);

	lcd_rectangle(23, 0, 2, 160, 1);
	lcd_rectangle(2, 20, 18, 2*one, 1);
	lcd_cursor(29, 0);						// set display coordinates
	printf("2:%d", two);

	lcd_rectangle(52, 0, 2, 160, 1);
	lcd_rectangle(30, 20, 18, 2*two, 1);
	lcd_cursor(58,0);						// set display coordinates
	printf("3:%d", three);

	lcd_rectangle(80, 0, 2, 160, 1);
	lcd_rectangle(58, 20, 18, 2*three, 1);
	lcd_cursor(87,0);						// set display coordinates
	printf("4:%d", four);

	lcd_rectangle(106, 0, 2, 160, 1);
	lcd_rectangle(86, 20, 18, 2*four, 1);
	lcd_cursor(112, 0);						// set display coordinates
	printf("5:%d", five);

	lcd_rectangle(133, 0, 2, 160, 1);
	lcd_rectangle(112, 20, 18, 2*five, 1);
	lcd_cursor(139,0);						// set display coordinates
	printf("6:%d", six);
	lcd_rectangle(140, 20, 18, 2*six, 1);



	while(((P1IN & 0x0f) ^ 0x0f) != SW_4);
	lcd_clear();
	lcd_rectangle(8, 45, 60, 60, 1);	// draw double die frame
	lcd_rectangle(9, 46, 58, 58, 1);
	lcd_rectangle(93, 45, 60, 60, 1);	// draw 2nd double die frame
	lcd_rectangle(94, 46, 58, 58, 1);
	lcd_mode(LCD_2X_FONT | LCD_PROPORTIONAL);
	lcd_wordImage(byu4_image, (160-75)/2, 110, 1);
	//lcd_printf("Press Switch\n      To Roll Dice");
	while(time++ != WDT_1SEC_CNT);
}

//------------------------------------------------------------------------------
// output tone subroutine ------------------------------------------------------
void doTone(uint16 tone, uint16 time)
{
	TBCCR0 = tone;						// set beep frequency/duty cycle
	TBCCR2 = tone >> 1;					// 50% duty cycle
	WDT_Tone_Cnt = time;				// turn on speaker
	while (WDT_Tone_Cnt);				// wait for tone off
	return;
} // end doTone


//------------------------------------------------------------------------------
// Watchdog sleep subroutine ---------------------------------------------------
void WDT_sleep(int sleep)
{
	if (sleep <= 0) return;
	WDT_Delay = sleep;					// set WD decrementer
	while (WDT_Delay!=0);					// wait for time to expire
	return;
} // end WDT_sleep()


//------------------------------------------------------------------------------
// draw die --------------------------------------------------------------------
//
//	IN:		die = 1-6 new die
//			*old_die = ptr to variable to store previous die #
//			x = left most column of die (must be divisible by 3)
//			y = bottom row of die
//
//  dot bit positions:  01    02
//                      04 08 10
//                      20    40
//
const uint8 dice[] = {0x08, 0x41, 0x49, 0x63, 0x6b, 0x77};

void drawDie(uint8 die, uint8* old_die, int16 x, int16 y)
{
	uint8 new_die = die = dice[die-1];
	uint8 change = *old_die ^ new_die;		// 1 = change
	int flag = 1;

	// draw any new dots
	new_die &= change;						// 1 = turn on
	do
	{
		if (new_die & 0x01) lcd_wordImage(spot_image, x, y+32, flag);
		if (new_die & 0x02) lcd_wordImage(spot_image, x+30, y+32, flag);
		if (new_die & 0x04) lcd_wordImage(spot_image, x, y+16, flag);
		if (new_die & 0x08) lcd_wordImage(spot_image, x+15, y+16, flag);
		if (new_die & 0x10) lcd_wordImage(spot_image, x+30, y+16, flag);
		if( new_die & 0x20) lcd_wordImage(spot_image, x, y, flag);
		if (new_die & 0x40) lcd_wordImage(spot_image, x+30, y, flag);

		// blank any invalid dots
		new_die = *old_die & change;		// 1 = blank
	} while (flag--);

	//	update old die
	*old_die = die;
	return;
} // end outDie()

// switch debounce function -----------------------------------------
#define SMCLK     8000000
#define DB_TIME   20                 // 10 ms debounce time
#define DB_CYCS   26                 // instruction cycles for delay
#define DB_DELAY  SMCLK*DB_TIME/DB_CYCS/1000 // delay count

int get_switch(int swMask)
{
   uint8 mySwitch;
   uint16 delay = DB_DELAY;

   while ((P1IN & 0x0f) != 0x0f);    // wait for all switches off
   while (delay--)
   {
      // reset count if switch not pressed
      mySwitch = (P1IN & 0x0f) ^ 0x0f;
      if ((mySwitch & swMask) == 0) delay = DB_DELAY;
   };
   time = 0;
   return mySwitch;
}

//------------------------------------------------------------------------------
// Watchdog Timer ISR ----------------------------------------------------------
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	// decrement delay (if non-zero)
	if (WDT_Delay && (--WDT_Delay == 0));

	// decrement tone counter - turn off tone when 0
	if (WDT_Tone_Cnt && (--WDT_Tone_Cnt == 0))
	{
		TBCCR0 = 0;
	}

	if (--WDT_Sec_Cnt == 0)
	{
		WDT_Sec_Cnt = WDT_1SEC_CNT;		// reset counter
		LED_GREEN_TOGGLE;				// toggle green LED
	}

	if(((P1IN & 0x0f) ^ 0x0f) == 8)
	{
		lcd_backlight(ON);
		time = 0;
		showHist();
		lcd_backlight(ON);
	}
	time++;
	if (time == fives)
	{
		time = 0;
		lcd_backlight(OFF);
	}

	rset--;
	rset2++;
} // end WDT_ISR(void)
