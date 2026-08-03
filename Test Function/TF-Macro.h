/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			TF-Macro.h
Purpose:		Defines techFlow macros.
UUTOffset:		Supported.
Version:		v1.0.0.3
----------------------------------------------------------------------*/

#pragma region "App-Wide-Variables"

//Return boolean, true if global variable found (1.0.0.3 format)
#define tf_AppWideVariable_Exist(VariableName) site->FlowEngine->AppWideVariables->ContainsKey(VariableName)

//Return boolean, true if global variable found (1.0.0.2 format fallback)
#define tf_AppWideVariable_exist(VariableName) site->FlowEngine->AppWideVariables->ContainsKey(VariableName)

//Return object containing app wide's variable value (Value casting is required)
#define tf_AppWideVariable_Cast(VariableName) site->FlowEngine->AppWideVariables[VariableName]->Value

#pragma endregion

//--------------------------------------------------

#pragma region "techFlow Variable"

//Return String containing Site Name
#define tf_SiteName() site->Name

//Return string containing flow name
#define tf_FlowName() site->Flow->Name
#define tf_Flow_Name() site->Flow->Name

//Return boolean, true if flow variable found
#define tf_FlowVariable_exist(VariableName) site->Variables->ContainsKey(VariableName)

//Return object containing flow's variable value (Value casting is required)
#define tf_FlowVariable_Cast(VariableName) site->Variables[VariableName][site]->Value

#pragma endregion

//--------------------------------------------------

#pragma region "Flow Item (general)"

//Return boolean, true if flow condition found
#define tf_FlowCondition_exist(ConditionName) site->Conditions->ContainsKey(ConditionName)
#define tf_Flow_ConditionExist(ConditionName) site->Conditions->ContainsKey(ConditionName)

//Return object containing flow's condition value (Value casting is required)
#define tf_FlowCondition_Cast(ConditionName) site->Conditions[ConditionName][site]->Value
#define tf_Flow_ConditionCast(ConditionName) site->Conditions[ConditionName][site]->Value

//Return total sub-items such as test step, control step and test parameter count in current test item
#define tf_Flow_SubItemCount() ((TestItem^)site->CurrentFlowItem)->SubItems->Count

#pragma endregion

//--------------------------------------------------

#pragma region "Control Item"

//Return current Controlitem name
#define tf_ControlItem_Name() ((ControlItem^)site->CurrentFlowItem)->Name

//Return control item display name
#define tf_ControlItem_DisplayName() ((ControlItem^)site->CurrentFlowItem)->DisplayName

//Return current Controlitem
#define tf_ControlItem() ((ControlItem ^)site->CurrentFlowItem)

//Return boolean, true if condition is exist
#define tf_ControlItemCondition_exist(ConditionName) ((ControlItem ^)site->CurrentFlowItem)->Conditions->ContainsKey(ConditionName)
#define tf_ControlItem_ConditionExist(ConditionName) ((ControlItem ^)site->CurrentFlowItem)->Conditions->ContainsKey(ConditionName)

//Return object containing current controlitem's condition value (Value casting is required)
#define tf_ControlItemCondition_Cast(ConditionName) ((ControlItem ^)site->CurrentFlowItem)->Conditions[ConditionName][site]->Value
#define tf_ControlItem_ConditionCast(ConditionName) ((ControlItem ^)site->CurrentFlowItem)->Conditions[ConditionName][site]->Value

//Return ControlConditionCollection
#define tf_ControlItemCondition_List() ((ControlItem^)site->CurrentFlowItem)->Conditions
#define tf_ControlItem_ConditionList() ((ControlItem^)site->CurrentFlowItem)->Conditions

//Return (current control item) bypass status
#define tf_CIBypass() ((ControlItem^)site->CurrentFlowItem)->Bypass
#define tf_ControlItem_BypassStatus() ((ControlItem^)site->CurrentFlowItem)->Bypass

#pragma endregion

//--------------------------------------------------

#pragma region "Test Item"

//Return current testitem Name
#define tf_TestItem_Name() ((TestItem^)site->CurrentFlowItem)->Name

//Return current testitem display Name
#define tf_TestItem_DisplayName() ((TestItem^)site->CurrentFlowItem)->DisplayName

//Return current testitem
#define tf_TestItem() ((TestItem^)site->CurrentFlowItem)

