#include "Module400Series.h"

namespace Functions
{
	// AM400e Load Phase Initialization 
	array<String^>^ Module400Series::GetAMModuleAlias(Site ^ site, int siteIndex)
{
	/*****************************************************************************************************
	** GetAmModuleAlias
	******************************************************************************************************
	** Descriptions:
	**		Usage: Get module alias for specified AM resource
	**
	** Parameters:
	**		am		- AM resource
	**
	** Return value:
	**		Module alias
	******************************************************************************************************/

	// 1. Declare variable OUTSIDE the try block so it stays in scope for the return statement
	array<String^>^ moduleAlias = nullptr;

	try
	{
		int moduleCount = 0;

		for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
		{
			ResourceManagerSett[siteIndex].HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];

			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM430e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM471e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM451e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM450e")
				{
					moduleCount++;
				}
			}
		}

		// 2. Instantiate array inside the try block
		moduleAlias = gcnew array<String^>(moduleCount);
		int count = 0;

		for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
		{
			ResourceManagerSett[siteIndex].HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
			if ((ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy[0]->StartsWith("AM") == true) &&
				ResourceManagerSett[siteIndex].HardwareRsrc->Hierarchy->Length == 1)
			{
				if (ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM430e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM471e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM451e" || ResourceManagerSett[siteIndex].HardwareRsrc->Type == "AM450e")
				{
					moduleAlias[count] = Rsrc->ToString();
					count++;
				}
			}
		}
	}
	catch (Exception ^ ex)
	{
		tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
		tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
		String^ ErrorMessage = "Module400Series::GetAMModuleAlias encountered an error: " + ex->Message;
		tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
		tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
	}

