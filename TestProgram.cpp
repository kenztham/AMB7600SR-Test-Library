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
		int tfSite = tl->glob->tf.TestSite;

		// ToDo: Write your tester hardware initialization routines here
		tl->glob->tf.CurrentPhase = site->CurrentPhase->Name;

#pragma region "Initialize Test Program"		

		tl->InitializeProgram(site);
		methods = gcnew MethodsBranch(tl);
		amb7600srtl = gcnew AMB7600SRTestLibrary(tl);
		amb7300tl = gcnew AMB7300TestLibrary(tl);
		module400series = gcnew Module400Series(tl);

		//Reference object to each other to sync variables
		methods->amb7600srtl = amb7600srtl;
		methods->amb7300tl = amb7300tl;
		methods->module400series = module400series;

		module400series->methods = methods;

		for (siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ">> Begin " + tl->glob->tf.CurrentPhase + " Phase");
		}
#pragma endregion "Initialize Test Program"

#pragma region "Methods Initialization"

		methods->InitializeCMDictionary(tl->glob->tf.NumberOfSites);
		methods->InitializeTMDicionary(tl->glob->tf.NumberOfSites);

#pragma endregion "Methods Initialization"

#pragma region "Tester Initialization"

		String^ message = "Please select the RF Test Platform for this program:\n\n" +
			"Click 'Yes' for AMB7300\n" +
			"Click 'No' for AMB7600SR";

		DialogResult result = MessageBox::Show(
			message, 
			TITLE_CONST_PLATFORM_SELECTION, 
			MessageBoxButtons::YesNo, 
			MessageBoxIcon::Question
		);

		PlatformSelection = result;

#pragma region "SiteConfiguration"

		amb7600srtl->SiteConfiguration(site);

#pragma endregion "SiteConfiguration"

		// Initialize DC modules first
		ret = module400series->InitializeTester(site, tl->glob->tf.NumberOfSites, tl->glob->HardwareProfile, tl->glob->tf.TestHead);

		if (PlatformSelection == AMB7300_PLATFORM)
		{
			// User selected AMB7300
			ret = amb7300tl->InitializeTester(site);

#pragma region "Committing Result"
			site->CommittingResult += gcnew CommitResult(this, &TestProgram::SaveSnpToBinAfterCommitResults);
#pragma endregion

#pragma region "HighPwrTest - Source Low on Load"
			if (tl->glob->AWV.HighPwrTest_EN == true)
			{
				tl->LoadAppsCalFile(tfSite, tl->glob->AWV.HighPwrTest_AppsCalFile);
				for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfTestSites; siteIndex++)
				{
					ret = amb7300tl->HighPwrTest_VNASourceLow(tfSite, siteIndex);
				}
			}
#pragma endregion
		}
		else if (PlatformSelection == AMB7600SR_PLATFORM)
		{
			// User selected AMB7600SR
			ret = amb7600srtl->InitializeTester(site, tl->glob->tf.NumberOfSites, tl->glob->HardwareProfile, tl->glob->tf.TestHead);
		}

		for (siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Done Compiled and Load Phase");
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ">> Executed " + tl->glob->tf.CurrentPhase + " Phase");
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
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ">>Executing " + tl->glob->tf.CurrentPhase + " Phase");
		}

		// Uninitialize DC modules first
		ret = module400series->UninitializeTester(site);

		if (PlatformSelection == AMB7300_PLATFORM)
		{

#pragma region "Committing Result"
			site->CommittingResult -= gcnew CommitResult(this, &TestProgram::SaveSnpToBinAfterCommitResults);
#pragma endregion

			// User selected AMB7300
			amb7300tl->UninitializeTester(site);
		}
		else if (PlatformSelection == AMB7600SR_PLATFORM)
		{
			// User selected AMB7600SR
			amb7600srtl->UninitializeTester(site);
		}

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

#pragma region "Uninitialize File Logger"

		tl->UninitializeFileLogger();

#pragma endregion

#pragma region "Uninitialize Tracer Logger"

		tl->UninitializeTracerLogger();

