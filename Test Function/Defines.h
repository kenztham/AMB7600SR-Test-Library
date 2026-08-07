/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			Defines.h
Purpose:		Defines standard constants. This is fixed.
UUTOffset:		Supported.
----------------------------------------------------------------------*/

#pragma once

#pragma region "GENERAL"
#define CONST_SEQUENCER_CRITICAL_BIN					"CriticalBin"
#define CONST_BRANCH_FLOW_NEXT_ITEM						0 
#define CONST_SMU_FUNC_INIT_STATE						2 
#define CONST_INVALID_RESULT							-999999999
#define CONST_INVALID_RESULT1							-888888888 
#define CONST_INVALID_RESULT2							-777777777 
#define CONST_DEBUG_MESSAGE_DELAY						1
#define CONST_PASS										0
#define CONST_FAIL										1
#define CONST_PI										3.141592653589793238460
#define SUCCESSFULL										0
#pragma endregion "GENERAL"

#pragma region "CM"
#define CM_CONST_TRIGGER_TRISTATE						0
#define CM_CONST_TRIGGER_PXI_TRIG0						1
#define CM_CONST_TRIGGER_PXI_TRIG1						2
#define CM_CONST_TRIGGER_PXI_TRIG2						3
#define CM_CONST_TRIGGER_PXI_TRIG3						4
#define CM_CONST_TRIGGER_PXI_TRIG4						5
#define CM_CONST_TRIGGER_PXI_TRIG5						6
#define CM_CONST_TRIGGER_PXI_TRIG6						7
#define CM_CONST_TRIGGER_PXI_TRIG7						8
#define CM_CONST_TRIGGER_PXI_LBR6						10
#define CM_CONST_TRIGGER_PXI_STAR						11
#define CM_CONST_TRIGGER_SOFT_TRIG0						19
#define CM_CONST_TRIGGER_SOFT_TRIG1						20
#define CM_CONST_TRIGGER_EXT_TRIG_A						23
#define CM_CONST_TRIGGER_EXT_TRIG_B						24
#define CM_CONST_100MHZ_OUTPUT							29
#define CM_CONST_10MHZ_OUTPUT							30
#define CM_CONST_SINGLE_SITE							0
#define CM_CONST_MULTI_SITE								1
#define CM501x_CONST_ALL_IO_AS_OUTPUT					0xFFFFFFFFF
#define CM_CONST_IO_HI									1 
#define CM_CONST_IO_LO									0
#pragma endregion "CM"

#pragma region "SMU"
#define AM_CONST_DUT_TYPE_POWER							7
#define AM_CONST_DUT_TYPE_POWER_CURRENT					8
#define AM_CONST_DUT_TYPE_POWER_VI						9
#define AM_CONST_MEASURECURRENT							0
#define AM_CONST_MEASUREVOLTAGE							1
#define AM_CONST_50_HERTZ 								50
#define AM_CONST_60_HERTZ 								60
#define AM_CONST_DVCI 									0
#define AM_CONST_DICV 									1
#define AM_CONST_LOCAL 									0
#define AM_CONST_REMOTE 								1
#define AM_CONST_SECONDS 								0
#define AM_CONST_PLC 									1
#define AM_CONST_OFF 									0
#define AM_CONST_ON 									1
#define AM_CONST_ON_WITH_SERIES_RES						2
#define AM_CONST_TRANSIENT_SLOW							0
#define AM_CONST_TRANSIENT_NORMAL 						1
#define AM_CONST_TRANSIENT_FAST 						2
#define AM_CONST_TRANSIENT_CUSTOM0						3
#define AM_CONST_TRANSIENT_CUSTOM1						4
#define AM_CONST_TRANSIENT_CUSTOM2						5
#define AM_CONST_TRANSIENT_CUSTOM3						6
#define AM_CONST_TRANSIENT_CUSTOM4						7
#define AM_CONST_AUTOMATICALLY_AFTER_SOURCE_COMPLETE	0
#define AM_CONST_ON_MEASURE_TRIGGER 					1
#define AM_CONST_ON_DEMAND								2
#define AM_CONST_ON_ACQUIRE_ARRAY						4
#define AM_CONST_ON_DYNAMIC_MEAS						3
#define AM_CONST_SMU_OUTPUT_TRIGGER_IDLE				0
#define AM_CONST_SMU_OUTPUT_TRIGGER_SOURCE_COMPLETE		1
#define AM_CONST_SMU_OUTPUT_TRIGGER_MEASURE_COMPLETE	2
#define AM_CONST_SMU_OUTPUT_TRIGGER_ENTER_CLAMP			3
#define AM_CONST_SMU_OUTPUT_TRIGGER_EXIT_CLAMP			4
#define AM_CONST_SMU_OUTPUT_TRIGGER_DURING_SOURCE		5	
#define AM_CONST_TRIGGER_TRISTATE						0
#define AM_CONST_TRIGGER_PXI_TRIG0						1
#define AM_CONST_TRIGGER_PXI_TRIG1						2
#define AM_CONST_TRIGGER_PXI_TRIG2						3
#define AM_CONST_TRIGGER_PXI_TRIG3						4
#define AM_CONST_TRIGGER_PXI_TRIG4						5
#define AM_CONST_TRIGGER_PXI_TRIG5						6
#define AM_CONST_TRIGGER_PXI_TRIG6						7
#define AM_CONST_TRIGGER_PXI_TRIG7						8
#define AM_CONST_TRIGGER_PXI_LBL6						9
#define AM_CONST_TRIGGER_PXI_LBR6						10
#define AM_CONST_TRIGGER_PXI_STAR						11
#define AM_CONST_TRIGGER_PXIE_DSTARA					12
#define AM_CONST_TRIGGER_PXIE_DSTARB					13
#define AM_CONST_TRIGGER_PXIE_DSTARC					14
#define AM_CONST_TRIGGER_SOFT_TRIG0						19
#define AM_CONST_TRIGGER_SOFT_TRIG1						20
#define AM_CONST_TRIGGER_SOFT_TRIG2						21
#define AM_CONST_TRIGGER_SOFT_TRIG3						22
#define AM_CONST_TRIGGER_EXT_TRIG						23
#define AM_CONST_SINGLE_SITE							0
#define AM_CONST_MULTI_SITE								1
#define AM_CONST_1V_RANGE								1
#define AM_CONST_2V_RANGE								2
#define AM_CONST_5V_RANGE								5	
#define AM_CONST_10V_RANGE								10					
#define AM_CONST_1UA_RANGE								1E-6
#define AM_CONST_10UA_RANGE								10E-6
#define AM_CONST_100UA_RANGE							100E-6
#define AM_CONST_1MA_RANGE								1E-3
#define AM_CONST_10MA_RANGE								10E-3	
#define AM_CONST_100MA_RANGE							100E-3
#define AM_CONST_1A_RANGE								1
#define AM_CONST_3A_RANGE								3
#pragma endregion "SMU"

