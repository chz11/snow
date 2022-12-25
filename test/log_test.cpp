#include "../snow/log.h"
#include "../snow/Times.h"
int main()
{
    base::Logger::LoggerPtr m_logger = std::make_shared<base::Logger>("main");
    base::LogAppender::LogAppenderPtr m_appender = std::make_shared<base::StdOutLogAppender>();
    m_logger->AddLogAppender(m_appender);
    //base::LogEvent::LogEventPtr m_logEvent = std::make_shared<base::LogEvent>(0,0,__FILE__,__LINE__,base::Times::now(),1,"12345");
    //m_logEvent->getss() << "1234";
    // m_logger->Debug(base::LogLevel::DEBUG,m_logEvent);
    TRACE(m_logger) << "dfsfew";
    return 0;
}