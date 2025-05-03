//P1 - Simulated environmental readings

#include <syscall.h>
#include <stdio.h>
#include "sensor_data.h"

int main (int argc, char **argv) {
	int tick = 0;
	int loop = SENSOR_DATA_LEN;

	while (loop--) {
		printf("\n");


		int temp = temperature_data[tick];
		int rad = radiation_data[tick]; //radiation mSv
		int bat = battery_mv_data[tick]; //battery in mV

		printf("microSAT|P1|Tick:%d|TEMP:%dC|RAD:%dmSv|BAT:%dmV\n", tick, temp, rad, bat);

		tick++;
		yield();
	}

	return 0;
}

// P1 — Environmental Health Sampler

//  Reads and logs sensor data: temperature, radiation, battery voltage.

//  Purpose: Monitors spacecraft health, even in degraded mode.
