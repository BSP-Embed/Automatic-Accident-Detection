//DEFINE MAIN HEADER FILE
#ifndef MAIN_H
#define MAIN_H

//INCLUDE DEFINITILOW OF HEADER FILE
#include <includes.h>

//DEFINE PORTS/PINS
#define SIGNALS_PORT1		P0
#define SIGNALS_PORT2		P1


#define G1		P0_5
#define Y1		P0_6
#define RED1	P0_7

#define G2		P1_5
#define Y2		P1_6
#define RED2	P1_7


#define G3		P1_1
#define Y3		P1_2
#define RED3	P1_3

#define G4		P0_1
#define Y4		P0_2
#define RED4	P0_3

//DEFINE CONSTANT
#define ON			0
#define OFF			1
#define MOVE_DLY	60
#define WARN_DLY	20	


enum { T1_MOVE = 0, T1_WARN, T2_MOVE, T2_WARN, T3_MOVE, T3_WARN, T4_MOVE, T4_WARN };

struct  {
	volatile int8u Amb:1;
	volatile int8u AmbTrf:1;
	volatile int8u Sym:1;
	volatile int8u Mchg:1;
	volatile int8u chg:1;
} Flag;

//DEFINE MACROS
#define Transition()	do {	   					\
							SIGNALS_PORT1 = 0xff; 	\
							SIGNALS_PORT2 = 0xff;	\
						} while (0)

#define ClrTrf1()		do {	   					\
							Transition(); 			\
							G3 = ON; 				\
							RED1 = ON; 				\
							RED2 = ON; 				\
							RED4 = ON;				\
						}while (0)

#define ClrTrf2()		do {	   					\
							Transition(); 			\
							G4 = ON; 				\
							RED1 = ON; 				\
							RED2 = ON; 				\
							RED3 = ON;				\
						}while (0)

#define ClrTrf3()		do {	   					\
							Transition(); 			\
							G1 = ON; 				\
							RED2 = ON; 				\
							RED3 = ON; 				\
							RED4 = ON;				\
						}while (0)

#define ClrTrf4()		do {	   					\
							Transition(); 			\
							G2 = ON; 				\
							RED1 = ON; 				\
							RED3 = ON; 				\
							RED4 = ON;				\
						}while (0)

#define WrnTrf1()		do {	   					\
							Transition(); 			\
							Y3 = ON; 				\
							RED1 = ON; 				\
							RED2 = ON; 				\
							RED4 = ON;				\
						}while (0)

#define WrnTrf2()		do {	   					\
							Transition(); 			\
							Y4 = ON; 				\
							RED1 = ON; 				\
							RED2 = ON; 				\
							RED3 = ON;				\
						}while (0)

#define WrnTrf3()		do {	   					\
							Transition(); 			\
							Y1 = ON; 				\
							RED2 = ON; 				\
							RED3 = ON; 				\
							RED4 = ON;				\
						}while (0)

#define WrnTrf4()		do {	   					\
							Transition(); 			\
							Y2 = ON; 				\
							RED1 = ON; 				\
							RED3 = ON; 				\
							RED4 = ON;				\
						}while (0)

//FUNCTILOW PROTOTYPES
		void main		(void);
static	void init		(void);
static 	void tmr0_init	(void);
static 	void EXTint_int	(void);
#endif

