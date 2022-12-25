
#include "log.h"
#include<map>
#include<functional>
namespace base
{
    class MsgFormatItem : public LogFormat::FormatItem
    {
    public:
        MsgFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << logEvevtPtr->getContent();
        }
    };

    class LevelFormatItem : public LogFormat::FormatItem
    {
        public:
        LevelFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << LogLevel::toString(level);
        }
    };

    class FileFormatItem : public LogFormat::FormatItem
    {
    public:
        FileFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << logEvevtPtr->getFileName();
        }
    };

    class PthreadIdFormatItem : public LogFormat::FormatItem
    {
    public:
        PthreadIdFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << logEvevtPtr->getPthreadId();
        }
    };

    class DateTimeFormatItem : public LogFormat::FormatItem
    {
    public:
        DateTimeFormatItem(const std::string& format) : m_format(format)
        {

        }
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << logEvevtPtr->getTime();
        }
    private:
        std::string m_format;
    };

    class LineFormatItem : public LogFormat::FormatItem
    {
    public:
        LineFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << logEvevtPtr->getLine();
        }
    };

    class NewLineFormatItem : public LogFormat::FormatItem
    {
    public:
        NewLineFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << std::endl;
        }
    };

    class TabFormatItem : public LogFormat::FormatItem
    {
    public:
        TabFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << "\t";
        }
    };

    class StringFormatItem : public LogFormat::FormatItem
    {
    public:
        StringFormatItem(const std::string& str) : m_str(str) {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << m_str;
        }
        std::string m_str;
    };   

    class ElapseFormatItem : public LogFormat::FormatItem
    {
    public:
        ElapseFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << logEvevtPtr->getElapse();
        }
    }; 

    class LogNameFormatItem : public LogFormat::FormatItem
    {
    public:
        LogNameFormatItem(const std::string& str = "") {}
        void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) override
        {
            os << loggerPtr->getName();
        }
    }; 

    const char* LogLevel::toString(LogLevel::Level level)
    {
        switch(level)
        {
        #define XX(name) \
            case LogLevel::name : \
                return #name; \
                break;
            XX(DEBUG);
            XX(INFO);
            XX(WARN);
            XX(ERROR);
            XX(FATAL);
        #undef XX
            default:
                return "UNKNOW";
        }
        return "UNKNOW";
    }
    LogEvent::LogEvent(LogLevel::Level level, std::shared_ptr<Logger> logger, uint32_t pthreadId, uint32_t fiberId, const char* fileName,
        uint32_t line, Times time, uint32_t elapse) : m_level(level), m_logger(logger),m_pthreadId(pthreadId),
        m_fiberId(fiberId),m_fileName(fileName),m_line(line),m_time(time),m_elapse(elapse)
    {

    }
    LogEventWrap::LogEventWrap(LogEvent::LogEventPtr logEventPtr) : m_logEventPtr(logEventPtr)
    {

    }
    LogEventWrap::~LogEventWrap()
    {
        m_logEventPtr->getLogger()->Log(m_logEventPtr->getLevel(), m_logEventPtr);
    }
    std::stringstream& LogEventWrap::getss()
    {
        return m_logEventPtr->getss();
    }

    LogFormat::LogFormat(const std::string& pattern) : m_pattern(pattern)
    {
        Init();
    }

    std::string LogFormat::Format(std::shared_ptr<Logger> loggerPtr,LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        std::stringstream ss;
        for(auto i : m_item)
        {
            i->Format(ss, loggerPtr, level, logEventPtr);
        }
        return ss.str();
    }

    void LogFormat::Init()
    {
        //str fmt type
        std::vector<std::tuple<std::string, std::string, int>> vec;
        std::string nStr;
        for(int i = 0; i < m_pattern.size(); i++)
        {
            if(m_pattern[i] != '%')
            {
                nStr.append(1, m_pattern[i]);
                continue;
            }
            
            if((i + 1) < m_pattern.size())
            {
                if(m_pattern[i + 1] == '%')
                {
                    nStr.append(1,'%');
                    continue;
                }
            }
            
            int n = i + 1;
            std::string str;
            std::string fmt;
            int fmt_status = 0;
            int fmt_begin;
            while(n < m_pattern.size())
            {
                if(!fmt_status && (!isalpha(m_pattern[n]) && m_pattern[n] != '{'
                    && m_pattern[n] != '}')) 
                {
                    str = m_pattern.substr(i + 1, n - i - 1);
                    break;
                }
                if(fmt_status == 0)
                {
                    if(m_pattern[n] == '{')
                    {
                        str = m_pattern.substr(i + 1, n - i - 1);
                        fmt_status = 1;
                        fmt_begin = n + 1;
                        n++;
                        continue;
                    }
                }
                else if(fmt_status == 1)
                {
                    if(m_pattern[n] == '}')
                    {
                        fmt = m_pattern.substr(fmt_begin, n - fmt_begin - 1);
                        fmt_status = 2;                      
                        break;
                    }
                }
                n++;
                if(n == m_pattern.size())
                {
                    if(str.empty())
                    {
                        str = m_pattern.substr(i + 1);
                    }
                }
            }
            if(fmt_status == 0)
            {
                if(!nStr.empty())
                {
                    vec.push_back(std::make_tuple(nStr, "", 0));
                    nStr.clear();
                }
                vec.push_back(std::make_tuple(str, fmt, 1));
                i = n - 1;
            }
            else if(fmt_status == 1)
            {
                // std::cout<<"patterm error\n";
                vec.push_back(std::make_tuple("error","", 0));
                break;
            }
            else if(fmt_status == 2)
            {
                if(!nStr.empty())
                {
                    vec.push_back(std::make_tuple(nStr, "", 0));
                    nStr.clear();
                }
                vec.push_back(std::make_tuple(str, fmt, 1));
                i = n - 1;
            }
        }

        if(!nStr.empty())
        {
            vec.push_back(std::make_tuple(nStr, "", 0));
            nStr.clear();
        }
        static std::map<std::string, std::function<FormatItem::FormatItemPtr(const std::string& str)> > formatItems = {
            #define XX(str, C) \
            {#str,[] (const std::string& fmt) {return FormatItem::FormatItemPtr(new C(fmt));}}
            XX(m,MsgFormatItem),
            XX(p,LevelFormatItem),
            XX(r,ElapseFormatItem),
            XX(c,LogNameFormatItem),
            XX(n,NewLineFormatItem),
            XX(t,PthreadIdFormatItem),
            XX(d,DateTimeFormatItem),
            XX(f,FileFormatItem),
            XX(l,LineFormatItem),
            XX(T,TabFormatItem),
            #undef XX
        };

        //%m 消息类容
        //%p 输出日志等级
        //%r 输出自应用启动到该条日志打印所耗时间
        //%c 输出日志名称
        //%n 输出换行符
        //%t 输出线程id
        //%d 输出日志打印时间
        //%f 输出文件名
        //%l 输出行号

        for(auto i : vec)
        {
            if(std::get<2>(i) == 0)
            {
                m_item.push_back(FormatItem::FormatItemPtr(new StringFormatItem(std::get<0>(i))));
            }
            else
            {
                auto it = formatItems.find(std::get<0>(i));
                if(it == formatItems.end())
                {
                    m_item.push_back(FormatItem::FormatItemPtr(new StringFormatItem("pattern_error!")));
                }
                else
                {
                    m_item.push_back(it->second(std::get<0>(i)));
                }
            }
            // std::cout<<"{"<<std::get<0>(i)<<"} - {"<<std::get<1>(i)<<"} - {"<<std::get<2>(i)<<"}"<<std::endl;
        }
    }

    Logger::Logger(std::string name) : m_name(name),m_level(LogLevel::DEBUG)
    {
        m_logFormatPtr.reset(new LogFormat("%d%T%t%T[%p]%T[%c]%T<%f:%l>%T%m%T%n"));
    }
    void Logger::Log(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        if(level >= m_level)
        {
            auto self = shared_from_this();
            for(auto i : m_logAppenderList)
            {
                i->Log(self, level,logEventPtr);
            }
        }
    }

    void Logger::AddLogAppender(LogAppender::LogAppenderPtr logAppenderPtr)
    {
        if(!logAppenderPtr->GetLogFormat())
        {
            logAppenderPtr->SetLogFormat(m_logFormatPtr);
        }
        m_logAppenderList.push_back(logAppenderPtr);
    }

    void Logger::DeleteLogAppender(LogAppender::LogAppenderPtr logAppenderPtr)
    {
        for(auto it = m_logAppenderList.begin(); it != m_logAppenderList.end(); ++it)
        {
            if(*it == logAppenderPtr)
            {
                m_logAppenderList.erase(it);
                break;
            }
        }
    }

    void Logger::Debug(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        Log(LogLevel::DEBUG,logEventPtr);
    }

    void Logger::Info(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        Log(LogLevel::INFO,logEventPtr);
    }

    void Logger::Warn(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        Log(LogLevel::WARN,logEventPtr);
    }

    void Logger::Error(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        Log(LogLevel::ERROR,logEventPtr);
    }

    void Logger::Fatal(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        Log(LogLevel::FATAL,logEventPtr);
    }

    void Logger::SetLogLevel(const LogLevel::Level& level)
    {
        m_level = level;
    }

    void StdOutLogAppender::Log(std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        if(level > m_level)
        {
            std::cout<<m_logFormatPtr->Format(loggerPtr, level, logEventPtr);
        }
    }
    
    FileOutLogAppender::FileOutLogAppender(std::string fileName) : m_fileName(fileName)
    {

    }

    void FileOutLogAppender::Log(std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEventPtr)
    {
        if(level > m_level)
        {
            m_fileStream << m_logFormatPtr->Format(loggerPtr, level, logEventPtr);
        }
    }

    bool FileOutLogAppender::reOpen()
    {
        if(m_fileStream)
        {
            m_fileStream.close();
        }
        m_fileStream.open(m_fileName);
        return !!m_fileStream;
    } 
}