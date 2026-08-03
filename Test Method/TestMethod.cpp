/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			TestMethod.cpp
Purpose:		To execute test function for all Control Steps, Control Items & Test Items
Version:		v1.0.0.0
----------------------------------------------------------------------*/


#include "..\\TestProgram.h"

namespace AMB7600SR_TestLibrary_REV2
{
	#pragma region "AM400e & DM400e ControlStep.xml"
	// AM400e DM400e
	#pragma region ".xml file -> Control Step -> DCCase_DriveVoltage"
	/// <summary> DCCase_DriveVoltage
	/// <list type="ControlStep" name="CM_DCCase_DriveVoltage" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveVoltage</item>
	/// <item attribute="displayas">DCCase_DriveVoltage</item>
	/// <item attribute="description">Configures the Voltage Level (DVCI) for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC1</item>
	/// <item attribute="description">Specifies the voltage level in volts (V).</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC2</item>
	/// <item attribute="description">Specifies the voltage level in volts (V).</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_DriveVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DCCase_DriveCurrent"
	/// <summary> DCCase_DriveCurrent
	/// <list type="ControlStep" name="CM_DCCase_DriveCurrent" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveCurrent</item>
	/// <item attribute="displayas">DCCase_DriveCurrent</item>
	/// <item attribute="description">Configures the Current Level (DVCI) for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC1</item>
	/// <item attribute="description">Specifies the drive current in amps (A).</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC2</item>
	/// <item attribute="description">Specifies the drive current in amps (A).</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_DriveCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;
	
		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;
	
	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> ClampVoltage"
	/// <summary> DCCase_ClampVoltage
	/// <list type="ControlStep" name="CM_DCCase_ClampVoltage" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ClampVoltage</item>
	/// <item attribute="displayas">DCCase_ClampVoltage</item>
	/// <item attribute="description">Configures the Clamp Voltage Level for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC1</item>
	/// <item attribute="description">Specifies the clamp level in volts (V). The voltage level range will be updated automatically based on the voltage level.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ClampVoltage_VCC2</item>
	/// <item attribute="description">Specifies the clamp level in volts (V). The voltage level range will be updated automatically based on the voltage level.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_ClampVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DCCase_ClampCurrent"
	/// <summary> DCCase_ClampCurrent
	/// <list type="ControlStep" name="CM_DCCase_ClampCurrent" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ClampCurrent</item>
	/// <item attribute="displayas">DCCase_ClampCurrent</item>
	/// <item attribute="description">Configures the Clamp Level for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC1</item>
	/// <item attribute="description">Specifies the clamp level in Amp (A). The current level range will be updated automatically based on the current level.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC2</item>
	/// <item attribute="description">Specifies the clamp level in Amp (A). The current level range will be updated automatically based on the current level.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_ClampCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> SetNPLC"
	/// <summary> DCCase_SetNPLC
	/// <list type="ControlStep" name="CM_DCCase_SetNPLC" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_SetNPLC</item>
	/// <item attribute="displayas">DCCase_SetNPLC</item>
	/// <item attribute="description">Configures the NPLC for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC1</item>
	/// <item attribute="description">Configures the NPLC for the specified PinAlias.</item>
	/// <item attribute="value">0.1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC2</item>
	/// <item attribute="description">Configures the NPLC for the specified PinAlias.</item>
	/// <item attribute="value">0.5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_SetNPLC(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> SetPinOnOff"
	/// <summary> DCCase_SetPinOnOff
	/// <list type="ControlStep" name="CM_DCCase_SetPinOnOff" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_SetPinOnOff</item>
	/// <item attribute="displayas">DCCase_SetPinOnOff</item>
	/// <item attribute="description">Turn On or Off on the specified PinAlias. Value 1 = Turn On PinAlias; Value 0 = Turn Off PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC1</item>
	/// <item attribute="description">Configures the SMU & DM output switch status. Mode0(Turn OFF), Mode1(Turn ON)</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCC2</item>
	/// <item attribute="description">Configures the SMU & DM output switch status. Mode0(Turn OFF), Mode1(Turn ON)</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_SetPinOnOff(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> WaitSecond"
	/// <summary> DCCase_WaitSecond
	/// <list type="ControlStep" name="CM_DCCase_WaitSecond" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_WaitSecond</item>
	/// <item attribute="displayas">DCCase_WaitSecond</item>
	/// <item attribute="description"></item>
	/// <list type="StepCondition">
	/// <item attribute="name">WaitSecond_Delay</item>
	/// <item attribute="description">Specifies the delay in second.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_WaitSecond(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	#pragma region ".xml file -> Control Step -> ConfigureTriggerEdgeLevel"
	/// <summary>DCCase_ConfigureTriggerEdgeLevel
	/// <list type="ControlStep" name="CM_DCCase_ConfigureTriggerEdgeLevel" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">AM430e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specifies the triggering source</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigMode</item>
	/// <item attribute="description">Specifies the triggering mode</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_ConfigureTriggerEdgeLevel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> ConfigureTriggerEdgeLevel"
	/// <summary>DCCase_ConfigureTriggerEdgeLevelExtra
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureTriggerEdgeLevelExtra" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="description">Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">AM430e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specifies the triggering mode</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigMode</item>
	/// <item attribute="description">Specifies the triggering mode</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IgnoreTrigCount</item>
	/// <item attribute="description">Specifies the number of triggers to be ignored, before performing measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_ConfigureTriggerEdgeLevelExtra(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> ConfigureInputTriggerSelect"
	/// <summary>DCCase_AMConfigureInputTriggerSelect
	/// <list type="ControlStep" name="CM_DCCase_ConfigureInputTriggerSelect" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureInputTriggerSelect</item>
	/// <item attribute="displayas">DCCase_ConfigureInputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger input to be used for operations such as AcquireMultiple() and AcquireArray(). Upon power-up nothing is selected for the triggerInput. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specifies the triggering source</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureDelayAfterTrig</item>
	/// <item attribute="description">Specifies the delay inserted after being triggered before next operation such as AcquireMultiple(), is executed. Minimum delay is 0. Maximum delay is 50ms.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_ConfigureInputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	// AM400e DM400e CM400e
	#pragma region ".xml file -> Control Step -> MapTriggerIntToTriggerOut"
	/// <summary>DCCase_ConfigureTriggerEdgeLevel
	/// <list type="ControlStep" name="CM_DCCase_MapTriggerIntToTriggerOut" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_MapTriggerIntToTriggerOut</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Connect 2 trigger lines together. Support AM430e, AM450e, AM451e, AM471e, DM483e, CM400e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">AM430e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputTerminal</item>
	/// <item attribute="description">Tri-state the trigger source.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">OutputTerminal</item>
	/// <item attribute="description">Tri-state the trigger source.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_MapTriggerIntToTriggerOut(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DriveSoftwareTrigger"
	/// <summary>DCCase_DriveSoftwareTrigger
	/// <list type="ControlStep" name="CM_DCCase_DriveSoftwareTrigger" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveSoftwareTrigger</item>
	/// <item attribute="displayas">DCCase_DriveSoftwareTrigger</item>
	/// <item attribute="description">Drives software trigger immediately. Support AM430e, AM450e, AM451e, AM471e, DM483e, CM401e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">AM430e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SoftwareTrigger_Select</item>
	/// <item attribute="description">Specifies to which software trigger to drive. Software trigger lines are digital signals coming from the on-board FPGA processor. There are four software triggers to choose from.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SoftwareTrigger_PulseWidth</item>
	/// <item attribute="description">Specifies the pulse width of the trigger signal, in second, ranged from 1us to 10 ms.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_DriveSoftwareTrigger(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	#pragma endregion
	
