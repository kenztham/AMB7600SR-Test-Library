#pragma once
/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:						Methods.h
Purpose:					Declare all test library functions.
UUTOffset:					Supported.
TrueParallelUUTOffset:		Supported.
Version	:					1.0.0.0
----------------------------------------------------------------------*/
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Test Function/TestFunction.h"
#include "../Test Function/Aemulus.Hardware.CM.h"
#include "../Test Function/Aemulus.Hardware.SMU.h"
#include "../Test Function/Aemulus.Hardware.DM.h"
#include "../Test Function/Aemulus.Hardware.DIO.h"
#include "../Test Function/Aemulus.Hardware.AMSRF.h"

//#using "C:\Aemulus\techFlow3\bin\libSync.dll" 
//#using "C:\Aemulus\techFlow3\bin\Aemulus.Hardware.ResourceManager.dll" 
//#using "C:\Aemulus\techFlow3\bin\Aemulus.Tech.Flow.Core.dll" 

using namespace System;
using namespace System::Data;
using namespace System::Reflection;
using namespace System::Text::RegularExpressions;

using namespace Aemulus::Hardware;
using namespace Aemulus::Configuration;
using namespace Aemulus::Configuration7600;
using namespace Aemulus::TestLib::RF::Utility;
namespace Functions
{
	//Forward Declaration
	ref class AMB7600SRTestLibrary;
	ref class AMB7300TestLibrary;
	ref class TestFunction;

	public ref class MethodsBranch
	{
	public:
		MethodsBranch::MethodsBranch(TestFunction ^ TestFunc);
		~MethodsBranch(void);

		TestFunction ^ tl;

		AMB7600SRTestLibrary ^ amb7600srtl;
		AMB7300TestLibrary ^ amb7300tl;

		ConcurrentDictionary<String^, int> ^ Dictionary_CM;
		ConcurrentDictionary<String^, int> ^ Dictionary_TM;
		void InitializeCMDictionary(int totalSite);
		void InitializeTMDicionary(int totalSite);
		
		void ControlMethod_Selection(AMB7600SRTestLibrary ^ lib, Site ^ site, int testSite, int controlMethodSelection, ConditionCollection ^ testConditionCollection);
		void ControlMethod_Selection(Site ^ site, int testSite, int controlMethodSelection, ConditionCollection ^ testConditionCollection);
		void TestMethod_Selection(AMB7600SRTestLibrary ^ lib, Site ^ site, int testSite, int testMethodSelection, String ^ testParameterName, int  testParameterCount, int % methodTestParameterCount);
		void TestMethod_Selection(Site ^ site, int testSite, int testMethodSelection, String ^ testParameterName, int  testParameterCount, int % methodTestParameterCount);
	};
}