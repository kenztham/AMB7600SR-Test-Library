#include "TestFunction.h"
#include "TF-Macro.h"

namespace Functions
{
	int TestFunction::DoThread(ParameterizedThreadStart^ function, Site^ site)
	{
		int ret = 0, ThreadNumber = 0;
		List<TestProgramData^>^ tpdatas = gcnew List<TestProgramData^>();
		array<bool>^ run_test = gcnew array<bool>(glob->tf.NumberOfSites);
		glob->tf.isRunTest = gcnew array<bool>(glob->tf.NumberOfSites);
		AFlowItem^ item = site->CurrentFlowItem;
		Type^ FlowType = item->GetType();

		try
		{
			IsRunTest(site, run_test);
			glob->tf.isRunTest = run_test;

			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				if (run_test[i])
				{
					Util->CreateNewThread(site, function, tpdatas, i);
				}
			}

			for each(TestProgramData^ tpdata in tpdatas)
			{
				tpdata->Thread->Join();
				if (tpdata->Exception != nullptr)
				{
					//Exception is found in the test method
					glob->runTimeError[tpdata->siteIndex] = true;
					ret = tpdata->ErrorCode != 0 ? tpdata->ErrorCode : -1;
				}
			}
		}
		finally
		{
			Util->ClearThread(tpdatas);
		}

