#include "../Module400Series/Module400Series.h"
using namespace Aemulus::TestLib::Utility;

namespace Functions
{
	//Control Method
#pragma region "Control Method"

#pragma region "AM400 DM400 CM400"
	
	void Module400Series::CM_MapTriggerIntToTriggerOut(Site ^ site, int testSite, ConditionCollection^ testConditionCollection)
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
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_MapTriggerIntToTriggerOut");

			//Control Method Compulsory Variable
			int inputTerminal		= 0;
			int outputTerminal		= 0;
			String^ moduleAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String ^ CM				= "MapTriggerInToTriggerOut_";

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

			if ((bool)testConditionCollection->ContainsKey("InputTerminal"))
			{
				ConditionInfo = testConditionCollection["InputTerminal"][site];
				inputTerminal = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "InputTerminal" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("OutputTerminal"))
			{
				ConditionInfo = testConditionCollection["OutputTerminal"][site];
				outputTerminal = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "OutputTerminal" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			#pragma endregion "Test Condition Casting"

			#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(moduleAlias)[0];  //Get Pin Resource Name

			if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
			{
				DM_MapTriggerInToTriggerOut(testSite, moduleAlias, inputTerminal, outputTerminal);
			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_MapTriggerInToTriggerOut(testSite, moduleAlias, inputTerminal, outputTerminal);

			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("CM") == true)
			{
				CM_MapTriggerInToTriggerOut(testSite, moduleAlias, inputTerminal, outputTerminal);
			}
			else
			{
				ErrorMessage = "Module Alias: " + moduleAlias + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_MapTriggerInToTriggerOut");

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
	void Module400Series::CM_DriveSoftwareTrigger(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_DriveSoftwareTrigger");

			//Control Method Compulsory Variable
			int select				= 0;
			double pulseWidth		= 0;
			String^ moduleAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String ^ CM				= "DriveSoftwareTrigger_";


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
			if ((bool)testConditionCollection->ContainsKey("SoftwareTrigger_Select"))
			{
				ConditionInfo = testConditionCollection["SoftwareTrigger_Select"][site];
				select = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Select" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("SoftwareTrigger_PulseWidth"))
			{
				ConditionInfo = testConditionCollection["SoftwareTrigger_PulseWidth"][site];
				pulseWidth = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PulseWidth" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			#pragma endregion "Test Condition Casting"

			#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(moduleAlias)[0];  

			if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
			{
				DM_DriveSoftwareTrigger(testSite, moduleAlias, select, pulseWidth);
			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_DriveSoftwareTrigger(testSite, moduleAlias, select, pulseWidth);

			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("CM") == true)
			{
				CM_DriveSoftwareTrigger(testSite, moduleAlias, select, pulseWidth);
			}
			else
			{
				ErrorMessage = "Module Alias: " + moduleAlias + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_DriveSoftwareTrigger");

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

#pragma endregion

#pragma region "AM400 DM400"
	
	void Module400Series::CM_ConfigureTriggerEdgeLevel(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_ConfigureTriggerEdgeLevel");

			//Control Method Compulsory Variable
			int trigMode			= 0;
			int trigSource			= 0;
			int ignoreTrigCount		= 0;
			String^ moduleAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage				= nullptr;
			String^ CM							= "ConfigureTriggerEdgeLevel_";
			bool ConditionExist_ignoreTrigCount = false;

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
			if ((bool)testConditionCollection->ContainsKey("TrigMode"))
			{
				ConditionInfo = testConditionCollection["TrigMode"][site];
				trigMode = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TrigMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
			if ((bool)testConditionCollection->ContainsKey("IgnoreTrigCount"))
			{
				ConditionInfo = testConditionCollection["IgnoreTrigCount"][site];
				ignoreTrigCount = (int)ConditionInfo->Value;
				ConditionExist_ignoreTrigCount = true;
			}
			#pragma endregion "Test Condition Casting"

			#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(moduleAlias)[0];

			if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
			{
				if (ConditionExist_ignoreTrigCount == true)
				{
					DM_ConfigureTriggerEdgeLevelExtra(testSite, moduleAlias, trigSource, trigMode, ignoreTrigCount);
				}
				else
				{
					DM_ConfigureTriggerEdgeLevel(testSite, moduleAlias, trigSource, trigMode);
				}
			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				if (ConditionExist_ignoreTrigCount == true)
				{
					SMU_ConfigureTriggerEdgeLevelExtra(testSite, moduleAlias, trigSource, trigMode, ignoreTrigCount);
				}
				else
				{
					SMU_ConfigureTriggerEdgeLevel(testSite, moduleAlias, trigSource, trigMode);
				}
			}
			else
			{
				ErrorMessage = "Module Alias: " + moduleAlias + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_ConfigureTriggerEdgeLevel");

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
	void Module400Series::CM_DriveVoltage(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_DriveVoltage");

			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			//Control Method Compulsory Variable
			array<String^> ^ pin			= nullptr;
			array<double> ^ driveVoltage	= nullptr;

			//Operation Variable			
			int Count						= 0;
			int PinCount					= 0;
			String ^ ErrorMessage			= nullptr;
			String ^ CM						= "DriveVoltage_";
			array<Char>^ Separators			= { '_' };
			array<String^>^ CondNametemp;			

			#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;				
			}

			pin	= gcnew array<String^>(PinCount);		
			driveVoltage = gcnew array<double>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
				#pragma region Check PinAlias exists in PinGroupPinMaps
				if (ResourceManagerSett[testSite].PinGroupPinMaps != nullptr) {
					bool aliasFound = false;

					// Iterate over all key-value pairs in PinGroupPinMaps
					for each (KeyValuePair<String^, array<String^>^>^ entry in ResourceManagerSett[testSite].PinGroupPinMaps) 
					{
						array<String^>^ pinAliases = entry->Value;

						// Check if the pinAliasToCheck exists in the array of pin aliases
						for each (String^ alias in pinAliases) {
							if (alias == pin[i]) {
								aliasFound = true;
								break;
							}
						}
						if (aliasFound) {
							break;  // No need to continue if the alias is found
						}
					}

					if (!aliasFound) {
						ErrorMessage = "Pin alias does not exist in Pin Groups.";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else {
					ErrorMessage = "PinGroupPinMaps is not initialized.";
					throw gcnew Exception(ErrorMessage);
				}
				#pragma endregion
				
				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("Force"))
				{
					ConditionInfo = testConditionCollection["Force"][site];
					driveVoltage[i] = (double)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("Force_" + i))
				{
					ConditionInfo = testConditionCollection["Force_" + i][site];
					driveVoltage[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pin[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

			#pragma endregion "Control Condition Casting"

			#pragma region "Test"


			for (int i = 0; i < PinCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pin[i])[0];  //Get Pin Resource Name

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true && HardwareRsrc->Hierarchy[1]->StartsWith("Pin") == true)
				{
					DM_OperationMode(testSite, pin[i], DM_CONST_FORCE_STATE_PMU);
					DM_ConfigureOutputFunction(testSite, pin[i], DM_CONST_DVCI);
					DM_DriveVoltage(testSite, pin[i], driveVoltage[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true && HardwareRsrc->Hierarchy[1]->StartsWith("Pin") == true)
				{
					SMU_ConfigureOutputFunction(testSite, pin[i], AM_CONST_DVCI);
					SMU_DriveVoltage(testSite, pin[i], driveVoltage[i]);
				}
				else
				{
					ErrorMessage = "Pin Alias: " + pin[i] + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
					throw gcnew Exception(ErrorMessage);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_DriveVoltage");

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
	void Module400Series::CM_DriveCurrent(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_DriveCurrent
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_DriveCurrent");

			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			//Control Method Compulsory Variable
			array<String^> ^ pin			= nullptr;
			array<double> ^ driveCurrent	= nullptr;

			//Operation Variable
			int Count						= 0;
			int PinCount					= 0;
			String ^ ErrorMessage			= nullptr;
			String ^ CM						= "DriveCurrent_";	
			array<Char>^ Separators			= { '_' };
			array<String^>^ CondNametemp;

			#pragma region "Control Condition Casting"

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;
			}

			pin = gcnew array<String^>(PinCount);
			driveCurrent = gcnew array<double>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
#pragma region Check PinAlias exists in PinGroupPinMaps
				if (ResourceManagerSett[testSite].PinGroupPinMaps != nullptr) {
					bool aliasFound = false;

					// Iterate over all key-value pairs in PinGroupPinMaps
					for each (KeyValuePair<String^, array<String^>^>^ entry in ResourceManagerSett[testSite].PinGroupPinMaps)
					{
						array<String^>^ pinAliases = entry->Value;

						// Check if the pinAliasToCheck exists in the array of pin aliases
						for each (String^ alias in pinAliases) {
							if (alias == pin[i]) {
								aliasFound = true;
								break;
							}
						}
						if (aliasFound) {
							break;  // No need to continue if the alias is found
						}
					}

					if (!aliasFound) {
						ErrorMessage = "Pin alias does not exist in Pin Groups.";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else {
					ErrorMessage = "PinGroupPinMaps is not initialized.";
					throw gcnew Exception(ErrorMessage);
				}
#pragma endregion

				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("Force"))
				{
					ConditionInfo = testConditionCollection["Force"][site];
					driveCurrent[i] = (double)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("Force_" + i))
				{
					ConditionInfo = testConditionCollection["Force_" + i][site];
					driveCurrent[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pin[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

			#pragma endregion "Control Condition Casting"

			#pragma region "Test"

			for (int i = 0; i < PinCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pin[i])[0];  //Get Pin Resource Name

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					DM_OperationMode(testSite, pin[i], DM_CONST_FORCE_STATE_PMU);
					DM_ConfigureOutputFunction(testSite, pin[i], DM_CONST_DICV);
					DM_DriveCurrent(testSite, pin[i], driveCurrent[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					SMU_ConfigureOutputFunction(testSite, pin[i], AM_CONST_DICV);
					SMU_DriveCurrent(testSite, pin[i], driveCurrent[i]);
				}
				else
				{
					ErrorMessage = "Pin Alias: " + pin[i] + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
					throw gcnew Exception(ErrorMessage);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_DriveCurrent");

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
	void Module400Series::CM_ClampVoltage(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_ClampVoltage
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_ClampVoltage");

			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			//Control Method Compulsory Variable
			array<String^> ^ pin			= nullptr;
			array<double> ^ clampVoltage	= nullptr;

			//Operation Variable
			int Count						= 0;
			int PinCount					= 0;
			String ^ ErrorMessage			= nullptr;
			String ^ CM						= "ClampVoltage_";
			array<Char>^ Separators			= { '_' };
			array<String^>^ CondNametemp;

			#pragma region "Control Condition Casting"

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;
			}

			pin = gcnew array<String^>(PinCount);
			clampVoltage = gcnew array<double>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
#pragma region Check PinAlias exists in PinGroupPinMaps
				if (ResourceManagerSett[testSite].PinGroupPinMaps != nullptr) {
					bool aliasFound = false;

					// Iterate over all key-value pairs in PinGroupPinMaps
					for each (KeyValuePair<String^, array<String^>^>^ entry in ResourceManagerSett[testSite].PinGroupPinMaps)
					{
						array<String^>^ pinAliases = entry->Value;

						// Check if the pinAliasToCheck exists in the array of pin aliases
						for each (String^ alias in pinAliases) {
							if (alias == pin[i]) {
								aliasFound = true;
								break;
							}
						}
						if (aliasFound) {
							break;  // No need to continue if the alias is found
						}
					}

					if (!aliasFound) {
						ErrorMessage = "Pin alias does not exist in Pin Groups.";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else {
					ErrorMessage = "PinGroupPinMaps is not initialized.";
					throw gcnew Exception(ErrorMessage);
				}
#pragma endregion

				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("Clamp"))
				{
					ConditionInfo = testConditionCollection["Clamp"][site];
					clampVoltage[i] = (double)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("Clamp_" + i))
				{
					ConditionInfo = testConditionCollection["Clamp_" + i][site];
					clampVoltage[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pin[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

			#pragma endregion "Control Condition Casting"

			#pragma region "Test"

			for (int i = 0; i < PinCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pin[i])[0];  //Get Pin Resource Name

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					DM_OperationMode(testSite, pin[i], DM_CONST_FORCE_STATE_PMU);
					DM_ConfigureOutputFunction(testSite, pin[i], DM_CONST_DICV);
					DM_ClampVoltage(testSite, pin[i], clampVoltage[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					SMU_ConfigureOutputFunction(testSite, pin[i], AM_CONST_DICV);
					SMU_ClampVoltage(testSite, pin[i], clampVoltage[i]);
				}

				else
				{
					ErrorMessage = "Pin Alias: " + pin[i] + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
					throw gcnew Exception(ErrorMessage);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_ClampVoltage");

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
	void Module400Series::CM_ClampCurrent(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
	{
		/*****************************************************************************************************
		** CM_ClampCurrent
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_ClampCurrent");

			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			//Control Method Compulsory Variable
			array<String^> ^ pin			= nullptr;
			array<double> ^ clampCurrent	= nullptr;

			//Operation Variable
			int Count						= 0;
			int PinCount					= 0;
			String ^ ErrorMessage			= nullptr;
			String ^ CM						= "ClampCurrent_";
			array<Char>^ Separators			= { '_' };
			array<String^>^ CondNametemp;

			#pragma region "Control Condition Casting"

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;
			}

			pin = gcnew array<String^>(PinCount);
			clampCurrent = gcnew array<double>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
#pragma region Check PinAlias exists in PinGroupPinMaps
				if (ResourceManagerSett[testSite].PinGroupPinMaps != nullptr) {
					bool aliasFound = false;

					// Iterate over all key-value pairs in PinGroupPinMaps
					for each (KeyValuePair<String^, array<String^>^>^ entry in ResourceManagerSett[testSite].PinGroupPinMaps)
					{
						array<String^>^ pinAliases = entry->Value;

						// Check if the pinAliasToCheck exists in the array of pin aliases
						for each (String^ alias in pinAliases) {
							if (alias == pin[i]) {
								aliasFound = true;
								break;
							}
						}
						if (aliasFound) {
							break;  // No need to continue if the alias is found
						}
					}

					if (!aliasFound) {
						ErrorMessage = "Pin alias does not exist in Pin Groups.";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else {
					ErrorMessage = "PinGroupPinMaps is not initialized.";
					throw gcnew Exception(ErrorMessage);
				}
#pragma endregion

				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("Clamp"))
				{
					ConditionInfo = testConditionCollection["Clamp"][site];
					clampCurrent[i] = (double)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("Clamp_" + i))
				{
					ConditionInfo = testConditionCollection["Clamp_" + i][site];
					clampCurrent[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pin[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

#pragma endregion "Control Condition Casting"

			#pragma region "Test"

			for (int i = 0; i < PinCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pin[i])[0];  //Get Pin Resource Name

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					DM_OperationMode(testSite, pin[i], DM_CONST_FORCE_STATE_PMU);
					DM_ConfigureOutputFunction(testSite, pin[i], DM_CONST_DVCI);
					DM_ClampCurrent(testSite, pin[i], clampCurrent[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					SMU_ConfigureOutputFunction(testSite, pin[i], AM_CONST_DVCI);
					SMU_ClampCurrent(testSite, pin[i], clampCurrent[i]);
				}
				else
				{
					ErrorMessage = "Pin Alias: " + pin[i] + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
					throw gcnew Exception(ErrorMessage);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_ClampCurrent");

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
	void Module400Series::CM_SetNPLC(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_SetNPLC");


			//Control Method Compulsory Variable
			array<String^> ^ pin	= nullptr;
			array<double> ^ nplc	= nullptr;

			//Operation Variable
			int PinCount			= 0;
			int Count				= 0;
			String ^ ErrorMessage	= nullptr;
			array<Char>^ Separators = { '_' };
			String ^ CM				= "SetNPLC_";
			array<String^>^ CondNametemp;

			#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();
			
			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;
			}

			pin = gcnew array<String^>(PinCount);
			nplc = gcnew array<double>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
#pragma region Check PinAlias exists in PinGroupPinMaps
				if (ResourceManagerSett[testSite].PinGroupPinMaps != nullptr) {
					bool aliasFound = false;

					// Iterate over all key-value pairs in PinGroupPinMaps
					for each (KeyValuePair<String^, array<String^>^>^ entry in ResourceManagerSett[testSite].PinGroupPinMaps)
					{
						array<String^>^ pinAliases = entry->Value;

						// Check if the pinAliasToCheck exists in the array of pin aliases
						for each (String^ alias in pinAliases) {
							if (alias == pin[i]) {
								aliasFound = true;
								break;
							}
						}
						if (aliasFound) {
							break;  // No need to continue if the alias is found
						}
					}

					if (!aliasFound) {
						ErrorMessage = "Pin alias does not exist in Pin Groups.";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else {
					ErrorMessage = "PinGroupPinMaps is not initialized.";
					throw gcnew Exception(ErrorMessage);
				}
#pragma endregion

				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("NPLC"))
				{
					ConditionInfo = testConditionCollection["NPLC"][site];
					nplc[i] = (double)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("NPLC_" + i))
				{
					ConditionInfo = testConditionCollection["NPLC_" + i][site];
					nplc[i] = (double)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pin[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

			#pragma endregion "Control Condition Casting"
			
			#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			for (int i = 0; i < PinCount; i++)
			{
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pin[i])[0];  //Get Pin Resource Name

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					DM_NplcSetting(testSite, pin[i], nplc[i]);
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
				{
					SMU_NplcSetting(testSite, pin[i], nplc[i]);
				}
				else
				{
					ErrorMessage = "Pin Alias: " + pin[i] + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
					throw gcnew Exception(ErrorMessage);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_SetNPLC");

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
	void Module400Series::CM_SetPinOnOff(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_SetPinOnOff");

			//Control Method Compulsory Variable
			array<String^> ^ pin	= nullptr;
			array<int> ^ pinState	= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String ^ CM				= "SetPinOnOff_";
			array<String^>^ CondNametemp;
			array<Char>^ Separators = { '_' };
			int PinCount			= 0;
			int Count				= 0;
			
			#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->Contains("PinAlias"))
					PinCount++;
			}

			pin = gcnew array<String^>(PinCount);
			pinState = gcnew array<int>(PinCount);

			for (Count = 0; Count < PinCount; Count++)
			{
				for each(Condition ^ testcond in testConditionCollection)
				{
					if (testcond->Name == "PinAlias" && Count == 0) //First condition as "PinAlias"
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
					else if (testcond->Name == "PinAlias_" + Count) //Following condition as "PinAlias_1", "PinAlias_2" ...
					{
						ConditionInfo = testConditionCollection[testcond->Name][site];
						pin[Count] = (String^)ConditionInfo->Value;
						break;
					}
				}
			}

			for (int i = 0; i < PinCount; i++)
			{
#pragma region Check PinAlias exists in PinGroupPinMaps
				if (ResourceManagerSett[testSite].PinGroupPinMaps != nullptr) {
					bool aliasFound = false;

					// Iterate over all key-value pairs in PinGroupPinMaps
					for each (KeyValuePair<String^, array<String^>^>^ entry in ResourceManagerSett[testSite].PinGroupPinMaps)
					{
						array<String^>^ pinAliases = entry->Value;

						// Check if the pinAliasToCheck exists in the array of pin aliases
						for each (String^ alias in pinAliases) {
							if (alias == pin[i]) {
								aliasFound = true;
								break;
							}
						}
						if (aliasFound) {
							break;  // No need to continue if the alias is found
						}
					}

					if (!aliasFound) {
						ErrorMessage = "Pin alias does not exist in Pin Groups.";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else {
					ErrorMessage = "PinGroupPinMaps is not initialized.";
					throw gcnew Exception(ErrorMessage);
				}
#pragma endregion

				//Getting all Pins and Conditions
				if (i == 0 && (bool)testConditionCollection->ContainsKey("PinOn"))
				{
					ConditionInfo = testConditionCollection["PinOn"][site];
					pinState[i] = (int)ConditionInfo->Value;
				}
				else if (i != 0 && (bool)testConditionCollection->ContainsKey("PinOn_" + i))
				{
					ConditionInfo = testConditionCollection["PinOn_" + i][site];
					pinState[i] = (int)ConditionInfo->Value;
				}
				else
				{
					ErrorMessage = "Test Condition [" + CM + pin[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

			#pragma endregion "Control Condition Casting"

			#pragma region "Test"

			for (int i = 0; i < PinCount; i++)
			{
				//Setting up Pin
				Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pin[i])[0];  //Get Pin Resource Name

				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true && HardwareRsrc->Hierarchy[1]->StartsWith("Pin") == true)
				{
					if (pinState[i] == 0)
					{
						DM_OffDMpin(testSite, pin[i]);
					}
					else if (pinState[i] == 1)
					{
						DM_OnDMpin(testSite, pin[i]);
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "PinOnOff_" + pin[i] + " value :" + pinState[i].ToString() + "is invalid as only 0 (OFF) or 1 (ON) is valid";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true && HardwareRsrc->Hierarchy[1]->StartsWith("Pin") == true)
				{
					if (pinState[i] == 0)
					{
						SMU_OffSMU(testSite, pin[i]);
					}
					else if (pinState[i] == 1)
					{
						SMU_OnSMU(testSite, pin[i]);
					}
					else
					{
						ErrorMessage = "Test Condition [" + CM + "PinOnOff_" + pin[i] + " value :" + pinState[i].ToString() + "is invalid as only 0 (OFF) or 1 (ON) is valid";
						throw gcnew Exception(ErrorMessage);
					}
				}
				else
				{
					ErrorMessage = "Pin Alias: " + pin[i] + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
					throw gcnew Exception(ErrorMessage);
				}
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_SetPinOnOff");

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

#pragma endregion

#pragma region "AM400"

	void Module400Series::CM_AMConfigureInputTriggerSelect(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_ConfigureInputTriggerSelect");

			//Control Method Compulsory Variabl
			int trigSource = 0;
			double delayAfterTrig = 0;
			String^ alias = nullptr;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ CM = "ConfigureInputTriggerSelect_";

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("PinAlias"))
			{
				ConditionInfo = testConditionCollection["PinAlias"][site];
				alias = (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PinAlias" + "] is not found.";
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
			if ((bool)testConditionCollection->ContainsKey("MeasureDelayAfterTrig"))
			{
				ConditionInfo = testConditionCollection["MeasureDelayAfterTrig"][site];
				delayAfterTrig = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "MeasureDelayAfterTrig" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			SMU_ConfigureInputTriggerSelect(testSite, alias, trigSource, delayAfterTrig);
				
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_ConfigureInputTriggerSelect");

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
	void Module400Series::CM_AMConfigureSMUOutputTriggerMode(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_AMConfigureSMUOutputTriggerMode");

			//Control Method Compulsory Variable
			int mode				= 0;
			String^ pinAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String ^ CM				= "AMConfigureSMUOutputTriggerMode_";

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
			if ((bool)testConditionCollection->ContainsKey("TriggerMode"))
			{
				ConditionInfo = testConditionCollection["TriggerMode"][site];
				mode = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TriggerMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			#pragma endregion "Test Condition Casting"

			#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			SMU_ConfigureSMUOutputTriggerMode(testSite, pinAlias, mode);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_AMConfigureSMUOutputTriggerMode");

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
	void Module400Series::CM_AMConfigureSMUOutputTriggerPulseWidth(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_AMConfigureSMUOutputTriggerPulseWidth");

			//Control Method Compulsory Variable
			double pulseWidth		= 0;
			String^ pinAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String^ CM				= "AMConfigureSMUOutputTriggerPulseWidth_";

			#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("PinAlias"))
			{
				ConditionInfo	= testConditionCollection["PinAlias"][site];
				pinAlias		= (String^)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage	= "Test Condition [" + CM + "PinAlias" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("PulseWidth"))
			{
				ConditionInfo	= testConditionCollection["PulseWidth"][site];
				pulseWidth		= (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "PulseWidth" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

			#pragma endregion "Test Condition Casting"

			#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			SMU_ConfigureSMUOutputTriggerPulseWidth(testSite, pinAlias, pulseWidth);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_AMConfigureSMUOutputTriggerPulseWidth");

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
	void Module400Series::CM_AMConfigureSMUOutputTriggerDuringSource(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_AMConfigureSMUOutputTriggerDuringSource");

			//Control Method Compulsory Variable
			double level			= 0;
			double range			= 0;
			int mode				= 0;
			int edgeSetting			= 0;
			String^ pinAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String ^ CM				= "AMConfigureSMUOutputTriggerDuringSource_";


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
			if ((bool)testConditionCollection->ContainsKey("ThresholdLevel"))
			{
				ConditionInfo = testConditionCollection["ThresholdLevel"][site];
				level = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ThresholdLevel" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}
			if ((bool)testConditionCollection->ContainsKey("ThresholdLevel_Range"))
			{
				ConditionInfo = testConditionCollection["ThresholdLevel_Range"][site];
				range = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ThresholdLevel_Range" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}
			if ((bool)testConditionCollection->ContainsKey("Threshold_Mode"))
			{
				ConditionInfo = testConditionCollection["Threshold_Mode"][site];
				mode = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "ThresholdMode" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}
			if ((bool)testConditionCollection->ContainsKey("EdgeSetting"))
			{
				ConditionInfo = testConditionCollection["EdgeSetting"][site];
				edgeSetting = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "EdgeSetting" + "] is not found.";
				throw gcnew Exception(ErrorMessage);

			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			SMU_ConfigureSMUOutputTriggerDuringSource(testSite,pinAlias, level, range, mode, edgeSetting);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_AMConfigureSMUOutputTriggerDuringSource");

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
	void Module400Series::CM_AMConfigureOutputTriggerSelect(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_AMConfigureOutputTriggerSelect");

			//Control Method Compulsory Variable
			int triggerOutput		= 0;
			double triggerDelay		= 0;
			String^ pinAlias		= nullptr;

			//Operation Variable
			String ^ ErrorMessage	= nullptr;
			String ^CM				= "AMConfigureOutputTriggerSelect_";

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
			if ((bool)testConditionCollection->ContainsKey("TriggerOutput"))
			{
				ConditionInfo = testConditionCollection["TriggerOutput"][site];
				triggerOutput = (int)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "TriggerOutput" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("TriggerDelay"))
			{
				ConditionInfo = testConditionCollection["TriggerDelay"][site];
				triggerDelay = (double)ConditionInfo->Value;
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
			SMU_ConfigureOutputTriggerSelect(testSite, pinAlias, triggerOutput, triggerDelay);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_AMConfigureOutputTriggerSelect");

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

#pragma endregion

	void Module400Series::TM_DifferentialResult(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method DCCase_DifferentialResult");
			testParameterCount = 1;

			//Test Method Compulsory Variable
			String ^ expression = nullptr;
			array<String^>^ globalResultKey = nullptr;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ TM = "DifferentialResult_";
			array<String^>^ Variable = nullptr;
			array<int>^ GlobalResultValue_Int32 = nullptr;
			array<double>^ GlobalResultValue_Double = nullptr;
			String ^ NewString = nullptr;
			array<Char>^ Separators = { '_' };
			array<String^>^ SplitString;
			int VariableCount = 0;
			int Count = 0;
			Object^Answer;
			DataTable ^ dt = gcnew DataTable();
			Regex ^ rgx = gcnew Regex("[a-zA-Z]");
			DataType dataType = ((TestItem^)site->FlowItems[site->CurrentFlowItem->Name])->TestParameters[testParameterName]->DataType;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			//Finding the number of Variable used for the expression
			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "ResultKey_"))
				{
					VariableCount++;
				}
			}

			Variable = gcnew array <String^>(VariableCount);
			globalResultKey = gcnew array <String^>(VariableCount);
			GlobalResultValue_Int32 = gcnew array <int>(VariableCount);
			GlobalResultValue_Double = gcnew array <double>(VariableCount);

			//Casting the Variable and Store in Array
			for each(Condition ^ testcond in testConditionCollection)
			{
				if (testcond->Name->StartsWith(TM + "ResultKey_"))
				{
					SplitString = testcond->Name->Split(Separators, System::StringSplitOptions::None);
					Variable[Count] = SplitString[2];
					Count++;
				}
			}

			//Casting the GlobalResultKey
			for (int i = 0; i < VariableCount; i++)
			{
				if ((bool)testConditionCollection->ContainsKey("ResultKey_" + Variable[i]))
				{
					globalResultKey[i] = (String^)tf_TestParameter_ConditionCast(testParameterName, "ResultKey_" + Variable[i]);
				}
				else
				{
					ErrorMessage = "Test Condition [" + TM + "ResultKey_" + Variable[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}
			}

			//Casting the Expression
			if ((bool)testConditionCollection->ContainsKey("Expression"))
			{
				expression = (String^)tf_TestParameter_ConditionCast(testParameterName, "Expression");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "Expression" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			//Checking and Casting
			for (int i = 0; i < VariableCount; i++)
			{
				//Checking the availablity of the key inside the Dictionary
				if (!tl->glob->GlobalResult[testSite]->ContainsKey(globalResultKey[i]))
				{
					ErrorMessage = "Test Condition [" + TM + "ResultKey_" + Variable[i] + " = " + globalResultKey[i] + "] is not found.";
					throw gcnew Exception(ErrorMessage);
				}

				//Cast the Value according to the Key
				switch (dataType)
				{
				case DataType::Double:
					GlobalResultValue_Double[i] = (double)tl->glob->GlobalResult[testSite][globalResultKey[i]];
					break;
				case DataType::Int32:
					GlobalResultValue_Int32[i] = (int)tl->glob->GlobalResult[testSite][globalResultKey[i]];
					break;
				default:
					break;
				}
			}

			//Replace the variable of the Expression to value(int or double)
			for (int i = 0; i < VariableCount; i++)
			{
				if (expression->Contains(Variable[i]))
				{
					switch (dataType)
					{
					case DataType::Double:
						NewString = GlobalResultValue_Double[i].ToString("f20");
						break;
					case DataType::Int32:
						NewString = GlobalResultValue_Int32[i].ToString("f20");
						break;
					default:
						break;
					}
					expression = expression->Replace(Variable[i], NewString);
				}
			}

			//Checking any Variable that are not assigned by value on the expression
			for each(Match ^match in rgx->Matches(expression))
			{
				String ^ Value = match->Value;

				ErrorMessage = "Test Condition [" + TM + "ResultKey_" + Value + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//Computation the Expression 
			Answer = dt->Compute(expression, "");

#pragma endregion "Test"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			switch (dataType)
			{
			case DataType::Double:
				tl->glob->TestResults[testSite][testParameterNumber] = Convert::ToDouble(Answer);
				break;
			case DataType::Int32:
				tl->glob->TestResults[testSite][testParameterNumber] = Convert::ToInt32(Answer);
				break;
			default:
				break;
			}

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method DCCase_DifferentialResult");

		}
		catch (Exception ^ ex)
		{
			String ^ methodType = "TM_";
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->UpdateTestResultsWhenException(site, testSite);
			tl->ErrorHandling(site, testSite, (methodType + tl->glob->ErrorInfo[testSite].TestMethodName), tl->glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void Module400Series::CM_WaitSecond(Site ^ site, int testSite, ConditionCollection ^ testConditionCollection)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Control Method DCCase_WaitSecond");

			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			//Control Method Compulsory Variable
			double delay = 0;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ CM = "WaitSecond_";

#pragma region "Control Condition Casting"	

			ConditionInSite ^ ConditionInfo = gcnew ConditionInSite();

			if ((bool)testConditionCollection->ContainsKey("Delay"))
			{
				ConditionInfo = testConditionCollection["Delay"][site];
				delay = (double)ConditionInfo->Value;
			}
			else
			{
				ErrorMessage = "Test Condition [" + CM + "Delay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}


#pragma endregion "Control Condition Casting"

#pragma region "Test"

			util->WaitSecond(delay);

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Control Method DCCase_WaitSecond");

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

#pragma endregion

	//Test Method
#pragma region "Test Method"

#pragma region "AM400 DM400"

	void Module400Series::TM_OS(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method DCCase_OS");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ pinMeasure = nullptr;
			double driveCurrent = 0.0;
			double clampVoltage = 0.0;
			double delay = 0.0;

			//Operation Variable
			double Result = 0.0;
			String ^ ErrorMessage = nullptr;
			String ^ TM = (String ^)tf_TestItem_Name();

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<


			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);


			if ((bool)testConditionCollection->ContainsKey("PinMeasure")) {
				pinMeasure = (String^)tf_TestParameter_ConditionCast(testParameterName, "PinMeasure");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + " -> PinMeasure" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("DriveCurrent")) {
				driveCurrent = (double)tf_TestParameter_ConditionCast(testParameterName, "DriveCurrent");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + " -> DriveCurrent" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("ClampVoltage")) {
				clampVoltage = (double)tf_TestParameter_ConditionCast(testParameterName, "ClampVoltage");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + " -> ClampVoltage" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Delay")) {
				delay = (double)tf_TestParameter_ConditionCast(testParameterName, "Delay");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + "-> Delay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<
#pragma endregion "Test Condition Casting"

#pragma region "Test"
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinMeasure)[0];
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "PinMeasure:" + HardwareRsrc->Alias);
			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
			{
				DM_MeasureOS(testSite, pinMeasure, driveCurrent, clampVoltage, delay, Result);
			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_MeasureOS(testSite, pinMeasure, driveCurrent, clampVoltage, delay, Result);
			}
			else
			{
				ErrorMessage = "Pin Alias: " + pinMeasure + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method DCCase_OS");

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
	void Module400Series::TM_MeasureCurrent(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method DCCase_MeasureCurrent");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ pinMeasure = nullptr;
			double delay = 0.0;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ TM = (String ^)tf_TestItem_Name();
			double Result = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("PinMeasure")) {
				pinMeasure = (String^)tf_TestParameter_ConditionCast(testParameterName, "PinMeasure");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + " -> PinMeasure" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}

			if ((bool)testConditionCollection->ContainsKey("Delay")) {
				delay = (double)tf_TestParameter_ConditionCast(testParameterName, "Delay");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + " -> Delay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinMeasure)[0];

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
			{
				DM_MeasureCurrent(testSite, pinMeasure, delay, Result);
			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_MeasureCurrent(testSite, pinMeasure, delay, Result);
			}
			else
			{
				ErrorMessage = "Pin Alias: " + pinMeasure + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}


#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method DCCase_MeasureCurrent");

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
	void Module400Series::TM_MeasureVoltage(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
	{
		try
		{
			//>>>>>>>>>>>>>>>>>>>> Local Variables <<<<<<<<<<<<<<<<<<<<

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method DCCase_MeasureVoltage");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ pinMeasure = nullptr;
			double delay = 0.0;
			double nplc = 0.0;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ TM = (String ^)tf_TestItem_Name();
			double Result = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<

			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);


			if ((bool)testConditionCollection->ContainsKey("PinMeasure"))
			{
				pinMeasure = (String^)tf_TestParameter_ConditionCast(testParameterName, "PinMeasure");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + " -> PinMeasure" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Delay"))
			{
				delay = (double)tf_TestParameter_ConditionCast(testParameterName, "Delay");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + " -> Delay" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			//>>>>>>>>>>>>>>>>>>>> Optional <<<<<<<<<<<<<<<<<<<<

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinMeasure)[0];

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
			{
				DM_MeasureVoltage(testSite, pinMeasure, delay, Result);
			}
			else if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_MeasureVoltage(testSite, pinMeasure, delay, Result);
			}
			else
			{
				ErrorMessage = "Pin Alias: " + pinMeasure + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method DCCase_MeasureVoltage");

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
#pragma endregion

#pragma region "AM400"
	void Module400Series::TM_MeasureBurstCurrent(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method DCCase_MeasureBurstCurrent");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ pinMeasure = nullptr;
			double duration = 0;
			double peakPercentage = 0;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			String ^ TM = (String ^)tf_TestItem_Name();
			double Result = 0.0;

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);


			if ((bool)testConditionCollection->ContainsKey("PinMeasure")) {
				pinMeasure = (String^)tf_TestParameter_ConditionCast(testParameterName, "PinMeasure");
			}
			else {
				ErrorMessage = "Test Condition [" + TM + "PinMeasure" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Duration"))
			{
				duration = (double)tf_TestParameter_ConditionCast(testParameterName, "Duration");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "Duration" + "] is not found.";
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

#pragma endregion "Test Condition Casting"

#pragma region "Test"
			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinMeasure)[0];

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_MeasureBurstCurrent(testSite, pinMeasure, duration, peakPercentage, Result);
			}
			else
			{
				ErrorMessage = "Pin Alias: " + pinMeasure + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}

#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method DCCase_MeasureBurstCurrent");

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
	void Module400Series::TM_MeasureBurstVoltage(Site ^ site, int testSite, String^ testParameterName, int testParameterNumber, int % testParameterCount)
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

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Executing Test Method DCCase_MeasureBurstVoltage");

			testParameterCount = 1;

			//Test Method Compulsory Variable
			String^ pinMeasure = nullptr;
			double duration = 0;
			double peakPercentage = 0;
			double delay = 0;

			//Operation Variable
			String ^ ErrorMessage = nullptr;
			double Result = 0.0;
			String ^ TM = (String ^)tf_TestItem_Name();

#pragma region "Test Condition Casting"

			//>>>>>>>>>>>>>>>>>>>> Compulsory <<<<<<<<<<<<<<<<<<<<
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			if ((bool)testConditionCollection->ContainsKey("PinMeasure"))
			{
				pinMeasure = (String^)tf_TestParameter_ConditionCast(testParameterName, "PinMeasure");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "PinMeasure" + "] is not found.";
				throw gcnew Exception(ErrorMessage);
			}
			if ((bool)testConditionCollection->ContainsKey("Duration"))
			{
				duration = (double)tf_TestParameter_ConditionCast(testParameterName, "Duration");
			}
			else
			{
				ErrorMessage = "Test Condition [" + TM + "Duration" + "] is not found.";
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

#pragma endregion "Test Condition Casting"

#pragma region "Test"

			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinMeasure)[0];
			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			if (HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true)
			{
				SMU_MeasureBurstVoltage(testSite, pinMeasure, duration, peakPercentage, Result);
			}
			else
			{
				ErrorMessage = "Pin Alias: " + pinMeasure + " , Hardware Resource: " + HardwareRsrc->Hierarchy[0] + " is not supported";
				throw gcnew Exception(ErrorMessage);
			}
#pragma endregion "Test"

#pragma region "Update Test Result"

			//>>>>>>>>>>>>>>>>>>>> Update Test Results <<<<<<<<<<<<<<<<<<<<

			tl->glob->TestResults[testSite][testParameterNumber] = Result;

			tl->WriteToTcrLgr("SITE " + testSite.ToString(), "Done Executing Test Method DCCase_MeasureBurstVoltage");

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
#pragma endregion

#pragma endregion

}