
#include "wlanprj.h"

void wlan_analyse(FILE* fp) {
	int ssidNum = wlan_count(fp);
	ssid* ssid_list = (ssid*)malloc(sizeof(ssid) * ssidNum);
	if (ssid_list == NULL) {
		printf("error in malloc");
		return;
	}
	char buf[MAXCHAR];
	int lc = 0, i = 0,j =0;//i is ssid count, j is ap count.lc is line count.
	while (fgets(buf, MAXCHAR, fp) != NULL) {
		enum LINE_TYPE tmp = what_line(buf);
		if ((lc >= 4) && (tmp == SSID)) {
			if (j > 0) { 
				i++; 	
			}
			if (i > 0) { 
				j = 0; 
			}
			strcpy(ssid_list[i].ssidnm,read_value(buf));
			//ssid_list[i].num_ap = j;	
		}
		else if ((lc >= 4) && (tmp == NET)) {
			strcpy(ssid_list[i].ssid_net, read_value(buf));
		}
		else if ((lc >= 4) && (tmp == AUTH)) {
			strcpy(ssid_list[i].ssid_aut, read_value(buf));
		}
		else if ((lc >= 4) && (tmp == ENCRYP)) {
			strcpy(ssid_list[i].ssid_encr, read_value(buf));
		}
		else if ((lc >= 4) && (tmp == BSSID)) {
			strcpy(ssid_list[i].aplist[j].apmac,read_value(buf));
		}
		else if ((lc >= 4) && (tmp == SIG)) {
			ssid_list[i].aplist[j].signal_strength = dBm_calculation(atoi(read_value(buf)));
		}
		else if ((lc >= 4) && (tmp == CH)) {
			ssid_list[i].aplist[j].channel = atoi(read_value(buf));
			j++;
			ssid_list[i].num_ap = j-1;
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
	char value[40];
	char* v = value;
	char* p = buf;
	if (p = strchr(buf, ':')) {
		size_t len = strlen(++p);
		if (len > 39) {
			fputs("error: value exceeds allowable length.\n", stderr);
			return 1;
		}
		memcpy(v, p, len + 1);
		return takeawaynewline(v);
	}
	
}
enum LINE_TYPE what_line(char* buf) {
	char keyword[20];
	char sc[20];
	sscanf(buf, "%s %s", keyword,sc);
	if (strcmp(keyword, "SSID") == 0) return SSID;
	else if (strcmp(keyword, "Network") == 0) return NET;
	else if (strcmp(keyword, "Authentication") == 0) return AUTH;
	else if (strcmp(keyword, "Encryption") == 0) return ENCRYP;
	else if (strcmp(keyword, "BSSID") == 0) return BSSID;
	else if (strcmp(keyword, "Signal") == 0) return SIG;
	//else if (strcmp(keyword, "Channel") == 0) return CH;
	else if (strcmp(keyword, "Channel") == 0 && sc[0] == ':') return CH;
	else return UNKNOWN;
}
void show_wlan(ssid* list, int ssidc) {
	printf("Found %d WLANs\n", ssidc);
	printf("\n");
	for (int i = 0; i < ssidc; i++) {
		printf("ESSID: %s", list[i].ssidnm);
		printf("\n\tNetwork type: %s", list[i].ssid_net);
		printf("\n\tAuthentication: %s", list[i].ssid_aut);
		printf("\n\tEncryption: %s\n", list[i].ssid_encr);
		printf("\n");
		sort_by_signal(list[i].aplist[list[i].num_ap+1].signal_strength, list[i].num_ap + 1);
		for (int j = 0; j < (list[i].num_ap + 1); j++) {
			printf("\tAP %d MAC: %s  Channel: %d, Signal: %ddBm",j + 1, list[i].aplist[j].apmac, list[i].aplist[j].channel, list[i].aplist[j].signal_strength);
		}
		printf("\n\n");
	}
}
char* takeawaynewline(char* value) {
	int len = strlen(value);
	if (value[len - 1] == '\n') {
		value[len - 1] = 0;
	}
	return value;
}
int dBm_calculation(int sig) {
	int dBm = (sig / 2) - 100;
	return dBm;
}

void sort_by_signal(int number[], int n) {
	int tmp;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if (number[i] < number[j])
			{
				tmp = number[i];
				number[i] = number[j];
				number[j] = tmp;
			}
		}
	}
}
