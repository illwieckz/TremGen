ctftrunk
{
	qer_editorimage models/mapobjects/ctftree/ctftree

	{
		map models/mapobjects/ctftree/ctftree
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
	deformVertexes wave 3 sin 0 1 0 .5
	deformVertexes bulge 3 3 .8

	nopicmip
	surfaceparm pointlight

	{
		map models/mapobjects/ctftree/ctftree
		alphaFunc GE128
		rgbGen vertex
	}
}

// Workaround for new picomodel
models/mapobjects/ctftree/ctftrunk
{
	qer_editorimage models/mapobjects/ctftree/ctftree

	{
		map models/mapobjects/ctftree/ctftree
		rgbGen Vertex
	}
}

models/mapobjects/ctftree/ctfleaves
{
	qer_editorimage models/mapobjects/ctftree/ctftree
	surfaceparm nonsolid
	surfaceparm nomarks
	surfaceparm noimpact

	cull disable
	deformVertexes wave 3 sin 0 1 0 .5
	deformVertexes bulge 3 3 .8

	nopicmip
	surfaceparm pointlight

	{
		map models/mapobjects/ctftree/ctftree
		alphaFunc GE128
		rgbGen vertex
	}
}
