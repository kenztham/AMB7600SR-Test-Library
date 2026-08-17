/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			AMB7300Utility.cpp
Purpose:		Contain flow item condition value casting
				Contain flow item condition name & value validation
Version:		v1.0.0.10
----------------------------------------------------------------------*/


#include "..\\TestProgram.h"

namespace Functions
{

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Control Step: VnaConfig
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::TestLib_ControlStep_VnaConfig_CastCondition(Site ^ site, int tfSite, int siteIndex, int segmentSetCount)
	{
		/*****************************************************************************************************
		**	TestLib_ControlStep_VnaConfig_CastCondition
		**	site			- This is techFlow site object.
		**	tfSite			- This is techFlow site index.
		**	siteIndex		- This is vna's object index, normally start from 0.
		**	segmentSetCount	- This is total segment set count of the VNA segment settings.
		**
		**	Descriptions:
		**		This function is to cast condition from the control step item 'VnaConfig'.
		******************************************************************************************************/

		// Local variable
		int ret							= 0;
		array<String^> ^ reservedForNA	= nullptr;

		vnaSetting[siteIndex].currentVnaFetchChannel = Vna_Channel_Reset;
		vnaSetting[siteIndex].currentVnaFetchChannelAve = Vna_Channel_Reset;

#pragma region "SweepType"

		//-------------------- SweepType --------------------
		array<String^> ^ sweepType = gcnew array<String^>(1);
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_SweepType))
		{
			sweepType[0] = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_SweepType);
		}
		else
		{
			ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_SweepType);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'SweepType' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'SweepType' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}
		
		// Validate condition value input --> 'SweepType'
		ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_SweepType, sweepType, segmentSetting[siteIndex].segmentCount);
		if (ret != 0) goto EndOfTest;

		segmentSetting[siteIndex].GetFromStateFile = false;
		if (sweepType[0] == Cond_SweepType_LinearFreq)
		{
			segmentSetting[siteIndex].sweepType			= Vna_Stimulus_SweepType_LinearFreq;
		}
		else if (sweepType[0] == Cond_SweepType_LogFreq)
		{
			segmentSetting[siteIndex].sweepType			= Vna_Stimulus_SweepType_LogFreq;
		}
		else if (sweepType[0] == Cond_SweepType_Segment)
		{
			segmentSetting[siteIndex].sweepType			= Vna_Stimulus_SweepType_Segment;
		}
		else if (sweepType[0] == Cond_SweepType_PowerSweep)
		{
			segmentSetting[siteIndex].sweepType			= Vna_Stimulus_SweepType_PowerSweep;
		}
		else if (sweepType[0] == Cond_SweepType_GetFromStateFile)
		{
			segmentSetting[siteIndex].sweepType			= Vna_SweepType_GetFromStateFile;
			segmentSetting[siteIndex].GetFromStateFile	= true;
		}
		else if (sweepType[0] == Cond_SweepType_SharedMemoryTransfer)
		{
			segmentSetting[siteIndex].sweepType			= Vna_SharedMemoryTransfer;
		}

#pragma endregion

#pragma region "ChannelNum"
		vnaSetting[siteIndex].ChannelNumCondition_Exist = false;

		//-------------------- ChannelNum --------------------
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_ChannelNum))
		{
			vnaSetting[siteIndex].ChannelNumCondition_Exist = true;

			// For True Parallel MultiUUT Project
			if (tl->glob->tf.ProjectType == int(ProjectType::SingleTFSiteMultiUUTOffsetSharedVNA))
			{
				vnaSetting[siteIndex].currentVnaFetchChannel = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_ChannelNum) + siteIndex;
			}
			else
			{
				vnaSetting[siteIndex].currentVnaFetchChannel = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_ChannelNum);
			}

			// Validate condition value input --> 'ChannelNum'
			ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_ChannelNum, reservedForNA, segmentSetting[siteIndex].segmentCount);
			if (ret != 0) goto EndOfTest;
		}
		//else
		{
			/*ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_ChannelNum);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'ChannelNum' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'ChannelNum' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;*/
		}

#pragma endregion

		/*if (segmentSetting[siteIndex].sweepType == Vna_SweepType_GetFromStateFile)
		{
			ret = GetChannelandTraceSetting_CMT(tfSite, siteIndex);
			if (ret != 0) goto EndOfTest;
		}
		else*/
		{
#pragma region "Setting <-> Not from the control step condition"

			if (segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_LinearFreq || segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_PowerSweep)
			{
				segmentSetting[siteIndex].segmentCount = 1;
			}
			else if (segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_Segment)
			{
				segmentSetting[siteIndex].segmentCount = segmentSetCount;
			}
			else if (segmentSetting[siteIndex].sweepType == Vna_SweepType_GetFromStateFile)
			{
				segmentSetting[siteIndex].segmentCount = 1;
			}
			else if (segmentSetting[siteIndex].sweepType == Vna_SharedMemoryTransfer)
			{
				segmentSetting[siteIndex].segmentCount = segmentSetCount;
			}
			// [Future Enchancement] For GetFromStateFile, for now user still need to fill-in Points, maybe there is a way to grab the points from the selected state file.

		// Setup storage
			segmentSetting[siteIndex].startFreq = gcnew array<double>(segmentSetting[siteIndex].segmentCount);
			segmentSetting[siteIndex].stopFreq = gcnew array<double>(segmentSetting[siteIndex].segmentCount);
			segmentSetting[siteIndex].point = gcnew array<int>(segmentSetting[siteIndex].segmentCount);
			segmentSetting[siteIndex].ifbw = gcnew array<double>(segmentSetting[siteIndex].segmentCount);
			segmentSetting[siteIndex].power = gcnew array<double>(segmentSetting[siteIndex].segmentCount);
			segmentSetting[siteIndex].delay = gcnew array<double>(segmentSetting[siteIndex].segmentCount);
			segmentSetting[siteIndex].singleMarker = gcnew array<double>(segmentSetting[siteIndex].segmentCount);

			if (prev_segmentSetting[siteIndex].segmentCount != segmentSetting[siteIndex].segmentCount)
			{
				prev_segmentSetting[siteIndex].segmentCount = segmentSetting[siteIndex].segmentCount;
				prev_segmentSetting[siteIndex].startFreq = gcnew array<double>(prev_segmentSetting[siteIndex].segmentCount);
				prev_segmentSetting[siteIndex].stopFreq = gcnew array<double>(prev_segmentSetting[siteIndex].segmentCount);
				prev_segmentSetting[siteIndex].point = gcnew array<int>(prev_segmentSetting[siteIndex].segmentCount);
				prev_segmentSetting[siteIndex].ifbw = gcnew array<double>(prev_segmentSetting[siteIndex].segmentCount);
				prev_segmentSetting[siteIndex].power = gcnew array<double>(prev_segmentSetting[siteIndex].segmentCount);
				prev_segmentSetting[siteIndex].delay = gcnew array<double>(prev_segmentSetting[siteIndex].segmentCount);
				prev_segmentSetting[siteIndex].singleMarker = gcnew array<double>(prev_segmentSetting[siteIndex].segmentCount);
			}

#pragma endregion

			// Get segment settings. Support multiple segment set
			for (int segmentSetIndex = 0; segmentSetIndex < segmentSetting[siteIndex].segmentCount; segmentSetIndex++)
			{
#pragma region"Start Freq"
				//-------------------- Start Freq --------------------
				if ((segmentSetIndex == 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StratFreq)))
				{
					segmentSetting[siteIndex].startFreq[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StratFreq);
				}
				else if ((segmentSetIndex > 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StratFreq_ + segmentSetIndex.ToString())))
				{
					segmentSetting[siteIndex].startFreq[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StratFreq_ + segmentSetIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_StratFreq);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'StartFreq' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'StartFreq' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
#pragma endregion

#pragma region "Stop Freq"
				//-------------------- Stop Freq --------------------
				if ((segmentSetIndex == 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StopFreq)))
				{
					segmentSetting[siteIndex].stopFreq[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StopFreq);
				}
				else if ((segmentSetIndex > 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StopFreq_ + segmentSetIndex.ToString())))
				{
					segmentSetting[siteIndex].stopFreq[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_StopFreq_ + segmentSetIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_StopFreq);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'StopFreq' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'StopFreq' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
#pragma endregion

#pragma region "Points"
				//-------------------- Points --------------------
				if ((segmentSetIndex == 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Points)))
				{
					segmentSetting[siteIndex].point[segmentSetIndex] = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Points);
				}
				else if ((segmentSetIndex > 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Points_ + segmentSetIndex.ToString())))
				{
					segmentSetting[siteIndex].point[segmentSetIndex] = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Points_ + segmentSetIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_Points);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Points' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Points' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
#pragma endregion

#pragma region "Ifbw"
				//-------------------- Ifbw --------------------
				if ((segmentSetIndex == 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Ifbw)))
				{
					segmentSetting[siteIndex].ifbw[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Ifbw);
				}
				else if ((segmentSetIndex > 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Ifbw_ + segmentSetIndex.ToString())))
				{
					segmentSetting[siteIndex].ifbw[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Ifbw_ + segmentSetIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_Ifbw);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Ifbw' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Ifbw' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
#pragma endregion

#pragma region "Power"
				//-------------------- Power --------------------
				if ((segmentSetIndex == 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Power)))
				{
					segmentSetting[siteIndex].power[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Power);
				}
				else if ((segmentSetIndex > 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Power_ + segmentSetIndex.ToString())))
				{
					segmentSetting[siteIndex].power[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Power_ + segmentSetIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_Power);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Power' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Power' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
#pragma endregion

#pragma region "Delay"
				//-------------------- Delay --------------------
				if ((segmentSetIndex == 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Delay)))
				{
					segmentSetting[siteIndex].delay[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Delay);
				}
				else if ((segmentSetIndex > 0) && (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Delay_ + segmentSetIndex.ToString())))
				{
					segmentSetting[siteIndex].delay[segmentSetIndex] = (double)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_Delay_ + segmentSetIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_Delay);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Delay' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'Delay' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
#pragma endregion

				//-------------------- Single Marker (Dummy) --------------------
				if (segmentSetIndex == 0)
					segmentSetting[siteIndex].singleMarker[segmentSetIndex] = segmentSetting[siteIndex].startFreq[segmentSetIndex];
			}

#pragma region "Setting <-> Not from the control step condition"

			// Get total points
			if (segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_LinearFreq)
			{
				segmentSetting[siteIndex].totalPoint = segmentSetting[siteIndex].point[0];
			}
			else if (segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_Segment)
			{
				int totalPoints = 0;
				for (int i = 0; i < segmentSetting[siteIndex].point->Length; i++)
				{
					totalPoints += segmentSetting[siteIndex].point[i];
				}
				segmentSetting[siteIndex].totalPoint = totalPoints;
				totalPoints = 0;
			}
			else if (segmentSetting[siteIndex].sweepType == Vna_SweepType_GetFromStateFile)
			{
				segmentSetting[siteIndex].totalPoint = segmentSetting[siteIndex].point[0];
				// [Future Enchancement] For GetFromStateFile, for now user still need to fill-in Points, maybe there is a way to get from the selected state file.
			}
			else if (segmentSetting[siteIndex].sweepType == Vna_SharedMemoryTransfer)
			{
			//	segmentSetting[siteIndex].totalPoint = segmentSetting[siteIndex].point[0];
				int totalPoints = 0;
				for (int i = 0; i < segmentSetting[siteIndex].point->Length; i++)
				{
					totalPoints += segmentSetting[siteIndex].point[i];
				}
				segmentSetting[siteIndex].totalPoint = totalPoints;
				totalPoints = 0;
			}

			// Default set LogMag for initial segment setting only, will be seting again in control step item 'VnaFetch'
			segmentSetting[siteIndex].sparaFormat = SParam_FormatVNA::LogMagnitude;

#pragma endregion
		}

		// Validate condition value input --> 'FreqStart' + 'FreqStop', 'Points', 'Ifbw', 'Power', 'Delay'
		if ((segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_LinearFreq) || (segmentSetting[siteIndex].sweepType == Vna_Stimulus_SweepType_Segment))
		{	
			ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_StratFreq, reservedForNA, segmentSetting[siteIndex].segmentCount);
			if (ret != 0) goto EndOfTest;
			ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_Points, reservedForNA, segmentSetting[siteIndex].segmentCount);
			if (ret != 0) goto EndOfTest;
			ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_Ifbw, reservedForNA, segmentSetting[siteIndex].segmentCount);
			if (ret != 0) goto EndOfTest;
			ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_Power, reservedForNA, segmentSetting[siteIndex].segmentCount);
			if (ret != 0) goto EndOfTest;
			ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_Delay, reservedForNA, segmentSetting[siteIndex].segmentCount);
			if (ret != 0) goto EndOfTest;
		}
		else if (segmentSetting[siteIndex].sweepType == Vna_SweepType_GetFromStateFile)
		{
			//ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_Points, reservedForNA, segmentSetting[siteIndex].segmentCount);
			//if (ret != 0) goto EndOfTest;
			// [Future Enchancement] For GetFromStateFile, for now user still need to fill-in Points, maybe there is a way to get from the selected state file.
		}

#pragma region "SNP"

		// Obsolete
		////-------------------- SNP --------------------
		//array<String^> ^ SNP_Override = gcnew array<String^>(1);
		//if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_SNP))
		//{
		//	SNP_Override[0] = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaConfigConditionName_SNP);
		//}
		//else
		//{
		//	ret = ER_CONST_VNACONFIG_CONDITION_NAME_NOT_FOUND;
		//	ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaConfigConditionName_SNP);
		//	tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'SNP' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
		//	tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition name verification] 'SNP' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
		//	return ret;
		//}

		//// Validate condition value input --> 'SweepType'
		//ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaConfigConditionName_SNP, SNP_Override, 1);
		//if (ret != 0) goto EndOfTest;

		//if (SNP_Override[0] == "NA")
		//{
		//	projectStateInfo.SNP_Override = "NA";
		//}
		//else if (SNP_Override[0] == Vna_SaveDataToTouchstoneFile_Type_S3P)
		//{
		//	projectStateInfo.SNP_Override = Vna_SaveDataToTouchstoneFile_Type_S3P;
		//}

#pragma endregion

	EndOfTest:
		return ret;
	}

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Control Step: VnaFetch
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::TestLib_ControlStep_VnaFetch_CastCondition(Site ^ site, int tfSite, int siteIndex)
	{
		/*****************************************************************************************************
		**	TestLib_ControlStep_VnaFetch_CastCondition
		**	site			- This is techFlow site object.
		**	tfSite			- This is techFlow site index.
		**	siteIndex		- This is vna's object index, normally start from 0.
		**
		**	Descriptions:
		**		This function is to cast condition from the control step item 'VnaFetch'.
		******************************************************************************************************/

		// Local variable
		int ret							= 0;
		array<String^> ^ reservedForNA	= nullptr;

#pragma region "Setting <-> Not from the control step condition - Reset Before New VnaFetch"

		// Reset vna setting, trace measurement parameter, and trace format before execute a new 'VnaFetch' (new sweep)
		for (int i = 0; i < 16; i++)
		{
			vnaSetting[siteIndex].measType[i]			= Vna_Measurement_Type_Reset;
			vnaSetting[siteIndex].vna_traceFormat[i]		= Vna_Format_Reset;
		}
		vnaSetting[siteIndex].userTraceCount				= 0;

#pragma endregion

#pragma region "MeasurePortPair"

		//-------------------- MeasurePortPair --------------------
		String ^ measurePortPair = String::Empty;
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_MeasurePortPair))
		{
			measurePortPair = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_MeasurePortPair);
		}
		else
		{
			ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaFetchConditionName_MeasurePortPair);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'MeasurePortPair' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'MeasurePortPair' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		array<String^> ^ arrStrFull		= gcnew array<String^>(0);
		array<String^> ^ separatorFull	= gcnew array<String^>(1);
		separatorFull[0]				= "/";
		arrStrFull						= measurePortPair->Split(separatorFull, StringSplitOptions::None);

		array<String^> ^ arrStr		= gcnew array<String^>(0);
		array<String^> ^ separator	= gcnew array<String^>(1);
		separator[0]				= ",";
		//arrStr						= measurePortPair->Split(separator, StringSplitOptions::None);
		if (arrStrFull->Length > 1)
		{
			arrStr = arrStrFull[siteIndex]->Split(separator, StringSplitOptions::None);
		}
		else
		{
			arrStr = arrStrFull[0]->Split(separator, StringSplitOptions::None);
		}

		// Validate condition value input --> 'MeasurePortPair'
		ret = ValidateConditionValueInput_VnaFetch(tfSite, siteIndex, VnaFetchConditionName_MeasurePortPair, arrStr);
		if (ret != 0) goto EndOfTest;

		int portCount = arrStr->Length;
		vnaSetting[siteIndex].pinAlias = gcnew array<String^>(portCount);
		for (int i = 0; i < portCount; i++)
		{
			vnaSetting[siteIndex].pinAlias[i] = arrStr[i];
		}

		/* 
		** Record the type of measurement 
		** Example: 2-port measurement: OUT1,OUT17
		** array size = 2
		** it is S2P type
		**
		** Example: 4-port measurement: OUT1,OUT2,OUT3,OUT4
		** array size = 4
		** it is S4P type
		*/
		vnaSetting[siteIndex].measureSnpType = portCount;

