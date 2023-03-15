#include "libzippp.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace libzippp;

int main(int argc, char **argv)
{

    const std::string sourceFile = "/home/tigran/Shared/Professional C++ (Marc Gregoire) (ed 5).epub";
    const std::string destinationDir = "/home/tigran/Downloads/abc/";

    ZipArchive zf(sourceFile);
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

        // create a new file with a name based on the Zip entry
        std::string outputFilename = destinationDir + name;

        boost::filesystem::path outputPath(outputFilename);
        boost::filesystem::create_directories(outputPath.parent_path());

        std::ofstream outputFile(outputFilename);

        // write the text data to the file
        outputFile << textData;

        // close the output file
        outputFile.close();
    }

    zf.close();

    return 0;
}