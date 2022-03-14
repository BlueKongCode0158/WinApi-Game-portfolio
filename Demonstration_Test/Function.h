#pragma once
#include "MyUI.h"
#include "MyButton.h"
#include "Text.h"
#include "Title.h"

template<class T>
void Safe_Delete(T& rObj)
{
	if (rObj)
	{
		delete rObj;
		rObj = nullptr;
	}
}