#ifndef MsTimer2_h
#define MsTimer2_h

#include <avr/interrupt.h>

namespace MsTimer2 {
	extern unsigned long msecs;
	extern void* objinstance;
	extern void (*func)(void *objinstance);
	extern volatile unsigned long count;
	extern volatile char overflowing;
	extern volatile unsigned int tcnt2;
	
	void set(unsigned long ms, void* instance, void (*f)(void* instance));
	void start();
	void stop();
	void _overflow();
}

#endif