	#pragma region "AM400e ControlStep.xml"
	
	#pragma region ".xml file -> Control Step -> AMConfigureSMUOutputTriggerPulseWidth"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerPulseWidth
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureSMUOutputTriggerPulseWidth" category="AMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="description">Configures the pulse width of trigger output signal.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PulseWidth</item>
	/// <item attribute="description">Specifies the width of the trigger output pulse, in seconds.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_AMConfigureSMUOutputTriggerPulseWidth(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> AMConfigureSMUOutputTriggerDuringSource"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerDuringSource
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureSMUOutputTriggerDuringSource" category="AMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerDuringSource</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerDuringSource</item>
	/// <item attribute="description">Configures when trigger signal is generated.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ThresholdLevel</item>
	/// <item attribute="description">Specifies the threshold level of the channel where a trigger output is generated when this threshold level is hit, depending on edgeSetting.</item>
	/// <item attribute="value">0.7</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ThresholdLevel_Range</item>
	/// <item attribute="description">Specifies the range of the threshold level.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Threshold_Mode</item>
	/// <item attribute="description">Specifies whether the threshold is voltage or current value.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">EdgeSetting</item>
	/// <item attribute="description">Specifies the condition on how to trigger output will be generated by the specified channel.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_AMConfigureSMUOutputTriggerDuringSource(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> AMConfigureSMUOutputTriggerMode"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerMode
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureSMUOutputTriggerMode" category="AMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerMode</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerMode</item>
	/// <item attribute="description">Configures when a trigger output signal is generated.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerMode</item>
	/// <item attribute="description">Specifies the trigger mode.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_AMConfigureSMUOutputTriggerMode(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> AMConfigureOutputTriggerSelect"
	/// <summary>DCCase_AMConfigureOutputTriggerSelect
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureOutputTriggerSelect" category="AMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureOutputTriggerSelect</item>
	/// <item attribute="displayas">DCCase_AMConfigureOutputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger output to be used Upon power-up nothing is selected for the triggerInput. Support AM430e, AM450e, AM451e, AM471e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerOutput</item>
	/// <item attribute="description">Specifies the trigger output signal.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerDelay</item>
	/// <item attribute="description">Specifies the delay inserted before generating the trigger output.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DCCase_AMConfigureOutputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	#pragma endregion
	
