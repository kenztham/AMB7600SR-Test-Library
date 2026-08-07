#include "AMB7600SR.h"

namespace Functions
{
	// DM400e Load Phase Initialization 
	array<String^>^ AMB7600SRTestLibrary::GetDMModuleAlias(Site ^ site, int siteIndex)
	{
		/*****************************************************************************************************
		** GetDmModuleAlias
		******************************************************************************************************
		** Descriptions:
		**		Usage: Get module alias for specified DM resource
		**
		** Parameters:
		**		dm		- DM resource
		**
		** Return value:
		**		Module alias
		******************************************************************************************************/

		int moduleCount = 0;
		
		for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
		{
			ResourceManagerSett[siteIndex].HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];

			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "DM483e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "DM482e")
				{
					moduleCount++;
				}
			}
		}

		array<String^>^ moduleAlias = gcnew array<String^>(moduleCount);
		int count = 0;

		for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
		{
			ResourceManagerSett[siteIndex].HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "DM483e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "DM482e")
				{
					moduleAlias[count] = Rsrc->ToString();
					count++;
				}
			}
		}

		return moduleAlias;
	}
	int AMB7600SRTestLibrary::InitDmPinAliasPreviousState(Site ^ site, int siteIndex)
	{
		int ret = 0;

		// Only hardware resources that have string values begin with "DM" will be added into global variables initialization

		for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].DMResourceAlias)
		{
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVIH->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVIL->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVOH->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVOL->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateIOH->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateIOL->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVCH->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVCL->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVTERM->Add(pinAlias->Key, 999);
			tl->glob->DIO_DMStateSettingsManager[siteIndex].DIOStatePinValue->Add(pinAlias->Key, 999);

			tl->glob->PEStateSettingsManager[siteIndex].PEStateVIH->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateVIL->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateVOH->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateVOL->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateIOH->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateIOL->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateVCH->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateVCL->Add(pinAlias->Key, 999);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateVTERM->Add(pinAlias->Key, 999);

			tl->glob->PEStateSettingsManager[siteIndex].PEStateInputTermEnable->Add(pinAlias->Key, false);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateHVEnable->Add(pinAlias->Key, false);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateActiveLoadEnable->Add(pinAlias->Key, false);
			tl->glob->PEStateSettingsManager[siteIndex].PEStateDifferentialComparatorEnable->Add(pinAlias->Key, false);

			tl->glob->PMUStateSettingsManager[siteIndex].PMUStateDriveVoltage->Add(pinAlias->Key, 999);
			tl->glob->PMUStateSettingsManager[siteIndex].PMUStateDriveCurrent->Add(pinAlias->Key, 999);
			tl->glob->PMUStateSettingsManager[siteIndex].PMUStateClampVoltage->Add(pinAlias->Key, 999);
			tl->glob->PMUStateSettingsManager[siteIndex].PMUStateClampCurrent->Add(pinAlias->Key, 999);
			tl->glob->PMUStateSettingsManager[siteIndex].PMUStateOutputFunction->Add(pinAlias->Key, 999);
			tl->glob->PMUStateSettingsManager[siteIndex].PMUStateNPLC->Add(pinAlias->Key, 999);

			tl->glob->DMStateSettingsManager[siteIndex].DMStateOperationMode->Add(pinAlias->Key, 999);

		}

		return ret;
	}
	bool AMB7600SRTestLibrary::CheckingAnyDmModuleRunVector(Site ^ site, int siteIndex, array<String ^>^ moduleAlias, array<String ^>^ % moduleAliasRunVector, array<String ^>^ % communicationProtocol)
	{
		bool RunVector = false;

		ConditionCollection ^ ControlConditionCollection = gcnew ConditionCollection();
		ControlConditionCollection = tf_ControlItem_ConditionList();

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		int moduleAliasRunVectorCount = 0;
		int count = 0;
		moduleAliasRunVector = nullptr;
		communicationProtocol = nullptr;
		array<String^>^ CondNametemp;
		array<Char>^ Separators = { '_' };
		array<bool> ^ exisAmaptModuleAliasRunVector = nullptr;

		for each(Condition ^ controlCondition in ControlConditionCollection)
		{
			if (controlCondition->Name->StartsWith("DmModuleVectorMode_"))
			{
				moduleAliasRunVectorCount++;
			}
		}

		if (moduleAliasRunVectorCount > 0)
		{
			moduleAliasRunVector = gcnew array <String^>(moduleAliasRunVectorCount);
			exisAmaptModuleAliasRunVector = gcnew array <bool>(moduleAliasRunVectorCount);
			communicationProtocol = gcnew array <String^>(moduleAliasRunVectorCount);

			for each(Condition ^ controlCondition in ControlConditionCollection)
			{
				if (controlCondition->Name->StartsWith("DmModuleVectorMode_"))
				{
					CondNametemp = controlCondition->Name->Split(Separators, System::StringSplitOptions::None);;
					moduleAliasRunVector[count] = CondNametemp[1];
					exisAmaptModuleAliasRunVector[count] = false;
					communicationProtocol[count] = (String^)tf_ControlItem_ConditionCast(controlCondition->Name);
					count++;
				}
			}

			//Checking the availablility of the ModuleAlias at Amap
			for (int i = 0; i < moduleAlias->Length; i++)
			{
				for (int j = 0; j < moduleAliasRunVector->Length; j++)
				{
					if (moduleAliasRunVector[j] == moduleAlias[i])
					{
						exisAmaptModuleAliasRunVector[j] = true;
					}
				}
			}
			for (int i = 0; i < moduleAliasRunVector->Length; i++)
			{
				if (exisAmaptModuleAliasRunVector[i] == false)
				{
					String^ ErrorMessage = " ModuleAlias: " + moduleAliasRunVector[i] + "that Stated at the Test Flow ControlItem Condition is not found in Resource Amap. Please check  DmModuleVectorMode_" + moduleAliasRunVector[i] + ".";
					tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
					tl->WriteToLogger(siteIndex, ErrorMessage);
				}
			}

			RunVector = true;
		}
		else
		{
			moduleAliasRunVector = gcnew array <String^>(moduleAliasRunVectorCount);
			communicationProtocol = gcnew array <String^>(moduleAliasRunVectorCount);
			RunVector = false;
		}


		return RunVector;
	}
	int AMB7600SRTestLibrary::CastTimingSetPeriodControlItem(Site ^ site, int siteIndex)
	{

		int testSite = 0;
		int ret = 0;
		int setCount = 0;
		String^ ErrorMessage = nullptr;


		try
		{
			ConditionCollection ^ ControlConditionCollection = gcnew ConditionCollection();
			ControlConditionCollection = tf_ControlItem_ConditionList();

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			int count = 0;
			int timingset = 0;

			for each(Condition ^ controlCondition in ControlConditionCollection)
			{
				if (controlCondition->Name->StartsWith("TimingSet_" + count.ToString()))
				{
					count++;
				}
			}

			tl->glob->TimingSetPeriod[siteIndex] = gcnew array<double>(count);
			count = 0;

			for each(Condition ^ controlCondition in ControlConditionCollection)
			{
				if (controlCondition->Name->StartsWith("TimingSet_" + count.ToString()))
				{
					tl->glob->TimingSetPeriod[siteIndex][count] = (double)tf_ControlItem_ConditionCast(controlCondition->Name);
					count++;
				}
			}

			if (tl->glob->TimingSetPeriod[siteIndex]->Length == 0)
			{
				ErrorMessage = "Test Condition[ TimingSet_0 ] is not found";
				throw gcnew Exception(ErrorMessage);
			}

		}
		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [Casting Timing Set Period condition at Load Phase] encountered error [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			tl->WriteToLogger(siteIndex, ErrorMessage);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::CastDpinLevelControlItem(Site ^ site, int siteIndex)
	{
		int ret = 0;
		int Count = 0;
		int DPinset = 0;
		int TotalDPinCondition = 9;
		bool StatusPass = true;

		array<String^>^ DPinCondition = gcnew array<String^>(TotalDPinCondition);
		array<bool>^ DPinConditionExist = gcnew array<bool>(TotalDPinCondition);
		array<Dictionary<String^, double>^>^ DPinConditionVal;
		String^ ErrorMessage = nullptr;

		DPinCondition[0] = "VIH";
		DPinCondition[1] = "VIL";
		DPinCondition[2] = "VOH";
		DPinCondition[3] = "VOL";
		DPinCondition[4] = "IOH";
		DPinCondition[5] = "IOL";
		DPinCondition[6] = "VCH";
		DPinCondition[7] = "VCL";
		DPinCondition[8] = "VTERM";

		try
		{
			ConditionCollection ^ ControlConditionCollection = gcnew ConditionCollection();
			ControlConditionCollection = tf_ControlItem_ConditionList();

			//Get the number of DPin Set
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalDPinCondition; i++)
				{
					DPinConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in ControlConditionCollection)
				{
					for (int i = 0; i < TotalDPinCondition; i++)
					{
						if (controlCondition->Name == (DPinCondition[i] + "_" + DPinset.ToString()))
						{
							DPinConditionExist[i] = true;
							Count++;
							break;
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
							ErrorMessage = "Test Condition [" + DPinCondition[i] + "_" + DPinset.ToString() + "] is not found.";
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
					DPinConditionVal[i]->Add(DPinCondition[j], 999);
					DPinConditionVal[i][DPinCondition[j]] = (double)tf_ControlItem_ConditionCast(DPinCondition[j] + "_" + i.ToString());
				}

				tl->glob->DPinLevelSet[siteIndex]->Add(DPinConditionVal[i]);
			}

		}
		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [Casting DpinLevel condition at Load Phase] encountered error [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			tl->WriteToLogger(siteIndex, ErrorMessage);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::CastPEAttributeControlItem(Site ^ site, int siteIndex)
	{
		int ret = 0;
		int Count = 0;
		int PEAttset = 0;
		int TotalPEAttCondition = 4;
		bool StatusPass = true;
		String ^ ErrorMessage = nullptr;


		array<String^>^ PEAttCondition = gcnew array<String^>(TotalPEAttCondition);
		array<bool>^ PEAttConditionExist = gcnew array<bool>(TotalPEAttCondition);
		array<Dictionary<String^, bool>^>^ PEAttConditionVal;

		PEAttCondition[0] = "InputTermEnable";
		PEAttCondition[1] = "HVEnable";
		PEAttCondition[2] = "ActiveLoadEnable";
		PEAttCondition[3] = "DifferentialComparatorEnable";

		try
		{
			ConditionCollection ^ ControlConditionCollection = gcnew ConditionCollection();
			ControlConditionCollection = tf_ControlItem_ConditionList();

			//Get the number of PEAttset Set
			while (StatusPass)
			{
				//Reset the Variable
				Count = 0;
				for (int i = 0; i < TotalPEAttCondition; i++)
				{
					PEAttConditionExist[i] = false;
				}

				for each(Condition ^ controlCondition in ControlConditionCollection)
				{
					for (int i = 0; i < TotalPEAttCondition; i++)
					{
						if (controlCondition->Name == (PEAttCondition[i] + "_" + PEAttset.ToString()))
						{
							PEAttConditionExist[i] = true;
							Count++;
							break;
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
							ErrorMessage = "Test Condition [" + PEAttCondition[i] + "_" + PEAttset.ToString() + "] is not found.";
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
								ErrorMessage = "Test Condition [" + PEAttCondition[i] + "_" + PEAttset.ToString() + "] is not found.";
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
					PEAttConditionVal[i]->Add(PEAttCondition[j], 999);
					PEAttConditionVal[i][PEAttCondition[j]] = (bool)tf_ControlItem_ConditionCast(PEAttCondition[j] + "_" + i.ToString());
				}
				tl->glob->PEAttributeSet[siteIndex]->Add(PEAttConditionVal[i]);
			}
		}
		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [Casting PEAttribute condition at Load Phase] encountered error [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			tl->WriteToLogger(siteIndex, ErrorMessage);
		}
		return ret;
	}
	int AMB7600SRTestLibrary::GetVectorFiles(Site ^ site)
	{
		int ret = 0;

		try
		{
			if (tl->glob->VectorSetNumber->Count == 0)
			{
				tl->glob->VectorSetNumber = gcnew Dictionary <String ^, int>();
				tl->glob->VectorFileDirectory = tl->glob->tf.RecipeFilePathDirectory + "\\" + "VectorFileFolder";

				int totalVectorFiles = Directory::GetFiles(tl->glob->VectorFileDirectory, "*.vec")->Length;
				array<String^> ^ vectorFiles = gcnew array<String^>(totalVectorFiles);

				vectorFiles = Directory::GetFiles(tl->glob->VectorFileDirectory, "*.vec");

				for (int i = 0; i < totalVectorFiles; i++)
				{
					vectorFiles[i] = vectorFiles[i]->Replace(tl->glob->VectorFileDirectory + "\\", "");
					vectorFiles[i] = vectorFiles[i]->Replace(".vec", "");
					tl->glob->VectorSetNumber->Add(vectorFiles[i], i);
				}
			}

		}

		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DMLoadVectorFiles(Site ^ site, int siteIndex, String ^ ModuleAlias)
	{
		int ret = 0;

		try
		{
			array<int>^ resourceArr = gcnew array<int>(DM_CONST_MAX_VECTOR_SET);

			for (int i = 0; i < DM_CONST_MAX_VECTOR_SET; i++)
			{
				resourceArr[i] = 1;
			}

			CheckError(siteIndex, dm[siteIndex]->DPINVectorResourceAllocation(ModuleAlias, DM_CONST_MAX_VECTOR_SET - 5, resourceArr));

			for each (String ^ s in tl->glob->VectorSetNumber->Keys)
			{
				CheckError(siteIndex, dm[siteIndex]->DPINVecLoad(ModuleAlias, DM_CONST_BIDIRECTIONAL_IO, tl->glob->VectorSetNumber[s], tl->glob->VectorFileDirectory + "\\" + s + ".vec"));
			}

			CheckError(siteIndex, dm[siteIndex]->ConfigureVectorEngineAttribute(ModuleAlias, false, false));

			for (int i = 0; i < tl->glob->TimingSetPeriod[siteIndex]->Length; i++)
			{
				double period = (1 / (2 * tl->glob->TimingSetPeriod[siteIndex][i]));
				CheckError(siteIndex, dm[siteIndex]->DPINPeriod(ModuleAlias, i, period));
			}
		}

		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::VectorFilesInfo(Site ^ site, int siteIndex)
	{
		int ret = 0;
		int count = 0;
		int found = 0;
		int vectorCount = 0;
		String^ ErrorMessage = nullptr;

		try
		{
			for each (String ^ s in tl->glob->VectorSetNumber->Keys)
			{
#pragma region "Read VectorStateFile"

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Check file exist <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				String ^ l_VectorStateFolder_Path = tl->glob->tf.RecipeFilePathDirectory + "\\" + "VectorStateFileFolder";
				String ^ l_VectorFile_Path = l_VectorStateFolder_Path + "\\" + s + ".csv";

				if (!File::Exists(l_VectorFile_Path))
				{
					ErrorMessage = l_VectorFile_Path + " file is not exist.";
					throw gcnew Exception(ErrorMessage);
				}

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get total factor <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				String ^ line = String::Empty;
				int l_Line_Number = 0;
				array<String ^> ^ ArrStr = gcnew array<String ^>(0);
				int l_Factor_Count = 0;
				StreamReader ^ sr = gcnew StreamReader(l_VectorFile_Path);

				while ((line = sr->ReadLine()) != nullptr)
				{
					l_Line_Number++;

					if (l_Line_Number >= 6)
					{
						l_Factor_Count++;
					}
				}

				sr->Close();
				sr = nullptr;
				line = String::Empty;

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Setup Storage <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				int l_MIPI_SetCount = 0;
				array<String^> ^ l_Mode = gcnew array<String^>(l_Factor_Count);
				array<double> ^ l_USID = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegAddr = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData1 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData2 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData3 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData4 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData5 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData6 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData7 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData8 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData9 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData10 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData11 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData12 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData13 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData14 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData15 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData16 = gcnew array<double>(l_Factor_Count);
				array<String^> ^ l_Operation = gcnew array<String^>(l_Factor_Count);
				array<String^> ^ l_Speed = gcnew array<String^>(l_Factor_Count);
				array<int> ^ l_MIPI_RegDataSetCount = gcnew array<int>(l_Factor_Count);

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get VectorStateFile Content <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				array<String ^> ^ Separator = gcnew array<String ^>(1);
				Separator[0] = ",";
				int l_Single_MIPI_Set = 0;
				int l_Read_Operation_Counter = 0;

				bool Read_VectorStateFileExtended_Success = false;
				String ^ Read_VectorStateFileExtended_ErrorMessage = "-";
				bool Read_VectorStateFileBasic_Success = false;
				String ^ Read_VectorStateFileBasic_ErrorMessage = "-";
				bool isFirstExtended = true;
				int Temp_Extended_RegData_Count = 0;
				int Previous_Extended_USID = 0;
				int Previous_Extended_RegAddr = 0;
				String ^ Previous_Extended_Operation = String::Empty;
				String ^ Previous_Extended_Speed = String::Empty;
				String ^ Temp_Mode = String::Empty;
				int Temp_USID = 0;
				int Temp_RegAddr = 0;
				int Temp_RegData = 0;
				int SCLKChannel = 0;
				int SDATAChannel = 0;
				int VectorTimingSet = 0;
				int DM_DPinGroup = 0;
				String ^ Temp_Operation = String::Empty;
				String ^ Temp_Speed = String::Empty;

				l_Line_Number = 0;
				sr = gcnew StreamReader(l_VectorFile_Path);
				while ((line = sr->ReadLine()) != nullptr)
				{
					if (l_Line_Number < 6)
					{
						ArrStr = line->Split(Separator, StringSplitOptions::None);
						if (ArrStr[0] == "DM_DPinGroup")
							tl->glob->VectorFileManager[siteIndex].DM_DPinGroup[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "SCLK_Channel")
							tl->glob->VectorFileManager[siteIndex].SCLKChannel[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "SDATA_Channel")
							tl->glob->VectorFileManager[siteIndex].SDATAChannel[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "VectorTimingSet")
							tl->glob->VectorFileManager[siteIndex].VectorTimingSet[s] = Convert::ToInt32(ArrStr[1]);
					}
					l_Line_Number++;

					if (l_Line_Number >= 6)
					{
						ArrStr = line->Split(Separator, StringSplitOptions::None);

						if ((ArrStr[0] == "EXTENDED") || (ArrStr[0] == "Extended") || (ArrStr[0] == "extended"))
						{
							//Read single vector state file & single line
							API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileExtended_Success, Read_VectorStateFileExtended_ErrorMessage);

							if (isFirstExtended == true) //first occur extended RegAddr no need comapare
							{
								Previous_Extended_USID = Temp_USID;
								Previous_Extended_RegAddr = Temp_RegAddr;
								Previous_Extended_Operation = Temp_Operation;
								Previous_Extended_Speed = Temp_Speed;

								isFirstExtended = false;

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //First set extended start from 1

								Temp_Extended_RegData_Count++;
							}
							else    //The other extended RegAddr need to compare with previous RegAddr
							{
								//If USID & Operation still same
								if ((Previous_Extended_USID == Temp_USID) && (Previous_Extended_Operation == Temp_Operation) && (Previous_Extended_Speed == Temp_Speed))
								{
									//If current RegAddr is the increament of the previous RegAddr, use extended format multiple byte RegData
									if (Temp_RegAddr == (Previous_Extended_RegAddr + 1))
									{
										if (Temp_Extended_RegData_Count == 1)
											l_RegData2[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 2)
											l_RegData3[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 3)
											l_RegData4[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 4)
											l_RegData5[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 5)
											l_RegData6[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 6)
											l_RegData7[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 7)
											l_RegData8[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 8)
											l_RegData9[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 9)
											l_RegData10[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 10)
											l_RegData11[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 11)
											l_RegData12[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 12)
											l_RegData13[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 13)
											l_RegData14[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 14)
											l_RegData15[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 15)
											l_RegData16[l_Single_MIPI_Set] = Temp_RegData;

										//RegDataByteCount ++
										l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = l_MIPI_RegDataSetCount[l_Single_MIPI_Set] + 1;

										//RegData count increament
										Temp_Extended_RegData_Count++;

										//Replace current item to previous item if still continue compare the followng 
										Previous_Extended_USID = Temp_USID;
										Previous_Extended_RegAddr = Temp_RegAddr;
										Previous_Extended_Operation = Temp_Operation;
										Previous_Extended_Speed = Temp_Speed;
									}
									//If USID & Operation still same, but RegAddr diff / no more increament follow the previous sequence
									else
									{
										//Next MIPI set
										l_MIPI_SetCount++;
										l_Single_MIPI_Set++;

										//Reset compare item and ready for next compare
										Temp_Extended_RegData_Count = 0;
										Previous_Extended_USID = Temp_USID;
										Previous_Extended_RegAddr = Temp_RegAddr;
										Previous_Extended_Operation = Temp_Operation;
										Previous_Extended_Speed = Temp_Speed;

										l_Mode[l_Single_MIPI_Set] = Temp_Mode;
										l_USID[l_Single_MIPI_Set] = Temp_USID;
										l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
										l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
										l_Operation[l_Single_MIPI_Set] = Temp_Operation;
										l_Speed[l_Single_MIPI_Set] = Temp_Speed;
										l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1

										Temp_Extended_RegData_Count++;
									}
								}
								//If USID | Operation changed
								else
								{
									//Next MIPI set
									l_MIPI_SetCount++;
									l_Single_MIPI_Set++;

									//Reset compare item and ready for next compare
									Temp_Extended_RegData_Count = 0;
									Previous_Extended_USID = Temp_USID;
									Previous_Extended_RegAddr = Temp_RegAddr;
									Previous_Extended_Operation = Temp_Operation;
									Previous_Extended_Speed = Temp_Speed;

									l_Mode[l_Single_MIPI_Set] = Temp_Mode;
									l_USID[l_Single_MIPI_Set] = Temp_USID;
									l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
									l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
									l_Operation[l_Single_MIPI_Set] = Temp_Operation;
									l_Speed[l_Single_MIPI_Set] = Temp_Speed;
									l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1

									Temp_Extended_RegData_Count++;
								}
							}
						}
						else if ((ArrStr[0] == "BASIC") || (ArrStr[0] == "Basic") || (ArrStr[0] == "basic"))
						{
							//If StateFile first line is Basic operation
							if (isFirstExtended == true)
							{
								isFirstExtended = false;

								//Read single vector state file & single line
								API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileBasic_Success, Read_VectorStateFileBasic_ErrorMessage);

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1
							}
							//The rest of the line that related to Basic operation
							else
							{
								//Next MIPI set
								l_MIPI_SetCount++;
								l_Single_MIPI_Set++;

								//Force reset when change to basic mode
								Temp_Extended_RegData_Count = 0;
								Previous_Extended_USID = 0;
								Previous_Extended_RegAddr = 0;
								Previous_Extended_Operation = "NA";

								//Read single vector state file & single line
								API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileBasic_Success, Read_VectorStateFileBasic_ErrorMessage);

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1
							}
						}
					}
				}

				sr->Close();
				sr = nullptr;
				line = String::Empty;

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get actual MIPI set array size <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				int l_Actual_MIPI_Set_in_VectorFile = 0;
				for (int i = 0; i < l_Factor_Count; i++)
				{
					if (l_USID[i] == 0)
					{
						break;
					}
					else
					{
						l_Actual_MIPI_Set_in_VectorFile++;

						//Get total READ operation in a VectorFile
						if ((l_Operation[i] == "READ") || (l_Operation[i] == "Read") || (l_Operation[i] == "read"))
						{
							if ((l_Mode[i] == "EXTENDED") || (l_Mode[i] == "Extended") || (l_Mode[i] == "extended"))
							{
								l_Read_Operation_Counter += l_MIPI_RegDataSetCount[i];
							}
							else if ((l_Mode[i] == "BASIC") || (l_Mode[i] == "Basic") || (l_Mode[i] == "basic"))
							{
								l_Read_Operation_Counter++;
							}
						}
					}
				}

#pragma endregion

#pragma region "Count Vector Start Read Location"
				tl->glob->VectorFileManager[siteIndex].l_Read_Operation_Counter[s] = l_Read_Operation_Counter;
				array<int> ^ l_Start_Read_Location_Single_VectorFile = gcnew array<int>(l_Read_Operation_Counter);
				array<String^> ^ l_Start_Read_Location_Speed = gcnew array<String^>(l_Read_Operation_Counter);

				l_Single_MIPI_Set = 0;
				int l_Count_AddUp = 0;
				int x = 0;

				int l_BasicCount_BufferLine = 2;
				int l_BasicCount_Parity = 2;
				int l_BasicCount_BusPark = 2;
				int l_BasicCount_SSC = 4;
				int l_BasicCount_SA = 8;
				int l_BasicCount_Operation = 6;
				int l_BasicCount_RegAddr = 10;
				int l_BasicCount_RegData = 16;

				int l_ExtendedCount_BufferLine = 2;
				int l_ExtendedCount_Parity = 2;
				int l_ExtendedCount_BusPark = 2;
				int l_ExtendedCount_SSC = 4;
				int l_ExtendedCount_SA = 8;
				int l_ExtendedCount_Operation = 8;
				int l_ExtendedCount_BC = 8;
				int l_ExtendedCount_RegAddr = 16;
				int l_ExtendedCount_RegData = 16;

				for (l_Single_MIPI_Set = 0; l_Single_MIPI_Set < l_Actual_MIPI_Set_in_VectorFile; l_Single_MIPI_Set++)
				{
					if ((l_Mode[l_Single_MIPI_Set] == "BASIC") || (l_Mode[l_Single_MIPI_Set] == "Basic") || (l_Mode[l_Single_MIPI_Set] == "basic"))
					{
						if ((l_Operation[l_Single_MIPI_Set] == "WRITE") || (l_Operation[l_Single_MIPI_Set] == "Write") || (l_Operation[l_Single_MIPI_Set] == "write"))
						{
							//Record MIPI set total line
							l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_RegData + l_BasicCount_Parity + l_BasicCount_BusPark;

							if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
							{
								//one MIPI set have front and back buffer line
								l_Count_AddUp += (l_BasicCount_BufferLine * 2);
							}
							else
							{
								//last MIPI set only have front buffer line
								l_Count_AddUp += l_BasicCount_BufferLine;
							}
						}
						else if ((l_Operation[l_Single_MIPI_Set] == "READ") || (l_Operation[l_Single_MIPI_Set] == "Read") || (l_Operation[l_Single_MIPI_Set] == "read"))
						{
							if ((l_Speed[l_Single_MIPI_Set] == "FULL") || (l_Speed[l_Single_MIPI_Set] == "Full") || (l_Speed[l_Single_MIPI_Set] == "full"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_BusPark + l_BasicCount_RegData + l_BasicCount_Parity + l_BasicCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - l_BasicCount_RegData - l_BasicCount_Parity - l_BasicCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
								else
								{
									//last MIPI set only have front buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - l_BasicCount_RegData - l_BasicCount_Parity - l_BasicCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
							}
							else if ((l_Speed[l_Single_MIPI_Set] == "HALF") || (l_Speed[l_Single_MIPI_Set] == "Half") || (l_Speed[l_Single_MIPI_Set] == "half"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_BusPark + (l_BasicCount_RegData * 2) + (l_BasicCount_Parity * 2) + l_BasicCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_BasicCount_RegData * 2) - (l_BasicCount_Parity * 2) - l_BasicCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
								else
								{
									//last MIPI set only have front buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_BasicCount_RegData * 2) - (l_BasicCount_Parity * 2) - l_BasicCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
							}
							else
							{
								ErrorMessage = l_Speed[l_Single_MIPI_Set] + " is invalid as only FULL and HALF is supported.";
								throw gcnew Exception(ErrorMessage);
							}
							//tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Speed[x]);
							//tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Single_VectorFile[x]);
							//tl->WriteToLogger(siteIndex, "VectorFile: " + s + " , Read_Location_Single_VectorFile =" + (tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[s]]).ToString() + ",  done");
							//Only ++ when have READ operation
							//x++;
						}
						else
						{
							ErrorMessage = l_Operation[l_Single_MIPI_Set] + " is invalid as only Write and Read operation is supported.";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else if ((l_Mode[l_Single_MIPI_Set] == "EXTENDED") || (l_Mode[l_Single_MIPI_Set] == "Extended") || (l_Mode[l_Single_MIPI_Set] == "extended"))
					{
						if ((l_Operation[l_Single_MIPI_Set] == "WRITE") || (l_Operation[l_Single_MIPI_Set] == "Write") || (l_Operation[l_Single_MIPI_Set] == "write"))
						{
							//Record MIPI set total line
							l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + l_ExtendedCount_BusPark;

							if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
							{
								//one MIPI set have front and back buffer line
								l_Count_AddUp += (l_BasicCount_BufferLine * 2);
							}
							else
							{
								//last MIPI set only have front buffer line
								l_Count_AddUp += l_BasicCount_BufferLine;
							}
						}
						else if ((l_Operation[l_Single_MIPI_Set] == "READ") || (l_Operation[l_Single_MIPI_Set] == "Read") || (l_Operation[l_Single_MIPI_Set] == "read"))
						{
							if ((l_Speed[l_Single_MIPI_Set] == "FULL") || (l_Speed[l_Single_MIPI_Set] == "Full") || (l_Speed[l_Single_MIPI_Set] == "full"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + l_ExtendedCount_BusPark + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + l_ExtendedCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - l_ExtendedCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 18;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
								else
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - l_ExtendedCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 18;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
							}
							else if ((l_Speed[l_Single_MIPI_Set] == "HALF") || (l_Speed[l_Single_MIPI_Set] == "Half") || (l_Speed[l_Single_MIPI_Set] == "half"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + l_ExtendedCount_BusPark + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) + l_ExtendedCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - l_ExtendedCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 36;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
								else
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - l_ExtendedCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 36;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
							}
							else
							{
								ErrorMessage = l_Speed[l_Single_MIPI_Set] + " is invalid as only FULL and HALF is supported.";
								throw gcnew Exception(ErrorMessage);
							}

						}
						else
						{
							ErrorMessage = l_Operation[l_Single_MIPI_Set] + " is invalid as only Write and Read operation is supported.";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else
					{
						ErrorMessage = l_Mode[l_Single_MIPI_Set] + " is invalid as only Basic and Extended is supported.";
						throw gcnew Exception(ErrorMessage);
					}
				}

				tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Speed);
				tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Single_VectorFile);
#pragma endregion
				vectorCount++;
				if (ret != 0) return ret;
			}
		}

		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [LoadVectorFiles at Load Phase] encountered error [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			tl->WriteToLogger(siteIndex, ErrorMessage);
		}

		return ret;
	}

	int AMB7600SRTestLibrary::InitializeDM400eResource(Site ^ site)
	{
		int ret = 0;
		int count = 0;
		int intControlMethod = 0;
		bool IsModuleAlias = false;
		String^ strControlMethod = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);
		array<String^>^moduleAliasRunVector = nullptr;
		array<String ^>^communicationProtocol = nullptr;
		array<array<String^>^>^ moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);
		ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
		testConditionCollection = tf_ControlItem_ConditionList();
		array <bool>^ userDMInit = gcnew array <bool>(tl->glob->tf.NumberOfSites);
		dm = gcnew array<DM ^>(tl->glob->tf.NumberOfSites);

		
#pragma region "DM module at Resource AMAP"
		//Checking any DM module at Resource AMAP
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetDMModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			if (moduleCount[siteIndex] > 0)
			{
				ResourceManagerSett[siteIndex].DM_HardwareStatus = true;
			}
		}
#pragma endregion "DM module at Resource AMAP"
		
#pragma region "DM Initialization"
		//DM Initialization	
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			userDMInit[siteIndex] = false;

			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				tl->WriteToLogger(siteIndex, "Initializing DM400e System Resources...");

				for each(Condition ^ controlMethod in testConditionCollection)
				{
					if (controlMethod->Name->StartsWith("ControlMethod") && (String^)tf_ControlItem_ConditionCast(controlMethod->Name) == "DMCase_DMInit")
					{
						strControlMethod = nullptr;
						intControlMethod = 0;
						strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
						tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
						Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);
						tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
						ControlMethod_Selection(site, siteIndex, intControlMethod, testConditionCollection);
						userDMInit[siteIndex] = true;
					}
				}

				if (userDMInit[siteIndex] == false)
				{
					DM_Init(siteIndex, 3);
				}

				tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] initialized");
			}
		}
#pragma endregion "DM Initialization"	

#pragma region "PowerLineFreq MultiSiteMode"

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
				{
					Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
					IsModuleAlias = false;

					if (((HardwareRsrc->Hierarchy[0]->StartsWith("DM483e") == true) || (HardwareRsrc->Hierarchy[0]->StartsWith("DM482e") == true)) &&
						(ResourceManagerSett[siteIndex].ResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) &&
						(ResourceManagerSett[siteIndex].DMResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false))
					//if ((HardwareRsrc->Hierarchy[0]->StartsWith("DM4") == true)&&
					//	(ResourceManagerSett[siteIndex].ResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) &&
					//	(ResourceManagerSett[siteIndex].DMResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) && Rsrc != "DigitalPin")
					{
						for (count = 0; count < moduleCount[siteIndex]; count++)
						{
							if (Rsrc == moduleAlias[siteIndex][count])
							{
								IsModuleAlias = true;								
							}
						}

						if (IsModuleAlias == false)
						{
							ResourceManagerSett[siteIndex].DMResourceAlias->Add(Rsrc, 1);
						}

						ResourceManagerSett[siteIndex].ResourceAlias->Add(HardwareRsrc->Alias->ToString(), 1);
					}
				}

				//Configure module alias only 
				for (count = 0; count < moduleCount[siteIndex]; count++)
				{
					/* 1. In multi site mode, DLL do lock down resource to prevent other thread from accessing it thus allowing every thread to function properly but it incurs more test time.
					* 2. In single site mode, DLL do not lock down resource so it incurs lesser test time..
					*
					*	0 : DM_CONST_SINGLE_SITE
					*	1 : DM_CONST_MULTI_SITE*/

					tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", DM_CONST_MULTI_SITE)");
					tl->CheckError(siteIndex, dm[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], DM_CONST_MULTI_SITE));

					tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->ConfigurePowerLineFrequency(" + moduleAlias[siteIndex][count] + "," + tl->glob->AWV.PowerLineFreq.ToString() + " )");
					tl->CheckError(siteIndex, dm[siteIndex]->ConfigurePowerLineFrequency(moduleAlias[siteIndex][count], tl->glob->AWV.PowerLineFreq));
				}

				tl->WriteToLogger(siteIndex, "Initializing DM400e Related Global Variables for Previous States...");
				InitDmPinAliasPreviousState(site, siteIndex);//initialize DM modules related global variables to store previous states

			}
			else if (moduleCount[siteIndex] == 0)
			{
				ResourceManagerSett[siteIndex].DM_HardwareStatus = false;
			}
		}

#pragma endregion "PowerLineFreq MultiSiteMode"

#pragma region "Vector"
		//Checking any DM module use to Run Vector
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				////Dpin Level use for Vector or DIO operation mode for DM
				//tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] casting the Dpin Level.");
				//CastDpinLevelControlItem(site, siteIndex);

				//if (CheckingAnyDmModuleRunVector(site, siteIndex, moduleAlias[siteIndex], moduleAliasRunVector, communicationProtocol))
				//{
				//	tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] casting the Timing Set Period.");
				//	CastTimingSetPeriodControlItem(site, siteIndex);

				//	tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] casting the PE Attribute.");
				//	CastPEAttributeControlItem(site, siteIndex);

				//	tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] getting the vector file.");
				//	GetVectorFiles(site);

				//	tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] obtaining the vector files' information.");
				//	VectorFilesInfo(site, siteIndex);

				//	tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] loading vector file to Module Alias.");
				//	for (int i = 0; i < moduleAliasRunVector->Length; i++)
				//	{
				//		DMLoadVectorFiles(site, siteIndex, moduleAliasRunVector[i]);
				//		tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + " ,Module Alias: " + moduleAliasRunVector[i] + " ,Communiation Protocol: " + communicationProtocol[i] + "] is loading vector");
				//	}

				//}

				for each(Condition ^ controlMethod in testConditionCollection)
				{
					if (controlMethod->Name->StartsWith("ControlMethod"))
					{
						strControlMethod = nullptr;
						intControlMethod = 0;
						strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
						tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
						Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);

						if (intControlMethod == DMCase_DMCastDPinLevel || intControlMethod == DMCase_DMCastTimingSetPeriod || intControlMethod == DMCase_DMCastPEAttribute || intControlMethod == DMCase_DMLoadVectorFile)
						{
							tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
							ControlMethod_Selection(site, siteIndex, intControlMethod, testConditionCollection);
						}
					}
				}

			}
		}
