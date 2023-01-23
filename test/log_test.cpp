#include "../snow/log.h"
#include "../snow/Times.h"
#include "../snow/Singleton.h"
int main()
{
    base::Logger::LoggerPtr m_logger = std::make_shared<base::Logger>("main");
    // base::LogAppender::LogAppenderPtr m_appender = std::make_shared<base::StdOutLogAppender>();
    base::LogAppender::LogAppenderPtr m_appender = std::make_shared<base::FileOutLogAppender>("./log.txt");
    m_logger->AddLogAppender(m_appender);
    base::Logger::LoggerPtr logger = base::Singleon<base::LogManager>::GetSingleonPtr()->GetLogger("sss");
    //base::LogEvent::LogEventPtr m_logEvent = std::make_shared<base::LogEvent>(0,0,__FILE__,__LINE__,base::Times::now(),1,"12345");
    //m_logEvent->getss() << "1234";
    // m_logger->Debug(base::LogLevel::DEBUG,m_logEvent);
    // TRACE(m_logger) << "dfsfew";
    // TRACE_FMT(m_logger, "abceder: %s", "aa");
    TRACE_FMT(logger, "ewww: %s", "sssss");
    return 0;
}