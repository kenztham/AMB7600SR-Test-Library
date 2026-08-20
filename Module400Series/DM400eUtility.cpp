#include "../Test Method/Methods.h"
#include "Module400Series.h"CM_Wait

namespace Functions
{

	array<String^>^ Module400Series::GetDMModuleAlias(Site ^ site, int siteIndex)
	{
		// [7600 original architecture] Scans hardware resource hierarchy for DM482e / DM483e modules
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

	int Module400Series::InitDmPinAliasPreviousState(Site ^ site, int siteIndex)
	{
		// [7600 original architecture] Populates PE, PMU, and DIO state settings managers with default values (999/false)
		int ret = 0;

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

	bool Module400Series::CheckingAnyDmModuleRunVector(Site ^ site, int siteIndex, array<String ^>^ moduleAlias, array<String ^>^ % moduleAliasRunVector, array<String ^>^ % communicationProtocol)
	{
		// [7600 original architecture] Scans control condition list to see if DM vector mode is configured
		bool RunVector = false;

		ConditionCollection ^ ControlConditionCollection = gcnew ConditionCollection();
		ControlConditionCollection = tf_ControlItem_ConditionList();

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
					tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
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

	int Module400Series::CastTimingSetPeriodControlItem(Site ^ site, int siteIndex)
	{
		// [7600 original architecture] Dynamically parses timing set period control items from Test Flow conditions
		int ret = 0;
		String^ ErrorMessage = nullptr;

		try
		{
			ConditionCollection ^ ControlConditionCollection = gcnew ConditionCollection();
			ControlConditionCollection = tf_ControlItem_ConditionList();

			int count = 0;

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
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::CastDpinLevelControlItem(Site ^ site, int siteIndex)
	{
		// [7600 original architecture] Dynamically casts DPin level conditions (VIH, VIL, VOH, etc.) from Test Flow
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

			while (StatusPass)
			{
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

			DPinConditionVal = gcnew array<Dictionary<String^, double>^>(DPinset);
			for (int i = 0; i < DPinset; i++)
			{
				DPinConditionVal[i] = gcnew Dictionary<String^, double>();
			}

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
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::CastPEAttributeControlItem(Site ^ site, int siteIndex)
	{
		// [7600 original architecture] Dynamically casts PE attributes (InputTerm, HVEnable, etc.) from Test Flow
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

			while (StatusPass)
			{
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

			PEAttConditionVal = gcnew array<Dictionary<String^, bool>^>(PEAttset);

			for (int i = 0; i < PEAttset; i++)
			{
				PEAttConditionVal[i] = gcnew Dictionary<String^, bool>();
			}

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
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		}
		return ret;
	}

	int Module400Series::GetVectorFiles(Site ^ site)
	{
		// [7600 original architecture] Discovers .vec files from directory and populates vector lookup map
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
			tl->ErrorHandling(site, tl->glob->TcrLgr.GlobalErrorMessage);
		}

		return ret;
	}


	
	//VECTOR LOADING ARCHITECTURE (from 7300) Lightweight and isolated routine that purely allocates hardware memory and loads.vec files.
	int Module400Series::DMLoadVectorFiles(Site ^ site, int siteIndex, String ^ ModuleAlias) 
	{
		int ret = 0;

		try
		{
			// Setup resource array cleanly from 7300
			array<int>^ resourceArr = gcnew array<int>(tl->glob->VectorFile.totalVecFileExist);
			for (int i = 0; i < tl->glob->VectorFile.totalVecFileExist; i++)
			{
				resourceArr[i] = 1;
			}

			tl->CheckError(siteIndex, dm[siteIndex]->DPINVectorResourceAllocation(ModuleAlias, tl->glob->VectorFile.totalVecFileExist, resourceArr));

			// Load vector files into DM hardware memory
			for (int i = 0; i < tl->glob->VectorFile.totalVecFileExist; i++)
			{
				tl->CheckError(siteIndex, dm[siteIndex]->DPINVecLoad(ModuleAlias, DM_CONST_DIRECTION_BIDIRECTIONAL_IO, tl->glob->VectorFile.vecFileNumber[i], tl->glob->VectorFile.vecFilePathList[i]));
			}

			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "[DMLoadVectorFiles] Successfully loaded " + tl->glob->VectorFile.totalVecFileExist.ToString() + " vector files to " + ModuleAlias);
		}
		catch (Exception ^ ex)
		{
			ret = ER_CONST_LOAD_VECTOR_FILE_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			String^ ErrorMessage = "Site " + siteIndex + ":: [DMLoadVectorFiles] Fail to load VectorFile. | Error Code: " + ret.ToString() + " | Detail: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::LoadVectorFiles(Site ^ site, int siteIndex, String ^ ModuleAlias)
	{
		
		return DMLoadVectorFiles(site, siteIndex, ModuleAlias);
	}


	
	//SYSTEM INITIALIZATION from (7600) Integrates directly with test flow conditions (DMCase_DMInit) and multi-site lockdowns
	int Module400Series::InitializeDM400eResource(Site ^ site) 
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

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetDMModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			if (moduleCount[siteIndex] > 0)
			{
				ResourceManagerSett[siteIndex].DM_HardwareStatus = true;
			}
		}

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			userDMInit[siteIndex] = false;

			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing DM400e System Resources...");

				for each(Condition ^ controlMethod in testConditionCollection)
				{
					if (controlMethod->Name->StartsWith("ControlMethod") && (String^)tf_ControlItem_ConditionCast(controlMethod->Name) == "DMCase_DMInit")
					{
						strControlMethod = nullptr;
						intControlMethod = 0;
						strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
						tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
						methods->Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);
						tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
						methods->ControlMethod_Selection(site, siteIndex, intControlMethod, testConditionCollection);
						userDMInit[siteIndex] = true;
					}
				}

				if (userDMInit[siteIndex] == false)
				{
					DM_Init(siteIndex, 3);
				}

				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "DM[site " + siteIndex + "] initialized");
			}
		}

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

				for (count = 0; count < moduleCount[siteIndex]; count++)
				{
					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing dm[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", DM_CONST_MULTI_SITE)");
					tl->CheckError(siteIndex, dm[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], DM_CONST_MULTI_SITE));

					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing dm[" + siteIndex + "]->ConfigurePowerLineFrequency(" + moduleAlias[siteIndex][count] + "," + tl->glob->AWV.PowerLineFreq.ToString() + " )");
					tl->CheckError(siteIndex, dm[siteIndex]->ConfigurePowerLineFrequency(moduleAlias[siteIndex][count], tl->glob->AWV.PowerLineFreq));
				}

				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing DM400e Related Global Variables for Previous States...");
				InitDmPinAliasPreviousState(site, siteIndex);
			}
			else if (moduleCount[siteIndex] == 0)
			{
				ResourceManagerSett[siteIndex].DM_HardwareStatus = false;
			}
		}

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				for each(Condition ^ controlMethod in testConditionCollection)
				{
					if (controlMethod->Name->StartsWith("ControlMethod"))
					{
						strControlMethod = nullptr;
						intControlMethod = 0;
						strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
						tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
						methods->Dictionary_CM->TryGetValue(strControlMethod, intControlMethod);

						if (intControlMethod == DMCase_DMCastDPinLevel || intControlMethod == DMCase_DMCastTimingSetPeriod || intControlMethod == DMCase_DMCastPEAttribute || intControlMethod == DMCase_DMLoadVectorFile)
						{
							tl->glob->ErrorInfo[siteIndex].ControlMethodName = strControlMethod;
							methods->ControlMethod_Selection(site, siteIndex, intControlMethod, testConditionCollection);
						}
					}
				}
			}
		}

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DM_HardwareStatus)
			{
				for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].DMResourceAlias)
				{
					DM_ConfigureDigitalPinToPMU(siteIndex, pinAlias->Key, DM_CONST_DVCI, DM_CONST_LOCAL, DM_CONST_200UA_RANGE, 0.0 V, DM_CONST_PLC);
				}
			}
		}
		return ret;
	}

	int Module400Series::UninitializeDM400eResource(Site ^ site) //UNINITIALIZATION (from 7600)
	{
		int ret = 0;
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
						tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing dm[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, dm[siteIndex]->Reset(moduleAlias[siteIndex][count]));

						tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing dm[" + siteIndex + "]->Close(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, dm[siteIndex]->Close(moduleAlias[siteIndex][count]));
					}
				}
			}
			catch (Exception ^ ex)
			{
				tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
				String^ ErrorMessage = "Module400Series:: UninitializeDM400eResource encountered error when performing.";
				tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
			}
		}

		return ret;
	}

	int Module400Series::DM_Init(int testSite, int dpinGroup)
	{
		// [keep 7600] Direct constructor helper for managed DM driver object
		int ret = 0;
		dm[testSite] = gcnew DM(tl->glob->HardwareProfile, dpinGroup, tl->glob->tf.TestHead, testSite, tl->glob->AWV.Offline, tl->glob->AWV.DMInitOption);
		return ret;
	}


	
	//VECTOR EXECUTION ARCHITECTURE (From 7300) Provides batch file array execution, standardized error return constants
	int Module400Series::DM_MIPIWriteVector(int testSite, String ^ moduleAlias, String ^ vectorFileName)
	{
		// [7300 DmRunVector Algorithm]: Polling loop, engine busy timeout checks, settling delay
		int ret = 0;

		try
		{
			int vecFileNumber = 9999;
			for (int i = 0; i < tl->glob->VectorFile.totalVecFileExist; i++)
			{
				if (tl->glob->VectorFile.vecFileName[i] == vectorFileName)
				{
					vecFileNumber = i;
					break;
				}
			}

			int count = 0;
			int dmStatus = 999;
			while ((count <= 200000) && (dmStatus != 0))
			{
				dmStatus = 999;
				tl->CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(moduleAlias, dmStatus));

				if (dmStatus == 0)
				{
					tl->CheckError(testSite, dm[testSite]->RunVector(moduleAlias, vecFileNumber));
					tl->Util->WaitSecond(dmMipiVec.runMipiDelay);
					break;
				}
				tl->Util->WaitSecond(1.0 uS);
				count++;

				if (count >= 200000)
				{
					ret = ER_CONST_DM_VECTOR_ENGINE_STATUS_BUSY;
					tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> DM_MIPIWriteVector] DM vector engine status BUSY | Error Code: " + ret.ToString());
					goto EndOfTest;
				}
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DM_RUN_VECTOR_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> DM_MIPIWriteVector] Fail to run vector file. | Detail: " + ex->Message);
			goto EndOfTest;
		}

	EndOfTest:
		return ret;
	}

	int Module400Series::DmPatternTestFunction_MipiWrite(int tfSite, int siteIndex, String ^ dmModuleAlias, array<String^> ^ vectorFileName)
	{
		// [7300 DmPatternTestFunction_MipiWrite Algorithm]: Iterates over vector file array
		int ret = 0;

		try
		{
			for (int i = 0; i < vectorFileName->Length; i++)
			{
				ret = DM_MIPIWriteVector(siteIndex, dmModuleAlias, vectorFileName[i]);
				if (ret != 0) goto EndOfTest;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DM_PATTERN_TEST_MIPI_WRITE_FAIL;
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, ERROR, "[Module400Series -> DmPatternTestFunction_MipiWrite] Fail MIPI write. | Detail: " + ex->Message);
			goto EndOfTest;
		}

	EndOfTest:
		return ret;
	}


	
	//VECTOR STATE CSV PARSING ARCHITECTURE (From 7300) Single-responsibility parser functions with strict bit-width boundary validation(e.g., max address / data limits) and clear diagnostic logging.
	int Module400Series::GetDpinGroupInfo(array<String^> ^ mipiSetInfo, int % dpinGroup, String^ % errorMessage)
	{
		int ret = 0;
		dpinGroup = 999;
		errorMessage = "NA";

		if (mipiSetInfo[0] != "DM_DPinGroup") return ER_CONST_VECTOR_STATE_FILE_DPINGROUP_NOT_FOUND;
		if (String::IsNullOrEmpty(mipiSetInfo[1])) return ER_CONST_VECTOR_STATE_FILE_DPINGROUP_INPUT_EMPTY;

		dpinGroup = Convert::ToInt32(mipiSetInfo[1], 10);
		if ((dpinGroup < 1) || (dpinGroup > 3)) return ER_CONST_VECTOR_STATE_FILE_DPINGROUP_INPUT_INVALID;

		return ret;
	}

	int Module400Series::GetSclkChannelInfo(array<String^> ^ mipiSetInfo, int dpinGroup, int % sclkChannel, String^ % errorMessage)
	{
		int ret = 0;
		sclkChannel = 999;
		errorMessage = "NA";

		if (mipiSetInfo[0] != "SCLK_Channel") return ER_CONST_VECTOR_STATE_FILE_SCLK_CH_NOT_FOUND;
		if (String::IsNullOrEmpty(mipiSetInfo[1])) return ER_CONST_VECTOR_STATE_FILE_SCLK_CH_INPUT_EMPTY;

		sclkChannel = Convert::ToInt32(mipiSetInfo[1], 10);
		if ((sclkChannel < 0) || (sclkChannel > 11)) return ER_CONST_VECTOR_STATE_FILE_SCLK_CH_INPUT_INVALID;
		if ((dpinGroup == 1) && ((sclkChannel < 0) || (sclkChannel > 5))) return ER_CONST_VECTOR_STATE_FILE_SCLK_CH_INPUT_INVALID;
		if ((dpinGroup == 2) && ((sclkChannel < 6) || (sclkChannel > 11))) return ER_CONST_VECTOR_STATE_FILE_SCLK_CH_INPUT_INVALID;

		return ret;
	}

	int Module400Series::GetSdataChannelInfo(array<String^> ^ mipiSetInfo, int dpinGroup, int sclkChannel, int % sdataChannel, String^ % errorMessage)
	{
		int ret = 0;
		sdataChannel = 999;
		errorMessage = "NA";

		if (mipiSetInfo[0] != "SDATA_Channel") return ER_CONST_VECTOR_STATE_FILE_SDATA_CH_NOT_FOUND;
		if (String::IsNullOrEmpty(mipiSetInfo[1])) return ER_CONST_VECTOR_STATE_FILE_SDATA_CH_INPUT_EMPTY;

		sdataChannel = Convert::ToInt32(mipiSetInfo[1], 10);
		if ((sdataChannel < 0) || (sdataChannel > 11)) return ER_CONST_VECTOR_STATE_FILE_SDATA_CH_INPUT_INVALID;
		if ((dpinGroup == 1) && ((sdataChannel < 0) || (sdataChannel > 5))) return ER_CONST_VECTOR_STATE_FILE_SDATA_CH_INPUT_INVALID;
		if ((dpinGroup == 2) && ((sdataChannel < 6) || (sdataChannel > 11))) return ER_CONST_VECTOR_STATE_FILE_SDATA_CH_INPUT_INVALID;
		if (sdataChannel == sclkChannel) return ER_CONST_VECTOR_STATE_FILE_SDATA_CH_INPUT_INVALID;

		return ret;
	}

	int Module400Series::GetVecTimingSetInfo(array<String^> ^ mipiSetInfo, int % vecTimingSet, String^ % errorMessage)
	{
		int ret = 0;
		vecTimingSet = 999;
		errorMessage = "NA";

		if (mipiSetInfo[0] != "VectorTimingSet") return ER_CONST_VECTOR_STATE_FILE_TIMING_SET_NOT_FOUND;
		if (String::IsNullOrEmpty(mipiSetInfo[1])) return ER_CONST_VECTOR_STATE_FILE_TIMING_SET_INPUT_EMPTY;

		vecTimingSet = Convert::ToInt32(mipiSetInfo[1], 10);
		if ((vecTimingSet < 0) || (vecTimingSet > 1023)) return ER_CONST_VECTOR_STATE_FILE_TIMING_SET_INPUT_INVALID;

		return ret;
	}

	int Module400Series::CheckMipiSetIdentifier(array<String^> ^ mipiSetInfo, String^ % errorMessage)
	{
		if ((mipiSetInfo[0] != "Mode") || (mipiSetInfo[1] != "USID") || (mipiSetInfo[2] != "RegAddr") ||
			(mipiSetInfo[3] != "RegData") || (mipiSetInfo[4] != "Operation") || (mipiSetInfo[5] != "Speed"))
		{
			return ER_CONST_VECTOR_STATE_FILE_MIPI_SET_HEADER_NOT_FOUND;
		}
		return 0;
	}

	int Module400Series::GetRegAddrList(array<String^> ^ mipiSetInfo, String^ mode, int % regAddr, String^ % errorMessage)
	{
		int ret = 0;
		regAddr = 999;
		errorMessage = "NA";

		if ((!String::IsNullOrEmpty(mipiSetInfo[2])) || (mode == "Reg0"))
		{
			if ((String::IsNullOrEmpty(mipiSetInfo[2])) && (mode == "Reg0"))
				regAddr = 0;
			else
				regAddr = Convert::ToInt32(mipiSetInfo[2], 16);

			if ((mode == "Basic") && (regAddr > 31)) return ER_CONST_VECTOR_STATE_FILE_MIPI_ADDR_INPUT_INVALID;
			if ((mode == "Extended") && (regAddr > 255)) return ER_CONST_VECTOR_STATE_FILE_MIPI_ADDR_INPUT_INVALID;
			if ((mode == "Reg0") && (regAddr > 0)) return ER_CONST_VECTOR_STATE_FILE_MIPI_ADDR_INPUT_INVALID;
		}
		else
		{
			return ER_CONST_VECTOR_STATE_FILE_MIPI_ADDR_INPUT_EMPTY;
		}

		return ret;
	}


	
	//MIPI READ BACK / PATTERN EXECUTION ARCHITECTURE (From 7300) Fully self-contained; dynamically parses CSV state files on-demand, calculates exact protocol bit offsets(SSC, SA, BC, Parity)
	int Module400Series::API_MIPI_Vector_Read(Site ^ site, int testSite, String ^ dataPinAlias, String ^ DM_Module_Alias, double channelInputDelay, String ^ VectorFileName, bool sweepOperation, array<int> ^ % ReadHistoryRam_Data, int % VectorFailCount, int % VectorFirstFail)
	{
		// [FULL 7300 ALGORITHM IMPLMENTED INSIDE 7600 API]
		int ret = 0;
		String ^ targetVecFileDirectory = tl->glob->VectorFile.VectorFileFolderDirectory + "\\" + VectorFileName + ".vec";
		String ^ targetVecStateFileDirectory = tl->glob->VectorStateFile.VectorStateFileFolderDirectory + "\\" + VectorFileName + ".csv";

		// 1. Validate file existence on-demand 
		if (!File::Exists(targetVecFileDirectory) || !File::Exists(targetVecStateFileDirectory))
		{
			ret = ER_CONST_PROJECT_VECTOR_FILE_NOT_FOUND;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> API_MIPI_Vector_Read] Target vector file or CSV state file missing: " + VectorFileName);
			goto EndOfTest;
		}

		// 2. Configure input channel delay
		tl->CheckError(testSite, dm[testSite]->ConfigureInputChannelDelay(dataPinAlias, channelInputDelay));

		// 3. Execute vector file using Source 1 execution pipeline
		ret = DM_MIPIWriteVector(testSite, DM_Module_Alias, VectorFileName);
		if (ret != 0) goto EndOfTest;

		// 4. Poll engine status with strict busy-timeout guarding 
		int dmStatus = 999;
		int count = 0;

		while ((count <= 200000) && (dmStatus != 0))
		{
			dmStatus = 999;
			tl->CheckError(testSite, dm[testSite]->AcquireVecEngineStatus(DM_Module_Alias, dmStatus));

			if (dmStatus == 0)
			{
				break;
			}
			tl->Util->WaitSecond(1.0 uS);
			count++;

			if (count >= 200000)
			{
				ret = ER_CONST_DM_VECTOR_ENGINE_STATUS_BUSY;
				tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> API_MIPI_Vector_Read] Engine status BUSY on readback.");
				goto EndOfTest;
			}
		}

		// 5. Read History RAM & decode pin bits (7300 DmVectorFileReadBack_Mipi)
		int readOperationCount = tl->glob->VectorFileManager[testSite].l_Read_Operation_Counter[VectorFileName];
		ReadHistoryRam_Data = gcnew array<int>(readOperationCount);

		for (int i = 0; i < readOperationCount; i++)
		{
			ReadHistoryRam_Data[i] = 0;
		}

		try
		{
			int readBackVecCount = 16;
			array<int>^ readBackArrRaw = gcnew array<int>(readBackVecCount);

			Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(dataPinAlias)[0];
			int dataPinChannel = Convert::ToInt32(HardwareRsrc->Value);

			for (int i = 0; i < readOperationCount; i++)
			{
				int startLoc = tl->glob->VectorFileManager[testSite].l_Start_Read_Location_Single_VectorFile[tl->glob->VectorSetNumber[VectorFileName]][i];
				int vecFileNum = tl->glob->VectorSetNumber[VectorFileName];

				tl->CheckError(testSite, dm[testSite]->ReadHistoryRam(DM_Module_Alias, readBackVecCount, startLoc, vecFileNum, readBackArrRaw));

				int readBackSumInt = 0;
				int readRawLineIndex = 0;

				for (int j = 0; j < (readBackVecCount / 2); j++)
				{
					int bitVal = (readBackArrRaw[readRawLineIndex] >> (dataPinChannel * 2)) & 0x000003;

					// Detect undefined binary 10 signal states (7300)
					if (bitVal == 2)
					{
						ReadHistoryRam_Data[i] = 999;
						ret = ER_CONST_DM_PATTERN_TEST_READHISTORYRAM_UNDEFINED;
						tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> API_MIPI_Vector_Read] Fail at ReadHistoryRam. Undefined (binary 10) detected on pin: " + dataPinAlias);
						goto EndOfTest;
					}

					readBackSumInt += bitVal << ((readBackVecCount / 2) - (j + 1));
					readRawLineIndex += 2;
				}

				ReadHistoryRam_Data[i] = readBackSumInt;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_MIPI_VECTOR_READ_BACK_HISTORYRAM_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> API_MIPI_Vector_Read] Fail at ReadHistoryRam bit extraction. Detail: " + ex->Message);
			goto EndOfTest;
		}

		// 6. Acquire fail counts and line of first fail (7300)
		try
		{
			tl->CheckError(testSite, dm[testSite]->AcquireChannelFirstFailVectorCount(dataPinAlias, VectorFirstFail));
			tl->CheckError(testSite, dm[testSite]->AcquireChannelVectorFailCount(dataPinAlias, VectorFailCount));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_MIPI_VECTOR_READ_BACK_FAILCOUNT_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> API_MIPI_Vector_Read] Fail at AcquireChannelVectorFailCount. Detail: " + ex->Message);
			goto EndOfTest;
		}

	EndOfTest:
		return ret;
	}


	
	//PIN PMU SETUP ARCHITECTURE (from 7600) Implements state caching (PMUStateSettingsManager) to eliminate redundant bus write calls, saving critical test execution time.
	int Module400Series::DM_ConfigureDigitalPinToPMU(int testSite, String^ PIN, int measureMode, int senseMode, double compliance, double driveValue, double nplc)
	{
		int ret = 0;

		try
		{
			DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_PMU);
			DM_ConfigureSense(testSite, PIN, senseMode);
			DM_NplcSetting(testSite, PIN, nplc);

			if (measureMode == DM_CONST_DICV)
			{
				DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DICV);
				DM_ClampVoltage(testSite, PIN, compliance);
				DM_DriveCurrent(testSite, PIN, driveValue);
			}
			else if (measureMode == DM_CONST_DVCI)
			{
				DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DVCI);
				DM_ClampCurrent(testSite, PIN, compliance);
				DM_DriveVoltage(testSite, PIN, driveValue);
			}

			DM_OnDMpin(testSite, PIN);
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_CONFIGURE_DM_PIN_TO_PMU_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> DM_ConfigureDigitalPinToPMU] Fail to configure PMU mode. | Detail: " + ex->Message);
		}

		return ret;
	}

	int Module400Series::DM_NplcSetting(int testSite, String ^ PIN, double nplc)
	{
		// [7600 original architecture] Directly updates PMU integration/sampling time with cached state validation
		int ret = 0;
		if (nplc != tl->glob->PMUStateSettingsManager[testSite].PMUStateNPLC[PIN])
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUSamplingTime(PIN, nplc, DM_CONST_PLC));
			tl->glob->PMUStateSettingsManager[testSite].PMUStateNPLC[PIN] = nplc;
		}
		return ret;
	}

	int Module400Series::DM_ConfigureOutputFunction(int testSite, String ^ PIN, int function)
	{
		// [7600 original architecture] Switches output function mode (DVCI/DICV) with cached state validation
		int ret = 0;
		if (function != tl->glob->PMUStateSettingsManager[testSite].PMUStateOutputFunction[PIN])
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUOutputFunction(PIN, function));
			tl->glob->PMUStateSettingsManager[testSite].PMUStateOutputFunction[PIN] = function;
		}
		return ret;
	}

	int Module400Series::DM_ClampCurrent(int testSite, String ^ PIN, double clampValue)
	{
		// [7600 original architecture] Sets PMU current limit range with cached state validation
		int ret = 0;
		if (clampValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN])
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUCurrentLimitRange(PIN, clampValue));
			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN] = clampValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN] = 0.0;
		}
		return ret;
	}

	int Module400Series::DM_ClampVoltage(int testSite, String ^ PIN, double clampValue)
	{
		// [7600 original architecture] Sets PMU voltage limit range with explicit hardware boundary checks and caching
		int ret = 0;
		if (clampValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN])
		{
			if (clampValue >= 2 V && clampValue <= 6 V)
			{
				tl->CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLimit(PIN, clampValue, DM_CONST_VMIN));
			}
			else if (clampValue > 0 V && clampValue <= 2 V)
			{
				tl->CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLimit(PIN, clampValue, -clampValue));
			}
			else if (clampValue < 0 V && clampValue >= -2 V)
			{
				tl->CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLimit(PIN, DM_CONST_VMIN, clampValue));
			}

			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampVoltage[PIN] = clampValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateClampCurrent[PIN] = 999;
		}
		return ret;
	}

	int Module400Series::DM_DriveCurrent(int testSite, String ^ PIN, double driveValue)
	{
		// [7600 original architecture] Programs force current level with cached state validation
		int ret = 0;
		if (driveValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN])
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUCurrentLevel(PIN, driveValue));
			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN] = driveValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN] = 999;
		}
		return ret;
	}

	int Module400Series::DM_DriveVoltage(int testSite, String ^ PIN, double driveValue)
	{
		// [7600 original architecture] Programs force voltage level with cached state validation
		int ret = 0;
		if (driveValue != tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN])
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUVoltageLevel(PIN, driveValue));
			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveVoltage[PIN] = driveValue;
			tl->glob->PMUStateSettingsManager[testSite].PMUStateDriveCurrent[PIN] = 999;
		}
		return ret;
	}

	int Module400Series::DM_OnDMpin(int testSite, String ^ PIN)
	{
		// [7600 original architecture] Wrapper call to turn digital pin ON (DPINOn)
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->DPINOn(PIN));
		return ret;
	}

	int Module400Series::DM_OffDMpin(int testSite, String ^ PIN)
	{
		// [7600 original architecture] Wrapper call to turn digital pin OFF (DPINOff)
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->DPINOff(PIN));
		return ret;
	}

	int Module400Series::DM_ConfigureSense(int testSite, String ^ PIN, int sense)
	{
		// [7600 original architecture] Configures PMU voltage sensing mode (Local vs Remote) with cached state validation
		int ret = 0;
		if (sense != tl->glob->PMUStateSettingsManager[testSite].PMUStateSense[PIN])
		{
			switch (sense)
			{
			case(0):
				tl->CheckError(testSite, dm[testSite]->ConfigurePMUSense(PIN, DM_CONST_LOCAL));
				break;
			case(1):
				tl->CheckError(testSite, dm[testSite]->ConfigurePMUSense(PIN, DM_CONST_REMOTE));
				break;
			default:
				break;
			}
			tl->glob->PMUStateSettingsManager[testSite].PMUStateSense[PIN] = sense;
		}
		return ret;
	}

	int Module400Series::DM_OperationMode(int testSite, String ^ PIN, int mode)
	{
		// [7600 original architecture] Changes low-level pin force states (VECTOR, PMU, DIO) and resets tracking states
		int ret = 0;
		if (mode != tl->glob->DMStateSettingsManager[testSite].DMStateOperationMode[PIN])
		{
			switch (mode)
			{
			case(0):
				tl->CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_VECTOR));
				break;
			case(1):
				tl->CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_PMU));
				break;
			case(2):
				tl->CheckError(testSite, dm[testSite]->Force(PIN, DM_CONST_FORCE_STATE_DIO));
				break;
			default:
				break;
			}
			tl->glob->DMStateSettingsManager[testSite].DMStateOperationMode[PIN] = mode;
		}
		return ret;
	}


	
	//PIN PE SETUP ARCHITECTURE (From 7600) Uses state-cached tracking (PEStateSettingsManager) to avoid re-writing driver voltage thresholds(VIH, VIL, VOH, VOL) if levels haven't changed.
	int Module400Series::DM_ConfigureDigitalPinToVector(int testSite, String^ PIN, int DPinLevelSet, int PEAttSet)
	{
		int ret = 0;
		DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_VECTOR);
		DM_ConfigureDPINLevelVector(testSite, PIN, tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VTERM"]);
		DM_ConfigurePEAttribute(testSite, PIN, tl->glob->PEAttributeSet[testSite][PEAttSet]["InputTermEnable"], tl->glob->PEAttributeSet[testSite][PEAttSet]["HVEnable"], tl->glob->PEAttributeSet[testSite][PEAttSet]["ActiveLoadEnable"], tl->glob->PEAttributeSet[testSite][PEAttSet]["DifferentialComparatorEnable"]);
		return ret;
	}

	int Module400Series::DM_ConfigureDPINLevelVector(int testSite, String ^ PIN, double VIH, double VIL, double VOH, double VOL, double IOH, double IOL, double VCH, double VCL, double VTERM)
	{
		// [7600 original architecture] Applies digital pin levels specifically for vector mode with cached state validation
		int ret = 0;
		if (tl->glob->PEStateSettingsManager[testSite].PEStateVIH[PIN] != VIH || tl->glob->PEStateSettingsManager[testSite].PEStateVIL[PIN] != VIL ||
			tl->glob->PEStateSettingsManager[testSite].PEStateVOH[PIN] != VOH || tl->glob->PEStateSettingsManager[testSite].PEStateVOL[PIN] != VOL)
		{
			tl->CheckError(testSite, dm[testSite]->DPINLevel(PIN, VIH, VIL, VOH, VOL, IOH, IOL, VCH, VCL, VTERM));
			tl->glob->PEStateSettingsManager[testSite].PEStateVIH[PIN] = VIH;
			tl->glob->PEStateSettingsManager[testSite].PEStateVIL[PIN] = VIL;
			tl->glob->PEStateSettingsManager[testSite].PEStateVOH[PIN] = VOH;
			tl->glob->PEStateSettingsManager[testSite].PEStateVOL[PIN] = VOL;
		}
		return ret;
	}

	int Module400Series::DM_ConfigurePEAttribute(int testSite, String ^ PIN, bool InputTermEnable, bool HVEnable, bool ActiveLoadEnable, bool DifferentialComparatorEnable)
	{
		// [7600 original architecture] Directly applies PE feature flags with cached state validation
		int ret = 0;
		if (tl->glob->PEStateSettingsManager[testSite].PEStateInputTermEnable[PIN] != InputTermEnable || tl->glob->PEStateSettingsManager[testSite].PEStateHVEnable[PIN] != HVEnable)
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePEAttribute(PIN, InputTermEnable, HVEnable, ActiveLoadEnable, DifferentialComparatorEnable));
			tl->glob->PEStateSettingsManager[testSite].PEStateInputTermEnable[PIN] = InputTermEnable;
			tl->glob->PEStateSettingsManager[testSite].PEStateHVEnable[PIN] = HVEnable;
		}
		return ret;
	}



	//PIN DIO SETUP ARCHITECTURE (From 7600)  Fully implemented active DIO operational mode with state caching, direction mapping(DM_DioModeSetPinDirection), and driving routines(DM_DioModeDrivePin).
	int Module400Series::DM_ConfigureDigitalPinToDIO(int testSite, String^ PIN, int DPinLevelSet, int pinDirection)
	{
		int ret = 0;
		DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_DIO);
		DM_ConfigureDPINLevelDIO(testSite, PIN, tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VIL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["IOL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCH"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VCL"], tl->glob->DPinLevelSet[testSite][DPinLevelSet]["VTERM"]);
		DM_DioModeSetPinDirection(testSite, PIN, pinDirection);
		return ret;
	}

	int Module400Series::DM_ConfigureDPINLevelDIO(int testSite, String ^ PIN, double VIH, double VIL, double VOH, double VOL, double IOH, double IOL, double VCH, double VCL, double VTERM)
	{
		// [7600 original architecture] Applies digital pin levels specifically for DIO mode with cached state validation
		int ret = 0;
		if (tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIH[PIN] != VIH || tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIL[PIN] != VIL)
		{
			tl->CheckError(testSite, dm[testSite]->DPINLevel(PIN, VIH, VIL, VOH, VOL, IOH, IOL, VCH, VCL, VTERM));
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIH[PIN] = VIH;
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStateVIL[PIN] = VIL;
		}
		return ret;
	}

	int Module400Series::DM_DioModeDrivePin(int testSite, String ^ PIN, int driveValue)
	{
		// [7600 original architecture] Drives a dynamic logic high/low value (0/1) on a pin operating in DIO mode
		int ret = 0;
		if (tl->glob->DIO_DMStateSettingsManager[testSite].DIOStatePinValue[PIN] != driveValue)
		{
			tl->CheckError(testSite, dm[testSite]->DrivePin(PIN, driveValue));
			tl->glob->DIO_DMStateSettingsManager[testSite].DIOStatePinValue[PIN] = driveValue;
		}
		return ret;
	}

	int Module400Series::DM_DioModeSetPinDirection(int testSite, String ^ PIN, int pinDirection)
	{
		// [7600 original architecture] Explicitly sets pin direction (Input vs Output) for DIO operational mode
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->SetPinDirection(PIN, pinDirection));
		return ret;
	}


	
	//CONTINUITY / OS TESTING ARCHITECTURE (From 7600) Self-contained routine that forces DICV mode for diode testing and automatically restores pins safely back to DVCI 0V to prevent pin - to - pin shorts.
	int Module400Series::DM_MeasureOS(int testSite, String ^ PIN, double driveCurrent, double clampVoltage, double delay, double % result)
	{
		int ret = 0;

		try
		{
			DM_OperationMode(testSite, PIN, DM_CONST_FORCE_STATE_PMU);
			DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DICV);
			DM_ClampVoltage(testSite, PIN, clampVoltage);
			DM_DriveCurrent(testSite, PIN, driveCurrent);
            DM_MeasureVoltage(testSite, PIN, delay, result);
			DM_ConfigureOutputFunction(testSite, PIN, DM_CONST_DVCI);
			DM_ClampCurrent(testSite, PIN, 25.0 mA);
			DM_DriveVoltage(testSite, PIN, 0.0 V);
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DM_TEST_FUNCTION_OS_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> DM_MeasureOS] OS test failed on pin: " + PIN + " | Detail: " + ex->Message);
		}

		return ret;
	}


	
	//PMU VOLTAGE & CURRENT MEASUREMENT ARCHITECTURE (From 7300) can configures NPLC noise integration time and applies settling delays immediately before reading measurements for maximum accuracy.
	int Module400Series::DM_MeasureVoltage(int testSite, String ^ PIN, double nplc, double measureDelay, double % result)
	{
		// [7300 DmTestFunction_MeasureVoltage]
		int ret = 0;

		try
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUSamplingTime(PIN, nplc, DM_CONST_SAMPLING_TIME_UNITS_PLC));
			tl->Util->WaitSecond(measureDelay);
			tl->CheckError(testSite, dm[testSite]->PMUMeasure(PIN, DM_CONST_PMU_MEASURE_VOLTAGE, result));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DM_TEST_FUNCTION_MEASURE_VOLTAGE_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> DM_MeasureVoltage] Voltage measurement failed on pin: " + PIN + " | Detail: " + ex->Message);
		}

		return ret;
	}

	int Module400Series::DM_MeasureVoltage(int testSite, String ^ PIN, double % result)
	{
		return DM_MeasureVoltage(testSite, PIN, 1.0, 0.001, result);
	}

	int Module400Series::DM_MeasureCurrent(int testSite, String ^ PIN, double nplc, double measureDelay, double % result)
	{
		// [7300 DmTestFunction_MeasureCurrent Algorithm]
		int ret = 0;

		try
		{
			tl->CheckError(testSite, dm[testSite]->ConfigurePMUSamplingTime(PIN, nplc, DM_CONST_SAMPLING_TIME_UNITS_PLC));
			tl->Util->WaitSecond(measureDelay);
			tl->CheckError(testSite, dm[testSite]->PMUMeasure(PIN, DM_CONST_PMU_MEASURE_CURRENT, result));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DM_TEST_FUNCTION_MEASURE_CURRENT_FAIL;
			tl->WriteToTracerAndFileLogger(testSite, testSite, ERROR, "[Module400Series -> DM_MeasureCurrent] Current measurement failed on pin: " + PIN + " | Detail: " + ex->Message);
		}

		return ret;
	}

	int Module400Series::DM_MeasureCurrent(int testSite, String ^ PIN, double % result)
	{
		return DM_MeasureCurrent(testSite, PIN, 1.0, 0.001, result);
	}


	
	int Module400Series::DM_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal)
	{
		// [7600 original architecture] Choosed Directly maps an input hardware trigger terminal to an output trigger terminal
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->MapTriggerInToTriggerOut(moduleAlias, inputTerminal, outputTerminal));
		return ret;
	}

	int Module400Series::DM_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth)
	{
		// [7600 original architecture] Generates a software-driven trigger pulse with specified pulse width
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->DriveSoftwareTrigger(moduleAlias, select, pulseWidth));
		return ret;
	}

	int Module400Series::DM_ConfigureTriggerEdgeLevel(int testSite, String ^ moduleAlias, int trigSource, int trigMode)
	{
		// [7600 original architecture] Configures trigger source and edge/level detection mode
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->ConfigureTriggerEdgeLevel(moduleAlias, trigSource, trigMode));
		return ret;
	}

	int Module400Series::DM_ConfigureTriggerEdgeLevelExtra(int testSite, String ^ moduleAlias, int trigSource, int trigMode, int ignoreTrigCount)
	{
		// [7600 original architecture] Configures trigger edge/level detection with ignored trigger count offset
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->ConfigureTriggerEdgeLevel(moduleAlias, trigSource, trigMode, ignoreTrigCount));
		return ret;
	}

	int Module400Series::DM_ConfigureInputTriggerSelect(int testSite, String ^ moduleAlias, int trigSource, double delayAfterTrig)
	{
		// [7600 original architecture] Configures module input trigger sources and post-trigger delay times
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->ConfigureInputTriggerSelect(moduleAlias, trigSource, delayAfterTrig));
		return ret;
	}

	int Module400Series::DM_ConfigureOutputTriggerSelect(int testSite, String ^ moduleAlias, int trigOutput0, int trigOutput1)
	{
		// [7600 original architecture] Configures module output trigger selections (trigOutput0, trigOutput1)
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->ConfigureOutputTriggerSelect(moduleAlias, trigOutput0, trigOutput1));
		return ret;
	}

	int Module400Series::DM_ConfigureReadPin_TriggerOutput(int testSite, String ^ pinAlias, int pinStatusSelect)
	{
		// [7600 original architecture] Configures digital read-pin status routing to trigger output lines
		int ret = 0;
		tl->CheckError(testSite, dm[testSite]->ConfigureReadPin_TriggerOutput(pinAlias, pinStatusSelect));
		return ret;
	}
}