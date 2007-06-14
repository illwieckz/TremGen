/*-----------------------------------------------------------------------------

  File	      : alias.h

  Description : File defining several macros to ensure backward compatibility
  with older versions of CImg.

  Copyright  : David Tschumperle - http://www.greyc.ensicaen.fr/~dtschump/

  This software is governed by the CeCILL  license under French law and
  abiding by the rules of distribution of free software.  You can  use,
  modify and/ or redistribute the software under the terms of the CeCILL
  license as circulated by CEA, CNRS and INRIA at the following URL
  "http://www.cecill.info".

  As a counterpart to the access to the source code and  rights to copy,
  modify and redistribute granted by the license, users are provided only
  with a limited warranty  and the software's author,  the holder of the
  economic rights,  and the successive licensors  have only  limited
  liability.

  In this respect, the user's attention is drawn to the risks associated
  with loading,  using,  modifying and/or developing or reproducing the
  software by the user in light of its specific status of free software,
  that may mean  that it is complicated to manipulate,	and  that  also
  therefore means  that it is reserved for developers  and  experienced
  professionals having in-depth computer knowledge. Users are therefore
  encouraged to load and test the software's suitability as regards their
  requirements in conditions enabling the security of their systems and/or
  data to be ensured and,  more generally, to use and operate it in the
  same conditions as regards security.

  The fact that you are presently reading this means that you have had
  knowledge of the CeCILL license and that you accept its terms.

  ------------------------------------------------------------------------------*/

#ifndef cimg_plugin_alias
#define cimg_plugin_alias

#define CImgl CImgList
#define cimgl_map cimglist_for
#define cimglist_map cimglist_for
#define cimg_map cimg_for
#define cimg_mapoff cimg_foroff
#define cimg_mapX cimg_forX
#define cimg_mapY cimg_forY
#define cimg_mapZ cimg_forZ
#define cimg_mapV cimg_forV
#define cimg_mapXY cimg_forXY
#define cimg_mapXZ cimg_forXZ
#define cimg_mapXV cimg_forXV
#define cimg_mapYZ cimg_forYZ
#define cimg_mapYV cimg_forYV
#define cimg_mapZV cimg_forZV
#define cimg_mapXYZ cimg_forXYZ
#define cimg_mapXYV cimg_forXYV
#define cimg_mapXZV cimg_forXZV
#define cimg_mapYZV cimg_forYZV
#define cimg_mapXYZV cimg_forXYZV
#define cimg_imapX cimg_for_insideX
#define cimg_imapY cimg_for_insideY
#define cimg_imapZ cimg_for_insideZ
#define cimg_imapV cimg_for_insideV
#define cimg_imapXY cimg_for_insideXY
#define cimg_imapXYZ cimg_for_insideXYZ
#define cimg_bmapX cimg_for_borderX
#define cimg_bmapY cimg_for_borderY
#define cimg_bmapZ cimg_for_borderZ
#define cimg_bmapV cimg_for_borderV
#define cimg_bmapXY cimg_for_borderXY
#define cimg_bmapXYZ cimg_for_borderXYZ
#define cimg_2mapX cimg_for2X
#define cimg_2mapY cimg_for2Y
#define cimg_2mapZ cimg_for2Z
#define cimg_2mapXY cimg_for2XY
#define cimg_2mapXZ cimg_for2XZ
#define cimg_2mapYZ cimg_for2YZ
#define cimg_2mapXYZ cimg_for2XYZ
#define cimg_3mapX cimg_for3X
#define cimg_3mapY cimg_for3Y
#define cimg_3mapZ cimg_for3Z
#define cimg_3mapXY cimg_for3XY
#define cimg_3mapXZ cimg_for3XZ
#define cimg_3mapYZ cimg_for3YZ
#define cimg_3mapXYZ cimg_for3XYZ
#define cimg_4mapX cimg_for4X
#define cimg_4mapY cimg_for4Y
#define cimg_4mapZ cimg_for4Z
#define cimg_4mapXY cimg_for4XY
#define cimg_4mapXZ cimg_for4XZ
#define cimg_4mapYZ cimg_for4YZ
#define cimg_4mapXYZ cimg_for4XYZ
#define cimg_5mapX cimg_for5X
#define cimg_5mapY cimg_for5Y
#define cimg_5mapZ cimg_for5Z
#define cimg_5mapXY cimg_for5XY
#define cimg_5mapXZ cimg_for5XZ
#define cimg_5mapYZ cimg_for5YZ
#define cimg_5mapXYZ cimg_for5XYZ
#define cimg_map2x2x1 cimg_for2x2
#define cimg_map3x3x1 cimg_for3x3
#define cimg_map4x4x1 cimg_for4x4
#define cimg_map5x5x1 cimg_for5x5
#define cimg_map2x2 cimg_for2x2
#define cimg_map3x3 cimg_for3x3
#define cimg_map4x4 cimg_for4x4
#define cimg_map5x5 cimg_for5x5
#define cimg_map3x3x3 cimg_for3x3x3
#define cimg_map2x2x2 cimg_for2x2x2
#define CImg_2x2x1 CImg_2x2
#define CImg_3x3x1 CImg_3x3
#define CImg_4x4x1 CImg_4x4
#define CImg_5x5x1 CImg_5x5
#define scroll translate
#define cimg_convert_path cimg_imagemagick_path
#define load_convert load_imagemagick
#define save_convert save_imagemagick
#endif
