/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			Globals.cpp
Purpose:		Provide interface to manage global variables (standard) and GlobalResult array.
UUTOffset:		Supported.
Version:		v1.1.0.0
----------------------------------------------------------------------*/
#pragma once
#include "TestFunction.h"  
#include "Globals.h"
#include "AppLevelException.h"

namespace Functions
{
	//Gloabal Variable & Result Functions
	void TestFunction::InitializeGlobalVariables(Site^ site)
	{
		/*****************************************************************************************************
		** InitializeGlobalVariables
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This method is to initialize the all the global variables.
		******************************************************************************************************/

		int siteIndex = 0;

#pragma region "Main Global Variables"
		//TechFLow Informations
		glob->tf._RTPlotter			= true;
		glob->tf.JumpOnFail			= false;
		glob->FileLog.IsWarning		= false;
		glob->tf.TestSite			= site->Index;	//Running techFlow Site	
		glob->tf.TotalUUTOffsets	= site->UUTOffsetResolver->UUTOffsets->Count;
		glob->tf.NumberOfSites		= glob->tf.TotalUUTOffsets;
		glob->tf.TestHead			= site->FlowEngine->HeadNumber;
		glob->TesterId				= site->FlowEngine->StationName;
		glob->tf.StageCount			= site->FlowEngine->Sites->Count/*site->FlowEngine->SiteGroupManager->SiteStages->StageCount*/;

		//Get Hardware Profile Path Location
		if (String::IsNullOrEmpty(site->Recipe->ResourceMappingFilePath) == false)
		{
			glob->HardwareProfile = site->Recipe->ResourceMappingFilePath;
		}
		else
		{
			CheckError(siteIndex, ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED);
		}

		//Get Test Recipe File Path
		glob->tf.RecipeFilePathDirectory = Path::GetDirectoryName(site->Recipe->RecipeFilePath);

		//Get Profile Name
		array<String^> ^ ArrString;
		array<Char>^ SpliterFormat = { '\\' };
		ArrString = glob->tf.RecipeFilePathDirectory->Split(SpliterFormat, System::StringSplitOptions::None);
		glob->tf.ProfileName = ArrString[5];

		//Get Project Name and Program Name from Techflow
		glob->tf.ProjectName = Path::GetFileName(glob->tf.RecipeFilePathDirectory);
		glob->tf.ProgramName = Path::GetFileName(site->DBPath);

		//DC Initialization
		glob->SMUStateSettingsManager			= gcnew array<Globals::SMUStateSettings>(glob->tf.NumberOfSites);
		glob->PMUStateSettingsManager			= gcnew array<Globals::PMUStateSettings>(glob->tf.NumberOfSites);
		glob->PEStateSettingsManager			= gcnew array<Globals::PEStateSettings>(glob->tf.NumberOfSites);
		glob->DMStateSettingsManager			= gcnew array<Globals::DMStateSettings>(glob->tf.NumberOfSites);
		glob->VectorFileManager					= gcnew array<Globals::VectorFileManagement>(glob->tf.NumberOfSites);
		glob->SourcePower_Status				= gcnew array<Globals::CM_RF_SourcePower_StateRecording>(glob->tf.NumberOfSites);
		glob->TimingSetPeriod					= gcnew array<array<double>^>(glob->tf.NumberOfSites);
		glob->DIO_DMStateSettingsManager		= gcnew array<Globals::DIO_DMStateSettings>(glob->tf.NumberOfSites);
		glob->TimingSetPeriod					= gcnew array<array<double>^>(glob->tf.NumberOfSites);
		glob->IOMModuleVIOStateSettingsManager	= gcnew array<Dictionary <String ^, int> ^>(glob->tf.NumberOfSites);
		glob->IOMPinValStateSettingsManager		= gcnew array<Dictionary <String ^, int> ^>(glob->tf.NumberOfSites);
		glob->IOMPortStateSettingsManager		= gcnew array<Globals::IOMPortStateSettings>(glob->tf.NumberOfSites);
		glob->DPinLevelSet						= gcnew array <List<Dictionary<String^, double>^>^>(glob->tf.NumberOfSites);
		glob->PEAttributeSet					= gcnew array <List<Dictionary<String^, bool>^>^>(glob->tf.NumberOfSites);

		//RF-Wlan
		glob->EvmAysncTask						= gcnew array<Dictionary <String ^, Task<double>^> ^>(glob->tf.NumberOfSites);
		glob->ExistEvmTaskList					= gcnew array<bool>(glob->tf.NumberOfSites);
		glob->EvmAsyncInfoCastResultToTF		= gcnew array < Globals::EvmAsyncInfo>(glob->tf.NumberOfSites);

		glob->SemAysncTask						= gcnew array<Dictionary <String ^, Task<SemMeasOutput^>^> ^>(glob->tf.NumberOfSites);
		glob->ExistSemTaskList					= gcnew array<bool>(glob->tf.NumberOfSites);
		glob->SemAsyncInfoCastResultToTF		= gcnew array < Globals::SemAsyncInfo>(glob->tf.NumberOfSites);

		//RF--Wolfer
		glob->WolferInfo_Status					= gcnew array <Globals::WolferInfo>(glob->tf.NumberOfSites);

		glob->freqcal_freq						= gcnew Dictionary<String^, array<double>^>();
		glob->freqcal_pout						= gcnew Dictionary<String^, array<double>^>();

		glob->freqHarcal_freq					= gcnew Dictionary<String^, array<double>^>();

		glob->txPathLoss_TXpath					= gcnew Dictionary<String^, array<int>^>();
		glob->txPathLoss_freq					= gcnew Dictionary<String^, array<double>^>();
		glob->txPathLoss_targetpout				= gcnew Dictionary<String^, array<double>^>();
		glob->txPathLoss_outIndex				= gcnew Dictionary<String^, array<int>^>();
		glob->txPathLoss_actualpout				= gcnew Dictionary<String^, array<double>^>();
		glob->txPathLoss_couppout				= gcnew Dictionary<String^, array<double>^>();
		glob->txPathLoss_source					= gcnew Dictionary<String^, array<double>^>();

		glob->g_txpath							= gcnew Dictionary<String^, int>();
		glob->g_rxpath							= gcnew Dictionary<String^, int>();
		glob->g_SelectTxPath					= gcnew Dictionary<String^, String^>();
		glob->g_SelectRxPath					= gcnew Dictionary<String^, String^>();
		glob->outIndex							= gcnew Dictionary<String^, int>();

		glob->freq_count						= gcnew Dictionary<String^, int>();
		glob->txpl_count						= gcnew Dictionary<String^, int>();
		glob->rxpl_count						= gcnew Dictionary<String^, int>();
		glob->rxrlpl_count						= gcnew Dictionary<String^, int>();
		glob->txrlpl_count						= gcnew Dictionary<String^, int>();
		glob->freqHar_count						= gcnew Dictionary<String^, int>();
		glob->txpl_Har_count					= gcnew Dictionary<String^, int>();
		glob->rxpl_Har_count					= gcnew Dictionary<String^, int>();

		glob->WolferCoupler_Pout				= gcnew array <double>(glob->tf.NumberOfSites);

		//BoardLoss 
		glob->boardLoss							= gcnew array<Dictionary<String^, double>^>(glob->tf.NumberOfSites);

		//ModulationFile
		glob->ModulationFile					= gcnew array<Dictionary<String^, String^>^>(glob->tf.NumberOfSites);

		//Check existence of path C:\\Aemulus\\Debug
		if (!Directory::Exists(FILE_CONST_AEM_DEBUG))
		{
			Directory::CreateDirectory(FILE_CONST_AEM_DEBUG);
		}

		//Check existence of path C:\\Aemulus\\TesterInfo
		if (!Directory::Exists(FILE_CONST_TESTER_INFO))
		{
			Directory::CreateDirectory(FILE_CONST_TESTER_INFO);
		}

		//ResultType
		glob->ResultType			= gcnew array <Globals::techFlowDataType>(glob->tf.NumberOfSites);

		//glob->AppsCal.AppsCalFactorCount = 0;
		glob->ResultOffset			= gcnew Dictionary <String ^, array<double> ^>();  //Fixed Offset 

		//Test Properties
		glob->TestProperty			= gcnew array<Globals::TestPropertyStruct>(glob->tf.NumberOfSites);
		glob->tf.TPropertyTotalSite = glob->tf.NumberOfSites;

		//Test Parameter Properties
		glob->TestNameWithTestNumber	= gcnew Dictionary <String^, String^>();
		glob->tp_TestItem				= gcnew Dictionary <String ^, String ^>();
		glob->tp_TestNumber				= gcnew Dictionary <String ^, String ^>();
		glob->tp_TestLimitLo			= gcnew Dictionary <String ^, String ^>();
		glob->tp_TestLimitHi			= gcnew Dictionary <String ^, String ^>();
		glob->tp_UnitPrefix				= gcnew Dictionary <String ^, String ^>();
		glob->tp_Units					= gcnew Dictionary <String ^, String ^>();
		glob->tp_DataType				= gcnew Dictionary <String ^, String ^>();
		glob->tp_EvalMode				= gcnew Dictionary <String ^, String ^>();
		glob->tp_BinName				= gcnew Dictionary <String ^, String ^>();
		glob->tp_HBin					= gcnew Dictionary <String ^, String ^>();
		glob->tp_SBin					= gcnew Dictionary <String ^, String ^>();
		glob->tp_Bypass					= gcnew Dictionary <String ^, int>();
		glob->tp_FTLimitLo				= gcnew Dictionary <String ^, String ^>();
		glob->tp_FTLimitHi				= gcnew Dictionary <String ^, String ^>();
		glob->tp_QALimitLo				= gcnew Dictionary <String ^, String ^>();
		glob->tp_QALimitHi				= gcnew Dictionary <String ^, String ^>();

		//Error Handling Properties
		glob->ErrorInfo = gcnew array<Globals::ErrorHandlingStruct>(glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
#pragma region "VectorFile"
			//VectorFile
			glob->VectorFileManager[siteIndex].DM_DPinGroup								= gcnew Dictionary <String ^, int>();
			glob->VectorFileManager[siteIndex].SCLKChannel								= gcnew Dictionary <String ^, int>();
			glob->VectorFileManager[siteIndex].SDATAChannel								= gcnew Dictionary <String ^, int>();
			glob->VectorFileManager[siteIndex].VectorTimingSet							= gcnew Dictionary <String ^, int>();
			glob->VectorFileManager[siteIndex].l_Read_Operation_Counter					= gcnew Dictionary <String ^, int>();
			glob->VectorFileManager[siteIndex].l_Start_Read_Location_Speed				= gcnew Dictionary <int, array<String^>^>();
			glob->VectorFileManager[siteIndex].l_Start_Read_Location_Single_VectorFile	= gcnew Dictionary <int, array<int>^>();
			glob->VectorSetNumber														= gcnew Dictionary <String ^, int>();
			glob->VectorFileDirectory													= System::IO::Path::GetDirectoryName(site->Recipe->FlowFilePath) + "\\" + "VectorFileFolder";
#pragma endregion "VectorFile"

#pragma region "RF-Wlan"

			glob->EvmAysncTask[siteIndex]		= gcnew Dictionary <String ^, Task<double>^>();
			glob->ExistEvmTaskList[siteIndex]	= false;

			glob->SemAysncTask[siteIndex]		= gcnew Dictionary <String ^, Task<SemMeasOutput^>^>();
			glob->ExistSemTaskList[siteIndex]	= false;

#pragma endregion "RF-Wlan"

#pragma region "RF-Wolfer"

			glob->WolferInfo_Status[siteIndex].freqcalFile								= gcnew Dictionary <String ^, String ^>();
			glob->WolferInfo_Status[siteIndex].freqHarcalFile							= gcnew Dictionary <String ^, String ^>();
			glob->WolferInfo_Status[siteIndex].txplFile									= gcnew Dictionary <String ^, String ^>();
			glob->WolferInfo_Status[siteIndex].rxplFile									= gcnew Dictionary <String ^, String ^>();
			glob->WolferInfo_Status[siteIndex].txHarplFile								= gcnew Dictionary <String ^, String ^>();
			glob->WolferInfo_Status[siteIndex].rxHarplFile								= gcnew Dictionary <String ^, String ^>();
			glob->WolferInfo_Status[siteIndex].wolferIOFile								= gcnew Dictionary <String ^, String ^>();

#pragma endregion "RF-Wolfer"

#pragma region "AM PreviousState"
			//AM - PreviousState
			glob->SMUStateSettingsManager[siteIndex].SMUStateDriveVoltage				= gcnew Dictionary <String ^, double>();
			glob->SMUStateSettingsManager[siteIndex].SMUStateDriveCurrent				= gcnew Dictionary <String ^, double>();
			glob->SMUStateSettingsManager[siteIndex].SMUStateClampVoltage				= gcnew Dictionary <String ^, double>();
			glob->SMUStateSettingsManager[siteIndex].SMUStateClampCurrent				= gcnew Dictionary <String ^, double>();
			glob->SMUStateSettingsManager[siteIndex].SMUStateOutputFunction				= gcnew Dictionary <String ^, int>();
			glob->SMUStateSettingsManager[siteIndex].SMUStateNPLC						= gcnew Dictionary <String ^, double>();
#pragma endregion "AM- PreviousState"

#pragma region "DM PreviousState"
			//DM - PreviousState
			glob->PMUStateSettingsManager[siteIndex].PMUStateDriveVoltage				= gcnew Dictionary <String ^, double>();
			glob->PMUStateSettingsManager[siteIndex].PMUStateDriveCurrent				= gcnew Dictionary <String ^, double>();
			glob->PMUStateSettingsManager[siteIndex].PMUStateClampVoltage				= gcnew Dictionary <String ^, double>();
			glob->PMUStateSettingsManager[siteIndex].PMUStateClampCurrent				= gcnew Dictionary <String ^, double>();
			glob->PMUStateSettingsManager[siteIndex].PMUStateOutputFunction				= gcnew Dictionary <String ^, int>();
			glob->PMUStateSettingsManager[siteIndex].PMUStateSense						= gcnew Dictionary <String ^, int>();
			glob->PMUStateSettingsManager[siteIndex].PMUStateNPLC						= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVIH							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVIL							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVOH							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVOL							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateIOH							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateIOL							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVCH							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVCL							= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateVTERM						= gcnew Dictionary <String ^, double>();
			glob->PEStateSettingsManager[siteIndex].PEStateInputTermEnable				= gcnew Dictionary <String ^, bool>();
			glob->PEStateSettingsManager[siteIndex].PEStateHVEnable						= gcnew Dictionary <String ^, bool>();
			glob->PEStateSettingsManager[siteIndex].PEStateActiveLoadEnable				= gcnew Dictionary <String ^, bool>();
			glob->PEStateSettingsManager[siteIndex].PEStateDifferentialComparatorEnable = gcnew Dictionary <String ^, bool>();
			glob->DMStateSettingsManager[siteIndex].DMStateOperationMode				= gcnew Dictionary <String ^, int>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVIH						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVIL						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVOH						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVOL						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateIOH						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateIOL						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVCH						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVCL						= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStateVTERM					= gcnew Dictionary <String ^, double>();
			glob->DIO_DMStateSettingsManager[siteIndex].DIOStatePinValue				= gcnew Dictionary <String ^, int>();
			glob->DPinLevelSet[siteIndex]												= gcnew List<Dictionary<String^, double>^>();
			glob->PEAttributeSet[siteIndex]												= gcnew List<Dictionary<String^, bool>^>();
#pragma endregion "DM- PreviousState"

#pragma region "IOM PreviousState"
			//IOM PreviousState
			glob->IOMModuleVIOStateSettingsManager[siteIndex] = gcnew Dictionary <String ^, int>();
			glob->IOMPinValStateSettingsManager[siteIndex] = gcnew Dictionary <String ^, int>();
			glob->IOMPortStateSettingsManager[siteIndex].PortValue = gcnew Dictionary <String ^, int>();
			glob->IOMPortStateSettingsManager[siteIndex].PortDirection = gcnew Dictionary <String ^, int>();
#pragma endregion "IOM- PreviousState"

#pragma region "BoardLoss"
			glob->boardLoss[siteIndex] = gcnew Dictionary<String^, double>();
#pragma endregion "BoardLoss"

#pragma region "ModulationFile"
			glob->ModulationFile[siteIndex] = gcnew Dictionary<String^, String^>();
#pragma endregion "ModulationFile"

#pragma region "ResultType"
			glob->ResultType[siteIndex].DoubleTypeResult = 999.99;
			glob->ResultType[siteIndex].IntTypeResult = 999;
			glob->ResultType[siteIndex].StringTyperesult = nullptr;
#pragma endregion "ResultType"

#pragma region "TestProperty"
			glob->TestProperty[siteIndex].TestParaNameWithSiteIndex			= gcnew Dictionary <String ^, String ^>();
			glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex	= gcnew Dictionary <String ^, String ^>();			
			// Flow Step (Control Step, Test Step)
			glob->TestProperty[siteIndex].totalFlowStep						= 0;
			glob->TestProperty[siteIndex].FlowStepItemName					= gcnew array<String^>(0);
			glob->TestProperty[siteIndex].FlowStepItemDisplayName			= gcnew array<String^>(0);
			glob->TestProperty[siteIndex].FlowStepItemExecuted				= gcnew array<bool>(0);
#pragma endregion "TestProperty"

#pragma region "TestProperty"
			
#pragma endregion "TestProperty"
		}

#pragma endregion "Main Global Variables"

#pragma region "RsrcManager"

		glob->RsrcManager.RsrcMngr	= gcnew array<ResourceManager ^>(glob->tf.NumberOfSites);
		glob->RsrcManager.RsrcACM	= gcnew array<String ^>(glob->tf.NumberOfSites);
		glob->RsrcManager.RsrcCM	= gcnew array<String ^>(glob->tf.NumberOfSites);
		glob->RsrcManager.RsrcDM	= gcnew array<String ^>(glob->tf.NumberOfSites);
		glob->RsrcManager.RsrcIOM	= gcnew array<String ^>(glob->tf.NumberOfSites);
		glob->RsrcManager.RsrcSMU	= gcnew array<String ^>(glob->tf.NumberOfSites);
		glob->RsrcManager.RsrcTMU	= gcnew array<String ^>(glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			glob->RsrcManager.RsrcMngr[siteIndex] = gcnew ResourceManager(glob->HardwareProfile, 0, siteIndex);

			for each (String ^ Rsrc in glob->RsrcManager.RsrcMngr[siteIndex]->MapNames)
			{
				Resource ^ HardwareRsrc = glob->RsrcManager.RsrcMngr[siteIndex]->ResolveResource(Rsrc)[0];

				if ((HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true))
				{
					glob->RsrcManager.RsrcSMU[siteIndex] = Rsrc;
				}
				if (HardwareRsrc->Hierarchy[0]->StartsWith("DM") == true)
				{
					glob->RsrcManager.RsrcDM[siteIndex] = Rsrc;
				}
				if (HardwareRsrc->Hierarchy[0]->StartsWith("ACM") == true)
				{
					glob->RsrcManager.RsrcACM[siteIndex] = Rsrc;
				}
				if (HardwareRsrc->Hierarchy[0]->StartsWith("CM") == true)
				{
					glob->RsrcManager.RsrcCM[siteIndex] = Rsrc;
				}
				if (HardwareRsrc->Hierarchy[0]->StartsWith("TMU") == true)
				{
					glob->RsrcManager.RsrcTMU[siteIndex] = Rsrc;
				}
				if (HardwareRsrc->Hierarchy[0]->StartsWith("IOM") == true)
				{
					glob->RsrcManager.RsrcIOM[siteIndex] = Rsrc;
				}
			}
		}

#pragma endregion "RsrcManager"

#pragma region "User Defined Globals"

		glob->runTimeError							= gcnew array<bool>(glob->tf.NumberOfSites);
		glob->dcRunTimeError						= gcnew array<bool>(glob->tf.NumberOfSites);
		glob->isCriticalBinFail						= gcnew array<bool>(glob->tf.NumberOfSites);
		glob->OnFailExcuteFlowItem					= gcnew array<String ^>(glob->tf.NumberOfSites);
		glob->OnPassExcuteFlowItem					= gcnew array<String ^>(glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			glob->runTimeError[siteIndex]			= false;
			glob->dcRunTimeError[siteIndex]			= false;
			glob->isCriticalBinFail[siteIndex]		= false;
			glob->OnFailExcuteFlowItem[siteIndex]	= String::Empty;
			glob->OnPassExcuteFlowItem[siteIndex]	= String::Empty;
		}

#pragma endregion "User Defined Globals"
	}
	void TestFunction::ResetGlobalVariables(Site^ site)
	{
		/*****************************************************************************************************
		** ResetGlobalVariables
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This method is to reset the all dynamic global variables to zero.
		******************************************************************************************************/

		//<Info> Determine if techFlow is set up to run Exit-First-Fail mode.
		//This variable is used to prevent execution on a site that has failed a test.
		glob->tf.JumpOnFail = site->Sequencer->JumpOnFailSettingBySite->Enable;

		if (glob->AWV.Debug == 1)
		{
			for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				WriteToLogger(siteIndex, "Reset Global Variables.");
				WriteToLogger(siteIndex, "JumpOnFail = " + glob->tf.JumpOnFail);
			}
		}

	}
	void TestFunction::InitializeGlobalResult(int TotalSite)
	{
		/*****************************************************************************************************
		** InitializeGlobalResult
		**		TotalSite	- This is total physical site. (Note: UUT offset index for the
		**					  MultiUUTOffsets project or techFlow sites for Index Parallel project.
		** Descriptions:
		**		This is a method to initialize the GlobalResult dictionary storage.
		******************************************************************************************************/

		int i = 0;

		glob->GlobalResult	= gcnew array<Dictionary<String^, Object^>^>(TotalSite);
		glob->TestResults	= gcnew array<array<Object^>^>(TotalSite);
		for (i = 0; i < glob->GlobalResult->Length; i++)
		{
			glob->GlobalResult[i] = gcnew Dictionary<String^, Object^>();
		}

		if (glob->AWV.Debug == 1)
		{
			for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				WriteToLogger(siteIndex, "Initialized Global Results Storage.");
			}
		}
	}
	void TestFunction::SetGlobalResult(String ^ Identifier, int siteIndex, double Result)
	{
		/*****************************************************************************************************
		** SetGlobalResult
		**		Identifier	- This is the specific string type identifier or ContainsKey to be add in
		**					  glob->GlobalResult dictionary.
		**		siteIndex	- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**					  project or techFlow sites for Index Parallel project.)
		**		Result		- This is the specific double type result to be add as value in glob->GlobalResult
		**					  dictionary.
		** Descriptions:
		**		This is a method to assign test results to GlobalResult array and check if the global result
		**      index has been used by other identifiers.
		******************************************************************************************************/

		if (!glob->GlobalResult[siteIndex]->ContainsKey(Identifier))
		{
			glob->GlobalResult[siteIndex]->Add(Identifier, Result);
		}
		else
		{
			glob->GlobalResult[siteIndex]->Remove(Identifier);
			glob->GlobalResult[siteIndex]->Add(Identifier, Result);
		}

		if (glob->AWV.Debug == 1)
		{
			if (glob->tf.StageCount > 1) //Index Parallel 
			{
				WriteToTracerLogger(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "Site " + siteIndex +
					":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result);
				FileLogging(siteIndex, LOGGER_INFO_TYPE, "Site " + siteIndex +
					":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result + "," + ",");
			}
			else //Multi UUTOffsets 
			{
				WriteToTracerLogger(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "UUT Offset Site " + siteIndex +
					":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result);
				FileLogging(siteIndex, LOGGER_INFO_TYPE, "UUT Offset Site " + siteIndex +
					":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result + "," + ",");
			}
		}
	}
	void TestFunction::ResetGlobalResult(int TotalSite)
	{
		/*****************************************************************************************************
		** ResetGlobalResult
		**		TotalSite	- This is total physical site. (Note: UUT offset index for the
		**					  MultiUUTOffsets project or techFlow sites for Index Parallel project.
		** Descriptions:
		**		This test method is to reset or remove all dictionary element from the global result during
		**		the test program initialization.
		******************************************************************************************************/

		int siteIndex = 0;

		for (siteIndex = 0; siteIndex < TotalSite; siteIndex++)
		{
			try
			{
				//Remove all Dictionary element
				glob->GlobalResult[siteIndex]->Clear();
			}
			catch (Exception ^ ex) //Dictionary is empty
			{
				glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
			}
		}

		if (glob->AWV.Debug == 1)
		{
			for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				WriteToLogger(siteIndex, "Reset Global Results Storage.");
			}
		}
	}
	Object ^ TestFunction::GetGlobalResult(String ^ Identifier, int siteIndex)
	{
		/*****************************************************************************************************
		** GetGlobalResult
		**		Identifier	- This is the specific string type identifier or ContainsKey in glob->GlobalResult dictionary.
		**		siteIndex	- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**					  project or techFlow sites for Index Parallel project.)
		** Descriptions:
		**		This test method is to get the global result from the GetResult dictionary based on input
		**		identifier.
		******************************************************************************************************/

		try
		{
			//Get results from global result based on index
			if (!glob->GlobalResult[siteIndex]->ContainsKey(Identifier))
			{
				return CONST_INVALID_RESULT;
			}

			if (glob->AWV.Debug == 1)
			{
				if (glob->tf.StageCount > 1) //Index Parallel 
				{
					WriteToTracerLogger(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier]);
					FileLogging(siteIndex, LOGGER_INFO_TYPE, "Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier] + "," + ",");
				}
				else //Multi UUTOffsets
				{
					WriteToTracerLogger(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "UUT Offset Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier]);
					FileLogging(siteIndex, LOGGER_INFO_TYPE, "UUT Offset Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier] + "," + ",");
				}
			}
		}
		catch (Exception ^ ex)
		{
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
		}

		return glob->GlobalResult[siteIndex][Identifier];
	}

	//Generic AppWideVariables Function  
	int TestFunction::LoadGenericAppsWideVariable(Site^ site)
	{
		/*****************************************************************************************************
		** LoadGenericAppsWideVariable
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This test method is to load all the generic App-Wide Variables from techFlow during Load Phase.
		******************************************************************************************************/

		int ret = 0;
		int siteIndex = 0;

		//<Info> "Debug" App Wide Variables  
		if (tf_AppWideVariable_Exist("debug"))
		{
			glob->AWV.Debug = (int)(tf_AppWideVariable_Cast("debug"));
		}
		else
		{
			glob->TcrLgr.GlobalErrorMessage = "Debug mode unspecified!";
			CheckError(siteIndex, ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED);
		}
		if (glob->AWV.Debug == 1)
		{
			for (siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				WriteToLogger(siteIndex, "Debug: " + glob->AWV.Debug);
			}
		}

		//<Info> "PowerLineFrequency" App Wide Variables
		//		  TH = Thailand = 50Hz
		//		  US = United States of America = 60Hz
		//		  MY = Malaysia = 50Hz
		//		  CN = China = 50Hz
		if (tf_AppWideVariable_Exist("PowerLineFrequency"))
		{
			int PowerLineFreqGet = 0;
			PowerLineFreqGet = (int)(tf_AppWideVariable_Cast("PowerLineFrequency"));

			if (PowerLineFreqGet == 0)
			{
				glob->AWV.PowerLineFreq = 50;
			}
			else if (PowerLineFreqGet == 1)
			{
				glob->AWV.PowerLineFreq = 60;
			}
			else
			{
				glob->TcrLgr.GlobalErrorMessage = "Invalid power line frequency specified!";
				CheckError(siteIndex, ER_CONST_INVALID_SETTING);
			}
		}
		else
		{
			glob->TcrLgr.GlobalErrorMessage = "Power line frequency unspecified!";
			CheckError(siteIndex, ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED);
		}
		for (siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, "Power Line Frequency: " + glob->AWV.PowerLineFreq + "Hz");
		}


		//<Info> "offline" App Wide Variables
		if (tf_AppWideVariable_Exist("offline"))
		{
			glob->AWV.Offline = (bool)(tf_AppWideVariable_Cast("offline"));
		}
		else
		{
			glob->TcrLgr.GlobalErrorMessage = "Offline mode unspecified!";
			CheckError(siteIndex, ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED);
		}
		for (siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, "Offline: " + glob->AWV.Offline);
		}


		//<Info> "DeviceName" App Wide Variables
		if (tf_AppWideVariable_Exist("DeviceName"))
		{
			glob->AWV.DeviceName = (String ^)(tf_AppWideVariable_Cast("DeviceName"));
		}
		else
		{
			glob->TcrLgr.GlobalErrorMessage = "DeviceName unspecified!";
			CheckError(siteIndex, ER_CONST_READ_FILE_ERROR);
		}
		for (siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, "DeviceName: " + glob->AWV.DeviceName);
		}

		//<Info> "AmsrfControllerMode" App Wide Variables
		if (tf_AppWideVariable_Exist("AmsrfControllerMode"))
		{
			glob->AWV.AmsrfControllerMode = (int)(tf_AppWideVariable_Cast("AmsrfControllerMode"));
		}
		else
		{
			glob->TcrLgr.GlobalErrorMessage = "AmsrfControllerMode unspecified!";
			CheckError(siteIndex, ER_CONST_READ_FILE_ERROR);
		}
		for (siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, "AmsrfControllerMode: " + glob->AWV.AmsrfControllerMode);
		}

		//<Info> "DMPinGroup" App Wide Variables
		//		  0 = DPin Group 0 and 1 (All)
		//		  1 = Dpin Group 0 for Odd Site, Dpin Group 1 for Even Site

		//if (tf_AppWideVariable_Exist("DMPinGroup"))
		//{
		//	glob->AWV.DMPinGroup = (int)(tf_AppWideVariable_Cast("DMPinGroup"));
		//}
		//else
		//{
		//	glob->TcrLgr.GlobalErrorMessage = "DMPinGroup unspecified!";
		//	CheckError(siteIndex, ER_CONST_READ_FILE_ERROR);
		//}
		for (siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, "DMPinGroup: " + glob->AWV.DMPinGroup);
		}

		if (tf_AppWideVariable_Exist("BoardLossMode"))
		{
			glob->AWV.BoardLossMode = (int)(tf_AppWideVariable_Cast("BoardLossMode"));
		}
		else
		{
			glob->TcrLgr.GlobalErrorMessage = "BoardLoss mode unspecified!";
			CheckError(siteIndex, ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED);
		}

		if (tf_AppWideVariable_Exist("DMInitOption"))
		{
			glob->AWV.DMInitOption = (int)(tf_AppWideVariable_Cast("DMInitOption"));
		}
		else
		{
			glob->AWV.DMInitOption = 0xf;
		}

		if (tf_AppWideVariable_Exist("AMInitOption"))
		{
			glob->AWV.AMInitOption = (int)(tf_AppWideVariable_Cast("AMInitOption"));
		}
		else
		{
			glob->AWV.AMInitOption = 0xf;
		}
		if (tf_AppWideVariable_Exist("CMInitOption"))
		{
			glob->AWV.CMInitOption = (int)(tf_AppWideVariable_Cast("CMInitOption"));
		}
		else
		{
			glob->AWV.CMInitOption = 0xf;
		}
		if (tf_AppWideVariable_Exist("IOMInitOption"))
		{
			glob->AWV.IOMInitOption = (int)(tf_AppWideVariable_Cast("IOMInitOption"));
		}
		else
		{
			glob->AWV.IOMInitOption = 0xf;
		}
		return ret;
	}

	//Multi-UUTOffset Run Test Function 
	void TestFunction::IsRunTest(Site^ site, array<bool>^ RunTest)
	{
		/*****************************************************************************************************
		** IsRunTest
		** Arguments:
		**		RunTest - Returns an array that tells whether or not to perform test on any of the sites
		**				   (UUTOffset).
		**				   An array of sufficient size must be allocated by the caller function.
		** Descriptions:
		**		This method is to check whether to execute tests on the sites (UUTOffset) based on the
		**		following rules:
		**			If the UUTOffset is active (ED setting):
		**			If jump_on_fail is turned on, check whether any of previous tests has failed:
		**			- False: Continue run next tests (RunTest = true)
		**			- True: Do not run remaining tests (RunTest = false)
		******************************************************************************************************/

		AFlowItem^ item					= site->CurrentFlowItem;
		Type^ FlowType					= item->GetType();
		bool isCurrentFlowItemByPassed	= false;
		String ^ currControlItemName	= String::Empty;
		String ^ currTestItemName		= String::Empty;

		if (FlowType == TestItem::typeid)
		{
			currTestItemName			= (String ^)tf_TestItem_Name();
			isCurrentFlowItemByPassed	= tf_TestItem_BypassStatus();
		}

		if (FlowType == ControlItem::typeid)
		{
			currControlItemName			= (String ^)tf_ControlItem_Name();
			isCurrentFlowItemByPassed	= tf_ControlItem_BypassStatus();
		}

		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			RunTest[siteIndex]			= false;
			AUUTOffset^ UUTOffset		= site->UUTOffsetResolver->UUTOffsets[siteIndex];

			if (UUTOffset->Active)
			{
				//copy from 5600 test library
				if (glob->RunTimeError[siteIndex] == true)
				{
					RunTest[siteIndex] = false;  //FALSE
				}
				else
				{
					if (glob->tf.JumpOnFail == true)
					{
						if (site->ResultsByOffset[UUTOffset]->CurrentResult->IfAnyTestParameterFailed == false)
						{
							RunTest[siteIndex] = true;
						}
						else
						{
							RunTest[siteIndex] = false;  //false
						}
					}
					else
					{
						RunTest[siteIndex] = true;
					}
				}
			}

			//Log the active site
		ENDUUTTOFFSETRUNTESTCHECK:	if (glob->AWV.Debug == 1)
		{
			WriteToLogger(siteIndex, "Is Run Test = " + RunTest[siteIndex]);
		}
		}




	}
	void TestFunction::ThreadingInfo(Site^ site, bool  RF_ResourceNeeded)
	{
		glob->ThreadingSite					= gcnew List<List<int>^>();
		List<List<int>^> ^ThreadingSiteRF	= gcnew List<List<int>^>();
		List<List<int>^> ^ThreadingSiteDC	= gcnew List<List<int>^>();

		List<int>^ThreadingSiteRFInfo;
		List<int>^ThreadingSiteDCInfo;

		if (RF_ResourceNeeded == false)
		{
			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				if (site->UUTOffsetResolver->UUTOffsets[i]->Active)
				{
					ThreadingSiteDCInfo = gcnew List<int>();
					ThreadingSiteDCInfo->Add(i);

					ThreadingSiteDC->Add(ThreadingSiteDCInfo);
				}
			}

			glob->ThreadingSite = ThreadingSiteDC;
		}
		else
		{
			if (glob->AMSRFInfo->Contains("AMSRF0") || glob->AMSRFInfo->Contains("AMSRF1"))
			{
				if (glob->AMSRFInfo->Contains("AMSRF0"))
				{
					ThreadingSiteRFInfo = gcnew List<int>();
					for (int i = 0; i < glob->Amsrf0Site->Length; i++)
					{
						if (site->UUTOffsetResolver->UUTOffsets[glob->Amsrf0Site[i]]->Active)
						{
							ThreadingSiteRFInfo->Add(glob->Amsrf0Site[i]);
						}
					}
					ThreadingSiteRF->Add(ThreadingSiteRFInfo);
				}
				if (glob->AMSRFInfo->Contains("AMSRF1"))
				{
					ThreadingSiteRFInfo = gcnew List<int>();
					for (int i = 0; i < glob->Amsrf1Site->Length; i++)
					{
						if (site->UUTOffsetResolver->UUTOffsets[glob->Amsrf1Site[i]]->Active)
						{
							ThreadingSiteRFInfo->Add(glob->Amsrf1Site[i]);
						}
					}
					ThreadingSiteRF->Add(ThreadingSiteRFInfo);
				}
			}
			else if (glob->AMSRFInfo == "NA")
			{
				for (int i = 0; i < glob->tf.NumberOfSites; i++)
				{
					if (site->UUTOffsetResolver->UUTOffsets[i]->Active)
					{
						ThreadingSiteRFInfo = gcnew List<int>();
						ThreadingSiteRFInfo->Add(i);

						ThreadingSiteRF->Add(ThreadingSiteRFInfo);
					}
				}
			}

			glob->ThreadingSite = ThreadingSiteRF;
		}

		glob->TotalThread = glob->ThreadingSite->Count;

	}

	//Initiliaze Test Program
	int TestFunction::InitializeProgram(Site ^ site)
	{
		/*****************************************************************************************************
		** InitializeProgram
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This is a method to initialize all the test program related functions in load phase.
		******************************************************************************************************/

		int ret = 0;

		//To instanstiate the tracer and file logger
		glob->tf.RecipeFilePathDirectory = System::IO::Path::GetDirectoryName(site->Recipe->FlowFilePath);
		glob->tf.RecipeFileName = Path::GetFileName(glob->tf.RecipeFilePathDirectory);

		if (tf_AppWideVariable_Exist("debug"))
		{
			glob->AWV.Debug = (int)(tf_AppWideVariable_Cast("debug"));
		}
		if (tf_AppWideVariable_Exist("AutoPat2Pbin"))
		{
			glob->AWV.AutoPat2Pbin = (bool)(tf_AppWideVariable_Cast("AutoPat2Pbin"));
		}

		InitializeGlobalVariables(site);
		InitializeLogger(site);
		//InitializeGlobalVariables(site);
		InitializeGlobalResult(glob->tf.NumberOfSites); //Supported for MultiUUTOffest's test result 
		LoadGenericAppsWideVariable(site);
		ResetGlobalVariables(site);
		ResetGlobalResult(glob->tf.NumberOfSites);
		InitializeTestCondProperty();

		//BoardLoss Mode
		if (glob->AWV.BoardLossMode == 1)
		{
			boardLossFileInit(site);
		}

		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++) {
			WriteToLogger(siteIndex, "Initialized program.");
		}

		//CorrFactor
		corrFactorFileInit(site);

		return ret;
	}
	void TestFunction::InitializeTestCondProperty(void)
	{
		/*****************************************************************************************************
		** InitializeTestCondProperty
		** Descriptions:
		**		This method is to instanstiate test condition properties.
		******************************************************************************************************/

		glob->TProperty = gcnew array<Globals::TestProperty_tf>(glob->tf.TPropertyTotalSite);

		for (int siteIndex = 0; siteIndex < glob->tf.TPropertyTotalSite; siteIndex++) {
			glob->TProperty[siteIndex].TC_dict = gcnew Dictionary <String ^, String ^>();
			WriteToLogger(siteIndex, "Initialized Test Condition Properties {TProperty[" + siteIndex + "].TC_dict}");
		}
	}

	//CheckError & Logger Utilities Functions
	int TestFunction::CHECKERROR(int siteIndex, int errorCode, int ErrorLineNumber, String^ FileName)
	{
		/*****************************************************************************************************
		** CheckError
		** Arguments:
		**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**						  project or techFlow sites for Index Parallel project.)
		**		errorCode		- This is the error code.
		**		ErrorLineNumber - This is the line number in test program where last error happens.
		**		FileName		- This is the file name of current executing function in test program where the
		**						  last error happens.
		** Descriptions:
		**		This method is to check whether the last operation has any error, by interpreting the given
		**		errorCode. If error happens (non-zero return code), an exception will be thrown to techFlow,
		**		together with the error message as well as the line where it happens.
		******************************************************************************************************/

		int ret = 0;
		String ^ ErrorMessageLog = String::Empty;
		String ^ ErrorMessage = String::Empty;
		String ^ WarningMessageType = String::Empty;
		StringBuilder ^ ReturnErrorMessage = gcnew StringBuilder(256);
		String ^ ExceptionMessageFormat = "\nSite Index={0};\nFile Name={1};\nLine Number={2};\nError Code={3};\nError Message={4}";

		if (errorCode != 0)
		{
			// <summary>
			// Check AEM resources (error code starts with 0xAE).
			// </summary>
			if (errorCode.ToString("X")->StartsWith("AE")) //Check whether it's AEM resources (error code starts with 0xAE)
			{
				// <summary>
				// Facility code - 9 for General[0xAE09 = General].
				// </summary>
				if (errorCode.ToString("X")->StartsWith("AE09"))
				{
					ErrorMessage = "Aemulus PXIE General error";
				}

				// <summary>
				// Facility code - 7 for SMU[0xAE07 = AemSMU].
				// </summary>
#if SMU_ENABLE 
				if (errorCode.ToString("X")->StartsWith("AE07"))
				{
					ret = smu[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcSMU[siteIndex], errorCode, ErrorMessage);
					ErrorMessage = ErrorMessage + " [Aemulus PXIE SMU error. Refer to \"Error Codes Reference Guide.pdf\" for details]";
				}
#endif 

				// <summary>
				// Facility code - 8 for IOM[0xAE08 = AemIOM].
				// </summary>				
#if DIO_ENABLE 
				if (errorCode.ToString("X")->StartsWith("AE08"))
				{
					ret = dio[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcIOM[siteIndex], errorCode, ErrorMessage);
					ErrorMessage = ErrorMessage + " [Aemulus PXIE IOM error. Refer to \"Error Codes Reference Guide.pdf\" for details]";
				}
#endif

				// <summary>
				// Facility code - B for DM[0xAE0B = AemDM].
				// </summary>
#if DM_ENABLE 
				if (errorCode.ToString("X")->StartsWith("AE0B") || errorCode.ToString("X")->StartsWith("AE04"))
				{
					ret = dm[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcDM[siteIndex], errorCode, ReturnErrorMessage);
					ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = ErrorMessage + " [Aemulus PXIE DM error. Refer to \"Error Codes Reference Guide.pdf\" for details]";
				}
#endif 

				// <summary>
				// Facility code - E for CM[0xAE0E = AemCM].
				// </summary>
#if CM_ENABLE 
				if (errorCode.ToString("X")->StartsWith("AE0E"))
				{
					ret = cm[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcCM[siteIndex], errorCode, ReturnErrorMessage);
					ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = ErrorMessage + " [Aemulus PXIE CM error. Refer to \"Error Codes Reference Guide.pdf\" for details]";
				}
#endif 

				// <summary>
				// Facility code - F for ACM[0xAE0F = AemACM].
				// </summary>
#if ACM_ENABLE
				if (errorCode.ToString("X")->StartsWith("AE0F"))
				{
					ret = acm[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcACM[siteIndex], errorCode, ReturnErrorMessage);
					ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = ErrorMessage + " [Aemulus PXIE ACM error. Refer to \"Error Codes Reference Guide.pdf\" for details]";
				}
#endif 

				// <summary>
				// Facility code - C for TMU[0xAE0C = AemTMU].
				// </summary>
#if TMU_ENABLE 
				if (errorCode.ToString("X")->StartsWith("AE0C"))
				{
					ret = tmu[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcTMU[siteIndex], errorCode, ReturnErrorMessage);
					ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = ErrorMessage + " [Aemulus PXIE TMU error. Refer to \"Error Codes Reference Guide.pdf\" for details]";
				}
#endif 

				// <summary>
				// Facility code - 10 for AMB7600[0xAE10 = AMB7600].
				// </summary>
				else if (errorCode.ToString("X")->StartsWith("AE10"))
				{
					switch (errorCode)
					{
					case ER_OPERATION_HALTED_BY_USER:	ErrorMessage = "ER_OPERATION_HALTED_BY_USER; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_PREREQUISITE_NOT_MET:		ErrorMessage = "ER_PREREQUISITE_NOT_MET; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_ILLEGAL_OPERATION:			ErrorMessage = "ER_ILLEGAL_OPERATION; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_NO_CALIBRATION_RECORD:		ErrorMessage = "ER_NO_CALIBRATION_RECORD; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_CALIBRATION_DUE:			ErrorMessage = "ER_CALIBRATION_DUE; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_INVALID_USER_INPUT:			ErrorMessage = "ER_INVALID_USER_INPUT; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_INVALID_QUERY:				ErrorMessage = "ER_INVALID_QUERY; ErrorCode: 0x" + errorCode.ToString("X");					break;
					case ER_STATION_ID_OCCUPIED:		ErrorMessage = "ER_STATION_ID_OCCUPIED; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_MODULATION_OVERLOADED:		ErrorMessage = "ER_MODULATION_OVERLOADED; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_MODULATION_NOT_LOADED:		ErrorMessage = "ER_MODULATION_NOT_LOADED; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_MODULATION_ALREADY_LOADED:	ErrorMessage = "ER_MODULATION_ALREADY_LOADED; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_RESOURCE_ALREADY_GRANTED:	ErrorMessage = "ER_RESOURCE_ALREADY_GRANTED; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_CORRELATION_ERROR:			ErrorMessage = "ER_CORRELATION_ERROR; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_INVALID_SETTING:			ErrorMessage = "ER_INVALID_SETTING; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_CALIBRATION_OUT_OF_SPECS:	ErrorMessage = "ER_CALIBRATION_OUT_OF_SPECS; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_UNSUPPORTED_OFFLINE:		ErrorMessage = "ER_UNSUPPORTED_OFFLINE; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_ENFORCED_OFFLINE:			ErrorMessage = "ER_ENFORCED_OFFLINE; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_SOFTWARE_TIMEOUT:			ErrorMessage = "ER_SOFTWARE_TIMEOUT; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_HADWARE_TIMEOUT:			ErrorMessage = "ER_HADWARE_TIMEOUT; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_EXCEED_MAX_SAMPLE_SZIE:		ErrorMessage = "ER_EXCEED_MAX_SAMPLE_SZIE; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_MISSING_CALIBRATION_FILE:	ErrorMessage = "ER_MISSING_CALIBRATION_FILE; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_NO_TESTHEAD:				ErrorMessage = "ER_NO_TESTHEAD; ErrorCode: 0x" + errorCode.ToString("X");					break;
					case ER_NO_TESTSITE:				ErrorMessage = "ER_NO_TESTSITE; ErrorCode: 0x" + errorCode.ToString("X");					break;
					case ER_API_NOT_SUPPORTED:			ErrorMessage = "ER_API_NOT_SUPPORTED; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_LOAD_DLL_FILE_ERROR:		ErrorMessage = "ER_LOAD_DLL_FILE_ERROR; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_LOAD_DLL_FUNCTION_ERROR:	ErrorMessage = "ER_LOAD_DLL_FUNCTION_ERROR; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_MEMORY_ALLOCATION_ERROR:	ErrorMessage = "ER_MEMORY_ALLOCATION_ERROR; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_FILE_IO_ERROR:				ErrorMessage = "ER_FILE_IO_ERROR; ErrorCode: 0x" + errorCode.ToString("X");					break;
					case ER_MISSING_GLOBAL_COND:		ErrorMessage = "ER_MISSING_GLOBAL_COND; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_MISSING_FLOWITEM_COND:		ErrorMessage = "ER_MISSING_FLOWITEM_COND; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_MISSING_TESTPARAM_COND:		ErrorMessage = "ER_MISSING_TESTPARAM_COND; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_INVALID_COMMAND:			ErrorMessage = "ER_INVALID_COMMAND; ErrorCode: 0x" + errorCode.ToString("X");				break;
					case ER_INVALID_COMMAND_ARGUMENTS:	ErrorMessage = "ER_INVALID_COMMAND_ARGUMENTS; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_REGISTER_INSTRUMENT_ERROR:	ErrorMessage = "ER_REGISTER_INSTRUMENT_ERROR; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_INIT_INSTRUMENT_ERROR:		ErrorMessage = "ER_INIT_INSTRUMENT_ERROR; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_INSTRUMENT_READ_ERROR:		ErrorMessage = "ER_INSTRUMENT_READ_ERROR; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_INSTRUMENT_WRITE_ERROR:		ErrorMessage = "ER_INSTRUMENT_WRITE_ERROR; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_INCOMPATIBLE_HARDWARE:		ErrorMessage = "ER_INCOMPATIBLE_HARDWARE; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_UNINIT_INSTRUMENT_ERROR:	ErrorMessage = "ER_UNINIT_INSTRUMENT_ERROR; ErrorCode: 0x" + errorCode.ToString("X");		break;
					case ER_VOLTAGE_OUT_OF_RANGE:		ErrorMessage = "ER_VOLTAGE_OUT_OF_RANGE; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_CURRENT_OUT_OF_RANGE:		ErrorMessage = "ER_CURRENT_OUT_OF_RANGE; ErrorCode: 0x" + errorCode.ToString("X");			break;
					case ER_INVALID_RESOURCE_PIN:		ErrorMessage = "ER_INVALID_RESOURCE_PIN; ErrorCode: 0x" + errorCode.ToString("X");			break;
					}
				}

#if AMSRF_ENABLE
				//else if (siteIndex == RF)
				//{
				//	ret = amsrf->GetErrorCodeMessage(errorCode, ReturnErrorMessage);
				//	ErrorMessage = ReturnErrorMessage->ToString();
				//	ErrorMessage = ErrorMessage + " [Aemulus AMSRF error.]";
				//}
#endif

#if AXRF_ENABLE
				else if (siteIndex == TEV)
				{
					if (errorCode == ER_TevDRPM_1)					ErrorMessage = "ER_TevDRPM_1";
					else if (errorCode == ER_TevDRPM_2)				ErrorMessage = "ER_TevDRPM_2";
					else if (errorCode == ER_TevDRPM_3)				ErrorMessage = "ER_TevDRPM_3";
					else if (errorCode == ER_TevDRPM_4)				ErrorMessage = "ER_TevDRPM_4";
					else if (errorCode == ER_TevRFSM)				ErrorMessage = "ER_TevRFSM";
					else if (errorCode == ER_TevRFM)				ErrorMessage = "ER_TevRFM";
					else if (errorCode == ER_AfSigGenA)				ErrorMessage = "ER_AfSigGenA";
					else if (errorCode == ER_AfDigitizer)			ErrorMessage = "ER_AfDigitizer";
					else if (errorCode == ER_AfSigGenB)				ErrorMessage = "ER_AfSigGenB";
					else if (errorCode == ER_SCALAR_FACTOR_READ)	ErrorMessage = "ER_SCALAR_FACTOR_READ";
					else if (errorCode == ER_VECTOR_FACTOR_READ)	ErrorMessage = "ER_VECTOR_FACTOR_READ";
					else if (errorCode == ER_NOISE_FACTOR_READ)		ErrorMessage = "ER_NOISE_FACTOR_READ";
					else if (errorCode == ER_CONFIG_FILE_READ)		ErrorMessage = "ER_CONFIG_FILE_READ";
					else if (errorCode == ER_NO_HARDWARE_FOUND)		ErrorMessage = "ER_NO_HARDWARE_FOUND";
				}
				else if (siteIndex == AFSG)
				{
					axrf->SigGen->afSigGen_ErrorMessage_Get(ErrorMessage);
					ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = ErrorMessage + " [Aemulus AXRF afSigGen error.]";
				}
				else if (siteIndex == AFDGT)
				{
					axrf->Digitizer->afDigitizer_ErrorMessage_Get(ErrorMessage, 256);
					ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = ErrorMessage + " [Aemulus AXRF afDigitizer error.]";
				}
				else if (siteIndex == AFERR)
				{
					ErrorMessage = glob->TcrLgr.GlobalErrorMessage + "; ErrorCode: 0x" + errorCode.ToString("X");
				}
#endif

				else
				{
					ErrorMessage = "UNKNOWN ERROR; ErrorCode: 0x" + errorCode.ToString("X");
				}
			}
			else if (errorCode == ER_CONST_ERRROR_CATCH)
			{
				ErrorMessage = glob->TcrLgr.GlobalErrorMessage + "; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_RESULT)
			{
				ErrorMessage = "ER_CONST_INVALID_RESULT (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_CALIBRATION_MODE)
			{
				ErrorMessage = "gCalibrationMode UN-SPECIFIED; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_CALIBRATION_MODE)
			{
				ErrorMessage = "INVALID gCalibrationMode HAS BEEN SET; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_BAD_ARGUMENTS)
			{
				ErrorMessage = "ERROR_BAD_ARGUMENTS; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_NOT_ENOUGH_MEMORY)
			{
				ErrorMessage = "ERROR_NOT_ENOUGH_MEMORY; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_OPEN_FAILED)
			{
				ErrorMessage = "ERROR_OPEN_FAILED; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED)
			{
				ErrorMessage = "ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_GENERAL)
			{
				ErrorMessage = "ER_CONST_GENERAL (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_TIMEOUT)
			{
				ErrorMessage = "ER_CONST_TIMEOUT; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_FILE_NOT_FOUND)
			{
				ErrorMessage = "ER_CONST_FILE_NOT_FOUND (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_READ_FILE_ERROR)
			{
				ErrorMessage = "ER_CONST_READ_FILE_ERROR (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_SETTING)
			{
				ErrorMessage = "ER_CONST_INVALID_SETTING (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_NOT_FOUND)
			{
				ErrorMessage = "ER_CONST_NOT_FOUND; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED)
			{
				ErrorMessage = "ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_RESOURCE_MANAGER)
			{
				ErrorMessage = "ER_CONST_RESOURCE_MANAGER; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_HARDWARE_RESOURCE)
			{
				ErrorMessage = "ER_CONST_INVALID_HARDWARE_RESOURCE; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_RFSiteConfigInfo)
			{
				ErrorMessage = "Encountered error during casting informations from RFSiteConfigInfo.xml. [" + glob->TcrLgr.GlobalErrorMessage + "]; ErrorCode: 0x" + errorCode.ToString("X"); "Please check the contents inside the RFSiteConfigInfo.xml";

				//ErrorMessage = glob->TcrLgr.GlobalErrorMessage + "; ErrorCode: 0x" + errorCode.ToString("X"); "Please check the contents inside the RFSiteConfigInfo.xml";
			}
			else if (errorCode == ER_CONST_DRIVE_CURRENT) //Check the compliance setting when enter run mode 
			{
				ErrorMessage = "INVALID_DRIVE_VALUE (Drive value with 0V or 0A is not allowed); ErrorCode: 0x" + errorCode.ToString("X");
				glob->TcrLgr.IsWarningMessage = true;
				glob->FileLog.IsWarning = true;
				WarningMessageType = "INVALID COMPLIANCE SETTING";
			}
			else
			{
				ErrorMessage = "UNKNOWN ERROR; ErrorCode: 0x" + errorCode.ToString("X");
			}

			if (siteIndex >= glob->tf.NumberOfSites)
			{
				siteIndex = 0; // Must fixed siteIndex to 0 here to eliminate Index was outside the bounds of the array (as siteIndex will inherit from previous test in try loop)
				WriteToLogger(siteIndex, "siteIndex is more than the number of sites, and is reset to zero");
			}

			String ^ l_TracerMessage = String::Empty;
			String ^ l_LogMssg = String::Empty;
			String ^ l_ErrorMessageLog = String::Empty;
			if (glob->TestProperty[siteIndex].TestParameterName == nullptr || glob->TestProperty[siteIndex].TestItemName == nullptr)
			{
				l_TracerMessage = "Cpp Source File = " + FileName + "\n\t\t\t" +
					"TestSite = " + siteIndex + "\n\t\t\t" +
					"ErrorLineNumber = " + ErrorLineNumber + "\n\t\t\t" +
					"ErrorCode = 0x" + errorCode.ToString("X") + "\n\t\t\t" +
					"ErrorMessage = " + ErrorMessage;

				l_LogMssg = "Cpp Source File = " + FileName + " " +
					"TestSite = " + siteIndex + " " +
					"ErrorLineNumber = " + ErrorLineNumber + " " +
					"ErrorCode = 0x" + errorCode.ToString("X") + " " +
					"ErrorMessage = " + ErrorMessage;

				l_ErrorMessageLog = "Cpp Source File = " + FileName + "\n\t\t\t\t" +
					"TestSite = " + siteIndex + "\n\t\t\t\t" +
					"ErrorLineNumber = " + ErrorLineNumber + "\n\t\t\t\t" +
					"ErrorCode = 0x" + errorCode.ToString("X") + "\n\t\t\t\t" +
					"ErrorMessage = " + ErrorMessage;
			}
			else
			{
				l_TracerMessage = "Cpp Source File = " + FileName + "\n\t\t\t" +
					"TestSite = " + siteIndex + "\n\t\t\t" +
					"TestItem = " + glob->TestProperty[siteIndex].TestItemName + "\n\t\t\t" +
					"TestParameter = " + glob->TestProperty[siteIndex].TestParameterName + "\n\t\t\t" +
					"ErrorLineNumber = " + ErrorLineNumber + "\n\t\t\t" +
					"ErrorCode = 0x" + errorCode.ToString("X") + "\n\t\t\t" +
					"ErrorMessage = " + ErrorMessage;

				l_LogMssg = "Cpp Source File = " + FileName + " " +
					"TestSite = " + siteIndex + " " +
					"TestItem = " + glob->TestProperty[siteIndex].TestItemName + " " +
					"TestParameter = " + glob->TestProperty[siteIndex].TestParameterName + " " +
					"ErrorLineNumber = " + ErrorLineNumber + " " +
					"ErrorCode = 0x" + errorCode.ToString("X") + " " +
					"ErrorMessage = " + ErrorMessage;

				l_ErrorMessageLog = "Cpp Source File = " + FileName + "\n\t\t\t\t" +
					"TestSite = " + siteIndex + "\n\t\t\t\t" +
					"TestItem = " + glob->TestProperty[siteIndex].TestItemName + "\n\t\t\t\t" +
					"TestParameter = " + glob->TestProperty[siteIndex].TestParameterName + "\n\t\t\t\t" +
					"ErrorLineNumber = " + ErrorLineNumber + "\n\t\t\t\t" +
					"ErrorCode = 0x" + errorCode.ToString("X") + "\n\t\t\t\t" +
					"ErrorMessage = " + ErrorMessage;
			}

			if (glob->TcrLgr.IsWarningMessage == true /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
			{
				glob->TcrLgr.TracerMessage = l_TracerMessage;
				glob->TcrLgr.TracerLog->WriteToTracer(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, LOGGER_WARNING_TYPE + " " + glob->TraceTime + ": " + glob->TcrLgr.TracerMessage);

				//[Requirement:]Should write to LogFile in both Release and Debug modes 
				glob->TcrLgr.LogMssg = l_LogMssg;
				FileLogging(siteIndex, LOGGER_WARNING_TYPE, glob->TcrLgr.LogMssg);
				WarningMessageBox(glob->TcrLgr.LogMssg, WarningMessageType);
			}

			if (glob->AWV.Debug == 1 /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
			{
				ErrorMessageLog = l_ErrorMessageLog;
				glob->TcrLgr.TracerLog->WriteToTracer(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, LOGGER_ERROR_TYPE + " " + glob->TraceTime + ": " + ErrorMessageLog);
			}

			glob->TcrLgr.LogMssg = l_LogMssg;
			FileLogging(siteIndex, LOGGER_ERROR_TYPE, glob->TcrLgr.LogMssg);

			throw gcnew Aemulus::Hardware::AlarmException(ErrorMessage + " at line " + ErrorLineNumber, errorCode);
		}

		return ret;
	}
	int TestFunction::TRACERLOGGING(int siteIndex, String ^ LogMessage, int LogLineNumber, String ^ FileName)
	{
		/*****************************************************************************************************
		** TracerLogging
		** Arguments:
		**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**						  project or techFlow sites for Index Parallel project.
		**		LogMesssage		- This is the message to be log by File and Tracer Logger.
		**		ErrorLineNumber - This is the line number in test program where last error happens.
		**		FileName		- This is the file name of current executing function in test program where the
		**						  last error happens.
		** Descriptions:
		**		This method is to log all every single action into log message to the tracer window or file logger
		**		when Debug mode is Enable. Main purpose is to ease the debug action. This is useful when user intended
		**		to trace the single API before executing and after execited effect.
		**		Usage:
		**			 TracerLogging(siteIndex, "dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF)");
		**			 CheckError(siteIndex, dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF));
		**			 TracerLogging(siteIndex, "dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF)");
		**		Effect on tracer window:
		**			Executing dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF) at line xx.
		**			Executed dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF) at line xx.
		******************************************************************************************************/

		int ret = 0;
		String^ TracerTabName = String::Empty;

		if (glob->AWV.Debug == 1)
		{
			if (glob->TcrLgr.CountNumber > 1)
			{
				glob->TcrLgr.CountNumber = 0; //Reset 
			}

			if (glob->TcrLgr.CountNumber == 0)
			{
				LogLineNumber = LogLineNumber + 1;
				glob->TcrLgr.TracerMessage = LogMessage + " at line " + LogLineNumber + " [" + FileName + "].";

				if (glob->tf.CurrentPhase == "Load")
				{
					WriteToTracerLogger(glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex, "Executing " + glob->TcrLgr.TracerMessage);
					glob->TcrLgr.LogMssg = "[" + glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex + "] " + "Executing " + glob->TcrLgr.TracerMessage;
				}
				else if (glob->tf.CurrentPhase == "Test")
				{
					WriteToTracerLogger(glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex, "Executing " + glob->TcrLgr.TracerMessage);
					glob->TcrLgr.LogMssg = "[" + glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex + "] " + "Executing " + glob->TcrLgr.TracerMessage;
				}
				else if (glob->tf.CurrentPhase == "Unload")
				{
					WriteToTracerLogger(glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex, "Executing " + glob->TcrLgr.TracerMessage);
					glob->TcrLgr.LogMssg = "[" + glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex + "] " + "Executing " + glob->TcrLgr.TracerMessage;
				}
			}

			else if (glob->TcrLgr.CountNumber == 1)
			{
				LogLineNumber = LogLineNumber - 1;
				glob->TcrLgr.TracerMessage = LogMessage + " at line " + LogLineNumber + " [" + FileName + "].";

				if (glob->tf.CurrentPhase == "Load")
				{
					WriteToTracerLogger(glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex, "Executed " + glob->TcrLgr.TracerMessage);
					glob->TcrLgr.LogMssg = "[" + glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex + "] " + "Executed " + glob->TcrLgr.TracerMessage;
				}
				else if (glob->tf.CurrentPhase == "Test")
				{
					WriteToTracerLogger(glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex, "Executed " + glob->TcrLgr.TracerMessage);
					glob->TcrLgr.LogMssg = "[" + glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex + "] " + "Executed " + glob->TcrLgr.TracerMessage;
				}
				else if (glob->tf.CurrentPhase == "Unload")
				{
					WriteToTracerLogger(glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex, "Executing " + glob->TcrLgr.TracerMessage);
					glob->TcrLgr.LogMssg = "[" + glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex + "] " + "Executed " + glob->TcrLgr.TracerMessage;
				}
			}
			FileLogging(siteIndex, LOGGER_INFO_TYPE, glob->TcrLgr.LogMssg);
			glob->TcrLgr.CountNumber++;
		}

		return ret;
	}
	void TestFunction::InitializeLogger(Site ^ site)
	{
		/*****************************************************************************************************
		** InitializeLogger
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This method is to instanstiate both Tracer and File Logger when Debug mode is Enable.
		******************************************************************************************************/

		//<Summary>
		//Make sure File Logger instanstiate during both Release and Debug modes 
		//Instanstiate File Logger 
		//</Summary>
		glob->FileLog.FileLgr = gcnew Aemulus::TestLib::Utility::FileLogger(FILE_CONST_AEM_DEBUG);

		if (glob->tf.StageCount > 1) //Mutiple TechFlow Site (True Parallel & Index Parallel) 
		{
			glob->TcrLgr.TracerTabNamePhysicalSite = "Site" + glob->tf.TestSite.ToString() + "_UutOffset";
		}

		else //Single Techflow SIte (Multi UUTOffsets) 
		{
			glob->AWV.NumberOfSites = glob->tf.NumberOfSites;
			glob->TcrLgr.TracerTabNamePhysicalSite = "UutOffset";
		}

		if (glob->AWV.Debug == 1)
		{
			//Instanstiate Tracer Logger 
			glob->TcrLgr.TracerLog = gcnew Aemulus::TestLib::Utility::TracerLogger(site);

			glob->TcrLgr.PrefixValue = 1.0;		//Default set as "None" prefix unit

			//Print to tracer window
			for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				WriteToLogger(siteIndex, "Instanstiated Tracer & File Logger");
			}
		}

		else
		{
			for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				FileLogging(siteIndex, LOGGER_INFO_TYPE, "Instanstiated File Logger");
			}
		}

		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, "Initialized Global Variables");
			WriteToLogger(siteIndex, "Tester ID = " + glob->TesterId);
			WriteToLogger(siteIndex, "Active Test Site = " + siteIndex);
			WriteToLogger(siteIndex, "Active Test Head = " + glob->tf.TestHead);
			WriteToLogger(siteIndex, "Total UUTOffsets = " + glob->tf.TotalUUTOffsets);
			WriteToLogger(siteIndex, "Loaded Hardware Profile = " + glob->HardwareProfile);
		}
	}
	void TestFunction::FileLogging(int siteIndex, String^ MssgType, String ^ LogMessage)
	{
		/*****************************************************************************************************
		** FileLogging
		**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**						  project or techFlow sites for Index Parallel project.
		**		MssgType		- Message type can be 3 types:
		**							1. LOGGER_WARNING_TYPE			"[WARNING]"
		**							2. LOGGER_ERROR_TYPE			"[ERROR]"
		**							3. LOGGER_INFO_TYPE				"[INFO]"
		**		LogMessage		- This is the specific log/ debug message to be log by FileLogger in debug/warning log.
		** Descriptions:
		**		This method is to append the log/ debug message into the debug or warning file.
		**		Enable in both release and debug mode or when MssgType is an error. Or log the warning message
		**		when needed during production mode.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1 || MssgType == LOGGER_ERROR_TYPE)
		{
			glob->FileLog.FileNameDebugLog = "DebugLog_Head" + glob->tf.TestHead.ToString() + "_Site" + glob->tf.TestSite.ToString() + "_UutOffset" + siteIndex.ToString() + "_" + glob->TesterId + "_" + glob->tf.RecipeFileName + "_" + glob->SWTraceTime + ".csv";
			glob->TcrLgr.ContLog = String::Concat(MssgType, ",", glob->TraceTime, ",", LogMessage);
			glob->FileLog.FileLgr->WriteToFile(glob->FileLog.FileNameDebugLog, glob->TcrLgr.ContLog, LOGGER_CONST_APPEND);
		}
		else if (glob->FileLog.IsWarning == true)
		{
			glob->FileLog.FileNameWarningLog = "WarningLog_Head" + glob->tf.TestHead.ToString() + "_SITE" + glob->tf.TestSite.ToString() + "_UutOffset" + siteIndex.ToString() + "_" + glob->TesterId + "_" + glob->tf.RecipeFileName + "_" + glob->SWTraceTime + ".csv";
			glob->TcrLgr.ContLog = String::Concat(MssgType, ",", glob->TraceTime, ",", LogMessage);
			glob->FileLog.FileLgr->WriteToFile(glob->FileLog.FileNameWarningLog, glob->TcrLgr.ContLog, LOGGER_CONST_APPEND);
		}
	}
	void TestFunction::WarningMessageBox(String ^ MssgContent, String ^ WarningMssgType)
	{
		/*****************************************************************************************************
		** WarningMessageBox
		** Arguments:
		**		MssgContent			- Specific text in the message box.
		**		WarningMssgType		- Caption of message box. eg: "Apps Calibration Setup".
		** Descriptions:
		**		This method is to displays a message box with specified text.
		******************************************************************************************************/

		MessageBox::Show(MssgContent, WarningMssgType,
			MessageBoxButtons::OK,
			MessageBoxIcon::Warning,
			MessageBoxDefaultButton::Button2,
			MessageBoxOptions::DefaultDesktopOnly, false);
	}
	void TestFunction::WriteToTracerLogger(String ^ TracerTabName, String ^ LogMessage)
	{
		/*****************************************************************************************************
		** WriteToTracerLogger
		** Arguments:
		**		TracerTabName	- The tracer tab name used is LOGGER_WARNING_TYPE "[INFO]".
		**		LogMessage		- Specific log/ debug message to be display on tracer window.
		** Descriptions:
		**		This method is to wrap the "glob->TcrLgr.TracerLog->WriteToTracer" action to ease the end-user
		**		when intended to write the debug message to tracer window. Only Enable when debug mode.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1 /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
		{
			glob->TcrLgr.TracerLog->WriteToTracer(TracerTabName, LOGGER_INFO_TYPE + glob->TraceTime + ":  " + LogMessage);
		}
	}
	void TestFunction::WRITETOLOGGER(int siteIndex, String ^ LogMessage, int LogLineNumber, String ^ FileName, String ^ FunctionName)
	{
		/*****************************************************************************************************
		** WRITETOLOGGER
		**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**						  project or techFlow sites for Index Parallel project.
		**		LogMesssage		- This is the message to be log by File and Tracer Logger.
		**		FileName		- This is the file name of current executing function in test program where the
		**					      last error happens.
		**		FunctionName	- This is the current executing method/function name in test program where the
		**					      last error happens.
		** Descriptions:
		**		This method is to wrap the "glob->TcrLgr.TracerLog->WriteToTracer", FileLoging and TracerLogging
		**		actions to ease the end-user when intended to write the debug message to tracer window or debug
		**		file. Only Enable when debug mode.
		******************************************************************************************************/

		//File Logging 
		LogLineNumber = LogLineNumber + 1;
		glob->TcrLgr.TracerMessage = LogMessage + " at line " + LogLineNumber + " [" + FileName + " @ " + FunctionName + "].";
		FileLogging(siteIndex, LOGGER_INFO_TYPE, glob->TcrLgr.TracerMessage);  //Treat all the messages as INFO

																			   //Tracer Logging 
		if (glob->AWV.Debug == 1 /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
		{
			WriteToTracerLogger(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, glob->TcrLgr.TracerMessage);
		}
	}
	void TestFunction::KillTracerLogger(int TotalSites, String ^ CurrentPhase)
	{
		/*****************************************************************************************************
		** KillTracerLogger
		**		TotalSites		- This is the total physical test sites to be used for updates the message to
		**						  each tracer tab accordingly.
		**		CurrentPhase	- This is the current executing phase (expected "UNLOAD") that is needed to log
		**						  the unload phase when successfully executed.
		** Descriptions:
		**		This method is to clear and remove all tracer tabsof tracer window. Only valid when tracer logger
		**		is instantaited at first. Only available when debug mode.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1 /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
		{
			for (int siteIndex = 0; siteIndex < TotalSites; siteIndex++)
			{
				WriteToLogger(siteIndex, ">>Executed " + CurrentPhase + " Phase");
				WriteToLogger(siteIndex, "Clearing and Closing Tracer Window");
				WriteToLogger(siteIndex, ">>Executed Check Error Tracker Succesfully");
			}

			Util->WaitSecond(2);
			glob->TcrLgr.TracerLog->RemoveAllTracer();
		}
	}
	void TestFunction::ErrorHandling(Site ^ site, int siteIndex, String^ methodName, String ^ ErrorMessage)
	{

		String^ methodType = String::Empty;
		array<String^>^ separators = { "CM_", "TM_" };
		array <String^>^ splitString = nullptr;

		if (site->CurrentFlowItem->GetType() == ControlItem::typeid)
		{
			if (methodName->Contains("CM_"))
			{
				splitString = methodName->Split(separators, StringSplitOptions::RemoveEmptyEntries);

				ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
					"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
					"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
					"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
					"Control Method = " + splitString[0] + "\n\t\t\t\t\t" +
					"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
			}
		}
		else if (site->CurrentFlowItem->GetType() == TestItem::typeid)
		{
			if (methodName->Contains("CM_"))
			{
				splitString = methodName->Split(separators, StringSplitOptions::RemoveEmptyEntries);

				ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
					"Test Item Identifier = " + glob->ErrorInfo[siteIndex].TestItemName + "\n\t\t\t\t\t" +
					"Test Parameter Identifier = " + glob->ErrorInfo[siteIndex].TestParameterName + "\n\t\t\t\t\t" +
					"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
					"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
					"Control Method = " + splitString[0] + "\n\t\t\t\t\t" +
					"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
			}
			else if (methodName->Contains("TM_"))
			{
				splitString = methodName->Split(separators, StringSplitOptions::RemoveEmptyEntries);

				ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
					"Test Item Identifier = " + glob->ErrorInfo[siteIndex].TestItemName + "\n\t\t\t\t\t" +
					"Test Parameter Identifier = " + glob->ErrorInfo[siteIndex].TestParameterName + "\n\t\t\t\t\t" +
					"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
					"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
					"Test Method = " + splitString[0] + "\n\t\t\t\t\t" +
					"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
			}
		}

		FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
		WriteToLogger(siteIndex, ErrorMessage);
		glob->TcrLgr.ErrorCode = 0;

	}
	void TestFunction::ErrorHandling(Site ^ site, int siteIndex, String^ methodName, Exception ^ Ex)
	{

		String^ methodType = String::Empty;
		String^ ErrorMessage = nullptr;
		array<String^>^ separators = { "CM_", "TM_" };
		array <String^>^ splitString = nullptr;

		if (site->CurrentFlowItem->GetType() == ControlItem::typeid)
		{
			if (methodName->Contains("CM_"))
			{
				splitString = methodName->Split(separators, StringSplitOptions::RemoveEmptyEntries);

				ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
					"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
					"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
					"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
					"Control Method = " + splitString[0] + "\n\t\t\t\t\t" +
					"Error Code = 0X" + Ex->HResult.ToString("X") + "\n\t\t\t\t\t" +
					"Error Message = " + Ex->Message + "\n\t\t\t\t\t" +
					"StackTrack = " + Ex->StackTrace + "\n\t\t\t\t\t";
			}
		}
		else if (site->CurrentFlowItem->GetType() == TestItem::typeid)
		{
			if (methodName->Contains("CM_"))
			{
				splitString = methodName->Split(separators, StringSplitOptions::RemoveEmptyEntries);

				ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
					"Test Item Identifier = " + glob->ErrorInfo[siteIndex].TestItemName + "\n\t\t\t\t\t" +
					"Test Parameter Identifier = " + glob->ErrorInfo[siteIndex].TestParameterName + "\n\t\t\t\t\t" +
					"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
					"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
					"Control Method = " + splitString[0] + "\n\t\t\t\t\t" +
					"Error Code = 0X" + Ex->HResult.ToString("X") + "\n\t\t\t\t\t" +
					"Error Message = " + Ex->Message + "\n\t\t\t\t\t" +
					"StackTrack = " + Ex->StackTrace + "\n\t\t\t\t\t";
			}
			else if (methodName->Contains("TM_"))
			{
				splitString = methodName->Split(separators, StringSplitOptions::RemoveEmptyEntries);

				ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
					"Test Item Identifier = " + glob->ErrorInfo[siteIndex].TestItemName + "\n\t\t\t\t\t" +
					"Test Parameter Identifier = " + glob->ErrorInfo[siteIndex].TestParameterName + "\n\t\t\t\t\t" +
					"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
					"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
					"Test Method = " + splitString[0] + "\n\t\t\t\t\t" +
					"Error Code = 0X" + Ex->HResult.ToString("X") + "\n\t\t\t\t\t" +
					"Error Message = " + Ex->Message + "\n\t\t\t\t\t" +
					"StackTrack = " + Ex->StackTrace + "\n\t\t\t\t\t";
			}
		}

		FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
		WriteToLogger(siteIndex, ErrorMessage);
		glob->TcrLgr.ErrorCode = 0;

	}

	void TestFunction::ErrorHandling(Site ^ site, int siteIndex, String ^ ErrorMessage)
	{

		if (site->CurrentFlowItem->GetType() == ControlItem::typeid)
		{
			ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
				"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
				"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
				"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
				"Error Code = 0X" + glob->TcrLgr.ErrorCode.ToString("X") + "\n\t\t\t\t\t" +
				"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
		}
		else if (site->CurrentFlowItem->GetType() == TestItem::typeid)
		{
			ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
				"Test Item Identifier = " + glob->ErrorInfo[siteIndex].TestItemName + "\n\t\t\t\t\t" +
				"Test Parameter Identifier = " + glob->ErrorInfo[siteIndex].TestParameterName + "\n\t\t\t\t\t" +
				"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
				"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
				"Error Code = 0X" + glob->TcrLgr.ErrorCode.ToString("X") + "\n\t\t\t\t\t" +
				"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
		}

		FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
		WriteToLogger(siteIndex, ErrorMessage);
		glob->TcrLgr.ErrorCode = 0;

	}
	void TestFunction::ErrorHandling(Site ^ site, String ^ ErrorMessage)
	{
		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			if (site->CurrentFlowItem->GetType() == ControlItem::typeid)
			{
				if (glob->TcrLgr.ErrorCode != 0)
				{
					ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
						"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
						"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
						"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
						"Error Code = 0X" + glob->TcrLgr.ErrorCode.ToString("X") + "\n\t\t\t\t\t" +
						"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
				}
				else
				{
					ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
						"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
						"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
						"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
						"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
				}
			}
			else if (site->CurrentFlowItem->GetType() == TestItem::typeid)
			{
				if (glob->TcrLgr.ErrorCode != 0)
				{
					ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
						"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
						"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
						"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
						"Error Code = 0X" + glob->TcrLgr.ErrorCode.ToString("X") + "\n\t\t\t\t\t" +
						"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
				}
				else
				{
					ErrorMessage = "Error Occur:" + "\n\t\t\t\t\t" +
						"Control Item Identifier = " + site->CurrentFlowItem->Name + "\n\t\t\t\t\t" +
						"techFlow Site = " + glob->tf.TestSite + "\n\t\t\t\t\t" +
						"UUTOffset Site = " + siteIndex + "\n\t\t\t\t\t" +
						"Error Message = " + ErrorMessage + "\n\t\t\t\t\t";
				}
			}

			FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
			WriteToLogger(siteIndex, ErrorMessage);
		}

		glob->TcrLgr.ErrorCode = 0;

	}
	void TestFunction::WriteToLoggerTotalSite(String ^ LogMessage)
	{
		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToLogger(siteIndex, LogMessage);
		}
	}
	void TestFunction::TestCondCheckingDataType(String^ item, DataType TC_DataType_Info, DataType TC_DataType_Casting)
	{
		String^ ErrorMessage = nullptr;

		if (TC_DataType_Casting != TC_DataType_Info)
		{
			switch (TC_DataType_Info)
			{
			case DataType::Double:
				ErrorMessage = "Test Condition [" + item + " DataType] must be Double.";
				throw gcnew Exception(ErrorMessage);

				break;

			case DataType::Boolean:
				ErrorMessage = "Test Condition [" + item + " DataType] must be Boolean.";
				throw gcnew Exception(ErrorMessage);
				break;

			case DataType::Int32:
                ErrorMessage = "Test Condition [" + item + " DataType] must be Int32.";
				throw gcnew Exception(ErrorMessage);
				break;

			case DataType::String:
				ErrorMessage = "Test Condition [" + item + " DataType] must be String.";
				throw gcnew Exception(ErrorMessage);
				break;

			default:
				ErrorMessage = "Test Condition [" + item + " DataType] not supported.";
				throw gcnew Exception(ErrorMessage);
				break;
			}
		}
	}

}

/*----------------------------------------------------------------------
* Revision Log
* $Log: Files.cpp.rca$


* v1.0.0.0 (20 March 2020), LKL
* Initial release version.

* V1.1.0.0 (29 Jan 2021), LKL
* Added operation setting value struct to support operation setting.
----------------------------------------------------------------------*/