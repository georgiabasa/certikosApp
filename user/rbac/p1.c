//P1 - Temperature and Voltage Sampler

#include <syscall.h>
#include <stdio.h>

int main (int argc, char **argv) {
	int tick = 0;
	int loop = 50;

	while (loop--) {
		tick++;
		int temp = 20 + (tick % 10); //simulated temperature
		int voltage = 330 + ((tick * 3) % 100); //mV

		printf("LOG|P1|Tick:%d|Temp:%dC|V:%dmV\n", tick, temp, voltage);
		yield();
	}

	return 0;
}

 //P1: Sensor Environment Sampler

//    Collects simulated data from fixed virtual sensors.

  //  Just logs readings periodically.

    //No communication needed.

   // ❓ Why? In real embedded systems, environmental data is sometimes just logged for later retrieval.
