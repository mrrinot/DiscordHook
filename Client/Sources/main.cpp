#include <Windows.h>
#include <string>
#include <iostream>
#include <winerror.h>

int main()
{
	HOOKPROC hkprc;
	static HINSTANCE hhookDLL;
	static HHOOK hhook;

	hhookDLL = LoadLibrary(TEXT("D:\\Epitech\\DiscordHook\\DLL\\Build\\Release\\Hook.dll"));
	if (hhookDLL == nullptr)
		std::cerr << "hhookdll = " << GetLastError() << std::endl;
	hkprc = (HOOKPROC)GetProcAddress(hhookDLL, "KeyboardProc");
	if (hkprc == nullptr)
		std::cerr << "hkprc = " << GetLastError() << std::endl;

	hhook = SetWindowsHookEx(
		WH_KEYBOARD_LL,
		hkprc,
		hhookDLL,
		0);
	if (hhook == nullptr)
		std::cerr << "hhook = " << GetLastError() << std::endl;
	LPMSG Msg = nullptr;
	while (Msg == nullptr || WM_QUIT != Msg->message)
	{
		while (PeekMessage(Msg, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(Msg);
			DispatchMessage(Msg);
		}
	}
	UnhookWindowsHookEx(hhook);
	return 0;
}