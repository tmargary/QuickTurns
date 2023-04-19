#pragma once

#include <iostream>
#include <map>
#include <sqlite3.h>
#include <string>
#include "BookMetadata.h"


class BookDB
{

  public:
    BookDB(const std::string &dbFilePath);
    Book getBookById(int bookId);
    Book getBookByPath(const std::string &bookPath);
    std::map<int, Book> *getBooksList();
    int addBookToDatabase(const Book& curBook);
    bool bookExists(const Book &bookToCheck);
    void changeLastePage(int, int);
    void removeBook(int bookId);
    ~BookDB();

  private:
    void createTable(const std::string &dbFilePath);
    void executeInsertQuery(int randomId, Book curBook);
    int generateUniqueId();
    int generateRandomId();
    bool idExists(int id);

  private:
    std::string bookDBTable;
    sqlite3 *DB;
    char *messaggeError;
    int exit = 0;
    sqlite3_stmt *stmt;
};