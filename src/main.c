/* Forth VM */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "machine.h"

void processFlags(int argc, char **argv, Machine *m)
{
	int ch;
	if (argc ==0)
		loadImage("forthdump", m);

	while ((ch = getopt(argc, argv, "i:v")) != -1) {
		switch (ch) {
		case 'i':
			if(loadImage(optarg, m))
				break;
			else
				exit(1);
		case 'v':
			m->debug++;
			break;
		}
	}
}

int main(int argc, char **argv)
{
	Machine m = initMachine();
	processFlags(argc, argv, &m);
	run(&m);
	writeImage(&m, "forthdump");
	printf("Done.\n");
}
