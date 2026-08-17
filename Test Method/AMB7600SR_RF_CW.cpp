#include "..\\TestProgram.h"

namespace Functions
{
	//Control Methods
	void AMB7600SRTestLibrary::CM_RF_SourcePower(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SourcePower");

			//Control Method Compulsory Variable
			String^ sourceChannel = nullptr;
			double sourceFreq = 0.0;
			double sourcePin = 0.0;

			//Control Method Option Variable
			double sourceAttenuation = 999.99;
			String ^ inputBoardLossItem = nullptr;
			double inputBoardLoss = 0.0;
			double inputExtAtt = 0.0;

			//Operation Variable
			double ActualSourcePower = 0;
			String^ ErrorMessage = nullptr;
			String ^ CM = "SourcePower_";
			bool UserInputSourceAttenuation = false;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				ConditionInfo = testConditionCollection["SourceChannel"][site];
				sourceChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceFreq"))
			{
				ConditionInfo = testConditionCollection["SourceFreq"][site];
				sourceFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourcePin"))
			{
				ConditionInfo = testConditionCollection["SourcePin"][site];
				sourcePin = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourcePin" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				ConditionInfo = testConditionCollection["SourceAttenuation"][site];
				sourceAttenuation = (double)ConditionInfo->Value;
				UserInputSourceAttenuation = true;
			}

			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				ConditionInfo = testConditionCollection["InputBoardLossItem"][site];
				inputBoardLossItem = (String^)ConditionInfo->Value;

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				ConditionInfo = testConditionCollection["InputExtAtt"][site];
				inputExtAtt = (double)ConditionInfo->Value;
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus = sourcePin;
			tl->glob->SourcePower_Status[testSite].SourceFreqPreStatus = sourceFreq;

			ActualSourcePower = sourcePin + inputBoardLoss + inputExtAtt;

			if (UserInputSourceAttenuation == false)
			{
				RF_SourcePower(testSite, sourceChannel, ActualSourcePower, sourceFreq);
			}
			else
			{
				RF_SourcePower(testSite, sourceChannel, ActualSourcePower, sourceFreq, sourceAttenuation);
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SourcePower");

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
	void AMB7600SRTestLibrary::CM_RF_SourcePowerFast(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SourcePowerFast");

			//Control Method Compulsory Variable
			String^ sourceChannel = nullptr;
			double sourceFreq = 0.0;
			double sourcePin = 0.0;

			//Test Method Option Variable
			double inputBoardLoss = 0.0;
			String ^ inputBoardLossItem = nullptr;
			double inputExtAtt = 0.0;
			double sourceAttenuation = 999.99;

			//Source Power Operation Variable		
			double ActualSourcePower = 0;
			String^ ErrorMessage = nullptr;
			String ^ CM = "SourcePowerFast_";
			bool UserInputSourceAttenuation = false;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				ConditionInfo = testConditionCollection["SourceChannel"][site];
				sourceChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceFreq"))
			{
				ConditionInfo = testConditionCollection["SourceFreq"][site];
				sourceFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourcePin"))
			{
				ConditionInfo = testConditionCollection["SourcePin"][site];
				sourcePin = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourcePin" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				ConditionInfo = testConditionCollection["InputBoardLossItem"][site];
				inputBoardLossItem = (String^)ConditionInfo->Value;

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				ConditionInfo = testConditionCollection["InputExtAtt"][site];
				inputExtAtt = (double)ConditionInfo->Value;
			}

			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				ConditionInfo = testConditionCollection["SourceAttenuation"][site];
				sourceAttenuation = (double)ConditionInfo->Value;
				UserInputSourceAttenuation = true;
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus = sourcePin;
			tl->glob->SourcePower_Status[testSite].SourceFreqPreStatus = sourceFreq;

			ActualSourcePower = sourcePin + inputBoardLoss + inputExtAtt;

			RF_SourcePowerFast(testSite, sourceChannel, ActualSourcePower, sourceFreq, UserInputSourceAttenuation, sourceAttenuation);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SourcePowerFast");

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
	void AMB7600SRTestLibrary::CM_RF_SourceTwoTone(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SourceTwoTone");

			//Control Method Compulsory Variable
			String^ sourceChannel = nullptr;
			double sourceFreq0 = 0.0;
			double sourcePin0 = 0.0;
			double sourceFreq1 = 0.0;
			double sourcePin1 = 0.0;
			double sourceAttenuation = 0.0;

			//Source Two Tone Operation Variable
			String ^ inputBoardLossItem = nullptr;
			array<double >^ inputBoardLoss = gcnew array <double>(2);
			double InputExtAtt = 0.0;
			String ^ CM = "SourceTwoTone_";
			String ^ ErrorMessage = nullptr;
			bool UserInputSourceAttenuation = false;
			double inputExtAtt = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				ConditionInfo = testConditionCollection["SourceChannel"][site];
				sourceChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceFreq0"))
			{
				ConditionInfo = testConditionCollection["SourceFreq0"][site];
				sourceFreq0 = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq0" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourcePin0"))
			{
				ConditionInfo = testConditionCollection["SourcePin0"][site];
				sourcePin0 = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourcePin0" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceFreq1"))
			{
				ConditionInfo = testConditionCollection["SourceFreq1"][site];
				sourceFreq1 = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq1" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourcePin1"))
			{
				ConditionInfo = testConditionCollection["SourcePin1"][site];
				sourcePin1 = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourcePin1" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				ConditionInfo = testConditionCollection["SourceAttenuation"][site];
				sourceAttenuation = (double)ConditionInfo->Value;
				UserInputSourceAttenuation = true;
			}

			for (int i = 0; i < 2; i++)
			{
				inputBoardLoss[i] = 0;

				if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem_" + i.ToString()))
				{
					ConditionInfo = testConditionCollection["InputBoardLossItem_" + i.ToString()][site];
					inputBoardLossItem = (String^)ConditionInfo->Value;

					if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
					{
						inputBoardLoss[i] = tl->glob->boardLoss[testSite][inputBoardLossItem];
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "InputBoardLossItem_" + i.ToString() + ": " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
						throw gcnew Exception(ErrorMessage);
					}
				}
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				ConditionInfo = testConditionCollection["InputExtAtt"][site];
				inputExtAtt = (double)ConditionInfo->Value;
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			ResetAmsrfPreviousState(testSite, true);

			tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus = sourcePin1;

			RF_LoadHardwareProfile(testSite);

			if (tl->glob->TwoToneMode == 1)
			{
				if (UserInputSourceAttenuation == true)
				{
					RF_SourceTwoTone(testSite, sourceChannel, sourcePin0 + inputBoardLoss[0] + inputExtAtt, sourceFreq0, sourcePin1 + inputBoardLoss[1] + inputExtAtt, sourceFreq1, sourceAttenuation);
				}
				else
				{
					RF_SourceTwoTone(testSite, sourceChannel, sourcePin0 + inputBoardLoss[0] + inputExtAtt, sourceFreq0, sourcePin1 + inputBoardLoss[1] + inputExtAtt, sourceFreq1);
				}
			}
			else if (tl->glob->TwoToneMode == 2)
			{
				RF_SourcePowerExternalSignalGenerator(testSite, sourcePin0 + inputBoardLoss[0] + inputExtAtt);
				RF_SourceFreqExternalSignalGenerator(testSite, sourceFreq0);
				RF_OutputEnableExternalSignalGenerator(testSite, true);

				if (UserInputSourceAttenuation == true)
				{
					RF_SourcePower(testSite, sourceChannel, sourcePin1 + inputBoardLoss[1] + inputExtAtt, sourceFreq1, sourceAttenuation);
				}
				else
				{
					RF_SourcePower(testSite, sourceChannel, sourcePin1 + inputBoardLoss[1] + inputExtAtt, sourceFreq1);
				}

				RF_RFDM621_SetInputSource(testSite, 2, 0);
				RF_RFDM621_SetMode(testSite, 2);
			}

			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] = 2;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SourceTwoTone");

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
	void AMB7600SRTestLibrary::CM_RF_SourcePowerLow(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SourcePowerLow");

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			double sourceFreq = 0.0;

			//Source Power Low Operation Variable
			String ^ CM = "SourcePowerLow_";
			double SourcePin = -120.0 dBm;
			String ^ ErrorMessage = nullptr;
			int sourceMode = (int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"];

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				ConditionInfo = testConditionCollection["SourceChannel"][site];
				sourceChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceFreq"))
			{
				ConditionInfo = testConditionCollection["SourceFreq"][site];
				sourceFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			if (sourceMode == 0 ||
				sourceMode == 1 ||
				sourceMode == 2)
			{
				RF_SourcePower(testSite, sourceChannel, SourcePin, sourceFreq);
			}
			else if (sourceMode == 3)
			{
				if (tl->glob->TwoToneMode == 1)
				{
					RF_SourceTwoTone(testSite, sourceChannel, SourcePin, sourceFreq, SourcePin, sourceFreq);
				}
				else if (tl->glob->TwoToneMode == 2)
				{
					RF_SourcePower(testSite, sourceChannel, SourcePin, sourceFreq);
					RF_OutputEnableExternalSignalGenerator(testSite, false);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SourcePowerLow");

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
	void AMB7600SRTestLibrary::CM_RF_RunSourceAlignment(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_RunSourceAlignment");

			//Test Method Compulsory Variable

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			if (tl->glob->TestSiteAmsrfType[testSite] == "AMSRF0")
			{
				if (tl->glob->SourceAlignment_Status.AMSRF0 == false)
				{
					RF_RunSourceAlignment(testSite);
					tl->glob->SourceAlignment_Status.AMSRF0 = true;
				}
			}
			else if (tl->glob->TestSiteAmsrfType[testSite] == "AMSRF1")
			{
				if (tl->glob->SourceAlignment_Status.AMSRF1 == false)
				{
					RF_RunSourceAlignment(testSite);
					tl->glob->SourceAlignment_Status.AMSRF1 = false;
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_RunSourceAlignment");

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
	void AMB7600SRTestLibrary::CM_RF_StartModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_StartModulation");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;
			String^ modulationFile = nullptr;
			int playBackMode = 0;

			//Start Modulation Operation Variable
			String ^ CM = "StartModulation_";
			String ^ PathModulationFile = nullptr;

			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ModulationFile"))
			{
				ConditionInfo = testConditionCollection["ModulationFile"][site];
				modulationFile = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModulationFile" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("PlayBackMode"))
			{
				ConditionInfo = testConditionCollection["PlayBackMode"][site];
				playBackMode = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PlayBackMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			PathModulationFile = tl->glob->ModulationFile[testSite][modulationFile];
			RF_StartModulation(testSite, moduleAlias, PathModulationFile, playBackMode);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_StartModulation");

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
	void AMB7600SRTestLibrary::CM_RF_IsolateChannel(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_IsolateChannel");

			//Control Method Compulsory Variable
			String^ channel = nullptr;

			//Start Modulation Operation Variable
			String ^ CM = "IsolateChannel_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("Channel"))
			{
				ConditionInfo = testConditionCollection["Channel"][site];
				channel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Channel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			if (channel == "AllChannel")
			{
				RF_IsolateAllChannel(testSite);
			}
			else
			{
				RF_IsolateChannel(testSite, channel);
			}

			ResetAmsrfPreviousState(testSite, true);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_IsolateChannel");

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
	void AMB7600SRTestLibrary::CM_RF_StopModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_StopModulation");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;


			//Start Modulation Operation Variable
			String ^ CM = "StopModulation_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_StopModulation(testSite, moduleAlias);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_StopModulation");

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
	void AMB7600SRTestLibrary::CM_RF_SetSourceTriggerOut(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SetSourceTriggerOut");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;
			bool enable = false;
			int trigDestination = 999;
			int trigOption = 999;

			//Start Modulation Operation Variable
			String ^ CM = "SetSourceTriggerOut_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();


			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Enable"))
			{
				ConditionInfo = testConditionCollection["Enable"][site];
				enable = (bool)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Enable" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigDestination"))
			{
				ConditionInfo = testConditionCollection["TrigDestination"][site];
				trigDestination = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigDestination" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigOption"))
			{
				ConditionInfo = testConditionCollection["TrigOption"][site];
				trigOption = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigOption" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_SetSourceTriggerOut(testSite, moduleAlias, enable, trigDestination, trigOption);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SetSourceTriggerOut");

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
	void AMB7600SRTestLibrary::CM_RF_SetSourceTriggerRouting(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SetSourceTriggerRouting");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;
			bool enable = false;
			int trigIn = 999;
			int trigOut = 999;

			//Start Modulation Operation Variable
			String ^ CM = "SetSourceTriggerRouting_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Enable"))
			{
				ConditionInfo = testConditionCollection["Enable"][site];
				enable = (bool)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Enable" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigIn"))
			{
				ConditionInfo = testConditionCollection["TrigIn"][site];
				trigIn = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigIn" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigOut"))
			{
				ConditionInfo = testConditionCollection["TrigOut"][site];
				trigOut = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigOut" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_SetSourceTriggerRouting(testSite, moduleAlias, enable, trigIn, trigOut);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SetSourceTriggerRouting");

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
	void AMB7600SRTestLibrary::CM_RF_SetMeasureTriggerRouting(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SetMeasureTriggerRouting");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;
			bool enable = false;
			int trigIn = 999;
			int trigOut = 999;

			//Start Modulation Operation Variable
			String ^ CM = "SetMeasureTriggerRouting_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();


			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Enable"))
			{
				ConditionInfo = testConditionCollection["Enable"][site];
				enable = (bool)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Enable" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigIn"))
			{
				ConditionInfo = testConditionCollection["TrigIn"][site];
				trigIn = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigIn" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigOut"))
			{
				ConditionInfo = testConditionCollection["TrigOut"][site];
				trigOut = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigOut" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_SetMeasureTriggerRouting(testSite, moduleAlias, enable, trigIn, trigOut);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SetMeasureTriggerRouting");

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
	void AMB7600SRTestLibrary::CM_RF_SetSourceTriggerIn(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SetSourceTriggerIn");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;
			bool enable = false;
			int trigSource = 999;
			int trigPolarity = 999;
			double trigDelay = 0.0;

			//Start Modulation Operation Variable
			String ^ CM = "SetSourceTriggerIn_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();


			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Enable"))
			{
				ConditionInfo = testConditionCollection["Enable"][site];
				enable = (bool)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Enable" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigSource"))
			{
				ConditionInfo = testConditionCollection["TrigSource"][site];
				trigSource = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigSource" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigPolarity"))
			{
				ConditionInfo = testConditionCollection["TrigPolarity"][site];
				trigPolarity = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigPolarity" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigDelay"))
			{
				ConditionInfo = testConditionCollection["TrigDelay"][site];
				trigDelay = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigDelay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_SetSourceTriggerIn(testSite, moduleAlias, enable, trigSource, trigPolarity, trigDelay);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SetSourceTriggerIn");

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
	void AMB7600SRTestLibrary::CM_RF_SetMeasureTriggerIn(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SetMeasureTriggerIn");

			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;
			bool enable = false;
			int trigSource = 999;
			int trigPolarity = 999;
			double trigDelay = 0.0;

			//Start Modulation Operation Variable
			String ^ CM = "SetMeasureTriggerIn_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();


			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Enable"))
			{
				ConditionInfo = testConditionCollection["Enable"][site];
				enable = (bool)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Enable" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigSource"))
			{
				ConditionInfo = testConditionCollection["TrigSource"][site];
				trigSource = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigSource" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigPolarity"))
			{
				ConditionInfo = testConditionCollection["TrigPolarity"][site];
				trigPolarity = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigPolarity" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TrigDelay"))
			{
				ConditionInfo = testConditionCollection["TrigDelay"][site];
				trigDelay = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigDelay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_SetMeasureTriggerIn(testSite, moduleAlias, enable, trigSource, trigPolarity, trigDelay);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SetMeasureTriggerIn");

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
	void AMB7600SRTestLibrary::CM_RF_LoadModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_LoadModulation");
			//tl->WriteToTracerAndFileLogger(testSite, testSite, INFO, "Executing Control Method RFCase_LoadModulation");
			
			//Control Method Compulsory Variable
			String^ moduleAlias = nullptr;

			//Start Modulation Operation Variable
			String ^ CM = "LoadModulation_";
			int StationNo = 0;
			String^ waveformFileDirectory = System::IO::Path::GetDirectoryName(site->Recipe->FlowFilePath) + "\\ModulationWaveform";
			int totalWaveformFiles_awf = Directory::GetFiles(waveformFileDirectory, "*.awf")->Length;
			int totalWaveformFiles_wfm = Directory::GetFiles(waveformFileDirectory, "*.wfm")->Length;
			int totalWaveformFiles = totalWaveformFiles_awf + totalWaveformFiles_wfm;
			array<String^> ^ waveformFiles_awf = gcnew array<String^>(totalWaveformFiles_awf);
			array<String^> ^ waveformFiles_wfm = gcnew array<String^>(totalWaveformFiles_wfm);
			String ^ fileName = nullptr;
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				ConditionInfo = testConditionCollection["ModuleAlias"][site];
				moduleAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			waveformFiles_awf = Directory::GetFiles(waveformFileDirectory, "*.awf");
			waveformFiles_wfm = Directory::GetFiles(waveformFileDirectory, "*.wfm");

			for (int i = 0; i < totalWaveformFiles_awf; i++)
			{
				fileName = nullptr;
				fileName = waveformFiles_awf[i]->Replace(waveformFileDirectory + "\\", "");
				tl->glob->ModulationFile[testSite]->Add(fileName, waveformFiles_awf[i]);

				RF_LoadModulation(testSite, moduleAlias, waveformFiles_awf[i], StationNo);
			}

			for (int i = 0; i < totalWaveformFiles_wfm; i++)
			{
				fileName = nullptr;
				fileName = waveformFiles_wfm[i]->Replace(waveformFileDirectory + "\\", "");
				tl->glob->ModulationFile[testSite]->Add(fileName, waveformFiles_wfm[i]);

				RF_LoadModulation(testSite, moduleAlias, waveformFiles_wfm[i], StationNo);
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_LoadModulation");

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
	void AMB7600SRTestLibrary::CM_RF_WlanInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_WlanInit");

			//Control Method Compulsory Variable
			String^ moduleAliasVSG = nullptr;
			String^ moduleAliasVSA = nullptr;
			int standardSelection = 999;
			int measureOption_ACAX = WLAN_ACAX;
			int measureOption_ABGN = WLAN_ABGN;

			//Start Modulation Operation Variable
			String ^ CM = "WlanInit_";
			String ^ ErrorMessage = nullptr;
			bool Init_ACAX = false;
			bool Init_ABGN = false;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("ModuleAliasVSG"))
			{
				ConditionInfo = testConditionCollection["ModuleAliasVSG"][site];
				moduleAliasVSG = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAliasVSG" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ModuleAliasVSA"))
			{
				ConditionInfo = testConditionCollection["ModuleAliasVSA"][site];
				moduleAliasVSA = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAliasVSA" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StandardSelection"))
			{
				ConditionInfo = testConditionCollection["StandardSelection"][site];
				standardSelection = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "StandardSelection" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("measureOption_ACAX"))
			{
				ConditionInfo = testConditionCollection["measureOption_ACAX"][site];
				Init_ACAX = (bool)ConditionInfo->Value;
			}

			if ((bool)testConditionCollection->ContainsKey("measureOption_ABGN"))
			{
				ConditionInfo = testConditionCollection["measureOption_ABGN"][site];
				Init_ABGN = (bool)ConditionInfo->Value;
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//	RF_LoadHardwareProfile(testSite);

			if (Init_ACAX == true)
			{
				RF_WlanInitSetup(testSite, moduleAliasVSG, moduleAliasVSA, standardSelection, measureOption_ACAX);
			}

			if (Init_ABGN == true)
			{
				RF_WlanInitSetup(testSite, moduleAliasVSG, moduleAliasVSA, standardSelection, measureOption_ABGN);
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_WlanInit");

#pragma endregion "Test"

		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
			throw;
		}
	}
	void AMB7600SRTestLibrary::CM_RF_EvmMeasurementSetup(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_EvmMeasurementSetup");

			//Control Method Compulsory Variable
			int wlanModulationStandard = 999;
			WlanModulationStandardEnum standard;

			//Start Modulation Operation Variable
			String ^ CM = "EvmMeasurementSetup_";
			String ^ ErrorMessage = nullptr;
			Dictionary<int, Object^>^ WlanSettings = gcnew Dictionary<int, Object^>();
			List<int>^ Setting = gcnew List<int>();
			array<String^>^ splitStr = nullptr;
			array<String^>^ separators = { CM + "Setting_" };
			DataType Var;
			bool SetWlanSetting = false;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("Setting_"))
				{
					splitStr = nullptr;
					splitStr = testcond->Name->Split(separators, StringSplitOptions::RemoveEmptyEntries);
					Setting->Add(Convert::ToInt32(splitStr[0]));
				}
			}

			if ((bool)testConditionCollection->ContainsKey("WlanModulationStandard"))
			{
				ConditionInfo = testConditionCollection["WlanModulationStandard"][site];
				tl->TestCondCheckingDataType(CM + "WlanModulationStandard", DataType::Int32, ConditionInfo->Condition->DataType);
				wlanModulationStandard = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "WlanModulationStandard" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}

			for (int i = 0; i<Setting->Count; i++)
			{
				ConditionInfo = testConditionCollection["Setting_" + Setting[i]][site];

				RF_WlanEvmSettingVariable(CM, Setting[i], Var);
				tl->TestCondCheckingDataType(CM + "Setting_" + Setting[i], Var, ConditionInfo->Condition->DataType);

				switch (Var)
				{
				case DataType::Double:
					WlanSettings->Add(Setting[i], (double)ConditionInfo->Value);
					break;

				case DataType::Int32:
					WlanSettings->Add(Setting[i], (int)ConditionInfo->Value);
					break;

				case DataType::String:
					WlanSettings->Add(Setting[i], (String^)ConditionInfo->Value);
					break;

				case DataType::Boolean:
					WlanSettings->Add(Setting[i], (bool)ConditionInfo->Value);
					break;
				}

			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_WlanStandardSelection(testSite, wlanModulationStandard, standard);

			if (WlanSettings->Count > 0)
			{
				SetWlanSetting = true;
			}
			else
			{
				SetWlanSetting = false;
			}

			RF_WlanEvmMeasurementSetup(testSite, standard, SetWlanSetting, WlanSettings);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_EvmMeasurementSetup");

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
	void AMB7600SRTestLibrary::CM_RF_SemMeasurementSetup(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_SemMeasurementSetup");

			//Control Method Compulsory Variable
			int wlanModulationStandard = 999;
			WlanModulationStandardEnum standard;
			int semAvg = 999;

			//Start Modulation Operation Variable
			String ^ CM = "SemMeasurementSetup_";
			String ^ ErrorMessage = nullptr;
			Dictionary<int, Object^>^ WlanSettings = gcnew Dictionary<int, Object^>();
			List<int>^ Setting = gcnew List<int>();
			array<String^>^ splitStr = nullptr;
			array<String^>^ separators = { CM + "Setting_" };
			DataType Var;
			bool SetWlanSetting = false;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("Setting_"))
				{
					splitStr = nullptr;
					splitStr = testcond->Name->Split(separators, StringSplitOptions::RemoveEmptyEntries);
					Setting->Add(Convert::ToInt32(splitStr[0]));
				}
			}

			if ((bool)testConditionCollection->ContainsKey("WlanModulationStandard"))
			{
				ConditionInfo = testConditionCollection["WlanModulationStandard"][site];
				wlanModulationStandard = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "WlanModulationStandard" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("SemAvg"))
			{
				ConditionInfo = testConditionCollection["SemAvg"][site];
				semAvg = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SemAvg" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			for (int i = 0; i<Setting->Count; i++)
			{
				ConditionInfo = testConditionCollection["Setting_" + Setting[i]][site];

				RF_WlanSemSettingVariable(CM, Setting[i], Var);

				switch (Var)
				{
				case DataType::Double:
					if (ConditionInfo->Condition->DataType == DataType::Double)
					{
						WlanSettings->Add(Setting[i], (double)ConditionInfo->Value);
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "Setting_" + Setting[i] + " DataType] is not double.";
						throw gcnew Exception(ErrorMessage);
					}
					break;
				case DataType::Int32:
					if (ConditionInfo->Condition->DataType == DataType::Int32)
					{
						WlanSettings->Add(Setting[i], (int)ConditionInfo->Value);
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "Setting_" + Setting[i] + " DataType] must be set to int32.";
						throw gcnew Exception(ErrorMessage);
					}
					break;

				case DataType::String:
					if (ConditionInfo->Condition->DataType == DataType::String)
					{
						WlanSettings->Add(Setting[i], (String^)ConditionInfo->Value);
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "Setting_" + Setting[i] + " DataType] must be set to String.";
						throw gcnew Exception(ErrorMessage);
					}
					break;

				case DataType::Boolean:
					if (ConditionInfo->Condition->DataType == DataType::Boolean)
					{
						WlanSettings->Add(Setting[i], (bool)ConditionInfo->Value);
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "Setting_" + Setting[i] + " DataType] must be set to boolean.";
						throw gcnew Exception(ErrorMessage);
					}
					break;
				}

			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_WlanStandardSelection(testSite, wlanModulationStandard, standard);

			if (WlanSettings->Count > 0)
			{
				SetWlanSetting = true;
			}
			else
			{
				SetWlanSetting = false;
			}

			RF_WlanSemMeasurementSetup(testSite, standard, SetWlanSetting, semAvg, WlanSettings);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_SemMeasurementSetup");

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
	void AMB7600SRTestLibrary::CM_RF_MeasureSetup(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_MeasureSetup");

			//Control Method Compulsory Variable
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 1.0 mS;

			//Start Modulation Operation Variable
			String ^ CM = "MeasureSetup_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				ConditionInfo = testConditionCollection["MeasureChannel"][site];
				measureChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				ConditionInfo = testConditionCollection["MeasurePower"][site];
				measurePower = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				ConditionInfo = testConditionCollection["MeasureFreq"][site];
				measureFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				ConditionInfo = testConditionCollection["MeasureDelay"][site];
				measureDelay = (double)ConditionInfo->Value;
			}
			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				ConditionInfo = testConditionCollection["FilterOption"][site];
				filterOption = (int)ConditionInfo->Value;
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_MeasureSetup(testSite, measureChannel, measurePower, measureFreq, filterOption);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_MeasureSetup");

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
	void AMB7600SRTestLibrary::CM_RF_MeasureSetupIQ(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_MeasureSetupIQ");

			//Control Method Compulsory Variable
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 1.0 mS;
			double sampleRate = 0.0;
			int sampleSize = 0.0;

			//Start Modulation Operation Variable
			String ^ CM = "MeasureSetupIQ_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				ConditionInfo = testConditionCollection["MeasureChannel"][site];
				measureChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				ConditionInfo = testConditionCollection["MeasurePower"][site];
				measurePower = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				ConditionInfo = testConditionCollection["MeasureFreq"][site];
				measureFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleRate"))
			{
				ConditionInfo = testConditionCollection["SampleRate"][site];
				sampleRate = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SampleRate" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleSize"))
			{
				ConditionInfo = testConditionCollection["SampleSize"][site];
				sampleSize = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SampleSize" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				ConditionInfo = testConditionCollection["MeasureDelay"][site];
				measureDelay = (double)ConditionInfo->Value;
			}
			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				ConditionInfo = testConditionCollection["FilterOption"][site];
				filterOption = (int)ConditionInfo->Value;
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);
			RF_MeasureSetupIQ(testSite, measureChannel, measurePower, measureFreq, sampleRate, sampleSize, filterOption);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_MeasureSetupIQ.\n");

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
	void AMB7600SRTestLibrary::CM_RF_TriggerSigenStartModulation(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_TriggerSigenStartModulation");

			//Control Method Compulsory Variable
			String^ moduleAliasSigen = nullptr;
			String^ moduleAliasDM = nullptr;
			String^ modulationFile = nullptr;
			String^ vectorFileName = nullptr;
			int playBackMode = 0;

			//Start Modulation Operation Variable
			String ^ CM = "TriggerSigenStartModulation_";
			String ^ ErrorMessage = nullptr;
			String ^ PathModulationFile = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("ModuleAliasSigen"))
			{
				ConditionInfo = testConditionCollection["ModuleAliasSigen"][site];
				moduleAliasSigen = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAliasSigen" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ModulationFile"))
			{
				ConditionInfo = testConditionCollection["ModulationFile"][site];
				modulationFile = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModulationFile" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("PlayBackMode"))
			{
				ConditionInfo = testConditionCollection["PlayBackMode"][site];
				playBackMode = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PlayBackMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("VectorFileName"))
			{
				ConditionInfo = testConditionCollection["VectorFileName"][site];
				vectorFileName = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "VectorFileName" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ModuleAliasDM"))
			{
				ConditionInfo = testConditionCollection["ModuleAliasDM"][site];
				moduleAliasDM = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ModuleAliasDM" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			PathModulationFile = tl->glob->ModulationFile[testSite][modulationFile];

			RF_StopModulation(testSite, moduleAliasSigen);
			RF_StartModulation(testSite, moduleAliasSigen, PathModulationFile, playBackMode);
			module400series->DM_MIPIWriteVector(testSite, moduleAliasDM, vectorFileName);

			//RF_KTM9420_ATTR_SOURCE_Trigger(testSite, "VSG1", tl->glob->ModulationFile[testSite]["WLAN_11AC_80MHz_MCS9.awf"]);
			//DM_MIPIWriteVector(testSite, "DM483E", "SW3");


			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_TriggerSigenStartModulation");

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
	void AMB7600SRTestLibrary::CM_RF_WolferInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_RF_WolferInit
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_WolferInit");

			//To get the desired Wolfer Number in current site
			int externalModuleNo = 0;
			for (int i = 0; i < CurrentHeadSite.ExternalModuleList->Count; i++)
			{
				if (CurrentHeadSite.ExternalModuleList[externalModuleNo]["Name"] == "Wolfer")
					externalModuleNo = i;
			}

			////Control Method Compulsory Variable
			String^ wolferType = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Type"];
			String^ IOControl = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Address"];

			//Start Modulation Operation Variable
			String ^ CM = "WolferInit_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//if ((bool)testConditionCollection->ContainsKey("WolferType"))
			//{
			//	ConditionInfo = testConditionCollection["WolferType"][site];
			//	wolferType = (String^)ConditionInfo->Value;
			//}
			//else
			//{
			//	ErrorMessage = "Test Condition [" + CM + "WolferType" + "] is not found.";
			//	throw gcnew Exception(ErrorMessage);
			//}
			//if ((bool)testConditionCollection->ContainsKey("IOControl")) //Get Hardware AMAP Name
			//{
			//	ConditionInfo = testConditionCollection["IOControl"][site];
			//	IOControl = (String^)ConditionInfo->Value;
			//}
			//else
			//{
			//	ErrorMessage = "Test Condition [" + CM + "IOControl" + "] is not found.";
			//	throw gcnew Exception(ErrorMessage);
			//}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			tl->glob->WolferInfo_Status[testSite].freqcalFile->Add(wolferType, FILE_CONST_WOLFER_INFO + "\\" + wolferType + "\\" + FILE_NAME_WOLFER_CAL_LIST);
			tl->glob->WolferInfo_Status[testSite].freqHarcalFile->Add(wolferType, FILE_CONST_WOLFER_INFO + "\\" + wolferType + "\\" + FILE_NAME_WOLFER_HAR_CAL_LIST);
			tl->glob->WolferInfo_Status[testSite].txplFile->Add(wolferType, FILE_CONST_WOLFER_INFO + "\\" + wolferType + "\\" + FILE_NAME_WOLFER_TX);
			tl->glob->WolferInfo_Status[testSite].rxplFile->Add(wolferType, FILE_CONST_WOLFER_INFO + "\\" + wolferType + "\\" + FILE_NAME_WOLFER_RX);
			tl->glob->WolferInfo_Status[testSite].txHarplFile->Add(wolferType, FILE_CONST_WOLFER_INFO + "\\" + wolferType + "\\" + FILE_NAME_WOLFER_TX_HAR);
			tl->glob->WolferInfo_Status[testSite].rxHarplFile->Add(wolferType, FILE_CONST_WOLFER_INFO + "\\" + wolferType + "\\" + FILE_NAME_WOLFER_RX_HAR);

			if (File::Exists(tl->glob->WolferInfo_Status[testSite].freqcalFile[wolferType]) != true)
			{
				throw gcnew Aemulus::Hardware::AlarmException(tl->glob->WolferInfo_Status[testSite].freqcalFile[wolferType] + " file not exist", -1);
			}

#pragma region "Read Frequency/Harmonic Frequency Calibration List and Path Loss"
			int tempCount = 0;

			tl->glob->freq_count[wolferType] = 0;
			ReadFreqCalList(testSite, wolferType, tempCount);
			tl->glob->freq_count[wolferType] = tempCount;

			tl->glob->txpl_count[wolferType] = 0;
			ReadTxPathLoss(testSite, wolferType, tempCount);
			tl->glob->txpl_count[wolferType] = tempCount;

			tl->glob->rxpl_count[wolferType] = 0;
			ReadRxPathLoss(testSite, wolferType, tempCount);
			tl->glob->rxpl_count[wolferType] = tempCount;

			tl->glob->freqHar_count[wolferType] = 0;
			ReadFreqHarList(testSite, wolferType, tempCount);
			tl->glob->freqHar_count[wolferType] = tempCount;

			tl->glob->rxpl_Har_count[wolferType] = 0;
			ReadRxHarPathLoss(testSite, wolferType, tempCount);
			tl->glob->rxpl_Har_count[wolferType] = tempCount;
#pragma endregion

			if (IOControl->StartsWith("IOM421"))
			{
				tl->glob->WolferInfo_Status[testSite].wolferIOFile->Add(wolferType, tl->glob->tf.RecipeFilePathDirectory + "\\" + "WolferIO\\" + wolferType + "\\" + wolferType + ".csv");
				wlfGetSwMatrix(testSite, wolferType);

				tl->glob->g_txpath[wolferType] = 0;
				tl->glob->g_rxpath[wolferType] = 0;

				tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Load " + tl->glob->WolferInfo_Status[testSite].wolferIOFile[wolferType] + " with " + IOControl + ".\n");
			}
			else if (IOControl == "DigitalBoard")
			{
				tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Load " + tl->glob->WolferInfo_Status[testSite].wolferIOFile[wolferType] + " with " + IOControl + ".\n");
			}
			else
			{
				throw gcnew Aemulus::Hardware::AlarmException(wolferType + " has undefined IOControl Type", -1);
			}

			wlfInit(testSite, IOControl);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method RFCase_WolferInit for " + wolferType + " wolfer.\n");

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
	void AMB7600SRTestLibrary::CM_RF_WolferSelectPath(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_RF_WolferSelectPath
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_WolferSelectPath");

			//To get the desired Wolfer Number in current site
			int externalModuleNo = 0;
			for (int i = 0; i < CurrentHeadSite.ExternalModuleList->Count; i++)
			{
				if (CurrentHeadSite.ExternalModuleList[externalModuleNo]["Name"] == "Wolfer")
					externalModuleNo = i;
			}

			////Control Method Compulsory Variable
			double sourceFreq;
			double measureFreq;
			String^ wolferType = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Type"];
			String^ IOControl = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Address"];
			String^ selectTxPath = nullptr;
			String^ selectRxPath = nullptr;
			bool TxBypassOn = false;
			String^ TxInternalPath = nullptr;
			String^ RxInternalPath = nullptr;

			//Start Modulation Operation Variable
			String ^ CM = "WolferSelectPath_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("SourceFreq"))
			{
				ConditionInfo = testConditionCollection["SourceFreq"][site];
				sourceFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				ConditionInfo = testConditionCollection["MeasureFreq"][site];
				measureFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SelectTxPath"))
			{
				ConditionInfo = testConditionCollection["SelectTxPath"][site];
				selectTxPath = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SelectTxPath" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SelectRxPath"))
			{
				ConditionInfo = testConditionCollection["SelectRxPath"][site];
				selectRxPath = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SelectRxPath" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("TxBypassOn")) //Tx Bypass Path Selection
			{
				ConditionInfo = testConditionCollection["TxBypassOn"][site];
				TxBypassOn = (bool)ConditionInfo->Value;
			}
			if ((bool)testConditionCollection->ContainsKey("TxInternalPath")) //Direct Select Wolfer Tx Internal Path
			{
				ConditionInfo = testConditionCollection["TxInternalPath"][site];
				TxInternalPath = (String^)ConditionInfo->Value;
			}
			if ((bool)testConditionCollection->ContainsKey("RxInternalPath")) //Direct Select Wolfer Rx Internal Path
			{
				ConditionInfo = testConditionCollection["RxInternalPath"][site];
				RxInternalPath = (String^)ConditionInfo->Value;
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			bool toggleSwitch = false;

			if (wolferType == "C2")
			{
				if (IOControl->StartsWith("IOM421"))
				{
					WolferSelectPath_C2(testSite, wolferType, selectTxPath, selectRxPath, sourceFreq, measureFreq, TxBypassOn, TxInternalPath, RxInternalPath);
				}
				else if (IOControl == "DigitalBoard")
				{
				}
				else
				{
					throw gcnew Aemulus::Hardware::AlarmException(wolferType + " has undefined IOControl Type", -1);
				}
			}
		}

#pragma endregion "Test"

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_RF_WolferSourcePower(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_RF_WolferSourcePower
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method RFCase_WolferSourcePower");

			//To get the desired Wolfer Number in current site
			int externalModuleNo = 0;
			for (int i = 0; i < CurrentHeadSite.ExternalModuleList->Count; i++)
			{
				if (CurrentHeadSite.ExternalModuleList[externalModuleNo]["Name"] == "Wolfer")
					externalModuleNo = i;
			}

			////Control Method Compulsory Variable
			String^ wolferType = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Type"];
			String^ IOControl = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Address"];
			String^ C2_Coupler_CH = nullptr;
			String^ sourceChannel = nullptr;
			double sourceFreq = 0.0;
			double sourcePin = 0.0;

			//WolferSourcePower Operation Variable
			String ^ CM = "WolferSourcePower_";
			String ^ ErrorMessage = nullptr;
			bool UserInputSourceAttenuation = false;

			//Control Method Option Variable
			double sourceAttenuation = 999.99;
			String ^ inputBoardLossItem = nullptr;
			double inputBoardLoss = 0.0;
			double inputExtAtt = 0.0;

			//Wolfer Operation Variable
			double offset = 0.0;
			double offset2 = 0.0;
			double actualSourceLevel = 0.0;
			double coupRef = -90.0;
			double coupledPout = -90.0;
			//double pathloss = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//SourceChannel Test Condition
			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				ConditionInfo = testConditionCollection["SourceChannel"][site];
				sourceChannel = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceFreq"))
			{
				ConditionInfo = testConditionCollection["SourceFreq"][site];
				sourceFreq = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourceFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourcePin"))
			{
				ConditionInfo = testConditionCollection["SourcePin"][site];
				sourcePin = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "SourcePin" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				ConditionInfo = testConditionCollection["SourceAttenuation"][site];
				sourceAttenuation = (double)ConditionInfo->Value;
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey(wolferType + "_Coupler_CH"))
			{
				ConditionInfo = testConditionCollection[wolferType + "_Coupler_CH"][site];
				C2_Coupler_CH = (String^)ConditionInfo->Value;
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(sourceChannel)[0];

			if ((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["TestSite_LoadHardwareProfile"] != testSite)
			{
				RF_LoadHardwareProfile(testSite);
				tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["TestSite_LoadHardwareProfile"] = testSite;
			}

			tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus = sourcePin;
			tl->glob->SourcePower_Status[testSite].SourceFreqPreStatus = sourceFreq;

			//ActualSourcePower = sourcePin + inputBoardLoss + inputExtAtt;

#pragma region Coupler Path Measurement & Adjustment

			if (wolferType == "C2")
			{
				if (IOControl->StartsWith("IOM421"))
				{

					for (int i = 0; i < tl->glob->txpl_count[wolferType]; i++)
					{
						if ((tl->glob->txPathLoss_freq[wolferType][i] == sourceFreq) && (tl->glob->txPathLoss_targetpout[wolferType][i] == sourcePin) && (tl->glob->txPathLoss_outIndex[wolferType][i] == tl->glob->outIndex[wolferType]))
						{
							coupRef = tl->glob->txPathLoss_couppout[wolferType][i];
							actualSourceLevel = tl->glob->txPathLoss_actualpout[wolferType][i];
							break;
						}
					}

					if ((bool)testConditionCollection->ContainsKey(wolferType + "_Coupler_CH"))
					{
						double l_Measure_Level_Coupler = coupRef + 5.0;

						tl->CheckError(testSite, amsrf[testSite]->amsrf->MeasureSetup(C2_Coupler_CH, l_Measure_Level_Coupler, sourceFreq, AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS));
						WlfSource(testSite, wolferType, sourceChannel, (int)wlfoutsw::wlfout1, tl->glob->outIndex[wolferType], tl->glob->g_txpath[wolferType], sourceFreq, sourcePin, offset + offset2, actualSourceLevel);
						util->WaitSecond(2 mS);

						try
						{
							tl->CheckError(testSite, amsrf[testSite]->amsrf->MeasureChannel(C2_Coupler_CH, coupledPout));
						}
						catch (Exception ^ ex)
						{
							tl->CheckError(testSite, amsrf[testSite]->amsrf->MeasureSetup(C2_Coupler_CH, l_Measure_Level_Coupler + 15, sourceFreq, AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS));
							util->WaitSecond(2 mS);
							tl->CheckError(testSite, amsrf[testSite]->amsrf->MeasureChannel(C2_Coupler_CH, coupledPout));
						}

						if (Math::Abs(coupRef - coupledPout) < 1)
						{
							offset2 = coupRef - coupledPout;
						}
					}
					tl->WriteToTcrLgr("SITE " + testSite.ToString(), "WolferCoupler Pout = " + coupledPout);
					tl->glob->WolferCoupler_Pout[testSite] = coupledPout; //Coupler Pout


																		  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  SourceChannel  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
					if (UserInputSourceAttenuation)
						WlfSource(testSite, wolferType, sourceChannel, (int)wlfoutsw::wlfout1, tl->glob->outIndex[wolferType], tl->glob->g_txpath[wolferType], sourceFreq, sourcePin, offset + offset2, sourceAttenuation, actualSourceLevel);
					else
						WlfSource(testSite, wolferType, sourceChannel, (int)wlfoutsw::wlfout1, tl->glob->outIndex[wolferType], tl->glob->g_txpath[wolferType], sourceFreq, sourcePin, offset + offset2, actualSourceLevel);

					util->WaitSecond(5 mS);
					//tl->CheckError(RF, Amsrf0->amsrf->MeasureChannel(C2_Coupler_CH, coupledPout));

				}
				else if (IOControl == "DigitalBoard")
				{
				}
				else
				{
					throw gcnew Aemulus::Hardware::AlarmException(wolferType + " has undefined IOControl Type", -1);
				}
			}
#pragma endregion

			//State Recording
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] = HardwareRsrc->Alias;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] = actualSourceLevel;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] = sourceFreq;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] = sourceAttenuation;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFactor"] = 999.99;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAlignFactor"] = 999.99;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] = 0;//Source Normal
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceStatus"] = 1;//Source High
		}

#pragma endregion "Test"

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}

	//Test Methods
	void AMB7600SRTestLibrary::TM_RF_MeasureChannel(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureChannel");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;

			//Test Method Option Variable
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5.0 mS;
			double outputBoardLoss = 0.0;
			double outputExtAtt = 0.0;
			String ^ outputBoardLossItem = nullptr;

			//Operation Variable
			double Pout = 0.0;
			String ^ TM = "MeasureChannel_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 3;
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

			RF_LoadHardwareProfile(testSite);
			RF_MeasureSetup(testSite, measureChannel, measurePower, measureFreq, filterOption);
			RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);

			//Storing Result into Array
			ResultArr[ResultCount] = tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus;
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;
			ResultArr[++ResultCount] = ResultArr[1] - ResultArr[0];

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureChannel");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);

		}
		finally
		{}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureChannelFast(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureChannelFast");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;

			//Test Method Option Variable
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5.0 mS;
			String ^ outputBoardLossItem = nullptr;
			double outputBoardLoss = 0.0;
			double outputExtAtt = 0.0;

			//Operation Variable
			double Pout = 0.0;
			String ^ TM = "MeasureChannelFast_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}
#pragma endregion

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 3; //Not include currentMeasurementCount & voltageMeasurementCount
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

			RF_LoadHardwareProfile(testSite);
			RF_MeasureFast(testSite, measureChannel, measurePower, measureFreq, filterOption, measureDelay, Pout);

			//Storing Result into Array
			ResultArr[ResultCount] = tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus;
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;
			ResultArr[++ResultCount] = ResultArr[1] - ResultArr[0];
			Result->Clear();
			Result->Add("Source", ResultArr[0]);
			Result->Add("Measure", ResultArr[1]);
			Result->Add("Gain", ResultArr[2]);

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureChannelFast");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureChannelIQ(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureChannelIQ");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			double sampleRate = 0.0;
			double sampleSize = 0.0;

			//Test Method Option Variable
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5.0 mS;
			double outputBoardLoss = 0.0;
			double outputExtAtt = 0.0;
			String ^ outputBoardLossItem = nullptr;

			//Operation Variable
			double Pout = 0.0;
			String ^ TM = "MeasureChannelIQ_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleRate"))
			{
				sampleRate = (double)tf_TestParameter_ConditionCast(testParameterName, "SampleRate");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleRate" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleSize"))
			{
				sampleSize = (int)tf_TestParameter_ConditionCast(testParameterName, "SampleSize");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleSize" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}

			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 3; //Not include currentMeasurementCount & voltageMeasurementCount
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
			RF_LoadHardwareProfile(testSite);
			RF_MeasureSetupIQ(testSite, measureChannel, measurePower, measureFreq, sampleRate, sampleSize, filterOption);
			RF_MeasureChannelIQ(testSite, measureChannel, measureDelay, Pout);

			//Storing Result into Array
			ResultArr[ResultCount] = tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus;
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;
			ResultArr[++ResultCount] = ResultArr[1] - ResultArr[0];

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureChannelIQ");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureBurstPower(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureBurstPower");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ measureChannel = nullptr;
			String ^ triggerVectorFileName = nullptr;
			String ^ initVectorFileName = nullptr;
			String ^ dmModuleAlias = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			double sampleRate = 0.0;
			double sampleSize = 0.0;
			double peakPercentage = 0.0;

			//Test Method Option Variable
			String ^ outputBoardLossItem = nullptr;
			double outputBoardLoss = 0.0;
			double delayAfterInitVector = 5 mS;
			double outputExtAtt = 0.0;

			//Operation Variable
			int Count = 0;
			double Pout = 0.0;
			double BurstPower_dBm = 0.0;
			double BurstPower_Watt = 0.0;
			double MaxPower = 0.0;
			double TotalPower = 0.0;
			double MeasureFactor = 0.0;
			String ^ TM = "MeasureBurstPower_";
			String^ ErrorMessage = nullptr;
			double MeasureLevelBuffer = 5.0;

			//File Logger
			FileLogger^ fileLogger = gcnew FileLogger(FILE_CONST_AEM_DEBUG);

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String ^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TriggerVectorFileName"))
			{
				triggerVectorFileName = (String ^)tf_TestParameter_ConditionCast(testParameterName, "TriggerVectorFileName");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TriggerVectorFileName" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("InitVectorFileName"))
			{
				initVectorFileName = (String ^)tf_TestParameter_ConditionCast(testParameterName, "InitVectorFileName");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "InitVectorFileName" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("DmModuleAlias"))
			{
				dmModuleAlias = (String ^)tf_TestParameter_ConditionCast(testParameterName, "DmModuleAlias");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "DmModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleRate"))
			{
				sampleRate = (double)tf_TestParameter_ConditionCast(testParameterName, "SampleRate");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleRate" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleSize"))
			{
				sampleSize = (int)tf_TestParameter_ConditionCast(testParameterName, "SampleSize");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleSize" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("PeakPercentage"))
			{
				peakPercentage = (double)tf_TestParameter_ConditionCast(testParameterName, "PeakPercentage");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "PeakPercentage" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("DelayAfterInitVector"))
			{
				delayAfterInitVector = (double)tf_TestParameter_ConditionCast(testParameterName, "DelayAfterInitVector");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 3; //Not include currentMeasurementCount & voltageMeasurementCount
			int ReusltCount = 0;
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
			RF_LoadHardwareProfile(testSite);

			array<double> ^ iData = gcnew array<double>(sampleSize);
			array<double> ^ qData = gcnew array<double>(sampleSize);
			array<double> ^ pwrData_watt = gcnew array<double>(sampleSize);
			array<double> ^ pwrData_dBm = gcnew array<double>(sampleSize);

			module400series->DM_MIPIWriteVector(testSite, dmModuleAlias, initVectorFileName);
			RF_KTM9420_ATTR_RECEIVER_TRIGGERS_EXTERNSL_TRIGGER_TERMINATION_SET(testSite, 0);
			RF_GetMeasureFactor(testSite, measureChannel, measurePower + MeasureLevelBuffer, measureFreq, AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS, MeasureFactor);
			RF_MeasureSetupIQ(testSite, measureChannel, measurePower + MeasureLevelBuffer, measureFreq, sampleRate, sampleSize, AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS);
			RF_KtM9420_Arm(testSite);
			util->WaitSecond(delayAfterInitVector);
			module400series->DM_MIPIWriteVector(testSite, dmModuleAlias, triggerVectorFileName);
			RF_KtM9420_GetIQData(testSite, iData, qData);

			for (int i = 0; i < sampleSize; i++)
			{
				RF_ConvertIQtoPower(iData[i], qData[i], pwrData_watt[i], pwrData_dBm[i]);
			}

			MaxPower = pwrData_watt[0];

			for (int i = 0; i < sampleSize; i++)
			{
				if (pwrData_watt[i] > MaxPower)
				{
					BurstPower_Watt = pwrData_watt[i];
				}
			}

			if (peakPercentage == 100.00)
			{
				BurstPower_Watt;
			}
			else
			{
				for (int i = 0; i < sampleSize; i++)
				{
					if (pwrData_watt[i] >(MaxPower * (peakPercentage / 100)))
					{
						TotalPower += pwrData_watt[i];
						Count++;
					}
				}
				BurstPower_Watt = TotalPower / Count;
			}

			RF_ConvertWattTodBm(BurstPower_Watt, BurstPower_dBm);
			Pout = BurstPower_dBm + MeasureFactor + outputBoardLoss + outputExtAtt;

			//Storing Result into Array
			ResultArr[ReusltCount] = tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus;
			ResultArr[++ReusltCount] = Pout;
			ResultArr[++ReusltCount] = ResultArr[1] - ResultArr[0];

			//Storing Array Result into Dictionary
			Result->Clear();
			ReusltCount = 0;
			Result->Add("Source", ResultArr[ReusltCount]);
			Result->Add("Measure", ResultArr[++ReusltCount]);
			Result->Add("Gain", ResultArr[++ReusltCount]);

			if (tl->glob->AWV.Debug == 1)
			{
				String ^ StrToFileSweep = "Index,Power_dBm,Power_Watt";
				String ^ fileSweepName = tl->glob->TestProperty[testSite].TestItemName + "_" + testParameterName + "_BurstRFPower_S" + tl->glob->tf.TestSite.ToString() + "UUT" + testSite.ToString() + ".csv";

				fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_OVERWRITE);


				//Converting the Raw IQ Data to dBm & Watt
				if (iData[0] != 0.0)
				{
					for (int i = 0; i < iData->Length; i++)
					{
						double Power_Watt = 0.0;
						double Power_dBm = 0.0;
						StrToFileSweep = nullptr;

						//Convert Raw Data IQ to dBm
						RF_ConvertIQtoPower(iData[i], qData[i], Power_Watt, Power_dBm);//PowerWatt is not used in this function

																					   //Add BoardLoss to the dBm
						Power_dBm = Power_dBm + MeasureFactor + outputBoardLoss;

						//Convert the dBm data to Watt
						RF_ConvertdBmToWatt(Power_dBm, Power_Watt);

						StrToFileSweep = i.ToString() + "," + Power_dBm.ToString() + "," + Power_Watt.ToString();
						fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);

					}
				}
				else
				{
					StrToFileSweep = "Fail";
					fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);
				}
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}


			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureBurstPower");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureSwitchingTime(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureSwitchingTime");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ measureChannel = nullptr;
			String^  measureMode = nullptr;
			String ^ dmModuleAlias = nullptr;
			String ^ initVectorFileName = nullptr;
			String ^ triggerVectorFileName = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			double sampleRate = 0.0;
			double sampleSize = 0.0;

			//Test Method Option Variable
			double thresholdUncertainty = 0.0;
			String ^ outputBoardLossItem = nullptr;
			double startCapture = 10.0;
			double stopCapture = 90.0;
			double outputBoardLoss = 0.0;
			int numberAveragingInit = 10;
			int numberAveragingFinal = 10;
			double digitizerTriggerDelay = 0.0 S;
			double delayAfterInitVector = 1 mS;
			double outputExtAtt = 0.0;
			bool movingAveragingOption = false;
			int movingAveragingFactor = 50;

			//Measure Channel Operation Variable
			int RetestCount = 5;
			int RetestCurrentCount = 0;
			double TpHighLimit = 0.0;
			double TpLowLimit = 0.0;
			double AveragePowerWatt = 0.0;
			double AveragePowerdBm = 0.0;
			double MeasureFactor = 0.0;
			double MeasureLevelBuffer = 5.0;
			double Timing = 0.0;
			double SwitchMode = 0.0;
			String ^ TM = "MeasureSwitchingTime_";
			String^ ErrorMessage = nullptr;

			//File Logger
			FileLogger^ fileLogger = gcnew FileLogger(FILE_CONST_AEM_DEBUG);

			//Result Variable
			double Result = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);


			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String ^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("DmModuleAlias"))
			{
				dmModuleAlias = (String ^)tf_TestParameter_ConditionCast(testParameterName, "DmModuleAlias");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "DmModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureMode"))
			{
				measureMode = (String ^)tf_TestParameter_ConditionCast(testParameterName, "MeasureMode");

				if (measureMode == "Rise")
				{
					SwitchMode = 1;
				}
				else if (measureMode == "Fall")
				{
					SwitchMode = 0;
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "MeasureMode: " + measureMode + "] is not supported.";
					throw gcnew Exception(ErrorMessage);
				}
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("InitVectorFileName"))
			{
				initVectorFileName = (String ^)tf_TestParameter_ConditionCast(testParameterName, "InitVectorFileName");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "InitVectorFileName" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TriggerVectorFileName"))
			{
				triggerVectorFileName = (String ^)tf_TestParameter_ConditionCast(testParameterName, "TriggerVectorFileName");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TriggerVectorFileName" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleRate"))
			{
				sampleRate = (double)tf_TestParameter_ConditionCast(testParameterName, "SampleRate");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleRate" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleSize"))
			{
				sampleSize = (int)tf_TestParameter_ConditionCast(testParameterName, "SampleSize");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleSize" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("StartCapture"))
			{
				startCapture = (double)tf_TestParameter_ConditionCast(testParameterName, "StartCapture");
			}
			if ((bool)testConditionCollection->ContainsKey("StopCapture"))
			{
				stopCapture = (double)tf_TestParameter_ConditionCast(testParameterName, "StopCapture");
			}
			if ((bool)testConditionCollection->ContainsKey("DelayAfterInitVector"))
			{
				delayAfterInitVector = (double)tf_TestParameter_ConditionCast(testParameterName, "DelayAfterInitVector");
			}
			if ((bool)testConditionCollection->ContainsKey("ThresholdUncertainty"))
			{
				thresholdUncertainty = (double)tf_TestParameter_ConditionCast(testParameterName, "ThresholdUncertainty");
			}
			if ((bool)testConditionCollection->ContainsKey("DigitizerTriggerDelay"))
			{
				digitizerTriggerDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "DigitizerTriggerDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("NumberAveragingInit"))
			{
				numberAveragingInit = (int)tf_TestParameter_ConditionCast(testParameterName, "NumberAveragingInit");

				if (numberAveragingInit == 0)
				{
					ErrorMessage = "Test Condition [" + TM + "NumberAveragingInit] cannot be zero.";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("NumberAveragingFinal"))
			{
				numberAveragingFinal = (int)tf_TestParameter_ConditionCast(testParameterName, "NumberAveragingFinal");

				if (numberAveragingFinal == 0)
				{
					ErrorMessage = "Test Condition [" + TM + "numberAveragingFinal] cannot be zero.";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}
			if ((bool)testConditionCollection->ContainsKey("MovingAveragingOption"))
			{
				movingAveragingOption = (bool)tf_TestParameter_ConditionCast(testParameterName, "MovingAveragingOption");

				if (movingAveragingOption == true)
				{
					if ((bool)testConditionCollection->ContainsKey("MovingAveragingFactor"))
					{
						movingAveragingFactor = (int)tf_TestParameter_ConditionCast(testParameterName, "MovingAveragingFactor");

						if (movingAveragingFactor == 0)
						{
							ErrorMessage = "Test Condition [" + TM + "MovingAveragingFactor: " + movingAveragingFactor.ToString() + "] must be greater than 0 (zero)";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else
					{
						movingAveragingFactor = 50;
					}
				}
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"
			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			array<double> ^ iData = gcnew array<double>(sampleSize);
			array<double> ^ qData = gcnew array<double>(sampleSize);
			array<double> ^ pData_Watt = nullptr;

			if (startCapture >stopCapture)
			{
				ErrorMessage = "StartCapture: " + startCapture.ToString() + " cannot be greater than StopCapture: " + stopCapture.ToString();
				throw gcnew Exception(ErrorMessage);
			}

		RETEST:
			module400series->DM_MIPIWriteVector(testSite, dmModuleAlias, initVectorFileName);
			RF_KTM9420_ATTR_RECEIVER_TRIGGERS_EXTERNSL_TRIGGER_TERMINATION_SET(testSite, 0);
			RF_GetMeasureFactor(testSite, measureChannel, measurePower + MeasureLevelBuffer, measureFreq, AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS, MeasureFactor);
			RF_MeasureSetupIQ(testSite, measureChannel, measurePower + MeasureLevelBuffer, measureFreq, sampleRate, sampleSize, AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS);
			RF_KtM9420_Arm(testSite);
			util->WaitSecond(delayAfterInitVector);
			module400series->DM_MIPIWriteVector(testSite, dmModuleAlias, triggerVectorFileName);
			RF_KtM9420_GetIQData(testSite, iData, qData);
			//CalculateSwitchingTime(SwitchMode, iData, qData, sampleRate, startCapture, stopCapture, numberAveragingInit, numberAveragingFinal, digitizerTriggerDelay, MeasureFactor + outputBoardLoss + outputExtAtt, thresholdUncertainty, Timing);
			CalculateSwitchingTime(SwitchMode, iData, qData, movingAveragingOption, movingAveragingFactor, sampleRate, startCapture, stopCapture, numberAveragingInit, numberAveragingFinal, digitizerTriggerDelay, MeasureFactor + outputBoardLoss + outputExtAtt, thresholdUncertainty, Timing, pData_Watt);

			TpHighLimit = (double)tf_TestParameter_MaxLimit(testParameterName);
			TpLowLimit = (double)tf_TestParameter_MinLimit(testParameterName);

			if (tl->glob->AWV.Debug == 1)
			{
				String ^ StrToFileSweep = String::Empty;

				if (movingAveragingOption == true)
				{
					StrToFileSweep = "Index,Power_dBm,Power_Watt,Power_Watt_MA";
				}
				else
				{
					StrToFileSweep = "Index,Power_dBm,Power_Watt";
				}

				String ^ fileSweepName = tl->glob->TestProperty[testSite].TestItemName + "_" + testParameterName + "_SwitchingTime_RetestCount_" + RetestCurrentCount.ToString() + "_S" + tl->glob->tf.TestSite.ToString() + "UUT" + testSite.ToString() + ".csv";

				fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_OVERWRITE);


				//Converting the Raw IQ Data to dBm & Watt
				if (iData[0] != 0.0)
				{
					for (int i = 0; i < iData->Length; i++)
					{
						double Power_Watt = 0.0;
						double Power_dBm = 0.0;
						StrToFileSweep = nullptr;

						//Convert Raw Data IQ to dBm
						RF_ConvertIQtoPower(iData[i], qData[i], Power_Watt, Power_dBm);//PowerWatt is not used in this function

																					   //Add BoardLoss to the dBm
						Power_dBm = Power_dBm + MeasureFactor + outputBoardLoss + outputExtAtt;

						//Convert the dBm data to Watt
						RF_ConvertdBmToWatt(Power_dBm, Power_Watt);

						if (movingAveragingOption == true)
						{
							StrToFileSweep = i.ToString() + "," + Power_dBm.ToString() + "," + Power_Watt.ToString() + "," + pData_Watt[i].ToString();
						}
						else
						{
							StrToFileSweep = i.ToString() + "," + Power_dBm.ToString() + "," + Power_Watt.ToString();
						}
						//StrToFileSweep = i.ToString() + "," + Power_dBm.ToString() + "," + Power_Watt.ToString();
						fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);

					}
				}
				else
				{
					StrToFileSweep = "Fail";
					fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);
				}
			}

			if (Timing < TpLowLimit || Timing > TpHighLimit)
			{
				if (RetestCurrentCount < RetestCount)
				{
					RetestCurrentCount++;

					goto RETEST;
				}
			}

			Result = Timing;

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureSwitchingTime");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureIIP3(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureIIP3");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			double twoToneFrequencySpacing = 0.0;
			double sampleRate = 0.0;
			int  sampleSize = 0;

			//Test Method Optional Variable
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5 mS;
			double startSweepFreq = 0.0;
			double stopSweepFreq = 0.0;
			double incrementFreq = 0.0;
			double outputExtAtt = 0.0;
			bool sweepOperation = false;
			String ^ outputBoardLossItem = nullptr;
			array<double >^ outputBoardLoss = gcnew array <double>(4);


			//Operation Variable
			double Pin = tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus;
			double Pout = 0.0;
			array<double>^ MeasureFreqArr = gcnew array<double>(4);
			String ^ TM = "MeasureIIP3_";
			String ^ ErrorMessage = nullptr;

			//File Logger
			FileLogger^ fileLogger = gcnew FileLogger(FILE_CONST_AEM_DEBUG);
			String ^ StrToFileSweep = "Freq,Power_dBm";
			String ^ fileSweepName = tl->glob->TestProperty[testSite].TestItemName + "_" + testParameterName + "_FreqSweepTwoTone_S" + tl->glob->tf.TestSite.ToString() + "UUT" + testSite.ToString() + ".csv";

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TwoToneFrequencySpacing"))
			{
				twoToneFrequencySpacing = (double)tf_TestParameter_ConditionCast(testParameterName, "TwoToneFrequencySpacing");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TwoToneFrequencySpacing" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleRate"))
			{
				sampleRate = (double)tf_TestParameter_ConditionCast(testParameterName, "SampleRate");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleRate" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleSize"))
			{
				sampleSize = (int)tf_TestParameter_ConditionCast(testParameterName, "SampleSize");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleSize" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}

			for (int i = 0; i < 4; i++)
			{
				outputBoardLoss[i] = 0;

				if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem_" + i.ToString()))
				{
					outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem_" + i.ToString());

					if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
					{
						outputBoardLoss[i] = tl->glob->boardLoss[testSite][outputBoardLossItem];
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem_" + i.ToString() + ": " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
						throw gcnew Exception(ErrorMessage);
					}
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if (tl->glob->AWV.Debug == 1)
			{
				if ((bool)testConditionCollection->ContainsKey("SweepOperation"))
				{
					sweepOperation = (bool)tf_TestParameter_ConditionCast(testParameterName, "SweepOperation");
				}

				if (sweepOperation == true)
				{
					if ((bool)testConditionCollection->ContainsKey("StartSweepFreq"))
					{
						startSweepFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "StartSweepFreq");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "StartSweepFreq" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}

					if ((bool)testConditionCollection->ContainsKey("StopSweepFreq"))
					{
						stopSweepFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "StopSweepFreq");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "StopSweepFreq" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}

					if ((bool)testConditionCollection->ContainsKey("IncrementFreq"))
					{
						incrementFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "IncrementFreq");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "IncrementFreq" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}
				}

			}
#pragma endregion

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 8;
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
			RF_LoadHardwareProfile(testSite);

			MeasureFreqArr[0] = measureFreq - twoToneFrequencySpacing - (twoToneFrequencySpacing / 2); // IM_lo (2F1-F2)
			MeasureFreqArr[1] = measureFreq - (twoToneFrequencySpacing / 2); // fundamental_lo (F1)
			MeasureFreqArr[2] = measureFreq + (twoToneFrequencySpacing / 2); // fundamental_hi (F2)
			MeasureFreqArr[3] = measureFreq + twoToneFrequencySpacing + (twoToneFrequencySpacing / 2); // IM_hi (2F2-F1)

			for (int i = 0; i < 4; i++)
			{
				RF_MeasureSetupIQ(testSite, measureChannel, measurePower, MeasureFreqArr[i], sampleRate, sampleSize, filterOption);
				RF_MeasureChannelIQ(testSite, measureChannel, measureDelay, ResultArr[i]);
				ResultArr[i] = ResultArr[i] + outputBoardLoss[i] + outputExtAtt;
			}

			if (tl->glob->AWV.Debug == 1)
			{
				if (sweepOperation == true)
				{
					fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_OVERWRITE);

					for (double i = startSweepFreq Hz; i <= stopSweepFreq Hz; i = i + incrementFreq Hz)
					{
						double Power_dBm = 0.0;

						StrToFileSweep = nullptr;

						RF_MeasureSetupIQ(testSite, measureChannel, measurePower, i, sampleRate, sampleSize, filterOption);
						RF_MeasureChannelIQ(testSite, measureChannel, measureDelay, Power_dBm);

						Power_dBm = Power_dBm + outputBoardLoss[0] + outputExtAtt;
						StrToFileSweep = i.ToString() + "," + Power_dBm.ToString();
						fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);
					}
				}
			}

			ResultArr[4] = ResultArr[1] + (Math::Abs(ResultArr[1] - ResultArr[0])) / 2; // OIP3_Lo
			ResultArr[5] = ResultArr[2] + (Math::Abs(ResultArr[2] - ResultArr[3])) / 2; // OIP3_Hi
			ResultArr[6] = ResultArr[4] - (ResultArr[1] - Pin); // IIP3_Lo
			ResultArr[7] = ResultArr[5] - (ResultArr[2] - Pin); // IIP3_Hi

			ResultCount = 7;

			Result->Clear();
			ResultCount = 0;
			Result->Add("F0", ResultArr[ResultCount]);
			Result->Add("F1", ResultArr[++ResultCount]);
			Result->Add("F2", ResultArr[++ResultCount]);
			Result->Add("F3", ResultArr[++ResultCount]);
			Result->Add("OIP3_Lo", ResultArr[++ResultCount]);
			Result->Add("OIP3_Hi", ResultArr[++ResultCount]);
			Result->Add("IIP3_Lo", ResultArr[++ResultCount]);
			Result->Add("IIP3_Hi", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["IM_lo"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureIIP3");


#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureSParam(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureSParam");

			testParameterCount = 1;
			//Test Method Compulsory Variable
			double sourcePower = 0.0;
			double measurePower = 0.0;
			double measureFreq = 0.0;

			//Test Method Optional Variable
			double measureDelay = 5 mS;
			String ^ boardLossItem = nullptr;
			array<double >^ boardLoss;
			array<double >^ ExtAtt;

			//Operation Variable
			int ChannelCount = 0;
			int ChannelIndex = 0;
			String ^ TM = "MeasureSParam_";
			array<String^>^ UserDesiredResult = nullptr;
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<


			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "Channel_"))
				{
					ChannelCount++;
				}
			}

			//Result Variable
			int ResultTotal = ChannelCount * (2 * ChannelCount);
			boardLoss = gcnew array <double>(ChannelCount);
			ExtAtt = gcnew array <double>(ChannelCount);
			array<String^> ^ channelArray = gcnew array<String^>(ChannelCount);
			array<ComplexNumber> ^ l_SparamRaw = gcnew array<ComplexNumber>(ResultTotal / 2);
			array<double>^ ResultArrRe = gcnew array<double >(ResultTotal / 2);
			array<double>^ ResultArrIm = gcnew array<double >(ResultTotal / 2);
			Dictionary<String ^, double> ^ Result = gcnew Dictionary<String^, double>();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "Channel_"))
				{
					channelArray[ChannelIndex] = (String^)tf_TestParameter_ConditionCast(testParameterName, "Channel_" + ChannelIndex);
					ChannelIndex++;
				}
			}

			for (int i = 0; i<(ResultTotal / 2); i++)
			{
				ResultArrRe[i] = 0.0;
				ResultArrIm[i] = 0.0;
			}

			if ((bool)testConditionCollection->ContainsKey("SourcePower"))
			{
				sourcePower = (double)tf_TestParameter_ConditionCast(testParameterName, "SourcePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourcePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			for (int i = 0; i < boardLoss->Length; i++)
			{
				boardLoss[i] = 0;

				if ((bool)testConditionCollection->ContainsKey("BoardLossItem_" + i.ToString()))
				{
					boardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "BoardLossItem_" + i.ToString());

					if (tl->glob->boardLoss[testSite]->ContainsKey(boardLossItem))
					{
						boardLoss[i] = tl->glob->boardLoss[testSite][boardLossItem];
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "BoardLossItem_" + i.ToString() + ": " + boardLossItem + "] is not exist in the BoardLoss.csv";
						throw gcnew Exception(ErrorMessage);
					}
				}
			}

			for (int i = 0; i < ExtAtt->Length; i++)
			{
				ExtAtt[i] = 0;

				if ((bool)testConditionCollection->ContainsKey("ExtAtt_" + i.ToString()))
				{
					ExtAtt[i] = (double)tf_TestParameter_ConditionCast(testParameterName, "ExtAtt_" + i.ToString());
				}
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			RF_MeasureSParamSetup(testSite, channelArray, sourcePower, measurePower, measureFreq);
			util->WaitSecond(measureDelay);
			RF_MeasureSParam(testSite, channelArray, SParam_Format::MAG_PHASE, l_SparamRaw);

			for (int i = 0; i < (ResultTotal / 2); i++)
			{
				ResultArrRe[i] = l_SparamRaw[i].Re;
				ResultArrIm[i] = l_SparamRaw[i].Im;
			}

			switch (ChannelCount)
			{
			case 1:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S11_Im", ResultArrIm[0]);
			case 2:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S12_Re", ResultArrRe[1] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S21_Re", ResultArrRe[2] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S22_Re", ResultArrRe[3] + (boardLoss[1] * 2) + (ExtAtt[1] * 2));

				Result->Add("S11_Im", ResultArrIm[0]);
				Result->Add("S12_Im", ResultArrIm[1]);
				Result->Add("S21_Im", ResultArrIm[2]);
				Result->Add("S22_Im", ResultArrIm[3]);
				break;
			case 3:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S12_Re", ResultArrRe[1] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S13_Re", ResultArrRe[2] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));

				Result->Add("S21_Re", ResultArrRe[3] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S22_Re", ResultArrRe[4] + (boardLoss[1] * 2) + (ExtAtt[1] * 2));
				Result->Add("S23_Re", ResultArrRe[5] + (boardLoss[1] + boardLoss[2]) + (ExtAtt[1] + ExtAtt[2]));

				Result->Add("S31_Re", ResultArrRe[6] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));
				Result->Add("S32_Re", ResultArrRe[7] + (boardLoss[1] + boardLoss[2]) + (ExtAtt[1] + ExtAtt[2]));
				Result->Add("S33_Re", ResultArrRe[8] + (boardLoss[2] * 2) + (ExtAtt[2] * 2));

				Result->Add("S11_Im", ResultArrIm[9]);
				Result->Add("S12_Im", ResultArrIm[10]);
				Result->Add("S13_Im", ResultArrIm[11]);

				Result->Add("S21_Im", ResultArrIm[12]);
				Result->Add("S22_Im", ResultArrIm[13]);
				Result->Add("S23_Im", ResultArrIm[14]);

				Result->Add("S31_Im", ResultArrIm[15]);
				Result->Add("S32_Im", ResultArrIm[16]);
				Result->Add("S33_Im", ResultArrIm[17]);

				break;
			case 4:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S12_Re", ResultArrRe[1] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S13_Re", ResultArrRe[2] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));
				Result->Add("S14_Re", ResultArrRe[3] + (boardLoss[3] + boardLoss[0]) + (ExtAtt[3] + ExtAtt[0]));

				Result->Add("S21_Re", ResultArrRe[4] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S22_Re", ResultArrRe[5] + (boardLoss[1] * 2) + (ExtAtt[1] * 2));
				Result->Add("S23_Re", ResultArrRe[6] + (boardLoss[2] + boardLoss[1]) + (ExtAtt[2] + ExtAtt[1]));
				Result->Add("S24_Re", ResultArrRe[7] + (boardLoss[3] + boardLoss[1]) + (ExtAtt[3] + ExtAtt[1]));

				Result->Add("S31_Re", ResultArrRe[8] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));
				Result->Add("S32_Re", ResultArrRe[9] + (boardLoss[1] + boardLoss[2]) + (ExtAtt[1] + ExtAtt[2]));
				Result->Add("S33_Re", ResultArrRe[10] + (boardLoss[2] * 2) + (ExtAtt[2] * 2));
				Result->Add("S34_Re", ResultArrRe[11] + (boardLoss[2] + boardLoss[3]) + (ExtAtt[2] + ExtAtt[3]));

				Result->Add("S41_Re", ResultArrRe[12] + (boardLoss[3] + boardLoss[0]) + (ExtAtt[3] + ExtAtt[0]));
				Result->Add("S42_Re", ResultArrRe[13] + (boardLoss[3] + boardLoss[1]) + (ExtAtt[3] + ExtAtt[1]));
				Result->Add("S43_Re", ResultArrRe[14] + (boardLoss[2] + boardLoss[3]) + (ExtAtt[2] + ExtAtt[3]));
				Result->Add("S44_Re", ResultArrRe[15] + (boardLoss[3] * 2) + (ExtAtt[3] * 2));

				Result->Add("S11_Im", ResultArrIm[0]);
				Result->Add("S12_Im", ResultArrIm[1]);
				Result->Add("S13_Im", ResultArrIm[2]);
				Result->Add("S14_Im", ResultArrIm[3]);

				Result->Add("S21_Im", ResultArrIm[4]);
				Result->Add("S22_Im", ResultArrIm[5]);
				Result->Add("S23_Im", ResultArrIm[6]);
				Result->Add("S24_Im", ResultArrIm[7]);

				Result->Add("S31_Im", ResultArrIm[8]);
				Result->Add("S32_Im", ResultArrIm[9]);
				Result->Add("S33_Im", ResultArrIm[10]);
				Result->Add("S34_Im", ResultArrIm[11]);

				Result->Add("S41_Im", ResultArrIm[12]);
				Result->Add("S42_Im", ResultArrIm[13]);
				Result->Add("S43_Im", ResultArrIm[14]);
				Result->Add("S44_Im", ResultArrIm[15]);
				break;
			default:
				break;
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["S11_Re"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureSParam");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_MeasureSParamIQ(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_MeasureSParamIQ");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			double sourcePower = 0.0;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			double sampleRate = 0.0;
			int sampleSize = 0.0;
			bool preampOn = false;

			//Test Method Optional Variable
			double measureDelay = 5 mS;
			String ^ boardLossItem = nullptr;
			array<double >^ boardLoss;
			array<double >^ ExtAtt;

			//Operation Variable
			int ChannelCount = 0;
			int ChannelIndex = 0;
			String ^ TM = "MeasureSParamIQ_";
			array<String^>^ UserDesiredResult = nullptr;
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "Channel_"))
				{
					ChannelCount++;
				}
			}

			//Result Variable
			int ResultTotal = ChannelCount * (2 * ChannelCount);
			boardLoss = gcnew array <double>(ChannelCount);
			ExtAtt = gcnew array <double>(ChannelCount);
			array<String^> ^ channelArray = gcnew array<String^>(ChannelCount);
			array<ComplexNumber> ^ l_SparamRaw = gcnew array<ComplexNumber>(ResultTotal / 2);
			array<double>^ ResultArrRe = gcnew array<double >(ResultTotal / 2);
			array<double>^ ResultArrIm = gcnew array<double >(ResultTotal / 2);
			Dictionary<String ^, double> ^ Result = gcnew Dictionary<String^, double>();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "Channel_"))
				{
					channelArray[ChannelIndex] = (String^)tf_TestParameter_ConditionCast(testParameterName, "Channel_" + ChannelIndex);
					ChannelIndex++;
				}
			}

			for (int i = 0; i<(ResultTotal / 2); i++)
			{
				ResultArrRe[i] = 0.0;
				ResultArrIm[i] = 0.0;
			}

			if ((bool)testConditionCollection->ContainsKey("SourcePower"))
			{
				sourcePower = (double)tf_TestParameter_ConditionCast(testParameterName, "SourcePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourcePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleRate"))
			{
				sampleRate = (double)tf_TestParameter_ConditionCast(testParameterName, "SampleRate");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleRate" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SampleSize"))
			{
				sampleSize = (int)tf_TestParameter_ConditionCast(testParameterName, "SampleSize");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SampleSize" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("PreampOn"))
			{
				preampOn = (bool)tf_TestParameter_ConditionCast(testParameterName, "PreampOn");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "PreampOn" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			for (int i = 0; i < boardLoss->Length; i++)
			{
				boardLoss[i] = 0;

				if ((bool)testConditionCollection->ContainsKey("BoardLossItem_" + i.ToString()))
				{
					boardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "BoardLossItem_" + i.ToString());

					if (tl->glob->boardLoss[testSite]->ContainsKey(boardLossItem))
					{
						boardLoss[i] = tl->glob->boardLoss[testSite][boardLossItem];
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "BoardLossItem_" + i.ToString() + ": " + boardLossItem + "] is not exist in the BoardLoss.csv";
						throw gcnew Exception(ErrorMessage);
					}
				}
			}
			for (int i = 0; i < ExtAtt->Length; i++)
			{
				ExtAtt[i] = 0;

				if ((bool)testConditionCollection->ContainsKey("ExtAtt_" + i.ToString()))
				{
					ExtAtt[i] = (double)tf_TestParameter_ConditionCast(testParameterName, "ExtAtt_" + i.ToString());
				}
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			RF_MeasureSParamSetup(testSite, channelArray, sourcePower, measurePower, measureFreq, preampOn, sampleSize, sampleRate);
			util->WaitSecond(measureDelay);
			RF_MeasureSParam(testSite, channelArray, SParam_Format::MAG_PHASE, l_SparamRaw);

			for (int i = 0; i < (ResultTotal / 2); i++)
			{
				ResultArrRe[i] = l_SparamRaw[i].Re;
				ResultArrIm[i] = l_SparamRaw[i].Im;
			}

			switch (ChannelCount)
			{
			case 1:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S11_Im", ResultArrIm[0]);
			case 2:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S12_Re", ResultArrRe[1] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S21_Re", ResultArrRe[2] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S22_Re", ResultArrRe[3] + (boardLoss[1] * 2) + (ExtAtt[1] * 2));

				Result->Add("S11_Im", ResultArrIm[0]);
				Result->Add("S12_Im", ResultArrIm[1]);
				Result->Add("S21_Im", ResultArrIm[2]);
				Result->Add("S22_Im", ResultArrIm[3]);
				break;
			case 3:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S12_Re", ResultArrRe[1] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S13_Re", ResultArrRe[2] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));

				Result->Add("S21_Re", ResultArrRe[3] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S22_Re", ResultArrRe[4] + (boardLoss[1] * 2) + (ExtAtt[1] * 2));
				Result->Add("S23_Re", ResultArrRe[5] + (boardLoss[1] + boardLoss[2]) + (ExtAtt[1] + ExtAtt[2]));

				Result->Add("S31_Re", ResultArrRe[6] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));
				Result->Add("S32_Re", ResultArrRe[7] + (boardLoss[1] + boardLoss[2]) + (ExtAtt[1] + ExtAtt[2]));
				Result->Add("S33_Re", ResultArrRe[8] + (boardLoss[2] * 2) + (ExtAtt[2] * 2));

				Result->Add("S11_Im", ResultArrIm[9]);
				Result->Add("S12_Im", ResultArrIm[10]);
				Result->Add("S13_Im", ResultArrIm[11]);

				Result->Add("S21_Im", ResultArrIm[12]);
				Result->Add("S22_Im", ResultArrIm[13]);
				Result->Add("S23_Im", ResultArrIm[14]);

				Result->Add("S31_Im", ResultArrIm[15]);
				Result->Add("S32_Im", ResultArrIm[16]);
				Result->Add("S33_Im", ResultArrIm[17]);

				break;
			case 4:
				Result->Clear();
				Result->Add("S11_Re", ResultArrRe[0] + (boardLoss[0] * 2) + (ExtAtt[0] * 2));
				Result->Add("S12_Re", ResultArrRe[1] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S13_Re", ResultArrRe[2] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));
				Result->Add("S14_Re", ResultArrRe[3] + (boardLoss[3] + boardLoss[0]) + (ExtAtt[3] + ExtAtt[0]));

				Result->Add("S21_Re", ResultArrRe[4] + (boardLoss[1] + boardLoss[0]) + (ExtAtt[1] + ExtAtt[0]));
				Result->Add("S22_Re", ResultArrRe[5] + (boardLoss[1] * 2) + (ExtAtt[1] * 2));
				Result->Add("S23_Re", ResultArrRe[6] + (boardLoss[2] + boardLoss[1]) + (ExtAtt[2] + ExtAtt[1]));
				Result->Add("S24_Re", ResultArrRe[7] + (boardLoss[3] + boardLoss[1]) + (ExtAtt[3] + ExtAtt[1]));

				Result->Add("S31_Re", ResultArrRe[8] + (boardLoss[2] + boardLoss[0]) + (ExtAtt[2] + ExtAtt[0]));
				Result->Add("S32_Re", ResultArrRe[9] + (boardLoss[1] + boardLoss[2]) + (ExtAtt[1] + ExtAtt[2]));
				Result->Add("S33_Re", ResultArrRe[10] + (boardLoss[2] * 2) + (ExtAtt[2] * 2));
				Result->Add("S34_Re", ResultArrRe[11] + (boardLoss[2] + boardLoss[3]) + (ExtAtt[2] + ExtAtt[3]));

				Result->Add("S41_Re", ResultArrRe[12] + (boardLoss[3] + boardLoss[0]) + (ExtAtt[3] + ExtAtt[0]));
				Result->Add("S42_Re", ResultArrRe[13] + (boardLoss[3] + boardLoss[1]) + (ExtAtt[3] + ExtAtt[1]));
				Result->Add("S43_Re", ResultArrRe[14] + (boardLoss[2] + boardLoss[3]) + (ExtAtt[2] + ExtAtt[3]));
				Result->Add("S44_Re", ResultArrRe[15] + (boardLoss[3] * 2) + (ExtAtt[3] * 2));

				Result->Add("S11_Im", ResultArrIm[0]);
				Result->Add("S12_Im", ResultArrIm[1]);
				Result->Add("S13_Im", ResultArrIm[2]);
				Result->Add("S14_Im", ResultArrIm[3]);

				Result->Add("S21_Im", ResultArrIm[4]);
				Result->Add("S22_Im", ResultArrIm[5]);
				Result->Add("S23_Im", ResultArrIm[6]);
				Result->Add("S24_Im", ResultArrIm[7]);

				Result->Add("S31_Im", ResultArrIm[8]);
				Result->Add("S32_Im", ResultArrIm[9]);
				Result->Add("S33_Im", ResultArrIm[10]);
				Result->Add("S34_Im", ResultArrIm[11]);

				Result->Add("S41_Im", ResultArrIm[12]);
				Result->Add("S42_Im", ResultArrIm[13]);
				Result->Add("S43_Im", ResultArrIm[14]);
				Result->Add("S44_Im", ResultArrIm[15]);
				break;
			default:
				ErrorMessage = "The Total Channel Count is more than 4 Channels. Only support S1p, S2p, S3p & S4p only.";
				throw gcnew Exception(ErrorMessage);
				break;
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["S11_Re"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureSParamIQ");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_PowerServo(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_PowerServo");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			String^ measureChannel = nullptr;
			double measureFreq = 0.0;
			double targetPout = 0.0;
			double gain = 0.0;

			//Test Method Optional Variable
			int maxServoCount = 10;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5 mS;
			double servoTolerance = 0.05;
			double sourceAttenuation = 0.0;
			String ^ outputBoardLossItem = nullptr;
			double outputBoardLoss;
			String ^ inputBoardLossItem = nullptr;
			double inputBoardLoss;
			double poutOffset = 0.0;
			double inputExtAtt = 0.0;
			double outputExtAtt = 0.0;

			//Operation Variable
			int Count = 0;
			int ServoAlarm = 100;
			int ServoPass = 0;
			double Pin = 0.0;
			double Pout_Target = 0.0;
			double MeasureLevel = 0.0;
			double MeasureLevelBuffer = 10;
			double SourceTunning = 0.0;
			double PowerMaxLimit = 15;
			double PowerMinLimit = -100;
			double Tolerance = 0.0;
			double Nextval = 0.0;
			double Pout = 0.0;
			bool UserInputSourceAttenuation = false;
			String ^ TM = "PowerServo_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Gain"))
			{
				gain = (double)tf_TestParameter_ConditionCast(testParameterName, "Gain");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "Gain" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TargetPout"))
			{
				targetPout = (double)tf_TestParameter_ConditionCast(testParameterName, "TargetPout");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TargetPout" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("MaxServoCount"))
			{
				maxServoCount = (int)tf_TestParameter_ConditionCast(testParameterName, "MaxServoCount");
			}
			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				sourceAttenuation = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceAttenuation");
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("ServoTolerance"))
			{
				servoTolerance = (double)tf_TestParameter_ConditionCast(testParameterName, "ServoTolerance");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 6; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			Pin = targetPout - gain;
			Pin = Pin + inputBoardLoss + inputExtAtt;
			SourceTunning = Pin;
			Pout_Target = targetPout - outputBoardLoss - outputExtAtt;
			MeasureLevel = Pout_Target + MeasureLevelBuffer;

			RF_MeasureSetup(testSite, measureChannel, MeasureLevel, measureFreq, filterOption);

			if (UserInputSourceAttenuation == true)
			{
				RF_SourcePower(testSite, sourceChannel, SourceTunning, measureFreq, sourceAttenuation);
			}
			else
			{
				RF_SourcePower(testSite, sourceChannel, SourceTunning, measureFreq);
			}

			RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);
			Count++;

			if (Math::Abs(Pout - Pout_Target) > servoTolerance)
			{
				while (true)
				{
					if (Count > maxServoCount - 1)
					{
						ServoPass = 0;
						ServoAlarm = 1;//ExceedSearchCount
						break;
					}

					Nextval = Pout_Target - Pout;
					SourceTunning += Nextval;

					if (SourceTunning > PowerMaxLimit || SourceTunning < PowerMinLimit)
					{
						SourceTunning = Pin;
					}

					if (UserInputSourceAttenuation == true)
					{
						RF_SourcePower(testSite, sourceChannel, SourceTunning, measureFreq, sourceAttenuation);
					}
					else
					{
						RF_SourcePower(testSite, sourceChannel, SourceTunning, measureFreq);
					}

					RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);

					Tolerance = Math::Abs(Pout - Pout_Target);
					Count++;

					if (Tolerance <= servoTolerance)
					{
						ServoPass = 1;
						ServoAlarm = 0;
						break;
					}

				}
			}
			else
			{
				ServoPass = 1;
				ServoAlarm = 0;
			}

			//Storing Result into Array
			ResultArr[ResultCount] = SourceTunning - inputBoardLoss - inputExtAtt;//Source Power
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;//Measured Power
			ResultArr[++ResultCount] = (Pout + outputBoardLoss + outputExtAtt) - (SourceTunning - inputBoardLoss - inputExtAtt);//Gain
			ResultArr[++ResultCount] = ServoPass;//Servo Pass Status 
			ResultArr[++ResultCount] = Count;//Servo Count 
			ResultArr[++ResultCount] = ServoAlarm;//Servo Alarm Status

												  //Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);
			Result->Add("ServoPassStatus", ResultArr[++ResultCount]);
			Result->Add("ServoCountStatus", ResultArr[++ResultCount]);
			Result->Add("ServoAlarmStatus", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_PowerServo");


#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_PowerServo_BinarySearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_PowerServo_BinarySearch");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			String^ measureChannel = nullptr;
			double measureFreq = 0.0;
			double targetPout = 0.0;
			double startSourceLevel = 0.0;
			double stopSourceLevel = 0.0;

			//Test Method Optional Variable
			int maxServoCount = 10;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5 mS;
			double servoTolerance = 0.05;
			double sourceAttenuation = 0.0;
			String^ inputBoardLossItem = nullptr;
			String^ outputBoardLossItem = nullptr;
			double outputBoardLoss = 0.0;
			double inputBoardLoss = 0.0;
			double inputExtAtt = 0.0;
			double outputExtAtt = 0.0;

			//Operation Variable
			int SearchCount = 0;
			int SearchAlarm = 100;
			int SearchPass = 0;
			bool SearchMinPass = false;
			bool SearchMaxPass = false;
			double XMin = 0.0;
			double XMax = 0.0;
			double Pin = 0.0;
			double Pout = 0.0;
			double YTarget = 0.0;
			double YTolerance = 0.0;
			double YMeasured = 0.0;
			double X1 = 0.0;
			double X2 = 0.0;
			double Y1 = 0.0;
			double Y2 = 0.0;
			double XDelta = 0.0;
			double YDelta = 0.0;
			double Slope = 0.0;
			double Algo = 0.0;
			double MeasureLevel = 0.0;
			double MeasureLevelBuffer = 10.0;
			double GainMeasured = 0.0;
			bool UserInputSourceAttenuation = false;
			String ^ TM = "PowerServo_BinarySearch_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<


			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TargetPout"))
			{
				targetPout = (double)tf_TestParameter_ConditionCast(testParameterName, "TargetPout");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TargetPout" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("StartSourceLevel"))
			{
				startSourceLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StartSourceLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartSourceLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("StopSourceLevel"))
			{
				stopSourceLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StopSourceLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopSourceLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("MaxServoCount"))
			{
				maxServoCount = (int)tf_TestParameter_ConditionCast(testParameterName, "MaxServoCount");
			}
			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				sourceAttenuation = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceAttenuation");
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("ServoTolerance"))
			{
				servoTolerance = (double)tf_TestParameter_ConditionCast(testParameterName, "ServoTolerance");
			}

			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 6; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			XMin = startSourceLevel + inputBoardLoss + inputExtAtt;
			XMax = stopSourceLevel + inputBoardLoss + inputExtAtt;
			Pin = XMin;
			YTarget = targetPout - outputBoardLoss - outputExtAtt;
			YTolerance = servoTolerance;

			MeasureLevel = targetPout - outputBoardLoss - outputExtAtt + MeasureLevelBuffer;
			RF_MeasureSetup(testSite, measureChannel, MeasureLevel, measureFreq, filterOption);

			while (!SearchPass)
			{
				if (SearchCount > maxServoCount - 1)
				{
					SearchPass = 0;
					SearchAlarm = 1;//ExceedSearchCount
					break;

				}
				else
				{
					if (UserInputSourceAttenuation == true)
					{
						RF_SourcePower(testSite, sourceChannel, Pin, measureFreq, sourceAttenuation);
					}
					else
					{
						RF_SourcePower(testSite, sourceChannel, Pin, measureFreq);
					}

					RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);
					YMeasured = Pout;

					if (SearchCount == 0)
					{
						if ((Math::Abs(YMeasured - YTarget)) <= YTolerance)
						{
							SearchAlarm = 0;//TARGET_FOUND
							SearchPass = 1;
						}
						else
						{
							if (YMeasured < YTarget)
							{
								SearchMinPass = true;
							}
							else
							{
								SearchMinPass = false;
							}

							X1 = Pin;
							Y1 = YMeasured;
							Pin = XMax;
						}
					}
					else if (SearchCount == 1)
					{
						if ((Math::Abs(YMeasured - YTarget)) <= YTolerance)
						{
							SearchAlarm = 0;//TARGET_FOUND
							SearchPass = 1;
						}
						else
						{
							if (YMeasured > YTarget)
							{
								SearchMaxPass = true;
							}
							else
							{
								SearchMaxPass = false;
							}

							if (Y1 < YMeasured)
							{
								X2 = Pin;
								Y2 = YMeasured;
							}
							else
							{
								X2 = X1;
								Y2 = Y1;
								X1 = Pin;
								Y1 = YMeasured;
							}

							if (!SearchMinPass)
							{
								SearchPass = 0;
								SearchAlarm = 2;//Min_Fail
								break;
							}
							else if (!SearchMaxPass)
							{
								SearchPass = 0;
								SearchAlarm = 3;//MaxFail
								break;

							}
							else
							{
								YDelta = Y2 - Y1;
								XDelta = X2 - X1;
								if ((YDelta == 0.0) || (XDelta == 0.0))
								{
									SearchPass = 0;
									SearchAlarm = 3;//SlopeFail
								}
								else
								{
									Slope = YDelta / XDelta;
									Algo = ((Y2 + Y1) - Slope * (X2 + X1)) / 2;
									Pin = (YTarget - Algo) / Slope;
								}
							}
						}
					}
					else if ((Math::Abs(YMeasured - YTarget)) > YTolerance)
					{
						if (YMeasured > YTarget)
						{
							X2 = Pin;
							Y2 = YMeasured;
						}
						else
						{
							X1 = Pin;
							Y1 = YMeasured;
						}

						YDelta = Y2 - Y1;
						XDelta = X2 - X1;

						if ((YDelta == 0.0) || (XDelta == 0.0))
						{
							SearchPass = 0;
							SearchAlarm = 3;//SlopeFail
						}
						else
						{
							Slope = YDelta / XDelta;
							Algo = ((Y2 + Y1) - Slope * (X2 + X1)) / 2;
							Pin = (YTarget - Algo) / Slope;
						}
					}
					else
					{
						SearchAlarm = 0;//TargetFail
						SearchPass = 1;
					}
					SearchCount++;

					//ResultArr[0] = Pin - InputBoardLoss - InputExtAtt;
					//ResultArr[1] = Pout + OutputBoardLoss + OutputExtAtt;
					//ResultArr[2] = (Pout + OutputBoardLoss + OutputExtAtt) - (Pin - InputBoardLoss - InputExtAtt);
					//ResultArr[3] = SearchPass;
					//ResultArr[4] = SearchCount;
					//ResultArr[5] = SearchAlarm;
				}
			}

			//Storing Result into Array
			ResultArr[ResultCount] = Pin - inputBoardLoss - inputExtAtt;
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;
			ResultArr[++ResultCount] = (Pout + outputBoardLoss + outputExtAtt) - (Pin - inputBoardLoss - inputExtAtt);
			ResultArr[++ResultCount] = SearchPass;
			ResultArr[++ResultCount] = SearchCount;
			ResultArr[++ResultCount] = SearchAlarm;

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);
			Result->Add("ServoPassStatus", ResultArr[++ResultCount]);
			Result->Add("ServoCountStatus", ResultArr[++ResultCount]);
			Result->Add("ServoAlarmStatus", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_PowerServo_BinarySearch");


#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_PowerServo_LinearSearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_PowerServo_LinearSearch");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			String^ measureChannel = nullptr;
			double measureFreq = 0.0;
			double targetPout = 0.0;
			double startSourceLevel = 0.0;
			double stopSourceLevel = 0.0;
			double sourceIncrement = 0.0;

			//Test Method Optional Variable
			int maxServoCount = 10;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5 mS;
			double servoTolerance = 0.05;
			double sourceAttenuation = 0.0;
			int currentMeasurementCount = 0;
			int voltageMeasurementCount = 0;
			bool sweepOperation = false;
			array<String^ >^ currentMeasurementPin;
			array<String^ >^ voltageMeasurementPin;
			array<double >^ currentMeasurementDelay;
			array<double >^ voltageMeasurementDelay;
			String^ inputBoardLossItem = nullptr;
			String^ outputBoardLossItem = nullptr;
			double outputBoardLoss = 0.0;
			double inputBoardLoss = 0.0;
			double typGainSweepOperation = 0.0;
			double inputExtAtt = 0.0;
			double outputExtAtt = 0.0;

			//Operation Variable
			int Count = 0;
			int ServoAlarm = 100;
			int ServoPass = 0;
			double Pin = 0.0;
			double Pout_Target = 0.0;
			double MeasureLevel = 0.0;
			double MeasureLevelBuffer = 10.0;
			double PowerMaxLimit = 15;
			double PowerMinLimit = -100;
			double Tolerance = 0.0;
			double Pout = 0.0;
			bool UserInputSourceAttenuation = false;
			String ^ TM = "PowerServo_LinearSearch_";
			String ^ ModeMeasurement = nullptr;
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<


			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "CurrentMeasurementPin_"))
				{
					currentMeasurementCount++;
				}

				if (testcond->Name->StartsWith(TM + "VoltageMeasurementPin_"))
				{
					voltageMeasurementCount++;
				}
			}

			if (currentMeasurementCount != 0)
			{
				currentMeasurementPin = gcnew array<String^>(currentMeasurementCount);
				currentMeasurementDelay = gcnew array<double>(currentMeasurementCount);
			}
			if (voltageMeasurementCount != 0)
			{
				voltageMeasurementPin = gcnew array<String^>(voltageMeasurementCount);
				voltageMeasurementDelay = gcnew array<double>(voltageMeasurementCount);
			}

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TargetPout"))
			{
				targetPout = (double)tf_TestParameter_ConditionCast(testParameterName, "TargetPout");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TargetPout" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("StartSourceLevel"))
			{
				startSourceLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StartSourceLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartSourceLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("StopSourceLevel"))
			{
				stopSourceLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StopSourceLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopSourceLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourceIncrement"))
			{
				sourceIncrement = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceIncrement");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceIncrement" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("MaxServoCount"))
			{
				maxServoCount = (int)tf_TestParameter_ConditionCast(testParameterName, "MaxServoCount");
			}
			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				sourceAttenuation = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceAttenuation");
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("ServoTolerance"))
			{
				servoTolerance = (double)tf_TestParameter_ConditionCast(testParameterName, "ServoTolerance");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			for (int i = 0; i < currentMeasurementCount; i++)
			{
				if ((bool)testConditionCollection->ContainsKey("CurrentMeasurementPin_" + i.ToString()))
				{
					currentMeasurementPin[i] = (String^)tf_TestParameter_ConditionCast(testParameterName, "CurrentMeasurementPin_" + i.ToString());
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "CurrentMeasurementPin_" + i.ToString() + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

				if ((bool)testConditionCollection->ContainsKey("CurrentMeasurementDelay_" + i.ToString()))
				{
					currentMeasurementDelay[i] = (int)tf_TestParameter_ConditionCast(testParameterName, "CurrentMeasurementDelay_" + i.ToString());
				}
				else
				{
					currentMeasurementDelay[i] = 0.0;
				}
			}

			for (int i = 0; i < voltageMeasurementCount; i++)
			{
				if ((bool)testConditionCollection->ContainsKey("VoltageMeasurementPin_" + i.ToString()))
				{
					voltageMeasurementPin[i] = (String^)tf_TestParameter_ConditionCast(testParameterName, "VoltageMeasurementPin_" + i);
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "VoltageMeasurementPin_" + i.ToString() + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

				if ((bool)testConditionCollection->ContainsKey("VoltageMeasurementDelay_" + i.ToString()))
				{
					voltageMeasurementDelay[i] = (int)tf_TestParameter_ConditionCast(testParameterName, "VoltageMeasurementDelay_" + i.ToString());
				}
				else
				{
					voltageMeasurementDelay[i] = 0.0;
				}
			}
			if (tl->glob->AWV.Debug == 1)
			{
				if ((bool)testConditionCollection->ContainsKey("SweepOperation"))
				{
					sweepOperation = (bool)tf_TestParameter_ConditionCast(testParameterName, "SweepOperation");
				}
				if (sweepOperation == true)
				{
					if ((bool)testConditionCollection->ContainsKey("TypGainSweepOperation"))
					{
						typGainSweepOperation = (double)tf_TestParameter_ConditionCast(testParameterName, "TypGainSweepOperation");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "TypGainSweepOperation" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 6; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			ResultTotal = ResultTotal + currentMeasurementCount + voltageMeasurementCount;
			array<double >^ currentMeasurementResult = gcnew array<double>(currentMeasurementCount);
			array<double >^ voltageMeasurementResult = gcnew array<double>(voltageMeasurementCount);
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			Pout_Target = targetPout - outputBoardLoss - outputExtAtt;
			MeasureLevel = Pout_Target + MeasureLevelBuffer;

			RF_MeasureSetup(testSite, measureChannel, MeasureLevel, measureFreq, filterOption);

			for (Pin = startSourceLevel; Pin <= stopSourceLevel; Pin = Pin + sourceIncrement)
			{
				if (UserInputSourceAttenuation == true)
				{
					RF_SourcePower(testSite, sourceChannel, Pin + inputBoardLoss + inputExtAtt, measureFreq, sourceAttenuation);
				}
				else
				{
					RF_SourcePower(testSite, sourceChannel, Pin + inputBoardLoss + inputExtAtt, measureFreq);
				}

				RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);
				Tolerance = Math::Abs(Pout - Pout_Target);
				Count++;

				if (Tolerance <= servoTolerance)
				{
					ServoAlarm = 0;
					ServoPass = 1;
					break;
				}

				if (Pin >= stopSourceLevel || Count > maxServoCount - 1)
				{
					if (Pin >= stopSourceLevel)
					{
						ServoAlarm = 3;//ExceedStopSourceLevel
						ServoPass = 0;
						break;
					}
					else
					{
						ServoAlarm = 1;//ExceedSearchCount
						ServoPass = 0;
						break;
					}
				}
			}

			//Current Measurement
			for (int i = 0; i < currentMeasurementCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(currentMeasurementPin[i])[0];

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					module400series->DM_MeasureCurrent(testSite, currentMeasurementPin[i], currentMeasurementDelay[i], currentMeasurementResult[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					module400series->SMU_MeasureCurrent(testSite, currentMeasurementPin[i], currentMeasurementDelay[i], currentMeasurementResult[i]);
				}
			}

			//Voltage Measurement
			for (int i = 0; i < voltageMeasurementCount; i++)
			{

				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(voltageMeasurementPin[i])[0];

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					module400series->DM_MeasureVoltage(testSite, voltageMeasurementPin[i], voltageMeasurementDelay[i], voltageMeasurementResult[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					module400series->SMU_MeasureVoltage(testSite, voltageMeasurementPin[i], voltageMeasurementDelay[i], voltageMeasurementResult[i]);
				}
			}

			//Storing Result into Array
			ResultArr[ResultCount] = Pin;
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;
			ResultArr[++ResultCount] = (Pout + outputBoardLoss + outputExtAtt) - (Pin);
			ResultArr[++ResultCount] = ServoPass;
			ResultArr[++ResultCount] = Count;
			ResultArr[++ResultCount] = ServoAlarm;

			for (int i = 0; i < currentMeasurementCount; i++)
			{
				ResultArr[++ResultCount] = currentMeasurementResult[i];
			}
			for (int i = 0; i < voltageMeasurementCount; i++)
			{
				ResultArr[++ResultCount] = voltageMeasurementResult[i];
			}

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);
			Result->Add("ServoPassStatus", ResultArr[++ResultCount]);
			Result->Add("ServoCountStatus", ResultArr[++ResultCount]);
			Result->Add("ServoAlarmStatus", ResultArr[++ResultCount]);

			for (int i = 0; i < currentMeasurementCount; i++)
			{
				ModeMeasurement = "Current_";
				Result->Add(ModeMeasurement + currentMeasurementPin[i], ResultArr[++ResultCount]);
			}
			for (int i = 0; i < voltageMeasurementCount; i++)
			{
				ModeMeasurement = "Voltage_";
				Result->Add(ModeMeasurement + voltageMeasurementPin[i], ResultArr[++ResultCount]);
			}

			if (tl->glob->AWV.Debug == 1)
			{
				if (sweepOperation == true)
				{
					FileLogger^ fileLogger = gcnew FileLogger(FILE_CONST_AEM_DEBUG);
					array <double>^ sweepResult;

					String ^ StrToFileSweep = "Pin,Pout,Gain";
					String ^ currentItem = "";
					String^ voltageItem = "";
					String ^ fileSweepName = tl->glob->TestProperty[testSite].TestItemName + "_" + testParameterName + "_SweepOperationPin_S" + tl->glob->tf.TestSite.ToString() + "UUT" + testSite.ToString() + ".csv";

					for (int i = 0; i < currentMeasurementCount; i++)
					{
						currentItem = currentItem + ",Current_" + currentMeasurementPin[i];
					}

					for (int i = 0; i < voltageMeasurementCount; i++)
					{
						voltageItem = voltageItem + ",Voltage_" + voltageMeasurementPin[i];
					}

					StrToFileSweep = StrToFileSweep + currentItem + voltageItem;
					fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_OVERWRITE);

					for (Pin = startSourceLevel; Pin <= stopSourceLevel; Pin = Pin + sourceIncrement)
					{
						int count = 0;
						StrToFileSweep = nullptr;
						sweepResult = gcnew array <double>(3 + currentMeasurementCount + voltageMeasurementCount);

						RF_MeasureSetup(testSite, measureChannel, (Pin + typGainSweepOperation - outputBoardLoss - outputExtAtt + MeasureLevelBuffer), measureFreq, filterOption);

						if (UserInputSourceAttenuation == true)
						{
							RF_SourcePower(testSite, sourceChannel, (Pin + inputBoardLoss + inputExtAtt), measureFreq, sourceAttenuation);
						}
						else
						{
							RF_SourcePower(testSite, sourceChannel, (Pin + inputBoardLoss + inputExtAtt), measureFreq);
						}

						RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);

						Pout = Pout + outputBoardLoss + outputExtAtt;

						sweepResult[count++] = Pin;
						sweepResult[count++] = Pout;
						sweepResult[count++] = Pout - Pin;

						//Current Measurement
						for (int i = 0; i < currentMeasurementCount; i++)
						{
							Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(currentMeasurementPin[i])[0];

							if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
							{
								module400series->DM_MeasureCurrent(testSite, currentMeasurementPin[i], currentMeasurementDelay[i], currentMeasurementResult[i]);
							}
							else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
							{
								module400series->SMU_MeasureCurrent(testSite, currentMeasurementPin[i], currentMeasurementDelay[i], currentMeasurementResult[i]);
							}

							sweepResult[count++] = currentMeasurementResult[i];

						}

						//Voltage Measurement
						for (int i = 0; i < voltageMeasurementCount; i++)
						{

							Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(voltageMeasurementPin[i])[0];

							if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
							{
								module400series->DM_MeasureVoltage(testSite, voltageMeasurementPin[i], voltageMeasurementDelay[i], voltageMeasurementResult[i]);
							}
							else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
							{
								module400series->SMU_MeasureVoltage(testSite, voltageMeasurementPin[i], voltageMeasurementDelay[i], voltageMeasurementResult[i]);
							}

							sweepResult[count++] = voltageMeasurementResult[i];

						}

						for (int i = 0; i < count; i++)
						{
							if (i == 0)
							{
								StrToFileSweep = sweepResult[i].ToString();
							}
							else
							{
								StrToFileSweep = StrToFileSweep + "," + sweepResult[i].ToString();
							}
						}

						fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);
					}
				}
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_PowerServo_LinearSearch");


#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_P1dB_BinarySearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_P1dB_BinarySearch");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			String^ measureChannel = nullptr;
			double measureFreq = 0.0;
			double Gain = 0.0;
			double startSourceLevel = 0.0;
			double stopSourceLevel = 0.0;

			//Test Method Optional Variable
			int maxServoCount = 10;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5 mS;
			double servoTolerance = 0.05;
			double sourceAttenuation = 0.0;
			double referenceGain = 0.0;
			String^ referenceGainItem = nullptr;
			String^ inputBoardLossItem = nullptr;
			String^ outputBoardLossItem = nullptr;
			double outputBoardLoss = 0.0;
			double inputBoardLoss = 0.0;
			double inputExtAtt = 0.0;
			double outputExtAtt = 0.0;

			//Operation Variable
			int SearchCount = 0;
			int SearchAlarm = 100;
			int SearchPass = 0;
			bool SearchMinPass = false;
			bool SearchMaxPass = false;
			double XMin = 0.0;
			double XMax = 0.0;
			double Pin = 0.0;
			double Pout = 0.0;
			double YTarget = 0.0;
			double YTolerance = 0.0;
			double YMeasured = 0.0;
			double X1 = 0.0;
			double X2 = 0.0;
			double Y1 = 0.0;
			double Y2 = 0.0;
			double XDelta = 0.0;
			double YDelta = 0.0;
			double Slope = 0.0;
			double Algo = 0.0;
			double MeasureLevel = 0.0;
			double MeasureLevelBuffer = 10.0;
			double GainMeasured = 0.0;
			bool UserInputSourceAttenuation = false;
			bool referenceGainExist = false;
			String ^ TM = "P1dB_BinarySearch_";
			String ^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Gain"))
			{
				Gain = (double)tf_TestParameter_ConditionCast(testParameterName, "Gain");
			}
			else
			{
				if (!((bool)testConditionCollection->ContainsKey("ReferenceGainItem")))
				{
					ErrorMessage = "Test Condition [" + TM + "Gain" + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("StartSourceLevel"))
			{
				startSourceLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StartSourceLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartSourceLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("StopSourceLevel"))
			{
				stopSourceLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StopSourceLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopSourceLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("MaxServoCount"))
			{
				maxServoCount = (int)tf_TestParameter_ConditionCast(testParameterName, "MaxServoCount");
			}
			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				sourceAttenuation = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceAttenuation");
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("ServoTolerance"))
			{
				servoTolerance = (double)tf_TestParameter_ConditionCast(testParameterName, "ServoTolerance");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("ReferenceGainItem"))
			{
				referenceGainItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "ReferenceGainItem");

				if (!tl->glob->GlobalResult[testSite]->ContainsKey(referenceGainItem))
				{
					ErrorMessage = "Test Condition [" + "ReferenceGainItem: " + referenceGainItem + "] is not exist.";
					throw gcnew Exception(ErrorMessage);
				}
				else
				{
					referenceGain = (double)tl->glob->GlobalResult[testSite][referenceGainItem];
					referenceGainExist = true;
				}
			}
			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 6; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);


			XMin = startSourceLevel + inputBoardLoss + inputExtAtt;
			XMax = stopSourceLevel + inputBoardLoss + inputExtAtt;
			Pin = XMin;
			if (referenceGainExist == false)
			{
				YTarget = Gain - 1;
			}
			else
			{
				YTarget = referenceGain - 1;
			}
			YTolerance = servoTolerance;

			MeasureLevel = Pin + YTarget - outputBoardLoss - outputExtAtt + MeasureLevelBuffer;
			RF_MeasureSetup(testSite, measureChannel, MeasureLevel, measureFreq, filterOption);

			while (!SearchPass)
			{
				if (SearchCount > maxServoCount - 1)
				{
					SearchPass = 0;
					SearchAlarm = 1;//ExceedSearchCount
					break;

				}
				else
				{
					if (UserInputSourceAttenuation == true)
					{
						RF_SourcePower(testSite, sourceChannel, Pin, measureFreq, sourceAttenuation);
					}
					else
					{
						RF_SourcePower(testSite, sourceChannel, Pin, measureFreq);
					}

					RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);
					GainMeasured = (Pout + outputBoardLoss + outputExtAtt) - (Pin);
					YMeasured = GainMeasured;

					if (SearchCount == 0)
					{
						if ((Math::Abs(YMeasured - YTarget)) <= YTolerance)
						{
							SearchAlarm = 0;//TARGET_FOUND
							SearchPass = 1;
						}
						else
						{
							if (YMeasured > YTarget)
							{
								SearchMinPass = true;
							}
							else
							{
								SearchMinPass = false;
							}

							X1 = Pin;
							Y1 = YMeasured;
							Pin = XMax;
						}
					}
					else if (SearchCount == 1)
					{
						if ((Math::Abs(YMeasured - YTarget)) <= YTolerance)
						{
							SearchAlarm = 0;//TARGET_FOUND
							SearchPass = 1;
						}
						else
						{
							if (YMeasured < YTarget)
							{
								SearchMaxPass = true;
							}
							else
							{
								SearchMaxPass = false;
							}

							if (Y1 > YMeasured)
							{
								X2 = Pin;
								Y2 = YMeasured;
							}
							else
							{
								X2 = X1;
								Y2 = Y1;
								X1 = Pin;
								Y1 = YMeasured;
							}

							if (!SearchMinPass)
							{
								SearchPass = 0;
								SearchAlarm = 2;//Min_Fail
								break;
							}
							else if (!SearchMaxPass)
							{
								SearchPass = 0;
								SearchAlarm = 3;//MaxFail
								break;

							}
							else
							{
								YDelta = Y2 - Y1;
								XDelta = X2 - X1;
								if ((YDelta == 0.0) || (XDelta == 0.0))
								{
									SearchPass = 0;
									SearchAlarm = 3;//SlopeFail
								}
								else
								{
									Slope = YDelta / XDelta;
									Algo = ((Y2 + Y1) - Slope * (X2 + X1)) / 2;
									Pin = (YTarget - Algo) / Slope;
									//Pin = x1 + (((yTarget-y1) * (x2-x1))/ (y2 - y1));
								}
							}
						}
					}
					else if ((Math::Abs(YMeasured - YTarget)) > YTolerance)
					{
						if (YMeasured < YTarget)//<
						{
							X2 = Pin;
							Y2 = YMeasured;
						}
						else
						{
							X1 = Pin;
							Y1 = YMeasured;
						}

						YDelta = Y2 - Y1;
						XDelta = X2 - X1;

						if ((YDelta == 0.0) || (XDelta == 0.0))
						{
							SearchPass = 0;
							SearchAlarm = 3;//SlopeFail
						}
						else
						{
							Slope = YDelta / XDelta;
							Algo = ((Y2 + Y1) - Slope * (X2 + X1)) / 2;
							Pin = (YTarget - Algo) / Slope;
							//Pin = x1 + (((yTarget - y1) * (x2 - x1)) / (y2 - y1));

						}
					}
					else
					{
						SearchAlarm = 0;//TargetFail
						SearchPass = 1;
					}
					SearchCount++;

				}
			}

			//Storing Result into Array
			ResultArr[ResultCount] = Pin - inputBoardLoss - inputExtAtt;
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;
			ResultArr[++ResultCount] = (Pout + outputBoardLoss + outputExtAtt) - (Pin - inputBoardLoss - inputExtAtt);
			ResultArr[++ResultCount] = SearchPass;
			ResultArr[++ResultCount] = SearchCount;
			ResultArr[++ResultCount] = SearchAlarm;

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);
			Result->Add("ServoPassStatus", ResultArr[++ResultCount]);
			Result->Add("ServoCountStatus", ResultArr[++ResultCount]);
			Result->Add("ServoAlarmStatus", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_P1dB_BinarySearch");


#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_P1dB_DirectSearch(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_P1dB_DirectSearch");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			String^ measureChannel = nullptr;
			double measureFreq = 0.0;
			double targetPoutP1dbMin = 0.0;
			double referenceGain = 0.0;

			//Test Method Optional Variable
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 5 mS;
			double sourceAttenuation = 0.0;
			String ^ outputBoardLossItem = nullptr;
			double outputBoardLoss;
			String ^ inputBoardLossItem = nullptr;
			double inputBoardLoss;
			String ^referenceGainItem = nullptr;
			double inputExtAtt = 0.0;
			double outputExtAtt = 0.0;

			//Operation Variable
			double Pin = 0.0;
			double Pout = 0.0;
			double MeasureLevel = 0.0;
			double MeasureLevelBuffer = 10.0;
			bool UserInputSourceAttenuation = false;
			String ^ TM = "P1dB_DirectSearch_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ReferenceGainItem"))
			{
				referenceGainItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "ReferenceGainItem");

				if (!tl->glob->GlobalResult[testSite]->ContainsKey(referenceGainItem))
				{
					ErrorMessage = "Test Condition [" + "ReferenceGainItem: " + referenceGainItem + "] is not exist.";
					throw gcnew Exception(ErrorMessage);
				}
				else
				{
					referenceGain = (double)tl->glob->GlobalResult[testSite][referenceGainItem];
				}
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "ReferenceGainItem" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("TargetPoutP1dbMin"))
			{
				targetPoutP1dbMin = (double)tf_TestParameter_ConditionCast(testParameterName, "TargetPoutP1dbMin");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TargetPoutP1dbMin" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				sourceAttenuation = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceAttenuation");
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}

			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 3; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);


			Pin = (targetPoutP1dbMin - referenceGain + 1);
			Pin = Pin + inputBoardLoss + inputExtAtt;
			MeasureLevel = targetPoutP1dbMin + MeasureLevelBuffer;

			RF_MeasureSetup(testSite, measureChannel, MeasureLevel, measureFreq, filterOption);

			if (UserInputSourceAttenuation == true)
			{
				RF_SourcePower(testSite, sourceChannel, Pin, measureFreq, sourceAttenuation);
			}
			else
			{
				RF_SourcePower(testSite, sourceChannel, Pin, measureFreq);
			}

			RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);

			//Storing Result into Array
			ResultArr[ResultCount] = Pin - inputBoardLoss - inputExtAtt;//Source Power
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;//Measured Power
			ResultArr[++ResultCount] = (Pout + outputBoardLoss + outputExtAtt) - (Pin - inputBoardLoss - inputExtAtt);//Gain

																													  //Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_P1dB_DirectSearch");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_ReadEvm(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_ReadEvm");

			testParameterCount = 1;

			//Test Method Compulsory Variable

			//Test Method Optional Variable

			//Operation Variable
			String ^ TM = "ReadEvm_";
			String^ ErrorMessage = nullptr;
			double Result = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_WlanEvmMeasurementReadEvm(testSite, Result);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<
			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_ReadEvm_acax");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_ReadEvmAsync(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_ReadEvmAsync");

			testParameterCount = 1;

			//Test Method Compulsory Variable

			//Test Method Optional Variable

			//Operation Variable
			String ^ TM = "ReadEvmAsync_";
			String^ ErrorMessage = nullptr;
			double Result = CONST_INVALID_RESULT;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_WlanEvmMeasurementReadEvmAsync(testSite, tl->glob->TestProperty[testSite].TestItemName, testParameterName);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<
			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_ReadEvmAsync");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_ReadSem(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_ReadSem");

			testParameterCount = 1;

			//Test Method Compulsory Variable

			//Test Method Optional Variable

			//Operation Variable
			String ^ TM = "ReadSem_";
			String^ ErrorMessage = nullptr;
			double PeakRefPower = 999;
			array<double>^ SemData = nullptr;
			array <double>^ MarginData = nullptr;
			int Status = 999;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 14; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_WlanSemMeasurementReadSem(testSite, PeakRefPower, SemData, MarginData, Status);

			//Storing Result into Array
			ResultArr[ResultCount] = PeakRefPower;//Source Power
			ResultArr[++ResultCount] = Status;//Status
			for (int i = 0; i < SemData->Length; i++)
			{
				ResultArr[++ResultCount] = SemData[i];//SemData
			}
			for (int i = 0; i < MarginData->Length; i++)
			{
				ResultArr[++ResultCount] = MarginData[i];//MarginData
			}


			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("PeakRefPower", ResultArr[ResultCount]);
			Result->Add("Status", ResultArr[++ResultCount]);

			for (int i = 0; i < SemData->Length; i++)
			{
				Result->Add("SemData_" + i.ToString(), ResultArr[++ResultCount]);
			}
			for (int i = 0; i < MarginData->Length; i++)
			{
				Result->Add("MarginData_" + i.ToString(), ResultArr[++ResultCount]);
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["PeakRefPower"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_ReadSem");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_ReadSemAsync(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_ReadSemAsyn");

			testParameterCount = 1;

			//Test Method Compulsory Variable

			//Test Method Optional Variable

			//Operation Variable
			String ^ TM = "ReadSemAsyn_";
			String^ ErrorMessage = nullptr;
			double PeakRefPower = CONST_INVALID_RESULT;
			array<double>^ SemData = { CONST_INVALID_RESULT,CONST_INVALID_RESULT, CONST_INVALID_RESULT, CONST_INVALID_RESULT, CONST_INVALID_RESULT, CONST_INVALID_RESULT };
			array <double>^ MarginData = { CONST_INVALID_RESULT,CONST_INVALID_RESULT, CONST_INVALID_RESULT, CONST_INVALID_RESULT, CONST_INVALID_RESULT, CONST_INVALID_RESULT };
			int Status = CONST_INVALID_RESULT;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 14; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_WlanSemMeasurementReadSemAsync(testSite, tl->glob->TestProperty[testSite].TestItemName, testParameterName);


			//Storing Result into Array
			ResultArr[ResultCount] = PeakRefPower;//Source Power
			ResultArr[++ResultCount] = Status;//Status
			for (int i = 0; i < SemData->Length; i++)
			{
				ResultArr[++ResultCount] = SemData[i];//SemData
			}
			for (int i = 0; i < MarginData->Length; i++)
			{
				ResultArr[++ResultCount] = MarginData[i];//MarginData
			}


			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("PeakRefPower", ResultArr[ResultCount]);
			Result->Add("Status", ResultArr[++ResultCount]);

			for (int i = 0; i < SemData->Length; i++)
			{
				Result->Add("SemData_" + i.ToString(), ResultArr[++ResultCount]);
			}
			for (int i = 0; i < MarginData->Length; i++)
			{
				Result->Add("MarginData_" + i.ToString(), ResultArr[++ResultCount]);
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<
			tl->glob->TestResults[testSite][testParameterNumber] = 999;

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["PeakRefPower"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_ReadSemAsyn");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_WlanPowerServo(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_WlanPowerServo");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ sourceChannel = nullptr;
			String^ measureChannel = nullptr;
			double freq = 0.0;
			double measurePower = 0.0;
			double sourcePin = 0.0;
			double targetPower = 0.0;
			double sourceAttenuation = 0.0;
			bool servoEnable = false;
			int wlanModulationStandard = 999;
			WlanModulationStandardEnum standard;
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;


			//Test Method Option Variable
			String ^ outputBoardLossItem = nullptr;
			double outputBoardLoss;
			String ^ inputBoardLossItem = nullptr;
			double inputBoardLoss;
			double inputExtAtt = 0.0;
			double outputExtAtt = 0.0;
			double servoTolerance = 0.05;

			//Operation Variable
			double Pout = 0.0;
			double SourcePower = 0.0;
			double Gain = 0.0;
			double Pout_Target = 0.0;
			bool ServoPass = false;
			int ServoPass_Int = 0;
			int ServoCount = 0;
			bool UserInputSourceAttenuation = false;

			String ^ TM = "WlanPowerServo_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("Freq"))
			{
				freq = (double)tf_TestParameter_ConditionCast(testParameterName, "Freq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "Freq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SourcePin"))
			{
				sourcePin = (double)tf_TestParameter_ConditionCast(testParameterName, "SourcePin");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourcePin" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TargetPower"))
			{
				targetPower = (double)tf_TestParameter_ConditionCast(testParameterName, "TargetPower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "TargetPower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("ServoEnable"))
			{
				servoEnable = (bool)tf_TestParameter_ConditionCast(testParameterName, "ServoEnable");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "ServoEnable" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("WlanModulationStandard"))
			{
				wlanModulationStandard = (int)tf_TestParameter_ConditionCast(testParameterName, "WlanModulationStandard");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "WlanModulationStandard" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}
			if ((bool)testConditionCollection->ContainsKey("SourceAttenuation"))
			{
				sourceAttenuation = (double)tf_TestParameter_ConditionCast(testParameterName, "SourceAttenuation");
				UserInputSourceAttenuation = true;
			}
			if ((bool)testConditionCollection->ContainsKey("ServoTolerance"))
			{
				servoTolerance = (double)tf_TestParameter_ConditionCast(testParameterName, "ServoTolerance");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 5; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			array<Object^>^ ResultArr = gcnew array<Object^ >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, Object^> ^ Result = gcnew Dictionary<String^, Object^>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			Pout_Target = targetPower - outputBoardLoss - outputExtAtt;

			RF_MeasureSetup(testSite, measureChannel, measurePower, freq, filterOption);

			if (UserInputSourceAttenuation == false)
			{
				RF_SourcePower(testSite, sourceChannel, (sourcePin + inputBoardLoss + inputExtAtt), freq);
			}
			else
			{
				RF_SourcePower(testSite, sourceChannel, (sourcePin + inputBoardLoss + inputExtAtt), freq, sourceAttenuation);
			}

			RF_WlanStandardSelection(testSite, wlanModulationStandard, standard);
			RF_WlanConfigurePowerServo(testSite, servoEnable, standard, (sourcePin + inputBoardLoss + inputExtAtt), Pout_Target, servoTolerance);
			RF_WlanRunPowerServo(testSite);
			RF_WlanReadPowerServo(testSite, Pout, SourcePower, ServoPass, ServoCount);

			if (ServoPass == true)ServoPass_Int = 1;

			//Storing Result into Array
			ResultArr[ResultCount] = SourcePower - inputBoardLoss - inputExtAtt;//Pin
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt;//Pout
			ResultArr[++ResultCount] = (Pout + outputBoardLoss + outputExtAtt) - (SourcePower - inputBoardLoss - inputExtAtt);//Gain
			ResultArr[++ResultCount] = ServoPass_Int;
			ResultArr[++ResultCount] = ServoCount;

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);
			Result->Add("ServoPassStatus", ResultArr[++ResultCount]);
			Result->Add("ServoCountStatus", ResultArr[++ResultCount]);

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_WlanPowerServo");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{
			//ResetAmsrfPreviousState(testSite, true);
		}
	}
	void AMB7600SRTestLibrary::TM_RF_WlanResidualEVM(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
		tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_WlanResidualEVM");

		testParameterCount = 1;

		//Test Method Compulsory Variable
		String^ sourceChannel = nullptr;
		String^ measureChannel = nullptr;

		double startFreq = 0.0;
		double stopFreq = 0.0;
		double incrementFreq = 0.0;
		double startTargetPower = 0.0;
		double stopTargetPower = 0.0;
		double incrementTargetPower = 0.0;
		double startMeasureLevel = 0.0;
		double stopMeasureLevel = 0.0;
		double incrementMeasureLevel = 0.0;
		double startSourceAtt = 0.0;
		double stopSourceAtt = 0.0;
		double incrementSourceAtt = 0.0;
		int wlanModulationStandard = 999;
		int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
		WlanModulationStandardEnum standard;

		//Test Method Option Variable
		String ^ outputBoardLossItem = nullptr;
		double outputBoardLoss;
		String ^ inputBoardLossItem = nullptr;
		double inputBoardLoss;
		double inputExtAtt = 0.0;
		double outputExtAtt = 0.0;
		double servoTolerance = 0.05;
		double typicalGain = 0.0;

		//Operation Variable
		double Pout = 0.0;
		double Pin = 0.0;
		double Gain = 0.0;
		double SourcePower = 0.0;
		double MeasureLevel = 0.0;
		double SourceAtt = 0.0;
		double Pout_Target = 0.0;
		double TargetPower = 0.0;
		double Result = 999.99;
		double Freq = 0.0;
		bool ServoPass = false;
		bool SetWlanSetting = false;
		int ServoPass_Int = 0;
		int ServoCount = 0;
		String ^ TM = "WlanResidualEVM_";
		String^ ErrorMessage = nullptr;
		Dictionary<int, Object^>^ WlanSettings = gcnew Dictionary<int, Object^>();
		List<int>^ Setting = gcnew List<int>();
		array<String^>^ splitStr = nullptr;
		array<String^>^ separators = { TM + "Setting_" };
		DataType Var;

		FileLogger^ fileLogger = gcnew FileLogger(FILE_CONST_AEM_DEBUG);
		array <double>^ sweepResult;

		String ^ StrToFileSweep = "Freq (MHz),TargetPout (dBm),ServoPass,ServoCount,Pout (dBm),Pin (dBm),Gain (dB),EVM (dB),MeasureLevel (dBm),SourceAett (dB)";
		String ^ fileSweepName = tl->glob->TestProperty[testSite].TestItemName + "_" + testParameterName + "_ResidualEVM_Site" + tl->glob->tf.TestSite.ToString() + "UUT" + testSite.ToString() + ".csv";
		fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_OVERWRITE);

		try
		{


#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);


			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "Setting_"))
				{
					splitStr = nullptr;
					splitStr = testcond->Name->Split(separators, StringSplitOptions::RemoveEmptyEntries);
					Setting->Add(Convert::ToInt32(splitStr[0]));
				}
			}

			if ((bool)testConditionCollection->ContainsKey("SourceChannel"))
			{
				sourceChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "SourceChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "SourceChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StartFreq"))
			{
				startFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "StartFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StopFreq"))
			{
				stopFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "StopFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("IncrementFreq"))
			{
				incrementFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "IncrementFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "IncrementFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StartTargetPower"))
			{
				startTargetPower = (double)tf_TestParameter_ConditionCast(testParameterName, "StartTargetPower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartTargetPower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StopTargetPower"))
			{
				stopTargetPower = (double)tf_TestParameter_ConditionCast(testParameterName, "StopTargetPower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopTargetPower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("IncrementTargetPower"))
			{
				incrementTargetPower = (double)tf_TestParameter_ConditionCast(testParameterName, "IncrementTargetPower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "IncrementTargetPower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StartMeasureLevel"))
			{
				startMeasureLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StartMeasureLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartMeasureLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StopMeasureLevel"))
			{
				stopMeasureLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "StopMeasureLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopMeasureLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("IncrementMeasureLevel"))
			{
				incrementMeasureLevel = (double)tf_TestParameter_ConditionCast(testParameterName, "IncrementMeasureLevel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "IncrementMeasureLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StartSourceAtt"))
			{
				startSourceAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "StartSourceAtt");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StartSourceAtt" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("StopSourceAtt"))
			{
				stopSourceAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "StopSourceAtt");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "StopSourceAtt" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("IncrementSourceAtt"))
			{
				incrementSourceAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "IncrementSourceAtt");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "IncrementSourceAtt" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//if ((bool)testConditionCollection->ContainsKey("ServoEnable"))
			//{
			//	servoEnable = (bool)tf_TestParameter_ConditionCast(testParameterName, "ServoEnable");
			//}
			//else
			//{
			//	ErrorMessage = "Test Condition [" + TM + "ServoEnable" + "] is not found.";
			//	throw gcnew Exception(ErrorMessage);
			//}

			if ((bool)testConditionCollection->ContainsKey("WlanModulationStandard"))
			{
				wlanModulationStandard = (int)tf_TestParameter_ConditionCast(testParameterName, "WlanModulationStandard");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "WlanModulationStandard" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("InputBoardLossItem"))
			{
				inputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "InputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(inputBoardLossItem))
				{
					inputBoardLoss = tl->glob->boardLoss[testSite][inputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "InputBoardLossItem: " + inputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("InputExtAtt"))
			{
				inputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "InputExtAtt");
			}

			if ((bool)testConditionCollection->ContainsKey("ServoTolerance"))
			{
				servoTolerance = (double)tf_TestParameter_ConditionCast(testParameterName, "ServoTolerance");
			}

			for (int i = 0; i<Setting->Count; i++)
			{
				RF_WlanEvmSettingVariable(TM, Setting[i], Var);
				tl->TestCondCheckingDataType(TM + "Setting_" + Setting[i], Var, tf_TestParameter_DataType(TM + "Setting_" + Setting[i]));

				switch (Var)
				{
				case DataType::Double:
					WlanSettings->Add(Setting[i], (double)tf_TestParameter_ConditionCast(testParameterName, "Setting_" + Setting[i]));
					break;

				case DataType::Int32:
					WlanSettings->Add(Setting[i], (int)tf_TestParameter_ConditionCast(testParameterName, "Setting_" + Setting[i]));
					break;

				case DataType::String:
					WlanSettings->Add(Setting[i], (String^)tf_TestParameter_ConditionCast(testParameterName, "Setting_" + Setting[i]));
					break;

				case DataType::Boolean:
					WlanSettings->Add(Setting[i], (bool)tf_TestParameter_ConditionCast(testParameterName, "Setting_" + Setting[i]));
					break;
				}

			}
			if ((bool)testConditionCollection->ContainsKey("TypicalGain"))
			{
				typicalGain = (double)tf_TestParameter_ConditionCast(testParameterName, "TypicalGain");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			RF_LoadHardwareProfile(testSite);

			for (Freq = startFreq; Freq <= stopFreq; Freq = Freq + incrementFreq)
			{
				for (TargetPower = startTargetPower; TargetPower <= stopTargetPower; TargetPower = TargetPower + incrementTargetPower)
				{
					SourcePower = TargetPower - typicalGain + inputBoardLoss + inputExtAtt;
					Pout_Target = TargetPower - outputBoardLoss - outputExtAtt;

					for (SourceAtt = startSourceAtt; SourceAtt <= stopSourceAtt; SourceAtt = SourceAtt + incrementSourceAtt)
					{
						for (MeasureLevel = startMeasureLevel; MeasureLevel <= stopMeasureLevel; MeasureLevel = MeasureLevel + incrementMeasureLevel)
						{
							try
							{
								Pout = 999.99;
								Pin = 999.99;
								Gain = 999.99;
								Result = 999.99;
								ServoPass = false;
								ServoCount = 0;

								RF_MeasureSetup(testSite, measureChannel, MeasureLevel, Freq, filterOption);
								util->WaitSecond(5 mS);
								RF_SourcePower(testSite, sourceChannel, SourcePower, Freq, SourceAtt);
								RF_WlanStandardSelection(testSite, wlanModulationStandard, standard);
								RF_WlanConfigurePowerServo(testSite, true, standard, SourcePower, Pout_Target, servoTolerance);
								util->WaitSecond(5 mS);
								RF_WlanRunPowerServo(testSite);
								RF_WlanReadPowerServo(testSite, Pout, Pin, ServoPass, ServoCount);

								Pout = Pout + outputBoardLoss + outputExtAtt;
								Pin = Pin - inputBoardLoss - inputExtAtt;
								Gain = Pout - Pin;

								RF_WlanEvmMeasurementSetup(testSite, standard, SetWlanSetting, WlanSettings);
								RF_WlanEvmMeasurementReadEvm(testSite, Result);

							}
							catch (Exception ^ ex)
							{

							}
							finally
							{
								StrToFileSweep = (Freq / 1000000 Hz).ToString("0.00") + ","
									+ TargetPower.ToString("0.00") + ","
									+ ServoPass.ToString() + ","
									+ ServoCount.ToString() + ","
									+ (Pout).ToString("0.00") + ","
									+ (Pin).ToString("0.00") + ","
									+ (Gain).ToString("0.00") + ","
									+ Result.ToString("0.00") + ","
									+ MeasureLevel.ToString("0.00") + ","
									+ SourceAtt.ToString("0.00");

								fileLogger->WriteToFile(fileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);
							}

						}
					}
				}
			}

			if (ServoPass == true)ServoPass_Int = 1;



#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;


			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_WlanPowerServo");

#pragma endregion "Update Test Result"

		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
		finally
		{




			//ResetAmsrfPreviousState(testSite, true);

		}
	}
	void AMB7600SRTestLibrary::TM_RF_WolferMeasureChannel(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_OS_Test
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

		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method RFCase_WolferMeasureChannel");

			testParameterCount = 1;

			//To get the desired Wolfer Number in current site
			int externalModuleNo = 0;
			for (int i = 0; i < CurrentHeadSite.ExternalModuleList->Count; i++)
			{
				if (CurrentHeadSite.ExternalModuleList[externalModuleNo]["Name"] == "Wolfer")
					externalModuleNo = i;
			}

			//Test Method Compulsory Variable
			String^ wolferType = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Type"];
			String^ IOControl = CurrentHeadSite.ExternalModuleList[externalModuleNo]["Address"];
			String^ selectRxPath = nullptr;
			String^ measureChannel = nullptr;
			double measurePower = 0.0;
			double measureFreq = 0.0;
			String^ measureMode = nullptr;

			//Test Method Option Variable
			int filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
			double measureDelay = 1.0 mS;
			bool measureIQ = false;
			double sampleRate = 0.0;
			int sampleSize = 0;
			int currentMeasurementCount = 0;
			int voltageMeasurementCount = 0;
			double outputBoardLoss = 0.0;
			double outputExtAtt = 0.0;
			String ^ outputBoardLossItem = nullptr;
			array<String^ >^ currentMeasurementPin;
			array<String^ >^ voltageMeasurementPin;
			array<double >^ currentMeasurementDelay;
			array<double >^ voltageMeasurementDelay;

			//Operation Variable
			double Pout = 0.0;
			String ^ TM = "WolferMeasureChannel_";
			String ^ ModeMeasurement = nullptr;
			String^ ErrorMessage = nullptr;

			//wolfer Operation Variable
			double pathloss = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "CurrentMeasurementPin_"))
				{
					currentMeasurementCount++;
				}

				if (testcond->Name->StartsWith(TM + "VoltageMeasurementPin_"))
				{
					voltageMeasurementCount++;
				}
			}

			if (currentMeasurementCount != 0)
			{
				currentMeasurementPin = gcnew array<String^>(currentMeasurementCount);
				currentMeasurementDelay = gcnew array<double>(currentMeasurementCount);
			}
			if (voltageMeasurementCount != 0)
			{
				voltageMeasurementPin = gcnew array<String^>(voltageMeasurementCount);
				voltageMeasurementDelay = gcnew array<double>(voltageMeasurementCount);
			}

			if ((bool)testConditionCollection->ContainsKey("MeasureChannel"))
			{
				measureChannel = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureChannel");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureChannel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasurePower"))
			{
				measurePower = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasurePower");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasurePower" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureFreq"))
			{
				measureFreq = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureFreq");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureFreq" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureMode")) //Bypass or Harmonic Mode
			{
				measureMode = (String^)tf_TestParameter_ConditionCast(testParameterName, "MeasureMode");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "MeasureMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("MeasureDelay"))
			{
				measureDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "MeasureDelay");
			}
			if ((bool)testConditionCollection->ContainsKey("MeasureIQ"))
			{
				measureIQ = (bool)tf_TestParameter_ConditionCast(testParameterName, "MeasureIQ");

				if (measureIQ)
				{
					if ((double)testConditionCollection->ContainsKey("SampleRate"))
					{
						sampleRate = (double)tf_TestParameter_ConditionCast(testParameterName, "SampleRate");
					}
					else
					{
						measureIQ = false;
						System::Windows::Forms::MessageBox::Show("Test Condition [" + TM + "SampleRate" + "] must exist to perform measureIQ.", "Incomplete Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
					if ((int)testConditionCollection->ContainsKey("SampleSize"))
					{
						sampleSize = (int)tf_TestParameter_ConditionCast(testParameterName, "SampleSize");
					}
					else
					{
						measureIQ = false;
						System::Windows::Forms::MessageBox::Show("Test Condition [" + TM + "SampleSize" + "] must exist to perform measureIQ.", "Incomplete Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
			}
			if ((bool)testConditionCollection->ContainsKey("FilterOption"))
			{
				filterOption = (int)tf_TestParameter_ConditionCast(testParameterName, "FilterOption");
			}
			if ((bool)testConditionCollection->ContainsKey("OutputBoardLossItem"))
			{
				outputBoardLossItem = (String^)tf_TestParameter_ConditionCast(testParameterName, "OutputBoardLossItem");

				if (tl->glob->boardLoss[testSite]->ContainsKey(outputBoardLossItem))
				{
					outputBoardLoss = tl->glob->boardLoss[testSite][outputBoardLossItem];
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "OutputBoardLossItem: " + outputBoardLossItem + "] is not exist in the BoardLoss.csv";
					throw gcnew Exception(ErrorMessage);
				}
			}
			for (int i = 0; i < currentMeasurementCount; i++)
			{
				if ((bool)testConditionCollection->ContainsKey("CurrentMeasurementPin_" + i.ToString()))
				{
					currentMeasurementPin[i] = (String^)tf_TestParameter_ConditionCast(testParameterName, "CurrentMeasurementPin_" + i.ToString());
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "CurrentMeasurementPin_" + i.ToString() + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

				if ((bool)testConditionCollection->ContainsKey("CurrentMeasurementDelay_" + i.ToString()))
				{
					currentMeasurementDelay[i] = (int)tf_TestParameter_ConditionCast(testParameterName, "CurrentMeasurementDelay_" + i.ToString());
				}
				else
				{
					currentMeasurementDelay[i] = 0.0;
				}
			}

			for (int i = 0; i < voltageMeasurementCount; i++)
			{
				if ((bool)testConditionCollection->ContainsKey("VoltageMeasurementPin_" + i.ToString()))
				{
					voltageMeasurementPin[i] = (String^)tf_TestParameter_ConditionCast(testParameterName, "VoltageMeasurementPin_" + i);
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "VoltageMeasurementPin_" + i.ToString() + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

				if ((bool)testConditionCollection->ContainsKey("VoltageMeasurementDelay_" + i.ToString()))
				{
					voltageMeasurementDelay[i] = (int)tf_TestParameter_ConditionCast(testParameterName, "VoltageMeasurementDelay_" + i.ToString());
				}
				else
				{
					voltageMeasurementDelay[i] = 0.0;
				}
			}
			if ((bool)testConditionCollection->ContainsKey("OutputExtAtt"))
			{
				outputExtAtt = (double)tf_TestParameter_ConditionCast(testParameterName, "OutputExtAtt");
			}
#pragma endregion "Test Condition Casting"

#pragma region "Result Variable"

			//Result Variable
			int ResultTotal = 4; //Not include currentMeasurementCount & voltageMeasurementCount
			int ResultCount = 0;
			ResultTotal = ResultTotal + currentMeasurementCount + voltageMeasurementCount;
			array<double >^ currentMeasurementResult = gcnew array<double>(currentMeasurementCount);
			array<double >^ voltageMeasurementResult = gcnew array<double>(voltageMeasurementCount);
			array<double>^ ResultArr = gcnew array<double >(ResultTotal);
			array<String^>^ UserDesiredResult = nullptr;
			Dictionary<String ^, double> ^ Result = gcnew Dictionary<String^, double>();

			for (int i = 0; i<ResultTotal; i++)
			{
				ResultArr[i] = 0.0;
			}

#pragma endregion "Result Variable"

#pragma region "Test"
			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get Path Loss <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			if (measureMode == "Bypass")
				getRxPathLoss(testSite, wolferType, measureFreq, tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus, tl->glob->g_txpath[wolferType], tl->glob->g_SelectRxPath[wolferType], pathloss, "Bypass");
			else if (measureMode == "Har")
				getRxHarPathLoss(testSite, wolferType, measureFreq, tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus, tl->glob->g_SelectRxPath[wolferType], pathloss, "Har");

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(measureChannel)[0];

			if ((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["TestSite_LoadHardwareProfile"] != testSite)
			{
				RF_LoadHardwareProfile(testSite);
				tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["TestSite_LoadHardwareProfile"] = testSite;
			}

			if (((String ^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] != HardwareRsrc->Alias) ||
				((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] != measurePower) ||
				((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] != measureFreq) ||
				((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] != filterOption) ||
				((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] != 0))// true if channel, measurePower, measureFreq & filterOption is not same as previous
			{
				if (!measureIQ)
				{
					RF_MeasureSetup(testSite, measureChannel, measurePower, measureFreq, filterOption);
				}
				else
				{
					RF_MeasureSetupIQ(testSite, measureChannel, measurePower, measureFreq, sampleRate, sampleSize, filterOption);
				}
			}

			if (!measureIQ)
			{
				RF_MeasureChannel(testSite, measureChannel, measureDelay, Pout);
			}
			else
			{
				RF_MeasureChannelIQ(testSite, measureChannel, measureDelay, Pout);
			}

			//State Recording
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] = HardwareRsrc->Alias;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] = measurePower;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] = measureFreq;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] = filterOption;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFactor"] = 999.99;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] = 0;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleRate"] = 999.99;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleSize"] = 999;


			//Current Measurement
			for (int i = 0; i < currentMeasurementCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(currentMeasurementPin[i])[0];

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					module400series->DM_MeasureCurrent(testSite, currentMeasurementPin[i], currentMeasurementDelay[i], currentMeasurementResult[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					module400series->SMU_MeasureCurrent(testSite, currentMeasurementPin[i], currentMeasurementDelay[i], currentMeasurementResult[i]);
				}
			}

			//Voltage Measurement
			for (int i = 0; i < voltageMeasurementCount; i++)
			{

				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(voltageMeasurementPin[i])[0];

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					module400series->DM_MeasureVoltage(testSite, voltageMeasurementPin[i], voltageMeasurementDelay[i], voltageMeasurementResult[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					module400series->SMU_MeasureVoltage(testSite, voltageMeasurementPin[i], voltageMeasurementDelay[i], voltageMeasurementResult[i]);
				}
			}

			//Storing Result into Array
			ResultArr[ResultCount] = tl->glob->SourcePower_Status[testSite].SourcePowerPreStatus; //Pin
			ResultArr[++ResultCount] = Pout + outputBoardLoss + outputExtAtt + pathloss; //Pout
			ResultArr[++ResultCount] = ResultArr[1] - ResultArr[0]; //Gain
			ResultArr[++ResultCount] = tl->glob->WolferCoupler_Pout[testSite]; //Coupler Pout

			for (int i = 0; i < currentMeasurementCount; i++)
			{
				ResultArr[++ResultCount] = currentMeasurementResult[i];
			}
			for (int i = 0; i < voltageMeasurementCount; i++)
			{
				ResultArr[++ResultCount] = voltageMeasurementResult[i];
			}

			//Storing Array Result into Dictionary
			Result->Clear();
			ResultCount = 0;
			Result->Add("Source", ResultArr[ResultCount]);
			Result->Add("Measure", ResultArr[++ResultCount]);
			Result->Add("Gain", ResultArr[++ResultCount]);
			Result->Add("Coupler", ResultArr[++ResultCount]);
			for (int i = 0; i < currentMeasurementCount; i++)
			{
				ModeMeasurement = "Current_";
				Result->Add(ModeMeasurement + currentMeasurementPin[i], ResultArr[++ResultCount]);
			}
			for (int i = 0; i < voltageMeasurementCount; i++)
			{
				ModeMeasurement = "Voltage_";
				Result->Add(ModeMeasurement + voltageMeasurementPin[i], ResultArr[++ResultCount]);
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			RF_TestMethod_ResultDisplayChecking(site, testSite, tl->glob->TestProperty[testSite].TotalTestParameter, ResultTotal, testParameterNumber, UserDesiredResult);

			//Result Storing
			if (ResultTotal > 1 && (UserDesiredResult->Length != 0))
			{
				for (int i = 0; i<UserDesiredResult->Length; i++)
				{
					tl->glob->TestResults[testSite][testParameterNumber + i] = Result[UserDesiredResult[i]];
				}
			}
			else
			{
				tl->glob->TestResults[testSite][testParameterNumber + 0] = Result["Measure"];
			}

			if (UserDesiredResult->Length != 0)
			{
				testParameterCount = UserDesiredResult->Length;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method RFCase_MeasureChannel");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);

		}
		finally
		{}
	}

}