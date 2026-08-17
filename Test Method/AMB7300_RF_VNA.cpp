#include "..\\TestProgram.h"

namespace Functions
{

	void AMB7300TestLibrary::CM_VNA_VnaConfig(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_VNA_VnaConfig
		** Arguments:
		**
		**
		**
		**
		** Descriptions:
		**
		**
		**
		******************************************************************************************************/
		int ret = 0;

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method VNACase_VnaConfig");

			//Control Method Compulsory Variable
			int startFreqCount = 0;
			int stopFreqCount = 0;
			int pointsCount = 0;
			int ifbwCount = 0;
			int powerCount = 0;
			int delayCount = 0;
			int segmentSetCount = 0;

			//Control Method Option Variable

			//Operation Variable
			String^ ErrorMessage = nullptr;
			String ^ CM = "VnaConfig_";
#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			for each (Condition ^ condition in testConditionCollection)
			{
				if (condition->Name->Contains(VnaConfigConditionName_StratFreq))
					startFreqCount++;

				if (condition->Name->Contains(VnaConfigConditionName_StopFreq))
					stopFreqCount++;

				if (condition->Name->Contains(VnaConfigConditionName_Points))
					pointsCount++;

				if (condition->Name->Contains(VnaConfigConditionName_Ifbw))
					ifbwCount++;

				if (condition->Name->Contains(VnaConfigConditionName_Power))
					powerCount++;

				if (condition->Name->Contains(VnaConfigConditionName_Delay))
					delayCount++;
			}

			// [CHECKING] Segment setting's conditions
			if ((startFreqCount != stopFreqCount) ||
				(startFreqCount != pointsCount) ||
				(startFreqCount != ifbwCount) ||
				(startFreqCount != powerCount) ||
				(startFreqCount != delayCount))
			{
				ret = ER_CONST_VNACONFIG_CONDITION_SEGMENT_SET_INVALID;
				tl->WriteToTcrLgr("SITE " + testSite.ToString(), "VNA segment set invalid. 1x of complete segment set contains 'StartFreq' & 'StopFreq' & 'Points' & 'Ifbw' & 'Power' & 'Delay'." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				//tl->WriteToTracerAndFileLogger(testSite, testSite, WARNING, "[VnaConfig] ");
			}
			else
			{
				segmentSetCount = startFreqCount;
			}

			//for (int l_siteIndex = 0; l_siteIndex < tl->glob->tf.NumberOfTestSites; l_siteIndex++)
			{
				//if (site->UUTOffsetResolver->UUTOffsets[l_siteIndex]->Active)
				{
					// Cast condition from 'VnaConfig' & perform the rest of the necessary settings @ AMB7300Utility
					ret = TestLib_ControlStep_VnaConfig_CastCondition(site, testSite, testSite, segmentSetCount);

					ret = CheckConditionChange_VnaConfig(site, testSite, testSite, segmentSetCount);
				}
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//RF_LoadHardwareProfile(testSite);

			// Execute 'VnaConfig' phase @ AMB7300
			ret = VnaConfig(testSite, testSite);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method VNACase_VnaConfig");

#pragma endregion "Test"
			

		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}

	void AMB7300TestLibrary::CM_VNA_VnaFetch(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_VNA_VnaFetch
		** Arguments:
		**
		**
		**
		**
		** Descriptions:
		**
		**
		**
		******************************************************************************************************/
		int ret = 0;

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method VNACase_VnaFetch");

			//Control Method Compulsory Variable

			//Control Method Option Variable

			//Operation Variable
			String^ ErrorMessage = nullptr;
			String ^ CM = "VnaFetch_";
#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			//for (int l_siteIndex = 0; l_siteIndex < tl->glob->tf.NumberOfTestSites; l_siteIndex++)
			{
				//if (site->UUTOffsetResolver->UUTOffsets[l_siteIndex]->Active)
				{
					// Cast condition from 'VnaFetch' & perform the rest of the necessary settings @ AMB7300Utility
					ret = TestLib_ControlStep_VnaFetch_CastCondition(site, testSite, testSite);
				}
			}

			///////////////////////////////Sequential//////////////////////////////////

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//RF_LoadHardwareProfile(testSite);

			// Execute 'VnaFetch' phase @ AMB7300
			ret = VnaFetch_TrueParallel(testSite, testSite);

			ret = SaveToTouchstoneFile(site, testSite, testSite);

			///////////////////////////////Sequential//////////////////////////////////
			
			//// Execute 'VnaFetch' phase @ AMB7300
			//ret = amb7300tl->VnaFetch(tfSite, siteIndex);
			//if (ret != 0) goto EndOfTest;

			//if (tl->glob->AWV.EnableSaveSnpData == true && amb7300tl->saveRecallSetting->EnableSaveSnpData == true)
			//{
			//	ret = amb7300tl->SaveToTouchstoneFile(site, tfSite, siteIndex);
			//	if (ret != 0) goto EndOfTest;
			//}
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method VNACase_VnaFetch");

#pragma endregion "Test"


		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7300TestLibrary::TM_VNA_VnaDataAnalysis(Site ^ site, int testSite,  String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_VNA_VnaDataAnalysis
		** Arguments:
		**
		**
		**
		**
		** Descriptions:
		**
		**
		**
		******************************************************************************************************/
		int ret = 0;

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method VNACase_VnaDataAnalysis");

			//Test Method Compulsory Variable

			//Test Method Option Variable

			//Operation Variable
			double Pout = 0.0;
			String ^ TM = "VnaDataAnalysis_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			// Cast condition from 'VnaDataAnalysis' @ AMB7300Utility
			ret = TestLib_TestParameter_VnaDataAnalysis_CastCondition(site, testSite, testSite);
			
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 1;
			int ResultCount = 0;
			array<double>^ ResultArr = gcnew array<double >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, double> ^ Result = gcnew Dictionary<String^, double>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//RF_LoadHardwareProfile(testSite);

			//for (int l_siteIndex = 0; l_siteIndex < tl->glob->tf.NumberOfTestSites; l_siteIndex++)
			{
				//if (site->UUTOffsetResolver->UUTOffsets[l_siteIndex]->Active)
				{
					// Execute 'VnaDataAnalysis' phase @ AMB7300
					VnaDataAnalysis_TrueParallel(testSite, testSite, ResultArr[0]);

					//// Save to result object
					//TPtestResult[l_siteIndex, resultIndex[l_siteIndex]] = result[l_siteIndex];
					//resultIndex[l_siteIndex]++;
				}
			}

			ResultCount = 1;

			Result->Clear();
			ResultCount = 0;
			Result->Add("VnaDataAnalysis", ResultArr[ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			//RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			////Result Storing
			//if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			//{
			//	for (int i = 0; i<UserDesiredResult->Length; i++)
			//	{
			//		tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
			//	}
			//}
			//else
			//{
			//	tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			//}

			//if (UserDesiredResult->Length != 0)
			//{
			//	testParameterCount = UserDesiredResult->Length;
			//}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method VNACase_VnaDataAnalysis");

#pragma endregion "Update Test Result"

		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
}