	#pragma region "CM400e ControlStep.xml"

#pragma region ".xml file -> Control Step -> CMDrivePin"
	/// <summary>CMCase_CMDrivePin
	/// <list type="ControlStep" name="CM_CMCase_CMDrivePin" category="CMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMDrivePin</item>
	/// <item attribute="displayas">CMCase_CMDrivePin</item>
	/// <item attribute="description">Configure the PinAlias to 1 (High) or 0 (Low) according to the ControlMethod (CMCase_CMSetModuleVIO)</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_CMCase_CMDrivePin(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> CMDrivePort"
	/// <summary>CMCase_CMDrivePort
	/// <list type="ControlStep" name="CM_CMCase_CMDrivePort" category="CMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMDrivePort</item>
	/// <item attribute="displayas">CMCase_CMDrivePort</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_CMCase_CMDrivePort(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> CMConfigurePXES2780_TriggerBus"
	/// <summary>CMCase_CMConfigurePXES2780_TriggerBus
	/// <list type="ControlStep" name="CM_CMCase_CMConfigurePXES2780_TriggerBus" category="CMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMConfigurePXES2780_TriggerBus</item>
	/// <item attribute="displayas">CMCase_CMConfigurePXES2780_TriggerBus</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_CMCase_CMConfigurePXES2780_TriggerBus(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> CMSetPortDirection"
	/// <summary>CMCase_CMSetPortDirection
	/// <list type="ControlStep" name="CM_CMCase_CMSetPortDirection" category="CMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMSetPortDirection</item>
	/// <item attribute="displayas">CMCase_CMSetPortDirection</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_CMCase_CMSetPortDirection(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	
	#pragma endregion

	#pragma region "DM400e ControlStep.xml"

