/* main.c Main application program for traffic signal  */
# include "main.h"

int8u TrfState = T1_MOVE;
int16u Dly;

void main(void)
{
		init();
		while (TRUE) {
			switch(TrfState) {
				case T1_MOVE: ClrTrf1(); Dly = MOVE_DLY; break;
				case T1_WARN: WrnTrf1(); Dly = WARN_DLY; break;
				case T2_MOVE: ClrTrf2(); Dly = MOVE_DLY; break;
				case T2_WARN: WrnTrf2(); Dly = WARN_DLY; break;
				case T3_MOVE: ClrTrf3(); Dly = MOVE_DLY; break;
				case T3_WARN: WrnTrf3(); Dly = WARN_DLY; break;
				case T4_MOVE: ClrTrf4(); Dly = MOVE_DLY; break;
				case T4_WARN: WrnTrf4(); Dly = WARN_DLY; break;
				default: break;
			}
		}
 }

static void init(void)
{
	SIGNALS_PORT1 = 0x00;
	SIGNALS_PORT2 = 0x00;

	SIGNALS_PORT1 = 0xFF;
	SIGNALS_PORT2 = 0xFF;

	tmr0_init();
	EXTint_int();
}

static void tmr0_init(void)
{
	TMOD = TMOD & 0xf0 | 0x01;		/* TMR0 in mode1*/
	TH0 = 0x4B;
	TL0 = 0xFD;
	EA = ET0 = 1;
	TR0 = 1;
} 
static void tmr0ISR() interrupt 1 using 2
{
	static int16u i;
	static int8u OldState;

	TH0 = 0x4B;
	TL0 = 0xFD;
	
	if (Flag.Amb) {
		OldState = TrfState;
		TrfState = T1_MOVE;
		i = 0;
		Flag.Amb = FALSE;
		Flag.AmbTrf = TRUE;
	}

	if (Flag.AmbTrf && TrfState >= 2) {
		Flag.AmbTrf = FALSE;
		TrfState = OldState;
		i = 0;
	}
		
	if (++i >= Dly) {
		if (++TrfState >= 8)
			TrfState = 0;
		i = 0;
	}
} 

static void EXTint_int(void)
{
	EX0 = 1;		/* Enable external Interrupt 1 */
	IT0 = 1;		/* EDGE triggeres */
}
static void EXTintISR() interrupt 0 using 2
{
	Flag.Amb = 1;
}