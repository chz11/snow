#ifndef _SNOW_LOG_H_
#define _SNOW_LOG_H_
#include<string.h>
#include<stdint.h>
#include<memory>
#include<list>
#include<vector>
#include<sstream>
#include<fstream>
#include<iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include "Times.h"

#define LOG_OUTPUT(level,logger) \
            if(logger->getLevel() <= level) \
                base::LogEventWrap(std::make_shared<base::LogEvent>(level,logger,syscall(SYS_gettid),0,__FILE__,__LINE__,base::Times::now(),0)).getss()
#define TRACE(logger) LOG_OUTPUT(base::LogLevel::DEBUG, logger)
#define INFO(logger)  LOG_OUTPUT(base::LogLevel::INFO, logger)
#define WARN(logger)  LOG_OUTPUT(base::LogLevel::WARN, logger)
#define ERROR(logger) LOG_OUTPUT(base::LogLevel::ERROR, logger)
#define FATAL(logger) LOG_OUTPUT(base::LogLevel::FATAL, logger)

namespace base
{
class Logger;
//日志等级
class LogLevel
{
public:
    enum Level
    {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* toString(LogLevel::Level level);
};

//日志实践
class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> LogEventPtr;
    LogEvent(LogLevel::Level level, std::shared_ptr<Logger> logger, uint32_t pthreadId, uint32_t fiberId, const char* fileName,
        uint32_t line, Times time, uint32_t m_elapse);
    uint32_t getPthreadId() const
    {
        return m_pthreadId;
    }

    uint32_t getFiberId() const
    {
        return m_fiberId;
    }

    const char* getFileName() const
    {
        return m_fileName;
    }

    uint32_t getLine() const
    {
        return m_line;
    }
    
    std::string getTime()
    {
        return m_time.toString();
    }

    uint32_t getElapse() const
    {
        return m_elapse;
    }

    std::string getContent() const
    {
        return ss.str();
    }

    std::shared_ptr<Logger> getLogger()
    {
        return m_logger;
    }

    LogLevel::Level getLevel() const
    {
        return m_level;
    }

    std::stringstream& getss()
    {
        return ss;
    }

private:
    uint32_t m_pthreadId;         //线程id
    uint32_t m_fiberId;           //协程id
    const char* m_fileName;       //文件名
    uint32_t m_line;              //行号
    Times m_time;           //时间戳
    uint32_t m_elapse;            //时间间隔
    std::stringstream ss;
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};

class LogEventWrap
{
public:
    LogEventWrap(LogEvent::LogEventPtr logEventPtr);

    ~LogEventWrap();

    std::stringstream& getss();

private:
    LogEvent::LogEventPtr m_logEventPtr;
};

//日志格式器
class LogFormat
{
public:
    typedef std::shared_ptr<LogFormat> LogFormatPtr;

    LogFormat(const std::string& pattern);
    std::string Format(std::shared_ptr<Logger> loggerPtr,LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);
    void Init();
public:
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> FormatItemPtr;
        FormatItem(const std::string& fmt = "") {}
        virtual ~FormatItem() {}
        virtual void Format(std::ostream& os, std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEvevtPtr) = 0;
    };
private:
    std::string m_pattern;
    std::vector<FormatItem::FormatItemPtr> m_item;
};

//日志输出器
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> LogAppenderPtr;
    virtual ~LogAppender() {}
    virtual void Log(std::shared_ptr<Logger> loggerPtr,LogLevel::Level level, LogEvent::LogEventPtr logEventPtr) = 0;
    void SetLogFormat(LogFormat::LogFormatPtr logFormatPtr) {m_logFormatPtr = logFormatPtr;}
    LogFormat::LogFormatPtr GetLogFormat() {return m_logFormatPtr;}
protected:
    LogLevel::Level m_level;
    LogFormat::LogFormatPtr m_logFormatPtr;
};

//日志器
class Logger : public std::enable_shared_from_this<Logger>
{
public:
    typedef std::shared_ptr<Logger> LoggerPtr;
    Logger(const std::string name = "root");

    void Log(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);

    void AddLogAppender(LogAppender::LogAppenderPtr logAppenderPtr);

    void DeleteLogAppender(LogAppender::LogAppenderPtr logAppenderPtr);

    void Debug(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);

    void Info(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);

    void Warn(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);

    void Error(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);

    void Fatal(LogLevel::Level level, LogEvent::LogEventPtr logEventPtr);

    void SetLogLevel(const LogLevel::Level& level);

    LogLevel::Level getLevel() {return m_level;}

    const std::string& getName() const {return m_name;}
private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::LogAppenderPtr> m_logAppenderList;
    LogFormat::LogFormatPtr m_logFormatPtr;
};

//终端输出器
class StdOutLogAppender : public LogAppender
{
public:
    void Log(std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEventPtr) override;
};

//文件输出器
class FileOutLogAppender: public LogAppender
{
public:
    FileOutLogAppender(std::string fileName);
    void Log(std::shared_ptr<Logger> loggerPtr, LogLevel::Level level, LogEvent::LogEventPtr logEventPtr) override;
    bool reOpen();
private:
    std::string m_fileName;
    std::ofstream m_fileStream;
};
}
#endif