	#pragma region ".xml file -> Control Step -> DMConfigurePinToVector"
	/// <summary>DMCase_DMConfigurePinToVector
	/// <list type="ControlStep" name="CM_DMCase_DMConfigurePinToVector" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to Vector. Configure the PinAlias’s level setting. Configure the PinAlias’s attribute of pin electronics. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToVector_PinAlias_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToVector_DPinLevelSet_0</item>
	/// <item attribute="description">Retrieve VIH_0, VIL_0, VOH_0, VOL_0, IOH_0, IOL_0, VCH_0, VCL_0, VTERM_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToVector_PEAttSet_0</item>
	/// <item attribute="description">Retrieve InputTermEnable_0, HVEnable_0, ActiveLoadEnable_0, DifferentialComparatorEnable_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToVector_PinAlias_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SDATA</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToVector_DPinLevelSet_1</item>
	/// <item attribute="description">Retrieve VIH_1, VIL_1, VOH_1, VOL_1, IOH_1, IOL_1, VCH_1, VCL_1, VTERM_1 values from Load phase.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToVector_PEAttSet_1</item>
	/// <item attribute="description">Retrieve InputTermEnable_1, HVEnable_1, ActiveLoadEnable_1, DifferentialComparatorEnable_1 values from Load phase.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMConfigurePinToVector(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMConfigurePinToPMU"
	/// <summary>DMCase_DMConfigurePinToPMU
	/// <list type="ControlStep" name="CM_DMCase_DMConfigurePinToPMU" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToPMU</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToPMU</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to PMU. Configure the PinAlias’s configuration to DVCI or DICV. Configure the PinAlias’sense to Local or Remote. Configure the PinAlias to Clamp Current or Clamp Voltage. Configure the PinAlias to Drive Voltage or Drive Current. Configure the PinAlias’s NPLC. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_PinAlias_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_MeasureMode_0</item>
	/// <item attribute="description">0: DVCI, 1:DICV</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_SenseMode_0</item>
	/// <item attribute="description">0: Local, 1: Remote</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_Compliance_0</item>
	/// <item attribute="description">Clamp Voltage value (if set to DICV), Clamp Current value (if set to DVCI)</item>
	/// <item attribute="value">200</item>
	/// <item attribute="prefix">Micro</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_DriveValue_0</item>
	/// <item attribute="description">Drive Current value (if set to DICV) or Drive Voltage value (if set to DVCI)</item>
	/// <item attribute="value">0.1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_Nplc_0</item>
	/// <item attribute="description">Number of power line cycle.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_PinAlias_1</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SDATA</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_MeasureMode_1</item>
	/// <item attribute="description">0: DVCI, 1:DICV</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_SenseMode_1</item>
	/// <item attribute="description">0: Local, 1: Remote</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_Compliance_1</item>
	/// <item attribute="description">Clamp Voltage value (if set to DICV), Clamp Current value (if set to DVCI)</item>
	/// <item attribute="value">200</item>
	/// <item attribute="prefix">Micro</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_DriveValue_1</item>
	/// <item attribute="description">Drive Current value (if set to DICV) or Drive Voltage value (if set to DVCI)</item>
	/// <item attribute="value">0.1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToPMU_Nplc_1</item>
	/// <item attribute="description">Number of power line cycle.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMConfigurePinToPMU(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMConfigurePinToDIO"
	/// <summary>DMCase_DMConfigurePinToDIO
	/// <list type="ControlStep" name="CM_DMCase_DMConfigurePinToDIO" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToDIO</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToDIO</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to DIO. Configure the PinAlias’s level setting. Configure the PinAlias’s to be input or output. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToDIO_PinAlias_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToDIO_DPinLevelSet_0</item>
	/// <item attribute="description">Retrieve InputTermEnable_0, HVEnable_0, ActiveLoadEnable_0, DifferentialComparatorEnable_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToDIO_PinDirection_0</item>
	/// <item attribute="description">0: Input, 1: Output</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToDIO_PinAlias_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SDATA</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToDIO_DPinLevelSet_1</item>
	/// <item attribute="description">Retrieve InputTermEnable_1, HVEnable_1, ActiveLoadEnable_1, DifferentialComparatorEnable_1 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMConfigurePinToDIO_PinDirection_1</item>
	/// <item attribute="description">0: Input, 1: Output</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_DMCase_DMConfigurePinToDIO(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMLoadVectorFile"
	/// <summary>DMCase_DMLoadVectorFile
	/// <list type="ControlStep" name="CM_DMCase_DMLoadVectorFile" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMLoadVectorFile</item>
	/// <item attribute="displayas">DMCase_DMLoadVectorFile</item>
	/// <item attribute="description">Loads the vectors to the device specified in the vector file. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMLoadVectorFile_ModuleAlias_0</item>
	/// <item attribute="description">Specifies the ModuleAlias to load vector file.</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMLoadVectorFile(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> WriteVector"
	/// <summary>DMCase_WriteVector
	/// <list type="ControlStep" name="CM_DMCase_WriteVector" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_WriteVector</item>
	/// <item attribute="displayas">DMCase_WriteVector</item>
	/// <item attribute="description">Execute the Vector Set. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">WriteVector_ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">WriteVector_VectorFileName</item>
	/// <item attribute="description">Specifies the Vector Set to be executed.</item>
	/// <item attribute="value">Quiescent_HB_LPM</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_WriteVector(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMDioModeDrivePin"
	/// <summary>DMCase_DMDioModeDrivePin
	/// <list type="ControlStep" name="CM_DMCase_DMDioModeDrivePin" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMDioModeDrivePin</item>
	/// <item attribute="displayas">DMCase_DMDioModeDrivePin</item>
	/// <item attribute="description">Drive PinAlias’s to 0 (Low) or 1 (High). The high or low value is set according to the ControlMethod (DMCase_DMConfigurePinToDIO). Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMDioModeDrivePin_VIO</item>
	/// <item attribute="description">Drive logic 0 for VIO PinAlias</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMDioModeDrivePin_VBIAS</item>
	/// <item attribute="description">Drive logic 1 for VBIAS PinAlias</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMDioModeDrivePin(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMDriveSoftwareTrigger"
	/// <summary>DMCase_DMDriveSoftwareTrigger
	/// <list type="ControlStep" name="CM_DMCase_DMDriveSoftwareTrigger" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMDriveSoftwareTrigger</item>
	/// <item attribute="displayas">DMCase_DMDriveSoftwareTrigger</item>
	/// <item attribute="description">•	Drives software trigger immediately. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMDriveSoftwareTrigger_ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMDriveSoftwareTrigger_Select</item>
	/// <item attribute="description">Specifies to which software trigger to drive. Software trigger lines are digital signals coming from the on-board FPGA processor. There are four software triggers to choose from.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMDriveSoftwareTrigger_PulseWidth</item>
	/// <item attribute="description">Specifies the pulse width of the trigger signal, in second, ranged from 1us to 10 ms.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_DMCase_DMDriveSoftwareTrigger(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMMapTriggerIntToTriggerOut"
	/// <summary>DMCase_DMMapTriggerIntToTriggerOut
	/// <list type="ControlStep" name="CM_DMCase_DMMapTriggerIntToTriggerOut" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMMapTriggerIntToTriggerOut</item>
	/// <item attribute="displayas">DMCase_DMMapTriggerIntToTriggerOut</item>
	/// <item attribute="description">Connect 2 trigger lines together. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">DMMapTriggerIntToTriggerOut_ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMMapTriggerIntToTriggerOut_InputTerminal</item>
	/// <item attribute="description">Tri-state the trigger source</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DMMapTriggerIntToTriggerOut_OutputTerminal</item>
	/// <item attribute="description">Tri-state the trigger source</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMMapTriggerIntToTriggerOut(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMConfigureTriggerEdgeLevel"
	/// <summary>DMCase_DMConfigureTriggerEdgeLevel
	/// <list type="ControlStep" name="CM_DMCase_DMConfigureTriggerEdgeLevel" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureTriggerEdgeLevel</item>
	/// <item attribute="displayas">DMCase_DMConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Configures the trigger edge level. Upon power-up nothing is selected for the triggerEnum.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMConfigureTriggerEdgeLevel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMConfigureOutputTriggerSelect"
	/// <summary>DMCase_DMConfigureOutputTriggerSelect
	/// <list type="ControlStep" name="CM_DMCase_DMConfigureOutputTriggerSelect" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureOutputTriggerSelect</item>
	/// <item attribute="displayas">DMCase_DMConfigureOutputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger output to be used.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMConfigureOutputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMConfigureReadPin_TriggerOutput"
	/// <summary>DMCase_DMConfigureReadPin_TriggerOutput
	/// <list type="ControlStep" name="CM_DMCase_DMConfigureReadPin_TriggerOutput" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureReadPin_TriggerOutput</item>
	/// <item attribute="displayas">DMCase_DMConfigureReadPin_TriggerOutput</item>
	/// <item attribute="description">Configure PinAlias as the selected physical trigger line.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMConfigureReadPin_TriggerOutput(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMCase_DMCastDPinLevel"
	/// <summary>DMCase_DMCase_DMCastDPinLevel
	/// <list type="ControlStep" name="CM_DMCase_DMCase_DMCastDPinLevel" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMCase_DMCastDPinLevel</item>
	/// <item attribute="displayas">DMCase_DMCase_DMCastDPinLevel</item>
	/// <item attribute="description">Define Dpin Level of the VIH/VIL/VOH/VOL/IOH/IOL/VCH/VCL/VTERM. The first set of Dpin Level is label as 0. User able to define second or more set of Dpin Level. Example: VIH_0, VIH_1, etc.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMCastDPinLevel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMCastTimingSetPeriod"
	/// <summary>DMCase_DMCastTimingSetPeriod
	/// <list type="ControlStep" name="CM_DMCase_DMCastTimingSetPeriod" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMCastTimingSetPeriod</item>
	/// <item attribute="displayas">DMCase_DMCastTimingSetPeriod</item>
	/// <item attribute="description">Define the waveforms period of the vector. The first set of Timing Set Period is label as 0. User able to define second or more set of Timing Set. Example: TimingSet_0, TimingSet_1.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMCastTimingSetPeriod(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DMCastPEAttribute"
	/// <summary>DMCase_DMCastPEAttribute
	/// <list type="ControlStep" name="CM_DMCase_DMCastPEAttribute" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMCastPEAttribute</item>
	/// <item attribute="displayas">DMCase_DMCastPEAttribute</item>
	/// <item attribute="description">To enable/disable Input Term/HV/Active Load/Differential Comparator function. The first set of PE Attribute is label as 0. User able to define second or more set of PE Attribute. Example: InputTermEnable_0, HVEnable_0, etc.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_DMCase_DMCastPEAttribute(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	
	#pragma endregion

