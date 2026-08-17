#include "Module400Series.h"
#include "../Test Method/Methods.h"

namespace Functions
{
	// AMB5600TestLibrary Contsructor and Destructor 
	Module400Series::Module400Series(TestFunction ^ TestFunc)
	{
		tl = TestFunc;
		ResourceManagerSett = gcnew array<ResourceManagerSetting>(tl->glob->tf.NumberOfSites);
	}
	Module400Series::~Module400Series(void)
	{

	}


	//Helper Functions
	int Module400Series::InitializeTester(Site^ site, int TotalSite, String^ HardwareProfile, int TestHead)
	{
		int ret = 0;
		int siteIndex = 0;
		int testSite = site->Index;

		for (siteIndex = 0; siteIndex < TotalSite; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing 400series Modules...");
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

#pragma region "Hardware Initialization"

			//DC Resource
			InitializeDM400eResource(site);
			InitializeAM400eResource(site);
			InitializeIOM421eResource(site);
			InitializeCM400eResource(site);

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
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initialized 400series Modules");
		}

		return ret;
	}
	int Module400Series::UninitializeTester(Site ^ site)
	{
		int ret = 0;
		int siteIndex = 0;

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Uninitializing 400series Modules...");
		}

		UninitializeDM400eResource(site);
		UninitializeAM400eResource(site);
		UninitializeIOM421eResource(site);
		UninitializeCM400eResource(site);


		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Uninitialized 400series Modules");
		}

		return ret;
	}
}