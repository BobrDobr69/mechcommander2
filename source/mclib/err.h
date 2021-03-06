//===========================================================================//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//
//***************************************************************************
//
//								ERR.H
//
//***************************************************************************

#ifndef ERR_H
#define	ERR_H

//***************************************************************************

void Fatal(int32_t errCode, PSTR errMessage);

void Assert(bool test, int32_t errCode, PSTR errMessage);

//***************************************************************************

#endif
