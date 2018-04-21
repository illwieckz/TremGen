textures/tremgen/skybox
{
	qer_editorimage textures/tremgen/mars.jpg
	surfaceparm noimpact
	surfaceparm nolightmap
	q3map_globaltexture
	q3map_skylight 250 3
	q3map_sun 1.00 0.949 0.977 150 135 45	
	surfaceparm sky
	skyparms env/tremgen/mars - -
}

textures/tremgen/rockground_grass
{
        q3map_nonplanar
        q3map_shadeangle 180
        qer_editorimage textures/atcs/rockground.tga

        q3map_surfaceModel models/mapobjects/multiplant/multiplant_b.md3 128 0.1 0.05 0.25 0 360 1
        {
                map $lightmap
                rgbGen identity
        }
	{
                map textures/atcs/rockground.tga
                blendFunc filter
        }
}

textures/tremgen/force_field_s
        {
        qer_editorimage textures/tremgen/force_field_gtk.tga
        surfaceparm trans
        surfaceparm nomarks
        surfaceparm nolightmap
        cull none
        {
                map textures/tremgen/force_field.tga
                tcMod Scroll .1 0
                blendFunc add
        }
        {
                map textures/tremgen/force_grid.tga
                tcMod Scroll -.01 0
                blendFunc add
                rgbgen wave sin .2 .2 0 .4
        }
}

textures/tremgen/ter_moss_mud
{
	qer_editorimage textures/tremgen/ter_mossmud.tga
	q3map_nonplanar
	q3map_shadeangle 180
	q3map_tcGen ivector ( 256 0 0 ) ( 0 256 0 )
	q3map_alphaMod dotproduct2 ( 0.0 0.0 0.75 )
	{
	map textures/tremgen/ter_moss1.tga
	rgbGen identity
	}
	{
	map textures/tremgen/ter_mud1.tga
	blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaFunc GE128
	rgbGen identity
	alphaGen vertex
	}
	{
	map $lightmap
	blendFunc GL_DST_COLOR GL_ZERO
	rgbGen identity
	}
}


textures/tremgen/ter_dirt_mud
{

	q3map_nonplanar
	qer_editorimage textures/tremgen/ter_mossmud.tga
	q3map_shadeangle 180
	q3map_tcGen ivector ( 256 0 0 ) ( 0 256 0 )
	q3map_alphaMod dotproduct2 ( 0.0 0.0 0.75 )
	{
	map textures/tremgen/ter_dirt1.tga
	rgbGen identity
	}
	{
	map textures/tremgen/ter_mud1.tga
	blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaFunc GE128
	rgbGen identity
	alphaGen vertex
	}
	{
	map $lightmap
	blendFunc GL_DST_COLOR GL_ZERO
	rgbGen identity
	}
}


textures/tremgen/ter_srock_mud
{

	qer_editorimage textures/tremgen/ter_mossmud.tga
	q3map_nonplanar
	q3map_shadeangle 180
	q3map_tcGen ivector ( 256 0 0 ) ( 0 256 0 )
	q3map_alphaMod dotproduct2 ( 0.0 0.0 0.75 )
	{
	map textures/tremgen/ter_rock3.tga
	rgbGen identity
	}
	{
	map textures/tremgen/ter_mud1.tga
	blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaFunc GE128
	rgbGen identity
	alphaGen vertex
	}
	{
	map $lightmap
	blendFunc GL_DST_COLOR GL_ZERO
	rgbGen identity
	}
}


textures/tremgen/ter_rock_mud
{

	qer_editorimage textures/tremgen/ter_mossmud.tga
	q3map_nonplanar
	q3map_shadeangle 180
	q3map_tcGen ivector ( 256 0 0 ) ( 0 256 0 )
	q3map_alphaMod dotproduct2 ( 0.0 0.0 0.75 )
	{
	map textures/tremgen/ter_rock2.tga
	rgbGen identity
	}
	{
	map textures/tremgen/ter_mud1.tga
	blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	alphaFunc GE128
	rgbGen identity
	alphaGen vertex
	}
	{
	map $lightmap
	blendFunc GL_DST_COLOR GL_ZERO
	rgbGen identity
	}
}
//ancient remains
textures/tremgen/alpha_000	// Primary texture ONLY
{
	q3map_alphaMod volume
	q3map_alphaMod set 0
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/tremgen/alpha_025
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.25
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/tremgen/alpha_050	// Perfect mix of both Primary + Secondary
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.50
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/tremgen/alpha_075
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.75
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/tremgen/alpha_085
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.85
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/tremgen/alpha_100	// Secondary texture ONLY
{
	q3map_alphaMod volume
	q3map_alphaMod set 1.0
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/tremgen/watercaulk
{ 
	qer_editorimage textures/common/caulk 
	surfaceparm nomarks 
	surfaceparm nodraw 
	surfaceparm water 
	//q3map_nolightmap 
}

textures/tremgen/water
{ 
   qer_editorimage textures/tremgen/water.jpg 
   qer_trans .5 
   q3map_lightimage textures/tremgen/water.jpg 
   //q3map_surfacelight 10000 
   q3map_globaltexture 

   surfaceparm trans 
   surfaceparm nonsolid 
   surfaceparm water 

   cull disable 
   deformVertexes wave 64 sin .25 .25 0 .5
   { 
      map textures/tremgen/water.jpg 
      blendFunc GL_dst_color GL_one 
      //rgbgen identity
      rgbgen vertex
      //alphagen vertex
      alphaFunc GE128
      alphaGen const 128
      tcmod scale .5 .5 
      tcmod scroll .025 .01 
   } 
   { 
      map textures/tremgen/water.jpg 
      blendFunc GL_dst_color GL_one 
      tcmod scale -.5 -.5 
      tcmod scroll .025 .025 
   } 
   { 
      map $lightmap 
      blendFunc GL_dst_color GL_zero 
      //rgbgen identity       
      rgbgen vertex
      //alphagen vertex
      alphaFunc GE128
      alphaGen const 128 
   } 
}


