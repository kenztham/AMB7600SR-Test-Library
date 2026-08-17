/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			MethodName.cpp
Purpose:		To execute test function for all Control Steps, Control Items & Test Items
Version:		v1.0.0.0
----------------------------------------------------------------------*/


#include "..\\TestProgram.h"

namespace AMB7600SR_TestLibrary_REV2
{

#pragma region ".xml file -> AppsWideVariable"

	/// <summary> AppsWideVariable
	/// <list type="AppsWideVariable">
	/// <item attribute="name">SharedVNA</item>
	/// <item attribute="description">Specifies if VNA is shared for MultiUUT Offset.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">gCreateFixedOffsetFile</item>
	/// <item attribute="description">True = create offset file as {TesterId}_{ProjectName}_CorrFactor_S{Site}.csv</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">SaveSnpData_Format</item>
	/// <item attribute="description">[snp] To enable the function of saving trace data into snp file. | Specifies the snp format.</item>
	/// <item attribute="value">SaveSnpDataOff/dB_Angle</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">S2Ppath</item>
	/// <item attribute="description">[snp] Specifies the snp filepath if SaveSnpDataOn.</item>
	/// <item attribute="value">C:\snp</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">S2Psave_ByHardBin</item>
	/// <item attribute="description">[snp] Move the S2P generated in S2Ppath to S2Ppath\Binnings [Based on the hard bin of the DUT result]</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">S2Prename_EN</item>
	/// <item attribute="description">[snp] 0 = Default | 1 = Rename as S2Prename_Name</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">S2Prename_Name</item>
	/// <item attribute="description">[snp] Specifies the snp file name if S2Prename_EN = 1, supported ${Macro} please refer to related Config Manual.</item>
	/// <item attribute="value">abc1234_$(Program Name)_$(TimeNow)</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">S2PswapData</item>
	/// <item attribute="description">[snp] Swap data in S2P file [Port1 -> Port2; Port2->Port1]</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">GenericStateMappingFile_EN</item>
	/// <item attribute="description">Use standardized state / mapping file istead of "AMB7300Config_DeviceName"</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">GenericStateMappingFile_Name</item>
	/// <item attribute="description">Specifies the file name in [ProgramData\Aemulus\AMB7300\State] for the generic state / mapping file when GenericStateMappingFile_EN is TRUE</item>
	/// <item attribute="value">AMB7300S6P1D_AMB7300_TestLibrary</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">HighPwrTest_EN</item>
	/// <item attribute="description">[HighPowerTest] 0 = Default | 1 = Enable high power testing. Expected external PA connected and separate AppsPowerCal done.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">HighPwrTest_AppsCalFile</item>
	/// <item attribute="description">[HighPowerTest] Specifies AppsCalFile path if HighPwrTest_EN = 1.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\AppsCal\SampleProfile\VNA_Cal_list.csv</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">VNA_Mutex_EN</item>
	/// <item attribute="description">[Mutex] 0 = Off | 1 = Enable enable ping-pong testing, use this for index parallel testing when VNA resource is shared for multiple sites.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">PortMatching1</item>
	/// <item attribute="description">[PortMatching] To specify the snp filepath of matching circuit at Port 1.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\Port Matching\PLPC.s2p</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">PortMatching2</item>
	/// <item attribute="description">[PortMatching] To specify the snp filepath of matching circuit at Port 2.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\Port Matching\PLPC.s2p</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">PortMatching3</item>
	/// <item attribute="description">[PortMatching] To specify the snp filepath of matching circuit at Port 3.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\Port Matching\PLPC.s2p</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">PortMatching4</item>
	/// <item attribute="description">[PortMatching] To specify the snp filepath of matching circuit at Port 4.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\Port Matching\PLPC.s2p</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">PortMatching5</item>
	/// <item attribute="description">[PortMatching] To specify the snp filepath of matching circuit at Port 5.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\Port Matching\PLPC.s2p</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="AppsWideVariable">
	/// <item attribute="name">PortMatching6</item>
	/// <item attribute="description">[PortMatching] To specify the snp filepath of matching circuit at Port 6.</item>
	/// <item attribute="value">C:\Aemulus\TesterInfo\Port Matching\PLPC.s2p</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </summary>

#pragma endregion

	//Control Item: PreProcessing
#pragma region ".xml file -> Control Item -> PreProcessing"

	/// <summary> PreProcessing
	/// <list type="ControlItem" name="PreProcessing" category="PreProcessing" group="Items" conditiontype="splitbysemicolon" methodname="PreProcessing">
	/// <item attribute="name">PreProcessing</item>
	/// <item attribute="displayas">PreProcessing</item>
	/// <item attribute="description">The is 'PreProcessing' item, which is to reload offsest file and spare for pre-test control.</item>
	/// <list type="ItemCondition">
	/// <item attribute="name">CorrFactorDirectory</item>
	/// <item attribute="description">Specifies the directory of CorrFactor file.</item>
	/// <item attribute="value">C:\Aemulus\techFlow3\Projects\TestRecipes\SampleProfile\AMB7300_TestLibrary_REV2P0_Beta\FixedOffsetFileFolder\AMB7300SR_AMB7300_TestLibrary_REV2P0_Beta_CorrFactor_S0.csv</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </summary>
	/// <param name="site">This is techFlow site object.</param>

#pragma endregion

	//Control Item: PostProcessing
#pragma region ".xml file -> Control Item -> PostProcessing"

	/// <summary> PostProcessing
	/// <list type="ControlItem" name="PostProcessing" category="PostProcessing" group="Items" conditiontype="splitbysemicolon" methodname="PostProcessing">
	/// <item attribute="name">PostProcessing</item>
	/// <item attribute="displayas">PostProcessing</item>
	/// <item attribute="description">The is 'PostProcessing' item, which spare for use of post-testing action.</item>
	/// <list type="ItemCondition">
	/// <item attribute="name">Condition</item>
	/// <item attribute="description">Specifies the condition description.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// </summary>
	/// <param name="site">This is techFlow site object.</param>

#pragma endregion

	//Control Step
#pragma region "AM400e & DM400e ControlStep.xml"
	// AM400e DM400e
#pragma region ".xml file -> Control Step -> DCCase_DriveVoltage"
	/// <summary> DCCase_DriveVoltage
	/// <list type="ControlStep" name="DCCase_DriveVoltage" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveVoltage</item>
	/// <item attribute="displayas">DCCase_DriveVoltage</item>
	/// <item attribute="description">Configures the Voltage Level (DVCI) for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DriveVoltage</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Force</item>
	/// <item attribute="description">Specifies the voltage level in volts (V).</item>
	/// <item attribute="value">3.3</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DriveCurrent</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Force</item>
	/// <item attribute="description">Specifies the drive current in amps (A).</item>
	/// <item attribute="value">100</item>
	/// <item attribute="prefix">Micro</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ClampVoltage</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Clamp</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ClampCurrent</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Clamp</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_SetNPLC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">NPLC</item>
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
	///	<summary>DCCase_SetPinOnOff
	/// <list type="ControlStep" name="CM_DCCase_SetPinOnOff" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_SetPinOnOff</item>
	/// <item attribute="displayas">DCCase_SetPinOnOff</item>
	/// <item attribute="description">Turn On or Off on the specified PinAlias. Value 1 = Turn On PinAlias; Value 0 = Turn Off PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_SetPinOnOff</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinOn</item>
	/// <item attribute="description">Configures the SMU &amp; DM output switch status. Mode0(Turn OFF), Mode1(Turn ON)</item>
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

#pragma region ".xml file -> Control Step -> ConfigureTriggerEdgeLevel"
	/// <summary>DCCase_ConfigureTriggerEdgeLevel
	/// <list type="ControlStep" name="CM_DCCase_ConfigureTriggerEdgeLevel" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
#pragma region ".xml file -> Control Step -> ConfigureTriggerEdgeLevelExtra"
	/// <summary>DCCase_ConfigureTriggerEdgeLevelExtra
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureTriggerEdgeLevelExtra" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="description">Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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

