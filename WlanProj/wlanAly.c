#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>//for malloc/free
#include <string.h>
#include "wlanprj.h"



void wlan_analyse(FILE* fp) {
	int ssidNum = wlan_count(fp);
	ssid* ssid_list = (ssid*)malloc(sizeof(ssid) * ssidNum);
	char buf[MAXCHAR] = { '\0' };
	int lc = 0;
	int i = 0,j =0;
	while (fgets(buf, MAXCHAR, fp)) {
		enum LINE_TYPE tmp = what_line(buf);
		if (tmp == UNKNOWN || buf[0] == '\n') {
			continue;//ignore uknown and empty line
		}
	    if ((lc>=4) && (tmp == SSID)) {
			j = 0;
			ssid_list[i].ssidnm[30] = read_value(buf);
			ssid_list[i].num_ap = j;
			i++;
		}
		else if ((lc >= 4) && (tmp == BSSID)) {
			ssid_list[i].aplist[j].apmac[20] = read_value(buf);
			j++;
		}
		else if ((lc >= 4) && (tmp == SIG)) {
			ssid_list[i].aplist[j].signal_strength = read_value(buf);
		}
		else if ((lc >= 4) && (tmp == CH)) {
			ssid_list[i].aplist[j].channel = read_value(buf);
		}
		lc++;
	}
	
	show_wlan(ssid_list, ssidNum);
	free(ssid_list);
}

int wlan_count(FILE* fp) {
	char line[MAXCHAR];
	int c = 0;
	int n = 0;
	while (fgets(line, MAXCHAR, fp)) {
		if (c == 2) {
			sscanf(line, "There are %d", &n);
			break;
		}
		c++;
	}
	rewind(fp);
	return n;
}

char* read_value(char* buf) {
	char value[200];
	sscanf(buf, "%*[^:]/%[^\n]", value);
	return value;
}
enum LINE_TYPE what_line(char* buf) {
	char keyword[20];
	sscanf(buf, "%s", keyword);
	if (strcmp(keyword, "SSID") == 0) return SSID;
	else if (strcmp(keyword, "Network") == 0) return NET;
	else if (strcmp(keyword, "Authentication") == 0) return AUTH;
	else if (strcmp(keyword, "Encryption") == 0) return ENCRYP;
	else if (strcmp(keyword, "BSSID") == 0) return BSSID;
	else if (strcmp(keyword, "Signal") == 0) return SIG;
	else if (strcmp(keyword, "Channel") == 0) return CH;
	else return UNKNOWN;
}
void show_wlan(ssid* list, int ssidc) {
	printf("Found %d WLANs", ssidc);
	printf("\n");
	for (int i = 0; i < ssidc; i++) {
		printf("ESSID: %s", list[i].ssidnm);
		printf("\n");
		printf("\t");
		for (int j = 0; j < list[i].num_ap; j++) {
			printf("AP %d MAC: %s\tChannel: %d, Signal: %d",j + 1, list[i].aplist[j].apmac, list[i].aplist[j].channel, list[i].aplist[j].signal_strength);
		}
		printf("\n");
	}
}
