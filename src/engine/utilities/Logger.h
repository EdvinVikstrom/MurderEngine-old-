#ifndef LOGGER_H
  #define LOGGER_H

#define LOG_ANSI_RESET                   "\e[0m"
#define LOG_ANSI_BOLD                    "\e[1m"
#define LOG_ANSI_FAINT                   "\e[2m"
#define LOG_ANSI_ITALIC                  "\e[3m"
#define LOG_ANSI_UNDERLINE               "\e[4m"

#define LOG_COLOR_BLACK                  "\e[30m"
#define LOG_COLOR_BLUE                   "\e[34m"
#define LOG_COLOR_CYAN                   "\e[36m"
#define LOG_COLOR_GREY                   "\e[30m;1m"
#define LOG_COLOR_GREEN                  "\e[32m"
#define LOG_COLOR_MAGENTA                "\e[35m"
#define LOG_COLOR_RED                    "\e[31m"
#define LOG_COLOR_WHITE                  "\e[37m"
#define LOG_COLOR_YELLOW                 "\e[33m"

#define LOG_BG_COLOR_BLACK               "\e[40m"
#define LOG_BG_COLOR_BLUE                "\e[44m"
#define LOG_BG_COLOR_CYAN                "\e[46m"
#define LOG_BG_COLOR_GREY                "\e[40m;1m"
#define LOG_BG_COLOR_GREEN               "\e[42m"
#define LOG_BG_COLOR_MAGENTA             "\e[45m"
#define LOG_BG_COLOR_RED                 "\e[41m"
#define LOG_BG_COLOR_WHITE               "\e[47m"
#define LOG_BG_COLOR_YELLOW              "\e[43m"

namespace me {

  enum logMsgType {
    INFO = 0,
    WARNING = 1,
    ERROR = 2,
    DEBUG = 3
  };

  struct log {
    const char* prefix;
    // N: Log name, T: time, D: date, M: message type
    std::string out_pattern, warn_pattern, err_pattern, debug_pattern;
    log(const char* prefix, std::string out_pattern, std::string warn_pattern, std::string err_pattern, std::string debug_pattern)
    {
      this->prefix = prefix;
      this->out_pattern = out_pattern;
      this->warn_pattern = warn_pattern;
      this->err_pattern = err_pattern;
      this->debug_pattern = debug_pattern;
    }
    void out(std::string message);
    void warn(std::string message);
    void err(std::string message);
    void debug(std::string message);
  };

};

#endif