	#pragma region "IOM400e ControlStep.xml"

	#pragma region ".xml file -> Control Step -> DIODrivePin"
	/// <summary>IOMCase_DIODrivePin
	/// <list type="ControlStep" name="CM_IOMCase_DIODrivePin" category="IOMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIODrivePin</item>
	/// <item attribute="displayas">IOMCase_DIODrivePin</item>
	/// <item attribute="description">Configure the PinAlias to 1 (High) or 0 (Low) according to the ControlMethod (IOMCase_DIOSetModuleVIO)</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_IOMCase_DIODrivePin(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DIODrivePort"
	/// <summary>IOMCase_DIODrivePort
	/// <list type="ControlStep" name="CM_IOMCase_DIODrivePort" category="IOMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIODrivePort</item>
	/// <item attribute="displayas">IOMCase_DIODrivePort</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_IOMCase_DIODrivePort(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}	
	#pragma region ".xml file -> Control Step -> DIOSetModuleVIO"
	/// <summary>IOMCase_DIOSetModuleVIO
	/// <list type="ControlStep" name="CM_IOMCase_DIOSetModuleVIO" category="IOMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIOSetModuleVIO</item>
	/// <item attribute="displayas">IOMCase_DIOSetModuleVIO</item>
	/// <item attribute="description">Configure ModuleAlias’s Voltage Level to 0 (3.3V), 1 (5V), 2 (External Input)</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_IOMCase_DIOSetModuleVIO(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> DIOSetPortDirection"
	/// <summary>IOMCase_DIOSetPortDirection
	/// <list type="ControlStep" name="CM_IOMCase_DIOSetPortDirection" category="IOMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIOSetPortDirection</item>
	/// <item attribute="displayas">IOMCase_DIOSetPortDirection</item>
	/// <item attribute="description">Configure the PortAlias’s port direction</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_IOMCase_DIOSetPortDirection(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	#pragma endregion

