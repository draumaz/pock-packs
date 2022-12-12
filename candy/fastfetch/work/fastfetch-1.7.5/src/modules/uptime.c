#include "fastfetch.h"
#include "common/printing.h"

#if __APPLE__
    #include "time.h"
    #include "sys/sysctl.h"
#endif

#define FF_UPTIME_MODULE_NAME "Uptime"
#define FF_UPTIME_NUM_FORMAT_ARGS 4

void ffPrintUptime(FFinstance* instance)
{
    uint64_t uptime;

    #if FF_HAVE_SYSINFO_H
        uptime = (uint64_t) instance->state.sysinfo.uptime;
    #elif __APPLE__
        struct timeval bootTime;
        size_t bootTimeSize = sizeof(bootTime);
        if(sysctl(
            (int[]) {CTL_KERN, KERN_BOOTTIME}, 2,
            &bootTime, &bootTimeSize,
            NULL, 0
        ) == 0)
            uptime = (uint64_t) difftime(time(NULL), bootTime.tv_sec);
        else
            uptime = 0;
    #else
        uptime = 0;
    #endif

    if(uptime == 0)
    {
        ffPrintError(instance, FF_UPTIME_MODULE_NAME, 0, &instance->config.uptime, "Uptime could't be detected");
        return;
    }

    uint32_t days    = (uint32_t)  uptime / 86400;
    uint32_t hours   = (uint32_t) (uptime - (days * 86400)) / 3600;
    uint32_t minutes = (uint32_t) (uptime - (days * 86400) - (hours * 3600)) / 60;
    uint32_t seconds = (uint32_t)  uptime - (days * 86400) - (hours * 3600) - (minutes * 60);

    if(instance->config.uptime.outputFormat.length == 0)
    {
        ffPrintLogoAndKey(instance, FF_UPTIME_MODULE_NAME, 0, &instance->config.uptime.key);

        if(days == 0 && hours == 0 && minutes == 0)
        {
            printf("%u seconds\n", seconds);
            return;
        }

        if(days > 0)
        {
            printf("%u day", days);

            if(days > 1)
                putchar('s');

            if(days >= 100)
                fputs("(!)", stdout);

            if(hours > 0 || minutes > 0)
                fputs(", ", stdout);
        }

        if(hours > 0)
        {
            printf("%u hour", hours);

            if(hours > 1)
                putchar('s');

            if(minutes > 0)
                fputs(", ", stdout);
        }

        if(minutes > 0)
        {
            printf("%u min", minutes);

            if(minutes > 1)
                putchar('s');
        }

        putchar('\n');
    }
    else
    {
        ffPrintFormat(instance, FF_UPTIME_MODULE_NAME, 0, &instance->config.uptime, FF_UPTIME_NUM_FORMAT_ARGS, (FFformatarg[]){
            {FF_FORMAT_ARG_TYPE_UINT, &days},
            {FF_FORMAT_ARG_TYPE_UINT, &hours},
            {FF_FORMAT_ARG_TYPE_UINT, &minutes},
            {FF_FORMAT_ARG_TYPE_UINT, &seconds}
        });
    }
}
