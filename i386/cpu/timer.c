#include "timer.h"
#include "../libc/string.h"
#include "isr.h"
#include "types.h"
#include "../cpu/ports.h"

u32 tick = 0;

static void timer_callback(/* registers_t regs */) {
	tick++;
	// If you want to use this piece of code make sure you
	// include ../drivers/screen.h
	/* kprint("Tick: ");

	char tick_ascii[256];
	int_to_ascii(tick, tick_ascii);
	kprint(tick_ascii);
	kprint("\n"); */
}

void init_timer(u32 freq) {
	register_interrupt_handler(IRQ0, timer_callback);

	// Get the PIT value: hardware clock at 1193180 Hz
	u32 divisor = 1193180 / freq;
	u8 low =  (u8)(divisor & 0xFF);
	u8 high = (u8)( (divisor >> 8) & 0xFF);
	// Send Command
	port_byte_out(0x43, 0x36); // Command port
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}