	#pragma region "RFCase ControlStep.xml"

	#pragma region ".xml file -> Control Step -> RF SourcePower"
	/// <summary>RFCase_SourcePower
	/// <list type="ControlStep" name="CM_RFCase_SourcePower" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePower</item>
	/// <item attribute="displayas">RFCase_SourcePower</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SourcePower(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SourcePowerFast"
	/// <summary>RFCase_SourcePowerFast
	/// <list type="ControlStep" name="CM_RFCase_SourcePowerFast" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePowerFast</item>
	/// <item attribute="displayas">RFCase_SourcePowerFast</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SourcePowerFast(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SourcePowerLow"
	/// <summary>RFCase_SourcePowerLow
	/// <list type="ControlStep" name="CM_RFCase_SourcePowerLow" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePowerLow</item>
	/// <item attribute="displayas">RFCase_SourcePowerLow</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SourcePowerLow(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SourceTwoTone"
	/// <summary>RFCase_SourceTwoTone
	/// <list type="ControlStep" name="CM_RFCase_SourceTwoTone" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourceTwoTone</item>
	/// <item attribute="displayas">RFCase_SourceTwoTone</item>
	/// <item attribute="description">Source two tone RF signals with specified power level and frequency respectively</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SourceTwoTone(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF IsolateChannel"
	/// <summary>RFCase_IsolateChannel
	/// <list type="ControlStep" name="CM_RFCase_IsolateChannel" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_IsolateChannel</item>
	/// <item attribute="displayas">RFCase_IsolateChannel</item>
	/// <item attribute="description">Configure RF PinAlias to the Isolate Mode.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_IsolateChannel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF StartModulation"
	/// <summary>RFCase_StartModulation
	/// <list type="ControlStep" name="CM_RFCase_StartModulation" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_StartModulation</item>
	/// <item attribute="displayas">RFCase_StartModulation</item>
	/// <item attribute="description">Start modulation on the signal generator.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_StartModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF StopModulation"
	/// <summary>RFCase_StopModulation
	/// <list type="ControlStep" name="CM_RFCase_StopModulation" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_StopModulation</item>
	/// <item attribute="displayas">RFCase_StopModulation</item>
	/// <item attribute="description">Disable IQ modulation on the signal generator.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_StopModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SetSourceTriggerRouting"
	/// <summary>RFCase_SetSourceTriggerRouting
	/// <list type="ControlStep" name="CM_RFCase_SetSourceTriggerRouting" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetSourceTriggerRouting</item>
	/// <item attribute="displayas">RFCase_SetSourceTriggerRouting</item>
	/// <item attribute="description">Setup Source Trigger Routing of the module.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SetSourceTriggerRouting(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SetSourceTriggerIn"
	/// <summary>RFCase_SetSourceTriggerIn
	/// <list type="ControlStep" name="CM_RFCase_SetSourceTriggerIn" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetSourceTriggerIn</item>
	/// <item attribute="displayas">RFCase_SetSourceTriggerIn</item>
	/// <item attribute="description">Setup Source TriggerIn of the module.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SetSourceTriggerIn(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SetSourceTriggerOut"
	/// <summary>RFCase_SetSourceTriggerOut
	/// <list type="ControlStep" name="CM_RFCase_SetSourceTriggerIn" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetSourceTriggerOut</item>
	/// <item attribute="displayas">RFCase_SetSourceTriggerOut</item>
	/// <item attribute="description">Setup Source TriggerOut of the module.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SetSourceTriggerOut(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Control Step -> RF SetMeasureTriggerRouting"
	/// <summary>RFCase_SetMeasureTriggerRouting
	/// <list type="ControlStep" name="CM_RFCase_SetMeasureTriggerRouting" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetMeasureTriggerRouting</item>
	/// <item attribute="displayas">RFCase_SetMeasureTriggerRouting</item>
	/// <item attribute="description">Setup Measure Trigger Routing of the module.</item>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::CM_RFCase_SetMeasureTriggerRouting(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}


