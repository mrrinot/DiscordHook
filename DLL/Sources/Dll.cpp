#include "Header.hh"

std::vector<DWORD> GetProcessIdByName(std::string procName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	std::vector<DWORD> processes;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	int i = 0;
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (stricmp(entry.szExeFile, procName.c_str()) == 0)
			{
				processes.push_back(entry.th32ProcessID);
			}
		}
	}
	CloseHandle(snapshot);
	return processes;
}



HWND g_HWND = NULL;
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
		if (nCode < 0)
			return CallNextHookEx(NULL, nCode, wParam, lParam);

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			FILE *file;
			std::string entry;
			file = _fsopen("C:\\Users\\Raphaël\\Desktop\\test.txt", "a", SH_DENYRD);
			if (file != nullptr)
			{
				//Get character pressed
				KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
				BYTE keyboard_state[256];

				GetKeyboardState(keyboard_state);
				WORD character;

				std::cout << " code = " << kbdStruct->vkCode << std::endl;
				switch (kbdStruct->vkCode)
				{
				case VK_BACK:
					entry += "[BACK]";
					break;
				case VK_TAB:
					entry += "[TAB]";
					break;
				case VK_ESCAPE:
					entry += "[ESC]";
					break;
				case VK_SHIFT:
					entry += "[SHFIT]";
					break;
				case VK_CONTROL:
					entry += "[CTRL]";
					break;
				case VK_CAPITAL:
					entry += "[CAPS]";
					break;
				case VK_PAUSE:
					entry += "[PAUSE]";
					break;
				case VK_PRIOR:
					entry += "[P.UP]";
					break;
				case VK_NEXT:
					entry += "[P.DOWN]";
					break;
				case VK_END:
					entry += "[END]";
					break;
				case VK_HOME:
					entry += "[HOME]";
					break;
				case VK_LEFT:
					entry += "[LEFT]";
					break;
				case VK_UP:
					entry += "[UP]";
					break;
				case VK_RIGHT:
					entry += "[RIGHT]";
					break;
				case VK_DOWN:
					entry += "[DOWN]";
					break;
				case VK_PRINT:
					entry += "[PRINT]";
					break;
				case VK_EXECUTE:
					entry += "[EXECUTE]";
					break;
				case VK_SNAPSHOT:
					entry += "[SNAP]";
					break;
				case VK_INSERT:
					entry += "[INS]";
					break;
				case VK_DELETE:
					entry += "[DEL]";
					break;
				case VK_LWIN:
					entry += "[L.WIN]";
					break;
				case VK_RWIN:
					entry += "[R.WIN]";
					break;
				case VK_RETURN:
					entry += "[ENTER]";
					break;
				case VK_F1:
					entry += "[F1]";
					break;
				case VK_F2:
					entry += "[F2]";
					break;
				case VK_F3:
					entry += "[F3]";
					break;
				case VK_F4:
					entry += "[F4]";
					break;
				case VK_F5:
					entry += "[F5]";
					break;
				case VK_F6:
					entry += "[F6]";
					break;
				case VK_F7:
					entry += "[F7]";
					break;
				case VK_F8:
					entry += "[F8]";
					break;
				case VK_F9:
					entry += "[F9]";
					break;
				case VK_F10:
					entry += "[F10]";
					break;
				case VK_F11:
					entry += "[F11]";
					break;
				case VK_F12:
					entry += "[F12]";
					break;
				case VK_NUMLOCK:
					entry += "[NUML]";
					break;
				case VK_SCROLL:
					entry += "[SCROLL]";
					break;
				case VK_LCONTROL:
					entry += "[L.CTRL]";
					break;
				case VK_RCONTROL:
					entry += "[R.CTRL]";
					break;
				case VK_LSHIFT:
					entry += "[L.SHIFT]";
					break;
				case VK_RSHIFT:
					entry += "[R.SHIFT]";
					break;
				case VK_LMENU:
					entry += "[L.ALT]";
					break;
				case VK_RMENU:
					entry += "[R.ALT]";
					break;
				case VK_APPS:
					entry += "[APPS]";
					break;
				case VK_OEM_6:
					entry += "^";
					break;
				case VK_VOLUME_MUTE:
					entry += "[V.MUTE]";
					break;
				case VK_VOLUME_DOWN:
					entry += "[V.DOWN]";
					break;
				case VK_VOLUME_UP:
					entry += "[V.UP]";
					break;
				case VK_MEDIA_NEXT_TRACK:
					entry += "[M.NEXT]";
					break;
				case VK_MEDIA_PREV_TRACK:
					entry += "[M.PREV]";
					break;
				case VK_MEDIA_PLAY_PAUSE:
					entry += "[M.PLAY/PAUSE]";
					break;
				case VK_MEDIA_STOP:
					entry += "[M.STOP]";
					break;
				default:
					if (!(MapVirtualKey(kbdStruct->vkCode, MAPVK_VK_TO_CHAR) >> (sizeof(UINT) * 8 - 1) & 1))
					{
						ToAscii((UINT)kbdStruct->vkCode, kbdStruct->scanCode,
							keyboard_state, &character, 0);
						entry += (char)(character);
					}
					break;
				}

				// Get focused process name
				HWND hwnd = GetForegroundWindow(); // get handle of currently active window
				DWORD winId;
				GetWindowThreadProcessId(hwnd, &winId);
				HANDLE Handle = OpenProcess(
					PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
					FALSE,
					winId
					);
				if (Handle)
				{
					TCHAR Buffer[MAX_PATH];
					if (GetProcessImageFileName(Handle, Buffer, MAX_PATH))
					{
						std::string process = std::string(Buffer);
						entry += " " + process.substr(process.find_last_of("\\") + 1);
					}
					CloseHandle(Handle);
				}
				char windowTitle[256];
				GetWindowText(hwnd, windowTitle, 256);
				std::string windowName(windowTitle);
				std::replace(windowName.begin(), windowName.end(), ' ', '_');
				entry += " " + windowName;
				time_t current;
				time(&current);
				std::stringstream ss;
				ss << current;
				std::string tmp;
				ss >> tmp;
				entry += " " + tmp;
				std::vector<DWORD> processes = GetProcessIdByName("Discord.exe");
				for (auto it : processes)
				{
					EnumWindows(EnumWindowsProcMy, it);
					//SetFocus(g_HWND);
					//ss.clear();
					//ss << GetLastError();
					//ss >> tmp;
					//entry += " error ? " + tmp;
					//PostMessage(g_HWND, WM_ACTIVATE, (WPARAM)true, (LPARAM)GetCurrentThreadId());
					//PostMessage(g_HWND, WM_KEYDOWN, kbdStruct->vkCode, 1);
					//PostMessage(g_HWND, WM_KEYUP, kbdStruct->vkCode, 1);
					PostMessage(g_HWND, WM_ACTIVATEAPP, (WPARAM)true, (LPARAM)GetCurrentThreadId());
					PostMessage(g_HWND, WM_ACTIVATE, (WPARAM)LOWORD(WA_ACTIVE), (LPARAM)g_HWND);
					//PostThreadMessage(it, WM_ACTIVATE, (WPARAM)true, (LPARAM)it);
					PostMessage(g_HWND, WM_KEYDOWN, kbdStruct->vkCode, 1);
					//PostMessage(g_HWND, WM_KEYUP, kbdStruct->vkCode, 1);
				}
				entry += "\n";
				fwrite(entry.c_str(), sizeof(char), entry.size(), file);
				fclose(file);
			}
			else
				std::cout << "could not open the file" << std::endl;
		}

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
}