//Return ConditionCollection
#define tf_TIConditions_List() ((TestItem^)site->CurrentFlowItem)->Conditions
#define tf_TestItem_ConditionList() ((TestItem^)site->CurrentFlowItem)->Conditions

//Return boolean, true if condition is exist
#define tf_TestItemCondition_exist(ConditionName) ((TestItem^)site->CurrentFlowItem)->Conditions->ContainsKey(ConditionName)
#define tf_TestItem_ConditionExist(ConditionName) ((TestItem^)site->CurrentFlowItem)->Conditions->ContainsKey(ConditionName)

//Return object containing testitem's condition value (Value casting is required)
#define tf_TestItemCondition_Cast(ConditionName) ((TestItem^)site->CurrentFlowItem)->Conditions[ConditionName][site]->Value
#define tf_TestItem_ConditionCast(ConditionName) ((TestItem^)site->CurrentFlowItem)->Conditions[ConditionName][site]->Value

//Return (current testitem) bypass status
#define tf_TIBypass() ((TestItem^)site->CurrentFlowItem)->Bypass
#define tf_TestItem_BypassStatus() ((TestItem^)site->CurrentFlowItem)->Bypass

#pragma endregion

//--------------------------------------------------

#pragma region "Test Parameter"

//Return number of test parameter in current testItem
#define tf_TestParameter_Count() ((TestItem ^)site->CurrentFlowItem)->TestParameters->Count
#define tf_TPCount() ((TestItem^)site->CurrentFlowItem)->TestParameters->Count

//Return test parameter name by test parameter index
#define tf_TestParameter_Name(TPIndex) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPIndex]->Name

//Return test parameter display name by test parameter index
#define tf_TestParameter_DisplayName(TPIndex) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPIndex]->DisplayName

//Return test parameter name by test parameter index
#define tf_TestParameter_FullName(TPIndex) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPIndex]->FullName

//Return (current testitem) specified test parameter
#define tf_TestParameter(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]

//Return Max Limit of test parameter in current test Item
#define tf_TestParameter_MaxLimit(TPName) ((TestItem ^)site->CurrentFlowItem)->TestParameters[TPName]->Limit[site]->LimitMax
#define tf_TPHighLimit_Cast(TestParameterName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TestParameterName]->Limit[site]->LimitMax

//Return Min Limit of test parameter in current test Item
#define tf_TestParameter_MinLimit(TPName) ((TestItem ^)site->CurrentFlowItem)->TestParameters[TPName]->Limit[site]->LimitMin
#define tf_TPLowLimit_Cast(TestParameterName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TestParameterName]->Limit[site]->LimitMin

//Return ConditionCollection
#define tf_TPConditions_List(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions
#define tf_TestParameter_ConditionList(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions

//Return Condition Count
#define tf_TPConditions_Count(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions->Count

//Return boolean, true if condition is exist
#define tf_TPCondition_Exist(TPName, ConditionName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions->ContainsKey(ConditionName)
#define tf_TestParameter_ConditionExist(TPName, ConditionName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions->ContainsKey(ConditionName)

//Return (current testitem) test parameter's condition value (Value casting is required)
#define tf_TPCondition_Cast(TPName, ConditionName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions[ConditionName][site]->Value
#define tf_TestParameter_ConditionCast(TPName, ConditionName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Conditions[ConditionName][site]->Value

//Return (current testitem) test parameter's DataType
#define tf_TP_DataType(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->DataType
#define tf_TPDataType(TestParameterName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TestParameterName]->DataType
#define tf_TestParameter_DataType(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->DataType

//Return (current testitem) test parameter's evalmode
#define tf_TPEvalMode(TestParameterName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TestParameterName]->EvalMode
#define tf_TestParameter_EvalMode(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->EvalMode

//Return (current testitem) test parameter's prefix
#define tf_TPPrefix(TestParameterName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TestParameterName]->Prefix
#define tf_TestParameter_Prefix(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Prefix

//Return test parameter's unit by test parameter name
#define tf_TestParameter_Unit(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Unit

//Return (current testitem) test parameter's bypass status
#define tf_TPBypass(TestParameterName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TestParameterName]->Bypass
#define tf_TestParameter_BypassStatus(TPName) ((TestItem^)site->CurrentFlowItem)->TestParameters[TPName]->Bypass

