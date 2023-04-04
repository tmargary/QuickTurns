#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <cstring>


std::string get_home_directory()
{
    const char *home_dir;
#if defined(_WIN32)
    home_dir = getenv("USERPROFILE");
#elif defined(__APPLE__) || defined(__linux__)
    home_dir = getenv("HOME");
#else
    // unsupported platform
    return "";
#endif
    if (home_dir == nullptr)
    {
        // environment variable not set
        return "";
    }
    return std::string(home_dir);
}


bool create_directory(const std::string& path) {
    int result = mkdir(path.c_str(), 0777);
    if (result == 0) {
        // directory created successfully
        return true;
    } else if (errno == EEXIST) {
        // directory already exists
        return true;
    } else {
        // failed to create directory
        std::cerr << "Error creating directory " << path << ": " << strerror(errno) << std::endl;
        return false;
    }
}