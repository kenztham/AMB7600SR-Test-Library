#include "AMB7600SR.h"

namespace Functions
{
	// AM400e Load Phase Initialization 
	array<String^>^ AMB7600SRTestLibrary::GetAMModuleAlias(Site ^ site, int siteIndex)
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

		array<String^>^ moduleAlias = gcnew array<String^>(moduleCount);
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

		return moduleAlias;
	}
	int AMB7600SRTestLibrary::InitAmPinAliasPreviousState(Site ^ site, int siteIndex)
	{
		int ret = 0;

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

		return ret;
	}
	int AMB7600SRTestLibrary::InitializeAM400eResource(Site ^site)
	{
		int ret = 0;
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
				tl->WriteToLogger(siteIndex, "Initializing SMU[site " + siteIndex + "]...");
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

				for ( count = 0; count < moduleCount[siteIndex]; count++)
				{
					Resource ^ HardwareRsrc = ResourceManagerSett[siteIndex].RsrcManager[siteIndex]->ResolveResource(moduleAlias[siteIndex][count])[0];

					if (HardwareRsrc->Type == "AM430e" || HardwareRsrc->Type == "AM471e" || HardwareRsrc->Type == "AM451e")
					{
						tl->CheckError(siteIndex, smu[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], AM_CONST_SINGLE_SITE));
						tl->WriteToLogger(siteIndex, "Executing smu[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", 0)");
					}
					else
					{
						tl->CheckError(siteIndex, smu[siteIndex]->ConfigureMultiSiteMode(moduleAlias[siteIndex][count], AM_CONST_MULTI_SITE));
						tl->WriteToLogger(siteIndex, "Executing smu[" + siteIndex + "]->ConfigureMultiSiteMode(" + moduleAlias[siteIndex][count] + ", 1)");
					}
				}

				tl->WriteToLogger(siteIndex, "Initializing AM400e Related Global Variables for Previous States...");
				InitAmPinAliasPreviousState(site, siteIndex); //initialize AM modules related global variables to store previous states

				for each (KeyValuePair<String^, int>^ pinAlias in ResourceManagerSett[siteIndex].AMResourceAlias)
				{
					ConfigureSMU(siteIndex, pinAlias->Key, AM_CONST_DVCI, AM_CONST_TRANSIENT_NORMAL, AM_CONST_100UA_RANGE, AM_CONST_PLC, tl->glob->AWV.PowerLineFreq);
				}

				tl->WriteToLogger(siteIndex, "SMU[site " + siteIndex + "] initialized");

			}
			else if (moduleCount[siteIndex] == 0)
			{
				ResourceManagerSett[siteIndex].AM_HardwareStatus = false;
			}
		}

		return ret;
	}
	int AMB7600SRTestLibrary::UninitializeAM400eResource(Site ^site)
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
						tl->WriteToLogger(siteIndex, "Executing smu[" + siteIndex + "]->Reset(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, smu[siteIndex]->Reset(moduleAlias[siteIndex][count]));
						tl->WriteToLogger(siteIndex, "Executing smu[" + siteIndex + "]->Close(" + moduleAlias[siteIndex][count] + ")");
						tl->CheckError(siteIndex, smu[siteIndex]->Close(moduleAlias[siteIndex][count]));
					}
				}
			}
			catch (Exception ^ ex)
			{
				tl->glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				tl->CheckError(siteIndex, ER_CONST_ERRROR_CATCH);
				String^ ErrorMessage = "AMB7600SRTestLibrary:: UninitializeAM400eResource " + "encountered error when performing.";
				tl->FileLogging(siteIndex, LOGGER_ERROR_TYPE, ErrorMessage);
				tl->WriteToLogger(siteIndex, ErrorMessage);
			}
		}

		return ret;
	}

	//AM400e Helper Function
	int AMB7600SRTestLibrary::ConfigureSMU(int testSite, String^ PIN, int Mode, int bandwidth, double compliance, double nplc, double powerLineFreq)
	{
		/*****************************************************************************************************
		** ConfigureSMU
		**		siteIndex	- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**					  project or techFlow sites for Index Parallel project.)
		**		PinAlias	- This is the pin alias name defined in the amap resource file(*.amap).
		**		Mode		- This is either AM_CONST_DICV(=1) or AM_CONST_DVCI(=0).
		**		Bandwidth	- This is the targeted bandwidth (0- Slow, 1-Default, 2-Fast).
		**		Compliance	- This is the targeted voltage compliance if selected mode = AM_CONST_DICV
		**					  else current compliance.
		**		NPLC		- This is the targeted NPLC or sampling time on the specified channel.  For example,
		**					  if the line frequency is set to 50Hz (period is 20ms), then 1 PLC equals to 20ms.
		** Descriptions:
		**		This test method wrapped the SMU configuration in a function to ease the user to configure SMU
		**		in more proper manner.
		******************************************************************************************************/

		int ret = 0;

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

		SMU_OnSMU(testSite,PIN);

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureOS(int testSite, String ^ PIN, double driveCurrent, double clampVoltage, double delay,double % result)
	{
		int ret = 0;

		SMU_ConfigureOutputFunction(testSite, PIN, AM_CONST_DICV);
		SMU_ClampVoltage(testSite, PIN, clampVoltage);		
		SMU_DriveCurrent(testSite, PIN, driveCurrent);
		SMU_MeasureVoltage(testSite, PIN,delay, result);
		SMU_ConfigureOutputFunction(testSite, PIN, AM_CONST_DVCI);
		SMU_ClampCurrent(testSite, PIN, AM_CONST_100UA_RANGE);
		SMU_DriveVoltage(testSite, PIN, 0.0 V);

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureCurrent(int testSite, String ^ PIN,double % result)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ReadCurrent(PIN, result));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureVoltage(int testSite, String ^ PIN, double % result)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ReadVoltage(PIN, result));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureCurrent(int testSite, String ^ PIN,double delay, double % result)
	{
		int ret = 0;

		util->WaitSecond(delay);
		CheckError(testSite, smu[testSite]->ReadCurrent(PIN, result));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureVoltage(int testSite, String ^ PIN, double delay, double % result)
	{
		int ret = 0;

		util->WaitSecond(delay);
		CheckError(testSite, smu[testSite]->ReadVoltage(PIN, result));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureBurstCurrent(int testSite, String ^ PIN, double duration, double peakPercentage, double % result)
	{
		int ret = 0;

		int samplesCount = duration*1e6; //hard code 1M sampling rate for AM430 

		int iHighCount = 0;
		double iHighSum = 0.0;

		array<double> ^ samples = gcnew array<double>(samplesCount);
		double average = 0.0;
		double max = 0.0;

		CheckError(testSite, smu[testSite]->ReadCurrentWithAverage(PIN, samplesCount, average, samples));

		if (!ret)
		{
			for (int i = 0; i<samplesCount; i++)
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

			for (int i = 0; i<samplesCount; i++)
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

				for (int i = 0; i<samplesCount; i++)
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
		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MeasureBurstVoltage(int testSite, String ^ PIN, double duration, double peakPercentage, double % result)
	{
		int ret = 0;

		int samplesCount = duration*1e6; //hard code 1M sampling rate for AM430 

		int iHighCount = 0;
		double iHighSum = 0.0;

		array<double> ^ samples = gcnew array<double>(samplesCount);
		double average = 0.0;
		double max = 0.0;

		CheckError(testSite, smu[testSite]->ReadVoltageWithAverage(PIN, samplesCount, average, samples));

		if (!ret)
		{
			for (int i = 0; i<samplesCount; i++)
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

			for (int i = 0; i<samplesCount; i++)
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

				for (int i = 0; i<samplesCount; i++)
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

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_NplcSetting(int testSite, String ^ PIN, double nplc)
	{
		int ret = 0;

		if ( nplc != tl->glob->SMUStateSettingsManager[testSite].SMUStateNPLC[PIN] )
		{
			CheckError(testSite, smu[testSite]->SetNPLC(PIN, nplc));
			tl->glob->SMUStateSettingsManager[testSite].SMUStateNPLC[PIN] = nplc;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureOutputFunction(int testSite, String ^ PIN, int function)
	{
		int ret = 0;

		if (function != tl->glob->SMUStateSettingsManager[testSite].SMUStateOutputFunction[PIN])
		{
			if (function == AM_CONST_DICV)
			{
				try
				{
					CheckError(testSite, smu[testSite]->ConfigureOutputFunction(PIN, AM_CONST_DICV));
				}
				catch(Exception ^ ex)
				{
					util->WaitSecond(1);
				}
			}
			else if (function == AM_CONST_DVCI)
			{
				CheckError(testSite, smu[testSite]->ConfigureOutputFunction(PIN, AM_CONST_DVCI));
			}

			tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN] = 999.99;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN] = 999.99;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN] = 999.99;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN] = 999.99;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateOutputFunction[PIN] = function;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ClampCurrent(int testSite, String ^ PIN, double clampValue)
	{
		int ret = 0;

		if (clampValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN])
		{
			CheckError(testSite, smu[testSite]->ClampCurrent(PIN, clampValue));

			tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN] = clampValue;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN] = 999.99;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ClampVoltage(int testSite, String ^ PIN, double clampValue)
	{
		int ret = 0;

		if (clampValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN])
		{
			CheckError(testSite, smu[testSite]->ClampVoltage(PIN, clampValue));
			tl->glob->SMUStateSettingsManager[testSite].SMUStateClampVoltage[PIN] = clampValue;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateClampCurrent[PIN] = 999.99;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_DriveCurrent(int testSite, String ^ PIN, double driveValue)
	{
		int ret = 0;

		if (driveValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN])
		{
			CheckError(testSite, smu[testSite]->DriveCurrent(PIN, driveValue));

			tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN] = driveValue;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN] = 999.99;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_DriveVoltage(int testSite, String ^ PIN, double driveValue)
	{
		int ret = 0;

		if (driveValue != tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN])
		{
			CheckError(testSite, smu[testSite]->DriveVoltage(PIN, driveValue));

			tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveVoltage[PIN] = driveValue;
			tl->glob->SMUStateSettingsManager[testSite].SMUStateDriveCurrent[PIN] = 999.99;
		}

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_OnSMU(int testSite, String ^ PIN)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->OnSmuPin(PIN, true, false));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_OffSMU(int testSite, String ^ PIN)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->OffSmuPin(PIN));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_SetBandwidth(int testSite, String ^ PIN, int bandwidth)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->SetBandwidth(PIN, bandwidth));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureSense(int testSite, String ^ PIN, int sense)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureSense(PIN, sense));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigurePowerLineFreq(int testSite, String ^ PIN, double plf)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigurePLF(PIN, plf));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_MapTriggerInToTriggerOut(int testSite, String ^ moduleAlias, int inputTerminal, int outputTerminal)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->MapTriggerInToTriggerOut(moduleAlias, inputTerminal, outputTerminal));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_DriveSoftwareTrigger(int testSite, String ^ moduleAlias, int select, double pulseWidth)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->DriveSoftwareTrigger(moduleAlias, select, pulseWidth));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureTriggerEdgeLevel(int testSite, String ^ moduleAlias, int trigSource, int trigMode)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureTriggerEdgeLevel(moduleAlias, trigSource, trigMode));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureTriggerEdgeLevelExtra(int testSite, String ^ moduleAlias, int trigSource, int trigMode, int ignoreTrigCount)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureTriggerEdgeLevelExtra(moduleAlias, trigSource, trigMode, ignoreTrigCount));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureInputTriggerSelect(int testSite, String ^ pinAlias, int trigSource, double delayAfterTrig)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureInputTriggerSelect(pinAlias, trigSource, delayAfterTrig));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureSMUOutputTriggerMode(int testSite, String ^ pinAlias, int mode)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureSMUOutputTriggerMode(pinAlias, mode));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureSMUOutputTriggerPulseWidth(int testSite, String ^ pinAlias, double pulseWidth)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureSMUOutputTriggerPulseWidth(pinAlias, pulseWidth));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureSMUOutputTriggerDuringSource(int testSite, String ^ pinAlias, double level, double range, int mode, int edgeSetting)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureSMUOutputTriggerDuringSource(pinAlias, level, range, mode, edgeSetting));

		return ret;
	}
	int AMB7600SRTestLibrary::SMU_ConfigureOutputTriggerSelect(int testSite, String ^ pinAlias, int triggerOutput, double triggerDelay)
	{
		int ret = 0;

		CheckError(testSite, smu[testSite]->ConfigureOutputTriggerSelect(pinAlias, triggerOutput, triggerDelay));

		return ret;
	}

}