#include "backend.h"
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <unordered_map>
#include <utility>

std::vector<std::string> backend::search(std::string folderPath, std::pair<std::string, std::string> createdDates, std::pair<std::string, std::string> modifiedDates){
  std::vector<std::string> files;
  for (const auto & entry : std::filesystem::directory_iterator(folderPath)){
    std::string file = entry.path().u8string();
    struct stat t_stat;
    stat(file.c_str(), &t_stat);
    std::string createdDate = backend::dateConverter(std::ctime(&t_stat.st_ctime));
    std::string modifiedDate = backend::dateConverter(std::ctime(&t_stat.st_mtime));
    if(createdDates.first != "NULL" && createdDates.second != "NULL"){
      if(!dateRangeComparison(createdDate, createdDates)){
        // If date is not in between given date range, don't add file
        continue;
      }
    }

    if(modifiedDates.first != "NULL" && modifiedDates.second != "NULL"){
      if(!dateRangeComparison(modifiedDate, modifiedDates)){
        // If date is not in between given date range, don't add file
        continue;
      }
    }

    // Only add file if passes criteria
    files.push_back(file);
  }
  return files;
}

// Converts date to MM/DD/YYYY Format
std::string backend::dateConverter(std::string date){
  // date is originally in this example format: "Sat Sep 19 18:57:40 2020"
  // after this modification, date should be: "Sep 19 2020"
  date = date.substr(4,7)+date.substr(20,4);
  // date should now be : "09/19/2020"
  date = backend::getMonthIndex(date.substr(0,3))+"/"+date.substr(4,2)+"/"+date.substr(7,4);
  return date;
}

std::string backend::getMonthIndex(std::string month)
{
    std::unordered_map<std::string, std::string> months
    {
        { "Jan", "01" },
        { "Feb", "02" },
        { "Mar", "03" },
        { "Apr", "04" },
        { "May", "05" },
        { "Jun", "06" },
        { "Jul", "07" },
        { "Aug", "08" },
        { "Sep", "09" },
        { "Oct", "10" },
        { "Nov", "11" },
        { "Dec", "12" }
    };

    const auto iter = months.find(month);

    if( iter != months.cend() )
        return iter->second;
    return "ERROR";
}

// Returns true if date is in the range.
// Returns false otherwise.
bool backend::dateRangeComparison(std::string date, std::pair<std::string, std::string> dateRange){
  // Convert date strings to stringstreams so can be parsed.
  std::stringstream dateStream(date);
  std::stringstream fromDateStream(dateRange.first);
  std::stringstream toDateStream(dateRange.second);

  // Get dates in terms of seconds so easy to compare
  struct tm dateTime;
  dateStream >> std::get_time( &dateTime, "%d\\%m\\%Y" );
  std::time_t dateSeconds = std::mktime( & dateTime );

  struct tm fromDateTime;
  fromDateStream >> std::get_time( &fromDateTime, "%d\\%m\\%Y" );
  std::time_t fromDateSeconds = std::mktime( & fromDateTime );

  struct tm toDateTime;
  toDateStream >> std::get_time( &toDateTime, "%d\\%m\\%Y" );
  std::time_t toDateSeconds = std::mktime( & toDateTime );

  // If date is in range return true, else return false
  if(dateSeconds >= fromDateSeconds && dateSeconds <= toDateSeconds){
    return true;
  }

  return false;
}

// Function serves as link between JS and C++ so that objects can be converted between languages
Napi::Array backend::searchWrapped(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();

  // Parsing input
  std::string folderPath = info[0].ToString().Utf8Value();
  std::string createdFromDate = info[1].ToString().Utf8Value();
  std::string createdToDate = info[2].ToString().Utf8Value();
  std::string modifiedFromDate = info[3].ToString().Utf8Value();
  std::string modifiedToDate = info[4].ToString().Utf8Value();

  // Call search function
  std::vector<std::string> results = backend::search(folderPath, std::make_pair(createdFromDate, createdToDate), std::make_pair(modifiedFromDate, modifiedToDate));

  // Iterate through vector to create Napi::Array based on results
  Napi::Array napiResults = Napi::Array::New(env, results.size());
  for (int i = 0; i < results.size(); i++){
    napiResults[i] = Napi::String::New(env, results[i]);
  }
  return napiResults;
}

Napi::Object backend::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("search", Napi::Function::New(env, backend::searchWrapped));
  return exports;
}