#pragma endregion

#pragma region "TraceCount"

		//-------------------- TraceCount --------------------
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_TraceCount))
		{
			vnaSetting[siteIndex].userTraceCount = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_TraceCount);
		}
		else
		{
			ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaFetchConditionName_TraceCount);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'TraceCount' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'TraceCount' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'TraceCount'
		ret = ValidateConditionValueInput_VnaFetch(tfSite, siteIndex, VnaFetchConditionName_TraceCount, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

#pragma region "TraceMeasurementFormat"

		//-------------------- TraceMeasurementFormat --------------------
		String ^ traceMeasurementFormat = String::Empty;
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_TraceMeasurementFormat))
		{
			traceMeasurementFormat = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_TraceMeasurementFormat);
		}
		else
		{
			ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaFetchConditionName_TraceMeasurementFormat);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'TraceMeasurementFormat' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'TraceMeasurementFormat' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		arrStr						= gcnew array<String^>(0);
		separator					= gcnew array<String^>(1);
		separator[0]				= ",";
		arrStr						= traceMeasurementFormat->Split(separator, StringSplitOptions::None);
		/*	outcome example	
		**	arrStr[0] = "S11/SWR"
		**	arrStr[1] = "S21/LogMag"
		**	arrStr[2] = "S12/LogMag"
		**	arrStr[3] = "S22/LogMag"
		*/

		// Validate condition value input --> 'TraceMeasurementFormat'
		ret = ValidateConditionValueInput_VnaFetch(tfSite, siteIndex, VnaFetchConditionName_TraceMeasurementFormat, arrStr);
		if (ret != 0) goto EndOfTest;

		array<String^> ^ arrStr2	= gcnew array<String^>(0);
		array<String^> ^ separator2 = gcnew array<String^>(1);
		separator2[0]				= "/";
		for (int i = 0; i < arrStr->Length; i++)
		{
			arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);
			/*	outcome example
			**	arrStr2[0] = "S11"	|	arrStr2[0]	= "S21"	
			**	arrStr2[1] = "SWR"	|	arrStr2[1]	= "LogMag"
			*/

			//-------------------- Trace Measure Type --------------------
			if ((arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S11) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S12) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S13) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S14) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S15) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S16) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S21) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S22) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S23) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S24) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S25) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S26) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S31) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S32) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S33) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S34) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S35) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S36) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S41) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S42) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S43) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S44) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S45) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S46) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S51) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S52) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S53) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S54) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S55) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S56) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S61) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S62) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S63) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S64) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S65) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_S66) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A11) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A12) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A13) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A14) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A15) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A16) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A21) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A22) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A23) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A24) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A25) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A26) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A31) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A32) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A33) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A34) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A35) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A36) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A41) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A42) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A43) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A44) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A45) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A46) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A51) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A52) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A53) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A54) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A55) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A56) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A61) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A62) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A63) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A64) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A65) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_A66) || 
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B11) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B12) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B13) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B14) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B15) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B16) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B21) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B22) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B23) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B24) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B25) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B26) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B31) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B32) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B33) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B34) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B35) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B36) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B41) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B42) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B43) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B44) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B45) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B46) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B51) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B52) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B53) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B54) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B55) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B56) ||
				(arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B61) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B62) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B63) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B64) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B65) || (arrStr2[0] == Cond_TraceMeasurementFormat_Parameter_B66))
			{
				vnaSetting[siteIndex].measType[i] = arrStr2[0];
			}

			//-------------------- Trace Format --------------------
			if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_LogMag)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::MLOGarithmic);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_SWR)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::SWR);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_Phase)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::PHASe);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_ExPhase)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::UPHase);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_Delay)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::GDELay);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_LinMag)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::MLINear);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_Real)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::REAL);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_Imag)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::IMAGinary);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_SmithLog)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::SLOGarithmic);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_SmithLin)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::SLINear);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_SmithReIm)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::SCOMplex);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_SmithRJX)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::SMITh);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_SmithGJB)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::SADMittance);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_PolarLog)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::PLOGarithmic);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_PolarLin)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::PLINear);
			}
			else if (arrStr2[1] == Cond_TraceMeasurementFormat_Format_PolarReIm)
			{
				vnaSetting[siteIndex].vna_traceFormat[i] = int(VNATraceFormat::POLar);
			}

			// Reset content
			arrStr2 = gcnew array<String^>(0);
		}

#pragma endregion

#pragma region "AveragingSetting"

		//-------------------- AveragingSetting --------------------
		String ^ averagingSetting = String::Empty;
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_AveragingSetting))
		{
			averagingSetting = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_AveragingSetting);
		}
		else
		{
			ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaFetchConditionName_AveragingSetting);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'AveragingSetting' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'AveragingSetting' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		arrStr			= gcnew array<String^>(0);
		separator		= gcnew array<String^>(1);
		separator[0]	= "/";
		arrStr			= averagingSetting->Split(separator, StringSplitOptions::None);

		// Validate condition value input --> 'AveragingSetting'
		ret = ValidateConditionValueInput_VnaFetch(tfSite, siteIndex, VnaFetchConditionName_AveragingSetting, arrStr);
		if (ret != 0) goto EndOfTest;

		// AveragingSetting parameter: AveragingEnable (AveOn | AveOff), AveragingFactor (default 10)
		if (arrStr->Length == 2)
		{
			averagingSettings.averagingEnable = arrStr[0];
			averagingSettings.averagingFactor = Double::Parse(arrStr[1]);
		}
		else
		{
			ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
			String ^ additionalMessage =	"'AveragingSetting' contain 2x parameter which is differentiate by '/'."	+ "\n" +
											"1st parameter: Enable averaging."											+ "\n" +
											"2nd parameter: Set averaging factor."										+ "\n" +
											"Example: AveOn/10 --> meaning enable averaging, apply 10 averaging factor.";
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_AveragingSetting, additionalMessage);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

#pragma endregion

#pragma region "ChannelNum"

		//// Obsolete
		////-------------------- ChannelNum --------------------
		////if ((amb7300SystemSetting->systemAlias = AMB7300_S4P1D_TYPE) ||
		////	(amb7300SystemSetting->systemAlias = AMB7300_S6P1D_TYPE))
		//{
		//	if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_ChannelNum))
		//	{
		//		//if (tl->glob->tf.activeUUT_count > 1)
		//		//{
		//		//	// Hardcode here for MultiUUT True Parellel channel
		//		//	if (siteIndex == 0)
		//		//		vnaSetting[siteIndex].currentVnaFetchChannel = 1;

		//		//	else if (siteIndex == 1)
		//		//		vnaSetting[siteIndex].currentVnaFetchChannel = 2;
		//		//}
		//		//else
		//		//{
		//		//	vnaSetting[siteIndex].currentVnaFetchChannel = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_ChannelNum);
		//		//}
		//		vnaSetting[siteIndex].currentVnaFetchChannel = (int)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_ChannelNum) + siteIndex;
		//	}
		//	//else
		//	{
		//		/*ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
		//		ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaFetchConditionName_ChannelNum);
		//		tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'ChannelNum' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
		//		tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'ChannelNum' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
		//		return ret;*/
		//	}

		//	// Validate condition value input --> 'ChannelNum'
		//	ret = ValidateConditionValueInput_VnaConfig(tfSite, siteIndex, VnaFetchConditionName_ChannelNum, reservedForNA);
		//	if (ret != 0) goto EndOfTest;
		//}

#pragma endregion

#pragma region "SaveSnpData"

		//-------------------- SaveSnpData --------------------

		// Need to set SaveSnpDataOn in AWV to enable snp data generation for current TestParameter

		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_SaveSnpData))
		{
			saveRecallSetting->EnableSaveSnpData = (bool)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_SaveSnpData);
		}
		else
		{
			// do nothing, code error message here if need to make this mandatory in future
		}

#pragma endregion

/*#pragma region "SnpDataFilePath"

		//-------------------- SnpDataFilePathway --------------------
		String ^ SnpDataFilePathway = String::Empty;
		if (tf_FlowStep_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_SnpDataFilePath))
		{
			saveRecallSetting->touchstoneFilePath = (String^)tf_FlowStep_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaFetchConditionName_SnpDataFilePath);
		}
		else
		{
			ret = ER_CONST_VNAFETCH_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaFetchConditionName_SnpDataFilePath);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'SnpDataFilePathway' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition name verification] 'SnpDataFilePathway' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

#pragma endregion*/

	EndOfTest:
		return ret;
	}

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Test Parameter: VnaDataAnalysis
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::TestLib_TestParameter_VnaDataAnalysis_CastCondition(Site ^ site, int tfSite, int siteIndex)
	{
		/*****************************************************************************************************
		**	TestLib_TestParameter_VnaDataAnalysis_CastCondition
		**	site			- This is techFlow site object.
		**	tfSite			- This is techFlow site index.
		**	siteIndex		- This is vna's object index, normally start from 0.
		**
		**	Descriptions:
		**		This function is to cast condition from the test parameter item 'VnaDataAnalysis'.
		******************************************************************************************************/

		// Local variable
		int ret										= 0;
		array<String^> ^ reservedForNA				= nullptr;
		array<String^> ^ arrStr						= gcnew array<String^>(0);
		array<String^> ^ separator					= gcnew array<String^>(1);
		array<String^> ^ arrStr2					= gcnew array<String^>(0);
		array<String^> ^ separator2					= gcnew array<String^>(1);
		ConditionCollection ^ conditionCollection	= gcnew ConditionCollection;
		Condition ^ condition;

#pragma region "TraceIndex"

		//-------------------- TraceIndex --------------------
		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_TraceIndex))
		{
			vnaDataAnalysisTPC.traceIndex = (int)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_TraceIndex);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_TraceIndex);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'TraceIndex' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'TraceIndex' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'TraceIndex'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_TraceIndex, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

#pragma region "Function"

		//-------------------- Function --------------------
		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Function))
		{
			vnaDataAnalysisTPC.function = (String^)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Function);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_Function);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Function' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Function' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'Function'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_Function, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

#pragma region "Freq | FreqRangeStart | FreqRangeStop"

		/*
		**	Default condition got 1x Freq, 1x FreqRangeStart, 1x FreqRangeStop.
		**	If it is a single test freq or single marker		--> user will insert in the 'Freq' condition.
		**	If it is a test freq range or marker freq range		--> user will insert in the 'FreqRangeStart' & 'FreqRangeStop' condition.
		**	If it is the multiple freq or freq range, the condition will have 'Freq_n' or 'FreqRangeStart_n', or 'FreqRangeStop_n' duplicated condition.
		**	The count and variable's array are reserved for the multiple set of freq or freq range condition in future.
		*/

		int countFreq				= 0;
		int countFreqRangeStart		= 0;
		int countFreqRangeStop		= 0;
		conditionCollection			= tf_TestParameter_ConditionList(tl->glob->currentSubItemName[siteIndex]);
		for each (condition in conditionCollection)
		{
			if (condition->Name->Contains(VnaDataAnalysisConditionName_FreqRangeStart))
				countFreqRangeStart++;
			else if (condition->Name->Contains(VnaDataAnalysisConditionName_FreqRangeStop))
				countFreqRangeStop++;
			else if (condition->Name->Contains(VnaDataAnalysisConditionName_Freq))
				countFreq++;
		}

		if ((countFreq == countFreqRangeStart) && (countFreq == countFreqRangeStop) & (countFreqRangeStart == countFreqRangeStop))
		{
			vnaDataAnalysisTPC.testFreq				= gcnew array<double>(countFreq);
			vnaDataAnalysisTPC.testFreqRangeStart	= gcnew array<double>(countFreqRangeStart);
			vnaDataAnalysisTPC.testFreqRangeStop		= gcnew array<double>(countFreqRangeStop);

			for (int freqIndex = 0; freqIndex < countFreq; freqIndex++)
			{
				//-------------------- Single Freq --------------------
				if ((freqIndex == 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Freq)))
				{
					vnaDataAnalysisTPC.testFreq[freqIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Freq);
				}
				else if ((freqIndex > 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Freq_ + freqIndex.ToString())))
				{
					vnaDataAnalysisTPC.testFreq[freqIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Freq_ + freqIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_Freq);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Freq' or 'Freq_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Freq' or 'Freq_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				//-------------------- Freq Range Start --------------------
				if ((freqIndex == 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStart)))
				{
					vnaDataAnalysisTPC.testFreqRangeStart[freqIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStart);
				}
				else if ((freqIndex > 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStart_ + freqIndex.ToString())))
				{
					vnaDataAnalysisTPC.testFreqRangeStart[freqIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStart_ + freqIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_FreqRangeStart);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'FreqRangeStart' or 'FreqRangeStart_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'FreqRangeStart' or 'FreqRangeStart_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				//-------------------- Freq Range Stop --------------------
				if ((freqIndex == 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStop)))
				{
					vnaDataAnalysisTPC.testFreqRangeStop[freqIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStop);
				}
				else if ((freqIndex > 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStop_ + freqIndex.ToString())))
				{
					vnaDataAnalysisTPC.testFreqRangeStop[freqIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_FreqRangeStop_ + freqIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_FreqRangeStop);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'FreqRangeStop' or 'FreqRangeStop_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'FreqRangeStop' or 'FreqRangeStop_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}

			// Record for generic use
			vnaDataAnalysisTPC.overallTestFreqCount = countFreq;
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Freq);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition set verification] 'Freq', 'FreqRangeStart', 'FreqRangeStop' condition name set amount invalid. Should have the same condition name set amount." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition set verification] 'Freq', 'FreqRangeStart', 'FreqRangeStop' condition name set amount invalid. Should have the same condition name set amount." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'Freq' + 'FreqRangeStart' + 'FreqRangeStop'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_Freq, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

#pragma region "PowerRangeStart | PowerRangeStop"

		/*
		**	Default condition got 1x PowerRangeStart, 1x PowerRangeStop.
		**	If it is a single test power or single marker		--> user will insert in the 'Power' condition.
		**	If it is a test power range or marker power range		--> user will insert in the 'PowerRangeStart' & 'PowerRangeStop' condition.
		**	If it is the multiple power or power range, the condition will have 'Power_n' or 'PowerRangeStart_n', or 'PowerRangeStop_n' duplicated condition.
		**	The count and variable's array are reserved for the multiple set of power or power range condition in future.
		*/

		int countPower = 0;
		int countPowerRangeStart = 0;
		int countPowerRangeStop = 0;
		conditionCollection = tf_TestParameter_ConditionList(tl->glob->currentSubItemName[siteIndex]);
		for each (condition in conditionCollection)
		{
			if (condition->Name->Contains(VnaDataAnalysisConditionName_PowerRangeStart))
				countPowerRangeStart++;
			else if (condition->Name->Contains(VnaDataAnalysisConditionName_PowerRangeStop))
				countPowerRangeStop++;
			else if (condition->Name->Contains(VnaDataAnalysisConditionName_Power))
				countPower++;
		}

		if ((countPower == countPowerRangeStart) && (countPower == countPowerRangeStop) & (countPowerRangeStart == countPowerRangeStop))
		{
			vnaDataAnalysisTPC.testPower = gcnew array<double>(countPower);
			vnaDataAnalysisTPC.testPowerRangeStart = gcnew array<double>(countPowerRangeStart);
			vnaDataAnalysisTPC.testPowerRangeStop = gcnew array<double>(countPowerRangeStop);

			for (int powerIndex = 0; powerIndex < countPower; powerIndex++)
			{
				//-------------------- Single Power --------------------
				if ((powerIndex == 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Power)))
				{
					vnaDataAnalysisTPC.testPower[powerIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Power);
				}
				else if ((powerIndex > 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Power_ + powerIndex.ToString())))
				{
					vnaDataAnalysisTPC.testPower[powerIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Power_ + powerIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_Power);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Power' or 'Power_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Power' or 'Power_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				//-------------------- Power Range Start --------------------
				if ((powerIndex == 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStart)))
				{
					vnaDataAnalysisTPC.testPowerRangeStart[powerIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStart);
				}
				else if ((powerIndex > 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStart_ + powerIndex.ToString())))
				{
					vnaDataAnalysisTPC.testPowerRangeStart[powerIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStart_ + powerIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_PowerRangeStart);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'PowerRangeStart' or 'PowerRangeStart_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'PowerRangeStart' or 'PowerRangeStart_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				//-------------------- Power Range Stop --------------------
				if ((powerIndex == 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStop)))
				{
					vnaDataAnalysisTPC.testPowerRangeStop[powerIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStop);
				}
				else if ((powerIndex > 0) && (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStop_ + powerIndex.ToString())))
				{
					vnaDataAnalysisTPC.testPowerRangeStop[powerIndex] = (double)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_PowerRangeStop_ + powerIndex.ToString());
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_PowerRangeStop);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'PowerRangeStop' or 'PowerRangeStop_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'PowerRangeStop' or 'PowerRangeStop_x' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}

			// Record for generic use
			vnaDataAnalysisTPC.overallTestPowerCount = countPower;
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Power);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition set verification] 'Power', 'PowerRangeStart', 'PowerRangeStop' condition name set amount invalid. Should have the same condition name set amount." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition set verification] 'Power', 'PowerRangeStart', 'PowerRangeStop' condition name set amount invalid. Should have the same condition name set amount." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'Power' + 'PowerRangeStart' + 'PowerRangeStop'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_Power, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

