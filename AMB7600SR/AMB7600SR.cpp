#include "AMB7600SR.h"

namespace Functions
{
	// AMB5600TestLibrary Contsructor and Destructor 
	AMB7600SRTestLibrary::AMB7600SRTestLibrary(TestFunction ^ TestFunc)
	{
		tl = TestFunc;

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
			tl->WriteToLogger(siteIndex, "Initializing Aemulus Tester...");
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

#pragma region "Methods Initialization"

			InitializeCMDictionary(TotalSite);
			InitializeTMDicionary(TotalSite);

#pragma endregion "Methods Initialization"

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
			tl->ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
			throw gcnew Aemulus::Hardware::AlarmException(ex->ToString(),ex->HResult);
		}

		for (siteIndex = 0; siteIndex < TotalSite; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "Initialized Aemulus Tester");
		}

		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeTester(Site ^ site)
	{
		int ret = 0;
		int siteIndex = 0;

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToLogger(siteIndex, "Uninitializing Aemulus Tester...");
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
			tl->WriteToLogger(siteIndex, "Uninitialized Aemulus Tester");
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
			//tl->WriteToLogger(0, ErrorMessage);
			//tl->CheckError(0, ER_CONST_RFSiteConfigInfo);
		}
	}
	void AMB7600SRTestLibrary::THROWEXCEPTION(int siteIndex, String^ errorMessage, int errorCode, int errorLineNumber, char* fileName)
	{
		/*****************************************************************************************************
		** ThrowException
		** Arguments:
		**		siteIndex - This is UUT offset index for the selected site.
		**		errorLineNumber - This is the line in test program where the error happens.
		**		errorMessage - This is a meaning error message associated to the errorCode.
		**		errorCode - This is the error code.
		** Descriptions:
		**		This method is to throw generic exception.
		******************************************************************************************************/

		String ^ exceptionMessageFormat = "\nSite Index={0};\nFile Name={1};\nLine Number={2};\nError Code={3};\nError Message={4}";

		String^ _fileName = gcnew String(fileName);
		_fileName = _fileName->Remove(0, 2);
		StringBuilder ^ sb = gcnew StringBuilder();
		sb->AppendFormat(exceptionMessageFormat, siteIndex.ToString(), _fileName, errorLineNumber, errorCode, errorMessage);

		if (debug)
		{
			tracerLogger->WriteToTracer(MainTracer, "sb->ToString()");
		}
		Exception(sb->ToString());
	}
	void AMB7600SRTestLibrary::THROWEXCEPTION(String^ errorMessage, int errorCode, int errorLineNumber, char* fileName)
	{
		/*****************************************************************************************************
		** ThrowException
		** Arguments:
		**		errorLineNumber - This is the line in test program where the error happens.
		**		errorMessage - This is a meaning error message associated to the errorCode.
		**		errorCode - This is the error code.
		** Descriptions:
		**		This method is to throw generic exception (site independent).
		******************************************************************************************************/

		String ^ exceptionMessageFormat = "\nFile Name={0};\nLine Number={1};\nError Code={2};\nError Message={3}";

		String^ _fileName = gcnew String(fileName);
		_fileName = _fileName->Remove(0, 2);
		StringBuilder ^ sb = gcnew StringBuilder();
		sb->AppendFormat(exceptionMessageFormat, _fileName, errorLineNumber, errorCode, errorMessage);

		if (debug)
		{
			tracerLogger->WriteToTracer(MainTracer, "sb->ToString()");
		}

		Exception(sb->ToString());
	}
	int AMB7600SRTestLibrary::CHECKERROR(int siteIndex, long errorCode, int errorLineNumber, char* fileName)
	{
		/*****************************************************************************************************
		** CheckError
		** Arguments:
		**		siteIndex - This is UUT offset index for the selected site.
		**		resourceAlias - This is the alias of the selected resource. This can be pinAlias or moduleAlias.
		**		errorCode - This is the error code.
		**		errorLineNumber - This is the line number in tets program where last error happens.
		** Descriptions:
		**		This method is to check whether the last operation has any error, by interpreting the given
		**		errorCode. If error happens (non-zero return code), an exception will be thrown to techFlow,
		**		together with the error message as well as the line where it happens.
		******************************************************************************************************/

		String ^ errorMessage = String::Empty;
		StringBuilder ^ sa = gcnew StringBuilder(256);
		int ret = 0;

		String ^ exceptionMessageFormat = "\nSite Index={0};\nFile Name={1};\nLine Number={2};\nError Code={3};\nError Message={4}";

		if (errorCode.ToString("X")->StartsWith("AE")) //Check whether it's AEM resources (error code starts with 0xAE)
		{
			if (errorCode.ToString("X")->StartsWith("AE09")) //0xAE09 = General
			{
				errorMessage = "Aemulus PXIE General error";
			}
			else if (errorCode.ToString("X")->StartsWith("AE07")) //0xAE07 = AM //sk@20180902 - enable error checking
			{
				ret = smu[siteIndex]->GetErrorMessage(resourceAM, errorCode, errorMessage);
				errorMessage = "SMU error";//sa->ToString(); 
			}
			//else if (errorCode.ToString("X")->StartsWith("AE08")) //0xAE08 = IOM //sk@20180902 - enable error checking
			//{
			//ret = dio[siteIndex]->GetErrorMessage(resourceIOM, errorCode, errorMessage);
			//}
			else if (errorCode.ToString("X")->StartsWith("AE0B") || errorCode.ToString("X")->StartsWith("AE04")) //0xAE0B = DM
			{
				ret = dm[siteIndex]->GetErrorMessage(resourceDM, errorCode, sa);
				//errorMessage = "DM error";//sa->ToString(); 
				errorMessage = sa->ToString(); //sk@20180902 - enable real DM error message display
			}
			if (errorCode.ToString("X")->StartsWith("AE10")) //0xAE10 = AMB7600
			{
				switch (errorCode)
				{
				case ER_OPERATION_HALTED_BY_USER:	errorMessage = "ER_OPERATION_HALTED_BY_USER"; break;
				case ER_PREREQUISITE_NOT_MET:		errorMessage = "ER_PREREQUISITE_NOT_MET"; break;
				case ER_ILLEGAL_OPERATION:			errorMessage = "ER_ILLEGAL_OPERATION"; break;
				case ER_NO_CALIBRATION_RECORD:		errorMessage = "ER_NO_CALIBRATION_RECORD"; break;
				case ER_CALIBRATION_DUE:			errorMessage = "ER_CALIBRATION_DUE"; break;
				case ER_INVALID_USER_INPUT:			errorMessage = "ER_INVALID_USER_INPUT"; break;
				case ER_INVALID_QUERY:				errorMessage = "ER_INVALID_QUERY"; break;
				case ER_STATION_ID_OCCUPIED:		errorMessage = "ER_STATION_ID_OCCUPIED"; break;
				case ER_MODULATION_OVERLOADED:		errorMessage = "ER_MODULATION_OVERLOADED"; break;
				case ER_MODULATION_NOT_LOADED:		errorMessage = "ER_MODULATION_NOT_LOADED"; break;
				case ER_MODULATION_ALREADY_LOADED:	errorMessage = "ER_MODULATION_ALREADY_LOADED"; break;
				case ER_RESOURCE_ALREADY_GRANTED:	errorMessage = "ER_RESOURCE_ALREADY_GRANTED"; break;
				case ER_CORRELATION_ERROR:			errorMessage = "ER_CORRELATION_ERROR"; break;
				case ER_INVALID_SETTING:			errorMessage = "ER_INVALID_SETTING"; break;
				case ER_CALIBRATION_OUT_OF_SPECS:	errorMessage = "ER_CALIBRATION_OUT_OF_SPECS"; break;
				case ER_UNSUPPORTED_OFFLINE:		errorMessage = "ER_UNSUPPORTED_OFFLINE"; break;
				case ER_ENFORCED_OFFLINE:			errorMessage = "ER_ENFORCED_OFFLINE"; break;
				case ER_SOFTWARE_TIMEOUT:			errorMessage = "ER_SOFTWARE_TIMEOUT"; break;
				case ER_HADWARE_TIMEOUT:			errorMessage = "ER_HADWARE_TIMEOUT"; break;
				case ER_EXCEED_MAX_SAMPLE_SZIE:		errorMessage = "ER_EXCEED_MAX_SAMPLE_SZIE"; break;
				case ER_MISSING_CALIBRATION_FILE:	errorMessage = "ER_MISSING_CALIBRATION_FILE"; break;
				case ER_NO_TESTHEAD:				errorMessage = "ER_NO_TESTHEAD"; break;
				case ER_NO_TESTSITE:				errorMessage = "ER_NO_TESTSITE"; break;
				case ER_API_NOT_SUPPORTED:			errorMessage = "ER_API_NOT_SUPPORTED"; break;
				case ER_LOAD_DLL_FILE_ERROR:		errorMessage = "ER_LOAD_DLL_FILE_ERROR"; break;
				case ER_LOAD_DLL_FUNCTION_ERROR:	errorMessage = "ER_LOAD_DLL_FUNCTION_ERROR"; break;
				case ER_MEMORY_ALLOCATION_ERROR:	errorMessage = "ER_MEMORY_ALLOCATION_ERROR"; break;
				case ER_FILE_IO_ERROR:				errorMessage = "ER_FILE_IO_ERROR"; break;
				case ER_MISSING_GLOBAL_COND:		errorMessage = "ER_MISSING_GLOBAL_COND"; break;
				case ER_MISSING_FLOWITEM_COND:		errorMessage = "ER_MISSING_FLOWITEM_COND"; break;
				case ER_MISSING_TESTPARAM_COND:		errorMessage = "ER_MISSING_TESTPARAM_COND"; break;
				case ER_INVALID_COMMAND:			errorMessage = "ER_INVALID_COMMAND"; break;
				case ER_INVALID_COMMAND_ARGUMENTS:	errorMessage = "ER_INVALID_COMMAND_ARGUMENTS"; break;
				case ER_REGISTER_INSTRUMENT_ERROR:	errorMessage = "ER_REGISTER_INSTRUMENT_ERROR"; break;
				case ER_INIT_INSTRUMENT_ERROR:		errorMessage = "ER_INIT_INSTRUMENT_ERROR"; break;
				case ER_INSTRUMENT_READ_ERROR:		errorMessage = "ER_INSTRUMENT_READ_ERROR"; break;
				case ER_INSTRUMENT_WRITE_ERROR:		errorMessage = "ER_INSTRUMENT_WRITE_ERROR"; break;
				case ER_INCOMPATIBLE_HARDWARE:		errorMessage = "ER_INCOMPATIBLE_HARDWARE"; break;
				case ER_UNINIT_INSTRUMENT_ERROR:	errorMessage = "ER_UNINIT_INSTRUMENT_ERROR"; break;
				case ER_VOLTAGE_OUT_OF_RANGE:		errorMessage = "ER_VOLTAGE_OUT_OF_RANGE"; break;
				case ER_CURRENT_OUT_OF_RANGE:		errorMessage = "ER_CURRENT_OUT_OF_RANGE"; break;
				case ER_INVALID_RESOURCE_PIN:		errorMessage = "ER_INVALID_RESOURCE_PIN"; break;
				case ER_CONST_RFSiteConfigInfo:		errorMessage = "Please check the contents inside the RFSiteConfigInfo.xml"; break;

				}
			}
			else
			{
				errorMessage = "Unknown error";
			}
		}
		else if (siteIndex == RF0 && errorCode != 0)
		{
			//ret = Amsrf1->amsrf->GetErrorCodeMessage(errorCode, errorMessage); //sk@20180902 - enable RF error message logging
			errorMessage == "ER_AMSRF";
		}
		else if (errorCode == 160) //ERROR_BAD_ARGUMENTS
		{
			errorMessage = "ERROR_BAD_ARGUMENTS";
		}
		else if (errorCode == 8) //ERROR_NOT_ENOUGH_MEMORY
		{
			errorMessage = "ERROR_NOT_ENOUGH_MEMORY";

		}
		else if (errorCode == 110) //ERROR_OPEN_FAILED
		{
			errorMessage = "ERROR_OPEN_FAILED";
		}
		else if (errorCode == ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED)
		{
			errorMessage = "ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED";
		}
		else if (errorCode == ER_CONST_GENERAL)
		{
			errorMessage = "ER_CONST_GENERAL";
		}
		else if (errorCode == ER_CONST_TIMEOUT)
		{
			errorMessage = "ER_CONST_TIMEOUT";
		}
		else if (errorCode == ER_CONST_FILE_NOT_FOUND)
		{
			errorMessage = "ER_CONST_FILE_NOT_FOUND";
		}
		else if (errorCode == ER_CONST_READ_FILE_ERROR)
		{
			errorMessage = "ER_CONST_READ_FILE_ERROR";
		}
		else if (errorCode == ER_CONST_INVALID_SETTING)
		{
			errorMessage = "ER_CONST_INVALID_SETTING";
		}
		else if (errorCode == ER_CONST_NOT_FOUND)
		{
			errorMessage = "ER_CONST_NOT_FOUND";
		}
		else if (errorCode == ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED)
		{
			errorMessage = "ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED";
		}
		else if (errorCode == ER_CONST_RESOURCE_MANAGER)
		{
			errorMessage = "ER_CONST_RESOURCE_MANAGER";
		}
		else
		{
			errorMessage = "Unknown error";
		}

		if (sa)
		{
			sa->Length = 0;
			sa = nullptr;
		}

		if (errorCode != 0)
		{
			if (siteIndex < 0 || siteIndex > totalSite)
				siteIndex = 0;

			glob->RunTimeErrorCode[siteIndex] = errorCode;

			String^ _fileName = gcnew String(fileName);
			_fileName = _fileName->Remove(0, 2);
			StringBuilder ^ sb = gcnew StringBuilder();
			sb->AppendFormat(exceptionMessageFormat, siteIndex.ToString(), _fileName, errorLineNumber, errorCode, errorMessage);
			glob->RunTimeError[siteIndex] = true;

			if (debug)
			{
				tracerLogger->WriteToTracer(MainTracer, sb->ToString());
			}

			throw gcnew Exception(sb->ToString());
		}

		return ret;
	}
	int AMB7600SRTestLibrary::CHECKERROR(long errorCode, int errorLineNumber, char* fileName)
	{
		/*****************************************************************************************************
		** CheckError
		** Arguments:
		**		errorCode - This is the error code.
		**		errorLineNumber - This is the line number in tets program where last error happens.
		** Descriptions:
		**		This method is to check whether the last operation has any error, by interpreting the given
		**		errorCode. If error happens (non-zero return code), an exception will be thrown to techFlow,
		**		together with the error message as well as the line where it happens.
		**		This is for non-hardware related errors.
		******************************************************************************************************/

		String ^ errorMessage = String::Empty;
		StringBuilder ^ sa = gcnew StringBuilder(256);
		int ret = 0;

		String ^ exceptionMessageFormat = "\nFile Name={0};\nLine Number={1};\nError Code={2};\nError Message={3}";

		if (errorCode == ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED)
		{
			errorMessage = "ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED";
		}
		else if (errorCode == ER_CONST_GENERAL)
		{
			errorMessage = "ER_CONST_GENERAL";
		}
		else if (errorCode == ER_CONST_TIMEOUT)
		{
			errorMessage = "ER_CONST_TIMEOUT";
		}
		else if (errorCode == ER_CONST_FILE_NOT_FOUND)
		{
			errorMessage = "ER_CONST_FILE_NOT_FOUND";
		}
		else if (errorCode == ER_CONST_READ_FILE_ERROR)
		{
			errorMessage = "ER_CONST_READ_FILE_ERROR";
		}
		else if (errorCode == ER_CONST_INVALID_SETTING)
		{
			errorMessage = "ER_CONST_INVALID_SETTING";
		}
		else if (errorCode == ER_CONST_NOT_FOUND)
		{
			errorMessage = "ER_CONST_NOT_FOUND";
		}
		else if (errorCode == ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED)
		{
			errorMessage = "ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED";
		}
		else if (errorCode == ER_CONST_RESOURCE_MANAGER)
		{
			errorMessage = "ER_CONST_RESOURCE_MANAGER";
		}
		else if (errorCode == ER_CONST_RFSiteConfigInfo)
		{
			errorMessage = "Please check the contents inside the RFSiteConfigInfo.xml";
		}
		else
		{
			errorMessage = "Unknown error";
		}

		if (sa)
		{
			sa->Length = 0;
			sa = nullptr;
		}

		if (errorCode != 0)
		{
			glob->RunTimeErrorCode[0] = errorCode; //default to "0" for non-hardware error

			String^ _fileName = gcnew String(fileName);
			_fileName = _fileName->Remove(0, 2);
			StringBuilder ^ sb = gcnew StringBuilder();
			sb->AppendFormat(exceptionMessageFormat, _fileName, errorLineNumber, errorCode, errorMessage);

			if (debug)
			{
				tracerLogger->WriteToTracer(MainTracer, sb->ToString());
			}

			Exception(sb->ToString());
		}

		return ret;
	}
}