#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Test Function/TestFunction.h"
#include "../Test Function/Aemulus.Hardware.CM.h"
#include "../Test Function/Aemulus.Hardware.DM.h"
#include "../Test Function/Aemulus.Hardware.SMU.h"

#include "../Test Method/TestTimeProfiling.h"

using namespace System;
using namespace System::Threading;
using namespace Aemulus::Hardware;
using namespace Aemulus::Tech;
using namespace Aemulus::Tech::Flow;
using namespace Aemulus::TestLib;
using namespace Aemulus::TestLib::Utility;
using namespace System::Reflection;
using namespace System::Xml;
using namespace Functions;

namespace TestMethods
{
	ref class ThreadInfo
	{
		int siteIndex;
		int testNumber;
		String^ testItemName;
		String^ testParameterName;
		int UUT_Index;
	};
	public ref class TestTimeProfiling
	{
	private:
		// Private properties
		array<int>^ cumulativeTestNumberCount;

	public:
		// Hardware Resource Manager 
		value struct ResourceManagerSetting
		{
			String ^ moduleAlias;
			String ^ ResourceType;
			Resource ^ HardwareRsrc;
			array<ResourceManager ^>^ RsrcManager;

			// Hardware initialization status
			array<bool>^ AM_HardwareStatus;
			array<bool>^ DM_HardwareStatus;
			array<bool>^ DIO_HardwareStatus;
			array<bool>^ CM_HardwareStatus;
			array<bool>^ AMSRF_HardwareStatus;

			Dictionary <String ^, int> ^ AMResourceAlias;
			Dictionary <String ^, int> ^ DMResourceAlias;
			Dictionary <String ^, int> ^ DIOResourceAlias;
			Dictionary <String ^, int> ^ ResourceAlias;

			array<ResourceManager ^>^ RsrcManagerSPG;
			PinGroupMapCollection ^ pinGroups;
			array<String ^>^ pinMapsTemp;
			Dictionary <String ^, MapCollection ^> ^ mcPinGroupPinMaps; //Key - PinGroup; Value - PinMaps 
			Dictionary <String ^, array<String ^>^> ^ PinGroupPinMaps;	//Key - PinGroup; Value - PinMaps 
		};
		array<ResourceManagerSetting> ^ ResourceManagerSett;

		// Test Time Profile
		value struct TestTimeCollection
		{
			int testNumber; // Under No, horizontal content
			String^ averageTime; // Under Average row, horizontal content
			String^ testItemName; // Under Test Item, horizontal content
			String^ testParameterName; // Under Test Parameter, horizontal content
			String^ testMethodName; // Under Description, horizontal content

			List<String^>^ testTime;
			List<double>^ d_testTime;
		};

		// Test Item Profile
		value struct TestItemMethod
		{
			int UUTNumber;

			Dictionary<String^, int>^ testParamNumber; //
			array<TestTimeCollection>^ testNumberTimeCollection; // Under Average Site#, per test cycle row content, test time for multiple test method, testNumberTimeCollection[testNumber]
																 //array<TestTimeCollection>^ UUT_TestTimeCollection; // Under Average Site#, per UUT column content, test time for multiple cycles, UUT_TestTimeCollection[UUT Index]
																 //array<Thread^>^ UUT_Thread; // For test time collection, unique thread for specific [site][testNumber][UUT Index]
		};

		// Output File Content
		value struct ProfileContent
		{
			bool isActive;
			int testHeadNum;
			String^ projectName;
			String^ projectType;
			String^ projectDescription;
			String^ platform;
			String^ projectConfig;
			String^ projectSiteConfig;
			String^ accessories;
			String^ projectTotalSite;
			String^ siteNum;
			String^ testRunDate;

			//Dictionary<String^, int>^ testParameterNumber;
			array<TestItemMethod>^ UUT_TestNumberContent; // Loop for all UUT, UUT_TestNumberContent[UUT Index]
														  //array<TestItemMethod>^ testNumberContent; // Loop for all test number/method, testNumberContent[testNumber]
		};
		/*
		For each head = independent project, will generate report as per head number, but content implementation same as others
		testTimeProfilingContent[siteIndex]->testNumberContent[testNumber] = Contains test item name, test method name, average of all test time
		testTimeProfilingContent[siteIndex]->testNumberContent[testNumber]->UUT_TestTimeCollection[UUT_Index] = List of test time

		Case: Single site
		testTimeProfilingContent[0]->testNumebrContent[testNumber]->UUT_TestTimeCollection[UUT_Index]->testTime->Add(new test time)

		Case: True Parallel/Index Parallel (only test method diff)
		testTimeProfilingContent[0]->testNumberContent[testNumber]->UUT_TestTimeCollection[UUT_Index]->testTime->Add(new test time)  || True Parallel = DC, Index Parallel = DC
		testTimeProfilingContent[0]->testNumberContent[testNumber]->UUT_TestTimeCollection[UUT_Index]->testTime->Add(new test time)  || True Parallel = DC, Index Parallel = RF

		Case: Multi-head
		This will be run in different techFlow instance as independent program.
		Generate file name according to relative TestHead number
		File Name:
		[ProjectName]_[Config]_[Head#]_[Site#].csv
		*/
		array<ProfileContent>^ testTimeProfilingContent; // testTimeProfilingContent[siteIndex] = Completed file content

														 //Site Configuration Xml File
		value struct SiteConfigurationInfo
		{
			String ^ SiteConfig;
			String ^ SCTypeUsed;
			//array <String^ >^ ExternalSignalGeneratorType;
			//array <String^ >^ ExternalSignalGeneratorAddress;
			//array <String^ >^ ExternalSignalGeneratorCH1;
			//array <String^ >^ ExternalSignalGeneratorCH2;
			//array <bool >^ ExternalSignalGeneratorExist;
			//array <int >^ ExternalSignalGeneratorTotalChannel;

			int TotalUUTCount_PerHead_PerSite;
			int TotalHeadCount;
			int TotalSiteAmsrf0;
			int TotalSiteAmsrf1;
			int TotalTestSite_PerHead_PerSite;
			int TotalThreadRF;
			int ModeSupportSC;
			int TotalSCExist;
			array<int>^ Site_AMSRF0;
			array <int>^ Site_AMSRF1;
			array <bool>^ RF_SiteThread;
			array<unsigned char  >^ SourceChannel_SC;
			bool Status_RFTest_Site0;
			bool Status_RFTest_Site1;
			bool Status_AMSRF0_Exist;
			bool Status_AMSRF1_Exist;
		};
		SiteConfigurationInfo  SiteConfigurationInfo;

		// Properties
		LARGE_INTEGER* startTime;
		LARGE_INTEGER* stopTime;
		LARGE_INTEGER* systemFreq;

		AppDomain^ currentDomain;
		String^ AMSRFConfigPath = "C:\\ProgramData\\Aemulus\\AMSRF\\Config\\AmsRFConfiguration.xml";
		String^ debugPath = "C:\\Aemulus\\Debug";

		TestTimeProfiling::TestTimeProfiling(TestFunction ^ testFunc);

		TestFunction^ tl;
		DateTime^ time = DateTime::Now;

		// Write File Template Content
		array<String^>^ fileTemplate;

		// Function
		int InitializeProgram(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead);

		void RetrieveProjectConfig(Site^ site);
		void RegisterTestNumber(int siteIndex, String^ testItemName, String^ testParameterName, String^ testMethodName);
		void CommitTestTime(int siteIndex, String^ testItemName, String^ testParameterName, String^ testMethodName, int UUTIndex, double testTime);
		void BuildFileTemplate();
		void WriteToFile(Site^ site);

		// Test Time Recorder
		void QueryStartTime();
		void QueryStopTime();
	};
}





