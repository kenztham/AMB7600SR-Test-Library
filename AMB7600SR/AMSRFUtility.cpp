#include "AMB7600SR.h"

namespace Functions
{
	int AMB7600SRTestLibrary::InitializeAMSRFResource(Site^ site)
	{
		int ret = 0;

		RF_SystemConfiguration(site);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "Initializing AMSRF System Resources...");
		}

		Amsrf0 = gcnew AMSRF();
		Amsrf1 = gcnew AMSRF();
		amsrf = gcnew array<AMSRF^>(tl->glob->tf.NumberOfSites);
		dig = gcnew array<IM9421A_Receiver^>(tl->glob->tf.NumberOfSites);
		sigGen = gcnew array<IM9421A_Source^>(tl->glob->tf.NumberOfSites);
		rfdms = gcnew array<IRFDM ^>(tl->glob->tf.NumberOfSites);
		rfmms = gcnew array<IRFMM ^>(tl->glob->tf.NumberOfSites);
		rfpms = gcnew array<IRFPM ^>(SystemConfigurationInfoAMSRF0.moduleRFM611Count);
		SC5511 = gcnew array <SC5511A ^>(tl->glob->tf.NumberOfSites);//Jenn
		SC5505 = gcnew array <SC5505A ^>(tl->glob->tf.NumberOfSites);//Jenn
		wlan = gcnew array <Wlan ^>(tl->glob->tf.NumberOfSites);
		wlan_acax = gcnew array <Wlan ^>(tl->glob->tf.NumberOfSites);
		wlan_abgn = gcnew array <Wlan ^>(tl->glob->tf.NumberOfSites);

		//System Init
		RF_SystemInitialization(site);

		//Global Init (RF Previous State)
		AmsrfPreviousState(site);

		//EVM Async Task
		RF_CheckingTestMethodEvmAsyncExist(site);

		//SEM Async Task
		RF_CheckingTestMethodSemAsyncExist(site);

		//Write to Logger (RF Informations)
		AmsrfInfoToLoggerFile();

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "AMSRF System Initialized.");
		}

		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeAMSRFResource(Site^ site)
	{
		int ret = 0;
		String ^ AmsrfSupported = CurrentHeadSite.AMSRFSupported;

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "Uninitializing AMSRF System Resources...");
		}

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			Amsrf0->amsrf->UnLoadAllModulation(0);
			Amsrf0->UnLoad();
		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			Amsrf1->UnLoad();
		}

		RF_ExternalModuleUninitialization(site);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "AMSRF System Uninitialized.");
		}

		return ret;
	}
	int AMB7600SRTestLibrary::AmsrfPreviousState(Site^ site)
	{
		int ret = 0;
		String ^ AmsrfSupported = CurrentHeadSite.AMSRFSupported;

		tl->glob->AmsrfStateSettingsManager = gcnew Dictionary <String^, Dictionary<String^, Object^>^>();
		Dictionary<String^, Object^>^ Amsrf0Setting = gcnew Dictionary<String^, Object^>();
		Dictionary<String^, Object^>^ Amsrf1Setting = gcnew Dictionary<String^, Object^>();

		String^ SourceChannel = nullptr;
		String^ MeasureChannel = nullptr;

		double SourcePower = 999.99;
		double SourceFreq = 999.99;
		double SourceAtt = 999.99;
		double SourceFactor = 999.99;
		double SourceAlignFactor = 999.99;
		double MeasurePower = 999.99;
		double MeasureFreq = 999.99;
		double MeasureFactor = 999.99;
		double MeasureSampleRate = 999.99;
		double SourceOffset = 0.0;
		int MeasureSampleSize = 999;
		int SourceMode = 999;
		int SourceSignal = 999;
		int MeasureFilter = 999;
		int MeasureMode = 999;
		int TestSite_LoadHardwareProfile = 999;
		bool MeasurePreAmpStatus = false;
		bool ExecutedMeasureFast = false;
		bool EnableMeasureFast = false;
		bool ExecutedSourceFast = false;
		bool EnableSourceFast = false;

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			Amsrf0Setting->Add("TestSite_LoadHardwareProfile", TestSite_LoadHardwareProfile);

			//Source
			Amsrf0Setting->Add("SourceChannel", SourceChannel);
			Amsrf0Setting->Add("SourcePower", SourcePower);
			Amsrf0Setting->Add("SourceFreq", SourceFreq);
			Amsrf0Setting->Add("SourceAtt", SourceAtt);
			Amsrf0Setting->Add("SourceMode", SourceMode);//0: SourceChannel With NO Source Att, 1: SourceChannel With Source Att 2: Two Tone 
			Amsrf0Setting->Add("SourceSignal", SourceSignal);//0:CW, 1:Modulated

			//Source Fast
			Amsrf0Setting->Add("ExecutedSourceFast", ExecutedSourceFast);
			Amsrf0Setting->Add("EnableSourceFast", EnableSourceFast);
			Amsrf0Setting->Add("SourceFactor", SourceFactor);
			Amsrf0Setting->Add("SourceAlignFactor", SourceAlignFactor);
			Amsrf0Setting->Add("SourceOffset", SourceOffset);

			//Measure 
			Amsrf0Setting->Add("MeasureChannel", MeasureChannel);
			Amsrf0Setting->Add("MeasurePower", MeasurePower);
			Amsrf0Setting->Add("MeasureFreq", MeasureFreq);
			Amsrf0Setting->Add("MeasureFilter", MeasureFilter);
			Amsrf0Setting->Add("MeasureSampleRate", MeasureSampleRate);
			Amsrf0Setting->Add("MeasureSampleSize", MeasureSampleSize);
			Amsrf0Setting->Add("MeasureMode", MeasureMode);//0: CW Normal,1: CW Fast, 2: Modulated Signal 3: Two Tone 
			Amsrf0Setting->Add("MeasurePreAmpStatus", MeasurePreAmpStatus);

			//Measure Fast
			Amsrf0Setting->Add("ExecutedMeasureFast", ExecutedMeasureFast);
			Amsrf0Setting->Add("EnableMeasureFast", EnableMeasureFast);
			Amsrf0Setting->Add("MeasureFactor", MeasureFactor);

			tl->glob->AmsrfStateSettingsManager->Add("AMSRF0", Amsrf0Setting);
		}

		if (AmsrfSupported->Contains("AMSRF1"))
		{
			Amsrf1Setting->Add("TestSite_LoadHardwareProfile", TestSite_LoadHardwareProfile);

			//Source
			Amsrf1Setting->Add("SourceChannel", SourceChannel);
			Amsrf1Setting->Add("SourcePower", SourcePower);
			Amsrf1Setting->Add("SourceFreq", SourceFreq);
			Amsrf1Setting->Add("SourceAtt", SourceAtt);
			Amsrf1Setting->Add("SourceMode", SourceMode);//0: Source Normal,1: Source Fast
			Amsrf1Setting->Add("SourceSignal", SourceSignal);//0:

			//Source Fast
			Amsrf1Setting->Add("ExecutedSourceFast", ExecutedSourceFast);
			Amsrf1Setting->Add("EnableSourceFast", EnableSourceFast);
			Amsrf1Setting->Add("SourceFactor", SourceFactor);
			Amsrf1Setting->Add("SourceAlignFactor", SourceAlignFactor);
			Amsrf1Setting->Add("SourceOffset", SourceOffset);

			//Measure 
			Amsrf1Setting->Add("MeasureChannel", MeasureChannel);
			Amsrf1Setting->Add("MeasurePower", MeasurePower);
			Amsrf1Setting->Add("MeasureFreq", MeasureFreq);
			Amsrf1Setting->Add("MeasureFilter", MeasureFilter);
			Amsrf1Setting->Add("MeasureSampleRate", MeasureSampleRate);
			Amsrf1Setting->Add("MeasureSampleSize", MeasureSampleSize);
			Amsrf1Setting->Add("MeasureMode", MeasureMode);//0: CW Normal,1: CW Fast, 2: Modulated Signal 3: Two Tone 
			Amsrf1Setting->Add("MeasurePreAmpStatus", MeasurePreAmpStatus);

			//Measure Fast
			Amsrf1Setting->Add("ExecutedMeasureFast", ExecutedMeasureFast);
			Amsrf1Setting->Add("EnableMeasureFast", EnableMeasureFast);
			Amsrf1Setting->Add("MeasureFactor", MeasureFactor);

			tl->glob->AmsrfStateSettingsManager->Add("AMSR1", Amsrf1Setting);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::ResetAmsrfPreviousState(int testSite, bool reset)
	{
		int ret = 0;

		String^ SourceChannel = nullptr;
		String^ MeasureChannel = nullptr;
		double SourcePower = 999.99;
		double SourceFreq = 999.99;
		double SourceAtt = 999.99;
		double SourceFactor = 999.99;
		double SourceAlignFactor = 999.99;
		double MeasurePower = 999.99;
		double MeasureFreq = 999.99;
		double MeasureFactor = 999.99;
		double MeasureSampleRate = 999.99;
		double SourceOffset = 0.0;
		int MeasureSampleSize = 999;
		int SourceMode = 999;
		int SourceSignal = 999;
		int MeasureFilter = 999;
		int MeasureMode = 999;
		bool ExecutedSourceFast = false;
		bool EnableSourceFast = false;
		bool ExecutedMeasureFast = false;
		bool EnableMeasureFast = false;
		bool MeasurePreAmpStatus = false;

		if (reset)
		{
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] = SourceChannel;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] = SourcePower;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] = SourceFreq;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] = SourceAtt;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFactor"] = SourceFactor;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAlignFactor"] = SourceAlignFactor;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] = SourceMode;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceSignal"] = SourceSignal;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] = ExecutedSourceFast;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableSourceFast"] = EnableSourceFast;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceOffset"] = SourceOffset;

			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] = MeasureChannel;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] = MeasurePower;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] = MeasureFreq;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] = MeasureFilter;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] = MeasureMode;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFactor"] = MeasureFactor;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleRate"] = MeasureSampleRate;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleSize"] = MeasureSampleSize;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedMeasureFast"] = ExecutedMeasureFast;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableMeasureFast"] = EnableMeasureFast;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePreAmpStatus"] = MeasurePreAmpStatus;

		}


		return ret;
	}


	int AMB7600SRTestLibrary::RF_SystemConfiguration(Site ^ site)
	{
		int ret = 0;
		int l_HeadNumber = site->FlowEngine->HeadNumber;
		int l_SiteIndex = site->Index;
		String ^ AmsrfSupported = CurrentHeadSite.AMSRFSupported;

		//AMSRF0
		SystemConfigurationInfoAMSRF0.ConfigPath = "C:\\ProgramData\\Aemulus\\AMSRF\\Config\\AmsRFConfiguration.xml";
		SystemConfigurationInfoAMSRF0.SystemType = nullptr;
		SystemConfigurationInfoAMSRF0.moduleRFM611Count = 0;
		SystemConfigurationInfoAMSRF0.moduleRFM641Count = 0;
		SystemConfigurationInfoAMSRF0.moduleRFM621Count = 0;
		SystemConfigurationInfoAMSRF0.moduleRFM631Count = 0;
		SystemConfigurationInfoAMSRF0.moduleRF = nullptr;

		//AMSRF1
		SystemConfigurationInfoAMSRF1.ConfigPath = "C:\\ProgramData\\Aemulus\\AMSRF\\Config1\\AmsRFConfiguration.xml";
		SystemConfigurationInfoAMSRF1.SystemType = nullptr;
		SystemConfigurationInfoAMSRF1.moduleRFM611Count = 0;
		SystemConfigurationInfoAMSRF1.moduleRFM641Count = 0;
		SystemConfigurationInfoAMSRF1.moduleRFM621Count = 0;
		SystemConfigurationInfoAMSRF1.moduleRFM631Count = 0;
		SystemConfigurationInfoAMSRF1.moduleRF = nullptr;

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			RF_CastSystemConfigFileInfo(SystemConfigurationInfoAMSRF0.ConfigPath, SystemConfigurationInfoAMSRF0.SystemType, SystemConfigurationInfoAMSRF0.moduleRFM611Count, SystemConfigurationInfoAMSRF0.moduleRFM641Count, SystemConfigurationInfoAMSRF0.moduleRFM621Count, SystemConfigurationInfoAMSRF0.moduleRFM631Count, SystemConfigurationInfoAMSRF0.moduleRF);
		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			RF_CastSystemConfigFileInfo(SystemConfigurationInfoAMSRF1.ConfigPath, SystemConfigurationInfoAMSRF1.SystemType, SystemConfigurationInfoAMSRF1.moduleRFM611Count, SystemConfigurationInfoAMSRF1.moduleRFM641Count, SystemConfigurationInfoAMSRF1.moduleRFM621Count, SystemConfigurationInfoAMSRF1.moduleRFM631Count, SystemConfigurationInfoAMSRF1.moduleRF);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::RF_CastSystemConfigFileInfo(String ^ ConfigPath, String ^ % SystemType, int % moduleRFM611Count, int % moduleRFM641Count, int % moduleRFM621Count, int % moduleRFM631Count, array<String ^, 2>^ % moduleRF)
	{
		int ret = 0;

		moduleRFM611Count = 0;
		moduleRFM641Count = 0;
		moduleRFM621Count = 0;
		moduleRFM631Count = 0;
		int TotalRfModule = 0;
		int ModuleItemInfo = 5;
		int resourceModuleIndexRow = 0;
		int resourceModuleIndexColoumn = 0;

		XmlLib ^ xmlLib = gcnew XmlLib();
		SystemConfiguration ^ SystemConfiguration;
		List<ModuleConfiguration ^> ^  ModuleConfigurations = gcnew List<ModuleConfiguration ^>();

		xmlLib->Read(ConfigPath, SystemConfiguration);
		SystemType = SystemConfiguration->type;
		ModuleConfigurations = SystemConfiguration->ModuleConfigurations;
		TotalRfModule = ModuleConfigurations->Count;
		moduleRF = gcnew array<String^, 2>(TotalRfModule, ModuleItemInfo);

		int resourceModuleIndex = 0;
		for each (ModuleConfiguration ^ resourceModule in ModuleConfigurations)
		{
			resourceModuleIndexColoumn = 0;

			moduleRF[resourceModuleIndexRow, resourceModuleIndexColoumn] = resourceModule->Address;
			moduleRF[resourceModuleIndexRow, ++resourceModuleIndexColoumn] = resourceModule->Chassis;
			moduleRF[resourceModuleIndexRow, ++resourceModuleIndexColoumn] = resourceModule->Slot;
			moduleRF[resourceModuleIndexRow, ++resourceModuleIndexColoumn] = resourceModule->Type;
			moduleRF[resourceModuleIndexRow, ++resourceModuleIndexColoumn] = resourceModule->Name;

			resourceModuleIndexRow++;

			if (resourceModule->Name == "RFM611e")
			{
				moduleRFM611Count++;
			}
			if (resourceModule->Name == "RFM621e")
			{
				moduleRFM621Count++;
			}
			if (resourceModule->Name == "RFM631e")
			{
				moduleRFM631Count++;
			}
			if (resourceModule->Name == "RFM641e")
			{
				moduleRFM641Count++;
			}

		}

		//Checking the support of Two Tone Signal
		if (SystemType->Contains("P2") || SystemType->Contains("P1T"))
		{
			tl->glob->TwoToneMode == 1;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::RF_SystemInitialization(Site^ site)
	{
		int ret = 0;

		int l_HeadNumber = site->FlowEngine->HeadNumber;
		int l_SiteIndex = site->Index;
		String ^ AmsrfSupported = CurrentHeadSite.AMSRFSupported;
		tl->glob->TestSiteAmsrfType = gcnew Dictionary <int, String ^>();

		if (l_HeadNumber > 1)
		{
			//Error: Throw Error
		}
		if (l_SiteIndex > 1)
		{
			//Error: Throw Error
		}

#pragma region "Initialization of VXT (Load API)"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			Amsrf0->Load(tl->glob->HardwareProfile, l_HeadNumber, CurrentHeadSite.AMSRF0_Site[0], "AMSRF0", tl->glob->AWV.Offline, tl->glob->AWV.AmsrfControllerMode);
		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			Amsrf1->Load(tl->glob->HardwareProfile, l_HeadNumber, CurrentHeadSite.AMSRF1_Site[0], "AMSRF1", tl->glob->AWV.Offline, tl->glob->AWV.AmsrfControllerMode);
		}

#pragma endregion 

#pragma region "Initialization of Dig Sig"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			DIGITIZER0 = (IDigitizer^)Amsrf0->amsrf->Digitizers[0];
			SIGGEN0 = (ISignalGenerator^)Amsrf0->amsrf->SignalGenerators[0];
		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			DIGITIZER1 = (IDigitizer^)Amsrf1->amsrf->Digitizers[0];
			SIGGEN1 = (ISignalGenerator^)Amsrf1->amsrf->SignalGenerators[0];
		}

#pragma endregion 

#pragma region "Initialization of RFMM RFDM"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			if (SystemConfigurationInfoAMSRF0.moduleRFM621Count > 0)
			{
				Rfdm0 = (IRFDM ^)Amsrf0->amsrf->RFDMs[0];
			}
			if (SystemConfigurationInfoAMSRF0.moduleRFM631Count > 0)
			{
				Rfmm0 = (IRFMM ^)Amsrf0->amsrf->RFMMs[0];
			}
		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			if (SystemConfigurationInfoAMSRF1.moduleRFM621Count > 0)
			{
				Rfdm1 = (IRFDM ^)Amsrf1->amsrf->RFDMs[0];
			}
			if (SystemConfigurationInfoAMSRF1.moduleRFM631Count > 0)
			{
				Rfmm1 = (IRFMM ^)Amsrf1->amsrf->RFMMs[0];
			}
		}

#pragma endregion 

#pragma region "Initialization of RFPM"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			for (int i = 0; i < SystemConfigurationInfoAMSRF0.moduleRFM611Count; i++)
			{
				rfpms[i] = (IRFPM ^)Amsrf0->amsrf->RFPMs[i];
			}
		}

		if (AmsrfSupported->Contains("AMSRF1"))
		{
			for (int i = 0; i < SystemConfigurationInfoAMSRF1.moduleRFM611Count; i++)
			{
				rfpms[i] = (IRFPM ^)Amsrf1->amsrf->RFPMs[i];
			}
		}

#pragma endregion

#pragma region "Initialization of External Module"

		RF_ExternalModuleInitialization(site);

#pragma endregion

#pragma region "Assign the VXT Resource to the Physical TestSite"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			for (int i = 0; i < CurrentHeadSite.AMSRF0_Site->Length; i++)
			{
				amsrf[CurrentHeadSite.AMSRF0_Site[i]] = Amsrf0;
				tl->glob->TestSiteAmsrfType->Add(i, "AMSRF0");
			}

		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			for (int i = 0; i < CurrentHeadSite.AMSRF1_Site->Length; i++)
			{
				amsrf[CurrentHeadSite.AMSRF1_Site[i]] = Amsrf1;
				tl->glob->TestSiteAmsrfType->Add(i, "AMSRF1");
			}
		}

#pragma endregion 

