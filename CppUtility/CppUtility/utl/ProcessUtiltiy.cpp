#include "ProcessUtility.h"

auto GetMaximumMemoryUsage()->size_t {
#if defined(_WIN32)
    PROCESS_MEMORY_COUNTERS pmem;  //Windows
    GetProcessMemoryInfo(GetCurrentProcess(), &pmem, sizeof(pmem));
    return (size_t)pmem.PeakWorkingSetSize;
#elif defined(__unix__) || defined(__unix) || defined(unix)
    struct rusage rusage;                       //Unix
    getrusage(RUSAGE_SELF, &rusage);
#if defined(__APPLE__) && defined(__MACH__)
    return (size_t)rusage.ru_maxrss;
#else
    return (size_t)(rusage.ru_maxrss * 1024L);
#endif
#else
    return (size_t)0L;  //unknown OS
#endif
}

auto GetCurrentMemoryUsage()->size_t {
#if defined(_WIN32)    
    PROCESS_MEMORY_COUNTERS pmem;  //Windows
    GetProcessMemoryInfo(GetCurrentProcess(), &pmem, sizeof(pmem));
    return (size_t)pmem.WorkingSetSize;
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    long rss = 0L; //Linux
    FILE* fp = NULL;
    if ((fp = fopen("/proc/self/statm", "r")) == NULL)
        return (size_t)0L;      /* Can't open? */
    if (fscanf(fp, "%*s%ld", &rss) != 1)
    {
        fclose(fp);
        return (size_t)0L;      /* Can't read? */
    }
    fclose(fp);
    return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);
#else
    return (size_t)0L;   //Unknown OS
#endif
}

