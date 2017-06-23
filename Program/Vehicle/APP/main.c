#include "main.h"

volatile int8u colliflag = 0;
volatile int8u collisens = 0;

extern lcdptr;

int main(void)
{

	init();
	while (TRUE) {

		if (colliflag == 1) {
			buzon();
			colliflag = 0;
			lcdclr();
			lcdws("COLLI OCC: ");
			if (collisens == FRONT)
				lcdws("FRONT");
			else
				lcdws("BACK");
			
			dlyms(DISP_DLY);
			SendLinkLoc(RPhNum,"");
			
			lcdws("Collision Occu'd");
			lcdr2();
			lcdws("Vehicle Stopped!");
			ledon();
			cli();
			sleep_enable();
			sleep_cpu();
			for(;;);	
		}

		sleep();
	}
	return 0;
}
static void init(void)
{
	buzinit();
	ledinit();

	beep(2,100);
	lcdinit();
	GPSInit();
	uartinit();
	tmr1init();
	EXT0init();
	GSMinit();
	disptitl();
	sei();

}

static void disptitl(void)
{ 
	lcdclr();
	lcdws(" SMART VEHICLE");

}
static void tmr1init(void)
{
	TCNT1H   = 0xD3;
	TCNT1L   = 0x00;
	TIMSK   |= _BV(TOIE1);			//ENABLE OVERFLOW INTERRUPT
	TCCR1A   = 0x00;					
	TCCR1B  |= _BV(CS10) | _BV(CS11); /* PRESCALAR BY 16 */
}

static void EXT0init(void)
{
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);

	INTDDR 	&= ~_BV(INT1_PIN);
	INTPORT |= _BV(INT1_PIN);

	GICR |= _BV(INT0) | _BV(INT1);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01) | _BV(ISC11);		//FALLING EDGE INTERRUPT

}
/* overflows at every 100msec */
ISR(TIMER1_OVF_vect) 
{ 
	static int8u i,j,k;

	TCNT1H = 0xD3;
	TCNT1L = 0x00;
	
	if (++i >= 50) i = 0;
	switch(i) {
		case 0: case 2: ledon();  break;
		case 1: case 3: ledoff(); break;
	} 
}

ISR(INT0_vect) 
{ 
	collisens = FRONT;
	colliflag = 1;
	GICR &= ~_BV(INT0);
}
ISR(INT1_vect) 
{ 
	collisens = BACK;
	colliflag = 1;
	GICR &= ~_BV(INT1);
}
