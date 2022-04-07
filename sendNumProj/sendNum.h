
#pragma once

#define N 20

typedef struct {
	int max;
	int min;
	char rname[N];
}numScope;

void send_data(numScope);
