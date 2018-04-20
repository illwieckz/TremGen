#include "main.h"
#include "math.h"
#ifndef TEXTURES_ROOT
#define TEXTURES_ROOT "tremgen"
#endif


string getTexture(int i){
                
        stringstream coord, ret;
        int j=0;
        for(j=0; j<=3; j++) {
                        if(j<2){ //offsets
                                coord << 16*round(5*random()) << " ";
                        }else if(j==2){//rot
                                coord << round(360*random()) << " ";
                        }
        }
   switch(i){
                case TEXTURE_SKYBOX:
                        return TEXTURES_ROOT"/skybox 0 0 0 0.5 0.5 0 0 0";
                case TEXTURE_ALPHA_50:
                        return TEXTURES_ROOT"/alpha_050 0 0 0 0.5 0.5 0 0 0";
                case TEXTURE_ALPHA_0:
                        return TEXTURES_ROOT"/alpha_0 0 0 0 0.5 0.5 0 0 0";
                case TEXTURE_ALPHA_100:
                        return TEXTURES_ROOT"/alpha_100 0 0 0 0.5 0.5 0 0 0";
                case TEXTURE_CAULK:
                        return "common/caulk 0 0 0 0 0 0 0 0";
                case TEXTURE_HINT:
                        return "common/hint 0 0 0 0 0 0 0 0";
                case TEXTURE_SKIP: //dans trem c'est toujours hint
                        return "common/hint 0 0 0 0 0 0 0 0";
                case TEXTURE_TER1:
                        ret << TEXTURES_ROOT"/ter_moss_mud " << coord.str() << "0 0 0 0 0";
                        return ret.str();
                case TEXTURE_TER2:
                        ret << TEXTURES_ROOT"/ter_dirt_mud " << coord.str() << "0 0 0 0 0";
                        return ret.str();
                case TEXTURE_TER3:
                        ret << TEXTURES_ROOT"/ter_srock_mud " << coord.str() << "0 0 0 0 0";
                        return ret.str();
                case TEXTURE_TER4:
                        ret << TEXTURES_ROOT"/ter_rock_mud " << coord.str() << "0 0 0 0 0";
                        return ret.str();
                case TEXTURE_WATER:
                        return TEXTURES_ROOT"/water 0 0 0 0.0 0.0 0 0 0";
                case TEXTURE_WATER_CAULK:
                        return TEXTURES_ROOT"/watercaulk 0 0 0 0.0 0.0 0 0 0";
                default:
			return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
			//return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
        }
}