#pragma endregion "Vector"

#pragma region "Set Default to PMU Mode"
		//Default Setting: Set all DM Pin Alias to PMU Mode
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].DMResourceAlias)
				{
					DM_ConfigureDigitalPinToPMU(siteIndex, pinAlias->Key, DM_CONST_DVCI, DM_CONST_LOCAL /*DM_CONST_REMOTE*/, DM_CONST_200UA_RANGE, 0.0 V, DM_CONST_PLC);
				}
			}
		}
#pragma endregion "Set Default to PMU Mode"
		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeDM400eResource(Site ^ site)
	{
		int ret = 0;
		int count = 0;
		array<array<String^>^>^ moduleAlias = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);
		moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetDMModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			try
			{
				if (ResourceManagerSett[siteIndex].DM_HardwareStatus == true)
				{
					for (int count = 0; count < moduleCount[siteIndex]; count++)
					{
						tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, dm[siteIndex]->Reset(moduleAlias[siteIndex][count]));

						tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->Close(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, dm[siteIndex]->Close(moduleAlias[siteIndex][count]));

					}
				}
			}
			catch (Exception ^ ex)
			{
				tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
				String^ ErrorMessage = "AMB7600SRTestLibrary:: UninitializeDM400eResource " + "encountered error when performing.";
				tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
				tl->WriteToLogger(siteIndex, ErrorMessage);
			}
		}


		return ret;
	}
	int AMB7600SRTestLibrary::InitializeDM400eResource_ORI(Site ^ site)
	{
		int ret = 0;
		int initOption = 0xf;
		int count = 0;
		bool IsModuleAlias = false;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);
		array<String^>^moduleAliasRunVector = nullptr;
		array<String ^>^communicationProtocol = nullptr;
		array<array<String^>^>^ moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);
		dm = gcnew array<DM ^>(tl->glob->tf.NumberOfSites);

		//	pinGroup : Specifies the pin group to be turned on or activated.
		//	pin Group = 1, DPin group 0 (PIN0 to PIN5) and trigout0
		//	pin Group = 2, DPin group 1 (PIN6 to PIN11) and trigout1
		//	pin Group = 3, DPin group 0 and 1 (PIN0 to PIN11), trigout0 and trigout1
		//	pinGroup setting is for multi site or single site parallel operation purpose.
		//
		//	init_options :
		//	bit[0] = reset the module during initialization.
		//	bit[1] = reset command FIFO during initialization.
		//	bit[2] = reset result FIFO during initialization.
		//	bit[3] = reset lock status during initialization.
		//	bit[5] = To bypass calibration data loading process.	

		//Checking any DM module at Resource AMAP
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetDMModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			if (moduleCount[siteIndex] > 0)
			{
				ResourceManagerSett[siteIndex].DM_HardwareStatus = true;
				tl->WriteToLogger(siteIndex, "Initializing DM400e System Resources...");
			}
		}

		//DM Initialization
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				if (tl->glob->AWV.DMPinGroup == 0)  //Dpin Group 0 and 1 (All)
				{
					dm[siteIndex] = gcnew DM(tl->glob->HardwareProfile, 3, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
				}
				else if (tl->glob->AWV.DMPinGroup == 1)
				{
					if ((tl->glob->tf.TestSite + 1) % 2 != 0) //Odd Techflow Site
					{
						if ((siteIndex + 1) % 2 != 0)  //Odd Test Site
						{
							dm[siteIndex] = gcnew DM(tl->glob->HardwareProfile, 1, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
						}
						else if ((siteIndex + 1) % 2 == 0)  //Even Test Site
						{
							dm[siteIndex] = gcnew DM(tl->glob->HardwareProfile, 2, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
						}
					}
					else if ((tl->glob->tf.TestSite + 1) % 2 == 0) //Even Techflow Site
					{
						if (tl->glob->tf.NumberOfSites == 1)
						{
							dm[siteIndex] = gcnew DM(tl->glob->HardwareProfile, 2, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
						}
						else
						{
							if ((siteIndex + 1) % 2 != 0)  //Odd Test Site
							{
								dm[siteIndex] = gcnew DM(tl->glob->HardwareProfile, 1, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
							}
							else if ((siteIndex + 1) % 2 == 0)  //Even Test Site
							{
								dm[siteIndex] = gcnew DM(tl->glob->HardwareProfile, 2, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
							}
						}
					}
				}

				for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
				{
					Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
					IsModuleAlias = false;

					if ((HardwareRsrc->Hierarchy[0]->StartsWith("DM483e") == true) || (HardwareRsrc->Hierarchy[0]->StartsWith("DM482e") == true) &&
						(ResourceManagerSett[siteIndex].ResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) &&
						(ResourceManagerSett[siteIndex].DMResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false))
					{
						for (count = 0; count < moduleCount[siteIndex]; count++)
						{
							if (Rsrc == moduleAlias[siteIndex][count])
							{
								IsModuleAlias = true;
							}
						}

						if (IsModuleAlias == false)
						{
							ResourceManagerSett[siteIndex].DMResourceAlias->Add(Rsrc, 1);
						}

						ResourceManagerSett[siteIndex].ResourceAlias->Add(HardwareRsrc->Alias->ToString(), 1);
					}
				}

				//Configure module alias only 
				for (count = 0; count < moduleCount[siteIndex]; count++)
				{
					//tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
					//tl->CheckError(siteIndex, dm[siteIndex]->Reset(moduleAlias[siteIndex][count]));

					/* 1. In multi site mode, DLL do lock down resource to prevent other thread from accessing it thus allowing every thread to function properly but it incurs more test time.
					* 2. In single site mode, DLL do not lock down resource so it incurs lesser test time..
					*
					*	0 : DM_CONST_SINGLE_SITE
					*	1 : DM_CONST_MULTI_SITE*/

					tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", DM_CONST_MULTI_SITE)");
					tl->CheckError(siteIndex, dm[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], DM_CONST_MULTI_SITE));

					tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->ConfigurePowerLineFrequency(" + moduleAlias[siteIndex][count] + "," + tl->glob->AWV.PowerLineFreq.ToString() + " )");
					tl->CheckError(siteIndex, dm[siteIndex]->ConfigurePowerLineFrequency(moduleAlias[siteIndex][count], tl->glob->AWV.PowerLineFreq));
				}

				tl->WriteToLogger(siteIndex, "Initializing DM400e Related Global Variables for Previous States...");
				InitDmPinAliasPreviousState(site, siteIndex);//initialize DM modules related global variables to store previous states

				tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] initialized");
			}
			else if (moduleCount[siteIndex] == 0)
			{
				ResourceManagerSett[siteIndex].DM_HardwareStatus = false;
			}
		}

		//Checking any DM module use to Run Vector
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] casting the Dpin Level.");
				CastDpinLevelControlItem(site, siteIndex);

				if (CheckingAnyDmModuleRunVector(site, siteIndex, moduleAlias[siteIndex], moduleAliasRunVector, communicationProtocol))
				{
					tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] casting the Timing Set Period.");
					CastTimingSetPeriodControlItem(site, siteIndex);
					tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] casting the PE Attribute.");
					CastPEAttributeControlItem(site, siteIndex);
					tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] loading vector file.");

					for (int i = 0; i < moduleAliasRunVector->Length; i++)
					{
						LoadVectorFiles(site, siteIndex, moduleAliasRunVector[i]);
						tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + " ,Module Alias: " + moduleAliasRunVector[i] + " ,Communiation Protocol: " + communicationProtocol[i] + "] is loading vector");
					}

					tl->WriteToLogger(siteIndex, "DM[site " + siteIndex + "] done loading vector file.");

				}
			}
		}

		//Default Setting: Set all DM Pin Alias to PMU Mode
		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].DMResourceAlias)
				{
					DM_ConfigureDigitalPinToPMU(siteIndex, pinAlias->Key, DM_CONST_DVCI, DM_CONST_REMOTE, DM_CONST_200UA_RANGE, 0.0 V, DM_CONST_PLC);
				}
			}
		}

		return ret;
	}
	int AMB7600SRTestLibrary::LoadVectorFiles_ORI(Site ^ site, int siteIndex, String ^ ModuleAlias)
	{
		int ret = 0;
		int count = 0;
		int found = 0;
		int vectorCount = 0;
		String^ ErrorMessage = nullptr;

		tl->glob->VectorSetNumber = gcnew Dictionary <String ^, int>();
		tl->glob->VectorFileDirectory = tl->glob->tf.RecipeFilePathDirectory + "\\" + "VectorFileFolder";

		try
		{
			int totalVectorFiles = Directory::GetFiles(tl->glob->VectorFileDirectory, "*.vec")->Length;
			array<String^> ^ vectorFiles = gcnew array<String^>(totalVectorFiles);

			vectorFiles = Directory::GetFiles(tl->glob->VectorFileDirectory, "*.vec");

			for (int i = 0; i < totalVectorFiles; i++)
			{
				vectorFiles[i] = vectorFiles[i]->Replace(tl->glob->VectorFileDirectory + "\\", "");
				vectorFiles[i] = vectorFiles[i]->Replace(".vec", "");
				tl->glob->VectorSetNumber->Add(vectorFiles[i], i);
			}

			array<int>^ resourceArr = gcnew array<int>(DM_CONST_MAX_VECTOR_SET);

			for (int i = 0; i < DM_CONST_MAX_VECTOR_SET; i++)
			{
				resourceArr[i] = 1;
			}

			CheckError(siteIndex, dm[siteIndex]->DPINVectorResourceAllocation(ModuleAlias, DM_CONST_MAX_VECTOR_SET - 5, resourceArr));

			for each (String ^ s in tl->glob->VectorSetNumber->Keys)
			{
				ret = dm[siteIndex]->DPINVecLoad(ModuleAlias, DM_CONST_BIDIRECTIONAL_IO, tl->glob->VectorSetNumber[s], tl->glob->VectorFileDirectory + "\\" + s + ".vec");
#pragma region "Read VectorStateFile"

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Check file exist <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				String ^ l_VectorStateFolder_Path = tl->glob->tf.RecipeFilePathDirectory + "\\" + "VectorStateFileFolder";
				String ^ l_VectorFile_Path = l_VectorStateFolder_Path + "\\" + s + ".csv";

				if (!File::Exists(l_VectorFile_Path))
				{
					ErrorMessage = l_VectorFile_Path + " file is not exist.";
					throw gcnew Exception(ErrorMessage);
				}

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get total factor <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				String ^ line = String::Empty;
				int l_Line_Number = 0;
				array<String ^> ^ ArrStr = gcnew array<String ^>(0);
				int l_Factor_Count = 0;
				StreamReader ^ sr = gcnew StreamReader(l_VectorFile_Path);

				while ((line = sr->ReadLine()) != nullptr)
				{
					l_Line_Number++;

					if (l_Line_Number >= 6)
					{
						l_Factor_Count++;
					}
				}

				sr->Close();
				sr = nullptr;
				line = String::Empty;

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Setup Storage <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				int l_MIPI_SetCount = 0;
				array<String^> ^ l_Mode = gcnew array<String^>(l_Factor_Count);
				array<double> ^ l_USID = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegAddr = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData1 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData2 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData3 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData4 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData5 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData6 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData7 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData8 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData9 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData10 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData11 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData12 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData13 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData14 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData15 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData16 = gcnew array<double>(l_Factor_Count);
				array<String^> ^ l_Operation = gcnew array<String^>(l_Factor_Count);
				array<String^> ^ l_Speed = gcnew array<String^>(l_Factor_Count);
				array<int> ^ l_MIPI_RegDataSetCount = gcnew array<int>(l_Factor_Count);

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get VectorStateFile Content <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				array<String ^> ^ Separator = gcnew array<String ^>(1);
				Separator[0] = ",";
				int l_Single_MIPI_Set = 0;
				int l_Read_Operation_Counter = 0;

				bool Read_VectorStateFileExtended_Success = false;
				String ^ Read_VectorStateFileExtended_ErrorMessage = "-";
				bool Read_VectorStateFileBasic_Success = false;
				String ^ Read_VectorStateFileBasic_ErrorMessage = "-";
				bool isFirstExtended = true;
				int Temp_Extended_RegData_Count = 0;
				int Previous_Extended_USID = 0;
				int Previous_Extended_RegAddr = 0;
				String ^ Previous_Extended_Operation = String::Empty;
				String ^ Previous_Extended_Speed = String::Empty;
				String ^ Temp_Mode = String::Empty;
				int Temp_USID = 0;
				int Temp_RegAddr = 0;
				int Temp_RegData = 0;
				int SCLKChannel = 0;
				int SDATAChannel = 0;
				int VectorTimingSet = 0;
				int DM_DPinGroup = 0;
				String ^ Temp_Operation = String::Empty;
				String ^ Temp_Speed = String::Empty;

				l_Line_Number = 0;
				sr = gcnew StreamReader(l_VectorFile_Path);
				while ((line = sr->ReadLine()) != nullptr)
				{
					if (l_Line_Number < 6)
					{
						ArrStr = line->Split(Separator, StringSplitOptions::None);
						if (ArrStr[0] == "DM_DPinGroup")
							tl->glob->VectorFileManager[siteIndex].DM_DPinGroup[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "SCLK_Channel")
							tl->glob->VectorFileManager[siteIndex].SCLKChannel[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "SDATA_Channel")
							tl->glob->VectorFileManager[siteIndex].SDATAChannel[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "VectorTimingSet")
							tl->glob->VectorFileManager[siteIndex].VectorTimingSet[s] = Convert::ToInt32(ArrStr[1]);
					}
					l_Line_Number++;

					if (l_Line_Number >= 6)
					{
						ArrStr = line->Split(Separator, StringSplitOptions::None);

						if ((ArrStr[0] == "EXTENDED") || (ArrStr[0] == "Extended") || (ArrStr[0] == "extended"))
						{
							//Read single vector state file & single line
							API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileExtended_Success, Read_VectorStateFileExtended_ErrorMessage);

							if (isFirstExtended == true) //first occur extended RegAddr no need comapare
							{
								Previous_Extended_USID = Temp_USID;
								Previous_Extended_RegAddr = Temp_RegAddr;
								Previous_Extended_Operation = Temp_Operation;
								Previous_Extended_Speed = Temp_Speed;

								isFirstExtended = false;

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //First set extended start from 1

								Temp_Extended_RegData_Count++;
							}
							else    //The other extended RegAddr need to compare with previous RegAddr
							{
								//If USID & Operation still same
								if ((Previous_Extended_USID == Temp_USID) && (Previous_Extended_Operation == Temp_Operation) && (Previous_Extended_Speed == Temp_Speed))
								{
									//If current RegAddr is the increament of the previous RegAddr, use extended format multiple byte RegData
									if (Temp_RegAddr == (Previous_Extended_RegAddr + 1))
									{
										if (Temp_Extended_RegData_Count == 1)
											l_RegData2[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 2)
											l_RegData3[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 3)
											l_RegData4[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 4)
											l_RegData5[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 5)
											l_RegData6[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 6)
											l_RegData7[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 7)
											l_RegData8[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 8)
											l_RegData9[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 9)
											l_RegData10[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 10)
											l_RegData11[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 11)
											l_RegData12[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 12)
											l_RegData13[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 13)
											l_RegData14[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 14)
											l_RegData15[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 15)
											l_RegData16[l_Single_MIPI_Set] = Temp_RegData;

										//RegDataByteCount ++
										l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = l_MIPI_RegDataSetCount[l_Single_MIPI_Set] + 1;

										//RegData count increament
										Temp_Extended_RegData_Count++;

										//Replace current item to previous item if still continue compare the followng 
										Previous_Extended_USID = Temp_USID;
										Previous_Extended_RegAddr = Temp_RegAddr;
										Previous_Extended_Operation = Temp_Operation;
										Previous_Extended_Speed = Temp_Speed;
									}
									//If USID & Operation still same, but RegAddr diff / no more increament follow the previous sequence
									else
									{
										//Next MIPI set
										l_MIPI_SetCount++;
										l_Single_MIPI_Set++;

										//Reset compare item and ready for next compare
										Temp_Extended_RegData_Count = 0;
										Previous_Extended_USID = Temp_USID;
										Previous_Extended_RegAddr = Temp_RegAddr;
										Previous_Extended_Operation = Temp_Operation;
										Previous_Extended_Speed = Temp_Speed;

										l_Mode[l_Single_MIPI_Set] = Temp_Mode;
										l_USID[l_Single_MIPI_Set] = Temp_USID;
										l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
										l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
										l_Operation[l_Single_MIPI_Set] = Temp_Operation;
										l_Speed[l_Single_MIPI_Set] = Temp_Speed;
										l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1

										Temp_Extended_RegData_Count++;
									}
								}
								//If USID | Operation changed
								else
								{
									//Next MIPI set
									l_MIPI_SetCount++;
									l_Single_MIPI_Set++;

									//Reset compare item and ready for next compare
									Temp_Extended_RegData_Count = 0;
									Previous_Extended_USID = Temp_USID;
									Previous_Extended_RegAddr = Temp_RegAddr;
									Previous_Extended_Operation = Temp_Operation;
									Previous_Extended_Speed = Temp_Speed;

									l_Mode[l_Single_MIPI_Set] = Temp_Mode;
									l_USID[l_Single_MIPI_Set] = Temp_USID;
									l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
									l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
									l_Operation[l_Single_MIPI_Set] = Temp_Operation;
									l_Speed[l_Single_MIPI_Set] = Temp_Speed;
									l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1

									Temp_Extended_RegData_Count++;
								}
							}
						}
						else if ((ArrStr[0] == "BASIC") || (ArrStr[0] == "Basic") || (ArrStr[0] == "basic"))
						{
							//If StateFile first line is Basic operation
							if (isFirstExtended == true)
							{
								isFirstExtended = false;

								//Read single vector state file & single line
								API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileBasic_Success, Read_VectorStateFileBasic_ErrorMessage);

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1
							}
							//The rest of the line that related to Basic operation
							else
							{
								//Next MIPI set
								l_MIPI_SetCount++;
								l_Single_MIPI_Set++;

								//Force reset when change to basic mode
								Temp_Extended_RegData_Count = 0;
								Previous_Extended_USID = 0;
								Previous_Extended_RegAddr = 0;
								Previous_Extended_Operation = "NA";

								//Read single vector state file & single line
								API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileBasic_Success, Read_VectorStateFileBasic_ErrorMessage);

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1
							}
						}
					}
				}

				sr->Close();
				sr = nullptr;
				line = String::Empty;

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get actual MIPI set array size <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				int l_Actual_MIPI_Set_in_VectorFile = 0;
				for (int i = 0; i < l_Factor_Count; i++)
				{
					if (l_USID[i] == 0)
					{
						break;
					}
					else
					{
						l_Actual_MIPI_Set_in_VectorFile++;

						//Get total READ operation in a VectorFile
						if ((l_Operation[i] == "READ") || (l_Operation[i] == "Read") || (l_Operation[i] == "read"))
						{
							if ((l_Mode[i] == "EXTENDED") || (l_Mode[i] == "Extended") || (l_Mode[i] == "extended"))
							{
								l_Read_Operation_Counter += l_MIPI_RegDataSetCount[i];
							}
							else if ((l_Mode[i] == "BASIC") || (l_Mode[i] == "Basic") || (l_Mode[i] == "basic"))
							{
								l_Read_Operation_Counter++;
							}
						}
					}
				}

