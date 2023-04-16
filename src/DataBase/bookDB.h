#include <iostream>
#include <map>
#include <sqlite3.h>
#include <string>
#pragma once

struct book
{
    std::string bookPath;
    std::string bookName;
    std::string bookAuthorName;
    int bookYear;
    int lastPage;
    book(std::string path, std::string bName, std::string aName, int year, int lPage)
        : bookPath(path), bookName(bName), bookAuthorName(aName), bookYear(year), lastPage(lPage) {}
    void print() {
        std::cout << bookPath << " " << bookName << " " << bookAuthorName << " " << bookYear << " " << lastPage << " \n";
    }
};

class bookDB
{
  private:
    std::string bookDBTable;
    sqlite3 *DB;
    char *messaggeError;
    static int ID;
    int exit = 0;
    sqlite3_stmt *stmt;

  public:
    bookDB();
    ~bookDB();
    void addBook(book);
    std::map<int, book>* getData();
    void changeLastePage(int, int);

};
