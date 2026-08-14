#include "AMB7600SR.h"
#include "../Test Method/Methods.h"

namespace Functions
{
	// AMB5600TestLibrary Contsructor and Destructor 
	AMB7600SRTestLibrary::AMB7600SRTestLibrary(TestFunction ^ TestFunc, MethodsBranch ^ sharedMethods)
	{
		tl = TestFunc;
		methods = sharedMethods;
		////Instanstiates value struc 
		/*iCISSetting = gcnew array<ImageCISSetting>(tl->glob->tf.NumberOfSites);
		DM500xSett = gcnew array<DM500xSetting>(tl->glob->tf.NumberOfSites);
		DM500xDIOSett = gcnew array<DM500xDIOSetting>(tl->glob->tf.NumberOfSites);
		DM500xPMUSett = gcnew array<DM500xPMUSetting>(tl->glob->tf.NumberOfSites);
		DM500xClockGenSett = gcnew array<DM500xClockGenSetting>(tl->glob->tf.NumberOfSites);
		DM500xVectorSett = gcnew array<DM500xVectorSetting>(tl->glob->tf.NumberOfSites);
		CbitOutControlSett = gcnew array<CbitOutController>(tl->glob->tf.NumberOfSites);
		AM500xSett = gcnew array<AM500xSetting>(tl->glob->tf.NumberOfSites);
		AM500xDPSSett = gcnew array<AM500xDPSSetting>(tl->glob->tf.NumberOfSites);
		DM500xTMUSett = gcnew array<DM500xTMUSetting>(tl->glob->tf.NumberOfSites);
		PELevelSett = gcnew array<PELevelSetting>(tl->glob->tf.NumberOfSites);
		iI2CSetting = gcnew array<I2CSetting>(tl->glob->tf.NumberOfSites);
		PatternLoggerSett = gcnew array<PatternLoggerSetting>(tl->glob->tf.NumberOfSites);*/
		ResourceManagerSett = gcnew array<ResourceManagerSetting>(tl->glob->tf.NumberOfSites);

#pragma region "Assembly Resolver"	

		// Perform assembly resolve if the loading of.dll / .exe turns out to be unsucessfull 
		//currentDomain = AppDomain::CurrentDomain;
		//this->currentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(this, &AMB5600TestLibrary::currentDomain_AssemblyResolve);

#pragma endregion "Assembly Resolver"	

	}
	AMB7600SRTestLibrary::~AMB7600SRTestLibrary(void)
	{

	}

