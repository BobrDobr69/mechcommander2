/*************************************************************************************************\
MPLoadMap.h			: Interface for the MPLoadMap component.
//---------------------------------------------------------------------------//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//
\*************************************************************************************************/

//*************************************************************************************************

#pragma once

#ifndef MPLOADMAP_H
#define MPLOADMAP_H

//#include "logisticsdialog.h"
//#include <mechgui/asystem.h>
//#include <mechgui/alistbox.h>
//#include "attributemeter.h"
//#include "simplecamera.h"
//#include <mechgui/aanim.h>

class aButton;

class MPLoadMap : public LogisticsDialog
{
public:

	MPLoadMap(void);
	virtual ~MPLoadMap(void);

	void init(FitIniFile* file);
	bool isDone(void);
	virtual void		begin(void);
	virtual void		end(void);
	virtual void		render(int32_t xOffset, int32_t yOffset);
	virtual void		render(void);
	virtual void		update(void);
	virtual int32_t			handleMessage(uint32_t, uint32_t);

	void				beginSingleMission(void);

	PCSTR getMapFileName()
	{
		return selMapName;
	}

	static void			getMapNameFromFile(PCSTR pFileName, PSTR pBuffer, int32_t bufferLength);




private:
	int32_t indexOfButtonWithID(int32_t id);
	void seedDialog(bool bSeedSingle);
	void seedFromCampaign(void);



	aListBox				mapList;
	aLocalizedListItem	templateItem;

	EString					selMapName;

	bool					bIsSingle;



	void	updateMapInfo(void);
	void	seedFromFile(PCSTR pFileName);
	void	addFile(PCSTR pFileName, bool bSeedSingle);



};



//*************************************************************************************************
#endif  // end of file ( MPLoadMap.h )