#pragma region "AnalysisSetting"

		/*
		**	The index usage and variable in array format are reserved for the multiple set of analysis settings in future.
		*/

		//-------------------- AnalysisSetting --------------------
		String ^ analysisSettingStrCond = String::Empty;
		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_AnalysisSetting))
		{
			analysisSettingStrCond = (String^)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_AnalysisSetting);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_AnalysisSetting);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'AnalysisSetting' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'AnalysisSetting' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		//-------------------- Handle Analysis Settings For Each DataAnalysis's Type --------------------
		arrStr			= gcnew array<String^>(0);
		separator		= gcnew array<String^>(1);
		separator[0]	= ",";
		arrStr			= analysisSettingStrCond->Split(separator, StringSplitOptions::None);
		arrStr2			= gcnew array<String^>(0);
		separator2		= gcnew array<String^>(1);
		separator2[0]	= "/";

		int index = 0;
		for (int i = 0; i < arrStr->Length; i++)
		{
			// TraceData
			if (vnaDataAnalysisTPC.function == Cond_Function_TraceData)
			{
				// NA
			}
			// mmMinMax
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMax)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> msMinMax'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.msMinMax_SearchRangeEnable	= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.msMinMax_SearchType			= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// msMinMax parameter: SearchRangeEnable (SearchRangeOn | SearchRangeOff), SearchType (Max | Min)
				if (arrStr2->Length == 2)
				{
					analysisSetting.msMinMax_SearchRangeEnable[index]	= arrStr2[0];
					analysisSetting.msMinMax_SearchType[index]			= arrStr2[1];
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msMinMax' function contain 2x parameter which is differentiate by '/'." + "\n" +  
													"1st parameter: Enable marker search range."													+ "\n" + 
													"2nd parameter: Select marker search type."														+ "\n" + 
													"Example: SearchRangeOn/Max --> meaning enable marker search range, searching for maximum value.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'msMinMax' mode is invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'msMinMax' mode is invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// msPeak
			else if (vnaDataAnalysisTPC.function == Cond_Function_msPeak)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> msPeak'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.msPeak_Type			= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.msPeak_PeakExcursion = gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.msPeak_PeakPolarity	= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				/*analysisSetting.msPeak_PeakThreshold = gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);*/
				// msPaek parameter: PeakType (SearchPeak | SearchPeakLeft | SearchPeakRight), PeakExcursion (default 1dB), PeakPolarity (Positive | Negative | Both)
				if (arrStr2->Length == 3)
				{
					analysisSetting.msPeak_Type[index]			= arrStr2[0];
					analysisSetting.msPeak_PeakExcursion[index]	= Double::Parse(arrStr2[1]);
					analysisSetting.msPeak_PeakPolarity[index]	= arrStr2[2];
					/*analysisSetting.msPeak_PeakThreshold[index] = Double::Parse(arrStr2[3]);*/
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msPeak' function contain 3x parameter which is differentiate by '/'."	+ "\n" +
													"1st parameter: Select marker search peak's type."												+ "\n" + 
													"2nd parameter: Set peak excursion."															+ "\n" + 
													"3rd parameter: Select peak polarity."															+ "\n" + 
													"Example: SearchPeak/1/Positive --> meaning select search peak type, apply 1dB peak excursion, select positive peak polarity.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'msPeak' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'msPeak' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// msTarget
			else if (vnaDataAnalysisTPC.function == Cond_Function_msTarget)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> msTarget'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.msTarget_Type				= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.msTarget_TargetValue			= gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.msTarget_TargetTransition	= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				//analysisSetting.msTarget_TargetLineEnable	= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// msTarget parameter: TargetType (SearchTarget | SearchTargetLeft | SearchTargetRight), TargetValue (default 0dB), TargetTransition (Both | Positive | Negative)
				if (arrStr2->Length == 3)
				{
					analysisSetting.msTarget_Type[index]				= arrStr2[0];
					analysisSetting.msTarget_TargetValue[index]		= Double::Parse(arrStr2[1]);
					analysisSetting.msTarget_TargetTransition[index] = arrStr2[2];
					//analysisSetting.msTarget_TargetLineEnable[index] = arrStr2[3];
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msTarget' function contain 3x parameter which is differentiate by '/'." + "\n" + 
													"1st parameter: Select marker search target's type."											+ "\n" + 
													"2nd parameter: Set target value."																+ "\n" + 
													"3rd parameter: Select target transition."														+ "\n" +  
													"Example: SearchTarget/-10/Positive --> meaning select search target, apply 10dB target value, select positive target transition.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'msTarget' mode is invalid. It should contain 4x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'msTarget' mode is invalid. It should contain 4x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// P1dBTarget
			else if (vnaDataAnalysisTPC.function == Cond_Function_P1dBTarget)
			{
			}
			// mmStatistics
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmStatistics)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> mmStatistics'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.mmStatistics_StatisticsRangeEnable = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// mmStatistics parameter: StatisticsRangeEnable (StatisticsRangeOn | StatisticsRangeOff)
				if (arrStr2->Length == 1)
				{
					analysisSetting.mmStatistics_StatisticsRangeEnable[index] = arrStr2[0];
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'mmStatistics' function contain 1x parameter which is differentiate by '/'." + "\n" +  
													"1st parameter: Enable statistics range."															+ "\n" +  
													"Example: StatisticsRangeOn --> meaning enable statistics range.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'mmStatistics' mode is invalid. It should contain 1x value parameter, without a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'mmStatistics' mode is invalid. It should contain 1x value parameter, without a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// mmBwSearch
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmBwSearch)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> mmBwSearch'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.mmBwSearch_Type				= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.mmBwSearch_SearchRef			= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.mmBwSearch_BandwidthValue	= gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.mmBwSearch_Condition         = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// mmBwSearch parameter: Type (Bandpass | Notch), Search Ref (Marker | Max | Min | Peak), Bandwidth Value (default -3dB)
				
				/*if (arrStr2->Length == 4) //obsolete
				{
					analysisSetting.mmBwSearch_Type[index]			= arrStr2[0];
					analysisSetting.mmBwSearch_SearchRef[index]		= arrStr2[1];
					analysisSetting.mmBwSearch_BandwidthValue[index] = Double::Parse(arrStr2[2]);
					analysisSetting.mmBwSearch_Condition[index]      = arrStr2[3];
				}*/
				if (arrStr2->Length == 3)
				{
					analysisSetting.mmBwSearch_Type[index] = arrStr2[0];
					analysisSetting.mmBwSearch_SearchRef[index] = arrStr2[1];
					analysisSetting.mmBwSearch_BandwidthValue[index] = Double::Parse(arrStr2[2]);
					analysisSetting.mmBwSearch_Condition[index] = "N/A";
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'mmBwSearch' function contain 3x parameter which is differentiate by '/'."	+ "\n" +  
													"1st parameter: Select search type."																+ "\n" + 
													"2nd parameter: Select search reference."															+ "\n" +  
													"3rd parameter: Set bandwidth value."																+ "\n" +  
													"Example: Bandpass/Marker/-3 --> meaning select bandpass type, select marker as search reference, apply -3dB bandwidth value.\n";           
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'mmBwSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'mmBwSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// mmBwSearchAbs
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmBwSearchAbs)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> mmBwSearch'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.mmBwSearch_Type = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.mmBwSearch_SearchRef = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.mmBwSearch_BandwidthValue = gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.mmBwSearch_Condition = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// mmBwSearch parameter: Type (Bandpass | Notch), Search Ref (Marker | Max | Min | Peak), Bandwidth Value (default -3dB)
				
				/*if (arrStr2->Length == 4) //obsolete
				{
					analysisSetting.mmBwSearch_Type[index] = arrStr2[0];
					analysisSetting.mmBwSearch_SearchRef[index] = arrStr2[1];
					analysisSetting.mmBwSearch_BandwidthValue[index] = Double::Parse(arrStr2[2]);
					analysisSetting.mmBwSearch_Condition[index] = arrStr2[3];
				}*/
				if (arrStr2->Length == 3)
				{
					analysisSetting.mmBwSearch_Type[index] = arrStr2[0];
					analysisSetting.mmBwSearch_SearchRef[index] = arrStr2[1];
					analysisSetting.mmBwSearch_BandwidthValue[index] = Double::Parse(arrStr2[2]);
					analysisSetting.mmBwSearch_Condition[index] = "Abs";
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'mmBwSearchAbs' function contain 3x parameter which is differentiate by '/'." + "\n" +
						"1st parameter: Select search type." + "\n" +
						"2nd parameter: Select search reference." + "\n" +
						"3rd parameter: Set bandwidth value." + "\n" +
						"Example: Bandpass/Marker/-3 --> meaning select bandpass type, select marker as search reference, apply -3dB bandwidth value.\n";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'mmBwSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'mmBwSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// mmFlatness
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmFlatness)
			{
				// NA
			}
			// msMinMaxRipple
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMaxRipple || vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryMinMaxRipple)
			{
				// NA
			}
			// SharedMemoryDataMinMax
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataMinMax)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> SharedMemoryDataMinMax'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.SharedMemorySearchRangeEnable = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataMinMax_SearchType = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// msMinMax parameter: SearchRangeEnable (SearchRangeOn | SearchRangeOff), SearchType (Max | Min)
				if (arrStr2->Length == 2)
				{
					analysisSetting.SharedMemorySearchRangeEnable[index] = arrStr2[0];
					analysisSetting.SharedMemoryDataMinMax_SearchType[index] = arrStr2[1];
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataMinMax' function contain 2x parameter which is differentiate by '/'." + "\n" +
						"1st parameter: Enable marker search range." + "\n" +
						"2nd parameter: Select marker search type." + "\n" +
						"Example: SearchRangeOn/Max --> meaning enable marker search range, searching for maximum value.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataMinMax' mode is invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataMinMax' mode is invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// SharedMemoryDataTarget
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataTarget)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> SharedMemoryDataTarget'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.SharedMemorySearchRangeEnable = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataTarget_TargetValue = gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataTarget_TargetTransition = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				//analysisSetting.msTarget_TargetLineEnable	= gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				// msTarget parameter: TargetType (SearchTarget | SearchTargetLeft | SearchTargetRight), TargetValue (default 0dB), TargetTransition (Both | Positive | Negative)
				if (arrStr2->Length == 3)
				{
					analysisSetting.SharedMemorySearchRangeEnable[index] = arrStr2[0];
					analysisSetting.SharedMemoryDataTarget_TargetValue[index] = Double::Parse(arrStr2[1]);
					analysisSetting.SharedMemoryDataTarget_TargetTransition[index] = arrStr2[2];
					//analysisSetting.msTarget_TargetLineEnable[index] = arrStr2[3];
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataTarget' function contain 3x parameter which is differentiate by '/'." + "\n" +
						"1st parameter: Select marker search target's type." + "\n" +
						"2nd parameter: Set target value." + "\n" +
						"3rd parameter: Select target transition." + "\n" +
						"Example: SearchTarget/-10/Positive --> meaning select search target, apply 10dB target value, select positive target transition.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataTarget' mode is invalid. It should contain 4x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataTarget' mode is invalid. It should contain 4x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// SharedMemoryDataBWSearch
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearch)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> SharedMemoryDataBwSearch'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.SharedMemorySearchRangeEnable = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_Type = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_SearchRef = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_BandwidthValue = gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_Condition = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
								
				/*if (arrStr2->Length == 4) //Obsolete
				{
					analysisSetting.mmBwSearch_Type[index] = arrStr2[0];
					analysisSetting.mmBwSearch_SearchRef[index] = arrStr2[1];
					analysisSetting.mmBwSearch_BandwidthValue[index] = Double::Parse(arrStr2[2]);
					analysisSetting.mmBwSearch_Condition[index] = arrStr2[3];
				}*/
				if (arrStr2->Length == 4)
				{
					analysisSetting.SharedMemorySearchRangeEnable[index] = arrStr2[0];
					analysisSetting.SharedMemoryDataBWSearch_Type[index] = arrStr2[1];
					analysisSetting.SharedMemoryDataBWSearch_SearchRef[index] = arrStr2[2];
					analysisSetting.SharedMemoryDataBWSearch_BandwidthValue[index] = Double::Parse(arrStr2[3]);
					analysisSetting.SharedMemoryDataBWSearch_Condition[index] = "N/A";//原先为 N/A，现修改为。。
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataBWSearch' function contain 3x parameter which is differentiate by '/'." + "\n" +
						"1st parameter: Select search range On/Off." + "\n" +
						"2nd parameter: Select search type." + "\n" +
						"3rd parameter: Select search reference." + "\n" +
						"4th parameter: Set bandwidth value." + "\n" +
						"Example: SearchRangeOff/Bandpass/Marker/-3 --> meaning select bandpass type, select marker as search reference, apply -3dB bandwidth value.\n";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataBWSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataBWSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// SharedMemoryDataBWSearch
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearchAbs)
			{
				arrStr2 = gcnew array<String^>(0);
				arrStr2 = arrStr[i]->Split(separator2, StringSplitOptions::None);

				// Validate condition value input --> 'AnalysisSetting -> SharedMemoryDataBwSearch'
				ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_AnalysisSetting, arrStr2);
				if (ret != 0) goto EndOfTest;

				analysisSetting.SharedMemorySearchRangeEnable = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_Type = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_SearchRef = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_BandwidthValue = gcnew array<double>(vnaDataAnalysisTPC.overallTestFreqCount);
				analysisSetting.SharedMemoryDataBWSearch_Condition = gcnew array<String^>(vnaDataAnalysisTPC.overallTestFreqCount);

				/*if (arrStr2->Length == 4) //Obsolete
				{
				analysisSetting.mmBwSearch_Type[index] = arrStr2[0];
				analysisSetting.mmBwSearch_SearchRef[index] = arrStr2[1];
				analysisSetting.mmBwSearch_BandwidthValue[index] = Double::Parse(arrStr2[2]);
				analysisSetting.mmBwSearch_Condition[index] = arrStr2[3];
				}*/
				if (arrStr2->Length == 4)
				{
					analysisSetting.SharedMemorySearchRangeEnable[index] = arrStr2[0];
					analysisSetting.SharedMemoryDataBWSearch_Type[index] = arrStr2[1];
					analysisSetting.SharedMemoryDataBWSearch_SearchRef[index] = arrStr2[2];
					analysisSetting.SharedMemoryDataBWSearch_BandwidthValue[index] = Double::Parse(arrStr2[3]);
					analysisSetting.SharedMemoryDataBWSearch_Condition[index] = "Abs";
				}
				else
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataBWSearch' function contain 3x parameter which is differentiate by '/'." + "\n" +
						"1st parameter: Select search range On/Off." + "\n" +
						"2nd parameter: Select search type." + "\n" +
						"3rd parameter: Select search reference." + "\n" +
						"4th parameter: Set bandwidth value." + "\n" +
						"Example: SearchRangeOff/Bandpass/Marker/-3 --> meaning select bandpass type, select marker as search reference, apply -3dB bandwidth value.\n";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataBWSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value for 'SharedMemoryDataBWSearch' mode is invalid. It should contain 3x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}

			index++;
		}
		index = 0;

#pragma endregion

