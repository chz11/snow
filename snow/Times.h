#ifndef _SNOW_TIMES_H_
#define _SNOW_TIMES_H_
#include<iostream>
#include<time.h>
namespace base
{
    class Times
    {
        public:
            Times() {}
            Times(int64_t microsesecond) : microsesecond_(microsesecond)
            {

            }
            Times(const Times& that)
            {
                microsesecond_=that.microsesecond_;
            }

            static int64_t persecondEqualtoMicrosesecond_;
            time_t MicosesecondToSecond()
            {
                return static_cast<time_t>(microsesecond_ / persecondEqualtoMicrosesecond_);
            }
            static Times now();
            std::string toString();
        private:
            int64_t microsesecond_;
            
    };
}
#endif