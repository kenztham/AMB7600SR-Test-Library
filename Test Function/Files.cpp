/*----------------------------------------------------------------------
Copyright (c) Aemulus Corporation Sdn Bhd
Title:			Files.cpp
Purpose:		Contains test functions for file I/O.
UUTOffset:		Supported.
----------------------------------------------------------------------*/

#include "TestFunction.h"

namespace Functions
{
	String ^ TestFunction::GetFileNameFromFullPathName(String^ FullPathName)
	{
		/*****************************************************************************************************
		** GetFileNameFromFullPathName
		**		FullPathName	- This is the full path directory.
		**						  (For example: C:\\Aemulus\\techFlow3\\Projects\\TestRecipes\\SampleProfile\\
		**											tf3p11p2_jcet_x32_vs2005_tcr\\AppsCal.csv)
		**						- Return FileName = "AppsCal"
		** Descriptions:
		**		This method is to get the intended filename from full path name.
		******************************************************************************************************/

		String ^ FileName = String::Empty;

		array<String^>^ ArrStr = gcnew array<String^>(0);
		array<String^>^ Separator = gcnew array<String^>(2);
		Separator[0] = "\\";
		Separator[1] = ".";

		ArrStr = FullPathName->Split(Separator, StringSplitOptions::None);
		FileName = ArrStr[ArrStr->Length - 2];

		return FileName;
	}
	bool TestFunction::IsRunningProduction(Site ^ site)
	{
		/*****************************************************************************************************
		** IsRunningProduction
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This method is to check whether is running production mode as Applications Calibration and
		**		Auto_GU_Correlation_Tool.exe can not run in production mode.
		******************************************************************************************************/

		IProductionSystem^ ps = (IProductionSystem^)site->FlowEngine->EngineManager->GetService(IProductionSystem::typeid);

		if (RemotingServices::IsTransparentProxy(ps))
			return false;
		else
			return true;

	}
	void TestFunction::corrFactorFileInit(Site ^ site)
	{
		try
		{
			//Get AppsWideVariable
			if (tf_AppWideVariable_Exist("gCalibrationMode"))
			{
				cf.gCalibrationMode = (int)(tf_AppWideVariable_Cast("gCalibrationMode"));  //0 = Normal Run, 1 = AutoGUCalTool Run
			}
			else
			{
				cf.gCalibrationMode = 0;
			}

			//0 = CorrFactor File located at TesterInfo Folder, 1 = CorrFactor File located at TestRecipe Folder, 2 = CorrFactor File located at Customized Folder
			if (tf_AppWideVariable_Exist("gCorrFactorFileMode"))
			{
				cf.gCorrFactorFileMode = (int)(tf_AppWideVariable_Cast("gCorrFactorFileMode"));
			}
			else
			{
				cf.gCorrFactorFileMode = 1;
			}

			if (cf.gCorrFactorFileMode == 2)
			{
				if (tf_AppWideVariable_Exist("gCustomCorrFactorPath"))
				{
					cf.gCustomCorrFactorPath = (String^)(tf_AppWideVariable_Cast("gCustomCorrFactorPath"));
				}
				else
				{
					throw gcnew Exception("CustomerCorrFactorPath not defined at App-Wide Variables!");
				}
			}

			//Check if Auto GU Cal Tool is running or normal mode
			if (tf_AppWideVariable_Exist("gCreateCorrfactorFile"))
				cf.gCreateCorrfactorFile = (int)(tf_AppWideVariable_Cast("gCreateCorrfactorFile"));
			else
				cf.gCreateCorrfactorFile = 0;

			ResultOffset = gcnew ConcurrentDictionary<String^, double>();
			//Test Recipe Path
			cf.recipeFilePath = nullptr;

			//CorrFactor Folder and File Location
			cf.corrFactorFolder = nullptr;
			cf.corrFactorFile = nullptr;

			//CorrFactor Folder and File Location (GU Cal)
			cf.corrfactorTesterInfoGUCalPath = nullptr;
			cf.corrFactorTesterInfoGUCalFile = nullptr;

			//CorrFactor Folder and File Location (Test Recipe)
			cf.corrFactorTestRecipePath = nullptr;
			cf.corrFactorTesterInfoGUCalFile = nullptr;

			//CorrFactor Folder and File Location (Custom Path)
			cf.corrFactorCustomPath = nullptr;
			cf.corrFactorCustomFile = nullptr;

			//CorrFactor Folder and File Location (Empty or Newly Generated)
			cf.corrFactorEmptyFolder = nullptr;
			cf.corrFactorEmptyFile = nullptr;

			//Get Info
			cf.testerID = site->FlowEngine->StationName;							//Get Current Tester ID	
			cf.techflowSite = site->Index;												//Get Techflow Site	
			cf.recipeFilePath = Path::GetDirectoryName(site->Recipe->RecipeFilePath);		//Get Test Recipe File Path
			cf.projectName = Path::GetFileName(cf.recipeFilePath);						//Get Project Name 
			cf.programName = Path::GetFileName(site->DBPath);							//Get Program Name
			cf.corrFactorEmptyFile = nullptr;// site->GetExternalDependency("CorrFactor");				//CorrFactor File that comes with TPKG with empty value

			cf.totalTestParameterCount = site->TestParameters->Count;
			cf.totalTestSiteCount = glob->tf.TotalUUTOffsets;  //Multi-UUT Count

													  //Get Path of CorrFactor in TesterInfo GU Cal Folder
			if (cf.gCorrFactorFileMode == 0)
			{
				cf.corrfactorTesterInfoGUCalPath = cf.recipeFilePath->Replace("C:\\Aemulus\\techFlow3\\Projects\\TestRecipes", "C:\\Aemulus\\TesterInfo\\GU_Cal");
				cf.corrFactorTesterInfoGUCalFile = cf.corrfactorTesterInfoGUCalPath + "\\CorrFactor_S" + cf.techflowSite.ToString() + ".csv";
				cf.corrFactorFolder = cf.corrfactorTesterInfoGUCalPath;
				cf.corrFactorFile = cf.corrFactorTesterInfoGUCalFile;
			}
			//Get Path of CorrFactor in Test Recipe Folder
			else if (cf.gCorrFactorFileMode == 1)
			{
				cf.corrFactorTestRecipePath = cf.recipeFilePath + "\\CorrFactor";
				cf.corrFactorTestRecipeFile = cf.corrFactorTestRecipePath + "\\CorrFactor_S" + cf.techflowSite.ToString() + ".csv";
				cf.corrFactorFolder = cf.corrFactorTestRecipePath;
				cf.corrFactorFile = cf.corrFactorTestRecipeFile;
			}
			//Get Path of CorrFactor in Customer Folder
			else if (cf.gCorrFactorFileMode == 2)
			{
				cf.corrFactorCustomPath = cf.gCustomCorrFactorPath;
				cf.corrFactorCustomFile = cf.corrFactorCustomPath + "\\CorrFactor_S" + cf.techflowSite.ToString() + ".csv";
				cf.corrFactorFolder = cf.corrFactorCustomPath;
				cf.corrFactorFile = cf.corrFactorCustomFile;
			}
			else
			{
				throw gcnew Exception("Invalid CorrFactorFileMode at App-Wide Variables!");
			}

			//Will Auto Create corr_factor.csv at Test Recipe File if AppsWideVariable:gCreateCorrfactorFile is set to 1.
			corrFactorFileCreate(site);

#pragma region "Check existance of Corrfactor file and folder"

			//Check if CorrFactor file Exist
			if (!File::Exists(cf.corrFactorFile))
			{
				MessageBox::Show(cf.corrFactorFile + " does not exist!", "Corrfactor File Checking");

				if (!Directory::Exists(cf.corrFactorFolder))
				{
					MessageBox::Show(cf.corrFactorFolder + " Folder does not exist!", "Corrfactor Folder Checking");
					Directory::CreateDirectory(cf.corrFactorFolder);
					MessageBox::Show(cf.corrFactorFolder + " has been created!", "Corrfactor Folder Creation");
				}

				//File::Copy(cf.corrFactorEmptyFile, cf.corrFactorFile);

				//MessageBox::Show(cf.corrFactorEmptyFile + " has been copied to " + cf.corrFactorFile, "Corrfactor File Copy");
				cf.gCreateCorrfactorFile = 1;  //Force Creation
				corrFactorFileCreate(site);
			}

#pragma endregion "Check existance of Corrfactor file and folder"

			//Get initial time
			cf.dateTimeInit = File::GetLastWriteTime(cf.corrFactorFile);

#pragma region "Get total corrfactor"

			//Get total Site available in offset file and get total number of factors
			StreamReader ^ sr = gcnew StreamReader(cf.corrFactorFile);
			String ^ line;
			array<String^> ^ arrStr;
			array<Char>^ Spliter = { ',' };

			while ((line = sr->ReadLine()) != nullptr)
			{
				arrStr = line->Split(Spliter, System::StringSplitOptions::None);

				if (line->StartsWith("//"))
				{
					cf.totalSite = arrStr->Length - 2;
				}
				else
				{
					cf.totalFactor++;
				}
			}

			sr->Close();
			sr = nullptr;
			line = nullptr;

			if (cf.totalFactor != cf.totalTestParameterCount)
			{
				throw gcnew Exception("Number of corrfactors available in Corrfactor File does not match with number of test parameters!");
			}

			if (cf.totalSite != cf.totalTestSiteCount)
			{
				throw gcnew Exception("Number of test sites available in Corrfactor File does not match with number of Multi-UUT count!");
			}

#pragma endregion "Get total corrfactor"

#pragma region "Read corrfactor"

			//Initiate CorrFactor variales
			cf.CorrFactor = gcnew array<double, 2>(cf.totalSite, cf.totalFactor);

			cf.index = gcnew array<int>(cf.totalFactor);
			cf.testParameter = gcnew array<String^>(cf.totalFactor);
			cf.corrFileTesterID = gcnew array<String^>(cf.totalFactor);

			array<String^>^ key = gcnew array<String^>(cf.totalFactor);
			//Read and Load corrfactors into CorrFactor Variable

			int i = 0;

			try
			{
				sr = gcnew StreamReader(cf.corrFactorFile);

				while ((line = sr->ReadLine()) != nullptr)
				{
					arrStr = line->Split(Spliter, System::StringSplitOptions::None);


					if (!line->StartsWith("//"))
					{
						cf.index[i] = int::Parse(arrStr[0]);
						cf.testParameter[i] = arrStr[1];
						key[i] = cf.testParameter[i];

						for (int site = 0; site < cf.totalSite; site++)
						{
							cf.CorrFactor[site, i] = double::Parse(arrStr[2 + site]);
						}
						i++;  //Next Line
					}
				}
			}
			catch (Exception^ex)
			{
				throw gcnew Exception("Failed to read corr_factor.csv file, please check the format!");
			}

			sr->Close();
			sr = nullptr;
			line = nullptr;

#pragma endregion "Read corrfactor"

#pragma region "Store corrfactor into Dictionary"

			String^ key1;

			for (int i = 0; i < cf.totalFactor; i++)
			{
				for (int s = 0; s < cf.totalSite; s++)
				{
					key1 = cf.testParameter[i] + "_" + s.ToString();

					if (ResultOffset->ContainsKey(key1))
					{
						ResultOffset[key1] = cf.CorrFactor[s, i];
					}
					else
					{
						ResultOffset->TryAdd(key1, cf.CorrFactor[s, i]);
					}
				}

			}

#pragma endregion "Store corrfactor into Dictionary"

		}
		catch (Exception ^ ex)
		{
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			glob->TcrLgr.ErrorCode = ER_CONST_CorrFactorInfo;
			ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
		}

	}
	void TestFunction::corrFactorFileCreate(Site ^ site)
	{
		try
		{
			if (cf.gCreateCorrfactorFile == 1)
			{
				cf.corrFactorEmptyFolder = cf.corrFactorFolder + "\\CorrFactor\\";

				////Check if the CorrFactor folder exist in Test Recipe Folder
				//if (!File::Exists(cf.corrFactorEmptyFolder))
				//{
				//	MessageBox::Show(cf.corrFactorEmptyFolder + " does not exist!", "Corrfactor Folder Checking");
				//	Directory::CreateDirectory(cf.corrFactorEmptyFolder);
				//	MessageBox::Show(cf.corrFactorEmptyFolder + " has been created!", "Corrfactor Folder Creation");
				//}

				StringBuilder ^ sb = gcnew StringBuilder();
				StreamWriter ^ sw = gcnew StreamWriter(cf.corrFactorFile);

				//First Line
				String ^ firstLine = firstLine = "//Index,Identified";

				for (int site = 0; site < cf.totalTestSiteCount; site++)
				{
					firstLine = firstLine + ",S" + site.ToString();
				}

				sb->AppendLine(firstLine);

				for (int i = 0; i < cf.totalTestParameterCount; i++)
				{
					//sb->Append("TesterID" + ",");  //or set as cf.testerID
					sb->Append(i.ToString() + ",");
					sb->Append(site->TestParameters[i]->DisplayName);

					for (int site = 0; site < cf.totalTestSiteCount; site++)
					{
						sb->Append(",0");
					}

					sb->AppendLine();
				}

				sw->Write(sb);
				sb = nullptr;
				sw->Close();

				MessageBox::Show(cf.corrFactorFile + " has been generated!", "Corrfactor File Generation");
			}
		}
		catch (Exception ^ ex)
		{
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			glob->TcrLgr.ErrorCode = ER_CONST_CorrFactorInfo;
			ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void TestFunction::corrFactorLoad(Site ^ site)
	{
		try
		{
			//Check if corr_Factor.csv Exist
			if (!File::Exists(cf.corrFactorFile))
			{
				throw gcnew Exception(cf.corrFactorFile + "does not exist!");
			}

#pragma region "Read corrfactor"

			//Initiate CorrFactor variales
			cf.CorrFactor = gcnew array<double, 2>(cf.totalSite, cf.totalFactor);
			cf.index = gcnew array<int>(cf.totalFactor);
			cf.testParameter = gcnew array<String^>(cf.totalFactor);
			cf.corrFileTesterID = gcnew array<String^>(cf.totalFactor);

			StreamReader ^ sr = gcnew StreamReader(cf.corrFactorFile);
			String ^ line;
			array<String^> ^ arrStr;
			array<Char>^ Spliter = { ',' };
			String^ key;

			//Read and Load corrfactors into CorrFactor Variable

			int i = 0;

			try
			{
				StreamReader ^ sr = gcnew StreamReader(cf.corrFactorFile);

				while ((line = sr->ReadLine()) != nullptr)
				{
					arrStr = line->Split(Spliter, System::StringSplitOptions::None);

					if (!line->StartsWith("//"))
					{
						cf.index[i] = int::Parse(arrStr[0]);
						cf.testParameter[i] = arrStr[1];


						for (int site = 0; site < cf.totalSite; site++)
						{
							cf.CorrFactor[site, i] = double::Parse(arrStr[2 + site]);
							key = cf.testParameter[i] + "_" + site.ToString();

							if (ResultOffset->ContainsKey(key))
							{
								ResultOffset[key] = cf.CorrFactor[site, i];
							}
							else
							{
								ResultOffset->TryAdd(key, cf.CorrFactor[site, i]);
							}
						}
						i++;  //Next Line
					}
				}
			}
			catch (Exception^ex)
			{
				throw gcnew Exception("Failed to read corr_factor.csv file, please check the format!");
			}

			sr->Close();
			sr = nullptr;
			line = nullptr;

#pragma endregion "Read corrfactor"
		}
		catch (Exception ^ ex)
		{
			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			glob->TcrLgr.ErrorCode = ER_CONST_CorrFactorInfo;
			ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
		}
	}
	double TestFunction::GetCorrFactor(String^ TPName, int testSite)
	{
		double offset = 0.0;

		ResultOffset->TryGetValue(TPName + "_" + testSite.ToString(), offset);

		return offset;
	}
	void TestFunction::boardLossFileInit(Site^ site)
	{
		String^ BoardLossFile = glob->tf.RecipeFilePathDirectory + "\\BoardLoss\\Head" + site->FlowEngine->HeadNumber.ToString() + "\\BoardLoss_Site" + site->Index.ToString() + ".csv";
		String^ ErrorMessage = nullptr;
		try
		{
			////////////////////////////////////////////////////////////////////////////////////////////////
			//1.  Checking the exist of the BoardLoss File
			////////////////////////////////////////////////////////////////////////////////////////////////
			if (!File::Exists(BoardLossFile))
			{
				ErrorMessage = "Cannot found the BoardLoss.csv file at the path" + BoardLossFile + ".";
				throw gcnew Exception(ErrorMessage);
			}
			else
			{
				for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
				{
					WriteToTcrLgr("SITE " + siteIndex.ToString(), "Loading BoardLoss.....");
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			//2.  Get total set of the boardloss value
			////////////////////////////////////////////////////////////////////////////////////////////////
			StreamReader ^ sr = gcnew StreamReader(BoardLossFile);

			String ^ line = String::Empty;
			int totalSetBoardLoss = 0;

			while ((line = sr->ReadLine()) != nullptr)
			{
				totalSetBoardLoss++;
			}
			totalSetBoardLoss = totalSetBoardLoss - 1;
			sr->Close();
			sr = nullptr;

			////////////////////////////////////////////////////////////////////////////////////////////////
			//3.  Set up storage
			////////////////////////////////////////////////////////////////////////////////////////////////
			array<String ^> ^ key = gcnew array<String ^>(totalSetBoardLoss);
			array<array<double>^>^ BoardlossValue = gcnew array<array<double>^>(glob->tf.NumberOfSites);

			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				BoardlossValue[i] = gcnew array<double>(totalSetBoardLoss);
			}

			for (int i = 0; i < totalSetBoardLoss; i++)
			{
				key[i] = String::Empty;
			}

			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				for (int j = 0; j < totalSetBoardLoss; j++)
				{
					BoardlossValue[i][j] = 0.0;
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			//4.  Read from board loss file
			////////////////////////////////////////////////////////////////////////////////////////////////
			sr = gcnew StreamReader(BoardLossFile);

			int LossFactorCount = 0;
			int lineInfo = glob->tf.NumberOfSites + 1;
			array<String^>^ ArrStr;
			array<Char>^ Spliter = { ',' };
			int lineCount = 0;

			while ((line = sr->ReadLine()) != nullptr)
			{
				ArrStr = line->Split(Spliter, System::StringSplitOptions::None);

				lineCount++;

				if (ArrStr->Length < lineInfo)
				{
					ErrorMessage = "BoardLossFile line_number " + lineCount.ToString() + " does not contain correct format!";
					throw gcnew Exception(ErrorMessage);
				}

				if (ArrStr[0] != "Item")
				{
					key[LossFactorCount] = ArrStr[0];
					for (int i = 0; i < glob->tf.NumberOfSites; i++)
					{
						int ArrStrIndex = i + 1;
						BoardlossValue[i][LossFactorCount] = Convert::ToDouble(ArrStr[ArrStrIndex]);
					}
					LossFactorCount++;
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			//5.  Cast the key and boardloss to dictionary
			////////////////////////////////////////////////////////////////////////////////////////////////
			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				for (int j = 0; j < totalSetBoardLoss; j++)
				{
					glob->boardLoss[i]->Add(key[j], BoardlossValue[i][j]);
				}
			}

			for (int siteIndex = 0; siteIndex < glob->tf.NumberOfSites; siteIndex++)
			{
				WriteToTcrLgr("SITE " + siteIndex.ToString(), "Done Loading BoardLoss.....");
			}
		}
		catch (Exception ^ ex)
		{

			glob->TcrLgr.GlobalErrorMessage = ex->ToString();
			glob->TcrLgr.ErrorCode = ER_CONST_BoardLossInfo;
			ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
		}
	}
	void TestFunction::boardLossFileLoad(Site^ site)
	{
		if (glob->AWV.BoardLossMode == 1)
		{
			String^ BoardLossFile = glob->tf.RecipeFilePathDirectory + "\\BoardLoss\\Head" + site->FlowEngine->HeadNumber.ToString() + "\\BoardLoss_Site" + site->Index.ToString() + ".csv";
			String^ ErrorMessage = nullptr;
			try
			{
				////////////////////////////////////////////////////////////////////////////////////////////////
				//1.  Checking the exist of the BoardLoss File
				////////////////////////////////////////////////////////////////////////////////////////////////
				if (!File::Exists(BoardLossFile))
				{
					ErrorMessage = "Cannot found the BoardLoss.csv file at the path" + BoardLossFile + ".";
					throw gcnew Exception(ErrorMessage);
				}

				////////////////////////////////////////////////////////////////////////////////////////////////
				//2.  Get total set of the boardloss value
				////////////////////////////////////////////////////////////////////////////////////////////////
				StreamReader ^ sr = gcnew StreamReader(BoardLossFile);

				String ^ line = String::Empty;
				int totalSetBoardLoss = 0;

				while ((line = sr->ReadLine()) != nullptr)
				{
					totalSetBoardLoss++;
				}
				totalSetBoardLoss = totalSetBoardLoss - 1;
				sr->Close();
				sr = nullptr;

				////////////////////////////////////////////////////////////////////////////////////////////////
				//3.  Set up storage
				////////////////////////////////////////////////////////////////////////////////////////////////
				array<String ^> ^ key = gcnew array<String ^>(totalSetBoardLoss);
				array<array<double>^>^ BoardlossValue = gcnew array<array<double>^>(glob->tf.NumberOfSites);

				for (int i = 0; i < glob->tf.NumberOfSites; i++)
				{
					BoardlossValue[i] = gcnew array<double>(totalSetBoardLoss);
				}

				for (int i = 0; i < totalSetBoardLoss; i++)
				{
					key[i] = String::Empty;
				}

				for (int i = 0; i < glob->tf.NumberOfSites; i++)
				{
					for (int j = 0; j < totalSetBoardLoss; j++)
					{
						BoardlossValue[i][j] = 0.0;
					}
				}

				////////////////////////////////////////////////////////////////////////////////////////////////
				//4.  Read from board loss file
				////////////////////////////////////////////////////////////////////////////////////////////////
				sr = gcnew StreamReader(BoardLossFile);

				int LossFactorCount = 0;
				int lineInfo = glob->tf.NumberOfSites + 1;
				array<String^>^ ArrStr;
				array<Char>^ Spliter = { ',' };
				int lineCount = 0;

				while ((line = sr->ReadLine()) != nullptr)
				{
					ArrStr = line->Split(Spliter, System::StringSplitOptions::None);

					lineCount++;

					if (ArrStr->Length < lineInfo)
					{
						ErrorMessage = "BoardLossFile line_number " + lineCount.ToString() + " does not contain correct format!";
						throw gcnew Exception(ErrorMessage);
					}

					if (ArrStr[0] != "Item")
					{
						key[LossFactorCount] = ArrStr[0];
						for (int i = 0; i < glob->tf.NumberOfSites; i++)
						{
							int ArrStrIndex = i + 1;
							BoardlossValue[i][LossFactorCount] = Convert::ToDouble(ArrStr[ArrStrIndex]);
						}
						LossFactorCount++;
					}
				}

				////////////////////////////////////////////////////////////////////////////////////////////////
				//5.  Cast the key and boardloss to dictionary
				////////////////////////////////////////////////////////////////////////////////////////////////
				for (int i = 0; i < glob->tf.NumberOfSites; i++)
				{
					for (int j = 0; j < totalSetBoardLoss; j++)
					{
						if (!glob->boardLoss[i]->ContainsKey(key[j]))
						{
							glob->boardLoss[i]->Add(key[j], BoardlossValue[i][j]);
						}
						else
						{
							glob->boardLoss[i]->Remove(key[j]);
							glob->boardLoss[i]->Add(key[j], BoardlossValue[i][j]);
						}
					}
				}

			}
			catch (Exception ^ ex)
			{

				glob->TcrLgr.GlobalErrorMessage = ex->ToString();
				glob->TcrLgr.ErrorCode = ER_CONST_BoardLossInfo;
				ErrorHandling(site, glob->TcrLgr.GlobalErrorMessage);
			}
		}
	}

}

/*----------------------------------------------------------------------
* Revision Log
* $Log: Files.cpp.rca$


* v1.0.0.0 (20 March 2020), LKL
* Initial release version.
----------------------------------------------------------------------*/
