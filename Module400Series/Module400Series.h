#pragma once
/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:						Module400Series.h
Purpose:					Declare all Module400Series test library functions.
UUTOffset:					Supported.
TrueParallelUUTOffset:		Supported.
Version	:					1.1.0.0
----------------------------------------------------------------------*/
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Test Function/TestFunction.h"
#include "../Test Function/Aemulus.Hardware.CM.h"
#include "../Test Function/Aemulus.Hardware.SMU.h"
#include "../Test Function/Aemulus.Hardware.DM.h"
#include "../Test Function/Aemulus.Hardware.DIO.h"
#include "../Test Function/Aemulus.Hardware.AMSRF.h"
#include "../Module400Series/Module400Series.h"

//#using "C:\Aemulus\techFlow3\bin\libSync.dll" 
//#using "C:\Aemulus\techFlow3\bin\Aemulus.Hardware.ResourceManager.dll" 
//#using "C:\Aemulus\techFlow3\bin\Aemulus.Tech.Flow.Core.dll" 

using namespace System;
using namespace System::Data;
using namespace System::Reflection;
using namespace System::Text::RegularExpressions;

using namespace Aemulus::Hardware;
using namespace Aemulus::Configuration;
using namespace Aemulus::TestLib::RF::Utility;
namespace Functions
{
	//Forward Declaration
	ref class MethodsBranch;
	ref class TestFunction;

	public ref class Module400Series
	{
	public:

#pragma region "Resource Module Object"

#if CM_ENABLE 
		array<CM ^>^ cm;
#endif 

#if SMU_ENABLE 
		array<SMU ^>^ smu;
#endif 

#if DM_ENABLE 
		array<DM ^>^ dm;
#endif 

#if DIO_ENABLE 
		array<DIO ^>^ dio;
#endif 


#if ACM_ENABLE 
		array<ACM ^>^ acm;
#endif 

#if TMU_ENABLE 
		array<TMU ^>^ tm;
#endif 

#pragma endregion "Resource Module Object"

		AppDomain ^ currentDomain;
		Module400Series::Module400Series(TestFunction ^ TestFunc);
		~Module400Series(void);

		TestFunction ^ tl;
		DateTime^ time = DateTime::Now;

		MethodsBranch ^ methods;


#pragma region "Hardware Resource Manager"
		// Hardware Resource Manager 
		value struct ResourceManagerSetting
		{
			String ^ moduleAlias;
			String ^ ResourceType;
			Resource ^ HardwareRsrc;
			array<ResourceManager ^>^ RsrcManager;

			// Hardware initialization status
			bool AM_HardwareStatus;
			bool DM_HardwareStatus;
			bool DIO_HardwareStatus;
			bool CM_HardwareStatus;
			bool AMSRF_HardwareStatus;

			Dictionary <String ^, String ^> ^ AMResourceAlias_ModuleType;

			Dictionary <String ^, int> ^ AMResourceAlias;
			Dictionary <String ^, int> ^ DMResourceAlias;
			Dictionary <String ^, int> ^ DIOResourceAlias;
			Dictionary <String ^, int> ^ DIOResourcePortAlias;
			Dictionary <String ^, int> ^ CMResourceAlias;

			Dictionary <String ^, int> ^ ResourceAlias;

			array<ResourceManager ^>^ RsrcManagerSPG;
			PinGroupMapCollection ^ pinGroups;
			array<String ^>^ pinMapsTemp;
			Dictionary <String ^, MapCollection ^> ^ mcPinGroupPinMaps; //Key - PinGroup; Value - PinMaps 
			Dictionary <String ^, array<String ^>^> ^ PinGroupPinMaps;	//Key - PinGroup; Value - PinMaps 
		};
		array<ResourceManagerSetting> ^ ResourceManagerSett;
#pragma endregion "Hardware Resource Manager"

		int InitializeTester(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead);
		int UninitializeTester(Site ^ site);

#pragma region "AM400e Helper Function"
		///////////////////////////////////////////////////////
		// AM400e Helper Function 
		///////////////////////////////////////////////////////
		int InitializeAM400eResource(Site ^site);
		int UninitializeAM400eResource(Site ^site);
		array<String^>^ GetAMModuleAlias(Site ^ site, int siteIndex);
		int InitAmPinAliasPreviousState(Site ^ site, int siteIndex);
		int ConfigureSMU(int testSite, String^ PIN, int Mode, int bandwidth, double compliance, double nplc, double powerLineFreq);
		int SMU_MeasureOS(int testSite, String ^ PIN, double driveCurrent, double clampVoltage, double delay, double % result);
		int SMU_MeasureCurrent(int testSite, String ^ PIN, double % result);
		int SMU_MeasureVoltage(int testSite, String ^ PIN, double % result);
		int SMU_MeasureCurrent(int testSite, String ^ PIN, double delay, double % result);
		int SMU_MeasureVoltage(int testSite, String ^ PIN, double delay, double % result);
		int SMU_MeasureBurstCurrent(int testSite, String ^ PIN, double duration, double peakPercentage, double % result);
		int SMU_MeasureBurstVoltage(int testSite, String ^ PIN, double duration, double peakPercentage, double % result);
		int SMU_NplcSetting(int testSite, String ^ PIN, double nplc);
		int SMU_ConfigureOutputFunction(int testSite, String ^ PIN, int function);
		int SMU_ClampCurrent(int testSite, String ^ PIN, double clampValue);
		int SMU_ClampVoltage(int testSite, String ^ PIN, double clampValue);
		int SMU_DriveCurrent(int testSite, String ^ PIN, double driveValue);
		int SMU_DriveVoltage(int testSite, String ^ PIN, double driveValue);
		int SMU_OnSMU(int testSite, String ^ PIN);
		int SMU_OffSMU(int testSite, String ^ PIN);
		int SMU_SetBandwidth(int testSite, String ^ PIN, int bandwidth);
		int SMU_ConfigureSense(int testSite, String ^ PIN, int sense);
		int SMU_ConfigurePowerLineFreq(int testSite, String ^ PIN, double plf);
		int SMU_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal);
		int SMU_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth);
		int SMU_ConfigureTriggerEdgeLevel(int testSite, String ^ moduleAlias, int trigSource, int trigMode);
		int SMU_ConfigureTriggerEdgeLevelExtra(int testSite, String ^ moduleAlias, int trigSource, int trigMode, int ignoreTrigCount);
		int SMU_ConfigureInputTriggerSelect(int testSite, String ^ pinAlias, int trigSource, double delayAfterTrig);
		int SMU_ConfigureSMUOutputTriggerMode(int testSite, String ^ pinAlias, int mode);
		int SMU_ConfigureSMUOutputTriggerPulseWidth(int testSite, String ^ pinAlias, double pulseWidth);
		int SMU_ConfigureSMUOutputTriggerDuringSource(int testSite, String ^ pinAlias, double level, double range, int mode, int edgeSetting);
		int SMU_ConfigureOutputTriggerSelect(int testSite, String ^ pinAlias, int triggerOutput, double triggerDelay);

