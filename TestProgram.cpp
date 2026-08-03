#include "TestProgram.h"

namespace AMB7600SR_TestLibrary_REV2
{
	// TestProgram Constructor
	TestProgram::TestProgram(void)
	{
		
		//<Info> tl - TestLibrary 
		tl = gcnew TestFunction(); 
	}

	// Public Methods
	int TestProgram::Load(Site ^ site)
	{
		int ret = 0;
		int siteIndex = 0;
		tl->glob->RunTimeError = gcnew array<bool>(1);
		tl->glob->RunTimeError[0] = false;

		// ToDo: Write your tester hardware initialization routines here
		tl->glob->tf.CurrentPhase = site->CurrentPhase->Name;

#pragma region "Initialize Test Program"		

		tl->InitializeProgram(site);
		amb7600srtl = gcnew AMB7600SRTestLibrary(tl);

		for (siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, ">> Begin " + tl->glob->tf.CurrentPhase + " Phase");
		}
#pragma endregion "Initialize Test Program"

#pragma region "Tester Initialization"

		ret = amb7600srtl->InitializeTester(site, tl->glob->tf.NumberOfSites, tl->glob->HardwareProfile, tl->glob->tf.TestHead);

		for (siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "Done Compiled and Load Phase");
			tl->WriteToLogger(siteIndex, ">> Executed " + tl->glob->tf.CurrentPhase + " Phase");
		}

#pragma endregion "Tester Initialization"

#pragma region "Test Time Profile"

		if (tl->glob->AWV.Debug == 1)
		{
			//ttp = gcnew array<TestTimeProfiling^>(tl->glob->tf.TotalUUTOffsets);

			//for (int testSite = 0; testSite < tl->glob->tf.TotalUUTOffsets; testSite++)
			//{
			//	String ^ AMSRFConfigPath = String::Empty;

			//	if (amb7600srtl->CurrentHeadSite.AMSRFSupported != "NA")
			//	{
			//		if (tl->glob->TestSiteAmsrfType[testSite] == "AMSRF0")
			//		{
			//			AMSRFConfigPath = amb7600srtl->SystemConfigurationInfoAMSRF0.ConfigPath;
			//		}
			//		else if (tl->glob->TestSiteAmsrfType[testSite] == "AMSRF1")
			//		{
			//			AMSRFConfigPath = amb7600srtl->SystemConfigurationInfoAMSRF1.ConfigPath;
			//		}
			//	}

			//	ttp[testSite] = gcnew TestTimeProfiling(tl);

			//	ttp[testSite]->InitializeProgram(site, tl->glob->tf.StageCount, "", tl->glob->tf.TestHead);
			//}
		}

#pragma endregion "Test Time Profile"

		return ret;
	}
	int TestProgram::Unload(Site ^ site)
	{
		// ToDo: Write your tester shutdown routines here		
		int ret = 0;

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, ">>Executing " + tl->glob->tf.CurrentPhase + " Phase");
		}
		amb7600srtl->UninitializeTester(site);
#pragma region "Test Time Profile"

		if (tl->glob->AWV.Debug == 1)
		{
			for (int testSite = 0; testSite < tl->glob->tf.TotalUUTOffsets; testSite++)
			{
				//ttp[testSite]->WriteToFile(site);
			}
		}