#pragma region "DM"
#define DM_CONST_FORCE_STATE_VECTOR						0
#define DM_CONST_FORCE_STATE_PMU						1
#define DM_CONST_FORCE_STATE_DIO						2
#define DM_CONST_FORCE_STATE_INPUT_DIR					3
#define DM_CONST_FORCE_STATE_OUTPUT_DIR					4
#define DM_CONST_FORCE_STATE_CLOCK						5
#define DM_CONST_FORCE_STATE_INVERTED_CLOCK				6
#define DM_CONST_DIR_OUTPUT								1
#define DM_CONST_DIR_INPUT								0
#define DM_CONST_DVCI									0
#define DM_CONST_DICV									1
#define DM_CONST_LOCAL									0
#define DM_CONST_REMOTE									1
#define DM_CONST_MEASURECURRENT							0
#define DM_CONST_MEASUREVOLTAGE							1
#define DM_CONST_50_HERTZ								50
#define DM_CONST_60_HERTZ								60
#define DM_CONST_SECONDS								0
#define DM_CONST_PLC									1
#define DM_CONST_TRIGGER_WHEN_RISING_EDGE 				0
#define DM_CONST_TRIGGER_WHEN_FALLING_EDGE 				1
#define DM_CONST_TRIGGER_WHEN_LOW 						2
#define DM_CONST_TRIGGER_WHEN_HIGH 						3
#define DM_CONST_TRIGGER_NO_CONNECT						0
#define DM_CONST_TRIGGER_PXI_TRIG0						1
#define DM_CONST_TRIGGER_PXI_TRIG1						2	
#define DM_CONST_TRIGGER_PXI_TRIG2						3
#define DM_CONST_TRIGGER_PXI_TRIG3						4
#define DM_CONST_TRIGGER_PXI_TRIG4						5
#define DM_CONST_TRIGGER_PXI_TRIG5						6
#define DM_CONST_TRIGGER_PXI_TRIG6						7
#define DM_CONST_TRIGGER_PXI_TRIG7						8
#define DM_CONST_TRIGGER_PXI_STAR 						11
#define DM_CONST_TRIGGER_PXIE_DSTARA 					12
#define DM_CONST_TRIGGER_PXIE_DSTARB 					13
#define DM_CONST_TRIGGER_PXIE_DSTARC 					14
#define DM_CONST_TRIGGER_VECTOR_TRIGGER2				15
#define DM_CONST_TRIGGER_VECTOR_TRIGGER3				16
#define DM_CONST_TRIGGER_VECTOR_TRIGGER0				17
#define DM_CONST_TRIGGER_VECTOR_TRIGGER1				18
#define DM_CONST_TRIGGER_SOFTWARE 						19
#define DM_CONST_TRIGGER_SOFTWARE2						20
#define DM_CONST_TRIGGER_EXT_TRIGIN0 					23
#define DM_CONST_TRIGGER_EXT_TRIGIN1 					24
#define DM_CONST_TRIGGER_EXT_TRIGOUT0 					25
#define DM_CONST_TRIGGER_EXT_TRIGOUT1 					26
#define DM_CONST_TRIGGER_VECTOR_TRIGGER4				27
#define DM_CONST_TRIGGER_VECTOR_TRIGGER5				28
#define DM_CONST_TRIGGER_VECTOR_TRIGGER6				29
#define DM_CONST_TRIGGER_VECTOR_TRIGGER7				30
#define DM_CONST_TRIGGER_MATCH_FLAG						39
#define DM_CONST_SINGLE_SITE							0
#define DM_CONST_MULTI_SITE								1
#define DM500X_CONST_SINGLE_SITE_PARALLEL				2
#define DM_CONST_2UA_RANGE								2E-6
#define DM_CONST_20UA_RANGE								20E-6
#define DM_CONST_200UA_RANGE							200E-6
#define DM_CONST_2MA_RANGE								2E-3
#define DM_CONST_25MA_RANGE								25E-3
#define DM_CONST_SPI_NCS_ACTIVE_LOW						0
#define DM_CONST_SPI_NCS_ACTIVE_HIGH					1
#define DM_CONST_VECTOR_PERIOD_1MHZ						0.5e-6
#define DM_CONST_VECTOR_PERIOD_2MHZ						0.25e-6
#define DM_CONST_VECTOR_PERIOD_10MHZ					50e-9
#define DM_CONST_VECTOR_PERIOD_20MHZ					25e-9
#define DM_CONST_VECTOR_PERIOD_25MHZ					20e-9
#define DM_CONST_VECTOR_PERIOD_40MHZ					12.5e-9
#define DM_CONST_VECTOR_PERIOD_50MHZ					10e-9
#define DM_CONST_VECTOR_PERIOD_100MHZ					5e-9
#define DM_CONST_VECTOR_PERIOD_60MHZ					8.33e-9
#define DM_CONST_VECTOR_PERIOD_70MHZ					7.14e-9
#define DM_CONST_VECTOR_PERIOD_80MHZ					6.25e-9
#define DM_CONST_VECTOR_PERIOD_90MHZ					5.55e-9
#define DM_CONST_VECTOR_PERIOD_100NS					100e-9
#define DM_CONST_VEC_ENG_STAT_DONE						0
#define DM_CONST_VEC_ENG_STAT_BUSY						1
#define DM_CONST_VEC_ENG_STAT_BUSY_PAUS					2
#define DM_CONST_VEC_ENG_STAT_BUSY_PAUSB				3
#define DM_CONST_VEC_ENG_STAT_BUSY_WAIT					4
#define DM_CONST_VEC_ENG_STAT_BUSY_WAITB				5
#define DM_CONST_BIDIRECTIONAL_IO						0
#define DM_CONST_DEDICATED_IO							1
#define DM_CONST_TOTAL_CHANNEL_PER_CARD					12
#define DM_CONST_MAX_VECTOR_SET							1000		
#define DM_CONST_MODULE_TYPE							0xA10D483e
#define DM_CONST_VMAX									2 V
#define DM_CONST_VMIN									-2 V
#define DM_CONST_SET_VIH								0
#define DM_CONST_SET_VIL								1
#define DM_CONST_SET_VTERM								2
#define DM_CONST_SET_VOL								3
#define DM_CONST_SET_VOH								4
#define DM_CONST_SET_VCH								5
#define DM_CONST_SET_VCL								6
#define DM_CONST_SET_IOH								7
#define DM_CONST_SET_IOL								8
#define DM_CONST_TRIGGER_READPIN						40
#define DM_CONST_TRIGGER_SPI0_TRIGIN					38
#define DM_CONST_TRIGGER_PIN4_PIN5_LEVEL_CONTROLLER		34
#define DM_CONST_TRIGGER_PIN6_PIN7_LEVEL_CONTROLLER		35
#define DM_CONST_DM481E_MODULE_TYPE						0xD481e12C 
#define DM_CONST_DM483E_MODULE_TYPE						0xA10D483e 
#define DM_CONST_TMU_STATUS_TIMEOUT						4	
#define DM_CONST_TMU_CORE_ARMED							8
#define DM_CONST_TMU_STATUS_DONE						1
#define DM_CONST_TMU_POS_EDGE_SLOPE						0	
#define DM_CONST_TMU_NEG_EDGE_SLOPE						1
#define DM_CONST_TMU_COMPARE_LOW						0	
#define DM_CONST_TMU_COMPARE_HIGH						1
#define DM_CONST_MAX_I2C_SET_PER_CORE					32	
#define DM_VECTOR_PTN_SYMBOL_1							1 
#define DM_VECTOR_PTN_SYMBOL_0							0 
#define TMU_TRIGGER_VECTOR								1	//TMU measurement starts when triggered by opcode in pattern
#define TMU_TRIGGER_NORM								0	//TMU measurement starts immediately
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT0			29
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT1			30
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT2			31
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT3			32
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT4			33
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT5			34
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT6			35
#define DM500X_CONST_TRIGGER_VECTOR_TRIGOUT7			36
#define DM500X_CONST_TRIGGER_SOFTWARE_TRIG0				41
#define DM500X_CONST_TRIGGER_SOFTWARE_TRIG1				42
#define DM500X_CONST_TRIGGER_SOFTWARE_TRIG2				43
#define DM500X_CONST_TRIGGER_SOFTWARE_TRIG3				44
#define DM500X_CONST_TRIGGER_LOGIC_LOW					192
#define DM500X_CONST_TRIGGER_LOGIC_HIGH					193
#define DM58X_CONST_EDGE_SEL_D0							0
#define DM58X_CONST_EDGE_SEL_D1							1
#define DM58X_CONST_EDGE_SEL_D2							2
#define DM58X_CONST_EDGE_SEL_D3							3
#define DM58X_CONST_EDGE_SEL_D4							4
#define DM58X_CONST_EDGE_SEL_D5							5
#define DM58X_CONST_EDGE_SEL_R0							6
#define DM58X_CONST_EDGE_SEL_R1							7
#pragma endregion "DM"

