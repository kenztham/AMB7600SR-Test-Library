#include "../AMB7600SR/AMB7600SR.h"

namespace Functions
{

	void AMB7600SRTestLibrary::InitializeCMDictionary(int totalSite)
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
	void AMB7600SRTestLibrary::InitializeTMDicionary(int totalSite)
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

	void AMB7600SRTestLibrary::ControlMethod_Selection(Site ^ site, int testSite, int controlMethodSelection, ConditionCollection ^ testConditionCollection)
	{
		try {
			switch (controlMethodSelection)
			{
#pragma region DC Case
			case DCCase_DriveVoltage:
				CM_DriveVoltage(site, testSite, testConditionCollection);
				break;
			case DCCase_DriveCurrent:
				CM_DriveCurrent(site, testSite, testConditionCollection);
				break;
			case DCCase_ClampVoltage:
				CM_ClampVoltage(site, testSite, testConditionCollection);
				break;
			case DCCase_ClampCurrent:
				CM_ClampCurrent(site, testSite, testConditionCollection);
				break;
			case DCCase_SetNPLC:
				CM_SetNPLC(site, testSite, testConditionCollection);
				break;
			case DCCase_SetPinOnOff:
				CM_SetPinOnOff(site, testSite, testConditionCollection);
				break;
			case DCCase_ConfigureTriggerEdgeLevel:
				CM_ConfigureTriggerEdgeLevel(site, testSite, testConditionCollection);
				break;
			case DCCase_MapTriggerIntToTriggerOut:
				CM_MapTriggerIntToTriggerOut(site, testSite, testConditionCollection);
				break;
			case DCCase_DriveSoftwareTrigger:
				CM_DriveSoftwareTrigger(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureInputTriggerSelect:
				CM_AMConfigureInputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerPulseWidth:
				CM_AMConfigureSMUOutputTriggerPulseWidth(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerDuringSource:
				CM_AMConfigureSMUOutputTriggerDuringSource(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureSMUOutputTriggerMode:
				CM_AMConfigureSMUOutputTriggerMode(site, testSite, testConditionCollection);
				break;
			case DCCase_AMConfigureOutputTriggerSelect:
				CM_AMConfigureOutputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DCCase_WaitSecond:
				CM_WaitSecond(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region DM Case
			case DMCase_DMInit:
				CM_DMInit(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToVector:
				CM_DMConfigurePinToVector(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToPMU:
				CM_DMConfigurePinToPMU(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigurePinToDIO:
				CM_DMConfigurePinToDIO(site, testSite, testConditionCollection);
				break;
			case DMCase_DMLoadVectorFile:
				CM_DMLoadVectorFile(site, testSite, testConditionCollection);
				break;
			case DMCase_WriteVector:
				CM_WriteVector(site, testSite, testConditionCollection);
				break;
			case DMCase_DMDioModeDrivePin:
				CM_DMDioModeDrivePin(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigureInputTriggerSelect:
				CM_DMConfigureInputTriggerSelect(site, testSite, testConditionCollection);
			case DMCase_DMConfigureOutputTriggerSelect:
				CM_DMConfigureOutputTriggerSelect(site, testSite, testConditionCollection);
				break;
			case DMCase_DMConfigureReadPin_TriggerOutput:
				CM_DMConfigureReadPin_TriggerOutput(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastDPinLevel:
				CM_DMCastDPinLevel(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastTimingSetPeriod:
				CM_DMCastTimingSetPeriod(site, testSite, testConditionCollection);
				break;
			case DMCase_DMCastPEAttribute:
				CM_DMCastPEAttribute(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region IOM Case
			case IOMCase_DIODrivePin:
				CM_DIODrivePin(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIODrivePort:
				CM_DIODrivePort(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIOSetModuleVIO:
				CM_DIOSetModuleVIO(site, testSite, testConditionCollection);
				break;
			case IOMCase_DIOSetPortDirection:
				CM_DIOSetPortDirection(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region CM Case
			case CMCase_CMDrivePin:
				CM_CMDrivePin(site, testSite, testConditionCollection);
				break;
			case CMCase_CMDrivePort:
				CM_CMDrivePort(site, testSite, testConditionCollection);
				break;
			case CMCase_CMConfigurePXES2780_TriggerBus:
				CM_CMConfigurePXES2780_TriggerBus(site, testSite, testConditionCollection);
				break;
			case CMCase_CMSetPortDirection:
				CM_CMSetPortDirection(site, testSite, testConditionCollection);
				break;
#pragma endregion

#pragma region RF Case
			case RFCase_SourcePower:
				CM_RF_SourcePower(site, testSite, testConditionCollection);
				break;
			case RFCase_SourcePowerFast:
				CM_RF_SourcePowerFast(site, testSite, testConditionCollection);
				break;
			case RFCase_SourcePowerLow:
				CM_RF_SourcePowerLow(site, testSite, testConditionCollection);
				break;
			case RFCase_SourceTwoTone:
				CM_RF_SourceTwoTone(site, testSite, testConditionCollection);
				break;
			case RFCase_IsolateChannel:
				CM_RF_IsolateChannel(site, testSite, testConditionCollection);
				break;
			case RFCase_StartModulation:
				CM_RF_StartModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_StopModulation:
				CM_RF_StopModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerRouting:
				CM_RF_SetSourceTriggerRouting(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerIn:
				CM_RF_SetSourceTriggerIn(site, testSite, testConditionCollection);
				break;
			case RFCase_SetSourceTriggerOut:
				CM_RF_SetSourceTriggerOut(site, testSite, testConditionCollection);
				break;
			case RFCase_SetMeasureTriggerRouting:
				CM_RF_SetMeasureTriggerRouting(site, testSite, testConditionCollection);
				break;
			case RFCase_SetMeasureTriggerIn:
				CM_RF_SetMeasureTriggerIn(site, testSite, testConditionCollection);
				break;
			case RFCase_RunSourceAlignment:
				CM_RF_RunSourceAlignment(site, testSite, testConditionCollection);
				break;
			case RFCase_LoadModulation:
				CM_RF_LoadModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_WlanInit:
				CM_RF_WlanInit(site, testSite, testConditionCollection);
				break;
			case RFCase_EvmMeasurementSetup:
				CM_RF_EvmMeasurementSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_SemMeasurementSetup:
				CM_RF_SemMeasurementSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_MeasureSetup:
				CM_RF_MeasureSetup(site, testSite, testConditionCollection);
				break;
			case RFCase_MeasureSetupIQ:
				CM_RF_MeasureSetupIQ(site, testSite, testConditionCollection);
				break;
			case RFCase_TriggerSigenStartModulation:
				CM_RF_TriggerSigenStartModulation(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferInit:
				CM_RF_WolferInit(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferSelectPath:
				CM_RF_WolferSelectPath(site, testSite, testConditionCollection);
				break;
			case RFCase_WolferSourcePower:
				CM_RF_WolferSourcePower(site, testSite, testConditionCollection);
				break;
#pragma endregion

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
	void AMB7600SRTestLibrary::TestMethod_Selection(Site ^ site, int testSite, int testMethodSelection, String ^ testParameterName, int  testParameterCount, int % methodTestParameterCount)
	{
		try {
			switch (testMethodSelection)
			{
#pragma region DC Case
			case DCCase_OS:
				TM_OS(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_MeasureCurrent:
				TM_MeasureCurrent(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_MeasureVoltage:
				TM_MeasureVoltage(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_AMMeasureBurstCurrent:
				TM_MeasureBurstCurrent(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_AMMeasureBurstVoltage:
				TM_MeasureBurstVoltage(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case DCCase_DifferentialResult:
				TM_DifferentialResult(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

#pragma region DM Case
			case DMCase_MIPIReadVector:
				TM_MIPIReadVector(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
#pragma endregion

#pragma region RF Case
			case RFCase_MeasureChannel:
				TM_RF_MeasureChannel(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureChannelFast:
				TM_RF_MeasureChannelFast(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureChannelIQ:
				TM_RF_MeasureChannelIQ(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureIIP3:
				TM_RF_MeasureIIP3(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureBurstPower:
				TM_RF_MeasureBurstPower(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSwitchingTime:
				TM_RF_MeasureSwitchingTime(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSParam:
				TM_RF_MeasureSParam(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_MeasureSParamIQ:
				TM_RF_MeasureSParamIQ(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_P1dB_DirectSearch:
				TM_RF_P1dB_DirectSearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break; 
			case RFCase_P1dB_BinarySearch:
				TM_RF_P1dB_BinarySearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo:
				TM_RF_PowerServo(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo_BinarySearch:
				TM_RF_PowerServo_BinarySearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_PowerServo_LinearSearch:
				TM_RF_PowerServo_LinearSearch(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadEvm:
				TM_RF_ReadEvm(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadEvmAsync:
				TM_RF_ReadEvmAsync(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadSem:
				TM_RF_ReadSem(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_ReadSemAsync:
				TM_RF_ReadSemAsync(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WlanPowerServo:
				TM_RF_WlanPowerServo(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WlanResidualEVM:
				TM_RF_WlanResidualEVM(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
				break;
			case RFCase_WolferMeasureChannel:
				TM_RF_WolferMeasureChannel(site, testSite, testParameterName, testParameterCount, methodTestParameterCount);
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