#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Test Function/TestFunction.h"
#include "Test Function/Globals.h"
#include "AMB7600SR/AMB7600SR.h"
#include "AMB7300/AMB7300.h"
#include "Module400Series/Module400Series.h"

//<Test Resources>
#include "Test Function/Aemulus.Hardware.SMU.h"
#include "Test Function/Aemulus.Hardware.DM.h"
#include "Test Function/Aemulus.Hardware.CM.h"
#include "Test Function/Aemulus.Hardware.AMSRF.h"
#include "Test Method/TestTimeProfiling.h"
#include "Test Method/Methods.h"
#include "Test Function/AppLevelException.h"

//<User defines>
#include "UserDefines.h"

using namespace Functions;
using namespace TestMethods;

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Collections::Concurrent;
using namespace System::Runtime::InteropServices;

using namespace Aemulus::Configuration;
using namespace Aemulus::Tech;
using namespace Aemulus::TestLib;
using namespace Aemulus::Hardware;
using namespace Aemulus::Tech::Flow;
using namespace Aemulus::TestLib::Utility;
using namespace Aemulus::TestLib::RF::Utility;

namespace AMB7600SR_TestLibrary_REV2
{
	public ref class TestProgram : ITestProgram
	{
	private:
		TestFunction ^ tl;
		
		MethodsBranch ^ methods;
		AMB7600SRTestLibrary ^ amb7600srtl;
		AMB7300TestLibrary ^ amb7300tl;
		Module400Series ^ module400series;

		Aemulus::TestLib::Utility::Utilities ^ Util;
		AppDomain ^ currentDomain;

		// Private Methods
		void AMB7600SR_TestLibrary_ControlMethod(Object ^ object);
		void AMB7600SR_TestLibrary_ControlMethod_TestMethod(Object ^ object);

		void SaveSnpToBinAfterCommitResults(Site^ site);
#pragma region "Global Variable"

		/*
		**	----------------------------------------------------------------------------------------------------
		**	Error Message in Threading
		**	----------------------------------------------------------------------------------------------------
		*/
		static array<String^>^ G_RunTimeErrorMessage;
		static array<int>^ G_RunTimeErrorCode;
		static array<bool>^ G_RunTimeError;
		static bool G_JumpOnFail;
		int G_TotalSites;

		//Results array for True Parellel test
		array<int> ^ resultIndex;
		array<Object ^, 2> ^ TPtestResult;

		int lineNUM;
		String ^ timerFilename;

		DialogResult PlatformSelection;
#pragma endregion

	public:

		// TestProgram Constructor
		TestProgram(void);
		array <TestTimeProfiling^>^ ttp;
		
		// Public Methods
		int Load(Site ^ site);
		int Unload(Site ^ site);
		int PreProcessing(Site ^ site);
		int PostProcessing(Site ^ site);
		int seq_ControlItem(Site ^ site);
		int seq_TestMethod(Site^ site);

		#pragma region ".xml -> Control Step for AM400e & DM400e"	
		int CM_DCCase_DriveVoltage(Site^ site);
		int CM_DCCase_DriveCurrent(Site^ site);
		int CM_DCCase_ClampVoltage(Site^ site);
		int CM_DCCase_ClampCurrent(Site^ site);
		int CM_DCCase_SetNPLC(Site^ site);
		int CM_DCCase_SetPinOnOff(Site^ site);
		int CM_DCCase_WaitSecond(Site^ site);
		int CM_DCCase_ConfigureTriggerEdgeLevel(Site^ site);
		int CM_DCCase_ConfigureTriggerEdgeLevelExtra(Site^ site);
		int CM_DCCase_MapTriggerIntToTriggerOut(Site^ site);
		int CM_DCCase_DriveSoftwareTrigger(Site^ site);
		#pragma endregion
		
		#pragma region ".xml -> Control Step for AM400e"
		int CM_DCCase_AMConfigureInputTriggerSelect(Site^ site);
		int CM_DCCase_AMConfigureSMUOutputTriggerPulseWidth(Site^ site);
		int CM_DCCase_AMConfigureSMUOutputTriggerDuringSource(Site^ site);
		int CM_DCCase_AMConfigureSMUOutputTriggerMode(Site^ site);
		int CM_DCCase_AMConfigureOutputTriggerSelect(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Step for DM400e"
		int CM_DMCase_DMConfigurePinToVector(Site^ site);
		int CM_DMCase_DMConfigurePinToPMU(Site^ site);
		int CM_DMCase_DMConfigurePinToDIO(Site^ site);
		int CM_DMCase_DMLoadVectorFile(Site^ site);
		int CM_DMCase_WriteVector(Site^ site);
		int CM_DMCase_DMDioModeDrivePin(Site^ site);
		int CM_DMCase_DMDriveSoftwareTrigger(Site^ site);
		int CM_DMCase_DMMapTriggerIntToTriggerOut(Site^ site);
		int CM_DMCase_DMConfigureTriggerEdgeLevel(Site^ site);
		int CM_DMCase_DMConfigureInputTriggerSelect(Site^ site);
		int CM_DMCase_DMConfigureOutputTriggerSelect(Site^ site);
		int CM_DMCase_DMConfigureReadPin_TriggerOutput(Site^ site);
		int CM_DMCase_DMCastDPinLevel(Site^ site);
		int CM_DMCase_DMCastTimingSetPeriod(Site^ site);
		int CM_DMCase_DMCastPEAttribute(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Step for IOM400e"
		int CM_IOMCase_DIODrivePin(Site^ site);
		int CM_IOMCase_DIODrivePort(Site^ site);
		int CM_IOMCase_DIOSetModuleVIO(Site^ site);
		int CM_IOMCase_DIOSetPortDirection(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Step for CM400e"
		int CM_CMCase_CMDrivePin(Site^ site);
		int CM_CMCase_CMDrivePort(Site^ site);
		int CM_CMCase_CMConfigurePXES2780_TriggerBus(Site^ site);
		int CM_CMCase_CMSetPortDirection(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Step for RF"
		int CM_RFCase_SourcePower(Site^ site);
		int CM_RFCase_SourcePowerFast(Site^ site);
		int CM_RFCase_SourcePowerLow(Site^ site);
		int CM_RFCase_SourceTwoTone(Site^ site);
		int CM_RFCase_IsolateChannel(Site^ site);
		int CM_RFCase_StartModulation(Site^ site);
		int CM_RFCase_StopModulation(Site^ site);
		int CM_RFCase_SetSourceTriggerRouting(Site^ site);
		int CM_RFCase_SetSourceTriggerIn(Site^ site);
		int CM_RFCase_SetSourceTriggerOut(Site^ site);
		int CM_RFCase_SetMeasureTriggerRouting(Site^ site);
		int CM_RFCase_SetMeasureTriggerIn(Site^ site);
		int CM_RFCase_RunSourceAlignment(Site^ site);
		int CM_RFCase_LoadModulation(Site^ site);
		int CM_RFCase_WlanInit(Site^ site);
		int CM_RFCase_EvmMeasurementSetup(Site^ site);
		int CM_RFCase_SemMeasurementSetup(Site^ site);
		int CM_RFCase_MeasureSetup(Site^ site);
		int CM_RFCase_MeasureSetupIQ(Site^ site);
		int CM_RFCase_TriggerSigenStartModulation(Site^ site);
		int CM_RFCase_WolferInit(Site^ site);
		int CM_RFCase_WolferSelectPath(Site^ site);
		int CM_RFCase_WolferSourcePower(Site^ site);
		#pragma endregion
		
		#pragma region ".xml -> Control Item for AM400e & DM400e"	
		int CI_DCCase_DriveVoltage(Site^ site);
		int CI_DCCase_DriveCurrent(Site^ site);
		int CI_DCCase_ClampVoltage(Site^ site);
		int CI_DCCase_ClampCurrent(Site^ site);
		int CI_DCCase_SetNPLC(Site^ site);
		int CI_DCCase_SetPinOnOff(Site^ site);
		int CI_DCCase_WaitSecond(Site^ site);
		int CI_DCCase_ConfigureTriggerEdgeLevel(Site^ site);
		int CI_DCCase_ConfigureTriggerEdgeLevelExtra(Site^ site);
		int CI_DCCase_MapTriggerIntToTriggerOut(Site^ site);
		int CI_DCCase_DriveSoftwareTrigger(Site^ site);
		#pragma endregion
		
		#pragma region ".xml -> Control Item for AM400e"
		int CI_DCCase_AMConfigureInputTriggerSelect(Site^ site);
		int CI_DCCase_AMConfigureSMUOutputTriggerPulseWidth(Site^ site);
		int CI_DCCase_AMConfigureSMUOutputTriggerDuringSource(Site^ site);
		int CI_DCCase_AMConfigureSMUOutputTriggerMode(Site^ site);
		int CI_DCCase_AMConfigureOutputTriggerSelect(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Item for DM400e"
		int CI_DMCase_DMConfigurePinToVector(Site^ site);
		int CI_DMCase_DMConfigurePinToPMU(Site^ site);
		int CI_DMCase_DMConfigurePinToDIO(Site^ site);
		int CI_DMCase_DMLoadVectorFile(Site^ site);
		int CI_DMCase_WriteVector(Site^ site);
		int CI_DMCase_DMDioModeDrivePin(Site^ site);
		int CI_DMCase_DMDriveSoftwareTrigger(Site^ site);
		int CI_DMCase_DMMapTriggerIntToTriggerOut(Site^ site);
		int CI_DMCase_DMConfigureTriggerEdgeLevel(Site^ site);
		int CI_DMCase_DMConfigureInputTriggerSelect(Site^ site);
		int CI_DMCase_DMConfigureOutputTriggerSelect(Site^ site);
		int CI_DMCase_DMConfigureReadPin_TriggerOutput(Site^ site);
		int CI_DMCase_DMCastDPinLevel(Site^ site);
		int CI_DMCase_DMCastTimingSetPeriod(Site^ site);
		int CI_DMCase_DMCastPEAttribute(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Item for IOM400e"
		int CI_IOMCase_DIODrivePin(Site^ site);
		int CI_IOMCase_DIODrivePort(Site^ site);
		int CI_IOMCase_DIOSetModuleVIO(Site^ site);
		int CI_IOMCase_DIOSetPortDirection(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Item for CM400e"
		int CI_CMCase_CMDrivePin(Site^ site);
		int CI_CMCase_CMDrivePort(Site^ site);
		int CI_CMCase_CMConfigurePXES2780_TriggerBus(Site^ site);
		int CI_CMCase_CMSetPortDirection(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Control Item for RF"
		int CI_RFCase_SourcePower(Site^ site);
		int CI_RFCase_SourcePowerFast(Site^ site);
		int CI_RFCase_SourcePowerLow(Site^ site);
		int CI_RFCase_SourceTwoTone(Site^ site);
		int CI_RFCase_IsolateChannel(Site^ site);
		int CI_RFCase_StartModulation(Site^ site);
		int CI_RFCase_StopModulation(Site^ site);
		int CI_RFCase_SetSourceTriggerRouting(Site^ site);
		int CI_RFCase_SetSourceTriggerIn(Site^ site);
		int CI_RFCase_SetSourceTriggerOut(Site^ site);
		int CI_RFCase_SetMeasureTriggerRouting(Site^ site);
		int CI_RFCase_SetMeasureTriggerIn(Site^ site);
		int CI_RFCase_RunSourceAlignment(Site^ site);
		int CI_RFCase_LoadModulation(Site^ site);
		int CI_RFCase_WlanInit(Site^ site);
		int CI_RFCase_EvmMeasurementSetup(Site^ site);
		int CI_RFCase_SemMeasurementSetup(Site^ site);
		int CI_RFCase_MeasureSetup(Site^ site);
		int CI_RFCase_MeasureSetupIQ(Site^ site);
		int CI_RFCase_TriggerSigenStartModulation(Site^ site);
		int CI_RFCase_WolferInit(Site^ site);
		int CI_RFCase_WolferSelectPath(Site^ site);
		int CI_RFCase_WolferSourcePower(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Test Item for AM400e & DM400e"
		int TM_DCCase_OS(Site^ site);
		int TM_DCCase_MeasureCurrent(Site^ site);
		int TM_DCCase_MeasureVoltage(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Test Item for AM400e"
		int TM_DCCase_AMMeasureBurstCurrent(Site^ site);
		int TM_DCCase_AMMeasureBurstVoltage(Site^ site);
		int TM_DCCase_DifferentialResult(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Test Item for DM400e"
		int TM_DMCase_MIPIReadVector(Site^ site);
		#pragma endregion

		#pragma region ".xml -> Test Item for RF"
		int TM_RFCase_MeasureChannel(Site^ site);
		int TM_RFCase_MeasureChannelFast(Site^ site);
		int TM_RFCase_MeasureChannelIQ(Site^ site);
		int TM_RFCase_MeasureIIP3(Site^ site);
		int TM_RFCase_MeasureBurstPower(Site^ site);
		int TM_RFCase_MeasureSwitchingTime(Site^ site);
		int TM_RFCase_MeasureSParam(Site^ site);
		int TM_RFCase_MeasureSParamIQ(Site^ site);
		int TM_RFCase_P1dB_DirectSearch(Site^ site);
		int TM_RFCase_P1dB_BinarySearch(Site^ site);
		int TM_RFCase_PowerServo(Site^ site);
		int TM_RFCase_PowerServo_BinarySearch(Site^ site);
		int TM_RFCase_PowerServo_LinearSearch(Site^ site);
		int TM_RFCase_ReadEvm(Site^ site);
		int TM_RFCase_ReadEvmAsync(Site^ site);
		int TM_RFCase_ReadSem(Site^ site);
		int TM_RFCase_ReadSemAsyn(Site^ site);
		int TM_RFCase_WlanPowerServo(Site^ site);
		int TM_RFCase_WlanResidualEVM(Site^ site);
		int TM_RFCase_WoferMeasureChannel(Site^ site);
		#pragma endregion

#pragma region "AMB7300"
		//void SaveSnpToBinAfterCommitResults(Site^ site);

#pragma region "AMB7300Utility.cpp -> Cast Conditions"

		/*
		**	----------------------------------------------------------------------------------------------------
		**	TF Test Library XML & Flow Item's Conditions (Test Item, Test Parameter, Control Step)
		**	----------------------------------------------------------------------------------------------------
		*/


		/*
		**	----------------------------------------------------------------------------------------------------
		**	Control Step: VnaConfig
		**	----------------------------------------------------------------------------------------------------
		*/
		int TestLib_ControlStep_VnaConfig(Site ^ site);
		/*
		**	----------------------------------------------------------------------------------------------------
		**	Control Step: VnaFetch
		**	----------------------------------------------------------------------------------------------------
		*/
		int TestLib_ControlStep_VnaFetch(Site ^ site);
		/*
		**	----------------------------------------------------------------------------------------------------
		**	Test Parameter: VnaDataAnalysis
		**	----------------------------------------------------------------------------------------------------
		*/
		int TestLib_TestParameter_VnaDataAnalysis(Site ^ site);
		/*
		**	----------------------------------------------------------------------------------------------------
		**	Threading Helper Function
		**	----------------------------------------------------------------------------------------------------
		*/
		//void DoThread(ParameterizedThreadStart^ function, Site^ site);
		//void IsRunTest(Site^ site, array<bool>^ run_test);
		//void ExecuteControlStep_DC(Object^ object);
		//void ExecuteTestParameter_DC(Object^ object);

#pragma endregion

#pragma endregion "AMB7300"
	};
}
