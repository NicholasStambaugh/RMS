#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <pdh.h>
#pragma comment(lib, "pdh.lib")
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/sysinfo.h>
#include <unistd.h>
#endif

void getSystemInfo() {
    // Platform-specific code to get system information

#ifdef _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    printf("System Memory Information:\n");
    printf("Total Physical Memory: %llu KB\n", memInfo.ullTotalPhys / 1024);
    printf("Free Physical Memory: %llu KB\n", memInfo.ullAvailPhys / 1024);
    printf("Total Virtual Memory: %llu KB\n", memInfo.ullTotalVirtual / 1024);
    printf("Free Virtual Memory: %llu KB\n", memInfo.ullAvailVirtual / 1024);

    // CPU information can be obtained using the Windows API or other third-party libraries
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) {
        perror("sysinfo");
        return;
    }

    printf("System Memory Information:\n");
    printf("Total RAM: %lu KB\n", sys_info.totalram / 1024);
    printf("Free RAM: %lu KB\n", sys_info.freeram / 1024);
    printf("Total Swap: %lu KB\n", sys_info.totalswap / 1024);
    printf("Free Swap: %lu KB\n", sys_info.freeswap / 1024);

    // CPU information can be obtained using other platform-specific methods
#endif
}

int main() {
    printf("System Information Tool\n");
    getSystemInfo();

    return 0;
}