#pragma endregion "Test Time Profile"



		if (tl->glob->tf.unloadRTPlotter)
		{
			tl->UnloadRTPlotter(0);
		}

		tl->KillTracerLogger(tl->glob->tf.NumberOfSites, tl->glob->tf.CurrentPhase);


		return ret;
	}
	int TestProgram::PreProcessing(Site^ site)
	{
		int ret = 0;

		//Initialize the Global Variables
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->glob->GlobalResult[siteIndex]->Clear();
		}

		//Reload CorrFactor
		tl->corrFactorLoad(site);

		//Reload BoardLoss
		tl->boardLossFileLoad(site);

		//Execute Control Method if any
		tl->ThreadingInfo(site, tl->ControlItem_RF_ResourceNeeded(site));
		ret = tl->DoThreadHardware(gcnew ParameterizedThreadStart(this, &TestProgram::AMB7600SR_TestLibrary_ControlMethod), site);

		return ret;
	}
	int TestProgram::PostProcessing(Site^ site)
	{
		int ret = 0;

		ret = amb7600srtl->PostProcessing_RF(site);

		tl->ThreadingInfo(site, tl->ControlItem_RF_ResourceNeeded(site));
		ret = tl->DoThreadHardware(gcnew ParameterizedThreadStart(this, &TestProgram::AMB7600SR_TestLibrary_ControlMethod), site);

		return ret;
	}	
	int TestProgram::seq_ControlItem(Site ^ site)
	{
		int ret = 0;

		tl->ThreadingInfo(site, tl->ControlItem_RF_ResourceNeeded(site));
		ret = tl->DoThreadHardware(gcnew ParameterizedThreadStart(this, &TestProgram::AMB7600SR_TestLibrary_ControlMethod), site);

		return ret;
	}
	int TestProgram::seq_TestItem(Site ^ site)
	{
		int ret = 0;

		tl->ThreadingInfo(site, tl->TestItem_RF_ResourceNeeded(site));
		ret = tl->DoThreadHardware(gcnew ParameterizedThreadStart(this, &TestProgram::AMB7600SR_TestLibrary_ControlMethod_TestMethod), site);

		return ret;
	}

	int TestProgram::seq_TestMethod(Site ^ site)
	{
		/*****************************************************************************************************
		**	seq_TestMethod
		**		site - This is techFlow site object.
		**
		**	Descriptions:
		**		This is a function to perform all the configuration and testing for all kind of flow items,
		**		such as DcControl, DcTest, PatternControl, PatternTest, VnaConfig, VnaFetch, VnaDataAnalysis.
		**		Get test property from tF3, and then return test result to display at tF3.
		******************************************************************************************************/

		int ret = 0;

		tl->ThreadingInfo(site, tl->TestItem_RF_ResourceNeeded(site));
		ret = tl->DoThreadHardware(gcnew ParameterizedThreadStart(this, &TestProgram::AMB7600SR_TestLibrary_ControlMethod_TestMethod), site);

		return ret;
	}

	//Private Method
	void TestProgram::AMB7600SR_TestLibrary_ControlMethod(Object ^ object)
	{
		TestProgramData ^ testProgramData = (TestProgramData^)object;
		Site^ site = testProgramData->t_site;
		int SiteIndex = testProgramData->siteIndex;
		String^ strControlMethod = nullptr;
		int testSite = 0;
		int intControlMethod = 0;

		try
		{
			for each (testSite in tl->glob->ThreadingSite[SiteIndex])
			{
				ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
				testConditionCollection = tf_ControlItem_ConditionList();

				for each(Condition ^ controlMethod in testConditionCollection)
				{
					if (controlMethod->Name->StartsWith("ControlMethod"))
					{
						strControlMethod = nullptr;
						intControlMethod = 0;		
						strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
						tl->glob->ErrorInfo[testSite].ControlMethodName = strControlMethod;
						amb7600srtl->Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);

						//ControlMethod_Selection(site, testSite, intControlMethod, testConditionCollection);
						amb7600srtl->ControlMethod_Selection(site, testSite, intControlMethod, testConditionCollection);
					}
				}
			}

		}
		catch (Exception ^ ex)
		{
			try {
				tl->UpdateTestResultsWhenException(site, testSite);
				testProgramData->Exception = ex;
				testProgramData->ErrorCode = ER_CONST_GENERAL;
				tl->ErrorHandling(site, testSite, ex->ToString());
			}
			catch (Exception^ innerEx)
			{
				testProgramData->Exception = gcnew Exception("Error during exception handling: " + innerEx->ToString() + " || Original Error: " + ex->ToString());
				testProgramData->ErrorCode = ER_CONST_GENERAL;
			}
		}
	}
	void TestProgram::AMB7600SR_TestLibrary_ControlMethod_TestMethod(Object ^ object)
	{
		TestProgramData ^ testProgramData = (TestProgramData^)object;
		Site^ site = testProgramData->t_site;
		int SiteIndex = testProgramData->siteIndex;
		String^ strControlMethod = nullptr;
		String^ testMethod = nullptr;
		String^ resultDisplay = nullptr;
		String^ testParameterName = nullptr;
		String^ testItemName = nullptr;
		String^ globalTestResultName = nullptr;
		int testParameterCount;
		int methodTestParameterCount = 0;
		int testSite = 0;
		int intControlMethod = 0;
		int intTestMethod = 0;

		LARGE_INTEGER tfreq;
		LARGE_INTEGER tstart, tend;
		QueryPerformanceFrequency(&tfreq);

		// Test item object
		TestItem ^ testItem;

		// Every sub flow item inside a test item. Eg: test parameter, control step, test step
		AFlowSubItem ^ subFlowItem;

		// Test step object
		TestStep ^ testStep;

		tl->glob->currentSubItemName = gcnew array<String^>(tl->glob->tf.NumberOfSites);

		try
		{
			for each (testSite in tl->glob->ThreadingSite[SiteIndex])
			{
				tl->UpdateTestProperty(site, testSite);
				testItemName								= tl->glob->TestProperty[testSite].TestItemName;
				tl->glob->ErrorInfo[testSite].TestItemName	= testItemName;
				testParameterCount							= tl->glob->TestProperty[testSite].TotalTestParameter;
				tl->glob->TestResults[testSite]				= gcnew array<Object^>(testParameterCount);

				array<Object^>^ testResults = gcnew array<Object^>(tl->glob->TestProperty[testSite].TotalTestParameter);
				testItem = (TestItem^)site->FlowItems[tl->glob->TestProperty[testSite].TestItemName];

				//Control Step & Test Parameter Count
				int csCount = 0;
				int tpCount = 0;

				// Loop every flow items in sequence (control step item, test parameter item)
				for each(subFlowItem in testItem->SubItems)
				{
					//QueryPerformanceCounter(&tstart);

					ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();

					for (int l_siteIndex = 0; l_siteIndex < tl->glob->tf.TPropertyTotalSite; l_siteIndex++)
					{
						// Get current flow item's name
						tl->glob->currentSubItemName[l_siteIndex] = subFlowItem->Name;
					}

					//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
					if (dynamic_cast<ControlStep^>(subFlowItem->Data) != nullptr)
					{
						AFlowStep^ flowStep = (AFlowStep^)testItem->FlowSteps[tl->glob->TestProperty[testSite].FlowStepItemName[csCount]];

						testConditionCollection = tf_FlowStep_ConditionList(tl->glob->currentSubItemName[testSite]);

						if (!flowStep->Bypass)
						{
							if (testConditionCollection->ContainsKey("ControlMethod"))
							{
								intControlMethod = 0;
								//strControlMethod = (String^)tf_TestParameter_ConditionCast(testParameterName, controlMethod->Name);
								strControlMethod = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[testSite], "ControlMethod");
								tl->glob->ErrorInfo[testSite].ControlMethodName = strControlMethod;
								amb7600srtl->Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);

								amb7600srtl->ControlMethod_Selection(site, testSite, intControlMethod, testConditionCollection);
							}
							else if (!testConditionCollection->ContainsKey("ControlMethod"))
							{
								throw gcnew Exception("ControlMethod is not found.");
							}
						}
						else
						{
						}
						csCount++;
					}
					//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
					else if (dynamic_cast<TestParameter^>(subFlowItem->Data) != nullptr)
					{
						TestParameter^ tp = (TestParameter^)testItem->TestParameters[tl->glob->TestProperty[testSite].TestParameterName[tpCount]];

						testConditionCollection = tf_TestParameter_ConditionList(tl->glob->currentSubItemName[testSite]);

						if (!tp->Bypass)
						{
							if (testConditionCollection->ContainsKey("TestMethod"))
							{
								testParameterName = tl->glob->currentSubItemName[testSite];
								tl->glob->ErrorInfo[testSite].TestParameterName = testParameterName;

								intTestMethod = 0;
								testMethod = (String^)tf_TestParameter_ConditionCast(testParameterName, "TestMethod");
								//testMethod = tl->glob->TestProperty[SiteIndex].MethodName;
								tl->glob->ErrorInfo[testSite].TestMethodName = testMethod;
								amb7600srtl->Dictionary_TM->TryGetValue(testMethod, intTestMethod);

								amb7600srtl->TestMethod_Selection(site, testSite, intTestMethod, testParameterName, tpCount, methodTestParameterCount);

								for (int j = 0; j < methodTestParameterCount; j++)
								{
									globalTestResultName = testItemName + "_" + tl->glob->TestProperty[testSite].TestParameterName[tpCount + j]; //group test parameter name into corresponding test item name
									tl->glob->GlobalResult[testSite]->Add(globalTestResultName, tl->glob->TestResults[testSite][tpCount + j]); //Add key string into dictionary
								}
							}
							else if (!testConditionCollection->ContainsKey("ResultDisplay"))
							{
								throw gcnew Exception("TestMethod or ResultDisplay is not found.");
							}
						}
						else
						{
						}
						tpCount++;
					}
					//QueryPerformanceCounter(&tend);

					//double testTime = (double)(tend.QuadPart - tstart.QuadPart) / (double)tfreq.QuadPart; //in sec

					if (tl->glob->AWV.Debug == 1)
					{
						//ttp[testSite]->CommitTestTime(SiteIndex, testItemName, testParameterName, testMethod, testSite, testTime);
					}

				}

				tl->UpdateTestResults(site, testSite, tl->glob->TestResults[testSite]);
			}

		}
		catch (Exception ^ ex)
		{
			tl->UpdateTestResultsWhenException(site, testSite);
			testProgramData->Exception = ex;
			testProgramData->ErrorCode = ER_CONST_GENERAL;
			tl->ErrorHandling(site, testSite, ex->ToString());
			throw ex->Message;
		}
	}
}