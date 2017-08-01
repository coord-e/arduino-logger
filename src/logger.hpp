#if !defined(LOGGER_SERIAL_HPP_)
#define LOGGER_SERIAL_HPP_

#if !defined(LOGGER_SERIAL)
#if defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_SAM_DUE)
#define LOGGER_SERIAL Serial1
#else
#define LOGGER_SERIAL Serial
#endif
#else
#define LOGGER_SERIAL_DEFINED
#endif

namespace logger{

static constexpr uint8_t FATAL = 0;
static constexpr uint8_t ERROR = 1;
static constexpr uint8_t WARN = 2;
static constexpr uint8_t INFO = 3;

static volatile uint8_t filter = INFO;

struct logger_stream {
  logger_stream(const char* file, const char* func, uint16_t line, uint8_t level) : en(level <= filter) {
    if (en) {
      LOGGER_SERIAL.print("[");
      switch (level) {
        case level::FATAL:
          LOGGER_SERIAL.print("FATAL");
          break;
        case level::ERROR:
          LOGGER_SERIAL.print("ERROR");
          break;
        case level::WARN:
          LOGGER_SERIAL.print("WARN");
          break;
        case level::INFO:
          LOGGER_SERIAL.print("INFO");
          break;
      }
      LOGGER_SERIAL.print("]\t");
      LOGGER_SERIAL.print(strrchr(file, '/') + 1);
      LOGGER_SERIAL.print(":");
      LOGGER_SERIAL.print(line);
      LOGGER_SERIAL.print(": ");
    }
  }

  bool en;
};

template<typename T> logger_stream const& operator<<(logger_stream const& s, T const& obj) {
  if (s.en)
    LOGGER_SERIAL.print(obj);
  return s;
}

};

#define LOGGER_LOG(LEVEL) logger::logger_stream(__FILE__, __func__, __LINE__, LEVEL)

#if defined(LOGGER_SERIAL_DEFINED)
#undef LOGGER_SERIAL_DEFINED
#else
#undef LOGGER_SERIAL
#endif

#endif
