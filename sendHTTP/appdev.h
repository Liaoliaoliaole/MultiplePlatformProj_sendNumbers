#pragma once

#define N 20

typedef struct {
	int max;
	int min;
	char rname[N];
}rock;

void send_data(rock);
