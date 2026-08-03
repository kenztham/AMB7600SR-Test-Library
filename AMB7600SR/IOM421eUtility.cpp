#include "AMB7600SR.h"

namespace Functions
{
	// IOM421e Load Phase Initialization
	array<String^>^ AMB7600SRTestLibrary::GetDIOModuleAlias(Site ^ site, int siteIndex)
	{
		/*****************************************************************************************************
		** GetDIOModuleAlias
		******************************************************************************************************
		** Descriptions:
		**		Usage: Get module alias for specified DIO resource
		**
		** Parameters:
		**		dio		- DIO resource
		**
		** Return value:
		**		Module alias
		******************************************************************************************************/


		int moduleCount = 0;

		for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
		{
			ResourceManagerSett[siteIndex].HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];

			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("IOM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "IOM421")
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
			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("IOM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "IOM421")
				{
					moduleAlias[count] = Rsrc->ToString();
					count++;
				}
			}
		}

		return moduleAlias;
	}
	int AMB7600SRTestLibrary::InitIOMModuleAliasPreviousState(Site ^ site, int siteIndex, array<String^> ^ ModuleAlias)
	{
		int ret = 0;

		for (int i = 0; i < ModuleAlias->Length; i++)
		{
			tl->glob->IOMModuleVIOStateSettingsManager[siteIndex]->Add(ModuleAlias[i], 999);
		}

		return ret;
	}
	int AMB7600SRTestLibrary::InitIOMPortAliasPreviousState(Site ^ site, int siteIndex)
	{
		int ret = 0;

		for each (KeyValuePair<String^, int>^ portAlias in ResourceManagerSett[siteIndex].DIOResourcePortAlias)
		{
			tl->glob->IOMPortStateSettingsManager[siteIndex].PortDirection->Add(portAlias->Key, 999);
			tl->glob->IOMPortStateSettingsManager[siteIndex].PortValue->Add(portAlias->Key, 999);

		}

		return ret;
	}
	int AMB7600SRTestLibrary::InitIOMPinAliasPreviousState(Site ^ site, int siteIndex)
	{
		int ret = 0;

		for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].DIOResourceAlias)
		{
			tl->glob->IOMPinValStateSettingsManager[siteIndex]->Add(pinAlias->Key, 999);
		}

		return ret;
	}

	int AMB7600SRTestLibrary::InitializeIOM421eResource(Site ^ site)
	{
		int ret = 0;
		int initOption = tl->glob->AWV.IOMInitOption;

		array<array<String^>^>^ moduleAlias = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);

		int count = 0;
		bool IsModuleAlias = false;

		moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetDIOModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;
			InitIOMModuleAliasPreviousState(site, siteIndex, moduleAlias[siteIndex]);
			if (moduleCount[siteIndex] > 0)
			{
				ResourceManagerSett[siteIndex].DIO_HardwareStatus = true;
				tl->WriteToLogger(siteIndex, "Initializing IOM421e System Resources...");
			}
		}

		dio = gcnew array<DIO ^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DIO_HardwareStatus)
			{
				dio[siteIndex] = gcnew DIO(tl->glob->HardwareProfile, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
			}
		}

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].DIO_HardwareStatus)
			{
				for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
				{
					Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
					IsModuleAlias = false;

					if ((HardwareRsrc->Hierarchy[0]->StartsWith("IOM421") == true) &&
						(ResourceManagerSett[siteIndex].ResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) &&
						(ResourceManagerSett[siteIndex].DIOResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false))
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
							if (HardwareRsrc->Type=="Port")
							{
								ResourceManagerSett[siteIndex].DIOResourcePortAlias->Add(Rsrc, 1);
							}
							else if (HardwareRsrc->Type == "Pin")
							{
								ResourceManagerSett[siteIndex].DIOResourceAlias->Add(Rsrc, 1);
							}
						}

						ResourceManagerSett[siteIndex].ResourceAlias->Add(HardwareRsrc->Alias->ToString(), 1);
					}
				}

				//Configure module alias only 
				for (int count = 0; count < moduleCount[siteIndex]; count++)
				{
					//tl->WriteToLogger(siteIndex, "Executing dio[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
					//tl->CheckError(siteIndex, dio[siteIndex]->Reset(moduleAlias[siteIndex][count]));

					/* 1. In multi site mode, DLL do lock down resource to prevent other thread from accessing it thus allowing every thread to function properly but it incurs more test time.
					* 2. In single site mode, DLL do not lock down resource so it incurs lesser test time..
					*
					*	0 : DM_CONST_SINGLE_SITE
					*	1 : DM_CONST_MULTI_SITE*/

					tl->WriteToLogger(siteIndex, "Executing dio[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", 1)");
					tl->CheckError(siteIndex, dio[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], IOM_CONST_MULTI_SITE));
				}

				InitIOMPortAliasPreviousState(site, siteIndex);
				InitIOMPinAliasPreviousState(site, siteIndex);

				tl->WriteToLogger(siteIndex, "DIO[site " + siteIndex + "] initialized");
			}

		}

		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeIOM421eResource(Site ^ site)
	{
		int ret = 0;
		array<array<String^>^>^ moduleAlias = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);
		moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetDIOModuleAlias(site, siteIndex);

			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			try
			{
				if (ResourceManagerSett[siteIndex].DIO_HardwareStatus== true)
				{
					for (int count = 0; count < moduleCount[siteIndex]; count++)
					{
						tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, dio[siteIndex]->Reset(moduleAlias[siteIndex][count]));

						tl->WriteToLogger(siteIndex, "Executing dm[" + siteIndex + "]->Close(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, dio[siteIndex]->Close(moduleAlias[siteIndex][count]));

					}
				}
			}
			catch (Exception ^ ex)
			{
				tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
				String^ ErrorMessage = "AMB7600SRTestLibrary:: UninitializeIOM421eResource " + "encountered error when performing.";
				tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
				tl->WriteToLogger(siteIndex, ErrorMessage);
			}
		}


		return ret;
	}

	//IOM421e Helper Function
	int AMB7600SRTestLibrary::DIO_SetVIO(int testSite, String ^ ModuleAlias, int setting)
	{
		int ret = 0;

		if (setting != tl->glob->IOMModuleVIOStateSettingsManager[testSite][ModuleAlias])
		{
			if (setting == 0)
			{
				CheckError(testSite, dio[testSite]->SetVIO(ModuleAlias, IOM_CONST_OUTPUT_VIO_3_3V));
			}
			else if (setting == 1)
			{
				CheckError(testSite, dio[testSite]->SetVIO(ModuleAlias, IOM_CONST_OUTPUT_VIO_5_0V));
			}
			tl->glob->IOMModuleVIOStateSettingsManager[testSite][ModuleAlias] = setting;

			Resource ^ moduleRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(ModuleAlias)[0];
			String ^ moduleAddress = moduleRsrc->Hierarchy[0];

			//Reset Port Alias
			for each (KeyValuePair<String^, int>^ portAlias in ResourceManagerSett[testSite].DIOResourcePortAlias)
			{
				Resource ^ portRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(portAlias->Key)[0];

				if (moduleAddress == portRsrc->Hierarchy[0])
				{
					tl->glob->IOMPortStateSettingsManager[testSite].PortValue[portAlias->Key] = 999;
				}

			}
			//Reset Pin Alias
			for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[testSite].DIOResourceAlias)
			{
				Resource ^ pinRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinAlias->Key)[0];

				if (moduleAddress == pinRsrc->Hierarchy[0])
				{
					tl->glob->IOMPinValStateSettingsManager[testSite][pinAlias->Key] = 999;
				}
			}
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DIO_SetPortDirection(int testSite, String ^ portAlias, int dirval)
	{
		int ret = 0;

		if (dirval!=tl->glob->IOMPortStateSettingsManager[testSite].PortDirection[portAlias])
		{
			if (dirval == 0)
			{
				CheckError(testSite, dio[testSite]->SetPortDirection(portAlias, IOM_CONST_PORT_DIRECTION_INPUT));
			}
			else if (dirval == 1)
			{
				CheckError(testSite, dio[testSite]->SetPortDirection(portAlias, IOM_CONST_PORT_DIRECTION_OUTPUT));
			}

			tl->glob->IOMPortStateSettingsManager[testSite].PortDirection[portAlias] = dirval;

		}
		return ret;
	}
	int AMB7600SRTestLibrary::DIO_DrivePort(int testSite, String ^ portAlias, int portval)
	{
		int ret = 0;

		if (portval != tl->glob->IOMPortStateSettingsManager[testSite].PortValue[portAlias])
		{
			CheckError(testSite, dio[testSite]->DrivePort(portAlias, portval));
			tl->glob->IOMPortStateSettingsManager[testSite].PortValue[portAlias] = portval;


			Resource ^ portRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(portAlias)[0];
			String ^ portAddress = portRsrc->Hierarchy[0];

			//Reset Pin Alias
			for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[testSite].DIOResourceAlias)
			{
				Resource ^ pinRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinAlias->Key)[0];

				if (portAddress == pinRsrc->Hierarchy[0])
				{
					tl->glob->IOMPinValStateSettingsManager[testSite][pinAlias->Key] = 999;
				}
			}
		}

		return ret;
	}
	int AMB7600SRTestLibrary::DIO_DrivePin(int testSite, String ^ pinAlias, int pinval)
	{
		int ret = 0;

		if (pinval != tl->glob->IOMPinValStateSettingsManager[testSite][pinAlias])
		{
			if (pinval == 0)
			{
				CheckError(testSite, dio[testSite]->DrivePin(pinAlias, IOM_CONST_PIN_DRIVE_LOW));
			}
			else if (pinval == 1)
			{
				CheckError(testSite, dio[testSite]->DrivePin(pinAlias, IOM_CONST_PIN_DRIVE_HIGH));
			}

			tl->glob->IOMPinValStateSettingsManager[testSite][pinAlias] = pinval;


			Resource ^ pinRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(pinAlias)[0];
			String ^ pinAddress = pinRsrc->Hierarchy[0];

			//Reset Port Alias
			for each (KeyValuePair<String^, int>^ portAlias in ResourceManagerSett[testSite].DIOResourcePortAlias)
			{
				Resource ^ portRsrc = ResourceManagerSett[testSite].RsrcManager[testSite]->ResolveResource(portAlias->Key)[0];

				if (pinAddress == portRsrc->Hierarchy[0])
				{
					tl->glob->IOMPortStateSettingsManager[testSite].PortValue[portAlias->Key] = 999;
				}

			}

		}

		return ret;
	}

}	