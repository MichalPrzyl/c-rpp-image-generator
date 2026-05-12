#include <stdio.h>

int main(){
  printf("Hello world!\n");
  int width = 512;
  int height = 512;
  FILE *f = fopen("output.ppm", "w");

  printf("Generating image \"output.ppm\"\n");
  
  fprintf(f, "P3\n%d %d\n255\n", width, height);
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      int r = x % 256;
      int g = y % 256;
      int b = (x + y) % 256;
      fprintf(f, "%d %d %d ", r,g,b);
    }
    fprintf(f, "\n");
  }

  fclose(f);
  
  return 0;
}
