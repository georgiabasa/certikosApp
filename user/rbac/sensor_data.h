// environmental telemetry arrays

#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#define SENSOR_DATA_LEN 60

#define TREND_WINDOW 5
#define DEVIATION_WINDOW 3

#define TEMP_ANOMALY_THRESHOLD 8
#define RADIATION_ANOMALY_THRESHOLD 10
#define BATTERY_DROP_THRESHOLD 100

#define TEMP_GLITCH_THRESHOLD 6
#define RAD_GLITCH_THRESHOLD 15
#define BAT_GLITCH_THRESHOLD 150

static const int temperature_data[SENSOR_DATA_LEN] = {
	22, 23, 24, 25, 26, 27, 25, 24, 23, 22,
	23, 24, 25, 26, 27, 28, 28, 27, 26, 25,
    	24, 23, 22, 21, 22, 23, 24, 25, 26, 27,
    	27, 26, 25, 24, 23, 22, 22, 23, 24, 25,
    	26, 27, 28, 29, 30, 31, 30, 29, 28, 27,
    	26, 25, 24, 23, 22, 21, 21, 22, 23, 24
};

static const int radiation_data[SENSOR_DATA_LEN] = {
	85, 87, 90, 92, 88, 85, 83, 82, 81, 84,
    	86, 88, 90, 89, 87, 85, 84, 83, 81, 80,
    	82, 83, 85, 87, 89, 91, 92, 90, 88, 86,
    	85, 84, 83, 82, 81, 83, 85, 87, 89, 91,
    	93, 94, 95, 96, 95, 94, 93, 92, 91, 90,
    	88, 87, 86, 85, 84, 83, 82, 81, 80, 79
};

static const int battery_mv_data[SENSOR_DATA_LEN] = {
	3760, 3755, 3750, 3745, 3740, 3735, 3730, 3725, 3720, 3715,
    	3710, 3705, 3700, 3695, 3690, 3685, 3680, 3675, 3670, 3665,
    	3660, 3655, 3650, 3645, 3640, 3635, 3630, 3625, 3620, 3615,
    	3610, 3605, 3600, 3595, 3590, 3585, 3580, 3575, 3570, 3565,
    	3560, 3555, 3550, 3545, 3540, 3535, 3530, 3525, 3520, 3515,
    	3510, 3505, 3500, 3495, 3490, 3485, 3480, 3475, 3470, 3465
};

#endif
