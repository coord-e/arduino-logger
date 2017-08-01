#include <logger.hpp>

void setup() {
  Serial.begin(9600);
}

// Only logs which has same as or higher importance than the value in logger::filter will be printed.

int count = 0;

void loop() {
  logger::filter = logger::FATAL; // only FATAL will be printed

  LOGGER_LOG(logger::FATAL) << "Fatal error!\n";
  LOGGER_LOG(logger::ERROR) << "Error!\n";
  LOGGER_LOG(logger::WARN) << "Warning!\n";
  LOGGER_LOG(logger::INFO) << "Information!\n";

  logger::filter = logger::INFO; // every logs will be printed

  LOGGER_LOG(logger::INFO) << "You can put almost every kinds of object into the log\n";
  LOGGER_LOG(logger::INFO) << "e.g. int: " << count << " or float: " << 3.14 << '\n';
  delay(1000);

  count++;
}
