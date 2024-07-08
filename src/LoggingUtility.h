#ifndef LoggingUtility_h
#define LoggingUtility_h
#include <Arduino.h>

#ifdef NODE_MCU
#include <FS.h>
#endif

class LoggingUtility
{
public:
    enum debugLevel
    {
        ALERT,
        GENERAL,
        VERBOSE
    };

    LoggingUtility(enum LoggingUtility::debugLevel debugLevel, String &statusStr);

    // call once hardware ready (setup() function in .ino file)
    void init();

    void setStatusSring(String msg);
    void clearStatusString();

    // define full function in header as it uses template
    // https://stackoverflow.com/a/58227924/830376
    template <typename T, typename... Types>
    void printDebug(LoggingUtility::debugLevel level, T first, Types... other)
    {
        if (level <= _debugLevel)
        {
            _printDebug(first, other...);
        }
    }

    template <typename T, typename... Types>
    void printDebugNoBreak(LoggingUtility::debugLevel level, T first, Types... other)
    {
        if (level <= _debugLevel)
        {
            _printDebugNoBreak(first, other...);
        }
    }

#ifdef NODE_MCU
    /**
     * NodeMCU ONLY
     * 
     * Used for writing contents of log file to Serial
     */
    void writeFile(LoggingUtility::debugLevel level, File file)
    {
        if (level <= _debugLevel)
        {
            Serial.write(file.read());
        }
    }
#endif

    bool setDebugLevel(int level)
    {
        printDebug(VERBOSE, "LoggingUtility::setDebugLevel: ", level);

        switch (level)
        {
        case 0:
            _debugLevel = LoggingUtility::ALERT;
            return true;
        case 1:
            _debugLevel = LoggingUtility::GENERAL;
            return true;
        case 2:
            _debugLevel = LoggingUtility::VERBOSE;
            return true;
        default:
            printDebug(ALERT, "LoggingUtility::setDebugLevel: Invalid level: ", level);
            return false;
        }
    }

    bool setDebugLevel(debugLevel level)
    {
        printDebug(VERBOSE, "LoggingUtility::setDebugLevel: ", level);
        _debugLevel = level;
        return true;
    }

    LoggingUtility::debugLevel getDebugLevel()
    {
        return _debugLevel;
    }

private:
    String &_statusStr;
    enum debugLevel _debugLevel;

    template <typename T, typename... Types>
    void _printDebug(T first, Types... other)
    {
        Serial.print(first);
        _printDebug(other...);
    }

    void _printDebug()
    {
        Serial.println();
    }

    template <typename T, typename... Types>
    void _printDebugNoBreak(T first, Types... other)
    {
        Serial.print(first);
        _printDebugNoBreak(other...);
    }

    void _printDebugNoBreak()
    {
        // do nothing
    }
};

#endif