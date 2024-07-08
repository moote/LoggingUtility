#include "LoggingUtility.h"

LoggingUtility::LoggingUtility(
    LoggingUtility::debugLevel debugLevel,
    String &statusStr)
    : _statusStr(statusStr)
{
    // set vars
    _debugLevel = debugLevel;
}

void LoggingUtility::init()
{
    // init serial
    printDebug(ALERT, "LoggingUtility::init");
}

void LoggingUtility::setStatusSring(String msg)
{
    _statusStr = msg;
}

void LoggingUtility::clearStatusString()
{
    _statusStr = "";
}

