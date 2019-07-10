#include <cstdlib>
#include "fractal.h"

static const double Delta = 0.001;
static const double xMid =  0.23701;
static const double yMid =  0.521;

int main(int argc, char *argv[]) {
  	printf("Fractal v1.6 [OpenAcc]\n");

  	// check command line
  	if (argc != 3) {fprintf(stderr, "usage: %s frame_width num_frames\n", argv[0]); exit(-1);}
  	int width = atoi(argv[1]);
  	if (width < 10) {fprintf(stderr, "error: frame_width must be at least 10\n"); exit(-1);}
  	int frames = atoi(argv[2]);
  	if (frames < 1) {fprintf(stderr, "error: num_frames must be at least 1\n"); exit(-1);}
  	printf("computing %d frames of %d by %d fractal\n", frames, width, width);

  	// allocate picture array
  	int size = frames*width*width;
  	unsigned char* pic = (unsigned char*)malloc(size * sizeof(unsigned char));

  	// compute frames
  	double delta;
  	#pragma acc data copy(pic[:size], delta)
  	#pragma acc parallel loop
  	for (int frame = 0; frame < frames; frame++) {
    	delta = Delta;
    	for(int i = 0; i < frame; i++) {
        	delta *= 0.98;
    	}
    	const double xMin = xMid - delta;
    	const double yMin = yMid - delta;
    	const double dw = 2.0 * delta / width;
    	for (int row = 0; row < width; row++) {
      		const double cy = yMin + row * dw;
      		for (int col = 0; col < width; col++) {
        		const double cx = xMin + col * dw;
        		double x = cx;
        		double y = cy;
        		int depth = 256;
        		double x2, y2;
        	do {
          		x2 = x * x;
          		y2 = y * y;
          		y = 2 * x * y + cy;
          		x = x2 - y2 + cx;
          		depth--;
        	} while ((depth > 0) && ((x2 + y2) < 5.0));
        	pic[frame * width * width + row * width + col] = (unsigned char)depth;
      		}
    	}
    	//delta *= 0.98;
  	}
    
  	// verify result by writing frames to BMP files
  	if ((width <= 256) && (frames <= 100)) {
    	for (int frame = 0; frame < frames; frame++) {
      		char name[32];
      		sprintf(name, "fractalAcc%d.bmp", frame + 1000);
      		writeBMP(width, width, &pic[frame * width * width], name);
    	}
  	}

  	delete [] pic;
  	return 0;
}