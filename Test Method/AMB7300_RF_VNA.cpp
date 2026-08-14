//include "..\\TestProgram.h"
//
//namespace Functions
//{
//
////	int AMB7300TestLibrary::CM_VNA_VnaConfig(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
////	{
////		/*****************************************************************************************************
////		** CM_VNA_VnaConfig
////		** Arguments:
////		**
////		**
////		**
////		**
////		** Descriptions:
////		**
////		**
////		**
////		******************************************************************************************************/
////
////		try
////		{
////			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
////			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method VNACase_VnaConfig");
////
////			//Control Method Compulsory Variable
////			String^ sourceChannel = nullptr;
////			double sourceFreq = 0.0;
////			double sourcePin = 0.0;
////
////			//Control Method Option Variable
////			double sourceAttenuation = 999.99;
////			String ^ inputBoardLossItem = nullptr;
////			double inputBoardLoss = 0.0;
////			double inputExtAtt = 0.0;
////
////			//Operation Variable
////			double ActualSourcePower = 0;
////			String^ ErrorMessage = nullptr;
////			String ^ CM = "VNA_VnaConfig_";
////			bool UserInputSourceAttenuation = false;
////
////#pragma region "Test Condition Casting"
////
////			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
////
////			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();
////
////			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
////			{
////				ConditionInfo = testConditionCollection["SourceChannel"][site];
////				sourceChannel = (String^)ConditionInfo->Value;
////			}
////			else
////			{
////				ErrorMessage = "Test Condition [" + CM + "SourceChannel" + "] is not found.";
////				throw gcnew Exception(ErrorMessage);
////			}
////			if ((bool)testConditionCollection->ContainsKey("SourceFreq"))
////			{
////				ConditionInfo = testConditionCollection["SourceFreq"][site];
////				sourceFreq = (double)ConditionInfo->Value;
////			}
////			else
////			{
////				ErrorMessage = "Test Condition [" + CM + "SourceFreq" + "] is not found.";
////				throw gcnew Exception(ErrorMessage);
////			}
////			if ((bool)testConditionCollection->ContainsKey("SourcePin"))
////			{
////				ConditionInfo = testConditionCollection["SourcePin"][site];
////				sourcePin = (double)ConditionInfo->Value;
////			}
////			else
////			{
////				ErrorMessage = "Test Condition [" + CM + "SourcePin" + "] is not found.";
////				throw gcnew Exception(ErrorMessage);
////			}
////
////			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
////
////			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
////			{
////				ConditionInfo = testConditionCollection["SourceAttenuation"][site];
////				sourceAttenuation = (double)ConditionInfo->Value;
////				UserInputSourceAttenuation = true;
////			}
////
////			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
////			{
////				ConditionInfo = testConditionCollection["InputBoardLossItem"][site];
////				inputBoardLossItem = (String^)ConditionInfo->Value;
////
////				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
////				{
////					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
////				}
////				else
////				{
////					ErrorMessage = "Test Condition [" + CM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
////					throw gcnew Exception(ErrorMessage);
////				}
////			}
////
////			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
////			{
////				ConditionInfo = testConditionCollection["InputExtAtt"][site];
////				inputExtAtt = (double)ConditionInfo->Value;
////			}
////
////#pragma endregion "Test Condition Casting"
////
////#pragma region "Test"
////
////			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
////			RF_LoadHardwareProfile(testSite);
////
////			tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus = sourcePin;
////			tl->glob->SourcePower_Status[testSite].SourceFreqPreStatus = sourceFreq;
////
////			ActualSourcePower = sourcePin + inputBoardLoss + inputExtAtt;
////
////			if (UserInputSourceAttenuation == false)
////			{
////				RF_SourcePower(testSite, sourceChannel, ActualSourcePower, sourceFreq);
////			}
////			else
////			{
////				RF_SourcePower(testSite, sourceChannel, ActualSourcePower, sourceFreq, sourceAttenuation);
////			}
////
////			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SourcePower");
////
////#pragma endregion "Test"
////			int startFreqCount = 0;
////			int stopFreqCount = 0;
////			int pointsCount = 0;
////			int ifbwCount = 0;
////			int powerCount = 0;
////			int delayCount = 0;
////			int segmentSetCount = 0;
////
////			conditionCollection = tf_FlowStep_ConditionList(tl->glob->currentSubItemName[siteIndex]);
////			for each (condition in conditionCollection)
////			{
////				if (condition->Name->Contains(VnaConfigConditionName_StratFreq))
////					startFreqCount++;
////
////				if (condition->Name->Contains(VnaConfigConditionName_StopFreq))
////					stopFreqCount++;
////
////				if (condition->Name->Contains(VnaConfigConditionName_Points))
////					pointsCount++;
////
////				if (condition->Name->Contains(VnaConfigConditionName_Ifbw))
////					ifbwCount++;
////
////				if (condition->Name->Contains(VnaConfigConditionName_Power))
////					powerCount++;
////
////				if (condition->Name->Contains(VnaConfigConditionName_Delay))
////					delayCount++;
////			}
////
////			// [CHECKING] Segment setting's conditions
////			if ((startFreqCount != stopFreqCount) ||
////				(startFreqCount != pointsCount) ||
////				(startFreqCount != ifbwCount) ||
////				(startFreqCount != powerCount) ||
////				(startFreqCount != delayCount))
////			{
////				ret = ER_CONST_VNACONFIG_CONDITION_SEGMENT_SET_INVALID;
////				amb7300tl->tl->WriteToTracerLogger(tfSite, siteIndex, WARNING, "[VnaConfig] VNA segment set invalid. 1x of complete segment set contains 'StartFreq' & 'StopFreq' & 'Points' & 'Ifbw' & 'Power' & 'Delay'." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
////				amb7300tl->tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "[VnaConfig] VNA segment set invalid. 1x of complete segment set contains 'StartFreq' & 'StopFreq' & 'Points' & 'Ifbw' & 'Power' & 'Delay'." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
////				goto EndOfTest;
////			}
////			else
////			{
////				segmentSetCount = startFreqCount;
////			}
////
////			for (int l_siteIndex = 0; l_siteIndex < tl->glob->tf.NumberOfTestSites; l_siteIndex++)
////			{
////				if (site->UUTOffsetResolver->UUTOffsets[l_siteIndex]->Active)
////				{
////					// Cast condition from 'VnaConfig' & perform the rest of the necessary settings @ AMB7300Utility
////					ret = TestLib_ControlStep_VnaConfig_CastCondition(site, tfSite, l_siteIndex, segmentSetCount);
////					if (ret != 0) goto EndOfTest;
////
////					ret = CheckConditionChange_VnaConfig(site, tfSite, l_siteIndex, segmentSetCount);
////					if (ret != 0) goto EndOfTest;
////				}
////			}
////
////			// Execute 'VnaConfig' phase @ AMB7300
////			ret = amb7300tl->VnaConfig(tfSite, vnaSiteIndex);
////			if (ret != 0) goto EndOfTest;
////		}
////		catch (Exception ^ ex)
////		{
////			String ^ methodType = "CM_";
////			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
////			tl->UpdateTestResultsWhenException(site, testSite);
////			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
////		}
////	}
////
//}