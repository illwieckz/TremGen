ctftrunk
{
	qer_editorimage models/mapobjects/ctftree/ctftree
	{
		map models/mapobjects/ctftree/ctftree.tga
		rgbGen Vertex
	}
}
ctfleaves
{
	qer_editorimage models/mapobjects/ctftree/ctftree
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm noimpact

	cull disable
	//deformVertexes wave 3 sin 0 1 0 .5
	//deformVertexes bulge 3 3 .8
	nopicmip
	surfaceparm pointlight
	{
		map models/mapobjects/ctftree/ctftree.tga
		alphaFunc GE128
		rgbGen vertex
	}
}