#pragma region "SmoothingSetting"

		//-------------------- SmoothingSetting --------------------
		String ^ smoothingSetting = String::Empty;
		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_SmoothingSetting))
		{
			smoothingSetting = (String^)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_SmoothingSetting);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_SmoothingSetting);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'SmoothingSetting' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'SmoothingSetting' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		arrStr			= gcnew array<String^>(0);
		separator		= gcnew array<String^>(1);
		separator[0]	= "/";
		arrStr			= smoothingSetting->Split(separator, StringSplitOptions::None);

		// Validate condition value input --> 'SmoothingSetting'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_SmoothingSetting, arrStr);
		if (ret != 0) goto EndOfTest;

		// SmoothingSetting parameter: SmoothingEnable (SmoOn | SmoOff), SmoothingAperture (default 1%)
		if (arrStr->Length == 2)
		{
			smoothingSettings.smoothingEnable	= arrStr[0];
			smoothingSettings.smoothingAperture	= Double::Parse(arrStr[1]);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
			String ^ additionalMessage =	"'SmoothingSetting' contain 2x parameter which is differentiate by '/'."	+ "\n" +
											"1st parameter: Enable smoothing."											+ "\n" +
											"2nd parameter: Set smoothing aperture."									+ "\n" +
											"Example: SmoOn/5 --> meaning enable smoothing, apply 5% smoothing aperture.";
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_SmoothingSetting, additionalMessage);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid. It should contain 2x value parameter, which is differentiate by a '/' symbol." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

#pragma endregion

#pragma region "OutputType"

		// [Future Enchancement] The variable's array are reserved for the multiple set of analysis settings but only return one result to TP in future.

		//-------------------- OutputType --------------------
		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_OutputType))
		{
			vnaDataAnalysisTPC.outputType = (String^)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_OutputType);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_OutputType);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'OutputType' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'OutputType' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'OutputType'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_OutputType, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

#pragma region "OutputFormat"

		//-------------------- OutputFormat --------------------
		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_OutputFormat))
		{
			vnaDataAnalysisTPC.outputFormat = (String^)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_OutputFormat);
		}
		else
		{
			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_OutputFormat);
			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'OutputFormat' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'OutputFormat' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
			return ret;
		}

		// Validate condition value input --> 'OutputFormat'
		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_OutputFormat, reservedForNA);
		if (ret != 0) goto EndOfTest;

#pragma endregion

