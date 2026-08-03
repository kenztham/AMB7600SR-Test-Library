#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Test Function/TestFunction.h"
#include "Test Function/Globals.h"
#include "AMB7600SR/AMB7600SR.h"

//<Test Resources>
#include "Test Function/Aemulus.Hardware.SMU.h"
#include "Test Function/Aemulus.Hardware.DM.h"
#include "Test Function/Aemulus.Hardware.CM.h"
#include "Test Function/Aemulus.Hardware.AMSRF.h"
#include "Test Method/TestTimeProfiling.h"
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
		
		AMB7600SRTestLibrary ^ amb7600srtl;

		// Private Methods
		void AMB7600SR_TestLibrary_ControlMethod(Object ^ object);
		void AMB7600SR_TestLibrary_ControlMethod_TestMethod(Object ^ object);

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
		int seq_TestItem(Site ^ site);
		int seq_TestMethod(Site^ site);

		#pragma region ".xml -> Control Step for AM400e & DM400e"	
		int CM_DCCase_DriveVoltage	(Site^ site);
		int CM_DCCase_DriveCurrent	(Site^ site);
		int CM_DCCase_ClampVoltage	(Site^ site);
		int CM_DCCase_ClampCurrent	(Site^ site);
		int CM_DCCase_SetNPLC		(Site^ site);
		int CM_DCCase_SetPinOnOff	(Site^ site);
		int CM_DCCase_WaitSecond	(Site^ site);
		int CM_DCCase_ConfigureTriggerEdgeLevel		(Site^ site);
		int CM_DCCase_ConfigureTriggerEdgeLevelExtra(Site^ site);
		int CM_DCCase_ConfigureInputTriggerSelect	(Site^ site);
		int CM_DCCase_MapTriggerIntToTriggerOut		(Site^ site);
		int CM_DCCase_DriveSoftwareTrigger		(Site^ site);
		#pragma endregion
		
		#pragma region ".xml -> Control Step for AM400e"
		int CM_DCCase_AMConfigureSMUOutputTriggerPulseWidth(Site^ site);
		int CM_DCCase_AMConfigureSMUOutputTriggerDuringSource(Site^ site);
		int CM_DCCase_AMConfigureSMUOutputTriggerMode(Site^ site);
		int CM_DCCase_AMConfigureOutputTriggerSelect(Site^ site);
		#pragma endregion

#pragma region ".xml -> Control Step for CM400e"
		int CM_CMCase_CMDrivePin(Site^ site);
		int CM_CMCase_CMDrivePort(Site^ site);
		int CM_CMCase_CMConfigurePXES2780_TriggerBus(Site^ site);
		int CM_CMCase_CMSetPortDirection(Site^ site);
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
		#pragma endregion
		
		int TM_OS(Site^ site);
		int TM_MeasureCurrent(Site^ site);
		int TM_MeasureVoltage(Site^ site);
		int TM_MeasureBurstCurrent(Site^ site);
		int TM_MeasureBurstVoltage(Site^ site);


	};
}
