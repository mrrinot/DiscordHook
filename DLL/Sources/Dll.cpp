#include "Header.hh"

#pragma data_seg (".myseg")
bool g_isActive = false;
DWORD processID[5] = { 0, 0, 0, 0, 0 };
#pragma data_seg()

HWND g_HWND = NULL;

void GetProcessIdByName(std::string procName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	int i = 0;
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, procName.c_str()) == 0)
				processID[i++] = entry.th32ProcessID;
		}
	}
	CloseHandle(snapshot);
}


BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		g_HWND = hwnd;
		return FALSE;
	}
	return TRUE;
}


extern "C"
{
	__declspec(dllexport) LRESULT CALLBACK		 KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;

		if (nCode < 0)
			return CallNextHookEx(NULL, nCode, wParam, lParam);

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			FILE *configFile;
			TCHAR docPath[128];
			//SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, docPath);
			//std::string path = docPath;
			//path += "DiscordHookConfig.txt";
			//configFile = _fsopen(path.c_str(), "r", _SH_DENYWR);
			//fclose(configFile);

			// TODO: replace with codes inside config file
			SHORT ctrl, alt, d;
			ctrl = GetAsyncKeyState(VK_LCONTROL);
			alt = GetAsyncKeyState(VK_LMENU);
			d = GetAsyncKeyState(0x44);
			if (((ctrl & 0x8000) || kbdStruct->vkCode == VK_LCONTROL)
				&& ((alt & 0x8000) || kbdStruct->vkCode == VK_LMENU)
				&& ((d & 0x8000) || kbdStruct->vkCode == 0x44))
			{
				g_isActive = !g_isActive;
				return 1;
			}
			if (processID[0] == 0)
			{
				GetProcessIdByName("Discord.exe");
			}
			if (g_isActive)
			{
				for (int i = 0; processID[i] != 0 && i < 5; ++i)
				{
					EnumWindows(EnumWindowsProcMy, processID[i]);
					PostMessage(g_HWND, WM_ACTIVATEAPP, (WPARAM)true, (LPARAM)GetCurrentThreadId());
					PostMessage(g_HWND, WM_ACTIVATE, (WPARAM)LOWORD(WA_ACTIVE), (LPARAM)g_HWND);
					PostMessage(g_HWND, WM_KEYDOWN, kbdStruct->vkCode, 1);
				}
				if (kbdStruct->vkCode != VK_CONTROL && kbdStruct->vkCode != VK_LMENU && kbdStruct->vkCode != VK_LCONTROL)
					return 1;
			}
		}
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
}