#include "backend.h"
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

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
  std::tm dateTime = {0};
  dateStream >> std::get_time( &dateTime, "%m/%d/%Y" );
  std::time_t dateSeconds = std::mktime( & dateTime );

  std::tm fromDateTime = {0};
  fromDateStream >> std::get_time( &fromDateTime, "%m/%d/%Y" );
  std::time_t fromDateSeconds = std::mktime( & fromDateTime );

  std::tm toDateTime = {0};
  toDateStream >> std::get_time( &toDateTime, "%m/%d/%Y" );
  std::time_t toDateSeconds = std::mktime( & toDateTime );

  // If date is in range return true, else return false
  if(dateSeconds >= fromDateSeconds && dateSeconds <= toDateSeconds){
    return true;
  }

  return false;
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

std::vector<std::string> backend::search(std::string folderPath, std::pair<std::string, std::string> accessedDates, std::pair<std::string, std::string> modifiedDates){
  std::vector<std::string> files;
  for (const auto & entry : std::filesystem::directory_iterator(folderPath)){
    std::string file = entry.path().u8string();
    struct stat t_stat;
    stat(file.c_str(), &t_stat);
    std::string accessedDate = backend::dateConverter(std::ctime(&t_stat.st_atime));
    std::string modifiedDate = backend::dateConverter(std::ctime(&t_stat.st_mtime));
    if (accessedDates.first != "NULL" && accessedDates.second != "NULL"){
      if(!dateRangeComparison(accessedDate, accessedDates)){
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

std::string backend::deleteFiles(std::vector<std::string> fileNames){
  //get current date for folder namespace
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  std::string seconds = std::to_string((now->tm_hour*60*60)+(now->tm_min*60)+now->tm_sec);
  auto p = std::filesystem::path(fileNames[0]);
  std::string folderPath = p.parent_path().u8string()+"-deleted-files-"+std::to_string(now->tm_mon+1)+"-"+std::to_string(now->tm_mday)+"-"+std::to_string(now->tm_year+1900)+"-"+seconds;
  //create folder
  //will ./ here create in correct spot???
  std::filesystem::create_directories(folderPath);
  //move all files to folder
  for(int  i = 0; i < fileNames.size(); i++){
    auto file = std::filesystem::path(fileNames[i]);
    std::filesystem::rename(fileNames[i], folderPath+"/"+file.filename().u8string());
  }
  auto folder = std::filesystem::path(folderPath);
  std::string deltedLocation = folderPath.substr(0,7)+"\$Recycle.Bin/"+folder.filename().u8string();
  std::filesystem::rename(folderPath,deltedLocation);
  return deltedLocation;
}

// Function serves as link between JS and C++ so that objects can be converted between languages
Napi::Array backend::searchWrapped(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  if (info.Length() < 5) {
      Napi::TypeError::New(env, "Incorrect number of arguments.").ThrowAsJavaScriptException();
  }
  // Parsing input
  std::string folderPath = info[0].ToString().Utf8Value();
  std::string accessedFromDate = info[1].ToString().Utf8Value();
  std::string accessedToDate = info[2].ToString().Utf8Value();
  std::string modifiedFromDate = info[3].ToString().Utf8Value();
  std::string modifiedToDate = info[4].ToString().Utf8Value();

  // Call search function
  std::vector<std::string> results = backend::search(folderPath, std::make_pair(accessedFromDate, accessedToDate), std::make_pair(modifiedFromDate, modifiedToDate));

  // Iterate through vector to create Napi::Array based on results
  Napi::Array napiResults = Napi::Array::New(env, results.size());
  for (int i = 0; i < results.size(); i++){
    napiResults[i] = Napi::String::New(env, results[i]);
  }
  return napiResults;
}

Napi::String backend::deleteFilesWrapped(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  if (info.Length() < 1) {
      Napi::TypeError::New(env, "Incorrect number of arguments.").ThrowAsJavaScriptException();
  }
  Napi::Array fileNapiArray = info[0].As<Napi::Array>();
  std::vector<std::string> filesVector;
  for(int i = 0; i < fileNapiArray.Length(); i++){
    filesVector.push_back(static_cast<Napi::Value>(fileNapiArray[i]).ToString().Utf8Value());
  }
  std::string folderName = backend::deleteFiles(filesVector);
  return Napi::String::New(env,folderName);
}

Napi::Object backend::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set("search", Napi::Function::New(env, backend::searchWrapped));
  exports.Set("deleteFiles", Napi::Function::New(env, backend::deleteFilesWrapped));
  return exports;
}
