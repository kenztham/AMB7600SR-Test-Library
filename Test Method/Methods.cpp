#include "../Test Method/Methods.h"
#include "../AMB7600SR/AMB7600SR.h"
#include "../AMB7300/AMB7300.h"

namespace Functions
{

	/*
	**	----------------------------------------------------------------------------------------------------
	**	MethodsBranch Contsructor and Destructor
	**	----------------------------------------------------------------------------------------------------
	*/
	MethodsBranch::MethodsBranch(TestFunction ^ TestFunc)
	{
		tl = TestFunc;
	}
	MethodsBranch::~MethodsBranch(void)
	{
	}

	void MethodsBranch::InitializeCMDictionary(int totalSite)
	{
		Dictionary_CM = gcnew ConcurrentDictionary<String^, int>();
		//DC_ControlMethods
		Dictionary_CM->TryAdd("DCCase_DriveVoltage", DCCase_DriveVoltage);
		Dictionary_CM->TryAdd("DCCase_DriveCurrent", DCCase_DriveCurrent);
		Dictionary_CM->TryAdd("DCCase_ClampVoltage", DCCase_ClampVoltage);
		Dictionary_CM->TryAdd("DCCase_ClampCurrent", DCCase_ClampCurrent);
		Dictionary_CM->TryAdd("DCCase_SetNPLC", DCCase_SetNPLC);
		Dictionary_CM->TryAdd("DCCase_SetPinOnOff", DCCase_SetPinOnOff);
		Dictionary_CM->TryAdd("DCCase_ConfigureTriggerEdgeLevel", DCCase_ConfigureTriggerEdgeLevel);
		Dictionary_CM->TryAdd("DCCase_MapTriggerIntToTriggerOut", DCCase_MapTriggerIntToTriggerOut);
		Dictionary_CM->TryAdd("DCCase_DriveSoftwareTrigger", DCCase_DriveSoftwareTrigger);
		Dictionary_CM->TryAdd("DCCase_AMConfigureInputTriggerSelect", DCCase_AMConfigureInputTriggerSelect);
		Dictionary_CM->TryAdd("DCCase_AMConfigureSMUOutputTriggerPulseWidth", DCCase_AMConfigureSMUOutputTriggerPulseWidth);
		Dictionary_CM->TryAdd("DCCase_AMConfigureSMUOutputTriggerDuringSource", DCCase_AMConfigureSMUOutputTriggerDuringSource);
		Dictionary_CM->TryAdd("DCCase_AMConfigureSMUOutputTriggerMode", DCCase_AMConfigureSMUOutputTriggerMode);
		Dictionary_CM->TryAdd("DCCase_AMConfigureOutputTriggerSelect", DCCase_AMConfigureOutputTriggerSelect);
		Dictionary_CM->TryAdd("DCCase_WaitSecond", DCCase_WaitSecond);

		//DM_ControlMethods
		Dictionary_CM->TryAdd("DMCase_DMInit", DMCase_DMInit);
		Dictionary_CM->TryAdd("DMCase_DMConfigurePinToVector", DMCase_DMConfigurePinToVector);
		Dictionary_CM->TryAdd("DMCase_DMConfigurePinToPMU", DMCase_DMConfigurePinToPMU);
		Dictionary_CM->TryAdd("DMCase_DMConfigurePinToDIO", DMCase_DMConfigurePinToDIO);
		Dictionary_CM->TryAdd("DMCase_DMLoadVectorFile", DMCase_DMLoadVectorFile);
		Dictionary_CM->TryAdd("DMCase_WriteVector", DMCase_WriteVector);
		Dictionary_CM->TryAdd("DMCase_DMDioModeDrivePin", DMCase_DMDioModeDrivePin);
		Dictionary_CM->TryAdd("DMCase_DMConfigureOutputTriggerSelect", DMCase_DMConfigureOutputTriggerSelect);
		Dictionary_CM->TryAdd("DMCase_DMConfigureReadPin_TriggerOutput", DMCase_DMConfigureReadPin_TriggerOutput);
		Dictionary_CM->TryAdd("DMCase_DMCastDPinLevel", DMCase_DMCastDPinLevel);
		Dictionary_CM->TryAdd("DMCase_DMCastTimingSetPeriod", DMCase_DMCastTimingSetPeriod);
		Dictionary_CM->TryAdd("DMCase_DMCastPEAttribute", DMCase_DMCastPEAttribute);

		//DIO_ControlMethods
		Dictionary_CM->TryAdd("IOMCase_DIODrivePin", IOMCase_DIODrivePin);
		Dictionary_CM->TryAdd("IOMCase_DIODrivePort", IOMCase_DIODrivePort);
		Dictionary_CM->TryAdd("IOMCase_DIOSetModuleVIO", IOMCase_DIOSetModuleVIO);
		Dictionary_CM->TryAdd("IOMCase_DIOSetPortDirection", IOMCase_DIOSetPortDirection);

		//CM_ControlMethods
		Dictionary_CM->TryAdd("CMCase_CMDrivePin", CMCase_CMDrivePin);
		Dictionary_CM->TryAdd("CMCase_CMDrivePort", CMCase_CMDrivePort);
		Dictionary_CM->TryAdd("CMCase_CMConfigurePXES2780_TriggerBus", CMCase_CMConfigurePXES2780_TriggerBus);
		Dictionary_CM->TryAdd("CMCase_CMSetPortDirection", CMCase_CMSetPortDirection);

		//RF_CW_ControlMethods
		Dictionary_CM->TryAdd("RFCase_SourcePower", RFCase_SourcePower);
		Dictionary_CM->TryAdd("RFCase_SourcePowerFast", RFCase_SourcePowerFast);
		Dictionary_CM->TryAdd("RFCase_SourcePowerLow", RFCase_SourcePowerLow);
		Dictionary_CM->TryAdd("RFCase_SourceTwoTone", RFCase_SourceTwoTone);
		Dictionary_CM->TryAdd("RFCase_IsolateChannel", RFCase_IsolateChannel);
		Dictionary_CM->TryAdd("RFCase_StartModulation", RFCase_StartModulation);
		Dictionary_CM->TryAdd("RFCase_StopModulation", RFCase_StopModulation);
		Dictionary_CM->TryAdd("RFCase_SetSourceTriggerRouting", RFCase_SetSourceTriggerRouting);
		Dictionary_CM->TryAdd("RFCase_SetSourceTriggerIn", RFCase_SetSourceTriggerIn);
		Dictionary_CM->TryAdd("RFCase_SetSourceTriggerOut", RFCase_SetSourceTriggerOut);
		Dictionary_CM->TryAdd("RFCase_SetMeasureTriggerRouting", RFCase_SetMeasureTriggerRouting);
		Dictionary_CM->TryAdd("RFCase_SetMeasureTriggerIn", RFCase_SetMeasureTriggerIn);
		Dictionary_CM->TryAdd("RFCase_RunSourceAlignment", RFCase_RunSourceAlignment);
		Dictionary_CM->TryAdd("RFCase_LoadModulation", RFCase_LoadModulation);
		Dictionary_CM->TryAdd("RFCase_WlanInit", RFCase_WlanInit);
		Dictionary_CM->TryAdd("RFCase_EvmMeasurementSetup", RFCase_EvmMeasurementSetup);
		Dictionary_CM->TryAdd("RFCase_SemMeasurementSetup", RFCase_SemMeasurementSetup);
		Dictionary_CM->TryAdd("RFCase_MeasureSetup", RFCase_MeasureSetup);
		Dictionary_CM->TryAdd("RFCase_MeasureSetupIQ", RFCase_MeasureSetupIQ);
		Dictionary_CM->TryAdd("RFCase_TriggerSigenStartModulation", RFCase_TriggerSigenStartModulation);
		Dictionary_CM->TryAdd("RFCase_WolferInit", RFCase_WolferInit);
		Dictionary_CM->TryAdd("RFCase_WolferSelectPath", RFCase_WolferSelectPath);
		Dictionary_CM->TryAdd("RFCase_WolferSourcePower", RFCase_WolferSourcePower);

		for (int siteIndex = 0; siteIndex < totalSite; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized Control Methods...");
		}
	}
	void MethodsBranch::InitializeTMDicionary(int totalSite)
	{
		Dictionary_TM = gcnew ConcurrentDictionary<String^, int>();
		//DC_TestMethods
		Dictionary_TM->TryAdd("DCCase_OS", DCCase_OS);
		Dictionary_TM->TryAdd("DCCase_MeasureCurrent", DCCase_MeasureCurrent);
		Dictionary_TM->TryAdd("DCCase_MeasureVoltage", DCCase_MeasureVoltage);
		Dictionary_TM->TryAdd("DCCase_AMMeasureBurstCurrent", DCCase_AMMeasureBurstCurrent);
		Dictionary_TM->TryAdd("DCCase_AMMeasureBurstVoltage", DCCase_AMMeasureBurstVoltage);
		Dictionary_TM->TryAdd("DCCase_DifferentialResult", DCCase_DifferentialResult);
		//DM_TestMethods
		Dictionary_TM->TryAdd("DMCase_MIPIReadVector", DMCase_MIPIReadVector);
		//RF_CW_TestMethods
		Dictionary_TM->TryAdd("RFCase_MeasureChannel", RFCase_MeasureChannel);
		Dictionary_TM->TryAdd("RFCase_MeasureChannelFast", RFCase_MeasureChannelFast);
		Dictionary_TM->TryAdd("RFCase_MeasureChannelIQ", RFCase_MeasureChannelIQ);
		Dictionary_TM->TryAdd("RFCase_MeasureIIP3", RFCase_MeasureIIP3);
		Dictionary_TM->TryAdd("RFCase_MeasureBurstPower", RFCase_MeasureBurstPower);
		Dictionary_TM->TryAdd("RFCase_MeasureSwitchingTime", RFCase_MeasureSwitchingTime);
		Dictionary_TM->TryAdd("RFCase_MeasureSParam", RFCase_MeasureSParam);
		Dictionary_TM->TryAdd("RFCase_MeasureSParamIQ", RFCase_MeasureSParamIQ);
		Dictionary_TM->TryAdd("RFCase_P1dB_DirectSearch", RFCase_P1dB_DirectSearch);
		Dictionary_TM->TryAdd("RFCase_P1dB_BinarySearch", RFCase_P1dB_BinarySearch);
		Dictionary_TM->TryAdd("RFCase_PowerServo", RFCase_PowerServo);
		Dictionary_TM->TryAdd("RFCase_PowerServo_BinarySearch", RFCase_PowerServo_BinarySearch);
		Dictionary_TM->TryAdd("RFCase_PowerServo_LinearSearch", RFCase_PowerServo_LinearSearch);
		Dictionary_TM->TryAdd("RFCase_ReadEvm", RFCase_ReadEvm);
		Dictionary_TM->TryAdd("RFCase_ReadEvmAsync", RFCase_ReadEvmAsync);
		Dictionary_TM->TryAdd("RFCase_ReadSem", RFCase_ReadSem);
		Dictionary_TM->TryAdd("RFCase_ReadSemAsync", RFCase_ReadSemAsync);
		Dictionary_TM->TryAdd("RFCase_WlanPowerServo", RFCase_WlanPowerServo);
		Dictionary_TM->TryAdd("RFCase_WlanResidualEVM", RFCase_WlanResidualEVM);
		Dictionary_TM->TryAdd("RFCase_WolferMeasureChannel", RFCase_WolferMeasureChannel);

		for (int siteIndex = 0; siteIndex < totalSite; siteIndex++) 
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized Test Methods...");
		}
	}

	void MethodsBranch::ControlMethod_Selection(Site ^ site, int testSite, int controlMethodSelection, ConditionCollection ^ testConditionCollection)
	{
		try {
			switch (controlMethodSelection)
			{
#pragma region DC Case
			case DCCase_DriveVoltage:
				amb7600srtl->CM_DriveVoltage(site, testSite, testConditionCollection);
				break;
			case DCCase_DriveCurrent:
				amb7600srtl->CM_DriveCurrent(site, testSite, testConditionCollection);
				break;
			case DCCase_ClampVoltage:
				amb7600srtl->CM_ClampVoltage(site, testSite, testConditionCollection);
				break;
			case DCCase_ClampCurrent:
				amb7600srtl->CM_ClampCurrent(site, testSite, testConditionCollection);
				break;
			case DCCase_SetNPLC:
				amb7600srtl->CM_SetNPLC(site, testSite, testConditionCollection);
				break;
			case DCCase_SetPinOnOff:
				amb7600srtl->CM_SetPinOnOff(site, testSite, testConditionCollection);
				break;
			case DCCase_ConfigureTriggerEdgeLevel:
				amb7600srtl->CM_ConfigureTriggerEdgeLevel(site, testSite, testConditionCollection);
				break;
			case DCCase_MapTriggerIntToTriggerOut:
				amb7600srtl->CM_MapTriggerIntToTriggerOut(site, testSite, testConditionCollection);
				break;
			case DCCase_DriveSoftwareTrigger:
				amb7600srtl->CM_DriveSoftwareTrigger(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureInputTriggerSelect:
				amb7600srtl->CM_AMConfigureInputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerPulseWidth:
				amb7600srtl->CM_AMConfigureSMUOutputTriggerPulseWidth(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerDuringSource:
				amb7600srtl->CM_AMConfigureSMUOutputTriggerDuringSource(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerMode:
				amb7600srtl->CM_AMConfigureSMUOutputTriggerMode(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureOutputTriggerSelect:
				amb7600srtl->CM_AMConfigureOutputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DCCase_WaitSecond:
				amb7600srtl->CM_WaitSecond(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region DM Case
			case DMCase_DMInit:
				amb7600srtl->CM_DMInit(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToVector:
				amb7600srtl->CM_DMConfigurePinToVector(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToPMU:
				amb7600srtl->CM_DMConfigurePinToPMU(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToDIO:
				amb7600srtl->CM_DMConfigurePinToDIO(site, testSite, testConditionCollection);
				break;
			case DMCase_DMLoadVectorFile:
				amb7600srtl->CM_DMLoadVectorFile(site, testSite, testConditionCollection);
				break;
			case DMCase_WriteVector:
				amb7600srtl->CM_WriteVector(site, testSite, testConditionCollection);
				break;
			case DMCase_DMDioModeDrivePin:
				amb7600srtl->CM_DMDioModeDrivePin(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigureInputTriggerSelect:
				amb7600srtl->CM_DMConfigureInputTriggerSelect(site, testSite, testConditionCollection);
			case DMCase_DMConfigureOutputTriggerSelect:
				amb7600srtl->CM_DMConfigureOutputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigureReadPin_TriggerOutput:
				amb7600srtl->CM_DMConfigureReadPin_TriggerOutput(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastDPinLevel:
				amb7600srtl->CM_DMCastDPinLevel(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastTimingSetPeriod:
				amb7600srtl->CM_DMCastTimingSetPeriod(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastPEAttribute:
				amb7600srtl->CM_DMCastPEAttribute(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region IOM Case
			case IOMCase_DIODrivePin:
				amb7600srtl->CM_DIODrivePin(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIODrivePort:
				amb7600srtl->CM_DIODrivePort(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIOSetModuleVIO:
				amb7600srtl->CM_DIOSetModuleVIO(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIOSetPortDirection:
				amb7600srtl->CM_DIOSetPortDirection(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region CM Case
			case CMCase_CMDrivePin:
				amb7600srtl->CM_CMDrivePin(site, testSite, testConditionCollection);
				break;
			case CMCase_CMDrivePort:
				amb7600srtl->CM_CMDrivePort(site, testSite, testConditionCollection);
				break;
			case CMCase_CMConfigurePXES2780_TriggerBus:
				amb7600srtl->CM_CMConfigurePXES2780_TriggerBus(site, testSite, testConditionCollection);
				break;
			case CMCase_CMSetPortDirection:
				amb7600srtl->CM_CMSetPortDirection(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region RF Case
			case RFCase_SourcePower:
				amb7600srtl->CM_RF_SourcePower(site, testSite, testConditionCollection);
				break;
			case RFCase_SourcePowerFast:
				amb7600srtl->CM_RF_SourcePowerFast(site, testSite, testConditionCollection);
				break;
			case RFCase_SourcePowerLow:
				amb7600srtl->CM_RF_SourcePowerLow(site, testSite, testConditionCollection);
				break;
			case RFCase_SourceTwoTone:
				amb7600srtl->CM_RF_SourceTwoTone(site, testSite, testConditionCollection);
				break;
			case RFCase_IsolateChannel:
				amb7600srtl->CM_RF_IsolateChannel(site, testSite, testConditionCollection);
				break;
			case RFCase_StartModulation:
				amb7600srtl->CM_RF_StartModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_StopModulation:
				amb7600srtl->CM_RF_StopModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerRouting:
				amb7600srtl->CM_RF_SetSourceTriggerRouting(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerIn:
				amb7600srtl->CM_RF_SetSourceTriggerIn(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerOut:
				amb7600srtl->CM_RF_SetSourceTriggerOut(site, testSite, testConditionCollection);
				break;
			case RFCase_SetMeasureTriggerRouting:
				amb7600srtl->CM_RF_SetMeasureTriggerRouting(site, testSite, testConditionCollection);
				break;
			case RFCase_SetMeasureTriggerIn:
				amb7600srtl->CM_RF_SetMeasureTriggerIn(site, testSite, testConditionCollection);
				break;
			case RFCase_RunSourceAlignment:
				amb7600srtl->CM_RF_RunSourceAlignment(site, testSite, testConditionCollection);
				break;
			case RFCase_LoadModulation:
				amb7600srtl->CM_RF_LoadModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_WlanInit:
				amb7600srtl->CM_RF_WlanInit(site, testSite, testConditionCollection);
				break;
			case RFCase_EvmMeasurementSetup:
				amb7600srtl->CM_RF_EvmMeasurementSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_SemMeasurementSetup:
				amb7600srtl->CM_RF_SemMeasurementSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_MeasureSetup:
				amb7600srtl->CM_RF_MeasureSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_MeasureSetupIQ:
				amb7600srtl->CM_RF_MeasureSetupIQ(site, testSite, testConditionCollection);
				break;
			case RFCase_TriggerSigenStartModulation:
				amb7600srtl->CM_RF_TriggerSigenStartModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferInit:
				amb7600srtl->CM_RF_WolferInit(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferSelectPath:
				amb7600srtl->CM_RF_WolferSelectPath(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferSourcePower:
				amb7600srtl->CM_RF_WolferSourcePower(site, testSite, testConditionCollection);
				break;
#pragma endregion
				/*
				#pragma region "VNA Case"
				case VNACase_VnaConfig:
				CM_VNA_VnaConfig(site, testSite, testConditionCollection);
				break;
				#pragma endregion "VNA Case"*/
			default:
				tl->glob->TcrLgr.ErrorCode = ER_CONST_InvalidControlMethod;
				throw gcnew Exception("This Control Method " + tl->glob->ErrorInfo[testSite].ControlMethodName + " is not supported.");
			}
		}
		catch (Exception^ ex)
		{
			throw;
		}
	}
	void MethodsBranch::TestMethod_Selection(Site ^ site, int testSite, int testMethodSelection, String ^ testParameterName, int  testParameterCount, int % methodTestParameterCount)
	{
		try {
			switch (testMethodSelection)
			{
#pragma region DC Case
			case DCCase_OS:
				amb7600srtl->TM_OS(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_MeasureCurrent:
				amb7600srtl->TM_MeasureCurrent(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_MeasureVoltage:
				amb7600srtl->TM_MeasureVoltage(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_AMMeasureBurstCurrent:
				amb7600srtl->TM_MeasureBurstCurrent(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_AMMeasureBurstVoltage:
				amb7600srtl->TM_MeasureBurstVoltage(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_DifferentialResult:
				amb7600srtl->TM_DifferentialResult(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

#pragma region DM Case
			case DMCase_MIPIReadVector:
				amb7600srtl->TM_MIPIReadVector(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

#pragma region RF Case
			case RFCase_MeasureChannel:
				amb7600srtl->TM_RF_MeasureChannel(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureChannelFast:
				amb7600srtl->TM_RF_MeasureChannelFast(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureChannelIQ:
				amb7600srtl->TM_RF_MeasureChannelIQ(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureIIP3:
				amb7600srtl->TM_RF_MeasureIIP3(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureBurstPower:
				amb7600srtl->TM_RF_MeasureBurstPower(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSwitchingTime:
				amb7600srtl->TM_RF_MeasureSwitchingTime(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSParam:
				amb7600srtl->TM_RF_MeasureSParam(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSParamIQ:
				amb7600srtl->TM_RF_MeasureSParamIQ(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_P1dB_DirectSearch:
				amb7600srtl->TM_RF_P1dB_DirectSearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_P1dB_BinarySearch:
				amb7600srtl->TM_RF_P1dB_BinarySearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo:
				amb7600srtl->TM_RF_PowerServo(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo_BinarySearch:
				amb7600srtl->TM_RF_PowerServo_BinarySearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo_LinearSearch:
				amb7600srtl->TM_RF_PowerServo_LinearSearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadEvm:
				amb7600srtl->TM_RF_ReadEvm(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadEvmAsync:
				amb7600srtl->TM_RF_ReadEvmAsync(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadSem:
				amb7600srtl->TM_RF_ReadSem(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadSemAsync:
				amb7600srtl->TM_RF_ReadSemAsync(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WlanPowerServo:
				amb7600srtl->TM_RF_WlanPowerServo(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WlanResidualEVM:
				amb7600srtl->TM_RF_WlanResidualEVM(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WolferMeasureChannel:
				amb7600srtl->TM_RF_WolferMeasureChannel(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

			default:
				tl->glob->TcrLgr.ErrorCode = ER_CONST_InvalidTestMethod;
				throw gcnew Exception("This Test Method " + tl->glob->ErrorInfo[testSite].TestMethodName + " is not supported.");
			}
		}
		catch (Exception^ ex)
		{
			throw;
		}
	}
	void MethodsBranch::ControlMethod_Selection(AMB7600SRTestLibrary ^ lib, Site ^ site, int testSite, int controlMethodSelection, ConditionCollection ^ testConditionCollection)
	{
		try {
			switch (controlMethodSelection)
			{
#pragma region DC Case
			case DCCase_DriveVoltage:
				lib->CM_DriveVoltage(site, testSite, testConditionCollection);
				break;
			case DCCase_DriveCurrent:
				lib->CM_DriveCurrent(site, testSite, testConditionCollection);
				break;
			case DCCase_ClampVoltage:
				lib->CM_ClampVoltage(site, testSite, testConditionCollection);
				break;
			case DCCase_ClampCurrent:
				lib->CM_ClampCurrent(site, testSite, testConditionCollection);
				break;
			case DCCase_SetNPLC:
				lib->CM_SetNPLC(site, testSite, testConditionCollection);
				break;
			case DCCase_SetPinOnOff:
				lib->CM_SetPinOnOff(site, testSite, testConditionCollection);
				break;
			case DCCase_ConfigureTriggerEdgeLevel:
				lib->CM_ConfigureTriggerEdgeLevel(site, testSite, testConditionCollection);
				break;
			case DCCase_MapTriggerIntToTriggerOut:
				lib->CM_MapTriggerIntToTriggerOut(site, testSite, testConditionCollection);
				break;
			case DCCase_DriveSoftwareTrigger:
				lib->CM_DriveSoftwareTrigger(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureInputTriggerSelect:
				lib->CM_AMConfigureInputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerPulseWidth:
				lib->CM_AMConfigureSMUOutputTriggerPulseWidth(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerDuringSource:
				lib->CM_AMConfigureSMUOutputTriggerDuringSource(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerMode:
				lib->CM_AMConfigureSMUOutputTriggerMode(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureOutputTriggerSelect:
				lib->CM_AMConfigureOutputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DCCase_WaitSecond:
				lib->CM_WaitSecond(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region DM Case
			case DMCase_DMInit:
				lib->CM_DMInit(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToVector:
				lib->CM_DMConfigurePinToVector(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToPMU:
				lib->CM_DMConfigurePinToPMU(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToDIO:
				lib->CM_DMConfigurePinToDIO(site, testSite, testConditionCollection);
				break;
			case DMCase_DMLoadVectorFile:
				lib->CM_DMLoadVectorFile(site, testSite, testConditionCollection);
				break;
			case DMCase_WriteVector:
				lib->CM_WriteVector(site, testSite, testConditionCollection);
				break;
			case DMCase_DMDioModeDrivePin:
				lib->CM_DMDioModeDrivePin(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigureInputTriggerSelect:
				lib->CM_DMConfigureInputTriggerSelect(site, testSite, testConditionCollection);
			case DMCase_DMConfigureOutputTriggerSelect:
				lib->CM_DMConfigureOutputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigureReadPin_TriggerOutput:
				lib->CM_DMConfigureReadPin_TriggerOutput(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastDPinLevel:
				lib->CM_DMCastDPinLevel(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastTimingSetPeriod:
				lib->CM_DMCastTimingSetPeriod(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastPEAttribute:
				lib->CM_DMCastPEAttribute(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region IOM Case
			case IOMCase_DIODrivePin:
				lib->CM_DIODrivePin(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIODrivePort:
				lib->CM_DIODrivePort(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIOSetModuleVIO:
				lib->CM_DIOSetModuleVIO(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIOSetPortDirection:
				lib->CM_DIOSetPortDirection(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region CM Case
			case CMCase_CMDrivePin:
				lib->CM_CMDrivePin(site, testSite, testConditionCollection);
				break;
			case CMCase_CMDrivePort:
				lib->CM_CMDrivePort(site, testSite, testConditionCollection);
				break;
			case CMCase_CMConfigurePXES2780_TriggerBus:
				lib->CM_CMConfigurePXES2780_TriggerBus(site, testSite, testConditionCollection);
				break;
			case CMCase_CMSetPortDirection:
				lib->CM_CMSetPortDirection(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region RF Case
			case RFCase_SourcePower:
				lib->CM_RF_SourcePower(site, testSite, testConditionCollection);
				break;
			case RFCase_SourcePowerFast:
				lib->CM_RF_SourcePowerFast(site, testSite, testConditionCollection);
				break;
			case RFCase_SourcePowerLow:
				lib->CM_RF_SourcePowerLow(site, testSite, testConditionCollection);
				break;
			case RFCase_SourceTwoTone:
				lib->CM_RF_SourceTwoTone(site, testSite, testConditionCollection);
				break;
			case RFCase_IsolateChannel:
				lib->CM_RF_IsolateChannel(site, testSite, testConditionCollection);
				break;
			case RFCase_StartModulation:
				lib->CM_RF_StartModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_StopModulation:
				lib->CM_RF_StopModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerRouting:
				lib->CM_RF_SetSourceTriggerRouting(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerIn:
				lib->CM_RF_SetSourceTriggerIn(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerOut:
				lib->CM_RF_SetSourceTriggerOut(site, testSite, testConditionCollection);
				break;
			case RFCase_SetMeasureTriggerRouting:
				lib->CM_RF_SetMeasureTriggerRouting(site, testSite, testConditionCollection);
				break;
			case RFCase_SetMeasureTriggerIn:
				lib->CM_RF_SetMeasureTriggerIn(site, testSite, testConditionCollection);
				break;
			case RFCase_RunSourceAlignment:
				lib->CM_RF_RunSourceAlignment(site, testSite, testConditionCollection);
				break;
			case RFCase_LoadModulation:
				lib->CM_RF_LoadModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_WlanInit:
				lib->CM_RF_WlanInit(site, testSite, testConditionCollection);
				break;
			case RFCase_EvmMeasurementSetup:
				lib->CM_RF_EvmMeasurementSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_SemMeasurementSetup:
				lib->CM_RF_SemMeasurementSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_MeasureSetup:
				lib->CM_RF_MeasureSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_MeasureSetupIQ:
				lib->CM_RF_MeasureSetupIQ(site, testSite, testConditionCollection);
				break;
			case RFCase_TriggerSigenStartModulation:
				lib->CM_RF_TriggerSigenStartModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferInit:
				lib->CM_RF_WolferInit(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferSelectPath:
				lib->CM_RF_WolferSelectPath(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferSourcePower:
				lib->CM_RF_WolferSourcePower(site, testSite, testConditionCollection);
				break;
#pragma endregion
				/*
				#pragma region "VNA Case"
				case VNACase_VnaConfig:
				CM_VNA_VnaConfig(site, testSite, testConditionCollection);
				break;
				#pragma endregion "VNA Case"*/
			default:
				tl->glob->TcrLgr.ErrorCode = ER_CONST_InvalidControlMethod;
				throw gcnew Exception("This Control Method " + tl->glob->ErrorInfo[testSite].ControlMethodName + " is not supported.");
			}
		}
		catch (Exception^ ex)
		{
			throw;
		}
	}
	void MethodsBranch::TestMethod_Selection(AMB7600SRTestLibrary ^ lib, Site ^ site, int testSite, int testMethodSelection, String ^ testParameterName, int  testParameterCount, int % methodTestParameterCount)
	{
		try {
			switch (testMethodSelection)
			{
#pragma region DC Case
			case DCCase_OS:
				lib->TM_OS(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_MeasureCurrent:
				lib->TM_MeasureCurrent(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_MeasureVoltage:
				lib->TM_MeasureVoltage(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_AMMeasureBurstCurrent:
				lib->TM_MeasureBurstCurrent(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_AMMeasureBurstVoltage:
				lib->TM_MeasureBurstVoltage(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_DifferentialResult:
				lib->TM_DifferentialResult(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

#pragma region DM Case
			case DMCase_MIPIReadVector:
				lib->TM_MIPIReadVector(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

#pragma region RF Case
			case RFCase_MeasureChannel:
				lib->TM_RF_MeasureChannel(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureChannelFast:
				lib->TM_RF_MeasureChannelFast(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureChannelIQ:
				lib->TM_RF_MeasureChannelIQ(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureIIP3:
				lib->TM_RF_MeasureIIP3(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureBurstPower:
				lib->TM_RF_MeasureBurstPower(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSwitchingTime:
				lib->TM_RF_MeasureSwitchingTime(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSParam:
				lib->TM_RF_MeasureSParam(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSParamIQ:
				lib->TM_RF_MeasureSParamIQ(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_P1dB_DirectSearch:
				lib->TM_RF_P1dB_DirectSearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_P1dB_BinarySearch:
				lib->TM_RF_P1dB_BinarySearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo:
				lib->TM_RF_PowerServo(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo_BinarySearch:
				lib->TM_RF_PowerServo_BinarySearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo_LinearSearch:
				lib->TM_RF_PowerServo_LinearSearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadEvm:
				lib->TM_RF_ReadEvm(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadEvmAsync:
				lib->TM_RF_ReadEvmAsync(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadSem:
				lib->TM_RF_ReadSem(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadSemAsync:
				lib->TM_RF_ReadSemAsync(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WlanPowerServo:
				lib->TM_RF_WlanPowerServo(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WlanResidualEVM:
				lib->TM_RF_WlanResidualEVM(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WolferMeasureChannel:
				lib->TM_RF_WolferMeasureChannel(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

			default:
				tl->glob->TcrLgr.ErrorCode = ER_CONST_InvalidTestMethod;
				throw gcnew Exception("This Test Method " + tl->glob->ErrorInfo[testSite].TestMethodName + " is not supported.");
			}
		}
		catch (Exception^ ex)
		{
			throw;
		}
	}
}