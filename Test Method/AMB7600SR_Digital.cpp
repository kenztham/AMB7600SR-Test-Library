#include "..\\TestProgram.h"

namespace Functions
{
	//DM-Control Methods
	void AMB7600SRTestLibrary::CM_DMInit(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DMInit
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMInit");

			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			//Compulsory Variable
			int DpinGroupSelection = 3;//Default

			//Operation Variable
			int techFlowSite = tl->glob->tf.TestSite;
			bool existDMInit = false;
			String ^ DpinGroupInfo = "DPinGroupSel_Site_" + techFlowSite.ToString() + "_UUTOffset_" + testSite.ToString();
			String ^ ErrorMessage = String::Empty;
			String ^ CM = "DMInit_";


#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey(DpinGroupInfo))
			{
				ConditionInfo = testConditionCollection[DpinGroupInfo][site];
				DpinGroupSelection = (int)ConditionInfo->Value;

				if (DpinGroupSelection == 0 || DpinGroupSelection >= 4)
				{
					ErrorMessage = "Test Condition [" + DpinGroupInfo + " value " + DpinGroupSelection.ToString() + "] is not supported as the value can only be 1, 2 or 3.";
					throw gcnew Exception(ErrorMessage);
				}

				existDMInit = true;
			}
			else
			{
				existDMInit = false;
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			DM_Init(testSite, DpinGroupSelection);

#pragma endregion "Test"

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMInit");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_WriteVector(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		{
			/*****************************************************************************************************
			** CM_WriteVector
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
				tl->WriteToLogger(testSite, "Executing Control Method DMCase_WriteVector");

				//Control Method Compulsory Variable
				String^ vectorFileName = nullptr;
				String^ moduleAlias = nullptr;

				//Operation Variable
				String ^ ErrorMessage = nullptr;
				String ^ CM = "WriteVector_";

#pragma region "Test Condition Casting"
				ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

				//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
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
				//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<


#pragma endregion "Test Condition Casting"

#pragma region "Test"

				DM_MIPIWriteVector(testSite, moduleAlias, vectorFileName);

				tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_WriteVector");

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
	}
	void AMB7600SRTestLibrary::CM_DMConfigureInputTriggerSelect(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DMConfigureInputTriggerSelect
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMConfigureInputTriggerSelect");
			//Control Method Compulsory Variable
			int trigOutput0 = 0;
			int trigOutput1 = 0;
			String^ moduleAlias = nullptr;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMConfigureInputTriggerSelect";

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

			if ((bool)testConditionCollection->ContainsKey("TriggerInput"))
			{
				ConditionInfo = testConditionCollection["TriggerInput"][site];
				trigOutput0 = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TriggerInput" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("TriggerDelay"))
			{
				ConditionInfo = testConditionCollection["TriggerDelay"][site];
				trigOutput1 = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TriggerDelay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//tl->CheckError(testSite, cm[testSite]->MapTriggerInToTriggerOut("CM400e", CM_CONST_TRIGGER_TRISTATE, 1));

			DM_ConfigureInputTriggerSelect(testSite, moduleAlias, trigOutput0, trigOutput1);
			//tl->CheckError(testSite, cm[testSite]->MapTriggerInToTriggerOut("CM400e", 1, 23));

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMConfigureInputTriggerSelect");


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
	void AMB7600SRTestLibrary::CM_DMConfigureOutputTriggerSelect(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DMConfigureOutputTriggerSelect
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMConfigureOutputTriggerSelect");
			//Control Method Compulsory Variable
			int trigOutput0 = 0;
			int trigOutput1 = 0;
			String^ moduleAlias = nullptr;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMConfigureOutputTriggerSelect_";

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

			if ((bool)testConditionCollection->ContainsKey("TriggerOutput0"))
			{
				ConditionInfo = testConditionCollection["TriggerOutput0"][site];
				trigOutput0 = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TriggerOutput0" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("TriggerOutput1"))
			{
				ConditionInfo = testConditionCollection["TriggerOutput1"][site];
				trigOutput1 = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TriggerOutput1" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			//tl->CheckError(testSite, cm[testSite]->MapTriggerInToTriggerOut("CM400e", CM_CONST_TRIGGER_TRISTATE, 1));

			DM_ConfigureOutputTriggerSelect(testSite, moduleAlias, trigOutput0, trigOutput1);
			//tl->CheckError(testSite, cm[testSite]->MapTriggerInToTriggerOut("CM400e", 1, 23));

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMConfigureOutputTriggerSelect");


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
	void AMB7600SRTestLibrary::CM_DMConfigureReadPin_TriggerOutput(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_MIPIWriteVector
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMConfigureReadPin_TriggerOutput");

			//Control Method Compulsory Variable
			String ^ pinAlias = nullptr;
			int pinStatusSelect = 0;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMConfigureReadPin_TriggerOutput_";

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("PinAlias"))
			{
				ConditionInfo = testConditionCollection["PinAlias"][site];
				pinAlias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PinAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("PinStatusSelect"))
			{
				ConditionInfo = testConditionCollection["PinStatusSelect"][site];
				pinStatusSelect = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PinStatusSelect" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			DM_ConfigureReadPin_TriggerOutput(testSite, pinAlias, pinStatusSelect);

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMConfigureReadPin_TriggerOutput");

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
	void AMB7600SRTestLibrary::CM_DMConfigurePinToPMU(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DriveVoltage
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMConfigurePinToPMU");

			//Control Method Compulsory Variable
			array<String ^>^ pinAlias = nullptr;
			array<int>^ measureMode = nullptr;
			array<int>^ senseMode = nullptr;
			array<double>^ compliance = nullptr;
			array<double>^ nplc = nullptr;
			array<double>^ driveValue = nullptr;

			//Operation Variable
			int Count = 0;
			int PMUPinset = 0;
			int TotalPMUCondition = 6;
			bool StatusPass = true;
			array<String^>^ PMUCondition = gcnew array<String^>(TotalPMUCondition);
			array<bool>^ PMUConditionExist = gcnew array<bool>(TotalPMUCondition);
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMConfigurePinToPMU_";

			PMUCondition[0] = "PinAlias";
			PMUCondition[1] = "MeasureMode";
			PMUCondition[2] = "SenseMode";
			PMUCondition[3] = "Compliance";
			PMUCondition[4] = "DriveValue";
			PMUCondition[5] = "Nplc";



#pragma region "Control Condition Casting"	

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();
				
			//Get the number of PMUPinset
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;

				for (int i = 0; i < TotalPMUCondition; i++)
				{
					PMUConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i = 0; i < TotalPMUCondition; i++)
					{
						if (PMUPinset == 0)
						{
							if (controlCondition->Name == (PMUCondition[i]))
							{
								PMUConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (PMUCondition[i] + "_" + PMUPinset.ToString()))
							{
								PMUConditionExist[i] = true;
								Count++;
								break;
							}
						}
					}

					if (Count == TotalPMUCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (PMUPinset == 0)
				{
					for (int i = 0; i < TotalPMUCondition; i++)
					{
						if (PMUConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition [" + CM + PMUCondition[i] + "_" + PMUPinset.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}
				else
				{
					if (Count != 0)
					{
						for (int i = 0; i < TotalPMUCondition; i++)
						{
							if (PMUConditionExist[i] == false)
							{
								ErrorMessage = "Test Condition [" + CM + PMUCondition[i] + "_" + PMUPinset.ToString() + "] is not found.";
								throw gcnew Exception(ErrorMessage);
							}
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalPMUCondition)
				{
					StatusPass = false;
				}
				else
				{
					PMUPinset++;
					StatusPass = true;
				}
			}

			pinAlias = gcnew array<String^>(PMUPinset);;
			measureMode = gcnew array<int>(PMUPinset);;
			senseMode = gcnew array<int>(PMUPinset);;
			compliance = gcnew array<double>(PMUPinset);;
			nplc = gcnew array<double>(PMUPinset);;
			driveValue = gcnew array<double>(PMUPinset);;

			//Cast Value 
			for (int i = 0; i < PMUPinset; i++)
			{
				Count = 0;

				if (i == 0)
				{
					ConditionInfo = testConditionCollection[PMUCondition[Count++]][site];
					pinAlias[i] = (String^)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++]][site];
					measureMode[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++]][site];
					senseMode[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++]][site];
					compliance[i] = (double)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++]][site];
					driveValue[i] = (double)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++]][site];
					nplc[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ConditionInfo = testConditionCollection[PMUCondition[Count++] + "_" + i.ToString()][site];
					pinAlias[i] = (String^)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++] + "_" + i.ToString()][site];
					measureMode[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++] + "_" + i.ToString()][site];
					senseMode[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++] + "_" + i.ToString()][site];
					compliance[i] = (double)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++] + "_" + i.ToString()][site];
					driveValue[i] = (double)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[PMUCondition[Count++] + "_" + i.ToString()][site];
					nplc[i] = (double)ConditionInfo->Value;
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			for (int i = 0; i < PMUPinset; i++)
			{
				DM_ConfigureDigitalPinToPMU(testSite, pinAlias[i], measureMode[i], senseMode[i], compliance[i], driveValue[i], nplc[i]);
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMConfigurePinToPMU");

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
	void AMB7600SRTestLibrary::CM_DMConfigurePinToVector(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DriveVoltage
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMConfigurePinToVector");

			//Control Method Compulsory Variable
			array<String ^>^ pinAlias = nullptr;
			array<int>^ dPinLevelSet = nullptr;
			array<int>^ pEAttSet = nullptr;

			//Operation Variable
			int Count = 0;
			int VectorPinset = 0;
			int TotalVectorCondition = 3;
			bool StatusPass = true;
			array<String^>^ VectorCondition = gcnew array<String^>(TotalVectorCondition);
			array<bool>^ VectorConditionExist = gcnew array<bool>(TotalVectorCondition);
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMConfigurePinToVector_";

			VectorCondition[0] = "PinAlias";
			VectorCondition[1] = "DPinLevelSet";
			VectorCondition[2] = "PEAttSet";

#pragma region "Control Condition Casting"	

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//Get the number of PMUPinset
			while (StatusPass)
			{
				//Reset the variable
				Count = 0;
				for (int i = 0; i < TotalVectorCondition; i++)
				{
					VectorConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i=0;i<TotalVectorCondition;i++)
					{
						if (VectorPinset == 0)
						{
							if (controlCondition->Name == (VectorCondition[i]))
							{
								VectorConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (VectorCondition[i] + "_" + VectorPinset.ToString()))
							{
								VectorConditionExist[i] = true;
								Count++;
								break;
							}
						}

					}

					if (Count == TotalVectorCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (VectorPinset == 0)
				{
					for (int i = 0; i < TotalVectorCondition; i++)
					{
						if (VectorConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition [" + CM + VectorCondition[i] + "_" + VectorPinset.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}
				else
				{
					if (Count != 0)
					{
						for (int i = 0; i < TotalVectorCondition; i++)
						{
							if (VectorConditionExist[i] == false)
							{
								ErrorMessage = "Test Condition [" + CM + VectorCondition[i] + "_" + VectorPinset.ToString() + "] is not found.";
								throw gcnew Exception(ErrorMessage);
							}
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalVectorCondition)
				{
					StatusPass = false;
				}
				else
				{
					VectorPinset++;
					StatusPass = true;
				}
			}


			pinAlias = gcnew array<String^>(VectorPinset);
			dPinLevelSet = gcnew array<int>(VectorPinset);
			pEAttSet = gcnew array<int>(VectorPinset);

			//Cast Value 
			for (int i = 0; i < VectorPinset; i++)
			{
				Count = 0;
				if (i == 0)
				{
					ConditionInfo = testConditionCollection[VectorCondition[Count++]][site];
					pinAlias[i] = (String^)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[VectorCondition[Count++]][site];
					dPinLevelSet[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[VectorCondition[Count++]][site];
					pEAttSet[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ConditionInfo = testConditionCollection[VectorCondition[Count++] + "_" + i.ToString()][site];
					pinAlias[i] = (String^)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[VectorCondition[Count++] + "_" + i.ToString()][site];
					dPinLevelSet[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[VectorCondition[Count++] + "_" + i.ToString()][site];
					pEAttSet[i] = (int)ConditionInfo->Value;
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			for (int i = 0; i < VectorPinset; i++)
			{
				DM_ConfigureDigitalPinToVector(testSite, pinAlias[i], dPinLevelSet[i], pEAttSet[i]);
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMConfigurePinToVector");

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
	void AMB7600SRTestLibrary::CM_DMConfigurePinToDIO(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DriveVoltage
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMConfigurePinToDIO");
			//Control Method Compulsory Variable
			//Operation Variable

			//Control Method Compulsory Variable
			array<String ^>^ pinAlias = nullptr;
			array<int>^ dPinLevelSet = nullptr;
			array<int>^ pinDirection = nullptr;


			//Operation Variable
			int Count = 0;
			int DIOPinset = 0;
			int TotalDIOCondition = 3;
			bool StatusPass = true;
			array<String^>^ DIOCondition = gcnew array<String^>(TotalDIOCondition);
			array<bool>^ DIOConditionExist = gcnew array<bool>(TotalDIOCondition);
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMConfigurePinToDIO_";

			DIOCondition[0] = "PinAlias";
			DIOCondition[1] = "DPinLevelSet";
			DIOCondition[2] = "PinDirection";

#pragma region "Control Condition Casting"	

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//Get the number of DIOPinset
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalDIOCondition; i++)
				{
					DIOConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i = 0; i < TotalDIOCondition; i++)
					{
						if (DIOPinset == 0)
						{
							if (controlCondition->Name == (DIOCondition[i]))
							{
								DIOConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (DIOCondition[i] + "_" + DIOPinset.ToString()))
							{
								DIOConditionExist[i] = true;
								Count++;
								break;
							}
						}
					}

					if (Count == TotalDIOCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (DIOPinset == 0)
				{
					for (int i = 0; i < TotalDIOCondition; i++)
					{
						if (DIOConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition [" + CM + DIOCondition[i] + "_" + DIOPinset.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}
				else
				{
					if (Count != 0)
					{
						for (int i = 0; i < TotalDIOCondition; i++)
						{
							if (DIOConditionExist[i] == false)
							{
								ErrorMessage = "Test Condition [" + CM + DIOCondition[i] + "_" + DIOPinset.ToString() + "] is not found.";
								throw gcnew Exception(ErrorMessage);
							}
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalDIOCondition)
				{
					StatusPass = false;
				}
				else
				{
					DIOPinset++;
					StatusPass = true;
				}
			}

			pinAlias = gcnew array<String^>(DIOPinset);
			dPinLevelSet = gcnew array<int>(DIOPinset);
			pinDirection = gcnew array<int>(DIOPinset);

			//Cast Value 
			for (int i = 0; i < DIOPinset; i++)
			{
				Count = 0;

				if (i == 0)
				{
					ConditionInfo = testConditionCollection[DIOCondition[Count++]][site];
					pinAlias[i] = (String^)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[DIOCondition[Count++]][site];
					dPinLevelSet[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[DIOCondition[Count++]][site];
					pinDirection[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ConditionInfo = testConditionCollection[DIOCondition[Count++] + "_" + i.ToString()][site];
					pinAlias[i] = (String^)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[DIOCondition[Count++] + "_" + i.ToString()][site];
					dPinLevelSet[i] = (int)ConditionInfo->Value;

					ConditionInfo = testConditionCollection[DIOCondition[Count++] + "_" + i.ToString()][site];
					pinDirection[i] = (int)ConditionInfo->Value;
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			for (int i = 0; i < DIOPinset; i++)
			{
				DM_ConfigureDigitalPinToDIO(testSite, pinAlias[i], dPinLevelSet[i], pinDirection[i]);
			
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMConfigurePinToDIO");

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
	void AMB7600SRTestLibrary::CM_DMDioModeDrivePin(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMDioModeDrivePin");
			//Control Method Compulsory Variable
			array<String^> ^ pinAlias = nullptr;
			array<int> ^ pinState = nullptr;

			//Operation Variable
			int PinCount = 0;
			int Count = 0;
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMDioModeDrivePin_";

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;
			}
		
			pinAlias = gcnew array<String^>(PinCount);
			pinState = gcnew array<int>(PinCount);

			for (int i = 0; i < PinCount; i++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pinAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pinAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("Logic"))
				{
					ConditionInfo = testConditionCollection["Logic"][site];
					pinState[i] = (double)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("Logic_" + i))
				{
					ConditionInfo = testConditionCollection["Logic_" + i][site];
					pinState[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pinAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

				DM_DioModeDrivePin(testSite, pinAlias[i], pinState[i]);
			}
#pragma endregion "Control Condition Casting"

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMDioModeDrivePin");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_DMCastDPinLevel(Site ^ site, int testSite, ConditionCollection^testConditionCollection)
	{
		try
		{
			tl->WriteToLogger(testSite, "Executing Control Method DMCastDPinLevelCondition");

			//Control Method Compulsory Variable

			//Operation Variable
			int Count = 0;
			int DPinset = 0;
			int TotalDPinCondition = 9;
			bool StatusPass = true;
			array<String^>^ DPinCondition = gcnew array<String^>(TotalDPinCondition);
			array<bool>^ DPinConditionExist = gcnew array<bool>(TotalDPinCondition);
			array<Dictionary<String^, double>^>^ DPinConditionVal;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMCastDPinLevel_";

			DPinCondition[0] = "VIH";
			DPinCondition[1] = "VIL";
			DPinCondition[2] = "VOH";
			DPinCondition[3] = "VOL";
			DPinCondition[4] = "IOH";
			DPinCondition[5] = "IOL";
			DPinCondition[6] = "VCH";
			DPinCondition[7] = "VCL";
			DPinCondition[8] = "VTERM";

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//Get the number of DPin Set
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalDPinCondition; i++)
				{
					DPinConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i = 0; i < TotalDPinCondition; i++)
					{
						if (DPinset == 0)
						{ 
							if (controlCondition->Name == (DPinCondition[i]))
							{
								DPinConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (DPinCondition[i] + "_" + DPinset.ToString()))
							{
								DPinConditionExist[i] = true;
								Count++;
								break;
							}
						}
					}

					if (Count == TotalDPinCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (Count != 0)
				{
					for (int i = 0; i < TotalDPinCondition; i++)
					{
						if (DPinConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition [" + CM + DPinCondition[i] + "_" + DPinset.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalDPinCondition)
				{
					StatusPass = false;
				}
				else
				{
					DPinset++;
					StatusPass = true;
				}
			}

			//Initialize the the Dictionary variable
			DPinConditionVal = gcnew array<Dictionary<String^, double>^>(DPinset);
			for (int i = 0; i < DPinset; i++)
			{
				DPinConditionVal[i] = gcnew Dictionary<String^, double>();
			}

			//Cast Value and key to the Dictionary
			for (int i = 0; i < DPinset; i++)
			{
				for (int j = 0; j < TotalDPinCondition; j++)
				{
					if (i == 0)
					{
						DPinConditionVal[i]->Add(DPinCondition[j], 999);
						ConditionInfo = testConditionCollection[DPinCondition[j]][site];
						DPinConditionVal[i][DPinCondition[j]] = (double)ConditionInfo->Value;
						//DPinConditionVal[i][DPinCondition[j]] = (double)tf_ControlItem_ConditionCast(CM + DPinCondition[j] + "_" + i.ToString());
					}
					else
					{
						DPinConditionVal[i]->Add(DPinCondition[j], 999);
						ConditionInfo = testConditionCollection[DPinCondition[j] + "_" + i.ToString()][site];
						DPinConditionVal[i][DPinCondition[j]] = (double)ConditionInfo->Value;
						//DPinConditionVal[i][DPinCondition[j]] = (double)tf_ControlItem_ConditionCast(CM + DPinCondition[j] + "_" + i.ToString());
					}
				}

				tl->glob->DPinLevelSet[testSite]->Add(DPinConditionVal[i]);
			}

#pragma endregion "Control Condition Casting"

			tl->WriteToLogger(testSite, "Done Executing Control Method CM_DMCastDPinLevelCondition");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_DMCastTimingSetPeriod(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMCastTimingSetPeriod");
			//Control Method Compulsory Variable

			//Operation Variable
			int count = 0;
			int timingset = 0;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMCastTimingSet_";


#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			for each(Condition ^ controlCondition in testConditionCollection)
			{
				if (controlCondition->Name->Contains("TimingSetPeriod"))
				{
					count++;
				}
			}

			tl->glob->TimingSetPeriod[testSite] = gcnew array<double>(count);
			count = 0;

			for each(Condition ^ controlCondition in testConditionCollection)
			{
				if (count == 0 && controlCondition->Name->Contains("TimingSetPeriod"))
				{
					ConditionInfo = testConditionCollection[controlCondition->Name][site];
					tl->glob->TimingSetPeriod[testSite][count] = (double)ConditionInfo->Value;
					//tl->glob->TimingSetPeriod[siteIndex][count] = (double)tf_ControlItem_ConditionCast(controlCondition->Name);
					count++;
				}
				if (count != 0 && controlCondition->Name->Contains("TimingSetPeriod_" + count.ToString()))
				{
					ConditionInfo = testConditionCollection[controlCondition->Name][site];
					tl->glob->TimingSetPeriod[testSite][count] = (double)ConditionInfo->Value;
					//tl->glob->TimingSetPeriod[siteIndex][count] = (double)tf_ControlItem_ConditionCast(controlCondition->Name);
					count++;
				}
				else
				{
					ConditionInfo = testConditionCollection[controlCondition->Name][site];
					ErrorMessage = "Test Condition[" + controlCondition->Name + "] is not valid";
					throw gcnew Exception(ErrorMessage);
				}
			}

			if (tl->glob->TimingSetPeriod[testSite]->Length == 0)
			{
				ErrorMessage = "Test Condition["+ CM +"TimingSetPeriod ] is not found";
				throw gcnew Exception(ErrorMessage);
			}
#pragma endregion "Control Condition Casting"

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMCastTimingSetPeriod");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_DMCastPEAttribute(Site ^ site, int testSite, ConditionCollection^testConditionCollection)
	{
		try
		{
			tl->WriteToLogger(testSite, "Executing Control Method DMCastPEAttribute");

			//Control Method Compulsory Variable

			//Operation Variable
			int Count = 0;
			int PEAttset = 0;
			int TotalPEAttCondition = 4;
			bool StatusPass = true;
			array<String^>^ PEAttCondition = gcnew array<String^>(TotalPEAttCondition);
			array<bool>^ PEAttConditionExist = gcnew array<bool>(TotalPEAttCondition);
			array<Dictionary<String^, bool>^>^ PEAttConditionVal;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMCastPEAttribute_";

			PEAttCondition[0] = "InputTermEnable";
			PEAttCondition[1] = "HVEnable";
			PEAttCondition[2] = "ActiveLoadEnable";
			PEAttCondition[3] = "DifferentialComparatorEnable";

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//Get the number of PEAttset Set
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalPEAttCondition; i++)
				{
					PEAttConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i = 0; i < TotalPEAttCondition; i++)
					{
						if (PEAttset == 0)
						{
							if (controlCondition->Name == (PEAttCondition[i]))
							{
								PEAttConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (PEAttCondition[i] + "_" + PEAttset.ToString()))
							{
								PEAttConditionExist[i] = true;
								Count++;
								break;
							}
						}
					}
					if (Count == TotalPEAttCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (PEAttset == 0)
				{
					for (int i = 0; i < TotalPEAttCondition; i++)
					{
						if (PEAttConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition ["+CM + PEAttCondition[i] + "_" + PEAttset.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}
				else
				{
					if (Count != 0)
					{
						for (int i = 0; i < TotalPEAttCondition; i++)
						{
							if (PEAttConditionExist[i] == false)
							{
								ErrorMessage = "Test Condition ["+CM + PEAttCondition[i] + "_" + PEAttset.ToString() + "] is not found.";
								throw gcnew Exception(ErrorMessage);
							}
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalPEAttCondition)
				{
					StatusPass = false;
				}
				else
				{
					PEAttset++;
					StatusPass = true;
				}
			}

			//Initialize the the Dictionary variable
			PEAttConditionVal = gcnew array<Dictionary<String^, bool>^>(PEAttset);

			for (int i = 0; i < PEAttset; i++)
			{
				PEAttConditionVal[i] = gcnew Dictionary<String^, bool>();
			}

			//Cast Value 
			for (int i = 0; i < PEAttset; i++)
			{
				for (int j = 0; j < TotalPEAttCondition; j++)
				{
					if (i == 0)
					{
						PEAttConditionVal[i]->Add(PEAttCondition[j], 999);
						ConditionInfo = testConditionCollection[PEAttCondition[j]][site];
						PEAttConditionVal[i][PEAttCondition[j]] = (bool)ConditionInfo->Value;
						//PEAttConditionVal[i][PEAttCondition[j]] = (bool)tf_ControlItem_ConditionCast(PEAttCondition[j] + "_" + i.ToString());
					}
					else
					{
						PEAttConditionVal[i]->Add(PEAttCondition[j], 999);
						ConditionInfo = testConditionCollection[PEAttCondition[j] + "_" + i.ToString()][site];
						PEAttConditionVal[i][PEAttCondition[j]] = (bool)ConditionInfo->Value;
						//PEAttConditionVal[i][PEAttCondition[j]] = (bool)tf_ControlItem_ConditionCast(PEAttCondition[j] + "_" + i.ToString());
					}
				}
				tl->glob->PEAttributeSet[testSite]->Add(PEAttConditionVal[i]);
			}
#pragma endregion "Control Condition Casting"

			tl->WriteToLogger(testSite, "Done Executing Control Method CM_DMCastDPinLevelCondition");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_DMLoadVectorFile(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method DMCase_DMLoadVectorFile");

			//Control Method Compulsory Variable
			array<String^> ^ moduleAlias = nullptr;

			//Operation Variable
			int ModuleCount = 0;
			int Count = 0;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DMLoadVectorFile_";

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ controlCondition in testConditionCollection)
			{
				if (controlCondition->Name->StartsWith(CM + "ModuleAlias_" + ModuleCount.ToString()))
				{
					ModuleCount++;
				}
			}

			moduleAlias = gcnew array<String^>(ModuleCount);
			
			for each(Condition ^ controlCondition in testConditionCollection)
			{
				if (controlCondition->Name->StartsWith(CM + "ModuleAlias_" + Count.ToString()))
				{
					ConditionInfo = testConditionCollection[controlCondition->Name][site];
					moduleAlias[Count] = (String^)ConditionInfo->Value;
					Count++;
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			if (ModuleCount > 0)
			{
				GetVectorFiles(site);
				VectorFilesInfo(site, testSite);

				for (int i = 0; i < ModuleCount; i++)
				{
					DMLoadVectorFiles(site, testSite, moduleAlias[i]);
				}
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method DMCase_DMLoadVectorFile");

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

	//IOM-Control Methods
	void AMB7600SRTestLibrary::CM_DIODrivePin(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method IOMCase_DIODrivePin");
			//Control Method Compulsory Variable
			array<String^> ^ pinAlias = nullptr;
			array<int> ^ dioPinState = nullptr;

			//Operation Variable
			int PinCount = 0;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DIODrivePin_";
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			int Count = 0;

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();


			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
				{
					PinCount++;
				}
			}

			pinAlias = gcnew array<String^>(PinCount);
			dioPinState = gcnew array<int>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pinAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pinAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("PinLogic"))
				{
					ConditionInfo = testConditionCollection["PinLogic"][site];
					dioPinState[i] = (int)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("PinLogic_" + i))
				{
					ConditionInfo = testConditionCollection["PinLogic_" + i][site];
					dioPinState[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pinAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			for (int i = 0; i < PinCount; i++)
			{
				DIO_DrivePin(testSite, pinAlias[i], dioPinState[i]);
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method IOMCase_DIODrivePin");

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
	void AMB7600SRTestLibrary::CM_DIODrivePort(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method IOMCase_DIODrivePort");

			//Control Method Compulsory Variable
			array<String^> ^ portAlias = nullptr;
			array<int> ^ dioPortVal = nullptr;

			//Operation Variable
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DIODrivePort_";
			int PortCount = 0;
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			int Count = 0;

#pragma region "Control Condition Casting"	


			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PortAlias"))
				{
					PortCount++;
				}
			}

			portAlias = gcnew array<String^>(PortCount);
			dioPortVal = gcnew array<int>(PortCount);

			for (Count = 0; Count < PortCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PortAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						portAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PortAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						portAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PortCount; i++)
			{
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("PortLogic"))
				{
					ConditionInfo = testConditionCollection["PortLogic"][site];
					dioPortVal[i] = (int)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("PortLogic_" + i))
				{
					ConditionInfo = testConditionCollection["PortLogic_" + i][site];
					dioPortVal[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + portAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

			}
#pragma endregion "Control Condition Casting"
	
#pragma region "Test"

			for (int i = 0; i < PortCount; i++)
			{
				DIO_DrivePort(testSite, portAlias[i], dioPortVal[i]);
			}

#pragma endregion "Test"

			tl->WriteToLogger(testSite, "Done Executing Control Method IOMCase_DIODrivePort");
		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_DIOSetModuleVIO(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method IOMCase_DIOSetModuleVIO");

			//Control Method Compulsory Variable
			array<String^> ^ ModuleAlias = nullptr;
			array<int> ^ dioVioVal = nullptr;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			int ModuleCount = 0;
			int Count = 0;
			String ^ CM = "DIOSetModuleVIO_";
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("ModuleAlias"))
				{
					ModuleCount++;
				}
			}

			ModuleAlias = gcnew array<String^>(ModuleCount);
			dioVioVal = gcnew array<int>(ModuleCount);

			for (Count = 0; Count < ModuleCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "ModuleAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						ModuleAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "ModuleAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						ModuleAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < ModuleCount; i++)
			{
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("ModuleVioMode"))
				{
					ConditionInfo = testConditionCollection["ModuleVioMode"][site];
					dioVioVal[i] = (int)ConditionInfo->Value;

					if (dioVioVal[i] != 0 && dioVioVal[i] != 1)
					{
						ErrorMessage = "Test Condition [" + CM + ModuleAlias[i] + " value :" + dioVioVal[i].ToString() + "]is invalid as only 0 (OFF) or 1 (ON) is valid";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("ModuleVioMode_" + i))
				{
					ConditionInfo = testConditionCollection["ModuleVioMode_" + i][site];
					dioVioVal[i] = (int)ConditionInfo->Value;

					if (dioVioVal[i] != 0 && dioVioVal[i] != 1)
					{
						ErrorMessage = "Test Condition [" + CM + ModuleAlias[i] + " value :" + dioVioVal[i].ToString() + "]is invalid as only 0 (OFF) or 1 (ON) is valid";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + ModuleAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}
#pragma endregion "Control Condition Casting"

#pragma region "Test"

			for (int i = 0; i < ModuleCount; i++)
			{
				DIO_SetVIO(testSite, ModuleAlias[i], dioVioVal[i]);
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method IOMCase_DIOSetModuleVIO");

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
	void AMB7600SRTestLibrary::CM_DIOSetPortDirection(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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

			tl->WriteToLogger(testSite, "Executing Control Method IOMCase_DIOSetPortDirection");

			//Control Method Compulsory Variable
			array<String^> ^ portAlias = nullptr;
			array<int> ^ dioPortDirectionVal = nullptr;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ CM = "DIOSetPortDirection_";
			int PortCount = 0;
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			int Count = 0;

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PortAlias"))
				{
					PortCount++;
				}
			}

			portAlias = gcnew array<String^>(PortCount);
	        dioPortDirectionVal = gcnew array<int>(PortCount);

			for (Count = 0; Count < PortCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PortAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						portAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PortAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						portAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < Count; i++)
			{
				if (i == 0 && (bool)testConditionCollection->ContainsKey("PortDirection"))
				{
					ConditionInfo = testConditionCollection["PortDirection"][site];
					dioPortDirectionVal[i] = (int)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("PortDirection_" + i))
				{
					ConditionInfo = testConditionCollection["PortDirection_" + i][site];
					dioPortDirectionVal[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + portAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}
#pragma endregion "Control Condition Casting"

#pragma region "Test"

			for (int i = 0; i < Count; i++)
			{
				DIO_SetPortDirection(testSite, portAlias[i], dioPortDirectionVal[i]);
			}

#pragma endregion "Test"

			tl->WriteToLogger(testSite, "Done Executing Control Method IOMCase_DIOSetPortDirection");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}

	//CM-Control Methods
	void AMB7600SRTestLibrary::CM_CMDrivePin(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method CMCase_CMDrivePin");

			//Control Method Compulsory Variable
			array<String^>^ moduleAlias = nullptr;
			array<int>^ pin = nullptr;
			array<int>^ pinVal = nullptr;

			//Operation Variable
			int Count = 0;
			int DrivePinSet = 0;
			int TotalDrivePinCondition = 3;
			bool StatusPass = true;
			array<String^>^ DrivePinCondition = gcnew array<String^>(TotalDrivePinCondition);
			array<bool>^ DrivePinConditionExist = gcnew array<bool>(TotalDrivePinCondition);
			String ^ ErrorMessage = nullptr;
			String ^ CM = "CMDrivePin_";
			DrivePinCondition[0] = "ModuleAlias";
			DrivePinCondition[1] = "Pin";
			DrivePinCondition[2] = "PinVal";


#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//Get the number of PEAttset Set
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalDrivePinCondition; i++)
				{
					DrivePinConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i = 0; i < TotalDrivePinCondition; i++)
					{
						if (DrivePinSet == 0)
						{
							if (controlCondition->Name == (DrivePinCondition[i]))
							{
								DrivePinConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (DrivePinCondition[i] + "_" + DrivePinSet.ToString()))
							{
								DrivePinConditionExist[i] = true;
								Count++;
								break;
							}
						}
					}
					if (Count == TotalDrivePinCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (DrivePinSet == 0)
				{
					for (int i = 0; i < TotalDrivePinCondition; i++)
					{
						if (DrivePinConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition [" + CM + DrivePinCondition[i] + "_" + DrivePinSet.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}
				else
				{
					if (Count != 0)
					{
						for (int i = 0; i < TotalDrivePinCondition; i++)
						{
							if (DrivePinConditionExist[i] == false)
							{
								ErrorMessage = "Test Condition [" + CM + DrivePinCondition[i] + "_" + DrivePinSet.ToString() + "] is not found.";
								throw gcnew Exception(ErrorMessage);
							}
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalDrivePinCondition)
				{
					StatusPass = false;
				}
				else
				{
					DrivePinSet++;
					StatusPass = true;
				}
			}

			moduleAlias = gcnew array <String^>(DrivePinSet);
			pin = gcnew array <int>(DrivePinSet);
			pinVal = gcnew array <int>(DrivePinSet);

			//Cast Value 
			for (int i = 0; i < DrivePinSet; i++)
			{
				for (int j = 0; j < TotalDrivePinCondition; j++)
				{
					if (i == 0)
					{
						ConditionInfo = testConditionCollection[DrivePinCondition[j]][site];
					}
					else
					{
						ConditionInfo = testConditionCollection[DrivePinCondition[j] + "_" + i.ToString()][site];
					}

					switch (j)
					{
					case 0:
						moduleAlias[j] = (String^)ConditionInfo->Value;
						break;

					case 1:
						pin[j] = (int)ConditionInfo->Value;
						break;

					default:
						pinVal[j] = (int)ConditionInfo->Value;
						break;
					}
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			for (int i = 0; i < DrivePinSet; i++)
			{
				CM_DrivePin(testSite, moduleAlias[i], pin[i], pinVal[i]);
			}

			tl->WriteToLogger(testSite, "Done Executing Control Method CMCase_CMDrivePin");

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
	void AMB7600SRTestLibrary::CM_CMDrivePort(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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
			tl->WriteToLogger(testSite, "Executing Control Method CMCase_CMDrivePort");

			//Control Method Compulsory Variable
			array<String^> ^ moduleAlias = nullptr;
			array<int> ^ portVal = nullptr;

			//Operation Variable
			int ModuleAliasCount = 0;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "CMDrivePort_";
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			int Count = 0;

#pragma region "Control Condition Casting"	


			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("ModuleAlias"))
				{
					ModuleAliasCount++;
				}
			}

			moduleAlias = gcnew array<String^>(ModuleAliasCount);
			portVal = gcnew array<int>(ModuleAliasCount);

			for (Count = 0; Count < ModuleAliasCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "ModuleAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						moduleAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "ModuleAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						moduleAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < ModuleAliasCount; i++)
			{
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("PortLogic"))
				{
					ConditionInfo = testConditionCollection["PortLogic"][site];
					portVal[i] = (int)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("PortLogic_" + i))
				{
					ConditionInfo = testConditionCollection["PortLogic_" + i][site];
					portVal[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + moduleAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

#pragma region "Test"

			for (int i = 0; i < ModuleAliasCount; i++)
			{
				CM_DrivePort(testSite, moduleAlias[i], portVal[i]);
			}

#pragma endregion "Test"

			tl->WriteToLogger(testSite, "Done Executing Control Method CMCase_CMDrivePort");
		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_CMSetPortDirection(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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

			tl->WriteToLogger(testSite, "Executing Control Method CMCase_CMSetPortDirection");

			//Control Method Compulsory Variable
			array<String^> ^ moduleAlias = nullptr;
			array<int> ^ portDir = nullptr;

			//Operation Variable
			int ModuleAliasCount = 0;
			String ^ ErrorMessage = nullptr;
			String ^ CM = "CMSetPortDirection_";
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			int Count = 0;

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("ModuleAlias"))
				{
					ModuleAliasCount++;
				}
			}

			moduleAlias = gcnew array<String^>(ModuleAliasCount);
			portDir = gcnew array<int>(ModuleAliasCount);

			for (Count = 0; Count < ModuleAliasCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "ModuleAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						moduleAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "ModuleAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						moduleAlias[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < ModuleAliasCount; i++)
			{
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("PortDirection"))
				{
					ConditionInfo = testConditionCollection["PortDirection"][site];
					portDir[i] = (int)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("PortDirection_" + i))
				{
					ConditionInfo = testConditionCollection["PortDirection_" + i][site];
					portDir[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + moduleAlias[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			for (int i = 0; i < ModuleAliasCount; i++)
			{
				CM_SetPortDirection(testSite, moduleAlias[i], portDir[i]);
			}

#pragma endregion "Test"

			tl->WriteToLogger(testSite, "Done Executing Control Method CMCase_CMSetPortDirection");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void AMB7600SRTestLibrary::CM_CMConfigurePXES2780_TriggerBus(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DIODrivePin
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

			tl->WriteToLogger(testSite, "Executing Control Method CMCase_CMConfigurePXES2780_TriggerBus");

			//Control Method Compulsory Variable
			array<String^>^ moduleAlias = nullptr;
			array<String^>^ triggerBus = nullptr;
			array<int>^ triggerEnable= nullptr;
			array<int>^ triggerDirection = nullptr;

			//Operation Variable
			int Count = 0;
			int TriggerBusSet = 0;
			int TotalTriggerBusCondition = 4;
			bool StatusPass = true;
			array<String^>^ TriggerBusCondition = gcnew array<String^>(TotalTriggerBusCondition);
			array<bool>^ TriggerBusConditionExist = gcnew array<bool>(TotalTriggerBusCondition);
			String ^ ErrorMessage = nullptr;
			String ^ CM = "CMConfigurePXES2780_TriggerBus_";
			TriggerBusCondition[0] = "ModuleAlias";
			TriggerBusCondition[1] = "TriggerBus";
			TriggerBusCondition[2] = "TriggerEnable";
			TriggerBusCondition[3] = "TriggerDirection";

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			//Get the number of PEAttset Set
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalTriggerBusCondition; i++)
				{
					TriggerBusConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in testConditionCollection)
				{
					for (int i = 0; i < TotalTriggerBusCondition; i++)
					{
						if (TriggerBusSet == 0)
						{
							if (controlCondition->Name == (TriggerBusCondition[i]))
							{
								TriggerBusConditionExist[i] = true;
								Count++;
								break;
							}
						}
						else
						{
							if (controlCondition->Name == (TriggerBusCondition[i] + "_" + TriggerBusSet.ToString()))
							{
								TriggerBusConditionExist[i] = true;
								Count++;
								break;
							}
						}
					}
					if (Count == TotalTriggerBusCondition)
					{
						break;
					}
				}

				//Checking the availability of the test condition
				if (TriggerBusSet == 0)
				{
					for (int i = 0; i < TotalTriggerBusCondition; i++)
					{
						if (TriggerBusConditionExist[i] == false)
						{
							ErrorMessage = "Test Condition [" + CM + TriggerBusCondition[i] + "_" + TriggerBusSet.ToString() + "] is not found.";
							throw gcnew Exception(ErrorMessage);
						}
					}
				}
				else
				{
					if (Count != 0)
					{
						for (int i = 0; i < TotalTriggerBusCondition; i++)
						{
							if (TriggerBusConditionExist[i] == false)
							{
								ErrorMessage = "Test Condition [" + CM + TriggerBusCondition[i] + "_" + TriggerBusSet.ToString() + "] is not found.";
								throw gcnew Exception(ErrorMessage);
							}
						}
					}
				}

				//Get the StatusPass
				if (Count != TotalTriggerBusCondition)
				{
					StatusPass = false;
				}
				else
				{
					TriggerBusSet++;
					StatusPass = true;
				}
			}

			moduleAlias = gcnew array <String^>(TriggerBusSet);
			triggerBus = gcnew array <String^>(TriggerBusSet);
			triggerEnable = gcnew array <int>(TriggerBusSet);
			triggerDirection = gcnew array <int>(TriggerBusSet);

			//Cast Value 
			for (int i = 0; i < TriggerBusSet; i++)
			{
				for (int j = 0; j < TotalTriggerBusCondition; j++)
				{
					if (i == 0)
					{
						ConditionInfo = testConditionCollection[TriggerBusCondition[j]][site];
					}
					else
					{
						ConditionInfo = testConditionCollection[TriggerBusCondition[j] + "_" + i.ToString()][site];
					}
					switch (j)
					{
					case 0:
						moduleAlias[j] = (String^)ConditionInfo->Value;
						break;

					case 1:
						triggerBus[j] = (String^)ConditionInfo->Value;

						if (triggerBus[j] != "AB" || triggerBus[j] != "BC")
						{
							ErrorMessage = "Test Condition [" + CM + TriggerBusCondition[j] + "_" + i.ToString() + " value :" + triggerBus[j] + "] is invalid as only AB or BC is valid";
							throw gcnew Exception(ErrorMessage);
						}
						break;

					case 2:
						triggerEnable[j] = (int)ConditionInfo->Value;
						break;

					default:
						triggerDirection[j] = (int)ConditionInfo->Value;
						break;

					}
				}
			}

#pragma endregion "Control Condition Casting"

#pragma region "Test"

			for (int i = 0; i < TriggerBusSet; i++)
			{
				if (triggerBus[i] == "AB")
				{
					CM_ConfigurePXES2780_TriggerBusAB(testSite,moduleAlias[i], triggerEnable[i],triggerDirection[i]);
				}
				else
				{
					CM_ConfigurePXES2780_TriggerBusBC(testSite, moduleAlias[i], triggerEnable[i], triggerDirection[i]);
				}
			}

#pragma endregion "Test"

			tl->WriteToLogger(testSite, "Done Executing Control Method CMCase_CMConfigurePXES2780_TriggerBus");

		}

		catch (Exception ^ ex)
		{
			String ^ methodType = "CM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].ControlMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}

	//DM_Test Methods
	void AMB7600SRTestLibrary::TM_MIPIReadVector(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		/*****************************************************************************************************
		** TM_MIPIReadVector
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
			tl->WriteToLogger(testSite, "Executing Test Method DMCase_MIPIReadVector");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ vectorFileName = nullptr;
			String^ moduleAlias = nullptr;
			String^ dataPinAlias = nullptr;
			double channelInputDelay = 0;

			//Test Method Option Variable
			bool operationSweepChannelInputDelay = false;
			double startChannelInputDelay = 0;
			double stopChannelInputDelay = 0;
			double intervalChannelInputDelay = 0;

			//Operation Variable
			int Result = 0.0;
			int VectorFailCount = 999;
			int VectorFirstFail = 0.0;
			int DPinSet = 999;
			int PEAttSet = 999;
			String ^ StrToFileSweep = nullptr;
			String ^ FileSweepName = tl->glob->TestProperty[testSite].TestItemName + "_" + testParameterName + "_SweepChannelInputDelay_S" + tl->glob->tf.TestSite.ToString() + "UUT" + testSite.ToString() + ".csv";
			array<int>^ ReadHistoryRam_Data = gcnew array<int>(1);
			String ^ TM = "MIPIReadVector_";
			String^ ErrorMessage = nullptr;

#pragma region "Test Condition Casting"
			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("VectorFileName"))
			{
				vectorFileName = (String^)tf_TestParameter_ConditionCast(testParameterName, "VectorFileName");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "VectorFileName" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ModuleAlias"))
			{
				moduleAlias = (String^)tf_TestParameter_ConditionCast(testParameterName, "ModuleAlias");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "ModuleAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("DataPinAlias"))
			{
				dataPinAlias = (String^)tf_TestParameter_ConditionCast(testParameterName, "DataPinAlias");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "DataPinAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ChannelInputDelay"))
			{
				channelInputDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "ChannelInputDelay");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "ChannelInputDelay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if (tl->glob->AWV.Debug == 1)
			{
				if ((bool)testConditionCollection->ContainsKey("SweepOperation"))
				{
					operationSweepChannelInputDelay = (bool)tf_TestParameter_ConditionCast(testParameterName, "SweepOperation");
				}

				if (operationSweepChannelInputDelay == true)
				{
					if ((bool)testConditionCollection->ContainsKey("StartChannelInputDelay"))
					{
						startChannelInputDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "StartChannelInputDelay");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "StartChannelInputDelay" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}

					if ((bool)testConditionCollection->ContainsKey("StopChannelInputDelay"))
					{
						stopChannelInputDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "StopChannelInputDelay");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "StopChannelInputDelay" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}

					if ((bool)testConditionCollection->ContainsKey("IncrementChannelInputDelay"))
					{
						intervalChannelInputDelay = (double)tf_TestParameter_ConditionCast(testParameterName, "IncrementChannelInputDelay");
					}
					else
					{
						ErrorMessage = "Test Condition [" + TM + "IncrementChannelInputDelay" + "] is not found.";
						throw gcnew Exception(ErrorMessage);
					}
				}

			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			//ReadVector
			API_MIPI_Vector_Read(site, testSite, dataPinAlias, moduleAlias, channelInputDelay, vectorFileName, operationSweepChannelInputDelay, ReadHistoryRam_Data, VectorFailCount, VectorFirstFail);

			if (tl->glob->AWV.Debug == 1)
			{
				if (operationSweepChannelInputDelay == true)
				{
					double channelInputDelay_Operation = 0;
					array<int>^ ReadHistoryRam_Data_Operation = gcnew array<int>(1);
					int VectorFailCount_Operation = 0;
					int VectorFirstFail_Operation = 0;

					FileLogger^ fileLogger = gcnew FileLogger(FILE_CONST_AEM_DEBUG);
					StrToFileSweep = "ChannelInputDelay,Result,VectorFailCount,VectorFirstFail";
					fileLogger->WriteToFile(FileSweepName, StrToFileSweep, LOGGER_CONST_OVERWRITE);

					for (channelInputDelay_Operation = startChannelInputDelay; channelInputDelay_Operation <= stopChannelInputDelay; channelInputDelay_Operation = channelInputDelay_Operation + intervalChannelInputDelay)
					{
						API_MIPI_Vector_Read(site, testSite, dataPinAlias, moduleAlias, channelInputDelay_Operation, vectorFileName, operationSweepChannelInputDelay, ReadHistoryRam_Data_Operation, VectorFailCount_Operation, VectorFirstFail_Operation);
						StrToFileSweep = channelInputDelay_Operation.ToString() + "," + (ReadHistoryRam_Data_Operation[0]).ToString() + "," + (VectorFailCount_Operation).ToString() + "," + (VectorFirstFail_Operation).ToString();
						fileLogger->WriteToFile(FileSweepName, StrToFileSweep, LOGGER_CONST_APPEND);

					}

				}
			}
#pragma endregion "Test"

#pragma region "Update Test Result"
			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<
			if (tl->glob->AWV.Debug == 0)
			{
				Result = ReadHistoryRam_Data[0];
			}
			else
			{
				Result = VectorFailCount;
			}

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToLogger(testSite, "Done Executing Test Method DMCase_MIPIReadVector");

#pragma endregion "Update Test Result"
		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}

}