#pragma endregion

#pragma region "Count Vector Start Read Location"
				tl->glob->VectorFileManager[siteIndex].l_Read_Operation_Counter[s] = l_Read_Operation_Counter;
				array<int> ^ l_Start_Read_Location_Single_VectorFile = gcnew array<int>(l_Read_Operation_Counter);
				array<String^> ^ l_Start_Read_Location_Speed = gcnew array<String^>(l_Read_Operation_Counter);

				l_Single_MIPI_Set = 0;
				int l_Count_AddUp = 0;
				int x = 0;

				int l_BasicCount_BufferLine = 2;
				int l_BasicCount_Parity = 2;
				int l_BasicCount_BusPark = 2;
				int l_BasicCount_SSC = 4;
				int l_BasicCount_SA = 8;
				int l_BasicCount_Operation = 6;
				int l_BasicCount_RegAddr = 10;
				int l_BasicCount_RegData = 16;

				int l_ExtendedCount_BufferLine = 2;
				int l_ExtendedCount_Parity = 2;
				int l_ExtendedCount_BusPark = 2;
				int l_ExtendedCount_SSC = 4;
				int l_ExtendedCount_SA = 8;
				int l_ExtendedCount_Operation = 8;
				int l_ExtendedCount_BC = 8;
				int l_ExtendedCount_RegAddr = 16;
				int l_ExtendedCount_RegData = 16;

				for (l_Single_MIPI_Set = 0; l_Single_MIPI_Set < l_Actual_MIPI_Set_in_VectorFile; l_Single_MIPI_Set++)
				{
					if ((l_Mode[l_Single_MIPI_Set] == "BASIC") || (l_Mode[l_Single_MIPI_Set] == "Basic") || (l_Mode[l_Single_MIPI_Set] == "basic"))
					{
						if ((l_Operation[l_Single_MIPI_Set] == "WRITE") || (l_Operation[l_Single_MIPI_Set] == "Write") || (l_Operation[l_Single_MIPI_Set] == "write"))
						{
							//Record MIPI set total line
							l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_RegData + l_BasicCount_Parity + l_BasicCount_BusPark;

							if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
							{
								//one MIPI set have front and back buffer line
								l_Count_AddUp += (l_BasicCount_BufferLine * 2);
							}
							else
							{
								//last MIPI set only have front buffer line
								l_Count_AddUp += l_BasicCount_BufferLine;
							}
						}
						else if ((l_Operation[l_Single_MIPI_Set] == "READ") || (l_Operation[l_Single_MIPI_Set] == "Read") || (l_Operation[l_Single_MIPI_Set] == "read"))
						{
							if ((l_Speed[l_Single_MIPI_Set] == "FULL") || (l_Speed[l_Single_MIPI_Set] == "Full") || (l_Speed[l_Single_MIPI_Set] == "full"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_BusPark + l_BasicCount_RegData + l_BasicCount_Parity + l_BasicCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - l_BasicCount_RegData - l_BasicCount_Parity - l_BasicCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
								else
								{
									//last MIPI set only have front buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - l_BasicCount_RegData - l_BasicCount_Parity - l_BasicCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
							}
							else if ((l_Speed[l_Single_MIPI_Set] == "HALF") || (l_Speed[l_Single_MIPI_Set] == "Half") || (l_Speed[l_Single_MIPI_Set] == "half"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_BusPark + (l_BasicCount_RegData * 2) + (l_BasicCount_Parity * 2) + l_BasicCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_BasicCount_RegData * 2) - (l_BasicCount_Parity * 2) - l_BasicCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
								else
								{
									//last MIPI set only have front buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_BasicCount_RegData * 2) - (l_BasicCount_Parity * 2) - l_BasicCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
							}
							else
							{
								ErrorMessage = l_Speed[l_Single_MIPI_Set] + " is invalid as only FULL and HALF is supported.";
								throw gcnew Exception(ErrorMessage);
							}
							//tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Speed[x]);
							//tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Single_VectorFile[x]);
							//tl->WriteToLogger(siteIndex, "VectorFile: " + s + " , Read_Location_Single_VectorFile =" + (tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[s]]).ToString() + ",  done");
							//Only ++ when have READ operation
							//x++;
						}
						else
						{
							ErrorMessage = l_Operation[l_Single_MIPI_Set] + " is invalid as only Write and Read operation is supported.";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else if ((l_Mode[l_Single_MIPI_Set] == "EXTENDED") || (l_Mode[l_Single_MIPI_Set] == "Extended") || (l_Mode[l_Single_MIPI_Set] == "extended"))
					{
						if ((l_Operation[l_Single_MIPI_Set] == "WRITE") || (l_Operation[l_Single_MIPI_Set] == "Write") || (l_Operation[l_Single_MIPI_Set] == "write"))
						{
							//Record MIPI set total line
							l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + l_ExtendedCount_BusPark;

							if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
							{
								//one MIPI set have front and back buffer line
								l_Count_AddUp += (l_BasicCount_BufferLine * 2);
							}
							else
							{
								//last MIPI set only have front buffer line
								l_Count_AddUp += l_BasicCount_BufferLine;
							}
						}
						else if ((l_Operation[l_Single_MIPI_Set] == "READ") || (l_Operation[l_Single_MIPI_Set] == "Read") || (l_Operation[l_Single_MIPI_Set] == "read"))
						{
							if ((l_Speed[l_Single_MIPI_Set] == "FULL") || (l_Speed[l_Single_MIPI_Set] == "Full") || (l_Speed[l_Single_MIPI_Set] == "full"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + l_ExtendedCount_BusPark + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + l_ExtendedCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - l_ExtendedCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 18;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
								else
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - l_ExtendedCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 18;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
							}
							else if ((l_Speed[l_Single_MIPI_Set] == "HALF") || (l_Speed[l_Single_MIPI_Set] == "Half") || (l_Speed[l_Single_MIPI_Set] == "half"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + l_ExtendedCount_BusPark + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) + l_ExtendedCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - l_ExtendedCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 36;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
								else
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - l_ExtendedCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 36;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
							}
							else
							{
								ErrorMessage = l_Speed[l_Single_MIPI_Set] + " is invalid as only FULL and HALF is supported.";
								throw gcnew Exception(ErrorMessage);
							}

						}
						else
						{
							ErrorMessage = l_Operation[l_Single_MIPI_Set] + " is invalid as only Write and Read operation is supported.";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else
					{
						ErrorMessage = l_Mode[l_Single_MIPI_Set] + " is invalid as only Basic and Extended is supported.";
						throw gcnew Exception(ErrorMessage);
					}
				}

				tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Speed);
				tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Single_VectorFile);
#pragma endregion
				vectorCount++;
				if (ret != 0) return ret;
			}

			tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->ConfigureVectorEngineAttribute(" + ModuleAlias + ", false, false)");
			CheckError(siteIndex, dm[siteIndex]->ConfigureVectorEngineAttribute(ModuleAlias, false, false));

			for (int i = 0; i < tl->glob->TimingSetPeriod[siteIndex]->Length; i++)
			{
				double period = (1 / (2 * tl->glob->TimingSetPeriod[siteIndex][i]));

				tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->DPINPeriod(" + ModuleAlias + "," + period.ToString() + " )");
				CheckError(siteIndex, dm[siteIndex]->DPINPeriod(ModuleAlias, i, period));
			}

			tl->WriteToLogger(siteIndex, "Successfully Loaded vector files...");
			tl->WriteToLogger(siteIndex, "Directory: " + tl->glob->VectorFileDirectory + "...");

		}

		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [LoadVectorFiles at Load Phase] encountered error [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			tl->WriteToLogger(siteIndex, ErrorMessage);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::LoadVectorFiles(Site ^ site, int siteIndex, String ^ ModuleAlias)
	{
		int ret = 0;
		int count = 0;
		int found = 0;
		int vectorCount = 0;
		String^ ErrorMessage = nullptr;

		tl->glob->VectorSetNumber = gcnew Dictionary <String ^, int>();
		tl->glob->VectorFileDirectory = tl->glob->tf.RecipeFilePathDirectory + "\\" + "VectorFileFolder";

		try
		{
			int totalVectorFiles = Directory::GetFiles(tl->glob->VectorFileDirectory, "*.vec")->Length;
			array<String^> ^ vectorFiles = gcnew array<String^>(totalVectorFiles);

			vectorFiles = Directory::GetFiles(tl->glob->VectorFileDirectory, "*.vec");

			for (int i = 0; i < totalVectorFiles; i++)
			{
				vectorFiles[i] = vectorFiles[i]->Replace(tl->glob->VectorFileDirectory + "\\", "");
				vectorFiles[i] = vectorFiles[i]->Replace(".vec", "");
				tl->glob->VectorSetNumber->Add(vectorFiles[i], i);
			}

			array<int>^ resourceArr = gcnew array<int>(DM_CONST_MAX_VECTOR_SET);

			for (int i = 0; i < DM_CONST_MAX_VECTOR_SET; i++)
			{
				resourceArr[i] = 1;
			}

			CheckError(siteIndex, dm[siteIndex]->DPINVectorResourceAllocation(ModuleAlias, DM_CONST_MAX_VECTOR_SET - 5, resourceArr));

			for each (String ^ s in tl->glob->VectorSetNumber->Keys)
			{
				ret = dm[siteIndex]->DPINVecLoad(ModuleAlias, DM_CONST_BIDIRECTIONAL_IO, tl->glob->VectorSetNumber[s], tl->glob->VectorFileDirectory + "\\" + s + ".vec");
#pragma region "Read VectorStateFile"

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Check file exist <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				String ^ l_VectorStateFolder_Path = tl->glob->tf.RecipeFilePathDirectory + "\\" + "VectorStateFileFolder";
				String ^ l_VectorFile_Path = l_VectorStateFolder_Path + "\\" + s + ".csv";

				if (!File::Exists(l_VectorFile_Path))
				{
					ErrorMessage = l_VectorFile_Path + " file is not exist.";
					throw gcnew Exception(ErrorMessage);
				}

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get total factor <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				String ^ line = String::Empty;
				int l_Line_Number = 0;
				array<String ^> ^ ArrStr = gcnew array<String ^>(0);
				int l_Factor_Count = 0;
				StreamReader ^ sr = gcnew StreamReader(l_VectorFile_Path);

				while ((line = sr->ReadLine()) != nullptr)
				{
					l_Line_Number++;

					if (l_Line_Number >= 6)
					{
						l_Factor_Count++;
					}
				}

				sr->Close();
				sr = nullptr;
				line = String::Empty;

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Setup Storage <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				int l_MIPI_SetCount = 0;
				array<String^> ^ l_Mode = gcnew array<String^>(l_Factor_Count);
				array<double> ^ l_USID = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegAddr = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData1 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData2 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData3 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData4 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData5 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData6 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData7 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData8 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData9 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData10 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData11 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData12 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData13 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData14 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData15 = gcnew array<double>(l_Factor_Count);
				array<double> ^ l_RegData16 = gcnew array<double>(l_Factor_Count);
				array<String^> ^ l_Operation = gcnew array<String^>(l_Factor_Count);
				array<String^> ^ l_Speed = gcnew array<String^>(l_Factor_Count);
				array<int> ^ l_MIPI_RegDataSetCount = gcnew array<int>(l_Factor_Count);

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get VectorStateFile Content <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				array<String ^> ^ Separator = gcnew array<String ^>(1);
				Separator[0] = ",";
				int l_Single_MIPI_Set = 0;
				int l_Read_Operation_Counter = 0;

				bool Read_VectorStateFileExtended_Success = false;
				String ^ Read_VectorStateFileExtended_ErrorMessage = "-";
				bool Read_VectorStateFileBasic_Success = false;
				String ^ Read_VectorStateFileBasic_ErrorMessage = "-";
				bool isFirstExtended = true;
				int Temp_Extended_RegData_Count = 0;
				int Previous_Extended_USID = 0;
				int Previous_Extended_RegAddr = 0;
				String ^ Previous_Extended_Operation = String::Empty;
				String ^ Previous_Extended_Speed = String::Empty;
				String ^ Temp_Mode = String::Empty;
				int Temp_USID = 0;
				int Temp_RegAddr = 0;
				int Temp_RegData = 0;
				int SCLKChannel = 0;
				int SDATAChannel = 0;
				int VectorTimingSet = 0;
				int DM_DPinGroup = 0;
				String ^ Temp_Operation = String::Empty;
				String ^ Temp_Speed = String::Empty;

				l_Line_Number = 0;
				sr = gcnew StreamReader(l_VectorFile_Path);
				while ((line = sr->ReadLine()) != nullptr)
				{
					if (l_Line_Number < 6)
					{
						ArrStr = line->Split(Separator, StringSplitOptions::None);
						if (ArrStr[0] == "DM_DPinGroup")
							tl->glob->VectorFileManager[siteIndex].DM_DPinGroup[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "SCLK_Channel")
							tl->glob->VectorFileManager[siteIndex].SCLKChannel[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "SDATA_Channel")
							tl->glob->VectorFileManager[siteIndex].SDATAChannel[s] = Convert::ToInt32(ArrStr[1]);
						if (ArrStr[0] == "VectorTimingSet")
							tl->glob->VectorFileManager[siteIndex].VectorTimingSet[s] = Convert::ToInt32(ArrStr[1]);
					}
					l_Line_Number++;

					if (l_Line_Number >= 6)
					{
						ArrStr = line->Split(Separator, StringSplitOptions::None);

						if ((ArrStr[0] == "EXTENDED") || (ArrStr[0] == "Extended") || (ArrStr[0] == "extended"))
						{
							//Read single vector state file & single line
							API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileExtended_Success, Read_VectorStateFileExtended_ErrorMessage);

							if (isFirstExtended == true) //first occur extended RegAddr no need comapare
							{
								Previous_Extended_USID = Temp_USID;
								Previous_Extended_RegAddr = Temp_RegAddr;
								Previous_Extended_Operation = Temp_Operation;
								Previous_Extended_Speed = Temp_Speed;

								isFirstExtended = false;

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //First set extended start from 1

								Temp_Extended_RegData_Count++;
							}
							else    //The other extended RegAddr need to compare with previous RegAddr
							{
								//If USID & Operation still same
								if ((Previous_Extended_USID == Temp_USID) && (Previous_Extended_Operation == Temp_Operation) && (Previous_Extended_Speed == Temp_Speed))
								{
									//If current RegAddr is the increament of the previous RegAddr, use extended format multiple byte RegData
									if (Temp_RegAddr == (Previous_Extended_RegAddr + 1))
									{
										if (Temp_Extended_RegData_Count == 1)
											l_RegData2[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 2)
											l_RegData3[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 3)
											l_RegData4[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 4)
											l_RegData5[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 5)
											l_RegData6[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 6)
											l_RegData7[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 7)
											l_RegData8[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 8)
											l_RegData9[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 9)
											l_RegData10[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 10)
											l_RegData11[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 11)
											l_RegData12[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 12)
											l_RegData13[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 13)
											l_RegData14[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 14)
											l_RegData15[l_Single_MIPI_Set] = Temp_RegData;
										else if (Temp_Extended_RegData_Count == 15)
											l_RegData16[l_Single_MIPI_Set] = Temp_RegData;

										//RegDataByteCount ++
										l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = l_MIPI_RegDataSetCount[l_Single_MIPI_Set] + 1;

										//RegData count increament
										Temp_Extended_RegData_Count++;

										//Replace current item to previous item if still continue compare the followng 
										Previous_Extended_USID = Temp_USID;
										Previous_Extended_RegAddr = Temp_RegAddr;
										Previous_Extended_Operation = Temp_Operation;
										Previous_Extended_Speed = Temp_Speed;
									}
									//If USID & Operation still same, but RegAddr diff / no more increament follow the previous sequence
									else
									{
										//Next MIPI set
										l_MIPI_SetCount++;
										l_Single_MIPI_Set++;

										//Reset compare item and ready for next compare
										Temp_Extended_RegData_Count = 0;
										Previous_Extended_USID = Temp_USID;
										Previous_Extended_RegAddr = Temp_RegAddr;
										Previous_Extended_Operation = Temp_Operation;
										Previous_Extended_Speed = Temp_Speed;

										l_Mode[l_Single_MIPI_Set] = Temp_Mode;
										l_USID[l_Single_MIPI_Set] = Temp_USID;
										l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
										l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
										l_Operation[l_Single_MIPI_Set] = Temp_Operation;
										l_Speed[l_Single_MIPI_Set] = Temp_Speed;
										l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1

										Temp_Extended_RegData_Count++;
									}
								}
								//If USID | Operation changed
								else
								{
									//Next MIPI set
									l_MIPI_SetCount++;
									l_Single_MIPI_Set++;

									//Reset compare item and ready for next compare
									Temp_Extended_RegData_Count = 0;
									Previous_Extended_USID = Temp_USID;
									Previous_Extended_RegAddr = Temp_RegAddr;
									Previous_Extended_Operation = Temp_Operation;
									Previous_Extended_Speed = Temp_Speed;

									l_Mode[l_Single_MIPI_Set] = Temp_Mode;
									l_USID[l_Single_MIPI_Set] = Temp_USID;
									l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
									l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
									l_Operation[l_Single_MIPI_Set] = Temp_Operation;
									l_Speed[l_Single_MIPI_Set] = Temp_Speed;
									l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1

									Temp_Extended_RegData_Count++;
								}
							}
						}
						else if ((ArrStr[0] == "BASIC") || (ArrStr[0] == "Basic") || (ArrStr[0] == "basic"))
						{
							//If StateFile first line is Basic operation
							if (isFirstExtended == true)
							{
								isFirstExtended = false;

								//Read single vector state file & single line
								API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileBasic_Success, Read_VectorStateFileBasic_ErrorMessage);

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1
							}
							//The rest of the line that related to Basic operation
							else
							{
								//Next MIPI set
								l_MIPI_SetCount++;
								l_Single_MIPI_Set++;

								//Force reset when change to basic mode
								Temp_Extended_RegData_Count = 0;
								Previous_Extended_USID = 0;
								Previous_Extended_RegAddr = 0;
								Previous_Extended_Operation = "NA";

								//Read single vector state file & single line
								API_Read_Single_VectorStateFile_SingleLine(ArrStr, Temp_Mode, Temp_USID, Temp_RegAddr, Temp_RegData, Temp_Operation, Temp_Speed, Read_VectorStateFileBasic_Success, Read_VectorStateFileBasic_ErrorMessage);

								l_Mode[l_Single_MIPI_Set] = Temp_Mode;
								l_USID[l_Single_MIPI_Set] = Temp_USID;
								l_RegAddr[l_Single_MIPI_Set] = Temp_RegAddr;
								l_RegData1[l_Single_MIPI_Set] = Temp_RegData;
								l_Operation[l_Single_MIPI_Set] = Temp_Operation;
								l_Speed[l_Single_MIPI_Set] = Temp_Speed;
								l_MIPI_RegDataSetCount[l_Single_MIPI_Set] = 1;    //new MIPI set RegDataByteCount strat from 1
							}
						}
					}
				}

				sr->Close();
				sr = nullptr;
				line = String::Empty;

				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Get actual MIPI set array size <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
				int l_Actual_MIPI_Set_in_VectorFile = 0;
				for (int i = 0; i < l_Factor_Count; i++)
				{
					if (l_USID[i] == 0)
					{
						break;
					}
					else
					{
						l_Actual_MIPI_Set_in_VectorFile++;

						//Get total READ operation in a VectorFile
						if ((l_Operation[i] == "READ") || (l_Operation[i] == "Read") || (l_Operation[i] == "read"))
						{
							if ((l_Mode[i] == "EXTENDED") || (l_Mode[i] == "Extended") || (l_Mode[i] == "extended"))
							{
								l_Read_Operation_Counter += l_MIPI_RegDataSetCount[i];
							}
							else if ((l_Mode[i] == "BASIC") || (l_Mode[i] == "Basic") || (l_Mode[i] == "basic"))
							{
								l_Read_Operation_Counter++;
							}
						}
					}
				}

#pragma endregion

#pragma region "Count Vector Start Read Location"
				tl->glob->VectorFileManager[siteIndex].l_Read_Operation_Counter[s] = l_Read_Operation_Counter;
				array<int> ^ l_Start_Read_Location_Single_VectorFile = gcnew array<int>(l_Read_Operation_Counter);
				array<String^> ^ l_Start_Read_Location_Speed = gcnew array<String^>(l_Read_Operation_Counter);

				l_Single_MIPI_Set = 0;
				int l_Count_AddUp = 0;
				int x = 0;

				int l_BasicCount_BufferLine = 2;
				int l_BasicCount_Parity = 2;
				int l_BasicCount_BusPark = 2;
				int l_BasicCount_SSC = 4;
				int l_BasicCount_SA = 8;
				int l_BasicCount_Operation = 6;
				int l_BasicCount_RegAddr = 10;
				int l_BasicCount_RegData = 16;

				int l_ExtendedCount_BufferLine = 2;
				int l_ExtendedCount_Parity = 2;
				int l_ExtendedCount_BusPark = 2;
				int l_ExtendedCount_SSC = 4;
				int l_ExtendedCount_SA = 8;
				int l_ExtendedCount_Operation = 8;
				int l_ExtendedCount_BC = 8;
				int l_ExtendedCount_RegAddr = 16;
				int l_ExtendedCount_RegData = 16;

				for (l_Single_MIPI_Set = 0; l_Single_MIPI_Set < l_Actual_MIPI_Set_in_VectorFile; l_Single_MIPI_Set++)
				{
					if ((l_Mode[l_Single_MIPI_Set] == "BASIC") || (l_Mode[l_Single_MIPI_Set] == "Basic") || (l_Mode[l_Single_MIPI_Set] == "basic"))
					{
						if ((l_Operation[l_Single_MIPI_Set] == "WRITE") || (l_Operation[l_Single_MIPI_Set] == "Write") || (l_Operation[l_Single_MIPI_Set] == "write"))
						{
							//Record MIPI set total line
							l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_RegData + l_BasicCount_Parity + l_BasicCount_BusPark;

							if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
							{
								//one MIPI set have front and back buffer line
								l_Count_AddUp += (l_BasicCount_BufferLine * 2);
							}
							else
							{
								//last MIPI set only have front buffer line
								l_Count_AddUp += l_BasicCount_BufferLine;
							}
						}
						else if ((l_Operation[l_Single_MIPI_Set] == "READ") || (l_Operation[l_Single_MIPI_Set] == "Read") || (l_Operation[l_Single_MIPI_Set] == "read"))
						{
							if ((l_Speed[l_Single_MIPI_Set] == "FULL") || (l_Speed[l_Single_MIPI_Set] == "Full") || (l_Speed[l_Single_MIPI_Set] == "full"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_BusPark + l_BasicCount_RegData + l_BasicCount_Parity + l_BasicCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - l_BasicCount_RegData - l_BasicCount_Parity - l_BasicCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
								else
								{
									//last MIPI set only have front buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - l_BasicCount_RegData - l_BasicCount_Parity - l_BasicCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
							}
							else if ((l_Speed[l_Single_MIPI_Set] == "HALF") || (l_Speed[l_Single_MIPI_Set] == "Half") || (l_Speed[l_Single_MIPI_Set] == "half"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_BasicCount_SSC + l_BasicCount_SA + l_BasicCount_Operation + l_BasicCount_RegAddr + l_BasicCount_Parity + l_BasicCount_BusPark + (l_BasicCount_RegData * 2) + (l_BasicCount_Parity * 2) + l_BasicCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_BasicCount_RegData * 2) - (l_BasicCount_Parity * 2) - l_BasicCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
								else
								{
									//last MIPI set only have front buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_BasicCount_RegData * 2) - (l_BasicCount_Parity * 2) - l_BasicCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
								}
							}
							else
							{
								ErrorMessage = l_Speed[l_Single_MIPI_Set] + " is invalid as only FULL and HALF is supported.";
								throw gcnew Exception(ErrorMessage);
							}
							//tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Speed[x]);
							//tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Single_VectorFile[x]);
							//tl->WriteToLogger(siteIndex, "VectorFile: " + s + " , Read_Location_Single_VectorFile =" + (tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[s]]).ToString() + ",  done");
							//Only ++ when have READ operation
							//x++;
						}
						else
						{
							ErrorMessage = l_Operation[l_Single_MIPI_Set] + " is invalid as only Write and Read operation is supported.";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else if ((l_Mode[l_Single_MIPI_Set] == "EXTENDED") || (l_Mode[l_Single_MIPI_Set] == "Extended") || (l_Mode[l_Single_MIPI_Set] == "extended"))
					{
						if ((l_Operation[l_Single_MIPI_Set] == "WRITE") || (l_Operation[l_Single_MIPI_Set] == "Write") || (l_Operation[l_Single_MIPI_Set] == "write"))
						{
							//Record MIPI set total line
							l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + l_ExtendedCount_BusPark;

							if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
							{
								//one MIPI set have front and back buffer line
								l_Count_AddUp += (l_BasicCount_BufferLine * 2);
							}
							else
							{
								//last MIPI set only have front buffer line
								l_Count_AddUp += l_BasicCount_BufferLine;
							}
						}
						else if ((l_Operation[l_Single_MIPI_Set] == "READ") || (l_Operation[l_Single_MIPI_Set] == "Read") || (l_Operation[l_Single_MIPI_Set] == "read"))
						{
							if ((l_Speed[l_Single_MIPI_Set] == "FULL") || (l_Speed[l_Single_MIPI_Set] == "Full") || (l_Speed[l_Single_MIPI_Set] == "full"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + l_ExtendedCount_BusPark + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) + l_ExtendedCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - l_ExtendedCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 18;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
								else
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set]) - l_ExtendedCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 18;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
							}
							else if ((l_Speed[l_Single_MIPI_Set] == "HALF") || (l_Speed[l_Single_MIPI_Set] == "Half") || (l_Speed[l_Single_MIPI_Set] == "half"))
							{
								//Record MIPI set total line
								l_Count_AddUp += l_ExtendedCount_SSC + l_ExtendedCount_SA + l_ExtendedCount_Operation + l_ExtendedCount_BC + l_ExtendedCount_Parity + l_ExtendedCount_RegAddr + l_ExtendedCount_Parity + l_ExtendedCount_BusPark + (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) + (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) + l_ExtendedCount_BusPark;

								if (l_Single_MIPI_Set < (l_Actual_MIPI_Set_in_VectorFile - 1))
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += (l_BasicCount_BufferLine * 2);
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - l_ExtendedCount_BusPark - l_BasicCount_BufferLine + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 36;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
								else
								{
									//one MIPI set have front and back buffer line
									l_Count_AddUp += l_BasicCount_BufferLine;
									//Record Start Read Location
									l_Start_Read_Location_Single_VectorFile[x] = l_Count_AddUp - (l_ExtendedCount_RegData * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - (l_ExtendedCount_Parity * l_MIPI_RegDataSetCount[l_Single_MIPI_Set] * 2) - l_ExtendedCount_BusPark + 1;
									//Record Start Read Location's Speed
									l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
									x++;
									//For multiple RegData set
									for (int y = 0; y < (l_MIPI_RegDataSetCount[l_Single_MIPI_Set] - 1); y++)
									{
										l_Start_Read_Location_Single_VectorFile[x] = l_Start_Read_Location_Single_VectorFile[x - 1] + 36;
										//Record Start Read Location's Speed
										l_Start_Read_Location_Speed[x] = l_Speed[l_Single_MIPI_Set];
										x++;
									}
								}
							}
							else
							{
								ErrorMessage = l_Speed[l_Single_MIPI_Set] + " is invalid as only FULL and HALF is supported.";
								throw gcnew Exception(ErrorMessage);
							}

						}
						else
						{
							ErrorMessage = l_Operation[l_Single_MIPI_Set] + " is invalid as only Write and Read operation is supported.";
							throw gcnew Exception(ErrorMessage);
						}
					}
					else
					{
						ErrorMessage = l_Mode[l_Single_MIPI_Set] + " is invalid as only Basic and Extended is supported.";
						throw gcnew Exception(ErrorMessage);
					}
				}

				tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Speed);
				tl->glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile->Add(tl->glob->VectorSetNumber[s], l_Start_Read_Location_Single_VectorFile);
#pragma endregion
				vectorCount++;
				if (ret != 0) return ret;
			}

			tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->ConfigureVectorEngineAttribute(" + ModuleAlias + ", false, false)");
			CheckError(siteIndex, dm[siteIndex]->ConfigureVectorEngineAttribute(ModuleAlias, false, false));

			for (int i = 0; i < tl->glob->TimingSetPeriod[siteIndex]->Length; i++)
			{
				double period = (1 / (2 * tl->glob->TimingSetPeriod[siteIndex][i]));

				tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->DPINPeriod(" + ModuleAlias + "," + period.ToString() + " )");
				CheckError(siteIndex, dm[siteIndex]->DPINPeriod(ModuleAlias, i, period));
			}

			tl->WriteToLogger(siteIndex, "Successfully Loaded vector files...");
			tl->WriteToLogger(siteIndex, "Directory: " + tl->glob->VectorFileDirectory + "...");

		}

		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [LoadVectorFiles at Load Phase] encountered error [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			tl->WriteToLogger(siteIndex, ErrorMessage);
		}

		return ret;
	}

	// DM400e Helper Function 
	int AMB7600SRTestLibrary::DM_Init(int testSite, int dpinGroup)
	{
		int ret = 0;

		dm[testSite] = gcnew DM(tl->glob->HardwareProfile, dpinGroup, tl->glob->tf.TestHead, testSite, tl->glob->AWV.Offline, tl->glob->AWV.DMInitOption);

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MIPIWriteVector(int testSite, String ^ moduleAlias, String ^ vectorFileName)
	{
		int ret = 0;
		int l_count = 0;
		int moduleStatus = 999;

		if (tl->glob->VectorSetNumber->ContainsKey(vectorFileName))
		{
			while ((l_count <= 10000) && (moduleStatus != DM_CONST_VEC_ENG_STAT_DONE))
			{
				moduleStatus = 999;

				CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(moduleAlias, moduleStatus));
				if (ret != 0) return ret; //exit if AcquireVecEngineStatus returns an error code 

				if ((moduleStatus == DM_CONST_VEC_ENG_STAT_DONE))
				{
					CheckError(testSite, dm[testSite]->RunVector(moduleAlias, tl->glob->VectorSetNumber[vectorFileName]));
					if (ret != 0) return ret; //exit if RunVector returns an error code
					break;
				}

				//tracerLogger->WriteToTracer("Site" + testSite.ToString(), "\n Wait for DM Status Done Count: " + l_count.ToString());
				util->WaitSecond(1.0 uS);
				l_count++;

				if (l_count > 10000)	ret += l_count;
			}
		}

		return ret;
	}
	int AMB7600SRTestLibrary::API_Read_Single_VectorStateFile_SingleLine(array<String^> ^  Reader_Value, String^ % Mode, int % USID, int % RegAddr, int % RegData, String^ % Operation, String^ % Speed, bool % Read_VectorStateFileBasic_Success, String^ % Read_VectorStateFileBasic_ErrorMessage)
	{
		int ret = 0;

		Mode = String::Empty;
		USID = 999;
		RegAddr = 999;
		RegData = 999;
		Operation = String::Empty;
		Speed = String::Empty;
		Read_VectorStateFileBasic_Success = false;
		Read_VectorStateFileBasic_ErrorMessage = "Unknown Error";

		//Mode
		if (!String::IsNullOrEmpty(Reader_Value[0]))
		{
			Mode = Reader_Value[0];
			Read_VectorStateFileBasic_Success = true;
		}
		else
		{
			Read_VectorStateFileBasic_Success = false;
			Read_VectorStateFileBasic_ErrorMessage = "Mode cannot leave empty";
			goto Read_VectorStateFileBasic_Fail;
		}

		//USID
		if (!String::IsNullOrEmpty(Reader_Value[1]))
		{
			USID = Convert::ToInt32(Reader_Value[1], 16);
			Read_VectorStateFileBasic_Success = true;
		}
		else
		{
			Read_VectorStateFileBasic_Success = false;
			Read_VectorStateFileBasic_ErrorMessage = "USID cannot leave empty";
			goto Read_VectorStateFileBasic_Fail;
		}

		//RegAddr
		if (!String::IsNullOrEmpty(Reader_Value[2]))
		{
			RegAddr = Convert::ToInt32(Reader_Value[2], 16);
			Read_VectorStateFileBasic_Success = true;
		}
		else
		{
			Read_VectorStateFileBasic_Success = false;
			Read_VectorStateFileBasic_ErrorMessage = "RegAddr cannot leave empty";
			goto Read_VectorStateFileBasic_Fail;
		}

		//RegData
		if (!String::IsNullOrEmpty(Reader_Value[3]))
		{
			RegData = Convert::ToInt32(Reader_Value[3], 16);
			Read_VectorStateFileBasic_Success = true;
			//MIPI_RegDataSetCount[j] = 1;
		}
		else
		{
			Read_VectorStateFileBasic_Success = false;
			Read_VectorStateFileBasic_ErrorMessage = "RegData cannot leave empty";
			goto Read_VectorStateFileBasic_Fail;
		}

		//Operation
		if (!String::IsNullOrEmpty(Reader_Value[4]))
		{
			Operation = Reader_Value[4];
			Read_VectorStateFileBasic_Success = true;
		}
		else
		{
			Read_VectorStateFileBasic_Success = false;
			Read_VectorStateFileBasic_ErrorMessage = "Operation cannot leave empty";
			goto Read_VectorStateFileBasic_Fail;
		}

		//Speed
		if (!String::IsNullOrEmpty(Reader_Value[5]))
		{
			Speed = Reader_Value[5];
			Read_VectorStateFileBasic_Success = true;
		}
		else
		{
			Read_VectorStateFileBasic_Success = false;
			Read_VectorStateFileBasic_ErrorMessage = "Speed cannot leave empty";
			goto Read_VectorStateFileBasic_Fail;
		}

	Read_VectorStateFileBasic_Fail:

		for (int i = 0; i < Reader_Value->Length; i++)
		{
			Reader_Value[i] = String::Empty;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::API_MIPI_Vector_Read(Site ^ site, int testSite, String ^ dataPinAlias, String ^ DM_Module_Alias, double channelInputDelay, String ^ VectorFileName, bool sweepOperation, array<int> ^ % ReadHistoryRam_Data, int % VectorFailCount, int % VectorFirstFail)
	{
		int ret = 0;

		int l_count = 0;
		int moduleStatus = 999;

		CheckError(testSite, dm[testSite]->ConfigureInputChannelDelay(dataPinAlias, channelInputDelay));

#pragma region "Run Vector File"
		if (tl->glob->VectorSetNumber->ContainsKey(VectorFileName))
		{
			while ((l_count <= 10000) && (moduleStatus != DM_CONST_VEC_ENG_STAT_DONE))
			{
				moduleStatus = 999;

				CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(DM_Module_Alias, moduleStatus));
				if (ret != 0) return ret; //exit if AcquireVecEngineStatus returns an error code 

				if ((moduleStatus == DM_CONST_VEC_ENG_STAT_DONE))
				{
					CheckError(testSite, dm[testSite]->RunVector(DM_Module_Alias, tl->glob->VectorSetNumber[VectorFileName]));
					if (ret != 0) return ret; //exit if RunVector returns an error code
					break;
				}

				util->WaitSecond(1.0 uS);
				l_count++;

				if (l_count > 10000)	ret += l_count;
			}
		}
#pragma endregion

#pragma region "ReadHistoryRam & ReadVectorFailCount"

		int l_DM_Status = 999;
		int l_ReadBack_Vector_Count = 0;	//Full: 16 | Half: 32
		int l_Retry_Counter = 0;
		int l_Counter = 0;
		int l_ReaddData_Raw_Int = 0;
		int l_VectorFailCount = 999;
		int l_VectorFirstFail = 0;
		int l_totalDataCount = 0;
		ReadHistoryRam_Data = gcnew array<int>(tl->glob->VectorFileManager[testSite].l_Read_Operation_Counter[VectorFileName]);

		//Initial data variable
		for (int i = 0; i < tl->glob->VectorFileManager[testSite].l_Read_Operation_Counter[VectorFileName]; i++)
		{
			ReadHistoryRam_Data[i] = 0;
		}

		if (tl->glob->AWV.Debug == 0)
		{
			//Setup array size to store ReadBack data
			array<int>^ l_ReadData_Raw_Array;
			array<int>^ l_ReadData_Array;
			//Execute ReadHistoryRam for each StartReadLocation
			for (int z = 0; z < tl->glob->VectorFileManager[testSite].l_Read_Operation_Counter[VectorFileName]; z++)
			{
				//Select ReadBack vector count
				if ((tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "FULL") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "Full") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "full"))
				{
					l_ReadBack_Vector_Count = 16;
					l_totalDataCount = 2;
				}
				else if ((tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "HALF") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "Half") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "half"))
				{
					l_ReadBack_Vector_Count = 32;
					l_totalDataCount = 4;
				}
				else
					l_ReadBack_Vector_Count = 0;

				//Setup array size to store ReadBack data
				l_ReadData_Raw_Array = gcnew array<int>(l_ReadBack_Vector_Count);
				l_ReadData_Array = gcnew array<int>(l_ReadBack_Vector_Count / 2);

				//ReadHistoryRam
				if (tl->glob->VectorSetNumber->ContainsKey(VectorFileName))
				{
					l_Retry_Counter = 0;
					l_DM_Status = 999;
					l_Counter = 0;
					while ((l_Retry_Counter <= 1000) && (l_DM_Status != DM_CONST_VEC_ENG_STAT_DONE))
					{
						CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(DM_Module_Alias, l_DM_Status));
						if (ret != 0) return ret;

						if ((l_DM_Status == DM_CONST_VEC_ENG_STAT_DONE))
						{
							tl->WriteToLogger(testSite, ">> ReadLocation =" + (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[VectorFileName]][z]).ToString() + ",  done");

							CheckError(testSite, dm[testSite]->ReadHistoryRam(DM_Module_Alias, l_ReadBack_Vector_Count, tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[VectorFileName]][z], tl->glob->VectorSetNumber[VectorFileName], l_ReadData_Raw_Array));

							if (ret != 0) return ret;
							break;
						}
						l_Retry_Counter++;

						if (l_Retry_Counter > 1000)	ret += l_Retry_Counter;
					}

					Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(dataPinAlias)[0];  //Get Pin Resource Name
					int dataPinAliasvalue = 999;
					dataPinAliasvalue = Convert::ToInt32(HardwareRsrc->Value);

					for (int l_ReadData_Count = 0; l_ReadData_Count < (l_ReadBack_Vector_Count / l_totalDataCount/*2*/); l_ReadData_Count++)
					{
						l_ReadData_Array[l_ReadData_Count] = (l_ReadData_Raw_Array[l_Counter] >> (dataPinAliasvalue * 2)) & 0x000003;

						if (l_ReadData_Array[l_ReadData_Count] == 2) //undefined received (bin 10)
						{
							ReadHistoryRam_Data[z] = 999;
							goto ReadHistoryRam_Fail;
						}

						l_ReaddData_Raw_Int += l_ReadData_Array[l_ReadData_Count] << ((l_ReadBack_Vector_Count / l_totalDataCount/*2*/) - (l_ReadData_Count + 1));
						l_Counter += l_totalDataCount/*2*/;
					}
					ReadHistoryRam_Data[z] = l_ReaddData_Raw_Int;
					l_ReaddData_Raw_Int = 0;
				}
				else
				{
					return ER_CONST_FILE_NOT_FOUND;
				}
			}
		}
		else
		{

			if (sweepOperation == true)
			{
				//Setup array size to store ReadBack data
				array<int>^ l_ReadData_Raw_Array;
				array<int>^ l_ReadData_Array;
				//Execute ReadHistoryRam for each StartReadLocation
				for (int z = 0; z < tl->glob->VectorFileManager[testSite].l_Read_Operation_Counter[VectorFileName]; z++)
				{
					//Select ReadBack vector count
					if ((tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "FULL") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "Full") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "full"))
					{
						l_ReadBack_Vector_Count = 16;
						l_totalDataCount = 2;
					}
					else if ((tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "HALF") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "Half") || (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Speed[tl->glob->VectorSetNumber[VectorFileName]][z] == "half"))
					{
						l_ReadBack_Vector_Count = 32;
						l_totalDataCount = 4;
					}
					else
						l_ReadBack_Vector_Count = 0;

					//Setup array size to store ReadBack data
					l_ReadData_Raw_Array = gcnew array<int>(l_ReadBack_Vector_Count);
					l_ReadData_Array = gcnew array<int>(l_ReadBack_Vector_Count / 2);

					//ReadHistoryRam
					if (tl->glob->VectorSetNumber->ContainsKey(VectorFileName))
					{
						l_Retry_Counter = 0;
						l_DM_Status = 999;
						l_Counter = 0;
						while ((l_Retry_Counter <= 1000) && (l_DM_Status != DM_CONST_VEC_ENG_STAT_DONE))
						{
							CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(DM_Module_Alias, l_DM_Status));
							if (ret != 0) return ret;

							if ((l_DM_Status == DM_CONST_VEC_ENG_STAT_DONE))
							{
								tl->WriteToLogger(testSite, ">> ReadLocation =" + (tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[VectorFileName]][z]).ToString() + ",  done");

								CheckError(testSite, dm[testSite]->ReadHistoryRam(DM_Module_Alias, l_ReadBack_Vector_Count, tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[VectorFileName]][z], tl->glob->VectorSetNumber[VectorFileName], l_ReadData_Raw_Array));

								if (ret != 0) return ret;
								break;
							}
							l_Retry_Counter++;

							if (l_Retry_Counter > 1000)	ret += l_Retry_Counter;
						}

						Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(dataPinAlias)[0];  //Get Pin Resource Name
						int dataPinAliasvalue = 999;
						dataPinAliasvalue = Convert::ToInt32(HardwareRsrc->Value);

						for (int l_ReadData_Count = 0; l_ReadData_Count < (l_ReadBack_Vector_Count / l_totalDataCount/*2*/); l_ReadData_Count++)
						{
							l_ReadData_Array[l_ReadData_Count] = (l_ReadData_Raw_Array[l_Counter] >> (dataPinAliasvalue * 2)) & 0x000003;

							if (l_ReadData_Array[l_ReadData_Count] == 2) //undefined received (bin 10)
							{
								ReadHistoryRam_Data[z] = 999;
								goto ReadHistoryRam_Fail;
							}

							l_ReaddData_Raw_Int += l_ReadData_Array[l_ReadData_Count] << ((l_ReadBack_Vector_Count / l_totalDataCount/*2*/) - (l_ReadData_Count + 1));
							l_Counter += l_totalDataCount/*2*/;
						}
						ReadHistoryRam_Data[z] = l_ReaddData_Raw_Int;
						l_ReaddData_Raw_Int = 0;
					}
					else
					{
						return ER_CONST_FILE_NOT_FOUND;
					}
				}
			}

			//Read vector fail count
			if (tl->glob->VectorSetNumber->ContainsKey(VectorFileName))
			{
				l_Retry_Counter = 0;
				l_DM_Status = 999;
				while ((l_Retry_Counter <= 1000) && (l_DM_Status != DM_CONST_VEC_ENG_STAT_DONE))
				{
					l_DM_Status = 999;
					CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(DM_Module_Alias, l_DM_Status));
					if (ret != 0) return ret; //sk@20180902 - exit if AcquireVecEngineStatus returns an error code

					if ((l_DM_Status == DM_CONST_VEC_ENG_STAT_DONE))
					{
						CheckError(testSite, dm[testSite]->AcquireChannelFirstFailVectorCount(dataPinAlias, l_VectorFirstFail));
						CheckError(testSite, dm[testSite]->AcquireChannelVectorFailCount(dataPinAlias, l_VectorFailCount));

						if (ret != 0) return ret; //sk@20180902 - exit if ReadHistoryRam returns an error code
						break;
					}
					l_Retry_Counter++;

					if (l_Retry_Counter > 1000)	ret += l_Retry_Counter;
				}
				VectorFailCount = l_VectorFailCount;
				VectorFirstFail = l_VectorFailCount;
			}
			else
			{
				return ER_CONST_FILE_NOT_FOUND;
			}
		}