#pragma region "DIO"
#define IOM_CONST_OUTPUT_VIO_OFF				-1
#define IOM_CONST_OUTPUT_VIO_3_3V				0
#define IOM_CONST_OUTPUT_VIO_5_0V				1
#define IOM_CONST_OUTPUT_VIO_EXT				2
#define IOM_CONST_OUTPUT_VCCOUT5_ON				1
#define IOM_CONST_OUTPUT_VCCOUT5_OFF			0
#define IOM_CONST_OUTPUT_VCCOUT12_ON			1
#define IOM_CONST_OUTPUT_VCCOUT12_OFF			0
#define IOM_CONST_DIR_OUTPUT					1
#define IOM_CONST_DIR_INPUT						0
#define IOM_CONST_TOTAL_IO						40
#define IOM_CONST_TOTAL_CBITS					72
#define IOM_CONST_TOTAL_PORTS					5
#define IOM_CONST_SINGLE_SITE					0
#define IOM_CONST_MULTI_SITE					1

#define IOM_CONST_OUTPUT_VIO_OFF				-1
#define IOM_CONST_OUTPUT_VIO_3_3V				0
#define IOM_CONST_OUTPUT_VIO_5_0V				1
#define IOM_CONST_OUTPUT_VIO_EXT				2
#define IOM_CONST_OUTPUT_VCCOUT5_ON				1
#define IOM_CONST_OUTPUT_VCCOUT5_OFF			0
#define IOM_CONST_OUTPUT_VCCOUT12_ON			1
#define IOM_CONST_OUTPUT_VCCOUT12_OFF			0
#define IOM_CONST_PORT_DIRECTION_INPUT			0
#define IOM_CONST_PORT_DIRECTION_OUTPUT			1
#define IOM_CONST_PORT_DRIVE_LOW				0
#define IOM_CONST_PORT_DRIVE_HIGH				1
#define IOM_CONST_PIN_DRIVE_LOW					0
#define IOM_CONST_PIN_DRIVE_HIGH				1
#define IOM_CONST_SINGLE_SITE					0
#define IOM_CONST_MULTI_SITE					1

