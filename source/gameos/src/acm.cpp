/*******************************************************************************
 Copyright (c) 2011-2014, Jerker Back. All rights reserved.

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the following
 conditions are met (OSI approved BSD 2-clause license):

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/
/*******************************************************************************
 acm.cpp  - gameos Audio Compression Manager wrappers

 MechCommander 2 source code

 2014-07-24 jerker_back, created

 $LastChangedBy$

================================================================================
 RcsID = $Id$ */

#include "stdafx.h"

#include <acm.hpp>

#define MMFAILED(x)		((x & 0x80000000u) != 0)

#if _JUST_SOME_INFO
// implemented function declarations
HRESULT __stdcall wACMStreamPrepareHeader(HACMSTREAM has, PACMSTREAMHEADER pash, uint32_t fdwPrepare);
HRESULT __stdcall wACMStreamConvert(HACMSTREAM has, PACMSTREAMHEADER pash, uint32_t fdwConvert);
HRESULT __stdcall wACMStreamUnprepareHeader(HACMSTREAM has, PACMSTREAMHEADER pash, uint32_t fdwUnprepare);
HRESULT __stdcall wACMStreamClose(HACMSTREAM has, uint32_t fdwClose);
HRESULT __stdcall wACMStreamOpen(PHACMSTREAM phas, HACMDRIVER had, const PWAVEFORMATEX pwfxSrc, const PWAVEFORMATEX pwfxDst, PWAVEFILTER pwfltr, ULONG_PTR dwCallback, ULONG_PTR dwInstance, uint32_t fdwOpen);
HRESULT __stdcall wACMStreamSize(HACMSTREAM has, uint32_t cbInput, puint32_t pdwOutputBytes, uint32_t fdwSize);
HRESULT __stdcall wACMFormatSuggest(HACMDRIVER had, const struct tWAVEFORMATEX* pwfxSrc, const struct tWAVEFORMATEX* pwfxDst, uint32_t cbwfxDst, uint32_t fdwSuggest);
#endif

#pragma region wACMStreamPrepareHeader
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMStreamPrepareHeader</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="has"></param>
/// <param name="pash"></param>
/// <param name="fdwPrepare"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMStreamPrepareHeader(HACMSTREAM has, PACMSTREAMHEADER pash, uint32_t fdwPrepare)
{
	PSTR		pszErrorMessage;
	MMRESULT	hResult;
	InternalFunctionSpew("GameOS_DirectSound", "acmStreamPrepareHeader(0x%x, 0x%x, 0x%x)", has, pash, fdwPrepare);
	hResult = acmStreamPrepareHeader(has, pash, fdwPrepare);
	if(MMFAILED(hResult))
	{
		pszErrorMessage = ErrorNumberToMessage(hResult);
		//PAUSE(
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamPrepareHeader(0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					has,
					pash,
					fdwPrepare))
			ENTER_DEBUGGER;
	}
	return hResult;
}

#pragma region wACMStreamConvert
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMStreamConvert</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="has"></param>
/// <param name="pash"></param>
/// <param name="fdwConvert"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMStreamConvert(HACMSTREAM has, PACMSTREAMHEADER pash, uint32_t fdwConvert)
{
	PSTR		pszErrorMessage;
	MMRESULT	hResult;
	InternalFunctionSpew("GameOS_DirectSound", "acmStreamConvert(0x%x, 0x%x, 0x%x)", has, pash, fdwConvert);
	hResult = acmStreamConvert(has, pash, fdwConvert);
	if(MMFAILED(hResult))
	{
		pszErrorMessage = ErrorNumberToMessage(hResult);
		//PAUSE(
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamConvert(0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					has,
					pash,
					fdwConvert))
			ENTER_DEBUGGER;
	}
	return hResult;
}

#pragma region wACMStreamUnprepareHeader
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMStreamUnprepareHeader</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="has"></param>
/// <param name="pash"></param>
/// <param name="fdwUnprepare"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMStreamUnprepareHeader(HACMSTREAM has, PACMSTREAMHEADER pash, uint32_t fdwUnprepare)
{
	PSTR		pszErrorMessage;
	MMRESULT	hResult;
	InternalFunctionSpew("GameOS_DirectSound", "acmStreamUnprepareHeader(0x%x, 0x%x, 0x%x)", has, pash, fdwUnprepare);
	hResult = acmStreamUnprepareHeader(has, pash, fdwUnprepare);
	if(MMFAILED(hResult))
	{
		pszErrorMessage = ErrorNumberToMessage(hResult);
		//PAUSE(
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamUnprepareHeader(0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					has,
					pash,
					fdwUnprepare))
			ENTER_DEBUGGER;
	}
	return hResult;
}

#pragma region wACMStreamClose
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMStreamClose</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="has"></param>
/// <param name="fdwClose"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMStreamClose(HACMSTREAM has, uint32_t fdwClose)
{
	PSTR		pszErrorMessage;
	MMRESULT	hResult;
	InternalFunctionSpew("GameOS_DirectSound", "acmStreamClose(0x%x, 0x%x)", has, fdwClose);
	hResult = acmStreamClose(has, fdwClose);
	if(MMFAILED(hResult))
	{
		pszErrorMessage = ErrorNumberToMessage(hResult);
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamClose(0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					has,
					fdwClose))
			ENTER_DEBUGGER;
	}
	return hResult;
}

