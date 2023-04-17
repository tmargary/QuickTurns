#pragma once

#include <iostream>
#include <map>
#include <sqlite3.h>
#include <string>

struct Book
{
    std::string bookPath;
    std::string bookName;
    std::string bookAuthorName;
    int bookYear{};
    int lastPage{};
    Book(std::string path, std::string bName, std::string aName, int year, int lPage)
        : bookPath(path), bookName(bName), bookAuthorName(aName), bookYear(year), lastPage(lPage)
    {
    }
    void print()
    {
        std::cout << bookPath << " " << bookName << " " << bookAuthorName << " " << bookYear << " " << lastPage
                  << " \n";
    }
};

class BookDB
{
  private:
    std::string bookDBTable;
    sqlite3 *DB;
    char *messaggeError;
    int exit = 0;
    sqlite3_stmt *stmt;

  public:
    BookDB(const std::string& dbFilePath);
    ~BookDB();
    int addBook(Book);
    std::map<int, Book> *getData();
    void changeLastePage(int, int);
    Book getBookById(int bookId);
    int generateRandomId();
    bool idExists(int id);
};