//#pragma region "Threshold"
//
//		//-------------------- Threshold --------------------
//		if (tf_TestParameter_ConditionExist(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Threshold))
//		{
//			vnaDataAnalysisTPC.Threshold = (double^)tf_TestParameter_ConditionCast(tl->glob->currentSubItemName[siteIndex], VnaDataAnalysisConditionName_Threshold);
//		}
//		else
//		{
//			ret = ER_CONST_VNADATAANALYSIS_CONDITION_NAME_NOT_FOUND;
//			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_CONDITION_NAME_NOT_FOUND, VnaDataAnalysisConditionName_Threshold);
//			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Threshold' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
//			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition name verification] 'Threshold' condition name not found." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
//			return ret;
//		}
//
//		// Validate condition value input --> 'Threshold'
//		ret = ValidateConditionValueInput_VnaDataAnalysis(tfSite, siteIndex, VnaDataAnalysisConditionName_OutputFormat, reservedForNA);
//		if (ret != 0) goto EndOfTest;
//
//#pragma endregion
//
	EndOfTest:
		return ret;
	}

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Validate condition value input ---> VnaConfig
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::ValidateConditionValueInput_VnaConfig(int tfSite, int siteIndex, String ^ conditionName, array<String^> ^ conditionValueRaw, int vnaConfigSegmentCount)
	{
		/*****************************************************************************************************
		**	ValidateConditionValueInput_VnaConfig
		**	tfSite					- This is techFlow site object.
		**	siteIndex				- This is techFlow site index.
		**	conditionName			- This is the condition name.
		**	conditionValueRaw		- This is the condition value input (raw) in the array form.
		**	vnaConfigSegmentCount	- This is the total VNA segment count.
		**
		**	Descriptions:
		**		This function is to validate all the condition value input in 'VnaConfig'.
		**		Include: 'SweepType', 'StartFreq', 'StopFreq', 'Points', 'Ifbw', 'Power', 'Delay'.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

#pragma region "SweepType"

		if (conditionName == VnaConfigConditionName_SweepType)
		{
			if ((conditionValueRaw[0] != Cond_SweepType_LinearFreq) &&
				(conditionValueRaw[0] != Cond_SweepType_LogFreq) &&
				(conditionValueRaw[0] != Cond_SweepType_Segment) &&
				(conditionValueRaw[0] != Cond_SweepType_PowerSweep) &&
				(conditionValueRaw[0] != Cond_SweepType_GetFromStateFile) &&
				(conditionValueRaw[0] != Cond_SweepType_SharedMemoryTransfer))
			{
				ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage = "'SweepType' available settings: " + "\n" +
					"-> LinearFreq" + "\n" +
					"-> LogFreq" + "\n" +
					"-> Segment" + "\n" +
					"-> PowerSweep" + "\n" +
					"-> GetFromStateFile" + "\n" +
					"-> SharedMemoryTransfer";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_SweepType, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'SweepType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'SweepType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}
		}

#pragma endregion

#pragma region "ChannelNum"

		if (conditionName == VnaConfigConditionName_ChannelNum)
		{
			bool match_flag = false;
			for (int i = 0; i < vnaSetting[siteIndex].vna_chn->Length; i++)
			{
				if (vnaSetting[siteIndex].vna_chn[i] == vnaSetting[siteIndex].currentVnaFetchChannel)
				{
					match_flag = true;
				}
			}
			if ((vnaSetting[siteIndex].currentVnaFetchChannel < 1) ||
				(vnaSetting[siteIndex].currentVnaFetchChannel > 8))
			{
				ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage = "'ChannelNum' available settings: " + "\n" +
					"-> 1 ~ 16";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_ChannelNum, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'ChannelNum' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'ChannelNum' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}
			else if (match_flag == false)
			{
				String^ str_vna_chn = "";
				ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
				for (int i = 0; i < vnaSetting[siteIndex].vna_chn->Length; i++)
				{
					str_vna_chn += vnaSetting[siteIndex].vna_chn[i].ToString() + ", " ;
				}
				String ^ additionalMessage = "'ChannelNum' does not exist in mapping file! Please calibrate the Channel. " + "\n" +
											"Channel available from Mapping file-> " + str_vna_chn;
					
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_ChannelNum, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'ChannelNum' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'ChannelNum' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}
		}

#pragma endregion

#pragma region "StartFreq & StopFreq"

		if ((conditionName == VnaConfigConditionName_StratFreq) ||
			(conditionName == VnaConfigConditionName_StopFreq))
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{ 
					if ((segmentSetting[siteIndex].startFreq[i] < 300.0 kHz) ||
						(segmentSetting[siteIndex].startFreq[i] > 9000.0 MHz))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'StartFreq' available settings: " + "\n" +
														"-> 300.0 kHz ~ 9000.0 MHz";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StratFreq, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}

					if ((segmentSetting[siteIndex].stopFreq[i] < 300.0 kHz) ||
						(segmentSetting[siteIndex].stopFreq[i] > 9000.0 MHz))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'StopFreq' available settings: " + "\n" +
														"-> 300.0 kHz ~ 9000.0 MHz";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StopFreq, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((segmentSetting[siteIndex].startFreq[i] < 9.0 kHz) ||
						(segmentSetting[siteIndex].startFreq[i] > 20000.0 MHz))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'StartFreq' available settings: " + "\n" +
														"-> 9.0 kHz ~ 20000.0 MHz";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StratFreq, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}

					if ((segmentSetting[siteIndex].stopFreq[i] < 9.0 kHz) ||
						(segmentSetting[siteIndex].stopFreq[i] > 20000.0 MHz))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'StopFreq' available settings: " + "\n" +
														"-> 9.0 kHz ~ 20000.0 MHz";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StopFreq, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
		}

#pragma endregion

#pragma region "If StartFreq same with StopFreq"

		if ((conditionName == VnaConfigConditionName_StratFreq) ||
			(conditionName == VnaConfigConditionName_StopFreq))
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (segmentSetting[siteIndex].startFreq[i] == segmentSetting[siteIndex].stopFreq[i])
				{
					ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'StartFreq' & 'StopFreq' cannot have the same frequency condition value.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StratFreq + " & " + VnaConfigConditionName_StopFreq, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' & 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''StartFreq' & StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "If segment frequency overlap with other segment frequency"

		if ((conditionName == VnaConfigConditionName_StratFreq) ||
			(conditionName == VnaConfigConditionName_StopFreq))
		{
			for (int i = 1; i < vnaConfigSegmentCount; i++)
			{
				if (segmentSetting[siteIndex].startFreq[i] <= segmentSetting[siteIndex].stopFreq[i - 1])
				{
					ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "Segment frequency cannot overlap with other segment frequency.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StratFreq + " & " + VnaConfigConditionName_StopFreq, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' & 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''StartFreq' & StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "If FreqStart & FreqStop invalid in range order"

		if ((conditionName == VnaConfigConditionName_StratFreq) ||
			(conditionName == VnaConfigConditionName_StopFreq))
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (segmentSetting[siteIndex].startFreq[i] > segmentSetting[siteIndex].stopFreq[i])
				{
					ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'StartFreq' & 'StopFreq' must exist in a valid range (StartFreq must < StopFreq).";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_StratFreq + " & " + VnaConfigConditionName_StopFreq, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'StartFreq' & 'StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''StartFreq' & StopFreq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "Points"

		if (conditionName == VnaConfigConditionName_Points)
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					// CMT spec max point is 500001, but in test library we limit the point up to 100001 to prevent S2VNA hang
					if ((segmentSetting[siteIndex].point[i] < 2 ) ||
						(segmentSetting[siteIndex].point[i] > 100001))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Points' available settings: " + "\n" +
														"-> 2 ~ 100001";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Ifbw, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Points' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Points' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((segmentSetting[siteIndex].point[i] < 1 ) ||
						(segmentSetting[siteIndex].point[i] > 100003))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Points' available settings: " + "\n" +
														"-> 1 ~ 100003";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Ifbw, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Points' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Points' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
		}

#pragma endregion

#pragma region "Ifbw"

		if (conditionName == VnaConfigConditionName_Ifbw)
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					if ((segmentSetting[siteIndex].ifbw[i] < 1.0 Hz) ||
						(segmentSetting[siteIndex].ifbw[i] > 1.0 MHz))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Ifbw' available settings: " + "\n" +
														"-> 1.0 Hz ~ 1.0 MHz";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Ifbw, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Ifbw' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Ifbw' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((segmentSetting[siteIndex].ifbw[i] < 1.0 Hz) ||
						(segmentSetting[siteIndex].ifbw[i] > 15.0 MHz))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Ifbw' available settings: " + "\n" +
														"-> 1.0 Hz ~ 15.0 MHz";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Ifbw, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Ifbw' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Ifbw' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
		}

#pragma endregion

#pragma region "Power"

		if (conditionName == VnaConfigConditionName_Power)
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					if ((segmentSetting[siteIndex].power[i] < -50.0 dBm) ||
						(segmentSetting[siteIndex].power[i] > 15.0 dBm))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Power' available settings: " + "\n" +
														"-> -50.0 dBm ~ +15.0 dBm";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Power, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((segmentSetting[siteIndex].power[i] < -100.0 dBm) ||
						(segmentSetting[siteIndex].power[i] > 20.0 dBm))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Power' available settings: " + "\n" +
														"-> -100.0 dBm ~ +20.0 dBm";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Power, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
		}

#pragma endregion

#pragma region "Delay"

		if (conditionName == VnaConfigConditionName_Delay)
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					if ((segmentSetting[siteIndex].delay[i] < 0.0 S) ||
						(segmentSetting[siteIndex].delay[i] > 100.0 S))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Delay' available settings: " + "\n" +
														"-> 0.0 sec ~ 100.0 sec";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Delay, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Delay' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Delay' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((segmentSetting[siteIndex].delay[i] < -86400.0 S) ||
						(segmentSetting[siteIndex].delay[i] > 86400.0 S))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'Delay' available settings: " + "\n" +
														"-> -86400 sec ~ 86400.0 sec";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_Delay, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'Delay' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''Delay' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
		}

#pragma endregion

#pragma region"SNP"

		if (conditionName == VnaConfigConditionName_SNP)
		{
			for (int i = 0; i < vnaConfigSegmentCount; i++)
			{
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					if ((conditionValueRaw[0] != "NA") &&
						(conditionValueRaw[0] != Vna_SaveDataToTouchstoneFile_Type_S3P))
					{
						ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'SNP' available settings: " + "\n" +
							"-> NA\n" +
							"-> S3P\n";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_SNP, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'SNP' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''SNP' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((conditionValueRaw[0] != "NA") &&
						(conditionValueRaw[0] != Vna_SaveDataToTouchstoneFile_Type_S3P))
					{
					ret = ER_CONST_VNACONFIG_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'SNP' available settings: " + "\n" +
						"-> NA\n" +
						"-> S3P\n";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaConfigConditionName_SNP, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] 'SNP' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaConfig' condition value verification] ''SNP' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
					}
				}
			}
		}

#pragma endregion

	EndOfTest:
		return ret;
	}
	
	/*
	**	----------------------------------------------------------------------------------------------------
	**	Validate condition value input ---> VnaFetch
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::ValidateConditionValueInput_VnaFetch(int tfSite, int siteIndex, String ^ conditionName, array<String^> ^ conditionValueRaw)
	{
		/*****************************************************************************************************
		**	ValidateConditionValueInput_VnaFetch
		**	tfSite				- This is techFlow site object.
		**	siteIndex			- This is techFlow site index.
		**	conditionName		- This is the condition name.
		**	conditionValueRaw	- This is the condition value input (raw) in the array form.
		**
		**	Descriptions:
		**		This function is to validate all the condition value input in the 'VnaFetch'.
		**		Include: 'MeasurePortPair', 'TraceCount', 
		**		'TraceMeasurementFormat', 'AveragingSetting', 'SaveSnpData'.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

#pragma region "MeasurePortPair --> validate port count and port alias pair"

		if (conditionName == VnaFetchConditionName_MeasurePortPair)
		{ 
			// Determine measurement type: 1-port / 2-port / 3-port / 4-port / 5-port / 6-port
			int measurePortCount = conditionValueRaw->Length;

			if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
			{
				if (measurePortCount == 2)
				{
					// A0 S2P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A0)) && (sysConfigInfo.configurationType == AMB7300_S2P1_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_A0_S2P_P1) ||
							(conditionValueRaw[1] != Cond_MeasurePortPair_A0_S2P_P2))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A0 (S2P)"	+ "\n" +
															"Port1 name only available in: P1"				+ "\n" +
															"Port2 name only available in: P2";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A1 S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A1)) && (sysConfigInfo.configurationType == AMB7300_S2P4_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A1_S2P_OUT1) && 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A1_S2P_OUT2)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A1_S2P_OUT3)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A1_S2P_OUT4)) ||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A1_S2P_OUT5) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A1_S2P_OUT6)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A1_S2P_OUT7)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A1_S2P_OUT8)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A1 (S2P)"				+ "\n" +
															"Port1 name only available in: OUT1, OUT2, OUT3, OUT4"		+ "\n" +
															"Port2 name only available in: OUT5, OUT6, OUT7, OUT8";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A2 S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A2)) && (sysConfigInfo.configurationType == AMB7300_S2P8_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT2)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT3)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT4)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT5)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT6)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT7)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A2_S2P_OUT8)) ||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT9) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT10) && 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT11) && 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT12) && 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT13) && 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT14) && 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT15) && 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A2_S2P_OUT16)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A2 (S2P)"											+ "\n" +
															"Port1 name only available in: OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8"			+ "\n" +
															"Port2 name only available in: OUT9, OUT10, OUT11, OUT12, OUT13, OUT14, OUT15, OUT16";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A3 S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A3)) && (sysConfigInfo.configurationType == AMB7300_S4P2_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT6)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT7)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT8))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT2)	&& 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT3)	&& 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT4)	&& 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT5)	&& 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT6)	&& 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT7)	&& 
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT8)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A3 (S2P)"											+ "\n" +
															"Port1 name only available in: OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8"			+ "\n" +
															"Port2 name only available in: OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A4 S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT4))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT4)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A4 (S2P)"					+ "\n" +
															"Port1 name only available in: OUT1, OUT2, OUT3, OUT4"			+ "\n" +
															"Port2 name only available in: OUT1, OUT2, OUT3, OUT4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A5 S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A5)) && (sysConfigInfo.configurationType == AMB7300_S2P16_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT1)		&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT2)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT3)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT4)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT5)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT6)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT7)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT8)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT9)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT10)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT11)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT12)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT13)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT14)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT15)		&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_A5_S2P_OUT16))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A5_S2P_OUT17)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A5_S2P_OUT18)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A5 (S2P)"																							+ "\n" +
															"Port1 name only available in: OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8, OUT9, OUT10, OUT11, OUT12, OUT13, OUT14, OUT15, OUT16"	+ "\n" +
															"Port2 name only available in: OUT17, OUT18";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration A5 only able to measure S2P ('MeasurePortPair' = OUT1,OUT17), unable to measure S3P ('MeasurePortPair' = OUT1,OUT2,OUT3).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 3)
				{
					// A3 S3P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A3)) && (sysConfigInfo.configurationType == AMB7300_S4P2_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT2))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT3) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT4)) ||
							((conditionValueRaw[2] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT5) &&
							(conditionValueRaw[2] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT6)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A3 (S3P)"		+ "\n" +
															"Port1 name only available in: OUT1, OUT2"			+ "\n" +
															"Port2 name only available in: OUT3, OUT4"			+ "\n" +
															"Port3 name only available in: OUT5, OUT6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A4 S3P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) ||
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2) ||
							(conditionValueRaw[2] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A4 (S3P)"	+ "\n" +
															"Port1 name only available in: OUT1"			+ "\n" +
															"Port2 name only available in: OUT2"			+ "\n" +
															"Port3 name only available in: OUT3";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration A5 only able to measure S2P ('MeasurePortPair' = OUT1,OUT17), unable to measure S3P ('MeasurePortPair' = OUT1,OUT2,OUT3).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 4)
				{
					// A3 S4P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A3)) && (sysConfigInfo.configurationType == AMB7300_S4P2_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT2))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT3) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT4)) ||
							((conditionValueRaw[2] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT5) &&
							(conditionValueRaw[2] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT6))	||
							((conditionValueRaw[3] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT7) &&
							(conditionValueRaw[3] != Cond_MeasurePortPair_A3_S2P_S3P_S4P_OUT8)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A3 (S4P)"	+ "\n" +
															"Port1 name only available in: OUT1, OUT2"		+ "\n" +
															"Port2 name only available in: OUT3, OUT4"		+ "\n" +
															"Port3 name only available in: OUT5, OUT6"		+ "\n" +
															"Port4 name only available in: OUT7, OUT8";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A4 S4P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) ||
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2) ||
							(conditionValueRaw[2] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3) ||
							(conditionValueRaw[3] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT4))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config A4 (S4P)"	+ "\n" +
															"Port1 name only available in: OUT1"			+ "\n" +
															"Port2 name only available in: OUT2"			+ "\n" +
															"Port3 name only available in: OUT3"			+ "\n" +
															"Port4 name only available in: OUT4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration A5 only able to measure S2P ('MeasurePortPair' = OUT1,OUT17), unable to measure S3P ('MeasurePortPair' = OUT1,OUT2,OUT3).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else
				{
					ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'MeasurePortPair' contain 1x parameter which is the actual port name showing in the tester front panel."	+ "\n" + 
													"The port name can be combined into a measurement port pair by using ','."									+ "\n" + 
													"Only available in 2-port, 3-port, 4-port measurement."														+ "\n" + 
													"Example: P1,P2 --> S2P 2-port measurement."																+ "\n" +  
													"Example: OUT1,OUT2,OUT3 --> S3P 3-port measurement."														+ "\n" +  
													"Example: OUT1,OUT2,OUT3,OUT4 --> S4P 4-port measurement.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
			{
				if (measurePortCount == 1)
				{
					// S2P1D S1P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S2P1D)) && (sysConfigInfo.configurationType == AMB7300_S2P1D_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S2P1D_P1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S2P1D_P2))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S2P1D (S1P)"	+ "\n" +
															"Port1 name only available in: P1, P2";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S4P1D S1P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P4))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S4P1D (S1P)"	+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S6P1D S1P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P6))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S6P1D (S1P)"	+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S22P1D
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P22N)) && (sysConfigInfo.configurationType == AMB7300_S6P22N_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT2) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT3) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT4) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT5) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT6) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT7) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT8) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT9) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT10) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT11) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT12) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT13) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT14) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT15) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT16) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT17) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT18) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT19) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT20) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT21) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT22))

						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'MeasurePortPair' for system config S6P22N (S1P)" + "\n" +
								"Port1 name only available in: P1A, P2A, P3A up to P22A";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration S4P1D only able to measure S1P/S2P/S3P/S4P ('MeasurePortPair' = P1,P2,P3,P4), unable to measure S6P ('MeasurePortPair' = P1,P2,P3,P4,P5,P6).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 2)
				{
					// S2P1D S2P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S2P1D)) && (sysConfigInfo.configurationType == AMB7300_S2P1D_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S2P1D_P1) ||
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S2P1D_P2))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S2P1D (S2P)"	+ "\n" +
															"Port1 name only available in: P1"					+ "\n" +
															"Port2 name only available in: P2";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S4P1D S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P4))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P4)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S4P1D (S2P)"	+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4"		+ "\n" +
															"Port2 name only available in: P2, P2, P3, P4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S6P1D S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P6)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S6P1D (S2P)"			+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port2 name only available in: P2, P2, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S6P22N S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P22N)) && (sysConfigInfo.configurationType == AMB7300_S6P22N_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT2) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT3) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT4) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT5) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT6) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT7) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT8) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT9) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT10) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT11) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT12) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT13) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT14) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT15) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT16) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT17) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT18) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT19) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT20) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT21) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P22N_OUT22)) ||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT1) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT2) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT3) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT4) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT5) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT6) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT7) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT8) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT9) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT10) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT11) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT12) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT13) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT14) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT15) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT16) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT17) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT18) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT19) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT20) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT21) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P22N_OUT22)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'MeasurePortPair' for system config S6P22N (S2P)" + "\n" +
								"Port1 name only available in: OUT1~OUT18, P3, P4, P5, P6" + "\n" +
								"Port2 name only available in: OUT1~OUT18, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A4 S2P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3) &&
							(conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT4)) ||
							((conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) &&
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3) &&
								(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT4)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'MeasurePortPair' for system config A4 (S2P)" + "\n" +
								"Port1 name only available in: OUT1, OUT2, OUT3, OUT4" + "\n" +
								"Port2 name only available in: OUT1, OUT2, OUT3, OUT4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration S4P1D only able to measure S1P/S2P/S3P/S4P ('MeasurePortPair' = P1,P2,P3,P4), unable to measure S6P ('MeasurePortPair' = P1,P2,P3,P4,P5,P6).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 3)
				{
					// S4P1D S3P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P4))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P4))	||
							((conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&& 
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P4)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S4P1D (S3P)"	+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4"		+ "\n" +
															"Port2 name only available in: P1, P2, P3, P4"		+ "\n" +
															"Port3 name only available in: P2, P2, P3, P4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S6P1D S3P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P6)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S6P1D (S3P)"			+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port2 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port3 name only available in: P2, P2, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A4 S3P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) ||
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2) ||
							(conditionValueRaw[2] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'MeasurePortPair' for system config A4 (S3P)" + "\n" +
								"Port1 name only available in: OUT1" + "\n" +
								"Port2 name only available in: OUT2" + "\n" +
								"Port3 name only available in: OUT3";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration S4P1D only able to measure S1P/S2P/S3P/S4P ('MeasurePortPair' = P1,P2,P3,P4), unable to measure S6P ('MeasurePortPair' = P1,P2,P3,P4,P5,P6).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 4)
				{
					// S4P1D S4P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S4P1D_P4))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S4P1D_P4))	||
							((conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&& 
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S4P1D_P4))	||
							((conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S4P1D_P1)	&& 
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S4P1D_P2)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S4P1D_P3)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S4P1D_P4)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S4P1D (S4P)"	+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4"		+ "\n" +
															"Port2 name only available in: P1, P2, P3, P4"		+ "\n" +
															"Port3 name only available in: P1, P2, P3, P4"		+ "\n" +
															"Port4 name only available in: P2, P2, P3, P4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// S6P1D S4P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P6)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S6P1D (S4P)"			+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port2 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port3 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port4 name only available in: P2, P2, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					// A4 S4P
					else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
					{
						if ((conditionValueRaw[0] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT1) ||
							(conditionValueRaw[1] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT2) ||
							(conditionValueRaw[2] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT3) ||
							(conditionValueRaw[3] != Cond_MeasurePortPair_A4_S2P_S3P_S4P_OUT4))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'MeasurePortPair' for system config A4 (S4P)" + "\n" +
								"Port1 name only available in: OUT1" + "\n" +
								"Port2 name only available in: OUT2" + "\n" +
								"Port3 name only available in: OUT3" + "\n" +
								"Port4 name only available in: OUT4";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration S4P1D only able to measure S1P/S2P/S3P/S4P ('MeasurePortPair' = P1,P2,P3,P4), unable to measure S6P ('MeasurePortPair' = P1,P2,P3,P4,P5,P6).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 5)
				{
					// S6P1D S5P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P6)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S6P1D (S5P)"			+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port2 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port3 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port4 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port5 name only available in: P2, P2, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration S4P1D only able to measure S1P/S2P/S3P/S4P ('MeasurePortPair' = P1,P2,P3,P4), unable to measure S6P ('MeasurePortPair' = P1,P2,P3,P4,P5,P6).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (measurePortCount == 6)
				{
					// S6P1D S6P
					if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
					{
						if (((conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[0] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[1] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[2] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[3] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[4] != Cond_MeasurePortPair_Keysight_S6P1D_P6))	||
							((conditionValueRaw[5] != Cond_MeasurePortPair_Keysight_S6P1D_P1)	&& 
							(conditionValueRaw[5] != Cond_MeasurePortPair_Keysight_S6P1D_P2)	&&
							(conditionValueRaw[5] != Cond_MeasurePortPair_Keysight_S6P1D_P3)	&&
							(conditionValueRaw[5] != Cond_MeasurePortPair_Keysight_S6P1D_P4)	&&
							(conditionValueRaw[5] != Cond_MeasurePortPair_Keysight_S6P1D_P5)	&&
							(conditionValueRaw[5] != Cond_MeasurePortPair_Keysight_S6P1D_P6)))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'MeasurePortPair' for system config S6P1D (S6P)"			+ "\n" +
															"Port1 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port2 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port3 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port4 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port5 name only available in: P1, P2, P3, P4, P5, P6"		+ "\n" +
															"Port6 name only available in: P2, P2, P3, P4, P5, P6";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else
					{
						ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"Unidentified 'MeasurePortPair'."										+ "\n"
														"'MeasurePortPair' type does not match with the system configuration."	+ "\n"
														"For example: system configuration S4P1D only able to measure S1P/S2P/S3P/S4P ('MeasurePortPair' = P1,P2,P3,P4), unable to measure S6P ('MeasurePortPair' = P1,P2,P3,P4,P5,P6).";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else
				{
					ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'MeasurePortPair' contain 1x parameter which is the actual port name showing in the tester front panel."	+ "\n" + 
													"The port name can be combined into a measurement port pair by using ','."									+ "\n" + 
													"Only available in 2-port, 3-port, 4-port measurement."														+ "\n" + 
													"Example: P1,P2 --> S2P 2-port measurement."																+ "\n" +  
													"Example: OUT1,OUT2,OUT3 --> S3P 3-port measurement."														+ "\n" +  
													"Example: OUT1,OUT2,OUT3,OUT4 --> S4P 4-port measurement.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_MeasurePortPair, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'MeasurePortPair' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "TraceCount"

		if (conditionName == VnaFetchConditionName_TraceCount)
		{ 
			if ((vnaSetting[siteIndex].userTraceCount < 1) ||
				(vnaSetting[siteIndex].userTraceCount > 16))
			{
				ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage =	"'TraceCount' available settings: " + "\n" +
												"-> 1 ~ 16";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceCount, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceCount' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceCount' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}
		}

#pragma endregion

#pragma region "TraceMeasurementFormat"

		/*	raw content
		**	conditionValueRaw[0] = "S11/LogMag"
		**	conditionValueRaw[1] = "S21/LogMag"
		**	conditionValueRaw[2] = "S12/LogMag"
		**	conditionValueRaw[3] = "S22/LogMag"
		*/

		if (conditionName == VnaFetchConditionName_TraceMeasurementFormat)
		{
			array<String^> ^ arrStr2	= gcnew array<String^>(0);
			array<String^> ^ separator2 = gcnew array<String^>(1);
			separator2[0]				= "/";
			
			for (int i = 0; i < conditionValueRaw->Length; i++)
			{
				arrStr2 = conditionValueRaw[i]->Split(separator2, StringSplitOptions::None);
				/*	outcome example
				**	arrStr2[0] = "S11"	|	arrStr2[0]	= "S21"
				**	arrStr2[1] = "SWR"	|	arrStr2[1]	= "LogMag"
				*/

				if (arrStr2->Length == 2)
				{
					if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
					{
						if (vnaSetting[siteIndex].measureSnpType == 2)
						{
							// A0, A1, A2, A3, A4, A5 S2P
							if (((amb7300SystemSetting->systemConfig == int(SystemConfig::A0)) && (sysConfigInfo.configurationType == AMB7300_S2P1_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A1)) && (sysConfigInfo.configurationType == AMB7300_S2P4_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A2)) && (sysConfigInfo.configurationType == AMB7300_S2P8_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A3)) && (sysConfigInfo.configurationType == AMB7300_S4P2_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A5)) && (sysConfigInfo.configurationType == AMB7300_S2P16_TYPE)))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage = "'TraceMeasurementFormat' for system config A0/A1/A2/A3/A4/A5 (S2P), 1st parameter available settings: " + "\n" +
										"-> S11 / A11 / B11" + "\n" +
										"-> S12 / A12 / B12" + "\n" +
										"-> S21 / A21 / B21" + "\n" +
										"-> S22 / A22 / B22";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 3)
						{
							// A3, A4 S3P
							if (((amb7300SystemSetting->systemConfig == int(SystemConfig::A3)) && (sysConfigInfo.configurationType == AMB7300_S4P2_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE)))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config  A3/A4 (S3P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 4)
						{
							// A3, A4 S4P
							if (((amb7300SystemSetting->systemConfig == int(SystemConfig::A3)) && (sysConfigInfo.configurationType == AMB7300_S4P2_TYPE)) ||
								((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE)))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config  A3/A4 (S4P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
															"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
															"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}

						// Measurement format
						if ((arrStr2[1] != Cond_TraceMeasurementFormat_Format_LogMag)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SWR)			&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Phase)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_ExPhase)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Delay)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_LinMag)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Real)			&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Imag)			&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithLog)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithLin)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithReIm)	&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithRJX)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithGJB)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_PolarLog)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_PolarLin)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_PolarReIm))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'TraceMeasurementFormat' 2nd parameter available settings: "	+ "\n" +
															"-> LogMag"														+ "\n" +
															"-> SWR"														+ "\n" +
															"-> Phase"														+ "\n" +
															"-> ExPhase"													+ "\n" +
															"-> Delay"														+ "\n" +
															"-> LinMag"														+ "\n" +
															"-> Real"														+ "\n" +
															"-> Imag"														+ "\n" +
															"-> SmithLog"													+ "\n" +
															"-> SmithLin"													+ "\n" +
															"-> SmithReIm"													+ "\n" +
															"-> SmithR+JX"													+ "\n" +
															"-> SmithG+JB"													+ "\n" +
															"-> PolarLog"													+ "\n" +
															"-> PolarLin"													+ "\n" +
															"-> PolarReIm";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
					{
						if (vnaSetting[siteIndex].measureSnpType == 1)
						{
							// S2P1D S1P
							if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S2P1D)) && (sysConfigInfo.configurationType == AMB7300_S2P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S2P1D (S1P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S22 / A22 / B22";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S4P1D S1P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S4P1D (S1P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S6P1D S1P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S6P1D (S1P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 2)
						{
							// S2P1D S2P
							if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S2P1D)) && (sysConfigInfo.configurationType == AMB7300_S2P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S2P1D (S2P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S4P1D S2P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S4P1D (S2P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S6P1D S2P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B15) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B16) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B25) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B26) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B35) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B36) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B45) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B46) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B51) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B52) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B53) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B54) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B56) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B61) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B62) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B63) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B64) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B65) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S6P1D (S2P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S15 / A15 / B15"																						+ "\n" +
																	"-> S16 / A16 / B16"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S25 / A25 / B25"																						+ "\n" +
																	"-> S26 / A26 / B26"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S35 / A35 / B35"																						+ "\n" +
																	"-> S36 / A36 / B36"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S45 / A45 / B45"																						+ "\n" +
																	"-> S46 / A46 / B46"																						+ "\n" +
																	"-> S51 / A51 / B51"																						+ "\n" +
																	"-> S52 / A52 / B52"																						+ "\n" +
																	"-> S53 / A53 / B53"																						+ "\n" +
																	"-> S54 / A54 / B54"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S56 / A56 / B56"																						+ "\n" +
																	"-> S61 / A61 / B61"																						+ "\n" +
																	"-> S62 / A62 / B62"																						+ "\n" +
																	"-> S63 / A63 / B63"																						+ "\n" +
																	"-> S64 / A64 / B64"																						+ "\n" +
																	"-> S65 / A65 / B65"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S6P22N S2P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P22N)) && (sysConfigInfo.configurationType == AMB7300_S6P22N_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B15) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B16) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B25) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B26) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B35) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B36) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B45) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B46) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B51) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B52) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B53) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B54) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B56) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B61) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B62) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B63) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B64) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B65) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage = "'TraceMeasurementFormat' for system config S6P22N (S2P), 1st parameter available settings: " + "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S15 / A15 / B15"																						+ "\n" +
																	"-> S16 / A16 / B16"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S25 / A25 / B25"																						+ "\n" +
																	"-> S26 / A26 / B26"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S35 / A35 / B35"																						+ "\n" +
																	"-> S36 / A36 / B36"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S45 / A45 / B45"																						+ "\n" +
																	"-> S46 / A46 / B46"																						+ "\n" +
																	"-> S51 / A51 / B51"																						+ "\n" +
																	"-> S52 / A52 / B52"																						+ "\n" +
																	"-> S53 / A53 / B53"																						+ "\n" +
																	"-> S54 / A54 / B54"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S56 / A56 / B56"																						+ "\n" +
																	"-> S61 / A61 / B61"																						+ "\n" +
																	"-> S62 / A62 / B62"																						+ "\n" +
																	"-> S63 / A63 / B63"																						+ "\n" +
																	"-> S64 / A64 / B64"																						+ "\n" +
																	"-> S65 / A65 / B65"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// A4 S2P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage = "'TraceMeasurementFormat' for system config A4(S2P), 1st parameter available settings: " + "\n" +
										"-> S11 / A11 / B11 " + "\n" +
										"-> S12 / A12 / B12 " + "\n" +
										"-> S21 / A21 / B21 " + "\n" +
										"-> S22 / A22 / B22 ";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 3)
						{
							// S4P1D S3P
							if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S4P1D (S3P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S6P1D S3P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B15) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B16) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B25) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B26) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B35) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B36) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B45) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B46) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B51) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B52) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B53) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B54) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B56) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B61) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B62) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B63) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B64) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B65) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S6P1D (S3P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S15 / A15 / B15"																						+ "\n" +
																	"-> S16 / A16 / B16"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S25 / A25 / B25"																						+ "\n" +
																	"-> S26 / A26 / B26"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S35 / A35 / B35"																						+ "\n" +
																	"-> S36 / A36 / B36"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S45 / A45 / B45"																						+ "\n" +
																	"-> S46 / A46 / B46"																						+ "\n" +
																	"-> S51 / A51 / B51"																						+ "\n" +
																	"-> S52 / A52 / B52"																						+ "\n" +
																	"-> S53 / A53 / B53"																						+ "\n" +
																	"-> S54 / A54 / B54"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S56 / A56 / B56"																						+ "\n" +
																	"-> S61 / A61 / B61"																						+ "\n" +
																	"-> S62 / A62 / B62"																						+ "\n" +
																	"-> S63 / A63 / B63"																						+ "\n" +
																	"-> S64 / A64 / B64"																						+ "\n" +
																	"-> S65 / A65 / B65"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// A4 S3P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage = "'TraceMeasurementFormat' for system config A4 (S3P), 1st parameter available settings: " + "\n" +
										"-> S11 / A11 / B11" + "\n" +
										"-> S12 / A12 / B12" + "\n" +
										"-> S13 / A13 / B13" + "\n" +
										"-> S21 / A21 / B21" + "\n" +
										"-> S22 / A22 / B22" + "\n" +
										"-> S23 / A23 / B23" + "\n" +
										"-> S31 / A31 / B31" + "\n" +
										"-> S32 / A32 / B32" + "\n" +
										"-> S33 / A33 / B33";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 4)
						{
							// S4P1D S4P
							if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S4P1D)) && (sysConfigInfo.configurationType == AMB7300_S4P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S4P1D (S4P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// S6P1D S4P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B15) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B16) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B25) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B26) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B35) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B36) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B45) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B46) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B51) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B52) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B53) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B54) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B56) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B61) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B62) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B63) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B64) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B65) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S6P1D (S4P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S15 / A15 / B15"																						+ "\n" +
																	"-> S16 / A16 / B16"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S25 / A25 / B25"																						+ "\n" +
																	"-> S26 / A26 / B26"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S35 / A35 / B35"																						+ "\n" +
																	"-> S36 / A36 / B36"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S45 / A45 / B45"																						+ "\n" +
																	"-> S46 / A46 / B46"																						+ "\n" +
																	"-> S51 / A51 / B51"																						+ "\n" +
																	"-> S52 / A52 / B52"																						+ "\n" +
																	"-> S53 / A53 / B53"																						+ "\n" +
																	"-> S54 / A54 / B54"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S56 / A56 / B56"																						+ "\n" +
																	"-> S61 / A61 / B61"																						+ "\n" +
																	"-> S62 / A62 / B62"																						+ "\n" +
																	"-> S63 / A63 / B63"																						+ "\n" +
																	"-> S64 / A64 / B64"																						+ "\n" +
																	"-> S65 / A65 / B65"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							// A3, A4 S4P
							else if ((amb7300SystemSetting->systemConfig == int(SystemConfig::A4)) && (sysConfigInfo.configurationType == AMB7300_S4P1_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage = "'TraceMeasurementFormat' for system config A4 (S4P), 1st parameter available settings: " + "\n" +
										"-> S11 / A11 / B11" + "\n" +
										"-> S12 / A12 / B12" + "\n" +
										"-> S13 / A13 / B13" + "\n" +
										"-> S14 / A14 / B14" + "\n" +
										"-> S21 / A21 / B21" + "\n" +
										"-> S22 / A22 / B22" + "\n" +
										"-> S23 / A23 / B23" + "\n" +
										"-> S24 / A24 / B24" + "\n" +
										"-> S31 / A31 / B31" + "\n" +
										"-> S32 / A32 / B32" + "\n" +
										"-> S33 / A33 / B33" + "\n" +
										"-> S34 / A34 / B34" + "\n" +
										"-> S41 / A41 / B41" + "\n" +
										"-> S42 / A42 / B42" + "\n" +
										"-> S43 / A43 / B43" + "\n" +
										"-> S44 / A44 / B44";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 5)
						{
							// S6P1D S5P
							if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B15) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B16) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B25) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B26) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B35) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B36) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B45) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B46) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B51) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B52) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B53) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B54) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B56) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B61) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B62) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B63) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B64) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B65) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S6P1D (S5P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S15 / A15 / B15"																						+ "\n" +
																	"-> S16 / A16 / B16"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S25 / A25 / B25"																						+ "\n" +
																	"-> S26 / A26 / B26"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S35 / A35 / B35"																						+ "\n" +
																	"-> S36 / A36 / B36"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S45 / A45 / B45"																						+ "\n" +
																	"-> S46 / A46 / B46"																						+ "\n" +
																	"-> S51 / A51 / B51"																						+ "\n" +
																	"-> S52 / A52 / B52"																						+ "\n" +
																	"-> S53 / A53 / B53"																						+ "\n" +
																	"-> S54 / A54 / B54"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S56 / A56 / B56"																						+ "\n" +
																	"-> S61 / A61 / B61"																						+ "\n" +
																	"-> S62 / A62 / B62"																						+ "\n" +
																	"-> S63 / A63 / B63"																						+ "\n" +
																	"-> S64 / A64 / B64"																						+ "\n" +
																	"-> S65 / A65 / B65"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else if (vnaSetting[siteIndex].measureSnpType == 6)
						{
							// S6P1D S6P
							if ((amb7300SystemSetting->systemConfig == int(SystemConfig::S6P1D)) && (sysConfigInfo.configurationType == AMB7300_S6P1D_TYPE))
							{
								// Measurement parameter
								if ((arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A11) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B11) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A12) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B12) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A13) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B13) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A14) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B14) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A15) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B15) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A16) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B16) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A21) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B21) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A22) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B22) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A23) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B23) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A24) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B24) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A25) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B25) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A26) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B26) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A31) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B31) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A32) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B32) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A33) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B33) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A34) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B34) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A35) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B35) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A36) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B36) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A41) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B41) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A42) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B42) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A43) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B43) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A44) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B44) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A45) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B45) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A46) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B46) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A51) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B51) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A52) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B52) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A53) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B53) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A54) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B54) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A55) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B55) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A56) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B56) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A61) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B61) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A62) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B62) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A63) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B63) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A64) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B64) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A65) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B65) &&
									(arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_S66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_A66) && (arrStr2[0] != Cond_TraceMeasurementFormat_Parameter_B66))
								{
									ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
									String ^ additionalMessage =	"'TraceMeasurementFormat' for system config S6P1D (S6P), 1st parameter available settings: "	+ "\n" +
																	"-> S11 / A11 / B11"																						+ "\n" +
																	"-> S12 / A12 / B12"																						+ "\n" +
																	"-> S13 / A13 / B13"																						+ "\n" +
																	"-> S14 / A14 / B14"																						+ "\n" +
																	"-> S15 / A15 / B15"																						+ "\n" +
																	"-> S16 / A16 / B16"																						+ "\n" +
																	"-> S21 / A21 / B21"																						+ "\n" +
																	"-> S22 / A22 / B22"																						+ "\n" +
																	"-> S23 / A23 / B23"																						+ "\n" +
																	"-> S24 / A24 / B24"																						+ "\n" +
																	"-> S25 / A25 / B25"																						+ "\n" +
																	"-> S26 / A26 / B26"																						+ "\n" +
																	"-> S31 / A31 / B31"																						+ "\n" +
																	"-> S32 / A32 / B32"																						+ "\n" +
																	"-> S33 / A33 / B33"																						+ "\n" +
																	"-> S34 / A34 / B34"																						+ "\n" +
																	"-> S35 / A35 / B35"																						+ "\n" +
																	"-> S36 / A36 / B36"																						+ "\n" +
																	"-> S41 / A41 / B41"																						+ "\n" +
																	"-> S42 / A42 / B42"																						+ "\n" +
																	"-> S43 / A43 / B43"																						+ "\n" +
																	"-> S44 / A44 / B44"																						+ "\n" +
																	"-> S45 / A45 / B45"																						+ "\n" +
																	"-> S46 / A46 / B46"																						+ "\n" +
																	"-> S51 / A51 / B51"																						+ "\n" +
																	"-> S52 / A52 / B52"																						+ "\n" +
																	"-> S53 / A53 / B53"																						+ "\n" +
																	"-> S54 / A54 / B54"																						+ "\n" +
																	"-> S55 / A55 / B55"																						+ "\n" +
																	"-> S56 / A56 / B56"																						+ "\n" +
																	"-> S61 / A61 / B61"																						+ "\n" +
																	"-> S62 / A62 / B62"																						+ "\n" +
																	"-> S63 / A63 / B63"																						+ "\n" +
																	"-> S64 / A64 / B64"																						+ "\n" +
																	"-> S65 / A65 / B65"																						+ "\n" +
																	"-> S66 / A66 / B66";
									ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
									tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
									return ret;
								}
							}
							else
							{
								ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
								String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
																"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
																"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
								ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
								tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
								return ret;
							}
						}
						else
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"Unidentified 'TraceMeasurementFormat'."														+ "\n"
															"'TraceMeasurementFormat' measurement parameter does not match with the system configuration."	+ "\n"
															"For example: system configuration A5 only able to set measurement parameter S11/S12/S21/S22, unable to set S13,S23,S31,S33.";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}

						// Measurement format
						if ((arrStr2[1] != Cond_TraceMeasurementFormat_Format_LogMag)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SWR)			&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Phase)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_ExPhase)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Delay)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_LinMag)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Real)			&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_Imag)			&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithLog)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithLin)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithReIm)	&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithRJX)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_SmithGJB)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_PolarLog)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_PolarLin)		&&
							(arrStr2[1] != Cond_TraceMeasurementFormat_Format_PolarReIm))
						{
							ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage =	"'TraceMeasurementFormat' 2nd parameter available settings: "	+ "\n" +
															"-> LogMag"														+ "\n" +
															"-> SWR"														+ "\n" +
															"-> Phase"														+ "\n" +
															"-> ExPhase"													+ "\n" +
															"-> Delay"														+ "\n" +
															"-> LinMag"														+ "\n" +
															"-> Real"														+ "\n" +
															"-> Imag"														+ "\n" +
															"-> SmithLog"													+ "\n" +
															"-> SmithLin"													+ "\n" +
															"-> SmithReIm"													+ "\n" +
															"-> SmithR+JX"													+ "\n" +
															"-> SmithG+JB"													+ "\n" +
															"-> PolarLog"													+ "\n" +
															"-> PolarLin"													+ "\n" +
															"-> PolarReIm";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
				}
				else
				{
					ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'TraceMeasurementFormat' contain 2x parameter which is differentiate by '/'."						+ "\n" + 
													"It is able to contain multiple sets of setting for each trace# which is differentiate by ','."		+ "\n" +
													"1st parameter: Trace measurement parameter."														+ "\n" + 
													"2nd parameter: Trace measurement format."															+ "\n" + 
													"Example: S21/LogMag --> trace#1 measure 'S21' parameter with 'LogMag' format."						+ "\n" +
													"Example: S11/SWR,S21/LogMag --> trace#1 measure 'S11' parameter with 'SWR' format, trace#2 measure 'S21' parameter with 'LogMag' format.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceMeasurementFormat, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'TraceMeasurementFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "AveragingSetting"

		if (conditionName == VnaFetchConditionName_AveragingSetting)
		{
			if ((conditionValueRaw[0] != Cond_AveragingSetting_Enable_AveOn) &&
				(conditionValueRaw[0] != Cond_AveragingSetting_Enable_AveOff))
			{
				ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage =	"'AveragingSetting' 1st parameter available settings: " + "\n" +
												"-> AveOn"												+ "\n" +
												"-> AveOff";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_AveragingSetting, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}

			if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
			{ 
				/*
				**	Note that the average factor cannot contain decimal, even insert into the S2VNA, it will eliminate the decimal value.
				**	Example: 1.1 ~ 1.9, it will display as 1.
				*/
				if ((Double::Parse(conditionValueRaw[1]) < 1.0) ||
					(Double::Parse(conditionValueRaw[1]) > 999.0))
				{
					ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AveragingSetting' 2nd parameter available settings: " + "\n" +
													"-> 1 ~ 999";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_AveragingSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
			{
				if ((Double::Parse(conditionValueRaw[1]) < 1.0) ||
					(Double::Parse(conditionValueRaw[1]) > 65535.0))
				{
					ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AveragingSetting' 2nd parameter available settings: " + "\n" +
													"-> 1 ~ 65535";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_AveragingSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'AveragingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "SaveSnpData"

		//Migrated to handled by AppsWideVariable during Load phase

#pragma endregion

#pragma region "ChannelNum"

		//// Obsolete
		//if (conditionName == VnaFetchConditionName_ChannelNum)
		//{
		//	if ((vnaSetting[siteIndex].currentVnaFetchChannel < 1) ||
		//		(vnaSetting[siteIndex].currentVnaFetchChannel > 8))
		//	{
		//		ret = ER_CONST_VNAFETCH_CONDITION_VALUE_INPUT_INVALID;
		//		String ^ additionalMessage = "'ChannelNum' available settings: " + "\n" +
		//			"-> 1 ~ 16";
		//		ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaFetchConditionName_TraceCount, additionalMessage);
		//		tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'ChannelNum' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
		//		tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaFetch' condition value verification] 'ChannelNum' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
		//		return ret;
		//	}
		//}

#pragma endregion

	EndOfTest:
		return ret;
	}
	
	/*
	**	----------------------------------------------------------------------------------------------------
	**	Validate condition value input ---> VnaDataAnalysis
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::ValidateConditionValueInput_VnaDataAnalysis(int tfSite, int siteIndex, String ^ conditionName, array<String^> ^ conditionValueRaw)
	{
		/*****************************************************************************************************
		**	ValidateConditionValueInput_VnaDataAnalysis
		**	tfSite				- This is techFlow site object.
		**	siteIndex			- This is techFlow site index.
		**	conditionName		- This is the condition name.
		**	conditionValueRaw	- This is the condition value input (raw) in the array form.
		**
		**	Descriptions:
		**		This function is to validate all the condition value input in the 'VnaDataAnalysis'.
		**		Include: 'TraceIndex', 'Function', 'AnalysisSetting', 'SmoothingSetting', 
		**		'Freq', 'FreqRangeStart', 'FreqRangeStop', 'OutputType', 'OutputFormat'.
		******************************************************************************************************/

		// Local variable
		int ret = 0;

#pragma region "TraceIndex"

		if (conditionName == VnaDataAnalysisConditionName_TraceIndex)
		{
			if ((vnaDataAnalysisTPC.traceIndex < 1) || 
				(vnaDataAnalysisTPC.traceIndex > 16))
			{
				ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage =	"'TraceIndex' available settings: " + "\n" +
												"-> 1 ~ 16";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_TraceIndex, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'TraceIndex' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'TraceIndex' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}

			if (vnaDataAnalysisTPC.traceIndex > vnaSetting[siteIndex].userTraceCount)
			{
				ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage = "Selected trace index must exists in 'TraceCount' at 'VnaFetch'.";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_TraceIndex, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'TraceIndex' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'TraceIndex' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}
		}

#pragma endregion

#pragma region "Function"

		if (conditionName == VnaDataAnalysisConditionName_Function)
		{
			if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
			{
				if ((vnaDataAnalysisTPC.function != Cond_Function_TraceData)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_msMinMax)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_msPeak)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_msTarget)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmStatistics)	&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmBwSearch)	&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmBwSearchAbs)	&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmFlatness)	&&
					(vnaDataAnalysisTPC.function != Cond_Function_msMinMaxRipple) &&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataBWSearch)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataBWSearchAbs)	&&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataMinMax)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataTarget)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryMinMaxRipple)		&&
					(vnaDataAnalysisTPC.function != Cond_Function_P1dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'Function' available settings: "	+ "\n" +
													"-> TraceData"						+ "\n" +
													"-> msMinMax"						+ "\n" +
													"-> msPeak"							+ "\n" +
													"-> msTarget"						+ "\n" +
													"-> mmStatistics"					+ "\n" + 
													"-> mmBwSearch"						+ "\n" +
													"-> mmBwSearchAbs"					+ "\n" +
													"-> mmFlatness"						+ "\n" +
													"-> msMinMaxRipple"					+ "\n" + 
													"-> Mean"							+ "\n" +
													"-> P1dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Function, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Function' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Function' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
				if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearch) 
				{
					vnaDataAnalysisTPC.function = Cond_Function_SharedMemoryDataBWSearch;
				}
				else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearchAbs)
				{
					vnaDataAnalysisTPC.function = Cond_Function_mmBwSearchAbs;
				}
				else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataMinMax)
				{
					vnaDataAnalysisTPC.function = Cond_Function_msMinMax;
				}
				else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataTarget) 
				{
					vnaDataAnalysisTPC.function = Cond_Function_msTarget;
				}
				else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryMinMaxRipple) 
				{
					vnaDataAnalysisTPC.function = Cond_Function_msMinMaxRipple;
				}
			}
			else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
			{
				if ((vnaDataAnalysisTPC.function != Cond_Function_TraceData)					&&
					(vnaDataAnalysisTPC.function != Cond_Function_msMinMax)					&&
					(vnaDataAnalysisTPC.function != Cond_Function_msPeak)					&&
					(vnaDataAnalysisTPC.function != Cond_Function_msTarget)					&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmStatistics)				&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmBwSearch)				&&
					(vnaDataAnalysisTPC.function != Cond_Function_mmBwSearchAbs)				&&
					// mmFlatness not supported
					(vnaDataAnalysisTPC.function != Cond_Function_msMinMaxRipple)			  &&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataBWSearch)	  &&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataBWSearchAbs) &&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataMinMax)	  &&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryDataTarget)	  &&
					(vnaDataAnalysisTPC.function != Cond_Function_SharedMemoryMinMaxRipple)	&&
					(vnaDataAnalysisTPC.function != Cond_Function_P1dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'Function' available settings: "	+ "\n" +
													"-> TraceData"						+ "\n" +
													"-> msMinMax"						+ "\n" +
													"-> msPeak"							+ "\n" +
													"-> msTarget"						+ "\n" +
													"-> mmStatistics"					+ "\n" + 
													"-> mmBwSearch"						+ "\n" +
													"-> mmBwSearAbs"					+ "\n" +
													"-> msMinMaxRipple"					+ "\n" +
													"-> SharedMemoryDataMinMax"			+ "\n" +
													"-> SharedMemoryDataTarget"			+ "\n" +
													"-> SharedMemoryDataBWSearch"		+ "\n" +
													"-> SharedMemoryMinMaxRipple"		+ "\n" +
													"-> P1dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Function, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Function' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Function' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "AnalysisSetting"

		if (conditionName == VnaDataAnalysisConditionName_AnalysisSetting)
		{
			// TraceData
			if (vnaDataAnalysisTPC.function == Cond_Function_TraceData)
			{
				// NA
			}
			// msMinMax
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMax)
			{
				// Search Range On/Off
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOn) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOff))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msMinMax' function, 1st parameter available settings: "	+ "\n" +
													"-> SearchRangeOn"																+ "\n" +
													"-> SearchRangeOff";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Search Type
				if ((conditionValueRaw[1] != Cond_AnalysisSetting_MS_Type_Maximum) && 
					(conditionValueRaw[1] != Cond_AnalysisSetting_MS_Type_Minimum))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msMinMax' function, 2nd parameter available settings: "	+ "\n" +
													"-> Max"																		+ "\n" +
													"-> Min";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// msPeak
			else if (vnaDataAnalysisTPC.function == Cond_Function_msPeak)
			{
				// Search Type
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_MSPeak_Type_SearchPeak)		&&
					//(conditionValueRaw[0] != Cond_AnalysisSetting_MSPeak_Type_SearchMaxPeak)	&&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MSPeak_Type_SearchPeakLeft)	&&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MSPeak_Type_SearchPeakRight))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msPeak' function, 1st parameter available settings: "	+ "\n" +
													"-> SearchPeak"																	+ "\n" +
													"-> SearchPeakLeft"																+ "\n" +
													"-> SearchPeakRight";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Peak Excursion
				if ((Double::Parse(conditionValueRaw[1]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[1]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msPeak' function, 2nd parameter available settings: " + "\n" +
													"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Peak Polarity
				if ((conditionValueRaw[2] != Cond_AnalysisSetting_MSPeak_PeakPolarity_Positive)	&&
					(conditionValueRaw[2] != Cond_AnalysisSetting_MSPeak_PeakPolarity_Negative)	&&
					(conditionValueRaw[2] != Cond_AnalysisSetting_MSPeak_PeakPolarity_Both))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	 "'AnalysisSetting' for 'msPeak' function, 3rd parameter available settings: "	+ "\n" +
													"-> Positive"																	+ "\n" +
													"-> Negative"																	+ "\n" +
													"-> Both";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				/*// Peak Threshold - Not Applicable to use
				if ((Double::Parse(conditionValueRaw[3]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[3]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'msPeak' function, 4th parameter available settings: " + "\n" +
						"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}*/

			}
			// msTarget
			else if (vnaDataAnalysisTPC.function == Cond_Function_msTarget)
			{
				// Search Type
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_MSTarget_Type_SearchTarget)		&&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MSTarget_Type_SearchTargetLeft)	&&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MSTarget_Type_SearchTargetRight))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msTarget' function, 1st parameter available settings: " + "\n" +
													"-> SearchTarget"																+ "\n" +
													"-> SearchTargetLeft"															+ "\n" +
													"-> SearchTargetRight";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Target Value
				if ((Double::Parse(conditionValueRaw[1]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[1]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msTarget' function, 2nd parameter available settings: " + "\n" +
													"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Target Transition
				if ((conditionValueRaw[2] != Cond_AnalysisSetting_MSTarget_TargetTransition_Positive) &&
					(conditionValueRaw[2] != Cond_AnalysisSetting_MSTarget_TargetTransition_Negative) &&
					(conditionValueRaw[2] != Cond_AnalysisSetting_MSTarget_TargetTransition_Both))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'msTarget' function, 3rd parameter available settings: " + "\n" +
													"-> Positive"																	+ "\n" +
													"-> Negative"																	+ "\n" +
													"-> Both";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				//// Target Line
				//if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				//{ 
				//	if ((conditionValueRaw[3] != Cond_AnalysisSetting_MSTarget_Enable_TargetLineOn) &&
				//		(conditionValueRaw[3] != Cond_AnalysisSetting_MSTarget_Enable_TargetLineOff))
				//	{
				//			ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
				//			String ^ additionalMessage =	"'AnalysisSetting' for 'msTarget' function, 4th parameter available settings: " + "\n" +
				//											"-> TargetLineOn"																+ "\n" +
				//											"-> TargetLineOff";
				//			ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
				//			tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				//			tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				//			return ret;
				//		}
				//	}
				//}
			}
			// mmStatistics
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmStatistics)
			{
				// Statistics Range On/Off
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_MMStatistics_Enable_StatisticsRangeOn) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MMStatistics_Enable_StatisticsRangeOff))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'mmStatistics' function, 1st parameter available settings: "	+ "\n" +
													"-> StatisticsRangeOn"																+ "\n" +
													"-> StatisticsRangeOff";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// mmBwSearch
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmBwSearch)
			{
				// Search Type
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_MMBwSearch_Type_Bandpass) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MMBwSearch_Type_Notch))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'mmBwSearch' function, 1st parameter available settings: "	+ "\n" +
													"-> Bandpass"																		+ "\n" +
													"-> Notch";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Search Ref
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{ 
					if ((conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Marker)	&&
						(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Maximum) &&
						(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Minimum))
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'AnalysisSetting' for 'mmBwSearch' function, 2nd parameter available settings: "	+ "\n" +
														"-> Marker"																			+ "\n" +
														"-> Max"																			+ "\n" +
														"-> Min";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Marker)	&&
						(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Peak))
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage =	"'AnalysisSetting' for 'mmBwSearch' function, 2nd parameter available settings: "	+ "\n" +
														"-> Marker"																			+ "\n" +
														"-> Peak";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}

				// Bandwidth Value / Notch Value
				if ((Double::Parse(conditionValueRaw[2]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[2]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'AnalysisSetting' for 'mmBwSearch' function, 3rd parameter available settings: " + "\n" +
													"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// mmBwSearchAbs
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmBwSearchAbs)
			{
				// Search Type
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_MMBwSearch_Type_Bandpass) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_MMBwSearch_Type_Notch))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'mmBwSearchAbs' function, 1st parameter available settings: " + "\n" +
						"-> Bandpass" + "\n" +
						"-> Notch";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Search Ref
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					if ((conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Marker) &&
						(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Maximum) &&
						(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Minimum))
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'AnalysisSetting' for 'mmBwSearchAbs' function, 2nd parameter available settings: " + "\n" +
							"-> Marker" + "\n" +
							"-> Max" + "\n" +
							"-> Min";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Marker) &&
						(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Peak))
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'AnalysisSetting' for 'mmBwSearchAbs' function, 2nd parameter available settings: " + "\n" +
							"-> Marker" + "\n" +
							"-> Peak";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}

				// Bandwidth Value / Notch Value
				if ((Double::Parse(conditionValueRaw[2]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[2]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'mmBwSearchAbs' function, 3rd parameter available settings: " + "\n" +
						"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// mmFlatness
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmFlatness)
			{
				// NA
			}
			// msMinMaxRipple
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMaxRipple || vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryMinMaxRipple)
			{
				// NA
			}
			// P1dB
			else if (vnaDataAnalysisTPC.function == Cond_Function_P1dB)
			{
				// NA
			}
			// SharedMemoryDataMinMax
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataMinMax)
			{
				// Search Range On/Off
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOn) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOff))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataMinMax' function, 1st parameter available settings: " + "\n" +
						"-> SearchRangeOn" + "\n" +
						"-> SearchRangeOff";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Search Type
				if ((conditionValueRaw[1] != Cond_AnalysisSetting_MS_Type_Maximum) &&
					(conditionValueRaw[1] != Cond_AnalysisSetting_MS_Type_Minimum))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataMinMax' function, 2nd parameter available settings: " + "\n" +
						"-> Max" + "\n" +
						"-> Min";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// SharedMemoryDataTarget
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataTarget)
			{
				// Search Range On/Off
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOn) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOff))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataTarget' function, 1st parameter available settings: " + "\n" +
						"-> SearchRangeOn" + "\n" +
						"-> SearchRangeOff";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Target Value
				if ((Double::Parse(conditionValueRaw[1]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[1]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataTarget' function, 2nd parameter available settings: " + "\n" +
						"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Target Transition
				if ((conditionValueRaw[2] != Cond_AnalysisSetting_MSTarget_TargetTransition_Positive) &&
					(conditionValueRaw[2] != Cond_AnalysisSetting_MSTarget_TargetTransition_Negative) &&
					(conditionValueRaw[2] != Cond_AnalysisSetting_MSTarget_TargetTransition_Both))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataTarget' function, 3rd parameter available settings: " + "\n" +
						"-> Positive" + "\n" +
						"-> Negative" + "\n" +
						"-> Both";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			// SharedMemoryDataBWSearch
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearch ||
					vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearchAbs)
			{
				// Search Range On/Off
				if ((conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOn) &&
					(conditionValueRaw[0] != Cond_AnalysisSetting_GenericMS_Enable_SearchRangeOff))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataTarget' function, 1st parameter available settings: " + "\n" +
						"-> SearchRangeOn" + "\n" +
						"-> SearchRangeOff";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Search Type
				if ((conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_Type_Bandpass) &&
					(conditionValueRaw[1] != Cond_AnalysisSetting_MMBwSearch_Type_Notch))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataBWSearch' function, 2nd parameter available settings: " + "\n" +
						"-> Bandpass" + "\n" +
						"-> Notch";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

				// Search Ref
				if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
				{
					if ((conditionValueRaw[2] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Marker) &&
						(conditionValueRaw[2] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Maximum) &&
						(conditionValueRaw[2] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Minimum))
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataBWSearch' function, 3rd parameter available settings: " + "\n" +
							"-> Marker" + "\n" +
							"-> Max" + "\n" +
							"-> Min";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
				else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
				{
					if ((conditionValueRaw[2] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Marker) &&
						(conditionValueRaw[2] != Cond_AnalysisSetting_MMBwSearch_SearchRef_Peak))
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataBWSearch' function, 3rd parameter available settings: " + "\n" +
							"-> Marker" + "\n" +
							"-> Peak";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}

				// Bandwidth Value / Notch Value
				if ((Double::Parse(conditionValueRaw[3]) < -500.0 dB) ||
					(Double::Parse(conditionValueRaw[3]) > 500.0 dB))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage = "'AnalysisSetting' for 'SharedMemoryDataBWSearch' function, 4th parameter available settings: " + "\n" +
						"-> -500.0 dB ~ +500.0 dB";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_AnalysisSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'AnalysisSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}

			}
		}

#pragma endregion

#pragma region "SmoothingSetting"

		if (conditionName == VnaDataAnalysisConditionName_SmoothingSetting)
		{
			if ((conditionValueRaw[0] != Cond_SmoothingSetting_Enable_SmoOn) &&
				(conditionValueRaw[0] != Cond_SmoothingSetting_Enable_SmoOff))
			{
				ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
				String ^ additionalMessage =	"'SmoothingSetting' 1st parameter available settings: " + "\n" +
												"-> SmoOn"												+ "\n" +
												"-> SmoOff";
				ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_SmoothingSetting, additionalMessage);
				tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
				return ret;
			}

			if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
			{
				if ((Double::Parse(conditionValueRaw[1]) < 0.01) ||
					(Double::Parse(conditionValueRaw[1]) > 20.0))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'SmoothingSetting' 2nd parameter available settings: " + "\n" +
													"-> 0.01 ~ 20.0";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_SmoothingSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
			{
				if ((Double::Parse(conditionValueRaw[1]) < 0.0) ||
					(Double::Parse(conditionValueRaw[1]) > 25.0))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'SmoothingSetting' 2nd parameter available settings: " + "\n" +
													"-> 0.0 ~ 25.0";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_SmoothingSetting, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'SmoothingSetting' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "Freq, FreqRangeStart, FreqRangeStop"

		// [Future Enchancement] Need to check each of the test function in different mode, need to check with config, start stop freq

		if ((conditionName == VnaDataAnalysisConditionName_Freq) || (conditionName == VnaDataAnalysisConditionName_FreqRangeStart) || (conditionName == VnaDataAnalysisConditionName_FreqRangeStop))
		{
			if (vnaDataAnalysisTPC.function == Cond_Function_TraceData || vnaDataAnalysisTPC.function == Cond_Function_P1dBTarget)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.

				for (int i = 0; i < vnaDataAnalysisTPC.overallTestFreqCount; i++)
				{
					if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
					{
						if ((vnaDataAnalysisTPC.testFreq[i] < 300.0 kHz) ||
							(vnaDataAnalysisTPC.testFreq[i] > 9000.0 MHz))
						{
							ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'Freq' for '" + vnaDataAnalysisTPC.function + "' function, the available settings: " + "\n" +
								"-> 300.0 kHz ~ 9000.0 MHz";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Freq, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Freq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Freq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
					{
						if ((vnaDataAnalysisTPC.testFreq[i] < 9.0 kHz) ||
							(vnaDataAnalysisTPC.testFreq[i] > 20000.0 MHz))
						{
							ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'Freq' for '" + vnaDataAnalysisTPC.function + "' function, the available settings: " + "\n" +
								"-> 9.0 kHz ~ 20000.0 MHz";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Freq, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Freq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Freq' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}

					if (vnaDataAnalysisTPC.testFreqRangeStart[i] != 0.0 MHz)
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'FreqRangeStart' is unavailable for '" + vnaDataAnalysisTPC.function + "' function, please remain the condition value as 0.0 MHz.";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_FreqRangeStart, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'FreqRangeStart' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'FreqRangeStart' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}

					if (vnaDataAnalysisTPC.testFreqRangeStop[i] != 0.0 MHz)
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'FreqRangeStop' is unavailable for '" + vnaDataAnalysisTPC.function + "' function, please remain the condition value as 0.0 MHz.";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_FreqRangeStop, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'FreqRangeStop' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'FreqRangeStop' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMax)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_msPeak)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_msTarget)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmStatistics)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmBwSearch)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmFlatness)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMaxRipple || vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryMinMaxRipple)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_P1dB)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataMinMax)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataTarget)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearch)
			{
				// [Future Enchancement] To check whether the user input freq is exist in the segment settings.
			}
		}

#pragma endregion

#pragma region "Power, PowerRangeStart, PowerRangeStop"

		// [Future Enchancement] Need to check each of the test function in different mode, need to check with config, start stop power

		if ((conditionName == VnaDataAnalysisConditionName_Power) || (conditionName == VnaDataAnalysisConditionName_PowerRangeStart) || (conditionName == VnaDataAnalysisConditionName_PowerRangeStop))
		{
			if (vnaDataAnalysisTPC.function == Cond_Function_P1dBTarget)
			{
				for (int i = 0; i < vnaDataAnalysisTPC.overallTestPowerCount; i++)
				{
					if (sysConfigInfo.moduleConfigurationName == VnaModel_CMT_SC5090)
					{
						if ((vnaDataAnalysisTPC.testPower[i] < -50 dBm) ||
							(vnaDataAnalysisTPC.testPower[i] > 15 dBm))
						{
							ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'Power' for 'P1dBTarget' function, the available settings: " + "\n" +
								"-> -50 dBm ~ 15 dBm";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Power, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}
					else if (sysConfigInfo.moduleConfigurationName == VnaModel_Keysight_M9804A)
					{
						if ((vnaDataAnalysisTPC.testPower[i] < -100 dBm) ||
							(vnaDataAnalysisTPC.testPower[i] > 20 dBm))
						{
							ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
							String ^ additionalMessage = "'Power' for 'P1dBTarget' function, the available settings: " + "\n" +
								"-> -100 dBm ~ 20 dBm";
							ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_Power, additionalMessage);
							tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'Power' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
							return ret;
						}
					}

					if (vnaDataAnalysisTPC.testPowerRangeStart[i] != 0.0 MHz)
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'PowerRangeStart' is unavailable for 'TraceData' function, please remain the condition value as 0.0 MHz.";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_PowerRangeStart, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'PowerRangeStart' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'PowerRangeStart' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}

					if (vnaDataAnalysisTPC.testPowerRangeStop[i] != 0.0 MHz)
					{
						ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
						String ^ additionalMessage = "'PowerRangeStop' is unavailable for 'TraceData' function, please remain the condition value as 0.0 MHz.";
						ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_PowerRangeStop, additionalMessage);
						tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'PowerRangeStop' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'PowerRangeStop' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
						return ret;
					}
				}
			}
			
		}

#pragma endregion

#pragma region "OutputType"

		if (conditionName == VnaDataAnalysisConditionName_OutputType)
		{
			if ((vnaDataAnalysisTPC.function == Cond_Function_TraceData)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msMinMax)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msPeak)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msTarget)				||
				(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataMinMax)|| 
				(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataTarget))
			{
				if ((vnaDataAnalysisTPC.outputType != Cond_OutputType_Generic_Freq) &&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_Generic_Data))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputType' for 'TraceData', 'msMinMax', 'msPeak, 'msTarget', 'SharedMemoryDataMinMax, 'SharedMemoryDataTarget' function,"	+ "\n" +
													"the available settings: "																										+ "\n" +
													"-> Freq"																														+ "\n" +
													"-> Data";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputType, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmStatistics)
			{
				if ((vnaDataAnalysisTPC.outputType != Cond_OutputType_mmStatistics_Mean)		&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmStatistics_StdDev)	&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmStatistics_PeakToPeak))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputType' for 'mmStatistics' function, the available settings: "	+ "\n" +
													"-> Mean"																+ "\n" +
													"-> StdDev"																+ "\n" +
													"-> PeakToPeak";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputType, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if ((vnaDataAnalysisTPC.function == Cond_Function_mmBwSearch)			||
					(vnaDataAnalysisTPC.function == Cond_Function_mmBwSearchAbs)			||
					(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearch))
			{
				if ((vnaDataAnalysisTPC.outputType != Cond_OutputType_mmBwSearch_BW)		&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmBwSearch_Cent)	&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmBwSearch_Low)	&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmBwSearch_High)	&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmBwSearch_Q)		&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmBwSearch_Loss))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputType' for 'mmBwSearch', 'mmBwSearchAbs', 'SharedMemoryDataBWSearch' function, the available settings: "	+ "\n" +
													"-> BW"																											+ "\n" +
													"-> Cent"																										+ "\n" +
													"-> Low"																										+ "\n" +
													"-> High"																										+ "\n" +
													"-> Q"																											+ "\n" +
													"-> Loss";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputType, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_mmFlatness)
			{
				if ((vnaDataAnalysisTPC.outputType != Cond_OutputType_mmFlatness_Gain)	&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmFlatness_Slope)	&&
					(vnaDataAnalysisTPC.outputType != Cond_OutputType_mmFlatness_Flat))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputType' for 'mmFlatness' function, the available settings: "	+ "\n" +
													"-> Gain"															+ "\n" +
													"-> Slope"															+ "\n" +
													"-> Flat";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputType, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
			else if (vnaDataAnalysisTPC.function == Cond_Function_msMinMaxRipple || vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryMinMaxRipple)
			{
				if (vnaDataAnalysisTPC.outputType != Cond_OutputType_Generic_Data)
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputType' for 'msMinMaxRipple', 'SharedMemoryMinMaxRipple' function, the available settings: " + "\n" +
													"-> Data";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputType, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputType' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

#pragma region "OutputFormat"

		if (conditionName == VnaDataAnalysisConditionName_OutputFormat)
		{
			if ((vnaDataAnalysisTPC.function == Cond_Function_TraceData)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msMinMax)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msPeak)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msTarget)				||
				(vnaDataAnalysisTPC.function == Cond_Function_msMinMaxRipple)		||
				(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataMinMax)||
				(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataTarget)||
				(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryMinMaxRipple))
			{
				if ((vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_Generic_Real)			&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_Generic_Imag)			&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_SmithRJX_Resistance)	&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_SmithRJX_Reactance)	&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_SmithRJX_CapInduc)		&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_SmithGJB_Conductance)	&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_SmithGJB_Susceptance)	&&
					(vnaDataAnalysisTPC.outputFormat != Cond_OutputFormat_SmithGJB_CapInduc))
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputType' for 'TraceData', 'msMinMax', 'msPeak, 'msTarget', 'SharedMemoryDataMinMax, 'SharedMemoryDataTarget' function," + "\n" +
													"the available settings: "																								+ "\n" +
													"-> Real"																												+ "\n" +
													"-> Imag"																												+ "\n" +
													"-> Resistance"																											+ "\n" +
													"-> Reactance"																											+ "\n" +
													"-> CapInduc"																											+ "\n" +
													"-> Conductance"																										+ "\n" +
													"-> Susceptance";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputFormat, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}

			if ((vnaDataAnalysisTPC.function == Cond_Function_mmStatistics)	||
				(vnaDataAnalysisTPC.function == Cond_Function_mmBwSearch)	||
				(vnaDataAnalysisTPC.function == Cond_Function_mmBwSearchAbs) ||
				(vnaDataAnalysisTPC.function == Cond_Function_mmFlatness)	||
				(vnaDataAnalysisTPC.function == Cond_Function_SharedMemoryDataBWSearch))
			{
				if (vnaDataAnalysisTPC.outputFormat != "")
				{
					ret = ER_CONST_VNADATAANALYSIS_CONDITION_VALUE_INPUT_INVALID;
					String ^ additionalMessage =	"'OutputFormat' is unavailable for 'mmStatistics', 'mmBwSearch', 'mmFlatness', 'SharedMemoryDataBWSearch' function, please remain the condition value empty.";
					ShowMessageBox(tfSite, siteIndex, TITLE_CONST_INVALID_CONDITION_INPUT_VALUE, VnaDataAnalysisConditionName_OutputFormat, additionalMessage);
					tl->WriteToTracerAndFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					tl->WriteToFileLogger(tfSite, siteIndex, WARNING, "['VnaDataAnalysis' condition value verification] 'OutputFormat' condition value invalid." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: ");
					return ret;
				}
			}
		}

