#include "../electron-gui/node_modules/node-addon-api/napi.h"
#include <iostream>
#include <string>
#include <utility>

namespace backend{
  std::vector<std::string> search(std::string folderPath, std::pair<std::string, std::string> accessedDates, std::pair<std::string, std::string> modifiedDates);
  std::string deleteFiles(std::vector<std::string> fileNames);
  std::string dateConverter(std::string date);
  std::string getMonthIndex(std::string month);
  bool dateRangeComparison(std::string date, std::pair<std::string, std::string> dateRange);
  Napi::Array searchWrapped(const Napi::CallbackInfo& info);
  Napi::String deleteFilesWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
