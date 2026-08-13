#include "TestTimeProfiling.h"

namespace TestMethods
{
#pragma region previous
//	TestTimeProfiling::TestTimeProfiling(TestFunction^ testFunc, String^ AMSRFConfigPath)
//	{
//		tl = testFunc;
//		BuildFileTemplate();
//		this->AMSRFConfigPath = AMSRFConfigPath;
//		//QueryPerformanceFrequency(&systemFreq);
//	}
//
//	int TestTimeProfiling::InitializeProgram(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead)
//	{
//#pragma region Variable Initialization
//		int ret = 0;
//
//		int currentSiteIndex = site->Index;
//		int totalSiteCount = site->FlowEngine->Sites->Count;
//		int totalSiteStage = site->FlowEngine->SiteGroupManager->SiteStages->Count;
//		int totalUUTOffset = site->UUTOffsetResolver->UUTOffsets->Count;
//		int totalTPCount = 0;
//
//		cumulativeTestNumberCount = gcnew array<int>(totalUUTOffset);
//		for (int UUTIndex = 0; UUTIndex < cumulativeTestNumberCount->Length; UUTIndex++)
//		{
//			cumulativeTestNumberCount[UUTIndex] = 0;
//		}
//#pragma endregion
//
//		// Count number of test parameters
//		for each(AFlowItem^ afi in site->FlowItems)
//		{
//			if (afi->GetType() == TestItem::typeid)
//			{
//				TestItem^ ti = (TestItem^)afi;
//				totalTPCount += ti->TestParameters->Count;
//			}
//		}
//
//		// Initialize test time profile collection
//		testTimeProfilingContent = gcnew array<ProfileContent>(totalSiteCount); // Temporary hard code for 4 sites
//		for (int siteIndex = 0; siteIndex < testTimeProfilingContent->Length; siteIndex++)
//		{
//			testTimeProfilingContent[siteIndex].isActive = false;
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent = gcnew array<TestItemMethod>(totalUUTOffset);
//			//testTimeProfilingContent[i].testParameterNumber = gcnew Dictionary<String^, int>();
//			//testTimeProfilingContent[i].testNumberContent = gcnew array<TestItemMethod>(totalTPCount);
//			testTimeProfilingContent[siteIndex].testHeadNum = site->FlowEngine->HeadNumber;
//			testTimeProfilingContent[siteIndex].projectName = site->Flow->Name;
//
//			for (int UUTIndex = 0; UUTIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length; UUTIndex++)
//			{
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].UUTNumber = UUTIndex;
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber = gcnew Dictionary<String^, int>();
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection = gcnew array<TestTimeCollection>(totalTPCount);
//
//				for (int testIndex = 0; testIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length; testIndex++)
//				{
//					testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime = gcnew List<String^>();
//					testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].d_testTime = gcnew List<double>();
//				}
//			}
//
//			/*
//			for (int j = 0; j < testTimeProfilingContent[siteIndex].testNumberContent->Length; j++)
//			{
//			testTimeProfilingContent[siteIndex].testNumberContent[j].UUT_TestTimeCollection = gcnew array<TestTimeCollection>(totalUUTOffset);
//			for (int k = 0; k < testTimeProfilingContent[siteIndex].testNumberContent[j].UUT_TestTimeCollection->Length; k++)
//			{
//			testTimeProfilingContent[siteIndex].testNumberContent[j].UUT_TestTimeCollection[k].testTime = gcnew List<String^>();
//			}
//			}
//			*/
//		}
//
//		// Load config file
//		RetrieveProjectConfig(site);
//
//		// Register test item, parameter and test method name with respective test number
//		for each(AFlowItem^ afi in site->FlowItems)
//		{
//			if (afi->GetType() == TestItem::typeid)
//			{
//				TestItem^ ti = (TestItem^)afi;
//				String^ testItemName = ti->Name;
//				String^ testParameterName = String::Empty;
//
//				for each(TestParameter^ tp in ti->TestParameters)
//				{
//					testParameterName = tp->Name;
//					String^ testMethodName = String::Empty;
//					//if (tf_TPCondition_Exist(testParameterName, "TestMethod"))
//					if (tp->Conditions->ContainsKey("TestMethod"))
//					{
//						//testMethodName = (String^) tf_TestParameter_ConditionCast(testParameterName, "TestMethod");
//						testMethodName = (String^)tp->Conditions["TestMethod"][site]->Value;
//					}
//					RegisterTestNumber(currentSiteIndex, testItemName, testParameterName, testMethodName);
//				}
//			}
//		}
//
//		return ret;
//	}
//	void TestTimeProfiling::RetrieveProjectConfig(Site^ site)
//	{
//#pragma region Variable Initialization
//		String^ errMsg = String::Empty;
//
//		int NumberOfUUTCount = site->UUTOffsetResolver->UUTOffsets->Count;
//		int NumberOfHeadCount = 0;
//		String^ siteConfigXMLPath = String::Empty;
//
//		String^ testerPlatform = String::Empty;
//		String^ testerConfig = String::Empty;
//		String^ testerSiteConfig = String::Empty;
//
//		XmlDocument^ siteConfigInfo = gcnew XmlDocument();
//		XmlDocument^ sitePortInfo = gcnew XmlDocument();
//#pragma endregion
//
//#pragma region "Retrieve Site Config"
//		try
//		{
//			siteConfigXMLPath = site->GetExternalDependency("RFSiteConfigInfo");
//			siteConfigInfo->Load(siteConfigXMLPath);
//			XmlNode^ xmlInfo = siteConfigInfo->DocumentElement->FirstChild;
//
//			array<String^>^ childNodes = gcnew array<String^>(xmlInfo->ChildNodes->Count);
//			array<String^>^ innerTexts = gcnew array<String^>(xmlInfo->ChildNodes->Count);
//
//			// Retrieve site configuration, number of UUTOffset per Head/Site, total head count
//			for (int i = 0; i < xmlInfo->ChildNodes->Count; i++)
//			{
//				childNodes[i] = xmlInfo->ChildNodes[i]->Name;
//				innerTexts[i] = xmlInfo->ChildNodes[i]->InnerText;
//
//				if (childNodes[i] == "SiteConfiguration")
//				{
//					testerSiteConfig = innerTexts[i];
//					tl->WriteToTcrLgr(0, childNodes[i] + ": " + testerSiteConfig);
//				}
//				//else if (childNodes[i] == "TotalUUTCount_PerHead_PerSite")
//				//{
//				//	NumberOfUUTCount = int::Parse(innerTexts[i]);
//
//				//	// Check error for techFlow site UUTOffset count vs user input number of UUTOffset
//				//	if (site->UUTOffsetResolver->UUTOffsets->Count != NumberOfUUTCount)
//				//	{
//				//		errMsg = "TechFlow Site number of UUTOffset mismatch to Project Site config.";
//				//		throw gcnew Aemulus::Hardware::AlarmException();
//				//	}
//
//				//	tl->WriteToTcrLgr(0, childNodes[i] + ": " + NumberOfUUTCount.ToString());
//				//}
//				//else if (childNodes[i] == "TotalHeadCount")
//				//{
//				//	NumberOfHeadCount = int::Parse(innerTexts[i]);
//				//	tl->WriteToTcrLgr(0, childNodes[i] + ": " + NumberOfHeadCount.ToString());
//				//}
//			}
//
//			// Register information to local variable
//			for (int siteIndex = 0; siteIndex < testTimeProfilingContent->Length; siteIndex++)
//			{
//				testTimeProfilingContent[siteIndex].isActive = true;
//				testTimeProfilingContent[siteIndex].projectSiteConfig = testerSiteConfig;
//				if (testerSiteConfig->Contains("Index") || testerSiteConfig->Contains("True"))
//				{
//					testTimeProfilingContent[siteIndex].projectTotalSite = "-";
//					testTimeProfilingContent[siteIndex].siteNum = siteIndex.ToString();
//				}
//				else if (testerSiteConfig->Contains("Single") || testerSiteConfig->Contains("MultiSite") || testerSiteConfig->Contains("MultiUUT"))
//				{
//					testTimeProfilingContent[siteIndex].projectTotalSite = NumberOfUUTCount.ToString();
//					testTimeProfilingContent[siteIndex].siteNum = "-";
//				}
//			}
//		}
//		catch (Exception^ ex)
//		{
//			if (errMsg == String::Empty) errMsg = "External Dependency - SiteConfigInfo not found!\n" + ex->Message->ToString();
//			throw gcnew Aemulus::Hardware::AlarmException(errMsg, -1);
//		}
//#pragma endregion
//
//#pragma region "Retrieve Tester Type and Port Config"
//		try
//		{
//			if (File::Exists(AMSRFConfigPath))
//			{
//				sitePortInfo->Load(AMSRFConfigPath);
//				XmlNode^ xmlInfo = sitePortInfo->DocumentElement->FirstChild;
//
//				for (int i = 0; i < xmlInfo->ParentNode->Attributes->Count; i++)
//				{
//					if (xmlInfo->ParentNode->Attributes[i]->Name == "type")
//					{
//						String^ tConfig = xmlInfo->ParentNode->Attributes[i]->Value;
//
//						if (tConfig->Contains("AMB7600SR"))
//						{
//							testerPlatform = "AMB7600SR";
//							testerConfig = tConfig->Replace("AMB7600SR", "");
//						}
//						else if (tConfig->Contains("AMB7600"))
//						{
//							testerPlatform = "AMB7600";
//							testerConfig = tConfig->Replace("AMB7600", "");
//						}
//					}
//				}
//			}
//			else if (tf_AppWideVariable_Exist("Platform"))
//			{
//				testerPlatform = (String^)tf_AppWideVariable_Cast("Platform");
//			}
//
//			for (int i = 0; i < testTimeProfilingContent->Length; i++)
//			{
//				testTimeProfilingContent[i].platform = testerPlatform;
//				testTimeProfilingContent[i].projectConfig = testerConfig;
//				testTimeProfilingContent[i].projectType = "-"; // @@@ Temporary leave blank
//				testTimeProfilingContent[i].projectDescription = "-"; // @@@ Temporary leave blank
//				testTimeProfilingContent[i].accessories = "-"; // @@@ Temporary leave blank
//				testTimeProfilingContent[i].testRunDate = time->ToString()->Split(gcnew array<wchar_t>{' '}, StringSplitOptions::None)[0];
//			}
//
//			// Throw error if none of these info existed
//			if (testerPlatform == String::Empty && testerConfig == String::Empty && testerSiteConfig == String::Empty)
//			{
//				throw gcnew Aemulus::Hardware::AlarmException("Fail loading project configuration files", -1);
//			}
//		}
//		catch (Exception^ ex)
//		{
//			throw gcnew Aemulus::Hardware::AlarmException("Error occur in loading project setting files.\n" + ex->Message->ToString(), -1);
//		}
//#pragma endregion
//	}
//	void TestTimeProfiling::RegisterTestNumber(int siteIndex, String^ testItemName, String^ testParameterName, String^ testMethodName)
//	{
//		if (siteIndex >= testTimeProfilingContent->Length)
//		{
//			throw gcnew Aemulus::Hardware::AlarmException("Site Index out of range!", -1);
//		}
//
//		String^ keyTestName = testItemName + "_" + testParameterName;
//		for (int UUTIndex = 0; UUTIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length; UUTIndex++)
//		{
//			if (!testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber->ContainsKey(keyTestName))
//			{
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber->Add(keyTestName, cumulativeTestNumberCount[UUTIndex]);
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testNumber = cumulativeTestNumberCount[UUTIndex];
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testMethodName = testMethodName;
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testItemName = testItemName;
//				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testParameterName = testParameterName;
//				cumulativeTestNumberCount[UUTIndex]++;
//			}
//		}
//
//	}
//	void TestTimeProfiling::CommitTestTime(int siteIndex, String^ testItemName, String^ testParameterName, String^ testMethodName, int UUTIndex, double testTime)
//	{
//		String^ errMsg = String::Empty;
//
//		try
//		{
//			// Check site index validity
//			if (siteIndex >= testTimeProfilingContent->Length)
//			{
//				errMsg = "Site Index out of range!";
//				errMsg += "\n File: " + __FILE__ + "\n Function: " + __FUNCTION__ + "\n Line: " + __LINE__ + "\n";
//				throw gcnew Aemulus::Hardware::AlarmException();
//			}
//
//			// Check UUTOffset index validity
//			if (UUTIndex >= testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length)
//			{
//				errMsg = "UUT Index out of range!";
//				errMsg += "\n File: " + __FILE__ + "\n Function: " + __FUNCTION__ + "\n Line: " + __LINE__ + "\n";
//				throw gcnew Aemulus::Hardware::AlarmException();
//			}
//
//			// Check test number validity
//			String^ testNumberKey = testItemName + "_" + testParameterName;
//
//			if (!testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber->ContainsKey(testNumberKey))
//			{
//				RegisterTestNumber(siteIndex, testItemName, testParameterName, testMethodName); // @@@ might need to change to throw error, temporary for escapee from load phase
//			}
//
//			// Get test number index
//			int testNumberIndex = testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber[testNumberKey];
//
//			// Save test item, parameter and test method name
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testItemName = testItemName;
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testParameterName = testParameterName;
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testMethodName = testMethodName;
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testNumber = testNumberIndex;
//
//			// Save test time to collection
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testTime->Add(testTime.ToString());
//			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].d_testTime->Add(testTime);
//		}
//		catch (Exception^ ex)
//		{
//			throw gcnew Aemulus::Hardware::AlarmException(errMsg, -1);
//		}
//	}
//	void TestTimeProfiling::BuildFileTemplate()
//	{
//		fileTemplate = gcnew array<String^>(15);
//
//		fileTemplate[0] = "Project";
//		fileTemplate[1] = "Project Type";
//		fileTemplate[2] = "Project Description";
//		fileTemplate[3] = "Platform";
//		fileTemplate[4] = "Configuration";
//		fileTemplate[5] = "Site Configuration";
//		fileTemplate[6] = "Accessories";
//		fileTemplate[7] = "Total Site";
//		fileTemplate[8] = "Site";
//		fileTemplate[9] = "Date";
//		fileTemplate[10] = "No,";
//		fileTemplate[11] = "Test Item, TestSite";
//		fileTemplate[12] = "Test Parameter,";
//		fileTemplate[13] = "Description,";
//		fileTemplate[14] = "Average,ALL";
//	}
//	void TestTimeProfiling::WriteToFile(Site^ site)
//	{
//		int testNumberCount = 0;
//		int count = 0;
//		int idxTestNum = 10;
//		int idxTItem = 11;
//		int idxTParam = 12;
//		int idxDescription = 13;
//		int idxAverage = 14;
//
//		int insertIndex = 14;
//		int testTimeStartIndex = 15;
//		int siteIndex = site->Index;
//		int totalTestCycles = 0;
//		String^ siteConfig = String::Empty;
//		double sumTestTime_PerTestPerUUT = 0;
//		array<array<double>^>^ averageTestTime; // averageTestTime[UUTIndex][testNumber] -> value
//		array<String^>^ insert_AverageTestTime; // concat test time of all test methods
//
//#pragma region Check Aemulus Debug folder existence
//		if (!Directory::Exists(debugPath)) Directory::CreateDirectory(debugPath);
//#pragma endregion
//
//		// To insert file content
//		try
//		{
//			array<String^>^ perSiteFile = gcnew array<String^>(fileTemplate->Length);
//			Array::Copy(fileTemplate, 0, perSiteFile, 0, fileTemplate->Length);
//			siteConfig = testTimeProfilingContent[siteIndex].projectSiteConfig;
//			averageTestTime = gcnew array<array<double>^>(testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length);
//			insert_AverageTestTime = gcnew array<String^>(testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length);
//			array<double>^ overallAverage;
//
//#pragma region Build file path and name
//			String^ fileName = debugPath + "\\" + siteConfig + "_H" + tl->glob->tf.TestHead.ToString() + "_Site" + siteIndex.ToString() + ".csv";
//			StreamWriter^ wr = gcnew StreamWriter(fileName);
//			String^ content = String::Empty;
//
//			if (!File::Exists(fileName))
//			{
//				File::Delete(fileName);
//			}
//#pragma endregion
//
//#pragma region Fill in Project Info
//			perSiteFile[0] += "," + testTimeProfilingContent[siteIndex].projectName;
//			perSiteFile[1] += "," + testTimeProfilingContent[siteIndex].projectType;
//			perSiteFile[2] += "," + testTimeProfilingContent[siteIndex].projectDescription;
//			perSiteFile[3] += "," + testTimeProfilingContent[siteIndex].platform;
//			perSiteFile[4] += "," + testTimeProfilingContent[siteIndex].projectConfig;
//			perSiteFile[5] += "," + testTimeProfilingContent[siteIndex].projectSiteConfig;
//			perSiteFile[6] += "," + testTimeProfilingContent[siteIndex].accessories;
//			perSiteFile[7] += "," + testTimeProfilingContent[siteIndex].projectTotalSite;
//			perSiteFile[8] += "," + testTimeProfilingContent[siteIndex].siteNum;
//			perSiteFile[9] += "," + testTimeProfilingContent[siteIndex].testRunDate;
//#pragma endregion
//
//			// Posting all test time collection content
//			for (int UUTIndex = 0; UUTIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length; UUTIndex++)
//			{
//				averageTestTime[UUTIndex] = gcnew array<double>(testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length);
//				testNumberCount = testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length;
//
//				for (int testIndex = 0; testIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length; testIndex++)
//				{
//					if (UUTIndex == 0)
//					{
//						perSiteFile[idxTestNum] += "," + (testIndex + 1).ToString();
//						perSiteFile[idxTItem] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testItemName;
//						perSiteFile[idxTParam] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testParameterName;
//						perSiteFile[idxDescription] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testMethodName;
//					}
//
//					if (testIndex == 0)
//					{
//						int testCycle = testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count;
//						Array::Resize(perSiteFile, perSiteFile->Length + testCycle);
//					}
//
//					if (UUTIndex == 0 && testIndex == 0) count = 1;
//
//					int idxTestTime = 15 + (UUTIndex * testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count);
//					sumTestTime_PerTestPerUUT = 0;
//
//					if (testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count == 0)
//					{
//						if (testIndex == 0)
//						{
//							if (siteConfig->Contains("True") || siteConfig->Contains("Index"))
//							{
//								perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
//							}
//							else if (siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
//							{
//								perSiteFile[idxTestTime] = count.ToString() + "," + UUTIndex.ToString();
//							}
//							else if (siteConfig->Contains("Single"))
//							{
//								if (Convert::ToInt32(testTimeProfilingContent[siteIndex].projectTotalSite) > 1)
//								{
//									perSiteFile[idxTestTime] = count.ToString() + "," + UUTIndex.ToString();
//								}
//								else
//								{
//									perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
//								}
//							}
//
//							count++;
//						}
//
//						for (int i = 0; i < totalTestCycles; i++)
//						{
//							perSiteFile[idxTestTime] += ",-";
//							idxTestTime++;
//						}
//					}
//					else
//					{
//						totalTestCycles = 0;
//					}
//
//					for (int i = 0; i < testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count; i++)
//					{
//						sumTestTime_PerTestPerUUT += testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].d_testTime[i];
//
//						if (testIndex == 0)
//						{
//							if (siteConfig->Contains("True") || siteConfig->Contains("Index"))
//							{
//								perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
//							}
//							else if (siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
//							{
//								perSiteFile[idxTestTime] = count.ToString() + "," + UUTIndex.ToString();
//							}
//							else if (siteConfig->Contains("Single"))
//							{
//								if (Convert::ToInt32(testTimeProfilingContent[siteIndex].projectTotalSite) > 1)
//								{
//									perSiteFile[idxTestTime] = count.ToString() + "," + UUTIndex.ToString();
//								}
//								else
//								{
//									perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
//								}
//							}
//
//							count++;
//						}
//
//						perSiteFile[idxTestTime] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime[i];
//						idxTestTime++;
//						totalTestCycles++;
//					}
//
//					averageTestTime[UUTIndex][testIndex] = (sumTestTime_PerTestPerUUT / testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count);
//					testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].averageTime = averageTestTime[UUTIndex][testIndex].ToString();
//				}
//			}
//
//			// Posting average values
//			for (int UUTIndex = testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length - 1; UUTIndex >= 0; UUTIndex = UUTIndex - 1)
//			{
//				if (siteConfig->Contains("True") || siteConfig->Contains("Index"))
//				{
//					// Per Site Average
//					String^ AverageSiteTestTime = "Average Site" + siteIndex.ToString() + "," + siteIndex.ToString();
//					for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
//					{
//						AverageSiteTestTime += "," + averageTestTime[UUTIndex][testIndex].ToString();
//					}
//
//					insert_AverageTestTime[UUTIndex] = AverageSiteTestTime;
//				}
//				else if (siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
//				{
//					// Per Site Average
//					String^ AverageSiteTestTime = "Average Site" + UUTIndex.ToString() + "," + UUTIndex.ToString();
//					for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
//					{
//						AverageSiteTestTime += "," + averageTestTime[UUTIndex][testIndex].ToString();
//					}
//
//					insert_AverageTestTime[UUTIndex] = AverageSiteTestTime;
//				}
//				else if (siteConfig->Contains("Single"))
//				{
//					if (Convert::ToInt32(testTimeProfilingContent[siteIndex].projectTotalSite) > 1)
//					{
//						// Per Site Average
//						String^ AverageSiteTestTime = "Average Site" + UUTIndex.ToString() + "," + UUTIndex.ToString();
//						for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
//						{
//							AverageSiteTestTime += "," + averageTestTime[UUTIndex][testIndex].ToString();
//						}
//
//						insert_AverageTestTime[UUTIndex] = AverageSiteTestTime;
//					}
//					else
//					{
//
//					}
//
//					// Overall Average
//					//for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
//					//{
//					//	perSiteFile[idxAverage] += "," + averageTestTime[UUTIndex][testIndex].ToString();
//					//}
//
//				}
//			}
//
//			// Calculate overall average - Mainly for MultiSite/MultiUUT
//			overallAverage = gcnew array<double>(testNumberCount);
//			for (int testIndex = 0; testIndex < testNumberCount; testIndex++)
//			{
//				double sumOfAverage = 0;
//				for (int UUTIndex = 0; UUTIndex < averageTestTime->Length; UUTIndex++)
//				{
//					sumOfAverage += averageTestTime[UUTIndex][testIndex];
//				}
//
//				overallAverage[testIndex] = sumOfAverage / (averageTestTime->Length); // Average out from each sites
//			}
//
//			// Upload overall average to perSiteFile content
//			for (int testIndex = 0; testIndex < testNumberCount; testIndex++)
//			{
//				perSiteFile[idxAverage] += "," + overallAverage[testIndex].ToString();
//			}
//
//			// Consolidate file content
//			for (int i = 0; i < perSiteFile->Length; i++)
//			{
//
//				if (i == 15)
//				{
//					if (siteConfig->Contains("Index") || siteConfig->Contains("True") || siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
//					{
//						for (int j = 0; j < insert_AverageTestTime->Length; j++)
//						{
//							content += insert_AverageTestTime[j] + "\n";
//						}
//					}
//					else if (siteConfig->Contains("Single"))
//					{
//						if (Convert::ToInt32(testTimeProfilingContent[siteIndex].projectTotalSite) > 1)
//						{
//							for (int j = 0; j < insert_AverageTestTime->Length; j++)
//							{
//								content += insert_AverageTestTime[j] + "\n";
//							}
//						}
//						// Do nothing as the average test time is already written in "perSiteFile" variable
//					}
//				}
//
//				content += perSiteFile[i] + "\n";
//			}
//
//			wr->Write(content);
//			wr->Close();
//		}
//		catch (Exception^ ex)
//		{
//			throw gcnew Aemulus::Hardware::AlarmException(ex->Message->ToString(), -1);
//		}
//	}
//	void TestTimeProfiling::QueryStartTime()
//	{
//		QueryPerformanceCounter(startTime);
//	}
//	void TestTimeProfiling::QueryStopTime()
//	{
//		QueryPerformanceCounter(stopTime);
//
//		if (startTime != nullptr)
//		{
//
//		}
//	}
#pragma endregion previous

