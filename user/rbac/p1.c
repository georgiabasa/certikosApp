//P1 - EnvMonitor

#include <syscall.h>
#include <stdio.h>
#include "sensor_data.h"

int delta(int a, int b) {
	return (a > b) ? (a - b) : (b - a);
}

int average(const int *array, int count) {
	int sum = 0;
	int i = 0;
	for (i = 0; i < count; i++) sum += array[i];
	return sum/count;
}

int is_trending_down(const int *buffer) {
	int i = 1;
	for (i = 1; i < TREND_WINDOW; i++)
		if (buffer[i] >= buffer[i-1]) return 0;
	return 1;
}

int is_trending_up(const int *buffer) {
	int i = 1;
	for (i = 1; i < TREND_WINDOW; i++)
		if (buffer[i] <= buffer[i-1]) return 0;
	return 1;
}

void print_health_index(int radiation, int battery_mv) {
	int health = 100 - radiation + (battery_mv / 100);
	if (health > 100) health = 100;
	if (health < 0) health = 0;
	printf("Health Index: %d%%\n", health);
}

int main (int argc, char **argv) {
	int temp_buf[TREND_WINDOW] = {0};
	int rad_buf[TREND_WINDOW] = {0};
	int bat_buf[TREND_WINDOW] = {0};

	int tick = 0;

	while (tick < SENSOR_DATA_LEN) {
		printf("\n[Tick %d]\n", tick);

		int raw_temp = temperature_data[tick];
		int raw_rad = radiation_data[tick];
		int raw_bat = battery_mv_data[tick];

		// glitch filtering
		if (tick > 0) {
			if (delta(raw_temp, temperature_data[tick - 1]) > TEMP_GLITCH_THRESHOLD)
				raw_temp = temperature_data[tick - 1];
			if (delta(raw_rad, radiation_data[tick - 1]) > RAD_GLITCH_THRESHOLD)
				raw_rad = radiation_data[tick - 1];
			if (delta(raw_bat, battery_mv_data[tick - 1]) > BAT_GLITCH_THRESHOLD)
				raw_bat = battery_mv_data[tick - 1];
		}

		// print current sensor data
		int i = 0;
		for (i = TREND_WINDOW - 1; i > 0; i--) {
			temp_buf[i] = temp_buf[i-1];
			rad_buf[i] = rad_buf[i-1];
			bat_buf[i] = bat_buf[i-1];
		}
		temp_buf[0] = raw_temp;
		rad_buf[0] = raw_rad;
		bat_buf[0] = raw_bat;

		// trend detection (after window fills)
		if (tick >= TREND_WINDOW) {
			if (is_trending_down(bat_buf))
				printf("(!) Battery dropping steadily over last %d cycles.\n", TREND_WINDOW);
			if (is_trending_up(temp_buf))
				printf("(!) Temperature rising trend detected.\n");
			if (is_trending_up(rad_buf))
				printf("(!) Radiation rising trend detected.\n");
		}

		// anomaly detection with rolling average
		if (tick >= DEVIATION_WINDOW) {
			int avg_temp = average(&temperature_data[tick - DEVIATION_WINDOW], DEVIATION_WINDOW);
			int avg_rad = average(&radiation_data[tick - DEVIATION_WINDOW], DEVIATION_WINDOW);
			int avg_bat = average(&battery_mv_data[tick - DEVIATION_WINDOW], DEVIATION_WINDOW);

			if (delta(raw_temp, avg_temp) > TEMP_ANOMALY_THRESHOLD)
				printf("!!! Thermal Anomaly Detected! dT=%d\n", delta(raw_temp, avg_temp));
			if (delta(raw_rad, avg_rad) > RADIATION_ANOMALY_THRESHOLD)
				printf("!!! Radiation Anomaly Detected! dR=%d\n", delta(raw_rad, avg_rad));
			if (delta(raw_bat, avg_bat) > BATTERY_DROP_THRESHOLD)
				printf("!!! Battery Anomaly Detected! dV=%d\n", delta(raw_bat, avg_bat));
		}

		// health metric
		print_health_index(raw_rad, raw_bat);
		
		tick++;;
		yield();
	}
	return 0;
}

//1. Trend Detection over a 5-cycle window.
//2. Anomaly Detection using deviation from a rolling average.
//3. Sensor Glitch Filter: Ignores values with sudden jumps.
//4. Derived Metric: A “Health Index” based on radiation and battery.
//5. Smart logging per cycle.