		return ret;
	}
	int TestFunction::DoThreadHardware(ParameterizedThreadStart^ function, Site^ site)
	{
		int ret = 0, ThreadNumber = 0;
		List<TestProgramData^>^ tpdatas = gcnew List<TestProgramData^>();
		AFlowItem^ item = site->CurrentFlowItem;
		Type^ FlowType = item->GetType();

		try
		{
			for (int i = 0; i < glob->TotalThread; i++)
			{
				Util->CreateNewThread(site, function, tpdatas, i);
			}

			for each(TestProgramData^ tpdata in tpdatas)
			{
				tpdata->Thread->Join();
				if (tpdata->Exception != nullptr)
				{
					//Exception is found in the test method
					glob->runTimeError[tpdata->siteIndex] = true;
					ret = tpdata->ErrorCode != 0 ? tpdata->ErrorCode : -1;
				}
			}
		}
		finally
		{
			Util->ClearThread(tpdatas);
		}

		return ret;
	}
	int TestFunction::DoThreadRunPattern(ParameterizedThreadStart^ function, Site^ site, int testSitePerDC)
	{
		/*****************************************************************************************************
		** DoThread
		**		function	- This is ParameterizedThreadStart object.
		**		site	- This is techFlow site object.
		** Descriptions:
		**		This method is used to create threads based on number of test sites (or UUT Offsets) set in
		**		techFlow test recipe.
		******************************************************************************************************/

		int ret = 0;
		int totalThreadNum = 0;
		bool DCFirstSiteDisable = false;
		List<TestProgramData^>^ tDs = gcnew List<TestProgramData^>();
		array<bool>^ run_test = gcnew array<bool>(glob->tf.NumberOfSites);
		glob->tf.isRunTest = gcnew array<bool>(glob->tf.NumberOfSites);

		try
		{
			IsRunTest(site, run_test);
			glob->tf.isRunTest = run_test;

			/* Create up to 3 thread max (3 DC max per DM582x)
			* Create dedicated thread based on the number of test site oer DC, since functional test will thread/ run in paralle with DC */

			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				if (i % testSitePerDC != 0)
				{
					if (DCFirstSiteDisable == true && run_test[i] == true)
					{
						run_test[i] = true;
						DCFirstSiteDisable = false; //Run once per DC will do 
					}
					else
					{
						run_test[i] = false;
					}
				}
				else
				{
					// Check the run test property of each DC's first site, if false need to change DCFirstSiteDisable flag 
					if (run_test[i] == false)
					{
						DCFirstSiteDisable = true;
					}
				}

				if (run_test[i])
				{
					Util->CreateNewThread(site, function, tDs, i);
				}
			}

			for each(TestProgramData^ tD in tDs)
			{
				tD->Thread->Join();
				if (tD->Exception != nullptr)
				{
					//Exception is found in the test method
					glob->runTimeError[tD->siteIndex] = true;
					ret = tD->ErrorCode != 0 ? tD->ErrorCode : -1;
				}
			}
		}
		finally
		{
			Util->ClearThread(tDs);
		}

		return ret;
	}
	int TestFunction::DoThreadRunAllSites(ParameterizedThreadStart^ function, Site^ site)
	{
		//Only used in seq_DeviceActive and seq_DeviceInActive
		int ret = 0;
		List<TestProgramData^>^ tpdatas = gcnew List<TestProgramData^>();
		array<bool>^ run_test = gcnew array<bool>(glob->tf.NumberOfSites);

		try
		{
			for (int i = 0; i < glob->tf.NumberOfSites; i++)
			{
				//If runTimeError is true, it means that previous has already run ResetTesterSite function
				if (glob->runTimeError[i] == false && glob->isPreviewPass[i] == false)
				{
					Util->CreateNewThread(site, function, tpdatas, i);
				}
			}

			for each(TestProgramData^ tpdata in tpdatas)
			{
				tpdata->Thread->Join();
				if (tpdata->Exception != nullptr)
				{
					//Exception is found in the test method
					glob->runTimeError[tpdata->siteIndex] = true;
					ret = tpdata->ErrorCode != 0 ? tpdata->ErrorCode : -1;
				}
			}
		}
		finally
		{
			Util->ClearThread(tpdatas);
		}

		return ret;
	}
	//int TestFunction::DoThread(ParameterizedThreadStart^ function, Site^ site)
	//{
	//	int ret = 0, ThreadNumber = 0;
	//	List<TestProgramData^>^ tpdatas = gcnew List<TestProgramData^>();
	//	array<bool>^ run_test = gcnew array<bool>(glob->tf.NumberOfSites);
	//	glob->tf.isRunTest = gcnew array<bool>(glob->tf.NumberOfSites);
	//	AFlowItem^ item = site->CurrentFlowItem;
	//	Type^ FlowType = item->GetType();

	//	try
	//	{
	//		IsRunTest(site, run_test);
	//		glob->tf.isRunTest = run_test;

	//		for (int i = 0; i < glob->tf.NumberOfSites; i++)
	//		{
	//			if (run_test[i])
	//			{
	//				Util->CreateNewThread(site, function, tpdatas, i);
	//			}
	//		}

	//		for each(TestProgramData^ tpdata in tpdatas)
	//		{
	//			tpdata->Thread->Join();
	//			if (tpdata->Exception != nullptr)
	//			{
	//				//Exception is found in the test method
	//				glob->runTimeError[tpdata->siteIndex] = true;
	//			}
	//		}
	//	}
	//	finally
	//	{
	//		Util->ClearThread(tpdatas);
	//	}

	//	return ret;
	//}
	//int TestFunction::DoThreadRunPattern(ParameterizedThreadStart^ function, Site^ site, int testSitePerDC)
	//{
	//	/*****************************************************************************************************
	//	** DoThread
	//	**		function	- This is ParameterizedThreadStart object.
	//	**		site	- This is techFlow site object.
	//	** Descriptions:
	//	**		This method is used to create threads based on number of test sites (or UUT Offsets) set in
	//	**		techFlow test recipe.
	//	******************************************************************************************************/

	//	int ret = 0;
	//	int totalThreadNum = 0;
	//	bool DCFirstSiteDisable = false; 
	//	List<TestProgramData^>^ tDs = gcnew List<TestProgramData^>();
	//	array<bool>^ run_test = gcnew array<bool>(glob->tf.NumberOfSites);
	//	glob->tf.isRunTest = gcnew array<bool>(glob->tf.NumberOfSites);

	//	try
	//	{
	//		IsRunTest(site, run_test);
	//		glob->tf.isRunTest = run_test; 

	//		/* Create up to 3 thread max (3 DC max per DM582x)
	//		* Create dedicated thread based on the number of test site oer DC, since functional test will thread/ run in paralle with DC */

	//		for (int i = 0; i < glob->tf.NumberOfSites; i++)
	//		{
	//			if (i % testSitePerDC != 0)
	//			{
	//				if (DCFirstSiteDisable == true && run_test[i] == true)
	//				{
	//					run_test[i] = true;
	//					DCFirstSiteDisable = false; //Run once per DC will do 
	//				}
	//				else
	//				{
	//					run_test[i] = false;
	//				}
	//			}
	//			else
	//			{
	//				// Check the run test property of each DC's first site, if false need to change DCFirstSiteDisable flag 
	//				if (run_test[i] == false)
	//				{
	//					DCFirstSiteDisable = true; 
	//				}
	//			}

	//			if (run_test[i])
	//			{
	//				Util->CreateNewThread(site, function, tDs, i);
	//			}
	//		}

	//		for each(TestProgramData^ tD in tDs)
	//		{
	//			tD->Thread->Join();
	//			if (tD->Exception != nullptr)
	//			{
	//				//Exception is found in the test method
	//				glob->runTimeError[tD->siteIndex] = true;
	//			}
	//		}
	//	}
	//	finally
	//	{
	//		Util->ClearThread(tDs);
	//	}

	//	return ret;
	//}
	//int TestFunction::DoThreadRunAllSites(ParameterizedThreadStart^ function, Site^ site)
	//{
	//	//Only used in seq_DeviceActive and seq_DeviceInActive
	//	int ret = 0;
	//	List<TestProgramData^>^ tpdatas = gcnew List<TestProgramData^>();
	//	array<bool>^ run_test = gcnew array<bool>(glob->tf.NumberOfSites);

	//	try
	//	{
	//		for (int i = 0; i < glob->tf.NumberOfSites; i++)
	//		{
	//			//If runTimeError is true, it means that previous has already run ResetTesterSite function
	//			if (glob->runTimeError[i] == false && glob->isPreviewPass[i] == false)
	//			{
	//				Util->CreateNewThread(site, function, tpdatas, i);
	//			}
	//		}

	//		for each(TestProgramData^ tpdata in tpdatas)
	//		{
	//			tpdata->Thread->Join();
	//			if (tpdata->Exception != nullptr)
	//			{
	//				//Exception is found in the test method
	//				glob->runTimeError[tpdata->siteIndex] = true;
	//			}
	//		}
	//	}
	//	finally
	//	{
	//		Util->ClearThread(tpdatas);
	//	}

	//	return ret;
	//}
}