#pragma endregion

//#pragma region "Threshold"
//
//		if (conditionName == VnaDataAnalysisConditionName_Threshold)
//		{
//			if (vnaDataAnalysisTPC.function != Cond_Function_msPeak)
//			{
//				//set threshold of other function to 0 except msPeak
//				vnaDataAnalysisTPC.Threshold = 0.0;
//			}
//		}
//
//#pragma endregion

	EndOfTest:
		return ret;
	}

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Check condition change ---> VnaConfig
	**	----------------------------------------------------------------------------------------------------
	*/
	int AMB7300TestLibrary::CheckConditionChange_VnaConfig(Site ^ site, int tfSite, int siteIndex, int segmentSetCount)
	{
		/*****************************************************************************************************
		**	CheckConditionChange_VnaConfig
		**	site			- This is techFlow site object.
		**	tfSite			- This is techFlow site index.
		**	siteIndex		- This is vna's object index, normally start from 0.
		**	segmentSetCount	- This is total segment set count of the VNA segment settings.
		**
		**	Descriptions:
		**		This function is to check condition change from the control step item 'VnaConfig'.
		******************************************************************************************************/

		// Local variable
		int ret = 0;
		
		// Compare each segment settings. Support multiple segment set
		for (int segmentSetIndex = 0; segmentSetIndex < segmentSetting[siteIndex].segmentCount; segmentSetIndex++)
		{
			//-------------------- Start Freq --------------------
			if ((segmentSetting[siteIndex].startFreq[segmentSetIndex]	!= prev_segmentSetting[siteIndex].startFreq[segmentSetIndex])	||
				(segmentSetting[siteIndex].stopFreq[segmentSetIndex]		!= prev_segmentSetting[siteIndex].stopFreq[segmentSetIndex])		||
				(segmentSetting[siteIndex].point[segmentSetIndex]		!= prev_segmentSetting[siteIndex].point[segmentSetIndex])		||
				(segmentSetting[siteIndex].ifbw[segmentSetIndex]			!= prev_segmentSetting[siteIndex].ifbw[segmentSetIndex])			||
				(segmentSetting[siteIndex].power[segmentSetIndex]		!= prev_segmentSetting[siteIndex].power[segmentSetIndex])		||
				(segmentSetting[siteIndex].delay[segmentSetIndex]		!= prev_segmentSetting[siteIndex].delay[segmentSetIndex]))
			{
				if ((segmentSetting[siteIndex].startFreq[segmentSetIndex] == 0.0) &&
					(segmentSetting[siteIndex].stopFreq[segmentSetIndex] == 0.0) &&
					(segmentSetting[siteIndex].point[segmentSetIndex] == 0) &&
					(segmentSetting[siteIndex].ifbw[segmentSetIndex] == 0.0) &&
					(segmentSetting[siteIndex].power[segmentSetIndex] == 0.0) &&
					(segmentSetting[siteIndex].delay[segmentSetIndex] == 0.0))
				{
					segmentSetting[siteIndex].SettingHasChanged = false;
				}
				else
				{
					segmentSetting[siteIndex].SettingHasChanged = true;
					prev_segmentSetting[siteIndex].startFreq[segmentSetIndex] = segmentSetting[siteIndex].startFreq[segmentSetIndex];
					prev_segmentSetting[siteIndex].stopFreq[segmentSetIndex] = segmentSetting[siteIndex].stopFreq[segmentSetIndex];
					prev_segmentSetting[siteIndex].point[segmentSetIndex] = segmentSetting[siteIndex].point[segmentSetIndex];
					prev_segmentSetting[siteIndex].ifbw[segmentSetIndex] = segmentSetting[siteIndex].ifbw[segmentSetIndex];
					prev_segmentSetting[siteIndex].power[segmentSetIndex] = segmentSetting[siteIndex].power[segmentSetIndex];
					prev_segmentSetting[siteIndex].delay[segmentSetIndex] = segmentSetting[siteIndex].delay[segmentSetIndex];
				}
			}
			else
			{
				segmentSetting[siteIndex].SettingHasChanged = false;
			}
		}

		EndOfTest:
				 return ret;
	}
	
}


