# do_ppm
a simple raw ppm (portable pixel map) loader

PPM specification:
  https://netpbm.sourceforge.net/doc/ppm.html

do_ppm contains the following structs and functions
```C
struct _ppm {
  int width, height, depth;
  char *pixels;
}; // the data from a ppm file
int _ppm_read(const char *path, struct _ppm *ppm); // reads the ppm file at path into <ppm>
                                                   // returns 0 on success and returns < 0 on fail
int _ppm_to_floatp(struct _ppm ppm, float **ret);  // reads the ppm data from whatever depth it is in
                                                   // into a set of floats between 0, and 1
```

for example we can load and print an images float values as follows:
```C
#include <stdio.h>
#include "ppm_read.h"

int main(int argc, char *argv[]) {
  struct _ppm image;
  float      *image_buffer;
  char       *path;

  //get path
  if(argc < 2) {
    printf("usage: %s <image path>\n", argv[0]);
    exit(0);
  }
  path = argv[1];
  printf("%s\n", path);

  //read image
  _ppm_read(path, &image);

  //read into floats
  _ppm_to_floatp(image, &image_buffer);

  //print results
  for(int i = 0; i < image.width * image.height * 3; i++)
    printf("%f ", image_buffer[i]);
  printf("\n");

  return 0;
}
```













