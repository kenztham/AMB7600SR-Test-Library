#pragma once
/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:						AMB7600SR.h
Purpose:					Declare all AMB7600SR test library functions.
UUTOffset:					Supported.
TrueParallelUUTOffset:		Supported.
Version	:					1.0.0.0
----------------------------------------------------------------------*/
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Test Function/Aemulus.Hardware.DIO.h"
#include "../Test Function/TestFunction.h"
#include "../Test Function/Aemulus.Hardware.SMU.h"
#include "../Test Function/Aemulus.Hardware.DM.h"
#include "../Test Function/Aemulus.Hardware.CM.h"
#include "../Test Function/Aemulus.Hardware.AMSRF.h"
#include "../AMB7600SR/AMB7600SR.h"

//#using "C:\Aemulus\techFlow3\bin\libSync.dll" 
//#using "C:\Aemulus\techFlow3\bin\Aemulus.Hardware.ResourceManager.dll" 
//#using "C:\Aemulus\techFlow3\bin\Aemulus.Tech.Flow.Core.dll" 

using namespace System;
using namespace System::Data;
using namespace Aemulus::Hardware;
using namespace System::Reflection;
using namespace Aemulus::Configuration;
using namespace Aemulus::Configuration7600;
using namespace Aemulus::TestLib::RF::Utility;
using namespace System::Text::RegularExpressions;

namespace Functions
{
	private enum class rxswpath { rx1, rx2, rx3, rx4, rx5, rx6, rx7, rx8, rx9, rx10, rx11, rx12, rx13, rx14, rx15, rx16, rx17, rx18, rx19, rx20, rx21, rx22, rx23, rx24 };
	private enum class txswpath { tx1, tx2, tx3, tx4 };
	private enum class wlfoutsw { wlfoutoff, wlfout1, wlfout2 };