/*----------------------------------------------------------------------
* Revision Log
* &Log: AMB7300Utility.cpp.rca&

*** Version : v1.0.0.10
*** Date	: 4 April 2025
*** PIC		: Tham Zhi Kean
* Added xml code for gCreateFixedOffsetFile
* Solved bug on CheckConditionChange_VnaConfig logic
* Add PreProcessing xml condition CorrFactorDirectory
* Add AWV for HighPwrTest_EN & HighPwrTest_AppsCalFile
* Add AWV for PortMatchingX
* Add VNA_Lock & VNA_Unlock xml code
* Solve bug on SharedMemoryTransfer: segmentSetting[siteIndex].segmentCount = segmentSetCount
* Support Trace Measure Type of A & B
* Move ChannelNum from VnaFetch to VnaConfig

*** Version : v1.0.0.9
*** Date	: 18 February 2025
*** PIC		: Tham Zhi Kean
* Added VnaConfig CheckConditionChange
* Updated xml configurations & condition inputs for AppsWideVariable, VnaConfig, VnaFetch & VnaDataAnalysis

*** Version : v1.0.0.8
*** Date	: 13 January 2025
*** PIC		: Tham Zhi Kean
* Updated XML file for VnaConfig and AppsWideVariable
* Added ChannelNum to VnaFetch XML file rules
* Migrate SaveToTouchstoneFile from VnaFetch_CastCondition & ValidateConditionInput to Globals.cpp

*** Version : v1.0.0.7
*** Date	: xx April 2024
*** PIC		: Jack Ho
* Target Search for BW Search
* Combine 3 S2P into S3p by input the "S3P" into the SNP condition.
* Snp file able to store into different folder/pathway based on the waferID/LotID
* Cal Expiration Check

*** Version	:  v1.0.0.6
*** Date	:  xx December 2023
*** PIC		: Jack Ho
* Fixed bug on Initialization for true paralel techflow site configurations for multi-system. (Config file at Config1 or ConfigX folder will have additional information on Config to identify between different config)
* AMB7300

*** Version	:  v1.0.0.5
*** Date	:  7 November 2023
*** PIC		: Jack Ho
* Added support for new BW Test method (mmBwSearchAbs) where it will capture the max value and calculate the new absolute BW reference value

*** Version	:  v1.0.0.4
*** Date	:  25 August 2023
*** PIC		: Jack Ho
* Added support for new Math Function. (Add, Subtract, AbsAdd, AbsSubtract)
* Added support for auto points obtain from the state file (thru S2VNA) where the users no longer required to key in the number of points in test conditions.

*** Version	:  v1.0.0.3
*** Date	:  13 August 2023
*** PIC		: Jack Ho
* Support control step and test parameters bypass
* Added support for multiUUT for Shared VNA, new project type: SingleTFSiteMultiUUTOffsetSharedVNA
* Updated XML file for SharedVNA AppWideVariable
* Changed SNP file name up to ms to avoid overwritten when the name is up to seconds.
* Support FT and CP, S2P generation. (Able to identify if sublot is enabled)
* Temporary supports only AMB7300 but not AMB7300SR!!

*** Version	: v1.0.0.2
*** Date	: 9 April 2023
*** PIC		: Ng Chen Yang
* Support the input validation of S2Ppath and SaveSnpData which moved to AppWideVariable
* Updated XML file for VNA FETCH and AppWideVariable

*** Version	: v1.0.0.1
*** Date	: 31 March 2023
*** PIC		: Ng Chen Yang
* SaveSnpFilePath to store the snai file to a specific file path 
* Detect the keyword "SkySemi" to enable special bw seacrh (reference to peak)

*** Version	: v1.0.0.0
*** Date	: 31 December 2022
*** PIC		: Ooi Jing Yao
* Initial release version. 
* Support AM, DM series configuration.
* Support CMT VNA SC5090, Keysight VNA M9804A configuration.
* Support user input validation.
* Support tF3.12.1 project library XML file.
----------------------------------------------------------------------*/