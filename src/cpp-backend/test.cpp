#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <ctime>
namespace fs = std::filesystem;
int main(){
  for (const auto & entry : fs::directory_iterator("/mnt/c/users/Sen/Desktop/workshop")){
    std::string path = entry.path().u8string();
    struct stat t_stat;
    stat(path.c_str(), &t_stat);
    printf("File Name: %s\n\t Created Time: %s\t Last Modified Time: %s\n",path.c_str() ,std::ctime(&t_stat.st_ctime), std::ctime(&t_stat.st_mtime));
  }
  return 0;
}
