#include "AMB7600SR.h"

namespace Functions
{
	// CM400e Load Phase Initialization
	array<String^>^ AMB7600SRTestLibrary::GetCMModuleAlias(Site ^ site, int siteIndex)
	{
		/*****************************************************************************************************
		** GetDIOModuleAlias
		******************************************************************************************************
		** Descriptions:
		**		Usage: Get module alias for specified DIO resource
		**
		** Parameters:
		**		cm		- CM resource
		**
		** Return value:
		**		Module alias
		******************************************************************************************************/


		int moduleCount = 0;

		for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
		{
			ResourceManagerSett[siteIndex].HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];

			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("CM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "CM400e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "CM401e")
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
			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("CM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "CM400e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "CM401e")
				{
					moduleAlias[count] = Rsrc->ToString();
					count++;
				}
			}
		}

		return moduleAlias;
	}
	int AMB7600SRTestLibrary::InitializeCM400eResource(Site ^ site)
	{
		int ret = 0;
		int initOption = tl->glob->AWV.CMInitOption;

		array<array<String^>^>^ moduleAlias = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);

		int count = 0;
		bool IsModuleAlias = false;

		moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetCMModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			if (moduleCount[siteIndex] > 0)
			{
				ResourceManagerSett[siteIndex].CM_HardwareStatus = true;
				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing CM400e System Resources...");
			}
		}

		cm = gcnew array<CM ^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].CM_HardwareStatus)
			{
				cm[siteIndex] = gcnew CM(tl->glob->HardwareProfile, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
			}
		}

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			if (ResourceManagerSett[siteIndex].CM_HardwareStatus)
			{
				for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
				{
					Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
					IsModuleAlias = false;

					if ((HardwareRsrc->Hierarchy[0]->StartsWith("CM400") == true || HardwareRsrc->Hierarchy[0]->StartsWith("CM401") == true) &&
						(ResourceManagerSett[siteIndex].ResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) &&
						(ResourceManagerSett[siteIndex].CMResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false))
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
							ResourceManagerSett[siteIndex].CMResourceAlias->Add(Rsrc, 1);
						}

						ResourceManagerSett[siteIndex].ResourceAlias->Add(HardwareRsrc->Alias->ToString(), 1);
					}
				}

				//Configure module alias only 
				for (int count = 0; count < moduleCount[siteIndex]; count++)
				{
					/* 1. In multi site mode, DLL do lock down resource to prevent other thread from accessing it thus allowing every thread to function properly but it incurs more test time.
					* 2. In single site mode, DLL do not lock down resource so it incurs lesser test time..
					*
					*	0 : DM_CONST_SINGLE_SITE
					*	1 : DM_CONST_MULTI_SITE*/

					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing cm[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", 1)");
					tl->CheckError(siteIndex, cm[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], CM_CONST_MULTI_SITE));
				}

				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "CM[site " + siteIndex + "] initialized");
			}

		}

		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeCM400eResource(Site ^ site)
	{
		int ret = 0;
		array<array<String^>^>^ moduleAlias = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);
		moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetCMModuleAlias(site, siteIndex);

			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			try
			{
				if (ResourceManagerSett[siteIndex].CM_HardwareStatus == true)
				{
					for (int count = 0; count < moduleCount[siteIndex]; count++)
					{
						tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing cm[" + siteIndex + "]->Close(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, cm[siteIndex]->Close(moduleAlias[siteIndex][count]));
					}
				}
			}
			catch (Exception ^ ex)
			{
				tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
				String^ ErrorMessage = "AMB7600SRTestLibrary:: UninitializeCM400eResource " + "encountered error when performing.";
				tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
			}
		}


		return ret;
	}

	//CM400e Helper Function
	int AMB7600SRTestLibrary::CM_ConfigurePXES2780_TriggerBusAB(int testSite, String^ moduleAlias, int Enable_AB, int AB_Direction)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->ConfigurePXES2780_TriggerBusAB(moduleAlias, Enable_AB, AB_Direction));

		return ret;
	}
	int AMB7600SRTestLibrary::CM_ConfigurePXES2780_TriggerBusBC(int testSite, String^ moduleAlias, int Enable_BC, int BC_Direction)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->ConfigurePXES2780_TriggerBusBC(moduleAlias, Enable_BC, BC_Direction));

		return ret;
	}
	int AMB7600SRTestLibrary::CM_DrivePort(int testSite, String^ moduleAlias, int portVal)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->DrivePort(moduleAlias, portVal));

		return ret;
	}
	int AMB7600SRTestLibrary::CM_DrivePin(int testSite, String^ moduleAlias, int pin, int pinVal)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->DrivePin(moduleAlias, pin, pinVal));

		return ret;
	}
	int AMB7600SRTestLibrary::CM_SetPortDirection(int testSite, String^ moduleAlias, int portDir)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->SetPortDirection(moduleAlias, portDir));

		return ret;
	}
	int AMB7600SRTestLibrary::CM_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->MapTriggerInToTriggerOut(moduleAlias, inputTerminal, outputTerminal));

		return ret;
	}
	int AMB7600SRTestLibrary::CM_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth)
	{
		int ret = 0;

		CheckError(testSite, cm[testSite]->DriveSoftwareTrigger(moduleAlias, select, pulseWidth));

		return ret;
	}
}