#pragma region "ACM"
#define ACM_CONST_MODE_FUNCTION_GENERATOR		0
#define ACM_CONST_MODE_AWG						1
#define ACM_CONST_SWITCH_OFF					0
#define ACM_CONST_SWITCH_ON						1
#define ACM_CONST_IMPEDANCE_HIGHZ				0
#define ACM_CONST_IMPEDANCE_50OHM				1
#define ACM_CONST_IMPEDANCE_75OHM				2
#define ACM_CONST_SINE							1
#define ACM_CONST_AUTOTRIG						0
#define ACM_CONST_EXTTRIG						2
#define ACM_CONST_EXTTRIG_CYCLE					6
#define ACM_CONST_TRIG_HIGH						1
#define ACM_CONST_TRIG_LOW						2
#define ACM_CONST_TRIG_RISE						3
#define ACM_CONST_TRIG_FALL						4
#define ACM_CONST_AWG_MAX_WAVEFORM_SETNO		1024
#define ACM_CONST_SINGLE_SITE					0
#define ACM_CONST_MULTI_SITE					1
#define ACM_CONST_TRIGGER_WHEN_RISING_EDGE 		0
#define ACM_CONST_TRIGGER_WHEN_FALLING_EDGE 	1
#define ACM_CONST_TRIGGER_WHEN_LOW 				2
#define ACM_CONST_TRIGGER_WHEN_HIGH 			3
#define ACM_CONST_TRIGGER_NO_CONNECT			0
#define ACM_CONST_TRIGGER_PXI_TRIG0				1
#define ACM_CONST_TRIGGER_PXI_TRIG1				2	
#define ACM_CONST_TRIGGER_PXI_TRIG2				3
#define ACM_CONST_TRIGGER_PXI_TRIG3				4
#define ACM_CONST_TRIGGER_PXI_TRIG4				5
#define ACM_CONST_TRIGGER_PXI_TRIG5				6
#define ACM_CONST_TRIGGER_PXI_TRIG6				7
#define ACM_CONST_TRIGGER_PXI_TRIG7				8
#define ACM_CONST_TRIGGER_PXI_LBL6 				9
#define ACM_CONST_TRIGGER_PXI_LBR6	 			10
#define ACM_CONST_TRIGGER_PXI_STAR 				11
#define ACM_CONST_TRIGGER_SOFTWARE 				19
#define ACM_CONST_TRIGGER_SOFTWARE2				20
#define ACM_CONST_TRIGGER_EXT_TRIGGER 			23
#define ACM_CONST_FG_MIN_FREQ 					70e3
#pragma endregion "ACM"

#pragma region "TM"
#define TM_CONST_SLOPE_POSITIVE					0
#define TM_CONST_SLOPE_NEGATIVE					1
#define TM_CONST_RANGE_0_50OHM					0
#define TM_CONST_RANGE_1_1MOHM					1
#define TM_CONST_RANGE_2_1MOHM					2
#define TM_CONST_START_CHANNEL					0
#define TM_CONST_STOP_CHANNEL					1
#define TM_CONST_OFF_ARM						0
#define TM_CONST_SOFTWARE_ARM					1
#define TM_CONST_HARDWARE_ARM					2
#define TM_CONST_TRIGGER_ARM					3
#define TM_CONST_SINGLE_SITE					0
#define TM_CONST_MULTI_SITE						1
#pragma endregion "TM"

#pragma region "AMSRF"
#define AMSRF_CONST_LOAD_WITH_CONTROLLER		0
#define AMSRF_CONST_LOAD_WITHOUT_CONTROLLER		1
#define AMSRF_CONST_MEASURESETUP_FILTOPT_HPF1	0
#define AMSRF_CONST_MEASURESETUP_FILTOPT_HPF2	1
#define AMSRF_CONST_MEASURESETUP_FILTOPT_HPF3	2
#define AMSRF_CONST_MEASURESETUP_FILTOPT_BYPASS	3
#define AMSRF_CONST_TRIGLOC_PXITRIG0			0
#define AMSRF_CONST_TRIGLOC_PXITRIG1			1
#define AMSRF_CONST_TRIGLOC_PXITRIG2			2
#define AMSRF_CONST_TRIGLOC_PXITRIG3			3
#define AMSRF_CONST_TRIGLOC_PXITRIG4			4
#define AMSRF_CONST_TRIGLOC_PXITRIG5			5
#define AMSRF_CONST_TRIGLOC_PXITRIG6			6
#define AMSRF_CONST_TRIGLOC_PXITRIG7			7
#define AMSRF_CONST_TRIGLOC_PXITRIGFRONTPANEL	8
#define AMSRF_CONST_TRIGOPT_NONE				0
#define AMSRF_CONST_TRIGOPT_ARBMARK1			1
#define AMSRF_CONST_TRIGOPT_ARBMARK2			2
#define AMSRF_CONST_TRIGOPT_ARBMARK3			3
#define AMSRF_CONST_TRIGPOL_POS					0
#define AMSRF_CONST_TRIGPOL_NEG					1
#define AMSRF_CONST_MODPLAYBACKMODE_SINGLE		0
#define AMSRF_CONST_MODPLAYBACKMODE_CONT		1
#pragma endregion "AMSRF"

#pragma region "ERROR CODE"
#define ER_CONST_HARDWARE_PROFILE_NOT_SPECIFIED	-1
#define ER_CONST_GENERAL						-2
#define ER_CONST_TIMEOUT						-3
#define ER_CONST_FILE_NOT_FOUND					-4
#define ER_CONST_READ_FILE_ERROR				-5
#define ER_CONST_INVALID_SETTING				-6
#define ER_CONST_NOT_FOUND						-7
#define ER_CONST_APPSWIDEVARIABLE_NOT_SPECIFIED	-8
#define ER_CONST_RESOURCE_MANAGER				-9
#define ER_CONST_READ_EEPROM_ERROR				-10
#define ER_CONST_DRIVE_CURRENT					-11 
#define ER_CONST_CALIBRATION_MODE				-12 
#define ER_CONST_INVALID_CALIBRATION_MODE		-13 
#define ER_CONST_INVALID_HARDWARE_RESOURCE		-14 
#define ER_CONST_INVALID_RESULT					-15 
#define	ER_CONST_ERRROR_CATCH					-16
#define ER_CONST_OPEN_FAILED					110 
#define ER_CONST_NOT_ENOUGH_MEMORY				 8
#define ER_CONST_BAD_ARGUMENTS					160
#define ER_CONST_RTPLOTTER						201
#define ER_CONST_CIS_CORE_BUSY					-100	//0xFFFFFF9C
#define ER_CONST_CIS_CORE_ERROR					-200	//0xFFFFFF38 
#pragma endregion "ERROR CODE"

