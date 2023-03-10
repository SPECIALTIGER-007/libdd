#include "Logging.h"

int main() {
  LOG_INFO << "Test INFO1";
  LOG_DEBUG << "Test DEBUG";
  LOG_INFO << "Test INFO2";
  LOG_WARN << "Test WARN";
  LOG_ERROR << "Test ERROR";
  LOG_FATAL << "Test FATAL";

  // 程序报错退出，以下的内容无法显示
  LOG_INFO << "Test INFO3";
}