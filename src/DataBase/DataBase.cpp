#include "DataBase.h"
#include <QRandomGenerator>

int BookDB::generateRandomId()
{
    int randomId = QRandomGenerator::global()->bounded(1, 1000001);
    return randomId;
}

BookDB::BookDB(const std::string &dbFilePath)
{
    createTable(dbFilePath);
}

void BookDB::createTable(const std::string &dbFilePath)
{
    bookDBTable = "CREATE TABLE IF NOT EXISTS BOOKS("
                  "ID INT PRIMARY KEY NOT NULL, "
                  "BOOKPATH     TEXT    NOT NULL, "
                  "BOOKNAME     TEXT    NOT NULL, "
                  "AUTHORNAME   TEXT    NOT NULL, "
                  "YEAR         INT     NOT NULL, "
                  "LASTPAGE     INT             );";
    exit = sqlite3_open(dbFilePath.c_str(), &DB);
    exit = sqlite3_exec(DB, bookDBTable.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
}

int BookDB::addBookToDatabase(Book curBook)
{
    int randomId = generateUniqueId();

    executeInsertQuery(randomId, curBook);
    return randomId;
}

void BookDB::executeInsertQuery(int randomId, Book curBook)
{
    bookDBTable = "INSERT INTO BOOKS VALUES (" + std::to_string(randomId) + ", '" + curBook.bookPath + "', '" +
                  curBook.bookName + "', '" + curBook.bookAuthorName + "', " + std::to_string(curBook.bookYear) + ", " +
                  std::to_string(curBook.lastPage) + ");";
    exit = sqlite3_exec(DB, bookDBTable.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Insert" << sqlite3_errmsg(DB) << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;
}

int BookDB::generateUniqueId()
{
    int randomId = generateRandomId();

    while (idExists(randomId))
    {
        randomId = generateRandomId();
    }

    return randomId;
}

bool BookDB::idExists(int id)
{
    bool exists = false;
    const char *query = "SELECT id FROM BOOKS WHERE id = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return exists;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        exists = true;
    }

    sqlite3_finalize(stmt);
    return exists;
}

std::map<int, Book> *BookDB::getBooksList()
{
    std::map<int, Book> *bookList = new std::map<int, Book>();
    bookDBTable = "SELECT * FROM BOOKS";
    exit = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *bookPath = (const char *)sqlite3_column_text(stmt, 1);
        const char *bookName = (const char *)sqlite3_column_text(stmt, 2);
        const char *authorName = (const char *)sqlite3_column_text(stmt, 3);
        int year = sqlite3_column_double(stmt, 4);
        int lastPage = sqlite3_column_double(stmt, 5);
        Book tmp(bookPath, bookName, authorName, year, lastPage);
        bookList->insert(std::make_pair(id, tmp));
    }
    if (exit != SQLITE_DONE)
    {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return bookList;
}

void BookDB::changeLastePage(int id, int newPage)
{
    bookDBTable = "UPDATE BOOKS SET LASTPAGE = ? WHERE id = ?";

    exit = sqlite3_prepare_v2(DB, bookDBTable.c_str(), -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cout << "Failed to prepare statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_bind_int(stmt, 1, newPage);
    sqlite3_bind_int(stmt, 2, id);

    exit = sqlite3_step(stmt);

    if (exit != SQLITE_DONE)
    {
        std::cout << "Failed to execute statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
    }

    sqlite3_finalize(stmt);
}

Book BookDB::getBookById(int bookId)
{
    Book result("", "", "", 0, 0);
    const char *query = "SELECT * FROM BOOKS WHERE id = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return result;
    }

    sqlite3_bind_int(stmt, 1, bookId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *bookPath = (const char *)sqlite3_column_text(stmt, 1);
        const char *bookName = (const char *)sqlite3_column_text(stmt, 2);
        const char *authorName = (const char *)sqlite3_column_text(stmt, 3);
        int year = sqlite3_column_double(stmt, 4);
        int lastPage = sqlite3_column_double(stmt, 5);

        result = Book(bookPath, bookName, authorName, year, lastPage);
    }
    else
    {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return result;
}

BookDB::~BookDB()
{
    sqlite3_close(DB);
}
