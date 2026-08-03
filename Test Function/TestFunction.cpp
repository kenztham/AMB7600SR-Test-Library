/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			TestFunction.cpp
Purpose:		Contains constructor and destructor.
UUTOffset:		Supported.
Version:		v1.1.0.0
----------------------------------------------------------------------*/

#include "TestFunction.h"

namespace Functions
{
	TestFunction::TestFunction()
	{
		glob = gcnew Globals();
		glob->AWV.Offline = false;
		glob->AWV.Debug = false;
		glob->AWV.PowerLineFreq = 50;
		glob->HardwareProfile = String::Empty;
		glob->tf.TestHead = 0;
		glob->tf.TestSite = 0;
		glob->tf.TotalUUTOffsets = 0;

		glob->TesterId = String::Empty;
		glob->HardwareProfile = String::Empty;
	}
	TestFunction::~TestFunction(void)
	{

	}

	//RTPlotter Utility
	void TestFunction::RTPlotter(Site ^ site, int siteIndex, String ^ xLabel, String ^ yLabel, String ^ Filename, Object ^ yData)
	{
		/*****************************************************************************************************
		** Real Time Plotter
		******************************************************************************************************/

		try 
		{
			String ^ fullFileName = Filename + ".dat";

			if (glob->tf._RTPlotter) 
			{
				glob->tf.plotterPath = "C:\\Aemulus\\techFlow3\\Projects\\VSProjects\\" + glob->tf.ProfileName + "\\" + glob->tf.ProjectName + "\\" +
					glob->tf.ProjectName + "\\RTPlotter\\";
				// Auto create the dat file 
				glob->FileLog.datFileLgr = gcnew Aemulus::TestLib::Utility::FileLogger(Path::GetDirectoryName(glob->tf.plotterPath));
			}
			glob->FileLog.traceMessage = yData->ToString();
			glob->FileLog.datFileLgr->WriteToFile(fullFileName, glob->FileLog.traceMessage, LOGGER_CONST_APPEND);

			// Instanstiate RTPlotter 
			if (glob->tf._RTPlotter) 
			{
				// Define and configure all the plot setting in gnuplot.exe 
				glob->FileLog.iniFileLgr = gcnew Aemulus::TestLib::Utility::FileLogger(Path::GetDirectoryName(glob->tf.plotterPath));
				glob->FileLog.traceMessage = "LogEnabled=true\n" +
					"set grid\n" +
					"set autoscale\n" +
					"set style data points\n" +
					"set ylabel \"" + yLabel + "\"\n" +
					"set xlabel \"" + xLabel + "\"\n";
				glob->FileLog.iniFileLgr->WriteToFile(FILE_CONST_BAT_RTPLOTTER_INI, glob->FileLog.traceMessage, LOGGER_CONST_OVERWRITE);

				// Configure RTPlotterSetup.bat 
				glob->FileLog.batFileLgr = gcnew Aemulus::TestLib::Utility::FileLogger(Path::GetDirectoryName(glob->tf.plotterPath));
				glob->FileLog.traceMessage = "@echo off\n" +
					"cd " + glob->tf.plotterPath + "\n" +
					"@echo off\n" +
					"start /d " + glob->tf.plotterPath + "\ RTPlot.exe " + Filename + ".dat";
				glob->FileLog.batFileLgr->WriteToFile(FILE_CONST_BAT_RTPLOTTER, glob->FileLog.traceMessage, LOGGER_CONST_OVERWRITE);

				int exeCount = 0;
				array<System::Diagnostics::Process ^ >^ processes = System::Diagnostics::Process::GetProcesses();

				// Check the gnuplot.exe processes; exit function if gnuplot.exe(s) run in background 
				for each (System::Diagnostics::Process ^ EachProcess in processes) 
				{
					if (EachProcess->ProcessName->Contains("gnuplot.exe")) 
					{
						WriteToLogger(siteIndex, ">> gnuplot.exe[" + exeCount + "] running in background...");
						exeCount++;
					}
				}
				// Call RTPlotterSetup.bat 
				System::Diagnostics::Process ^ process = gcnew System::Diagnostics::Process();
				process->StartInfo->UseShellExecute = false;
				process->StartInfo->FileName = glob->tf.plotterPath + FILE_CONST_BAT_RTPLOTTER;
				process->Start();
				process->WaitForExit();
				glob->tf._RTPlotter = false;
			}
		}
		catch (Exception^ ex) 
		{
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			CheckError(siteIndex, ER_CONST_RTPLOTTER);
		}
	}
	void TestFunction::UnloadRTPlotter(int siteIndex)
	{
		/*****************************************************************************************************
		** Unload/end the processes of Real Time Plotter (RTPlot.exe and gnuplot.exe)
		******************************************************************************************************/

		try 
		{
			// Instanstiate RTPlotter 
			glob->FileLog.batFileLgr = gcnew Aemulus::TestLib::Utility::FileLogger(Path::GetDirectoryName(glob->tf.plotterPath));
			glob->FileLog.traceMessage = "@echo off\n" +
				"cd " + glob->tf.plotterPath + "\n" +
				"@echo off\n" +
				"taskkill /IM RTPlot.exe /F\n" +
				"timeout 3\n" +
				"taskkill /IM gnuplot.exe /F\n";

			glob->FileLog.batFileLgr->WriteToFile(FILE_CONST_BAT_RTPLOTTER, glob->FileLog.traceMessage, LOGGER_CONST_OVERWRITE);

			int exeCount = 0;
			int _exeCount = 0;
			array<System::Diagnostics::Process ^ >^ processes = System::Diagnostics::Process::GetProcesses();

			// Check the gnuplot.exe processes; exit function if gnuplot.exe(s) run in background 
			for each (System::Diagnostics::Process ^ EachProcess in processes) 
			{
				if (EachProcess->ProcessName->Contains("gnuplot.exe")) 
				{
					WriteToLogger(siteIndex, ">> Un-loaded gnuplot.exe[" + exeCount + "]");
					exeCount++;
				}
				else if (EachProcess->ProcessName->Contains("RTPlot.exe")) 
				{
					WriteToLogger(siteIndex, ">> Un-loaded RTPlot.exe[" + exeCount + "]");
					_exeCount++;
				}
			}
			// Call RTPlotterSetup.bat (contains the taskkill /IM RTPlot.exe /F and taskkill /IM gnuplot.exe /F)
			System::Diagnostics::Process ^ process = gcnew System::Diagnostics::Process();
			process->StartInfo->UseShellExecute = false;
			process->StartInfo->FileName = glob->tf.plotterPath + FILE_CONST_BAT_RTPLOTTER;
			process->Start();
			process->WaitForExit();
			glob->tf._RTPlotter = false;
		}
		catch (Exception^ ex) 
		{
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			CheckError(siteIndex, ER_CONST_RTPLOTTER);
		}
	}

}


/*----------------------------------------------------------------------
* Revision Log
* $Log: TestFunction.cpp.rca$


* v1.0.0.0 (20 March 2020), LKL
* Initial release version.

* v1.0.0.1 (03 November 2020), LKL
* Added RTPlotter utility functions.

* v1.1.0.0 (29 Jan 2021), LKL 
* Added OperatioSett value struct instantiation in TestFunction constructor. 
----------------------------------------------------------------------*/

