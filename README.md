# Logger for Arduino

Simple logging library for arduino

- [Features](#features)
- [Get started](#get-started)
    - [Installation](#installation)
    - [Sketch](#sketch)
    - [Output](#output)
- [Using alternative serial port](#using-alternative-serial-port)
- [License](#license)

# Features
- Stream-like syntax
- Logging with line number and file name
- Filter by importance

Logging in Arduino is sometimes written redundantly.

```cpp
Serial.print("In line ");
Serial.print(__LINE__);
Serial.print(", Value is: ");
Serial.println(val);
// Output: In line 2, Value is: ??
```

We can write logging process briefly using this library.

```cpp
LOGGER_LOG(logger::INFO) << "Value is: " << val << '\n';
// Output: [INFO] sketch.ino:2: Value is: ??
```


# Get started

### Installation

1. Download [arduino-logger.zip](https://github.com/coord-e/arduino-logger/archive/master.zip).
2. Import downloaded zip using Arduino IDE's "Add .ZIP library..."
3. You can find arduno-logger is shown as "Logger" in "Examples" or "Include Library" in Arduino IDE.

### Sketch

```cpp
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
```

### Output

```
[FATAL]  logging.ino:13: Fatal error!
[INFO]  logging.ino:20: You can put almost every kinds of object into the log
[INFO]  logging.ino:21: e.g. int: 2 or float: 3.14
```

# Using alternative serial port

You can use alternative serial ports on Arduino Leonardo, Mega, Due, etc...

```cpp
// Use Serial2 as a output of logs
#define LOGGER_SERIAL Serial2
#include <logger.hpp>

...
```

# License
This library is distributed under MIT license.
See `LICENSE`.
