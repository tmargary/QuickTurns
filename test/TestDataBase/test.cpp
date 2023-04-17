#include "DataBase.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(BookDBTest, CreateTableTest)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB1(dbFilePath);
    BookDB testDB2(dbFilePath);
}

TEST(BookDBTest, AddBookTest0)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);
    Book testBook("path/to/book", "Test Book", "John Doe", 2023, 1);
    int bookId = testDB.addBookToDatabase(testBook);

    Book retrievedBook = testDB.getBookById(bookId);

    ASSERT_EQ(testBook.bookPath, retrievedBook.bookPath);
    ASSERT_EQ(testBook.bookName, retrievedBook.bookName);
    ASSERT_EQ(testBook.bookAuthorName, retrievedBook.bookAuthorName);
    ASSERT_EQ(testBook.bookYear, retrievedBook.bookYear);
    ASSERT_EQ(testBook.lastPage, retrievedBook.lastPage);
}

TEST(BookDBTest, AddBookTest1)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);
    Book testBook("", "", "", 0, 0);
    int bookId = testDB.addBookToDatabase(testBook);

    Book retrievedBook = testDB.getBookById(bookId);

    ASSERT_EQ(testBook.bookPath, retrievedBook.bookPath);
    ASSERT_EQ(testBook.bookName, retrievedBook.bookName);
    ASSERT_EQ(testBook.bookAuthorName, retrievedBook.bookAuthorName);
    ASSERT_EQ(testBook.bookYear, retrievedBook.bookYear);
    ASSERT_EQ(testBook.lastPage, retrievedBook.lastPage);
}

TEST(BookDBTest, GetBookByIdTest0)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);

    Book testBook("path/to/book2", "Test Book 2", "Jane Doe", 2022, 2);
    int bookId = testDB.addBookToDatabase(testBook);

    Book retrievedBook = testDB.getBookById(bookId);

    ASSERT_EQ(testBook.bookPath, retrievedBook.bookPath);
    ASSERT_EQ(testBook.bookName, retrievedBook.bookName);
    ASSERT_EQ(testBook.bookAuthorName, retrievedBook.bookAuthorName);
    ASSERT_EQ(testBook.bookYear, retrievedBook.bookYear);
    ASSERT_EQ(testBook.lastPage, retrievedBook.lastPage);
}

TEST(BookDBTest, GetBookByIdTest1)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);

    Book emptyBook("", "", "", 0, 0);
    int nonExistingId = -1;
    Book retrievedBook = testDB.getBookById(nonExistingId);

    ASSERT_EQ(emptyBook.bookPath, retrievedBook.bookPath);
    ASSERT_EQ(emptyBook.bookName, retrievedBook.bookName);
    ASSERT_EQ(emptyBook.bookAuthorName, retrievedBook.bookAuthorName);
    ASSERT_EQ(emptyBook.bookYear, retrievedBook.bookYear);
    ASSERT_EQ(emptyBook.lastPage, retrievedBook.lastPage);
}

TEST(BookDBTest, GetBooksListTest0)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);
    Book testBook1("path/to/book3", "Test Book 3", "Alice", 2021, 3);
    Book testBook2("path/to/book4", "Test Book 4", "Bob", 2020, 4);

    int bookId1 = testDB.addBookToDatabase(testBook1);
    int bookId2 = testDB.addBookToDatabase(testBook2);

    std::map<int, Book> *bookList = testDB.getBooksList();

    ASSERT_TRUE(bookList->find(bookId1) != bookList->end());
    ASSERT_TRUE(bookList->find(bookId2) != bookList->end());

    Book retrievedBook1 = bookList->at(bookId1);
    Book retrievedBook2 = bookList->at(bookId2);

    ASSERT_EQ(testBook1.bookPath, retrievedBook1.bookPath);
    ASSERT_EQ(testBook1.bookName, retrievedBook1.bookName);
    ASSERT_EQ(testBook1.bookAuthorName, retrievedBook1.bookAuthorName);
    ASSERT_EQ(testBook1.bookYear, retrievedBook1.bookYear);
    ASSERT_EQ(testBook1.lastPage, retrievedBook1.lastPage);

    ASSERT_EQ(testBook2.bookPath, retrievedBook2.bookPath);
    ASSERT_EQ(testBook2.bookName, retrievedBook2.bookName);
    ASSERT_EQ(testBook2.bookAuthorName, retrievedBook2.bookAuthorName);
    ASSERT_EQ(testBook2.bookYear, retrievedBook2.bookYear);
    ASSERT_EQ(testBook2.lastPage, retrievedBook2.lastPage);

    delete bookList;
}

TEST(BookDBTest, GetBooksListTest1)
{
    std::string dbFilePath = "emptyDB.db";
    BookDB testDB(dbFilePath);

    std::map<int, Book> *bookList = testDB.getBooksList();

    ASSERT_TRUE(bookList->empty());

    delete bookList;
}


TEST(BookDBTest, ChangeLastPageTest0)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);
    Book testBook("path/to/book5", "Test Book 5", "Eve", 2019, 5);
    int bookId = testDB.addBookToDatabase(testBook);

    int newLastPage = 10;
    testDB.changeLastePage(bookId, newLastPage);

    Book updatedBook = testDB.getBookById(bookId);

    ASSERT_EQ(newLastPage, updatedBook.lastPage);
}

TEST(BookDBTest, ChangeLastPageTest1)
{
    std::string dbFilePath = "testDB.db";
    BookDB testDB(dbFilePath);
    Book testBook("path/to/book5", "Test Book 5", "Eve", 2019, 5);
    int bookId = testDB.addBookToDatabase(testBook);

    int newLastPage = -10;
    testDB.changeLastePage(bookId, newLastPage);

    Book updatedBook = testDB.getBookById(bookId);

    ASSERT_EQ(newLastPage, updatedBook.lastPage);
}