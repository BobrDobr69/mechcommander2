//---------------------------------------------------------------------------
//
// cepoly.h - This file contains the class declarations for the polygon element
//
//---------------------------------------------------------------------------//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//

#ifndef CEPOLY_H
#define CEPOLY_H
//---------------------------------------------------------------------------
// Include files

#ifndef CELEMENT_H
#include "celement.h"
#endif

#ifndef VFX_H
#include "vfx.h"
#endif

//---------------------------------------------------------------------------
struct PolyElementData
{
	uint32_t		numVertices;			//Actually num_vertices + extras for clipping
	SCRNVERTEX	vertices[6]; 			//Draw Vertices

	bool		correctTexture;			//Should we Correctly Texture?
	bool		isClipped;				//Set by zclip to let me know
	bool		drawTranslucent;		//Used for FX
	bool		StatusBar;				//Is this a status bar?
	int32_t		BarWidth;				//Width of status bar
	int32_t			BarColor;				//Color of status bar

	puint8_t	textureMap;				//Pointer to Bitmap for Texture
	int32_t	    width;					//Width of texture
	int32_t		height;					//Height of texture
	char*		hazePalette;			//Translucency/haze table


	void init(void)
	{
		numVertices = 0;
		correctTexture = FALSE;
		isClipped = FALSE;
		StatusBar = FALSE;
		textureMap = 0;
		width = 0;
		height = 0;
		hazePalette = nullptr;
		drawTranslucent = FALSE;
	}

	PolyElementData(void)
	{
		init(void);
	}
};

typedef PolyElementData* PolyElementDataPtr;

//---------------------------------------------------------------------------
class PolygonElement : public Element
{
public:

	PolyElementData		polyData;

	PolygonElement(void)
	{
		polyData.init(void);
	}

	PolygonElement(PolyElementDataPtr pData, int32_t depth);

	virtual void draw(void);
};

//---------------------------------------------------------------------------
#endif
