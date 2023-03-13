#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <zip.h>

// Function to extract and process the contents of an EPUB file
void extract_epub(const std::string& file_path, const std::string& dest_path)
{
    // Open the EPUB file using libzip
    int err;
    zip* epub = zip_open(file_path.c_str(), 0, &err);
    if (epub == nullptr) {
        std::cerr << "Error opening EPUB file: " << zip_strerror(epub) << std::endl;
        return;
    }

    // Get the number of entries in the EPUB file
    zip_int64_t num_entries = zip_get_num_entries(epub, 0);

    // Loop over all the entries in the EPUB file
    for (zip_int64_t i = 0; i < num_entries; i++) {
        // Get information about the current entry
        const zip_stat_t* entry_info = zip_get_stat_index(epub, i, 0);

        // Determine the destination path for the current entry
        std::string entry_dest_path = dest_path + entry_info->name;

        // Create any necessary subdirectories in the destination path
        size_t last_slash_pos = entry_dest_path.rfind('/');
        if (last_slash_pos != std::string::npos) {
            std::string parent_dir = entry_dest_path.substr(0, last_slash_pos);
            if (!std::filesystem::exists(parent_dir)) {
                std::filesystem::create_directories(parent_dir);
            }
        }

        // Extract the current entry to the destination path
        zip_file* entry_file = zip_fopen_index(epub, i, 0);
        if (entry_file == nullptr) {
            std::cerr << "Error opening entry " << entry_info->name << ": " << zip_strerror(epub) << std::endl;
            continue;
        }
        std::ofstream output(entry_dest_path, std::ios::binary);
        if (!output.good()) {
            std::cerr << "Error opening output file " << entry_dest_path << std::endl;
            continue;
        }
        char buffer[4096];
        while (true) {
            zip_int64_t bytes_read = zip_fread(entry_file, buffer, sizeof(buffer));
            if (bytes_read < 0) {
                std::cerr << "Error reading from entry " << entry_info->name << ": " << zip_file_strerror(entry_file) << std::endl;
                break;
            }
            if (bytes_read == 0) {
                break;
            }
            output.write(buffer, bytes_read);
        }
        output.close();
        zip_fclose(entry_file);
    }

    // Close the EPUB file
    zip_close(epub);
}


int main()
{
    // Path to the EPUB file to be processed
    std::string file_path = "/home/tigran/Shared/Professional C++ (Marc Gregoire) (ed 5).epub";

    // Path to the directory where the extracted contents will be saved
    std::string dest_path = "/home/tigran/Desktop/extracted_epub/";

    // Call the extract_epub function to extract and process the contents of the EPUB file
    extract_epub(file_path, dest_path);

    // Print a message indicating that the extraction is complete
    std::cout << "Extraction complete." << std::endl;

    return 0;
}