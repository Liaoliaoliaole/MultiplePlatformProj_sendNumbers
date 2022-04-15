#pragma once
#define CMD "netsh wlan show networks mode=bssid > wlan.txt"
#define MAXCHAR 100

enum LINE_TYPE {UNKNOWN, SSID, NET, AUTH, ENCRYP, BSSID, SIG, RADIO, CH};

typedef struct {
	char apmac[40];//mac-address of AP:
	int signal_strength;//a percentage value
	int channel;//between 1-13 in EU
}bssid;

typedef struct {
	char ssidnm[40];//name of WLAN(SSID)
	char ssid_net[30];
	char ssid_aut[30];
	char ssid_encr[10];
	int num_ap;//number of aps
    bssid aplist[20];//a list of APs(dynamics)
}ssid;


void wlan_analyse(FILE* fp);
int wlan_count(FILE*);
char* read_value(char*);
enum LINE_TYPE what_line(char*);
void show_wlan(ssid*, int);
char* takeawaynewline(char*);
int dBm_calculation(int);
void sort_by_signal(int number[], int n);