	return moduleAlias;
}
	int Module400Series::InitAmPinAliasPreviousState(Site ^ site, int siteIndex) 
		//
	{
		int ret = 0;
		try
		{
			// Only hardware resources that have string values begin with "AM" will be added into global variables initialization

			for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].AMResourceAlias)
			{
				tl->glob->SMUStateSettingsManager[siteIndex].SMUStateDriveVoltage->Add(pinAlias->Key, 0.0);
				tl->glob->SMUStateSettingsManager[siteIndex].SMUStateDriveCurrent->Add(pinAlias->Key, 0.0);
				tl->glob->SMUStateSettingsManager[siteIndex].SMUStateClampVoltage->Add(pinAlias->Key, 0.0);
				tl->glob->SMUStateSettingsManager[siteIndex].SMUStateClampCurrent->Add(pinAlias->Key, 0.0);
				tl->glob->SMUStateSettingsManager[siteIndex].SMUStateOutputFunction->Add(pinAlias->Key, 0.0);
				tl->glob->SMUStateSettingsManager[siteIndex].SMUStateNPLC->Add(pinAlias->Key, 0.0);

			}
		}
		catch (Exception ^ ex)
		{
			ret = ER_CONST_ERRROR_CATCH;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::InitAmPinAliasPreviousState encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
		}

		return ret;
	}
	int Module400Series::InitializeAM400eResource(Site ^site) 
		//Automatically checks resource planner status, handles multi-site modes, and initializes state tracking variables.
	{
		int ret = 0;

		try
		{
			int initOption = tl->glob->AWV.AMInitOption;

			array<array<String^>^>^ moduleAlias = nullptr;
			array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);

			int count = 0;
			bool IsModuleAlias = false;

			moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);
			smu = gcnew array<SMU ^>(tl->glob->tf.NumberOfSites);

			//Checking any AM Module used at Resource Plannar
			for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
			{
				moduleAlias[siteIndex] = GetAMModuleAlias(site, siteIndex);
				moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

				if (moduleCount[siteIndex] > 0)
				{
					ResourceManagerSett[siteIndex].AM_HardwareStatus = true;
					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing SMU[site " + siteIndex + "]...");
				}
			}

			//Iniatialization of the AM Module
			for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
			{
				if (ResourceManagerSett[siteIndex].AM_HardwareStatus)
				{
					smu[siteIndex] = gcnew SMU(tl->glob->HardwareProfile, tl->glob->tf.TestHead, siteIndex, tl->glob->AWV.Offline, initOption); //Initialize/reset all HW
				}
			}

			for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
			{
				if (ResourceManagerSett[siteIndex].AM_HardwareStatus)
				{
					for each (String ^ Rsrc in ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->MapNames)
					{
						Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(Rsrc)[0];
						IsModuleAlias = false;

						if ((HardwareRsrc->Hierarchy[0]->StartsWith("AM430e") == true || HardwareRsrc->Hierarchy[0]->StartsWith("AM471e") == true || HardwareRsrc->Hierarchy[0]->StartsWith("AM450e") == true || HardwareRsrc->Hierarchy[0]->StartsWith("AM451e") == true) &&
							(ResourceManagerSett[siteIndex].ResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false) &&
							(ResourceManagerSett[siteIndex].AMResourceAlias->ContainsKey(HardwareRsrc->Alias->ToString()) == false))
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
								ResourceManagerSett[siteIndex].AMResourceAlias->Add(Rsrc, 1);
							}

							ResourceManagerSett[siteIndex].ResourceAlias->Add(HardwareRsrc->Alias->ToString(), 1);
						}
					}

					for (count = 0; count < moduleCount[siteIndex]; count++)
					{
						Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(moduleAlias[siteIndex][count])[0];

						if (HardwareRsrc->Type == "AM430e" || HardwareRsrc->Type == "AM471e" || HardwareRsrc->Type == "AM451e")
						{
							tl->CheckError(siteIndex, smu[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], AM_CONST_SINGLE_SITE));
							tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing smu[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", 0)");
						}
						else
						{
							tl->CheckError(siteIndex, smu[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], AM_CONST_MULTI_SITE));
							tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing smu[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", 1)");
						}
					}

					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Initializing AM400e Related Global Variables for Previous States...");
					InitAmPinAliasPreviousState(site, siteIndex); //initialize AM modules related global variables to store previous states

					for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].AMResourceAlias)
					{
						ConfigureSMU(siteIndex, pinAlias->Key, AM_CONST_DVCI, AM_CONST_TRANSIENT_NORMAL, AM_CONST_100UA_RANGE, AM_CONST_PLC, tl->glob->AWV.PowerLineFreq);
					}

					tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "SMU[site " + siteIndex + "] initialized");

				}
				else if (moduleCount[siteIndex] == 0)
				{
					ResourceManagerSett[siteIndex].AM_HardwareStatus = false;
				}
			}
		}
		catch (Exception ^ ex)
		{
			ret = ER_CONST_INIT_AM_HARDWARE_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(0, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::InitializeAM400eResource encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE 0", ErrorMessage);
		
		}

		return ret;
	}
	int Module400Series::UninitializeAM400eResource(Site ^site) 
	//maintain from (7600) hardware resets alongside module closures, paired with structured try-catch error logging.
	{
		int ret = 0;
		array<array<String^>^>^ moduleAlias = nullptr;
		array<int>^ moduleCount = gcnew array<int>(tl->glob->tf.NumberOfSites);
		moduleAlias = gcnew array<array<String^>^>(tl->glob->tf.NumberOfSites);

		for (int siteIndex = 0; siteIndex < tl->glob->tf.NumberOfSites; siteIndex++)
		{
			moduleAlias[siteIndex] = GetAMModuleAlias(site, siteIndex);
			moduleCount[siteIndex] = moduleAlias[siteIndex]->Length;

			try
			{
				if (ResourceManagerSett[siteIndex].AM_HardwareStatus == true)
				{
					for (int count = 0; count < moduleCount[siteIndex]; count++)
					{
						tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing smu[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, smu[siteIndex]->Reset(moduleAlias[siteIndex][count]));
						tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), "Executing smu[" + siteIndex + "]->Close(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, smu[siteIndex]->Close(moduleAlias[siteIndex][count]));
					}
				}
			}
			catch (Exception ^ ex)
			{
				tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
				String^ ErrorMessage = "Module400Series:: UninitializeAM400eResource " + "encountered error when performing.";
				tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
				tl->WriteToTcrLgr("SITE " + siteIndex.ToString(), ErrorMessage);
			}
		}

		return ret;
	}

	int Module400Series::ConfigureSMU(int testSite, String^ PIN, int Mode, int bandwidth, double compliance, double nplc, double powerLineFreq)
	{
		
		int ret = 0;
		try
		{
			SMU_NplcSetting(testSite, PIN, nplc);
			SMU_SetBandwidth(testSite, PIN, bandwidth);
			SMU_ConfigureSense(testSite, PIN, AM_CONST_REMOTE);
			SMU_ConfigurePowerLineFreq(testSite, PIN, powerLineFreq);

			if (Mode == AM_CONST_DICV)
			{
				SMU_ConfigureOutputFunction(testSite, PIN, AM_CONST_DICV);
				SMU_ClampVoltage(testSite, PIN, compliance);
				SMU_DriveCurrent(testSite, PIN, 0.0 A);
			}
			else if (Mode == AM_CONST_DVCI)
			{
				SMU_ConfigureOutputFunction(testSite, PIN, AM_CONST_DVCI);
				SMU_ClampCurrent(testSite, PIN, compliance);
				SMU_DriveVoltage(testSite, PIN, 0.0 V);
			}

			SMU_OnSMU(testSite, PIN);
		}
		catch (Exception ^ ex)
		{
			ret = ER_CONST_CONFIGURE_AM_PIN_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::ConfigureSMU encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}
		return ret;
	}

	
	int Module400Series::SmuTestFunction_OS(int testSite, String ^ pinAlias, double nplc, double measureDelay, double % result) 
		//SmuTestFunction_OS (From 7300) Directly accepts nplc and measureDelay parameters, reading voltage and forcing a 100mA clamp low-voltage safety reset for short testing.
	{
		
		int ret = 0;

		try
		{
			// Set NPLC and wait for measure delay
			tl->CheckError(testSite, smu[testSite]->SetNPLC(pinAlias, nplc));
			util->WaitSecond(measureDelay);

			// Measure Voltage
			tl->CheckError(testSite, smu[testSite]->ReadVoltage(pinAlias, result));

			// Reconfigure to DVCI and drive low to cater for pin-to-pin short testing (7300 core logic)
			tl->CheckError(testSite, smu[testSite]->ConfigureOutputFunction(pinAlias, AM_CONST_DVCI));
			tl->CheckError(testSite, smu[testSite]->ClampCurrent(pinAlias, 100.0 mA));
			tl->CheckError(testSite, smu[testSite]->DriveVoltage(pinAlias, 0.0 V));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_AM_TEST_FUNCTION_OS_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "[Module400Series -> SmuTestFunction_OS] Fail at OS test. Error Code: " + ret.ToString() + " | Detail: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}
	int Module400Series::SMU_MeasureCurrent(int testSite, String ^ PIN,double % result)
	{
		int ret = 0;
		try
		{

			tl->CheckError(testSite, smu[testSite]->ReadCurrent(PIN, result));

		}
		catch (Exception ^ ex)
		{
			ret = ER_CONST_AM_TEST_FUNCTION_MEASURE_CURRENT_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MeasureCurrent encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}
			return ret;
	}
	int Module400Series::SMU_MeasureVoltage(int testSite, String ^ PIN, double % result)
	{
		int ret = 0;
		try
		{
        	tl->CheckError(testSite, smu[testSite]->ReadVoltage(PIN, result));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_AM_TEST_FUNCTION_MEASURE_VOLTAGE_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MeasureVoltage encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}
		return ret;
	}
	int Module400Series::SMU_MeasureCurrent(int testSite, String ^ PIN, double delay, double % result)
	{
		int ret = 0;

		try
		{
			util->WaitSecond(delay);
			ret = tl->CheckError(testSite, smu[testSite]->ReadCurrent(PIN, result));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_AM_TEST_FUNCTION_MEASURE_CURRENT_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MeasureCurrent with delay encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_MeasureVoltage(int testSite, String ^ PIN, double delay, double % result)
	{
		int ret = 0;

		try
		{
			util->WaitSecond(delay);
			tl->CheckError(testSite, smu[testSite]->ReadVoltage(PIN, result));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_AM_TEST_FUNCTION_MEASURE_VOLTAGE_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MeasureVoltage with delay encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_MeasureBurstCurrent(int testSite, String ^ PIN, double duration, double peakPercentage, double % result)
	{
		int ret = 0;

		try
		{
			int samplesCount = duration * 1e6; // hard code 1M sampling rate for AM430 

			int iHighCount = 0;
			double iHighSum = 0.0;

			array<double> ^ samples = gcnew array<double>(samplesCount);
			double average = 0.0;
			double max = 0.0;

			tl->CheckError(testSite, smu[testSite]->ReadCurrentWithAverage(PIN, samplesCount, average, samples));

			if (!ret)
			{
				for (int i = 0; i < samplesCount; i++)
				{
					if (samples[i] > average)
					{
						if (i == 0)
						{
							max = samples[i];
						}

						if (i > 0)
						{
							if (samples[i] > max)
								max = samples[i];
						}
					}
				}

				for (int i = 0; i < samplesCount; i++)
				{
					if (samples[i] >(((100 - peakPercentage) / 100) * max))
					{
						iHighSum += samples[i];
						iHighCount++;
					}
				}

				if (iHighCount < 5)
				{
					iHighSum = 0;
					iHighCount = 0;

					for (int i = 0; i < samplesCount; i++)
					{
						if (samples[i] >(0.70 * max))
						{
							iHighSum += samples[i];
							iHighCount++;
						}
					}
				}

				result = iHighSum / static_cast<double>(iHighCount);
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_MeasureBurstCurrent;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MeasureBurstCurrent encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_MeasureBurstVoltage(int testSite, String ^ PIN, double duration, double peakPercentage, double % result)
	{
		int ret = 0;

		try
		{
			int samplesCount = duration * 1e6; // hard code 1M sampling rate for AM430 

			int iHighCount = 0;
			double iHighSum = 0.0;

			array<double> ^ samples = gcnew array<double>(samplesCount);
			double average = 0.0;
			double max = 0.0;

			tl->CheckError(testSite, smu[testSite]->ReadVoltageWithAverage(PIN, samplesCount, average, samples));

			if (!ret)
			{
				for (int i = 0; i < samplesCount; i++)
				{
					if (samples[i] > average)
					{
						if (i == 0)
						{
							max = samples[i];
						}

						if (i > 0)
						{
							if (samples[i] > max)
								max = samples[i];
						}
					}
				}

				for (int i = 0; i < samplesCount; i++)
				{
					if (samples[i] >(((100 - peakPercentage) / 100) * max))
					{
						iHighSum += samples[i];
						iHighCount++;
					}
				}

				if (iHighCount < 5)
				{
					iHighSum = 0;
					iHighCount = 0;

					for (int i = 0; i < samplesCount; i++)
					{
						if (samples[i] >(0.70 * max))
						{
							iHighSum += samples[i];
							iHighCount++;
						}
					}
				}

				result = iHighSum / static_cast<double>(iHighCount);
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_MeasureBurstVoltage;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MeasureBurstVoltage encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_NplcSetting(int testSite, String ^ PIN, double nplc)
	{
		int ret = 0;

		try
		{
			if (nplc != tl->glob->SMUStateSettingsManager[testSite].SMUStateNPLC[PIN])
			{
				tl->CheckError(testSite, smu[testSite]->SetNPLC(PIN, nplc));
				tl->glob->SMUStateSettingsManager[testSite].SMUStateNPLC[PIN] = nplc;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_SetNPLC;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_NplcSetting encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureOutputFunction(int testSite, String ^ PIN, int function)	{
		int ret = 0;

		try
		{
			if (function != tl->glob->SMUStateSettingsManager[testSite].SMUStateOutputFunction[PIN])
			{
				if (function == AM_CONST_DICV)
				{
					try
					{
						tl->CheckError(testSite, smu[testSite]->ConfigureOutputFunction(PIN, AM_CONST_DICV));
					}
					catch (Exception ^ ex)
					{
						util->WaitSecond(1);
					}
				}
				else if (function == AM_CONST_DVCI)
				{
					tl->CheckError(testSite, smu[testSite]->ConfigureOutputFunction(PIN, AM_CONST_DVCI));
				}

				tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN] = 999.99;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN] = 999.99;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN] = 999.99;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN] = 999.99;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateOutputFunction[PIN] = function;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_CONFIGURE_AM_PIN_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureOutputFunction encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ClampCurrent(int testSite, String ^ PIN, double clampValue)
	{
		int ret = 0;

		try
		{
			if (clampValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN])
			{
				tl->CheckError(testSite, smu[testSite]->ClampCurrent(PIN, clampValue));

				tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN] = clampValue;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN] = 999.99;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_ClampCurrent;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ClampCurrent encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ClampVoltage(int testSite, String ^ PIN, double clampValue)
	{
		int ret = 0;

		try
		{
			if (clampValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN])
			{
				tl->CheckError(testSite, smu[testSite]->ClampVoltage(PIN, clampValue));
				tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN] = clampValue;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN] = 999.99;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_ClampVoltage;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ClampVoltage encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_DriveCurrent(int testSite, String ^ PIN, double driveValue)
	{
		int ret = 0;

		try
		{
			if (driveValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN])
			{
				tl->CheckError(testSite, smu[testSite]->DriveCurrent(PIN, driveValue));

				tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN] = driveValue;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN] = 999.99;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_DriveCurrent;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_DriveCurrent encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_DriveVoltage(int testSite, String ^ PIN, double driveValue)
	{
		int ret = 0;

		try
		{
			if (driveValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN])
			{
				tl->CheckError(testSite, smu[testSite]->DriveVoltage(PIN, driveValue));

				tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN] = driveValue;
				tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN] = 999.99;
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_DriveVoltage;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_DriveVoltage encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_OnSMU(int testSite, String ^ PIN)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->OnSmuPin(PIN, true, false));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_SetPinOnOff;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_OnSMU encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_OffSMU(int testSite, String ^ PIN)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->OffSmuPin(PIN));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_SetPinOnOff;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_OffSMU encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_SetBandwidth(int testSite, String ^ PIN, int bandwidth)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->SetBandwidth(PIN, bandwidth));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_CONFIGURE_AM_PIN_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_SetBandwidth encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureSense(int testSite, String ^ PIN, int sense)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureSense(PIN, sense));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_CONFIGURE_AM_PIN_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureSense encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigurePowerLineFreq(int testSite, String ^ PIN, double plf)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigurePLF(PIN, plf));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_CONFIGURE_AM_PIN_FAIL;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigurePowerLineFreq encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->MapTriggerInToTriggerOut(moduleAlias, inputTerminal, outputTerminal));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMMapTriggerIntToTriggerOut;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_MapTriggerInToTriggerOut encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->DriveSoftwareTrigger(moduleAlias, select, pulseWidth));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMDriveSoftwareTrigger;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_DriveSoftwareTrigger encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureTriggerEdgeLevel(int testSite, String ^ moduleAlias, int trigSource, int trigMode)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureTriggerEdgeLevel(moduleAlias, trigSource, trigMode));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureTriggerEdgeLevel;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureTriggerEdgeLevel encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureTriggerEdgeLevelExtra(int testSite, String ^ moduleAlias, int trigSource, int trigMode, int ignoreTrigCount)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureTriggerEdgeLevelExtra(moduleAlias, trigSource, trigMode, ignoreTrigCount));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureTriggerEdgeLevelExtra;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureTriggerEdgeLevelExtra encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureInputTriggerSelect(int testSite, String ^ pinAlias, int trigSource, double delayAfterTrig)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureInputTriggerSelect(pinAlias, trigSource, delayAfterTrig));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureInputTriggerSelect;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureInputTriggerSelect encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureSMUOutputTriggerMode(int testSite, String ^ pinAlias, int mode)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureSMUOutputTriggerMode(pinAlias, mode));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureSMUOutputTriggerMode;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureSMUOutputTriggerMode encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureSMUOutputTriggerPulseWidth(int testSite, String ^ pinAlias, double pulseWidth)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureSMUOutputTriggerPulseWidth(pinAlias, pulseWidth));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureSMUOutputTriggerPulseWidth;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureSMUOutputTriggerPulseWidth encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureSMUOutputTriggerDuringSource(int testSite, String ^ pinAlias, double level, double range, int mode, int edgeSetting)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureSMUOutputTriggerDuringSource(pinAlias, level, range, mode, edgeSetting));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureSMUOutputTriggerDuringSource;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureSMUOutputTriggerDuringSource encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}

	int Module400Series::SMU_ConfigureOutputTriggerSelect(int testSite, String ^ pinAlias, int triggerOutput, double triggerDelay)
	{
		int ret = 0;

		try
		{
			tl->CheckError(testSite, smu[testSite]->ConfigureOutputTriggerSelect(pinAlias, triggerOutput, triggerDelay));
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_DCCase_AMConfigureOutputTriggerSelect;
			tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			tl->CheckError(testSite, ER_CONST_ERRROR_CATCH);
			String^ ErrorMessage = "Module400Series::SMU_ConfigureOutputTriggerSelect encountered an error: " + ex->Message;
			tl->WriteToFileLgr(tl->glob->FileLog.FileNameDebugLog, ErrorMessage);
			tl->WriteToTcrLgr("SITE " + testSite.ToString(), ErrorMessage);
		}

		return ret;
	}
}