#pragma region "LOGGER"
#define LOGGER_CONST_INFORMATION				0
#define LOGGER_CONST_WARNING					1
#define LOGGER_CONST_ERROR						2
#define LOGGER_CONST_FILE						0
#define LOGGER_CONST_TRACER						1
#define LOGGER_CONST_FILE_TRACER				2
#define LOGGER_CONST_BASE						3
#define LOGGER_CONST_OVERWRITE					0
#define LOGGER_CONST_APPEND						1
#define LOGGER_WARNING_TYPE						"[WARNING]"
#define LOGGER_ERROR_TYPE						"[ERROR] "
#define LOGGER_INFO_TYPE						"[INFO]  "
#pragma endregion "LOGGER"

#pragma region "MESSAGE_TYPE"
#define MESSG_TYPE_APPS_CAL_SETUP				"Apps Calibration Setup"
#define MESSG_TYPE_CORR_FACTOR_SETUP			"CorrFactor Setup"
#define MESSG_TYPE_BOARD_LOSS_SETUP				"BoardLoss Setup"
#define MESSG_TYPE_AUTO_GU_CAL_SETUP			"Auto GU Calibration Setup"
#define MESSG_TYPE_WARNING						"WARNING"
#pragma endregion "MESSAGE_TYPE"

#pragma region "FILE_PATH"
#define FILE_CONST_AEM_DEBUG					"C:\\Aemulus\\Debug"
#define FILE_CONST_AEM_DEBUG_CIS_LOG			"C:\\Aemulus\\Debug\\CIS_Debug_Log_S"
#define FILE_CONST_BAT_RTPLOTTER				"RTPlotterSetup.bat"
#define FILE_CONST_BAT_RTPLOTTER_INI			"RTPlot_setting.ini"
#define FILE_CONST_TESTER_INFO					"C:\\Aemulus\\TesterInfo"
#define FILE_CONST_TEST_RECIPE					"C:\\Aemulus\\techFlow3\\Projects\\TestRecipes"
#define FILE_CONST_APPS_CALIBRATION				"C:\\Aemulus\\TesterInfo\\AppsCal"
#define FILE_CONST_APPS_CALIBRATION_ARCHIVED	"C:\\Aemulus\\TesterInfo\\AppsCal_Archived"
#define FILE_CONST_GU_CAL						"C:\\Aemulus\\TesterInfo\\GU_Cal"
#define FILE_CONST_CORR_FACTOR					"C:\\Aemulus\\TesterInfo\\Corrfactor"
#define FILE_CONST_CORR_FACTOR_ARCHIVED			"C:\\Aemulus\\TesterInfo\\Corrfactor_Archived"
#define FILE_CONST_BOARD_LOSS					"C:\\Aemulus\\TesterInfo\\BoardLoss"
#define FILE_CONST_AUTO_GU_RECIPE_CONFIG_x32	"C:\\Aemulus\\techFlow3\\bin\\Auto_GU_RecipeConfig.txt"
#define FILE_CONST_AUTO_GU_RECIPE_CONFIG_x64	"C:\\Aemulus\\techFlow3\\bin\\NF4\\x64\\Auto_GU_RecipeConfig.txt"
#define FILE_CONST_AUTO_GU_CORR_TOOL_x32		"C:\\Aemulus\\techFlow3\\bin\\Auto_GU_Correlation_Tool.exe"
#define FILE_CONST_AUTO_GU_CORR_TOOL_x64		"C:\\Aemulus\\techFlow3\\bin\\NF4\\x64\\Auto_GU_Correlation_Tool.exe"
#define FILE_CONST_AUTO_GU_CORR_TOOL_ini_x32	"C:\\Aemulus\\techFlow3\\bin\\Auto_GU_Correlation_Tool.ini" 
#define FILE_CONST_AUTO_GU_CORR_TOOL_ini_x64	"C:\\Aemulus\\techFlow3\\bin\\NF4\\x64\\Auto_GU_Correlation_Tool.ini"
#define FILE_CONST_WOLFER_INFO					"C:\\Aemulus\\Wolfer\\"
#pragma endregion "FILE_PATH"

#pragma region "FILE NAME"
#define FILENAME_CONST_FIXED_OFFSET				"FixedOffset.csv"
#define FILENAME_CONST_CORR_FACTOR				"CorrFactor_S"
#define FILENAME_CONST_REFERENCE				"Reference.csv"
#define FILENAME_CONST_APPS_CALIBRATION			"AppsCal.csv"
#define FILENAME_CONST_BOARD_LOSS				"BoardLoss.csv"
#define FILE_NAME_WOLFER_TX						"tx_pathloss.txt"
#define FILE_NAME_WOLFER_RX						"rx_pathloss.txt"
#define FILE_NAME_WOLFER_CAL_LIST				"freq_cal_list.txt"
#define FILE_NAME_WOLFER_HAR_CAL_LIST			"freq_Har_cal_list.txt"
#define FILE_NAME_WOLFER_TX_HAR					"tx_Har_pathloss.txt"
#define FILE_NAME_WOLFER_RX_HAR					"rx_Har_pathloss.txt"
#define FILE_NAME_WOLFER_TX_RL					"tx_rl_pathloss.txt"
#define FILE_NAME_WOLFER_RX_RL					"rx_rl_pathloss.txt" 
#pragma endregion "FILE NAME"

