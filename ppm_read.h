#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef PPM_READ_H
struct _ppm {
	int width,
		height,
		depth;
	char *pixels;
};
int _ppm_to_floatp(struct _ppm ppm, float **ret);
int _ppm_read(const char *path, struct _ppm *ppm);
#endif