	// AM400e DM400e CM400e
#pragma region ".xml file -> Control Step -> MapTriggerIntToTriggerOut"
	/// <summary>DCCase_ConfigureTriggerEdgeLevel
	/// <list type="ControlStep" name="CM_DCCase_MapTriggerIntToTriggerOut" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_MapTriggerIntToTriggerOut</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Connect 2 trigger lines together. Support AM430e, AM450e, AM451e, AM471e, DM483e, CM400e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DriveSoftwareTrigger</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">AM430e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Select</item>
	/// <item attribute="description">Specifies to which software trigger to drive. Software trigger lines are digital signals coming from the on-board FPGA processor. There are four software triggers to choose from.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PulseWidth</item>
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

#pragma region ".xml file -> Control Step -> WaitSecond"
	/// <summary> DCCase_WaitSecond
	/// <list type="ControlStep" name="CM_DCCase_WaitSecond" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_WaitSecond</item>
	/// <item attribute="displayas">DCCase_WaitSecond</item>
	/// <item attribute="description"></item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_WaitSecond</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Delay</item>
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
#pragma endregion

#pragma region "AM400e ControlStep.xml"

#pragma region ".xml file -> Control Step -> AMConfigureInputTriggerSelect"
	/// <summary>DCCase_AMConfigureInputTriggerSelect
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureInputTriggerSelect" category="DCCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureInputTriggerSelect</item>
	/// <item attribute="displayas">DCCase_ConfigureInputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger input to be used for operations such as AcquireMultiple() and AcquireArray(). Upon power-up nothing is selected for the triggerInput. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureInputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CM_DCCase_AMConfigureInputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> AMConfigureSMUOutputTriggerPulseWidth"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerPulseWidth
	/// <list type="ControlStep" name="CM_DCCase_AMConfigureSMUOutputTriggerPulseWidth" category="AMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="description">Configures the pulse width of trigger output signal.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureSMUOutputTriggerDuringSource</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Level</item>
	/// <item attribute="description">Specifies the threshold level of the channel where a trigger output is generated when this threshold level is hit, depending on edgeSetting.</item>
	/// <item attribute="value">0.7</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Range</item>
	/// <item attribute="description">Specifies the range of the threshold level.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Mode</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureSMUOutputTriggerMode</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureOutputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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

#pragma region "DM400e ControlStep.xml"

#pragma region ".xml file -> Control Step -> DMConfigurePinToVector"
	/// <summary>DMCase_DMConfigurePinToVector
	/// <list type="ControlStep" name="CM_DMCase_DMConfigurePinToVector" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to Vector. Configure the PinAlias’s level setting. Configure the PinAlias’s attribute of pin electronics. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DPinLevelSet</item>
	/// <item attribute="description">Retrieve VIH_0, VIL_0, VOH_0, VOL_0, IOH_0, IOL_0, VCH_0, VCL_0, VTERM_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PEAttSet</item>
	/// <item attribute="description">Retrieve InputTermEnable_0, HVEnable_0, ActiveLoadEnable_0, DifferentialComparatorEnable_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigurePinToPMU</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureMode</item>
	/// <item attribute="description">0: DVCI, 1:DICV</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SenseMode</item>
	/// <item attribute="description">0: Local, 1: Remote</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Compliance</item>
	/// <item attribute="description">Clamp Voltage value (if set to DICV), Clamp Current value (if set to DVCI)</item>
	/// <item attribute="value">200</item>
	/// <item attribute="prefix">Micro</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DriveValue</item>
	/// <item attribute="description">Drive Current value (if set to DICV) or Drive Voltage value (if set to DVCI)</item>
	/// <item attribute="value">0.1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Nplc</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigurePinToDIO</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DPinLevelSet</item>
	/// <item attribute="description">Retrieve InputTermEnable_0, HVEnable_0, ActiveLoadEnable_0, DifferentialComparatorEnable_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinDirection</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMLoadVectorFile</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_WriteVector</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VectorFileName</item>
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
	/// <item attribute="description">Drive PinAlias’s to 0 (Low) or 1 (High). The high or low value is set according to the MethodName (DMCase_DMConfigurePinToDIO). Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMDioModeDrivePin</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VIO</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Logic</item>
	/// <item attribute="description">Drive logic 0 / 1 for VBIAS PinAlias</item>
	/// <item attribute="value">0</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMDriveSoftwareTrigger</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Select</item>
	/// <item attribute="description">Specifies to which software trigger to drive. Software trigger lines are digital signals coming from the on-board FPGA processor. There are four software triggers to choose from.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PulseWidth</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMMapTriggerIntToTriggerOut</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputTerminal</item>
	/// <item attribute="description">Tri-state the trigger source</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">OutputTerminal</item>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureTriggerEdgeLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerEnum</item>
	/// <item attribute="description">Specifies the triggering source</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Option</item>
	/// <item attribute="description">Specifies the edge of trigger</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IgnoreTriggerCount</item>
	/// <item attribute="description">Specifies the number of trigger count should be ignored before measuring</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <summary>DMCase_DMConfigureInputTriggerSelect
	/// <list type="ControlStep" name="CM_DMCase_DMConfigureInputTriggerSelect" category="DMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureInputTriggerSelect</item>
	/// <item attribute="displayas">DMCase_DMConfigureInputTriggerSelect</item>
	/// <item attribute="description">•	Selects the trigger input to be used for operations such as AcquireMultiple() and AcquireArray().Upon power - up nothing is selected for the triggerInput</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureInputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerInput</item>
	/// <item attribute="description">Tri-state the trigger input</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerDelay</item>
	/// <item attribute="description">Specifies the delay inserted before generating the trigger output.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_DMCase_DMConfigureInputTriggerSelect(Site^ site)
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureOutputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerOutput0</item>
	/// <item attribute="description">Specifies the trigger output signal.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerOutput1</item>
	/// <item attribute="description">Specifies the delay inserted before generating the trigger output.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureReadPin_TriggerOutput</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinStatusSelect</item>
	/// <item attribute="description">0: Fire the trigger output when read pin value is logic LOW 1: Fire the trigger output when read pin value is logic HIGH</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <item attribute="description">Define Dpin Level of the VIH/VIL/VOH/VOL/IOH/IOL/VCH/VCL/VTERM. The first set of Dpin Level is has no index. User able to define second or more set of Dpin Level with index. Example: VIH, VIH_1, etc.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMCase_DMCastDPinLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VIH</item>
	/// <item attribute="description">Specifies the VIH with reference to DPin set</item>
	/// <item attribute="value">1.8</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VIL</item>
	/// <item attribute="description">Specifies the VIL with reference to DPin set</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VOH</item>
	/// <item attribute="description">Specifies the VOH with reference to DPin set</item>
	/// <item attribute="value">0.9</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VOL</item>
	/// <item attribute="description">Specifies the VOL with reference to DPin set</item>
	/// <item attribute="value">0.7</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IOH</item>
	/// <item attribute="description">Specifies the IOH with reference to DPin set</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IOL</item>
	/// <item attribute="description">Specifies the IOL with reference to DPin set</item>
	/// <item attribute="value">1.8</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCH</item>
	/// <item attribute="description">Specifies the VCH with reference to DPin set</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCL</item>
	/// <item attribute="description">Specifies the VCL with reference to DPin set</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VTERM</item>
	/// <item attribute="description">Specifies the VTERM with reference to DPin set</item>
	/// <item attribute="value">0.9</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
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
	/// <item attribute="description">Define the waveforms period of the vector. The first set of Timing Set Period has no index. User able to define second or more set of Timing Set ing index. Example: TimingSetPeriod, TimingSetPeriod_1.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMCastTimingSetPeriod</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TimingSetPeriod</item>
	/// <item attribute="description">Specifies the period of respective timing set</item>
	/// <item attribute="value">26</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMCastPEAttribute</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputTermEnable</item>
	/// <item attribute="description">Specifies the input terminal enable</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">HVEnable</item>
	/// <item attribute="description">Specifies the high voltage enable</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ActiveLoadEnable</item>
	/// <item attribute="description">Specifies the active laod enable</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DifferentialComparatorEnable</item>
	/// <item attribute="description">Specifies the differential comparator enable</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
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
	/// <item attribute="description">Configure the PinAlias to 1 (High) or 0 (Low) according to the MethodName (IOMCase_DIOSetModuleVIO)</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIODrivePin</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinLogic</item>
	/// <item attribute="description">Specifies the logic for specific PinAlias.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIODrivePort</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortAlias</item>
	/// <item attribute="description">Specifies the Port.</item>
	/// <item attribute="value">Port1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortLogic</item>
	/// <item attribute="description">Specifies the logic for specific Port.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIOSetModuleVIO</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">IOM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleVioMode</item>
	/// <item attribute="description">Set the ModuleAlias to specified Voltage Level</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIOSetPortDirection</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortAlias</item>
	/// <item attribute="description">Specifies the Port.</item>
	/// <item attribute="value">Port1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortDirection</item>
	/// <item attribute="description">Set the PortAlias to specified direction.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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

#pragma region "CM400e ControlStep.xml"

#pragma region ".xml file -> Control Step -> CMDrivePin"
	/// <summary>CMCase_CMDrivePin
	/// <list type="ControlStep" name="CM_CMCase_CMDrivePin" category="CMCase" group="DC_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMDrivePin</item>
	/// <item attribute="displayas">CMCase_CMDrivePin</item>
	/// <item attribute="description">Configure the PinAlias to 1 (High) or 0 (Low) according to the MethodName (CMCase_CMSetModuleVIO)</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMDrivePin</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Pin</item>
	/// <item attribute="description">Specifies the Pin.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinLogic</item>
	/// <item attribute="description">Specifies the logic for specific PinAlias.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMDrivePort</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">Port1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortLogic</item>
	/// <item attribute="description">Specifies the logic for specific Port.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMConfigurePXES2780_TriggerBus</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerBus</item>
	/// <item attribute="description">Specifies the TriggerBus.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerEnable</item>
	/// <item attribute="description">Specifies the TriggerEnable.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerDirection</item>
	/// <item attribute="description">Specifies the TriggerDirection.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMSetPortDirection</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortLogic</item>
	/// <item attribute="description">Specifies the logic for specific Port.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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

#pragma region "RFCase ControlStep.xml"

#pragma region ".xml file -> Control Step -> RF SourcePower"
	/// <summary>RFCase_SourcePower
	/// <list type="ControlStep" name="RFCase_SourcePower" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePower</item>
	/// <item attribute="displayas">RFCase_SourcePower</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourcePower</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal frequency.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourcePowerFast</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal frequency.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourcePowerLow</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourceTwoTone</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq0</item>
	/// <item attribute="description">Specifies the RF signal frequency to port A.</item>
	/// <item attribute="value">1999.5</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin0</item>
	/// <item attribute="description">Specifies the RF signal power to port A.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq1</item>
	/// <item attribute="description">Specifies the RF signal frequency to port B.</item>
	/// <item attribute="value">2000.5</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin1</item>
	/// <item attribute="description">Specifies the RF signal power to port B.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem_0</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem_1</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_IsolateChannel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Channel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_StartModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModulationFile</item>
	/// <item attribute="description">Specifies the modulation file to be executed.</item>
	/// <item attribute="value">2Tones_1MHz.awf</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PlayBackMode</item>
	/// <item attribute="description">Specifies the playback mode of ARB.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_StopModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetSourceTriggerRouting</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigIn</item>
	/// <item attribute="description">Specify the triggerIn of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigOut</item>
	/// <item attribute="description">Specifies the triggerOut of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetSourceTriggerIn</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specify the trigSource of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigPolarity</item>
	/// <item attribute="description">Specifies the trigPolarity of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigDelay</item>
	/// <item attribute="description">Specifies the trigDelay of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetSourceTriggerOut</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigDestination</item>
	/// <item attribute="description">Specify the trigDest of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigOption</item>
	/// <item attribute="description">Specifies the trigOption of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetMeasureTriggerRouting</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigIn</item>
	/// <item attribute="description">Specify the triggerIn of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigOut</item>
	/// <item attribute="description">Specifies the triggerOut of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
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
#pragma region ".xml file -> Control Step -> RF SetMeasureTriggerIn"
	/// <summary>RFCase_SetMeasureTriggerIn
	/// <list type="ControlStep" name="CM_RFCase_SetMeasureTriggerIn" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetMeasureTriggerIn</item>
	/// <item attribute="displayas">RFCase_SetMeasureTriggerIn</item>
	/// <item attribute="description">Setup Measure Trigger Routing of the module.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetMeasureTriggerIn</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specify the trigSource of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigPolarity</item>
	/// <item attribute="description">Specifies the trigPolarity of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigDelay</item>
	/// <item attribute="description">Specifies the trigDelay of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_SetMeasureTriggerIn(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF RunSourceAlignment"
	/// <summary>RFCase_RunSourceAlignment
	/// <list type="ControlStep" name="CM_RFCase_RunSourceAlignment" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_RunSourceAlignment</item>
	/// <item attribute="displayas">RFCase_RunSourceAlignment</item>
	/// <item attribute="description">Perform Source Alignement</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_RunSourceAlignment</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_RunSourceAlignment(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF LoadModulation"
	/// <summary>RFCase_LoadModulation
	/// <list type="ControlStep" name="CM_RFCase_LoadModulation" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_LoadModulation</item>
	/// <item attribute="displayas">RFCase_LoadModulation</item>
	/// <item attribute="description">Load the modulation file.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_LoadModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModulationFile</item>
	/// <item attribute="description">Specifies the modulation file to be loaded to tester.</item>
	/// <item attribute="value">2Tones_1MHz.awf</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_LoadModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF WlanInit"
	/// <summary>RFCase_WlanInit
	/// <list type="ControlStep" name="CM_RFCase_WlanInit" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WlanInit</item>
	/// <item attribute="displayas">RFCase_WlanInit</item>
	/// <item attribute="description">Wlan initialization</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WlanInit</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasVSG</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasVSA</item>
	/// <item attribute="description">Specifies the Module Alias of the signal analyzer </item>
	/// <item attribute="value">VSA1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">measureOption_ACAX</item>
	/// <item attribute="description">Specifies enable or disable the measure option of 11ac &amp; 11ax </item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">measureOption_ABGN</item>
	/// <item attribute="description">Specifies enable or disable the measure option of 11abgn</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_WlanInit(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF EvmMeasurementSetup"
	/// <summary>RFCase_EvmMeasurementSetup
	/// <list type="ControlStep" name="CM_RFCase_EvmMeasurementSetup" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_EvmMeasurementSetup</item>
	/// <item attribute="displayas">RFCase_EvmMeasurementSetup</item>
	/// <item attribute="description">Evm Measurement Setup</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_EvmMeasurementSetup</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">WlanModulationStandard</item>
	/// <item attribute="description">Specifies Evm Wlan Modulation Standard.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_0</item>
	/// <item attribute="description">(Optional)Specifies AcqTime</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_1</item>
	/// <item attribute="description">(Optional)Specifies viewConstellation</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_2</item>
	/// <item attribute="description">(Optional)Specifies mcsIndex</item>
	/// <item attribute="value">8</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_3</item>
	/// <item attribute="description">(Optional)Specifies PSDULength</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_4</item>
	/// <item attribute="description">(Optional)Specifies autoConfigSetup</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_EvmMeasurementSetup(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF SemMeasurementSetup"
	/// <summary>RFCase_SemMeasurementSetup
	/// <list type="ControlStep" name="CM_RFCase_SemMeasurementSetup" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SemMeasurementSetup</item>
	/// <item attribute="displayas">RFCase_SemMeasurementSetup</item>
	/// <item attribute="description">Sem Measurement Setup</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SemMeasurementSetup</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">WlanModulationStandard</item>
	/// <item attribute="description">Specifies Evm Wlan Modulation Standard.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SemAvg</item>
	/// <item attribute="description">Specifies the sem average of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_0</item>
	/// <item attribute="description">(Optional)Specifies AcqTime</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_1</item>
	/// <item attribute="description">(Optional)Specifies viewSpectrum</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_SemMeasurementSetup(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF MeasureSetup"
	/// <summary>RFCase_MeasureSetup
	/// <list type="ControlStep" name="CM_RFCase_MeasureSetup" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSetup</item>
	/// <item attribute="displayas">RFCase_MeasureSetup</item>
	/// <item attribute="description">CW RF Measurement Setup</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSetup</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies MeasureChannel</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the MeasurePower</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies MeasureFreq</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional)Specifies MeasureDelay</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies FilterOption</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_MeasureSetup(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF MeasureSetupIQ"
	/// <summary>RFCase_MeasureSetupIQ
	/// <list type="ControlStep" name="CM_RFCase_MeasureSetupIQ" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSetupIQ</item>
	/// <item attribute="displayas">RFCase_MeasureSetupIQ</item>
	/// <item attribute="description">CW RF Measurement Setup IQ</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSetupIQ</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies MeasureChannel</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the MeasurePower</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies MeasureFreq</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies SampleRate</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies SampleSize</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional)Specifies MeasureDelay</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies FilterOption</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_MeasureSetupIQ(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF TriggerSigenStartModulation"
	/// <summary>RFCase_TriggerSigenStartModulation
	/// <list type="ControlStep" name="CM_RFCase_TriggerSigenStartModulation" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_TriggerSigenStartModulation</item>
	/// <item attribute="displayas">RFCase_TriggerSigenStartModulation</item>
	/// <item attribute="description">RF trigger signal generator to start sourcing modulation</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_TriggerSigenStartModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasSigen</item>
	/// <item attribute="description">Specifies the signal generator module alias</item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModulationFile</item>
	/// <item attribute="description">Specifies the modulation file to be executed</item>
	/// <item attribute="value">WLAN_11AC_80MHz_MCS9.awf</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PlayBackMode</item>
	/// <item attribute="description">Specifies the playback mode; 0 : Single, 1 : Continuous</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VectorFileName</item>
	/// <item attribute="description">Specifies the vector file name to be executed</item>
	/// <item attribute="value">DynamicEVM</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasDM</item>
	/// <item attribute="description">Specifies the alias of the target DM</item>
	/// <item attribute="value">DM483E</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_TriggerSigenStartModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF WolferInit"
	/// <summary>RFCase_WolferInit
	/// <list type="ControlStep" name="CM_RFCase_WolferInit" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WolferInit</item>
	/// <item attribute="displayas">RFCase_WolferInit</item>
	/// <item attribute="description">Wolfer initialization</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WolferInit</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_WolferInit(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF WolferSelectPath"
	/// <summary>RFCase_WolferSelectPath
	/// <list type="ControlStep" name="CM_RFCase_WolferSelectPath" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WolferSelectPath</item>
	/// <item attribute="displayas">RFCase_WolferSelectPath</item>
	/// <item attribute="description">Wolfer path selection</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WolferSelectPath</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal source frequency.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the RF signal measure frequency.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SelectTxPath</item>
	/// <item attribute="description">Specifies the TX path (TX1 only)</item>
	/// <item attribute="value">TX1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SelectRxPath</item>
	/// <item attribute="description">Specifies the RX path (RX1 – RX8)</item>
	/// <item attribute="value">RX1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TxBypassOn</item>
	/// <item attribute="description">(Optional)Specifies the bypass mode for TX</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TxInternalPath</item>
	/// <item attribute="description">(Optional)Specifies the TX internal path(T1 – T4)</item>
	/// <item attribute="value">T1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">RxInternalPath</item>
	/// <item attribute="description">(Optional)Specifies the RX internal path(R1 – R24)</item>
	/// <item attribute="value">R1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_WolferSelectPath(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Step -> RF WolferSourcePower"
	/// <summary>RFCase_WolferSourcePower
	/// <list type="ControlStep" name="CM_RFCase_WolferSourcePower" category="RFCase" group="RF_ControlStep" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WolferSourcePower</item>
	/// <item attribute="displayas">RFCase_WolferSourcePower</item>
	/// <item attribute="description">Source power configuration of wolfer</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WolferSourcePower</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal source frequency.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">-30</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Coupler_CH</item>
	/// <item attribute="description">(Optional)Specifies the coupler channel</item>
	/// <item attribute="value">RF2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CM_RFCase_WolferSourcePower(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "VNACase ControlStep.xml"

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Control Step: VnaConfig
	**	----------------------------------------------------------------------------------------------------
	*/
#pragma region ".xml file -> Control Step -> VnaConfig"