#pragma endregion "AM400e Helper Function"

#pragma region "DM400e Helper Function "
		///////////////////////////////////////////////////////
		// DM400e Helper Function 
		///////////////////////////////////////////////////////		
		int InitializeDM400eResource(Site ^ site);
		int InitializeDM400eResource_ORI(Site ^ site);
		int UninitializeDM400eResource(Site ^ site);
		array<String^>^ GetDMModuleAlias(Site ^ site, int siteIndex);
		int InitDmPinAliasPreviousState(Site ^site, int siteIndex);
		int DM_MeasureOS(int testSite, String ^ PIN, double driveCurrent, double clampVoltage, double delay, double % result);
		int DM_MeasureCurrent(int testSite, String ^ PIN, double % result);
		int DM_MeasureVoltage(int testSite, String ^ PIN, double % result);
		int DM_MeasureCurrent(int testSite, String ^ PIN, double delay, double % result);
		int DM_MeasureVoltage(int testSite, String ^ PIN, double delay, double % result);
		int DM_NplcSetting(int testSite, String ^ PIN, double nplc);
		int DM_ConfigureOutputFunction(int testSite, String ^ PIN, int function);
		int DM_ClampCurrent(int testSite, String ^ PIN, double clampValue);
		int DM_ClampVoltage(int testSite, String ^ PIN, double clampValue);
		int DM_DriveCurrent(int testSite, String ^ PIN, double driveValue);
		int DM_DriveVoltage(int testSite, String ^ PIN, double driveValue);
		int DM_OnDMpin(int testSite, String ^ PIN);
		int DM_OffDMpin(int testSite, String ^ PIN);
		int DM_ConfigureSense(int testSite, String ^ PIN, int sense);
		int DM_OperationMode(int testSite, String ^ PIN, int mode);
		int DM_ConfigureDPINLevelVector(int testSite, String ^ PIN, double VIH, double VIL, double VOH, double VOL, double IOH, double IOL, double VCH, double VCL, double VTERM);
		int DM_ConfigureDPINLevelDIO(int testSite, String ^ PIN, double VIH, double VIL, double VOH, double VOL, double IOH, double IOL, double VCH, double VCL, double VTERM);
		int DM_ConfigurePEAttribute(int testSite, String ^ PIN, bool InputTermEnable, bool HVEnable, bool ActiveLoadEnable, bool DifferentialComparatorEnable);

		int DM_DioModeDrivePin(int testSite, String ^ PIN, int driveValue);
		int DM_DioModeSetPinDirection(int testSite, String ^ PIN, int pinDirection);
		int DM_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal);
		int DM_ConfigureTriggerEdgeLevel(int testSite, String ^ moduleAlias, int trigSource, int trigMode);
		int DM_ConfigureTriggerEdgeLevelExtra(int testSite, String ^ moduleAlias, int trigSource, int trigMode, int ignoreTrigCount);
		int DM_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth);
		int DM_ConfigureInputTriggerSelect(int testSite, String ^ moduleAlias, int trigSource, double delayAfterTrig);
		int DM_ConfigureOutputTriggerSelect(int testSite, String ^ moduleAlias, int trigOutput0, int trigOutput1);
		int DM_ConfigureReadPin_TriggerOutput(int testSite, String ^ pinAlias, int pinStatusSelect);
		int DM_ConfigureDigitalPinToPMU(int testSite, String^ PIN, int measureMode, int senseMode, double compliance, double driveValue, double nplc);
		int DM_ConfigureDigitalPinToVector(int testSite, String^ PIN, int DPinLevelSet, int PEAttSet);
		int DM_ConfigureDigitalPinToDIO(int testSite, String^ PIN, int DPinLevelSet, int pinDirection);
		int DM_Init(int testSite, int dpinGroup);
		int DM_MIPIWriteVector(int testSite, String ^ moduleAlias, String ^ vectorFileName);
		int CastTimingSetPeriodControlItem(Site ^ site, int siteIndex);
		int CastDpinLevelControlItem(Site ^ site, int siteIndex);
		int CastPEAttributeControlItem(Site ^ site, int siteIndex);
		bool CheckingAnyDmModuleRunVector(Site ^ site, int siteIndex, array<String ^>^ moduleAlias, array<String ^>^ % moduleAliasRunVector, array<String ^>^ % communicationProtocol);
		int LoadVectorFiles(Site ^ site, int siteIndex, String ^ ModuleAlias);
		int LoadVectorFiles_ORI(Site ^ site, int siteIndex, String ^ ModuleAlias);
		int GetVectorFiles(Site ^ site);
		int DMLoadVectorFiles(Site ^ site, int siteIndex, String ^ ModuleAlias);
		int VectorFilesInfo(Site ^ site, int siteIndex);
		int API_Read_Single_VectorStateFile_SingleLine(array<String^> ^  Reader_Value, String^ % Mode, int % USID, int % RegAddr, int % RegData, String^ % Operation, String^ % Speed, bool % Read_VectorStateFileBasic_Success, String^ % Read_VectorStateFileBasic_ErrorMessage);
		int API_MIPI_Vector_Read(Site ^ site, int testSite, String ^ dataPinAlias, String ^ DM_Module_Alias, double channelInputDelay, String ^ VectorFileName, bool sweepOperation, array<int> ^ % ReadHistoryRam_Data, int % VectorFailCount, int % VectorFirstFail);

