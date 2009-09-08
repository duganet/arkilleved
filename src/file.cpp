#include "file.h"
std::string path_construct(std::string dir_shortname, std::string filename)
{
    std::string dir_basename;
    #ifdef _WIN32
    dir_basename = "";
    #else
    dir_basename = DATADIR "/arkilloid/";
    #endif
    return dir_basename + dir_shortname + "/" + filename;
}