TestTimeProfiling::TestTimeProfiling(TestFunction^ testFunc)
{
	tl = testFunc;
	BuildFileTemplate();
	//QueryPerformanceFrequency(&systemFreq);
}

int TestTimeProfiling::InitializeProgram(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead)
{
#pragma region Variable Initialization
	int ret = 0;

	int currentSiteIndex = site->Index;
	int totalSiteCount = site->FlowEngine->Sites->Count;
	int totalSiteStage = site->FlowEngine->SiteGroupManager->SiteStages->Count;
	int totalUUTOffset = site->UUTOffsetResolver->UUTOffsets->Count;
	int totalTPCount = 0;

	cumulativeTestNumberCount = gcnew array<int>(totalUUTOffset);
	for (int i = 0; i < cumulativeTestNumberCount->Length; i++)
	{
		cumulativeTestNumberCount[i] = 0;
	}
#pragma endregion

	// Count number of test parameters
	for each(AFlowItem^ afi in site->FlowItems)
	{
		if (afi->GetType() == TestItem::typeid)
		{
			TestItem^ ti = (TestItem^)afi;
			totalTPCount += ti->TestParameters->Count;
		}
	}

	// Initialize test time profile collection
	testTimeProfilingContent = gcnew array<ProfileContent>(totalSiteCount); // Temporary hard code for 4 sites
	for (int siteIndex = 0; siteIndex < testTimeProfilingContent->Length; siteIndex++)
	{
		testTimeProfilingContent[siteIndex].isActive = false;
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent = gcnew array<TestItemMethod>(totalUUTOffset);
		//testTimeProfilingContent[i].testParameterNumber = gcnew Dictionary<String^, int>();
		//testTimeProfilingContent[i].testNumberContent = gcnew array<TestItemMethod>(totalTPCount);
		testTimeProfilingContent[siteIndex].testHeadNum = site->FlowEngine->HeadNumber;
		testTimeProfilingContent[siteIndex].projectName = site->Flow->Name;

		for (int UUTIndex = 0; UUTIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length; UUTIndex++)
		{
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].UUTNumber = UUTIndex;
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber = gcnew Dictionary<String^, int>();
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection = gcnew array<TestTimeCollection>(totalTPCount);

			for (int testIndex = 0; testIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length; testIndex++)
			{
				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime = gcnew List<String^>();
				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].d_testTime = gcnew List<double>();
			}
		}

		/*
		for (int j = 0; j < testTimeProfilingContent[siteIndex].testNumberContent->Length; j++)
		{
		testTimeProfilingContent[siteIndex].testNumberContent[j].UUT_TestTimeCollection = gcnew array<TestTimeCollection>(totalUUTOffset);
		for (int k = 0; k < testTimeProfilingContent[siteIndex].testNumberContent[j].UUT_TestTimeCollection->Length; k++)
		{
		testTimeProfilingContent[siteIndex].testNumberContent[j].UUT_TestTimeCollection[k].testTime = gcnew List<String^>();
		}
		}
		*/
	}

	// Load config file
	RetrieveProjectConfig(site);

	// Register test item, parameter and test method name with respective test number
	for each(AFlowItem^ afi in site->FlowItems)
	{
		if (afi->GetType() == TestItem::typeid)
		{
			TestItem^ ti = (TestItem^)afi;
			String^ testItemName = ti->Name;
			String^ testParameterName = String::Empty;

			for each(TestParameter^ tp in ti->TestParameters)
			{
				testParameterName = tp->Name;
				String^ testMethodName = String::Empty;
				//if (tf_TPCondition_Exist(testParameterName, "TestMethod"))
				if (tp->Conditions->ContainsKey("TestMethod"))
				{
					//testMethodName = (String^) tf_TestParameter_ConditionCast(testParameterName, "TestMethod");
					testMethodName = (String^)tp->Conditions["TestMethod"][site]->Value;
				}
				RegisterTestNumber(currentSiteIndex, testItemName, testParameterName, testMethodName);
			}
		}
	}

	return ret;
}
void TestTimeProfiling::RetrieveProjectConfig(Site^ site)
{
#pragma region Variable Initialization
	String^ errMsg = String::Empty;

	int NumberOfUUTCount = 0;
	int NumberOfHeadCount = 0;
	String^ siteConfigXMLPath = String::Empty;

	String^ testerPlatform = String::Empty;
	String^ testerConfig = String::Empty;
	String^ testerSiteConfig = String::Empty;

	XmlDocument^ siteConfigInfo = gcnew XmlDocument();
	XmlDocument^ sitePortInfo = gcnew XmlDocument();
#pragma endregion

#pragma region "Retrieve Site Config"
	try
	{
		siteConfigXMLPath = site->GetExternalDependency("RFSiteConfigInfo");
		siteConfigInfo->Load(siteConfigXMLPath);
		XmlNode^ xmlInfo = siteConfigInfo->DocumentElement->FirstChild;

		array<String^>^ childNodes = gcnew array<String^>(xmlInfo->ChildNodes->Count);
		array<String^>^ innerTexts = gcnew array<String^>(xmlInfo->ChildNodes->Count);

		for (int i = 0; i < xmlInfo->ChildNodes->Count; i++)
		{
			childNodes[i] = xmlInfo->ChildNodes[i]->Name;
			innerTexts[i] = xmlInfo->ChildNodes[i]->InnerText;

			if (childNodes[i] == "SiteConfiguration")
			{
				testerSiteConfig = innerTexts[i];
				tl->WriteToTcrLgr("0", childNodes[i] + ": " + testerSiteConfig);
			}
			else if (childNodes[i] == "TotalUUTCount_PerHead_PerSite")
			{
				NumberOfUUTCount = int::Parse(innerTexts[i]);

				// Check error for techFlow site UUTOffset count vs user input number of UUTOffset
				if (site->UUTOffsetResolver->UUTOffsets->Count != NumberOfUUTCount)
				{
					errMsg = "TechFlow Site number of UUTOffset mismatch to Project Site config.";
					throw gcnew Aemulus::Hardware::AlarmException();
				}

				tl->WriteToTcrLgr("0", childNodes[i] + ": " + NumberOfUUTCount.ToString());
			}
			else if (childNodes[i] == "TotalHeadCount")
			{
				NumberOfHeadCount = int::Parse(innerTexts[i]);
				tl->WriteToTcrLgr("0", childNodes[i] + ": " + NumberOfHeadCount.ToString());
			}
		}

		for (int i = 0; i < testTimeProfilingContent->Length; i++)
		{
			testTimeProfilingContent[i].isActive = true;
			testTimeProfilingContent[i].projectSiteConfig = testerSiteConfig;
			if (testerSiteConfig->Contains("Index") || testerSiteConfig->Contains("True"))
			{
				testTimeProfilingContent[i].projectTotalSite = "-";
				testTimeProfilingContent[i].siteNum = i.ToString();
			}
			else if (testerSiteConfig->Contains("Single") || testerSiteConfig->Contains("MultiSite") || testerSiteConfig->Contains("MultiUUT"))
			{
				testTimeProfilingContent[i].projectTotalSite = NumberOfUUTCount.ToString();
				testTimeProfilingContent[i].siteNum = "-";
			}
		}
	}
	catch (Exception^ ex)
	{
		if (errMsg == String::Empty) errMsg = "External Dependency - SiteConfigInfo not found!\n" + ex->Message->ToString();
		throw gcnew Aemulus::Hardware::AlarmException(errMsg, -1);
	}
#pragma endregion

#pragma region "Retrieve Tester Type and Port Config"
	try
	{
		if (File::Exists(AMSRFConfigPath))
		{
			sitePortInfo->Load(AMSRFConfigPath);
			XmlNode^ xmlInfo = sitePortInfo->DocumentElement->FirstChild;

			for (int i = 0; i < xmlInfo->ParentNode->Attributes->Count; i++)
			{
				if (xmlInfo->ParentNode->Attributes[i]->Name == "type")
				{
					String^ tConfig = xmlInfo->ParentNode->Attributes[i]->Value;

					if (tConfig->Contains("AMB7600SR"))
					{
						testerPlatform = "AMB7600SR";
						testerConfig = tConfig->Replace("AMB7600SR", "");
					}
					else if (tConfig->Contains("AMB7600"))
					{
						testerPlatform = "AMB7600";
						testerConfig = tConfig->Replace("AMB7600", "");
					}
				}
			}
		}
		else if (tf_AppWideVariable_Exist("Platform"))
		{
			testerPlatform = (String^)tf_AppWideVariable_Cast("Platform");
		}

		for (int i = 0; i < testTimeProfilingContent->Length; i++)
		{
			testTimeProfilingContent[i].platform = testerPlatform;
			testTimeProfilingContent[i].projectConfig = testerConfig;
			testTimeProfilingContent[i].projectType = "-"; // @@@ Temporary leave blank
			testTimeProfilingContent[i].projectDescription = "-"; // @@@ Temporary leave blank
			testTimeProfilingContent[i].accessories = "-"; // @@@ Temporary leave blank
			testTimeProfilingContent[i].testRunDate = time->ToString()->Split(gcnew array<wchar_t>{' '}, StringSplitOptions::None)[0];
		}

		// Throw error if none of these info existed
		if (testerPlatform == String::Empty && testerConfig == String::Empty && testerSiteConfig == String::Empty)
		{
			throw gcnew Aemulus::Hardware::AlarmException("Fail loading project configuration files", -1);
		}
	}
	catch (Exception^ ex)
	{
		throw gcnew Aemulus::Hardware::AlarmException("Error occur in loading project setting files.\n" + ex->Message->ToString(), -1);
	}
#pragma endregion
}
void TestTimeProfiling::RegisterTestNumber(int siteIndex, String^ testItemName, String^ testParameterName, String^ testMethodName)
{
	if (siteIndex >= testTimeProfilingContent->Length)
	{
		throw gcnew Aemulus::Hardware::AlarmException("Site Index out of range!", -1);
	}

	String^ keyTestName = testItemName + "_" + testParameterName;
	for (int UUTIndex = 0; UUTIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length; UUTIndex++)
	{
		if (!testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber->ContainsKey(keyTestName))
		{
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber->Add(keyTestName, cumulativeTestNumberCount[UUTIndex]);
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testNumber = cumulativeTestNumberCount[UUTIndex];
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testMethodName = testMethodName;
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testItemName = testItemName;
			testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[cumulativeTestNumberCount[UUTIndex]].testParameterName = testParameterName;
			cumulativeTestNumberCount[UUTIndex]++;
		}
	}

}
void TestTimeProfiling::CommitTestTime(int siteIndex, String^ testItemName, String^ testParameterName, String^ testMethodName, int UUTIndex, double testTime)
{
	String^ errMsg = String::Empty;

	try
	{
		// Check site index validity
		if (siteIndex >= testTimeProfilingContent->Length)
		{
			errMsg = "Site Index out of range!";
			errMsg += "\n File: " + __FILE__ + "\n Function: " + __FUNCTION__ + "\n Line: " + __LINE__ + "\n";
			throw gcnew Aemulus::Hardware::AlarmException();
		}

		// Check UUTOffset index validity
		if (UUTIndex >= testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length)
		{
			errMsg = "UUT Index out of range!";
			errMsg += "\n File: " + __FILE__ + "\n Function: " + __FUNCTION__ + "\n Line: " + __LINE__ + "\n";
			throw gcnew Aemulus::Hardware::AlarmException();
		}

		// Check test number validity
		String^ testNumberKey = testItemName + "_" + testParameterName;

		if (!testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber->ContainsKey(testNumberKey))
		{
			RegisterTestNumber(siteIndex, testItemName, testParameterName, testMethodName); // @@@ might need to change to throw error, temporary for escapee from load phase
		}

		// Get test number index
		int testNumberIndex = testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testParamNumber[testNumberKey];

		// Save test item, parameter and test method name
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testItemName = testItemName;
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testParameterName = testParameterName;
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testMethodName = testMethodName;
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testNumber = testNumberIndex;

		// Save test time to collection
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].testTime->Add(testTime.ToString());
		testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testNumberIndex].d_testTime->Add(testTime);
	}
	catch (Exception^ ex)
	{
		throw gcnew Aemulus::Hardware::AlarmException(errMsg, -1);
	}
}
void TestTimeProfiling::BuildFileTemplate()
{
	fileTemplate = gcnew array<String^>(15);

	fileTemplate[0] = "Project";
	fileTemplate[1] = "Project Type";
	fileTemplate[2] = "Project Description";
	fileTemplate[3] = "Platform";
	fileTemplate[4] = "Configuration";
	fileTemplate[5] = "Site Configuration";
	fileTemplate[6] = "Accessories";
	fileTemplate[7] = "Total Site";
	fileTemplate[8] = "Site";
	fileTemplate[9] = "Date";
	fileTemplate[10] = "No,";
	fileTemplate[11] = "Test Item, TestSite";
	fileTemplate[12] = "Test Parameter,";
	fileTemplate[13] = "Description,";
	fileTemplate[14] = "Average,ALL";
}
void TestTimeProfiling::WriteToFile(Site^ site)
{
	int testNumberCount = 0;
	int count = 0;
	int idxTestNum = 10;
	int idxTItem = 11;
	int idxTParam = 12;
	int idxDescription = 13;
	int idxAverage = 14;

	int insertIndex = 14;
	int testTimeStartIndex = 15;
	int siteIndex = site->Index;
	int totalTestCycles = 0;
	String^ siteConfig = String::Empty;
	double sumTestTime_PerTestPerUUT = 0;
	array<array<double>^>^ averageTestTime; // averageTestTime[UUTIndex][testNumber] -> value
	array<String^>^ insert_AverageTestTime; // concat test time of all test methods

#pragma region Check Aemulus Debug folder existence
	if (!Directory::Exists(debugPath)) Directory::CreateDirectory(debugPath);
#pragma endregion

	// To insert file content
	try
	{
		array<String^>^ perSiteFile = gcnew array<String^>(fileTemplate->Length);
		Array::Copy(fileTemplate, 0, perSiteFile, 0, fileTemplate->Length);
		siteConfig = testTimeProfilingContent[siteIndex].projectSiteConfig;
		averageTestTime = gcnew array<array<double>^>(testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length);
		insert_AverageTestTime = gcnew array<String^>(testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length);
		array<double>^ overallAverage;

#pragma region Build file path and name
		String^ fileName = debugPath + "\\" + siteConfig + "_H" + tl->glob->tf.TestHead.ToString() + "_Site" + siteIndex.ToString() + ".csv";
		StreamWriter^ wr = gcnew StreamWriter(fileName);
		String^ content = String::Empty;

		if (!File::Exists(fileName))
		{
			File::Delete(fileName);
		}
#pragma endregion

#pragma region Fill in Project Info
		perSiteFile[0] += "," + testTimeProfilingContent[siteIndex].projectName;
		perSiteFile[1] += "," + testTimeProfilingContent[siteIndex].projectType;
		perSiteFile[2] += "," + testTimeProfilingContent[siteIndex].projectDescription;
		perSiteFile[3] += "," + testTimeProfilingContent[siteIndex].platform;
		perSiteFile[4] += "," + testTimeProfilingContent[siteIndex].projectConfig;
		perSiteFile[5] += "," + testTimeProfilingContent[siteIndex].projectSiteConfig;
		perSiteFile[6] += "," + testTimeProfilingContent[siteIndex].accessories;
		perSiteFile[7] += "," + testTimeProfilingContent[siteIndex].projectTotalSite;
		perSiteFile[8] += "," + testTimeProfilingContent[siteIndex].siteNum;
		perSiteFile[9] += "," + testTimeProfilingContent[siteIndex].testRunDate;
#pragma endregion

		// Posting all test time collection content
		for (int UUTIndex = 0; UUTIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length; UUTIndex++)
		{
			averageTestTime[UUTIndex] = gcnew array<double>(testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length);
			testNumberCount = testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length;

			for (int testIndex = 0; testIndex < testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection->Length; testIndex++)
			{
				if (UUTIndex == 0)
				{
					perSiteFile[idxTestNum] += "," + (testIndex + 1).ToString();
					perSiteFile[idxTItem] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testItemName;
					perSiteFile[idxTParam] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testParameterName;
					perSiteFile[idxDescription] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testMethodName;
				}

				if (testIndex == 0)
				{
					int testCycle = testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count;
					Array::Resize(perSiteFile, perSiteFile->Length + testCycle);
				}

				if (UUTIndex == 0 && testIndex == 0) count = 1;

				int idxTestTime = 15 + (UUTIndex * testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count);
				sumTestTime_PerTestPerUUT = 0;

				if (testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count == 0)
				{
					if (testIndex == 0)
					{
						if (siteConfig->Contains("True") || siteConfig->Contains("Index"))
						{
							perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
						}
						else if (siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
						{
							perSiteFile[idxTestTime] = count.ToString() + "," + UUTIndex.ToString();
						}
						else if (siteConfig->Contains("Single"))
						{
							perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
						}

						count++;
					}

					for (int i = 0; i < totalTestCycles; i++)
					{
						perSiteFile[idxTestTime] += ",-";
						idxTestTime++;
					}
				}
				else
				{
					totalTestCycles = 0;
				}

				for (int i = 0; i < testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count; i++)
				{
					sumTestTime_PerTestPerUUT += testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].d_testTime[i];

					if (testIndex == 0)
					{
						if (siteConfig->Contains("True") || siteConfig->Contains("Index"))
						{
							perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
						}
						else if (siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
						{
							perSiteFile[idxTestTime] = count.ToString() + "," + UUTIndex.ToString();
						}
						else if (siteConfig->Contains("Single"))
						{
							perSiteFile[idxTestTime] = count.ToString() + "," + siteIndex.ToString();
						}

						count++;
					}

					perSiteFile[idxTestTime] += "," + testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime[i];
					idxTestTime++;
					totalTestCycles++;
				}

				averageTestTime[UUTIndex][testIndex] = (sumTestTime_PerTestPerUUT / testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].testTime->Count);
				testTimeProfilingContent[siteIndex].UUT_TestNumberContent[UUTIndex].testNumberTimeCollection[testIndex].averageTime = averageTestTime[UUTIndex][testIndex].ToString();
			}
		}

		// Posting average values
		for (int UUTIndex = testTimeProfilingContent[siteIndex].UUT_TestNumberContent->Length - 1; UUTIndex >= 0; UUTIndex = UUTIndex - 1)
		{
			if (siteConfig->Contains("True") || siteConfig->Contains("Index"))
			{
				// Per Site Average
				String^ AverageSiteTestTime = "Average Site" + siteIndex.ToString() + "," + siteIndex.ToString();
				for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
				{
					AverageSiteTestTime += "," + averageTestTime[UUTIndex][testIndex].ToString();
				}

				insert_AverageTestTime[UUTIndex] = AverageSiteTestTime;
			}
			else if (siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
			{
				// Per Site Average
				String^ AverageSiteTestTime = "Average Site" + UUTIndex.ToString() + "," + UUTIndex.ToString();
				for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
				{
					AverageSiteTestTime += "," + averageTestTime[UUTIndex][testIndex].ToString();
				}

				insert_AverageTestTime[UUTIndex] = AverageSiteTestTime;
			}
			else if (siteConfig->Contains("Single"))
			{
				// Overall Average
				//for (int testIndex = 0; testIndex < averageTestTime[UUTIndex]->Length; testIndex++)
				//{
				//	perSiteFile[idxAverage] += "," + averageTestTime[UUTIndex][testIndex].ToString();
				//}

			}
		}

		// Calculate overall average - Mainly for MultiSite/MultiUUT
		overallAverage = gcnew array<double>(testNumberCount);
		for (int testIndex = 0; testIndex < testNumberCount; testIndex++)
		{
			double sumOfAverage = 0;
			for (int UUTIndex = 0; UUTIndex < averageTestTime->Length; UUTIndex++)
			{
				sumOfAverage += averageTestTime[UUTIndex][testIndex];
			}

			overallAverage[testIndex] = sumOfAverage / (averageTestTime->Length); // Average out from each sites
		}

		// Upload overall average to perSiteFile content
		for (int testIndex = 0; testIndex < testNumberCount; testIndex++)
		{
			perSiteFile[idxAverage] += "," + overallAverage[testIndex].ToString();
		}

		// Consolidate file content
		for (int i = 0; i < perSiteFile->Length; i++)
		{

			if (i == 15)
			{
				if (siteConfig->Contains("Index") || siteConfig->Contains("True") || siteConfig->Contains("MultiSite") || siteConfig->Contains("MultiUUT"))
				{
					for (int j = 0; j < insert_AverageTestTime->Length; j++)
					{
						content += insert_AverageTestTime[j] + "\n";
					}
				}
				else if (siteConfig->Contains("Single"))
				{
					// Do nothing as the average test time is already written in "perSiteFile" variable
				}
			}

			content += perSiteFile[i] + "\n";
		}

		wr->Write(content);
		wr->Close();
	}
	catch (Exception^ ex)
	{
		throw gcnew Aemulus::Hardware::AlarmException(ex->Message->ToString(), -1);
	}
}
void TestTimeProfiling::QueryStartTime()
{
	QueryPerformanceCounter(startTime);
}
void TestTimeProfiling::QueryStopTime()
{
	QueryPerformanceCounter(stopTime);

	if (startTime != nullptr)
	{

	}
}

}