#pragma endregion "DM400e Helper Function "	

#pragma region "CM400e Helper Function "
		///////////////////////////////////////////////////////
		// IOM421e Helper Function 
		///////////////////////////////////////////////////////		
		int InitializeCM400eResource(Site ^ site);
		int UninitializeCM400eResource(Site ^ site);
		array<String^>^ GetCMModuleAlias(Site ^ site, int siteIndex);

		int CM_ConfigurePXES2780_TriggerBusAB(int testSite, String^ moduleAlias, int Enable_AB, int AB_Direction);
		int CM_ConfigurePXES2780_TriggerBusBC(int testSite, String^ moduleAlias, int Enable_BC, int BC_Direction);
		int CM_DrivePort(int testSite, String^ moduleAlias, int portVal);
		int CM_DrivePin(int testSite, String^ moduleAlias, int pin, int pinVal);
		int CM_SetPortDirection(int testSite, String^ moduleAlias, int portDir);
		int CM_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal);
		int CM_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth);

#pragma endregion "CM400e Helper Function "	

#pragma region "IOM421e Helper Function "
		///////////////////////////////////////////////////////
		// IOM421e Helper Function 
		///////////////////////////////////////////////////////		
		int InitializeIOM421eResource(Site ^ site);
		int UninitializeIOM421eResource(Site ^ site);
		array<String^>^ GetDIOModuleAlias(Site ^ site, int siteIndex);
		int InitIOMModuleAliasPreviousState(Site ^ site, int siteIndex, array<String^> ^ ModuleAlias);
		int InitIOMPortAliasPreviousState(Site ^ site, int siteIndex);
		int InitIOMPinAliasPreviousState(Site ^ site, int siteIndex);
		int DIO_SetVIO(int testSite, String ^ ModuleAlias, int setting);
		int DIO_SetPortDirection(int testSite, String ^ portAlias, int dirval);
		int DIO_DrivePort(int testSite, String ^ portAlias, int portval);
		int DIO_DrivePin(int testSite, String ^ pinAlias, int pinval);