#pragma region "AMB7600"
#define ER_OPERATION_HALTED_BY_USER		0xAE100000
#define ER_PREREQUISITE_NOT_MET			0xAE100001
#define ER_ILLEGAL_OPERATION			0xAE100002
#define ER_NO_CALIBRATION_RECORD		0xAE100003
#define ER_CALIBRATION_DUE				0xAE100004
#define ER_INVALID_USER_INPUT			0xAE100005
#define ER_INVALID_QUERY				0xAE100006
#define ER_STATION_ID_OCCUPIED			0xAE100007
#define ER_MODULATION_OVERLOADED		0xAE100008
#define ER_MODULATION_NOT_LOADED		0xAE100009
#define ER_MODULATION_ALREADY_LOADED	0xAE100010
#define ER_RESOURCE_ALREADY_GRANTED		0xAE100011
#define ER_CORRELATION_ERROR			0xAE100012
#define ER_INVALID_SETTING				0xAE100013
#define ER_CALIBRATION_OUT_OF_SPECS		0xAE100014
#define ER_UNSUPPORTED_OFFLINE			0xAE100015
#define ER_ENFORCED_OFFLINE				0xAE100016
#define ER_SOFTWARE_TIMEOUT				0xAE100020
#define ER_HADWARE_TIMEOUT				0xAE100021
#define ER_EXCEED_MAX_SAMPLE_SZIE		0xAE100022
#define ER_MISSING_CALIBRATION_FILE		0xAE100023
#define ER_NO_TESTHEAD					0xAE100024
#define ER_NO_TESTSITE					0xAE100025
#define ER_API_NOT_SUPPORTED			0xAE100026
#define ER_LOAD_DLL_FILE_ERROR			0xAE100100
#define ER_LOAD_DLL_FUNCTION_ERROR		0xAE100101
#define ER_MEMORY_ALLOCATION_ERROR		0xAE100102
#define ER_FILE_IO_ERROR				0xAE100110
#define ER_MISSING_GLOBAL_COND			0xAE100120
#define ER_MISSING_FLOWITEM_COND		0xAE100121
#define ER_MISSING_TESTPARAM_COND		0xAE100122
#define ER_INVALID_COMMAND				0xAE100130
#define ER_INVALID_COMMAND_ARGUMENTS	0xAE100131
#define ER_REGISTER_INSTRUMENT_ERROR	0xAE100200
#define ER_INIT_INSTRUMENT_ERROR		0xAE100201
#define ER_INSTRUMENT_READ_ERROR		0xAE100202
#define ER_INSTRUMENT_WRITE_ERROR		0xAE100203
#define ER_INCOMPATIBLE_HARDWARE		0xAE100204
#define ER_UNINIT_INSTRUMENT_ERROR		0xAE100205
#define ER_VOLTAGE_OUT_OF_RANGE			0xAE100210
#define ER_CURRENT_OUT_OF_RANGE			0xAE100211
#define ER_INVALID_RESOURCE_PIN			0xAE100212


#define ER_TevDRPM_1					0x00001
#define ER_TevDRPM_2					0x00002
#define ER_TevDRPM_3					0x00004
#define ER_TevDRPM_4					0x00008
#define ER_TevRFSM						0x00010
#define ER_TevRFM						0x00020
#define ER_AfSigGenA					0x00040
#define ER_AfDigitizer					0x00080
#define ER_AfSigGenB					0x00100
#define ER_SCALAR_FACTOR_READ			0x00200
#define ER_VECTOR_FACTOR_READ			0x00400
#define ER_NOISE_FACTOR_READ			0x00800
#define ER_CONFIG_FILE_READ				0x10000
#define ER_NO_HARDWARE_FOUND			0x20000	

#define ER_CONST_RFSiteConfigInfo		0x30000
#define ER_CONST_BoardLossInfo		    0x40000
#define ER_CONST_CorrFactorInfo		    0x50000
#define ER_CONST_TestCondition_Not_Found        0x60000	//0xFFFFFF38 
#define ER_CONST_TestCondition_DataType_Invalid 0x60001	//0xFFFFFF38 

#define ER_CONST_InvalidControlMethod								0x60000
#define ER_CONST_DCCase_DriveVoltage								0x60001
#define ER_CONST_DCCase_DriveCurrent								0x60002
#define ER_CONST_DCCase_ClampVoltage								0x60003
#define ER_CONST_DCCase_ClampCurrent								0x60004
#define ER_CONST_DCCase_AMConfigureTriggerEdgeLevel					0x60005
#define ER_CONST_DCCase_AMConfigureTriggerEdgeLevelExtra			0x60006
#define ER_CONST_DCCase_AMMapTriggerIntToTriggerOut					0x60007
#define ER_CONST_DCCase_AMDriveSoftwareTrigger						0x60008
#define ER_CONST_DCCase_AMConfigureInputTriggerSelect				0x60009
#define ER_CONST_DCCase_AMConfigureSMUOutputTriggerMode				0x60010
#define ER_CONST_DCCase_AMConfigureSMUOutputTriggerPulseWidth		0x60011
#define ER_CONST_DCCase_AMConfigureSMUOutputTriggerDuringSource		0x60012
#define ER_CONST_DCCase_AMConfigureOutputTriggerSelect				0x60013
#define ER_CONST_DCCase_SetNPLC										0x60014
#define ER_CONST_DCCase_SetPinOnOff									0x60015
#define ER_CONST_DCCase_WaitSecond									0x60016
#define ER_CONST_DMCase_WriteVector									0x60017
#define ER_CONST_DMCase_DMConfigureTriggerEdgeLevel					0x60018
#define ER_CONST_DMCase_DMMapTriggerIntToTriggerOut					0x60019
#define ER_CONST_DMCase_DMConfigureInputTriggerSelect				0x60020
#define ER_CONST_DMCase_DMConfigureOutputTriggerSelect				0x60021
#define ER_CONST_DMCase_DMDriveSoftwareTrigger						0x60022
#define ER_CONST_DMCase_DMConfigureReadPin_TriggerOutput			0x60023
#define ER_CONST_DMCase_DMConfigurePinToPMU							0x60024
#define ER_CONST_DMCase_DMConfigurePinToVector						0x60025
#define ER_CONST_DMCase_DMConfigurePinToDIO							0x60026
#define ER_CONST_DMCase_DMDioModeDrivePin							0x60027
#define ER_CONST_IOMCase_DIODrivePin								0x60028
#define ER_CONST_IOMCase_DIODrivePort								0x60029
#define ER_CONST_IOMCase_DIOSetModuleVIO							0x60030
#define ER_CONST_IOMCase_DIOSetPortDirection						0x60031
#define ER_CONST_RFCase_SourcePower									0x60032
#define ER_CONST_RFCase_SourcePowerFast								0x60033
#define ER_CONST_RFCase_SourcePowerLow								0x60034
#define ER_CONST_RFCase_IsolateChannel								0x60035
#define ER_CONST_RFCase_SourceTwoTone								0x60036
#define ER_CONST_RFCase_StartModulation								0x60037
#define ER_CONST_RFCase_StopModulation								0x60038
#define ER_CONST_RFCase_SetSourceTriggerRouting						0x60039
#define ER_CONST_RFCase_SetSourceTriggerIn							0x60040
#define ER_CONST_RFCase_SetSourceTriggerOut							0x60041
#define ER_CONST_RFCase_SetMeasureTriggerRouting					0x60042
#define ER_CONST_RFCase_SetMeasureTriggerIn							0x60043
#define ER_CONST_RFCase_RunSourceAlignment							0x60044
#define ER_CONST_RFCase_LoadModulation								0x60045
#define ER_CONST_RFCase_WlanInit									0x60046
#define ER_CONST_RFCase_EvmMeasurementSetupAuto						0x60047
#define ER_CONST_RFCase_EvmMeasurementSetupManual					0x60048
#define ER_CONST_RFCase_MeasureSetup								0x60049
#define ER_CONST_RFCase_MeasureSetupIQ								0x60050