#pragma region "Assign the Dig Sig to the Physical TestSite"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			for (int i = 0; i < CurrentHeadSite.AMSRF0_Site->Length; i++)
			{
				dig[CurrentHeadSite.AMSRF0_Site[i]] = (IM9421A_Receiver^)DIGITIZER0->CurrentDigitizer;
				sigGen[CurrentHeadSite.AMSRF0_Site[i]] = (IM9421A_Source^)SIGGEN0->CurrentSigGen;
			}

		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			for (int i = 0; i < CurrentHeadSite.AMSRF1_Site->Length; i++)
			{
				dig[CurrentHeadSite.AMSRF1_Site[i]] = (IM9421A_Receiver^)DIGITIZER1->CurrentDigitizer;
				sigGen[CurrentHeadSite.AMSRF1_Site[i]] = (IM9421A_Source^)SIGGEN1->CurrentSigGen;
			}
		}

#pragma endregion 

#pragma region "Assign the RFMM RFDM to the Physical TestSite"

		if (AmsrfSupported->Contains("AMSRF0"))
		{
			for (int i = 0; i < CurrentHeadSite.AMSRF0_Site->Length; i++)
			{
				if (SystemConfigurationInfoAMSRF0.moduleRFM621Count > 0)
				{
					rfdms[CurrentHeadSite.AMSRF0_Site[i]] = Rfdm0;
				}
				if (SystemConfigurationInfoAMSRF0.moduleRFM631Count > 0)
				{
					rfmms[CurrentHeadSite.AMSRF0_Site[i]] = Rfmm0;
				}
			}

		}
		if (AmsrfSupported->Contains("AMSRF1"))
		{
			for (int i = 0; i < CurrentHeadSite.AMSRF1_Site->Length; i++)
			{
				if (SystemConfigurationInfoAMSRF1.moduleRFM621Count > 0)
				{
					rfdms[CurrentHeadSite.AMSRF1_Site[i]] = Rfdm1;
				}
				if (SystemConfigurationInfoAMSRF1.moduleRFM631Count > 0)
				{
					rfmms[CurrentHeadSite.AMSRF1_Site[i]] = Rfmm1;
				}
			}
		}

