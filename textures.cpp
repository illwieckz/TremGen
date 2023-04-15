#include "main.h"
#include "math.h"

#ifndef TREMGEN_TEXTURES_ROOT
	#define TREMGEN_TEXTURES_ROOT "tremgen"
#endif

#ifndef COMMON_TEXTURES_ROOT
	#define COMMON_TEXTURES_ROOT "common"
#endif

string
getTexture(int i) {
	stringstream coord, ret;
	int j = 0;
	for (j = 0; j <= 3; j++) {
		if (j < 2) { // offsets
			coord << 16 * round(5 * random()) << " ";
		} else if (j == 2) { // rot
			coord << round(360 * random()) << " ";
		}
	}
	switch (i) {
	case TEXTURE_SKYBOX:
		return TREMGEN_TEXTURES_ROOT "/skybox 0 0 0 0.5 0.5 0 0 0";
	case TEXTURE_ALPHA_50:
		return COMMON_TEXTURES_ROOT "/alpha_050 0 0 0 0.5 0.5 0 0 0";
	case TEXTURE_ALPHA_0:
		return COMMON_TEXTURES_ROOT "/alpha_000 0 0 0 0.5 0.5 0 0 0";
	case TEXTURE_ALPHA_100:
		return COMMON_TEXTURES_ROOT "/alpha_100 0 0 0 0.5 0.5 0 0 0";
	case TEXTURE_CAULK:
		return COMMON_TEXTURES_ROOT "/caulk 0 0 0 1 1 0 0 0";
	case TEXTURE_HINT:
		return COMMON_TEXTURES_ROOT "/hint 0 0 0 1 1 0 0 0";
	case TEXTURE_SKIP: // dans trem c'est toujours hint
		return COMMON_TEXTURES_ROOT "/hint 0 0 0 1 1 0 0 0";
	case TEXTURE_TER1:
		ret << TREMGEN_TEXTURES_ROOT "/ter_moss_mud " << coord.str() << "1 1 0 0 0";
		return ret.str();
	case TEXTURE_TER2:
		ret << TREMGEN_TEXTURES_ROOT "/ter_dirt_mud " << coord.str() << "1 1 0 0 0";
		return ret.str();
	case TEXTURE_TER3:
		ret << TREMGEN_TEXTURES_ROOT "/ter_srock_mud " << coord.str() << "1 1 0 0 0";
		return ret.str();
	case TEXTURE_TER4:
		ret << TREMGEN_TEXTURES_ROOT "/ter_rock_mud " << coord.str() << "1 1 0 0 0";
		return ret.str();
	case TEXTURE_WATER:
		return TREMGEN_TEXTURES_ROOT "/water 0 0 0 1 1 0 0 0";
	case TEXTURE_WATER_CAULK:
		return TREMGEN_TEXTURES_ROOT "/watercaulk 0 0 0 1 1 0 0 0";
	default:
		return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
		// return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
	}
}
