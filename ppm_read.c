#include "ppm_read.h"

static int whitespace(char c) {
	return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

int _ppm_to_floatp(struct _ppm ppm, float **ret) {
	*ret = malloc(sizeof(float) * ppm.width * ppm.height * 3);
	for(int i = 0; i < ppm.width * ppm.height * 3; i++)
		(*ret)[i] = (float)(unsigned char)ppm.pixels[i] / ppm.depth;
}

int _ppm_read(const char *path, struct _ppm *ppm) {
	FILE *fp;
	int fsz, count, i;
	char *content, buff[10];

	fp = fopen(path, "r");
	fsz = (fseek(fp, 0L, SEEK_END), ftell(fp)); rewind(fp);
	content = malloc(fsz);
	fread(content, 1, fsz, fp);
	fclose(fp);

	count = 3;
	//check file type
	if(content[0] != 'P' || content[1] != '6') {
		printf("ERROR: %s is not a ppm file", path);
		exit(0);
	}
	//check width
	i = 0;
	while( whitespace(content[count])) count++;
	while(!whitespace(content[count])) {
		if(i > 9) {
			printf("ERROR: width to large\n");
			return -1;
		}
		buff[i++] = content[count];
		buff[i] = '\0';
		count++;
	}
	ppm->width = atoi(buff);
	//check height
	i = 0;
	while( whitespace(content[count])) count++;
	while(!whitespace(content[count])) {
		if(i > 9) {
			printf("ERROR: height to large\n");
			return -1;
		}
		buff[i++] = content[count];
		buff[i] = '\0';
		count++;
	}
	ppm->height = atoi(buff);
	//check bitdepth
	i = 0;
	while( whitespace(content[count])) count++;
	while(!whitespace(content[count])) {
		if(i > 3) {
			printf("ERROR: bitdepth too large, must be less than "
					"255\n");
			return -1;
		}
		buff[i++] = content[count];
		buff[i] = '\0';
		count++;
	}
	ppm->depth = atoi(buff);
	if(ppm->depth > 255) {
		printf("ERROR: bitdepth too large must be less than 255\n");
		return -1;
	}
	while( whitespace(content[count])) count++;
	//check data
	ppm->pixels = malloc(ppm->width * ppm->height * 3);
	memcpy(ppm->pixels, content + count, ppm->width * ppm->height * 3);
}








