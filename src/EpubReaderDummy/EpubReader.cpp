#include <vector>
#include <string>
#include <iostream>
#include "libzippp.h"
using namespace libzippp;

int main(int argc, char **argv)
{
    ZipArchive zf("/home/tigran/Shared/Professional C++ (Marc Gregoire) (ed 5).epub");
    zf.open(ZipArchive::ReadOnly);

    std::vector<ZipEntry> entries = zf.getEntries();
    std::vector<ZipEntry>::iterator it;
    for (it = entries.begin(); it != entries.end(); ++it)
    {
        ZipEntry entry = *it;
        std::string name = entry.getName();
        int size = entry.getSize();

        // the length of binaryData will be size
        void *binaryData = entry.readAsBinary();
        
        // the length of textData will be size
        std::string textData = entry.readAsText();
        std::cout << textData;
        exit;
        //...
    }

    zf.close();

    return 0;
}

/* #include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>


int main()
{
    const std::std::string epubFilePath = "/home/tigran/Shared/Professional C++ (Marc Gregoire) (ed 5).epub";
    const std::std::string destinationDir = "/home/tigran/Downloads/abc";

    std::ifstream epub_file(epubFilePath, std::ios_base::in);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(epub_file);

    std::std::stringstream ss;
    boost::iostreams::copy(in, ss);
    std::std::string epub_contents = ss.str();

    boost::filesystem::path output_dir(destinationDir);
    boost::filesystem::create_directories(output_dir);

    boost::zip::zip_file epub_zip_file(ss);

    // for (auto &entry : epub_zip_file)
    // {
    //     boost::filesystem::path entry_path(output_dir / entry.get_path());
    //     boost::filesystem::create_directories(entry_path.parent_path());

    //     std::ofstream out(entry_path.std::string(), std::ios_base::out);
    //     boost::iostreams::copy(entry.get_stream(), out);


    return 0;
} */