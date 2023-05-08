/*
* @Author:
* @Date:   2023-05-08 08:47:36
* @Last Modified by:
* @Last Modified time: 2023-05-08 16:08:41
* @Function:
*/
#include <iostream>
#include <memory>
#include <spdlog/common.h>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <type_traits>
#include <cmath>
using namespace std;

/*
 * 日志级别
 * trace 0
 * debug 1
 * info 2
 * warn 3
 * error 4
 * critical 5
 */
int main()
{
    auto logger = spdlog::stdout_color_mt("hello");
    logger->set_level(spdlog::level::info);
    logger->set_pattern("%# %v");
    SPDLOG_LOGGER_CRITICAL(logger, "nihao");
    // logger->critical("nihao");
    return 0;
}
