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