#pragma region wACMStreamOpen
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMStreamOpen</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="phas"></param>
/// <param name="had"></param>
/// <param name="pwfxSrc"></param>
/// <param name="pwfxDst"></param>
/// <param name="pwfltr"></param>
/// <param name="dwCallback"></param>
/// <param name="dwInstance"></param>
/// <param name="fdwOpen"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMStreamOpen(PHACMSTREAM phas, HACMDRIVER had, const PWAVEFORMATEX pwfxSrc,
			   const PWAVEFORMATEX pwfxDst, PWAVEFILTER pwfltr, ULONG_PTR dwCallback,
			   ULONG_PTR dwInstance, uint32_t fdwOpen)
{
	PSTR		pszwfDst;
	PSTR		pszwfSrc;
	PSTR		pszErrorMessage;
	MMRESULT	hResult;
	char		BUffer2[128];
	char		Buffer[128];
	pszwfDst = GetWaveFormat(Buffer, pwfxDst);
	pszwfSrc = GetWaveFormat(BUffer2, pwfxSrc);
	InternalFunctionSpew(
		"GameOS_DirectSound",
		"acmStreamOpen(0x%x, 0x%x, %s, %s, 0x%x,0x%x, 0x%x, 0x%x)",
		phas,
		had,
		pszwfSrc,
		pszwfDst,
		pwfltr,
		dwCallback,
		dwInstance,
		fdwOpen);
	hResult = acmStreamOpen(phas, had, pwfxSrc, pwfxDst, pwfltr, dwCallback, dwInstance, 1u);
	if(MMFAILED(hResult))
	{
		pszwfDst = GetWaveFormat(Buffer, pwfxDst);
		pszwfSrc = GetWaveFormat(BUffer2, pwfxSrc);
		pszErrorMessage = ErrorNumberToMessage(hResult);
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamOpen(0x%x, 0x%x, %s, %s, 0x%x,0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					phas,
					had,
					pszwfSrc,
					pszwfDst,
					pwfltr,
					dwCallback,
					dwInstance,
					fdwOpen))
			ENTER_DEBUGGER;
	}
	hResult = acmStreamOpen(phas, had, pwfxSrc, pwfxDst, pwfltr, dwCallback, dwInstance, fdwOpen);
	if(MMFAILED(hResult))
	{
		pszwfDst = GetWaveFormat(Buffer, pwfxDst);
		pszwfSrc = GetWaveFormat(BUffer2, pwfxSrc);
		pszErrorMessage = ErrorNumberToMessage(hResult);
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamOpen(0x%x, 0x%x, %s, %s, 0x%x,0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					phas,
					had,
					pszwfSrc,
					pszwfDst,
					pwfltr,
					dwCallback,
					dwInstance,
					fdwOpen))
			ENTER_DEBUGGER;
	}
	return hResult;
}

#pragma region wACMStreamSize
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMStreamSize</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="has"></param>
/// <param name="cbInput"></param>
/// <param name="pdwOutputBytes"></param>
/// <param name="fdwSize"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMStreamSize(HACMSTREAM has, uint32_t cbInput, puint32_t pdwOutputBytes, uint32_t fdwSize)
{
	PSTR		pszErrorMessage;
	MMRESULT	hResult;
	InternalFunctionSpew(
		"GameOS_DirectSound",
		"acmStreamSize(0x%x, 0x%x, 0x%x, 0x%x)",
		has,
		cbInput,
		pdwOutputBytes,
		fdwSize);
	hResult = acmStreamSize(has, cbInput, pdwOutputBytes, fdwSize);
	if(MMFAILED(hResult))
	{
		pszErrorMessage = ErrorNumberToMessage(hResult);
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmStreamSize(0x%x, 0x%x, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					has,
					cbInput,
					pdwOutputBytes,
					fdwSize))
			ENTER_DEBUGGER;
	}
	return hResult;
}

#pragma region wACMFormatSuggest
/*

*/
#pragma endregion local info
/// <summary>
/// <c>wACMFormatSuggest</c>
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="had"></param>
/// <param name="pwfxSrc"></param>
/// <param name="pwfxDst"></param>
/// <param name="cbwfxDst"></param>
/// <param name="fdwSuggest"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall
wACMFormatSuggest(HACMDRIVER had, const PWAVEFORMATEX pwfxSrc, const PWAVEFORMATEX pwfxDst,
				  uint32_t cbwfxDst, uint32_t fdwSuggest)
{
	PSTR		pszwfDst;
	PSTR		pszwfSrc;
	PSTR		pszErrorMessage;
	char		Buffer2[128];
	char		Buffer[128];
	MMRESULT	hResult;
	pszwfDst = GetWaveFormat(Buffer, pwfxDst);
	pszwfSrc = GetWaveFormat(Buffer2, pwfxSrc);
	InternalFunctionSpew(
		"GameOS_DirectSound",
		"acmFormatSuggest(0x%x, %s, %s, 0x%x, 0x%x)",
		had,
		pszwfSrc,
		pszwfDst,
		cbwfxDst,
		fdwSuggest);
	hResult = acmFormatSuggest(had, pwfxSrc, pwfxDst, cbwfxDst, fdwSuggest);
	if(MMFAILED(hResult))
	{
		pszwfDst = GetWaveFormat(Buffer, pwfxDst);
		pszwfSrc = GetWaveFormat(Buffer2, pwfxSrc);
		pszErrorMessage = ErrorNumberToMessage(hResult);
		if(InternalFunctionPause(
					"FAILED (0x%x - %s) - acmFormatSuggest(0x%x, %s, %s, 0x%x, 0x%x)",
					hResult,
					pszErrorMessage,
					had,
					pszwfSrc,
					pszwfDst,
					cbwfxDst,
					fdwSuggest))
			ENTER_DEBUGGER;
	}
	return hResult;
}