	#pragma endregion

	#pragma region "AM400e & DM400e Test Item"

	#pragma region ".xml file -> Test Item -> TM OS"
	/// <summary> DCTest_OpenShort
	/// <list type="TestItem" name="TM_OS" category="DcTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCTest_OpenShort</item>
	/// <item attribute="displayas">DCTest_OpenShort</item>
	/// <item attribute="description">Measures the current level for the specified pin alias. The test function is executed and the result is returned to the respective test parameter.</item>
	/// <list type="TestParameter" name="TM_OS" category="DcTest" group="DC_Items">
	/// <item attribute="name">DCTest_OS</item>
	/// <item attribute="displayas">DCTest_OS</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-0.8</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">-0.2</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DriveCurrent</item>
	/// <item attribute="description">Specifies the Current Level.</item>
	/// <item attribute="value">-100</item>
	/// <item attribute="prefix">Mirco</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ClampVoltage</item>
	/// <item attribute="description">Specifies the Clamp Level.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">WaitSecond</item>
	/// <item attribute="description">Specifies the delay time.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">sec</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::TM_OS(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Test Item -> TM MeasureCurrent"
	/// <summary> DCTest_MeasureCurrent
	/// <list type="TestItem" name="TM_MeasureCurrent" category="DcTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCTest_MeasureCurrent</item>
	/// <item attribute="displayas">DCTest_MeasureCurrent</item>
	/// <item attribute="description">Measures the current level for the specified pin alias. The test function is executed and the result is returned to the respective test parameter.</item>
	/// <list type="TestParameter" name="TM_MeasureCurrent" category="DcTest" group="DC_Items">
	/// <item attribute="name">DCTest_MeasureCurrent</item>
	/// <item attribute="displayas">DCTest_MeasureCurrent</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">Micro</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">0</item>
	/// <item attribute="lolimitprefix">Micro</item>
	/// <item attribute="hilimit">10</item>        
	/// <item attribute="hilimitprefix">Micro</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">WaitSecond</item>
	/// <item attribute="description">Specifies the delay before perform measurement.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">sec</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::TM_MeasureCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Test Item -> TM MeasureVoltage"
	/// <summary> DCTest_MeasureVoltage
	/// <list type="TestItem" name="TM_MeasureVoltage" category="DcTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCTest_MeasureVoltage</item>
	/// <item attribute="displayas">DCTest_MeasureVoltage</item>
	/// <item attribute="description">Measures the voltage level for the specified pin alias. The test function is executed and the result is returned to the respective test parameter.</item>
	/// <list type="TestParameter" name="TM_MeasureCurrent" category="DcTest" group="DC_Items">
	/// <item attribute="name">DCTest_MeasureVoltage</item>
	/// <item attribute="displayas">DCTest_MeasureVoltage</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">0</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">2</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">WaitSecond</item>
	/// <item attribute="description">Specifies the delay before perform measurement.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">sec</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::TM_MeasureVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Test Item -> TM MeasureBurstCurrent"
	/// <summary> AMTest_MeasureBurstCurrent
	/// <list type="TestItem" name="TM_MeasureBurstCurrent" category="AMTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">AMTest_MeasureBurstCurrent</item>
	/// <item attribute="displayas">AMTest_MeasureBurstCurrent</item>
	/// <item attribute="description">Measure the Burst Current Level for the specified PinAlias.</item>
	/// <list type="TestParameter" name="TM_MeasureBurstCurrent" category="AMTest" group="DC_Items">
	/// <item attribute="name">AMTest_MeasureBurstCurrent</item>
	/// <item attribute="displayas">AMTest_MeasureBurstCurrent</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">0</item>
	/// <item attribute="lolimitprefix">Milli</item>
	/// <item attribute="hilimit">50</item>        
	/// <item attribute="hilimitprefix">Milli</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Duration</item>
	/// <item attribute="description">Specifies the duration to capture the measurement.</item>
	/// <item attribute="value">0.01</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">sec</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PeakPercentage</item>
	/// <item attribute="description">Specifies the percentage of the peak to be taken for measurement.</item>
	/// <item attribute="value">90</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">%</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::TM_MeasureBurstCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
	#pragma region ".xml file -> Test Item -> TM MeasureBurstVoltage"
	/// <summary> AMTest_MeasureBurstVoltage
	/// <list type="TestItem" name="TM_MeasureBurstCurrent" category="AMTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">AMTest_MeasureBurstVoltage</item>
	/// <item attribute="displayas">AMTest_MeasureBurstVoltage</item>
	/// <item attribute="description">Measure the Burst Voltage Level for the specified PinAlias.</item>
	/// <list type="TestParameter" name="TM_MeasureBurstCurrent" category="AMTest" group="DC_Items">
	/// <item attribute="name">AMTest_MeasureBurstVoltage</item>
	/// <item attribute="displayas">AMTest_MeasureBurstVoltage</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">0</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">5</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Duration</item>
	/// <item attribute="description">Specifies the duration to capture the measurement.</item>
	/// <item attribute="value">0.01</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">sec</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PeakPercentage</item>
	/// <item attribute="description">Specifies the percentage of the peak to be taken for measurement.</item>
	/// <item attribute="value">90</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">%</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
	#pragma endregion
	int TestProgram::TM_MeasureBurstVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}


	#pragma endregion
	
}


/*----------------------------------------------------------------------
* Revision Log
* &Log: TestMethod.cpp.rca&


*** Version	:
*** Date	:
*** PIC		:
*

*** Version	: v1.0.0.1
*** Date	: 31 March 2023
*** PIC		: Ng Chen Yang
*UP REV

*** Version	: v1.0.0.0
*** Date	: 31 December 2022
*** PIC		: Ooi Jing Yao
* Initial release version.
* Auto detech test flow, perform the control phase and test phase.
* Support project UUT:
  - Single Site Single UUT
  - Single Site Multi UUT
  - True Parallel Single UUT
* Support AEM module:
  - AM
  - DM
* Support VNA:
  - CMT SC5090
  - Keysight M9804A
* Support platform execution phase:
  - DcControl
  - DcTest
  - PatternControl
  - PatternTest
  - VnaConfig
  - VnaFetch
  - VnaDataAnalysis
----------------------------------------------------------------------*/

