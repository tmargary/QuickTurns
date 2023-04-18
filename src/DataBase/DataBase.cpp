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
                  "TITLE        TEXT, "
                  "AUTHOR       TEXT, "
                  "AUTHOR_FILE_AS TEXT, "
                  "CONTRIBUTOR  TEXT, "
                  "PUBLISHER    TEXT, "
                  "UUID         TEXT, "
                  "DATE         TEXT, "
                  "RIGHTS       TEXT, "
                  "LANGUAGE     TEXT, "
                  "ISBN         TEXT, "
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
    Book::Builder builder;

    // Set the fields of the book using the builder's setter methods
    builder.setBookPath(curBook.bookPath)
        .setTitle(curBook.title)
        .setAuthor(curBook.author)
        .setAuthorFileAs(curBook.author_file_as)
        .setContributor(curBook.contributor)
        .setPublisher(curBook.publisher)
        .setUuid(curBook.uuid)
        .setDate(curBook.date)
        .setRights(curBook.rights)
        .setLanguage(curBook.language)
        .setIsbn(curBook.isbn)
        .setLastPage(curBook.lastPage);

    // Build the Book object
    Book book = builder.build();

    // Construct the INSERT query
    bookDBTable = "INSERT INTO BOOKS (ID, BOOKPATH, TITLE, AUTHOR, AUTHOR_FILE_AS, CONTRIBUTOR, PUBLISHER, UUID, DATE, "
                  "RIGHTS, LANGUAGE, ISBN, LASTPAGE) "
                  "VALUES (" +
                  std::to_string(randomId) + ", '" + book.bookPath + "', '" + book.title.value_or("") + "', '" +
                  book.author.value_or("") + "', '" + book.author_file_as.value_or("") + "', '" +
                  book.contributor.value_or("") + "', '" + book.publisher.value_or("") + "', '" +
                  book.uuid.value_or("") + "', '" + book.date.value_or("") + "', '" + book.rights.value_or("") +
                  "', '" + book.language.value_or("") + "', '" + book.isbn.value_or("") + "', " +
                  std::to_string(book.lastPage) + ");";

    // Execute the INSERT query
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
        const char *year = (const char *)sqlite3_column_text(stmt, 4);
        int lastPage = static_cast<int>(sqlite3_column_double(stmt, 5));

        Book tmp = Book::create()
                       .setBookPath(bookPath)
                       .setTitle(bookName)
                       .setAuthor(authorName)
                       .setDate(year)
                       .setLastPage(lastPage)
                       // Add more setters for the remaining fields
                       .build();

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
    Book::Builder builder;
    const char *query = "SELECT * FROM BOOKS WHERE id = ?";
    exit = sqlite3_prepare_v2(DB, query, -1, &stmt, NULL);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return builder.build();
    }

    sqlite3_bind_int(stmt, 1, bookId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *bookPath = (const char *)sqlite3_column_text(stmt, 1);
        const char *bookName = (const char *)sqlite3_column_text(stmt, 2);
        const char *authorName = (const char *)sqlite3_column_text(stmt, 3);
        const char *year = (const char *)sqlite3_column_text(stmt, 4);
        int lastPage = sqlite3_column_double(stmt, 5);

        builder.setBookPath(bookPath)
                       .setBookPath(bookPath)
                       .setTitle(bookName)
                       .setAuthor(authorName)
                       .setDate(year)
                       .setLastPage(lastPage);
        // Add more setters for the remaining fields
    }
    else
    {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(DB) << std::endl;
    }

    sqlite3_finalize(stmt);
    return builder.build();
}


BookDB::~BookDB()
{
    sqlite3_close(DB);
}