	/// <summary> VnaConfig
	/// <list type="ControlStep" name="TestLib_ControlStep_VnaConfig" category="VnaConfig" group="Items" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">VnaConfig</item>
	/// <item attribute="displayas">VnaConfig</item>
	/// <item attribute="description">The is 'VnaConfig' item, which is to configure vna segment setting.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">SweepType</item>
	/// <item attribute="description">Specifies the vna sweep type.</item>
	/// <item attribute="value">SharedMemoryTransfer</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ChannelNum</item>
	/// <item attribute="description">Specifies Channel to be configured.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">StartFreq</item>
	/// <item attribute="description">Specifies the start frequency of the target segment.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">StopFreq</item>
	/// <item attribute="description">Specifies the stop frequency of the target segment.</item>
	/// <item attribute="value">3000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Points</item>
	/// <item attribute="description">Specifies the number of points of the target segment.</item>
	/// <item attribute="value">201</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Ifbw</item>
	/// <item attribute="description">Specifies the ifbw of the target segment.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Power</item>
	/// <item attribute="description">Specifies the power level of the target segment.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Delay</item>
	/// <item attribute="description">Specifies the delay of the target segment.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">sec</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SNP</item>
	/// <item attribute="description">Specifies the file type to override the config auto SNP file.</item>
	/// <item attribute="value">NA</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>

#pragma endregion 
	int TestProgram::TestLib_ControlStep_VnaConfig(Site ^ site)
	{
		/*
		** Dummy control step function.
		** To generate Project Library's control step item, and let techFlow3 user to drag into the test recipes editor.
		** Only applicable for techFlow3 user (using test recipes editor).
		** It will link to the all-in-one generic Test Method --> seq_TestMethod()
		*/

		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Control Step: VnaFetch
	**	----------------------------------------------------------------------------------------------------
	*/
#pragma region ".xml file -> Control Step -> VnaFetch"

	/// <summary> VnaFetch
	/// <list type="ControlStep" name="TestLib_ControlStep_VnaFetch" category="VnaFetch" group="Items" conditiontype="nosplit" methodname="seq_TestMethod">
	/// <item attribute="name">VnaFetch</item>
	/// <item attribute="displayas">VnaFetch</item>
	/// <item attribute="description">The is 'VnaFetch' item, which is to configure vna trace setting and then fetch data.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasurePortPair</item>
	/// <item attribute="description">Specifies the mpex port pair to perform the measurement. The alias must exist in the resource planner, and the port alias must follow the label on the mpex hardware. The group pair must exist in the mapping file as well.</item>
	/// <item attribute="value">OUT1,OUT17</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TraceCount</item>
	/// <item attribute="description">Specifies the total trace count to activate in the target channel. The trace count must match with the 'TraceMeasurementFormat' setting.</item>
	/// <item attribute="value">4</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TraceMeasurementFormat</item>
	/// <item attribute="description">Specifies the measurement parameter and format for each trace.</item>
	/// <item attribute="value">S11/LogMag,S21/LogMag,S12/LogMag,S22/LogMag</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">AveragingSetting</item>
	/// <item attribute="description">To enable averaging on the target channel. | Specifies the averaging factor.</item>
	/// <item attribute="value">AveOff/10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/*/// <list type="StepCondition">
	/// <item attribute="name">ChannelNum</item>
	/// <item attribute="description">Only applicable for Keysight DIRECT Config, S4P1D/S6P1D.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>*/
	/// <list type="StepCondition">
	/// <item attribute="name">SaveSnpData</item>
	/// <item attribute="description">To enable snp data generation for current TestParameter.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>

#pragma endregion 
	int TestProgram::TestLib_ControlStep_VnaFetch(Site ^ site)
	{
		/*
		** Dummy control step function.
		** To generate Project Library's control step item, and let techFlow3 user to drag into the test recipes editor.
		** Only applicable for techFlow3 user (using test recipes editor).
		** It will link to the all-in-one generic Test Method --> seq_TestMethod()
		*/

		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma endregion "VNACase ControlStep.xml"

	//Control Item
#pragma region "AM400e & DM400e ControlItem.xml"
	// AM400e DM400e
#pragma region ".xml file -> Control Item -> DCCase_DriveVoltage"
	/// <summary> DCCase_DriveVoltage
	/// <list type="ControlItem" name="CI_DCCase_DriveVoltage" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveVoltage</item>
	/// <item attribute="displayas">DCCase_DriveVoltage</item>
	/// <item attribute="description">Configures the Voltage Level (DVCI) for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DriveVoltage</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Force</item>
	/// <item attribute="description">Specifies the voltage level in volts (V).</item>
	/// <item attribute="value">3.3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DCCase_DriveVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DCCase_DriveCurrent"
	/// <summary> DCCase_DriveCurrent
	/// <list type="ControlItem" name="CI_DCCase_DriveCurrent" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveCurrent</item>
	/// <item attribute="displayas">DCCase_DriveCurrent</item>
	/// <item attribute="description">Configures the Current Level (DVCI) for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DriveCurrent</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Force</item>
	/// <item attribute="description">Specifies the drive current in amps (A).</item>
	/// <item attribute="value">100</item>
	/// <item attribute="prefix">Micro</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DCCase_DriveCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> ClampVoltage"
	/// <summary> DCCase_ClampVoltage
	/// <list type="ControlItem" name="CI_DCCase_ClampVoltage" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ClampVoltage</item>
	/// <item attribute="displayas">DCCase_ClampVoltage</item>
	/// <item attribute="description">Configures the Clamp Voltage Level for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ClampVoltage</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Clamp</item>
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
	int TestProgram::CI_DCCase_ClampVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DCCase_ClampCurrent"
	/// <summary> DCCase_ClampCurrent
	/// <list type="ControlItem" name="CI_DCCase_ClampCurrent" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ClampCurrent</item>
	/// <item attribute="displayas">DCCase_ClampCurrent</item>
	/// <item attribute="description">Configures the Clamp Level for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ClampCurrent</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Clamp</item>
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
	int TestProgram::CI_DCCase_ClampCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> SetNPLC"
	/// <summary> DCCase_SetNPLC
	/// <list type="ControlItem" name="CI_DCCase_SetNPLC" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_SetNPLC</item>
	/// <item attribute="displayas">DCCase_SetNPLC</item>
	/// <item attribute="description">Configures the NPLC for the specified PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_SetNPLC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">NPLC</item>
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
	int TestProgram::CI_DCCase_SetNPLC(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> SetPinOnOff"
	///	<summary>DCCase_SetPinOnOff
	/// <list type="ControlItem" name="CI_DCCase_SetPinOnOff" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_SetPinOnOff</item>
	/// <item attribute="displayas">DCCase_SetPinOnOff</item>
	/// <item attribute="description">Turn On or Off on the specified PinAlias. Value 1 = Turn On PinAlias; Value 0 = Turn Off PinAlias. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_SetPinOnOff</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinOn</item>
	/// <item attribute="description">Configures the SMU &amp; DM output switch status. Mode0(Turn OFF), Mode1(Turn ON)</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DCCase_SetPinOnOff(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma region ".xml file -> Control Item -> ConfigureTriggerEdgeLevel"
	/// <summary>DCCase_ConfigureTriggerEdgeLevel
	/// <list type="ControlItem" name="CI_DCCase_ConfigureTriggerEdgeLevel" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_ConfigureTriggerEdgeLevel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> ConfigureTriggerEdgeLevelExtra"
	/// <summary>DCCase_ConfigureTriggerEdgeLevelExtra
	/// <list type="ControlItem" name="CI_DCCase_AMConfigureTriggerEdgeLevelExtra" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="description">Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ConfigureTriggerEdgeLevelExtra</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_ConfigureTriggerEdgeLevelExtra(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

	// AM400e DM400e CM400e
#pragma region ".xml file -> Control Item -> MapTriggerIntToTriggerOut"
	/// <summary>DCCase_ConfigureTriggerEdgeLevel
	/// <list type="ControlItem" name="CI_DCCase_MapTriggerIntToTriggerOut" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_MapTriggerIntToTriggerOut</item>
	/// <item attribute="displayas">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Connect 2 trigger lines together. Support AM430e, AM450e, AM451e, AM471e, DM483e, CM400e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_ConfigureTriggerEdgeLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_MapTriggerIntToTriggerOut(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DriveSoftwareTrigger"
	/// <summary>DCCase_DriveSoftwareTrigger
	/// <list type="ControlItem" name="CI_DCCase_DriveSoftwareTrigger" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DriveSoftwareTrigger</item>
	/// <item attribute="displayas">DCCase_DriveSoftwareTrigger</item>
	/// <item attribute="description">Drives software trigger immediately. Support AM430e, AM450e, AM451e, AM471e, DM483e, CM401e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DriveSoftwareTrigger</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">AM430e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Select</item>
	/// <item attribute="description">Specifies to which software trigger to drive. Software trigger lines are digital signals coming from the on-board FPGA processor. There are four software triggers to choose from.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PulseWidth</item>
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
	int TestProgram::CI_DCCase_DriveSoftwareTrigger(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma region ".xml file -> Control Item -> WaitSecond"
	/// <summary> DCCase_WaitSecond
	/// <list type="ControlItem" name="CI_DCCase_WaitSecond" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_WaitSecond</item>
	/// <item attribute="displayas">DCCase_WaitSecond</item>
	/// <item attribute="description"></item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_WaitSecond</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Delay</item>
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
	int TestProgram::CI_DCCase_WaitSecond(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma endregion

#pragma region "AM400e ControlItem.xml"

#pragma region ".xml file -> Control Item -> AMConfigureInputTriggerSelect"
	/// <summary>DCCase_AMConfigureInputTriggerSelect
	/// <list type="ControlItem" name="CI_DCCase_AMConfigureInputTriggerSelect" category="DCCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_ConfigureInputTriggerSelect</item>
	/// <item attribute="displayas">DCCase_ConfigureInputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger input to be used for operations such as AcquireMultiple() and AcquireArray(). Upon power-up nothing is selected for the triggerInput. Support AM430e, AM450e, AM451e, AM471e, DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureInputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_AMConfigureInputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> AMConfigureSMUOutputTriggerPulseWidth"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerPulseWidth
	/// <list type="ControlItem" name="CI_DCCase_AMConfigureSMUOutputTriggerPulseWidth" category="AMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="description">Configures the pulse width of trigger output signal.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureSMUOutputTriggerPulseWidth</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_AMConfigureSMUOutputTriggerPulseWidth(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> AMConfigureSMUOutputTriggerDuringSource"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerDuringSource
	/// <list type="ControlItem" name="CI_DCCase_AMConfigureSMUOutputTriggerDuringSource" category="AMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerDuringSource</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerDuringSource</item>
	/// <item attribute="description">Configures when trigger signal is generated.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureSMUOutputTriggerDuringSource</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Level</item>
	/// <item attribute="description">Specifies the threshold level of the channel where a trigger output is generated when this threshold level is hit, depending on edgeSetting.</item>
	/// <item attribute="value">0.7</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Range</item>
	/// <item attribute="description">Specifies the range of the threshold level.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Mode</item>
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
	int TestProgram::CI_DCCase_AMConfigureSMUOutputTriggerDuringSource(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> AMConfigureSMUOutputTriggerMode"
	/// <summary>DCCase_AMConfigureSMUOutputTriggerMode
	/// <list type="ControlItem" name="CI_DCCase_AMConfigureSMUOutputTriggerMode" category="AMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureSMUOutputTriggerMode</item>
	/// <item attribute="displayas">DCCase_AMConfigureSMUOutputTriggerMode</item>
	/// <item attribute="description">Configures when a trigger output signal is generated.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureSMUOutputTriggerMode</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_AMConfigureSMUOutputTriggerMode(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> AMConfigureOutputTriggerSelect"
	/// <summary>DCCase_AMConfigureOutputTriggerSelect
	/// <list type="ControlItem" name="CI_DCCase_AMConfigureOutputTriggerSelect" category="AMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMConfigureOutputTriggerSelect</item>
	/// <item attribute="displayas">DCCase_AMConfigureOutputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger output to be used Upon power-up nothing is selected for the triggerInput. Support AM430e, AM450e, AM451e, AM471e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMConfigureOutputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
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
	int TestProgram::CI_DCCase_AMConfigureOutputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "DM400e ControlItem.xml"

#pragma region ".xml file -> Control Item -> DMConfigurePinToVector"
	/// <summary>DMCase_DMConfigurePinToVector
	/// <list type="ControlItem" name="CI_DMCase_DMConfigurePinToVector" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to Vector. Configure the PinAlias’s level setting. Configure the PinAlias’s attribute of pin electronics. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigurePinToVector</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DPinLevelSet</item>
	/// <item attribute="description">Retrieve VIH_0, VIL_0, VOH_0, VOL_0, IOH_0, IOL_0, VCH_0, VCL_0, VTERM_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PEAttSet</item>
	/// <item attribute="description">Retrieve InputTermEnable_0, HVEnable_0, ActiveLoadEnable_0, DifferentialComparatorEnable_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMConfigurePinToVector(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMConfigurePinToPMU"
	/// <summary>DMCase_DMConfigurePinToPMU
	/// <list type="ControlItem" name="CI_DMCase_DMConfigurePinToPMU" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToPMU</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToPMU</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to PMU. Configure the PinAlias’s configuration to DVCI or DICV. Configure the PinAlias’sense to Local or Remote. Configure the PinAlias to Clamp Current or Clamp Voltage. Configure the PinAlias to Drive Voltage or Drive Current. Configure the PinAlias’s NPLC. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigurePinToPMU</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureMode</item>
	/// <item attribute="description">0: DVCI, 1:DICV</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SenseMode</item>
	/// <item attribute="description">0: Local, 1: Remote</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Compliance</item>
	/// <item attribute="description">Clamp Voltage value (if set to DICV), Clamp Current value (if set to DVCI)</item>
	/// <item attribute="value">200</item>
	/// <item attribute="prefix">Micro</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DriveValue</item>
	/// <item attribute="description">Drive Current value (if set to DICV) or Drive Voltage value (if set to DVCI)</item>
	/// <item attribute="value">0.1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>	
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Nplc</item>
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
	int TestProgram::CI_DMCase_DMConfigurePinToPMU(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMConfigurePinToDIO"
	/// <summary>DMCase_DMConfigurePinToDIO
	/// <list type="ControlItem" name="CI_DMCase_DMConfigurePinToDIO" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigurePinToDIO</item>
	/// <item attribute="displayas">DMCase_DMConfigurePinToDIO</item>
	/// <item attribute="description">Configure the PinAlias’s operation mode to DIO. Configure the PinAlias’s level setting. Configure the PinAlias’s to be input or output. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigurePinToDIO</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">SCLK</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DPinLevelSet</item>
	/// <item attribute="description">Retrieve InputTermEnable_0, HVEnable_0, ActiveLoadEnable_0, DifferentialComparatorEnable_0 values from Load phase.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinDirection</item>
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
	int TestProgram::CI_DMCase_DMConfigurePinToDIO(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMLoadVectorFile"
	/// <summary>DMCase_DMLoadVectorFile
	/// <list type="ControlItem" name="CI_DMCase_DMLoadVectorFile" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMLoadVectorFile</item>
	/// <item attribute="displayas">DMCase_DMLoadVectorFile</item>
	/// <item attribute="description">Loads the vectors to the device specified in the vector file. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMLoadVectorFile</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
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
	int TestProgram::CI_DMCase_DMLoadVectorFile(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> WriteVector"
	/// <summary>DMCase_WriteVector
	/// <list type="ControlItem" name="CI_DMCase_WriteVector" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_WriteVector</item>
	/// <item attribute="displayas">DMCase_WriteVector</item>
	/// <item attribute="description">Execute the Vector Set. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_WriteVector</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VectorFileName</item>
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
	int TestProgram::CI_DMCase_WriteVector(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMDioModeDrivePin"
	/// <summary>DMCase_DMDioModeDrivePin
	/// <list type="ControlItem" name="CI_DMCase_DMDioModeDrivePin" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMDioModeDrivePin</item>
	/// <item attribute="displayas">DMCase_DMDioModeDrivePin</item>
	/// <item attribute="description">Drive PinAlias’s to 0 (Low) or 1 (High). The high or low value is set according to the MethodName (DMCase_DMConfigurePinToDIO). Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMDioModeDrivePin</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VIO</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Logic</item>
	/// <item attribute="description">Drive logic 0 / 1 for VBIAS PinAlias</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMDioModeDrivePin(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMDriveSoftwareTrigger"
	/// <summary>DMCase_DMDriveSoftwareTrigger
	/// <list type="ControlItem" name="CI_DMCase_DMDriveSoftwareTrigger" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMDriveSoftwareTrigger</item>
	/// <item attribute="displayas">DMCase_DMDriveSoftwareTrigger</item>
	/// <item attribute="description">•	Drives software trigger immediately. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMDriveSoftwareTrigger</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Select</item>
	/// <item attribute="description">Specifies to which software trigger to drive. Software trigger lines are digital signals coming from the on-board FPGA processor. There are four software triggers to choose from.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PulseWidth</item>
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
	int TestProgram::CI_DMCase_DMDriveSoftwareTrigger(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMMapTriggerIntToTriggerOut"
	/// <summary>DMCase_DMMapTriggerIntToTriggerOut
	/// <list type="ControlItem" name="CI_DMCase_DMMapTriggerIntToTriggerOut" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMMapTriggerIntToTriggerOut</item>
	/// <item attribute="displayas">DMCase_DMMapTriggerIntToTriggerOut</item>
	/// <item attribute="description">Connect 2 trigger lines together. Support DM483e</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMMapTriggerIntToTriggerOut</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputTerminal</item>
	/// <item attribute="description">Tri-state the trigger source</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">OutputTerminal</item>
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
	int TestProgram::CI_DMCase_DMMapTriggerIntToTriggerOut(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMConfigureTriggerEdgeLevel"
	/// <summary>DMCase_DMConfigureTriggerEdgeLevel
	/// <list type="ControlItem" name="CI_DMCase_DMConfigureTriggerEdgeLevel" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureTriggerEdgeLevel</item>
	/// <item attribute="displayas">DMCase_DMConfigureTriggerEdgeLevel</item>
	/// <item attribute="description">Configures the trigger edge level. Upon power-up nothing is selected for the triggerEnum.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureTriggerEdgeLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerEnum</item>
	/// <item attribute="description">Specifies the triggering source</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Option</item>
	/// <item attribute="description">Specifies the edge of trigger</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IgnoreTriggerCount</item>
	/// <item attribute="description">Specifies the number of trigger count should be ignored before measuring</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMConfigureTriggerEdgeLevel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMConfigureOutputTriggerSelect"
	/// <summary>DMCase_DMConfigureInputTriggerSelect
	/// <list type="ControlItem" name="CI_DMCase_DMConfigureInputTriggerSelect" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureInputTriggerSelect</item>
	/// <item attribute="displayas">DMCase_DMConfigureInputTriggerSelect</item>
	/// <item attribute="description">•	Selects the trigger input to be used for operations such as AcquireMultiple() and AcquireArray().Upon power - up nothing is selected for the triggerInput</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureInputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerInput</item>
	/// <item attribute="description">Tri-state the trigger input</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerDelay</item>
	/// <item attribute="description">Specifies the delay inserted before generating the trigger output.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMConfigureInputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMConfigureOutputTriggerSelect"
	/// <summary>DMCase_DMConfigureOutputTriggerSelect
	/// <list type="ControlItem" name="CI_DMCase_DMConfigureOutputTriggerSelect" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureOutputTriggerSelect</item>
	/// <item attribute="displayas">DMCase_DMConfigureOutputTriggerSelect</item>
	/// <item attribute="description">Selects the trigger output to be used.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureOutputTriggerSelect</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerOutput0</item>
	/// <item attribute="description">Specifies the trigger output signal.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerOutput1</item>
	/// <item attribute="description">Specifies the delay inserted before generating the trigger output.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMConfigureOutputTriggerSelect(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMConfigureReadPin_TriggerOutput"
	/// <summary>DMCase_DMConfigureReadPin_TriggerOutput
	/// <list type="ControlItem" name="CI_DMCase_DMConfigureReadPin_TriggerOutput" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMConfigureReadPin_TriggerOutput</item>
	/// <item attribute="displayas">DMCase_DMConfigureReadPin_TriggerOutput</item>
	/// <item attribute="description">Configure PinAlias as the selected physical trigger line.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMConfigureReadPin_TriggerOutput</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinStatusSelect</item>
	/// <item attribute="description">0: Fire the trigger output when read pin value is logic LOW 1: Fire the trigger output when read pin value is logic HIGH</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMConfigureReadPin_TriggerOutput(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMCase_DMCastDPinLevel"
	/// <summary>DMCase_DMCase_DMCastDPinLevel
	/// <list type="ControlItem" name="CI_DMCase_DMCase_DMCastDPinLevel" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMCase_DMCastDPinLevel</item>
	/// <item attribute="displayas">DMCase_DMCase_DMCastDPinLevel</item>
	/// <item attribute="description">Define Dpin Level of the VIH/VIL/VOH/VOL/IOH/IOL/VCH/VCL/VTERM. The first set of Dpin Level is has no index. User able to define second or more set of Dpin Level with index. Example: VIH, VIH_1, etc.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMCase_DMCastDPinLevel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VIH</item>
	/// <item attribute="description">Specifies the VIH with reference to DPin set</item>
	/// <item attribute="value">1.8</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VIL</item>
	/// <item attribute="description">Specifies the VIL with reference to DPin set</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VOH</item>
	/// <item attribute="description">Specifies the VOH with reference to DPin set</item>
	/// <item attribute="value">0.9</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VOL</item>
	/// <item attribute="description">Specifies the VOL with reference to DPin set</item>
	/// <item attribute="value">0.7</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IOH</item>
	/// <item attribute="description">Specifies the IOH with reference to DPin set</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">IOL</item>
	/// <item attribute="description">Specifies the IOL with reference to DPin set</item>
	/// <item attribute="value">1.8</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">A</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCH</item>
	/// <item attribute="description">Specifies the VCH with reference to DPin set</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VCL</item>
	/// <item attribute="description">Specifies the VCL with reference to DPin set</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VTERM</item>
	/// <item attribute="description">Specifies the VTERM with reference to DPin set</item>
	/// <item attribute="value">0.9</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">V</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMCastDPinLevel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMCastTimingSetPeriod"
	/// <summary>DMCase_DMCastTimingSetPeriod
	/// <list type="ControlItem" name="CI_DMCase_DMCastTimingSetPeriod" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMCastTimingSetPeriod</item>
	/// <item attribute="displayas">DMCase_DMCastTimingSetPeriod</item>
	/// <item attribute="description">Define the waveforms period of the vector. The first set of Timing Set Period has no index. User able to define second or more set of Timing Set ing index. Example: TimingSetPeriod, TimingSetPeriod_1.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMCastTimingSetPeriod</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TimingSetPeriod</item>
	/// <item attribute="description">Specifies the period of respective timing set</item>
	/// <item attribute="value">26</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMCastTimingSetPeriod(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DMCastPEAttribute"
	/// <summary>DMCase_DMCastPEAttribute
	/// <list type="ControlItem" name="CI_DMCase_DMCastPEAttribute" category="DMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_DMCastPEAttribute</item>
	/// <item attribute="displayas">DMCase_DMCastPEAttribute</item>
	/// <item attribute="description">To enable/disable Input Term/HV/Active Load/Differential Comparator function. The first set of PE Attribute is label as 0. User able to define second or more set of PE Attribute. Example: InputTermEnable_0, HVEnable_0, etc.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_DMCastPEAttribute</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputTermEnable</item>
	/// <item attribute="description">Specifies the input terminal enable</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">HVEnable</item>
	/// <item attribute="description">Specifies the high voltage enable</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ActiveLoadEnable</item>
	/// <item attribute="description">Specifies the active laod enable</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">DifferentialComparatorEnable</item>
	/// <item attribute="description">Specifies the differential comparator enable</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_DMCase_DMCastPEAttribute(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "IOM400e ControlItem.xml"

#pragma region ".xml file -> Control Item -> DIODrivePin"
	/// <summary>IOMCase_DIODrivePin
	/// <list type="ControlItem" name="CI_IOMCase_DIODrivePin" category="IOMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIODrivePin</item>
	/// <item attribute="displayas">IOMCase_DIODrivePin</item>
	/// <item attribute="description">Configure the PinAlias to 1 (High) or 0 (Low) according to the MethodName (IOMCase_DIOSetModuleVIO)</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIODrivePin</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinAlias</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">VCC</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinLogic</item>
	/// <item attribute="description">Specifies the logic for specific PinAlias.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_IOMCase_DIODrivePin(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DIODrivePort"
	/// <summary>IOMCase_DIODrivePort
	/// <list type="ControlItem" name="CI_IOMCase_DIODrivePort" category="IOMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIODrivePort</item>
	/// <item attribute="displayas">IOMCase_DIODrivePort</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIODrivePort</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortAlias</item>
	/// <item attribute="description">Specifies the Port.</item>
	/// <item attribute="value">Port1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortLogic</item>
	/// <item attribute="description">Specifies the logic for specific Port.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_IOMCase_DIODrivePort(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DIOSetModuleVIO"
	/// <summary>IOMCase_DIOSetModuleVIO
	/// <list type="ControlItem" name="CI_IOMCase_DIOSetModuleVIO" category="IOMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIOSetModuleVIO</item>
	/// <item attribute="displayas">IOMCase_DIOSetModuleVIO</item>
	/// <item attribute="description">Configure ModuleAlias’s Voltage Level to 0 (3.3V), 1 (5V), 2 (External Input)</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIOSetModuleVIO</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">IOM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleVioMode</item>
	/// <item attribute="description">Set the ModuleAlias to specified Voltage Level</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_IOMCase_DIOSetModuleVIO(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> DIOSetPortDirection"
	/// <summary>IOMCase_DIOSetPortDirection
	/// <list type="ControlItem" name="CI_IOMCase_DIOSetPortDirection" category="IOMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">IOMCase_DIOSetPortDirection</item>
	/// <item attribute="displayas">IOMCase_DIOSetPortDirection</item>
	/// <item attribute="description">Configure the PortAlias’s port direction</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">IOMCase_DIOSetPortDirection</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortAlias</item>
	/// <item attribute="description">Specifies the Port.</item>
	/// <item attribute="value">Port1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortDirection</item>
	/// <item attribute="description">Set the PortAlias to specified direction.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_IOMCase_DIOSetPortDirection(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "CM400e ControlItem.xml"

#pragma region ".xml file -> Control Item -> CMDrivePin"
	/// <summary>CMCase_CMDrivePin
	/// <list type="ControlItem" name="CI_CMCase_CMDrivePin" category="CMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMDrivePin</item>
	/// <item attribute="displayas">CMCase_CMDrivePin</item>
	/// <item attribute="description">Configure the PinAlias to 1 (High) or 0 (Low) according to the MethodName (CMCase_CMSetModuleVIO)</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMDrivePin</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Pin</item>
	/// <item attribute="description">Specifies the Pin.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PinLogic</item>
	/// <item attribute="description">Specifies the logic for specific PinAlias.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_CMCase_CMDrivePin(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> CMDrivePort"
	/// <summary>CMCase_CMDrivePort
	/// <list type="ControlItem" name="CI_CMCase_CMDrivePort" category="CMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMDrivePort</item>
	/// <item attribute="displayas">CMCase_CMDrivePort</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMDrivePort</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortAlias</item>
	/// <item attribute="description">Specifies the Port.</item>
	/// <item attribute="value">Port1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortLogic</item>
	/// <item attribute="description">Specifies the logic for specific Port.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_CMCase_CMDrivePort(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> CMConfigurePXES2780_TriggerBus"
	/// <summary>CMCase_CMConfigurePXES2780_TriggerBus
	/// <list type="ControlItem" name="CI_CMCase_CMConfigurePXES2780_TriggerBus" category="CMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMConfigurePXES2780_TriggerBus</item>
	/// <item attribute="displayas">CMCase_CMConfigurePXES2780_TriggerBus</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMConfigurePXES2780_TriggerBus</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerBus</item>
	/// <item attribute="description">Specifies the TriggerBus.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerEnable</item>
	/// <item attribute="description">Specifies the TriggerEnable.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TriggerDirection</item>
	/// <item attribute="description">Specifies the TriggerDirection.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_CMCase_CMConfigurePXES2780_TriggerBus(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> CMSetPortDirection"
	/// <summary>CMCase_CMSetPortDirection
	/// <list type="ControlItem" name="CI_CMCase_CMSetPortDirection" category="CMCase" group="DC_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">CMCase_CMSetPortDirection</item>
	/// <item attribute="displayas">CMCase_CMSetPortDirection</item>
	/// <item attribute="description">Drive the PortAlias to specified Digital Value.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">CMCase_CMSetPortDirection</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias.</item>
	/// <item attribute="value">CM1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PortLogic</item>
	/// <item attribute="description">Specifies the logic for specific Port.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_CMCase_CMSetPortDirection(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "RFCase ControlItem.xml"

#pragma region ".xml file -> Control Item -> RF SourcePower"
	/// <summary>RFCase_SourcePower
	/// <list type="ControlItem" name="CI_RFCase_SourcePower" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePower</item>
	/// <item attribute="displayas">RFCase_SourcePower</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourcePower</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal frequency.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external output attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SourcePower(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SourcePowerFast"
	/// <summary>RFCase_SourcePowerFast
	/// <list type="ControlItem" name="CI_RFCase_SourcePowerFast" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePowerFast</item>
	/// <item attribute="displayas">RFCase_SourcePowerFast</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourcePowerFast</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal frequency.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external output attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SourcePowerFast(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SourcePowerLow"
	/// <summary>RFCase_SourcePowerLow
	/// <list type="ControlItem" name="CI_RFCase_SourcePowerLow" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourcePowerLow</item>
	/// <item attribute="displayas">RFCase_SourcePowerLow</item>
	/// <item attribute="description">Configure RF PinAlias to source an RF Signal at the specified power level and frequency.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourcePowerLow</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SourcePowerLow(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SourceTwoTone"
	/// <summary>RFCase_SourceTwoTone
	/// <list type="ControlItem" name="CI_RFCase_SourceTwoTone" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SourceTwoTone</item>
	/// <item attribute="displayas">RFCase_SourceTwoTone</item>
	/// <item attribute="description">Source two tone RF signals with specified power level and frequency respectively</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SourceTwoTone</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq0</item>
	/// <item attribute="description">Specifies the RF signal frequency to port A.</item>
	/// <item attribute="value">1999.5</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin0</item>
	/// <item attribute="description">Specifies the RF signal power to port A.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq1</item>
	/// <item attribute="description">Specifies the RF signal frequency to port B.</item>
	/// <item attribute="value">2000.5</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin1</item>
	/// <item attribute="description">Specifies the RF signal power to port B.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem_0</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputBoardLossItem_1</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. (Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_IN</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SourceTwoTone(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF IsolateChannel"
	/// <summary>RFCase_IsolateChannel
	/// <list type="ControlItem" name="CI_RFCase_IsolateChannel" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_IsolateChannel</item>
	/// <item attribute="displayas">RFCase_IsolateChannel</item>
	/// <item attribute="description">Configure RF PinAlias to the Isolate Mode.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_IsolateChannel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Channel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_IsolateChannel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF StartModulation"
	/// <summary>RFCase_StartModulation
	/// <list type="ControlItem" name="CI_RFCase_StartModulation" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_StartModulation</item>
	/// <item attribute="displayas">RFCase_StartModulation</item>
	/// <item attribute="description">Start modulation on the signal generator.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_StartModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModulationFile</item>
	/// <item attribute="description">Specifies the modulation file to be executed.</item>
	/// <item attribute="value">2Tones_1MHz.awf</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PlayBackMode</item>
	/// <item attribute="description">Specifies the playback mode of ARB.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_StartModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF StopModulation"
	/// <summary>RFCase_StopModulation
	/// <list type="ControlItem" name="CI_RFCase_StopModulation" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_StopModulation</item>
	/// <item attribute="displayas">RFCase_StopModulation</item>
	/// <item attribute="description">Disable IQ modulation on the signal generator.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_StopModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_StopModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SetSourceTriggerRouting"
	/// <summary>RFCase_SetSourceTriggerRouting
	/// <list type="ControlItem" name="CI_RFCase_SetSourceTriggerRouting" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetSourceTriggerRouting</item>
	/// <item attribute="displayas">RFCase_SetSourceTriggerRouting</item>
	/// <item attribute="description">Setup Source Trigger Routing of the module.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetSourceTriggerRouting</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigIn</item>
	/// <item attribute="description">Specify the triggerIn of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigOut</item>
	/// <item attribute="description">Specifies the triggerOut of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SetSourceTriggerRouting(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SetSourceTriggerIn"
	/// <summary>RFCase_SetSourceTriggerIn
	/// <list type="ControlItem" name="CI_RFCase_SetSourceTriggerIn" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetSourceTriggerIn</item>
	/// <item attribute="displayas">RFCase_SetSourceTriggerIn</item>
	/// <item attribute="description">Setup Source TriggerIn of the module.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetSourceTriggerIn</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specify the trigSource of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigPolarity</item>
	/// <item attribute="description">Specifies the trigPolarity of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigDelay</item>
	/// <item attribute="description">Specifies the trigDelay of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SetSourceTriggerIn(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SetSourceTriggerOut"
	/// <summary>RFCase_SetSourceTriggerOut
	/// <list type="ControlItem" name="CI_RFCase_SetSourceTriggerIn" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetSourceTriggerOut</item>
	/// <item attribute="displayas">RFCase_SetSourceTriggerOut</item>
	/// <item attribute="description">Setup Source TriggerOut of the module.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetSourceTriggerOut</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigDestination</item>
	/// <item attribute="description">Specify the trigDest of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigOption</item>
	/// <item attribute="description">Specifies the trigOption of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SetSourceTriggerOut(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SetMeasureTriggerRouting"
	/// <summary>RFCase_SetMeasureTriggerRouting
	/// <list type="ControlItem" name="CI_RFCase_SetMeasureTriggerRouting" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetMeasureTriggerRouting</item>
	/// <item attribute="displayas">RFCase_SetMeasureTriggerRouting</item>
	/// <item attribute="description">Setup Measure Trigger Routing of the module.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetMeasureTriggerRouting</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigIn</item>
	/// <item attribute="description">Specify the triggerIn of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigOut</item>
	/// <item attribute="description">Specifies the triggerOut of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SetMeasureTriggerRouting(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SetMeasureTriggerIn"
	/// <summary>RFCase_SetMeasureTriggerIn
	/// <list type="ControlItem" name="CI_RFCase_SetMeasureTriggerIn" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SetMeasureTriggerIn</item>
	/// <item attribute="displayas">RFCase_SetMeasureTriggerIn</item>
	/// <item attribute="description">Setup Measure Trigger Routing of the module.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SetMeasureTriggerIn</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Enable</item>
	/// <item attribute="description">Specifies enable or disable of the module.</item>
	/// <item attribute="value">False</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigSource</item>
	/// <item attribute="description">Specify the trigSource of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigPolarity</item>
	/// <item attribute="description">Specifies the trigPolarity of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TrigDelay</item>
	/// <item attribute="description">Specifies the trigDelay of the module.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SetMeasureTriggerIn(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF RunSourceAlignment"
	/// <summary>RFCase_RunSourceAlignment
	/// <list type="ControlItem" name="CI_RFCase_RunSourceAlignment" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_RunSourceAlignment</item>
	/// <item attribute="displayas">RFCase_RunSourceAlignment</item>
	/// <item attribute="description">Perform Source Alignement</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_RunSourceAlignment</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_RunSourceAlignment(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF LoadModulation"
	/// <summary>RFCase_LoadModulation
	/// <list type="ControlItem" name="CI_RFCase_LoadModulation" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_LoadModulation</item>
	/// <item attribute="displayas">RFCase_LoadModulation</item>
	/// <item attribute="description">Load the modulation file.</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_LoadModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModulationFile</item>
	/// <item attribute="description">Specifies the modulation file to be loaded to tester.</item>
	/// <item attribute="value">2Tones_1MHz.awf</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_LoadModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF WlanInit"
	/// <summary>RFCase_WlanInit
	/// <list type="ControlItem" name="CI_RFCase_WlanInit" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WlanInit</item>
	/// <item attribute="displayas">RFCase_WlanInit</item>
	/// <item attribute="description">Wlan initialization</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WlanInit</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasVSG</item>
	/// <item attribute="description">Specifies the Module Alias of the signal generator </item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasVSA</item>
	/// <item attribute="description">Specifies the Module Alias of the signal analyzer </item>
	/// <item attribute="value">VSA1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">measureOption_ACAX</item>
	/// <item attribute="description">Specifies enable or disable the measure option of 11ac &amp; 11ax </item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">measureOption_ABGN</item>
	/// <item attribute="description">Specifies enable or disable the measure option of 11abgn</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_WlanInit(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF EvmMeasurementSetup"
	/// <summary>RFCase_EvmMeasurementSetup
	/// <list type="ControlItem" name="CI_RFCase_EvmMeasurementSetup" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_EvmMeasurementSetup</item>
	/// <item attribute="displayas">RFCase_EvmMeasurementSetup</item>
	/// <item attribute="description">Evm Measurement Setup</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_EvmMeasurementSetup</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">WlanModulationStandard</item>
	/// <item attribute="description">Specifies Evm Wlan Modulation Standard.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_0</item>
	/// <item attribute="description">(Optional)Specifies AcqTime</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_1</item>
	/// <item attribute="description">(Optional)Specifies viewConstellation</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_2</item>
	/// <item attribute="description">(Optional)Specifies mcsIndex</item>
	/// <item attribute="value">8</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_3</item>
	/// <item attribute="description">(Optional)Specifies PSDULength</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_4</item>
	/// <item attribute="description">(Optional)Specifies autoConfigSetup</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_EvmMeasurementSetup(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF SemMeasurementSetup"
	/// <summary>RFCase_SemMeasurementSetup
	/// <list type="ControlItem" name="CI_RFCase_SemMeasurementSetup" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_SemMeasurementSetup</item>
	/// <item attribute="displayas">RFCase_SemMeasurementSetup</item>
	/// <item attribute="description">Sem Measurement Setup</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_SemMeasurementSetup</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">WlanModulationStandard</item>
	/// <item attribute="description">Specifies Evm Wlan Modulation Standard.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SemAvg</item>
	/// <item attribute="description">Specifies the sem average of the module.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_0</item>
	/// <item attribute="description">(Optional)Specifies AcqTime</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Setting_1</item>
	/// <item attribute="description">(Optional)Specifies viewSpectrum</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_SemMeasurementSetup(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF MeasureSetup"
	/// <summary>RFCase_MeasureSetup
	/// <list type="ControlItem" name="CI_RFCase_MeasureSetup" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSetup</item>
	/// <item attribute="displayas">RFCase_MeasureSetup</item>
	/// <item attribute="description">CW RF Measurement Setup</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSetup</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies MeasureChannel</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the MeasurePower</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies MeasureFreq</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional)Specifies MeasureDelay</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies FilterOption</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_MeasureSetup(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF MeasureSetupIQ"
	/// <summary>RFCase_MeasureSetupIQ
	/// <list type="ControlItem" name="CI_RFCase_MeasureSetupIQ" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSetupIQ</item>
	/// <item attribute="displayas">RFCase_MeasureSetupIQ</item>
	/// <item attribute="description">CW RF Measurement Setup IQ</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSetupIQ</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies MeasureChannel</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the MeasurePower</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies MeasureFreq</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies SampleRate</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies SampleSize</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional)Specifies MeasureDelay</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies FilterOption</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_MeasureSetupIQ(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF TriggerSigenStartModulation"
	/// <summary>RFCase_TriggerSigenStartModulation
	/// <list type="ControlItem" name="CI_RFCase_TriggerSigenStartModulation" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_TriggerSigenStartModulation</item>
	/// <item attribute="displayas">RFCase_TriggerSigenStartModulation</item>
	/// <item attribute="description">RF trigger signal generator to start sourcing modulation</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_TriggerSigenStartModulation</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasSigen</item>
	/// <item attribute="description">Specifies the signal generator module alias</item>
	/// <item attribute="value">VSG1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModulationFile</item>
	/// <item attribute="description">Specifies the modulation file to be executed</item>
	/// <item attribute="value">WLAN_11AC_80MHz_MCS9.awf</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">PlayBackMode</item>
	/// <item attribute="description">Specifies the playback mode; 0 : Single, 1 : Continuous</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">VectorFileName</item>
	/// <item attribute="description">Specifies the vector file name to be executed</item>
	/// <item attribute="value">DynamicEVM</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">ModuleAliasDM</item>
	/// <item attribute="description">Specifies the alias of the target DM</item>
	/// <item attribute="value">DM483E</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_TriggerSigenStartModulation(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF WolferInit"
	/// <summary>RFCase_WolferInit
	/// <list type="ControlItem" name="CI_RFCase_WolferInit" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WolferInit</item>
	/// <item attribute="displayas">RFCase_WolferInit</item>
	/// <item attribute="description">Wolfer initialization</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WolferInit</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_WolferInit(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF WolferSelectPath"
	/// <summary>RFCase_WolferSelectPath
	/// <list type="ControlItem" name="CI_RFCase_WolferSelectPath" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WolferSelectPath</item>
	/// <item attribute="displayas">RFCase_WolferSelectPath</item>
	/// <item attribute="description">Wolfer path selection</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WolferSelectPath</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal source frequency.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the RF signal measure frequency.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SelectTxPath</item>
	/// <item attribute="description">Specifies the TX path (TX1 only)</item>
	/// <item attribute="value">TX1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SelectRxPath</item>
	/// <item attribute="description">Specifies the RX path (RX1 – RX8)</item>
	/// <item attribute="value">RX1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TxBypassOn</item>
	/// <item attribute="description">(Optional)Specifies the bypass mode for TX</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">TxInternalPath</item>
	/// <item attribute="description">(Optional)Specifies the TX internal path(T1 – T4)</item>
	/// <item attribute="value">T1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">RxInternalPath</item>
	/// <item attribute="description">(Optional)Specifies the RX internal path(R1 – R24)</item>
	/// <item attribute="value">R1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_WolferSelectPath(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Control Item -> RF WolferSourcePower"
	/// <summary>RFCase_WolferSourcePower
	/// <list type="ControlItem" name="CI_RFCase_WolferSourcePower" category="RFCase" group="RF_ControlItem" conditiontype="splitbycomma" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WolferSourcePower</item>
	/// <item attribute="displayas">RFCase_WolferSourcePower</item>
	/// <item attribute="description">Source power configuration of wolfer</item>
	/// <list type="StepCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WolferSourcePower</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceFreq</item>
	/// <item attribute="description">Specifies the RF signal source frequency.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">-30</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="StepCondition">
	/// <item attribute="name">Coupler_CH</item>
	/// <item attribute="description">(Optional)Specifies the coupler channel</item>
	/// <item attribute="value">RF2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::CI_RFCase_WolferSourcePower(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

	//Test Step
#pragma region "AM400e & DM400e Test Step.xml"

#pragma region ".xml file -> Test Item -> TM OS"
	/// <summary> DCCase_OS
	/// <list type="TestItem" name="TM_DCCase_OS" category="DcTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_OS</item>
	/// <item attribute="displayas">DCCase_OS</item>
	/// <item attribute="description">Measures the current level for the specified pin alias. The test function is executed and the result is returned to the respective test parameter.</item>
	/// <list type="TestParameter" name="TM_OS" category="DcTest" group="DC_Items">
	/// <item attribute="name">DCCase_OS</item>
	/// <item attribute="displayas">DCCase_OS</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_OS</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinMeasure</item>
	/// <item attribute="description">Specifies the PinMeasure.</item>
	/// <item attribute="value">VCC1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DriveCurrent</item>
	/// <item attribute="description">Specifies the Current Level.</item>
	/// <item attribute="value">-100</item>
	/// <item attribute="prefix">Micro</item>
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
	/// <item attribute="name">Delay</item>
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
	int TestProgram::TM_DCCase_OS(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureCurrent"
	/// <summary> DCCase_MeasureCurrent
	/// <list type="TestItem" name="DCCase_MeasureCurrent" category="DcTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_MeasureCurrent</item>
	/// <item attribute="displayas">DCCase_MeasureCurrent</item>
	/// <item attribute="description">Measures the current level for the specified pin alias. The test function is executed and the result is returned to the respective test parameter.</item>
	/// <list type="TestParameter" name="TM_DCCase_MeasureCurrent" category="DcTest" group="DC_Items">
	/// <item attribute="name">DCCase_MeasureCurrent</item>
	/// <item attribute="displayas">DCCase_MeasureCurrent</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_MeasureCurrent</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinMeasure</item>
	/// <item attribute="description">Specifies the PinMeasure.</item>
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
	int TestProgram::TM_DCCase_MeasureCurrent(Site^ site)
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
	/// <list type="TestItem" name="TM_MeasureVoltage" category="AMTest" group="AM_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCTest_MeasureVoltage</item>
	/// <item attribute="displayas">DCTest_MeasureVoltage</item>
	/// <item attribute="description">Measures the voltage level for the specified pin alias. The test function is executed and the result is returned to the respective test parameter.</item>
	/// <list type="TestParameter" name="TM_MeasureVoltage" category="AMTest" group="AM_Items">
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_MeasureVoltage</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinMeasure</item>
	/// <item attribute="description">Specifies the PinMeasure.</item>
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
	int TestProgram::TM_DCCase_MeasureVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureBurstCurrent"
	/// <summary> DCCase_AMMeasureBurstCurrent
	/// <list type="TestItem" name="TM_DCCase_AMMeasureBurstCurrent" category="AMTest" group="AM_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMMeasureBurstCurrent</item>
	/// <item attribute="displayas">DCCase_MeasureBurstCurrent</item>
	/// <item attribute="description">Measure the Burst Current Level for the specified PinAlias.</item>
	/// <list type="TestParameter" name="TM_DCCase_AMMeasureBurstCurrent" category="AMTest" group="AM_Items">
	/// <item attribute="name">DCCase_AMMeasureBurstCurrent</item>
	/// <item attribute="displayas">DCCase_AMMeasureBurstCurrent</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMMeasureBurstCurrent</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinMeasure</item>
	/// <item attribute="description">Specifies the PinMeasure.</item>
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
	int TestProgram::TM_DCCase_AMMeasureBurstCurrent(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureBurstVoltage"
	/// <summary> DCCase_AMMeasureBurstVoltage
	/// <list type="TestItem" name="TM_DCCase_AMMeasureBurstVoltage" category="AMTest" group="AM_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_AMMeasureBurstVoltage</item>
	/// <item attribute="displayas">DCCase_AMMeasureBurstVoltage</item>
	/// <item attribute="description">Measure the Burst Voltage Level for the specified PinAlias.</item>
	/// <list type="TestParameter" name="TM_DCCase_AMMeasureBurstVoltage" category="AMTest" group="AM_Items">
	/// <item attribute="name">DCCase_AMMeasureBurstVoltage</item>
	/// <item attribute="displayas">DCCase_AMMeasureBurstVoltage</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_AMMeasureBurstVoltage</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PinMeasure</item>
	/// <item attribute="description">Specifies the PinMeasure.</item>
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
	int TestProgram::TM_DCCase_AMMeasureBurstVoltage(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM DifferentialResult"
	/// <summary> DCCase_DifferentialResult
	/// <list type="TestItem" name="TM_DCCase_DifferentialResult" category="DcTest" group="DC_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DCCase_DifferentialResult</item>
	/// <item attribute="displayas">DCCase_DifferentialResult</item>
	/// <item attribute="description">Perform post processing on the result returned from the Test Parameters.</item>
	/// <list type="TestParameter" name="TM_DCCase_DifferentialResult" category="DcTest" group="DC_Items">
	/// <item attribute="name">DCCase_DifferentialResult</item>
	/// <item attribute="displayas">DCCase_DifferentialResult</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">0</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DCCase_DifferentialResult</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultKey_a</item>
	/// <item attribute="description">Retrieve result of the Test ItemNaame_Test ParameterName</item>
	/// <item attribute="value">OIP311_F_lo</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultKey_b</item>
	/// <item attribute="description">Retrieve result of the Test ItemName_Test ParameterName</item>
	/// <item attribute="value">OIP311_OIP3_Lo</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Expression</item>
	/// <item attribute="description">Specifies the expression of the result</item>
	/// <item attribute="value">b-(a+1)</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_DCCase_DifferentialResult(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "DM400e Test Step.xml"

#pragma region ".xml file -> Test Item -> TM MIPIReadVector"
	/// <summary> DMCase_MIPIReadVector
	/// <list type="TestItem" name="TM_DMCase_MIPIReadVector" category="DMTest" group="DN_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">DMCase_MIPIReadVector</item>
	/// <item attribute="displayas">DMCase_MIPIReadVector</item>
	/// <item attribute="description">ReadBack every stored bit in the HistoryRam of DM483 (Support for Mipi protocol)</item>
	/// <list type="TestParameter" name="TM_DMCase_MIPIReadVector" category="DMTest" group="DM_Items">
	/// <item attribute="name">DMCase_MIPIReadVector</item>
	/// <item attribute="displayas">DMCase_MIPIReadVector</item>
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
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">DMCase_MIPIReadVector</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">VectorFileName</item>
	/// <item attribute="description">Specifies the Vector Set to be executed.</item>
	/// <item attribute="value">OIP311_F_lo</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ModuleAlias</item>
	/// <item attribute="description">Specifies the module alias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DataPinAlias</item>
	/// <item attribute="description">Specifies the PinAlias</item>
	/// <item attribute="value">SDATA</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ChannelInputDelay</item>
	/// <item attribute="description">Specifies the delay, in seconds.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SweepOperation</item>
	/// <item attribute="description">(Optional)Specifies the Sweep Operation to be True or False</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartChannelInputDelay</item>
	/// <item attribute="description">(Optional, Compulsary if SweepOperation set to True);	Specifies the StartChannelInputDelay value</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopChannelInputDelay</item>
	/// <item attribute="description">(Optional, Compulsary if SweepOperation set to True);	Specifies the StopChannelInputDelay value</item>
	/// <item attribute="value">30</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">IncrementChannelInputDelay</item>
	/// <item attribute="description">(Optional, Compulsary if SweepOperation set to True);	Specifies the IncrementChannelInputDelay value</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_DMCase_MIPIReadVector(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "RFCase Test Step.xml"

#pragma region ".xml file -> Test Item -> TM MeasureChannel"
	/// <summary> RFCase_MeasureChannel
	/// <list type="TestItem" name="RFCase_MeasureChannel" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureChannel</item>
	/// <item attribute="displayas">RFCase_MeasureChannel</item>
	/// <item attribute="description">Perform RF power measurement at the targeted PinAlias.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureChannel" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureChannel</item>
	/// <item attribute="displayas">RFCase_MeasureChannel</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureChannel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file.(Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureChannel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureChannelFast"
	/// <summary> RFCase_MeasureChannelFast
	/// <list type="TestItem" name="TM_RFCase_MeasureChannelFast" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureChannelFast</item>
	/// <item attribute="displayas">RFCase_MeasureChannelFast</item>
	/// <item attribute="description">Perform RF power measurement at the targeted PinAlias.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureChannelFast" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureChannelFast</item>
	/// <item attribute="displayas">RFCase_MeasureChannelFast</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureChannelFast</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file.(Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureChannelFast(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureChannelIQ"
	/// <summary> RFCase_MeasureChannelIQ
	/// <list type="TestItem" name="TM_RFCase_MeasureChannelIQ" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureChannelIQ</item>
	/// <item attribute="displayas">RFCase_MeasureChannelIQ</item>
	/// <item attribute="description">Perform RF power measurement at the targeted PinAlias.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureChannelIQ" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureChannelIQ</item>
	/// <item attribute="displayas">RFCase_MeasureChannelIQ</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureChannelIQ</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies the sample rate.</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies the sample size.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file.(Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureChannelIQ(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureIIP3"
	/// <summary> RFCase_MeasureIIP3
	/// <list type="TestItem" name="TM_RFCase_MeasureIIP3" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureIIP3</item>
	/// <item attribute="displayas">RFCase_MeasureIIP3</item>
	/// <item attribute="description">Perform OIP3 and IIP3 measurement at the targeted pin alias.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureIIP3" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureIIP3</item>
	/// <item attribute="displayas">RFCase_MeasureIIP3</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureIIP3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TwoToneFrequencySpacing</item>
	/// <item attribute="description">Specifies the spacing gap between the 2 frequency.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies the sample rate.</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies the sample size.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem_0</item>
	/// <item attribute="description">(Optional)Specifies the item (IM_Lo) in BoardLoss file.</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem_1</item>
	/// <item attribute="description">(Optional)Specifies the item (F_lo) in BoardLoss file.</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem_2</item>
	/// <item attribute="description">(Optional)Specifies the item (F_Hi) in BoardLoss file</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem_3</item>
	/// <item attribute="description">(Optional)Specifies the item (IM_Hi) in BoardLoss file.</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SweepOperation</item>
	/// <item attribute="description">(Optional)Specifies the Sweep Operation to be True or False</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartSweepFreq</item>
	/// <item attribute="description">(Optional, Compulsary if SweepOperation set to True)Specifies the starting sweep frequency.</item>
	/// <item attribute="value">1998</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopSweepFreq</item>
	/// <item attribute="description">(Optional)Specifies the ending of sweep frequency</item>
	/// <item attribute="value">2002</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">IncrementFreq</item>
	/// <item attribute="description">(Optional)Specifies the increment of sweep frequency.</item>
	/// <item attribute="value">0.01</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureIIP3(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureBurstPower"
	/// <summary> RFCase_MeasureBurstPower
	/// <list type="TestItem" name="TM_RFCase_MeasureBurstPower" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureBurstPower</item>
	/// <item attribute="displayas">RFCase_MeasureBurstPower</item>
	/// <item attribute="description">Measure the RF power at the stated frequency and channel.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureBurstPower" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureBurstPower</item>
	/// <item attribute="displayas">RFCase_MeasureBurstPower</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureBurstPower</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TriggerVectorFileName</item>
	/// <item attribute="description">Specifies the trigger vector file.</item>
	/// <item attribute="value">MB1_LPM_Rise</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InitVectorFileName</item>
	/// <item attribute="description">Specifies the init vector file.</item>
	/// <item attribute="value">MB1_LPM_Init</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DmModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies the sample rate.</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies the sample size.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PeakPercentage</item>
	/// <item attribute="description">Specifies the percentage of the peak to be taken for measurement. Setting this to 0% will return the peak point.</item>
	/// <item attribute="value">100</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">%</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DelayAfterInitVector</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay after init vector.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureBurstPower(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureSwitchingTime"
	/// <summary> RFCase_MeasureSwitchingTime
	/// <list type="TestItem" name="TM_RFCase_MeasureSwitchingTime" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSwitchingTime</item>
	/// <item attribute="displayas">RFCase_MeasureSwitchingTime</item>
	/// <item attribute="description">Measure the rise time or fall time of the RF Signal.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureSwitchingTime" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureSwitchingTime</item>
	/// <item attribute="displayas">RFCase_MeasureSwitchingTime</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSwitchingTime</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TriggerVectorFileName</item>
	/// <item attribute="description">Specifies the trigger vector file.</item>
	/// <item attribute="value">MB1_LPM_Rise</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InitVectorFileName</item>
	/// <item attribute="description">Specifies the init vector file.</item>
	/// <item attribute="value">MB1_LPM_Init</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DmModuleAlias</item>
	/// <item attribute="description">Specifies the ModuleAlias</item>
	/// <item attribute="value">DM483e</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureMode</item>
	/// <item attribute="description">Specifies the MeasureMode to Rise or Fall</item>
	/// <item attribute="value">Fall</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies the sample rate.</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies the sample size.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartCapture</item>
	/// <item attribute="description">(Optional, Default)Specifies the start capture percentage of the RF Signal “On” Level</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopCapture</item>
	/// <item attribute="description">(Optional, Default)Specifies the stop capture percentage of the RF Signal “On” Level</item>
	/// <item attribute="value">90</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DelayAfterInitVector</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay after init vector.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ThresholdUncertainty</item>
	/// <item attribute="description">(Optional, Default)Specifies the threshold uncertainty in dBm at the stop capture.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">DigitizerTriggerDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the trigger delay for the digitizer.This value will be add on to the return result.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">NumberAveragingInit</item>
	/// <item attribute="description">(Optional, Default)Specifies the number of sample to be average out to be the Initial power of the RF Signal.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">NumberAveragingFinal</item>
	/// <item attribute="description">(Optional, Default)Specifies the number of sample to be average out to be the Final power of the RF Signal.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file.</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureSwitchingTime(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureSParam"
	/// <summary> RFCase_MeasureSParam
	/// <list type="TestItem" name="TM_RFCase_MeasureSParam" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSParam</item>
	/// <item attribute="displayas">RFCase_MeasureSParam</item>
	/// <item attribute="description">Perform an S-parameter measurment.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureSParam" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureSParam</item>
	/// <item attribute="displayas">RFCase_MeasureSParam</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSParam</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Channel_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Channel_1</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourcePower</item>
	/// <item attribute="description">Specifies the source power of those specified channel.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">BoardLossItem_0</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file of the Channel_0.</item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">BoardLossItem_1</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file of the Channel_1.</item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ExtAtt_1</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">S11_Re</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureSParam(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM MeasureSParamIQ"
	/// <summary> RFCase_MeasureSParamIQ
	/// <list type="TestItem" name="TM_RFCase_MeasureSParamIQ" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_MeasureSParamIQ</item>
	/// <item attribute="displayas">RFCase_MeasureSParamIQ</item>
	/// <item attribute="description">Perform an S-parameter measurment.</item>
	/// <list type="TestParameter" name="TM_RFCase_MeasureSParamIQ" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_MeasureSParamIQ</item>
	/// <item attribute="displayas">RFCase_MeasureSParamIQ</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_MeasureSParamIQ</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Channel_0</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Channel_1</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourcePower</item>
	/// <item attribute="description">Specifies the source power of those specified channel.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Specifies the sample rate.</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Specifies the sample size.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">PreampOn</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">BoardLossItem_0</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file of the Channel_0.</item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">BoardLossItem_1</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file of the Channel_1.</item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ExtAtt_1</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">S11_Re</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_MeasureSParamIQ(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM P1dB_DirectSearch"
	/// <summary> RFCase_P1dB_DirectSearch
	/// <list type="TestItem" name="TM_RFCase_P1dB_DirectSearch" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_P1dB_DirectSearch</item>
	/// <item attribute="displayas">RFCase_P1dB_DirectSearch</item>
	/// <item attribute="description">Perform P1dB search on the devices.</item>
	/// <list type="TestParameter" name="TM_RFCase_P1dB_DirectSearch" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_P1dB_DirectSearch</item>
	/// <item attribute="displayas">RFCase_P1dB_DirectSearch</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_P1dB_DirectSearch</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ReferenceGainItem</item>
	/// <item attribute="description">Retrieve result of the Test ItemName_Test ParameterName which is the gain result</item>
	/// <item attribute="value">PowerServoBinarySearch_Gain</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TargetPoutP1dbMin</item>
	/// <item attribute="description">Specifies the minimum target Pout at P1dB. </item>
	/// <item attribute="value">29.5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional, Default)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_P1dB_DirectSearch(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM P1dB_BinarySearch"
	/// <summary> RFCase_P1dB_BinarySearch
	/// <list type="TestItem" name="TM_RFCase_P1dB_BinarySearch" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_P1dB_BinarySearch</item>
	/// <item attribute="displayas">RFCase_P1dB_BinarySearch</item>
	/// <item attribute="description">Perform P1dB search on the devices.</item>
	/// <list type="TestParameter" name="TM_RFCase_P1dB_BinarySearch" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_P1dB_BinarySearch</item>
	/// <item attribute="displayas">RFCase_P1dB_BinarySearch</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_P1dB_BinarySearch</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Gain</item>
	/// <item attribute="description">Specifies the gain of the device.</item>
	/// <item attribute="value">28</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartSourceLevel</item>
	/// <item attribute="description">Specifies the starting source power level.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopSourceLevel</item>
	/// <item attribute="description">Specifies the stopping source power level.</item>
	/// <item attribute="value">6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional, Default)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MaxServoCount</item>
	/// <item attribute="description">(Optional, Default)Specifies the maximum number of servo.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoTolerance</item>
	/// <item attribute="description">(Optional, Default)Specifies the tolerance value of the Targeted Pout.</item>
	/// <item attribute="value">10.05</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ReferenceGainItem</item>
	/// <item attribute="description">(Optional, Compulsory if Gain is not stated)Retrieve result of the Test ItemName_Test ParameterName which is the gain result</item>
	/// <item attribute="value">PowerServoBinarySearch_Gain</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_P1dB_BinarySearch(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM PowerServo"
	/// <summary> RFCase_PowerServo
	/// <list type="TestItem" name="TM_RFCase_PowerServo" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_PowerServo</item>
	/// <item attribute="displayas">RFCase_PowerServo</item>
	/// <item attribute="description">Perform Power Servo to obtain the Targeted Pout.</item>
	/// <list type="TestParameter" name="TM_RFCase_PowerServo" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_PowerServo</item>
	/// <item attribute="displayas">RFCase_PowerServo</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_PowerServo</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Gain</item>
	/// <item attribute="description">Specifies the gain of the device.</item>
	/// <item attribute="value">28</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TargetPout</item>
	/// <item attribute="description">Specifies the Targeted Pout</item>
	/// <item attribute="value">25</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional, Default)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MaxServoCount</item>
	/// <item attribute="description">(Optional, Default)Specifies the maximum number of servo.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoTolerance</item>
	/// <item attribute="description">(Optional, Default)Specifies the tolerance value of the Targeted Pout.</item>
	/// <item attribute="value">10.05</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_PowerServo(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM PowerServo_BinarySearch"
	/// <summary> RFCase_PowerServo_BinarySearch
	/// <list type="TestItem" name="TM_RFCase_PowerServo_BinarySearch" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_PowerServo_BinarySearch</item>
	/// <item attribute="displayas">RFCase_PowerServo_BinarySearch</item>
	/// <item attribute="description">Perform Power Servo to obtain the Targeted Pout using Binary Search.</item>
	/// <list type="TestParameter" name="TM_RFCase_PowerServo_BinarySearch" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_PowerServo_BinarySearch</item>
	/// <item attribute="displayas">RFCase_PowerServo_BinarySearch</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_PowerServo_BinarySearch</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TargetPout</item>
	/// <item attribute="description">Specifies the Targeted Pout</item>
	/// <item attribute="value">25</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartSourceLevel</item>
	/// <item attribute="description">Specifies the starting source power level.</item>
	/// <item attribute="value">-6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopSourceLevel</item>
	/// <item attribute="description">Specifies the stopping source power level.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional, Default)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MaxServoCount</item>
	/// <item attribute="description">(Optional, Default)Specifies the maximum number of servo.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoTolerance</item>
	/// <item attribute="description">(Optional, Default)Specifies the tolerance value of the Targeted Pout.</item>
	/// <item attribute="value">10.05</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_PowerServo_BinarySearch(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM PowerServo_LinearSearch"
	/// <summary> RFCase_PowerServo_LinearSearch
	/// <list type="TestItem" name="TM_RFCase_PowerServo_LinearSearch" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_PowerServo_LinearSearch</item>
	/// <item attribute="displayas">RFCase_PowerServo_LinearSearch</item>
	/// <item attribute="description">Perform Power Servo to obtain the Targeted Pout using Linear Search.</item>
	/// <list type="TestParameter" name="TM_RFCase_PowerServo_LinearSearch" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_PowerServo_LinearSearch</item>
	/// <item attribute="displayas">RFCase_PowerServo_LinearSearch</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_PowerServo_LinearSearch</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TargetPout</item>
	/// <item attribute="description">Specifies the Targeted Pout</item>
	/// <item attribute="value">25</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartSourceLevel</item>
	/// <item attribute="description">Specifies the starting source power level.</item>
	/// <item attribute="value">-6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopSourceLevel</item>
	/// <item attribute="description">Specifies the stopping source power level.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceIncrement</item>
	/// <item attribute="description">Specifies the increment of source power level</item>
	/// <item attribute="value">0.1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional, Default)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MaxServoCount</item>
	/// <item attribute="description">(Optional, Default)Specifies the maximum number of servo.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoTolerance</item>
	/// <item attribute="description">(Optional, Default)Specifies the tolerance value of the Targeted Pout.</item>
	/// <item attribute="value">10.05</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SweepOperation</item>
	/// <item attribute="description">(Optional)Specifies the Sweep Operation to be True or False</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TypGainSweepOperation</item>
	/// <item attribute="description">(Optional, Compulsary if SweepOperation set to True)Specifies the gain of the device.</item>
	/// <item attribute="value">28</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_PowerServo_LinearSearch(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM ReadEvm"
	/// <summary> RFCase_ReadEvm
	/// <list type="TestItem" name="TM_RFCase_ReadEvm" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_ReadEvm</item>
	/// <item attribute="displayas">RFCase_ReadEvm</item>
	/// <item attribute="description">Perform Evm measurement in synchronous</item>
	/// <list type="TestParameter" name="TM_RFCase_ReadEvm" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_ReadEvm</item>
	/// <item attribute="displayas">RFCase_ReadEvm</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_ReadEvm</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_ReadEvm(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM ReadEvmAsync"
	/// <summary> RFCase_ReadEvmAsync
	/// <list type="TestItem" name="TM_RFCase_ReadEvmAsync" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_ReadEvmAsync</item>
	/// <item attribute="displayas">RFCase_ReadEvmAsync</item>
	/// <item attribute="description">Perform Evm measurement in synchronous</item>
	/// <list type="TestParameter" name="TM_RFCase_ReadEvmAsync" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_ReadEvmAsync</item>
	/// <item attribute="displayas">RFCase_ReadEvmAsync</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_ReadEvmAsync</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_ReadEvmAsync(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM ReadSem"
	/// <summary> RFCase_ReadSem
	/// <list type="TestItem" name="TM_RFCase_ReadSem" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_ReadSem</item>
	/// <item attribute="displayas">RFCase_ReadSem</item>
	/// <item attribute="description">Perform Sem measurement in synchronous mode.</item>
	/// <list type="TestParameter" name="TM_RFCase_ReadSem" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_ReadSem</item>
	/// <item attribute="displayas">RFCase_ReadSem</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_ReadSem</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">SemData_0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_ReadSem(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM ReadSemAsyn"
	/// <summary> RFCase_ReadSemAsyn
	/// <list type="TestItem" name="TM_RFCase_ReadSemAsyn" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_ReadSemAsyn</item>
	/// <item attribute="displayas">RFCase_ReadSemAsyn</item>
	/// <item attribute="description">Perform Sem measurement in asynchronous mode.</item>
	/// <list type="TestParameter" name="TM_RFCase_ReadSemAsyn" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_ReadSemAsyn</item>
	/// <item attribute="displayas">RFCase_ReadSemAsyn</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_ReadSemAsyn</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">SemData_0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_ReadSemAsyn(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM WlanPowerServo"
	/// <summary> RFCase_WlanPowerServo
	/// <list type="TestItem" name="TM_RFCase_WlanPowerServo" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WlanPowerServo</item>
	/// <item attribute="displayas">RFCase_WlanPowerServo</item>
	/// <item attribute="description">Perform Power Servo to obtain the Targeted Pout.</item>
	/// <list type="TestParameter" name="TM_RFCase_WlanPowerServo" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_WlanPowerServo</item>
	/// <item attribute="displayas">RFCase_WlanPowerServo</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WlanPowerServo</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Freq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourcePin</item>
	/// <item attribute="description">Specifies the RF signal power in dBm.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TargetPower</item>
	/// <item attribute="description">Specifies the target power level.</item>
	/// <item attribute="value">-30</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoEnable</item>
	/// <item attribute="description">Specifies the enable power servo.</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">WlanModulationStandard</item>
	/// <item attribute="description">Specifies Evm Wlan Modulation Standard.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceAttenuation</item>
	/// <item attribute="description">(Optional)Specifies the RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoTolerance</item>
	/// <item attribute="description">(Optional, Default)Specifies the tolerance value of the Targeted Pout.</item>
	/// <item attribute="value">10.05</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">s</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_WlanPowerServo(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM WlanResidualEVM"
	/// <summary> RFCase_WlanResidualEVM
	/// <list type="TestItem" name="TM_RFCase_WlanResidualEVM" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WlanResidualEVM</item>
	/// <item attribute="displayas">RFCase_WlanResidualEVM</item>
	/// <item attribute="description">Perform residual Evm measurement.</item>
	/// <list type="TestParameter" name="TM_RFCase_WlanResidualEVM" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_WlanResidualEVM</item>
	/// <item attribute="displayas">RFCase_WlanResidualEVM</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WlanResidualEVM</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SourceChannel</item>
	/// <item attribute="description">Specifies the source PinAlias</item>
	/// <item attribute="value">RF5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the measure PinAlias</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartFreq</item>
	/// <item attribute="description">Specifies the start frequency</item>
	/// <item attribute="value">2400</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopFreq</item>
	/// <item attribute="description">Specifies the stop frequency</item>
	/// <item attribute="value">2500</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">IncrementFreq</item>
	/// <item attribute="description">Specifies the incremental  frequency</item>
	/// <item attribute="value">100</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartTargetPower</item>
	/// <item attribute="description">Specifies the target start output power</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopTargetPower</item>
	/// <item attribute="description">Specifies the target stop output power</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">IncrementTargetPower</item>
	/// <item attribute="description">Specifies the incremental  target power</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartMeasureLevel</item>
	/// <item attribute="description">Specifies the start measured power level.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopMeasureLevel</item>
	/// <item attribute="description">Specifies the stop measured power level.</item>
	/// <item attribute="value">20</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">IncrementMeasureLevel</item>
	/// <item attribute="description">Specifies the incremental  measured power level.</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StartSourceAtt</item>
	/// <item attribute="description">Specifies the start RFPM input attenuation.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">StopSourceAtt</item>
	/// <item attribute="description">Specifies the  stop  RFPM input attenuation.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">IncrementSourceAtt</item>
	/// <item attribute="description">Specifies the  incremental  RFPM input attenuation.</item>
	/// <item attribute="value">10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">WlanModulationStandard</item>
	/// <item attribute="description">Specifies Evm Wlan Modulation Standard.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_TRX2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file. </item>
	/// <item attribute="value">HB_OUT2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">InputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external input attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ServoTolerance</item>
	/// <item attribute="description">(Optional, Default)Specifies the tolerance value of the Targeted Pout.</item>
	/// <item attribute="value">10.05</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Setting_0</item>
	/// <item attribute="description">(Optional)Specifies AcqTime</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Setting_1</item>
	/// <item attribute="description">(Optional)Specifies viewConstellation</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Setting_2</item>
	/// <item attribute="description">(Optional)Specifies mcsIndex</item>
	/// <item attribute="value">8</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Setting_3</item>
	/// <item attribute="description">(Optional)Specifies PSDULength</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Setting_4</item>
	/// <item attribute="description">(Optional)Specifies autoConfigSetup</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_WlanResidualEVM(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma region ".xml file -> Test Item -> TM WoferMeasureChannel"
	/// <summary> RFCase_WoferMeasureChannel
	/// <list type="TestItem" name="TM_RFCase_WoferMeasureChannel" category="RFTest" group="RF_Items" conditiontype="splitbysemicolon" methodname="seq_TestMethod">
	/// <item attribute="name">RFCase_WoferMeasureChannel</item>
	/// <item attribute="displayas">RFCase_WoferMeasureChannel</item>
	/// <item attribute="description">Perform RF power measurement at the targeted PinAlias.</item>
	/// <list type="TestParameter" name="TM_RFCase_WoferMeasureChannel" category="RFTest" group="RF_Items">
	/// <item attribute="name">RFCase_WoferMeasureChannel</item>
	/// <item attribute="displayas">RFCase_WoferMeasureChannel</item>
	/// <item attribute="description"></item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MethodName</item>
	/// <item attribute="description">Specifies the MethodName.</item>
	/// <item attribute="value">RFCase_WoferMeasureChannel</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureChannel</item>
	/// <item attribute="description">Specifies the PinAlias.</item>
	/// <item attribute="value">RF6</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasurePower</item>
	/// <item attribute="description">Specifies the measured power level.</item>
	/// <item attribute="value">-10</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dBm</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureFreq</item>
	/// <item attribute="description">Specifies the measured frequency.</item>
	/// <item attribute="value">2000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureMode</item>
	/// <item attribute="description">(Optional)Specifies the delay before perform measurement</item>
	/// <item attribute="value">Bypass</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureDelay</item>
	/// <item attribute="description">(Optional, Default)Specifies the delay before perform measurement</item>
	/// <item attribute="value">5</item>
	/// <item attribute="prefix">Milli</item>
	/// <item attribute="unit">S</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">FilterOption</item>
	/// <item attribute="description">(Optional)Specifies the filter option.“0” = HP1, “1” = HPF2, “2” = HFP3, “3” = BYPASS(Default)</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputBoardLossItem</item>
	/// <item attribute="description">(Optional)Specifies the item in BoardLoss file.(Refer to explanation on BoardLoss Topic)</item>
	/// <item attribute="value">MB1_OUT</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputExtAtt</item>
	/// <item attribute="description">(Optional)Specifies the external attenuation</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">MeasureIQ</item>
	/// <item attribute="description">(Optional)Specifies the Measure Setup IQ</item>
	/// <item attribute="value">True</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Boolean</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleRate</item>
	/// <item attribute="description">Compulsory when MeasureIQ = True</item>
	/// <item attribute="value">100000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SampleSize</item>
	/// <item attribute="description">Compulsory when MeasureIQ = True</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">ResultDisplay</item>
	/// <item attribute="description">(Refer to explanation on ResultDisplay Topic)</item>
	/// <item attribute="value">Measure</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// <param name="site">This is techFlow site object.</param>
	/// </summary>
#pragma endregion
	int TestProgram::TM_RFCase_WoferMeasureChannel(Site^ site)
	{
		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}

#pragma endregion

#pragma region "VNACase Test Step.xml"

	/*
	**	----------------------------------------------------------------------------------------------------
	**	Test Parameter: VnaDataAnalysis
	**	----------------------------------------------------------------------------------------------------
	*/
#pragma region ".xml file -> Test Parameter -> VnaDataAnalysis"

	/// <summary> VnaDataAnalysis
	/// <list type="TestItem" name="TestLib_TestParameter_VnaDataAnalysis" category="VnaDataAnalysis" group="Items" conditiontype="splitbysemicoloncomma" methodname="seq_TestMethod">
	/// <item attribute="name">VnaDataAnalysis_TestItemName</item>
	/// <item attribute="displayas">VnaDataAnalysis_TestItemName</item>
	/// <item attribute="description">This is 'VnaDataAnalysis' item with the combination of test item and test parameter, which is to execute test function and return result to test parameter.</item>
	/// <list type="TestParameter" name="TestLib_TestParameter_VnaDataAnalysis" category="VnaDataAnalysis" group="Items">
	/// <item attribute="name">VnaDataAnalysis_TestParameterName_S11</item>
	/// <item attribute="displayas">VnaDataAnalysis_TestParameterName_S11</item>
	/// <item attribute="description">VnaDataAnalysis</item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TraceIndex</item>
	/// <item attribute="description">Specifies the target trace for this particular measurement.</item>
	/// <item attribute="value">1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Function</item>
	/// <item attribute="description">Specifies the test function to perform the data analysis.</item>
	/// <item attribute="value">TraceData</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">AnalysisSetting</item>
	/// <item attribute="description">Specifies the settings for the specific data analysis function. Refer to the user manual for more information.| Remain empty if it is using default setting or not applicable.</item>
	/// <item attribute="value"></item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SmoothingSetting</item>
	/// <item attribute="description">To enable the smoothing on the target trace. | Specifies the smoothing aperture.</item>
	/// <item attribute="value">SmoOff/1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">Freq</item>
	/// <item attribute="description">Specifies the single test frequency or single marker frequency. | Remain 0 if not applicable.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStart</item>
	/// <item attribute="description">Specifies the start frequency (freq range start). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStop</item>
	/// <item attribute="description">Specifies the stop frequency (freq range stop). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputType</item>
	/// <item attribute="description">Specifies the result output type. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Data</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputFormat</item>
	/// <item attribute="description">Specifies the result output format. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Real</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <list type="TestParameter" name="TestLib_TestParameter_VnaDataAnalysis" category="VnaDataAnalysis" group="Items">
	/// <item attribute="name">VnaDataAnalysis_TestParameterName_S21</item>
	/// <item attribute="displayas">VnaDataAnalysis_TestParameterName_S21</item>
	/// <item attribute="description">VnaDataAnalysis</item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TraceIndex</item>
	/// <item attribute="description">Specifies the target trace for this particular measurement.</item>
	/// <item attribute="value">2</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Function</item>
	/// <item attribute="description">Specifies the test function to perform the data analysis.</item>
	/// <item attribute="value">TraceData</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">AnalysisSetting</item>
	/// <item attribute="description">Specifies the settings for the specific data analysis function. Refer to the user manual for more information.| Remain empty if it is using default setting or not applicable.</item>
	/// <item attribute="value"></item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SmoothingSetting</item>
	/// <item attribute="description">To enable the smoothing on the target trace. | Specifies the smoothing aperture.</item>
	/// <item attribute="value">SmoOff/1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">Freq</item>
	/// <item attribute="description">Specifies the single test frequency or single marker frequency. | Remain 0 if not applicable.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStart</item>
	/// <item attribute="description">Specifies the start frequency (freq range start). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStop</item>
	/// <item attribute="description">Specifies the stop frequency (freq range stop). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputType</item>
	/// <item attribute="description">Specifies the result output type. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Data</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputFormat</item>
	/// <item attribute="description">Specifies the result output format. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Real</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <list type="TestParameter" name="TestLib_TestParameter_VnaDataAnalysis" category="VnaDataAnalysis" group="Items">
	/// <item attribute="name">VnaDataAnalysis_TestParameterName_S12</item>
	/// <item attribute="displayas">VnaDataAnalysis_TestParameterName_S12</item>
	/// <item attribute="description">VnaDataAnalysis</item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TraceIndex</item>
	/// <item attribute="description">Specifies the target trace for this particular measurement.</item>
	/// <item attribute="value">3</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Function</item>
	/// <item attribute="description">Specifies the test function to perform the data analysis.</item>
	/// <item attribute="value">TraceData</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">AnalysisSetting</item>
	/// <item attribute="description">Specifies the settings for the specific data analysis function. Refer to the user manual for more information.| Remain empty if it is using default setting or not applicable.</item>
	/// <item attribute="value"></item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SmoothingSetting</item>
	/// <item attribute="description">To enable the smoothing on the target trace. | Specifies the smoothing aperture.</item>
	/// <item attribute="value">SmoOff/1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">Freq</item>
	/// <item attribute="description">Specifies the single test frequency or single marker frequency. | Remain 0 if not applicable.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStart</item>
	/// <item attribute="description">Specifies the start frequency (freq range start). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStop</item>
	/// <item attribute="description">Specifies the stop frequency (freq range stop). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputType</item>
	/// <item attribute="description">Specifies the result output type. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Data</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputFormat</item>
	/// <item attribute="description">Specifies the result output format. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Real</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// <list type="TestParameter" name="TestLib_TestParameter_VnaDataAnalysis" category="VnaDataAnalysis" group="Items">
	/// <item attribute="name">VnaDataAnalysis_TestParameterName_S22</item>
	/// <item attribute="displayas">VnaDataAnalysis_TestParameterName_S22</item>
	/// <item attribute="description">VnaDataAnalysis</item>
	/// <item attribute="datatype">Double</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit">dB</item>
	/// <item attribute="evalmode">Between_IncludeMinAndMax</item>
	/// <item attribute="lolimit">-999</item>
	/// <item attribute="lolimitprefix">None</item>
	/// <item attribute="hilimit">999</item>        
	/// <item attribute="hilimitprefix">None</item>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">TraceIndex</item>
	/// <item attribute="description">Specifies the target trace for this particular measurement.</item>
	/// <item attribute="value">4</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">Int32</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">Function</item>
	/// <item attribute="description">Specifies the test function to perform the data analysis.</item>
	/// <item attribute="value">TraceData</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">AnalysisSetting</item>
	/// <item attribute="description">Specifies the settings for the specific data analysis function. Refer to the user manual for more information.| Remain empty if it is using default setting or not applicable.</item>
	/// <item attribute="value"></item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">SmoothingSetting</item>
	/// <item attribute="description">To enable the smoothing on the target trace. | Specifies the smoothing aperture.</item>
	/// <item attribute="value">SmoOff/1</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">Freq</item>
	/// <item attribute="description">Specifies the single test frequency or single marker frequency. | Remain 0 if not applicable.</item>
	/// <item attribute="value">1000</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStart</item>
	/// <item attribute="description">Specifies the start frequency (freq range start). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition" excelname="">
	/// <item attribute="name">FreqRangeStop</item>
	/// <item attribute="description">Specifies the stop frequency (freq range stop). | Remain 0 if not applicable.</item>
	/// <item attribute="value">0</item>
	/// <item attribute="prefix">Mega</item>
	/// <item attribute="unit">Hz</item>
	/// <item attribute="datatype">Double</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputType</item>
	/// <item attribute="description">Specifies the result output type. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Data</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// <list type="TestParameterCondition">
	/// <item attribute="name">OutputFormat</item>
	/// <item attribute="description">Specifies the result output format. Refer to user manual for more information. | Remain empty if not applicable.</item>
	/// <item attribute="value">Real</item>
	/// <item attribute="prefix">None</item>
	/// <item attribute="unit"></item>
	/// <item attribute="datatype">String</item>
	/// </list>
	/// </list>
	/// </list>
	/// </summary>
	/// <param name="site">This is techFlow site object.</param>

#pragma endregion
	int TestProgram::TestLib_TestParameter_VnaDataAnalysis(Site ^ site)
	{
		/* 
		** Dummy test parameter function.
		** To generate Project Library's test parameter item, and let techFlow3 user to drag into the test recipes editor.
		** Only applicable for techFlow3 user (using test recipes editor).
		** It will link to the all-in-one generic Test Method --> seq_TestMethod() 
		*/

		// Local variable
		int ret = 0;

		ret = seq_TestMethod(site);
		if (ret != 0) goto EndOfTest;

	EndOfTest:
		return ret;
	}
#pragma endregion "VNACase Test Step.xml"

}


/*----------------------------------------------------------------------
* Revision Log
* &Log: MethodName.cpp.rca&


*** Version	:v1.0.0.2
*** Date	: 5 August 2026
*** PIC		:Tham Zhi Kean
* (7600 Test Library) Add API to support MethodName and MethodName for TPEE xml import/export format

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