#pragma endregion

//--------------------------------------------------

#pragma region "Flow Step (Control Step & Test Step)"

//Return total flow step count (Control Step & Test Step) in current test item
#define tf_FlowStep_Count() ((TestItem^)site->CurrentFlowItem)->FlowSteps->Count;

//Return ConditionCollection by flow step name
#define tf_FlowStep_ConditionList(FlowStepName) ((TestItem^)site->CurrentFlowItem)->FlowSteps[FlowStepName]->Conditions

//Return boolean, true if condition is exist
#define tf_FlowStep_ConditionExist(FlowStepName, ConditionName) ((TestItem^)site->CurrentFlowItem)->FlowSteps[FlowStepName]->Conditions->ContainsKey(ConditionName)

//Return flow step's condition value
#define tf_FlowStep_ConditionCast(FlowStepName, ConditionName) ((TestItem^)site->CurrentFlowItem)->FlowSteps[FlowStepName]->Conditions[ConditionName][site]->Value

//Return flow step's condition count
#define tf_FlowStep_ConditionCount(FlowStepName) ((TestItem^)site->CurrentFlowItem)->FlowSteps[FlowStepName]->Conditions->Count

#pragma endregion

//--------------------------------------------------

#pragma region "Set Result"

//Set test parameter's run result
#define tf_SetResult(TPName, Result) site->SetResult(((TestItem^)site->CurrentFlowItem)->TestParameters[TPName], Result )

//Set test parameter's run result
#define tf_SetResult_UUTOffset(TPName, Result, uutOffset) site->SetResult(((TestItem^)site->CurrentFlowItem)->TestParameters[TPName], Result, site->UUTOffsetResolver->UUTOffsets[uutOffset])

//Set test parameter's run result
#define tf_SetResult_UUTOffset_PassFail(TPName, Result, uutOffset, passFail) site->SetResult(((TestItem^)site->CurrentFlowItem)->TestParameters[TPName], Result, site->UUTOffsetResolver->UUTOffsets[uutOffset], passFail)

//Set test parameter's run result with defined prefix
#define tf_SetResultPrefix(TPName, Result, AemulusUnitPrefix) site->SetResult(((TestItem^)site->CurrentFlowItem)->TestParameters[TPName], Result, AemulusUnitPrefix)

//Set test parameter's run result
#define tf_SetResultnTestTime(TPName, Result, TestTime) site->SetResult(((TestItem^)site->CurrentFlowItem)->TestParameters[TPName], Result, TestTime)

//Set test parameter's run result with uut offsets
#define tf_SetResultnTestTime_byUUTOffsetName(TPName, Result, TestTime, UUTOffsetName) site->SetResult(((TestItem^)site->CurrentFlowItem)->TestParameters[TPName], Result, TestTime, site->UUTOffsetResolver->UUTOffsets[UUTOffsetName])

//Set test parameter's run result
#define tf_SetResult_UUTOffset_TI(TIName, TPName, Result, uutOffset) site->SetResult(((TestItem^)site->FlowItems[TIName])->TestParameters[TPName], Result, site->UUTOffsetResolver->UUTOffsets[uutOffset])

#pragma endregion

//--------------------------------------------------

/*----------------------------------------------------------------------
* Revision Log
* &Log: TF-Macro.cpp.rca&

*** Version	: v1.0.0.3
*** Date	: 29 July 2026
*** PIC		: Tham Zhi Kean
* Sync existing AMB7600 Test Library REV1 with AMB7300 Test Library REV2P0

* V1.0.0.2 (26 Jan 2021), LKL
+ tf_TIBypass(), tf_CIBypass() macros.

*** Version	:
*** Date	:
*** PIC		:
*

*** Version	: v1.0.0.1
*** Date	: 31 March 2023
*** PIC		: Ng Chen Yang
* UP REV

*** Version	: v1.0.0.0
*** Date	: 31 December 2022
*** PIC		: Ooi Jing Yao
* Initial release version.
* Support App-Wide-Variables.
* Support Flow Item (general).
* Support Control Item, Test Item, Test Parameter.
* Support Flow Step (Control Step, Test Step).
* Support tF3 result posting.
----------------------------------------------------------------------*/