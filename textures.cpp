#include "main.h"
#include "math.h"
#ifndef TEXTURES_ROOT
#define TEXTURES_ROOT "tremgen"
#endif


string getTexture(int i){
                
        stringstream end,ret;
        int j=0;
        for(j=0;j<8;j++){
                if(j<3 || j>4){
                        if(j<2){ //offsets
                                end << 16*round(5*random()) << " ";
                        }else if(j==2){//rot
                                end << round(360*random()) << " ";
                        }else{ //autres

                                end << 20*random() << " ";
                        }
                }else{
                        end << 0 << " ";
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
                        ret << TEXTURES_ROOT"/ter_moss_mud ";
                        break;
                case TEXTURE_TER2:
                        ret << TEXTURES_ROOT"/ter_dirt_mud ";
                        break;
                case TEXTURE_TER3:
                        ret << TEXTURES_ROOT"/ter_srock_mud ";
                        break;
                case TEXTURE_TER4:
                        ret << TEXTURES_ROOT"/ter_rock_mud ";
                        break;
                case TEXTURE_WATER:
                        return TEXTURES_ROOT"/water 0 0 0 0.0 0.0 0 0 0";
                case TEXTURE_WATER_CAULK:
                        return TEXTURES_ROOT"/watercaulk 0 0 0 0.0 0.0 0 0 0";
                default:
			return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
			//return "arachnid2/dirt_1 0 0 0 0.5 0.5 0 0 0";
        }
        ret << end.str();
        return ret.str();
}

