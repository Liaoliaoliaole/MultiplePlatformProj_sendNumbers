#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>//for malloc/free
#include <string.h>
#include "wlanprj.h"



void wlan_analyse(FILE* fp) {
	int ssidNum = wlan_count(fp);
	ssid* ssid_list = (ssid*)malloc(sizeof(ssid) * ssidNum);
	char buf[MAXCHAR];
	int lc = 0;//line count
	int i = 0;
	while (fgets(buf, MAXCHAR, fp)) {
		//if (buf[0] == '\n') continue;//ignore empty line
		enum LINE_TYPE tmp = what_line(buf);
		//if (tmp == UNKNOWN) continue;//ignore uknown information line
	    if (lc>3 && tmp == SSID) {
			ssid_list[i].num_ap = i+1;
			ssid_list[i].ssidnm = read_value(buf,SSID);
			i++;
		}






		lc++;
	}
	

	
	
	
	
	
	printf("Found %d WLANs", ssidNum);
	printf("\n");

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


////int wlan_number(char*);
char* read_value(char* buf,char* kw) {
	char* token = strtok(buf, ":");


	
}
enum LINE_TYPE what_line(char* buf) {
	char keyword[MAXCW];
	//read buf，renturn keyword，same as one of enum type
	sscanf(buf, "%s", keyword);
	//if type fit call function rea-value,
	if (strcmp(keyword, "SSID") == 0) return SSID;
	else if (strcmp(keyword, "Network") == 0) return NET;
	else if (strcmp(keyword, "Authentication") == 0) return AUTH;
	else if (strcmp(keyword, "Encryption") == 0) return ENCRYP;
	else if (strcmp(keyword, "BSSID") == 0) return BSSID;
	else if (strcmp(keyword, "Signal") == 0) return SIG;
	else if (strcmp(keyword, "Channel") == 0) return CH;
	else return UNKNOWN;
}
//void show_wlan(ssid* list, int typ) {
//
//	//show in each ssid (AP 123...)
//}
////void takeawaynewline(char*);