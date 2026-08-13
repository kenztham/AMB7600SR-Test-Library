#include "AMB7600SR.h"

namespace Functions 
{
	//SiteConfig
	void AMB7600SRTestLibrary::HeadSite(Site ^ site, XmlNode ^ XmlInfo, SiteConfigInfo  % SiteInfo)
	{
		String ^ Site_ChildNode = nullptr;
		String ^ ErrorMessage = nullptr;
		array<int, 2>^ SiteChecking;

		int SiteCheckingColumn = 0;
		int SiteCheckingRow = 0;

		SiteInfo.AMSRF0_Exist = false;
		SiteInfo.AMSRF1_Exist = false;
		SiteInfo.AMSRF0_Site = nullptr;
		SiteInfo.AMSRF1_Site = nullptr;
		SiteInfo.TotalUUTOffset = 0;
		SiteInfo.TotalSignalCore = 0;
		SiteInfo.TotalExternalModule = 0;
		SiteInfo.ExternalModuleList = gcnew List<Dictionary<String^, String^>^>();

		for (int i = 0; i < XmlInfo->ChildNodes->Count; i++)
		{
			Site_ChildNode = XmlInfo->ChildNodes[i]->Name;

			if (Site_ChildNode == "AMSRF0" || Site_ChildNode == "AMSRF1")
			{
				AMSRFInfoCasting(site, XmlInfo->ChildNodes[i], SiteInfo);
			}
			else if (Site_ChildNode == "ExternalModule")
			{
				ExternalModuleInfoCasting(site, XmlInfo->ChildNodes[i], SiteInfo);
			}
			else
			{
				ErrorMessage = Site_ChildNode + " is not supported at " + HeadSiteInfo + ". Only AMSRF0, AMSRF1 or ExternalModule is supported.";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}

		AMSRFInfoChecking(SiteInfo);
		ExternalModuleInfoChecking(SiteInfo);

		if (SiteInfo.AMSRF0_Exist == true && SiteInfo.AMSRF1_Exist == false)
		{
			SiteInfo.AMSRFSupported = "AMSRF0";
		}
		else if (SiteInfo.AMSRF0_Exist == false && SiteInfo.AMSRF1_Exist == true)
		{
			SiteInfo.AMSRFSupported = "AMSRF1";
		}
		else if (SiteInfo.AMSRF0_Exist == true && SiteInfo.AMSRF1_Exist == true)
		{
			SiteInfo.AMSRFSupported = "AMSRF0_AMSRF1";
		}
	}
	void AMB7600SRTestLibrary::SiteConfigInfoCasting(Site ^ site, XmlNode ^ XmlInfo)
	{

		String ^ErrorMessage = nullptr;
		String ^ Name = XmlInfo->FirstChild->Name;
		String ^ InnerText = XmlInfo->FirstChild->InnerText;


		if (Name == "SiteConfiguration")
		{
			if (InnerText != "Single TechFlow Site" && InnerText != "True Parallel" && InnerText != "Index Parallel")
			{
				ErrorMessage = InnerText + " is not supported under the SiteConfiguration.";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
			else
			{
				SiteConfig = InnerText;
			}
		}
		else
		{
			ErrorMessage = Name + " is not equal to SiteConfiguration.";
			throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
		}

		SiteConfigInfoChecking(site, XmlInfo);
		TotalHeadCountInfo(site, XmlInfo);
		HeadSiteXmlInfo(site, XmlInfo);

	}
	void AMB7600SRTestLibrary::SiteConfigInfoChecking(Site ^ site, XmlNode ^ XmlInfo)
	{

		String ^ ErrorMessage = nullptr;

		if (SiteConfig == "Single TechFlow Site")
		{
			if (XmlInfo->ChildNodes->Count == 2)
			{
				//H0S0
				if (XmlInfo->ChildNodes[1]->Name == "H0")
				{
					if (!XmlInfo->ChildNodes[1]->HasChildNodes)
					{
						ErrorMessage = "Inside H0 " + "do not have information for Site0.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes->Count > 1)
					{
						ErrorMessage = "Inside H0 " + "only Site0 are allowed.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes[0]->Name != "Site0")
					{
						ErrorMessage = "Inside H0 " + "Site0 is not found.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
				else
				{
					ErrorMessage = "H0 " + "is not found.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}
			else if (XmlInfo->ChildNodes->Count == 3)
			{
				//H0S0
				if (XmlInfo->ChildNodes[1]->Name == "H0")
				{
					if (!XmlInfo->ChildNodes[1]->HasChildNodes)
					{
						ErrorMessage = "Inside H0 " + "do not have information for Site0.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes->Count > 1)
					{
						ErrorMessage = "Inside H0 " + "only Site0 are allowed.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes[0]->Name != "Site0")
					{
						ErrorMessage = "Inside H0 " + "Site0 is not found.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
				else
				{
					ErrorMessage = "Inside H0 " + "is not found.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}

				//H1S0
				if (XmlInfo->ChildNodes[2]->Name == "H1")
				{
					if (!XmlInfo->ChildNodes[2]->HasChildNodes)
					{
						ErrorMessage = "Inside H1 " + "do not have information for Site0.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[2]->ChildNodes->Count > 1)
					{
						ErrorMessage = "Inside H1 " + "only Site0 are allowed.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[2]->ChildNodes[0]->Name != "Site0")
					{
						ErrorMessage = "Inside H1 " + "Site0 is not found.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
				else
				{
					ErrorMessage = "Inside H1 " + "is not found.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}

		}
		else if (SiteConfig == "True Parallel")
		{
			//H0S0 & H0S1
			if (XmlInfo->ChildNodes->Count == 2)
			{
				if (XmlInfo->ChildNodes[1]->Name != "H0")
				{
					ErrorMessage = "H0 " + "is not found.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (!XmlInfo->ChildNodes[1]->HasChildNodes)
				{
					ErrorMessage = "Inside H0 " + "do not have information for Site0 or Site1.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (XmlInfo->ChildNodes[1]->ChildNodes->Count != 2)
				{
					ErrorMessage = "Inside H0 " + "only Site0 & Site1 are allowed.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (XmlInfo->ChildNodes[1]->ChildNodes[0]->Name != "Site0")
				{
					ErrorMessage = "Inside H0 " + "Site0 is missing.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (XmlInfo->ChildNodes[1]->ChildNodes[1]->Name != "Site1")
				{
					ErrorMessage = "Inside H0 " + "Site1 is missing.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}
			else
			{
				ErrorMessage = "SiteConfiguration or H0 " + "is not found.";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}
		else if (SiteConfig == "Index Parallel")
		{
			//H0S0 or H0S1
			if (XmlInfo->ChildNodes->Count == 2)
			{
				if (XmlInfo->ChildNodes[1]->ChildNodes->Count == 2)
				{
					if (XmlInfo->ChildNodes[1]->Name != "H0")
					{
						ErrorMessage = "H0 " + "is not found.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (!XmlInfo->ChildNodes[1]->HasChildNodes)
					{
						ErrorMessage = "Inside H0 " + "do not have information for Site0 or Site1.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes[0]->Name != "Site0")
					{
						ErrorMessage = "Inside H0 " + "Site0 is missing.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes[1]->Name != "Site1")
					{
						ErrorMessage = "Inside H0 " + "Site1 is missing.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
				else if (XmlInfo->ChildNodes[1]->ChildNodes->Count == 1)
				{
					if (XmlInfo->ChildNodes[1]->Name != "H0")
					{
						ErrorMessage = "H0 " + "is not found.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (!XmlInfo->ChildNodes[1]->HasChildNodes)
					{
						ErrorMessage = "Inside H0 " + "do not have information for Site1.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
					if (XmlInfo->ChildNodes[1]->ChildNodes[0]->Name != "Site1")
					{
						ErrorMessage = "Inside H0 " + "Site1 is missing.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
			}
			//H0S1 & H1S1
			else if (XmlInfo->ChildNodes->Count == 3)
			{
				if (XmlInfo->ChildNodes[1]->Name != "H0")
				{
					ErrorMessage = "H0 " + "is not found.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (!XmlInfo->ChildNodes[1]->HasChildNodes)
				{
					ErrorMessage = "Inside H0 " + "do not have information for Site1.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (XmlInfo->ChildNodes[1]->ChildNodes[0]->Name != "Site1")
				{
					ErrorMessage = "Inside H0 " + "Site1 is missing.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}

				if (XmlInfo->ChildNodes[2]->Name != "H1")
				{
					ErrorMessage = "H1 " + "is not found.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (!XmlInfo->ChildNodes[2]->HasChildNodes)
				{
					ErrorMessage = "Inside H1 " + "do not have information for Site1.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
				if (XmlInfo->ChildNodes[2]->ChildNodes[0]->Name != "Site1")
				{
					ErrorMessage = "Inside H1 " + "Site1 is missing.";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}
			else
			{
				ErrorMessage = "SiteConfiguration & H0 " + "is not found.";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}

	}
	void AMB7600SRTestLibrary::TotalHeadCountInfo(Site ^ site, XmlNode ^ XmlInfo)
	{

		String ^ ErrorMessage = nullptr;

		if (XmlInfo->ChildNodes->Count == 2)
		{
			TotalHeadCount = 1;
		}
		else if (XmlInfo->ChildNodes->Count == 3)
		{
			TotalHeadCount = 2;
		}
		else if (XmlInfo->ChildNodes->Count == 1 || XmlInfo->ChildNodes->Count > 3)
		{
			ErrorMessage = "Check the availablity of SiteConfiguration, H0 or H1.";
			throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
		}

	}
	void AMB7600SRTestLibrary::HeadSiteXmlInfo(Site ^ site, XmlNode ^ XmlInfo)
	{

		if (SiteConfig == "Single TechFlow Site")
		{
			if (XmlInfo->ChildNodes->Count == 2)
			{
				HeadSiteXml = gcnew array<String ^>(1);
				HeadXmlIndex = gcnew array<int>(1);
				SiteXmlIndex = gcnew array<int>(1);

				HeadSiteXml[0] = "H0S0";
				HeadXmlIndex[0] = 1;
				SiteXmlIndex[0] = 0;

			}
			else if (XmlInfo->ChildNodes->Count == 3)
			{
				HeadSiteXml = gcnew array<String ^>(2);
				HeadXmlIndex = gcnew array<int>(2);
				SiteXmlIndex = gcnew array<int>(2);
				HeadSiteXml[0] = "H0S0";
				HeadSiteXml[1] = "H1S0";
				HeadXmlIndex[0] = 1;
				SiteXmlIndex[0] = 0;
				HeadXmlIndex[1] = 2;
				SiteXmlIndex[1] = 0;
			}
		}
		else if (SiteConfig == "True Parallel")
		{
			if (XmlInfo->ChildNodes->Count == 2)
			{
				HeadSiteXml = gcnew array<String ^>(2);
				HeadXmlIndex = gcnew array<int>(2);
				SiteXmlIndex = gcnew array<int>(2);
				HeadSiteXml[0] = "H0S0";
				HeadSiteXml[1] = "H0S1";
				HeadXmlIndex[0] = 1;
				SiteXmlIndex[0] = 0;
				HeadXmlIndex[1] = 1;
				SiteXmlIndex[1] = 1;
			}
		}
		else if (SiteConfig == "Index Parallel")
		{
			if (XmlInfo->ChildNodes->Count == 2)
			{
				if (XmlInfo->ChildNodes[1]->ChildNodes->Count == 2)
				{
					HeadSiteXml = gcnew array<String ^>(2);
					HeadXmlIndex = gcnew array<int>(2);
					SiteXmlIndex = gcnew array<int>(2);
					HeadSiteXml[0] = "H0S0";
					HeadSiteXml[1] = "H0S1";
					HeadXmlIndex[0] = 1;
					SiteXmlIndex[0] = 0;
					HeadXmlIndex[1] = 1;
					SiteXmlIndex[1] = 1;
				}
				else if (XmlInfo->ChildNodes[1]->ChildNodes->Count == 1)
				{
					HeadSiteXml = gcnew array<String ^>(1);
					HeadXmlIndex = gcnew array<int>(1);
					SiteXmlIndex = gcnew array<int>(1);
					HeadSiteXml[0] = "H0S1";
					HeadXmlIndex[0] = 1;
					SiteXmlIndex[0] = 0;

				}
			}
			else if (XmlInfo->ChildNodes->Count == 3)
			{
				HeadSiteXml = gcnew array<String ^>(2);
				HeadXmlIndex = gcnew array<int>(2);
				SiteXmlIndex = gcnew array<int>(2);
				HeadSiteXml[0] = "H0S1";
				HeadSiteXml[1] = "H1S1";
				HeadXmlIndex[0] = 1;
				SiteXmlIndex[0] = 0;
				HeadXmlIndex[1] = 2;
				SiteXmlIndex[1] = 0;
			}
		}
	}
	//AMSRF
	void AMB7600SRTestLibrary::AMSRFInfoCasting(Site ^ site, XmlNode ^ AMSRFxml, SiteConfigInfo  % SiteInfo)
	{

		array<Char>^ Separator = { ' ' };
		array<String^>^AMSRF_Site_String;
		String ^ErrorMessage = nullptr;
		String ^ AMSRFtype = AMSRFxml->Name;

		if (AMSRFxml->Attributes->Count != 1)
		{
			ErrorMessage = "There is no attribute Exist at " + AMSRFtype + " for " + HeadSiteInfo + ".";
			throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
		}

		XmlAttributeCollection   ^ Site_ChildNode_AMSRF_Att = AMSRFxml->Attributes;
		String ^ ExistAttributeName = Site_ChildNode_AMSRF_Att[0]->Name;
		bool ExistAttributeValue = bool::Parse(Site_ChildNode_AMSRF_Att[0]->Value);

		if (ExistAttributeName == "Exist")
		{
			if (ExistAttributeValue == true)
			{
				if (AMSRFtype == "AMSRF0" && SiteInfo.AMSRF0_Exist == false)
				{
					AMSRF_Site_String = nullptr;
					AMSRF_Site_String = AMSRFxml->InnerText->Split(Separator, StringSplitOptions::None);

					StringArrayToIntArray(AMSRF_Site_String, SiteInfo.AMSRF0_Site);

					SiteInfo.AMSRF0_Exist = true;
				}
				else if (AMSRFtype == "AMSRF1" && SiteInfo.AMSRF1_Exist == false)
				{
					AMSRF_Site_String = nullptr;
					AMSRF_Site_String = AMSRFxml->InnerText->Split(Separator, StringSplitOptions::None);

					StringArrayToIntArray(AMSRF_Site_String, SiteInfo.AMSRF1_Site);

					SiteInfo.AMSRF1_Exist = true;
				}
				else
				{
					ErrorMessage = "Multiple " + AMSRFtype + " has exist at " + HeadSiteInfo + ".";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}
			else if (ExistAttributeValue == false)
			{
				if (AMSRFxml->Name == "AMSRF0")
				{
					SiteInfo.AMSRF0_Exist = false;
				}
				else if (AMSRFxml->Name == "AMSRF1")
				{
					SiteInfo.AMSRF1_Exist = false;
				}
			}
			else
			{
				ErrorMessage = "Exist attribute value = " + ExistAttributeValue.ToString() + " is not supported at " + HeadSiteInfo + " as only true or false value is available";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}
		else
		{
			ErrorMessage = "There is no attribute Exist at " + AMSRFtype + " at " + HeadSiteInfo + ".";
			throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
		}


	}
	void AMB7600SRTestLibrary::AMSRFInfoChecking(SiteConfigInfo SiteInfo)
	{

		int Amsrf0SameValueExist = 0;
		int Amsrf1SameValueExist = 0;
		int Amsrf0Amsrf1SameValueExist = 0;
		int TotalAmsrf0Site = 0;
		int TotalAmsrf1Site = 0;

		String ^ ErrorMessage = nullptr;

		if (SiteInfo.AMSRF0_Exist == true)
		{
			TotalAmsrf0Site = SiteInfo.AMSRF0_Site->Length;
		}
		if (SiteInfo.AMSRF1_Exist == true)
		{
			TotalAmsrf1Site = SiteInfo.AMSRF1_Site->Length;
		}

		SiteInfo.TotalUUTOffset = TotalAmsrf0Site + TotalAmsrf1Site;

		array<int>^ SiteIndex = gcnew array<int>(SiteInfo.TotalUUTOffset);
		array<int>^ SiteCheckingDone = gcnew array<int>(SiteInfo.TotalUUTOffset);

		for (int i = 0; i < SiteInfo.TotalUUTOffset; i++)
		{
			SiteIndex[i] = i;
			SiteCheckingDone[i] = 0;
		}

		//Checking any duplicate site at AMSRF0 
		if (SiteInfo.AMSRF0_Exist == true)
		{
			for (int i = 0; i < SiteInfo.AMSRF0_Site->Length; i++)
			{
				for (int j = i + 1; j < SiteInfo.AMSRF0_Site->Length; j++)
				{
					if (SiteInfo.AMSRF0_Site[i] == SiteInfo.AMSRF0_Site[j])
					{
						Amsrf0SameValueExist++;
						i = SiteInfo.AMSRF0_Site->Length;
						break;
					}
				}
			}

			if (Amsrf0SameValueExist > 0)
			{
				ErrorMessage = "Same testSite value exist at AMSRF0 at " + HeadSiteInfo + ".";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}

		//Checking any duplicate site at AMSRF1 
		if (SiteInfo.AMSRF1_Exist == true)
		{
			for (int i = 0; i < SiteInfo.AMSRF1_Site->Length; i++)
			{
				for (int j = i + 1; j < SiteInfo.AMSRF1_Site->Length; j++)
				{
					if (SiteInfo.AMSRF1_Site[i] == SiteInfo.AMSRF1_Site[j])
					{
						Amsrf1SameValueExist++;
						i = SiteInfo.AMSRF1_Site->Length;
						break;
					}
				}
			}

			if (Amsrf1SameValueExist > 0)
			{
				ErrorMessage = "Same testSite value exist at AMSRF1 at " + HeadSiteInfo + "..";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}

		//Checking any duplicate site between AMSRF0 & AMSRF1 
		if (SiteInfo.AMSRF0_Exist == true && SiteInfo.AMSRF1_Exist == true)
		{
			for (int i = 0; i < SiteInfo.AMSRF0_Site->Length; i++)
			{
				for (int j = 0; j < SiteInfo.AMSRF1_Site->Length; j++)
				{
					if (SiteInfo.AMSRF0_Site[i] == SiteInfo.AMSRF1_Site[j])
					{
						Amsrf0Amsrf1SameValueExist++;
						i = SiteInfo.AMSRF0_Site->Length;
						break;
					}
				}
			}

			if (Amsrf0Amsrf1SameValueExist > 0)
			{
				ErrorMessage = "Same testSite value exist at AMSRF0 & AMSRF1 at " + HeadSiteInfo + ".";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}

		//Checking the avaliablity site of AMSRF0 or AMSRF1 
		if (SiteInfo.AMSRF0_Exist == true || SiteInfo.AMSRF1_Exist == true)
		{
			if (SiteInfo.AMSRF0_Exist == true)
			{
				for (int i = 0; i < SiteInfo.TotalUUTOffset; i++)
				{
					if (SiteCheckingDone[i] == 0)
					{
						for (int j = 0; j < SiteInfo.AMSRF0_Site->Length; j++)
						{
							if (SiteIndex[i] == SiteInfo.AMSRF0_Site[j])
							{
								SiteCheckingDone[i] = 1;
								break;
							}
						}
					}
				}
			}

			if (SiteInfo.AMSRF1_Exist == true)
			{
				for (int i = 0; i < SiteInfo.TotalUUTOffset; i++)
				{
					if (SiteCheckingDone[i] == 0)
					{
						for (int j = 0; j < SiteInfo.AMSRF1_Site->Length; j++)
						{
							if (SiteIndex[i] == SiteInfo.AMSRF1_Site[j])
							{
								SiteCheckingDone[i] = 1;
								break;
							}
						}
					}
				}
			}

			for (int i = 0; i < SiteInfo.TotalUUTOffset; i++)
			{
				if (SiteCheckingDone[i] == 0)
				{
					ErrorMessage = "The sequnece of the testSite value for AMSRF0 or AMSRF1 is not correct at " + HeadSiteInfo + ".";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}
		}


	}
	//ExternalModule
	void AMB7600SRTestLibrary::ExternalModuleInfoCasting(Site ^ site, XmlNode ^ ExternalModule, SiteConfigInfo  % SiteInfo)
	{
		XmlAttributeCollection ^ ExternalModule_ChildNode_Att;

		Dictionary<String ^, String^>^ ExternalModuleInfo;

		String ^ ExternalModule_Name = nullptr;
		String ^ ExternalModule_Type = nullptr;
		String ^ Info = nullptr;
		String ^ ErrorMessage = nullptr;

		array<String ^> ^ ExternalModule_ChildNode = gcnew array<String^>(ExternalModule->ChildNodes->Count);
		array<String ^> ^ ExternalModule_InnerText = gcnew array<String^>(ExternalModule->ChildNodes->Count);
		array<String^>^  ExternalModule_Info;

		int ExternalModuleInfoCount;
		int ExternalModule_TotalChannel;
		int MaxSearch = 0;

		if (ExternalModule->HasChildNodes)
		{
			for (int i = 0; i < ExternalModule->ChildNodes->Count; i++)
			{
				ExternalModule_ChildNode_Att = ExternalModule->ChildNodes[i]->Attributes;

				ExternalModule_ChildNode[i] = ExternalModule->ChildNodes[i]->Name;
				ExternalModule_InnerText[i] = ExternalModule->ChildNodes[i]->InnerText;

				if (ExternalModule->ChildNodes[i]->Name == "SignalCore")
				{
					if (ExternalModule_ChildNode_Att[0]->Name == "Exist")
					{
						if (ExternalModule_ChildNode_Att[0]->Value == "true")
						{
							if (ExternalModule_ChildNode_Att[1]->Name == "Type")
							{
								ExternalModule_Info = nullptr;
								ExternalModule_TotalChannel = 0;

								if (SupportedExternalModule(ExternalModule_ChildNode_Att[1]->Value, ExternalModule_TotalChannel, ExternalModule_Info))
								{
									ExternalModuleInfoCount = 0;
									ExternalModule_Name = ExternalModule->ChildNodes[i]->Name;
									ExternalModule_Type = ExternalModule_ChildNode_Att[1]->Value;
									MaxSearch = ExternalModule_Info->Length - 1;

									ExternalModuleInfo = gcnew Dictionary<String ^, String^>();

									ExternalModuleInfo->Add("Name", ExternalModule_Name);
									ExternalModuleInfo->Add("Type", ExternalModule_Type);

									for (int a = 0; a < ExternalModule->ChildNodes[i]->ChildNodes->Count; a++)
									{
										for (int InfoCount = 0; InfoCount < ExternalModule_Info->Length; InfoCount++)
										{
											Info = ExternalModule_Info[InfoCount];

											if (ExternalModule->ChildNodes[i]->ChildNodes[a]->Name == Info)
											{
												ExternalModuleInfo->Add(ExternalModule->ChildNodes[i]->ChildNodes[a]->Name, ExternalModule->ChildNodes[i]->ChildNodes[a]->InnerText);
												break;
											}
											else if (InfoCount == MaxSearch)
											{
												ErrorMessage = ExternalModule->ChildNodes[i]->ChildNodes[a]->Name + " is not supported for Signal Core Model " + ExternalModule_Type + " at " + HeadSiteInfo + ".";
												throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
											}
										}
									}

									SiteInfo.TotalSignalCore++;
									SiteInfo.ExternalModuleList->Add(ExternalModuleInfo);
								}
								else
								{
									ErrorMessage = "Signal Core  " + i.ToString() + " Type = " + ExternalModule_ChildNode_Att[1]->Value + " is not supported at " + HeadSiteInfo + ".";
									throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
								}
							}
						}
						else if (ExternalModule_ChildNode_Att[0]->Value == "false")
						{

						}
						else
						{
							ErrorMessage = "There is no attribute Exist at SignalCore " + i.ToString() + " at " + HeadSiteInfo + ".";
							throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
						}
					}
					else
					{
						ErrorMessage = "There is no attribute Exist at SignalCore " + i.ToString() + " at " + HeadSiteInfo + ".";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
				else if (ExternalModule->ChildNodes[i]->Name == "Wolfer")
				{
					if (ExternalModule_ChildNode_Att[0]->Name == "Exist")
					{
						if (ExternalModule_ChildNode_Att[0]->Value == "true")
						{
							if (ExternalModule_ChildNode_Att[1]->Name == "Type")
							{
								ExternalModule_Info = nullptr;
								ExternalModule_TotalChannel = 0;

								if (SupportedExternalModule(ExternalModule_ChildNode_Att[1]->Value, ExternalModule_TotalChannel, ExternalModule_Info))
								{
									ExternalModuleInfoCount = 0;
									ExternalModule_Name = ExternalModule->ChildNodes[i]->Name;
									ExternalModule_Type = ExternalModule_ChildNode_Att[1]->Value;
									MaxSearch = ExternalModule_Info->Length - 1;

									ExternalModuleInfo = gcnew Dictionary<String ^, String^>();

									ExternalModuleInfo->Add("Name", ExternalModule_Name);
									ExternalModuleInfo->Add("Type", ExternalModule_Type);

									for (int a = 0; a < ExternalModule->ChildNodes[i]->ChildNodes->Count; a++)
									{
										for (int InfoCount = 0; InfoCount < ExternalModule_Info->Length; InfoCount++)
										{
											Info = ExternalModule_Info[InfoCount];

											if (ExternalModule->ChildNodes[i]->ChildNodes[a]->Name == Info)
											{
												ExternalModuleInfo->Add(ExternalModule->ChildNodes[i]->ChildNodes[a]->Name, ExternalModule->ChildNodes[i]->ChildNodes[a]->InnerText);
												break;
											}
											else if (InfoCount == MaxSearch)
											{
												ErrorMessage = ExternalModule->ChildNodes[i]->ChildNodes[a]->Name + " is not supported for Wolfer Model " + ExternalModule_Type + " at " + HeadSiteInfo + ".";
												throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
											}
										}
									}

									SiteInfo.TotalWolfer++;
									SiteInfo.ExternalModuleList->Add(ExternalModuleInfo);
								}
								else
								{
									ErrorMessage = "Wolfer  " + i.ToString() + " Type = " + ExternalModule_ChildNode_Att[1]->Value + " is not supported at " + HeadSiteInfo + ".";
									throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
								}
							}
						}
						else if (ExternalModule_ChildNode_Att[0]->Value == "false")
						{

						}
						else
						{
							ErrorMessage = "There is no attribute Exist at Wolfer " + i.ToString() + " at " + HeadSiteInfo + ".";
							throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
						}
					}
					else
					{
						ErrorMessage = "There is no attribute Exist at Wolfer " + i.ToString() + " at " + HeadSiteInfo + ".";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
				else
				{
					ErrorMessage = "ExternalModule " + ExternalModule->ChildNodes[i]->Name + " is not supported at " + HeadSiteInfo + ".";
					throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
				}
			}

			SiteInfo.TotalExternalModule = SiteInfo.ExternalModuleList->Count;
		}
		else
		{
			SiteInfo.TotalExternalModule = 0;
		}
	}
	void AMB7600SRTestLibrary::ExternalModuleInfoChecking(SiteConfigInfo SiteInfo)
	{
		String ^ ErrorMessage = nullptr;

		if (SiteInfo.TotalExternalModule != 0)
		{
			int FrequencyAmsrf0Appear = 0;
			int FrequencyAmsrf1Appear = 0;
			int AddressCount = 0;
			String ^ ExternalModuleName = nullptr;
			String ^ ExternalModuleType = nullptr;
			String ^ ExternalModuleAddress = nullptr;
			array<String ^ >^Address = gcnew array <String ^>(SiteInfo.ExternalModuleList->Count);


			//Checking any duplicate AMSRF used at all existing ExternalModule CH
			for each (Dictionary<String^, String^>^ Index in SiteInfo.ExternalModuleList)
			{
				for each(KeyValuePair<String^, String^>^ ExternalModule in Index)
				{
					if (ExternalModule->Key->Contains("Name"))
					{
						ExternalModuleName = ExternalModule->Value;
					}
					if (ExternalModule->Key->Contains("Type"))
					{
						ExternalModuleType = ExternalModule->Value;
					}
					if (ExternalModule->Key->Contains("Address"))
					{
						ExternalModuleAddress = ExternalModule->Value;
					}

					if (ExternalModule->Key->Contains("CH"))
					{
						if (ExternalModule->Value == "AMSRF0")
						{
							if (SiteInfo.AMSRF0_Exist == false)
							{
								ErrorMessage = " AMSRF0 is not exist for " + ExternalModule->Key + " ExternalModule= " + ExternalModuleName + ", Type = " + ExternalModuleType + ", Address = " + ExternalModuleAddress + " at " + HeadSiteInfo + ".";
								throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
							}
							else
							{
								FrequencyAmsrf0Appear++;

								if (FrequencyAmsrf0Appear > 1)
								{
									ErrorMessage = "There are two channel using AMSRF0 at " + HeadSiteInfo + ".";
									throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
								}
							}
						}
						if (ExternalModule->Value == "AMSRF1")
						{
							if (SiteInfo.AMSRF1_Exist == false)
							{
								ErrorMessage = " AMSRF1 is not exist for " + ExternalModule->Key + " ExternalModule= " + ExternalModuleName + ", Type = " + ExternalModuleType + ", Address = " + ExternalModuleAddress + " at " + HeadSiteInfo + ".";
								throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
							}
							else
							{
								FrequencyAmsrf1Appear++;

								if (FrequencyAmsrf1Appear > 1)
								{
									ErrorMessage = "There are two channel of Signal Core using AMSRF1 at " + HeadSiteInfo + ".";
									throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
								}
							}
						}
					}

				}
			}

			//Checking any duplicate address at all existing ExternalModule
			if (SiteInfo.ExternalModuleList->Count > 1)
			{
				for each (Dictionary<String^, String^>^ Index in SiteInfo.ExternalModuleList)
				{
					for each(KeyValuePair<String^, String^>^ ExternalModule in Index)
					{
						if (ExternalModule->Key->Contains("Address"))
						{
							Address[AddressCount] = ExternalModule->Value;
							AddressCount++;
						}
					}
				}

				for (int i = 0; i < Address->Length; i++)
				{
					for (int j = i + 1; j < Address->Length; j++)
					{
						if (Address[i] == Address[j])
						{
							ErrorMessage = "Same address appear at the External Module" + " at " + HeadSiteInfo + ".";
							throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
						}
					}
				}
			}
		}
	}
	bool AMB7600SRTestLibrary::SupportedExternalModule(String ^ ExternalModule, int % NoOfChannel, array<String^>^ % ExternalModuleInfo)
	{
		bool Support = false;

		if (ExternalModule == "SC5511A")
		{
			ExternalModuleInfo = gcnew array<String ^>(4);
			ExternalModuleInfo[0] = "Name";
			ExternalModuleInfo[1] = "Type";
			ExternalModuleInfo[2] = "Address";
			ExternalModuleInfo[3] = "CH1";

			NoOfChannel = 2;
			Support = true;
		}
		else if (ExternalModule == "SC5505A")
		{
			ExternalModuleInfo = gcnew array<String ^>(5);
			ExternalModuleInfo[0] = "Name";
			ExternalModuleInfo[1] = "Type";
			ExternalModuleInfo[2] = "Address";
			ExternalModuleInfo[3] = "CH1";
			ExternalModuleInfo[4] = "CH2";


			NoOfChannel = 1;
			Support = true;

		}
		else if (ExternalModule == "C2")
		{
			ExternalModuleInfo = gcnew array<String ^>(3);
			ExternalModuleInfo[0] = "Name";
			ExternalModuleInfo[1] = "Type";
			ExternalModuleInfo[2] = "Address";

			NoOfChannel = 1;
			Support = true;
		}
		else
		{
			ExternalModuleInfo = gcnew array<String ^>(0);

			NoOfChannel = 0;
			Support = false;
		}


		return Support;
	}
	//Function Helper
	void AMB7600SRTestLibrary::StringArrayToIntArray(array<String^> ^ StringInfo, array<int> ^ % IntInfo)
	{

		String ^ErrorMessage = nullptr;
		IntInfo = gcnew array<int>(StringInfo->Length);

		for (int i = 0; i < StringInfo->Length; i++)
		{
			if (StringInfo[i] == "")
			{
				ErrorMessage = "Spacing are not allowed after the last Integer at AMSRF0 or AMSRF1 at " + HeadSiteInfo + ".";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}

			IntInfo[i] = int::Parse(StringInfo[i]);
		}

	}
	//Checking between H0S0,H0S1,H1S0,H1S1
	void AMB7600SRTestLibrary::HeadSiteAmsrfChecking()
	{

		String ^ ErrorMessage = nullptr;
		int FrequencyAMSRF0Appear = 0;
		int FrequencyAMSRF1Appear = 0;

		for each(KeyValuePair<String^, String^>^ HeadSiteAmsrf in AMSRF_Head_Site)
		{
			if (HeadSiteAmsrf->Value->Contains("AMSRF0"))
			{
				FrequencyAMSRF0Appear++;
			}
			else if (HeadSiteAmsrf->Value->Contains("AMSRF1"))
			{
				FrequencyAMSRF1Appear++;
			}

			if (FrequencyAMSRF0Appear > 1)
			{
				ErrorMessage = "Multiple AMSRF0 exist is not allowed.";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
			if (FrequencyAMSRF1Appear > 1)
			{
				ErrorMessage = "Multiple AMSRF1 exist is not allowed.";
				throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
			}
		}

	}
	void AMB7600SRTestLibrary::HeadSiteExternalModuleChecking()
	{

		String ^ ErrorMessage = nullptr;
		array <String ^> ^ Address;
		int AddressCount = 0;

		//Total External Module
		for (int i = 0; i < HeadSiteXml->Length; i++)
		{
			if (HeadSiteXml[i] == "H0S0")
			{
				if (H0S0.TotalExternalModule >= 1)
				{
					AddressCount = AddressCount + H0S0.ExternalModuleList->Count;
				}
			}
			else if (HeadSiteXml[i] == "H0S1")
			{
				if (H0S1.TotalExternalModule >= 1)
				{
					AddressCount = AddressCount + H0S1.ExternalModuleList->Count;
				}
			}
			else if (HeadSiteXml[i] == "H1S0")
			{
				if (H1S0.TotalExternalModule >= 1)
				{
					AddressCount = AddressCount + H1S0.ExternalModuleList->Count;
				}
			}
			else if (HeadSiteXml[i] == "H1S1")
			{
				if (H1S1.TotalExternalModule >= 1)
				{
					AddressCount = AddressCount + H1S1.ExternalModuleList->Count;
				}
			}
		}

		Address = gcnew array <String^>(AddressCount);
		AddressCount = 0;

		if (Address->Length >= 1)
		{
			//Duplicate the Address from Dictionary to Array
			for (int i = 0; i < HeadSiteXml->Length; i++)
			{
				if (HeadSiteXml[i] == "H0S0")
				{
					for (int j = 0; j < H0S0.ExternalModuleList->Count; j++)
					{
						Address[AddressCount++] = H0S0.ExternalModuleList[j]["Address"];
					}
				}
				else if (HeadSiteXml[i] == "H0S1")
				{
					for (int j = 0; j < H0S1.ExternalModuleList->Count; j++)
					{
						Address[AddressCount++] = H0S1.ExternalModuleList[j]["Address"];
					}
				}
				else if (HeadSiteXml[i] == "H1S0")
				{
					for (int j = 0; j < H1S0.ExternalModuleList->Count; j++)
					{
						Address[AddressCount++] = H1S0.ExternalModuleList[j]["Address"];
					}
				}
				else if (HeadSiteXml[i] == "H1S1")
				{
					for (int j = 0; j < H1S1.ExternalModuleList->Count; j++)
					{
						Address[AddressCount++] = H1S1.ExternalModuleList[j]["Address"];
					}
				}
			}

			//Checking any duplicate Address among the External Module
			for (int i = 0; i < Address->Length; i++)
			{
				for (int j = i + 1; j < Address->Length; j++)
				{
					if (Address[i] == Address[j])
					{
						ErrorMessage = "ExternalModule = " + Address[i] + " appear multiple time.";
						throw gcnew Exception(ErrorMessage + "Please check the contents inside the RFSiteConfigInfo.xml.");
					}
				}
			}
		}

	}
	//Write Info to Logger & File
	void AMB7600SRTestLibrary::AmsrfInfoToLoggerFile()
	{
		String ^ InfoMessage = String::Empty;
		String^ ExternalModuleInfo = nullptr;

		if (CurrentHeadSite.AMSRFSupported->Contains("AMSRF0"))
		{
			for (int index = 0; index < tl->glob->Amsrf0Site->Length; index++)
			{
				if (CurrentHeadSite.TotalSignalCore > 0)
				{
					if (TestSiteSignalCoreType->ContainsKey(index))
					{
						ExternalModuleInfo = ExternalModuleInfo->Concat(TestSiteSignalCoreType[index]," ");
					}
				}

				InfoMessage = "RF Infomations:" + "\n\t\t\t\t\t" +
					"Site Configuration  = " + SiteConfig + "\n\t\t\t\t\t" +
					"AMSRF Type  = "         + "AMSRF0" + "\n\t\t\t\t\t" +
					"RF System Type = "      + SystemConfigurationInfoAMSRF0.SystemType + "\n\t\t\t\t\t" +
					"System EXternal RF Module = " + ExternalModuleInfo + "\n\t\t\t\t\t";

				ExternalModuleInfo = nullptr;

				tl->WriteToTcrLgr("SITE " + tl->glob->Amsrf0Site[index].ToString(), InfoMessage);
			}
		}
		if (CurrentHeadSite.AMSRFSupported->Contains("AMSRF1"))
		{
			for (int index = 0; index < tl->glob->Amsrf1Site->Length; index++)
			{
				if (CurrentHeadSite.TotalSignalCore > 0)
				{
					if (TestSiteSignalCoreType->ContainsKey(index))
					{
						ExternalModuleInfo = ExternalModuleInfo->Concat(TestSiteSignalCoreType[index], " ");
					}
				}

				InfoMessage = "RF Infomations:" + "\n\t\t\t\t\t" +
					"Site COnfiguration  = " + SiteConfig + "\n\t\t\t\t\t" +
					"AMSRF Type  = " + "AMSRF1" + "\n\t\t\t\t\t" +
					"RF System Type = " + SystemConfigurationInfoAMSRF1.SystemType + "\n\t\t\t\t\t" +
					"System EXternal RF Module = " + ExternalModuleInfo + "\n\t\t\t\t\t";

				ExternalModuleInfo = nullptr;

				tl->WriteToTcrLgr("SITE " + tl->glob->Amsrf1Site[index].ToString(), "Initialized Aemulus Tester");
			}
		}
		
	}

}