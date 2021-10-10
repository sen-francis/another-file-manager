#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
namespace fs = std::filesystem;

std::string getMonthIndex(std::string month)
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
bool dateRangeComparison(std::string date, std::pair<std::string, std::string> dateRange){
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
std::string dateConverter(std::string date){
  // date is originally in this example format: "Sat Sep 19 18:57:40 2020"
  // after this modification, date should be: "Sep 19 2020"
  date = date.substr(4,7)+date.substr(20,4);
  // date should now be : "09/19/2020"
  date = getMonthIndex(date.substr(0,3))+"/"+date.substr(4,2)+"/"+date.substr(7,4);
  return date;
}

std::vector<std::string> search(std::string folderPath, std::pair<std::string, std::string> createdDates, std::pair<std::string, std::string> modifiedDates){
  std::vector<std::string> files;
  for (const auto & entry : std::filesystem::directory_iterator(folderPath)){
    std::string file = entry.path().u8string();
    struct stat t_stat;
    stat(file.c_str(), &t_stat);
    std::string createdDate = dateConverter(std::ctime(&t_stat.st_ctime));
    std::string modifiedDate = dateConverter(std::ctime(&t_stat.st_mtime));
    std::cout <<"createdDate: " <<createdDate << ", Modified Date: "<<modifiedDate <<"\n" ;
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

int main(){
  /*for (const auto & entry : fs::directory_iterator("/mnt/c/users/Sen/Desktop/workshop")){
    std::string path = entry.path().u8string();
    struct stat t_stat;
    stat(path.c_str(), &t_stat);
    printf("File Name: %s\n\t Created Time: %s\t Last Modified Time: %s\n",path.c_str() ,std::ctime(&t_stat.st_ctime), std::ctime(&t_stat.st_mtime));
  }*/
  std::vector<std::string> tmp = search("/mnt/d/projects/tts-discord-bot", std::make_pair("05/31/2021","06/01/2021"), std::make_pair("NULL","NULL"));
  for(int  i = 0; i < tmp.size(); i++){
    printf("FILE: %s\n", tmp[i].c_str());
  }
  return 0;
}
