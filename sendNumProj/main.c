#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sendNum.h"

int main() {
	numScope r;
	printf("Number Monitoring Record\n");
	printf("Enter users' name: ");
	scanf_s("%s", r.rname, (unsigned)_countof(r.rname));
	r.max = rand() % 50 + 51;
	r.min = rand() % 50 + 1;
	send_data(r);
	printf("Rockn'Roll\n");

	return 0;
}