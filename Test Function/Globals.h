/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			Globals.h
Purpose:		Define common global variables
UUTOffset:		Supported.
Version:		v1.1.0.0
----------------------------------------------------------------------*/
#pragma once

#include <windows.h>
#include <math.h>
#include <iostream>

#include "Aemulus.Hardware.CM.h"
#include "Aemulus.Hardware.SMU.h"
#include "Aemulus.Hardware.DM.h"
#include "Aemulus.Hardware.DIO.h"
#include "Aemulus.Hardware.ACM.h"
#include "Aemulus.Hardware.TMU.h"
#include "../Test Function/Aemulus.Hardware.AMSRF.h"
//#using "C:\Aemulus\techFlow3\bin\x64\Aemulus.TestLib.Utility.dll" 

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Diagnostics;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Text::RegularExpressions;
using namespace System::Xml;

using namespace Aemulus::Tech;
using namespace Aemulus::TestLib;
using namespace Aemulus::Hardware;
using namespace Aemulus::Tech::Flow;
using namespace Aemulus::TestLib::Utility;
using namespace Aemulus::Tech::Flow::ProductionSystem;

namespace Functions
{
	public ref class Globals
	{
	public:

		// [Future Enchancement] These are used in Globals.cpp check error function
		// but the program is using the object from the AMB7300.h & AMB7600SR.h
		// plan to combine or just init the object at here for check error purpose.
		// Need further investigate whether to remove or not.
		//#if CM_ENABLE 
		//		array<CM ^>^ cm;
		//#endif 
		//
		//#if SMU_ENABLE
		//		array<SMU ^>^ smu;
		//#endif 
		//
		//#if DM_ENABLE 
		//		array<DM ^>^ dm;
		//#endif 
		//
		//#if DIO_ENABLE 
		//		array<DIO ^>^ iom;
		//#endif 
		//
		//	// [Future Enchancement] To ready ACM & TMU dll and then add reference.
		//
		//#if ACM_ENABLE 
		//		array<ACM ^>^ acm;
		//#endif 
		//
		//#if TMU_ENABLE 
		//		array<TMU ^>^ tm;
		//#endif 

#pragma region "General"
		String ^ TesterId;
		String ^ HardwareProfile;
		String ^ currentFlowName;
		array<String^> ^ currentSubItemName;
		//String ^ currentSubItemName;

		//for Merged SNP 
		int iMergeSnPFile;
		int GeneratedS3PFile = 0;
		array<String^> ^ mergerdTouchstoneFilePath; //path to grab s2p file and merged.

		MessageBoxIconFormat messageBoxIcon;
		//bool EnableLogInDebug;
		//bool EnableTracerInDebug;

#pragma endregion

#pragma region "App Wide Variables "

		///////////////////////////////////////////////////////
		//App Wide Variables 
		///////////////////////////////////////////////////////
		value struct AppWideVariablesStruct
		{
			String ^ DeviceName;
			int CalibrationMode;
			int BoardLossMode;
			int CreateCorrfactorFile;
			int AutoGuCalibrationSetup;
			int writeToRawFile;
			int NumberOfSites;
			int RunAll;
			int PrintLSCenterPointInfo;
			int LSSettingsCalibration;
			String^ DatalogPath;
			bool AutoPat2Pbin;
			bool CheckOperationRegister;
			int AmsrfControllerMode;
			int DMPinGroup;
			int DMInitOption;
			int AMInitOption;
			int CMInitOption;
			int	IOMInitOption;

			int UUT;
			bool Offline;										// True = activate Offline mode
			int Debug;											// 0 = debug mode OFF | 1 = debug mode ON
			double PowerLineFreq;								// 0 = 50Hz | 1 = 60Hz
			bool CreateFixedOffsetFile;							// To enable and create a new FixedOffset.csv file
			String ^ SaveSnpData;								// SaveSnpDataOff | SaveSnpDataOn / Re_Imag | Mag_Angle | dB_Angle
			bool EnableSaveSnpData;
			int touchstoneFileDataFormat;
			String ^ S2Ppath;									//S2Ppath
			bool EnableRenameSnpData;							//S2P_rename
			String ^ snpFileName;								//snpFileName
			bool SharedVNA;
			int CalibrationValidityDay;
			bool isSwapS2PData = false;									//是否交换S2P文件内的数据位置
			bool isSaveBinFolder = false;								//是否保存到对应的分bin文件夹内
			bool GenericStateMappingFile_EN;				// 0 = AMB7300Config_DeviceName | 1 = Use specified generic state / mapping file
			String^ GenericStateMappingFile_Name;			// Generic state / ampping file name if GenericStateMappingFile_EN is TRUE
			bool HighPwrTest_EN;							// 0 = Default | 1 = Enable HighPowerTest
			String^ HighPwrTest_AppsCalFile;				// AppsCalFile path if HighPwrTest_EN is TRUE
			bool VNA_Mutex_EN;								// To enable/disable VNA_Lock() in Pre-Processing & VNA_Unlock() in Post-Processing

															//Port Matching circuit filepath
			array<bool>^ PortMatching_EN;
			String^ PortMatching1;
			String^ PortMatching2;
			String^ PortMatching3;
			String^ PortMatching4;
			String^ PortMatching5;
			String^ PortMatching6;
		};
		AppWideVariablesStruct AWV;

#pragma endregion "App Wide Variables "

#pragma region "Threading Variable"

		///////////////////////////////////////////////////////
		//Threading Variable
		///////////////////////////////////////////////////////
		List<List<int>^> ^ThreadingSite;
		String ^ AMSRFInfo;
		array <int> ^ Amsrf0Site;
		array <int> ^ Amsrf1Site;
		int TotalThread;

#pragma endregion "Threading Variable"

#pragma region "Test Result"

		///////////////////////////////////////////////////////
		//Two Tone Mode
		//Mode:0 (P2 or P1T)
		//Mode:1 (External SignalCore)
		///////////////////////////////////////////////////////
		int TwoToneMode;

#pragma endregion "Test Result"

#pragma region "Error Handling"

		value struct ErrorHandlingStruct {
			String ^ ControlMethodName;
			String ^ TestMethodName;
			String ^ TestItemName;
			String ^ TestParameterName;
		};
		array <ErrorHandlingStruct> ^ ErrorInfo;

#pragma endregion "Error Handling"

#pragma region "PreviousState DC & RF"
		///////////////////////////////////////////////////////
		//DC - PreviousState
		///////////////////////////////////////////////////////
		value struct SMUStateSettings
		{
			Dictionary <String ^, double> ^ SMUStateDriveVoltage;
			Dictionary <String ^, double> ^ SMUStateDriveCurrent;
			Dictionary <String ^, double> ^ SMUStateClampVoltage;
			Dictionary <String ^, double> ^ SMUStateClampCurrent;
			Dictionary <String ^, int> ^ SMUStateOutputFunction;
			Dictionary <String ^, double> ^ SMUStateNPLC;
		};
		array<SMUStateSettings> ^ SMUStateSettingsManager;

		///////////////////////////////////////////////////////
		//Digital - PreviousState (PMU,Vector,DIO)
		///////////////////////////////////////////////////////
		value struct PMUStateSettings
		{
			Dictionary <String ^, double> ^ PMUStateDriveVoltage;
			Dictionary <String ^, double> ^ PMUStateDriveCurrent;
			Dictionary <String ^, double> ^ PMUStateClampVoltage;
			Dictionary <String ^, double> ^ PMUStateClampCurrent;
			Dictionary <String ^, double> ^ PMUStateNPLC;
			Dictionary <String ^, int> ^ PMUStateSense;

			Dictionary <String ^, int> ^ PMUStateOutputFunction;
		};
		array<PMUStateSettings> ^ PMUStateSettingsManager;

		value struct DMStateSettings
		{
			Dictionary <String ^, int> ^ DMStateOperationMode;
		};
		array<DMStateSettings> ^ DMStateSettingsManager;

		value struct PEStateSettings
		{
			Dictionary <String ^, double> ^ PEStateVIH;
			Dictionary <String ^, double> ^ PEStateVIL;
			Dictionary <String ^, double> ^ PEStateVOH;
			Dictionary <String ^, double> ^ PEStateVOL;
			Dictionary <String ^, double> ^ PEStateIOH;
			Dictionary <String ^, double> ^ PEStateIOL;
			Dictionary <String ^, double> ^ PEStateVCH;
			Dictionary <String ^, double> ^ PEStateVCL;
			Dictionary <String ^, double> ^ PEStateVTERM;
			Dictionary <String ^, bool> ^ PEStateInputTermEnable;
			Dictionary <String ^, bool> ^ PEStateHVEnable;
			Dictionary <String ^, bool> ^ PEStateActiveLoadEnable;
			Dictionary <String ^, bool> ^ PEStateDifferentialComparatorEnable;
		};
		array<PEStateSettings>^ PEStateSettingsManager;

		value struct DIO_DMStateSettings
		{
			Dictionary <String ^, double> ^ DIOStateVIH;
			Dictionary <String ^, double> ^ DIOStateVIL;
			Dictionary <String ^, double> ^ DIOStateVOH;
			Dictionary <String ^, double> ^ DIOStateVOL;
			Dictionary <String ^, double> ^ DIOStateIOH;
			Dictionary <String ^, double> ^ DIOStateIOL;
			Dictionary <String ^, double> ^ DIOStateVCH;
			Dictionary <String ^, double> ^ DIOStateVCL;
			Dictionary <String ^, double> ^ DIOStateVTERM;
			Dictionary <String ^, int> ^ DIOStatePinValue;

		};
		array<DIO_DMStateSettings>^ DIO_DMStateSettingsManager;

		///////////////////////////////////////////////////////
		//IOM - PreviousState on Module,Port,Pin
		///////////////////////////////////////////////////////

		array<Dictionary <String ^, int> ^> ^ IOMModuleVIOStateSettingsManager;
		array<Dictionary <String ^, int> ^> ^ IOMPinValStateSettingsManager;
		value struct IOMPortStateSettings
		{
			Dictionary <String ^, int> ^ PortDirection;
			Dictionary <String ^, int> ^ PortValue;

		};
		array<IOMPortStateSettings> ^IOMPortStateSettingsManager;

		///////////////////////////////////////////////////////
		//RF - State Recording								 
		///////////////////////////////////////////////////////

		Dictionary <String^, Dictionary<String^, Object^>^> ^ AmsrfStateSettingsManager;
		Dictionary <int, String ^> ^ TestSiteAmsrfType;
		

		array<Dictionary<String^, String^>^>^ModulationFile;

		value struct CM_RF_SourcePower_StateRecording {
			double SourcePowerPreStatus;
			double SourceFreqPreStatus;
		};
		array<CM_RF_SourcePower_StateRecording>^ SourcePower_Status;


		value struct SourceAlignment_Status {
			bool AMSRF0;
			bool AMSRF1;
		};
		SourceAlignment_Status SourceAlignment_Status;

#pragma endregion "PreviousState DC & RF"

#pragma region "RF-Wlan"

		array<Dictionary <String ^, Task<double>^> ^> ^ EvmAysncTask;
		array<bool>^ ExistEvmTaskList;

		array<Dictionary <String ^, Task<SemMeasOutput^>^> ^> ^ SemAysncTask;
		array<bool>^ ExistSemTaskList;

		value struct EvmAsyncInfo
		{
			array <String^>^ testItemName;
			array <String^>^ testParaName;
			int testParaCount;
			array <double>^ result;
		};
		array<EvmAsyncInfo> ^ EvmAsyncInfoCastResultToTF;

		value struct SemAsyncInfo
		{
			array <String^>^ testItemName;
			array<array<String^>^>^ testParaName;
			int testParaCount;
			array<array<Object^>^>^ result;

			array<array<double>^>^ResultMarginData;
			array<array<double>^>^ ResultSemData;
			array<double>^ ResultPeakReferenceData;
			array<int>^ ResultStatus;
		};
		array<SemAsyncInfo> ^ SemAsyncInfoCastResultToTF;

		Dictionary<String^, array<String^>^> ^ResultDisplaySemAsync;
		array<Dictionary<String^, Object^>^> ^ResultSemAsync;
#pragma endregion "RF-Wlan"

#pragma region "RF-Wolfer"

		value struct WolferInfo
		{
			Dictionary<String^, String^> ^ freqcalFile;
			Dictionary<String^, String^> ^ freqHarcalFile;
			Dictionary<String^, String^> ^ txplFile;
			Dictionary<String^, String^> ^ rxplFile;
			Dictionary<String^, String^> ^ txHarplFile;
			Dictionary<String^, String^> ^ rxHarplFile;
			Dictionary<String^, String^> ^ wolferIOFile;
		};
		array<WolferInfo> ^ WolferInfo_Status;
		Dictionary<String^, array<double>^> ^ freqcal_freq;
		Dictionary<String^, array<double>^> ^ freqcal_pout;
		Dictionary<String^, array<double>^> ^ freqHarcal_freq;

		Dictionary<String^, array<int>^> ^ txPathLoss_TXpath;
		Dictionary<String^, array<double>^> ^ txPathLoss_freq;
		Dictionary<String^, array<double>^> ^ txPathLoss_targetpout;
		Dictionary<String^, array<int>^> ^ txPathLoss_outIndex;
		Dictionary<String^, array<double>^> ^ txPathLoss_actualpout;
		Dictionary<String^, array<double>^> ^ txPathLoss_couppout;
		Dictionary<String^, array<double>^> ^ txPathLoss_source;

		Dictionary<String^, int> ^ g_txpath;
		Dictionary<String^, int> ^ g_rxpath;
		Dictionary<String^, String^> ^ g_SelectTxPath;
		Dictionary<String^, String^> ^ g_SelectRxPath;
		Dictionary<String^, int> ^ outIndex;

		/*value struct WolferCoupler_Info {
			double Pout;
			double Pref;
		};
		array<WolferCoupler_Info> ^ WolferCoupler_Data;*/

		array<double> ^ WolferCoupler_Pout;

		//bool sw_wlfout;
		Dictionary<String^, int> ^ freq_count;
		Dictionary<String^, int> ^ txpl_count;
		//int cf_count;
		Dictionary<String^, int> ^ rxpl_count;
		Dictionary<String^, int> ^ rxrlpl_count;
		Dictionary<String^, int> ^ txrlpl_count;
		Dictionary<String^, int> ^ freqHar_count;
		Dictionary<String^, int> ^ txpl_Har_count;
		Dictionary<String^, int> ^ rxpl_Har_count;
		//double rxpl1;
		//double rxpl2;
		//double rxpl3;

#pragma endregion "RF-Wolfer"

#pragma region "DM Vector"

		array <List<Dictionary<String^, double>^>^>^ DPinLevelSet;


		///////////////////////////////////////////////////////
		//Vector
		///////////////////////////////////////////////////////
		String ^ VectorFileDirectory;
		Dictionary <String ^, int> ^ VectorSetNumber;
		array<array<double>^>^ TimingSetPeriod;
		array <List<Dictionary<String^, bool>^>^>^ PEAttributeSet;
		value struct VectorFileManagement
		{
			Dictionary<String^, int> ^ DM_DPinGroup;
			Dictionary<String^, int> ^ SCLKChannel;
			Dictionary<String^, int> ^ SDATAChannel;
			Dictionary<String^, int> ^ VectorTimingSet;
			Dictionary<String^, int> ^ l_Read_Operation_Counter;
			Dictionary<int, array<String^>^> ^ l_Start_Read_Location_Speed;
			Dictionary<int, array<int>^> ^ l_Start_Read_Location_Single_VectorFile;
		};
		array<VectorFileManagement> ^ VectorFileManager;

		///////////////////////////////////////////////////////
		//DIO						 
		///////////////////////////////////////////////////////



#pragma endregion "DM Vector"

#pragma region "Test Result"

		///////////////////////////////////////////////////////
		//Dictionary & Storage for Result
		///////////////////////////////////////////////////////
		array<array<Object^>^>^ TestResults;
		array<Dictionary<String ^, Object^>^>^ GlobalResult;// Key:TestItemName Value:Result

															///////////////////////////////////////////////////////
															//DataType Result
															///////////////////////////////////////////////////////
		value struct techFlowDataType {
			int	IntTypeResult;
			bool BoolTypeResult;
			double DoubleTypeResult;
			String ^ StringTyperesult;
		};
		array <techFlowDataType> ^ ResultType;

		///////////////////////////////////////////////////////
		//Fixed Offset 
		///////////////////////////////////////////////////////
		Dictionary <String ^, array<double> ^> ^ ResultOffset;

#pragma endregion "Test Result"

#pragma region "ResourceModule"

		value struct ResourceManagement
		{
			array<String ^>^ RsrcSMU;
			array<String ^>^ RsrcACM;
			array<String ^>^ RsrcDM;
			array<String ^>^ RsrcCM;
			array<String ^>^ RsrcIOM;
			array<String ^>^ RsrcTMU;
			array<ResourceManager ^>^ RsrcMngr;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	CM400 Series Module Alias & Pin Alias
			**	----------------------------------------------------------------------------------------------------
			*/
			int cmModuleCount;
			array<String^, 2> ^ moduleAlias_CM_PinMapName;
			array<String^, 2> ^ moduleAlias_CM_Address;
			array<bool, 2> ^ hardwareStatus_CM;
			int cmPinCount;
			array<String^, 2> ^ pinAlias_CM_PinMapName;
			array<String^, 2> ^ pinAlias_CM_Address;
			array<String^, 2> ^ pinAlias_CM_HwResourceAlias;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	AM400 Series Module Alias & Pin Alias
			**	----------------------------------------------------------------------------------------------------
			*/
			int amModuleCount;
			array<String^, 2> ^ moduleAlias_AM_PinMapName;
			array<String^, 2> ^ moduleAlias_AM_Address;
			array<bool, 2> ^ hardwareStatus_AM;
			int amPinCount;
			array<String^, 2> ^ pinAlias_AM_PinMapName;
			array<String^, 2> ^ pinAlias_AM_Address;
			array<String^, 2> ^ pinAlias_AM_HwResourceAlias;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	DM400 Series Module Alias & Pin Alias
			**	----------------------------------------------------------------------------------------------------
			*/
			int dmModuleCount;
			array<String^, 2> ^ moduleAlias_DM_PinMapName;
			array<String^, 2> ^ moduleAlias_DM_Address;
			array<bool, 2> ^ hardwareStatus_DM;
			int dmPinCount;
			array<String^, 2> ^ pinAlias_DM_PinMapName;
			array<String^, 2> ^ pinAlias_DM_Address;
			array<String^, 2> ^ pinAlias_DM_HwResourceAlias;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	IOM400 Series Module Alias & Pin Alias
			**	----------------------------------------------------------------------------------------------------
			*/
			int iomModuleCount;
			array<String^, 2> ^ moduleAlias_IOM_PinMapName;
			array<String^, 2> ^ moduleAlias_IOM_Address;
			array<bool, 2> ^ hardwareStatus_IOM;
			int iomPinCount;
			array<String^, 2> ^ pinAlias_IOM_PinMapName;
			array<String^, 2> ^ pinAlias_IOM_Address;
			array<String^, 2> ^ pinAlias_IOM_HwResourceAlias;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	ACM400 Series Module Alias & Pin Alias
			**	----------------------------------------------------------------------------------------------------
			*/
			int acmModuleCount;
			array<String^, 2> ^ moduleAlias_ACM_PinMapName;
			array<String^, 2> ^ moduleAlias_ACM_Address;
			array<bool, 2> ^ hardwareStatus_ACM;
			int acmPinCount;
			array<String^, 2> ^ pinAlias_ACM_PinMapName;
			array<String^, 2> ^ pinAlias_ACM_Address;
			array<String^, 2> ^ pinAlias_ACM_HwResourceAlias;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	TM400 Series Module Alias & Pin Alias
			**	----------------------------------------------------------------------------------------------------
			*/
			int tmModuleCount;
			array<String^, 2> ^ moduleAlias_TM_PinMapName;
			array<String^, 2> ^ moduleAlias_TM_Address;
			array<bool, 2> ^ hardwareStatus_TM;
			int tmPinCount;
			array<String^, 2> ^ pinAlias_TM_PinMapName;
			array<String^, 2> ^ pinAlias_TM_Address;
			array<String^, 2> ^ pinAlias_TM_HwResourceAlias;
		};
		ResourceManagement RsrcManager;

#pragma endregion "ResourceModule"

#pragma region "Logger"

		///////////////////////////////////////////////////////
		//Logger
		///////////////////////////////////////////////////////
		value struct FileLoggerStruct
		{
			FileLogger^ FileLgr;
			FileLogger^ datFileLgr;
			FileLogger^ batFileLgr;
			FileLogger^ iniFileLgr;
			FileInfo ^ fi;
			// Usage: 
			// 1. tl->FileLogger.traceMessage = "traceFormatData->totalFreqPoints: " + traceFormatData->totalFreqPoints.ToString();
			// 2. tl->FileLogger.debugFileLgr->WriteToFile("traceFormatData_Thread.txt", tl->FileLogger.traceMessage, LOGGER_CONST_APPEND);
			bool IsWarning;
			int LoggerType;
			String ^ FileNameDebugLog;
			String ^ FileNameWarningLog;
			String ^ LogMessage;
			String ^ traceMessage;
		};
		FileLoggerStruct FileLog;

		///////////////////////////////////////////////////////
		//Tracer Logger
		///////////////////////////////////////////////////////
		value struct TracerLoggerStruct
		{
			static double PrefixValue = 1.0;
			static int CountNumber;
			static bool IsInfinity;
			static int UnloadCount;
			static String^ ContLog;
			static String^ LogMssg;
			static String^ TracerMessage;
			static TracerLogger^ TracerLog;
			static String ^ Messages;
			static int  ErrorCode;
			static String ^ GlobalErrorMessage;
			static String ^ StackTrack;
			static bool IsWarningMessage = false;
			static String^ InfoMssg = "[INFO]";
			static String^ ErrorMssg = "[ERROR]";
			static String^ WarningMssg = "[WARNING]";
			static String^ TracerWarningTabName = "WARNING";
			static String^ TracerExceptionTabName = "EXCEPTION";
			static String^ TracerLoadPhaseTabName = "LOAD PHASE";
			static String^ TracerTestPhaseTabName = "TEST PHASE";
			static String^ TracerUnloadPhaseTabName = "UNLOAD PHASE";
			static String^ TracerTabNamePhysicalSite;
			static int tracerMainTab = 999;
		};
		TracerLoggerStruct TcrLgr;

#pragma endregion "Logger"

#pragma region "Date & Time"

		///////////////////////////////////////////////////////
		//DateTime 
		///////////////////////////////////////////////////////
		String ^ TimeNow;
		//static DateTime TimeNow = DateTime::Now;
		//static String ^ TraceTime = TimeNow.Year + "/" + TimeNow.Month + "/" + TimeNow.Day + " " + TimeNow.ToString("h:mm:ss tt");
		//static String ^ SWTraceTime = TimeNow.Year + "." + TimeNow.Month + "." + TimeNow.Day + "_" + TimeNow.ToString("h.mm.sstt");
		String ^ S3P_TimeNow;
		static String ^ FileNameTime = DateTime::Now.ToString("yyyy.MM.dd'_'h.mm.ss.tt");

#pragma endregion "Date & Time"

#pragma region "Test Item and Parameter properties"

		value struct TestPropertyStruct {
			bool DebugEnable;

			Dictionary <String ^, String ^> ^ TestParaNameWithSiteIndex;
			Dictionary <String ^, String ^> ^ TestParaDisplayNameWithSiteIndex;
			Dictionary<String^, Object^> ^ TestResults;

			// Sub Item
			String ^ ControlItemName;
			String ^ FlowItemName;

			// Test Item
			String^ TestItemName;
			String ^ TestItemDisplayName;

			// Sub Item (Test Step, Control Step, Test Parameter) 
			int totalSubItem;
			array<Type^> ^ SubFlowItemTypeId;								// Typeid for each flow sub-items in a test item | SubFlowItemTypeId = ControlStep::typeid or TestStep::typeid or TestParameter::typeid 

			// Test Parameter
			int TotalTestParameter;
			array<String ^> ^ TestParameterName;
			array<String ^> ^ TestParameterDisplayName;
			array<Type^> ^ TestParameterTypeId;								// Typeid for test parameter item
			Dictionary<String^, bool> ^ TestParameterExecuted;				// Set true when the item has been executed, else false
			array<int> ^ TestParameterTestStatus;							// 0 = Fail | 1 = Pass 
			Dictionary<String^, bool> ^ TestParameterUpdateResStatus;		// False = Pending to update result to techFlow | True = Update test result to techFlow
			array<bool> ^ IsCurrentTPBypassed;	//Curernt Test Parameter by-pass status with siteIndex 

			// Flow Step (Control Step, Test Step)
			int totalFlowStep;
			array<String^> ^ FlowStepItemName;
			array<String^> ^ FlowStepItemDisplayName;
			array<bool> ^ FlowStepItemExecuted;

			String^ MethodName;

		};
		array <TestPropertyStruct> ^ TestProperty;

		value struct techFlowDataType_TC {
			int	IntTypeTC;
			bool BoolTypeTC;
			double DoubleTypeTC;
			String ^ StringTypeTC;
		};
		techFlowDataType_TC TC_type;

		value struct TestProperty_tf {
			int TC_count;
			bool IsCI;
			String ^ TCond;
			String ^ TI_Name;
			String ^ CI_Name;
			array<String ^> ^ TP_Name;
			int TotalTestParameter;
			Dictionary <String ^, String ^> ^ TC_dict;
		};
		array <TestProperty_tf> ^ TProperty;

		///////////////////////////////////////////////////////
		//Test Parameter Properties
		///////////////////////////////////////////////////////
		array<String^>^ tp_TestParameter;

		Dictionary <String^, String^> ^ TestNameWithTestNumber;
		Dictionary <String ^, String ^> ^ tp_TestItem;
		Dictionary <String ^, String ^> ^ tp_TestNumber;
		Dictionary <String ^, String ^> ^ tp_TestLimitLo;
		Dictionary <String ^, String ^> ^ tp_TestLimitHi;
		Dictionary <String ^, String ^> ^ tp_UnitPrefix;
		Dictionary <String ^, String ^> ^ tp_Units;
		Dictionary <String ^, String ^> ^ tp_DataType;
		Dictionary <String ^, String ^> ^ tp_EvalMode;
		Dictionary <String ^, String ^> ^ tp_BinName;
		Dictionary <String ^, String ^> ^ tp_HBin;
		Dictionary <String ^, String ^> ^ tp_SBin;
		Dictionary <String ^, int> ^ tp_Bypass;

		Dictionary <String ^, String ^> ^ tp_FTLimitLo;
		Dictionary <String ^, String ^> ^ tp_FTLimitHi;
		Dictionary <String ^, String ^> ^ tp_QALimitLo;
		Dictionary <String ^, String ^> ^ tp_QALimitHi;

#pragma endregion "Test Item and Parameter properties"

#pragma region "TechFlow Property"

		value struct techFlowProperty {
			
			/*
			**	----------------------------------------------------------------------------------------------------
			**	GetTechFlowSiteProperty
			**	----------------------------------------------------------------------------------------------------
			*/
			int StageCount;										// Identify single site / true parallel / index parallel project
			int TestHead;										// TF test head
			int TestSite;										// TF test site
			int TotalUUTOffsets;								// Total UUTOffset site count
			int TotalTestSite;									// Total tF test site in a project
			int NumberOfTestSites;								// For the ForLoop termination parameter usage, to handle between single site, multiple site, uutoffset
			bool SharedVNA;										//
			int activeUUT_count;
			array<bool>^ arr_activeUUT;
			
			/*
			**	----------------------------------------------------------------------------------------------------
			**	GetTechFlowProjectType
			**	----------------------------------------------------------------------------------------------------
			*/
			int ProjectType;									// TF project type, eg: single site single uut / single site multi uut / true parallel single uut / true parallel multi uut		

			/*
			**	----------------------------------------------------------------------------------------------------
			**	GetTechFlowFilePathProperty
			**	----------------------------------------------------------------------------------------------------
			*/
			String ^ RecipeFileName;
			String ^ ProfileName;								// eg: SampleProfile / ALP / ...
			String ^ ProjectName;								// TF Project Name
			String ^ DeviceName;								// TF Device Name
			String ^ DeviceRevision;							// TF Device Revision
			String ^ ProgramName;								// TF Program Name
			String ^ ProgramRevision;							// TF Program Revision
			String ^ HandlerPathDirectory;						// C:\Aemulus\techFlow3\Projects\Handlers
			String ^ PSRecipePathDirectory;						// C:\Aemulus\techFlow3\Projects\PSRecipes\SampleProfile\ProjectName
			String ^ TestProgramPathDirectory;					// C:\Aemulus\techFlow3\Projects\TestProgramsSampleProfile\ProjectName
			String ^ RecipeFilePathDirectory;					// C:\Aemulus\techFlow3\Projects\TestRecipesSampleProfile\ProjectName
			String ^ VSProjectPathDirectory;					// C:\Aemulus\techFlow3\Projects\VSProjectsSampleProfile\ProjectName\ProjectName

			int TPropertyTotalSite;
			int NumberOfSites;			//Physical Test Sites  
			bool JumpOnFail;
			String^ CurrentPhase;
			bool _RTPlotter;
			bool RTDataScope;
			bool unloadRTPlotter;
			String ^ plotterPath;
			array<bool> ^ isRunTest;

			/*
			**	----------------------------------------------------------------------------------------------------
			**	GetTechFlowBinningProperty
			**	----------------------------------------------------------------------------------------------------
			*/
			int SoftBinCount;									// To count total number of SoftBin from techFlow
			int HardBinCount;									// To count total number of HardBin from techFlow
			array<int>^ arr_HBin;								// To store value of HardBin for each SoftBin
			array<String^>^ str_arrHBin;						// To store HardBin value as String (for folder path use)
			String ^ G_LotId;
			String ^ G_TestCode;
			bool create_S2PpathByBin_flag = false;

			//放在load中，获取所有的testparameter对应的Hbin信息
			Dictionary <String^, int> ^ TiTpRule_by_HBin;

			//放在SaveToTouchstoneFile方法中，获取每一个料保存时，保存的S2P文件 对应的testitem信息
			Dictionary <String^, String^> ^ Ti_by_S2PFilename;

			//放在commitresult方法里，保存分bin文件夹的路径，包含bin1.1文件夹
			Dictionary <String^, String^> ^ BinString_by_BinPath;
			/*
			**	----------------------------------------------------------------------------------------------------
			**	Other General
			**	----------------------------------------------------------------------------------------------------
			*/

		};
		techFlowProperty tf;

#pragma endregion "TechFlow Property"

		bool JumpOnFail;

		array<int>^ RunTimeErrorCode;

		array<bool>^ isPreviewPass;
		array<bool>^ runTimeError;
		array<bool>^ dcRunTimeError;
		array<bool>^ isCriticalBinFail;
		array<bool>^ RunTimeError;

		array<String ^>^ OnFailExcuteFlowItem;
		array<String ^>^ OnPassExcuteFlowItem;
		array<String^>^ RunTimeErrorMessage;
		array<Dictionary<String^, double>^>^boardLoss;

#pragma region "BoardLossFileFolder Folder Property"

		value struct BoardLossFileFolderProperty
		{
			String ^ BoardLossFileFolderDirectory;						// Reserved for 'BoardLossFileFolder' folder path directory. Example: BoardLossFileFolder
			String ^ BoardLossFileDirectory;							// Reserved for 'BoardLoss_TesterID_Sx.csv' file patt directory. Example: BoardLoss_TesterID_S0.csv, BoardLoss_TesterID_S1.csv

			array<int> ^ index;											// BoardLoss file content 'Index'
			array<String^> ^ hardwarePath;								// BoardLoss file content 'HardwarePath'
			array<array<double>^> ^ factorValue;						// BoardLoss file content 'S0/S1/S2/...' boardloss factor
			String ^ BoardLossFileVersion;								// BoardLoss file header 'BoardLoss File Version'

			bool isCreateNewBoardLossFile;								// To determine whether to generate a new BoardLoss_TesterID_Sx.csv file

			Dictionary<String^, array<double>^> ^ BoardLossFactor;		// Global BoardLoss factor, to be called when necessary
		};
		BoardLossFileFolderProperty BoardLoss;

#pragma endregion

#pragma region "DeviceStateFileTemplate Folder Property"

		value struct DeviceStateFileTemplateProperty
		{
			String ^ DeviceStateFileTemplateDirectory;					// Reserved for 'DeviceStateFileTemplate' folder path directory. Example: DeviceStateFileTemplate

			int totalStateFileExist;									// Total number of state file exist inside the folder (.sta type)
			int totalMappingFileExist;									// Total number of mapping file exist inside the folder (.xml type)

			String ^ stateFileDirectory_sta;							// State file path directory (.sta type)
			String ^ stateFileDirectory_csa;							// State file path directory (.sta type)
			String ^ mappingFileDirectory;								// Mapping file path directory (.xml type)

			bool isDeviceStateFileTemplateStateFIleInvalid;				// To determine whether the state file is valid inside the 'DeviceStateFileTemplate' folder
			bool isDeviceStateFileTemplateMappingFileInvalid;			// To determine whether the mapping file is valid inside the 'DeviceStateFileTemplate' folder
		};
		DeviceStateFileTemplateProperty DeviceStateFileTemplate;

#pragma endregion

#pragma region "FixedOffsetFileFolder Folder Property"

		value struct FixedOffsetFileFolderPorperty
		{
			String ^ FixedOffsetFileFolderDirectory;					// Reserved for 'FixedOffsetFileFolder' folder path directory. Example: FixedOffsetFileFolder
			String ^ FixedOffsetFileDirectory;							// Reserved for 'FixedOffset_TesterID_Sx.csv' file patt directory. Example: FixedOffset_AMB73001_S0.csv, FixedOffset_AMB73001_S1.csv

			array<int> ^ index;											// FixedOffset file content 'Index'
			array<String^> ^ testItem;									// FixedOffset file content 'Test Item'
			array<String^> ^ testParameter;								// FixedOffset file content 'Test Parameter'
			array<array<double>^> ^ offsetValue;						// FixedOffset file content 'S0/S1/S2/...' offset value
			String ^ OffsetFileVersion;									// FixedOffset file header 'Offset File Version'

			bool isCreateNewFixedOffsetFile;							// To determine whether to generate a new FixedOffset_TesterID_Sx.csv file

																		//Dictionary<String^, array<double>^> ^ ResultOffset;			// Global fixed offset factor, to be called when update result to techFlow

			Dictionary<String^, double> ^ ResultOffset;			// Global fixed offset factor, to be called when update result to techFlow
		};
		FixedOffsetFileFolderPorperty FixedOffset;

#pragma endregion

#pragma region "ModulationFileFolderSiteX Folder Property"

		value struct ModulationFileFolderPorperty
		{
			String ^ ModulationFileFolderDirectory;						// Reserved for 'ModulationFileFolderSite"X"' folder path directory. Example: ModulationFileFolderSite0, ModulationFileFolderSite1

			int totalAwfTypeFileExist;									// Total number of modulation file exist inside the folder (.awf type)
			int totalWfmTypeFileExist;									// Total number of modulation file exist inside the folder (.wfm type)

			array<String^> ^ awfTypeFilePathList;						// Modulation file path directory (.awf type)
			array<String^> ^ wfmTypeFilePathList;						// Modulation file path directory (.wfm type)

			array<String^> ^ awfTypeFileName;							// Modulation file name (.awf type)
			array<String^> ^ wfmTypeFileName;							// Modulation file name (.wfm type)
		};
		ModulationFileFolderPorperty ModulationFileProperty;

#pragma endregion

#pragma region "VectorFileFolderSiteX Folder Property"

		value struct VectorFileFolderPorperty
		{
			String ^ VectorFileFolderDirectory;						// Reserved for 'VectorFileFolderSite"X"' folder path directory. Example: VectorFileFolderSite0, VectorFileFolderSite1

			int totalVecFileExist;										// Total number of vector file exist inside the folder (.vec type)
			array<String^> ^ vecFilePathList;							// Vector file path directory
			array<String^> ^ vecFileName;								// Vector file name
			array<int> ^ vecFileNumber;									// Vector file number. Example: 0,1,2,3,4,5,...
		};
		VectorFileFolderPorperty VectorFile;

#pragma endregion

#pragma region "VectorStateFileFolderSiteX Folder Property"

		value struct VectorStateFileFolderPorperty
		{
			String ^ VectorStateFileFolderDirectory;				// Reserved for 'VectorStateFileFolderSite"X"' folder path directory. Example: VectorStateFileFolderSite0, VectorStateFileFolderSite1

			int totalVecStateFileExist;									// Total number of vector state file exist inside the folder (.csv type)
			array<String^> ^ vecStateFilePathList;						// Vector state file path directory
			array<String^> ^ vecStateFileName;							// Vector state file name
			array<int> ^ vecStateFileNumber;							// Vector state file number. Example: 0,1,2,3,4,5,...
		};
		VectorStateFileFolderPorperty VectorStateFile;

#pragma endregion

#pragma region "AppsCalFileFolder Folder Property"

		value struct AppsCalFileFolderPorperty
		{
			String ^ AppsCalFileFolderDirectory;					// Reserved for 'AppsCalFileFolder' folder path directory. Example: AppsCalFileFolder
			String ^ AppsCalFileDirectory;							// Reserved for 'AppsCal_TesterID_Sx.csv' file patt directory. Example: AppsCal_AMB73001_S0.csv, AppsCal_AMB73001_S1.csv

			array<int> ^ ChannelIndex;											// AppsCal file content 'Index'
			array<double> ^ TargetPout;									// AppsCal file content 'Test Item'
			array<array<double>^> ^ offsetValue;						// AppsCal file content 'S0/S1/S2/...' offset value
			String ^ OffsetFileVersion;									// AppsCal file header 'Offset File Version'

			bool isCreateNewAppsCalFile;							// To determine whether to generate a new AppsCal_TesterID_Sx.csv file

																	//Dictionary<String^, array<double>^> ^ ResultOffset;			// Global fixed offset factor, to be called when update result to techFlow

			Dictionary<String^, double> ^ AppsCalFactor;			// Global fixed offset factor, to be called when update result to techFlow
		};
		AppsCalFileFolderPorperty AppsCalFile;

#pragma endregion

#pragma region "Test Parameter DataType Property"

		value struct TestParameterDataTypeProperty
		{
			String ^ StringTyperesult;
			Int16 Int16TypeResult;
			Int32 Int32TypeResult;
			Int64 Int64TypeResult;
			float FloatTyperesult;
			double DoubleTypeResult;
			bool BoolTypeResult;
			UInt16 UInt16TypeResult;
			UInt32 UInt32TypeResult;
			UInt64 UInt64TypeResult;
			int	IntTypeResult;
			unsigned int UIntTypeResult;
		};
		array<TestParameterDataTypeProperty> ^ ResultWithDataType;

#pragma endregion

#pragma region "Flow Variable Property"

		value struct FlowVariablesProperty
		{
			bool AssemblyResolver;								// Set True to perform assembly resolve if the loading of.dll / .exe turns out to be unsucessfull due to different DLL Encryptor used for encryption, else False to by-pass the Assembly Resolve via current domain event handler.
		};
		FlowVariablesProperty FLOWVAR;

#pragma endregion

	};
}


