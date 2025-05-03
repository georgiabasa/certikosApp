// P2 - System Watchdoging (independent timer)

#include <syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int tick = 0;
	int loop = 50;

	while (loop--) {
		tick++;
		if (tick % 5 == 0) {
			printf("LOG|P2|Tick:%d|WATCHDOG OK\n", tick);
		}
		yield();
	}

	return 0;
}

// Purely counts time spent in execution.

// Can simulate a heartbeat or watchdog.

//  Why? This would exist in a drone to restart the system if something freezes — no need to talk to others.
