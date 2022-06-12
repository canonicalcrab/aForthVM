/* Functions for loading an image into the VM and
 * dumping images from the VM into a file */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "machine.h"

CELL loadImage(char *filename, Machine *m)
{
	FILE *fp;
	CELL size = 0;
	long length;

	if((fp = fopen(filename, "r")) != NULL){
		fseek(fp, 0, SEEK_END);
		length = ftell(fp) / sizeof(CELL);
		rewind(fp);

		size = fread(m->memory, sizeof(CELL), length, fp);
		fclose(fp);
	} else {
		printf("Unable to find file %s\n", filename);
	}
	return size;
}

CELL writeImage(Machine *m, char *filename)
{
	FILE *fp;

	if((fp = fopen(filename, "w")) != NULL){
		fwrite(m->memory,
			sizeof(CELL),
			sizeof(m->memory),
			fp);
	} else {
		printf("Failed to write to file %s\n", filename);
		return 0;
	}
	return 1;
}