/*----------------------------------------------------------------------
* Revision Log
* $Log: Globals.h.rca$

*** Version	: v1.1.0.0
*** Date	: 12 August 2026
*** PIC		: Tham Zhi Kean
* Merge AMB7600 Test Library with AMB7300 Test Library

*** Version	: v1.0.0.5
*** Date	: 4 April 2025
*** PIC		: Tham Zhi Kean
* Add arr_activeUUT
* Add AWV for HighPwrTest, Mutex & PortMatchingX variables

*** Version	: v1.0.0.4
*** Date	: 18 February 2025
*** PIC		: Tham Zhi Kean
* Added UseGenericStateFileMappingFile in AWV
* Added S2P_rename & snpFileName
* Modified FixedOffset.ResultOffset datatype from array<double>^ to double

*** Version	: v1.0.0.3
*** Date	: 13 January 2025
*** PIC		: Tham Zhi Kean
* Added AppWideVariablesProperty variables

*** Version	: v1.0.0.2
*** Date	: 9 April 2024
*** PIC		: Ng Chen Yang
* Added S2Ppath AppWideVariable as global variable.

*** Version	: v1.0.0.1
*** Date	: 31 March 2023
*** PIC		: Ng Chen Yang
* Support SkySemi special BW by detecting "SkySemi" at Analysis_Setting.
* Support for the CSA/STA state file template depends on the VNA model.
* Support specific SaveSnpFilePath entered by users. Pass the file path to AppWideVariable "S2Ppath"

*** Version	: v1.0.0.0
*** Date	: 31 December 2022
*** PIC		: Ooi Jing Yao
* Initial release version.
----------------------------------------------------------------------*/