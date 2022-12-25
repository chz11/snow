#include "Times.h"
#include <sys/time.h>
#include<stdio.h>
namespace base
{
    int64_t Times::persecondEqualtoMicrosesecond_ = 1000*1000;
    Times Times::now()
    {
         struct timeval tv;
         gettimeofday(&tv,NULL);
         int64_t secondes = tv.tv_sec;
         return Times(secondes * persecondEqualtoMicrosesecond_ + tv.tv_usec);
    }
    std::string Times::toString()
    {
        char buf[256]={0};
        struct tm* tmPtr;
        int64_t secondes = microsesecond_ / persecondEqualtoMicrosesecond_;
        tmPtr = localtime(&secondes);
        sprintf(buf,"%04d-%02d-%02d %02d:%02d:%02d:%03ld",
        tmPtr->tm_year+1900,tmPtr->tm_mon+1,tmPtr->tm_mday,tmPtr->tm_hour,tmPtr->tm_min,tmPtr->tm_sec,microsesecond_ % persecondEqualtoMicrosesecond_);
        return buf;
    }

}