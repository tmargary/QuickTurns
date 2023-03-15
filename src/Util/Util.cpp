
#include <fstream>
#include <boost/filesystem.hpp>

std::string get_project_root_dir() {
    // Get the current working directory
    boost::filesystem::path current_dir = boost::filesystem::current_path();

    // Traverse up the directory hierarchy until we find a directory
    // containing a file named "CMakeLists.txt" (or we reach the root directory)
    while (!boost::filesystem::exists(current_dir / "CMakeLists.txt") && current_dir.has_parent_path()) {
        current_dir = current_dir.parent_path();
    }

    // If we found the project root directory, return it
    if (boost::filesystem::exists(current_dir / "CMakeLists.txt")) {
        return current_dir.string();
    } 
    return boost::filesystem::path().string();
}

std::string read_file_contents(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + file_path);
  }
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
  return contents;
}