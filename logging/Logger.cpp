// #include "Logger.hpp"

// Logger& Logger::getInstance()
// {
//     static Logger instance;
//     return instance;
// }

// void Logger::setMode(const Modes mode)
// {
//     this->loggingMode = mode;
// }

// Logger::Logger(): loggingMode{Modes::DEBUG} {}

// std::string Logger::levelToString(const Modes mode) {
//   switch (mode) {
//   case Modes::INFO:
//     return "INFO";
//   case Modes::VERBOSE:
//     return "VERBOSE";
//   case Modes::WARNING:
//     return "WARNING";
//   case Modes::DEBUG:
//     return "DEBUG";
//   case Modes::ERROR:
//     return "ERROR";
//   default:
//     return "UNKNOWN";
//   }
//   return std::string();
// }

// template <typename... Args>
// void Logger::LOG(const Modes mode, Args&&... message)
// {
//     // Log message
//     // Function name : [time] : Mode | message
//     std::lock_guard<std::mutex> lck(mtx);
//     std::ostringstream oss;
//     (oss << ... << message);
//     std::cout << '[' << levelToString(mode) << "] ["  << "] " << oss.str() << '\n';
// }

// // template <typename... Args>
// // void Logger::LOGI(Args&&... message)
// // {
// //     LOG(Modes::INFO, std::forward<Args>(message)...);
// // }

// // template <typename... Args>
// // void Logger::LOGV(Args&&... message)
// // {
// //     LOG(Modes::VERBOSE, std::forward<Args>(message)...);

// // }

// // template <typename... Args>
// // void Logger::LOGW(Args&&... message)
// // {
// //     LOG(Modes::WARNING, std::forward<Args>(message)...);
// // }

// // template <typename... Args>
// // void Logger::LOGD(Args&&... message)
// // {
// //     LOG(Modes::DEBUG, std::forward<Args>(message)...);
// // }

// // template <typename... Args>
// // void Logger::LOGE(Args&&... message)
// // {
// //     LOG(Modes::ERROR, std::forward<Args>(message)...);
// // }