#define ER_CONST_InvalidTestMethod							0x70000
#define ER_CONST_DCCase_OS									0x70001
#define ER_CONST_DCCase_MeasureCurrent						0x70002
#define ER_CONST_DCCase_MeasureVoltage						0x70003
#define ER_CONST_DCCase_MeasureBurstCurrent					0x70004
#define ER_CONST_DCCase_MeasureBurstVoltage					0x70005
#define ER_CONST_DCCase_DifferentialResult					0x70006
#define ER_CONST_DMCase_MIPIReadVector						0x70007
#define ER_CONST_RFCase_MeasureChannel						0x70008
#define ER_CONST_RFCase_MeasureChannelFast					0x70009
#define ER_CONST_RFCase_MeasureChannelIQ					0x70010
#define ER_CONST_RFCase_MeasureBurstPower					0x70011
#define ER_CONST_RFCase_MeasureSwitchingTime				0x70012
#define ER_CONST_RFCase_MeasureSParam						0x70013
#define ER_CONST_RFCase_MeasureSParamIQ						0x70014
#define ER_CONST_RFCase_P1dB_BinarySearch					0x70015
#define ER_CONST_RFCase_PowerServo							0x70016
#define ER_CONST_RFCase_PowerServo_BinarySearch             0x70017
#define ER_CONST_RFCase_PowerServo_LinearSearch				0x70018
#define ER_CONST_RFCase_P1dB_DirectSearch					0x70019
#define ER_CONST_RFCase_MeasureIIP3							0x70020
#define ER_CONST_RFCase_ReadEvm								0x70021
#define ER_CONST_RFCase_ReadEvmAsync						0x70022
#define ER_CONST_RFCase_WlanPowerServo						0x70023

//Resource type to ease errors checking
#define AFERR							698282		//Ascii E=69, R=82, R=82 //AXRF ERROR - Reserved for CheckErorr function 
#define RF0								8270		//Ascii A=65, M=77, S=83, R=82, F=70
#define TEV								846986		//Ascii T=84, E=69, V=86			
#define AFSG							8371		//Ascii A=65, F=70, S=83, G=71	
#define AFDGT							687184		//Ascii A=65, F=70, D=68, G=71,T=84				
#pragma endregion "AMB7600"

#pragma region "User_Defined_Unit"
#define V		*1
#define mV		*1e-3
#define A		*1
#define mA		*1e-3
#define uA		*1e-6
#define nA		*1e-9
#define S		*1
#define mS		*1e-3
#define uS		*1e-6
#define nS		*1e-9
#define Hz		*1
#define KHz		*1e3
#define MHz		*1e6
#define GHz		*1e9
#define db		*1
#define dbm		*1
#define dbc		*1
#define K		*1e3 
#define pixel	*1 
#define bits	*1 
#pragma endregion "User_Defined_Unit"

#pragma region "axrfCW"
#define INVALID_TESTCOND		-999
#define TC_REQUIRED				0
#define TC_OPTIONAL				1
#define IQ_CORRECTIONFACTOR		10
#pragma region "axrfCW"

#pragma region "DM500x_TimingSet"
#define TimingSet_TS0			"TS0"
#pragma endregion "DM500x_TimingSet"

#pragma region "DM500x_Opcode"
#define DM500x_OP_NOP		"nop"
#define DM500x_OP_STR		"str"
#define DM500x_OP_TRIG		"trig"
#define DM500x_OP_REP		"rep"	
#define DM500x_OP_JMP		"jmp"	
#define DM500x_OP_CJUMP		"cjmp"	
#define DM500x_OP_SSR		"ssr"	
#define DM500x_OP_JSR		"jsr"	
#define DM500x_OP_CJSR		"cjsr"	
#define DM500x_OP_RTN		"rtn"	
#define DM500x_OP_CRTN		"crtn"	
#define DM500x_OP_WAIT		"wait"	
#define DM500x_OP_WAITB		"waitb"	
#define DM500x_OP_PAUS		"paus"	
#define DM500x_OP_PAUSB		"pausb"		
#define DM500x_OP_SETR0		"setr0"		
#define DM500x_OP_SETR1		"setr1"		
#define DM500x_OP_SETR2		"setr2"		
#define DM500x_OP_SETR3		"setr3"		
#define DM500x_OP_JNZ0		"jnz0"		
#define DM500x_OP_JNZ1		"jnz1"		
#define DM500x_OP_JNZ2		"jnz2"		
#define DM500x_OP_JNZ3		"jnz3"		
#define DM500x_OP_STOP		"stop"		
#define DM500x_OP_CSTOP		"cstop"		
#define DM500x_OP_RCODE		"rcode"		
#define DM500x_OP_SETF		"setf"		
#define DM500x_OP_CLRF		"clrf"		
#define DM500x_OP_SELC		"selc"		
#define DM500x_OP_CLRFAIL	"clrfail"	
#define DM500x_OP_STARTM	"startm"	
#define DM500x_OP_ENDM		"endm"		
#define DM500x_OP_SINGLEM	"singlem"	
#define DM500x_OP_SELSOU	"selsou"	
#define DM500x_OP_SELCAP	"selcap"	
#pragma endregion "DM500x_Opcode"

#pragma region "DM500x_Action"
#define Action_N				"N"
#define Action_Zero				"0"
#define Action_One				"1"
#define Action_Z_Tristate		"Z"
#define Action_Source			"D"
#define Action_Capture			"P"
#define Action_CompareLow		"L"
#define Action_CompareHigh		"H"
#define Action_CompareMidband	"M"
#define Action_WindowLow		"l"
#define Action_WindowHigh		"h"
#define Action_WindowMidband	"m"
#define Action_Tristate_D0_D3	"Z"
#pragma endregion "DM500x_Action"

