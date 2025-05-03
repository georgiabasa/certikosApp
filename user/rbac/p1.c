//P1 - Simulated environmental readings

#include <syscall.h>
#include <stdio.h>

int main (int argc, char **argv) {
	int tick = 0;
	int loop = 50;

	while (loop--) {
		printf("\n");
		tick++;

		int temp = 20 + (tick % 15); //simulated temperature in C
		int radiation = (tick * 7) % 120; //radiation mSv
		int battery_mv = 3700 - (tick % 50); //battery in mV

		printf("LOG|P1|Tick:%d|Temp:%dC|Rad:%dmSv|Bat:%dmV\n", tick, temp, radiation, battery_mv);

		yield();
	}

	return 0;
}

// P1 — Environmental Health Sampler

//  Reads and logs sensor data: temperature, radiation, battery voltage.

//  Purpose: Monitors spacecraft health, even in degraded mode.