#pragma endregion

		ReadHistoryRam_Fail:
						   return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureDigitalPinToPMU(int testSite, String^ PIN, int measureMode, int senseMode, double compliance, double driveValue, double nplc)
	{
		int ret = 0;

		DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_PMU);
		DM_ConfigureSense(testSite, PIN, senseMode);
		DM_NplcSetting(testSite, PIN, nplc);

		if (measureMode == DM_CONST_DICV)
		{
			DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DICV);
			DM_ClampVoltage(testSite, PIN, compliance V);
			DM_DriveCurrent(testSite, PIN, driveValue A);
		}
		else if (measureMode == DM_CONST_DVCI)
		{
			DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DVCI);
			DM_ClampCurrent(testSite, PIN, compliance A);
			DM_DriveVoltage(testSite, PIN, driveValue V);
		}

		DM_OnDMpin(testSite, PIN);

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureDigitalPinToVector(int testSite, String^ PIN, int DPinLevelSet, int PEAttSet)
	{
		int ret = 0;

		DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_VECTOR);
		DM_ConfigureDPINLevelVector(testSite, PIN, tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VTERM"]);
		DM_ConfigurePEAttribute(testSite, PIN, tl->glob->PEAttributeSet[testSite][PEAttSet]["InputTermEnable"], tl->glob->PEAttributeSet[testSite][PEAttSet]["HVEnable"], tl->glob->PEAttributeSet[testSite][PEAttSet]["ActiveLoadEnable"], tl->glob->PEAttributeSet[testSite][PEAttSet]["DifferentialComparatorEnable"]);

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureDigitalPinToDIO(int testSite, String^ PIN, int DPinLevelSet, int pinDirection)
	{
		int ret = 0;

		DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_DIO);
		DM_ConfigureDPINLevelDIO(testSite, PIN, tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VTERM"]);
		DM_DioModeSetPinDirection(testSite, PIN, pinDirection);

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MeasureOS(int testSite, String ^ PIN, double driveCurrent, double clampVoltage, double delay, double % result)
	{
		int ret = 0;

		DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_PMU);
		DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DICV);
		DM_ClampVoltage(testSite, PIN, clampVoltage);
		DM_DriveCurrent(testSite, PIN, driveCurrent);
		DM_MeasureVoltage(testSite, PIN, delay, result);
		DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DVCI);
		DM_ClampCurrent(testSite, PIN, DM_CONST_200UA_RANGE);
		DM_DriveVoltage(testSite, PIN, 0.0 V);

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MeasureCurrent(int testSite, String ^ PIN, double % result)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->PMUMeasure(PIN, DM_CONST_MEASURECURRENT, result));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MeasureVoltage(int testSite, String ^ PIN, double % result)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->PMUMeasure(PIN, DM_CONST_MEASUREVOLTAGE, result));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MeasureCurrent(int testSite, String ^ PIN, double delay, double % result)
	{
		int ret = 0;

		util->WaitSecond(delay);
		CheckError(testSite, dm[testSite]->PMUMeasure(PIN, DM_CONST_MEASURECURRENT, result));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MeasureVoltage(int testSite, String ^ PIN, double delay, double % result)
	{
		int ret = 0;

		util->WaitSecond(delay);
		CheckError(testSite, dm[testSite]->PMUMeasure(PIN, DM_CONST_MEASUREVOLTAGE, result));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_NplcSetting(int testSite, String ^ PIN, double nplc)
	{
		int ret = 0;

		if (nplc != tl->glob->PMUStateSettingsManager[testSite].PMUStateNPLC[PIN])
		{
			CheckError(testSite, dm[testSite]->ConfigurePMUSamplingTime(PIN, nplc, DM_CONST_PLC));

			tl->glob->PMUStateSettingsManager[testSite].PMUStateNPLC[PIN] = nplc;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureOutputFunction(int testSite, String ^ PIN, int function)
	{
		int ret = 0;

		if (function != tl->glob->PMUStateSettingsManager[testSite].PMUStateOutputFunction[PIN])
		{
			CheckError(testSite, dm[testSite]->ConfigurePMUOutputFunction(PIN, function));

			tl->glob->PMUStateSettingsManager[testSite].PMUStateOutputFunction[PIN] = function;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ClampCurrent(int testSite, String ^ PIN, double clampValue)
	{
		int ret = 0;

		if (clampValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN])
		{
			CheckError(testSite, dm[testSite]->ConfigurePMUCurrentLimitRange(PIN, clampValue));

			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN] = clampValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN] = 0.0;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ClampVoltage(int testSite, String ^ PIN, double clampValue)
	{
		int ret = 0;

		if (clampValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN])
		{
			if (clampValue >= 2 V && clampValue <= 6 V)
			{
				CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLimit(PIN, clampValue, DM_CONST_VMIN));
			}
			else if (clampValue > 0 V && clampValue <= 2 V)
			{
				CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLimit(PIN, clampValue, -clampValue));
			}
			else if (clampValue < 0 V && clampValue >= -2 V)
			{
				CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLimit(PIN, DM_CONST_VMIN, clampValue));
			}

			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN] = clampValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN] = 999;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_DriveCurrent(int testSite, String ^ PIN, double driveValue)
	{
		int ret = 0;

		if (driveValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN])
		{
			CheckError(testSite, dm[testSite]->ConfigurePMUCurrentLevel(PIN, driveValue));

			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN] = driveValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN] = 999;
		}
		return ret;
	}
	int AMB7600SRTestLibrary::DM_DriveVoltage(int testSite, String ^ PIN, double driveValue)
	{
		int ret = 0;

		if (driveValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN])
		{
			CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLevel(PIN, driveValue));

			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN] = driveValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN] = 999;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_OnDMpin(int testSite, String ^ PIN)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->DPINOn(PIN));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_OffDMpin(int testSite, String ^ PIN)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->DPINOff(PIN));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureSense(int testSite, String ^ PIN, int sense)
	{
		int ret = 0;

		if (sense != tl->glob->PMUStateSettingsManager[testSite].PMUStateSense[PIN])
		{
			switch (sense)
			{
			case(0):
				CheckError(testSite, dm[testSite]->ConfigurePMUSense(PIN, DM_CONST_LOCAL));
				break;
			case(1):
				CheckError(testSite, dm[testSite]->ConfigurePMUSense(PIN, DM_CONST_REMOTE));
				break;
			default:
				break;
			}

			tl->glob->PMUStateSettingsManager[testSite].PMUStateSense[PIN] = sense;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_OperationMode(int testSite, String ^ PIN, int mode)
	{
		int ret = 0;

		if (mode != tl->glob->DMStateSettingsManager[testSite].DMStateOperationMode[PIN])
		{
			switch (mode)
			{
			case(0):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_VECTOR));
				tl->glob->PEStateSettingsManager[testSite].PEStateVIH[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateVIL[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateVOH[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateVOL[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateIOH[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateIOL[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateVCH[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateVCL[PIN] = 999;
				tl->glob->PEStateSettingsManager[testSite].PEStateVTERM[PIN] = 999;
				break;
			case(1):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_PMU));
				tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN] = 999;
				tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN] = 999;
				tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN] = 999;
				tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN] = 999;
				tl->glob->PMUStateSettingsManager[testSite].PMUStateOutputFunction[PIN] = 999;
				tl->glob->PMUStateSettingsManager[testSite].PMUStateSense[PIN] = 999;
				tl->glob->PMUStateSettingsManager[testSite].PMUStateNPLC[PIN] = 999;
				break;
			case(2):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_DIO));
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIH[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIL[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVOH[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVOL[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateIOH[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateIOL[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVCH[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVCL[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVTERM[PIN] = 999;
				tl->glob->DIO_DMStateSettingsManager[testSite].DIOStatePinValue[PIN] = 999;

				break;
			case(3):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_INPUT_DIR));
				break;
			case(4):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_OUTPUT_DIR));
				break;
			case(5):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_CLOCK));
				break;
			case(6):
				CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_INVERTED_CLOCK));
				break;
			default:
				break;
			}

			tl->glob->DMStateSettingsManager[testSite].DMStateOperationMode[PIN] = mode;
		}
		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureDPINLevelVector(int testSite, String ^ PIN, double VIH, double VIL, double VOH, double VOL, double IOH, double IOL, double VCH, double VCL, double VTERM)
	{
		int ret = 0;

		if (tl->glob->PEStateSettingsManager[testSite].PEStateVIH[PIN] != VIH || tl->glob->PEStateSettingsManager[testSite].PEStateVIL[PIN] != VIL
			|| tl->glob->PEStateSettingsManager[testSite].PEStateVOH[PIN] != VOH || tl->glob->PEStateSettingsManager[testSite].PEStateVOL[PIN] != VOL
			|| tl->glob->PEStateSettingsManager[testSite].PEStateIOH[PIN] != IOH || tl->glob->PEStateSettingsManager[testSite].PEStateIOL[PIN] != IOL
			|| tl->glob->PEStateSettingsManager[testSite].PEStateVCH[PIN] != VCH || tl->glob->PEStateSettingsManager[testSite].PEStateVCL[PIN] != VCL
			|| tl->glob->PEStateSettingsManager[testSite].PEStateVTERM[PIN] != VTERM)
		{
			CheckError(testSite, dm[testSite]->DPINLevel(PIN, VIH, VIL, VOH, VOL, IOH, IOL, VCH, VCL, VTERM));

			tl->glob->PEStateSettingsManager[testSite].PEStateVIH[PIN] = VIH;
			tl->glob->PEStateSettingsManager[testSite].PEStateVIL[PIN] = VIL;
			tl->glob->PEStateSettingsManager[testSite].PEStateVOH[PIN] = VOH;
			tl->glob->PEStateSettingsManager[testSite].PEStateVOL[PIN] = VOL;
			tl->glob->PEStateSettingsManager[testSite].PEStateIOH[PIN] = IOH;
			tl->glob->PEStateSettingsManager[testSite].PEStateIOL[PIN] = IOL;
			tl->glob->PEStateSettingsManager[testSite].PEStateVCH[PIN] = VCH;
			tl->glob->PEStateSettingsManager[testSite].PEStateVCL[PIN] = VCL;
			tl->glob->PEStateSettingsManager[testSite].PEStateVTERM[PIN] = VTERM;
		}
		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureDPINLevelDIO(int testSite, String ^ PIN, double VIH, double VIL, double VOH, double VOL, double IOH, double IOL, double VCH, double VCL, double VTERM)
	{
		int ret = 0;

		if (tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIH[PIN] != VIH || tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIL[PIN] != VIL
			|| tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVOH[PIN] != VOH || tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVOL[PIN] != VOL
			|| tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateIOH[PIN] != IOH || tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateIOL[PIN] != IOL
			|| tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVCH[PIN] != VCH || tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVCL[PIN] != VCL
			|| tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVTERM[PIN] != VTERM)
		{
			CheckError(testSite, dm[testSite]->DPINLevel(PIN, VIH, VIL, VOH, VOL, IOH, IOL, VCH, VCL, VTERM));


			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIH[PIN] = VIH;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIL[PIN] = VIL;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVOH[PIN] = VOH;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVOL[PIN] = VOL;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateIOH[PIN] = IOH;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateIOL[PIN] = IOL;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVCH[PIN] = VCH;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVCL[PIN] = VCL;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVTERM[PIN] = VTERM;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStatePinValue[PIN] = 999;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigurePEAttribute(int testSite, String ^ PIN, bool InputTermEnable, bool HVEnable, bool ActiveLoadEnable, bool DifferentialComparatorEnable)
	{
		int ret = 0;

		if (tl->glob->PEStateSettingsManager[testSite].PEStateInputTermEnable[PIN] != InputTermEnable || tl->glob->PEStateSettingsManager[testSite].PEStateHVEnable[PIN] != HVEnable
			|| tl->glob->PEStateSettingsManager[testSite].PEStateActiveLoadEnable[PIN] != ActiveLoadEnable || tl->glob->PEStateSettingsManager[testSite].PEStateDifferentialComparatorEnable[PIN] != DifferentialComparatorEnable)
		{
			CheckError(testSite, dm[testSite]->ConfigurePEAttribute(PIN, InputTermEnable, HVEnable, ActiveLoadEnable, DifferentialComparatorEnable));

			tl->glob->PEStateSettingsManager[testSite].PEStateInputTermEnable[PIN] = InputTermEnable;
			tl->glob->PEStateSettingsManager[testSite].PEStateHVEnable[PIN] = HVEnable;
			tl->glob->PEStateSettingsManager[testSite].PEStateActiveLoadEnable[PIN] = ActiveLoadEnable;
			tl->glob->PEStateSettingsManager[testSite].PEStateDifferentialComparatorEnable[PIN] = DifferentialComparatorEnable;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DM_DioModeDrivePin(int testSite, String ^ PIN, int driveValue)
	{
		int ret = 0;

		if (tl->glob->DIO_DMStateSettingsManager[testSite].DIOStatePinValue[PIN] != driveValue)
		{
			CheckError(testSite, dm[testSite]->DrivePin(PIN, driveValue));
		}
		return ret;
	}
	int AMB7600SRTestLibrary::DM_DioModeSetPinDirection(int testSite, String ^ PIN, int pinDirection)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->SetPinDirection(PIN, pinDirection));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias,int inputTerminal, int outputTerminal)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->MapTriggerInToTriggerOut(moduleAlias, inputTerminal, outputTerminal));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->DriveSoftwareTrigger(moduleAlias, select, pulseWidth));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureTriggerEdgeLevel(int testSite, String ^ moduleAlias, int trigSource, int trigMode)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->ConfigureTriggerEdgeLevel(moduleAlias, trigSource, trigMode));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureTriggerEdgeLevelExtra(int testSite, String ^ moduleAlias, int trigSource, int trigMode, int ignoreTrigCount)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->ConfigureTriggerEdgeLevel(moduleAlias, trigSource, trigMode, ignoreTrigCount));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureInputTriggerSelect(int testSite, String ^ moduleAlias, int trigSource, double delayAfterTrig)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->ConfigureInputTriggerSelect(moduleAlias, trigSource, delayAfterTrig));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureOutputTriggerSelect(int testSite, String ^ moduleAlias, int trigOutput0, int trigOutput1)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->ConfigureOutputTriggerSelect(moduleAlias, trigOutput0, trigOutput1));

		return ret;
	}
	int AMB7600SRTestLibrary::DM_ConfigureReadPin_TriggerOutput(int testSite, String ^ pinAlias, int pinStatusSelect)
	{
		int ret = 0;

		CheckError(testSite, dm[testSite]->ConfigureReadPin_TriggerOutput(pinAlias, pinStatusSelect));

		return ret;
	}

}