#pragma endregion 



		return ret;
	}
	int AMB7600SRTestLibrary::RF_ExternalModuleInitialization(Site^ site)
	{
		int ret = 0;

		if (CurrentHeadSite.TotalSignalCore > 0)
		{
			TestSiteSignalCoreType = gcnew Dictionary <int, String ^>();
			tl->glob->TwoToneMode = 2;// To indicate that Signal Core is used for Two Tone Mode

			for (int i = 0; i < CurrentHeadSite.ExternalModuleList->Count; i++)
			{
				if (CurrentHeadSite.ExternalModuleList[i]["Name"] == "SignalCore")
				{
					if (CurrentHeadSite.ExternalModuleList[i]["Type"] == "SC5511A")
					{
						SIG_SC5511 = gcnew SC5511A(CurrentHeadSite.ExternalModuleList[i]["Address"], false, 0);

						if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0" || CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
						{
							if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0")
							{
								SIG_SC5511_A0 = SIG_SC5511;

								for (int a = 0; a < CurrentHeadSite.AMSRF0_Site->Length; a++)
								{
									SC5511[CurrentHeadSite.AMSRF0_Site[a]] = SIG_SC5511;
									TestSiteSignalCoreType->Add(CurrentHeadSite.AMSRF0_Site[a], CurrentHeadSite.ExternalModuleList[i]["Type"]);
								}
							}
							else if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
							{
								SIG_SC5511_A1 = SIG_SC5511;

								for (int a = 0; a < CurrentHeadSite.AMSRF1_Site->Length; a++)
								{
									SC5511[CurrentHeadSite.AMSRF1_Site[a]] = SIG_SC5511;
									TestSiteSignalCoreType->Add(CurrentHeadSite.AMSRF1_Site[a], CurrentHeadSite.ExternalModuleList[i]["Type"]);

								}
							}
						}
					}
					else if (CurrentHeadSite.ExternalModuleList[i]["Type"] == "SC5505A")
					{
						SIG_SC5505 = gcnew SC5505A(CurrentHeadSite.ExternalModuleList[i]["Address"], false, 1);

						if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0" || CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
						{
							if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0")
							{
								SIG_SC5505_A0 = SIG_SC5505;

								for (int i = 0; i < CurrentHeadSite.AMSRF0_Site->Length; i++)
								{
									SC5505[CurrentHeadSite.AMSRF0_Site[i]] = SIG_SC5505;
								}
							}
							else if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
							{
								SIG_SC5505_A1 = SIG_SC5505;

								for (int i = 0; i < CurrentHeadSite.AMSRF1_Site->Length; i++)
								{
									SC5505[CurrentHeadSite.AMSRF1_Site[i]] = SIG_SC5505;
								}
							}
						}
						if (CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF0" || CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF1")
						{
							if (CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF0")
							{
								SIG_SC5505_A0 = SIG_SC5505;

								for (int i = 0; i < CurrentHeadSite.AMSRF0_Site->Length; i++)
								{
									SC5505[CurrentHeadSite.AMSRF0_Site[i]] = SIG_SC5505;
								}
							}
							else if (CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF1")
							{
								SIG_SC5505_A1 = SIG_SC5505;

								for (int i = 0; i < CurrentHeadSite.AMSRF1_Site->Length; i++)
								{
									SC5505[CurrentHeadSite.AMSRF1_Site[i]] = SIG_SC5505;
								}
							}
						}

					}
				}
			}
		}

		return ret;
	}
	int AMB7600SRTestLibrary::RF_ExternalModuleUninitialization(Site^ site)
	{
		int ret = 0;

		if (CurrentHeadSite.TotalSignalCore > 0)
		{
			TestSiteSignalCoreType = gcnew Dictionary <int, String ^>();

			for (int i = 0; i < CurrentHeadSite.ExternalModuleList->Count; i++)
			{
				if (CurrentHeadSite.ExternalModuleList[i]["Name"] == "SignalCore")
				{
					if (CurrentHeadSite.ExternalModuleList[i]["Type"] == "SC5511A")
					{
						if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0" || CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
						{
							if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0")
							{
								SIG_SC5511_A0->sc5511a_CloseDevice();
							}
							else if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
							{
								SIG_SC5511_A1->sc5511a_CloseDevice();
							}
						}
					}
					else if (CurrentHeadSite.ExternalModuleList[i]["Type"] == "SC5505A")
					{
						if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0" || CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
						{
							if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF0")
							{
								SIG_SC5505_A0->sc5505a_CloseDevice();
							}
							else if (CurrentHeadSite.ExternalModuleList[i]["CH1"] == "AMSRF1")
							{
								SIG_SC5505_A1->sc5505a_CloseDevice();
							}
						}
						if (CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF0" || CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF1")
						{
							if (CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF0")
							{
								SIG_SC5505_A0->sc5505a_CloseDevice();
							}
							else if (CurrentHeadSite.ExternalModuleList[i]["CH2"] == "AMSRF1")
							{
								SIG_SC5505_A1->sc5505a_CloseDevice();
							}
						}
					}
				}
			}
		}

		return ret;
	}

	//AMB7600SR_High Level (Test Phase)
	void AMB7600SRTestLibrary::RF_MeasureSetup(int testSite, String ^ measureChannel, double measureLevel, double measureFreq, int filterOption)
	{
		Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(measureChannel)[0];

		if (((String ^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] != HardwareRsrc->Alias) ||
			((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] != measureLevel) ||
			((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] != measureFreq) ||
			((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] != filterOption) ||
			((bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedMeasureFast"] == true) ||
			((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] != 0))// true if channel, measurePower, measureFreq & filterOption is not same as previous
		{
			CheckError(testSite, amsrf[testSite]->amsrf->MeasureSetup(measureChannel, measureLevel, measureFreq, filterOption));
		}

		//State Recording
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] = HardwareRsrc->Alias;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] = measureLevel;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] = measureFreq;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] = filterOption;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] = 0;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedMeasureFast"] = false;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFactor"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleRate"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleSize"] = 999;		
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableMeasureFast"] = true;

		if (measureLevel >= 0)
		{
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePreAmpStatus"] = false;
		}
		else
		{
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePreAmpStatus"] = true;
		}

	}
	void AMB7600SRTestLibrary::RF_MeasureSetupIQ(int testSite, String ^ measureChannel, double measureLevel, double measureFreq, double sampleRate, int sampleSize, int filterOption)
	{
		Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(measureChannel)[0];

		if (((String^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] != HardwareRsrc->Alias) ||
			((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] != measureLevel) ||
			((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] != measureFreq) ||
			((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] != filterOption) ||
			((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] != 1) ||
			((bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedMeasureFast"] == true) ||
			((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleRate"] != sampleRate) ||
			((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleSize"] != sampleSize))// true if channel, measurePower, measureFreq & filterOption is not same as previous
		{
			CheckError(testSite, amsrf[testSite]->amsrf->MeasureSetupIQ(measureChannel, measureLevel, measureFreq, sampleRate, sampleSize, filterOption));
		}

		//State Recording
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] = HardwareRsrc->Alias;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] = measureLevel;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] = measureFreq;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] = filterOption;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] = 1;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleRate"] = sampleRate;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleSize"] = sampleSize;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedMeasureFast"] = false;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFactor"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableMeasureFast"] = false;

	}
	void AMB7600SRTestLibrary::RF_MeasureFast(int testSite, String ^ measureChannel, double measureLevel, double measureFreq, int filterOption, double delay, double % result)
	{
		Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(measureChannel)[0];

		double measureFactor = 0.0;
		bool status = false;
		bool overload = true;
		result = CONST_INVALID_RESULT;
		bool PreAmpStatus = false;

		if (measureLevel >= 0)
		{
			PreAmpStatus = false;
		}
		else
		{
			PreAmpStatus = true;
		}

		if ((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] != 0 ||
			(bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePreAmpStatus"] != PreAmpStatus ||
			(int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] != filterOption ||
			(String^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] != HardwareRsrc->Alias)// true if no perform this CM before
		{
			RF_MeasureSetup(testSite, measureChannel, measureLevel, measureFreq, filterOption);
			RF_MeasureChannel(testSite, measureChannel, delay, result);
		}
		else
		{
			RF_GetMeasureFactor(testSite, measureChannel, measureLevel, measureFreq, filterOption, measureFactor);

			if ((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFactor"] != measureFactor ||
				(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] != measureLevel)
			{
				RF_KTM9420_ATTR_RECEIVER_RF_POWER_SET(testSite, measureLevel - measureFactor);
			}
			if ((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] != measureFreq)
			{
				RF_KTM9420_ATTR_RECEIVER_RF_FREQUENCY_SET(testSite, measureFreq);
			}
			
			RF_KtM9420_Apply(testSite);
			util->WaitSecond(delay);
			RF_KtM9420_Arm(testSite);
			RF_KtM9420_WaitForData(testSite, 1000, status);

			if (status)
			{
				RF_KtM9420_ReadPower(testSite, 0, result, overload);
			}

			result = result + measureFactor;

			//State Recording
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureChannel"] = HardwareRsrc->Alias;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFactor"] = measureFactor;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePower"] = measureLevel;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFreq"] = measureFreq;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureFilter"] = filterOption;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureMode"] = 0;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasurePreAmpStatus"] = PreAmpStatus;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedMeasureFast"] = true;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleRate"] = 999.99;
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["MeasureSampleSize"] = 999;
		}


	}
	void AMB7600SRTestLibrary::RF_SourcePower(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq)
	{
		Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(sourceChannel)[0];

		if ((String^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] != HardwareRsrc->Alias ||
			(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] != sourceLevel ||
			(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] != sourceFreq ||
			(bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] == true ||
			(int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] != 0)
		{
			CheckError(testSite, amsrf[testSite]->amsrf->SourceChannel(sourceChannel, sourceLevel, sourceFreq));
		}

		//State Recording
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] = HardwareRsrc->Alias;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] = sourceLevel;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] = sourceFreq;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFactor"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAlignFactor"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] = 0;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] = false;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableSourceFast"] = true;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceOffset"] = 0.0;

	}
	void AMB7600SRTestLibrary::RF_SourcePower(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, double attenuation)
	{
		Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(sourceChannel)[0];

		if ((String^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] != HardwareRsrc->Alias ||
			(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] != sourceLevel ||
			(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] != sourceFreq ||
			(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] != attenuation ||
			(bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] == true ||
			(int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] != 1)
		{
			CheckError(testSite, amsrf[testSite]->amsrf->SourceChannel(sourceChannel, sourceLevel, sourceFreq, attenuation));
		}

		//State Recording
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] = HardwareRsrc->Alias;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] = sourceLevel;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] = sourceFreq;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] = attenuation;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFactor"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAlignFactor"] = 999.99;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceMode"] = 1;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] = false;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableSourceFast"] = true;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceOffset"] = 0.0;
	}
	void AMB7600SRTestLibrary::RF_SourcePowerFast(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, bool userSetAttenuation, double attenuation)
	{
		Resource ^ HardwareRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(sourceChannel)[0];

		double RfpmInAtt = 0.0;
		double SourceFactor = 0.0;
		double Couplerfatcor = 0.0;
		double AlignFactor = 0.0;

		double SourceFactor_Pre = 0.0;
		double AlignFactor_Pre = 0.0;
		double SourceLevel_Pre = 0.0;
		double SourceOffset = 0.0;
		double SourcePower = 0;
		double SourceOffset_Pre = 0.0;

		if (userSetAttenuation == true)
		{
			RfpmInAtt = attenuation;
		}
		else
		{
			if (sourceLevel <= -20.0)
			{
				RfpmInAtt = 20.0;
			}
			else
			{
				RfpmInAtt = 0.0;
			}
		}

		RF_GetSourceFactor(testSite, sourceChannel, sourceLevel, sourceFreq, RfpmInAtt, SourceFactor, Couplerfatcor);
		RF_GetSourceAlignFactor(testSite, sourceChannel, sourceLevel, sourceFreq, RfpmInAtt, AlignFactor);

		if ((String^)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] != HardwareRsrc->Alias ||
			(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] != RfpmInAtt ||
			(bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["EnableSourceFast"] == false)
		{
			if (userSetAttenuation == true)
			{
				RF_SourcePower(testSite, sourceChannel, sourceLevel, sourceFreq, RfpmInAtt);
			}
			else
			{
				RF_SourcePower(testSite, sourceChannel, sourceLevel, sourceFreq);
			}
		}
		else
		{
			if (((double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] != sourceLevel) ||
				(bool)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] == false ||
				(double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] != sourceFreq)
			{
				SourceFactor_Pre = (double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFactor"];
				AlignFactor_Pre = (double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAlignFactor"];
				SourceLevel_Pre = (double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"];
				SourceOffset_Pre = (double)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceOffset"];
				SourceOffset = sourceLevel - SourceLevel_Pre + SourceFactor - SourceFactor_Pre + AlignFactor - AlignFactor_Pre;

				if (SourceOffset <= 10 && SourceOffset >= -50) // if within baseband power limit
				{
					RF_KTM9420_ATTR_SOURCE_MODULATION_BASEBAND_POWER_SET(testSite, SourceOffset + SourceOffset_Pre);
				}
				else
				{
					SourceOffset_Pre = 0.0;
					SourceOffset = 0.0;
					SourcePower = sourceLevel + SourceFactor + AlignFactor;

					RF_KTM9420_ATTR_SOURCE_MODULATION_BASEBAND_POWER_SET(testSite, 0.0);
					RF_KTM9420_ATTR_SOURCE_RF_LEVEL_SET(testSite, SourcePower);
				}

				RF_KTM9420_ATTR_SOURCE_RF_FREQUENCY_SET(testSite, sourceFreq);
			}
		}

		//State Recording
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceChannel"] = HardwareRsrc->Alias;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourcePower"] = sourceLevel;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFreq"] = sourceFreq;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAtt"] = RfpmInAtt;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceFactor"] = SourceFactor;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceAlignFactor"] = AlignFactor;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["ExecutedSourceFast"] = true;
		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceOffset"] = SourceOffset + SourceOffset_Pre;
	}
	int AMB7600SRTestLibrary::RF_MeasureChannel(int testSite, String^ measureChannel, double delay, double % result)
	{
		int ret = 0;
		util->WaitSecond(delay);
		CheckError(testSite, amsrf[testSite]->amsrf->MeasureChannel(measureChannel, result));
		return ret;
	}
	int AMB7600SRTestLibrary::RF_MeasureChannelIQ(int testSite, String^ measureChannel, double delay, double % result)
	{
		int ret = 0;
		util->WaitSecond(delay);
		CheckError(testSite, amsrf[testSite]->amsrf->MeasureChannelIQ(measureChannel, result));
		return ret;
	}
	int AMB7600SRTestLibrary::RF_MeasureRawIQArray(int testSite, String^ measureChannel, double delay, array <double>^ % iData, array <double>^ % qData)
	{
		int ret = 0;
		util->WaitSecond(delay);
		CheckError(testSite, amsrf[testSite]->amsrf->MeasureRawIQArray(measureChannel, iData, qData));

		return ret;
	}
	int AMB7600SRTestLibrary::RF_GetMeasureFactor(int testSite, String^ measureChannel, double measureLevel, double measureFreq, int filterOption, double  % measureFactor)
	{
		int ret = 0;
		CheckError(testSite, amsrf[testSite]->amsrf->GetMeasureFactor(measureChannel, measureLevel, measureFreq, filterOption, measureFactor));

		return ret;
	}
	int AMB7600SRTestLibrary::RF_GetSourceFactor(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, double % sourceFactor, double  % couplerFactor)
	{
		int ret = 0;
		CheckError(testSite, amsrf[testSite]->amsrf->GetSourceFactor(sourceChannel, sourceLevel, sourceFreq, sourceFactor, couplerFactor));
		return ret;
	}
	int AMB7600SRTestLibrary::RF_GetSourceFactor(int testSite, String^ sourceChannel, double sourceLevel, double sourceFreq, double sourceAttenuattion, double % sourceFactor, double  % couplerFactor)
	{
		int ret = 0;
		CheckError(testSite, amsrf[testSite]->amsrf->GetSourceFactor(sourceChannel, sourceLevel, sourceFreq, sourceAttenuattion, sourceFactor, couplerFactor));

		return ret;
	}
	int AMB7600SRTestLibrary::RF_GetSourceAlignFactor(int testSite, String^ l_SourceChannel, double l_SourceLevel, double l_SourceFreq, double l_RfpmInAtt, double % l_AlignFactor)
	{
		int ret = 0;

		CheckError(testSite, amsrf[testSite]->amsrf->GetSourceAlignFactor(l_SourceChannel, l_SourceLevel, l_SourceFreq, l_RfpmInAtt, l_AlignFactor));

		return ret;
	}
	void AMB7600SRTestLibrary::RF_SourceTwoTone(int testSite, String^ sourceChannel, double sourceLevel0, double sourceFreq0, double sourceLevel1, double sourceFreq1, double attenuation)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SourceTwoTone(sourceChannel, sourceLevel0, sourceFreq0, sourceLevel1, sourceFreq1, attenuation));
	}
	void AMB7600SRTestLibrary::RF_SourceTwoTone(int testSite, String^ sourceChannel, double sourceLevel0, double sourceFreq0, double sourceLevel1, double sourceFreq1)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SourceTwoTone(sourceChannel, sourceLevel0, sourceFreq0, sourceLevel1, sourceFreq1));
	}
	void AMB7600SRTestLibrary::RF_StartModulation(int testSite, String ^ VSG, String ^ modulationFile, int playBackMode)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->StartModulation(VSG, modulationFile, playBackMode));
		//int ret = 0;
		//ret = sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_ENABLE_SET(true);
		//ret = sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_LEVEL_SET(1.0); // +1.0V
		//ret = sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_MODE_SET(1); // KTM9420_VAL_TRIGGER_MODE_PULSE - 1

		//	ret = sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_SLOPE_SET(0); // KTM9420_VAL_TRIGGER_POLARITY_POSITIVE - 0

		//ret = sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_SOURCE_SET(8);
		//ret = sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_DELAY_SET(0);

		//CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_MODULATION_PLAYBACK_MODE_SET(1));

		//CheckError(testSite, sigGen[testSite]->KtM9420_Apply());

		//CheckError(testSite, sigGen[testSite]->KtM9420_SourceModulationPlayArb(modulationFile, 1));
		//CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_MODULATION_IQ_ARB_ENABLED_SET(true));
		//CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_MODULATION_ENABLED_SET(true));
		//CheckError(testSite, sigGen[testSite]->KtM9420_Apply());

		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceSignal"] = 1;

	}
	void AMB7600SRTestLibrary::RF_LoadModulation(int testSite, String ^ VSG, String ^ modulationFile, int stationNo)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->LoadModulation(VSG, modulationFile, stationNo));
	}

	void AMB7600SRTestLibrary::RF_StopModulation(int testSite, String ^ VSG)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->StopModulation(VSG));

		tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["SourceSignal"] = 0;
	}
	void AMB7600SRTestLibrary::RF_SetSourceTriggerOut(int testSite, String ^ VSG, bool enable, int trigDestination, int trigOption)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SetSourceTriggerOut(VSG, enable, trigDestination, trigOption));
	}
	void AMB7600SRTestLibrary::RF_SetMeasureTriggerRouting(int testSite, String ^ VSA, bool enable, int trigIn, int trigOut)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SetMeasureTriggerRouting(VSA, enable, trigIn, trigIn));
	}
	void AMB7600SRTestLibrary::RF_SetSourceTriggerRouting(int testSite, String ^ VSG, bool enable, int trigIn, int trigOut)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SetSourceTriggerRouting(VSG, enable, trigIn, trigIn));
	}
	void AMB7600SRTestLibrary::RF_SetMeasureTriggerIn(int testSite, String ^ VSA, bool enable, int trigSource, int trigPolarity, double trigDelay)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SetMeasureTriggerIn(VSA, enable, trigSource, trigPolarity, trigDelay));
	}
	void AMB7600SRTestLibrary::RF_SetSourceTriggerIn(int testSite, String ^ VSG, bool enable, int trigSource, int trigPolarity, double trigDelay)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->SetSourceTriggerIn(VSG, enable, trigSource, trigPolarity, trigDelay));
	}
	void AMB7600SRTestLibrary::RF_MeasureSParamSetup(int testSite, array<String^>^ channelArray, double sourcePower, double measurePower, double measurefreq)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->MeasureSParamSetup(channelArray, sourcePower, measurePower, measurefreq));
	}
	void AMB7600SRTestLibrary::RF_MeasureSParamSetup(int testSite, array<String^>^ channelArray, double sourcePower, double measurePower, double measurefreq, bool preampOn, double sampleSize, double sampleRate)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->MeasureSParamSetup(channelArray, sourcePower, measurePower, measurefreq, preampOn, sampleSize, sampleRate));
	}
	void AMB7600SRTestLibrary::RF_MeasureSParam(int testSite, array<String^>^ channelArray, SParam_Format format, array<ComplexNumber> ^ % sparamResult)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->MeasureSParam(channelArray, format, sparamResult));
	}
	void AMB7600SRTestLibrary::RF_IsolateAllChannel(int testSite)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->IsolateAllChannels());
	}
	void AMB7600SRTestLibrary::RF_IsolateChannel(int testSite, String ^ channel)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->IsolateSelectedChannels(channel));
	}
	void AMB7600SRTestLibrary::RF_RunSourceAlignment(int testSite)
	{
		CheckError(testSite, amsrf[testSite]->amsrf->RunSourceAlignment());
	}
	void AMB7600SRTestLibrary::RF_LoadHardwareProfile(int testSite)
	{
		if ((int)tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["TestSite_LoadHardwareProfile"] != testSite)
		{
			amsrf[testSite]->amsrf->LoadHardwareProfile(tl->glob->HardwareProfile, tl->glob->tf.TestHead, testSite, tl->glob->AWV.Offline);
			tl->glob->AmsrfStateSettingsManager[tl->glob->TestSiteAmsrfType[testSite]]["TestSite_LoadHardwareProfile"] = testSite;
		}
	}
	//Helper Function (Test Phase)
	void AMB7600SRTestLibrary::RF_ConvertIQtoPower(double iData, double qData, double % powerWatt, double % powerdBm)
	{
		powerdBm = 0.0;
		powerWatt = 0.0;

		powerWatt = (iData * iData + qData* qData) / 100;

		powerdBm = 10 * Math::Log10(powerWatt / 0.001);
	}
	void AMB7600SRTestLibrary::RF_ConvertIQtoPower(array <double>^  iData, array <double>^  qData, int sampleSize, int l_StartIndex, double % averagePowerWatt, double % averagePowerdBm)
	{
		averagePowerdBm = 0.0;
		averagePowerWatt = 0.0;
		double totalPower = 0.0;

		for (int i = l_StartIndex; i < sampleSize; i++)
		{
			totalPower += ((iData[i] * iData[i] + qData[i] * qData[i]) / 100);
		}
		averagePowerWatt = totalPower / sampleSize;
		averagePowerdBm = 10 * Math::Log10(averagePowerWatt / 0.001);
	}
	void AMB7600SRTestLibrary::RF_ConvertWattTodBm(double powerWatt, double % powerdBm)
	{
		powerdBm = 10 * Math::Log10(powerWatt / 0.001);
	}
	void AMB7600SRTestLibrary::RF_ConvertdBmToWatt(double powerdBm, double % powerWatt)
	{
		powerWatt = (Math::Pow(10, (powerdBm / 10))) / 1000;
	}
	void AMB7600SRTestLibrary::RF_RFM631FilterOption(double fundamentalFreq, double harmonicFreq, int % filterOption)
	{
		if ((1300 MHz <= harmonicFreq && harmonicFreq <= 5000 MHz) && (fundamentalFreq < 1300 MHz || fundamentalFreq > 5000 MHz))
		{
			filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_HPF1;
		}
		else if ((3700 MHz <= harmonicFreq && harmonicFreq <= 8400 MHz) && (fundamentalFreq < 3700 MHz || fundamentalFreq > 8400 MHz))
		{
			filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_HPF2;
		}
		else if ((7700 MHz <= harmonicFreq && harmonicFreq <= 8400 MHz) && (fundamentalFreq < 7700 MHz || fundamentalFreq > 8400 MHz))
		{
			filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_HPF3;
		}
		else
		{
			filterOption = AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS;
		}
	}
	void AMB7600SRTestLibrary::RF_TestMethod_ResultDisplayChecking(Site^ site, int testSite, int totalTestParameter, int totalResult, int testParameterNum, array<String^>^ % userDesiredResult)
	{
		if (totalResult > 1)
		{
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();

			int i = 0;
			int UserDispRes = 0;
			String ^ testParameterName = nullptr;
			int TpNum = testParameterNum;

			while ((TpNum < (totalTestParameter)) && i<totalResult)
			{
				testParameterName = tl->glob->TestProperty[testSite].TestParameterName[TpNum];
				testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

				if ((bool)testConditionCollection->ContainsKey("ResultDisplay"))
				{
					if (i == 0)
					{
						UserDispRes++;
					}
					else
					{
						if (!(bool)testConditionCollection->ContainsKey("TestMethod"))
						{
							UserDispRes++;
						}
						else
						{
							break;
						}
					}
				}

				if (i == 0 && UserDispRes == 0)
				{
					break;
				}
				TpNum++;
				i++;
			}

			userDesiredResult = gcnew array <String^>(UserDispRes);
			TpNum = testParameterNum;

			for (i = 0; i < UserDispRes; i++)
			{
				testParameterName = tl->glob->TestProperty[testSite].TestParameterName[TpNum + i];
				testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

				userDesiredResult[i] = (String^)tf_TestParameter_ConditionCast(testParameterName, "ResultDisplay");

			}
		}

	}

	//VXT_Low Level (Test Phase)
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_RECEIVER_TRIGGERS_EXTERNSL_TRIGGER_TERMINATION_SET(int testSite, int terminationMode)
	{
		CheckError(testSite, dig[testSite]->KTM9420_ATTR_RECEIVER_TRIGGERS_EXTERNSL_TRIGGER_TERMINATION_SET(terminationMode)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_RECEIVER_RF_POWER_SET(int testSite, double measurePower)
	{
		CheckError(testSite, dig[testSite]->KTM9420_ATTR_RECEIVER_RF_POWER_SET(measurePower)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_RECEIVER_RF_FREQUENCY_SET(int testSite, double measureFreq)
	{
		CheckError(testSite, dig[testSite]->KTM9420_ATTR_RECEIVER_RF_FREQUENCY_SET(measureFreq)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KtM9420_WaitForData(int testSite, double timeOut, bool % status)
	{
		CheckError(testSite, dig[testSite]->KtM9420_WaitForData(timeOut, status)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KtM9420_ReadPower(int testSite, long captureID, double % result, bool % overLoad)
	{
		CheckError(testSite, dig[testSite]->KtM9420_ReadPower(captureID, result, overLoad)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KtM9420_Apply(int testSite)
	{
		CheckError(testSite, dig[testSite]->KtM9420_Apply()); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KtM9420_Arm(int testSite)
	{
		try
		{
			CheckError(testSite, dig[testSite]->KtM9420_Arm());
		}
		catch (Exception ^ ex)
		{
			//tracerLogger->WriteToTracer("Site" + testSite.ToString(), "RF: " + ret.ToString());
			//tracerLogger->WriteToTracer("Site" + testSite.ToString(), ex->StackTrace);
		}
	}
	int AMB7600SRTestLibrary::RF_KtM9420_GetIQData(int testSite, array<double> ^% iData, array<double> ^% qData)
	{
		long ret = 0;
		bool overload = true;
		bool status = false;

		if (dig != nullptr)
		{
			try
			{
				ret = dig[testSite]->KtM9420_WaitForData(5, status);

				if (!status)
				{
					String^ ErrorMessage = "Wait For Data Timeout at API KtM9420_WaitForData ErrorCode RF: " + ER_HADWARE_TIMEOUT.ToString();
					tl->FileLogging(testSite, LOGGER_ERROR_TYPE, "Wait For Data Timeout at API KtM9420_WaitForData ErrorCode RF: " + ER_HADWARE_TIMEOUT.ToString());
					tl->WriteToLogger(testSite, ErrorMessage);
				}
			}
			catch (Exception ^ ex)
			{
				String^ ErrorMessage = "Site" + testSite.ToString() + "ErrorCode RF: " + ret.ToString();
				tl->FileLogging(testSite, LOGGER_ERROR_TYPE, ErrorMessage);
				tl->WriteToLogger(testSite, ErrorMessage);
			}


			//Create array for IQ Data
			int samples = 0;
			try
			{
				CheckError(testSite, dig[testSite]->KTM9420_ATTR_IQ_ACQUISITION_SAMPLES_GET(samples));
			}
			catch (Exception ^ ex)
			{
				String^ ErrorMessage = "Site " + testSite + ":: KTM9420_ATTR_IQ_ACQUISITION_SAMPLES_GET [" + testSite + "] " + "encountered error [" + ex->ToString() + "] when performing.";
				tl->FileLogging(testSite, LOGGER_ERROR_TYPE, ErrorMessage);
				tl->WriteToLogger(testSite, ErrorMessage);
			}
			int actualSamples = samples * 2;

			array<double> ^l_iData = gcnew array<double>(samples);
			array<double> ^l_qData = gcnew array<double>(samples);
			array<double> ^ l_iqData = gcnew array<double>(actualSamples);
			try
			{
				CheckError(testSite, dig[testSite]->KtM9420_IQAcquisitionReadIQData(0, 0, samples, actualSamples, l_iqData, actualSamples, overload));
			}
			catch (Exception ^ ex)
			{
				String^ ErrorMessage = "Site " + testSite + ":: KtM9420_IQAcquisitionReadIQData [" + testSite + "] " + "encountered error [" + ex->ToString() + "] when performing.";
				tl->FileLogging(testSite, LOGGER_ERROR_TYPE, ErrorMessage);
				tl->WriteToLogger(testSite, ErrorMessage);
			}
			if (overload)
			{
				String^ ErrorMessage = "Digitizer Overload!Please adjust the measure level to a higher value.ErrorCode RF : " + ER_ILLEGAL_OPERATION.ToString();
				tl->FileLogging(testSite, LOGGER_ERROR_TYPE, "Digitizer Overload! Please adjust the measure level to a higher value. ErrorCode RF: " + ER_ILLEGAL_OPERATION.ToString());
				tl->WriteToLogger(testSite, ErrorMessage);
			}

			for (int index = 0; index < samples; index++)
			{
				l_iData[index] = l_iqData[2 * index];
				l_qData[index] = l_iqData[(2 * index) + 1];
			}

			for (int i = 0; i < samples; i++)
			{
				if (double::IsPositiveInfinity(l_iData[i]))
				{
					iData[i] = double::MaxValue;
				}
				else if (double::IsNegativeInfinity(l_iData[i]))
				{
					iData[i] = double::MinValue;
				}
				else
				{
					iData[i] = l_iData[i];
				}

				if (double::IsPositiveInfinity(l_qData[i]))
				{
					qData[i] = double::MaxValue;
				}
				else if (double::IsNegativeInfinity(l_qData[i]))
				{
					qData[i] = double::MinValue;
				}
				else
				{
					qData[i] = l_qData[i];
				}
			}
		}

		return ret;
	}
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_SOURCE_MODULATION_BASEBAND_POWER_SET(int testSite, double powerLevel)
	{
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_MODULATION_BASEBAND_POWER_SET(powerLevel)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_SOURCE_RF_LEVEL_SET(int testSite, double powerLevel)
	{
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_RF_LEVEL_SET(powerLevel)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_SOURCE_RF_FREQUENCY_SET(int testSite, double sourceFreq)
	{
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_RF_FREQUENCY_SET(sourceFreq)); //KTM9420_VAL_TRIGGER_TERMINATION_HIGH_IMPEDANCE
	}
	void AMB7600SRTestLibrary::RF_KTM9420_ATTR_SOURCE_Trigger(int testSite, String ^ VSG, String ^ modulationFile)
	{
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_ENABLE_SET(true));
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_LEVEL_SET(1.0));			//trigger level
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_MODE_SET(1));				//0 = level | 1 = pulse
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_SLOPE_SET(0));			//0 = positive | 1 = negative
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_SOURCE_SET(0));			//0 = front trigger
		CheckError(testSite, sigGen[testSite]->KTM9420_ATTR_SOURCE_TRIGGERS_EXTERNALTRIGGER_DELAY_SET(0));			//trigger delay
		CheckError(testSite, sigGen[testSite]->KtM9420_Apply());


		// *** SG still output CW signal at this point
		//CheckError(testSite, sigGen[testSite]->KtM9420_SourceModulationPlayArb(modulationFile, 1));

		// *** SG stop CW signal
		// *** need to apply dummy Stop & StartModulation API to arm the vxt
		// *** send external trigger signal
		// *** waveform start to playback upon triggered
		CheckError(testSite, amsrf[testSite]->amsrf->StopModulation(VSG));
		CheckError(testSite, amsrf[testSite]->amsrf->StartModulation(VSG, modulationFile, AMSRF_CONST_MODPLAYBACKMODE_CONT));

	}
	//RFM600e_Low Level (Test Phase)
	void AMB7600SRTestLibrary::RF_RFDM621_SetInputSource(int testSite, int outputPort, int mode)
	{
		CheckError(testSite, rfdms[testSite]->SetInputSource(outputPort, mode));
	}
	void AMB7600SRTestLibrary::RF_RFDM621_SetMode(int testSite, int mode)
	{
		CheckError(testSite, rfdms[testSite]->SetMode(mode));
	}
	void AMB7600SRTestLibrary::MovingAverageUtility(array<double>^ pData_Watt, int movingAverageFactor, array<double>^ % pData_Watt_MA)
	{
		int delta = 0;
		int sampleNum=pData_Watt->Length;
		pData_Watt_MA = gcnew array<double>(sampleNum);

		for (int i = 0; i < sampleNum; i++)
		{
			if (i < movingAverageFactor / 2)
			{
				delta = movingAverageFactor / 2 - i;  //Number of insufficient point(s) on the left

				//Get Points on the left
				if (i != 0)
				{
					for (int n = i - 1; n >= i - (movingAverageFactor / 2) + delta; n--)
					{
						pData_Watt_MA[i] += pData_Watt[n];
					}
				}

				//Get Points on the right
				for (int n = i + 1; n <= i + movingAverageFactor / 2 + delta; n++)
				{
					pData_Watt_MA[i] += pData_Watt[n];
				}

				pData_Watt_MA[i] += pData_Watt[i];
				pData_Watt_MA[i] = pData_Watt_MA[i] / (movingAverageFactor + 1);

			}
			else if (i + movingAverageFactor / 2 > sampleNum - 1)
			{
				delta = movingAverageFactor / 2 + i - (sampleNum - 1);  //Number of insufficient point(s) on the right

				//Get Points on the left
				for (int n = i - 1; n >= i - (movingAverageFactor / 2) - delta; n--)
				{
					pData_Watt_MA[i] += pData_Watt[n];
				}

				//Get Points on the right
				if (i != sampleNum - 1)
				{
					for (int n = i + 1; n <= i + movingAverageFactor / 2 - delta; n++)
					{
						pData_Watt_MA[i] += pData_Watt[n];
					}
				}
				pData_Watt_MA[i] += pData_Watt[i];
				pData_Watt_MA[i] = pData_Watt_MA[i] / (movingAverageFactor + 1);
			}
			else
			{
				//Get Points on the left
				for (int n = i - 1; n >= i - movingAverageFactor / 2; n--)
				{
					pData_Watt_MA[i] += pData_Watt[n];
				}

				//Get Points on the right
				for (int n = i + 1; n <= i + movingAverageFactor / 2; n++)
				{
					pData_Watt_MA[i] += pData_Watt[n];
				}

				pData_Watt_MA[i] += pData_Watt[i];
				pData_Watt_MA[i] = pData_Watt_MA[i] / (movingAverageFactor + 1);
			}
		}
	}
	void AMB7600SRTestLibrary::CalculateSwitchingTime(int optionRiseFall, array<double>^ iData, array<double>^ qData, bool movingAverageStatus,int movingAverageFactor,  double sampleRate, double startCapture, double stopCapture, int numberAveragingInit, int numberAveragingFinal, double digitizerTriggerDelay, double correctionFactor, double thresholdUncertainty, double % timing, array<double>^ % pData_Watt)
	{
		int sampleNum = iData->Length;
		int consecutiveFound = 5;
		int iStart = 0;
		int count = 0; //intitialize count 
		int result = 0; //initialize max 
		int pCount = 0;
		double pInit = 0.0;
		double pSettle = 0.0;
		double pDynamicRange = 0.0;
		double pStart = 0;
		bool startCounting = false;
		double power_at_threshold = 0;
		double powerWatt;
		array<double> ^ iqData = gcnew array<double>(sampleNum);
		pData_Watt = gcnew array<double>(sampleNum);
		array<double> ^ pData_Watt_PostProcess = gcnew array<double>(sampleNum);
		array<double> ^ pData_dBm = gcnew array<double>(sampleNum);
		array<double> ^ LogIqData = gcnew array<double>(sampleNum);
		timing = CONST_INVALID_RESULT;



		//Initialization of the Variable
		for (int i = 0; i < sampleNum; i++)
		{
			iqData[i] = 0;
			pData_dBm[i] = 0;
			pData_Watt[i] = 0;
			LogIqData[i] = 0;
			pData_Watt_PostProcess[i] = 0;
		}

		//Converting the Raw IQ Data to dBm & Watt
		for (int i = 0; i < sampleNum; i++)
		{
			//Convert Raw Data IQ to dBm
			RF_ConvertIQtoPower(iData[i], qData[i], powerWatt, pData_dBm[i]);//PowerWatt is not used in this function

			//Add BoardLoss to the dBm
			pData_dBm[i] = pData_dBm[i] + correctionFactor;

			//Convert the dBm data to Watt
			RF_ConvertdBmToWatt(pData_dBm[i], pData_Watt_PostProcess[i]);
		}

		//Moving Aeveraging Function if any
		if (movingAverageStatus == true)
		{
			MovingAverageUtility(pData_Watt_PostProcess, movingAverageFactor, pData_Watt);
		}
		else
		{
			pData_Watt = pData_Watt_PostProcess;
		}

		//Averaging the power at Initial State
		for (int i = 0; i < numberAveragingInit; i++)
		{
			pInit += pData_Watt[i];
			pCount++;
		}

		pInit = pInit / pCount;

		//Averaging the power at Final State
		pCount = 0;
		for (int i = sampleNum - 1; i >(sampleNum - (numberAveragingFinal + 1)); i--)
		{
			pSettle += pData_Watt[i];
			pCount++;
		}

		pSettle = pSettle / pCount;


		if (optionRiseFall == 0)
		{
			pDynamicRange = pInit - pSettle;
			pStart = pInit - ((startCapture / 100)*pDynamicRange);
			power_at_threshold = pSettle + ((1 - (stopCapture / 100))*pDynamicRange);
		}
		else
		{
			pDynamicRange = pSettle - pInit;
			pStart = pInit + ((startCapture / 100)*pDynamicRange);
			power_at_threshold = pSettle - ((1 - (stopCapture / 100))*pDynamicRange);
		}

		for (int i = 0; i < sampleNum; i++)
		{
			if (optionRiseFall == 1)
			{
				if (startCounting == false && pData_Watt[i] > pStart)
				{
					startCounting = true;
					iStart = i;
				}

				if (startCounting == true)
				{
					if (pData_Watt[i] > (power_at_threshold - thresholdUncertainty))//0.1 dB) // Increment count and update result if count becomes more. 0.5dB as uncertainty
					{
						count++; //increase count
						result = Math::Max(result, count);

						if (result >= consecutiveFound) //more than 5 data consequtively more than threshold
						{
							timing = (i - iStart - consecutiveFound) * (1 / sampleRate);
							timing = timing + digitizerTriggerDelay;

							break;
						}
					}
					else // Reset count when 0 is found
					{
						count = 0;
					}
				}
			}
			else
			{
				if (startCounting == false && pData_Watt[i] < pStart)
				{
					startCounting = true;
					iStart = i;
					//tl->WriteToLogger(0, "RiseFall: " optionRiseFall.ToString());
				}

				if (startCounting == true)
				{
					if (pData_Watt[i] < (power_at_threshold + thresholdUncertainty))
					{
						count++; //increase count
						result = Math::Max(result, count);

						if (result >= consecutiveFound) //more than 5 data consequtively more than threshold
						{
							timing = (i - iStart - consecutiveFound) * (1 / sampleRate);
							timing = timing + digitizerTriggerDelay;

							break;
						}
					}
					else // Reset count when 0 is found
					{
						count = 0;
					}
				}
			}
		}
	}

	//External Signal Generator Signal Core (Test Phase)
	void AMB7600SRTestLibrary::RF_SourcePowerExternalSignalGenerator(int testSite, double sourceLevel)
	{
		String ^ SignalCoreType = nullptr;

		SignalCoreType = TestSiteSignalCoreType[testSite];

		if (SignalCoreType == "SC5511A")
		{
			SC5511[testSite]->sc5511a_SetPowerLevel(sourceLevel);
		}
		else if (SignalCoreType == "SC5505A")
		{
			SC5505[testSite]->sc5505a_SetPowerLevel(SourceChannel_SC[testSite], sourceLevel);
		}
	}
	void AMB7600SRTestLibrary::RF_SourceFreqExternalSignalGenerator(int testSite, double sourceFreq)
	{
		String ^ SignalCoreType = nullptr;

		SignalCoreType = TestSiteSignalCoreType[testSite];

		if (SignalCoreType == "SC5511A")
		{
			SC5511[testSite]->sc5511a_SetFrequency(sourceFreq);
		}
		else if (SignalCoreType == "SC5505A")
		{
			SC5505[testSite]->sc5505a_SetFrequency(SourceChannel_SC[testSite], sourceFreq);
		}
	}
	void AMB7600SRTestLibrary::RF_OutputEnableExternalSignalGenerator(int testSite, bool enable)
	{
		String ^ SignalCoreType = nullptr;

		SignalCoreType = TestSiteSignalCoreType[testSite];

		if (SignalCoreType == "SC5511A")
		{
			SC5511[testSite]->OutputEnable_Set(enable);
		}
		else if (SignalCoreType == "SC5505A")
		{
			SC5505[testSite]->sc5505a_SetRfOutput(SourceChannel_SC[testSite], enable);
		}
	}

#pragma region "WLAN"
	//Wlan Modulation 
	void AMB7600SRTestLibrary::RF_WlanInitSetup(int testSite, String ^ VSG, String ^ VSA, int standardSelection, int measureOption)
	{
		if (measureOption == WLAN_ABGN)
		{
			wlan_abgn[testSite] = gcnew Wlan(VSG, VSA, amsrf[testSite]->amsrf, tl->glob->AWV.Offline, standardSelection, measureOption);
			wlan_abgn[testSite]->SetResource(VSG, VSA);
		}
		else if (measureOption == WLAN_ACAX)
		{
			wlan_acax[testSite] = gcnew Wlan(VSG, VSA, amsrf[testSite]->amsrf, tl->glob->AWV.Offline, standardSelection, measureOption);
			wlan_acax[testSite]->SetResource(VSG, VSA);
		}

	}
	void AMB7600SRTestLibrary::RF_WlanStandardSelection(int testSite, int WlanModulationStandard, WlanModulationStandardEnum % standard)
	{
		switch (WlanModulationStandard)
		{
		case WlanModulationStandardEnum::AC160:
			standard = WlanModulationStandardEnum::AC160;
			wlan[testSite] = wlan_acax[testSite];
		    break;

		case WlanModulationStandardEnum::AC20:
			standard = WlanModulationStandardEnum::AC20;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AC40:
			standard = WlanModulationStandardEnum::AC40;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AC80:
			standard = WlanModulationStandardEnum::AC80;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AG20:
			standard = WlanModulationStandardEnum::AG20;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AX160:
			standard = WlanModulationStandardEnum::AX160;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AX20:
			standard = WlanModulationStandardEnum::AX20;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AX40:
			standard = WlanModulationStandardEnum::AX40;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::AX80:
			standard = WlanModulationStandardEnum::AX80;
			wlan[testSite] = wlan_acax[testSite];
			break;

		case WlanModulationStandardEnum::BG_CCK11:
			standard = WlanModulationStandardEnum::BG_CCK11;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::BG_CCK55:
			standard = WlanModulationStandardEnum::BG_CCK55;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::BG_DSSS1:
			standard = WlanModulationStandardEnum::BG_DSSS1;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::BG_DSSS2:
			standard = WlanModulationStandardEnum::BG_DSSS2;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::BG_PBCC11:
			standard = WlanModulationStandardEnum::BG_PBCC11;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::BG_PBCC55:
			standard = WlanModulationStandardEnum::BG_PBCC55;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::N20:
			standard = WlanModulationStandardEnum::N20;
			wlan[testSite] = wlan_abgn[testSite];
			break;

		case WlanModulationStandardEnum::N40:
			standard = WlanModulationStandardEnum::N40;
			wlan[testSite] = wlan_abgn[testSite];
			break;
		}
	}

	//EVM 
	void AMB7600SRTestLibrary::RF_WlanEvmMeasurementSetup(int testSite, WlanModulationStandardEnum standard, bool setWlanSettings, Dictionary<int, Object^>^ wlanSettings)
	{
		wlan[testSite]->ConfigureEvm(standard);

		if (setWlanSettings == true)
		{
			RF_WlanEvmSettingConfig(testSite, wlanSettings);
		}

	}
	void AMB7600SRTestLibrary::RF_WlanEvmSettingConfig(int testSite, Dictionary<int, Object^>^ wlanSettings)
	{
		IWlanSettingFactory ^ setting = (IWlanSettingFactory ^)wlan[testSite]->WlanSetting;

		for each(int i in wlanSettings->Keys)
		{
			switch (i)
			{
			case wlanEvmSetting_APP::AcqTime:
				setting->ModulationSetting->Evm->AcqTime = (double)wlanSettings[i];
				break;
			case wlanEvmSetting_APP::mcsIndex:
				setting->ModulationSetting->Evm->mcsIndex = (int)wlanSettings[i];
				break;
			case wlanEvmSetting_APP::viewConstellation:
				setting->ModulationSetting->Evm->viewConstellation = (int)wlanSettings[i];
				break;
			case wlanEvmSetting_APP::PSDULength:
				setting->ModulationSetting->Evm->PSDULength = (int)wlanSettings[i];
				break;
			case wlanEvmSetting_APP::autoConfigSetup:
				setting->ModulationSetting->Evm->autoConfigSetup = (int)wlanSettings[i];
				break;
			}
		}

		wlan[testSite]->ConfigureEvm((IWlanSettingFactory ^)setting);
	}
	void AMB7600SRTestLibrary::RF_WlanEvmSettingVariable(String^ controlMethod, int settingSelection, DataType % var)
	{
		String^ ErrorMessage = nullptr;

		switch (settingSelection)
		{
		case wlanEvmSetting_APP::AcqTime:
			var = DataType::Double;
			break;
		case wlanEvmSetting_APP::viewConstellation:
			var = DataType::Int32;
			break;
		case wlanEvmSetting_APP::mcsIndex:
			var = DataType::Int32;
			break;
		case wlanEvmSetting_APP::PSDULength:
			var = DataType::Int32;
			break;
		case wlanEvmSetting_APP::autoConfigSetup:
			var = DataType::Int32;
			break;
		default:
			ErrorMessage = "Test Condition [" + controlMethod + "Setting_" + settingSelection.ToString() + " ] is not supported.";
			throw gcnew Exception(ErrorMessage);
		}
	}

	//SEM
	void AMB7600SRTestLibrary::RF_WlanSemMeasurementSetup(int testSite, WlanModulationStandardEnum standard, bool setWlanSettings,int semAvg , Dictionary<int, Object^>^ wlanSettings)
	{
		wlan[testSite]->ConfigureSem(standard, semAvg);

		if (setWlanSettings == true)
		{
			RF_WlanSemSettingConfig(testSite, semAvg, wlanSettings);
		}

	}
	void AMB7600SRTestLibrary::RF_WlanSemSettingConfig(int testSite, int semAvg, Dictionary<int, Object^>^ wlanSettings)
	{
		IWlanSettingFactory ^ setting = (IWlanSettingFactory ^)wlan[testSite]->WlanSetting;

		for each(int i in wlanSettings->Keys)
		{
			switch (i)
			{
			case wlanSemSetting_APP::AcqTime:
				setting->ModulationSetting->Sem->AcqTime = (double)wlanSettings[i];
				break;
			case wlanSemSetting_APP::viewSpectrum:
				setting->ModulationSetting->Sem->viewSpectrum = (int)wlanSettings[i];
				break;
			}
		}

		wlan[testSite]->ConfigureSem((IWlanSettingFactory ^)setting, semAvg);

	}
	void AMB7600SRTestLibrary::RF_WlanSemSettingVariable(String^ controlMethod, int settingSelection, DataType % var)
	{
		String^ ErrorMessage = nullptr;

		switch (settingSelection)
		{
		case wlanSemSetting_APP::AcqTime:
			var = DataType::Double;
			break;
		case wlanSemSetting_APP::viewSpectrum:
			var = DataType::Int32;
			break;
		default:
			ErrorMessage = "Test Condition [" + controlMethod + "Setting_" + settingSelection.ToString() + " ] is not supported.";
			throw gcnew Exception(ErrorMessage);
		}
	}

	//Power Servo
	void AMB7600SRTestLibrary::RF_WlanConfigurePowerServo(int testSite, bool servoEnable, WlanModulationStandardEnum standard, double sourcePower, double targetPower, double targetPowerMargin)
	{
		wlan[testSite]->ConfigurePowerServo(servoEnable, standard, sourcePower, targetPower, targetPowerMargin);
	}
	void AMB7600SRTestLibrary::RF_WlanRunPowerServo(int testSite)
	{
		wlan[testSite]->RunPowerServo();
	}
	void AMB7600SRTestLibrary::RF_WlanReadPowerServo(int testSite, double % outputPower, double % sourcePower, bool % servoPass, int % servoCount)
	{
		wlan[testSite]->ReadPowerServo(outputPower, sourcePower, servoPass, servoCount);
	}

	//Get Result
	void AMB7600SRTestLibrary::RF_WlanEvmMeasurementReadEvm(int testSite, double % result)
	{
		wlan[testSite]->ReadEvm(result);
	}
	void AMB7600SRTestLibrary::RF_WlanEvmMeasurementReadEvmAsync(int testSite, String^ testItemName, String^ testParaName)
	{
		tl->glob->EvmAysncTask[testSite]["//TI:" + testItemName + "//TP:" + testParaName] = wlan[testSite]->ReadEvmAsync();
	}
	void AMB7600SRTestLibrary::RF_WlanSemMeasurementReadSem(int testSite,double % peakRefPower, array<double>^ % semData, array<double>^ % margindata, int % status)
	{
		wlan[testSite]->ReadSem(peakRefPower, semData, margindata, status);
	}
	void AMB7600SRTestLibrary::RF_WlanSemMeasurementReadSemAsync(int testSite, String^ testItemName, String^ testParaName)
	{
		tl->glob->SemAysncTask[testSite]["//TI:" + testItemName + "//TP:" + testParaName] = wlan[testSite]->ReadSemAsync();
	}

	//Checking Wlan Task List
	void AMB7600SRTestLibrary::RF_CheckingTestMethodSemAsyncExist(Site ^ site)
	{
		FlowItemCollection ^ flowItems = gcnew FlowItemCollection();
		TestParameterCollection ^ TPtestCollection = gcnew TestParameterCollection();
		ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
		ConditionCollection ^ test_ResultDisplayConditionCollection = gcnew ConditionCollection();

		String^ testItemName = String::Empty;
		String^ testParaName = String::Empty;
		String^ dic_testItem_testPara_Name = String::Empty;
		String^ conditionValue = String::Empty;

		flowItems = site->FlowItems;
		tl->glob->SemAysncTask->Clear;

		tl->glob->ResultDisplaySemAsync = gcnew Dictionary<String^, array<String^>^>();
		tl->glob->ResultSemAsync = gcnew array<Dictionary<String^, Object^>^>(tl->glob->tf.NumberOfSites);

		array<String^>^TiTpTc = nullptr;
		List<String^>^TiTpTc_List = gcnew List<String^>();
		String^ resultDisplayValue = String::Empty;
		String^ resultDisplayItem = String::Empty;
		bool ExistResultDisplay = false;

		for each (AFlowItem ^ flowItemInfo in flowItems)
		{
			if (flowItemInfo->GetType() == TestItem::typeid)
			{
				TPtestCollection = ((TestItem^)flowItemInfo)->TestParameters;

				for each (TestParameter ^ TPInfo in TPtestCollection)
				{
					testConditionCollection = TPInfo->Conditions;

					for each (Condition ^ testCondition in testConditionCollection)
					{
						if (testCondition->Name == "TestMethod")
						{
							conditionValue = String::Empty;
							testItemName = String::Empty;
							testParaName = String::Empty;
							dic_testItem_testPara_Name = String::Empty;
							TiTpTc_List->Clear();
							conditionValue = (String^)TPInfo->Conditions[testCondition->Name][site]->Value;
							ExistResultDisplay = false;

							if (conditionValue->Contains("RFCase_ReadSemAsync"))
							{
								testItemName = flowItemInfo->Name;
								testParaName = TPInfo->Name;
								dic_testItem_testPara_Name = "//TI:" + testItemName + "//TP:" + testParaName;

								//Store in dictionary for those test parameter that perform EvmAsync
								for (int testSite = 0; testSite < tl->glob->tf.NumberOfSites; testSite++)
								{
									tl->glob->SemAysncTask[testSite]->Add(dic_testItem_testPara_Name, nullptr);
								}

								//Finding other Test Parameters' Result Display on SemAsync
								for each (TestParameter ^ TP_ResultDisplayInfo in TPtestCollection)
								{
									test_ResultDisplayConditionCollection = TP_ResultDisplayInfo->Conditions;

									for each (Condition ^ test_ResultDisplay in test_ResultDisplayConditionCollection)
									{
										if (TP_ResultDisplayInfo->Name == TPInfo->Name && test_ResultDisplay->Name == "ResultDisplay")
										{
											resultDisplayValue = (String^)TP_ResultDisplayInfo->Conditions[test_ResultDisplay->Name][site]->Value;
											resultDisplayItem = "//TI:" + testItemName + "//TP:" + TP_ResultDisplayInfo->Name + "//TC:" + resultDisplayValue;

											if (!TiTpTc_List->Contains(resultDisplayItem))
											{
												TiTpTc_List->Add(resultDisplayItem);
												ExistResultDisplay = true;
												break;
											}
										}

										if (ExistResultDisplay == true && !(TP_ResultDisplayInfo->Conditions->ContainsKey("TestMethod")) && test_ResultDisplay->Name == "ResultDisplay")
										{
											resultDisplayValue = (String^)TP_ResultDisplayInfo->Conditions[test_ResultDisplay->Name][site]->Value;
											resultDisplayItem = "//TI:" + testItemName + "//TP:" + TP_ResultDisplayInfo->Name + "//TC:" + resultDisplayValue;

											if (!TiTpTc_List->Contains(resultDisplayItem))
											{
												TiTpTc_List->Add("//TI:" + testItemName + "//TP:" + TP_ResultDisplayInfo->Name + "//TC:" + resultDisplayValue);
											}
											else
											{
												//Error
											}
										}
									}
								}
								TiTpTc = gcnew array<String^>(TiTpTc_List->Count);

								for (int i = 0; i < TiTpTc_List->Count; i++)
								{
									TiTpTc[i] = TiTpTc_List[i];
								}

								tl->glob->ResultDisplaySemAsync->Add(dic_testItem_testPara_Name, TiTpTc);
							}
						}
					}
				}

				for (int testSite = 0; testSite < tl->glob->tf.NumberOfSites; testSite++)
				{
					if (tl->glob->SemAysncTask[testSite]->Count > 0)
					{
						tl->glob->ExistSemTaskList[testSite] = true;
					}
				}
			}
		}

	}
	void AMB7600SRTestLibrary::RF_CheckingTestMethodEvmAsyncExist(Site ^ site)
	{
		FlowItemCollection ^ flowItems = gcnew FlowItemCollection();
		TestParameterCollection ^ TPtestCollection = gcnew TestParameterCollection();
		ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();

		String^ testItemName = String::Empty;
		String^ testParaName = String::Empty;
		String^ dic_testItem_testPara_Name = String::Empty;
		String^ conditionValue = String::Empty;

		flowItems = site->FlowItems;
		tl->glob->EvmAysncTask->Clear;

		for each (AFlowItem ^ flowItemInfo in flowItems)
		{
			if (flowItemInfo->GetType() == TestItem::typeid)
			{
				TPtestCollection = ((TestItem^)flowItemInfo)->TestParameters;

				for each (TestParameter ^ TPInfo in TPtestCollection)
				{
					testConditionCollection = TPInfo->Conditions;

					for each (Condition ^ testCondition in testConditionCollection)
					{
						if (testCondition->Name == "TestMethod")
						{
							conditionValue = String::Empty;
							testItemName = String::Empty;
							testParaName = String::Empty;
							dic_testItem_testPara_Name = String::Empty;

							conditionValue = (String^)TPInfo->Conditions[testCondition->Name][site]->Value;

							if (conditionValue->Contains("RFCase_ReadEvmAsync"))
							{
								testItemName = flowItemInfo->Name;
								testParaName = TPInfo->Name;
								dic_testItem_testPara_Name = "//TI:" + testItemName + "//TP:" + testParaName;

								//Store in dictionary for those test parameter that perform EvmAsync
								for (int testSite = 0; testSite < tl->glob->tf.NumberOfSites; testSite++)
								{
									tl->glob->EvmAysncTask[testSite]->Add(dic_testItem_testPara_Name, nullptr);
								}
							}
						}
					}
				}

				for (int testSite = 0; testSite < tl->glob->tf.NumberOfSites; testSite++)
				{
					if (tl->glob->EvmAysncTask[testSite]->Count > 0)
					{
						tl->glob->ExistEvmTaskList[testSite] = true;
					}
				}
			}
		}

	}

	//Cast Result to TechFlow
	void AMB7600SRTestLibrary::RF_EvmAsyncCastResultToTechFlow(Site ^ site, int testSite)
	{
		String^ testItemName = String::Empty;
		String^ testParaName = String::Empty;
		array <String^>^ keyInfo = gcnew array<String^>(2);
		array<String^>^ separators = { "//TI:", "//TP:" };
		array<String^>^ TestName = nullptr;
		double result = 0.0;
		int index = 0;
		int TestNameIndex = 0;

		if (tl->glob->ExistEvmTaskList[testSite] == true)
		{
			TestName = gcnew array<String^>(tl->glob->EvmAysncTask[testSite]->Count);
			index = 0;

			for each(KeyValuePair<String ^, Task<double>^> ^ TaskInfo in tl->glob->EvmAysncTask[testSite])
			{
				TestName[TestNameIndex] = TaskInfo->Key;

				if (TaskInfo->Value != nullptr)
				{
					index++;
				}

				TestNameIndex++;
			}

			tl->glob->EvmAsyncInfoCastResultToTF[testSite].testParaCount = index;
			tl->glob->EvmAsyncInfoCastResultToTF[testSite].testItemName = gcnew array<String^>(tl->glob->EvmAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->EvmAsyncInfoCastResultToTF[testSite].testParaName = gcnew array<String^>(tl->glob->EvmAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->EvmAsyncInfoCastResultToTF[testSite].result = gcnew array<double>(tl->glob->EvmAsyncInfoCastResultToTF[testSite].testParaCount);

			index = 0;

			for each(KeyValuePair<String ^, Task<double>^> ^ TaskInfo in tl->glob->EvmAysncTask[testSite])
			{

				if (TaskInfo->Value != nullptr)
				{
					keyInfo = TaskInfo->Key->Split(separators, StringSplitOptions::RemoveEmptyEntries);


					tl->glob->EvmAsyncInfoCastResultToTF[testSite].testItemName[index] = keyInfo[0];
					tl->glob->EvmAsyncInfoCastResultToTF[testSite].testParaName[index] = keyInfo[1];

					tl->glob->EvmAsyncInfoCastResultToTF[testSite].result[index] = TaskInfo->Value->Result;

					index++;
				}
			}

			for (int i = 0; i < tl->glob->EvmAysncTask[testSite]->Count; i++)
			{
				//Reset the value to be nullptr
				if (tl->glob->EvmAysncTask[testSite][TestName[i]] != nullptr)
				{
					tl->glob->EvmAysncTask[testSite][TestName[i]] = nullptr;
				}
			}
		}


	}
	void AMB7600SRTestLibrary::RF_SemAsyncCastResultToTechFlow(Site ^ site, int testSite)
	{
		String^ testItemName = String::Empty;
		String^ testParaName = String::Empty;
		array <String^>^ keyInfo = gcnew array<String^>(2);
		array<String^>^ separators = { "//TI:", "//TP:","//TC:" };
		array<String^>^ separators_ResultDisplay = { "_" };

		array<String^>^ TestName = nullptr;
		double result = 0.0;
		int index = 0;
		int TestNameIndex = 0;
		int ResultCount = 0;

		array <String^>^ resultSplitInfo = gcnew array<String^>(2);
		int resultSplitInfoIndex = 0;

		if (tl->glob->ExistSemTaskList[testSite] == true)
		{
			TestName = gcnew array<String^>(tl->glob->SemAysncTask[testSite]->Count);
			index = 0;

			for each(KeyValuePair<String ^, Task<SemMeasOutput^>^> ^ TaskInfo in tl->glob->SemAysncTask[testSite])
			{
				TestName[TestNameIndex] = TaskInfo->Key;

				if (TaskInfo->Value != nullptr)
				{
					index++;
				}

				TestNameIndex++;
			}

			tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount = index;
			tl->glob->SemAsyncInfoCastResultToTF[testSite].testItemName = gcnew array<String^>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaName = gcnew array<array<String^>^>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->SemAsyncInfoCastResultToTF[testSite].result = gcnew array<array<Object^>^>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultMarginData = gcnew array<array<double>^>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultSemData = gcnew array<array<double>^>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultStatus = gcnew array<int>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);
			tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultPeakReferenceData = gcnew array<double>(tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaCount);


			index = 0;

			for each(KeyValuePair<String ^, Task<SemMeasOutput^>^> ^ TaskInfo in tl->glob->SemAysncTask[testSite])
			{

				if (TaskInfo->Value != nullptr)
				{
					keyInfo = TaskInfo->Key->Split(separators, StringSplitOptions::RemoveEmptyEntries);

					tl->glob->SemAsyncInfoCastResultToTF[testSite].testItemName[index] = keyInfo[0];
					tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaName[index] = gcnew array<String^>(tl->glob->ResultDisplaySemAsync[TaskInfo->Key]->Length);
					tl->glob->SemAsyncInfoCastResultToTF[testSite].result[index] = gcnew array<Object^>(tl->glob->ResultDisplaySemAsync[TaskInfo->Key]->Length);

					//Result
					tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultMarginData[index] = TaskInfo->Value->Result->marginData;
					tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultSemData[index] = TaskInfo->Value->Result->semData;
					tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultPeakReferenceData[index] = TaskInfo->Value->Result->PeakRefPower;
					tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultStatus[index] = TaskInfo->Value->Result->Status;

					ResultCount = 0;

					for each(String^ ResultDisplayInfo in tl->glob->ResultDisplaySemAsync[TaskInfo->Key])
					{
						keyInfo = ResultDisplayInfo->Split(separators, StringSplitOptions::RemoveEmptyEntries);

						if (keyInfo[2] == "PeakRefPower")
						{
							tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaName[index][ResultCount] = keyInfo[1];
							tl->glob->SemAsyncInfoCastResultToTF[testSite].result[index][ResultCount] = tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultPeakReferenceData[index];
						}
						else if (keyInfo[2] == "Status")
						{
							tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaName[index][ResultCount] = keyInfo[1];
							tl->glob->SemAsyncInfoCastResultToTF[testSite].result[index][ResultCount] = tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultStatus[index];
						}
						else if (keyInfo[2]->Contains("SemData"))
						{
							resultSplitInfo = keyInfo[2]->Split(separators_ResultDisplay, StringSplitOptions::RemoveEmptyEntries);
							resultSplitInfoIndex = (int)Convert::ToInt32(resultSplitInfo[1]);

							tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaName[index][ResultCount] = keyInfo[1];
							tl->glob->SemAsyncInfoCastResultToTF[testSite].result[index][ResultCount] = tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultSemData[index][resultSplitInfoIndex];

						}
						else if (keyInfo[2]->Contains("MarginData"))
						{
							resultSplitInfo = keyInfo[2]->Split(separators_ResultDisplay, StringSplitOptions::RemoveEmptyEntries);
							resultSplitInfoIndex = (int)Convert::ToInt32(resultSplitInfo[1]);

							tl->glob->SemAsyncInfoCastResultToTF[testSite].testParaName[index][ResultCount] = keyInfo[1];
							tl->glob->SemAsyncInfoCastResultToTF[testSite].result[index][ResultCount] = tl->glob->SemAsyncInfoCastResultToTF[testSite].ResultMarginData[index][resultSplitInfoIndex];
						}
						ResultCount++;

					}

					index++;
				}
			}

			for (int i = 0; i < tl->glob->SemAysncTask[testSite]->Count; i++)
			{
				//Reset the value to be nullptr
				if (tl->glob->SemAysncTask[testSite][TestName[i]] != nullptr)
				{
					tl->glob->SemAysncTask[testSite][TestName[i]] = nullptr;
				}
			}
		}


	}

#pragma endregion "WLAN"

#pragma region "Wolfer Done By Khin Leong & Harn Seng"
	//Wolfer
	double AMB7600SRTestLibrary::StrToDouble(String ^ str)
	{
		double value = 0.0;

		try
		{
			value = double::Parse(str);
		}
		catch (Exception ^)
		{
			value = 0.0;
		}

		return value;
	}
	int AMB7600SRTestLibrary::StrToInt(String ^ str)
	{
		int value = 0;

		try
		{
			value = int::Parse(str);
		}
		catch (Exception ^)
		{
			value = 0;
		}

		return value;
	}
	int AMB7600SRTestLibrary::ReadFreqCalList(int testSite, String^ wolferType, int %freq_count)
	{
		int ret = 0;

		int arraySize = 256;

		StringBuilder ^ sbw = gcnew StringBuilder();

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].freqcalFile[wolferType]))
		{
			sbw->AppendLine(tl->glob->WolferInfo_Status[testSite].freqcalFile[wolferType] + " not found.");
			MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return 0;
		}

		//freqcal_freq = gcnew array<double>(arraySize);
		//freqcal_pout = gcnew array<double>(arraySize);

		tl->glob->freqcal_freq->Add(wolferType, gcnew array<double>(arraySize));
		tl->glob->freqcal_pout->Add(wolferType, gcnew array<double>(arraySize));


		int freqcal_count = 0;
		String ^ line = String::Empty;
		array<String ^> ^ ArrStr = gcnew array<String ^>(0);
		array<String ^> ^ Separator = gcnew array<String ^>(1);
		Separator[0] = ",";

		StreamReader ^ sr = gcnew StreamReader(tl->glob->WolferInfo_Status[testSite].freqcalFile[wolferType]);
		while ((line = sr->ReadLine()) != nullptr)
		{
			if (line->StartsWith("//") == false)
			{
				ArrStr = line->Split(Separator, StringSplitOptions::None);

				if (ArrStr->Length == 2)
				{
					//freqcal_freq[freqcal_count] = StrToDouble(ArrStr[0]);
					//freqcal_pout[freqcal_count] = StrToDouble(ArrStr[1]);

					tl->glob->freqcal_freq[wolferType][freqcal_count] = StrToDouble(ArrStr[0]);
					tl->glob->freqcal_pout[wolferType][freqcal_count] = StrToDouble(ArrStr[1]);


				}

				freqcal_count++;

				if (freqcal_count > 256)
				{
					sbw->AppendLine("The number of freq cal points has exceeded 256");
					MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return 0;
				}
			}
		}

		sr->Close();
		sr = nullptr;

		freq_count = freqcal_count;

		return ret;

	}
	int AMB7600SRTestLibrary::ReadFreqHarList(int testSite, String^ wolferType, int %freq_count)
	{
		int ret = 0;

		int arraySize = 256;

		StringBuilder ^ sbw = gcnew StringBuilder();

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].freqHarcalFile[wolferType]))
		{
			sbw->AppendLine(tl->glob->WolferInfo_Status[testSite].freqHarcalFile[wolferType] + " not found.");
			MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return 0;
		}

		//freqHarcal_freq = gcnew array<double>(arraySize);
		//freqHarcal_pout = gcnew array<double>(arraySize);

		tl->glob->freqHarcal_freq->Add(wolferType, gcnew array<double>(arraySize));


		int freqHar_count = 0;
		String ^ line = String::Empty;
		array<String ^> ^ ArrStr = gcnew array<String ^>(0);
		array<String ^> ^ Separator = gcnew array<String ^>(1);
		Separator[0] = ",";

		StreamReader ^ sr = gcnew StreamReader(tl->glob->WolferInfo_Status[testSite].freqHarcalFile[wolferType]);
		while ((line = sr->ReadLine()) != nullptr)
		{
			if (line->StartsWith("//") == false)
			{
				ArrStr = line->Split(Separator, StringSplitOptions::None);

				if (ArrStr->Length == 1)
				{
					//freqHarcal_freq[freqHar_count] = StrToDouble(ArrStr[0]);
					////freqHarcal_pout[freqHar_count] = StrToDouble(ArrStr[1]);

					tl->glob->freqHarcal_freq[wolferType][freqHar_count] = StrToDouble(ArrStr[0]);
				}

				freqHar_count++;

				if (freqHar_count > 256)
				{
					sbw->AppendLine("The number of freq cal points has exceeded 256");
					MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return 0;
				}
			}
		}

		sr->Close();
		sr = nullptr;

		freq_count = freqHar_count;

		return ret;

	}
	int AMB7600SRTestLibrary::ReadTxPathLoss(int testSite, String^ wolferType, int %txpl_Count)
	{
		int ret = 0;

		StringBuilder ^ sbw = gcnew StringBuilder();

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].txplFile[wolferType]))
		{
			sbw->AppendLine(tl->glob->WolferInfo_Status[testSite].txplFile[wolferType] + " not found.");
			MessageBox::Show(sbw->ToString(), "AMSRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return 0;
		}

		int txFactorCount = 0;

		GetFactorCountFromFile(tl->glob->WolferInfo_Status[testSite].txplFile[wolferType], txFactorCount);

		//txPathLoss_TXpath = gcnew array<int>(txFactorCount);
		//txPathLoss_freq = gcnew array<double>(txFactorCount);
		//txPathLoss_targetpout = gcnew array<double>(txFactorCount);
		//txPathLoss_outIndex = gcnew array<int>(txFactorCount);
		//txPathLoss_actualpout = gcnew array<double>(txFactorCount);
		//txPathLoss_couppout = gcnew array<double>(txFactorCount);
		//txPathLoss_source = gcnew array<double>(txFactorCount);

		tl->glob->txPathLoss_TXpath->Add(wolferType, gcnew array<int>(txFactorCount));
		tl->glob->txPathLoss_freq->Add(wolferType, gcnew array<double>(txFactorCount));
		tl->glob->txPathLoss_targetpout->Add(wolferType, gcnew array<double>(txFactorCount));
		tl->glob->txPathLoss_outIndex->Add(wolferType, gcnew array<int>(txFactorCount));
		tl->glob->txPathLoss_actualpout->Add(wolferType, gcnew array<double>(txFactorCount));
		tl->glob->txPathLoss_couppout->Add(wolferType, gcnew array<double>(txFactorCount));
		tl->glob->txPathLoss_source->Add(wolferType, gcnew array<double>(txFactorCount));

		int corrfactor_count = 0;
		String ^ line = String::Empty;
		array<String ^> ^ ArrStr = gcnew array<String ^>(0);
		array<String ^> ^ Separator = gcnew array<String ^>(1);
		Separator[0] = ",";



		StreamReader ^ sr = gcnew StreamReader(tl->glob->WolferInfo_Status[testSite].txplFile[wolferType]);
		while ((line = sr->ReadLine()) != nullptr)
		{
			if (line->StartsWith("//") == false)
			{
				ArrStr = line->Split(Separator, StringSplitOptions::None);

				if (ArrStr->Length == 7)
				{
					util->StringToInteger(ArrStr[0], tl->glob->txPathLoss_outIndex[wolferType][corrfactor_count]);
					util->StringToInteger(ArrStr[1], tl->glob->txPathLoss_TXpath[wolferType][corrfactor_count]);
					util->StringToDouble(ArrStr[2], tl->glob->txPathLoss_freq[wolferType][corrfactor_count]);
					util->StringToDouble(ArrStr[3], tl->glob->txPathLoss_targetpout[wolferType][corrfactor_count]);
					util->StringToDouble(ArrStr[4], tl->glob->txPathLoss_actualpout[wolferType][corrfactor_count]);
					util->StringToDouble(ArrStr[5], tl->glob->txPathLoss_couppout[wolferType][corrfactor_count]);
					util->StringToDouble(ArrStr[6], tl->glob->txPathLoss_source[wolferType][corrfactor_count]);
				}
				else
				{
					util->PrintConsole("Wrong tx pathloss file format!");
				}

				corrfactor_count++;
			}
		}

		sr->Close();
		sr = nullptr;

		txpl_Count = corrfactor_count;

		return ret;

	}
	int AMB7600SRTestLibrary::ReadRxPathLoss(int testSite, String^ wolferType, int %rxpl_count)
	{
		int ret = 0;

		int arraySize = 256;

		StringBuilder ^ sbw = gcnew StringBuilder();

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].rxplFile[wolferType]))
		{
			sbw->AppendLine(tl->glob->WolferInfo_Status[testSite].rxplFile[wolferType] + " not found.");
			MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return 0;
		}

		rxpl_TXPath = gcnew array<int>(arraySize);
		rxpl_freq = gcnew array<double>(arraySize);
		rxpl_pout = gcnew array<double>(arraySize);
		rxpl_p1 = gcnew array<double>(arraySize);
		rxpl_p2 = gcnew array<double>(arraySize);
		rxpl_p3 = gcnew array<double>(arraySize);
		rxpl_p4 = gcnew array<double>(arraySize);
		rxpl_p5 = gcnew array<double>(arraySize);
		rxpl_p6 = gcnew array<double>(arraySize);
		rxpl_p7 = gcnew array<double>(arraySize);
		rxpl_p8 = gcnew array<double>(arraySize);
		rxpl_p9 = gcnew array<double>(arraySize);
		rxpl_p10 = gcnew array<double>(arraySize);
		rxpl_p11 = gcnew array<double>(arraySize);
		rxpl_p12 = gcnew array<double>(arraySize);
		rxpl_p13 = gcnew array<double>(arraySize);
		rxpl_p14 = gcnew array<double>(arraySize);
		rxpl_p15 = gcnew array<double>(arraySize);
		rxpl_p16 = gcnew array<double>(arraySize);
		rxpl_p17 = gcnew array<double>(arraySize);
		rxpl_p18 = gcnew array<double>(arraySize);
		rxpl_p19 = gcnew array<double>(arraySize);
		rxpl_p20 = gcnew array<double>(arraySize);
		rxpl_p21 = gcnew array<double>(arraySize);
		rxpl_p22 = gcnew array<double>(arraySize);
		rxpl_p23 = gcnew array<double>(arraySize);
		rxpl_p24 = gcnew array<double>(arraySize);

		int rx_pl_count = 0;
		String ^ line = String::Empty;
		array<String ^> ^ ArrStr = gcnew array<String ^>(0);
		array<String ^> ^ Separator = gcnew array<String ^>(1);
		Separator[0] = ",";

		StreamReader ^ sr = gcnew StreamReader(tl->glob->WolferInfo_Status[testSite].rxplFile[wolferType]);
		while ((line = sr->ReadLine()) != nullptr)
		{
			if (line->StartsWith("//") == false)
			{
				ArrStr = line->Split(Separator, StringSplitOptions::None);

				//if (ArrStr->Length == 26)
				{
					rxpl_TXPath[rx_pl_count] = StrToInt(ArrStr[0]);
					rxpl_freq[rx_pl_count] = StrToDouble(ArrStr[1]);
					rxpl_pout[rx_pl_count] = StrToDouble(ArrStr[2]);
					rxpl_p1[rx_pl_count] = StrToDouble(ArrStr[3]);
					rxpl_p2[rx_pl_count] = StrToDouble(ArrStr[4]);
					rxpl_p3[rx_pl_count] = StrToDouble(ArrStr[5]);
					rxpl_p4[rx_pl_count] = StrToDouble(ArrStr[6]);
					rxpl_p5[rx_pl_count] = StrToDouble(ArrStr[7]);
					rxpl_p6[rx_pl_count] = StrToDouble(ArrStr[8]);
					rxpl_p7[rx_pl_count] = StrToDouble(ArrStr[9]);
					rxpl_p8[rx_pl_count] = StrToDouble(ArrStr[10]);
					rxpl_p9[rx_pl_count] = StrToDouble(ArrStr[11]);
					rxpl_p10[rx_pl_count] = StrToDouble(ArrStr[12]);
					rxpl_p11[rx_pl_count] = StrToDouble(ArrStr[13]);
					rxpl_p12[rx_pl_count] = StrToDouble(ArrStr[14]);
					rxpl_p13[rx_pl_count] = StrToDouble(ArrStr[15]);
					rxpl_p14[rx_pl_count] = StrToDouble(ArrStr[16]);
					rxpl_p15[rx_pl_count] = StrToDouble(ArrStr[17]);
					rxpl_p16[rx_pl_count] = StrToDouble(ArrStr[18]);
					rxpl_p17[rx_pl_count] = StrToDouble(ArrStr[19]);
					rxpl_p18[rx_pl_count] = StrToDouble(ArrStr[20]);
					rxpl_p19[rx_pl_count] = StrToDouble(ArrStr[21]);
					rxpl_p20[rx_pl_count] = StrToDouble(ArrStr[22]);
					rxpl_p21[rx_pl_count] = StrToDouble(ArrStr[23]);
					rxpl_p22[rx_pl_count] = StrToDouble(ArrStr[24]);
					rxpl_p23[rx_pl_count] = StrToDouble(ArrStr[25]);
					rxpl_p24[rx_pl_count] = StrToDouble(ArrStr[26]);
				}
				//else
				//{
				//	throw gcnew Aemulus::Hardware::AlarmException("Wrong rx_pathloss.txt format!", -1);
				//}

				rx_pl_count++;

				if (rx_pl_count > arraySize)
				{
					sbw->AppendLine("The number of rx path loss cal points has exceeded 256");
					MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return 0;
				}
			}
		}

		sr->Close();
		sr = nullptr;

		rxpl_count = rx_pl_count;

		return ret;
	}
	int AMB7600SRTestLibrary::GetFactorCountFromFile(String^ filePath, int % factorCount)
	{
		int ret = 0;

		try
		{
			StreamReader ^ sr = gcnew StreamReader(filePath);
			String^ line;
			factorCount = 0;

			while ((line = sr->ReadLine()) != nullptr)
			{
				if (!(line->StartsWith("//")))
				{
					factorCount++;
				}
			}
		}
		catch (Exception ^ ex)
		{
			util->PrintConsole(ex->StackTrace);
			return -1;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::wlfInit(int testSite, String^ moduleAlias)
	{
		int ret = 0;

		ret += dio[testSite]->ResetPort("DIO_PORT0");	// 1 port = 8 pins
		ret += dio[testSite]->ResetPort("DIO_PORT1");
		ret += dio[testSite]->ResetPort("DIO_PORT2");
		ret += dio[testSite]->ResetPort("DIO_PORT3");
		ret += dio[testSite]->ResetPort("DIO_PORT4");
		DIO_SetVIO(testSite, moduleAlias, 1);		//5V
		DIO_SetPortDirection(testSite, "DIO_PORT0", 1); // 1 output. 0 input
		DIO_SetPortDirection(testSite, "DIO_PORT1", 1);
		DIO_SetPortDirection(testSite, "DIO_PORT2", 1);
		DIO_SetPortDirection(testSite, "DIO_PORT3", 1);
		DIO_SetPortDirection(testSite, "DIO_PORT4", 1);
		ret += dio[testSite]->PowerOnOff(moduleAlias, 0, 0); // turn off 5V, turn off 12V
		DIO_DrivePort(testSite, "DIO_PORT0", 0); // 0 driving low, 1 driving high
		DIO_DrivePort(testSite, "DIO_PORT1", 0);
		DIO_DrivePort(testSite, "DIO_PORT2", 0);
		DIO_DrivePort(testSite, "DIO_PORT3", 0);
		DIO_DrivePort(testSite, "DIO_PORT4", 0);

		return ret;
	}
	int AMB7600SRTestLibrary::wlfTxPath(int testSite, int tx_sw)
	{
		int ret = 0;

		ret += dio[testSite]->DrivePin("DIO0", diosw0[tx_sw]);
		ret += dio[testSite]->DrivePin("DIO1", diosw1[tx_sw]);
		ret += dio[testSite]->DrivePin("DIO2", diosw2[tx_sw]);
		ret += dio[testSite]->DrivePin("DIO3", diosw3[tx_sw]);
		ret += dio[testSite]->DrivePin("DIO4", diosw4[tx_sw]);
		ret += dio[testSite]->DrivePin("DIO35", diosw35[tx_sw]);	//Version D
		ret += dio[testSite]->DrivePin("DIO36", diosw36[tx_sw]);	//Version D

																	//util->WaitSecond(0.025);

		return ret;
	}
	int AMB7600SRTestLibrary::wlfRxPath(int testSite, int rx_sw)
	{
		int ret = 0;

		int rx_sw_offset = rx_sw + 4;	//Version D

		if (rx_sw > 11)
		{
			ret += dio[testSite]->DrivePin("DIO20", diosw20[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO21", diosw21[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO22", diosw22[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO23", diosw23[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO24", diosw24[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO25", diosw25[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO26", diosw26[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO27", diosw27[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO28", diosw28[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO29", diosw29[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO30", diosw30[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO31", diosw31[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO32", diosw32[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO33", diosw33[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO34", diosw34[rx_sw_offset]);
		}
		else
		{
			ret += dio[testSite]->DrivePin("DIO5", diosw5[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO6", diosw6[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO7", diosw7[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO8", diosw8[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO9", diosw9[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO10", diosw10[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO11", diosw11[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO12", diosw12[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO13", diosw13[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO14", diosw14[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO15", diosw15[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO16", diosw16[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO17", diosw17[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO18", diosw18[rx_sw_offset]);
			ret += dio[testSite]->DrivePin("DIO19", diosw19[rx_sw_offset]);
		}

		//util->WaitSecond(0.025);

		return ret;
	}
	int AMB7600SRTestLibrary::wlfGetSwMatrix(int testSite, String ^ wolferType)
	{
		int ret = 0;

		if (wolferType == "C2")
		{
			int arraySize = 256;

			StringBuilder ^ sbw = gcnew StringBuilder();

			if (!File::Exists(tl->glob->WolferInfo_Status[testSite].wolferIOFile[wolferType]))
			{
				sbw->AppendLine(tl->glob->WolferInfo_Status[testSite].wolferIOFile[wolferType] + " not found.");
				MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return 0;
			}

			dioswname = gcnew array<String ^>(arraySize);
			diosw0 = gcnew array<int>(arraySize);
			diosw1 = gcnew array<int>(arraySize);
			diosw2 = gcnew array<int>(arraySize);
			diosw3 = gcnew array<int>(arraySize);
			diosw4 = gcnew array<int>(arraySize);
			diosw5 = gcnew array<int>(arraySize);
			diosw6 = gcnew array<int>(arraySize);
			diosw7 = gcnew array<int>(arraySize);
			diosw8 = gcnew array<int>(arraySize);
			diosw9 = gcnew array<int>(arraySize);
			diosw10 = gcnew array<int>(arraySize);
			diosw11 = gcnew array<int>(arraySize);
			diosw12 = gcnew array<int>(arraySize);
			diosw13 = gcnew array<int>(arraySize);
			diosw14 = gcnew array<int>(arraySize);
			diosw15 = gcnew array<int>(arraySize);
			diosw16 = gcnew array<int>(arraySize);
			diosw17 = gcnew array<int>(arraySize);
			diosw18 = gcnew array<int>(arraySize);
			diosw19 = gcnew array<int>(arraySize);
			diosw20 = gcnew array<int>(arraySize);
			diosw21 = gcnew array<int>(arraySize);
			diosw22 = gcnew array<int>(arraySize);
			diosw23 = gcnew array<int>(arraySize);
			diosw24 = gcnew array<int>(arraySize);
			diosw25 = gcnew array<int>(arraySize);
			diosw26 = gcnew array<int>(arraySize);
			diosw27 = gcnew array<int>(arraySize);
			diosw28 = gcnew array<int>(arraySize);
			diosw29 = gcnew array<int>(arraySize);
			diosw30 = gcnew array<int>(arraySize);
			diosw31 = gcnew array<int>(arraySize);
			diosw32 = gcnew array<int>(arraySize);
			diosw33 = gcnew array<int>(arraySize);
			diosw34 = gcnew array<int>(arraySize);
			diosw35 = gcnew array<int>(arraySize);	//Version D
			diosw36 = gcnew array<int>(arraySize);	//Version D
			dioswmode = gcnew array<String ^>(arraySize);

			array <int> ^ ary_buffdio = gcnew array<int>(arraySize);

			int diosw_count = 0;
			String ^ line = String::Empty;
			array<String ^> ^ ArrStr = gcnew array<String ^>(0);
			array<String ^> ^ Separator = gcnew array<String ^>(1);
			Separator[0] = ",";

			StreamReader ^ sr = gcnew StreamReader(tl->glob->WolferInfo_Status[testSite].wolferIOFile[wolferType]);
			while ((line = sr->ReadLine()) != nullptr)
			{
				if (line->StartsWith("//") == false)
				{
					ArrStr = line->Split(Separator, StringSplitOptions::None);

					if (ArrStr->Length == 38)	//Version D
					{
						dioswmode[diosw_count] = ArrStr[0];
						diosw0[diosw_count] = StrToInt(ArrStr[1]);
						diosw1[diosw_count] = StrToInt(ArrStr[2]);
						diosw2[diosw_count] = StrToInt(ArrStr[3]);
						diosw3[diosw_count] = StrToInt(ArrStr[4]);
						diosw4[diosw_count] = StrToInt(ArrStr[5]);
						diosw5[diosw_count] = StrToInt(ArrStr[6]);
						diosw6[diosw_count] = StrToInt(ArrStr[7]);
						diosw7[diosw_count] = StrToInt(ArrStr[8]);
						diosw8[diosw_count] = StrToInt(ArrStr[9]);
						diosw9[diosw_count] = StrToInt(ArrStr[10]);
						diosw10[diosw_count] = StrToInt(ArrStr[11]);
						diosw11[diosw_count] = StrToInt(ArrStr[12]);
						diosw12[diosw_count] = StrToInt(ArrStr[13]);
						diosw13[diosw_count] = StrToInt(ArrStr[14]);
						diosw14[diosw_count] = StrToInt(ArrStr[15]);
						diosw15[diosw_count] = StrToInt(ArrStr[16]);
						diosw16[diosw_count] = StrToInt(ArrStr[17]);
						diosw17[diosw_count] = StrToInt(ArrStr[18]);
						diosw18[diosw_count] = StrToInt(ArrStr[19]);
						diosw19[diosw_count] = StrToInt(ArrStr[20]);
						diosw20[diosw_count] = StrToInt(ArrStr[21]);
						diosw21[diosw_count] = StrToInt(ArrStr[22]);
						diosw22[diosw_count] = StrToInt(ArrStr[23]);
						diosw23[diosw_count] = StrToInt(ArrStr[24]);
						diosw24[diosw_count] = StrToInt(ArrStr[25]);
						diosw25[diosw_count] = StrToInt(ArrStr[26]);
						diosw26[diosw_count] = StrToInt(ArrStr[27]);
						diosw27[diosw_count] = StrToInt(ArrStr[28]);
						diosw28[diosw_count] = StrToInt(ArrStr[29]);
						diosw29[diosw_count] = StrToInt(ArrStr[30]);
						diosw30[diosw_count] = StrToInt(ArrStr[31]);
						diosw31[diosw_count] = StrToInt(ArrStr[32]);
						diosw32[diosw_count] = StrToInt(ArrStr[33]);
						diosw33[diosw_count] = StrToInt(ArrStr[34]);
						diosw34[diosw_count] = StrToInt(ArrStr[35]);
						diosw35[diosw_count] = StrToInt(ArrStr[35]);	//Version D
						diosw36[diosw_count] = StrToInt(ArrStr[36]);	//Version D
					}

					diosw_count++;

					if (diosw_count > arraySize)
					{
						sbw->AppendLine("The number of freq cal points has exceeded 256");
						MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						return 0;
					}
				}
			}

			sr->Close();
			sr = nullptr;
		}

		return ret;
	}
	long AMB7600SRTestLibrary::WlfSource(int testSite, String ^ wolferType, String ^ Source_CH, int wlfoutsw, int outIndex, int TXpath, double % freq, double % targetPout, double offset, double % actualSourceLevel)
	{
		int ret = 0;

		double sourceLevel = 0.0;
		double powerMaxLimit = 0.0;
		double powerMinLimit = 0.0;
		double coupledPout = 0.0;
		double coupRef = 0.0;
		double sourceLevelRef = 0.0;
		bool freqnotfound = 1;

		if (wlfoutsw == 0)
		{
			//ret += axrf->IsolateChannel(SourceCh);
		}
		else if (wlfoutsw == 1)
		{
			/*if (!File::Exists(corrfactorFile))
			{
			throw gcnew Aemulus::Hardware::AlarmException("File not found - " + corrfactorFile, -1);
			}*/

			for (int i = 0; i < tl->glob->txpl_count[wolferType]; i++)
			{
				if ((tl->glob->txPathLoss_freq[wolferType][i] == freq) && (tl->glob->txPathLoss_targetpout[wolferType][i] == targetPout) && (tl->glob->txPathLoss_TXpath[wolferType][i] == TXpath) && (tl->glob->txPathLoss_outIndex[wolferType][i] == outIndex))
				{
					coupRef = tl->glob->txPathLoss_couppout[wolferType][i];
					sourceLevelRef = tl->glob->txPathLoss_source[wolferType][i];
					actualSourceLevel = tl->glob->txPathLoss_actualpout[wolferType][i];
					freqnotfound = 0;
					break;
				}
			}

			//powerMaxLimit = AXRF_Driver::GetMaxPower(freq);
			//powerMinLimit = AXRF_Driver::GetMinPower();

			sourceLevel = sourceLevelRef;

			CheckError(testSite, amsrf[testSite]->amsrf->SourceChannel(Source_CH, sourceLevel + offset, freq));
			util->WaitSecond(0.0005);
			//ret += dio[testSite]->DrivePin("DIO0", 1);
		}

		return ret;

	}
	long AMB7600SRTestLibrary::WlfSource(int testSite, String ^ wolferType, String ^ Source_CH, int wlfoutsw, int outIndex, int TXpath, double % freq, double % targetPout, double offset, double sourceAttenuation, double % actualSourceLevel)
	{
		int ret = 0;

		double sourceLevel = 0.0;
		double powerMaxLimit = 0.0;
		double powerMinLimit = 0.0;
		double coupledPout = 0.0;
		double coupRef = 0.0;
		double sourceLevelRef = 0.0;
		bool freqnotfound = 1;

		if (wlfoutsw == 0)
		{
			//ret += axrf->IsolateChannel(SourceCh);
		}
		else if (wlfoutsw == 1)
		{
			/*if (!File::Exists(corrfactorFile))
			{
			throw gcnew Aemulus::Hardware::AlarmException("File not found - " + corrfactorFile, -1);
			}*/

			for (int i = 0; i < tl->glob->txpl_count[wolferType]; i++)
			{
				if ((tl->glob->txPathLoss_freq[wolferType][i] == freq) && (tl->glob->txPathLoss_targetpout[wolferType][i] == targetPout) && (tl->glob->txPathLoss_TXpath[wolferType][i] == TXpath) && (tl->glob->txPathLoss_outIndex[wolferType][i] == outIndex))
				{
					coupRef = tl->glob->txPathLoss_couppout[wolferType][i];              //9.60707
					sourceLevelRef = tl->glob->txPathLoss_source[wolferType][i];          //-4.45427
					actualSourceLevel = tl->glob->txPathLoss_actualpout[wolferType][i];   //35.021
					freqnotfound = 0;
					break;
				}
			}

			//powerMaxLimit = AXRF_Driver::GetMaxPower(freq);
			//powerMinLimit = AXRF_Driver::GetMinPower();

			sourceLevel = sourceLevelRef;          //-4.45427 dBm

												   //ret += dio[testSite]->DrivePin("DIO0", 0);

			CheckError(testSite, amsrf[testSite]->amsrf->SourceChannel(Source_CH, sourceLevel + offset, freq, sourceAttenuation));
			util->WaitSecond(0.0005);
			//ret += dio[testSite]->DrivePin("DIO0", 1);
		}

		return ret;

	}
	int AMB7600SRTestLibrary::wlfMonPath(int testSite, bool mon_sw)
	{
		int ret = 0;

		int monsw = 12;

		if (mon_sw)
		{
			ret += dio[testSite]->DrivePin("Ctrl_RxSw9", diosw9[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw8", diosw8[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw7", diosw7[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw6", diosw6[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw5", diosw5[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw4", diosw4[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw3", diosw3[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw2", diosw2[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw1", diosw1[monsw]);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw0", diosw0[monsw]);
		}
		else
		{
			ret += dio[testSite]->DrivePin("Ctrl_RxSw9", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw8", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw7", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw6", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw5", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw4", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw3", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw2", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw1", 0);
			ret += dio[testSite]->DrivePin("Ctrl_RxSw0", 0);
		}

		return ret;
	}
	long AMB7600SRTestLibrary::getRxPathLoss(int testSite, String^ wolferType, double %freq, double %sourceLevel, int TXpath, String ^ PIN, double %pathloss, String ^ type)
	{
		int ret = 0;

		//freq2H = 2 * freq;
		//freq3H = 3 * freq;

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].rxplFile[wolferType]))
		{
			throw gcnew Aemulus::Hardware::AlarmException("File not found - " + tl->glob->WolferInfo_Status[testSite].rxplFile[wolferType], -1);
		}

		if (type == "Bypass")//((freq <= 2.7e9) && (type == "Bypass"))
		{
			if ((pathloss == 0.0))
			{
				for (int i = 0; i <= tl->glob->rxpl_count[wolferType]; i++)
				{
					if ((rxpl_freq[i] == freq) && (rxpl_pout[i] == sourceLevel) && (rxpl_TXPath[i] == TXpath))
					{
						if (PIN == "RX1")
						{
							//MeasureCh = RFOutCh3;
							pathloss = rxpl_p1[i];
							break;
						}

						if (PIN == "RX2")
						{
							//MeasureCh = RFOutCh3;
							pathloss = rxpl_p4[i];
							break;
						}

						if (PIN == "RX3")
						{
							//MeasureCh = RFOutCh3;
							pathloss = rxpl_p7[i];
							break;
						}

						if (PIN == "RX4")
						{
							//MeasureCh = RFOutCh3;
							pathloss = rxpl_p10[i];
							break;
						}

						if (PIN == "RX5")
						{
							//MeasureCh = RFOutCh4;
							pathloss = rxpl_p13[i];
							break;
						}

						if (PIN == "RX6")
						{
							//MeasureCh = RFOutCh4;
							pathloss = rxpl_p16[i];
							break;
						}

						if (PIN == "RX7")
						{
							//MeasureCh = RFOutCh4;
							pathloss = rxpl_p19[i];
							break;
						}

						if (PIN == "RX8")
						{
							//MeasureCh = RFOutCh4;
							pathloss = rxpl_p22[i];
							break;
						}

					}
					else if ((i >= tl->glob->rxpl_count[wolferType]))
					{
						throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
					}
				}
			}
		}
		/*else
		{
		throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range",-1);
		}*/

		//else if ((freq2H >= 1.2e9) && (freq2H <= 3.5e9) && (type == "Har"))
		//{
		//	if ((pathloss == 0))
		//	{
		//		for (int i = 0; i <= tl->glob->rxrlpl_count[wolferType]; i++)
		//		{
		//			if ((rxrlpl_freq[i] == freq2H))// && (rxrlpl_pout[i]==sourceLevel))
		//			{
		//				if (PIN == "RF1")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p2[i];
		//					break;
		//				}
		//				if (PIN == "RF2")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p5[i];
		//					break;
		//				}
		//				if (PIN == "RF3")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p8[i];
		//					break;
		//				}
		//				if (PIN == "RF4")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p11[i];
		//					break;
		//				}
		//				if (PIN == "RF5")
		//				{
		//					//MeasureCh = RFOutCh4;//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p14[i];
		//					break;
		//				}
		//				if (PIN == "RF6")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p17[i];
		//					break;
		//				}
		//				if (PIN == "RF7")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p20[i];
		//					break;
		//				}
		//				if (PIN == "RF8")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p23[i];
		//					break;
		//				}
		//			}
		//			else if ((i >= tl->glob->rxrlpl_count[wolferType]))
		//			{
		//				throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
		//			}
		//		}
		//	}
		//}
		///*else
		//{
		//throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range",-1);
		//}*/
		//else if ((freq2H >= 3.5e9) && (freq2H <= 6e9) && (type == "Har"))
		//{
		//	if ((pathloss == 0))
		//	{
		//		for (int i = 0; i <= tl->glob->rxrlpl_count[wolferType]; i++)
		//		{
		//			if ((rxrlpl_freq[i] == freq2H))// && (rxrlpl_pout[i]==sourceLevel))
		//			{
		//				if (PIN == "RF1")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p3[i];
		//					break;
		//				}
		//				if (PIN == "RF2")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p6[i];
		//					break;
		//				}
		//				if (PIN == "RF3")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p9[i];
		//					break;
		//				}
		//				if (PIN == "RF4")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p12[i];
		//					break;
		//				}
		//				if (PIN == "RF5")
		//				{
		//					//MeasureCh = RFOutCh4; //MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p15[i];
		//					break;
		//				}
		//				if (PIN == "RF6")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p18[i];
		//					break;
		//				}
		//				if (PIN == "RF7")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p21[i];
		//					break;
		//				}
		//				if (PIN == "RF8")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p24[i];
		//					break;
		//				}
		//			}
		//			else if ((i >= tl->glob->rxrlpl_count[wolferType]))
		//			{
		//				throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
		//			}
		//		}
		//	}
		//}
		///*else
		//{
		//throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range",-1);
		//}*/
		//else if ((freq3H >= 3.5e9) && (freq3H <= 6e9) && (type == "Har"))
		//{
		//	if ((pathloss == 0))
		//	{
		//		for (int i = 0; i <= tl->glob->rxrlpl_count[wolferType]; i++)
		//		{
		//			if ((rxrlpl_freq[i] == freq3H)) // && (rxrlpl_pout[i]==sourceLevel))
		//			{
		//				if (PIN == "RF1")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p3[i];
		//					break;
		//				}
		//				if (PIN == "RF2")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p6[i];
		//					break;
		//				}
		//				if (PIN == "RF3")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p9[i];
		//					break;
		//				}
		//				if (PIN == "RF4")
		//				{
		//					//MeasureCh = RFOutCh3;
		//					pathloss = rxrlpl_p12[i];
		//					break;
		//				}
		//				if (PIN == "RF5")
		//				{
		//					//MeasureCh = RFOutCh4; //MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p15[i];
		//					break;
		//				}
		//				if (PIN == "RF6")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p18[i];
		//					break;
		//				}
		//				if (PIN == "RF7")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p21[i];
		//					break;
		//				}
		//				if (PIN == "RF8")
		//				{
		//					//MeasureCh = RFOutCh4;
		//					pathloss = rxrlpl_p24[i];
		//					break;
		//				}
		//			}
		//			else if ((i >= tl->glob->rxrlpl_count[wolferType]))
		//			{
		//				throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
		//			}
		//		}
		//	}
		//}
		else
		{
			throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range, Check Freq or Type setting", -1);
		}

		return ret;
	}
	long AMB7600SRTestLibrary::getRxHarPathLoss(int testSite, String^ wolferType, double %freq, double %sourceLevel, String ^ PIN, double %pathloss, String ^ type)
	{
		int ret = 0;

		//freq2H = 2*freq;
		//freq3H = 3*freq;

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].rxHarplFile[wolferType]))
		{
			throw gcnew Aemulus::Hardware::AlarmException("File not found - " + tl->glob->WolferInfo_Status[testSite].rxHarplFile[wolferType], -1);
		}

		if ((freq <= 1.0e9) && (type == "Har"))
		{
			if ((pathloss == 0.0))
			{
				for (int i = 0; i <= tl->glob->rxpl_Har_count[wolferType]; i++)
				{
					if ((rxpl_freq_Har[i] == freq))// && (rxpl_pout[i]==sourceLevel))
					{
						if (PIN == "RX1")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p1_Har[i];
							break;
						}

						if (PIN == "RX2")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p4_Har[i];
							break;
						}

						if (PIN == "RX3")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p7_Har[i];
							break;
						}

						if (PIN == "RX4")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p10_Har[i];
							break;
						}

						if (PIN == "RX5")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p13_Har[i];
							break;
						}

						if (PIN == "RX6")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p16_Har[i];
							break;
						}

						if (PIN == "RX7")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p19_Har[i];
							break;
						}

						if (PIN == "RX8")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p22_Har[i];
							break;
						}

					}
					else if ((i >= tl->glob->rxpl_Har_count[wolferType]))
					{
						throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
					}
				}
			}
		}
		/*else
		{
		throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range",-1);
		}*/

		else if ((freq >= 1.2e9) && (freq <= 3.5e9) && (type == "Har"))
		{
			if ((pathloss == 0))
			{
				for (int i = 0; i <= tl->glob->rxpl_Har_count[wolferType]; i++)
				{
					if ((rxpl_freq_Har[i] == freq))// && (rxrlpl_pout[i]==sourceLevel))
					{
						if (PIN == "RX1")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p2_Har[i];
							break;
						}

						if (PIN == "RX2")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p5_Har[i];
							break;
						}

						if (PIN == "RX3")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p8_Har[i];
							break;
						}

						if (PIN == "RX4")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p11_Har[i];
							break;
						}

						if (PIN == "RX5")
						{
							MeasureCh = RFOutCh4;//MeasureCh = RFOutCh4;
							pathloss = rxpl_p14_Har[i];
							break;
						}

						if (PIN == "RX6")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p17_Har[i];
							break;
						}

						if (PIN == "RX7")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p20_Har[i];
							break;
						}

						if (PIN == "RX8")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p23_Har[i];
							break;
						}
					}
					else if ((i >= tl->glob->rxpl_Har_count[wolferType]))
					{
						throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
					}


				}
			}
		}
		/*else
		{
		throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range",-1);
		}*/

		else if ((freq >= 3.5e9) && (freq <= 6e9) && (type == "Har"))
		{
			if ((pathloss == 0))
			{
				for (int i = 0; i <= tl->glob->rxpl_Har_count[wolferType]; i++)
				{
					if ((rxpl_freq_Har[i] == freq))// && (rxrlpl_pout[i]==sourceLevel))
					{
						if (PIN == "RF1")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p3_Har[i];
							break;
						}

						if (PIN == "RF2")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p6_Har[i];
							break;
						}

						if (PIN == "RF3")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p9_Har[i];
							break;
						}

						if (PIN == "RF4")
						{
							MeasureCh = RFOutCh3;
							pathloss = rxpl_p12_Har[i];
							break;
						}

						if (PIN == "RF5")
						{
							MeasureCh = RFOutCh4; //MeasureCh = RFOutCh4;
							pathloss = rxpl_p15_Har[i];
							break;
						}

						if (PIN == "RF6")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p18_Har[i];
							break;
						}

						if (PIN == "RF7")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p21_Har[i];
							break;
						}

						if (PIN == "RF8")
						{
							MeasureCh = RFOutCh4;
							pathloss = rxpl_p24_Har[i];
							break;
						}

					}
					else if ((i >= tl->glob->rxpl_Har_count[wolferType]))
					{
						throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match", -1);
					}


				}
			}
		}
		/*else
		{
		throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range",-1);
		}*/


		//else if ((freq3H >= 3.5e9) && (freq3H <= 6e9) && (type == "Har"))
		//	{	
		//			if ((pathloss == 0 ))
		//			{
		//					for (int i = 0; i <= rxpl_Har_count; i++)
		//					{
		//						if ((rxpl_freq_Har[i]==freq3H)) // && (rxrlpl_pout[i]==sourceLevel))
		//						{	
		//							if(PIN == "RF1")
		//							{				
		//								MeasureCh = RFOutCh3;
		//								pathloss = rxrlpl_p3[i];
		//								break;
		//							}	

		//							if(PIN == "RF2")
		//							{				
		//								MeasureCh = RFOutCh3;
		//								pathloss = rxrlpl_p6[i];
		//								break;
		//							}	

		//							if(PIN == "RF3")
		//							{				
		//								MeasureCh = RFOutCh3;
		//								pathloss = rxrlpl_p9[i];
		//								break;
		//							}	

		//							if(PIN == "RF4")
		//							{				
		//								MeasureCh = RFOutCh3;
		//								pathloss = rxrlpl_p12[i];
		//								break;
		//							}	

		//							if(PIN == "RF5")
		//							{				
		//								MeasureCh = RFOutCh4; //MeasureCh = RFOutCh4;
		//								pathloss = rxrlpl_p15[i];
		//								break;
		//							}	

		//							if(PIN == "RF6")
		//							{				
		//								MeasureCh = RFOutCh4;
		//								pathloss = rxrlpl_p18[i];
		//								break;
		//							}	

		//							if(PIN == "RF7")
		//							{				
		//								MeasureCh = RFOutCh4;
		//								pathloss = rxrlpl_p21[i];
		//								break;
		//							}	

		//							if(PIN == "RF8")
		//							{				
		//								MeasureCh = RFOutCh4;
		//								pathloss = rxrlpl_p24[i];
		//								break;
		//							}	
		//						}
		//					else if ((i >= rxpl_Har_count))
		//							{
		//								throw gcnew Aemulus::Hardware::AlarmException("Freq or Power level not match",-1);
		//							}
		//					
		//					}
		//				}
		//			}	
		else
		{
			throw gcnew Aemulus::Hardware::AlarmException("Measurement Out of Range, Check Freq or Type setting", -1);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::ReadRxHarPathLoss(int testSite, String^ wolferType, int %rxpl_Har_count)
	{
		int ret = 0;

		int arraySize = 256;

		StringBuilder ^ sbw = gcnew StringBuilder();

		if (!File::Exists(tl->glob->WolferInfo_Status[testSite].rxHarplFile[wolferType]))
		{
			sbw->AppendLine(tl->glob->WolferInfo_Status[testSite].rxHarplFile[wolferType] + " not found.");
			MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return 0;
		}

		rxpl_freq_Har = gcnew array<double>(arraySize);
		rxpl_pout_Har = gcnew array<double>(arraySize);
		rxpl_p1_Har = gcnew array<double>(arraySize);
		rxpl_p2_Har = gcnew array<double>(arraySize);
		rxpl_p3_Har = gcnew array<double>(arraySize);
		rxpl_p4_Har = gcnew array<double>(arraySize);
		rxpl_p5_Har = gcnew array<double>(arraySize);
		rxpl_p6_Har = gcnew array<double>(arraySize);
		rxpl_p7_Har = gcnew array<double>(arraySize);
		rxpl_p8_Har = gcnew array<double>(arraySize);
		rxpl_p9_Har = gcnew array<double>(arraySize);
		rxpl_p10_Har = gcnew array<double>(arraySize);
		rxpl_p11_Har = gcnew array<double>(arraySize);
		rxpl_p12_Har = gcnew array<double>(arraySize);
		rxpl_p13_Har = gcnew array<double>(arraySize);
		rxpl_p14_Har = gcnew array<double>(arraySize);
		rxpl_p15_Har = gcnew array<double>(arraySize);
		rxpl_p16_Har = gcnew array<double>(arraySize);
		rxpl_p17_Har = gcnew array<double>(arraySize);
		rxpl_p18_Har = gcnew array<double>(arraySize);
		rxpl_p19_Har = gcnew array<double>(arraySize);
		rxpl_p20_Har = gcnew array<double>(arraySize);
		rxpl_p21_Har = gcnew array<double>(arraySize);
		rxpl_p22_Har = gcnew array<double>(arraySize);
		rxpl_p23_Har = gcnew array<double>(arraySize);
		rxpl_p24_Har = gcnew array<double>(arraySize);


		int rx_pl_Har_count = 0;
		String ^ line = String::Empty;
		array<String ^> ^ ArrStr = gcnew array<String ^>(0);
		array<String ^> ^ Separator = gcnew array<String ^>(1);
		Separator[0] = ",";

		StreamReader ^ sr = gcnew StreamReader(tl->glob->WolferInfo_Status[testSite].rxHarplFile[wolferType]);
		while ((line = sr->ReadLine()) != nullptr)
		{
			if (line->StartsWith("//") == false)
			{
				ArrStr = line->Split(Separator, StringSplitOptions::None);

				if (ArrStr->Length == 25)
				{

					rxpl_freq_Har[rx_pl_Har_count] = StrToDouble(ArrStr[0]);
					rxpl_p1_Har[rx_pl_Har_count] = StrToDouble(ArrStr[1]);
					rxpl_p2_Har[rx_pl_Har_count] = StrToDouble(ArrStr[2]);
					rxpl_p3_Har[rx_pl_Har_count] = StrToDouble(ArrStr[3]);
					rxpl_p4_Har[rx_pl_Har_count] = StrToDouble(ArrStr[4]);
					rxpl_p5_Har[rx_pl_Har_count] = StrToDouble(ArrStr[5]);
					rxpl_p6_Har[rx_pl_Har_count] = StrToDouble(ArrStr[6]);
					rxpl_p7_Har[rx_pl_Har_count] = StrToDouble(ArrStr[7]);
					rxpl_p8_Har[rx_pl_Har_count] = StrToDouble(ArrStr[8]);
					rxpl_p9_Har[rx_pl_Har_count] = StrToDouble(ArrStr[9]);
					rxpl_p10_Har[rx_pl_Har_count] = StrToDouble(ArrStr[10]);
					rxpl_p11_Har[rx_pl_Har_count] = StrToDouble(ArrStr[11]);
					rxpl_p12_Har[rx_pl_Har_count] = StrToDouble(ArrStr[12]);
					rxpl_p13_Har[rx_pl_Har_count] = StrToDouble(ArrStr[13]);
					rxpl_p14_Har[rx_pl_Har_count] = StrToDouble(ArrStr[14]);
					rxpl_p15_Har[rx_pl_Har_count] = StrToDouble(ArrStr[15]);
					rxpl_p16_Har[rx_pl_Har_count] = StrToDouble(ArrStr[16]);
					rxpl_p17_Har[rx_pl_Har_count] = StrToDouble(ArrStr[17]);
					rxpl_p18_Har[rx_pl_Har_count] = StrToDouble(ArrStr[18]);
					rxpl_p19_Har[rx_pl_Har_count] = StrToDouble(ArrStr[19]);
					rxpl_p20_Har[rx_pl_Har_count] = StrToDouble(ArrStr[20]);
					rxpl_p21_Har[rx_pl_Har_count] = StrToDouble(ArrStr[21]);
					rxpl_p22_Har[rx_pl_Har_count] = StrToDouble(ArrStr[22]);
					rxpl_p23_Har[rx_pl_Har_count] = StrToDouble(ArrStr[23]);
					rxpl_p24_Har[rx_pl_Har_count] = StrToDouble(ArrStr[24]);

				}
				else
				{
					gcnew Aemulus::Hardware::AlarmException("Wrong rx_pathloss.txt format!", -1);
				}

				rx_pl_Har_count++;

				if (rx_pl_Har_count > arraySize)
				{
					sbw->AppendLine("The number of rx path loss cal points has exceeded 256");
					MessageBox::Show(sbw->ToString(), "AXRF Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					return 0;
				}
			}
		}

		sr->Close();
		sr = nullptr;

		rxpl_Har_count = rx_pl_Har_count;

		return ret;
	}
	int AMB7600SRTestLibrary::WolferSelectPath_C2(int testSite, String^ wolferType, String^ selectTxPath, String^ selectRxPath, double sourceFreq, double measureFreq, bool TxBypassOn, String^ TxInternalPath, String^ RxInternalPath)
	{
		int ret = 0;
		bool toggleSwitch;

		// Switch Tx Path
		if (TxInternalPath != nullptr)
		{
			if (TxInternalPath == "T1" && tl->glob->g_txpath[wolferType] != 1)
			{
				wlfTxPath(testSite, (int)txswpath::tx1);
				tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
				tl->glob->g_txpath[wolferType] = 1; //TxPath inside Wolfer
				tl->glob->g_SelectTxPath[wolferType] = "TX1";
				toggleSwitch = true;
			}
			else if (TxInternalPath == "T2" && tl->glob->g_txpath[wolferType] != 2)
			{
				wlfTxPath(testSite, (int)txswpath::tx2);
				tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
				tl->glob->g_txpath[wolferType] = 2; //TxPath inside Wolfer
				tl->glob->g_SelectTxPath[wolferType] = "TX1";
				toggleSwitch = true;
			}
			else if (TxInternalPath == "T3" && tl->glob->g_txpath[wolferType] != 3)
			{
				wlfTxPath(testSite, (int)txswpath::tx3);
				tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
				tl->glob->g_txpath[wolferType] = 3; //TxPath inside Wolfer
				tl->glob->g_SelectTxPath[wolferType] = "TX1";
				toggleSwitch = true;
			}
			else if (TxInternalPath == "T4" && tl->glob->g_txpath[wolferType] != 4)
			{
				wlfTxPath(testSite, (int)txswpath::tx4);
				tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
				tl->glob->g_txpath[wolferType] = 4; //TxPath inside Wolfer
				tl->glob->g_SelectTxPath[wolferType] = "TX1";
				toggleSwitch = true;
			}
			else
			{
				throw gcnew Aemulus::Hardware::AlarmException(wolferType + " has undefined TxInternalPath Type", -1);
			}
		}
		else
		{
			if (TxBypassOn)
			{
				if (selectTxPath == "TX1" && tl->glob->g_txpath[wolferType] != 3)
				{
					wlfTxPath(testSite, (int)txswpath::tx3);
					tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
					tl->glob->g_txpath[wolferType] = 3; //TxPath inside Wolfer
					tl->glob->g_SelectTxPath[wolferType] = "TX1";
					toggleSwitch = true;
				}
			}
			else
			{
				if (sourceFreq <= 1.0 GHz)
				{
					if (selectTxPath == "TX1" && tl->glob->g_txpath[wolferType] != 1)
					{
						wlfTxPath(testSite, (int)txswpath::tx1);
						tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
						tl->glob->g_txpath[wolferType] = 1; //TxPath inside Wolfer
						tl->glob->g_SelectTxPath[wolferType] = "TX1";
						toggleSwitch = true;
					}
				}
				if (sourceFreq >= 1.8 GHz && sourceFreq <= 2.6 GHz)
				{
					if (selectTxPath == "TX1" && tl->glob->g_txpath[wolferType] != 2)
					{
						wlfTxPath(testSite, (int)txswpath::tx2);
						tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
						tl->glob->g_txpath[wolferType] = 2; //TxPath inside Wolfer
						tl->glob->g_SelectTxPath[wolferType] = "TX1";
						toggleSwitch = true;
					}
				}
				if (sourceFreq >= 2.6 GHz)
				{
					if (selectTxPath == "TX1" && tl->glob->g_txpath[wolferType] != 4)
					{
						wlfTxPath(testSite, (int)txswpath::tx4);
						tl->glob->outIndex[wolferType] = 0; //outIndex 0 -> TX1
						tl->glob->g_txpath[wolferType] = 4; //TxPath inside Wolfer
						tl->glob->g_SelectTxPath[wolferType] = "TX1";
						toggleSwitch = true;
					}
				}
			}
		}

		// Switch RX Paths 
		if (RxInternalPath != nullptr)
		{
			if (selectRxPath == "R1" && tl->glob->g_rxpath[wolferType] != 1)
			{
				wlfRxPath(testSite, (int)rxswpath::rx1);
				tl->glob->g_rxpath[wolferType] = 1;
				tl->glob->g_SelectRxPath[wolferType] = "RX1";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R2" && tl->glob->g_rxpath[wolferType] != 2)
			{
				wlfRxPath(testSite, (int)rxswpath::rx2);
				tl->glob->g_rxpath[wolferType] = 2;
				tl->glob->g_SelectRxPath[wolferType] = "RX1";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R3" && tl->glob->g_rxpath[wolferType] != 3)
			{
				wlfRxPath(testSite, (int)rxswpath::rx3);
				tl->glob->g_rxpath[wolferType] = 3;
				tl->glob->g_SelectRxPath[wolferType] = "RX1";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R4" && tl->glob->g_rxpath[wolferType] != 4)
			{
				wlfRxPath(testSite, (int)rxswpath::rx4);
				tl->glob->g_rxpath[wolferType] = 4;
				tl->glob->g_SelectRxPath[wolferType] = "RX2";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R5" && tl->glob->g_rxpath[wolferType] != 5)
			{
				wlfRxPath(testSite, (int)rxswpath::rx5);
				tl->glob->g_rxpath[wolferType] = 5;
				tl->glob->g_SelectRxPath[wolferType] = "RX2";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R6" && tl->glob->g_rxpath[wolferType] != 6)
			{
				wlfRxPath(testSite, (int)rxswpath::rx6);
				tl->glob->g_rxpath[wolferType] = 6;
				tl->glob->g_SelectRxPath[wolferType] = "RX2";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R7" && tl->glob->g_rxpath[wolferType] != 7)
			{
				wlfRxPath(testSite, (int)rxswpath::rx7);
				tl->glob->g_rxpath[wolferType] = 7;
				tl->glob->g_SelectRxPath[wolferType] = "RX3";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R8" && tl->glob->g_rxpath[wolferType] != 8)
			{
				wlfRxPath(testSite, (int)rxswpath::rx8);
				tl->glob->g_rxpath[wolferType] = 8;
				tl->glob->g_SelectRxPath[wolferType] = "RX3";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R9" && tl->glob->g_rxpath[wolferType] != 9)
			{
				wlfRxPath(testSite, (int)rxswpath::rx9);
				tl->glob->g_rxpath[wolferType] = 9;
				tl->glob->g_SelectRxPath[wolferType] = "RX3";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R10" && tl->glob->g_rxpath[wolferType] != 10)
			{
				wlfRxPath(testSite, (int)rxswpath::rx10);
				tl->glob->g_rxpath[wolferType] = 10;
				tl->glob->g_SelectRxPath[wolferType] = "RX4";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R11" && tl->glob->g_rxpath[wolferType] != 11)
			{
				wlfRxPath(testSite, (int)rxswpath::rx11);
				tl->glob->g_rxpath[wolferType] = 11;
				tl->glob->g_SelectRxPath[wolferType] = "RX4";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R12" && tl->glob->g_rxpath[wolferType] != 12)
			{
				wlfRxPath(testSite, (int)rxswpath::rx12);
				tl->glob->g_rxpath[wolferType] = 12;
				tl->glob->g_SelectRxPath[wolferType] = "RX4";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R13" && tl->glob->g_rxpath[wolferType] != 13)
			{
				wlfRxPath(testSite, (int)rxswpath::rx13);
				tl->glob->g_rxpath[wolferType] = 13;
				tl->glob->g_SelectRxPath[wolferType] = "RX5";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R14" && tl->glob->g_rxpath[wolferType] != 14)
			{
				wlfRxPath(testSite, (int)rxswpath::rx14);
				tl->glob->g_rxpath[wolferType] = 14;
				tl->glob->g_SelectRxPath[wolferType] = "RX5";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R15" && tl->glob->g_rxpath[wolferType] != 15)
			{
				wlfRxPath(testSite, (int)rxswpath::rx15);
				tl->glob->g_rxpath[wolferType] = 15;
				tl->glob->g_SelectRxPath[wolferType] = "RX5";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R16" && tl->glob->g_rxpath[wolferType] != 16)
			{
				wlfRxPath(testSite, (int)rxswpath::rx16);
				tl->glob->g_rxpath[wolferType] = 16;
				tl->glob->g_SelectRxPath[wolferType] = "RX6";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R17" && tl->glob->g_rxpath[wolferType] != 17)
			{
				wlfRxPath(testSite, (int)rxswpath::rx17);
				tl->glob->g_rxpath[wolferType] = 17;
				tl->glob->g_SelectRxPath[wolferType] = "RX6";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R18" && tl->glob->g_rxpath[wolferType] != 18)
			{
				wlfRxPath(testSite, (int)rxswpath::rx18);
				tl->glob->g_rxpath[wolferType] = 18;
				tl->glob->g_SelectRxPath[wolferType] = "RX6";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R19" && tl->glob->g_rxpath[wolferType] != 19)
			{
				wlfRxPath(testSite, (int)rxswpath::rx19);
				tl->glob->g_rxpath[wolferType] = 19;
				tl->glob->g_SelectRxPath[wolferType] = "RX7";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R20" && tl->glob->g_rxpath[wolferType] != 20)
			{
				wlfRxPath(testSite, (int)rxswpath::rx20);
				tl->glob->g_rxpath[wolferType] = 20;
				tl->glob->g_SelectRxPath[wolferType] = "RX7";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R21" && tl->glob->g_rxpath[wolferType] != 21)
			{
				wlfRxPath(testSite, (int)rxswpath::rx21);
				tl->glob->g_rxpath[wolferType] = 21;
				tl->glob->g_SelectRxPath[wolferType] = "RX7";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R22" && tl->glob->g_rxpath[wolferType] != 22)
			{
				wlfRxPath(testSite, (int)rxswpath::rx22);
				tl->glob->g_rxpath[wolferType] = 22;
				tl->glob->g_SelectRxPath[wolferType] = "RX8";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R23" && tl->glob->g_rxpath[wolferType] != 23)
			{
				wlfRxPath(testSite, (int)rxswpath::rx23);
				tl->glob->g_rxpath[wolferType] = 23;
				tl->glob->g_SelectRxPath[wolferType] = "RX8";
				toggleSwitch = true;
			}
			else if (selectRxPath == "R24" && tl->glob->g_rxpath[wolferType] != 24)
			{
				wlfRxPath(testSite, (int)rxswpath::rx24);
				tl->glob->g_rxpath[wolferType] = 24;
				tl->glob->g_SelectRxPath[wolferType] = "RX8";
				toggleSwitch = true;
			}
			else
			{
				throw gcnew Aemulus::Hardware::AlarmException(wolferType + " has undefined RxInternalPath Type", -1);
			}
		}
		else
		{
			if (measureFreq < 1.32 GHz)
			{
				if (selectRxPath == "RX1" && tl->glob->g_rxpath[wolferType] != 1)
				{
					wlfRxPath(testSite, (int)rxswpath::rx1);
					tl->glob->g_rxpath[wolferType] = 1;
					tl->glob->g_SelectRxPath[wolferType] = "RX1";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX2" && tl->glob->g_rxpath[wolferType] != 4)
				{
					wlfRxPath(testSite, (int)rxswpath::rx4);
					tl->glob->g_rxpath[wolferType] = 4;
					tl->glob->g_SelectRxPath[wolferType] = "RX2";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX3" && tl->glob->g_rxpath[wolferType] != 7)
				{
					wlfRxPath(testSite, (int)rxswpath::rx7);
					tl->glob->g_rxpath[wolferType] = 7;
					tl->glob->g_SelectRxPath[wolferType] = "RX3";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX4" && tl->glob->g_rxpath[wolferType] != 10)
				{
					wlfRxPath(testSite, (int)rxswpath::rx10);
					tl->glob->g_rxpath[wolferType] = 10;
					tl->glob->g_SelectRxPath[wolferType] = "RX4";
					toggleSwitch = true;
				}
				if (selectRxPath == "RX5" && tl->glob->g_rxpath[wolferType] != 13)
				{
					wlfRxPath(testSite, (int)rxswpath::rx13);
					tl->glob->g_rxpath[wolferType] = 13;
					tl->glob->g_SelectRxPath[wolferType] = "RX5";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX6" && tl->glob->g_rxpath[wolferType] != 16)
				{
					wlfRxPath(testSite, (int)rxswpath::rx16);
					tl->glob->g_rxpath[wolferType] = 16;
					tl->glob->g_SelectRxPath[wolferType] = "RX6";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX7" && tl->glob->g_rxpath[wolferType] != 19)
				{
					wlfRxPath(testSite, (int)rxswpath::rx19);
					tl->glob->g_rxpath[wolferType] = 19;
					tl->glob->g_SelectRxPath[wolferType] = "RX7";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX8" && tl->glob->g_rxpath[wolferType] != 22)
				{
					wlfRxPath(testSite, (int)rxswpath::rx22);
					tl->glob->g_rxpath[wolferType] = 22;
					tl->glob->g_SelectRxPath[wolferType] = "RX8";
					toggleSwitch = true;
				}
			}
			else if ((measureFreq >= 1.32 GHz) && (measureFreq < 3.5 GHz))
			{
				if (selectRxPath == "RX1" && tl->glob->g_rxpath[wolferType] != 2)
				{
					wlfRxPath(testSite, (int)rxswpath::rx2);
					tl->glob->g_rxpath[wolferType] = 2;
					tl->glob->g_SelectRxPath[wolferType] = "RX1";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX2" && tl->glob->g_rxpath[wolferType] != 5)
				{
					wlfRxPath(testSite, (int)rxswpath::rx5);
					tl->glob->g_rxpath[wolferType] = 5;
					tl->glob->g_SelectRxPath[wolferType] = "RX2";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX3" && tl->glob->g_rxpath[wolferType] != 8)
				{
					wlfRxPath(testSite, (int)rxswpath::rx8);
					tl->glob->g_rxpath[wolferType] = 8;
					tl->glob->g_SelectRxPath[wolferType] = "RX3";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX4" && tl->glob->g_rxpath[wolferType] != 11)
				{
					wlfRxPath(testSite, (int)rxswpath::rx11);
					tl->glob->g_rxpath[wolferType] = 11;
					tl->glob->g_SelectRxPath[wolferType] = "RX4";
					toggleSwitch = true;
				}
				if (selectRxPath == "RX5" && tl->glob->g_rxpath[wolferType] != 14)
				{
					wlfRxPath(testSite, (int)rxswpath::rx14);
					tl->glob->g_rxpath[wolferType] = 14;
					tl->glob->g_SelectRxPath[wolferType] = "RX5";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX6" && tl->glob->g_rxpath[wolferType] != 17)
				{
					wlfRxPath(testSite, (int)rxswpath::rx17);
					tl->glob->g_rxpath[wolferType] = 17;
					tl->glob->g_SelectRxPath[wolferType] = "RX6";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX7" && tl->glob->g_rxpath[wolferType] != 20)
				{
					wlfRxPath(testSite, (int)rxswpath::rx20);
					tl->glob->g_rxpath[wolferType] = 20;
					tl->glob->g_SelectRxPath[wolferType] = "RX7";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX8" && tl->glob->g_rxpath[wolferType] != 23)
				{
					wlfRxPath(testSite, (int)rxswpath::rx23);
					tl->glob->g_rxpath[wolferType] = 23;
					tl->glob->g_SelectRxPath[wolferType] = "RX8";
					toggleSwitch = true;
				}
			}

			else if ((measureFreq >= 3.5 GHz) && (measureFreq < 6 GHz))
			{
				if (selectRxPath == "RX1" && tl->glob->g_rxpath[wolferType] != 3)
				{
					wlfRxPath(testSite, (int)rxswpath::rx3);
					tl->glob->g_rxpath[wolferType] = 3;
					tl->glob->g_SelectRxPath[wolferType] = "RX1";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX2" && tl->glob->g_rxpath[wolferType] != 6)
				{
					wlfRxPath(testSite, (int)rxswpath::rx6);
					tl->glob->g_rxpath[wolferType] = 6;
					tl->glob->g_SelectRxPath[wolferType] = "RX2";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX3" && tl->glob->g_rxpath[wolferType] != 9)
				{
					wlfRxPath(testSite, (int)rxswpath::rx9);
					tl->glob->g_rxpath[wolferType] = 9;
					tl->glob->g_SelectRxPath[wolferType] = "RX3";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX4" && tl->glob->g_rxpath[wolferType] != 12)
				{
					wlfRxPath(testSite, (int)rxswpath::rx12);
					tl->glob->g_rxpath[wolferType] = 12;
					tl->glob->g_SelectRxPath[wolferType] = "RX4";
					toggleSwitch = true;
				}
				if (selectRxPath == "RX5" && tl->glob->g_rxpath[wolferType] != 15)
				{
					wlfRxPath(testSite, (int)rxswpath::rx15);
					tl->glob->g_rxpath[wolferType] = 15;
					tl->glob->g_SelectRxPath[wolferType] = "RX5";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX6" && tl->glob->g_rxpath[wolferType] != 18)
				{
					wlfRxPath(testSite, (int)rxswpath::rx18);
					tl->glob->g_rxpath[wolferType] = 18;
					tl->glob->g_SelectRxPath[wolferType] = "RX6";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX7" && tl->glob->g_rxpath[wolferType] != 21)
				{
					wlfRxPath(testSite, (int)rxswpath::rx21);
					tl->glob->g_rxpath[wolferType] = 21;
					tl->glob->g_SelectRxPath[wolferType] = "RX7";
					toggleSwitch = true;
				}
				else if (selectRxPath == "RX8" && tl->glob->g_rxpath[wolferType] != 24)
				{
					wlfRxPath(testSite, (int)rxswpath::rx24);
					tl->glob->g_rxpath[wolferType] = 24;
					tl->glob->g_SelectRxPath[wolferType] = "RX8";
					toggleSwitch = true;
				}
			}
		}
		if (toggleSwitch)
		{
			//Wolfer SW delay
			util->WaitSecond(25 mS);
			toggleSwitch = false;
		}

		return ret;
	}

#pragma endregion "Wolfer"
}