#pragma endregion


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

		if (PlatformSelection == AMB7300_PLATFORM)
		{
			int tfSite = tl->glob->tf.TestSite;

			String^ CorrFactorDirectory;

			ret = amb7300tl->PreProcessingTester(site);

			if (tf_ControlItem_ConditionExist(PreProcessing_CorrFactorDirectory))
			{
				CorrFactorDirectory = (String^)tf_ControlItem_ConditionCast(PreProcessing_CorrFactorDirectory);
			}
			else
			{
				CorrFactorDirectory = tl->glob->tf.RecipeFilePathDirectory + "\\" + FILENAME_CONST_PROJECT_FIXEDOFFSETFILEFOLDER + "\\" + tl->glob->TesterId + "_" + tl->glob->tf.ProjectName + "_CorrFactor_S" + tfSite.ToString() + ".csv";
			}

			tl->LoadFixedOffsetFile(tfSite, CorrFactorDirectory);
		}
		else if (PlatformSelection == AMB7600SR_PLATFORM)
		{
			//Reload CorrFactor
			tl->corrFactorLoad(site);

			//Reload BoardLoss
			tl->boardLossFileLoad(site);
		}
		//Execute Control Method if any
		tl->ThreadingInfo(site, tl->ControlItem_RF_ResourceNeeded(site));
		ret = tl->DoThreadHardware(gcnew ParameterizedThreadStart(this, &TestProgram::AMB7600SR_TestLibrary_ControlMethod), site);

		return ret;
	}
	int TestProgram::PostProcessing(Site^ site)
	{
		int ret = 0;

		if (PlatformSelection == AMB7300_PLATFORM)
		{
			ret = amb7300tl->PostProcessingTester(site);
		}
		else if (PlatformSelection == AMB7600SR_PLATFORM)
		{
			ret = amb7600srtl->PostProcessing_RF(site);
		}

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
					if (controlMethod->Name->StartsWith("MethodName"))
					{
						strControlMethod = nullptr;
						intControlMethod = 0;		
						strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
						tl->glob->ErrorInfo[testSite].ControlMethodName = strControlMethod;
						methods->Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);

						//ControlMethod_Selection(site, testSite, intControlMethod, testConditionCollection);
						//methods->ControlMethod_Selection(amb7600srtl, site, testSite, intControlMethod, testConditionCollection);
						methods->ControlMethod_Selection(site, testSite, intControlMethod, testConditionCollection);
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
				tl->ErrorHandling(site, testSite, innerEx->ToString());
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
		//TestStep ^ testStep;

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

					for (int l_siteIndex = 0; l_siteIndex < tl->glob->tf.NumberOfSites; l_siteIndex++)
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
							if (testConditionCollection->ContainsKey("MethodName"))
							{
								intControlMethod = 0;
								//strControlMethod = (String^)tf_TestParameter_ConditionCast(testParameterName, controlMethod->Name);
								strControlMethod = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[testSite], "MethodName");
								tl->glob->ErrorInfo[testSite].ControlMethodName = strControlMethod;
								methods->Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);

								//methods->ControlMethod_Selection(amb7600srtl,site, testSite, intControlMethod, testConditionCollection);
								methods->ControlMethod_Selection(site, testSite, intControlMethod, testConditionCollection);
							}
							else if (!testConditionCollection->ContainsKey("MethodName"))
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
							if (testConditionCollection->ContainsKey("MethodName"))
							{
								testParameterName = tl->glob->currentSubItemName[testSite];
								tl->glob->ErrorInfo[testSite].TestParameterName = testParameterName;

								intTestMethod = 0;
								testMethod = (String^)tf_TestParameter_ConditionCast(testParameterName, "MethodName");
								//testMethod = tl->glob->TestProperty[SiteIndex].MethodName;
								tl->glob->ErrorInfo[testSite].TestMethodName = testMethod;
								methods->Dictionary_TM->TryGetValue(testMethod, intTestMethod);

								//methods->TestMethod_Selection(amb7600srtl, site, testSite, intTestMethod, testParameterName, tpCount, methodTestParameterCount);
								methods->TestMethod_Selection(site, testSite, intTestMethod, testParameterName, tpCount, methodTestParameterCount);

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
		}
	}


	void TestProgram::SaveSnpToBinAfterCommitResults(Site^ site)
	{
		int current_site = 0;

		if (tl->glob->AWV.EnableSaveSnpData && tl->glob->AWV.isSaveBinFolder && amb7300tl->vnaDataAnalysisTPC.saveSnpData == true)
		{
			for each(ResultPerDUTCollection ^ resultCollection in site->ResultsByOffset)
			{
				for each (ResultPerDUT ^ dutResult in resultCollection)
				{
					if (dutResult->Active)
					{

#pragma region "Generate touchstoneFolder\\Bin[bin] folder if create_S2PpathByBin_flag not flagged"

						if (!tl->glob->tf.create_S2PpathByBin_flag)
						{
							array<String^>^ touchstoneFolder_HardBin = gcnew array<String^>(tl->glob->tf.HardBinCount);

							for (int i = 0; i < tl->glob->tf.HardBinCount; i++)
							{
								touchstoneFolder_HardBin[i] = amb7300tl->saveRecallSetting->touchstoneFolder + "\\" + "Bin" + tl->glob->tf.str_arrHBin[i];

								// Create S2Ppath > [bin] folder if not exist
								if (!(Directory::Exists(touchstoneFolder_HardBin[i])))
								{
									Directory::CreateDirectory(touchstoneFolder_HardBin[i]);
								}

								// Store S2Ppath_Bin folder path to BinString_by_BinPath Dictionary
								if (tl->glob->tf.BinString_by_BinPath->ContainsKey(tl->glob->tf.str_arrHBin[i]))
								{
									tl->glob->tf.BinString_by_BinPath[tl->glob->tf.str_arrHBin[i]] = touchstoneFolder_HardBin[i];
								}
								else
								{
									tl->glob->tf.BinString_by_BinPath->Add(tl->glob->tf.str_arrHBin[i], touchstoneFolder_HardBin[i]);
								}
							}
							tl->glob->tf.create_S2PpathByBin_flag = true;
						}
#pragma endregion

#pragma region "Move failed S2P file to respective BinFolder"
						array<String^>^ arr_Failed_TiTpName = gcnew array<String^>(0);
						array<String^>^ arrSeparator_F = gcnew array<String^>(1);
						arrSeparator_F[0] = ".";

						int arr_FailedTP_TotalCount = dutResult->FailedTestParameters->Count;

						String^ FailedTi = String::Empty;
						String^ FailedTp = String::Empty;
						int FailTp_Hbin = -9999;
						String^ FailTi_S2PFilename = String::Empty;
						String^ BinPath_FailedTiBySite_Folder = String::Empty;
						String^ temp_S2P_FullFilePath = String::Empty;


						for each (String^ Failed_TiTpName in dutResult->FailedTestParameters)	// Failed_TiTpName = testItem.testParameter
						{

							arr_Failed_TiTpName = Failed_TiTpName->Split(arrSeparator_F, StringSplitOptions::None);

							if (FailedTi != arr_Failed_TiTpName[0])
							{
								FailedTi = arr_Failed_TiTpName[0];

								if (tl->glob->tf.Ti_by_S2PFilename->ContainsKey(FailedTi + "_S" + current_site))
								{
									if (amb7300tl->sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
									{
										// Get snp file name from Ti_by_S2PFilename Dictionary
										FailTi_S2PFilename = tl->glob->tf.Ti_by_S2PFilename[FailedTi + "_S" + current_site] + ".s2p";
									}
									else if (amb7300tl->sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
									{
										// Get snp file name from Ti_by_S2PFilename Dictionary
										FailTi_S2PFilename = tl->glob->tf.Ti_by_S2PFilename[FailedTi + "_S" + current_site];// +".s2p";
									}

									// Update selected S2P file path
									temp_S2P_FullFilePath = amb7300tl->saveRecallSetting->touchstoneFolder + "\\" + FailTi_S2PFilename;

									// Get HardBin number from TiTpRule_by_HBin Dictionary
									FailTp_Hbin						= tl->glob->tf.TiTpRule_by_HBin[Failed_TiTpName];

									// Create snp folder by HBin and FailedTi
									BinPath_FailedTiBySite_Folder	= tl->glob->tf.BinString_by_BinPath[FailTp_Hbin.ToString()] + "\\" + FailedTi + "_S" + current_site;

									if (!(Directory::Exists(BinPath_FailedTiBySite_Folder)))
									{
										Directory::CreateDirectory(BinPath_FailedTiBySite_Folder);
									}

									// Move respective S2P file to failed HardBin Folder
									File::Move(temp_S2P_FullFilePath, BinPath_FailedTiBySite_Folder + "\\" + FailTi_S2PFilename);
								}
							}
						}
#pragma endregion

#pragma region "Move remaining S2P file to respective Pass HardBin Folder"

						int Pass_SNPFiles_count = 0;
						int split_SNPFilePath_count = 0;
						//int FailTp_count = dutResult->FailedTestParameters->Count;

						array<String^>^ Separator1 = gcnew array<String^>(1);
						Separator1[0] = "\\";
						array<String^>^ Separator2 = gcnew array<String^>(1);
						Separator2[0] = "_";

						String^ S2PFile_ItemName = String::Empty;
						String^ mod_Pass_SNPFilepath_byBin1 = String::Empty;

						Pass_SNPFiles_count = Directory::GetFiles(amb7300tl->saveRecallSetting->touchstoneFolder, "*.s2p")->Length;
						array<String^> ^ arr_Pass_SNPFilePath = gcnew array<String^>(Pass_SNPFiles_count);
						array<String^>^ arr_spilt_SNPFile = gcnew array<String^>(0);
						array<String^>^ SNPFileName = gcnew array<String^>(Pass_SNPFiles_count);

						arr_Pass_SNPFilePath = Directory::GetFiles(amb7300tl->saveRecallSetting->touchstoneFolder, "*.s2p");	// e.g. "C:\\snp\\ProjectName\\LOTID\\WaferID\\abc1234.s2p"

						for (int j = 0; j < Pass_SNPFiles_count; j++)
						{
							arr_spilt_SNPFile = arr_Pass_SNPFilePath[j]->Split(Separator1, StringSplitOptions::None);	// e.g. arr_spilt_SNPFile = {"C:","snp","ProjectName","LOTID","WaferID","abc1234.s2p"}

							split_SNPFilePath_count = arr_spilt_SNPFile->Length;

							SNPFileName[j] = arr_spilt_SNPFile[split_SNPFilePath_count - 1];							//e.g. "abc1234.s2p"

																														// Move to Bin1 folder only if Bin1 exist in BinSorter
							if (tl->glob->tf.BinString_by_BinPath->ContainsKey("1"))
							{
								//if (FailTp_count > 0)
								//{
								//	mod_Pass_SNPFilepath_byBin1 = tl->glob->tf.BinString_by_BinPath["1.1"] + "\\" + S2PFile_ItemName;
								//	if (!(Directory::Exists(mod_Pass_SNPFilepath_byBin1)))
								//	{
								//		Directory::CreateDirectory(mod_Pass_SNPFilepath_byBin1);
								//	}
								//	File::Move(arr_Pass_SNPFilePath[j], mod_Pass_SNPFilepath_byBin1 + "\\" + SNPFileName[j]);
								//}
								//else
								{
									File::Move(arr_Pass_SNPFilePath[j], tl->glob->tf.BinString_by_BinPath["1"] + "\\" + SNPFileName[j]);
								}
							}
							else
							{
								// Do nothing because Bin1 is not set in BinSorter
							}
						}
#pragma endregion

					}
				}
				current_site++;
			}
		}
	}
}