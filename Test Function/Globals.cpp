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
		int tfSite = glob->tf.TestSite;
		glob->messageBoxIcon = MessageBoxIconFormat::Warning;

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
		//InitializeGlobalVariables(site);

		// Init tracer logger
		ret = InitializeTracerLogger(site, tfSite);
		if (ret != 0) goto EndOfTest;

		// Get tester ID
		GetTesterID(site, tfSite);

		// Init file logger
		ret = InitializeFileLogger(tfSite);
		if (ret != 0) goto EndOfTest;

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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized program.");
		}

		//CorrFactor
		corrFactorFileInit(site);

	EndOfTest:
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized Test Condition Properties {TProperty[" + siteIndex + "].TC_dict}");
		}
	}

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
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "Reset Global Variables.");
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "JumpOnFail = " + glob->tf.JumpOnFail);
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
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized Global Results Storage.");
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
				WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "Site " + siteIndex +
					":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result);
				//WriteToFileLgr(glob->FileLog.FileNameDebugLog,  "Site " + siteIndex +
					//":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result + "," + ",");
			}
			else //Multi UUTOffsets 
			{
				WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "UUT Offset Site " + siteIndex +
					":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result);
				//WriteToFileLgr(glob->FileLog.FileNameDebugLog,  "UUT Offset Site " + siteIndex +
				//	":: SetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + Result + "," + ",");
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
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "Reset Global Results Storage.");
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
					WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier]);
					WriteToFileLgr(glob->FileLog.FileNameDebugLog,  "Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier] + "," + ",");
				}
				else //Multi UUTOffsets
				{
					WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, "UUT Offset Site " + siteIndex +
						":: GetGlobalResult [" + siteIndex + "] = " + "Identifier: " + Identifier + "& Result: " + glob->GlobalResult[siteIndex][Identifier]);
					WriteToFileLgr(glob->FileLog.FileNameDebugLog,  "UUT Offset Site " + siteIndex +
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

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Tester ID
	**	----------------------------------------------------------------------------------------------------
	*/
	void TestFunction::GetTesterID(Site ^ site, int tfSite)
	{
		/*****************************************************************************************************
		** GetTesterID
		**		site - This is techFlow site object.
		**
		** Descriptions:
		**		This is a function to get Tester ID | Tester Name | Station Name.
		******************************************************************************************************/

		// Local variable
		//int tfSite = glob->tf.TestSite;

		//WriteToTracerLogger(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> GetTesterId] Load tester ID.");
		//WriteToTcrLgr(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> GetTesterId] Load tester ID.");

		// Tester ID | Tester Name | Station Name
		glob->TesterId = site->FlowEngine->StationName;

		//WriteToTracerLogger(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> GetTesterId] Tester ID | Tester Name | Station Name: " + glob->TesterId + ".");
		//WriteToTcrLgr(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> GetTesterId] Tester ID | Tester Name | Station Name: " + glob->TesterId + ".");
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
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "Debug: " + glob->AWV.Debug);
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "Power Line Frequency: " + glob->AWV.PowerLineFreq + "Hz");
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "Offline: " + glob->AWV.Offline);
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "DeviceName: " + glob->AWV.DeviceName);
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "AmsrfControllerMode: " + glob->AWV.AmsrfControllerMode);
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "DMPinGroup: " + glob->AWV.DMPinGroup);
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
			WriteToTcrLgr("SITE " + siteIndex.ToString(), "Is Run Test = " + RunTest[siteIndex]);
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

	//CheckError & Logger Utilities Functions

	int TestFunction::InitializeTracerLogger(Site ^ site, int tfSite)
	{
		/*****************************************************************************************************
		** InitializeTracerLogger
		**		site - This is techFlow site object.
		**
		** Descriptions:
		**		This is a function to initiate tracer logger when debug mode is enabled.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

		// Instanstiate Tracer Logger in 'Debug' mode only.
		if (glob->AWV.Debug == 1)
		{
			if (glob->tf.StageCount == 1)
			{
				try
				{
					// Initialize
					glob->TcrLgr.TracerLog = gcnew Aemulus::TestLib::Utility::TracerLogger(site);
				}
				catch (Exception^ ex)
				{
					ret = ER_CONST_FAIL_TO_INIT_TRACER_LOGGER;
					return ret;
				}

				// Default set as "None" prefix unit
				glob->TcrLgr.PrefixValue = 1.0;

				WriteToTracerLogger(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> InitializeTracerLogger] Initialize tracer logger.");
				//WriteToTcrLgr(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> InitializeTracerLogger] Initialize tracer logger.");
			}
			else
			{
				// [Future Enchancement] reserved for index parallel project.
			}
		}

	EndOfTest:
		return ret;
	}
	void TestFunction::WriteToTcrLgr(String ^ TracerTabName, String ^ LogMessage)
	{
		/*****************************************************************************************************
		** WriteToTcrLgr
		** Arguments:
		**		TracerTabName	- The tracer tab name used is LOGGER_WARNING_TYPE "[INFO]".
		**		LogMessage		- Specific log/ debug message to be display on tracer window.
		** Descriptions:
		**		This method is to wrap the "glob->TcrLgr.TracerLog->WriteToTracer" action to ease the end-user
		**		when intended to write the debug message to tracer window. Only Enable when debug mode.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1 /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
		{
			glob->TcrLgr.TracerLog->WriteToTracer(TracerTabName, LOGGER_INFO_TYPE + glob->TimeNow + ":  " + LogMessage);
		}
	}
	void TestFunction::WRITETOTRACERLOGGER(int tfSite, int siteIndex, String ^ messageType, String ^ message, int programLineNumber, String ^ programFileName, String ^ programFunctionName)
	{
		/*****************************************************************************************************
		** WRITETOTRACERLOGGER
		**		tfSite					- This is techFlow site index.
		**		siteIndex				- This is resource object index, normally start from 0.
		**		messageType				- This is message type, such as INFO / ERROR / WARNING.
		**		message					- This is message to display.
		**		programLineNumber		- This is program's line number where exception happened.
		**		programFileName			- This is program's file name where exception happened.
		**		programFunctionName		- This is program's function name where exception happened.
		**
		** Descriptions:
		**		This is a function to log all every single action into log message to the tracer window.
		**		Only applicable in debug mode.
		**		Main purpose is to ease the debug action.
		**		This is useful when user intended to trace the single API before executing and after execited effect.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1)
		{
			// Get tracer's tab name
			if (siteIndex == glob->TcrLgr.tracerMainTab)
			{
				glob->TcrLgr.TracerTabNamePhysicalSite = "SITE " + tfSite.ToString() + " Main";
			}
			else
			{
				if (glob->tf.ProjectType == int(ProjectType::SingleTFSiteSingleUUTOffset))
				{
					glob->TcrLgr.TracerTabNamePhysicalSite = "SITE " + tfSite.ToString();
				}
				else if (glob->tf.ProjectType == int(ProjectType::SingleTFSiteMultiUUTOffset))
				{
					glob->TcrLgr.TracerTabNamePhysicalSite = "SITE " + tfSite.ToString() + " UUT OFFSET " + siteIndex.ToString();
				}
				else if (glob->tf.ProjectType == int(ProjectType::SingleTFSiteMultiUUTOffsetSharedVNA))
				{
					glob->TcrLgr.TracerTabNamePhysicalSite = "SITE " + tfSite.ToString() + " UUT OFFSET " + siteIndex.ToString();
				}
				else if (glob->tf.ProjectType == int(ProjectType::TrueParallelSingleUUTOffset))
				{
					glob->TcrLgr.TracerTabNamePhysicalSite = "SITE " + tfSite.ToString();
				}
				else if (glob->tf.ProjectType == int(ProjectType::TrueParallelMultiUUTOffset))
				{
					glob->TcrLgr.TracerTabNamePhysicalSite = "SITE " + tfSite.ToString() + " UUT OFFSET " + siteIndex.ToString();
				}
				else if (glob->tf.ProjectType == int(ProjectType::IndexParallel))
				{
					// [Future Enchancement] reserved for index parallel project.
				}
			}

			// Get time now
			glob->TimeNow = DateTime::Now.ToString("yyyy/MM/dd' 'h:mm:ss tt");

			// Write to tracer logger
			if (messageType == WARNING)
			{
				glob->TcrLgr.TracerMessage = LOGGER_TYPE_WARNING + "[" + glob->TimeNow + "] " + message + " at line #" + programLineNumber + " [" + programFileName + " @ " + programFunctionName + "].";
				WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite, glob->TcrLgr.TracerMessage);
			}
			else if (messageType == ERROR)
			{
				glob->TcrLgr.TracerMessage = LOGGER_TYPE_ERROR + "[" + glob->TimeNow + "] " + message + " at line #" + programLineNumber + " [" + programFileName + " @ " + programFunctionName + "].";
				WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite, glob->TcrLgr.TracerMessage);
			}
			else if (messageType == INFO)
			{
				glob->TcrLgr.TracerMessage = LOGGER_TYPE_INFO + "[" + glob->TimeNow + "] " + message + " at line #" + programLineNumber + " [" + programFileName + " @ " + programFunctionName + "].";
				WriteToTcrLgr(glob->TcrLgr.TracerTabNamePhysicalSite, glob->TcrLgr.TracerMessage);
			}
		}
	}
	int TestFunction::UninitializeTracerLogger()
	{
		/*****************************************************************************************************
		** UninitializeTracerLogger
		**
		**
		** Descriptions:
		**		This is a function to clear and remove all the tracer tabsof tracer window.
		**		Only valid when tracer logger is instantaited at first.
		**		Only available when debug mode.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

		if (glob->AWV.Debug == 1)
		{
			if (glob->tf.StageCount == 1)
			{
				WriteToTracerLogger(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, INFO, "[Unload -> UninitializeProgram -> UninitializeTracerLogger] Uninitialize tracer logger.");
				//WriteToTcrLgr(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, INFO, "[Unload -> UninitializeProgram -> UninitializeTracerLogger] Uninitialize tracer logger.");

				try
				{
					// Uninitialize
					Util->WaitSecond(2.0 S);
					glob->TcrLgr.TracerLog->RemoveAllTracer();
				}
				catch (Exception^ ex)
				{
					ret = ER_CONST_FAIL_TO_UNINIT_TRACER_LOGGER;
					WriteToTracerLogger(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, ERROR, "[Unload -> UninitializeProgram -> UninitializeTracerLogger] Fail to uninitialize tracer logger." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
					//WriteToTcrLgr(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, ERROR, "[Unload -> UninitializeProgram -> UninitializeTracerLogger] Fail to uninitialize tracer logger." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
					return ret;
				}
			}
			else
			{
				// [Future Enchancement] reserved for index parallel project.
			}
		}

	EndOfTest:
		return ret;
	}

	int TestFunction::InitializeFileLogger(int tfSite)
	{
		/*****************************************************************************************************
		** InitializeFileLogger
		**		site - This is techFlow site object.
		**
		** Descriptions:
		**		This is a function to initiate file logger when debug mode is enabled.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

		// [Future Enchancement] To support file logger is able to log only error code in 'Release' mode.

		// Instanstiate File Logger in 'Debug' mode only.
		if (glob->AWV.Debug == 1)
		{
			if (glob->tf.StageCount == 1)
			{
				try
				{
					// Initialize
					glob->FileLog.FileLgr = gcnew Aemulus::TestLib::Utility::FileLogger(FOLDER_CONST_AEM_DEBUG);
					//glob->FileLog.fi			= gcnew FileInfo(FOLDER_CONST_AEM_DEBUG + "\\" + glob->FileLog.FileNameDebugLog);
					//glob->FileLog.IsWarning	= false;
				}
				catch (Exception^ ex)
				{
					ret = ER_CONST_FAIL_TO_INIT_FILE_LOGGER;
					WriteToTracerLogger(tfSite, glob->TcrLgr.tracerMainTab, ERROR, "[Load -> InitializeProgram -> InitializeFileLogger] Fail to initialize file logger." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
					WriteToFileLogger(tfSite, glob->TcrLgr.tracerMainTab, ERROR, "[Load -> InitializeProgram -> InitializeFileLogger] Fail to initialize file logger." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
					return ret;
				}

				WriteToTracerLogger(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> InitializeFileLogger] Initialize file logger.");
				WriteToFileLogger(tfSite, glob->TcrLgr.tracerMainTab, INFO, "[Load -> InitializeProgram -> InitializeFileLogger] Initialize file logger.");
			}
			else
			{
				// [Future Enchancement] reserved for index parallel project.
			}
		}

	EndOfTest:
		return ret;
	}
	void TestFunction::WRITETOFILELOGGER(int tfSite, int siteIndex, String ^ messageType, String ^ message, int programLineNumber, String ^ programFileName, String ^ programFunctionName)
	{
		/*****************************************************************************************************
		** WRITETOFILELOGGER
		**		tfSite					- This is techFlow site index.
		**		siteIndex				- This is resource object index, normally start from 0.
		**		messageType				- This is message type, such as INFO / ERROR / WARNING.
		**		message					- This is message to display.
		**		programLineNumber		- This is program's line number where exception happened.
		**		programFileName			- This is program's file name where exception happened.
		**		programFunctionName		- This is program's function name where exception happened.
		**
		** Descriptions:
		**		This is a function to log all every single action into log message to the file logger.
		**		Only applicable in debug mode.
		**		This is to record all the actions of the debugging process.
		**		This is useful when user intended to trace the single API before executing and after execited effect.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1)
		{
			// Get debug's file name
			if (siteIndex == glob->TcrLgr.tracerMainTab)
			{
				glob->FileLog.FileNameDebugLog = "DebugLog" + "_" + glob->TesterId + "_" + glob->tf.ProjectName + "_" + "SITE" + tfSite.ToString() + "_" + "Main" + "_" + glob->FileNameTime + ".csv";
			}
			else
			{
				if (glob->tf.ProjectType == int(ProjectType::SingleTFSiteSingleUUTOffset))
				{
					glob->FileLog.FileNameDebugLog = "DebugLog" + "_" + glob->TesterId + "_" + glob->tf.ProjectName + "_" + "SITE" + tfSite.ToString() + "_" + glob->FileNameTime + ".csv";
				}
				else if (glob->tf.ProjectType == int(ProjectType::SingleTFSiteMultiUUTOffset))
				{
					glob->FileLog.FileNameDebugLog = "DebugLog" + "_" + glob->TesterId + "_" + glob->tf.ProjectName + "_" + "SITE" + tfSite.ToString() + "_" + "UUTOFFSET" + siteIndex.ToString() + "_" + glob->FileNameTime + ".csv";
				}
				else if (glob->tf.ProjectType == int(ProjectType::SingleTFSiteMultiUUTOffsetSharedVNA))
				{
					glob->FileLog.FileNameDebugLog = "DebugLog" + "_" + glob->TesterId + "_" + glob->tf.ProjectName + "_" + "SITE" + tfSite.ToString() + "_" + "UUTOFFSET" + siteIndex.ToString() + "_" + glob->FileNameTime + ".csv";
				}
				else if (glob->tf.ProjectType == int(ProjectType::TrueParallelSingleUUTOffset))
				{
					glob->FileLog.FileNameDebugLog = "DebugLog" + "_" + glob->TesterId + "_" + glob->tf.ProjectName + "_" + "SITE" + tfSite.ToString() + "_" + glob->FileNameTime + ".csv";
				}
				else if (glob->tf.ProjectType == int(ProjectType::TrueParallelMultiUUTOffset))
				{
					glob->FileLog.FileNameDebugLog = "DebugLog" + "_" + glob->TesterId + "_" + glob->tf.ProjectName + "_" + "SITE" + tfSite.ToString() + "_" + "UUTOFFSET" + siteIndex.ToString() + "_" + glob->FileNameTime + ".csv";
				}
				else if (glob->tf.ProjectType == int(ProjectType::IndexParallel))
				{
					// [Future Enchancement] reserved for index parallel project.
				}
			}

			// Get time now
			glob->TimeNow = DateTime::Now.ToString("yyyy/MM/dd' 'h:mm:ss tt");

			// Write to file logger
			if (messageType == WARNING)
			{
				glob->FileLog.LogMessage = LOGGER_TYPE_WARNING + "[" + glob->TimeNow + "] " + message + " at line #" + programLineNumber + " [" + programFileName + " @ " + programFunctionName + "].";
				WriteToFileLgr(glob->FileLog.FileNameDebugLog, glob->FileLog.LogMessage);
			}
			else if (messageType == ERROR)
			{
				glob->FileLog.LogMessage = LOGGER_TYPE_ERROR + "[" + glob->TimeNow + "] " + message + " at line #" + programLineNumber + " [" + programFileName + " @ " + programFunctionName + "].";
				WriteToFileLgr(glob->FileLog.FileNameDebugLog, glob->FileLog.LogMessage);
			}
			else if (messageType == INFO)
			{
				glob->FileLog.LogMessage = LOGGER_TYPE_INFO + "[" + glob->TimeNow + "] " + message + " at line #" + programLineNumber + " [" + programFileName + " @ " + programFunctionName + "].";
				WriteToFileLgr(glob->FileLog.FileNameDebugLog, glob->FileLog.LogMessage);
			}
		}
	}
	void TestFunction::WriteToFileLgr(String ^ fileDirectory, String ^ message)
	{
		/*****************************************************************************************************
		** WriteToFileLgr
		**		fileDirectory	- This is debug logger file's directory.
		**		message			- This is message to display.
		**
		** Descriptions:
		**		This is a function to write the detail/message to the file logger.
		**		This is to record all the actions of the debugging process.
		**		Only applicable in debug mode.
		******************************************************************************************************/

		if (glob->AWV.Debug == 1)
		{
			glob->FileLog.FileLgr->WriteToFile(fileDirectory, message, LOGGER_CONST_APPEND);
			Util->WaitSecond(5.0 mS); // ori setting 2S
		}
	}
	int TestFunction::UninitializeFileLogger()
	{
		/*****************************************************************************************************
		** UninitializeFileLogger
		**
		**
		** Descriptions:
		**		This is a function to close file logger session.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

		if (glob->AWV.Debug == 1)
		{
			if (glob->tf.StageCount == 1)
			{
				WriteToTracerLogger(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, INFO, "[Unload -> UninitializeFileLogger] Uninitialize file logger.");
				WriteToFileLogger(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, INFO, "[Unload -> UninitializeFileLogger] Uninitialize file logger.");

				try
				{
					// [Future Enchancement] Closing file logger and handle situation if got error occur.
					// Uninitialize
				}
				catch (Exception^ ex)
				{
					ret = ER_CONST_FAIL_TO_UNINIT_FILE_LOGGER;
					WriteToTracerLogger(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, ERROR, "[Unload -> UninitializeFileLogger] Fail to uninitialize file logger." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
					WriteToFileLogger(glob->tf.TestSite, glob->TcrLgr.tracerMainTab, ERROR, "[Unload -> UninitializeFileLogger] Fail to uninitialize file logger." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
					return ret;
				}
			}
			else
			{
				// [Future Enchancement] reserved for index parallel project.
			}
		}

	EndOfTest:
		return ret;
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

		WriteToFileLgr(glob->FileLog.FileNameDebugLog, ErrorMessage);
		WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
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

		WriteToFileLgr(glob->FileLog.FileNameDebugLog, ErrorMessage);
		WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		glob->TcrLgr.ErrorCode = 0;

	}

	//int TestFunction::TRACERLOGGING(int siteIndex, String ^ LogMessage, int LogLineNumber, String ^ FileName)
	//{
	//	/*****************************************************************************************************
	//	** WriteToTracerLogger
	//	** Arguments:
	//	**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
	//	**						  project or techFlow sites for Index Parallel project.
	//	**		LogMesssage		- This is the message to be log by File and Tracer Logger.
	//	**		ErrorLineNumber - This is the line number in test program where last error happens.
	//	**		FileName		- This is the file name of current executing function in test program where the
	//	**						  last error happens.
	//	** Descriptions:
	//	**		This method is to log all every single action into log message to the tracer window or file logger
	//	**		when Debug mode is Enable. Main purpose is to ease the debug action. This is useful when user intended
	//	**		to trace the single API before executing and after execited effect.
	//	**		Usage:
	//	**			 WriteToTracerLogger(siteIndex, "dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF)");
	//	**			 CheckError(siteIndex, dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF));
	//	**			 WriteToTracerLogger(siteIndex, "dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF)");
	//	**		Effect on tracer window:
	//	**			Executing dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF) at line xx.
	//	**			Executed dio[siteIndex]->PowerOnOff("DIO", IOM_CONST_OUTPUT_VCCOUT5_OFF, IOM_CONST_OUTPUT_VCCOUT12_OFF) at line xx.
	//	******************************************************************************************************/
	//	int ret = 0;
	//	String^ TracerTabName = String::Empty;
	//	if (tl->glob->AWV.Debug == 1)
	//	{
	//		if (tl->glob->TcrLgr.CountNumber > 1)
	//		{
	//			tl->glob->TcrLgr.CountNumber = 0; //Reset 
	//		}
	//		if (tl->glob->TcrLgr.CountNumber == 0)
	//		{
	//			LogLineNumber = LogLineNumber + 1;
	//			tl->glob->TcrLgr.TracerMessage = LogMessage + " at line " + LogLineNumber + " [" + FileName + "].";
	//			if (tl->glob->tf.CurrentPhase == "Load")
	//			{
	//				//WriteToTcrLgr(tl->glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex, "Executing " + tl->glob->TcrLgr.TracerMessage);
	//				tl->glob->TcrLgr.LogMssg = "[" + tl->glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex + "] " + "Executing " + tl->glob->TcrLgr.TracerMessage;
	//			}
	//			else if (tl->glob->tf.CurrentPhase == "Test")
	//			{
	//				//WriteToTcrLgr(tl->glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex, "Executing " + tl->glob->TcrLgr.TracerMessage);
	//				tl->glob->TcrLgr.LogMssg = "[" + tl->glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex + "] " + "Executing " + tl->glob->TcrLgr.TracerMessage;
	//			}
	//			else if (tl->glob->tf.CurrentPhase == "Unload")
	//			{
	//				//WriteToTcrLgr(tl->glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex, "Executing " + tl->glob->TcrLgr.TracerMessage);
	//				tl->glob->TcrLgr.LogMssg = "[" + tl->glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex + "] " + "Executing " + tl->glob->TcrLgr.TracerMessage;
	//			}
	//		}
	//		else if (tl->glob->TcrLgr.CountNumber == 1)
	//		{
	//			LogLineNumber = LogLineNumber - 1;
	//			tl->glob->TcrLgr.TracerMessage = LogMessage + " at line " + LogLineNumber + " [" + FileName + "].";
	//			if (tl->glob->tf.CurrentPhase == "Load")
	//			{
	//				//WriteToTcrLgr(tl->glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex, "Executed " + tl->glob->TcrLgr.TracerMessage);
	//				tl->glob->TcrLgr.LogMssg = "[" + tl->glob->TcrLgr.TracerLoadPhaseTabName + "_SITE" + siteIndex + "] " + "Executed " + tl->glob->TcrLgr.TracerMessage;
	//			}
	//			else if (tl->glob->tf.CurrentPhase == "Test")
	//			{
	//				//WriteToTcrLgr(tl->glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex, "Executed " + tl->glob->TcrLgr.TracerMessage);
	//				tl->glob->TcrLgr.LogMssg = "[" + tl->glob->TcrLgr.TracerTestPhaseTabName + "_SITE" + siteIndex + "] " + "Executed " + tl->glob->TcrLgr.TracerMessage;
	//			}
	//			else if (tl->glob->tf.CurrentPhase == "Unload")
	//			{
	//				//WriteToTcrLgr(tl->glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex, "Executing " + tl->glob->TcrLgr.TracerMessage);
	//				tl->glob->TcrLgr.LogMssg = "[" + tl->glob->TcrLgr.TracerUnloadPhaseTabName + "_SITE" + siteIndex + "] " + "Executed " + tl->glob->TcrLgr.TracerMessage;
	//			}
	//		}
	//		WriteToFileLgr(glob->FileLog.FileNameDebugLog,  tl->glob->TcrLgr.LogMssg);
	//		tl->glob->TcrLgr.CountNumber++;
	//	}
	//	return ret;
	//}
	//void TestFunction::WriteToFileLgr(int siteIndex, String^ MssgType, String ^ LogMessage)
	//{
	//	/*****************************************************************************************************
	//	** WriteToFileLgr
	//	**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
	//	**						  project or techFlow sites for Index Parallel project.
	//	**		MssgType		- Message type can be 3 types:
	//	**							1. LOGGER_WARNING_TYPE			"[WARNING]"
	//	**							2. LOGGER_ERROR_TYPE			"[ERROR]"
	//	**							3. LOGGER_INFO_TYPE				"[INFO]"
	//	**		LogMessage		- This is the specific log/ debug message to be log by FileLogger in debug/warning log.
	//	** Descriptions:
	//	**		This method is to append the log/ debug message into the debug or warning file.
	//	**		Enable in both release and debug mode or when MssgType is an error. Or log the warning message
	//	**		when needed during production mode.
	//	******************************************************************************************************/
	//	if (tl->glob->AWV.Debug == 1 || MssgType == LOGGER_ERROR_TYPE)
	//	{
	//		tl->glob->FileLog.FileNameDebugLog = "DebugLog_Head" + tl->glob->tf.TestHead.ToString() + "_Site" + tl->glob->tf.TestSite.ToString() + "_UutOffset" + siteIndex.ToString() + "_" + tl->glob->TesterId + "_" + tl->glob->tf.RecipeFileName + "_" + tl->glob->SWTraceTime + ".csv";
	//		tl->glob->TcrLgr.ContLog = String::Concat(MssgType, ",", tl->glob->TimeNow, ",", LogMessage);
	//		tl->glob->FileLog.FileLgr->WriteToFile(tl->glob->FileLog.FileNameDebugLog, tl->glob->TcrLgr.ContLog, LOGGER_CONST_APPEND);
	//	}
	//	else if (tl->glob->FileLog.IsWarning == true)
	//	{
	//		tl->glob->FileLog.FileNameWarningLog = "WarningLog_Head" + tl->glob->tf.TestHead.ToString() + "_SITE" + tl->glob->tf.TestSite.ToString() + "_UutOffset" + siteIndex.ToString() + "_" + tl->glob->TesterId + "_" + tl->glob->tf.RecipeFileName + "_" + tl->glob->SWTraceTime + ".csv";
	//		tl->glob->TcrLgr.ContLog = String::Concat(MssgType, ",", tl->glob->TimeNow, ",", LogMessage);
	//		tl->glob->FileLog.FileLgr->WriteToFile(tl->glob->FileLog.FileNameWarningLog, tl->glob->TcrLgr.ContLog, LOGGER_CONST_APPEND);
	//	}
	//}
	//void TestFunction::WRITETOLOGGER(int siteIndex, String ^ LogMessage, int LogLineNumber, String ^ FileName, String ^ FunctionName)
	//{
	//	/*****************************************************************************************************
	//	** WRITETOLOGGER
	//	**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
	//	**						  project or techFlow sites for Index Parallel project.
	//	**		LogMesssage		- This is the message to be log by File and Tracer Logger.
	//	**		FileName		- This is the file name of current executing function in test program where the
	//	**					      last error happens.
	//	**		FunctionName	- This is the current executing method/function name in test program where the
	//	**					      last error happens.
	//	** Descriptions:
	//	**		This method is to wrap the "tl->glob->TcrLgr.TracerLog->WriteToTracer", FileLoging and WriteToTracerLogger
	//	**		actions to ease the end-user when intended to write the debug message to tracer window or debug
	//	**		file. Only Enable when debug mode.
	//	******************************************************************************************************/
	//	//File Logging 
	//	LogLineNumber = LogLineNumber + 1;
	//	tl->glob->TcrLgr.TracerMessage = LogMessage + " at line " + LogLineNumber + " [" + FileName + " @ " + FunctionName + "].";
	//	WriteToFileLgr(glob->FileLog.FileNameDebugLog,  tl->glob->TcrLgr.TracerMessage);  //Treat all the messages as INFO
	//																		   //Tracer Logging 
	//	if (tl->glob->AWV.Debug == 1 /*&& tl->glob->AutoGUCal.AutoGUCalToolActive == false*/)
	//	{
	//		WriteToTcrLgr(tl->glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, tl->glob->TcrLgr.TracerMessage);
	//	}
	//}

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

		WriteToFileLgr(glob->FileLog.FileNameDebugLog, ErrorMessage);
		WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
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

			WriteToFileLgr(glob->FileLog.FileNameDebugLog, ErrorMessage);
			WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		}

		glob->TcrLgr.ErrorCode = 0;

	}
	void TestFunction::WriteToLoggerTotalSite(String ^ LogMessage)
	{
		for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
		{
			WriteToTcrLgr("SITE " + siteIndex.ToString(), LogMessage);
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
	
	int TestFunction::CHECKERROR(int siteIndex, int errorCode, int ErrorLineNumber, String^ FileName)
	{
		/*****************************************************************************************************
		** CHECKERROR
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

		// Local variable
		int ret = 0;
		String ^ errorCodeMessage = String::Empty;
		String ^ ErrorMessage = String::Empty;
		String ^ WarningMessageType = String::Empty;

		if (errorCode != 0)
		{
			/*
			**	----------------------------------------------------------------------------------------------------
			**	AEM resources (error code start with "0xAE")
			**	----------------------------------------------------------------------------------------------------
			*/
			if (errorCode.ToString("X")->StartsWith("AE"))
			{
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 0 [General]
				**	----------------------------------------------------------------------------------------------------
				*/
				if (errorCode.ToString("X")->StartsWith("AE00"))
				{
					switch (errorCode)
					{
					case ER_S_OK: errorCodeMessage = "S_OK";												//break;
					case ER_ERROR_NOT_ENOUGH_MEMORY: errorCodeMessage = "ERROR_NOT_ENOUGH_MEMORY";								//break;
					case ER_ERROR_BAD_ARGUMENTS: errorCodeMessage = "ERROR_BAD_ARGUMENTS";									//break;
					case ER_ERROR_OPEN_FAILED: errorCodeMessage = "ERROR_OPEN_FAILED";									//break;
					case ER_AEM_INFO: errorCodeMessage = "AEM_INFO";											//break;
					case ER_AEM_WARNING: errorCodeMessage = "AEM_WARNING";											//break;
					case ER_AEM_ERROR: errorCodeMessage = "AEM_ERROR";											//break;
					case ER_AEM_CRITICAL: errorCodeMessage = "AEM_CRITICAL";										//break;
					}
					ErrorMessage = "[AEM Facility Code 0: General] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 1 [AemIPC]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE01"))
				{
					switch (errorCode)
					{
					case ER_AEMIPC_E_NOT_OPEN: errorCodeMessage = "AEMIPC_E_NOT_OPEN";									//break;
					case ER_AEMIPC_E_ALREADY_OPEN: errorCodeMessage = "AEMIPC_E_ALREADY_OPEN";								//break;
					}
					ErrorMessage = "[AEM Facility Code 1: AemIPC] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 2 [AemDAPI]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE02"))
				{
					switch (errorCode)
					{
					case ER_AEMHW_E_SYSTYPE_MISMATCH: errorCodeMessage = "AEMHW_E_SYSTYPE_MISMATCH";							//break;
					case ER_AEMHW_E_INVALID_HANDLE: errorCodeMessage = "AEMHW_E_INVALID_HANDLE";								//break;
					case ER_AEMHW_E_INVALID_RESULT: errorCodeMessage = "AEMHW_E_INVALID_RESULT";								//break;
					case ER_AEMHW_E_LOAD_AVEC_OVERFLOW: errorCodeMessage = "AEMHW_E_LOAD_AVEC_OVERFLOW";							//break;
					case ER_AEMDUSB_E_CANNOT_WRITE_TO_DEVICE: errorCodeMessage = "AEMDUSB_E_CANNOT_WRITE_TO_DEVICE";					//break;
					case ER_AEMDUSB_E_CANNOT_READ_FROM_DEVICE: errorCodeMessage = "AEMDUSB_E_CANNOT_READ_FROM_DEVICE";					//break;
					case ER_AEMDUSB_E_EXT_SIZE_NOT_MATCH_IPC: errorCodeMessage = "AEMDUSB_E_EXT_SIZE_NOT_MATCH_IPC";					//break;
					case ER_AEMDUSB_E_GET_SITEID_FAILED: errorCodeMessage = "AEMDUSB_E_GET_SITEID_FAILED";							//break;
					case ER_AEMDUSB_E_SITEID_ALREADY_EXIST: errorCodeMessage = "AEMDUSB_E_SITEID_ALREADY_EXIST";						//break;
					case ER_AEMDUSB_E_SITEID_NOT_FOUND: errorCodeMessage = "AEMDUSB_E_SITEID_NOT_FOUND";							//break;
					case ER_AEMDUSB_E_MODULEID_NOT_FOUND: errorCodeMessage = "AEMDUSB_E_MODULEID_NOT_FOUND";						//break;
					case ER_AEMDUSB_E_PORTID_NOT_FOUND: errorCodeMessage = "AEMDUSB_E_PORTID_NOT_FOUND";							//break;
					case ER_AEMDUSB_E_RESPINID_NOT_FOUND: errorCodeMessage = "AEMDUSB_E_RESPINID_NOT_FOUND";						//break;
					}
					ErrorMessage = "[AEM Facility Code 2: AemDAPI] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 3 [AemFlow]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE03"))
				{
					switch (errorCode)
					{
					case ER_AEMPARAMS_E_PARAM_NOT_FOUND: errorCodeMessage = "AEMPARAMS_E_PARAM_NOT_FOUND";							//break;
					case ER_AEMPARAMS_E_TEST_NOT_FOUND: errorCodeMessage = "AEMPARAMS_E_TEST_NOT_FOUND";							//break;
					case ER_AEMPARAMS_E_EMPTY_PARAM_VALUE: errorCodeMessage = "AEMPARAMS_E_EMPTY_PARAM_VALUE";						//break;
					case ER_AEMFLOW_E_OBJECT_NOT_FOUND: errorCodeMessage = "AEMFLOW_E_OBJECT_NOT_FOUND";							//break;
					case ER_AEMFLOW_E_OBJECT_ALREADY_EXISTS: errorCodeMessage = "AEMFLOW_E_OBJECT_ALREADY_EXISTS";						//break;
					case ER_AEMFLOW_E_NULL_OBJECT: errorCodeMessage = "AEMFLOW_E_NULL_OBJECT";								//break;
					case ER_AEMFLOW_E_DLL_LOAD_FAIL: errorCodeMessage = "AEMFLOW_E_DLL_LOAD_FAIL";								//break;
					case ER_AEMFLOW_E_DLL_FUNCTION_NOT_FOUND: errorCodeMessage = "AEMFLOW_E_DLL_FUNCTION_NOT_FOUND";					//break;
					case ER_AEMFLOW_E_DLL_FUNCTION_ERROR: errorCodeMessage = "AEMFLOW_E_DLL_FUNCTION_ERROR";						//break;
					}
					ErrorMessage = "[AEM Facility Code 3: AemFlow] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 4 [AemVector]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE04"))
				{
					switch (errorCode)
					{
					case ER_AEMVECTOR_UNSUPPORTED_EXT: errorCodeMessage = "AEMVECTOR_UNSUPPORTED_EXT";							//break;
					case ER_AEMVECTOR_SYNTAX_ERROR: errorCodeMessage = "AEMVECTOR_SYNTAX_ERROR";								//break;
					case ER_AEMVECTOR_FILE_CORRUPTED: errorCodeMessage = "AEMVECTOR_FILE_CORRUPTED";							//break;
					case ER_AEMVECTOR_CHECKSUM_ERROR: errorCodeMessage = "AEMVECTOR_CHECKSUM_ERROR";							//break;
					case ER_AEMVECTOR_LOADDLL_FAIL: errorCodeMessage = "AEMVECTOR_LOADDLL_FAIL";								//break;
					case ER_AEMVECTOR_LOADFUNCTION_FAIL: errorCodeMessage = "AEMVECTOR_LOADFUNCTION_FAIL";							//break;
					case ER_AEMVECTOR_TESTER_EXCEPTION: errorCodeMessage = "AEMVECTOR_TESTER_EXCEPTION";							//break;
					case ER_AEMVECTOR_NOT_FOUND: errorCodeMessage = "AEMVECTOR_NOT_FOUND";									//break;
					case ER_AEMVECTOR_DOBV_NOT_FOUND: errorCodeMessage = "AEMVECTOR_DOBV_NOT_FOUND";							//break;
					case ER_AEMVECTOR_LOAD_DVEC_OVERFLOW: errorCodeMessage = "AEMVECTOR_LOAD_DVEC_OVERFLOW";						//break;
					case ER_AEMVECTOR_INVALID_RESULT: errorCodeMessage = "AEMVECTOR_INVALID_RESULT";							//break;
					case ER_AEMVECTOR_INVALID_ARGUMENT: errorCodeMessage = "AEMVECTOR_INVALID_ARGUMENT";							//break;
					case ER_AEMVECTOR_INVALID_CH: errorCodeMessage = "AEMVECTOR_INVALID_CH";								//break;
					case ER_AEMVECTOR_UNDEFINED_PIN: errorCodeMessage = "AEMVECTOR_UNDEFINED_PIN";								//break;
					case ER_AEMVECTOR_INVALID_HEADER: errorCodeMessage = "AEMVECTOR_INVALID_HEADER";							//break;
					}
					ErrorMessage = "[AEM Facility Code 4: AemVector] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 5 [AemHW]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE05"))
				{
					switch (errorCode)
					{
					case ER_AEMHW_E_CANNOT_WRITE_TO_HW: errorCodeMessage = "AEMHW_E_CANNOT_WRITE_TO_HW";							//break;
					case ER_AEMHW_E_CANNOT_READ_FROM_HW: errorCodeMessage = "AEMHW_E_CANNOT_READ_FROM_HW";							//break;
					case ER_AEMHW_E_COMM_TIMED_OUT: errorCodeMessage = "AEMHW_E_COMM_TIMED_OUT";								//break;
					case ER_AEMHW_E_TEMPERATURE_OVERHEAT: errorCodeMessage = "AEMHW_E_TEMPERATURE_OVERHEAT";						//break;
					case ER_AEMHW_E_FAILED_UPGRADE_FIRMWARE: errorCodeMessage = "AEMHW_E_FAILED_UPGRADE_FIRMWARE";						//break;
					case ER_AEMHW_E_WRONG_MSG_SIZE: errorCodeMessage = "AEMHW_E_WRONG_MSG_SIZE";								//break;
					case ER_AEMHW_E_API_NOT_IMPLEMENTED: errorCodeMessage = "AEMHW_E_API_NOT_IMPLEMENTED";							//break;
					case ER_AEMHW_E_INVALID_CARD_TYPE: errorCodeMessage = "AEMHW_E_INVALID_CARD_TYPE";							//break;
					case ER_AEMHW_E_FIRMWARE_FILE_CHECKSUM_ERROR: errorCodeMessage = "AEMHW_E_FIRMWARE_FILE_CHECKSUM_ERROR";				//break;
					case ER_AEMHW_E_FIRMWARE_FILESIZE_ERROR: errorCodeMessage = "AEMHW_E_FIRMWARE_FILESIZE_ERROR";						//break;
					case ER_AEMHW_E_WAIT4UNLOCK_TIMEOUT: errorCodeMessage = "AEMHW_E_WAIT4UNLOCK_TIMEOUT";							//break;
					case ER_AEMHW_E_WAIT4READY_TIMEOUT: errorCodeMessage = "AEMHW_E_WAIT4READY_TIMEOUT";							//break;
					}
					ErrorMessage = "[AEM Facility Code 5: AemHW] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 6 [AemDig]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE06"))
				{
					switch (errorCode)
					{
					case ER_AEMDIG_E_READ_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_READ_EPCS_FAIL";								//break;
					case ER_AEMDIG_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_ERASE_EPCS_FAIL";							//break;
					case ER_AEMDIG_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_WRITE_EPCS_FAIL";							//break;
					case ER_AEMDIG_E_OPEN_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_OPEN_EPCS_FAIL";								//break;
					case ER_AEMDIG_E_WRITE_EEPROM_FAIL: errorCodeMessage = "AEMDIG_E_WRITE_EEPROM_FAIL";							//break;
					case ER_AEMDIG_E_READ_EEPROM_FAIL: errorCodeMessage = "AEMDIG_E_READ_EEPROM_FAIL";							//break;
					case ER_AEMDIG_E_VEC_VARNUM_NOT_MATCH: errorCodeMessage = "AEMDIG_E_VEC_VARNUM_NOT_MATCH";						//break;
					case ER_AEMDIG_E_HA_ERASE_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_HA_ERASE_EPCS_FAIL";							//break;
					case ER_AEMDIG_E_HA_WRITE_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_HA_WRITE_EPCS_FAIL";							//break;
					case ER_AEMDIG_E_HA_READ_EPCS_FAIL: errorCodeMessage = "AEMDIG_E_HA_READ_EPCS_FAIL";							//break;
					case ER_AEMDIG_E_HA_ERASE_UFM_FAIL: errorCodeMessage = "AEMDIG_E_HA_ERASE_UFM_FAIL";							//break;
					case ER_AEMDIG_E_HA_WRITE_UFM_FAIL: errorCodeMessage = "AEMDIG_E_HA_WRITE_UFM_FAIL";							//break;
					case ER_AEMDIG_E_HA_READ_UFM_FAIL: errorCodeMessage = "AEMDIG_E_HA_READ_UFM_FAIL";							//break;
					case ER_AEMDIG_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMDIG_E_FIRMWARE_FILE_NOT_FOUND";					//break;
					case ER_AEMDIG_E_COMM_TIMED_OUT: errorCodeMessage = "AEMDIG_E_COMM_TIMED_OUT";								//break;
					case ER_AEMDIG_E_FREQ_MEAS_TIMED_OUT: errorCodeMessage = "AEMDIG_E_FREQ_MEAS_TIMED_OUT";						//break;
					case ER_AEMDIG_E_DC_MEAS_TIMED_OUT: errorCodeMessage = "AEMDIG_E_DC_MEAS_TIMED_OUT";							//break;
					case ER_AEMDIG_E_UPGRADE_TOOL_OUTDATED: errorCodeMessage = "AEMDIG_E_UPGRADE_TOOL_OUTDATED";						//break;
					case ER_AEMDIG_E_RESOURCE_UNAVAILABLE: errorCodeMessage = "AEMDIG_E_RESOURCE_UNAVAILABLE";						//break;
					case ER_AEMDIG_E_RESOURCE_ALREADY_RELEASED: errorCodeMessage = "AEMDIG_E_RESOURCE_ALREADY_RELEASED";					//break;
					case ER_AEMDIG_E_COMM_BUS_OCCUPIED: errorCodeMessage = "AEMDIG_E_COMM_BUS_OCCUPIED";							//break;
					case ER_AEMDIG_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMDIG_E_CAL_HEADER_NOT_FOUND";						//break;
					case ER_AEMDIG_E_CAL_SIZE_INVALID: errorCodeMessage = "AEMDIG_E_CAL_SIZE_INVALID";							//break;
					case ER_AEMDIG_E_CAL_DATA_OUT_OF_RANGE: errorCodeMessage = "AEMDIG_E_CAL_DATA_OUT_OF_RANGE";						//break;
					case ER_AEMDIG_E_JTAG_INVALID_SIZE: errorCodeMessage = "AEMDIG_E_JTAG_INVALID_SIZE";							//break;
					case ER_AEMDIG_E_JTAG_INVALID_COMMAND: errorCodeMessage = "AEMDIG_E_JTAG_INVALID_COMMAND";						//break;
					case ER_AEMDIG_E_JTAG_NOT_DONE: errorCodeMessage = "AEMDIG_E_JTAG_NOT_DONE";								//break;
					}
					ErrorMessage = "[AEM Facility Code 6: AemDig] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 7 [AemSmu & AemDCPwr]
				**	----------------------------------------------------------------------------------------------------
				*/
#if SMU_ENABLE 
				else if (errorCode.ToString("X")->StartsWith("AE07"))
				{
					switch (errorCode)
					{
						// 7-AemSmu
					case ER_AEMSMU_E_CURRENT_OVERDRIVE: errorCodeMessage = "AEMSMU_E_CURRENT_OVERDRIVE";							//break;
					case ER_AEMSMU_E_COMM_TIMED_OUT: errorCodeMessage = "AEMSMU_E_COMM_TIMED_OUT";								//break;
					case ER_AEMSMU_E_INTERLOCKOFF: errorCodeMessage = "AEMSMU_E_INTERLOCKOFF";								//break;
					case ER_AEMSMU_E_SMUOFF: errorCodeMessage = "AEMSMU_E_SMUOFF";										//break;
					case ER_AEMSMU_E_SMU_NOT_FOUND: errorCodeMessage = "AEMSMU_E_SMU_NOT_FOUND";								//break;
					case ER_AEMSMU_E_MEASCOUNT_OVERFLOW: errorCodeMessage = "AEMSMU_E_MEASCOUNT_OVERFLOW";							//break;
					case ER_AEMSMU_E_VEC_VARNUM_NOT_MATCH: errorCodeMessage = "AEMSMU_E_VEC_VARNUM_NOT_MATCH";						//break;
					case ER_AEMSMU_E_WRONG_PIN_NUM: errorCodeMessage = "AEMSMU_E_WRONG_PIN_NUM";								//break;
					case ER_AEMSMU_E_RDAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_RDAC_TIMED_OUT";								//break;
					case ER_AEMSMU_E_OPDAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_OPDAC_TIMED_OUT";							//break;
					case ER_AEMSMU_E_WRONG_DAC_CH: errorCodeMessage = "AEMSMU_E_WRONG_DAC_CH";								//break;
					case ER_AEMSMU_E_OP_DAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_OP_DAC_TIMED_OUT";							//break;
					case ER_AEMSMU_E_MISC_DAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_MISC_DAC_TIMED_OUT";							//break;
					case ER_AEMSMU_E_EXTIN_MDAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_EXTIN_MDAC_TIMED_OUT";						//break;
					case ER_AEMSMU_E_ADC0_TIMED_OUT: errorCodeMessage = "AEMSMU_E_ADC0_TIMED_OUT";								//break;
					case ER_AEMSMU_E_ADC1_TIMED_OUT: errorCodeMessage = "AEMSMU_E_ADC1_TIMED_OUT";								//break;
					case ER_AEMSMU_E_ADC2_TIMED_OUT: errorCodeMessage = "AEMSMU_E_ADC2_TIMED_OUT";								//break;
					case ER_AEMSMU_E_EPCS_SE_TIMED_OUT: errorCodeMessage = "AEMSMU_E_EPCS_SE_TIMED_OUT";							//break;
					case ER_AEMSMU_E_EPCS_RD_TIMED_OUT: errorCodeMessage = "AEMSMU_E_EPCS_RD_TIMED_OUT";							//break;
					case ER_AEMSMU_E_EPCS_WR_TIMED_OUT: errorCodeMessage = "AEMSMU_E_EPCS_WR_TIMED_OUT";							//break;
					case ER_AEMSMU_E_AWG_TIMED_OUT: errorCodeMessage = "AEMSMU_E_AWG_TIMED_OUT";								//break;
					case ER_AEMSMU_E_WRONG_CALTYPE: errorCodeMessage = "AEMSMU_E_WRONG_CALTYPE";								//break;
					case ER_AEMSMU_E_ERASE_FLASH_FAIL: errorCodeMessage = "AEMSMU_E_ERASE_FLASH_FAIL";							//break;
					case ER_AEMSMU_E_WRITE_FLASH_FAIL: errorCodeMessage = "AEMSMU_E_WRITE_FLASH_FAIL";							//break;
					case ER_AEMSMU_E_READ_FLASH_FAIL: errorCodeMessage = "AEMSMU_E_READ_FLASH_FAIL";							//break;
					case ER_AEMSMU_E_WRONG_VI_READ: errorCodeMessage = "AEMSMU_E_WRONG_VI_READ";								//break;
					case ER_AEMSMU_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMSMU_E_FIRMWARE_FILE_NOT_FOUND";					//break;
					case ER_AEMSMU_E_FIRMWARE_FILE_WRONG_SIZE: errorCodeMessage = "AEMSMU_E_FIRMWARE_FILE_WRONG_SIZE";					//break;
					case ER_AEMSMU_E_VDET_MDAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_VDET_MDAC_TIMED_OUT";						//break;
					case ER_AEMSMU_E_IDET_MDAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_IDET_MDAC_TIMED_OUT";						//break;
					case ER_AEMSMU_E_VBUF_HI_MDAC_TIMED_OUT: errorCodeMessage = "AEMSMU_E_VBUF_HI_MDAC_TIMED_OUT";						//break;
					case ER_AEMSMU_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMSMU_E_CAL_HEADER_NOT_FOUND";						//break;
					case ER_AEMSMU_E_CAL_SIZE_NOT_MATCH: errorCodeMessage = "AEMSMU_E_CAL_SIZE_NOT_MATCH";							//break;
					case ER_AEMSMU_E_INVALID_BOOST_STEP: errorCodeMessage = "AEMSMU_E_INVALID_BOOST_STEP";							//break;
					case ER_AEMSMU_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMSMU_E_WRONG_FIRMWARE_FILE_USED";					//break;
					case ER_AEMSMU_E_COMMON_MODE_CAL_OUT_OF_RANGE: errorCodeMessage = "AEMSMU_E_COMMON_MODE_CAL_OUT_OF_RANGE";				//break;
					case ER_AEMSMU_E_BANDWIDTH_OUT_OF_RANGE: errorCodeMessage = "AEMSMU_E_BANDWIDTH_OUT_OF_RANGE";						//break;
					case ER_AEMSMU_E_NPLC_TOO_BIG_WARNING: errorCodeMessage = "AEMSMU_E_NPLC_TOO_BIG_WARNING";						//break;
					case ER_AEMSMU_E_CAL_FILE_NOT_FOUND: errorCodeMessage = "AEMSMU_E_CAL_FILE_NOT_FOUND";							//break;
					case ER_AEMSMU_E_INVALID_CAL_FILE: errorCodeMessage = "AEMSMU_E_INVALID_CAL_FILE";							//break;
					case ER_AEMSMU_E_INVALID_RELAY_SIZE: errorCodeMessage = "AEMSMU_E_INVALID_RELAY_SIZE";							//break;
					case ER_AEMSMU_E_INVALID_HEADER: errorCodeMessage = "AEMSMU_E_INVALID_HEADER";								//break;
					case ER_AEMSMU_E_LOAD_CAL_FAIL: errorCodeMessage = "AEMSMU_E_LOAD_CAL_FAIL";								//break;
					case ER_AEMSMU_E_BW_TOO_HIGH_WARNING: errorCodeMessage = "AEMSMU_E_BW_TOO_HIGH_WARNING";						//break;
					case ER_AEMSMU_E_BW_TOO_LOW_WARNING: errorCodeMessage = "AEMSMU_E_BW_TOO_LOW_WARNING";							//break;
					case ER_AEMSMU_E_OVER_TEMPERATURE: errorCodeMessage = "AEMSMU_E_OVER_TEMPERATURE";							//break;
					case ER_AEMSMU_E_RESOURCE_OCCUPIED: errorCodeMessage = "AEMSMU_E_RESOURCE_OCCUPIED";							//break;
					case ER_AEMSMU_E_RESOURCE_NOT_READY: errorCodeMessage = "AEMSMU_E_RESOURCE_NOT_READY";							//break;
					case ER_AEMSMU_E_HS_PROTECTION_ENGAGE_OR_LV_NOT_FOUND: errorCodeMessage = "AEMSMU_E_HS_PROTECTION_ENGAGE_OR_LV_NOT_FOUND";		//break;
																																					//case ER_AEMSMU_E_LV_NOT_FOUND								: errorCodeMessage = "AEMSMU_E_LV_NOT_FOUND";								//break;
					case ER_AEMSMU_E_HV_NOT_FOUND: errorCodeMessage = "AEMSMU_E_HV_NOT_FOUND";								//break;
					case ER_AEMSMU_E_HAM_NOT_FOUND: errorCodeMessage = "AEMSMU_E_HAM_NOT_FOUND";								//break;
					case ER_AEMSMU_E_DTM130_NOT_FOUND: errorCodeMessage = "AEMSMU_E_DTM130_NOT_FOUND";							//break;
					case ER_AEMSMU_E_SCOPE_DATA_INVALID: errorCodeMessage = "AEMSMU_E_SCOPE_DATA_INVALID";							//break;
					case ER_AEMSMU_E_HAM320_NOT_FOUND: errorCodeMessage = "AEMSMU_E_HAM320_NOT_FOUND";							//break;
					case ER_AEMSMU_E_HAM330_NOT_FOUND: errorCodeMessage = "AEMSMU_E_HAM330_NOT_FOUND";							//break;
					case ER_AEMSMU_E_HAM340_NOT_FOUND: errorCodeMessage = "AEMSMU_E_HAM340_NOT_FOUND";							//break;
					case ER_AEMSMU_E_SITE01_NOT_FOUND: errorCodeMessage = "AEMSMU_E_SITE01_NOT_FOUND";							//break;
					case ER_AEMSMU_E_SITE23_NOT_FOUND: errorCodeMessage = "AEMSMU_E_SITE23_NOT_FOUND";							//break;
					case ER_AEMSMU_E_OVER_POWER_LIMIT: errorCodeMessage = "AEMSMU_E_OVER_POWER_LIMIT";							//break;
					case ER_AEMSMU_E_COMM_ERROR: errorCodeMessage = "AEMSMU_E_COMM_ERROR";									//break;
					case ER_AEMSMU_E_SPI_RDLENGTH_MISTMATCH: errorCodeMessage = "AEMSMU_E_SPI_RDLENGTH_MISTMATCH";						//break;
					case ER_AEMSMU_E_INVALID_CAL_ACCUM_COUNT: errorCodeMessage = "AEMSMU_E_INVALID_CAL_ACCUM_COUNT";					//break;
					case ER_AEMSMU_E_INVALID_CAL_DATE: errorCodeMessage = "AEMSMU_E_INVALID_CAL_DATE";							//break;
					case ER_AEMSMU_E_INVALID_CAL_TIME: errorCodeMessage = "AEMSMU_E_INVALID_CAL_TIME";							//break;
					case ER_AEMSMU_E_INVALID_CAL_TEMPERATURE: errorCodeMessage = "AEMSMU_E_INVALID_CAL_TEMPERATURE";					//break;
					case ER_AEMSMU_E_INVALID_CAL_INTERVAL_MONTHS: errorCodeMessage = "AEMSMU_E_INVALID_CAL_INTERVAL_MONTHS";				//break;
					case ER_AEMSMU_E_CAL_DATA_OUT_OF_RANGE: errorCodeMessage = "AEMSMU_E_CAL_DATA_OUT_OF_RANGE";						//break;
					case ER_AEMSMU_E_MODEL_NOT_MATCH: errorCodeMessage = "AEMSMU_E_MODEL_NOT_MATCH";							//break;
					case ER_AEMSMU_E_CASCADE_MODE_ERROR: errorCodeMessage = "AEMSMU_E_CASCADE_MODE_ERROR";							//break;
					case ER_AEMSMU_E_MODEL_NOT_SUPPORTED: errorCodeMessage = "AEMSMU_E_MODEL_NOT_SUPPORTED";						//break;
					case ER_AEMSMU_E_PULSE_DURATION_ERROR: errorCodeMessage = "AEMSMU_E_PULSE_DURATION_ERROR";						//break;
					case ER_AEMSMU_E_AIBANDWIDTH_INVALID_LOAD: errorCodeMessage = "AEMSMU_E_AIBANDWIDTH_INVALID_LOAD";					//break;
					case ER_AEMSMU_E_AIBANDWIDTH_INVALID_SETTLING_TIME: errorCodeMessage = "AEMSMU_E_AIBANDWIDTH_INVALID_SETTLING_TIME";			//break;
					case ER_AEMSMU_E_PULSE_VALUE_ERROR: errorCodeMessage = "AEMSMU_E_PULSE_VALUE_ERROR";							//break;
					case ER_AEMSMU_E_ADAPTER_BOARD_NOT_DETECTED: errorCodeMessage = "AEMSMU_E_ADAPTER_BOARD_NOT_DETECTED";					//break;
					case ER_AEMSMU_E_INVALID_SETTING: errorCodeMessage = "AEMSMU_E_INVALID_SETTING";							//break;
					case ER_AEMSMU_E_INVALID_INTERVAL: errorCodeMessage = "AEMSMU_E_INVALID_INTERVAL";							//break;
					case ER_AEMSMU_E_PULSE_OPERATION_IS_ARMED: errorCodeMessage = "AEMSMU_E_PULSE_OPERATION_IS_ARMED	";					//break;
					case ER_AEMSMU_E_PULSE_OPERATION_IS_UNDONE: errorCodeMessage = "AEMSMU_E_PULSE_OPERATION_IS_UNDONE";					//break;
					case ER_AEMSMU_E_INVALID_BW_FV: errorCodeMessage = "AEMSMU_E_INVALID_BW_FV";								//break;
					case ER_AEMSMU_E_INVALID_BW_FI: errorCodeMessage = "AEMSMU_E_INVALID_BW_FI";								//break;
					case ER_AEMSMU_E_DPS_NOT_FOUND: errorCodeMessage = "AEMSMU_E_DPS_NOT_FOUND";								//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_MV: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_MV";							//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_LSB: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_LSB";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_MSB_D13: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_MSB_D13";					//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_MSB_D14: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_MSB_D14";					//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_MSB_D15: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_MSB_D15";					//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_OFFDAC: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_OFFDAC";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_GAINDAC: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_GAINDAC";					//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_FV: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_FV";							//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_ADJ0: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_ADJ0";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_ADJ1: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_ADJ1";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_ADJ2: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_ADJ2";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_LADJ3: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_LADJ3";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_HADJ3: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_HADJ3";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_LADJ4: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_LADJ4";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_HADJ4: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_HADJ4";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_ADJ5: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_ADJ5";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_MISRC: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_MISRC";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_MISNK: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_MISNK";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_CISRC: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_CISRC";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_CISNK: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_CISNK";						//break;
					case ER_AEMSMU_E_DPS_INVALID_CAL_FI: errorCodeMessage = "AEMSMU_E_DPS_INVALID_CAL_FI";							//break;
					case ER_AEMSMU_E_PROTECTION_ACTIVATED: errorCodeMessage = "AEMSMU_E_PROTECTION_ACTIVATED";						//break;
					case ER_AEMSMU_E_OVI_PROTECTION_LATCHED: errorCodeMessage = "AEMSMU_E_OVI_PROTECTION_LATCHED";						//break;
					case ER_AEMSMU_E_BAD_ARGUMENTS: errorCodeMessage = "AEMSMU_E_BAD_ARGUMENTS";								//break;
					case ER_AEMSMU_E_INVALID_APERTURE_TIME_UNIT: errorCodeMessage = "AEMSMU_E_INVALID_APERTURE_TIME_UNIT";					//break;
					case ER_AEMSMU_E_INVALID_ARGUMENTS: errorCodeMessage = "AEMSMU_E_INVALID_ARGUMENTS";							//break;
					case ER_AEMSMU_E_DLL_NOT_FOUND: errorCodeMessage = "AEMSMU_E_DLL_NOT_FOUND";								//break;
					case ER_AEMSMU_E_API_NOT_FOUND: errorCodeMessage = "AEMSMU_E_API_NOT_FOUND";								//break;
					case ER_AEMSMU_E_CARD_NOT_FOUND: errorCodeMessage = "AEMSMU_E_CARD_NOT_FOUND";								//break;
					case ER_AEMSMU_E_OPEN_FAIL: errorCodeMessage = "AEMSMU_E_OPEN_FAIL";									//break;
					case ER_AEMSMU_E_SYS_ID_NOT_FOUND: errorCodeMessage = "AEMSMU_E_SYS_ID_NOT_FOUND";							//break;
					case ER_AEMSMU_E_FIRMWARE_FILE_CHECKSUM_ERROR: errorCodeMessage = "AEMSMU_E_FIRMWARE_FILE_CHECKSUM_ERROR";				//break;
					case ER_AEMSMU_E_INVALID_ACTION: errorCodeMessage = "AEMSMU_E_INVALID_ACTION";								//break;
					case ER_AEMSMU_RESERVED1: errorCodeMessage = "AEMSMU_RESERVED1";									//break;
					case ER_AEMSMU_RESERVED2: errorCodeMessage = "AEMSMU_RESERVED2";									//break;
					case ER_AEMSMU_RESERVED3: errorCodeMessage = "AEMSMU_RESERVED3";									//break;
					case ER_AEMSMU_E_EXTTRIGARM_TIMEOUT: errorCodeMessage = "AEMSMU_E_EXTTRIGARM_TIMEOUT";							//break;
					case ER_AEMSMU_E_EXTTRIGARM_ARMED: errorCodeMessage = "AEMSMU_E_EXTTRIGARM_ARMED";							//break;
					case ER_AEMSMU_E_EXTTRIGGET_BUSY: errorCodeMessage = "AEMSMU_E_EXTTRIGGET_BUSY";							//break;
					case ER_AEMSMU_E_READCURR10x_RANGE_NOT_SUPPORTED: errorCodeMessage = "AEMSMU_E_READCURR10x_RANGE_NOT_SUPPORTED";			//break;
																																				// 7-AemDCPwr
					case ER_AEMDCPWR_E_DCLC_DEBUG_IDLE: errorCodeMessage = "AEMDCPWR_E_DCLC_DEBUG_IDLE";							//break;
					case ER_AEMDCPWR_E_DCLC_DEBUG_BUSY: errorCodeMessage = "AEMDCPWR_E_DCLC_DEBUG_BUSY";							//break;
					case ER_AEMDCPWR_E_EXCEED_NULL_LIMIT: errorCodeMessage = "AEMDCPWR_E_EXCEED_NULL_LIMIT";						//break;
					case ER_AEMDCPWR_E_INVALID_CHANNEL: errorCodeMessage = "AEMDCPWR_E_INVALID_CHANNEL";							//break;
					case ER_AEMDCPWR_E_INVALID_CURRENT_LEVEL: errorCodeMessage = "AEMDCPWR_E_INVALID_CURRENT_LEVEL";					//break;
					case ER_AEMDCPWR_E_INVALID_CURRENT_LIMIT: errorCodeMessage = "AEMDCPWR_E_INVALID_CURRENT_LIMIT";					//break;
					case ER_AEMDCPWR_E_INVALID_VOLTAGE_LEVEL: errorCodeMessage = "AEMDCPWR_E_INVALID_VOLTAGE_LEVEL";					//break;
					case ER_AEMDCPWR_E_INVALID_VOLTAGE_LIMIT: errorCodeMessage = "AEMDCPWR_E_INVALID_VOLTAGE_LIMIT";					//break;
					case ER_AEMDCPWR_E_INVALID_VOLTAGE_RANGE: errorCodeMessage = "AEMDCPWR_E_INVALID_VOLTAGE_RANGE";					//break;
					case ER_AEMDCPWR_E_INVALID_CURRENT_RANGE: errorCodeMessage = "AEMDCPWR_E_INVALID_CURRENT_RANGE";					//break;
					case ER_AEMDCPWR_E_EXCEED_CHANNEL_LIMIT: errorCodeMessage = "AEMDCPWR_E_EXCEED_CHANNEL_LIMIT";						//break;
					case ER_AEMDCPWR_E_INVALID_ACTION: errorCodeMessage = "AEMDCPWR_E_INVALID_ACTION";							//break;
					case ER_AEMDCPWR_E_INVALID_OUTPUT_STATE: errorCodeMessage = "AEMDCPWR_E_INVALID_OUTPUT_STATE";						//break;
					case ER_AEMDCPWR_E_INVALID_POWER_LINE_FREQUENCY: errorCodeMessage = "AEMDCPWR_E_INVALID_POWER_LINE_FREQUENCY";				//break;
					case ER_AEMDCPWR_E_INVALID_OUTPUT_FUNCTION: errorCodeMessage = "AEMDCPWR_E_INVALID_OUTPUT_FUNCTION";					//break;
					case ER_AEMDCPWR_E_INVALID_SENSE: errorCodeMessage = "AEMDCPWR_E_INVALID_SENSE";							//break;
					case ER_AEMDCPWR_E_INVALID_CHANNEL_COUNT: errorCodeMessage = "AEMDCPWR_E_INVALID_CHANNEL_COUNT";					//break;
					case ER_AEMDCPWR_E_INVALID_CHANNEL_NAME: errorCodeMessage = "AEMDCPWR_E_INVALID_CHANNEL_NAME";						//break;
					case ER_AEMDCPWR_E_INVALID_MEASUREMENT_TYPE: errorCodeMessage = "AEMDCPWR_E_INVALID_MEASUREMENT_TYPE";					//break;
					case ER_AEMDCPWR_E_INVALID_SOURCE_MODE: errorCodeMessage = "AEMDCPWR_E_INVALID_SOURCE_MODE";						//break;
					case ER_AEMDCPWR_E_INVALID_APERTURE_TIME_UNIT: errorCodeMessage = "AEMDCPWR_E_INVALID_APERTURE_TIME_UNIT";				//break;
					case ER_AEMDCPWR_E_INVALID_EDGE_SETTING: errorCodeMessage = "AEMDCPWR_E_INVALID_EDGE_SETTING";						//break;
					case ER_AEMDCPWR_E_INVALID_TIMEOUT_VALUE: errorCodeMessage = "AEMDCPWR_E_INVALID_TIMEOUT_VALUE";					//break;
					case ER_AEMDCPWR_E_FETCHMULTIPLE_TIMEOUT: errorCodeMessage = "AEMDCPWR_E_FETCHMULTIPLE_TIMEOUT";					//break;
					case ER_AEMDCPWR_E_INVALID_OUTPUT_TRANSIENT: errorCodeMessage = "AEMDCPWR_E_INVALID_OUTPUT_TRANSIENT";					//break;
					case ER_AEMDCPWR_E_INVALID_OUTPUT_RESISTANCE: errorCodeMessage = "AEMDCPWR_E_INVALID_OUTPUT_RESISTANCE";				//break;
					case ER_AEMDCPWR_E_INVALID_ACQUIRE_LENGTH: errorCodeMessage = "AEMDCPWR_E_INVALID_ACQUIRE_LENGTH";					//break;
					case ER_AEMDCPWR_E_INVALID_ACQUIRE_DELTA_TIME: errorCodeMessage = "AEMDCPWR_E_INVALID_ACQUIRE_DELTA_TIME";				//break;
					case ER_AEMDCPWR_E_INVALID_MULTI_SITE_MODE: errorCodeMessage = "AEMDCPWR_E_INVALID_MULTI_SITE_MODE";					//break;
					case ER_AEMDCPWR_E_SMU_OFF: errorCodeMessage = "AEMDCPWR_E_SMU_OFF";									//break;
					case ER_AEMDCPWR_E_AIBANDWIDTH_OUT_OF_RANGE: errorCodeMessage = "AEMDCPWR_E_AIBANDWIDTH_OUT_OF_RANGE";					//break;
					case ER_AEMDCPWR_E_INVALID_SSRAM_ADDRESS: errorCodeMessage = "AEMDCPWR_E_INVALID_SSRAM_ADDRESS";					//break;
					case ER_AEMDCPWR_E_INVALID_MEASURE_MODE: errorCodeMessage = "AEMDCPWR_E_INVALID_MEASURE_MODE";						//break;
					case ER_AEMDCPWR_E_EXCEED_AWG_SIZE_LIMIT: errorCodeMessage = "AEMDCPWR_E_EXCEED_AWG_SIZE_LIMIT";					//break;
					case ER_AEMDCPWR_E_INVALID_AWG_FREQUENCY: errorCodeMessage = "AEMDCPWR_E_INVALID_AWG_FREQUENCY";					//break;
					case ER_AEMDCPWR_E_INVALID_AWG_CYCLE: errorCodeMessage = "AEMDCPWR_E_INVALID_AWG_CYCLE";						//break;
					case ER_AEMDCPWR_E_AWG_BUSY: errorCodeMessage = "AEMDCPWR_E_AWG_BUSY";									//break;
					case ER_AEMDCPWR_E_INVALID_AWG_MODE: errorCodeMessage = "AEMDCPWR_E_INVALID_AWG_MODE";							//break;
					case ER_AEMDCPWR_E_EXCEED_LIMIT: errorCodeMessage = "AEMDCPWR_E_EXCEED_LIMIT";								//break;
					}
					//ret = glob->smu[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcSMU[siteIndex], errorCode, ErrorMessage);
					ErrorMessage = "[AEM Facility Code 7: AemSmu & AemDCPwr] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
#endif 
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 8 [AemIom]
				**	----------------------------------------------------------------------------------------------------
				*/
#if DIO_ENABLE 
				else if (errorCode.ToString("X")->StartsWith("AE08"))
				{
					switch (errorCode)
					{
					case ER_AEMIOM_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMIOM_E_ERASE_EPCS_FAIL";							//break;
					case ER_AEMIOM_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMIOM_E_WRITE_EPCS_FAIL";							//break;
					case ER_AEMIOM_E_READ_EPCS_FAIL: errorCodeMessage = "AEMIOM_E_READ_EPCS_FAIL";								//break;
					case ER_AEMIOM_E_IOM_NOT_FOUND: errorCodeMessage = "AEMIOM_E_IOM_NOT_FOUND";								//break;
					case ER_AEMIOM_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMIOM_E_FIRMWARE_FILE_NOT_FOUND";					//break;
					case ER_AEMIOM_E_INVALID_PORT: errorCodeMessage = "AEMIOM_E_INVALID_PORT";								//break;
					case ER_AEMIOM_E_INVALID_PIN: errorCodeMessage = "AEMIOM_E_INVALID_PIN";								//break;
					case ER_AEMIOM_E_INVALID_OPTION: errorCodeMessage = "AEMIOM_E_INVALID_OPTION";								//break;
					case ER_AEMIOM_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMIOM_E_WRONG_FIRMWARE_FILE_USED";					//break;
					case ER_AEMIOM_E_COMM_TIMED_OUT: errorCodeMessage = "AEMIOM_E_COMM_TIMED_OUT";								//break;
					case ER_AEMIOM_E_INVALID_MULTI_SITE_MODE: errorCodeMessage = "AEMIOM_E_INVALID_MULTI_SITE_MODE";					//break;
					case ER_AEMIOM_E_INVALID_SPI_CHSEL: errorCodeMessage = "AEMIOM_E_INVALID_SPI_CHSEL";							//break;
					case ER_AEMIOM_E_INVALID_I2C_CHSEL: errorCodeMessage = "AEMIOM_E_INVALID_I2C_CHSEL";							//break;
					case ER_AEMIOM_E_INVALID_HEADER: errorCodeMessage = "AEMIOM_E_INVALID_HEADER";								//break;
					case ER_AEMIOM_E_VE_TIMED_OUT: errorCodeMessage = "AEMIOM_E_VE_TIMED_OUT";								//break;
					case ER_AEMIOM_E_INVALID_SPI_CORE: errorCodeMessage = "AEMIOM_E_INVALID_SPI_CORE";							//break;
					case ER_AEMIOM_E_INVALID_I2C_CORE: errorCodeMessage = "AEMIOM_E_INVALID_I2C_CORE";							//break;
					case ER_AEMIOM_E_FILE_NOT_FOUND: errorCodeMessage = "AEMIOM_E_FILE_NOT_FOUND";								//break;
					case ER_AEMIOM_E_FILE_CORRUPTED: errorCodeMessage = "AEMIOM_E_FILE_CORRUPTED";								//break;
					case ER_AEMIOM_E_BAD_ARGUMENTS: errorCodeMessage = "AEMIOM_E_BAD_ARGUMENTS";								//break;
					}
					//ret = glob->iom[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcIOM[siteIndex], errorCode, ErrorMessage);
					ErrorMessage = "[AEM Facility Code 8: AemIom] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
#endif
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 9 [AemPXIe]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE09"))
				{
					switch (errorCode)
					{
					case ER_AEMPXIE_E_OPEN_FAIL: errorCodeMessage = "AEMPXIE_E_OPEN_FAIL";									//break;
					case ER_AEMPXIE_E_DLL_NOT_FOUND: errorCodeMessage = "AEMPXIE_E_DLL_NOT_FOUND";								//break;
					case ER_AEMPXIE_E_API_NOT_FOUND: errorCodeMessage = "AEMPXIE_E_API_NOT_FOUND";								//break;
					case ER_AEMPXIE_E_INVALID_MULTI_SITE_MODE: errorCodeMessage = "AEMPXIE_E_INVALID_MULTI_SITE_MODE";					//break;
					case ER_AEMPXIE_E_OPEN_RM_FAIL: errorCodeMessage = "AEMPXIE_E_OPEN_RM_FAIL";								//break;
					case ER_AEMPXIE_E_DMA_READ_TIMEOUT: errorCodeMessage = "AEMPXIE_E_DMA_READ_TIMEOUT";							//break;
					case ER_AEMPXIE_E_INVALID_SUBDID: errorCodeMessage = "AEMPXIE_E_INVALID_SUBDID";							//break;
					case ER_AEMPXIE_E_RESOURCE_NOT_FOUND: errorCodeMessage = "AEMPXIE_E_RESOURCE_NOT_FOUND";						//break;
					case ER_AEMPXIE_E_MODULE_ALREAD_INIT: errorCodeMessage = "AEMPXIE_E_MODULE_ALREAD_INIT";						//break;
					case ER_AEMPXIE_E_API_NOT_FOUND_IN_DLL: errorCodeMessage = "AEMPXIE_E_API_NOT_FOUND_IN_DLL";						//break;
					case ER_AEMPXIE_E_BAD_ARGUMENTS: errorCodeMessage = "AEMPXIE_E_BAD_ARGUMENTS";								//break;
					case ER_AEMPXIE_RESERVED1: errorCodeMessage = "AEMPXIE_RESERVED1";									//break;
					}
					ErrorMessage = "[AEM Facility Code 9: AemPXIe] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 10 [AemDM]
				**	----------------------------------------------------------------------------------------------------
				*/
#if DM_ENABLE	
				else if (errorCode.ToString("X")->Contains("AE0A"))
				{
					switch (errorCode)
					{

					}
					ErrorMessage = "[AEM Facility Code 10: AemDM] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
#endif
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 11 [AemDM]
				**	----------------------------------------------------------------------------------------------------
				*/
#if DM_ENABLE 
				else if (errorCode.ToString("X")->Contains("AE0B"))
				{
					switch (errorCode)
					{
					case ER_AEMDM_E_INVALID_ARGUMENTS: errorCodeMessage = "AEMDM_E_INVALID_ARGUMENTS";								//break;
					case ER_AEMDM_E_INVALID_CALIBRATION_ARGUMENTS: errorCodeMessage = "AEMDM_E_INVALID_CALIBRATION_ARGUMENTS";					//break;
					case ER_AEMDM_E_UNDEFINED_VECTOR_SET: errorCodeMessage = "AEMDM_E_UNDEFINED_VECTOR_SET";							//break;
					case ER_AEMDM_E_CHANNEL_NOT_IN_PMU_STATE: errorCodeMessage = "AEMDM_E_CHANNEL_NOT_IN_PMU_STATE";						//break;
					case ER_AEMDM_E_ADATE_TIMEOUT: errorCodeMessage = "AEMDM_E_ADATE_TIMEOUT";									//break;
					case ER_AEMDM_E_ADC_TIMEOUT: errorCodeMessage = "AEMDM_E_ADC_TIMEOUT";										//break;
					case ER_AEMDM_E_DDS_TIMEOUT: errorCodeMessage = "AEMDM_E_DDS_TIMEOUT";										//break;
					case ER_AEMDM_E_PATTERN_MEMORY_TIMEOUT: errorCodeMessage = "AEMDM_E_PATTERN_MEMORY_TIMEOUT";							//break;
					case ER_AEMDM_E_HISTORY_RAM_TIMEOUT: errorCodeMessage = "AEMDM_E_HISTORY_RAM_TIMEOUT";								//break;
					case ER_AEMDM_E_D2R_FAIL_CALIBRATION_STAGE1: errorCodeMessage = "AEMDM_E_D2R_FAIL_CALIBRATION_STAGE1";						//break;
					case ER_AEMDM_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMDM_E_CAL_HEADER_NOT_FOUND";							//break;
					case ER_AEMDM_E_CAL_SIZE_NOT_MATCH: errorCodeMessage = "AEMDM_E_CAL_SIZE_NOT_MATCH";								//break;
					case ER_AEMDM_E_INVALID_CAL_ACCUM_COUNT: errorCodeMessage = "AEMDM_E_INVALID_CAL_ACCUM_COUNT";							//break;
					case ER_AEMDM_E_INVALID_CAL_DATE: errorCodeMessage = "AEMDM_E_INVALID_CAL_DATE";								//break;
					case ER_AEMDM_E_VECTOR_ENGINE_BUSY: errorCodeMessage = "AEMDM_E_VECTOR_ENGINE_BUSY";								//break;
					case ER_AEMDM_E_EXCEED_VECTOR_MEMORY_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_VECTOR_MEMORY_LIMIT";						//break;
					case ER_AEMDM_E_EXCEED_TOTAL_VECTOR_MEMORY_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_TOTAL_VECTOR_MEMORY_LIMIT";				//break;
					case ER_AEMDM_E_DM482E_NOT_FOUND: errorCodeMessage = "AEMDM_E_DM482E_NOT_FOUND";								//break;
					case ER_AEMDM_E_D2R_FAIL_CALIBRATION_STAGE2: errorCodeMessage = "AEMDM_E_D2R_FAIL_CALIBRATION_STAGE2";						//break;
					case ER_AEMDM_E_INPUT_DELAY_OUT_OF_RANGE: errorCodeMessage = "AEMDM_E_INPUT_DELAY_OUT_OF_RANGE";						//break;
					case ER_AEMDM_E_EXCEED_PERIOD_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_PERIOD_LIMIT";								//break;
					case ER_AEMDM_E_EXCEED_READ_VECTOR_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_READ_VECTOR_LIMIT";						//break;
					case ER_AEMDM_E_CHANNEL_NOT_IN_DIO_STATE: errorCodeMessage = "AEMDM_E_CHANNEL_NOT_IN_DIO_STATE";						//break;
					case ER_AEMDM_E_INVALID_DIO_VALUE: errorCodeMessage = "AEMDM_E_INVALID_DIO_VALUE";								//break;
					case ER_AEMDM_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMDM_E_FIRMWARE_FILE_NOT_FOUND";							//break;
					case ER_AEMDM_E_DM_NOT_FOUND: errorCodeMessage = "AEMDM_E_DM_NOT_FOUND";									//break;
					case ER_AEMDM_E_I2C_TIME_OUT: errorCodeMessage = "AEMDM_E_I2C_TIME_OUT";									//break;
					case ER_AEMDM_E_INVALID_TRIGGER_IN: errorCodeMessage = "AEMDM_E_INVALID_TRIGGER_IN";								//break;
					case ER_AEMDM_E_INVALID_TRIGGER_OUT: errorCodeMessage = "AEMDM_E_INVALID_TRIGGER_OUT";								//break;
					case ER_AEMDM_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMDM_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMDM_E_INVALID_INSTRUCTION_CORE: errorCodeMessage = "AEMDM_E_INVALID_INSTRUCTION_CORE";						//break;
					case ER_AEMDM_E_INSTRUCTION_LENGTH_OVERFLOW: errorCodeMessage = "AEMDM_E_INSTRUCTION_LENGTH_OVERFLOW";						//break;
					case ER_AEMDM_E_RECORDING_IN_PROGRESS: errorCodeMessage = "AEMDM_E_RECORDING_IN_PROGRESS";							//break;
					case ER_AEMDM_E_RECORDING_IDLE: errorCodeMessage = "AEMDM_E_RECORDING_IDLE";									//break;
					case ER_AEMDM_E_INVALID_RESULTS_TAG: errorCodeMessage = "AEMDM_E_INVALID_RESULTS_TAG";								//break;
					case ER_AEMDM_E_INVALID_RESULTS_REG: errorCodeMessage = "AEMDM_E_INVALID_RESULTS_REG";								//break;
					case ER_AEMDM_E_INSTRUCTION_LENGTH_ZERO: errorCodeMessage = "AEMDM_E_INSTRUCTION_LENGTH_ZERO";							//break;
					case ER_AEMDM_E_INVALID_SAMPLE_SIZE: errorCodeMessage = "AEMDM_E_INVALID_SAMPLE_SIZE";								//break;
					case ER_AEMDM_E_INVALID_PMU_STATE: errorCodeMessage = "AEMDM_E_INVALID_PMU_STATE";								//break;
					case ER_AEMDM_E_VECTOR_NOT_RUN: errorCodeMessage = "AEMDM_E_VECTOR_NOT_RUN";									//break;
					case ER_AEMDM_E_INVALID_CAL_TIME: errorCodeMessage = "AEMDM_E_INVALID_CAL_TIME";								//break;
					case ER_AEMDM_E_INVALID_CAL_INTERVAL_MONTHS: errorCodeMessage = "AEMDM_E_INVALID_CAL_INTERVAL_MONTHS";						//break;
					case ER_AEMDM_E_INVALID_PE_WRDATA: errorCodeMessage = "AEMDM_E_INVALID_PE_WRDATA";								//break;
					case ER_AEMDM_E_INVALID_PE_WRADDR: errorCodeMessage = "AEMDM_E_INVALID_PE_WRADDR";								//break;
					case ER_AEMDM_E_INVALID_PE_RDADDR: errorCodeMessage = "AEMDM_E_INVALID_PE_RDADDR";								//break;
					case ER_AEMDM_E_INVALID_RANGE: errorCodeMessage = "AEMDM_E_INVALID_RANGE";									//break;
					case ER_AEMDM_E_CAL_FILE_NOT_FOUND: errorCodeMessage = "AEMDM_E_CAL_FILE_NOT_FOUND";								//break;
					case ER_AEMDM_E_INVALID_CAL_FILE: errorCodeMessage = "AEMDM_E_INVALID_CAL_FILE";								//break;
					case ER_AEMDM_E_INVALID_CAL_TEMPERATURE: errorCodeMessage = "AEMDM_E_INVALID_CAL_TEMPERATURE";							//break;
					case ER_AEMDM_E_WR_RAM_TIMEOUT: errorCodeMessage = "AEMDM_E_WR_RAM_TIMEOUT";									//break;
					case ER_AEMDM_E_RD_RAM_TIMEOUT: errorCodeMessage = "AEMDM_E_RD_RAM_TIMEOUT";									//break;
					case ER_AEMDM_E_INVALID_LEVEL: errorCodeMessage = "AEMDM_E_INVALID_LEVEL";									//break;
					case ER_AEMDM_E_INVALID_EDGE_VALUE: errorCodeMessage = "AEMDM_E_INVALID_EDGE_VALUE";								//break;
					case ER_AEMDM_E_INVALID_FORCE_ACTION: errorCodeMessage = "AEMDM_E_INVALID_FORCE_ACTION";							//break;
					case ER_AEMDM_E_INVALID_DRIVE_ACTION: errorCodeMessage = "AEMDM_E_INVALID_DRIVE_ACTION";							//break;
					case ER_AEMDM_E_INVALID_RECEIVE_ACTION: errorCodeMessage = "AEMDM_E_INVALID_RECEIVE_ACTION";							//break;
					case ER_AEMDM_E_CAL_DATA_OUT_OF_RANGE: errorCodeMessage = "AEMDM_E_CAL_DATA_OUT_OF_RANGE";							//break;
					case ER_AEMDM_E_INVALID_INDEX: errorCodeMessage = "AEMDM_E_INVALID_INDEX";									//break;
					case ER_AEMDM_E_INVALID_PIN_NAME: errorCodeMessage = "AEMDM_E_INVALID_PIN_NAME";								//break;
					case ER_AEMDM_E_INVALID_OPCODE_DM481e: errorCodeMessage = "AEMDM_E_INVALID_OPCODE_DM481e";							//break;
					case ER_AEMDM_E_INVALID_WAVESET: errorCodeMessage = "AEMDM_E_INVALID_WAVESET";									//break;
					case ER_AEMDM_E_INVALID_CLK_FREQ: errorCodeMessage = "AEMDM_E_INVALID_CLK_FREQ";								//break;
					case ER_AEMDM_E_INVALID_CH: errorCodeMessage = "AEMDM_E_INVALID_CH";										//break;
					case ER_AEMDM_E_INVALID_MIPI_COMMAND: errorCodeMessage = "AEMDM_E_INVALID_MIPI_COMMAND";							//break;
					case ER_AEMDM_E_INVALID_MIPI_DATA: errorCodeMessage = "AEMDM_E_INVALID_MIPI_DATA";								//break;
					case ER_AEMDM_E_INVALID_MIPI_CONNECT: errorCodeMessage = "AEMDM_E_INVALID_MIPI_CONNECT";							//break;
					case ER_AEMDM_E_INVALID_MIPI_SPEED: errorCodeMessage = "AEMDM_E_INVALID_MIPI_SPEED";								//break;
					case ER_AEMDM_E_MIPI_STATUS_TIMEOUT: errorCodeMessage = "AEMDM_E_MIPI_STATUS_TIMEOUT";								//break;
					case ER_AEMDM_E_INVALID_MIPI_RDDATA_COUNT: errorCodeMessage = "AEMDM_E_INVALID_MIPI_RDDATA_COUNT";						//break;
					case ER_AEMDM_E_INVALID_MIPI_RDDATA: errorCodeMessage = "AEMDM_E_INVALID_MIPI_RDDATA";								//break;
					case ER_AEMDM_E_INVALID_MIPI_DELAY: errorCodeMessage = "AEMDM_E_INVALID_MIPI_DELAY";								//break;
					case ER_AEMDM_E_INVALID_SPI_CHSEL: errorCodeMessage = "AEMDM_E_INVALID_SPI_CHSEL";								//break;
					case ER_AEMDM_E_DIG_BUSY: errorCodeMessage = "AEMDM_E_DIG_BUSY";										//break;
					case ER_AEMDM_E_DIG_IDLE: errorCodeMessage = "AEMDM_E_DIG_IDLE";										//break;
					case ER_AEMDM_E_DIG_INVALID_STATUS: errorCodeMessage = "AEMDM_E_DIG_INVALID_STATUS";								//break;
					case ER_AEMDM_E_DIG_ARMED: errorCodeMessage = "AEMDM_E_DIG_ARMED";										//break;
					case ER_AEMDM_E_FREQ_COUNTER_BUSY: errorCodeMessage = "AEMDM_E_FREQ_COUNTER_BUSY";								//break;
					case ER_AEMDM_E_DIG_TIMEOUT: errorCodeMessage = "AEMDM_E_DIG_TIMEOUT";										//break;
					case ER_AEMDM_E_NOT_ENOUGH_MEMORY: errorCodeMessage = "AEMDM_E_NOT_ENOUGH_MEMORY	";								//break;
					case ER_AEMDM_E_INVALID_I2C_CHSEL: errorCodeMessage = "AEMDM_E_INVALID_I2C_CHSEL";								//break;
					case ER_AEMDM_E_UPGRADE_FIRMWARE_FAIL: errorCodeMessage = "AEMDM_E_UPGRADE_FIRMWARE_FAIL";							//break;
					case ER_AEMDM_E_UPGRADE_FIRMWARE_TIMEOUT: errorCodeMessage = "AEMDM_E_UPGRADE_FIRMWARE_TIMEOUT";						//break;
					case ER_AEMDM_E_DIG_PRETRIG_SAMPLE_INVALID: errorCodeMessage = "AEMDM_E_DIG_PRETRIG_SAMPLE_INVALID";						//break;
					case ER_AEMDM_E_COMM_TIMED_OUT: errorCodeMessage = "AEMDM_E_COMM_TIMED_OUT";									//break;
					case ER_AEMDM_E_BUFFERED_MODULE_INIT_FAIL: errorCodeMessage = "AEMDM_E_BUFFERED_MODULE_INIT_FAIL";						//break;
					case ER_AEMDM_E_RX_FAIL_CALIBRATION: errorCodeMessage = "AEMDM_E_RX_FAIL_CALIBRATION";								//break;
					case ER_AEMDM_E_OUTPUT_DELAY_OUT_OF_RANGE: errorCodeMessage = "AEMDM_E_OUTPUT_DELAY_OUT_OF_RANGE";						//break;
					case ER_AEMDM_E_WRONG_CALTYPE: errorCodeMessage = "AEMDM_E_WRONG_CALTYPE";									//break;
					case ER_AEMDM_E_INVALID_LENGTH: errorCodeMessage = "AEMDM_E_INVALID_LENGTH";									//break;
					case ER_AEMDM_E_MODULE_NOT_SUPPORTED_FOR_THIS_PATFILE: errorCodeMessage = "AEMDM_E_MODULE_NOT_SUPPORTED_FOR_THIS_PATFILE";			//break;
					case ER_AEMDM_E_THIS_PATFILE_VERSION_IS_NOT_SUPPORTED: errorCodeMessage = "AEMDM_E_THIS_PATFILE_VERSION_IS_NOT_SUPPORTED";			//break;
					case ER_AEMDM_E_INVALID_HEADER: errorCodeMessage = "AEMDM_E_INVALID_HEADER";									//break;
					case ER_AEMDM_E_INVALID_RTD_DELAY: errorCodeMessage = "AEMDM_E_INVALID_RTD_DELAY";								//break;
					case ER_AEMDM_E_UNDEFINED_VECTOR_SETS: errorCodeMessage = "AEMDM_E_UNDEFINED_VECTOR_SETS";							//break;
					case ER_AEMDM_E_THIS_PATFILE_HAS_NO_PIN_USING_THIS_MODULE: errorCodeMessage = "AEMDM_E_THIS_PATFILE_HAS_NO_PIN_USING_THIS_MODULE";		//break;
					case ER_AEMDM_E_WARNING_PERIOD_GREATER_THAN_EDGE: errorCodeMessage = "AEMDM_E_WARNING_PERIOD_GREATER_THAN_EDGE";				//break;
					case ER_AEMDM_E_WARNING_EDGE_GREATER_THAN_PERIOD: errorCodeMessage = "AEMDM_E_WARNING_EDGE_GREATER_THAN_PERIOD";				//break;
					case ER_AEMDM_E_TMU_NOT_IN_DONE_STATE: errorCodeMessage = "AEMDM_E_TMU_NOT_IN_DONE_STATE";							//break;
					case ER_AEMDM_E_EXCEED_ALLOCATED_MEMORY: errorCodeMessage = "AEMDM_E_EXCEED_ALLOCATED_MEMORY";							//break;
					case ER_AEMDM_E_CANNOT_OPEN_FILE: errorCodeMessage = "AEMDM_E_CANNOT_OPEN_FILE";								//break;
					case ER_AEMDM_E_INVALID_ATTRIBUTE: errorCodeMessage = "AEMDM_E_INVALID_ATTRIBUTE";								//break;
					case ER_AEMDM_E_TDR_NO_UNDEFINED_REGION_DETECTED: errorCodeMessage = "AEMDM_E_TDR_NO_UNDEFINED_REGION_DETECTED";				//break;
					case ER_AEMDM_E_LOGIC_ANALYZER_BUSY: errorCodeMessage = "AEMDM_E_LOGIC_ANALYZER_BUSY";								//break;
					case ER_AEMDM_E_EXCEED_READ_LOGIC_ANALYZER_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_READ_LOGIC_ANALYZER_LIMIT";				//break;
					case ER_AEMDM_E_VECTOR_FILEPATH_EXCEED_1024B: errorCodeMessage = "AEMDM_E_VECTOR_FILEPATH_EXCEED_1024B";					//break;
					case ER_AEMDM_E_PIN_NAME_IS_USED: errorCodeMessage = "AEMDM_E_PIN_NAME_IS_USED";								//break;
					case ER_AEMDM_E_INVALID_PINGROUP: errorCodeMessage = "AEMDM_E_INVALID_PINGROUP";								//break;
					case ER_AEMDM_E_EXCEED_PIN_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_PIN_LIMIT";								//break;
					case ER_AEMDM_E_EPCS_BUSY: errorCodeMessage = "AEMDM_E_EPCS_BUSY";										//break;
					case ER_AEMDM_E_INSUFFICIENT_ALLOCATED_MEMORY: errorCodeMessage = "AEMDM_E_INSUFFICIENT_ALLOCATED_MEMORY";					//break;
					case ER_AEMDM_E_VEC_ENGINE_NOT_IN_SYNC: errorCodeMessage = "AEMDM_E_VEC_ENGINE_NOT_IN_SYNC";							//break;
					case ER_AEMDM_E_EXCEED_TMU_CORE_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_TMU_CORE_LIMIT";							//break;
					case ER_AEMDM_E_INVALID_PIN_FOR_TMU: errorCodeMessage = "AEMDM_E_INVALID_PIN_FOR_TMU";								//break;
					case ER_AEMDM_E_INVALID_PIN_FOR_LOGIC_ANALYZER: errorCodeMessage = "AEMDM_E_INVALID_PIN_FOR_LOGIC_ANALYZER";					//break;
					case ER_AEMDM_E_LOGIC_ANALYZER_NOT_IN_SYNC: errorCodeMessage = "AEMDM_E_LOGIC_ANALYZER_NOT_IN_SYNC";						//break;
					case ER_AEMDM_E_MC_DC_COMM_TIMEOUT: errorCodeMessage = "AEMDM_E_MC_DC_COMM_TIMEOUT";								//break;
					case ER_AEMDM_E_SRAM_TIMEOUT: errorCodeMessage = "AEMDM_E_SRAM_TIMEOUT";									//break;
					case ER_AEMDM_E_MC_TIMEOUT: errorCodeMessage = "AEMDM_E_MC_TIMEOUT";										//break;
					case ER_AEMDM_E_DM581X_UNSUPPORTED_DC_CONFIGURATION: errorCodeMessage = "AEMDM_E_DM581X_UNSUPPORTED_DC_CONFIGURATION";				//break;
					case ER_AEMDM_E_SRAM_CAL_FAIL: errorCodeMessage = "AEMDM_E_SRAM_CAL_FAIL";									//break;
					case ER_AEMDM_E_EXCEED_DIO_PORT_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_DIO_PORT_LIMIT";							//break;
					case ER_AEMDM_E_ADC_BUSY: errorCodeMessage = "AEMDM_E_ADC_BUSY";										//break;
					case ER_AEMDM_E_ADC_ERROR: errorCodeMessage = "AEMDM_E_ADC_ERROR";										//break;
					case ER_AEMDM_E_EXCEED_TOTAL_SCAN_CHAIN: errorCodeMessage = "AEMDM_E_EXCEED_TOTAL_SCAN_CHAIN";							//break;
					case ER_AEMDM_E_EXCEED_TOTAL_SCAN_CHAIN_PER_DC: errorCodeMessage = "AEMDM_E_EXCEED_TOTAL_SCAN_CHAIN_PER_DC";					//break;
					case ER_AEMDM_E_EXCEED_TOTAL_SCAN_CHAIN_PER_BLOCK: errorCodeMessage = "AEMDM_E_EXCEED_TOTAL_SCAN_CHAIN_PER_BLOCK";				//break;
					case ER_AEMDM_E_NO_IMAGE_CAPTURED: errorCodeMessage = "AEMDM_E_NO_IMAGE_CAPTURED";								//break;
					case ER_AEMDM_E_EXCEED_IMAGE_PROC_DIMENSION: errorCodeMessage = "AEMDM_E_EXCEED_IMAGE_PROC_DIMENSION";						//break;
					case ER_AEMDM_E_EXCEED_IMAGE_CORE_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_IMAGE_CORE_LIMIT";							//break;
					case ER_AEMDM_E_EXCEED_LABEL_LIMIT: errorCodeMessage = "AEMDM_E_EXCEED_LABEL_LIMIT";								//break;
					case ER_AEMDM_E_EXCEED_FRAME_MAX: errorCodeMessage = "AEMDM_E_EXCEED_FRAME_MAX";								//break;
					case ER_AEMDM_E_INVALID_I2C_COMMAND: errorCodeMessage = "AEMDM_E_INVALID_I2C_COMMAND";								//break;
					case ER_AEMDM_E_LOGIC_ANALYZER_WRONG_MODE: errorCodeMessage = "AEMDM_E_LOGIC_ANALYZER_WRONG_MODE";						//break;
					case ER_AEMDM_E_IMAGE_PROC_BUSY: errorCodeMessage = "AEMDM_E_IMAGE_PROC_BUSY";									//break;
					case ER_AEMDM_E_INVALID_LOGIC_ANALYZER_CH: errorCodeMessage = "AEMDM_E_INVALID_LOGIC_ANALYZER_CH";						//break;
					case ER_AEMDM_E_CAL_DATA_MISMATCH: errorCodeMessage = "AEMDM_E_CAL_DATA_MISMATCH";								//break;
					case ER_AEMDM_E_MEMORY_SELFTEST_TIMEOUT: errorCodeMessage = "AEMDM_E_MEMORY_SELFTEST_TIMEOUT";							//break;
					case ER_AEMDM_E_INVALID_CAPTURE_PIN: errorCodeMessage = "AEMDM_E_INVALID_CAPTURE_PIN";								//break;
					case ER_AEMDM_E_INVALID_SOURCE_PIN: errorCodeMessage = "AEMDM_E_INVALID_SOURCE_PIN";								//break;
					case ER_AEMDM_E_TRIGGER_CAL_FAIL: errorCodeMessage = "AEMDM_E_TRIGGER_CAL_FAIL";								//break;
					case ER_AEMDM_E_FINE_DELAY_CAL_ERROR: errorCodeMessage = "AEMDM_E_FINE_DELAY_CAL_ERROR";							//break;
					case ER_AEMDM_E_API_NOT_SUPPORTED_FOR_THIS_MODEL: errorCodeMessage = "AEMDM_E_API_NOT_SUPPORTED_FOR_THIS_MODEL";				//break;
					case ER_AEMDM_E_INVALID_MULTIPLEX_PIN: errorCodeMessage = "AEMDM_E_INVALID_MULTIPLEX_PIN";							//break;
					case ER_AEMDM_E_TRIGGER_PLL_TIMEOUT: errorCodeMessage = "AEMDM_E_TRIGGER_PLL_TIMEOUT";								//break;
					case ER_AEMDM_E_INVALID_PIN: errorCodeMessage = "AEMDM_E_INVALID_PIN";										//break;
					case ER_AEMDM_E_WARNING_TDR_THRESHOLD_OUT_OF_RANGE: errorCodeMessage = "AEMDM_E_WARNING_TDR_THRESHOLD_OUT_OF_RANGE";				//break;
					case ER_AEMDM_E_INVALID_OPCODE: errorCodeMessage = "AEMDM_E_INVALID_OPCODE";									//break;
					case ER_AEMDM_E_INVALID_OPERAND: errorCodeMessage = "AEMDM_E_INVALID_OPERAND";									//break;
					}
					//ret = glob->dm[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcDM[siteIndex], errorCode, ReturnErrorMessage);
					//ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = "[AEM Facility Code 11: AemDM] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
#endif 
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 12 [AemTmu]
				**	----------------------------------------------------------------------------------------------------
				*/
#if TMU_ENABLE 
				else if (errorCode.ToString("X")->StartsWith("AE0C"))
				{
					switch (errorCode)
					{
					case ER_AEMTMU_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMTMU_E_ERASE_EPCS_FAIL";								//break;
					case ER_AEMTMU_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMTMU_E_WRITE_EPCS_FAIL";								//break;
					case ER_AEMTMU_E_READ_EPCS_FAIL: errorCodeMessage = "AEMTMU_E_READ_EPCS_FAIL";									//break;
					case ER_AEMTMU_E_TMU_NOT_FOUND: errorCodeMessage = "AEMTMU_E_TMU_NOT_FOUND";									//break;
					case ER_AEMTMU_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMTMU_E_FIRMWARE_FILE_NOT_FOUND";						//break;
					case ER_AEMTMU_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMTMU_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMTMU_E_COMM_TIMED_OUT: errorCodeMessage = "AEMTMU_E_COMM_TIMED_OUT";									//break;
					case ER_AEMTMU_E_ADC_TIMED_OUT: errorCodeMessage = "AEMTMU_E_ADC_TIMED_OUT";									//break;
					case ER_AEMTMU_E_RETRIEVE_RESULTS_TIMED_OUT: errorCodeMessage = "AEMTMU_E_RETRIEVE_RESULTS_TIMED_OUT";						//break;
					case ER_AEMTMU_E_INVALID_RESULTS: errorCodeMessage = "AEMTMU_E_INVALID_RESULTS";								//break;
					case ER_AEMTMU_E_INVALID_TIMEOUT: errorCodeMessage = "AEMTMU_E_INVALID_TIMEOUT";								//break;
					case ER_AEMTMU_E_WRONG_CALTYPE: errorCodeMessage = "AEMTMU_E_WRONG_CALTYPE";									//break;
					case ER_AEMTMU_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMTMU_E_CAL_HEADER_NOT_FOUND";							//break;
					case ER_AEMTMU_E_CAL_SIZE_NOT_MATCH: errorCodeMessage = "AEMTMU_E_CAL_SIZE_NOT_MATCH";								//break;
					case ER_AEMTMU_E_CAL_FILE_NOT_FOUND: errorCodeMessage = "AEMTMU_E_CAL_FILE_NOT_FOUND";								//break;
					case ER_AEMTMU_E_INVALID_CAL_FILE: errorCodeMessage = "AEMTMU_E_INVALID_CAL_FILE";								//break;
					case ER_AEMTMU_E_INVALID_CAL_ACCUM_COUNT: errorCodeMessage = "AEMTMU_E_INVALID_CAL_ACCUM_COUNT";						//break;
					case ER_AEMTMU_E_INVALID_CAL_DATE: errorCodeMessage = "AEMTMU_E_INVALID_CAL_DATE";								//break;
					case ER_AEMTMU_E_INVALID_CAL_TIME: errorCodeMessage = "AEMTMU_E_INVALID_CAL_TIME";								//break;
					case ER_AEMTMU_E_INVALID_CAL_TEMPERATURE: errorCodeMessage = "AEMTMU_E_INVALID_CAL_TEMPERATURE";						//break;
					case ER_AEMTMU_E_INVALID_CAL_INTERVAL_MONTHS: errorCodeMessage = "AEMTMU_E_INVALID_CAL_INTERVAL_MONTHS";					//break;
					case ER_AEMTMU_E_CAL_DATA_OUT_OF_RANGE: errorCodeMessage = "AEMTMU_E_CAL_DATA_OUT_OF_RANGE";							//break;
					case ER_AEMTMU_E_INVALID_ATTRIBUTE: errorCodeMessage = "AEMTMU_E_INVALID_ATTRIBUTE";								//break;
					case ER_AEMTMU_E_INVALID_ARGUMENTS: errorCodeMessage = "AEMTMU_E_INVALID_ARGUMENTS";								//break;
					}
					//ret = tmu[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcTMU[siteIndex], errorCode, ReturnErrorMessage);
					//ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = "[AEM Facility Code 12: AemTmu] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x";
				}
#endif 
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 13 [AemSwitch]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE0D"))
				{
					switch (errorCode)
					{
					case ER_AEMSWM_E_SWM_NOT_FOUND: errorCodeMessage = "AEMSWM_E_SWM_NOT_FOUND";									//break;
					case ER_AEMSWM_E_ERASE_FLASH_FAIL: errorCodeMessage = "AEMSWM_E_ERASE_FLASH_FAIL";								//break;
					case ER_AEMSWM_E_WRITE_FLASH_FAIL: errorCodeMessage = "AEMSWM_E_WRITE_FLASH_FAIL";								//break;
					case ER_AEMSWM_E_READ_FLASH_FAIL: errorCodeMessage = "AEMSWM_E_READ_FLASH_FAIL";								//break;
					case ER_AEMSWM_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMSWM_E_FIRMWARE_FILE_NOT_FOUND";						//break;
					case ER_AEMSWM_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMSWM_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMSWM_E_COMM_TIMED_OUT: errorCodeMessage = "AEMSWM_E_COMM_TIMED_OUT";									//break;
					case ER_AEMSWM_E_INVALID_HEADER: errorCodeMessage = "AEMSWM_E_INVALID_HEADER";									//break;
					case ER_AEMSWM_E_INVALID_CH_SEL: errorCodeMessage = "AEMSWM_E_INVALID_CH_SEL";									//break;
					case ER_AEMSWM_E_INVALID_SWITCH_VALUE: errorCodeMessage = "AEMSWM_E_INVALID_SWITCH_VALUE";							//break;
					case ER_AEMSWM_E_INVALID_MULTI_SITE_MODE: errorCodeMessage = "AEMSWM_E_INVALID_MULTI_SITE_MODE";						//break;
					}
					ErrorMessage = "[AEM Facility Code 13: AemSwitch] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 14 [AemCM]
				**	----------------------------------------------------------------------------------------------------
				*/
#if CM_ENABLE 
				else if (errorCode.ToString("X")->StartsWith("AE0E"))
				{
					switch (errorCode)
					{
					case ER_AEMCM_E_CM_NOT_FOUND: errorCodeMessage = "AEMCM_E_CM_NOT_FOUND";									//break;
					case ER_AEMCM_E_ERASE_SFLASH_FAIL: errorCodeMessage = "AEMCM_E_ERASE_SFLASH_FAIL";								//break;
					case ER_AEMCM_E_WRITE_SFLASH_FAIL: errorCodeMessage = "AEMCM_E_WRITE_SFLASH_FAIL";								//break;
					case ER_AEMCM_E_READ_SFLASH_FAIL: errorCodeMessage = "AEMCM_E_READ_SFLASH_FAIL";								//break;
					case ER_AEMCM_E_TIMED_OUT: errorCodeMessage = "AEMCM_E_TIMED_OUT";										//break;
					case ER_AEMCM_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMCM_E_FIRMWARE_FILE_NOT_FOUND";							//break;
					case ER_AEMCM_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMCM_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMCM_E_INVALID_NAME: errorCodeMessage = "AEMCM_E_INVALID_NAME";									//break;
					case ER_AEMCM_E_INVALID_OPTION: errorCodeMessage = "AEMCM_E_INVALID_OPTION";									//break;
					case ER_AEMCM_E_EXCEED_LIMIT: errorCodeMessage = "AEMCM_E_EXCEED_LIMIT";									//break;
					case ER_AEMCM_E_DIRECTORY_NAME_TOO_LONG: errorCodeMessage = "AEMCM_E_DIRECTORY_NAME_TOO_LONG";							//break;
					case ER_AEMCM_E_INVALID_SPI_CHSEL: errorCodeMessage = "AEMCM_E_INVALID_SPI_CHSEL";								//break;
					case ER_AEMCM_E_INVALID_ATTRIBUTE: errorCodeMessage = "AEMCM_E_INVALID_ATTRIBUTE";								//break;
					case ER_AEMCM_E_INVALID_SPI_CORE: errorCodeMessage = "AEMCM_E_INVALID_SPI_CORE";								//break;
					case ER_AEMCM_E_INVALID_TRIGGER_IN: errorCodeMessage = "AEMCM_E_INVALID_TRIGGER_IN";								//break;
					case ER_AEMCM_E_INVALID_TRIGGER_OUT: errorCodeMessage = "AEMCM_E_INVALID_TRIGGER_OUT";								//break;
					case ER_AEMCM_E_SYS_ID_NOT_FOUND: errorCodeMessage = "AEMCM_E_SYS_ID_NOT_FOUND";								//break;
					case ER_AEMCM_E_BAD_ARGUMENTS: errorCodeMessage = "AEMCM_E_BAD_ARGUMENTS";									//break;
					}
					//ret = glob->cm[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcCM[siteIndex], errorCode, ReturnErrorMessage);
					//ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = "[AEM Facility Code 14: AemCM] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
#endif 
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 15 [AemAWG]
				**	----------------------------------------------------------------------------------------------------
				*/
#if ACM_ENABLE
				else if (errorCode.ToString("X")->StartsWith("AE0F"))
				{
					switch (errorCode)
					{
					case ER_AEMAWG_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMAWG_E_CAL_HEADER_NOT_FOUND";							//break;
					case ER_AEMAWG_E_CAL_SIZE_NOT_MATCH: errorCodeMessage = "AEMAWG_E_CAL_SIZE_NOT_MATCH";								//break;
					case ER_AEMAWG_E_INVALID_CAL_ACCUM_COUNT: errorCodeMessage = "AEMAWG_E_INVALID_CAL_ACCUM_COUNT";						//break;
					case ER_AEMAWG_E_INVALID_CAL_DATE: errorCodeMessage = "AEMAWG_E_INVALID_CAL_DATE";								//break;
					case ER_AEMAWG_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMAWG_E_FIRMWARE_FILE_NOT_FOUND";						//break;
					case ER_AEMAWG_E_DDS_TIMEOUT: errorCodeMessage = "AEMAWG_E_DDS_TIMEOUT";									//break;
					case ER_AEMAWG_E_WAVEFORM_MEMORY_TIMEOUT: errorCodeMessage = "AEMAWG_E_WAVEFORM_MEMORY_TIMEOUT";						//break;
					case ER_AEMAWG_E_AWG_NOT_FOUND: errorCodeMessage = "AEMAWG_E_AWG_NOT_FOUND";									//break;
					case ER_AEMAWG_E_INVALID_CHANNEL_COUNT: errorCodeMessage = "AEMAWG_E_INVALID_CHANNEL_COUNT";							//break;
					case ER_AEMAWG_E_INVALID_CHANNEL_NAME: errorCodeMessage = "AEMAWG_E_INVALID_CHANNEL_NAME";							//break;
					case ER_AEMAWG_E_INVALID_SAMPLING_TIME: errorCodeMessage = "AEMAWG_E_INVALID_SAMPLING_TIME";							//break;
					case ER_AEMAWG_E_ADC_TIMEOUT: errorCodeMessage = "AEMAWG_E_ADC_TIMEOUT";									//break;
					case ER_AEMAWG_E_INVALID_OPERATION_MODE: errorCodeMessage = "AEMAWG_E_INVALID_OPERATION_MODE";							//break;
					case ER_AEMAWG_E_EXCEED_FREQUENCY_SPEC: errorCodeMessage = "AEMAWG_E_EXCEED_FREQUENCY_SPEC";							//break;
					case ER_AEMAWG_E_EXCEED_VOLTAGE_SPEC: errorCodeMessage = "AEMAWG_E_EXCEED_VOLTAGE_SPEC";							//break;
					case ER_AEMAWG_E_EXCEED_STARTPHASE_SPEC: errorCodeMessage = "AEMAWG_E_EXCEED_STARTPHASE_SPEC";							//break;
					case ER_AEMAWG_E_EXCEED_DUTYCYCLE_SPEC: errorCodeMessage = "AEMAWG_E_EXCEED_DUTYCYCLE_SPEC";							//break;
					case ER_AEMAWG_E_WRONG_MODULE_GAIN: errorCodeMessage = "AEMAWG_E_WRONG_MODULE_GAIN";								//break;
					case ER_AEMAWG_E_FUNCTION_GENERATOR_BUSY: errorCodeMessage = "AEMAWG_E_FUNCTION_GENERATOR_BUSY";						//break;
					case ER_AEMAWG_E_EXCEED_TOTAL_WAVEFORM_MEMORY_LIMIT: errorCodeMessage = "AEMAWG_E_EXCEED_TOTAL_WAVEFORM_MEMORY_LIMIT";				//break;
					case ER_AEMAWG_E_UNALLOCATED_RESOURCE: errorCodeMessage = "AEMAWG_E_UNALLOCATED_RESOURCE";							//break;
					case ER_AEMAWG_E_EXCEED_MEMORY_LIMIT_OF_RESOURCE: errorCodeMessage = "AEMAWG_E_EXCEED_MEMORY_LIMIT_OF_RESOURCE";				//break;
					case ER_AEMAWG_E_FILE_NOT_FOUND: errorCodeMessage = "AEMAWG_E_FILE_NOT_FOUND";									//break;
					case ER_AEMAWG_E_FILE_CORRUPTED: errorCodeMessage = "AEMAWG_E_FILE_CORRUPTED";									//break;
					case ER_AEMAWG_E_EXCEED_LEVEL_LIMIT: errorCodeMessage = "AEMAWG_E_EXCEED_LEVEL_LIMIT";								//break;
					case ER_AEMAWG_E_INVALID_CHANNEL: errorCodeMessage = "AEMAWG_E_INVALID_CHANNEL";								//break;
					case ER_AEMAWG_E_MARKER_OVERLAP: errorCodeMessage = "AEMAWG_E_MARKER_OVERLAP";									//break;
					case ER_AEMAWG_E_CHANNEL_IS_ARMED: errorCodeMessage = "AEMAWG_E_CHANNEL_IS_ARMED";								//break;
					case ER_AEMAWG_E_FILTER_SET_UNINITIALIZED: errorCodeMessage = "AEMAWG_E_FILTER_SET_UNINITIALIZED";						//break;
					case ER_AEMAWG_E_INVALID_INTERPOLATOR_SETTING: errorCodeMessage = "AEMAWG_E_INVALID_INTERPOLATOR_SETTING";					//break;
					case ER_AEMAWG_E_INVALID_FILTER_SETTING: errorCodeMessage = "AEMAWG_E_INVALID_FILTER_SETTING";							//break;
					case ER_AEMAWG_E_EXCEED_TRANSITION_SPEC: errorCodeMessage = "AEMAWG_E_EXCEED_TRANSITION_SPEC";							//break;
					case ER_AEMAWG_E_AWG_BUSY: errorCodeMessage = "AEMAWG_E_AWG_BUSY";										//break;
					case ER_AEMAWG_E_INVALID_CALIBRATION_ARGUMENTS: errorCodeMessage = "AEMAWG_E_INVALID_CALIBRATION_ARGUMENTS";					//break;
					case ER_AEMAWG_E_TIMED_OUT: errorCodeMessage = "AEMAWG_E_TIMED_OUT";										//break;
					case ER_AEMAWG_E_READ_FLASH_FAIL: errorCodeMessage = "AEMAWG_E_READ_FLASH_FAIL";								//break;
					case ER_AEMAWG_E_INVALID_CAL_TEMPERATURE: errorCodeMessage = "AEMAWG_E_INVALID_CAL_TEMPERATURE";						//break;
					case ER_AEMAWG_E_INVALID_CAL_INTERVAL_MONTHS: errorCodeMessage = "AEMAWG_E_INVALID_CAL_INTERVAL_MONTHS";					//break;
					case ER_AEMAWG_E_CAL_DATA_OUT_OF_RANGE: errorCodeMessage = "AEMAWG_E_CAL_DATA_OUT_OF_RANGE";							//break;
					case ER_AEMAWG_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMAWG_E_WRITE_EPCS_FAIL";								//break;
					case ER_AEMAWG_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMAWG_E_ERASE_EPCS_FAIL";								//break;
					case ER_AEMAWG_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMAWG_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMAWG_E_WRONG_CALTYPE: errorCodeMessage = "AEMAWG_E_WRONG_CALTYPE";									//break;
					case ER_AEMAWG_E_INVALID_HEADER: errorCodeMessage = "AEMAWG_E_INVALID_HEADER";									//break;
					case ER_AEMAWG_E_NULL_ERROR: errorCodeMessage = "AEMAWG_E_NULL_ERROR";										//break;
					case ER_AEMAWG_E_CALIBRATED_GAIN_OUT_OF_RANGE: errorCodeMessage = "AEMAWG_E_CALIBRATED_GAIN_OUT_OF_RANGE";					//break;
					case ER_AEMAWG_E_CALIBRATION_DATA_SIZE_MISMATCH: errorCodeMessage = "AEMAWG_E_CALIBRATION_DATA_SIZE_MISMATCH";					//break;
					case ER_AEMAWG_E_INVALID_OPTION: errorCodeMessage = "AEMAWG_E_INVALID_OPTION";									//break;
					case ER_AEMAWG_E_FILTER_SET_IS_IIR: errorCodeMessage = "AEMAWG_E_FILTER_SET_IS_IIR";								//break;
					case ER_AEMAWG_E_FILTER_SET_IS_FIR: errorCodeMessage = "AEMAWG_E_FILTER_SET_IS_FIR";								//break;
					case ER_AEMAWG_E_API_NOT_SUPPORTED_FOR_THIS_MODEL: errorCodeMessage = "AEMAWG_E_API_NOT_SUPPORTED_FOR_THIS_MODEL";				//break;
					case ER_AEMAWG_E_EXCEED_IMPEDANCE_LIMIT: errorCodeMessage = "AEMAWG_E_EXCEED_IMPEDANCE_LIMIT";							//break;
					case ER_AEMAWG_E_EXCEED_CURRENT_LIMIT: errorCodeMessage = "AEMAWG_E_EXCEED_CURRENT_LIMIT";							//break;
					}
					//ret = glob->acm[siteIndex]->GetErrorMessage(glob->RsrcManager.RsrcACM[siteIndex], errorCode, ReturnErrorMessage);
					//ErrorMessage = ReturnErrorMessage->ToString();
					ErrorMessage = "[AEM Facility Code 15: AemAWG] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
#endif 
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 16 [Reserved for wrapper use]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE10"))
				{
					switch (errorCode)
					{
						// AMB7600
					case ER_OPERATION_HALTED_BY_USER: errorCodeMessage = "OPERATION_HALTED_BY_USER";								//break;
					case ER_PREREQUISITE_NOT_MET: errorCodeMessage = "PREREQUISITE_NOT_MET";									//break;
					case ER_ILLEGAL_OPERATION: errorCodeMessage = "ILLEGAL_OPERATION";										//break;
					case ER_NO_CALIBRATION_RECORD: errorCodeMessage = "NO_CALIBRATION_RECORD";									//break;
					case ER_CALIBRATION_DUE: errorCodeMessage = "CALIBRATION_DUE";											//break;
					case ER_INVALID_USER_INPUT: errorCodeMessage = "INVALID_USER_INPUT";										//break;
					case ER_INVALID_QUERY: errorCodeMessage = "INVALID_QUERY";											//break;
					case ER_STATION_ID_OCCUPIED: errorCodeMessage = "STATION_ID_OCCUPIED";										//break;
					case ER_MODULATION_OVERLOADED: errorCodeMessage = "MODULATION_OVERLOADED";									//break;
					case ER_MODULATION_NOT_LOADED: errorCodeMessage = "MODULATION_NOT_LOADED";									//break;
					case ER_MODULATION_ALREADY_LOADED: errorCodeMessage = "MODULATION_ALREADY_LOADED";								//break;
					case ER_RESOURCE_ALREADY_GRANTED: errorCodeMessage = "RESOURCE_ALREADY_GRANTED";								//break;
					case ER_CORRELATION_ERROR: errorCodeMessage = "CORRELATION_ERROR";										//break;
					case ER_INVALID_SETTING: errorCodeMessage = "INVALID_SETTING";											//break;
					case ER_CALIBRATION_OUT_OF_SPECS: errorCodeMessage = "CALIBRATION_OUT_OF_SPECS";								//break;
					case ER_UNSUPPORTED_OFFLINE: errorCodeMessage = "UNSUPPORTED_OFFLINE";										//break;
					case ER_ENFORCED_OFFLINE: errorCodeMessage = "ENFORCED_OFFLINE";										//break;
					case ER_SOFTWARE_TIMEOUT: errorCodeMessage = "SOFTWARE_TIMEOUT";										//break;
					case ER_HADWARE_TIMEOUT: errorCodeMessage = "HADWARE_TIMEOUT";											//break;
					case ER_EXCEED_MAX_SAMPLE_SZIE: errorCodeMessage = "EXCEED_MAX_SAMPLE_SZIE";									//break;
					case ER_MISSING_CALIBRATION_FILE: errorCodeMessage = "MISSING_CALIBRATION_FILE";								//break;
					case ER_NO_TESTHEAD: errorCodeMessage = "NO_TESTHEAD";												//break;
					case ER_NO_TESTSITE: errorCodeMessage = "NO_TESTSITE";												//break;
					case ER_API_NOT_SUPPORTED: errorCodeMessage = "API_NOT_SUPPORTED";										//break;
					case ER_LOAD_DLL_FILE_ERROR: errorCodeMessage = "LOAD_DLL_FILE_ERROR";										//break;
					case ER_LOAD_DLL_FUNCTION_ERROR: errorCodeMessage = "LOAD_DLL_FUNCTION_ERROR";									//break;
					case ER_MEMORY_ALLOCATION_ERROR: errorCodeMessage = "MEMORY_ALLOCATION_ERROR";									//break;
					case ER_FILE_IO_ERROR: errorCodeMessage = "FILE_IO_ERROR";											//break;
					case ER_MISSING_GLOBAL_COND: errorCodeMessage = "MISSING_GLOBAL_COND";										//break;
					case ER_MISSING_FLOWITEM_COND: errorCodeMessage = "MISSING_FLOWITEM_COND";									//break;
					case ER_MISSING_TESTPARAM_COND: errorCodeMessage = "MISSING_TESTPARAM_COND";									//break;
					case ER_INVALID_COMMAND: errorCodeMessage = "INVALID_COMMAND";											//break;
					case ER_INVALID_COMMAND_ARGUMENTS: errorCodeMessage = "INVALID_COMMAND_ARGUMENTS";								//break;
					case ER_REGISTER_INSTRUMENT_ERROR: errorCodeMessage = "REGISTER_INSTRUMENT_ERROR";								//break;
					case ER_INIT_INSTRUMENT_ERROR_OR_INCORRECT_RESOURCE_CONFIG: errorCodeMessage = "INIT_INSTRUMENT_ERROR_OR_INCORRECT_RESOURCE_CONFIG";		//break;
					case ER_INSTRUMENT_READ_ERROR: errorCodeMessage = "INSTRUMENT_READ_ERROR";									//break;
					case ER_INSTRUMENT_WRITE_ERROR: errorCodeMessage = "INSTRUMENT_WRITE_ERROR";									//break;
					case ER_INCOMPATIBLE_HARDWARE: errorCodeMessage = "INCOMPATIBLE_HARDWARE";									//break;
					case ER_UNINIT_INSTRUMENT_ERROR: errorCodeMessage = "UNINIT_INSTRUMENT_ERROR";									//break;
					case ER_VOLTAGE_OUT_OF_RANGE: errorCodeMessage = "VOLTAGE_OUT_OF_RANGE";									//break;
					case ER_CURRENT_OUT_OF_RANGE: errorCodeMessage = "CURRENT_OUT_OF_RANGE";									//break;
					case ER_INVALID_RESOURCE_PIN: errorCodeMessage = "INVALID_RESOURCE_PIN";									//break;
																																// AMB7300 
					case ER_PORTPAIR_ALIAS_NOT_MATCHED: errorCodeMessage = "PORTPAIR_ALIAS_NOT_MATCHED (Port-Pair Combination Does Not Exist in AMB7300AxMapping.xml File)";						//break;
					case ER_MISSING_INSTR_CONFIG_FILE: errorCodeMessage = "MISSING_INSTR_CONFIG_FILE";																							//break;
					case ER_X86_NOT_COMPATIBLE: errorCodeMessage = "X86_NOT_COMPATIBLE";																									//break;
					case ER_MISSING_STATE_FILE: errorCodeMessage = "MISSING_STATE_FILE (State File (*.sta) does not exit in C:\\ProgramData\\Aemulus\\AMB7300\\State)";					//break;
					case ER_MISSING_MAPPING_FILE: errorCodeMessage = "MISSING_MAPPING_FILE";																								//break;
					case ER_CONST_DUPLICATED_MEAS_TYPE: errorCodeMessage = "CONST_DUPLICATED_MEAS_TYPE (Duplicated measurement type been set with amb7300tl->vnaSetting[siteIndex].measType)";	//break;
																																																//case ER_CONST_INCORRECT_RESOURCE_CONFIG					: errorCodeMessage = "ER_CONST_INCORRECT_RESOURCE_CONFIG (Platform resource module and system configuration module not match! Please check AMB7300Configuration.xml in the directory of C:\\ProgramData\\Aemulus\\AMB7300\\Config)";	break;
					}
					ErrorMessage = "[AEM Facility Code 16: Reserved for wrapper use] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}

				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 17 [AemDBG_1]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE11"))
				{
					switch (errorCode)
					{
					case ER_AEMDBG_E_DBG_NOT_FOUND: errorCodeMessage = "AEMDBG_E_DBG_NOT_FOUND";									//break;
					case ER_AEMDBG_E_INVALID_RESOURCE_OUT1: errorCodeMessage = "AEMDBG_E_INVALID_RESOURCE_OUT1";							//break;
					case ER_AEMDBG_E_INVALID_RESOURCE_OUT2: errorCodeMessage = "AEMDBG_E_INVALID_RESOURCE_OUT2";							//break;
					case ER_AEMDBG_E_INVALID_PC_OUT1: errorCodeMessage = "AEMDBG_E_INVALID_PC_OUT1";								//break;
					case ER_AEMDBG_E_INVALID_COL_OUT1: errorCodeMessage = "AEMDBG_E_INVALID_COL_OUT1";								//break;
					case ER_AEMDBG_E_INVALID_PAD_OUT1: errorCodeMessage = "AEMDBG_E_INVALID_PAD_OUT1";								//break;
					case ER_AEMDBG_E_INVALID_PC_OUT2: errorCodeMessage = "AEMDBG_E_INVALID_PC_OUT2";								//break;
					case ER_AEMDBG_E_INVALID_COL_OUT2: errorCodeMessage = "AEMDBG_E_INVALID_COL_OUT2";								//break;
					case ER_AEMDBG_E_INVALID_PAD_OUT2: errorCodeMessage = "AEMDBG_E_INVALID_PAD_OUT2";								//break;
					case ER_AEMDBG_E_INVALID_MUX_CONDITION: errorCodeMessage = "AEMDBG_E_INVALID_MUX_CONDITION";							//break;
					case ER_AEMDBG_E_READSUBID_FAIL: errorCodeMessage = "AEMDBG_E_READSUBID_FAIL";									//break;
					case ER_AEMDBG_E_READMODEL_FAIL: errorCodeMessage = "AEMDBG_E_READMODEL_FAIL";									//break;
					case ER_AEMDBG_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMDBG_E_WRITE_EPCS_FAIL";								//break;
					case ER_AEMDBG_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMDBG_E_ERASE_EPCS_FAIL";								//break;
					case ER_AEMDBG_E_READ_EPCS_FAIL: errorCodeMessage = "AEMDBG_E_READ_EPCS_FAIL";									//break;
					case ER_AEMDBG_E_DLL_NOT_FOUND: errorCodeMessage = "AEMDBG_E_DLL_NOT_FOUND";									//break;
					case ER_AEMDBG_E_API_NOT_FOUND: errorCodeMessage = "AEMDBG_E_API_NOT_FOUND";									//break;
					case ER_AEMDBG_E_OPEN_FAIL: errorCodeMessage = "AEMDBG_E_OPEN_FAIL";										//break;
					case ER_AEMDBG_E_RESET_FAIL: errorCodeMessage = "AEMDBG_E_RESET_FAIL";										//break;
					case ER_AEMDBG_E_WRITE_FLASH_FAIL: errorCodeMessage = "AEMDBG_E_WRITE_FLASH_FAIL";								//break;
					case ER_AEMDBG_E_READ_FLASH_FAIL: errorCodeMessage = "AEMDBG_E_READ_FLASH_FAIL";								//break;
					case ER_AEMDBG_E_ERASE_FLASH_FAIL: errorCodeMessage = "AEMDBG_E_ERASE_FLASH_FAIL";								//break;
					case ER_AEMDBG_E_SIGNATURE_NOT_MATCH: errorCodeMessage = "AEMDBG_E_SIGNATURE_NOT_MATCH";							//break;
					case ER_AEMDBG_E_BAD_ARGUMENTS: errorCodeMessage = "AEMDBG_E_BAD_ARGUMENTS";									//break;
					case ER_AEMDBG_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMDBG_E_FIRMWARE_FILE_NOT_FOUND";						//break;
					case ER_AEMDBG_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMDBG_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMDBG_E_RS232_FAIL: errorCodeMessage = "AEMDBG_E_RS232_FAIL";										//break;
					}
					ErrorMessage = "[AEM Facility Code 17: AemDBG_1] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 18 [AemDBG_2]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE12"))
				{
					switch (errorCode)
					{
					case ER_AEMDBG_E_INSTRUMENT_SIGNATURE_NOT_MATCH: errorCodeMessage = "AEMDBG_E_INSTRUMENT_SIGNATURE_NOT_MATCH";					//break;
					case ER_AEMDBG_E_DIAGNOSTIC_SIGNATURE_NOT_MATCH: errorCodeMessage = "AEMDBG_E_DIAGNOSTIC_SIGNATURE_NOT_MATCH";					//break;
					case ER_AEMDBG_E_READSUBID_FAIL_2: errorCodeMessage = "ER_AEMDBG_E_READSUBID_FAIL_2";							//break;
					case ER_AEMDBG_E_INVALID_ARGUMENTS: errorCodeMessage = "AEMDBG_E_INVALID_ARGUMENTS";								//break;
					case ER_AEMDBG_E_ADC_TIMED_OUT: errorCodeMessage = "AEMDBG_E_ADC_TIMED_OUT";									//break;
					case ER_AEMDBG_E_EXCEED_VOLTAGE_SPEC: errorCodeMessage = "AEMDBG_E_EXCEED_VOLTAGE_SPEC";							//break;
					case ER_AEMDBG_E_CALIBRATED_GAIN_OUT_OF_RANGE: errorCodeMessage = "AEMDBG_E_CALIBRATED_GAIN_OUT_OF_RANGE";					//break;
					case ER_AEMDBG_E_TDC_TRIGGER_STATUS_FAILED: errorCodeMessage = "AEMDBG_E_TDC_TRIGGER_STATUS_FAILED";						//break;
					case ER_AEMDBG_E_DBG_WRONG_SITE: errorCodeMessage = "AEMDBG_E_DBG_WRONG_SITE";									//break;
					case ER_AEMDBG_E_DBG_FLASH_BUSY_TIMEOUT: errorCodeMessage = "AEMDBG_E_DBG_FLASH_BUSY_TIMEOUT";							//break;
					case ER_AEMDBG_E_DBG_SIGNATURES0_MISMATCH: errorCodeMessage = "AEMDBG_E_DBG_SIGNATURES0_MISMATCH";						//break;
					case ER_AEMDBG_E_DBG_SIGNATURES1_MISMATCH: errorCodeMessage = "AEMDBG_E_DBG_SIGNATURES1_MISMATCH";						//break;
					case ER_AEMDBG_E_DBG_SIGNATURES2_MISMATCH: errorCodeMessage = "AEMDBG_E_DBG_SIGNATURES2_MISMATCH";						//break;
					case ER_AEMDBG_E_DBG_SIGNATURES3_MISMATCH: errorCodeMessage = "AEMDBG_E_DBG_SIGNATURES3_MISMATCH";						//break;
					case ER_AEMDBG_E_INVALID_HEADER: errorCodeMessage = "AEMDBG_E_INVALID_HEADER";									//break;
					case ER_AEMDBG_E_WRONG_CALTYPE: errorCodeMessage = "AEMDBG_E_WRONG_CALTYPE";									//break;
					case ER_AEMDBG_E_INVALID_CAL_INDEX: errorCodeMessage = "AEMDBG_E_INVALID_CAL_INDEX";								//break;
					case ER_AEMDBG_E_NOT_ENOUGH_MEMORY: errorCodeMessage = "AEMDBG_E_NOT_ENOUGH_MEMORY";								//break;
					case ER_AEMDBG_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMDBG_E_CAL_HEADER_NOT_FOUND";							//break;
					case ER_AEMDBG_E_INVALID_CAL_ARRAYMODE: errorCodeMessage = "AEMDBG_E_INVALID_CAL_ARRAYMODE";							//break;
					case ER_AEMDBG_E_INVALID_SITE_NUMBER: errorCodeMessage = "AEMDBG_E_INVALID_SITE_NUMBER";							//break;
					case ER_AEMDBG_E_FILE_NOT_FOUND: errorCodeMessage = "AEMDBG_E_FILE_NOT_FOUND";									//break;
					case ER_AEMDBG_E_FILE_CORRUPTED: errorCodeMessage = "AEMDBG_E_FILE_CORRUPTED";									//break;
					case ER_AEMDBG_E_FIRMWARE_FILE_NOT_FOUND_2: errorCodeMessage = "ER_AEMDBG_E_FIRMWARE_FILE_NOT_FOUND_2";					//break;
					case ER_AEMDBG_E_FILE_CORRUPTED_2: errorCodeMessage = "ER_AEMDBG_E_FILE_CORRUPTED_2";							//break;
					case ER_AEMDBG_E_WRONG_FIRMWARE_FILE_USED_2: errorCodeMessage = "ER_AEMDBG_E_WRONG_FIRMWARE_FILE_USED_2";					//break;
					case ER_AEMDBG_E_FIRMWARE_FILE_CHECKSUM_ERROR: errorCodeMessage = "AEMDBG_E_FIRMWARE_FILE_CHECKSUM_ERROR";					//break;
					case ER_AEMDBG_E_WRONG_CAL_MODE: errorCodeMessage = "AEMDBG_E_WRONG_CAL_MODE";									//break;
					case ER_AEMDBG_E_COL_INVALID: errorCodeMessage = "AEMDBG_E_COL_INVALID";									//break;
					case ER_AEMDBG_E_INVALID_DBG_ADDR: errorCodeMessage = "AEMDBG_E_INVALID_DBG_ADDR";								//break;
					}
					ErrorMessage = "[AEM Facility Code 18: AemDBG_2] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 19 [AemRFM]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE13"))
				{
					switch (errorCode)
					{
					case ER_AEMRFM_E_RFM_NOT_FOUND: errorCodeMessage = "AEMRFM_E_RFM_NOT_FOUND";									//break;
					case ER_AEMRFM_E_ERASE_SFLASH_FAIL: errorCodeMessage = "AEMRFM_E_ERASE_SFLASH_FAIL";								//break;
					case ER_AEMRFM_E_WRITE_SFLASH_FAIL: errorCodeMessage = "AEMRFM_E_WRITE_SFLASH_FAIL";								//break;
					case ER_AEMRFM_E_READ_SFLASH_FAIL: errorCodeMessage = "AEMRFM_E_READ_SFLASH_FAIL";								//break;
					case ER_AEMRFM_E_TIMED_OUT: errorCodeMessage = "AEMRFM_E_TIMED_OUT";										//break;
					case ER_AEMRFM_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMRFM_E_FIRMWARE_FILE_NOT_FOUND";						//break;
					case ER_AEMRFM_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMRFM_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMRFM_E_INVALID_NAME: errorCodeMessage = "AEMRFM_E_INVALID_NAME";									//break;
					case ER_AEMRFM_E_INVALID_PORT: errorCodeMessage = "AEMRFM_E_INVALID_PORT";									//break;
					case ER_AEMRFM_E_INVALID_PIN: errorCodeMessage = "AEMRFM_E_INVALID_PIN";									//break;
					case ER_AEMRFM_E_INVALID_CHANNEL: errorCodeMessage = "AEMRFM_E_INVALID_CHANNEL";								//break;
					case ER_AEMRFM_E_ADC_TIMEOUT: errorCodeMessage = "AEMRFM_E_ADC_TIMEOUT";									//break;
					case ER_AEMRFM_E_FILE_NOT_FOUND: errorCodeMessage = "AEMRFM_E_FILE_NOT_FOUND";									//break;
					case ER_AEMRFM_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMRFM_E_CAL_HEADER_NOT_FOUND";							//break;
					case ER_AEMRFM_E_BAD_ARGUMENTS: errorCodeMessage = "AEMRFM_E_BAD_ARGUMENTS";									//break;
					case ER_AEMRFM_E_M_OUTRANGE: errorCodeMessage = "AEMRFM_E_M_OUTRANGE";										//break;
					case ER_AEMRFM_E_C_OUTRANGE: errorCodeMessage = "AEMRFM_E_C_OUTRANGE";										//break;
					case ER_EMRFM_E_INVALID_SPI_CHSEL: errorCodeMessage = "EMRFM_E_INVALID_SPI_CHSEL";								//break;
					case ER_AEMRFM_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMRFM_E_WRITE_EPCS_FAIL";								//break;
					case ER_AEMRFM_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMRFM_E_ERASE_EPCS_FAIL";								//break;
					case ER_AEMRFM_E_READ_EPCS_FAIL: errorCodeMessage = "AEMRFM_E_READ_EPCS_FAIL";									//break;
					case ER_AEMRFM_E_WRONG_CALTYPE: errorCodeMessage = "AEMRFM_E_WRONG_CALTYPE";									//break;
					case ER_AEMRFM_E_EXCEED_ALLOCATED_SPACE: errorCodeMessage = "AEMRFM_E_EXCEED_ALLOCATED_SPACE";							//break;
					case ER_AEMRFM_E_FILE_CORRUPTED: errorCodeMessage = "AEMRFM_E_FILE_CORRUPTED";									//break;
					case ER_AEMRFM_E_INVALID_HEADER: errorCodeMessage = "AEMRFM_E_INVALID_HEADER";									//break;
					}
					ErrorMessage = "[AEM Facility Code 19: AemRFM] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 20 [AemCAL]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE14"))
				{
					switch (errorCode)
					{
					case ER_AEMCAL_E_OPEN_FAIL: errorCodeMessage = "AEMCAL_E_OPEN_FAIL";										//break;
					case ER_AEMCAL_E_RESET_FAIL: errorCodeMessage = "AEMCAL_E_RESET_FAIL";										//break;
					case ER_AEMCAL_E_WRITE_ERROR: errorCodeMessage = "AEMCAL_E_WRITE_ERROR";									//break;
					case ER_AEMCAL_E_WRITE_LENGTH_NOT_MATCH: errorCodeMessage = "AEMCAL_E_WRITE_LENGTH_NOT_MATCH";							//break;
					case ER_AEMCAL_E_READ_ERROR: errorCodeMessage = "AEMCAL_E_READ_ERROR";										//break;
					case ER_AEMCAL_E_READ_LENGTH_NOT_MATCH: errorCodeMessage = "AEMCAL_E_READ_LENGTH_NOT_MATCH";							//break;
					case ER_AEMCAL_E_SIGNATURE_NOT_MATCH: errorCodeMessage = "AEMCAL_E_SIGNATURE_NOT_MATCH";							//break;
					case ER_AEMCAL_E_CLOSE_FAIL: errorCodeMessage = "AEMCAL_E_CLOSE_FAIL";										//break;
					case ER_AEMCAL_E_INVALID_SLOT: errorCodeMessage = "AEMCAL_E_INVALID_SLOT";									//break;
					case ER_AEMCAL_E_READ_SFLASH_FAIL: errorCodeMessage = "AEMCAL_E_READ_SFLASH_FAIL";								//break;
					case ER_AEMCAL_E_API_NOT_SUPPORTED: errorCodeMessage = "AEMCAL_E_API_NOT_SUPPORTED";								//break;
					case ER_AEMCAL_E_DLL_NOT_FOUND: errorCodeMessage = "AEMCAL_E_DLL_NOT_FOUND";									//break;
					case ER_AEMCAL_E_API_NOT_FOUND: errorCodeMessage = "AEMCAL_E_API_NOT_FOUND";									//break;
					case ER_AEMCAL_E_CARD_NOT_FOUND: errorCodeMessage = "AEMCAL_E_CARD_NOT_FOUND";									//break;
					case ER_AEMCAL_E_SUB_ID_NOT_MATCH: errorCodeMessage = "AEMCAL_E_SUB_ID_NOT_MATCH";								//break;
					case ER_AEMCAL_E_INVALID_ARGUMENTS: errorCodeMessage = "AEMCAL_E_INVALID_ARGUMENTS";								//break;
					case ER_AEMCAL_E_EXCEED_VOLTAGE_SPEC: errorCodeMessage = "AEMCAL_E_EXCEED_VOLTAGE_SPEC";							//break;
					case ER_AEMCAL_E_EXCEED_FREQUENCY_SPEC: errorCodeMessage = "AEMCAL_E_EXCEED_FREQUENCY_SPEC";							//break;
					case ER_AEMCAL_E_EXCEED_STARTPHASE_SPEC: errorCodeMessage = "AEMCAL_E_EXCEED_STARTPHASE_SPEC";							//break;
					case ER_AEMCAL_E_CALIBRATED_GAIN_OUT_OF_RANGE: errorCodeMessage = "AEMCAL_E_CALIBRATED_GAIN_OUT_OF_RANGE";					//break;
					case ER_AEMCAL_E_FUNCTION_GENERATOR_BUSY: errorCodeMessage = "AEMCAL_E_FUNCTION_GENERATOR_BUSY";						//break;
					case ER_AEMCAL_E_CAL_HEADER_NOT_FOUND: errorCodeMessage = "AEMCAL_E_CAL_HEADER_NOT_FOUND";							//break;
					case ER_AEMCAL_E_INVALID_HEADER: errorCodeMessage = "AEMCAL_E_INVALID_HEADER";									//break;
					case ER_AEMCAL_E_ERASE_EPCS_FAIL: errorCodeMessage = "AEMCAL_E_ERASE_EPCS_FAIL";								//break;
					case ER_AEMCAL_E_FIRMWARE_FILE_NOT_FOUND: errorCodeMessage = "AEMCAL_E_FIRMWARE_FILE_NOT_FOUND";						//break;
					case ER_AEMCAL_E_FILE_NOT_FOUND: errorCodeMessage = "AEMCAL_E_FILE_NOT_FOUND";									//break;
					case ER_AEMCAL_E_FILE_CORRUPTED: errorCodeMessage = "AEMCAL_E_FILE_CORRUPTED";									//break;
					case ER_AEMCAL_E_WRONG_FIRMWARE_FILE_USED: errorCodeMessage = "AEMCAL_E_WRONG_FIRMWARE_FILE_USED";						//break;
					case ER_AEMCAL_E_FIRMWARE_FILE_CHECKSUM_ERROR: errorCodeMessage = "AEMCAL_E_FIRMWARE_FILE_CHECKSUM_ERROR";					//break;
					case ER_AEMCAL_E_NOT_ENOUGH_MEMORY: errorCodeMessage = "AEMCAL_E_NOT_ENOUGH_MEMORY";								//break;
					case ER_AEMCAL_E_WRONG_CALTYPE: errorCodeMessage = "AEMCAL_E_WRONG_CALTYPE";									//break;
					case ER_AEMCAL_E_NO_VOLTAGERANGE: errorCodeMessage = "AEMCAL_E_NO_VOLTAGERANGE";								//break;
					case ER_AEMCAL_E_NO_CURRENTRANGE: errorCodeMessage = "AEMCAL_E_NO_CURRENTRANGE";								//break;
					case ER_AEMCAL_E_ADC_TIMED_OUT: errorCodeMessage = "AEMCAL_E_ADC_TIMED_OUT";									//break;
					case ER_AEMCAL_E_SPI_STATUS_TIMEOUT: errorCodeMessage = "AEMCAL_E_SPI_STATUS_TIMEOUT";								//break;
					case ER_AEMCAL_E_READ_EPCS_FAIL: errorCodeMessage = "AEMCAL_E_READ_EPCS_FAIL";									//break;
					case ER_AEMCAL_E_DELAYIC_VALUE_GREEN_MISMATCH: errorCodeMessage = "AEMCAL_E_DELAYIC_VALUE_GREEN_MISMATCH";					//break;
					case ER_AEMCAL_E_DELAYIC_VALUE_RED_MISMATCH: errorCodeMessage = "AEMCAL_E_DELAYIC_VALUE_RED_MISMATCH";						//break;
					case ER_AEMCAL_E_WRONG_SLOT: errorCodeMessage = "AEMCAL_E_WRONG_SLOT";										//break;
					case ER_AEMCAL_E_CLR_TRIGGER_STATUS_TIMEOUT: errorCodeMessage = "AEMCAL_E_CLR_TRIGGER_STATUS_TIMEOUT";						//break;
					case ER_AEMCAL_E_RETRIEVE_RESULTS_TIMED_OUT: errorCodeMessage = "AEMCAL_E_RETRIEVE_RESULTS_TIMED_OUT";						//break;
					case ER_AEMCAL_E_INVALID_RESULTS: errorCodeMessage = "AEMCAL_E_INVALID_RESULTS";								//break;
					case ER_AEMCAL_E_WRITE_EPCS_FAIL: errorCodeMessage = "AEMCAL_E_WRITE_EPCS_FAIL";								//break;
					case ER_AEMCAL_E_DUPLICATE_ENTRIES_FOUND: errorCodeMessage = "AEMCAL_E_DUPLICATE_ENTRIES_FOUND";						//break;
					case ER_AEMCAL_E_SYS_ID_NOT_FOUND: errorCodeMessage = "AEMCAL_E_SYS_ID_NOT_FOUND";								//break;
					}
					ErrorMessage = "[AEM Facility Code 20: AemCAL] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
				/*
				**	----------------------------------------------------------------------------------------------------
				**	Facility Code -> 21 [AemPXIScan]
				**	----------------------------------------------------------------------------------------------------
				*/
				else if (errorCode.ToString("X")->StartsWith("AE15"))
				{
					switch (errorCode)
					{
					case ER_AEMPXISCAN_E_GET_CLASS_DEVICE_FAILED: errorCodeMessage = "AEMPXISCAN_E_GET_CLASS_DEVICE_FAILED";					//break;
					case ER_AEMPXISCAN_E_CM_FUNCTION_FAILED: errorCodeMessage = "AEMPXISCAN_E_CM_FUNCTION_FAILED";							//break;
					case ER_AEMPXISCAN_E_INVALID_CARD_INDEX: errorCodeMessage = "AEMPXISCAN_E_INVALID_CARD_INDEX";							//break;
					case ER_AEMPXISCAN_E_INVALID_CARD_ADDRESS: errorCodeMessage = "AEMPXISCAN_E_INVALID_CARD_ADDRESS";						//break;
					case ER_AEMPXISCAN_E_NO_CARD_FOUND: errorCodeMessage = "AEMPXISCAN_E_NO_CARD_FOUND";								//break;
					}
					ErrorMessage = "[AEM Facility Code 21: AemPXIScan] " + errorCodeMessage + ". Refer to \"Error Codes Reference Guide.pdf\" for details." + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}

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
					errorCodeMessage = "Unknown error.";
					ErrorMessage = "[AEM Facility Code --: Unknown Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
				}
			}
			/*
			**	----------------------------------------------------------------------------------------------------
			**	Process Error
			**	----------------------------------------------------------------------------------------------------
			*/
			else if (errorCode == ER_CONST_TERMINATION_CHARACTER_VISA_ERROR)
			{
				// Reset return 0 to solve 0x3FFF0005 termination character VISA error
				errorCode = 0;
				goto SkipCheckError;
			}
			else if (errorCode == ER_CONST_DICTIONARY_KEY_NOT_PRESENT)
			{
				// Error Code:-16(0xFFFFFFF0) Message:Aemulus.Hardware.AlarmException: System.Collections.Generic.KeyNotFoundException: The given key was not present in the dictionary. 
				errorCodeMessage = "The given key was not present in the dictionary.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_VALUE_CANNOT_BE_NULL)
			{
				errorCodeMessage = "Value cannot be null. (System.ArgumentNullException: Value cannot be null.)";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_ERROR_CATCH)
			{
				errorCodeMessage = "Error catch.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_BAD_ARGUMENTS)
			{
				errorCodeMessage = "Bad arguments.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_NOT_ENOUGH_MEMORY)
			{
				errorCodeMessage = "Not enough memory.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_OPEN_FAILED)
			{
				errorCodeMessage = "Open failed.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_RTPLOTTER)
			{
				errorCodeMessage = "RTPlotter error.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_NOT_FOUND)
			{
				errorCodeMessage = "Error not found.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_FILE_NOT_FOUND)
			{
				errorCodeMessage = "Error file not found.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_READ_FILE_ERROR)
			{
				errorCodeMessage = "Read file error.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_SETTING)
			{
				errorCodeMessage = "Invalid setting.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_GENERAL)
			{
				errorCodeMessage = "General error.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_TIMEOUT)
			{
				errorCodeMessage = "Time out error.";
				ErrorMessage = "[Process Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_RESULT)
			{
				errorCodeMessage = "Invalid result.";
				ErrorMessage = "[Result Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_CALIBRATION_MODE)
			{
				errorCodeMessage = "Calibration Mode error.";
				ErrorMessage = "gCalibrationMode UN-SPECIFIED; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_CALIBRATION_MODE)
			{
				errorCodeMessage = "Invalid Calibration Mode.";
				ErrorMessage = "INVALID gCalibrationMode HAS BEEN SET; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED)
			{
				errorCodeMessage = "Hardware profile not specified error.";
				ErrorMessage = "ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED)
			{
				errorCodeMessage = "AppsWideVariable not specified error.";
				ErrorMessage = "ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED (" + glob->TcrLgr.GlobalErrorMessage + "); ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_RESOURCE_MANAGER)
			{
				errorCodeMessage = "Resource Manager error.";
				ErrorMessage = "ER_CONST_RESOURCE_MANAGER; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_INVALID_HARDWARE_RESOURCE)
			{
				errorCodeMessage = "Invalid hardware resource error.";
				ErrorMessage = "ER_CONST_INVALID_HARDWARE_RESOURCE; ErrorCode: 0x" + errorCode.ToString("X");
			}
			else if (errorCode == ER_CONST_RFSiteConfigInfo)
			{
				errorCodeMessage = "RFSiteConfigInfo error.";
				ErrorMessage = "Encountered error during casting informations from RFSiteConfigInfo.xml. [" + glob->TcrLgr.GlobalErrorMessage + "]; ErrorCode: 0x" + errorCode.ToString("X"); "Please check the contents inside the RFSiteConfigInfo.xml";

				//ErrorMessage = glob->TcrLgr.GlobalErrorMessage + "; ErrorCode: 0x" + errorCode.ToString("X"); "Please check the contents inside the RFSiteConfigInfo.xml";
			}
			else if (errorCode == ER_CONST_DRIVE_CURRENT) //Check the compliance setting when enter run mode 
			{
				errorCodeMessage = "RFSiteConfigInfo error.";
				ErrorMessage = "INVALID_DRIVE_VALUE (Drive value with 0V or 0A is not allowed); ErrorCode: 0x" + errorCode.ToString("X");
				glob->TcrLgr.IsWarningMessage = true;
				glob->FileLog.IsWarning = true;
				WarningMessageType = "INVALID COMPLIANCE SETTING";
			}
			else
			{
				errorCodeMessage = "Unknown error.";
				ErrorMessage = "[Unknown Error] " + errorCodeMessage + " | " + "Error Code: 0x" + errorCode.ToString("X");
			}


			if (siteIndex >= glob->tf.NumberOfSites)
			{
				siteIndex = 0; // Must fixed siteIndex to 0 here to eliminate Index was outside the bounds of the array (as siteIndex will inherit from previous test in try loop)
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "siteIndex is more than the number of sites, and is reset to zero");
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
				glob->TcrLgr.TracerLog->WriteToTracer(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, LOGGER_WARNING_TYPE + " " + glob->TimeNow + ": " + glob->TcrLgr.TracerMessage);

				//[Requirement:]Should write to LogFile in both Release and Debug modes 
				glob->TcrLgr.LogMssg = l_LogMssg;
				WriteToTcrLgr("SITE " + siteIndex.ToString(),glob->TcrLgr.LogMssg);
				WarningMessageBox(glob->TcrLgr.LogMssg, WarningMessageType);
			}

			if (glob->AWV.Debug == 1 /*&& glob->AutoGUCal.AutoGUCalToolActive == false*/)
			{
				glob->TcrLgr.TracerLog->WriteToTracer(glob->TcrLgr.TracerTabNamePhysicalSite + siteIndex, LOGGER_ERROR_TYPE + " " + glob->TimeNow + ": " + l_ErrorMessageLog);
			}

			glob->TcrLgr.LogMssg = l_LogMssg;
			WriteToFileLgr(glob->FileLog.FileNameDebugLog, glob->TcrLgr.LogMssg);

			//// Write to tracer logger
			//WriteToTcrLgr(glob->tf.TestSite, siteIndex, ERROR, ErrorMessage);
			//// Write to file logger
			//WriteToTcrLgr(glob->tf.TestSite, siteIndex, ERROR, ErrorMessage);

			throw gcnew Aemulus::Hardware::AlarmException(ErrorMessage + " at line " + ErrorLineNumber, errorCode);
		}
	SkipCheckError:

		return ret;
	}
	
	void TestFunction::WarningMessageBox(String ^ MssgContent, String ^ WarningMssgType)
	{
		/*****************************************************************************************************
		** WarningMessageBox
		**		MssgContent		- Message to display.
		**		WarningMssgType	- Caption of the message box. eg: "Apps Calibration Setup".
		**
		** Descriptions:
		**		This is a function to displays a message box with specified text.
		******************************************************************************************************/

		MessageBoxIcon messageBoxIconDisplay = MessageBoxIcon::Information;

		if (glob->messageBoxIcon == MessageBoxIconFormat::Asterisk) messageBoxIconDisplay = MessageBoxIcon::Asterisk;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Error) messageBoxIconDisplay = MessageBoxIcon::Error;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Exclamation) messageBoxIconDisplay = MessageBoxIcon::Exclamation;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Hand) messageBoxIconDisplay = MessageBoxIcon::Hand;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Information) messageBoxIconDisplay = MessageBoxIcon::Information;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::None) messageBoxIconDisplay = MessageBoxIcon::None;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Question) messageBoxIconDisplay = MessageBoxIcon::Question;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Stop) messageBoxIconDisplay = MessageBoxIcon::Stop;
		else if (glob->messageBoxIcon == MessageBoxIconFormat::Warning) messageBoxIconDisplay = MessageBoxIcon::Warning;

		MessageBox::Show(MssgContent, WarningMssgType,
			MessageBoxButtons::OK,
			messageBoxIconDisplay,
			MessageBoxDefaultButton::Button2,
			MessageBoxOptions::DefaultDesktopOnly, false);
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