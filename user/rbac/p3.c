// P3 - Self-Test Cycler

#include <syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int tick = 0;
	int loop = 50;

	while (loop--) {
		tick++;
		if (tick % 10 == 0) {
			int code = (tick * 13) %256;
			printf("LOG|P3|Tick:%d|SelfTestCode:%d\n", tick, code);
		}
		yield();
	}
	
	return 0;
}

// Every N ticks, runs a self-test (e.g., math, timing).

// Never needs to talk to other modules.

// ❓ Why? Like periodic self-test in pacemakers or secure boot blocks.