	public ref class AMB7600SRTestLibrary
	{
	public:

#pragma region "Resource Module Object"
#if SMU_ENABLE 
		array<SMU ^>^ smu;
#endif 

#if DM_ENABLE 
		array<DM ^>^ dm;
#endif 

#if DIO_ENABLE 
		array<DIO ^>^ dio;
#endif 

#if CM_ENABLE 
		array<CM ^>^ cm;
#endif 


#if AMSRF_ENABLE 
		//Hardware Object
		AMSRF ^ Amsrf0;
		IRFDM ^ Rfdm0;
		IRFMM ^ Rfmm0;
		IDigitizer ^ DIGITIZER0;
		ISignalGenerator ^ SIGGEN0;

		AMSRF ^ Amsrf1;
		IRFDM ^ Rfdm1;
		IRFMM ^ Rfmm1;
		IDigitizer ^ DIGITIZER1;
		ISignalGenerator ^ SIGGEN1;

		array<AMSRF^>^ amsrf;
		array<IM9421A_Receiver^> ^ dig;
		array<IM9421A_Source^>^ sigGen;
		array<IRFDM ^> ^ rfdms;
		array<IRFMM ^> ^ rfmms;
		array<IRFPM ^> ^ rfpms;

		SC5511A  ^ SIG_SC5511;
		SC5505A ^ SIG_SC5505;

		SC5511A  ^ SIG_SC5511_A0;
		SC5511A  ^ SIG_SC5511_A1;
		SC5505A ^ SIG_SC5505_A0;
		SC5505A ^ SIG_SC5505_A1;

		array< SC5511A^> ^ SC5511;
		array< SC5505A^> ^ SC5505;

		array<Wlan ^> ^wlan;
		array<Wlan ^> ^wlan_acax;
		array<Wlan ^> ^wlan_abgn;

#endif 
#pragma endregion "Resource Module Object"

		AppDomain ^ currentDomain;
		AMB7600SRTestLibrary::AMB7600SRTestLibrary(TestFunction ^ TestFunc);
		~AMB7600SRTestLibrary(void);

		TestFunction ^ tl;
		DateTime^ time = DateTime::Now;


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

#pragma region "External Module"
		///////////////////////////////////////////////////////
		//External Module
		///////////////////////////////////////////////////////
		array<unsigned char  >^ SourceChannel_SC;
		Dictionary <int, String ^> ^ TestSiteSignalCoreType;
#pragma endregion "External Module"

#pragma region "Site Configuration Information"
		///////////////////////////////////////////////////////
		//Site Configuration Xml File
		///////////////////////////////////////////////////////

		String ^ SiteConfig;
		String ^ HeadSiteInfo;

		array<String ^>^HeadSiteXml;

		array<int>^HeadXmlIndex;
		array<int>^SiteXmlIndex;
		int TotalHeadCount = 0;

		Dictionary <String ^, String ^> ^ AMSRF_Head_Site;

		value struct SiteConfigInfo
		{
			//AMSRF0
			array<int> ^ AMSRF0_Site;
			bool AMSRF0_Exist;

			//AMSRF1
			array<int> ^ AMSRF1_Site;
			bool AMSRF1_Exist;

			//ExternalModule
			List<Dictionary<String^, String^>^> ^ExternalModuleList;


			int TotalUUTOffset;
			int TotalExternalModule;
			int TotalSignalCore;
			int TotalWolfer;
			String ^ AMSRFSupported;
		};
		SiteConfigInfo H0S0;
		SiteConfigInfo H0S1;
		SiteConfigInfo H1S0;
		SiteConfigInfo H1S1;
		SiteConfigInfo CurrentHeadSite;

		///////////////////////////////////////////////////////
		// Site Configuration Function
		///////////////////////////////////////////////////////			
		int RF_SystemConfiguration(Site ^ site);
		int RF_CastSystemConfigFileInfo(String ^ ConfigPath, String ^ % SystemType, int % moduleRFM611Count, int % moduleRFM641Count, int % moduleRFM621Count, int % moduleRFM631Count, array<String ^, 2>^ % moduleRF);
		int RF_SystemInitialization(Site^ site);
		int RF_ExternalModuleInitialization(Site^ site);
		int RF_ExternalModuleUninitialization(Site^ site);

		void SiteConfiguration(Site ^ site);
		void HeadSite(Site ^ site, XmlNode ^ XmlInfo, SiteConfigInfo % SiteInfo);
		bool SupportedExternalModule(String ^ ExternalModule, int % NoOfChannel, array<String^>^ % ExternalModuleInfo);
		void ExternalModuleInfoCasting(Site ^ site, XmlNode ^ ExternalModule, SiteConfigInfo  % SiteInfo);
		void AMSRFInfoCasting(Site ^ site, XmlNode ^ AMSRFxml, SiteConfigInfo  % SiteInfo);
		void AMSRFInfoChecking(SiteConfigInfo SiteInfo);
		void ExternalModuleInfoChecking(SiteConfigInfo SiteInfo);
		void StringArrayToIntArray(array<String^> ^ StringInfo, array<int> ^ % IntInfo);
		void SiteConfigInfoCasting(Site ^ site, XmlNode ^ Xmlnfo);
		void SiteConfigInfoChecking(Site ^ site, XmlNode ^ XmlInfo);
		void TotalHeadCountInfo(Site ^ site, XmlNode ^ XmlInfo);
		void HeadSiteXmlInfo(Site ^ site, XmlNode ^ XmlInfo);
		void HeadSiteAmsrfChecking();
		void HeadSiteExternalModuleChecking();
		void AmsrfInfoToLoggerFile();
#pragma endregion "Site Configuration Information"

#pragma region "System Configuration Xml File"
		///////////////////////////////////////////////////////
		//System Configuration Xml File
		///////////////////////////////////////////////////////
		value struct SystemConfigurationInfo
		{
			String ^ ConfigPath;
			String ^ SystemType;
			int moduleRFM611Count;
			int moduleRFM641Count;
			int moduleRFM621Count;
			int moduleRFM631Count;
			array<String ^, 2>^ moduleRF;

		};
		SystemConfigurationInfo  SystemConfigurationInfoAMSRF0;
		SystemConfigurationInfo  SystemConfigurationInfoAMSRF1;
#pragma endregion "System Configuration Xml File"

#pragma region "Init and Uninit Resource Helper Function "

		// AMB7600SR SW & HW Utility Helper Functions
		int InitializeTester(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead);
		int UninitializeTester(Site ^ site);
		int PostProcessing_RF(Site ^ site);

		// AMSRF Helper Function 
		int InitializeAMSRFResource(Site ^ site);
		int UninitializeAMSRFResource(Site ^ site);
		int AmsrfPreviousState(Site^ site);
		int ResetAmsrfPreviousState(int testSite, bool reset);
#pragma endregion "Init and Uninit Resource Helper Function"

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

#pragma region "RF Helper Function"
		///////////////////////////////////////////////////////
		// RF Helper Function
		///////////////////////////////////////////////////////			
		//AMB7600SR_High Level (Test Phase)
		void RF_MeasureSetup(int testSite, String ^ measureChannel, double measureLevel, double measureFreq, int filterOption);
		void RF_MeasureSetupIQ(int testSite, String ^ measureChannel, double measureLevel, double measureFreq, double sampleRate, int sampleSize, int filterOption);
		void RF_MeasureFast(int testSite, String ^ measureChannel, double measureLevel, double measureFreq, int filterOption, double delay, double % result);
		int RF_MeasureChannel(int testSite, String^ measureChannel, double delay, double % result);
		int RF_MeasureChannelIQ(int testSite, String^ measureChannel, double delay, double % result);
		int RF_MeasureRawIQArray(int testSite, String^ measureChannel, double delay, array <double>^ % iData, array <double>^ % qData);
		int RF_GetMeasureFactor(int testSite, String^ measureChannel, double measureLevel, double measureFreq, int filterOption, double  % measureFactor);
		int RF_GetSourceFactor(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, double % sourceFactor, double  % couplerFactor);
		int RF_GetSourceFactor(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, double sourceAttenuattion, double % sourceFactor, double  % couplerFactor);
		int RF_GetSourceAlignFactor(int l_TestSite, String^ l_SourceChannel, double l_SourceLevel, double l_SourceFreq, double l_RfpmInAtt, double % l_AlignFactor);
		void RF_SourcePower(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq);
		void RF_SourcePower(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, double attenuation);
		void RF_SourcePowerFast(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, bool userSetAttenuation, double attenuation);
		void RF_SourceTwoTone(int testSite, String^ sourceChannel, double sourceLevel0, double sourceFreq0, double sourceLevel1, double sourceFreq1, double attenuation);
		void RF_SourceTwoTone(int testSite, String^ sourceChannel, double sourceLevel0, double sourceFreq0, double sourceLevel1, double sourceFreq1);
		void RF_StartModulation(int testSite, String ^ VSG, String ^ modulationFile, int playBackMode);
		void RF_LoadModulation(int testSite, String ^ VSG, String ^ modulationFile, int stationNo);
		void RF_StopModulation(int testSite, String ^ VSG);
		void RF_SetSourceTriggerOut(int testSite, String ^ VSG, bool enable, int trigDestination, int trigOption);
		void RF_SetMeasureTriggerRouting(int testSite, String ^ VSA, bool enable, int trigIn, int trigOut);
		void RF_SetSourceTriggerRouting(int testSite, String ^ VSG, bool enable, int trigIn, int trigOut);
		void RF_SetMeasureTriggerIn(int testSite, String ^ VSA, bool enable, int trigSource, int trigPolarity, double trigDelay);
		void RF_SetSourceTriggerIn(int testSite, String ^ VSG, bool enable, int trigSource, int trigPolarity, double trigDelay);
		void RF_MeasureSParamSetup(int testSite, array<String^>^ channelArray, double sourcePower, double measurePower, double measurefreq);
		void RF_MeasureSParamSetup(int testSite, array<String^>^ channelArray, double sourcePower, double measurePower, double measurefreq, bool preampOn, double sampleSize, double sampleRate);
		void RF_MeasureSParam(int testSite, array<String^>^ channelArray, SParam_Format format, array<ComplexNumber> ^ % sparamResult);
		void RF_IsolateAllChannel(int testSite);
		void RF_IsolateChannel(int testSite, String ^ channel);
		void RF_RunSourceAlignment(int testSite);
		void RF_LoadHardwareProfile(int testSite);
		//Helper Function (Test Phase)
		void RF_ConvertIQtoPower(double iData, double qData, double % powerWatt, double % powerdBm);
		void RF_ConvertIQtoPower(array <double>^  iData, array <double>^  qData, int sampleSize, int l_StartIndex, double % averagePowerWatt, double % averagePowerdBm);
		void RF_ConvertWattTodBm(double powerWatt, double % powerdBm);
		void RF_ConvertdBmToWatt(double powerdBm, double % powerWatt);
		void RF_RFM631FilterOption(double fundamentalFreq, double harmonicFreq, int % filterOption);
		void RF_TestMethod_ResultDisplayChecking(Site^ site, int testSite, int totalTestParameter, int totalResult, int testParameterNum, array<String^>^ % userDesiredResult);

		//VXT_Low Level (Test Phase)
		void RF_KTM9420_ATTR_RECEIVER_TRIGGERS_EXTERNSL_TRIGGER_TERMINATION_SET(int testSite, int terminationMode);
		void RF_KTM9420_ATTR_RECEIVER_RF_POWER_SET(int testSite, double measurePower);
		void RF_KTM9420_ATTR_RECEIVER_RF_FREQUENCY_SET(int testSite, double measureFreq);
		void RF_KtM9420_WaitForData(int testSite, double timeOut, bool % status);
		void RF_KtM9420_ReadPower(int testSite, long captureID, double % result, bool % overLoad);
		void RF_KtM9420_Apply(int testSite);
		void RF_KtM9420_Arm(int testSite);
		int RF_KtM9420_GetIQData(int testSite, array<double> ^% iData, array<double> ^% qData);
		void RF_KTM9420_ATTR_SOURCE_MODULATION_BASEBAND_POWER_SET(int testSite, double powerLevel);
		void RF_KTM9420_ATTR_SOURCE_RF_LEVEL_SET(int testSite, double powerLevel);
		void RF_KTM9420_ATTR_SOURCE_RF_FREQUENCY_SET(int testSite, double sourceFreq);
		void RF_KTM9420_ATTR_SOURCE_Trigger(int testSite, String ^ VSG, String ^ modulationFile);

		//RFM600e_Low Level (Test Phase)
		void RF_RFDM621_SetInputSource(int testSite, int outputPort, int mode);
		void RF_RFDM621_SetMode(int testSite, int mode);
	//	void CalculateSwitchingTime(int optionRiseFall, array<double>^ iData, array<double>^ qData, double sampleRate, double startCapture, double stopCapture, int numberAveragingInit, int numberAveragingFinal, double digitizerTriggerDelay, double correctionFactor, double thresholdUncertainty, double % timing);
		void MovingAverageUtility(array<double>^ pData_Watt, int movingAverageFactor, array<double>^ % pData_Watt_MA);
		void CalculateSwitchingTime(int optionRiseFall, array<double>^ iData, array<double>^ qData, bool movingAverageStatus, int movingAverageFactor, double sampleRate, double startCapture, double stopCapture, int numberAveragingInit, int numberAveragingFinal, double digitizerTriggerDelay, double correctionFactor, double thresholdUncertainty, double % timing, array<double>^ % pData_Watt);

		//External Signal Generator Signal Core(Test Phase)
		void RF_SourcePowerExternalSignalGenerator(int testSite, double sourceLevel);
		void RF_SourceFreqExternalSignalGenerator(int testSite, double sourceFreq);
		void RF_OutputEnableExternalSignalGenerator(int testSite, bool enable);

		void RF_WlanInitSetup(int testSite, String ^ VSG, String ^ VSA, int standardSelection, int measureOption);
		void RF_WlanStandardSelection(int testSite, int WlanModulationStandard, WlanModulationStandardEnum % standard);
		void RF_WlanEvmSettingVariable(String^ controlMethod, int settingSelection, DataType % var);

		void RF_WlanEvmMeasurementSetup(int testSite, WlanModulationStandardEnum standard, bool setWlanSettings, Dictionary<int, Object^>^ wlanSettings);
		void RF_WlanEvmSettingConfig(int testSite, Dictionary<int, Object^>^ wlanSettings);
		void RF_WlanEvmMeasurementReadEvm(int testSite, double % result);
		void RF_WlanEvmMeasurementReadEvmAsync(int testSite, String ^testItemName, String^ testParaName);

		void RF_CheckingTestMethodEvmAsyncExist(Site ^ site);
		void RF_EvmAsyncCastResultToTechFlow(Site ^ site, int testSite);

		void RF_CheckingTestMethodSemAsyncExist(Site ^ site);
		void RF_SemAsyncCastResultToTechFlow(Site ^ site, int testSite);
		void RF_WlanSemMeasurementSetup(int testSite, WlanModulationStandardEnum standard, bool setWlanSettings, int semAvg, Dictionary<int, Object^>^ wlanSettings);
		void RF_WlanSemSettingConfig(int testSite, int semAvg, Dictionary<int, Object^>^ wlanSettings);
		void RF_WlanSemSettingVariable(String^ controlMethod, int settingSelection, DataType % var);
		void RF_WlanSemMeasurementReadSem(int testSite, double % peakRefPower, array<double> ^% semData, array<double> ^% margindata, int % status);
		void RF_WlanSemMeasurementReadSemAsync(int testSite, String^ testItemName, String^ testParaName);

		void RF_WlanConfigurePowerServo(int testSit, bool servoEnable, WlanModulationStandardEnum standard, double sourcePower, double targetPower, double targetPowerMargin);
		void RF_WlanRunPowerServo(int testSite);
		void RF_WlanReadPowerServo(int testSite, double % outputPower, double % sourcePower, bool % servoPass, int % servoCount);

		//Wolfer
		double StrToDouble(String ^ str);
		int StrToInt(String ^ str);
		int ReadFreqCalList(int testSite, String^ wolferType, int % freq_count);
		int ReadFreqHarList(int testSite, String^ wolferType, int %freq_count);
		int ReadTxPathLoss(int testSite, String^ wolferType, int %pathLossCount);
		int ReadRxPathLoss(int testSite, String^ wolferType, int %rxpl_count);
		int wlfInit(int testSite, String ^ moduleAlias);
		int wlfTxPath(int testSite, int tx_sw);
		int wlfRxPath(int testSite, int rx_sw);
		int wlfGetSwMatrix(int testSite, String^ wolferType);
		long WlfSource(int testSite, String ^ wolferType, String ^ Source_CH, int wlfoutsw, int outIndex, int TXpath, double % freq, double % targetPout, double offset, double % actualSourceLevel);
		long WlfSource(int testSite, String ^ wolferType, String ^ Source_CH, int wlfoutsw, int outIndex, int TXpath, double % freq, double % targetPout, double offset, double sourceAttenuation, double % actualSourceLevel);
		int wlfMonPath(int testSite, bool mon_sw);
		long getRxPathLoss(int testSite, String^ wolferType, double %freq, double %sourceLevel, int TXpath, String ^ PIN, double %pathloss, String ^ type);
		long getRxHarPathLoss(int testSite, String^ wolferType, double %freq, double %sourceLevel, String ^ PIN, double %pathloss, String ^ type);
		int ReadRxHarPathLoss(int testSite, String^ wolferType, int %rxpl_Har_count);
		int GetFactorCountFromFile(String^ filePath, int % factorCount);
		int WolferSelectPath_C2(int testSite, String^ wolferType, String^ selectTxPath, String^ selectRxPath, double sourceFreq, double measureFreq, bool TxBypassOn, String^ TxInternalPath, String^ RxInternalPath);

#pragma endregion "RF Helper Function"

#pragma region "Test Method Function"

		ConcurrentDictionary<String^, int> ^ Dictionary_TM;

		void InitializeTMDicionary(int totalSite);

		//DC - Test Methods
		void TM_OS(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureCurrent(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureVoltage(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureBurstCurrent(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_MeasureBurstVoltage(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_DifferentialResult(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);

		//Digital - Test Methods
		void TM_MIPIReadVector(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);

		//RF(CW) - Test Methods
		void TM_RF_MeasureChannel(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureChannelFast(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureChannelIQ(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureBurstPower(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureSwitchingTime(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureIIP3(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureSParam(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_MeasureSParamIQ(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_PowerServo(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_PowerServo_BinarySearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_PowerServo_LinearSearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_P1dB_BinarySearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_P1dB_DirectSearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_ReadEvm(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_ReadEvmAsync(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_ReadSem(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_ReadSemAsync(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_WlanPowerServo(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_WlanResidualEVM(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		//void TM_RF_WlanDynamicEVM(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);
		void TM_RF_WolferMeasureChannel(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount);

#pragma endregion "Test Method Function"

#pragma region "Control Method Function"
		void ControlMethod_Selection(Site ^ site, int testSite, int controlMethodSelection, ConditionCollection ^ testConditionCollection);
		void TestMethod_Selection(Site ^ site, int testSite, int testMethodSelection, String ^ testParameterName, int  testParameterCount, int % methodTestParameterCount);
		ConcurrentDictionary<String^, int> ^ Dictionary_CM;

		void InitializeCMDictionary(int totalSite);

		//DC - Control Methods
		void CM_DriveVoltage(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);

		void CM_DriveCurrent(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);
		void CM_ClampVoltage(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_ClampCurrent(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
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
		void CM_ConfigureInputTriggerSelect(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection);

		//Digital - Control Methods
		void CM_DMInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_WriteVector(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
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
		//RF - Control Methods
		void CM_RF_SourcePower(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SourcePowerFast(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SourceTwoTone(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SourcePowerLow(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_RunSourceAlignment(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_StartModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_StopModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SetSourceTriggerOut(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SetSourceTriggerIn(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SetMeasureTriggerIn(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_IsolateChannel(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SetSourceTriggerRouting(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SetMeasureTriggerRouting(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_LoadModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_WlanInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_EvmMeasurementSetup(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_SemMeasurementSetup(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);

		void CM_RF_MeasureSetup(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_MeasureSetupIQ(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_TriggerSigenStartModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_WolferInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_WolferSelectPath(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);
		void CM_RF_WolferSourcePower(Site ^ site, int testSite, ConditionCollection^ testConditionCollection);


#pragma endregion "Control Method Function"

	private:
		Aemulus::TestLib::Utility::Utilities ^ util;
		array<ResourceManager^> ^ RsrcManager;
		int debug;

		int lineNumber;
		String^ timerFileName = "TimingFile_Manual" + System::DateTime::Now.ToString("yyyyMMddHHmmss");

		//Global Variable
		int totalSite;

		Globals ^ glob;

		//Tracer Logger
		String^ MainTracer;
		Aemulus::TestLib::Utility::TracerLogger ^ tracerLogger;

		//Module Resource
		static String^ resourceAM = "AM430e";
		static String^ resourceDM = "DM483e";
#pragma region "wolfer DIO"

		//Global Variable for Wolfer
		double freq2H;
		double freq3H;

		//Channel for Wolfer
		String ^ RFOutCh1;
		String ^ RFOutCh2;
		String ^ RFOutCh3;
		String ^ RFOutCh4;

		String ^ MeasureCh;

		// Corr Factor Arrays

		//array<double> ^ freqcal_freq;
		//array<double> ^ freqcal_pout;
		//array<double> ^ freqHarcal_freq;
		//array<double> ^ freqHarcal_pout;
		array<double> ^ corrfactor_freq_Har;
		array<double> ^	corrfactor_txpl_Har;

		//TxPathLoss Array 

		//array <int>^ txPathLoss_TXpath;
		//array <double>^ txPathLoss_freq;
		//array <double>^txPathLoss_targetpout;
		//array <int>^txPathLoss_outIndex;
		//array <double>^txPathLoss_actualpout;
		//array <double>^txPathLoss_couppout;
		//array <double>^txPathLoss_source;

		//RxPathLoss Array
		array<double> ^ rxrlpl_freq;
		array<double> ^ rxrlpl_p1;
		array<double> ^ rxrlpl_p2;
		array<double> ^ rxrlpl_p3;
		array<double> ^ rxrlpl_p4;
		array<double> ^	rxrlpl_p5;
		array<double> ^	rxrlpl_p8;
		array<double> ^	rxrlpl_p11;
		array<double> ^	rxrlpl_p14;
		array<double> ^	rxrlpl_p17;
		array<double> ^	rxrlpl_p20;
		array<double> ^	rxrlpl_p23;
		array<double> ^	rxrlpl_p6;
		array<double> ^	rxrlpl_p9;
		array<double> ^	rxrlpl_p12;
		array<double> ^	rxrlpl_p15;
		array<double> ^	rxrlpl_p18;
		array<double> ^	rxrlpl_p21;
		array<double> ^	rxrlpl_p24;

		array<int> ^ rxpl_TXPath;
		array<double> ^ rxpl_freq;
		array<double> ^ rxpl_pout;
		array<double> ^ rxpl_p1;
		array<double> ^ rxpl_p2;
		array<double> ^ rxpl_p3;
		array<double> ^ rxpl_p4;
		array<double> ^ rxpl_p5;
		array<double> ^ rxpl_p6;
		array<double> ^ rxpl_p7;
		array<double> ^ rxpl_p8;
		array<double> ^ rxpl_p9;
		array<double> ^ rxpl_p10;
		array<double> ^ rxpl_p11;
		array<double> ^ rxpl_p12;
		array<double> ^ rxpl_p13;
		array<double> ^ rxpl_p14;
		array<double> ^ rxpl_p15;
		array<double> ^ rxpl_p16;
		array<double> ^ rxpl_p17;
		array<double> ^ rxpl_p18;
		array<double> ^ rxpl_p19;
		array<double> ^ rxpl_p20;
		array<double> ^ rxpl_p21;
		array<double> ^ rxpl_p22;
		array<double> ^ rxpl_p23;
		array<double> ^ rxpl_p24;

		array<double> ^ rxpl_freq_Har;
		array<double> ^ rxpl_pout_Har;
		array<double> ^ rxpl_p1_Har;
		array<double> ^ rxpl_p2_Har;
		array<double> ^ rxpl_p3_Har;
		array<double> ^ rxpl_p4_Har;
		array<double> ^ rxpl_p5_Har;
		array<double> ^ rxpl_p6_Har;
		array<double> ^ rxpl_p7_Har;
		array<double> ^ rxpl_p8_Har;
		array<double> ^ rxpl_p9_Har;
		array<double> ^ rxpl_p10_Har;
		array<double> ^ rxpl_p11_Har;
		array<double> ^ rxpl_p12_Har;
		array<double> ^ rxpl_p13_Har;
		array<double> ^ rxpl_p14_Har;
		array<double> ^ rxpl_p15_Har;
		array<double> ^ rxpl_p16_Har;
		array<double> ^ rxpl_p17_Har;
		array<double> ^ rxpl_p18_Har;
		array<double> ^ rxpl_p19_Har;
		array<double> ^ rxpl_p20_Har;
		array<double> ^ rxpl_p21_Har;
		array<double> ^ rxpl_p22_Har;
		array<double> ^ rxpl_p23_Har;
		array<double> ^ rxpl_p24_Har;

		//sw matrix dio
		array<String ^> ^ dioswname;
		array<String ^> ^ dioswmode;
		array<int> ^ diosw0;
		array<int> ^ diosw1;
		array<int> ^ diosw2;
		array<int> ^ diosw3;
		array<int> ^ diosw4;
		array<int> ^ diosw5;
		array<int> ^ diosw6;
		array<int> ^ diosw7;
		array<int> ^ diosw8;
		array<int> ^ diosw9;
		array<int> ^ diosw10;
		array<int> ^ diosw11;
		array<int> ^ diosw12;
		array<int> ^ diosw13;
		array<int> ^ diosw14;
		array<int> ^ diosw15;
		array<int> ^ diosw16;
		array<int> ^ diosw17;
		array<int> ^ diosw18;
		array<int> ^ diosw19;
		array<int> ^ diosw20;
		array<int> ^ diosw21;
		array<int> ^ diosw22;
		array<int> ^ diosw23;
		array<int> ^ diosw24;
		array<int> ^ diosw25;
		array<int> ^ diosw26;
		array<int> ^ diosw27;
		array<int> ^ diosw28;
		array<int> ^ diosw29;
		array<int> ^ diosw30;
		array<int> ^ diosw31;
		array<int> ^ diosw32;
		array<int> ^ diosw33;
		array<int> ^ diosw34;
		array<int> ^ diosw35;
		array<int> ^ diosw36;

#pragma endregion
		// <summary>
		// Perform assembly resolve if the loading of .dll/.exe turns out to be unsucessfull
		// </summary> 
		Assembly ^ currentDomain_AssemblyResolve(Object^ Sender, ResolveEventArgs^ args)
		{
			String^ assemblyPath = String::Empty;

			if (args->Name->Contains("techFlow") == true) {
				assemblyPath = Path::Combine(Path::Combine(Environment::GetEnvironmentVariable("techFlow"), "bin"), "techFlow.exe");
			}

			return Assembly::LoadFile(assemblyPath);
		}
		void THROWEXCEPTION(int siteIndex, String^ errorMessage, int errorCode, int errorLineNumber, char* fileName);
#define ThrowException(siteIndex, errorMessage, errorCode) THROWEXCEPTION(siteIndex, errorMessage, errorCode, __LINE__, __FILE__);
		void THROWEXCEPTION(String^ errorMessage, int errorCode, int errorLineNumber, char* fileName);
#define ThrowSoftException(errorMessage, errorCode) THROWEXCEPTION(errorMessage, errorCode, __LINE__, __FILE__);
		int CHECKERROR(int siteIndex, long errorCode, int errorLineNumber, char* fileName);
#define CheckError(siteIndex, errorCode) CHECKERROR(siteIndex, errorCode, __LINE__, __FILE__);
		int CHECKERROR(long errorCode, int errorLineNumber, char* fileName);
#define CheckSoftError(errorCode) CHECKERROR(errorCode, __LINE__, __FILE__);
	};
}

/*----------------------------------------------------------------------
* Revision Log
* $Log: AMB7600SR.h.rca$

* v1.0.0.0 (20/4/2020), Jack
* Initial release version.

----------------------------------------------------------------------*/