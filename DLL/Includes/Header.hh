#pragma once

#include "windows.h"
#include <Psapi.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>

extern "C"
{
	__declspec(dllexport) LRESULT CALLBACK 		 KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
}