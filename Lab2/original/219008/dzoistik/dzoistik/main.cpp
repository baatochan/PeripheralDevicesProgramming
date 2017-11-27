#include <stdio.h>
#include "joystick.h"

void
main()
{
	Joystick* joysticks[4];
	unsigned int i;

	unsigned int numJoysticks = Joystick::deviceCount();

	for (i = 0; i < numJoysticks; i++) {
		joysticks[i] = new Joystick(i);
		joysticks[i]->open();

		char name[MAX_PATH];
		joysticks[i]->deviceName(name);
	}

	for (;;){
		DIJOYSTATE2 js;
		system("cls");

		Sleep(0.000000000000001);
		joysticks[0]->poll(&js);
		printf("ski            %ld\n", js.lX);
		printf("kergi          %ld\n", js.lY);
		printf("tez            %ld\n", js.lZ);

		printf("ezsiwalK: ");
		for (int i = 0; i < 128; i++) {
			if (js.rgbButtons[i] & 0x80) {

				printf("%02d ", i);
			}
		}
		printf("\n");
	}

	for (i = 0; i < numJoysticks; i++) {
		joysticks[i]->close();
	}
}
