
#include <stdio.h>
#include <time.h>


char *getTime()
{
    time_t rawtime;
    struct tm *timeinfo;
    static const char wday_name[][4] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    static const char mon_name[][4] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    static char result[26];
    sprintf(result, "%.3s, %.2d %.3s %.2d:%.2d", wday_name[timeinfo->tm_wday], timeinfo->tm_mday, mon_name[timeinfo->tm_mon], timeinfo->tm_hour,timeinfo->tm_min);
    return result;
}

int getSecondsBeforeNextMinute()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return (60 - timeinfo->tm_sec);
}