#pragma endregion "IOM421e Helper Function "	

#pragma region "Test Method Function"

		//DC - Test Methods
		void TM_OS(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureCurrent(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureVoltage(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureBurstCurrent(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureBurstVoltage(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_DifferentialResult(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);

		//Digital - Test Methods
		void TM_MIPIReadVector(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);

#pragma endregion "Test Method Function"

#pragma region "Control Method Function"

		//DC - Control Methods
		void CM_DriveVoltage(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);

		void CM_DriveCurrent(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_ClampVoltage(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_ClampCurrent(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_AMConfigureInputTriggerSelect(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_AMConfigureSMUOutputTriggerMode(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_AMConfigureSMUOutputTriggerPulseWidth(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_AMConfigureSMUOutputTriggerDuringSource(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_AMConfigureOutputTriggerSelect(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_SetNPLC(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_SetPinOnOff(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_WaitSecond(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_MapTriggerIntToTriggerOut(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DriveSoftwareTrigger(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_ConfigureTriggerEdgeLevel(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);

		//Digital - Control Methods
		void CM_DMInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_WriteVector(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DMConfigureInputTriggerSelect(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DMConfigureOutputTriggerSelect(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DMConfigureReadPin_TriggerOutput(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DMConfigurePinToPMU(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_DMConfigurePinToVector(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_DMConfigurePinToDIO(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_DMDioModeDrivePin(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DMCastDPinLevel(Site ^ site, int testSIte, ConditionCollection^testConditionCollection);
		void CM_DMCastTimingSetPeriod(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DMCastPEAttribute(Site ^ site, int testSite, ConditionCollection^testConditionCollection);
		void CM_DMLoadVectorFile(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);

		//IOM421e - Control Methods
		void CM_DIODrivePin(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DIODrivePort(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DIOSetModuleVIO(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_DIOSetPortDirection(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);

		void CM_CMDrivePin(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_CMDrivePort(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_CMSetPortDirection(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_CMConfigurePXES2780_TriggerBus(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);

#pragma endregion "Control Method Function"

	private:
		Aemulus::TestLib::Utility::Utilities ^ util;
		array<ResourceManager^> ^ RsrcManager;
		int debug;

		int lineNumber;
		String^ timerFileName = "TimingFile_Manual" + System::DateTime::Now.ToString("yyyyMMddHHmmss");

		//Global Variable
		int totalSite;

		//Globals ^ glob;

		//Tracer Logger
		String^ MainTracer;
		Aemulus::TestLib::Utility::TracerLogger ^ tracerLogger;

		//Module Resource
		static String^ resourceAM = "AM430e";
		static String^ resourceDM = "DM483e";

	};
}

/*----------------------------------------------------------------------
* Revision Log
* $Log: AMB7600SR.h.rca$

* v1.1.0.0 (20/4/2020), Wafiq
* Separate DC class from RF Test Library.

* v1.0.0.0 (20/4/2020), Jack
* Initial release version.

----------------------------------------------------------------------*/