	//Helper Functions
	int AMB7600SRTestLibrary::InitializeTester(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead)
	{
		int ret = 0;
		int siteIndex = 0;
		int testSite = site->Index;

		for (siteIndex = 0; siteIndex < TotalSite; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing Aemulus Tester...");
		}

		try
		{
#pragma region "Resource Manager"
			
			for (siteIndex = 0; siteIndex < TotalSite; siteIndex++)
			{
				// Reset AM/DM/CM hardware initialization flag 
				ResourceManagerSett[siteIndex].AM_HardwareStatus			= false;
				ResourceManagerSett[siteIndex].DM_HardwareStatus			= false;
				ResourceManagerSett[siteIndex].CM_HardwareStatus			= false;
				ResourceManagerSett[siteIndex].DIO_HardwareStatus			= false;
				ResourceManagerSett[siteIndex].AMSRF_HardwareStatus			= false;
				ResourceManagerSett											= gcnew array<ResourceManagerSetting>(TotalSite);
				ResourceManagerSett[siteIndex].RsrcManager					= gcnew array<ResourceManager ^>(TotalSite);
				//ResourceManagerSett[siteIndex].AMResourceAlias_ModuleType	= gcnew Dictionary <String ^, String ^>();
				ResourceManagerSett[siteIndex].AMResourceAlias				= gcnew Dictionary <String ^, int>();	//Reserved for application-wise used 
				ResourceManagerSett[siteIndex].CMResourceAlias				= gcnew Dictionary <String ^, int>();	//Reserved for application-wise used 
				ResourceManagerSett[siteIndex].DMResourceAlias				= gcnew Dictionary <String ^, int>();	//Reserved for application-wise used
				ResourceManagerSett[siteIndex].DIOResourceAlias				= gcnew Dictionary <String ^, int>();	//Reserved for application-wise used
				ResourceManagerSett[siteIndex].DIOResourcePortAlias			= gcnew Dictionary <String ^, int>();	//Reserved for application-wise used
				ResourceManagerSett[siteIndex].ResourceAlias				= gcnew Dictionary <String ^, int>();	//Reserved for application-wise used 

				ResourceManagerSett[siteIndex].RsrcManager[siteIndex]		= nullptr;
				ResourceManagerSett[siteIndex].RsrcManager[siteIndex]		= gcnew ResourceManager(HardwareProfile, TestHead, siteIndex);

				

				ResourceManagerSett[siteIndex].RsrcManagerSPG				= gcnew array<ResourceManager ^>(TotalSite);
				ResourceManagerSett[siteIndex].RsrcManagerSPG[siteIndex]	= gcnew ResourceManager(HardwareProfile);
				ResourceManagerSett[siteIndex].mcPinGroupPinMaps			= gcnew Dictionary <String ^, MapCollection ^>();
				ResourceManagerSett[siteIndex].PinGroupPinMaps				= gcnew Dictionary <String ^, array<String ^>^>();


				List<String ^> ^ pinMapsGroup = gcnew List<String ^>();

				if (ResourceManagerSett[siteIndex].RsrcManagerSPG[siteIndex]->PinGroups != nullptr)
				{
					ResourceManagerSett[siteIndex].pinGroups = ResourceManagerSett[siteIndex].RsrcManagerSPG[siteIndex]->PinGroups;

					for (int iPinGroup = 0; iPinGroup < ResourceManagerSett[siteIndex].pinGroups->Count; iPinGroup++)
					{
						String^ CurrentPinGroups = ResourceManagerSett[siteIndex].RsrcManagerSPG[siteIndex]->PinGroups[iPinGroup]->Name;//for checking

						pinMapsGroup->Add(ResourceManagerSett[siteIndex].RsrcManagerSPG[siteIndex]->PinGroups[iPinGroup]->Name);
						ResourceManagerSett[siteIndex].pinMapsTemp = gcnew array<String^>(ResourceManagerSett[siteIndex].pinGroups[iPinGroup]->PinMaps->Count);

						for (int iPin = 0; iPin < ResourceManagerSett[siteIndex].pinGroups[iPinGroup]->PinMaps->Count; iPin++)
						{
							//Retrieved the pin maps for each pin group in the hardware profile 
							ResourceManagerSett[siteIndex].pinMapsTemp[iPin] = ResourceManagerSett[siteIndex].pinGroups[iPinGroup]->PinMaps[iPin]->Name;
						}

						ResourceManagerSett[siteIndex].mcPinGroupPinMaps->Add(ResourceManagerSett[siteIndex].pinGroups[iPinGroup]->Name, ResourceManagerSett[siteIndex].pinGroups[iPinGroup]->PinMaps);
						ResourceManagerSett[siteIndex].PinGroupPinMaps->Add(ResourceManagerSett[siteIndex].pinGroups[iPinGroup]->Name, ResourceManagerSett[siteIndex].pinMapsTemp);

					}
				}

			}





#pragma endregion "Resource Manager"

#pragma region "SiteConfiguration"

			SiteConfiguration(site);

#pragma endregion "SiteConfiguration"

#pragma region "Hardware Initialization"

			//DC Resource
			InitializeDM400eResource(site);
			InitializeAM400eResource(site);
			InitializeIOM421eResource(site);
			InitializeCM400eResource(site);

			//RF Resource
			if (CurrentHeadSite.AMSRFSupported != "NA")
			{
				InitializeAMSRFResource(site);
			}


#pragma endregion "Hardware Initialization"

		}
		catch (Exception^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->ErrorHandling(site, tl->glob->TcrLgr.GlobalErrorMessage);
			throw gcnew Aemulus::Hardware::AlarmException(ex->ToString(),ex->HResult);
		}

		for (siteIndex = 0; siteIndex < TotalSite; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized Aemulus Tester");
		}

		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeTester(Site ^ site)
	{
		int ret = 0;
		int siteIndex = 0;

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Uninitializing Aemulus Tester...");
		}

		UninitializeDM400eResource(site);
		UninitializeAM400eResource(site);
		UninitializeIOM421eResource(site);
		UninitializeCM400eResource(site);

		if (CurrentHeadSite.AMSRFSupported != "NA")
		{
			//UninitializeAMSRFResource(site); //Nicholas
		}

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Uninitialized Aemulus Tester");
		}

