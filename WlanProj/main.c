#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "wlanprj.h"

int main() {
	system(CMD);
	FILE* fp = fopen("wlan.txt", "r");
	if (fp != NULL) {
		wlan_analyse(fp);
		fclose(fp);
	}
	else printf("Error: wlan.txt file doesn't exist!");

}