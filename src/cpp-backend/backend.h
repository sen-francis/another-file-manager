#include "../electron-gui/node_modules/node-addon-api/napi.h"
#include <iostream>
#include <string>
namespace backend{
  std::vector<std::string> search(std::string folderPath, pair<std::string, std::string> createdDates, pair<std::string, std::string> modifiedDates);
  std::string dateConverter(std::string date);
  int getMonthIndex(string month);
  bool dateRangeComparison(std::string date, pair<std::string, std::string> dateRange);
  Napi::Array searchWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
  NODE_API_MODULE(searchon, Init)
}
