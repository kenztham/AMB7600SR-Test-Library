/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			TestFunction.h
Purpose:		Declare all test functions.
UUTOffset:		Supported.
Version:		v1.2.0.0
----------------------------------------------------------------------*/

#pragma once

#include <windows.h>
#include "Enum.h"
#include "Globals.h"
#include "Defines.h"
#include "TF-Macro.h"

//Support Kill Process Function 
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <fstream>
//#using "C:\Aemulus\techFlow3\bin\x64\Aemulus.TestLib.Utility.dll" 

using namespace System;
using namespace System::IO;
using namespace System::IO::MemoryMappedFiles;
using namespace System::Text;
using namespace System::Net;
using namespace System::Xml;
using namespace System::Reflection;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Windows::Forms;
using namespace System::Runtime::Remoting;
using namespace System::Collections::Generic;
using namespace System::Collections::Concurrent;
using namespace System::Runtime::InteropServices;

using namespace Aemulus::Hardware;
using namespace Aemulus::Tech::Flow;
using namespace Aemulus::Tech::Flow::Result;
using namespace Aemulus::TestLib::Utility;
using namespace Aemulus::Tech::Flow::ProductionSystem;
using namespace Aemulus::WaferTestLibrary;

namespace Functions
{
	public ref class TestFunction
	{
	public:

		//Instanstiate Utilities 
		Aemulus::TestLib::Utility::Utilities ^ Util;
		//Instanstiate Logger
		Aemulus::TestLib::Utility::FileLogger^ FileLog;

		TestFunction();
		~TestFunction(void);

#pragma region "Globals.cpp"

		Globals^ glob;

		// Barrier
		BaseBarrierCollections^ barrier;

		int InitializeProgram(Site ^ site);
		void ResetGlobalResult(int TotalSite);
		void InitializeGlobalVariables(Site^ site);
		void ResetGlobalVariables(Site^ site);
		void InitializeGlobalResult(int TotalSite);
		int LoadGenericAppsWideVariable(Site^ site);
		void IsRunTest(Site^ site, array<bool>^ RunTest);
		void ThreadingInfo(Site^ site, bool RF_ResourceNeeded);
		Object ^  GetGlobalResult(String^ Identifier, int siteIndex);
		void SetGlobalResult(String ^ Identifier, int siteIndex, double Result);

		/*
		**	----------------------------------------------------------------------------------------------------
		**	Tester ID
		**	----------------------------------------------------------------------------------------------------
		*/
		void GetTesterID(Site ^ site, int tfSite);

#pragma endregion "Globals.cpp"
		
#pragma region "Diagnostic"

		void TestCondCheckingDataType(String^ item, DataType var, DataType TC_DataType_Casting);
		//int AppErrorCodeChecking(String^ testCondName, String^ message);

		void ErrorHandling(Site ^ site, int siteIndex, String^ methodName, String ^ ErrorMessage);
		void ErrorHandling(Site ^ site, int siteIndex, String^ methodName, Exception ^ Ex);
		void ErrorHandling(Site ^ site, int siteIndex, String ^ ErrorMessage);
		void ErrorHandling(Site ^ site, String ^ ErrorMessage);

		//Tracer Logging and Logging Functions
		int InitializeTracerLogger(Site ^ site, int tfSite);
		void WRITETOTRACERLOGGER(int tfSite, int siteIndex, String ^ messageType, String ^ message, int programLineNumber, String ^ programFileName, String ^ programFunctionName);
#define WriteToTracerLogger(tfSite, siteIndex, messageType, message) WRITETOTRACERLOGGER(tfSite, siteIndex, messageType, message, __LINE__, __FILE__, __FUNCTION__);
		void WriteToTcrLgr(String ^ TracerTabName, String ^ LogMessage);
		int UninitializeTracerLogger();

		int InitializeFileLogger(int tfSite);
		void WRITETOFILELOGGER(int tfSite, int siteIndex, String ^ messageType, String ^ message, int programLineNumber, String ^ programFileName, String ^ programFunctionName);
#define WriteToFileLogger(tfSite, siteIndex, messageType, message) WRITETOFILELOGGER(tfSite, siteIndex, messageType, message, __LINE__, __FILE__, __FUNCTION__);
		void WriteToFileLgr(String ^ fileDirectory, String ^ message);
		int UninitializeFileLogger();

		void WriteToLoggerTotalSite(String ^ LogMessage);
		//void FileLogging(int siteIndex, String^ MssgType, String ^ LogMessage);
		//int TRACERLOGGING(int siteIndex, String ^ LogMessage, int LogLineNumber, String ^ FileName);

		//Check Error Functions
		int CHECKERROR(int siteIndex, int errorCode, int ErrorLineNumber, String^ FileName);
#define CheckError(siteIndex, errorCode) CHECKERROR(siteIndex, errorCode, __LINE__, __FILE__);

		void WarningMessageBox(String^ MssgContent, String^ WarningMssgType);

#pragma endregion "Diagnostic"

#pragma region "Files"

		String ^ GetFileNameFromFullPathName(String ^ FullPathName);

		//Apps Calibration Functions
		bool IsRunningProduction(Site^ site);

		//CorrFactor & Offset
		ConcurrentDictionary <String ^, double> ^ ResultOffset;

		
		value struct corrFactor
		{
			//Apps Wide Variable
			int gCalibrationMode;
			int gAutoGuCalibrationSetup;
			int gCreateCorrfactorFile;
			int gCorrFactorFileMode;
			String^ gCustomCorrFactorPath;

			String^ projectName;
			String^ programName;
			String^ recipeFilePath;

			//CorrFactor
			String^ corrFactorFolder;
			String^ corrFactorFile;	
			String^ corrFactorEmptyFolder;
			String^ corrFactorEmptyFile;

			//TesterInfo/GU_Cal
			String^ corrfactorTesterInfoGUCalPath;
			String^ corrFactorTesterInfoGUCalFile;
			String^ referenceTesterInfoGUCalFile;

			//Test Recipe
			String^ corrFactorTestRecipePath;
			String^ corrFactorTestRecipeFile;
			String^ referenceTestRecipeFile;

			//Custom Folder
			String^ corrFactorCustomPath;
			String^ corrFactorCustomFile;

			int totalTestParameterCount;
			int totalTestSiteCount;

			int totalFactor;
			int totalSite;
			int techflowSite;
			int techflowHead;
			String^ testerID;

			array<String^>^ corrFileTesterID;
			array<double, 2> ^ CorrFactor;
			array<int> ^ index;
			array<String^>^ testParameter;

			DateTime ^ dateTimeInit;
			DateTime ^ dateTimeNow;

		};
		corrFactor cf;

		array<double, 2> ^ CorrFactor;

		void corrFactorFileInit(Site ^ site);
		void corrFactorFileCreate(Site ^ site);
		void corrFactorLoad(Site ^ site);
		double GetCorrFactor(String^ TPName, int testSite);
		void boardLossFileInit(Site^ site);
		void boardLossFileLoad(Site^ site);
#pragma endregion "Files"

#pragma region "techFlow"

		bool IsNum(String^ value);
		int BypassTests(Site^ site);
		int UpdateTestLimit(Site^ site);
		int BypassTestItems(Site^ site);
		bool IsAlphaNum(String^ value);
		int UpdateTestNumber(Site^ site);
		int UpdateTestParameterDescription(Site^ site);
		void KillProcessByName(const char * exeName);
		void UpdateTestProperty(Site^ site, int siteIndex);
		int Update_Test_Property(Site^ site, int siteIndex);
		void InitializeTestCondProperty(void);
		bool IsTPResultFailed(Site^ site, String ^ tpName, Object ^ result);
		void SequenceBranchControl(Site ^ site, int siteIndex, String ^ tpName, Object ^ result);
		int UpdateTestConditionProperty(Site^ site, int siteIndex);
		void UpdateTestResults(Site^ site, int siteIndex, array<Object ^> ^ TestResult);
		void UpdateTestResultWlanAsync(Site^site, int siteIndex, String^ testItemName, String^ testParameterName, Object^ testResult);
		void UpdateTestResultsWhenException(Site^ site, int siteIndex);
		int GetPinNameFromAmapAlias(String^ pinAlias, String^ % pinName);
		String^ GetStringUnitPrefix(Site^ site, String ^ TestItemName, String ^ TestParameterName);
		int GetPinNameFromTestParameterDisplayName(String^ TestParameterDisplayName, String^ % pinName);
		int SetTestLimitFromDeviceFile(Site^ site, String^ TestItemName, String^ TestParameterName, String^ LowLimit, String^ HighLimit);
		int UpdateDoubleTestLimitsWithPrefix(double HiLimit, double LoLimit, UnitPrefix Prefix, double % NewHiLimit, double % NewLoLimit);
		int ModifyTestParameterEvalMode(Site^ site, String^ TestItemName, String^ TestParameterDisplayName, EvalMode TestParameterEvalMode);
		int ModifyTestParameterDisplayName(Site^ site, String^ TestItemName, String^ TestParameterDisplayName, String^ NewTestParameterDisplayname);
		int ModifyTestParameterLimits(Site^ site, String^ TestItemName, String^ TestParameterDisplayName, String^ LowLimit, String^ HighLimit);
		int SetTestLimit(Site^ site, String^ TestItemName, String^ TestParameterName, String^ LowLimit, String^ HighLimit);
		void RTPlotter(Site ^ site, int siteIndex, String ^ xLabel, String ^ yLabel, String ^ Filename, Object ^ yData);
		void UnloadRTPlotter(int siteIndex);
		bool TestItem_RF_ResourceNeeded(Site ^ site);
		bool ControlItem_RF_ResourceNeeded(Site ^ site);
		bool ControlStep_RF_ResourceNeeded(Site ^ site, int siteIndex);

#pragma endregion "techFlow"

#pragma region "Threads"

		int DoThread(ParameterizedThreadStart^ function, Site^ site);
		int DoThreadHardware(ParameterizedThreadStart^ function, Site^ site);
		int DoThreadRunPattern(ParameterizedThreadStart^ function, Site^ site, int testSitePerDC);
		int DoThreadRunAllSites(ParameterizedThreadStart^ function, Site^ site);

#pragma endregion "Threads"

	};


}

/*----------------------------------------------------------------------
* Revision Log
* $Log: TestFunction.h.rca$

* v1.0.0.0 (20 March 2020), LKL
* Initial release version.

* v1.1.0.0 (29 Jan 2021), LKL 
* Added bool IsTPResultFailed(Site^ site, String ^ tpName, Object ^ result);
		int OperationBranchingCheck(Site^ site, int siteIndex);
		void SequenceBranchControl(Site ^ site, int siteIndex, String ^ tpName, Object ^ result);

* v1.2.0.0 (12 Aug 2026), ZhiKean
* Merge AMB7600SR Test Library REV1 with AMB7300 Test Library REV2P0 (v1.0.0.3)

----------------------------------------------------------------------*/