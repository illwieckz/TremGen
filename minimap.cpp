#include "main.h"
#include "altimap.h"
#define trem_random() ((double)rand() / RAND_MAX)

#include "CImg.h"
using namespace cimg_library;

int
main(int argc, char **argv) {
	char *filename;

	AltitudeMap hmap(MAPSIZE, MAPSIZE);

	if (argc > 1) {
		srand(atoi(argv[1]));
		cout << "using seed " << argv[1] << endl;
	} else {
		srand(time(NULL));
	}

	if (argc > 2) {
		filename = (char *) malloc(sizeof(char) * (1 + strlen(argv[2])));
		strcpy(filename, argv[2]);
	} else {
		filename = (char *) malloc(sizeof(char) * (1 + strlen("levelshot.tga")));
		strcpy(filename, "levelshot.tga");
	}

	cout << "generating map" << endl;
	hmap.randomize(0.5);
	hmap.subdivision(0.85, trem_random(), trem_random(), trem_random(), trem_random());
	hmap.randomize(0.2);
	hmap.erosion(2, 1);
	hmap.normalize();

	cout << "generating levelshot" << endl;
	CImg<double> img(10 * MAPSIZE, 10 * MAPSIZE, 1, 3);
	// Cimg.fill(158);

	// img.RGBtoHSV();
	// unsigned char purple[3]={255, 0, 255};

	cimg_forXY(img, x, y) {
		img(x, y, 0) = (1 - hmap.getaltitude(x / 10, y / 10)) * 0.4f * 2 * M_PI;
		img(x, y, 1) = 0.5f;
		img(x, y, 2) = 1.0f;
	}

	img.HSVtoRGB().blur(3);

	cout << "Saving levelshot as " << filename << endl;
	img.save_imagemagick(filename);
	free(filename);

#ifdef DEBUG
	img.display("HeightMap");
#endif
}
