#include "DataBase.h"
#include <sqlite3.h>
#include <string>

int main()
{
    BookDB dp;

    std::string path = "path 2";
    std::string bName = "book name 2";
    std::string aName = "author name 2";
    int year = 1994;
    int p = 45;
    book girq(path, bName, aName, year, p);
    dp.addBook(girq);

    std::map<int, book>* bookMap = dp.getData();
    if (!bookMap) {
        std::cout << "Error: bookMap is null" << std::endl;
        return 1;
    }
    for (auto it = bookMap->begin(); it != bookMap->end(); ++it)
    {
        std::cout << it->first << ": ";
        it->second.print();
    }
    std::cout << std::endl;

    dp.changeLastePage(5, 15);

    bookMap = dp.getData();
    if (!bookMap)
    {
        std::cout << "Error: bookMap is null" << std::endl;
        return 1;
    }
    for (auto it = bookMap->begin(); it != bookMap->end(); ++it)
    {
        std::cout << it->first << ": ";
        it->second.print();
    }

    delete bookMap;
    return 0;
}
