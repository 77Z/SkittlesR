#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../drivers/keyboard.h"
#include "../drivers/serial.h"

// Kernel Modules
#include "../modules/uname.h"

void reset_view() { kprint("\n# "); }
void halt_cpu() { asm("hlt"); }

void kernel_main() {
	kprint("Driver Ready: Screen\n");
	init_serial();
	kprint("Driver Ready: Serial\n");
	isr_install();
	irq_install();
	kprint("Driver Ready: Keyboard\n");

	kprint("Writing Boot Message to Serial\n");
	write_serial_str("Hello Serial from SkittlesR "VERSION); // THIS WORKS WOOOHOOOOO

	kprint("Loading SkittlesR Kernel Version "VERSION"\n");


	reset_view();
}

void user_input(char *input) {
	
	char *Modules[] = {
		"uname"
	};

	if (strcmp(input, "END") == 0) {
		clear_screen();
		kprint_at("Halting the CPU. Have a good day!", 24, 12);
		halt_cpu();
	} else if (strcmp(input, "clear") == 0) {
		clear_screen();
		reset_view();
	} else if (strcmp(input, "help") == 0) {
		kprint("List of all commands/modules:\n");
		kprint("System: END, clear, help\n");
		kprint("Kernel Modules: ");
		for (unsigned int i = 0; i < sizeof Modules / sizeof Modules[0]; i++) {
			kprint(Modules[i]);
			kprint(", ");
		}
		reset_view();
	} else {
		// Not a system command, check if it's a Kernel Module
		int MatchFound = 0;

		for (unsigned int i = 0; i < sizeof Modules / sizeof Modules[0]; i++) {
			if (strcmp(Modules[i], input) == 0) {
				MatchFound = 1;

				if (strcmp(Modules[i], "uname") == 0) {
					UNAME_main();
				}
			}
		}

		if (!MatchFound) {
			kprint("Entered Command \"");
			kprint(input);
			kprint("\" Was not recognized as a system command or application.");
		}

		reset_view();
	}

}