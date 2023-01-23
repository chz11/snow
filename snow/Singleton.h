#ifndef _SNOW_SINGLETON_H_
#define _SNOW_SINGLETON_H_
#include "log.h"

#define LOG_ROOT() \ 
        base::Singleon<base::LogManager>::GetSingleonPtr()->GetLogRoot()
namespace base
{
    template<class T>
    class Singleon
    {
    public:
        static T& GetSingleon()
        {
            return *v;
        }
        static std::shared_ptr<T> GetSingleonPtr()
        {
            static std::shared_ptr<T> ptr(v);
            return ptr;
        } 
        static T* v;
    };

    template<class T>
    T* Singleon<T>::v = new LogManager();
}

#endif