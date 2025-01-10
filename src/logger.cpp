#include <iostream>
#include <windows.h>

#include "logger.hpp"

#include <chrono>
#include <thread>

void* logger::console;

// reds
WORD fg_red   = 0x0004;
WORD fg_l_red = 0x000C;

// greens
WORD fg_green   = 0x0002;
WORD fg_l_green = 0x000A;

// blues
WORD fg_cyan   = 0x000B;
WORD fg_blue   = 0x0009;
WORD fg_l_blue = 0x0003;
WORD fg_d_blue = 0x0001;

WORD fg_purple   = 0x0005;
WORD fg_l_purple = 0x000D;

// yellows
WORD fg_yellow   = 0x0006;
WORD fg_l_yellow = 0x000E;

// grays
WORD fg_white  = 0x000F;
WORD fg_l_gray = 0x0007;
WORD fg_gray   = 0x0008;

bool thread_write_locked;

void logger::init()
{
#ifdef _WIN32
    console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    log_info("init()");
}

void logger::log_name()
{
    while (thread_write_locked) std::this_thread::sleep_for(std::chrono::microseconds(250));
    thread_write_locked = true;
#ifdef _WIN32
    SetConsoleTextAttribute(console, fg_l_purple);
#endif
    std::cout << "[SimpleLog]";
}

void debug(const std::string& msg)
{
    logger::log_name();
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_gray);
#endif
    std::cout << " [DEBUG] ";
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_white);
#endif
    std::cout << msg << std::endl;
    thread_write_locked = false;
}

void info(const std::string& msg)
{
    logger::log_name();
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_l_green);
#endif
    std::cout << " [INFO] ";
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_white);
#endif
    std::cout << msg << std::endl;
    thread_write_locked = false;
}

void warn(const std::string& msg)
{
    logger::log_name();
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_l_yellow);
#endif
    std::cout << " [WARN] ";
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_white);
#endif
    std::cout << msg << std::endl;
    thread_write_locked = false;
}

void err(const std::string& msg)
{
    logger::log_name();
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_l_red);
#endif
    std::cout << " [ERR] ";
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_white);
#endif
    std::cout << msg << std::endl;
    thread_write_locked = false;
}

void fatal(const std::string& msg)
{
    logger::log_name();
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_red);
#endif
    std::cout << " [FATAL] ";
#ifdef _WIN32
    SetConsoleTextAttribute(logger::console, fg_white);
#endif
    std::cout << msg << std::endl;
    thread_write_locked = false;
}

void logger::log_debug(const std::string& msg)
{
    std::thread log_thread(debug, msg);
    log_thread.join();
}

void logger:: log_info(const std::string& msg)
{
    std::thread log_thread(info, msg);
    log_thread.join();
}

void logger:: log_warn(const std::string& msg)
{
    std::thread log_thread(warn, msg);
    log_thread.join();
}

void logger::log_err(const std::string& msg)
{
    std::thread log_thread(err, msg);
    log_thread.join();
}

void logger::log_fatal(const std::string& msg)
{
    std::thread log_thread(fatal, msg);
    log_thread.join();
}
