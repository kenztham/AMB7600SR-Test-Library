#pragma once
#include "Defines.h" 

using namespace System;

namespace AppLevelException
{
	public ref class ThorwAppLevelException : Exception
	{

	public: ThorwAppLevelException(String^ message) :Exception(message)

	{
		if (message->Contains("ER_CONST_TestCondition_Not_Found"))
		{
			HResult = ER_CONST_TestCondition_Not_Found;
		}
		else if (message->Contains("ER_CONST_TestCondition_DataType_Invalid"))
		{
			HResult = ER_CONST_TestCondition_DataType_Invalid;
		}
								
	}
	};
}