/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			Globals.h
Purpose:		Defines common global variables.
UUTOffset:		Supported.
----------------------------------------------------------------------*/
#pragma once

#include <windows.h>
#include <math.h>
#include <iostream>
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

#pragma region "General"

		array<String^> ^ currentSubItemName;
#pragma endregion

#pragma region "App Wide Variables "

		///////////////////////////////////////////////////////
		//App Wide Variables 
		///////////////////////////////////////////////////////
		value struct AppWideVariablesStruct
		{
			int Debug;
			bool Offline;
			String ^ DeviceName;
			int CalibrationMode;
			int BoardLossMode;
			double PowerLineFreq;
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

#pragma region "Tester General Info"

		///////////////////////////////////////////////////////
		//Global variables - be able to identify 
		///////////////////////////////////////////////////////
		String ^ TesterId;
		String ^ currentFlowName;
		//String ^ currentSubItemName;

#pragma endregion "Tester General Info"

#pragma region "ResourceModule"

		String ^ HardwareProfile;

		value struct ResourceManagement
		{
			array<String ^>^ RsrcSMU;
			array<String ^>^ RsrcACM;
			array<String ^>^ RsrcDM;
			array<String ^>^ RsrcCM;
			array<String ^>^ RsrcIOM;
			array<String ^>^ RsrcTMU;
			array<ResourceManager ^>^ RsrcMngr;
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
			// Usage: 
			// 1. tl->FileLogger.traceMessage = "traceFormatData->totalFreqPoints: " + traceFormatData->totalFreqPoints.ToString();
			// 2. tl->FileLogger.debugFileLgr->WriteToFile("traceFormatData_Thread.txt", tl->FileLogger.traceMessage, LOGGER_CONST_APPEND);
			bool IsWarning;
			int LoggerType;
			String ^ FileNameDebugLog;
			String ^ FileNameWarningLog;
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
		};
		TracerLoggerStruct TcrLgr;

#pragma endregion "Logger"

#pragma region "Date & Time"

		///////////////////////////////////////////////////////
		//DateTime 
		///////////////////////////////////////////////////////

		static DateTime TimeNow = DateTime::Now;
		static String ^ TraceTime = TimeNow.Year + "/" + TimeNow.Month + "/" + TimeNow.Day + " " + TimeNow.ToString("h:mm:ss tt");
		static String ^ SWTraceTime = TimeNow.Year + "." + TimeNow.Month + "." + TimeNow.Day + "_" + TimeNow.ToString("h.mm.sstt");

#pragma endregion "Date & Time"

#pragma region "Test Item and Parameter properties"

		value struct TestPropertyStruct {
			bool DebugEnable;

			Dictionary <String ^, String ^> ^ TestParaNameWithSiteIndex;
			Dictionary <String ^, String ^> ^ TestParaDisplayNameWithSiteIndex;

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

		///////////////////////////////////////////////////////
		//Misc
		///////////////////////////////////////////////////////

		value struct techFlowProperty {
			int TPropertyTotalSite;
			int StageCount;
			int TestSite;
			int TestHead;
			int TotalUUTOffsets;		//UUTOffset Sites
			int NumberOfSites;			//Physical Test Sites  
			bool JumpOnFail;
			String^ CurrentPhase;
			String ^ RecipeFilePathDirectory;
			String ^ RecipeFileName;
			String ^ ProfileName;
			String ^ ProjectName;
			String ^ ProgramName;
			bool _RTPlotter;
			bool RTDataScope;
			bool unloadRTPlotter;
			String ^ plotterPath;
			array<bool> ^ isRunTest;
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

	};


}


/*----------------------------------------------------------------------
* Revision Log
* $Log: Globals.h.rca$


* v1.0.0.0 (20 March 2020), LKL
* Initial release version.
----------------------------------------------------------------------*/