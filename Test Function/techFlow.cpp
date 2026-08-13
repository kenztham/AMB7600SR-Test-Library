/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			TechFlow.cpp
Purpose:		Contains techFlow3 opearion & diagnostic functions.
UUTOffset:		Supported.
Version:		v1.2.0.0
----------------------------------------------------------------------*/

#include "TestFunction.h"
#include "TF-Macro.h"

namespace Functions
{
	bool TestFunction::IsAlphaNum(String^ value)
	{
		/*****************************************************************************************************
		** IsAlphaNum
		**		value - This is the string type value.
		** Descriptions:
		**		This test method is to check whether the input value is an alphanumeric.
		**			True	- If the input string value is match
		**			False	- else
		******************************************************************************************************/

		if (System::Text::RegularExpressions::Regex::IsMatch(value, "^[a-zA-Z0-9]+$"))
			return true;
		else
			return false;
	}
	bool TestFunction::IsNum(String^ value)
	{
		/*****************************************************************************************************
		** IsNum
		**		value - This is the string type value.
		** Descriptions:
		**		This test method is to check whether the input value is a numerical value.
		**			True	- If the input string value is match
		**			False	- else
		******************************************************************************************************/

		if (System::Text::RegularExpressions::Regex::IsMatch(value, "^[0-9]+$"))
			return true;
		else
			return false;
	}
	bool TestFunction::IsTPResultFailed(Site^ site, String ^ tpName, Object ^ result)
	{
		/*****************************************************************************************************
		** IsTPResultFailed
		**		site	- This is techFlow site object.
		**		tpName	- Test parameter name.
		**		result	- The result fo the specified test parameter.
		** Descriptions:
		**		This is used to determine the test status (Pass or Fail) of the specified test parameter.
		**		The function return TRUE when test result is failing and FALSE when test results is passing.
		******************************************************************************************************/

		bool ret = 0;
		double dlowLimit = 0.0;
		double dhighLimit = 0.0;
		int ilowLimit = 0;
		int ihighLimit = 0;

		EvalMode mode = ((TestItem^)site->FlowItems[site->CurrentFlowItem->Name])->TestParameters[tpName]->EvalMode;
		DataType dataType = ((TestItem^)site->FlowItems[site->CurrentFlowItem->Name])->TestParameters[tpName]->DataType;

		if (mode == EvalMode::Between_IncludeMinAndMax)
		{
			switch (dataType)
			{
			case DataType::Double:
				dlowLimit = (double)(tf_TestParameter_MinLimit(tpName));
				dhighLimit = (double)(tf_TestParameter_MaxLimit(tpName));
				if (Convert::ToDouble(result) >= dlowLimit && Convert::ToDouble(result) <= dhighLimit)
					ret = false;
				else
					ret = true;
				break;

			case DataType::Int32:
				ilowLimit = (int)(tf_TestParameter_MinLimit(tpName));
				ihighLimit = (int)(tf_TestParameter_MaxLimit(tpName));
				if (Convert::ToDouble(result) >= ilowLimit && Convert::ToDouble(result) <= ihighLimit)
					ret = false;
				else
					ret = true;
				break;

			default:
				break;
			}
		}
		else if (mode == EvalMode::Between_ExcludeMinAndMax)
		{
			switch (dataType)
			{
			case DataType::Double:
				dlowLimit = (double)(tf_TestParameter_MinLimit(tpName));
				dhighLimit = (double)(tf_TestParameter_MaxLimit(tpName));
				dhighLimit = (double)(tf_TestParameter_MaxLimit(tpName));
				if (Convert::ToDouble(result) >= dlowLimit && Convert::ToDouble(result) <= dhighLimit)
					ret = false;
				else
					ret = true;
				break;

			case DataType::Int32:
				ilowLimit = (int)(tf_TestParameter_MinLimit(tpName));
				ihighLimit = (int)(tf_TestParameter_MaxLimit(tpName));
				if (Convert::ToDouble(result) >= ilowLimit && Convert::ToDouble(result) <= ihighLimit)
					ret = false;
				else
					ret = true;
				break;

			default:
				break;
			}
		}
		else if (mode == EvalMode::Equal)
		{
			switch (dataType)
			{
			case DataType::Double:
				dhighLimit = (double)(tf_TestParameter_MaxLimit(tpName));
				if (Convert::ToDouble(result) == dhighLimit)
					ret = false;
				else
					ret = true;
				break;

			case DataType::Int32:
				ihighLimit = (int)(tf_TestParameter_MaxLimit(tpName));
				if (Convert::ToDouble(result) == ihighLimit)
					ret = false;
				else
					ret = true;
				break;

			default:
				break;
			}
		}

		return ret;
	}
	void TestFunction::SequenceBranchControl(Site ^ site, int siteIndex, String ^ tpName, Object ^ result)
	{
		bool IsEnableCriticalBin = false;
		AFlowItem^ item = site->CurrentFlowItem;
		Type^ FlowType = item->GetType();
		AUUTOffset^ UUTOffset = site->UUTOffsetResolver->UUTOffsets[siteIndex];

		if (FlowType == TestItem::typeid)
		{
			if ((bool)tf_TestParameter_ConditionExist(tpName, CONST_SEQUENCER_CRITICAL_BIN) == true)
			{
				IsEnableCriticalBin = (bool)tf_TestParameter_ConditionCast(tpName, CONST_SEQUENCER_CRITICAL_BIN);
			}
			if ((bool)tf_TestItem_ConditionExist(CONST_SEQUENCER_CRITICAL_BIN) == true)
			{
				IsEnableCriticalBin = (bool)tf_TestItem_ConditionCast(CONST_SEQUENCER_CRITICAL_BIN);
			}
			if (UUTOffset->Active)
			{
				if ((bool)tf_TestItem_ConditionExist("OnPassExecute") == true)
				{
					if (!IsTPResultFailed(site, tpName, result))
					{
						glob->OnPassExcuteFlowItem[siteIndex] = (String ^)tf_TestItem_ConditionCast("OnPassExecute");
					}
				}
				if ((bool)tf_TestItem_ConditionExist("OnFailExecute") == true)
				{
					if (IsTPResultFailed(site, tpName, result))
					{
						glob->OnFailExcuteFlowItem[siteIndex] = (String ^)tf_TestItem_ConditionCast("OnFailExecute");
					}
				}
			}
		}

		// Sequence Branching Control
		if (IsEnableCriticalBin)
		{
			if (IsTPResultFailed(site, tpName, result))
			{
				glob->isCriticalBinFail[siteIndex] = true;
			}
		}
	}
	int TestFunction::GetPinNameFromTestParameterDisplayName(String^ TestParameterDisplayName, String^ % pinName)
	{
		/*****************************************************************************************************
		** GetPinNameFromTestParameterDisplayName
		**		TestParameterDisplayName	- This is the display name of current test item specified test
		**									  parameter.
		**		pinName						- This is the return pin name from the test parameter display name.
		** Descriptions:
		**		This test method is to get the pin name from the test parameter display name.
		******************************************************************************************************/

		int ret = 0;
		pinName = String::Empty;

		array<String^>^ ArrStr = gcnew array<String^>(0);
		array<String^>^ Separator = gcnew array<String^>(1);
		Separator[0] = "!";

		ArrStr = TestParameterDisplayName->Split(Separator, StringSplitOptions::RemoveEmptyEntries);

		if (ArrStr->Length > 1)
		{
			if (ArrStr[1]->Length > 1) //More than one character
			{
				pinName = ArrStr[1];
			}
			else
			{
				ret = ER_CONST_INVALID_SETTING;
			}
		}
		else
		{
			ret = ER_CONST_INVALID_SETTING;
		}

		return ret;
	}
	int TestFunction::GetPinNameFromAmapAlias(String^ pinAlias, String^ % pinName)
	{
		/*****************************************************************************************************
		** GetPinNameFromAmapAlias
		**		pinAlias		- This is the pin alias (amap pin alias).
		**		pinName			- This is the return pin alias name from the amap alias.
		** Descriptions:
		**		This test method is to get the pin alias name from the amap alias.
		******************************************************************************************************/

		int ret = 0;
		pinName = String::Empty;

		array<String^>^ ArrStr = gcnew array<String^>(0);
		array<String^>^ Separator = gcnew array<String^>(1);
		Separator[0] = "_";

		ArrStr = pinAlias->Split(Separator, StringSplitOptions::RemoveEmptyEntries);

		if (ArrStr->Length > 1)
		{
			if (ArrStr[0]->Length > 1) //More than one character
			{
				pinName = ArrStr[0];
			}
			else
			{
				ret = ER_CONST_INVALID_SETTING;
			}
		}
		else
		{
			ret = ER_CONST_INVALID_SETTING;
		}

		return ret;
	}
	int TestFunction::ModifyTestParameterDisplayName(Site^ site, String^ TestItemName, String^ TestParameterDisplayName, String^ NewTestParameterDisplayname)
	{
		/*****************************************************************************************************
		** ModifyTestParameterDisplayName
		**		site						- This is techFlow site object.
		**		TestItemName				- This is the name of current test item.
		**		TestParameterDisplayName	- This is the display name of current test item specified test
		**									  parameter.
		**		NewTestParameterDisplayname	- This is the new display name of current test item specified test
		**									  parameter.
		** Descriptions:
		**		This test method is to modify the specify test parameter display name.
		******************************************************************************************************/

		int ret = 0;
		int siteIndex = 0;

		String^ TestParameterName = TestParameterDisplayName;

		for (int i = 0; i<TestParameterName->Length; i++)
		{
			if (IsAlphaNum(TestParameterName[i].ToString()) == false)
			{
				TestParameterName = TestParameterName->Remove(i, 1);
				TestParameterName = TestParameterName->Insert(i, "_");
			}
		}

		//Modify Test Parameter Display Name
		try
		{
			((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->DisplayName = NewTestParameterDisplayname;
		}
		catch (Exception^ ex)
		{
			delete ex;
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			CheckError(siteIndex, ER_CONST_GENERAL);
		}

		return 0;
	}
	int TestFunction::ModifyTestParameterLimits(Site^ site, String^ TestItemName, String^ TestParameterDisplayName, String^ LowLimit, String^ HighLimit)
	{
		/*****************************************************************************************************
		** ModifyTestParameterLimits
		**		site						- This is techFlow site object.
		**		TestItemName				- This is the name of current test item.
		**		TestParameterDisplayName	- This is the display name of current test item specified test
		**									  parameter.
		**		LowLimit					- This is the lower test limit of current test item specified test
		**									  parameter.
		**		HighLimit					- This is the upper test limit of current test item specified test
		**								      parameter.
		** Descriptions:
		**		This test method is to modify the specify test parameter limits.
		******************************************************************************************************/

		int ret = 0;

		String^ TestParameterName = TestParameterDisplayName;

		for (int i = 0; i<TestParameterName->Length; i++)
		{
			if (IsAlphaNum(TestParameterName[i].ToString()) == false)
			{
				TestParameterName = TestParameterName->Remove(i, 1);
				TestParameterName = TestParameterName->Insert(i, "_");
			}
		}

		ret = SetTestLimit(site, TestItemName, TestParameterName, LowLimit, HighLimit);

		return ret;
	}
	int TestFunction::SetTestLimit(Site^ site, String^ TestItemName, String^ TestParameterName, String^ LowLimit, String^ HighLimit)
	{
		/*****************************************************************************************************
		** SetTestLimit
		**		site				- This is techFlow site object.
		**		TestItemName		- This is the current test item name.
		**		TestParameterName	- This is the current test item specified test parameter name.
		**		LowLimit			- This is the lower test limit of current test item specified test parameter.
		**		HighLimit			- This is the upper test limit of current test item specified test parameter.
		** Descriptions:
		**		This test method is to set the test limit for each test parameter.
		******************************************************************************************************/

		int ret = 0;

		Int16 i16_maxLimit = 0;
		Int16 i16_minLimit = 0;

		Int32 i32_maxLimit = 0;
		Int32 i32_minLimit = 0;

		Int64 i64_maxLimit = 0;
		Int64 i64_minLimit = 0;

		UInt16 ui16_maxLimit = 0;
		UInt16 ui16_minLimit = 0;

		UInt32 ui32_maxLimit = 0;
		UInt32 ui32_minLimit = 0;

		UInt64 ui64_maxLimit = 0;
		UInt64 ui64_minLimit = 0;

		double d_maxLimit = 0;
		double d_minLimit = 0;

		float f_maxLimit = 0;
		float f_minLimit = 0;

		bool b_maxLimit = false;
		bool b_minLimit = false;

		String ^ s_maxLimit = String::Empty;
		String ^ s_minLimit = String::Empty;

		EvalMode mode = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->EvalMode;
		DataType dataType = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->DataType;
		UnitPrefix unitPrefix = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->Prefix;

		double NewHiLimit = 0;
		double NewLoLimit = 0;

		if (mode == EvalMode::Between_ExcludeMinAndMax || mode == EvalMode::Between_ExcludeMinIncludeMax ||
			mode == EvalMode::Between_IncludeMinAndMax || mode == EvalMode::Between_IncludeMinExcludeMax ||
			mode == EvalMode::NotBetween_ExcludeMinAndMax || mode == EvalMode::NotBetween_ExcludeMinIncludeMax ||
			mode == EvalMode::NotBetween_IncludeMinAndMax || mode == EvalMode::NotBetween_IncludeMinExcludeMax)
		{
			switch (dataType)
			{
			case DataType::Double:
				Util->StringToDouble(LowLimit, d_minLimit);
				Util->StringToDouble(HighLimit, d_maxLimit);

				UpdateDoubleTestLimitsWithPrefix(d_maxLimit, d_minLimit, unitPrefix, NewHiLimit, NewLoLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetValue(DataType::Double, unitPrefix, NewLoLimit, unitPrefix, NewHiLimit);
				break;

			case DataType::Float:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int32:
				Util->StringToInteger(LowLimit, i32_minLimit);
				Util->StringToInteger(HighLimit, i32_maxLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetValue(DataType::Int32, unitPrefix, i32_minLimit, unitPrefix, i32_maxLimit);
				break;

			case DataType::Int64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt32:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Boolean:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::String:
				ret = ER_CONST_INVALID_SETTING;
				break;

			default:
				break;
			}
		}
		else if (mode == EvalMode::Equal || mode == EvalMode::LessThan ||
			mode == EvalMode::LessThanAndEqual || mode == EvalMode::NotEqual)
		{
			switch (dataType)
			{
			case DataType::Double:
				Util->StringToDouble(HighLimit, d_maxLimit);

				NewHiLimit = 0;
				NewLoLimit = 0;

				UpdateDoubleTestLimitsWithPrefix(d_maxLimit, 0, unitPrefix, NewHiLimit, NewLoLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetHighLimitValue(DataType::Double, unitPrefix, NewHiLimit);
				break;

			case DataType::Float:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int32:
				Util->StringToInteger(HighLimit, i32_maxLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetHighLimitValue(DataType::Int32, unitPrefix, i32_maxLimit);
				break;

			case DataType::Int64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt32:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Boolean:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::String:
				ret = ER_CONST_INVALID_SETTING;
				break;

			default:
				break;
			}
		}
		else if (mode == EvalMode::GreaterThan ||
			mode == EvalMode::GreaterThanAndEqual)
		{
			switch (dataType)
			{
			case DataType::Double:
				Util->StringToDouble(LowLimit, d_minLimit);

				NewHiLimit = 0;
				NewLoLimit = 0;

				UpdateDoubleTestLimitsWithPrefix(0, d_minLimit, unitPrefix, NewHiLimit, NewLoLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetLowLimitValue(DataType::Double, unitPrefix, NewLoLimit);
				break;

			case DataType::Float:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int32:
				Util->StringToInteger(LowLimit, i32_minLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetLowLimitValue(DataType::Int32, unitPrefix, i32_minLimit);
				break;

			case DataType::Int64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt32:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Boolean:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::String:
				ret = ER_CONST_INVALID_SETTING;
				break;

			default:
				break;
			}
		}

		return ret;
	}
	int TestFunction::BypassTests(Site^ site)
	{
		/*****************************************************************************************************
		** BypassTests
		**		site - This is techFlow site object.
		** Descriptions:
		**		This test method is to ByPass the corresponding tests.
		******************************************************************************************************/

		int ret = 0;

		String ^ TIName = String::Empty;
		String ^ TPName = String::Empty;
		String ^ TPDisplayName = String::Empty;

		int found = 0;

		//tp_Bypass contains the modified tp display name as the dictionary key. Need to search for the corresponding tp name.

		for each (KeyValuePair<String ^, int>^ pair in glob->tp_Bypass)
		{
			found = 0;

			if (pair->Value == 1)
			{
				TPDisplayName = pair->Key;

				for each(AFlowItem^ item in site->FlowItems)
				{
					Type^ type = item->GetType();

					if (type == TestItem::typeid)	//test items
					{
						TestItem^ testItem = (TestItem^)item;

						for each(Aemulus::Tech::Flow::TestParameter^ tp in testItem->TestParameters)	//test parameters
						{
							TIName = testItem->Name;

							if (tp->DisplayName->CompareTo(TPDisplayName) == 0)
							{
								TPName = tp->Name;
								found = 1;
								break;
							}
						}
					}

					if (found == 1)
						break;
				}

				((TestItem^)site->FlowItems[TIName])->TestParameters[TPName]->Bypass = true;
			}
		}

		return ret;
	}
	int TestFunction::BypassTestItems(Site^ site)
	{
		/*****************************************************************************************************
		** BypassTestItems
		**		site - This is techFlow site object.
		** Descriptions:
		**		This test method is to ByPass the corresponding test items by loop through test items in recipe.
		******************************************************************************************************/

		int ret = 0;

		String ^ TIName = String::Empty;
		String ^ TPName = String::Empty;

		int TPTotal = 0;
		int TPBypassCount = 0;

		// loop through test items in recipe
		for each(AFlowItem^ item in site->FlowItems)
		{
			Type^ type = item->GetType();

			if (type == TestItem::typeid)	// check only test items
			{
				TestItem^ testItem = (TestItem^)item;

				// get total TPCount
				TPTotal = testItem->TestParameters->Count;
				TPBypassCount = 0;

				for each(Aemulus::Tech::Flow::TestParameter^ tp in testItem->TestParameters)	//test parameters
				{
					TIName = testItem->Name;
					TPName = tp->Name;

					if (((TestItem^)site->FlowItems[TIName])->TestParameters[TPName]->Bypass == true)
						TPBypassCount++;

				}

				if (TPBypassCount == TPTotal)
					((TestItem^)site->FlowItems[TIName])->Bypass = true;
			}
		}

		return ret;
	}
	int TestFunction::UpdateTestNumber(Site^ site)
	{
		/*****************************************************************************************************
		** UpdateTestNumber
		**		site - This is techFlow site object.
		** Descriptions:
		**		This test method is to update the test number as tp_Bypass contains the modified test parameter
		**		display name as the dictionary key. Need to search for the corresponding test parameter name.
		******************************************************************************************************/

		int ret = 0;

		String ^ TIName = String::Empty;
		String ^ TPName = String::Empty;
		String ^ TPDisplayName = String::Empty;

		int found = 0;

		for each (KeyValuePair<String ^, int>^ pair in glob->tp_Bypass)
		{
			found = 0;

			if (pair->Value == 0)
			{
				TPDisplayName = pair->Key;

				for each(AFlowItem^ item in site->FlowItems)
				{
					Type^ type = item->GetType();

					if (type == TestItem::typeid)	//test items
					{
						TestItem^ testItem = (TestItem^)item;

						for each(Aemulus::Tech::Flow::TestParameter^ tp in testItem->TestParameters)	//test parameters
						{
							TIName = testItem->Name;

							if (tp->DisplayName->CompareTo(TPDisplayName) == 0)
							{
								TPName = tp->Name;
								found = 1;

								tp[site]->TestNumber = glob->tp_TestNumber[TPDisplayName];

								break;
							}
						}
					}

					if (found == 1)
						break;
				}
			}
		}

		return ret;
	}
	int TestFunction::UpdateTestParameterDescription(Site^ site)
	{
		/*****************************************************************************************************
		** UpdateTestParameterDescription
		**		site - This is techFlow site object.
		** Descriptions:
		**		This test method is to update the test parameter description with test item name.
		******************************************************************************************************/

		int ret = 0;

		String ^ TIName = String::Empty;
		String ^ TPName = String::Empty;
		int TP_HeadNumber = 0;

		for each(AFlowItem^ item in site->FlowItems)
		{
			Type^ type = item->GetType();

			if (type == TestItem::typeid)	//test items
			{
				TestItem^ testItem = (TestItem^)item;
				TIName = testItem->Name;

				for each(Aemulus::Tech::Flow::TestParameter^ tp in testItem->TestParameters)	//test parameters
				{
					TPName = tp->Name;

					tp->Description = TIName;
				}
			}
		}

		return ret;
	}
	int TestFunction::UpdateDoubleTestLimitsWithPrefix(double HiLimit, double LoLimit, UnitPrefix Prefix, double % NewHiLimit, double % NewLoLimit)
	{
		/*****************************************************************************************************
		** UpdateDoubleTestLimitsWithPrefix
		**		HiLimit			- This is the upper test limit of current test item specified test parameter.
		**		LoLimit			- This is the lower test limit of current test item specified test parameter.
		**		Prefix			- This is the unit prefix of current test item specified test parameter.
		**		NewHiLimit		- This is the return value of new upper limit.
		**		NewLoLimit		- This is the return value of new lower limit.
		** Descriptions:
		**		This test method is to update the double format of test limit with defined input unit prefix.
		******************************************************************************************************/

		NewHiLimit = HiLimit;
		NewLoLimit = LoLimit;

		if (Prefix == UnitPrefix::Milli)
		{
			NewHiLimit = HiLimit * 1e3;
			NewLoLimit = LoLimit * 1e3;
		}
		else if (Prefix == UnitPrefix::Micro)
		{
			NewHiLimit = HiLimit * 1e6;
			NewLoLimit = LoLimit * 1e6;
		}
		else if (Prefix == UnitPrefix::Nano)
		{
			NewHiLimit = HiLimit * 1e9;
			NewLoLimit = LoLimit * 1e9;
		}
		else if (Prefix == UnitPrefix::Pico)
		{
			NewHiLimit = HiLimit * 1e12;
			NewLoLimit = LoLimit * 1e12;
		}
		else if (Prefix == UnitPrefix::Femto)
		{
			NewHiLimit = HiLimit * 1e15;
			NewLoLimit = LoLimit * 1e15;
		}
		else if (Prefix == UnitPrefix::Deci)
		{
			NewHiLimit = HiLimit * 10;
			NewLoLimit = LoLimit * 10;
		}
		else if (Prefix == UnitPrefix::Atto)
		{
			NewHiLimit = HiLimit * 1e18;
			NewLoLimit = LoLimit * 1e18;
		}
		else if (Prefix == UnitPrefix::Centi)
		{
			NewHiLimit = HiLimit * 1e2;
			NewLoLimit = LoLimit * 1e2;
		}
		else if (Prefix == UnitPrefix::Deca)
		{
			NewHiLimit = HiLimit / 10;
			NewLoLimit = LoLimit / 10;
		}
		else if (Prefix == UnitPrefix::Exa)
		{
			NewHiLimit = HiLimit / 1e18;
			NewLoLimit = LoLimit / 1e18;
		}
		else if (Prefix == UnitPrefix::Giga)
		{
			NewHiLimit = HiLimit / 1e9;
			NewLoLimit = LoLimit / 1e9;
		}
		else if (Prefix == UnitPrefix::Hecto)
		{
			NewHiLimit = HiLimit / 1e2;
			NewLoLimit = LoLimit / 1e2;
		}
		else if (Prefix == UnitPrefix::Kilo)
		{
			NewHiLimit = HiLimit / 1e3;
			NewLoLimit = LoLimit / 1e3;
		}
		else if (Prefix == UnitPrefix::Mega)
		{
			NewHiLimit = HiLimit / 1e6;
			NewLoLimit = LoLimit / 1e6;
		}
		else if (Prefix == UnitPrefix::Peta)
		{
			NewHiLimit = HiLimit / 1e15;
			NewLoLimit = LoLimit / 1e15;
		}
		else if (Prefix == UnitPrefix::Tera)
		{
			NewHiLimit = HiLimit / 1e12;
			NewLoLimit = LoLimit / 1e12;
		}
		else if (Prefix == UnitPrefix::Yocto)
		{
			NewHiLimit = HiLimit * 1e24;
			NewLoLimit = LoLimit * 1e24;
		}
		else if (Prefix == UnitPrefix::Yotta)
		{
			NewHiLimit = HiLimit / 1e24;
			NewLoLimit = LoLimit / 1e24;
		}
		else if (Prefix == UnitPrefix::Zepto)
		{
			NewHiLimit = HiLimit * 1e21;
			NewLoLimit = LoLimit * 1e21;
		}
		else if (Prefix == UnitPrefix::Zetta)
		{
			NewHiLimit = HiLimit / 1e21;
			NewLoLimit = LoLimit / 1e21;
		}
		else //None
		{
			NewHiLimit = HiLimit;
			NewLoLimit = LoLimit;
		}

		return 0;
	}
	int TestFunction::ModifyTestParameterEvalMode(Site^ site, String^ TestItemName, String^ TestParameterDisplayName, EvalMode TestParameterEvalMode)
	{
		/*****************************************************************************************************
		** ModifyTestParameterEvalMode
		** Arguments:
		**		site - This is techFlow site object.
		**		TestItemName - This is the name of the current test item.
		**		TestParameterDisplayName - This is the display name of the current test paramater.
		**		TestParameterEvalMode - This is the evaluation mode to be changed to.
		** Descriptions:
		**		This method is to modify the eval mode of the TestParameterDisplayName, maintaining the
		**		unit prefix and data type of the test parameter.
		******************************************************************************************************/

		int ret = 0;

		String^ TestParameterName = TestParameterDisplayName;

		for (int i = 0; i<TestParameterName->Length; i++)
		{
			if (IsAlphaNum(TestParameterName[i].ToString()) == false)
			{
				TestParameterName = TestParameterName->Remove(i, 1);
				TestParameterName = TestParameterName->Insert(i, "_");
			}
		}

		DataType dataType = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->DataType;
		UnitPrefix unitPrefix = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->Prefix;

		((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->SetValue(dataType, unitPrefix, TestParameterEvalMode);

		return ret;
	}
	int TestFunction::UpdateTestLimit(Site^ site)
	{
		/*****************************************************************************************************
		** UpdateTestLimit
		**		site - This is techFlow site object.
		** Descriptions:
		**		This test method is to update the test limit to the specific test parameter.
		******************************************************************************************************/

		int ret = 0;
		int siteIndex = 0;

		try
		{
			String^ TestParameterName = String::Empty;

			for each (KeyValuePair<String ^, String ^>^ pair in glob->tp_TestItem)
			{
				TestParameterName = pair->Key;

				for (int i = 0; i<TestParameterName->Length; i++)
				{
					if (IsAlphaNum(TestParameterName[i].ToString()) == false)
					{
						TestParameterName = TestParameterName->Remove(i, 1);
						TestParameterName = TestParameterName->Insert(i, "_");
					}
				}

				//For test names that start with numbers
				if (IsNum(TestParameterName[0].ToString()) == true)
				{
					TestParameterName = "TP" + TestParameterName;
				}

				ret = SetTestLimitFromDeviceFile(site, pair->Value, TestParameterName, glob->tp_TestLimitLo[pair->Key], glob->tp_TestLimitHi[pair->Key]);
				if (ret) return ret;
			}
		}
		catch (Exception ^ ex)
		{
			glob->TcrLgr.GlobalErrorMessage = "Update test limits error. " + ex->ToString();
			CheckError(siteIndex, ER_CONST_GENERAL);
		}

		return ret;
	}
	int TestFunction::SetTestLimitFromDeviceFile(Site^ site, String^ TestItemName, String^ TestParameterName, String^ LowLimit, String^ HighLimit)
	{
		/*****************************************************************************************************
		** SetTestLimitFromDeviceFile
		**		site				- This is techFlow site object.
		**		TestItemName		- This is the name of current test item.
		**		TestParameterName	- This is the name of current test item specified test parameter.
		**		LowLimit			- This is the lower test limit of current test item specified test parameter.
		**		HighLimit			- This is the upper test limit of current test item specified test parameter.
		** Descriptions:
		**		This test method is to set the test limit for each test parameter.
		**		This fucntion will be call by UpdateTestLimit(Site^ site).
		******************************************************************************************************/

		int ret = 0;

		Int16 i16_maxLimit = 0;
		Int16 i16_minLimit = 0;

		Int32 i32_maxLimit = 0;
		Int32 i32_minLimit = 0;

		Int64 i64_maxLimit = 0;
		Int64 i64_minLimit = 0;

		UInt16 ui16_maxLimit = 0;
		UInt16 ui16_minLimit = 0;

		UInt32 ui32_maxLimit = 0;
		UInt32 ui32_minLimit = 0;

		UInt64 ui64_maxLimit = 0;
		UInt64 ui64_minLimit = 0;

		double d_maxLimit = 0;
		double d_minLimit = 0;

		float f_maxLimit = 0;
		float f_minLimit = 0;

		bool b_maxLimit = false;
		bool b_minLimit = false;

		String ^ s_maxLimit = String::Empty;
		String ^ s_minLimit = String::Empty;

		EvalMode mode = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->EvalMode;
		DataType dataType = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->DataType;
		UnitPrefix unitPrefix = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->Prefix;

		double NewHiLimit = 0;
		double NewLoLimit = 0;

		if (mode == EvalMode::Between_ExcludeMinAndMax || mode == EvalMode::Between_ExcludeMinIncludeMax ||
			mode == EvalMode::Between_IncludeMinAndMax || mode == EvalMode::Between_IncludeMinExcludeMax ||
			mode == EvalMode::NotBetween_ExcludeMinAndMax || mode == EvalMode::NotBetween_ExcludeMinIncludeMax ||
			mode == EvalMode::NotBetween_IncludeMinAndMax || mode == EvalMode::NotBetween_IncludeMinExcludeMax)
		{
			switch (dataType)
			{
			case DataType::Double:
				Util->StringToDouble(LowLimit, d_minLimit);
				Util->StringToDouble(HighLimit, d_maxLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetValue(DataType::Double, unitPrefix, d_minLimit, unitPrefix, d_maxLimit);
				break;

			case DataType::Float:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int32:
				Util->StringToInteger(LowLimit, i32_minLimit);
				Util->StringToInteger(HighLimit, i32_maxLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetValue(DataType::Int32, unitPrefix, i32_minLimit, unitPrefix, i32_maxLimit);
				break;

			case DataType::Int64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt32:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Boolean:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::String:
				ret = ER_CONST_INVALID_SETTING;
				break;

			default:
				break;
			}
		}
		else if (mode == EvalMode::Equal || mode == EvalMode::LessThan ||
			mode == EvalMode::LessThanAndEqual || mode == EvalMode::NotEqual)
		{
			switch (dataType)
			{
			case DataType::Double:
				Util->StringToDouble(HighLimit, d_maxLimit);

				NewHiLimit = 0;
				NewLoLimit = 0;

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetHighLimitValue(DataType::Double, unitPrefix, d_maxLimit);
				break;

			case DataType::Float:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int32:
				Util->StringToInteger(HighLimit, i32_maxLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetHighLimitValue(DataType::Int32, unitPrefix, i32_maxLimit);
				break;

			case DataType::Int64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt32:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Boolean:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::String:
				ret = ER_CONST_INVALID_SETTING;
				break;

			default:
				break;
			}
		}
		else if (mode == EvalMode::GreaterThan ||
			mode == EvalMode::GreaterThanAndEqual)
		{
			switch (dataType)
			{
			case DataType::Double:
				Util->StringToDouble(LowLimit, d_minLimit);

				NewHiLimit = 0;
				NewLoLimit = 0;

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetLowLimitValue(DataType::Double, unitPrefix, d_minLimit);
				break;

			case DataType::Float:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Int32:
				Util->StringToInteger(LowLimit, i32_minLimit);

				((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->LimitValues[LimitSetPredefinedTypes::SpecLimit][site]->SetLowLimitValue(DataType::Int32, unitPrefix, i32_minLimit);
				break;

			case DataType::Int64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt16:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt32:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::UInt64:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::Boolean:
				ret = ER_CONST_INVALID_SETTING;
				break;

			case DataType::String:
				ret = ER_CONST_INVALID_SETTING;
				break;

			default:
				break;
			}
		}

		return ret;
	}
	void TestFunction::KillProcessByName(const char * exeName)
	{
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
		PROCESSENTRY32 pEntry;
		pEntry.dwSize = sizeof(pEntry);
		BOOL hRes = Process32First(hSnapShot, &pEntry);

		char output[260];

		while (hRes)
		{
			sprintf(output, "%ws", pEntry.szExeFile);

			if (strcmp(output, exeName) == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
				if (hProcess != NULL)
				{
					TerminateProcess(hProcess, 9);
					CloseHandle(hProcess);


					//<Info> Need a better method to wait for complete exit
					Util->WaitSecond(2);
				}
			}
			hRes = Process32Next(hSnapShot, &pEntry);
		}
		CloseHandle(hSnapShot);
	}

	//AMB7600SR Test Library Related
	void TestFunction::UpdateTestResultWlanAsync(Site^site, int siteIndex, String^ testItemName, String^ testParaName, Object^ testResult)
	{
		TypeCode typeCode = Type::GetTypeCode(testResult->GetType());
		Object^ OffsetFactor = 0;

		switch (typeCode)
		{
		 case TypeCode::Double:
			 OffsetFactor = (double)GetCorrFactor(testParaName, siteIndex);
			 testResult = (double)testResult + (double)OffsetFactor;
			 break;

		 case TypeCode::Int32:
			 OffsetFactor = (int)GetCorrFactor(testParaName, siteIndex);
			 testResult = (int)testResult + (int)OffsetFactor;
			 break;
		}

		tf_SetResult_UUTOffset_TI(testItemName, testParaName, testResult, siteIndex);
	}
	void TestFunction::UpdateTestResultsWhenException(Site^ site, int siteIndex)
	{
		/*****************************************************************************************************
		** UpdateTestResultsWhenException
		**		site			- This is techFlow site object.
		**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**						  project or techFlow sites for Index Parallel project.
		** Descriptions:
		**		This test method is to updates the test results with a dummy test result (999.99) to techFlow
		**      when catch an exception catch during updating the test results.
		******************************************************************************************************/

		double Result = CONST_INVALID_RESULT;

		if (site->CurrentFlowItem->GetType() == TestItem::typeid)
		{
			WriteToTcrLgr("SITE " + siteIndex.ToString(),">>Updated test results as an exception catch during updating the test results");
			for (int i = 0; i < glob->TestProperty[siteIndex].TotalTestParameter; i++)
			{
				DataType dataType = ((TestItem^)site->FlowItems[glob->TestProperty[siteIndex].TestItemName])->
					TestParameters[glob->TestProperty[siteIndex].TestParameterName[i]]->DataType;

				if (glob->tf.StageCount > 1) //Index Parallel 
				{
					if (dataType == DataType::Int32)
					{
						//tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], (int)Result);
						tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], (int)Result, siteIndex);
					}
					else if (dataType == DataType::Double)
					{
						//tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], Result);
						tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], Result, siteIndex);
					}
					else if (dataType == DataType::String)
					{
						//tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], "FFFF");
						tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], "FFFF", siteIndex);
					}
				}
				else //Multi UUTOffsets
				{
					if (dataType == DataType::Int32)
					{
						tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], (int)Result, siteIndex);
					}
					else if (dataType == DataType::Double)
					{
						tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], Result, siteIndex);
					}
					else if (dataType == DataType::String)
					{
						tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], "FFFF", siteIndex);
					}
				}
			}
			WriteToTcrLgr("SITE " + siteIndex.ToString(),">>Updated test results as an exception catch during updating the test results");
		}

	}
	bool TestFunction::TestItem_RF_ResourceNeeded(Site ^ site)
	{
		bool RF_ResourceNeeded = false;

		int testParameterCount = tf_TestParameter_Count();
		String ^ testParameterName = nullptr;
		String ^ testMethod = nullptr;

		for (int i = 0; i < testParameterCount; i++)
		{
			ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
			testParameterName = tf_TestParameter_Name(i);
			testConditionCollection = tf_TestParameter_ConditionList(testParameterName);

			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

			for each(Condition ^ method in testConditionCollection)
			{
				if (method->Name->StartsWith("ControlMethod") || method->Name->StartsWith("TestMethod"))
				{
					testMethod = (String^)tf_TestParameter_ConditionCast(testParameterName, method->Name);

					if (testMethod->Contains("RFCase"))
					{
						RF_ResourceNeeded = true;
						break;
					}
				}
			}

			if (RF_ResourceNeeded == true)
			{
				break;
			}
		}

		return RF_ResourceNeeded;

	}
	bool TestFunction::ControlItem_RF_ResourceNeeded(Site ^ site)
	{
		bool RF_ResourceNeeded = false;
		String ^ strControlMethod = nullptr;
		int intControlMethod = 0;

		ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
		testConditionCollection = tf_ControlItem_ConditionList();

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		for each(Condition ^ controlMethod in testConditionCollection)
		{
			if (controlMethod->Name->StartsWith("ControlMethod"))
			{
				strControlMethod = nullptr;
				intControlMethod = 0;

				strControlMethod = (String^)tf_ControlItem_ConditionCast(controlMethod->Name);
				if (strControlMethod->Contains("RFCase"))
				{
					RF_ResourceNeeded = true;
					break;
				}
			}
		}

		return RF_ResourceNeeded;

	}
	bool TestFunction::ControlStep_RF_ResourceNeeded(Site ^ site, int siteIndex)
	{
		bool RF_ResourceNeeded	= false;
		String ^ strControlStep = nullptr;
		int intControlStep		= 0;

		ConditionCollection ^ testConditionCollection = gcnew ConditionCollection();
		testConditionCollection = tf_FlowStep_ConditionList(glob->currentSubItemName[siteIndex]);
	
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Control Method <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		for each(Condition ^ controlMethod in testConditionCollection)
		{
			if (controlMethod->Name->StartsWith("ControlMethod"))
			{
				strControlStep = nullptr;
				intControlStep = 0;

				strControlStep = (String^)tf_FlowStep_ConditionCast(glob->currentSubItemName[siteIndex], controlMethod->Name);
				if (strControlStep->Contains("RFCase"))
				{
					RF_ResourceNeeded = true;
					break;
				}
			}
		}

		return RF_ResourceNeeded;

	}
	
	//Standard funcitons
	int TestFunction::UpdateTestProperty(Site^ site, int siteIndex)
	{
		/*****************************************************************************************************
		** UpdateTestProperty
		**		site			- This is techFlow site object.
		**		siteIndex		- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**						  project or techFlow sites for Index Parallel project.
		** Descriptions:
		**		This test method is to updates the test properties for all test parameters for each test item.
		**		The test properties included:
		**		(1) TestParaNameWithSiteIndex is a string dictionary to add "TestParameterName with siteIndex"
		**			as Key and "TestParameterName" as value.
		**			- TestParNameWithSiteIndexIdentifier format: TestParameterName + siteIndex eg: TI1_TP1_POUT_S0
		**
		**		Purpose: The "TestParameterName" property will be use when call tf_SetResult or
		**				 tf_SetResult_UUTOffset in UpdateTestResults function.
		******************************************************************************************************/

		// Local variable
		int ret = 0;
		int iSubItemIndex = 0;
		int iFlowStepIndex = 0;
		int iTPIndex = 0;
		String ^ TestParNameWithSiteIndexIdentifier = String::Empty;

		AFlowItem ^ item = site->CurrentFlowItem;
		Type ^ FlowType = item->GetType();

		// Test Item
		glob->TestProperty[siteIndex].TestItemName = (String^)tf_TestItem_Name();
		glob->TestProperty[siteIndex].TestItemDisplayName = (String^)tf_TestItem_DisplayName();

		// Sub Item (Test Step, Control Step, Test Parameter) 
		glob->TestProperty[siteIndex].totalSubItem = (int)tf_Flow_SubItemCount();
		glob->TestProperty[siteIndex].SubFlowItemTypeId = gcnew array<Type ^>(glob->TestProperty[siteIndex].totalSubItem);

		// Test Parameter
		glob->TestProperty[siteIndex].TotalTestParameter = (int)tf_TestParameter_Count();
		glob->TestProperty[siteIndex].TestParameterName = gcnew array<String ^>(glob->TestProperty[siteIndex].TotalTestParameter);
		glob->TestProperty[siteIndex].TestParameterDisplayName = gcnew array<String ^>(glob->TestProperty[siteIndex].TotalTestParameter);
		glob->TestProperty[siteIndex].TestParameterTypeId = gcnew array<Type ^>(glob->TestProperty[siteIndex].TotalTestParameter);
		glob->TestProperty[siteIndex].TestParameterExecuted = gcnew Dictionary<String ^, bool>();
		glob->TestProperty[siteIndex].TestParameterTestStatus = gcnew array<int>(glob->TestProperty[siteIndex].TotalTestParameter);
		glob->TestProperty[siteIndex].TestParameterUpdateResStatus = gcnew Dictionary<String ^, bool>();
		glob->TestProperty[siteIndex].IsCurrentTPBypassed = gcnew array<bool>(glob->TestProperty[siteIndex].TotalTestParameter);

		// Flow Step (Control Step, Test Step)
		glob->TestProperty[siteIndex].totalFlowStep = (int)tf_FlowStep_Count();
		glob->TestProperty[siteIndex].FlowStepItemName = gcnew array<String ^>(glob->TestProperty[siteIndex].totalFlowStep);
		glob->TestProperty[siteIndex].FlowStepItemDisplayName = gcnew array<String ^>(glob->TestProperty[siteIndex].totalFlowStep);
		glob->TestProperty[siteIndex].FlowStepItemExecuted = gcnew array<bool>(glob->TestProperty[siteIndex].totalFlowStep);

		WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, INFO, "[Update Test Property] Update test property.");

		try
		{
			if (FlowType == TestItem::typeid)
			{
				TestItem ^ testItem = (TestItem^)site->FlowItems[glob->TestProperty[siteIndex].TestItemName];

				for each(AFlowSubItem ^ subFlowItem in testItem->SubItems)
				{
					// Control Step Item & Test Step Item
					if ((dynamic_cast<ControlStep^>(subFlowItem->Data) != nullptr) || (dynamic_cast<TestStep^>(subFlowItem->Data) != nullptr))
					{
						glob->TestProperty[siteIndex].FlowStepItemName[iFlowStepIndex] = subFlowItem->Name;
						glob->TestProperty[siteIndex].FlowStepItemDisplayName[iFlowStepIndex] = subFlowItem->Name;
						glob->TestProperty[siteIndex].FlowStepItemExecuted[iFlowStepIndex] = false;

						if (dynamic_cast<TestStep^>(subFlowItem->Data) != nullptr)
						{
							TestStep^ testStep = (TestStep^)testItem->FlowSteps[subFlowItem->Name];
							for (int iTsTp = 0; iTsTp < glob->TestProperty[siteIndex].TotalTestParameter; iTsTp++)
							{
								if (glob->TestProperty[siteIndex].TestParameterName[iTsTp] == testStep->TestParameter->Name)
								{
									// Replace test parameter under test step with TestStep::typeid 
									glob->TestProperty[siteIndex].TestParameterTypeId[iTsTp] = subFlowItem->Data->GetType();
								}
							}
						}
						iFlowStepIndex++;
					}
					// Test Parameter Item
					else if (dynamic_cast<TestParameter^>(subFlowItem->Data) != nullptr)
					{
						TestParameter^ tp = (TestParameter^)testItem->TestParameters[subFlowItem->Name];

						glob->TestProperty[siteIndex].TestParameterExecuted->Add(subFlowItem->Name, false);
						glob->TestProperty[siteIndex].TestParameterUpdateResStatus->Add(subFlowItem->Name, false);

						glob->TestProperty[siteIndex].TestParameterName[iTPIndex] = tp->Name;
						glob->TestProperty[siteIndex].TestParameterDisplayName[iTPIndex] = tp->DisplayName;
						glob->TestProperty[siteIndex].TestParameterTypeId[iTPIndex] = subFlowItem->Data->GetType();
						TestParNameWithSiteIndexIdentifier = glob->TestProperty[siteIndex].TestParameterDisplayName[iTPIndex] + "_S" + siteIndex.ToString();

						// Eliminate "An item with the same key has already been added" error 
						if (!glob->TestProperty[siteIndex].TestParaNameWithSiteIndex->ContainsKey(TestParNameWithSiteIndexIdentifier))
						{
							glob->TestProperty[siteIndex].TestParaNameWithSiteIndex->Add(TestParNameWithSiteIndexIdentifier, glob->TestProperty[siteIndex].TestParameterName[iTPIndex]);
						}

						// Eliminate "An item with the same key has already been added" error 
						if (!glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex->ContainsKey(TestParNameWithSiteIndexIdentifier))
						{
							glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex->Add(TestParNameWithSiteIndexIdentifier, glob->TestProperty[siteIndex].TestParameterDisplayName[iTPIndex]);
						}

						glob->TestProperty[siteIndex].IsCurrentTPBypassed[iTPIndex] = tp->Bypass;
						iTPIndex++;
					}

					// ControlStep::typeid or TestStep::typeid or TestParameter::typeid
					glob->TestProperty[siteIndex].SubFlowItemTypeId[iSubItemIndex] = subFlowItem->GetType();
					iSubItemIndex++;
				}
			}

			(glob->AWV.Debug == 1) ? glob->TestProperty[siteIndex].DebugEnable = true : false;
		}
		catch (Exception ^ ex)
		{
			ret = ER_CONST_UPDATE_TEST_PROPERTY_FAIL;
			WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, ERROR, "[UpdateTestProperty] Fail to update test property." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
			throw gcnew Aemulus::Hardware::AlarmException(ex->ToString(), ex->HResult);
			goto EndOfTest;
		}

	EndOfTest:
		return ret;
	}

	int TestFunction::UpdateTestResults(Site^ site, int siteIndex, array<Object ^> ^ TestResult)
	{
		/*****************************************************************************************************
		** UpdateTestResultWithOffsetToTechFlow
		**		site		- This is techFlow site object.
		**		siteIndex	- This is selected physical site. (Note: UUT offset index for the MultiUUTOffsets
		**					  project or techFlow sites for Index Parallel project.
		**		TestResult	- This is a double type array of test result, store test result of each test parameter.
		**
		** Descriptions:
		**		This is a function to update the test results together with the offset value (get from FixedOffset.csv)
		**		to techFlow.
		******************************************************************************************************/

		// Local variable
		int ret = 0;
		int tfSite = glob->tf.TestSite;
		String ^ Identifier = String::Empty;
		String ^ ResultUnit = String::Empty;
		String ^ ResultUnitPrefix = String::Empty;
		bool IsInfinityStatus = false;
		double OffsetFactor = 0.0;
		String^ key;

		WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, INFO, "[Update Result To TF] Updating test result to techFlow.");

		try
		{
			for (int i = 0; i < glob->TestProperty[siteIndex].TotalTestParameter; i++)
			{
				Identifier = glob->TestProperty[siteIndex].TestParameterDisplayName[i] + "_S" + siteIndex.ToString();
				key = glob->TestProperty[siteIndex].TestItemDisplayName + "_" + Identifier;

				if ((glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex->ContainsKey(Identifier) == true) &&
					(glob->TestProperty[siteIndex].IsCurrentTPBypassed[i] == false) &&
					(glob->TestProperty[siteIndex].TestParameterTypeId[i] == TestParameter::typeid))
				{
					ResultUnit = ((TestItem^)site->FlowItems[glob->TestProperty[siteIndex].TestItemName])->TestParameters[glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex[Identifier]]->Unit;
					ResultUnitPrefix = GetStringUnitPrefix(site, glob->TestProperty[siteIndex].TestItemName, glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex[Identifier]);
					DataType ResultDataType = ((TestItem^)site->FlowItems[glob->TestProperty[siteIndex].TestItemName])->TestParameters[glob->TestProperty[siteIndex].TestParaDisplayNameWithSiteIndex[Identifier]]->DataType;
					OffsetFactor = GetFixedOffsetValue(tfSite, siteIndex, key);

					switch (ResultDataType)
					{
					case DataType::Double:

						glob->ResultWithDataType[siteIndex].DoubleTypeResult = Convert::ToDouble(TestResult[i]) + OffsetFactor;
						Util->IsInfinity(glob->ResultWithDataType[siteIndex].DoubleTypeResult, IsInfinityStatus);

						if (IsInfinityStatus == true)
						{
							glob->ResultWithDataType[siteIndex].DoubleTypeResult = ER_CONST_ERROR_CATCH;
						}

						//Store Test Results into global Dictionary
						if (glob->TestProperty[siteIndex].TestResults->ContainsKey(glob->TestProperty[siteIndex].TestParameterDisplayName[i]))
						{
							glob->TestProperty[siteIndex].TestResults[glob->TestProperty[siteIndex].TestParameterDisplayName[i]] = glob->ResultWithDataType[siteIndex].DoubleTypeResult;
						}
						else
						{
							glob->TestProperty[siteIndex].TestResults->Add(glob->TestProperty[siteIndex].TestParameterDisplayName[i], glob->ResultWithDataType[siteIndex].DoubleTypeResult);
						}

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].DoubleTypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].DoubleTypeResult, siteIndex);
						}
						break;

					case DataType::Int32:

						glob->ResultWithDataType[siteIndex].IntTypeResult = Convert::ToInt32(TestResult[i]) + (int)OffsetFactor;

						//Store Test Results into global Dictionary
						if (glob->TestProperty[siteIndex].TestResults->ContainsKey(glob->TestProperty[siteIndex].TestParameterDisplayName[i]))
						{
							glob->TestProperty[siteIndex].TestResults[glob->TestProperty[siteIndex].TestParameterDisplayName[i]] = glob->ResultWithDataType[siteIndex].IntTypeResult;
						}
						else
						{
							glob->TestProperty[siteIndex].TestResults->Add(glob->TestProperty[siteIndex].TestParameterDisplayName[i], glob->ResultWithDataType[siteIndex].IntTypeResult);
						}


						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].IntTypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].IntTypeResult, siteIndex);
						}
						break;

					case DataType::UInt32:

						glob->ResultWithDataType[siteIndex].UIntTypeResult = Convert::ToUInt32(TestResult[i]) + (int)OffsetFactor;

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].UIntTypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].UIntTypeResult, siteIndex);
						}
						break;

					case DataType::Int64:

						glob->ResultWithDataType[siteIndex].Int64TypeResult = Convert::ToInt64(TestResult[i]) + (int)OffsetFactor;

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].Int64TypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].Int64TypeResult, siteIndex);
						}
						break;

					case DataType::UInt64:

						glob->ResultWithDataType[siteIndex].UInt64TypeResult = Convert::ToUInt64(TestResult[i]) + (int)OffsetFactor;

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].UInt64TypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].UInt64TypeResult, siteIndex);
						}
						break;

					case DataType::Int16:

						glob->ResultWithDataType[siteIndex].Int16TypeResult = Convert::ToInt16(TestResult[i]) + (int)OffsetFactor;

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].Int16TypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].Int16TypeResult, siteIndex);
						}
						break;

					case DataType::UInt16:

						glob->ResultWithDataType[siteIndex].UInt16TypeResult = Convert::ToUInt16(TestResult[i]) + (int)OffsetFactor;

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].Int16TypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].Int16TypeResult, siteIndex);
						}
						break;

					case DataType::String:

						glob->ResultWithDataType[siteIndex].StringTyperesult = Convert::ToString(TestResult[i]);

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].StringTyperesult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].StringTyperesult, siteIndex);
						}
						break;

					case DataType::Boolean:

						glob->ResultWithDataType[siteIndex].BoolTypeResult = Convert::ToBoolean(TestResult[i]);

						//Index Parallel 
						if (glob->tf.StageCount > 1)
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].BoolTypeResult);
						}
						//Multi UUTOffsets
						else
						{
							glob->TestProperty[siteIndex].TestParameterTestStatus[i] = tf_SetResult_UUTOffset(glob->TestProperty[siteIndex].TestParameterName[i], glob->ResultWithDataType[siteIndex].BoolTypeResult, siteIndex);
						}
						break;
					}

					glob->TestProperty[siteIndex].TestParameterUpdateResStatus[glob->TestProperty[siteIndex].TestParameterName[i]] = true;

					if (glob->AWV.Debug == 1)
					{
						if (ResultDataType == DataType::Double)
						{
							WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, INFO, "[Update Result To TF] " + "\n" +
								"\t Test Parameter Identifier: " + Identifier + "\n" +
								"\t techFlow Site: Site " + glob->tf.TestSite.ToString() + "\n" +
								"\t UUTOffset: Site " + siteIndex.ToString() + "\n" +
								"\t Raw Test Result: " + (Convert::ToDouble(TestResult[i]) / glob->TcrLgr.PrefixValue).ToString() + ResultUnitPrefix + ResultUnit + "\n" +
								"\t Offset Factor: " + (OffsetFactor / glob->TcrLgr.PrefixValue).ToString() + ResultUnitPrefix + ResultUnit + "\n" +
								"\t Final Test Result: " + (glob->ResultWithDataType[siteIndex].DoubleTypeResult / glob->TcrLgr.PrefixValue).ToString() + ResultUnitPrefix + ResultUnit + "\n");
						}
						else if (ResultDataType == DataType::Int32)
						{
							WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, INFO, "[Update Result To TF] " + "\n" +
								"\t Test Parameter Identifier: " + Identifier + "\n" +
								"\t techFlow Site: Site " + glob->tf.TestSite.ToString() + "\n" +
								"\t UUTOffset: Site " + siteIndex.ToString() + "\n" +
								"\t Raw Test Result: " + (Convert::ToDouble(TestResult[i]) / glob->TcrLgr.PrefixValue).ToString() + ResultUnitPrefix + ResultUnit + "\n" +
								"\t Offset Factor: " + (OffsetFactor / glob->TcrLgr.PrefixValue).ToString() + ResultUnitPrefix + ResultUnit + "\n" +
								"\t Final Test Result: " + (glob->ResultWithDataType[siteIndex].IntTypeResult / glob->TcrLgr.PrefixValue).ToString() + ResultUnitPrefix + ResultUnit + "\n");
						}
						else if (ResultDataType == DataType::String)
						{
							WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, INFO, "[Update Result To TF] " + "\n" +
								"\t Test Parameter Identifier: " + Identifier + "\n" +
								"\t techFlow Site: Site " + glob->tf.TestSite.ToString() + "\n" +
								"\t UUTOffset: Site " + siteIndex.ToString() + "\n" +
								"\t Raw Test Result: " + glob->ResultWithDataType[siteIndex].StringTyperesult + "\n" +
								"\t Offset Factor: " + "NA" + "\n" +
								"\t Final Test Result: " + glob->ResultWithDataType[siteIndex].StringTyperesult + "\n");
						}
					}

				}
			}
		}
		catch (Exception^ ex)
		{
			ret = ER_CONST_UPDATE_RESULT_TO_TF3_FAIL;
			WriteToTracerAndFileLogger(glob->tf.TestSite, siteIndex, ERROR, "[UpdateTestResultWithOffsetToTechFlow] Fail to update test result to techFlow." + " | " + "Error Code: " + ret.ToString() + " | " + "Detail: " + ex->Message);
			goto EndOfTest;
		}

	EndOfTest:
		return ret;
	}

	String^ TestFunction::GetStringUnitPrefix(Site^ site, String ^ TestItemName, String ^ TestParameterName)
	{
		/*****************************************************************************************************
		** GetStringUnitPrefix
		**		site				- This is techFlow site object.
		**		TestItemName		- This is the name of current test item.
		**		TestParameterName	- This is the name of current test item specified test parameter.
		** Descriptions:
		**		This test method is to get the unit prefix for each test parameter which is needed for file and
		**		tracer logging.
		******************************************************************************************************/

		String ^ Prefix = String::Empty;
		UnitPrefix ResultUnitPrefix = ((TestItem^)site->FlowItems[TestItemName])->TestParameters[TestParameterName]->Prefix;

		if (ResultUnitPrefix == UnitPrefix::Milli)
		{
			Prefix = "m";
			glob->TcrLgr.PrefixValue = 1e-3;
		}
		else if (ResultUnitPrefix == UnitPrefix::Micro)
		{
			Prefix = "u";
			glob->TcrLgr.PrefixValue = 1e-6;
		}
		else if (ResultUnitPrefix == UnitPrefix::Nano)
		{
			Prefix = "n";
			glob->TcrLgr.PrefixValue = 1e-9;
		}
		else if (ResultUnitPrefix == UnitPrefix::Pico)
		{
			Prefix = "p";
			glob->TcrLgr.PrefixValue = 1e-12;
		}
		else if (ResultUnitPrefix == UnitPrefix::Femto)
		{
			Prefix = "f";
			glob->TcrLgr.PrefixValue = 1e-15;
		}
		else if (ResultUnitPrefix == UnitPrefix::Deci)
		{
			Prefix = "d";
			glob->TcrLgr.PrefixValue = 1e-1;
		}
		else if (ResultUnitPrefix == UnitPrefix::Atto)
		{
			Prefix = "a";
			glob->TcrLgr.PrefixValue = 1e-18;
		}
		else if (ResultUnitPrefix == UnitPrefix::Centi)
		{
			Prefix = "c";
			glob->TcrLgr.PrefixValue = 1e-2;
		}
		else if (ResultUnitPrefix == UnitPrefix::Deca)
		{
			Prefix = "da";
			glob->TcrLgr.PrefixValue = 1e1;
		}
		else if (ResultUnitPrefix == UnitPrefix::Exa)
		{
			Prefix = "E";
			glob->TcrLgr.PrefixValue = 1e18;
		}
		else if (ResultUnitPrefix == UnitPrefix::Giga)
		{
			Prefix = "G";
			glob->TcrLgr.PrefixValue = 1e9;
		}
		else if (ResultUnitPrefix == UnitPrefix::Hecto)
		{
			Prefix = "h";
			glob->TcrLgr.PrefixValue = 1e2;
		}
		else if (ResultUnitPrefix == UnitPrefix::Kilo)
		{
			Prefix = "k";
			glob->TcrLgr.PrefixValue = 1e3;
		}
		else if (ResultUnitPrefix == UnitPrefix::Mega)
		{
			Prefix = "M";
			glob->TcrLgr.PrefixValue = 1e6;
		}
		else if (ResultUnitPrefix == UnitPrefix::Peta)
		{
			Prefix = "P";
			glob->TcrLgr.PrefixValue = 1e15;
		}
		else if (ResultUnitPrefix == UnitPrefix::Tera)
		{
			Prefix = "T";
			glob->TcrLgr.PrefixValue = 1e12;
		}
		else if (ResultUnitPrefix == UnitPrefix::Yocto)
		{
			Prefix = "y";
			glob->TcrLgr.PrefixValue = 1e-24;
		}
		else if (ResultUnitPrefix == UnitPrefix::Yotta)
		{
			Prefix = "Y";
			glob->TcrLgr.PrefixValue = 1e24;
		}
		else if (ResultUnitPrefix == UnitPrefix::Zepto)
		{
			Prefix = "z";
			glob->TcrLgr.PrefixValue = 1e-21;
		}
		else if (ResultUnitPrefix == UnitPrefix::Zetta)
		{
			Prefix = "Z";
			glob->TcrLgr.PrefixValue = 1e21;
		}
		else //None 
		{
			Prefix = "";
			glob->TcrLgr.PrefixValue = 1.0;
		}

		return Prefix;
	}

}


/*----------------------------------------------------------------------
* Revision Log
* $Log: techFlow.cpp.rca$


* v1.0.0.0 (20 March 2020), LKL
* Initial release version.

* v1.1.0.0 (29 Jan 2021), LKL
* Added OperationBranchingCheck(), SequenceBranchControl() to support
sequencer branching for MUUTO with thread project.

* v1.2.0.0 (13 Aug 2026), ZhiKean
* Merge AMB7600SR Test Library REV1 with AMB7300 Test Library REV2P0
----------------------------------------------------------------------*/