		return ret;
	}
	int AMB7600SRTestLibrary::PostProcessing_RF(Site ^ site)
	{
		int ret = 0;

		if (CurrentHeadSite.AMSRFSupported != "NA")
		{
			for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
			{
				RF_EvmAsyncCastResultToTechFlow(site, siteIndex);
				RF_SemAsyncCastResultToTechFlow(site, siteIndex);
				
				//EVM
				if (tl->glob->EvmAsyncInfoCastResultToTF[siteIndex].testParaCount > 0)
				{
					for (int i = 0; i < tl->glob->EvmAsyncInfoCastResultToTF[siteIndex].testParaCount; i++)
					{
						tl->UpdateTestResultWlanAsync(site, siteIndex, tl->glob->EvmAsyncInfoCastResultToTF[siteIndex].testItemName[i], tl->glob->EvmAsyncInfoCastResultToTF[siteIndex].testParaName[i], tl->glob->EvmAsyncInfoCastResultToTF[siteIndex].result[i]);
					}
				}

				//SEM
				if (tl->glob->SemAsyncInfoCastResultToTF[siteIndex].testParaCount > 0)
				{
					for (int i = 0; i < tl->glob->SemAsyncInfoCastResultToTF[siteIndex].testParaCount; i++)
					{
						for (int j = 0; j < tl->glob->SemAsyncInfoCastResultToTF[siteIndex].result[i]->Length; j++)
						{
							tl->UpdateTestResultWlanAsync(site, siteIndex, tl->glob->SemAsyncInfoCastResultToTF[siteIndex].testItemName[i], tl->glob->SemAsyncInfoCastResultToTF[siteIndex].testParaName[i][j], tl->glob->SemAsyncInfoCastResultToTF[siteIndex].result[i][j]);
						}
					}
				}

				tl->glob->EvmAsyncInfoCastResultToTF[siteIndex].testParaCount = 0;
				tl->glob->SemAsyncInfoCastResultToTF[siteIndex].testParaCount = 0;
			}
		}

		return ret;
	}
	void AMB7600SRTestLibrary::SiteConfiguration(Site ^ site)
	{
		try
		{
			int l_HeadNumber = site->FlowEngine->HeadNumber;
			int l_SiteIndex = site->Index;

			//Local Variable
			String ^ SiteConfiqFilePath = nullptr;
			String ^ testHeadSite = "H" + l_HeadNumber.ToString() + "S" + l_SiteIndex.ToString();

			XmlNode^ XmlInfo;
			XmlNode^ XmlSiteConfigInfo;
			XmlDocument ^ SiteConfiqInfo = gcnew XmlDocument();

			//Xml Information
			SiteConfiqFilePath = site->GetExternalDependency("RFSiteConfigInfo");
			SiteConfiqInfo->Load(SiteConfiqFilePath);
			XmlSiteConfigInfo = SiteConfiqInfo->DocumentElement->FirstChild;

			//Initialization
			H0S0.AMSRFSupported = "NA";
			H0S0.TotalUUTOffset = 0;
			H0S0.TotalExternalModule = 0;
			H0S0.TotalSignalCore = 0;
			H0S0.AMSRF0_Site = nullptr;
			H0S0.AMSRF0_Exist = false;
			H0S0.AMSRF1_Site = nullptr;
			H0S0.AMSRF1_Exist = false;

			H0S1.AMSRFSupported = "NA";
			H0S1.TotalUUTOffset = 0;
			H0S1.TotalExternalModule = 0;
			H0S1.TotalSignalCore = 0;
			H0S1.AMSRF0_Site = nullptr;
			H0S1.AMSRF0_Exist = false;
			H0S1.AMSRF1_Site = nullptr;
			H0S1.AMSRF1_Exist = false;

			H1S0.AMSRFSupported = "NA";
			H1S0.TotalUUTOffset = 0;
			H1S0.TotalExternalModule = 0;
			H1S0.TotalSignalCore = 0;
			H1S0.AMSRF0_Site = nullptr;
			H1S0.AMSRF0_Exist = false;
			H1S0.AMSRF1_Site = nullptr;
			H1S0.AMSRF1_Exist = false;

			H1S1.AMSRFSupported = "NA";
			H1S1.TotalUUTOffset = 0;
			H1S1.TotalExternalModule = 0;
			H1S1.TotalSignalCore = 0;
			H1S1.AMSRF0_Site = nullptr;
			H1S1.AMSRF0_Exist = false;
			H1S1.AMSRF1_Site = nullptr;
			H1S1.AMSRF1_Exist = false;

			//Cast Information at SiteConfiguration
			SiteConfigInfoCasting(site, XmlSiteConfigInfo);
			AMSRF_Head_Site = gcnew Dictionary <String ^, String ^>(HeadSiteXml->Length);

			//Cast Information at H0S0, H0S1, H1S0 & H1S1
			for (int i = 0; i < HeadSiteXml->Length; i++)
			{
				HeadSiteInfo = HeadSiteXml[i];
				int InfoHead = HeadXmlIndex[i];
				int InfoSite = SiteXmlIndex[i];

				XmlInfo = SiteConfiqInfo->DocumentElement->FirstChild->ChildNodes[InfoHead]->ChildNodes[InfoSite];

				if (HeadSiteInfo == "H0S0")
				{
					HeadSite(site, XmlInfo, H0S0);
					AMSRF_Head_Site->Add("H0S0", H0S0.AMSRFSupported);
				}
				else if (HeadSiteInfo == "H0S1")
				{
					HeadSite(site, XmlInfo, H0S1);
					AMSRF_Head_Site->Add("H0S1", H0S1.AMSRFSupported);
				}
				else if (HeadSiteInfo == "H1S0")
				{
					HeadSite(site, XmlInfo, H1S0);
					AMSRF_Head_Site->Add("H1S0", H1S0.AMSRFSupported);
				}
				else if (HeadSiteInfo == "H1S1")
				{
					HeadSite(site, XmlInfo, H1S1);
					AMSRF_Head_Site->Add("H1S1", H1S1.AMSRFSupported);
				}
			}

			//Error Checking between H0S0, H0S1, H1S0 & H1S1
			HeadSiteAmsrfChecking();
			HeadSiteExternalModuleChecking();

			//Assign the H0S0, H0S1, H1S0 or H1S1 to CurrentHeadSite
			if (testHeadSite == "H0S0")
			{
				CurrentHeadSite = H0S0;
			}
			else if (testHeadSite == "H0S1")
			{
				CurrentHeadSite = H0S1;
			}
			else if (testHeadSite == "H1S0")
			{
				CurrentHeadSite = H1S0;
			}
			else if (testHeadSite == "H1S1")
			{
				CurrentHeadSite = H1S1;
			}

			//Cast Infomation for IsRunTest function
			tl->glob->AMSRFInfo = CurrentHeadSite.AMSRFSupported;
			if (CurrentHeadSite.AMSRFSupported->Contains("AMSRF0"))
			{
				tl->glob->Amsrf0Site = gcnew array <int>(CurrentHeadSite.AMSRF0_Site->Length);
				tl->glob->Amsrf0Site = CurrentHeadSite.AMSRF0_Site;

			}
			if (CurrentHeadSite.AMSRFSupported->Contains("AMSRF1"))
			{
				tl->glob->Amsrf1Site = gcnew array <int>(CurrentHeadSite.AMSRF1_Site->Length);
				tl->glob->Amsrf1Site = CurrentHeadSite.AMSRF1_Site;
			}
		}
		catch (Exception ^ ex)
		{
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->glob->TcrLgr.ErrorCode = ER_CONST_RFSiteConfigInfo;
			tl->ErrorHandling(site, tl->glob->TcrLgr.GlobalErrorMessage);
			//String^ ErrorMessage = "Error: Encountered error during casting informations from RFSiteConfigInfo.xml [" + tl->glob->TcrLgr.GlobalErrorMessage + "]";
			//tl->FileLogging(0, LOGGER_ERROR_TYPE, ErrorMessage);
			//tl->WriteToFileLogger(0, ErrorMessage);
			//tl->CheckError(0, ER_CONST_RFSiteConfigInfo);
		}
	}
}