#pragma once

#include "windows.h"
#include <Psapi.h>
#include <cstdio>
#include <tlhelp32.h>
#include <time.h>
#include <share.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

extern "C"
{
	__declspec(dllexport) LRESULT CALLBACK 		 KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
}