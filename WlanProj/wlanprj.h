#pragma once
#define CMD "netsh wlan show networks mode=bssid > wlan.txt"

#define MAXCHAR 1024
#define MAXCW 25

enum LINE_TYPE {UNKNOWN =-1, SSID, NET, AUTH, ENCRYP, BSSID, SIG, RADIO, CH};

typedef struct {
	char apmac[20];//mac-address of AP:
	int signal_strength;//a percentage value
	int channel;//between 1-13 in EU
}bssid;

typedef struct {
	char ssidnm[30];//name of WLAN(SSID)
	int num_ap;//number of aps
    bssid aplist[20 ];//a list of APs(dynamics)
}ssid;


void wlan_analyse(FILE* fp);
int wlan_count(FILE*);
//int wlan_number(char*);
char* read_value(char*);
enum LINE_TYPE what_line(char*);
void show_wlan(ssid*, int);
//void takeawaynewline(char*);

