//***************************************************************
// multiplant.shader	Todd Gantzler/ydnar/Obsidian	28.05.04
// Originally by Todd Gantzler, this file has been rewritten to
// work properly with proper alpha and Q3Map2 support. Vertex lit
// by default.
//***************************************************************

models/mapobjects/multiplant/fern
{
	qer_editorImage models/mapobjects/multiplant/fern
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/fern
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/bannanaleaf
{	
	qer_editorImage models/mapobjects/multiplant/bannanaleaf
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/bannanaleaf
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/batleaf
{
	qer_editorImage models/mapobjects/multiplant/batleaf
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/batleaf
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/batleaf2
{
	qer_editorImage models/mapobjects/multiplant/batleaf2
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none
	deformVertexes wave 100 sin 3 5 0.1 0.1

	{
		map models/mapobjects/multiplant/batleaf2
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
	{
		map models/mapobjects/multiplant/batleaf2veins
		blendFunc blend
		rgbGen wave sin 0 1 0 .33
		depthFunc equal
	}
}

models/mapobjects/multiplant/leaf1
{
	qer_editorImage models/mapobjects/multiplant/leaf1
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/leaf1
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/leaf2
{
	qer_editorImage models/mapobjects/multiplant/leaf2
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/leaf2
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/leaf3
{
	qer_editorImage models/mapobjects/multiplant/leaf3
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/leaf3
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/pleaf1
{
	qer_editorImage models/mapobjects/multiplant/pleaf1
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/pleaf1
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/pleaf2
{
	qer_editorImage models/mapobjects/multiplant/pleaf2
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/pleaf2
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/pleaf3
{
	qer_editorImage models/mapobjects/multiplant/pleaf3
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/pleaf3
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/multiplant/palmfrond
{
	qer_editorImage models/mapobjects/multiplant/palmfrond
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	cull none

	{
		map models/mapobjects/multiplant/palmfrond
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

// Note: no longer uses invisible, replaced with nodraw
models/mapobjects/multiplant/invisible
{
	qer_editorImage textures/common/nodraw

	surfaceparm nodraw
	surfaceparm nolightmap
	surfaceparm nonsolid	//Forces nonsolid even on autoclipped models
	surfaceparm trans
	surfaceparm nomarks
}

//***************************************************************
// palms.shader		Todd Gantzler/ydnar/Obsidian	28.05.04
// Originally by Todd Gantzler, this file has been rewritten to
// work properly with proper alpha and Q3Map2 support. Vertex lit
// by default.
//***************************************************************


models/mapobjects/palm2/trunk
{
	qer_editorImage models/mapobjects/palm2/trunk

	surfaceparm pointlight

	{
		map models/mapobjects/palm2/trunk
		rgbGen vertex
	}
}

models/mapobjects/palm1/palm1
{
	qer_editorImage models/mapobjects/palm1/palm1
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	deformVertexes autosprite2
	cull none

	{
		map models/mapobjects/palm1/palm1
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}

models/mapobjects/palm3/palmtop
{
	qer_editorImage models/mapobjects/palm3/palmtop
	qer_alphaFunc gequal 0.5

	surfaceparm alphashadow
	surfaceparm pointlight
	surfaceparm trans

	deformVertexes autosprite
	cull none

	{
		map models/mapobjects/palm3/palmtop
		rgbGen vertex
		alphaFunc GE128
		depthWrite
	}
}
