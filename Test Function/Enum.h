/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			Enum.h
Purpose:		Defines global enumerations.
UUTOffset:		Supported.
Version:		v1.2.0.0 
----------------------------------------------------------------------*/

#ifndef ENUM_H
#define ENUM_H

#pragma once

using namespace System;

namespace Functions
{
	public enum class SEGMENT_TRIGGER
	{
		SEGMENT_A = 1,
		SEGMENT_B = 1,
		SEGMENT_C = 1,
		SEGMENT_AB = 2,
		SEGMENT_BA = 3,
		SEGMENT_BC = 4,
		SEGMENT_CB = 5,
		SEGMENT_ABC = 6,
		SEGMENT_CBA = 7,
	};

	public enum class PMU_MEAS_TYPE
	{
		PMU_STATIC_MEAS = 0,
		PMU_DYNAMIC_MEAS = 1,
	};

	public enum class PMU_MEAS_MODE
	{
		DM_MEASURECURRENT = 0,
		DM_MEASUREVOLTAGE = 1,
	};

	public enum class MEAS_MODULE_TYPE
	{
		AM = 0,
		DM = 1,
		CM = 2,
	};

	public enum class TMU_SLOPE_EDGE
	{
		POSITIVE_EDGE = 0,
		NEGATIVE_EDGE = 1,
	};

	//Specifies the sampling edge of PClk. The CIS Receiver core samples the incoming signals at falling edge or rising edge of PClk.
	public enum class PCLKSamEdge
	{
		PCLK_FALLING_EDGE = 0,
		PCLK_RISING_EDGE = 1,
	};

	//Specifies the active state of VSync signal. VSync signal is valid only when it is in active low or active high state.
	public enum class VSYNC
	{
		VSYNC_ACTIVE_LOW = 0,
		VSYNC_ACTIVE_HIGH = 1,
	};

	//Specifies the active state of HSync signal.HSync signal is valid only when it is in active low or active high state.
	public enum class HSYNC
	{
		HSYNC_ACTIVE_LOW = 0,
		HSYNC_ACTIVE_HIGH = 1,
	};

	public enum class VECTOR_LINE
	{
		SINGLE_VECTORLINE_PER_BIT = 1,
		TWO_VECTORLINE_PER_BIT = 2,
		FOUR_VECTORLINE_PER_BIT = 4,
	};

	public enum class REG_ADDR_BYTE
	{
		SINGLE_BYTE = 1,
		TWO_BYTE = 2,
		THREE_BYTE = 3,
		FOUR_BYTE = 4,
	};

	public enum class REG_DATA_BYTE
	{
		SINGLE_BYTE = 1,
		TWO_BYTE = 2,
		THREE_BYTE = 3,
		FOUR_BYTE = 4,
	};

	public enum class wlanEvmSetting_APP
	{
		AcqTime = 0,
		viewConstellation = 1,
		mcsIndex = 2,
		PSDULength = 3,
		autoConfigSetup = 4,

	};
	public enum class wlanSemSetting_APP
	{
		AcqTime = 0,
		viewSpectrum = 1,

	};
}

#endif



/*----------------------------------------------------------------------
* Revision Log
* $Log: Enum.h.rca$


* v1.0.0.0 (20 March 2020), LKL
* Initial release version.

* v1.1.0.0 (25 Nov 2020), LKL
* Included VECTOR_LINE, REG_ADDR_BYTE, REG_DATA_BYTRE enum class.

* v1.2.0.0 (28 Nov 2020), LKL
* Included CIS Image_CIS_Receiver_Configure related enum class.
----------------------------------------------------------------------*/