#pragma region "DC_ControlMethods"
#define DCCase_DriveVoltage								1001
#define DCCase_DriveCurrent								1002
#define DCCase_ClampVoltage								1003
#define DCCase_ClampCurrent								1004
#define DCCase_SetNPLC									1005
#define DCCase_SetPinOnOff								1006
#define DCCase_ConfigureTriggerEdgeLevel                1007
#define DCCase_MapTriggerIntToTriggerOut                1008
#define DCCase_DriveSoftwareTrigger                     1009
#define DCCase_AMConfigureInputTriggerSelect			    1010
#define DCCase_AMConfigureSMUOutputTriggerPulseWidth	1011
#define DCCase_AMConfigureSMUOutputTriggerDuringSource	1012
#define DCCase_AMConfigureSMUOutputTriggerMode			1013
#define DCCase_AMConfigureOutputTriggerSelect			1014
#define DCCase_WaitSecond								1015
#pragma endregion "DC_ControlMethods"

#pragma region "DC_TestMethods"
#define DCCase_OS							1101
#define DCCase_MeasureCurrent				1102
#define DCCase_MeasureVoltage				1103
#define DCCase_AMMeasureBurstCurrent		1104
#define DCCase_AMMeasureBurstVoltage		1105
#define DCCase_DifferentialResult			1106
#pragma endregion "DC_TestMethods"

#pragma region "DM_ControlMethods"
#define DMCase_DMInit									3001
#define DMCase_DMConfigurePinToPMU						3002
#define DMCase_DMConfigurePinToVector					3003
#define DMCase_DMConfigurePinToDIO						3004
#define DMCase_DMLoadVectorFile							3005
#define DMCase_WriteVector								3006
#define DMCase_DMDioModeDrivePin						3007
#define DMCase_DMConfigureInputTriggerSelect			3008
#define DMCase_DMConfigureOutputTriggerSelect			3009
#define DMCase_DMConfigureReadPin_TriggerOutput			3010
#define DMCase_DMCastDPinLevel							3011
#define DMCase_DMCastTimingSetPeriod					3012
#define DMCase_DMCastPEAttribute						3013
#pragma endregion "DM_ControlMethods"

#pragma region "DM_TestMethods"
#define DMCase_MIPIReadVector				3001
#pragma endregion "DM_TestMethods"

#pragma region "DIO_ControlMethods"
#define IOMCase_DIODrivePin								4001
#define IOMCase_DIODrivePort							4002
#define IOMCase_DIOSetModuleVIO							4003
#define IOMCase_DIOSetPortDirection						4004
#pragma endregion "DIO_ControlMethods"

#pragma region "CM_ControlMethods"
#define CMCase_CMDrivePin								5001
#define CMCase_CMDrivePort								5002
#define CMCase_CMConfigurePXES2780_TriggerBus			5003
#define CMCase_CMSetPortDirection						5004
#pragma endregion "CM_ControlMethods"

#pragma region "RF_CW_ControlMethods"
#define RFCase_SourcePower								2001
#define RFCase_SourcePowerFast							2002
#define RFCase_SourcePowerLow							2003
#define RFCase_SourceTwoTone							2004
#define RFCase_IsolateChannel							2005
#define RFCase_StartModulation							2006
#define RFCase_StopModulation							2007
#define RFCase_SetSourceTriggerRouting					2008
#define RFCase_SetSourceTriggerIn						2009
#define RFCase_SetSourceTriggerOut						2010
#define RFCase_SetMeasureTriggerRouting					2011
#define RFCase_SetMeasureTriggerIn						2012
#define RFCase_RunSourceAlignment						2013
#define RFCase_LoadModulation							2014
#define RFCase_WlanInit									2015
#define RFCase_EvmMeasurementSetup						2016
#define RFCase_SemMeasurementSetup						2017
#define RFCase_MeasureSetup								2018
#define RFCase_MeasureSetupIQ							2019
#define RFCase_TriggerSigenStartModulation				2020
#define RFCase_WolferInit								2021
#define RFCase_WolferSelectPath							2022
#define RFCase_WolferSourcePower						2023
#pragma endregion "RF_CW_ControlMethods"

#pragma region "RF_CW_TestMethods"
#define RFCase_MeasureChannel				2101
#define RFCase_MeasureChannelFast			2102
#define RFCase_MeasureChannelIQ				2103
#define RFCase_MeasureIIP3					2104
#define RFCase_MeasureBurstPower			2105
#define RFCase_MeasureSwitchingTime			2106
#define RFCase_MeasureSParam				2107
#define RFCase_MeasureSParamIQ				2108
#define RFCase_P1dB_DirectSearch			2109
#define RFCase_P1dB_BinarySearch			2110
#define RFCase_PowerServo					2111
#define RFCase_PowerServo_BinarySearch		2112
#define RFCase_PowerServo_LinearSearch		2113
#define RFCase_ReadEvm						2114
#define RFCase_ReadEvmAsync					2115
#define RFCase_ReadSem						2116
#define RFCase_ReadSemAsync					2117
#define RFCase_WlanPowerServo				2118
#define RFCase_WlanResidualEVM				2119
#define RFCase_WolferMeasureChannel			2120
#pragma endregion "RF_CW_TestMethods"

#pragma region "DC_ErrorCode"
#define DC_TestConditionNotFound			11001
#pragma endregion "DC_ErrorCode"

#pragma region "Wlan_Standard"
#define WLAN_ABGN			1
#define WLAN_ACAX			2
#pragma endregion "Wlan_Standard"

/*----------------------------------------------------------------------
* Revision Log
* $Log: Defines.h.rca$

*** Version	: v1.0.0.2
*** Date	: 29 July 2026
*** PIC		: Tham Zhi Kean
* Reorganise TestMethod and ControlMethod constants to follow document sequence

* V1.0.0.1 (14 Nov 2020), LKL
* Included DM500x Opcode defination.
* Included kHz unit prefix under User_Defined_Unit region.

* v1.0.0.0 (20 March 2020), LKL
* Initial release version.
----------------------------------------------------------------------*/