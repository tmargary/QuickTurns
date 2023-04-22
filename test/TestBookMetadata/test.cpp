#include "BookMetadata.h"
#include "gtest/gtest.h"


TEST(BookTest, BuilderBasic)
{
    Book book = Book::create()
                    .setBookPath("path/to/test/book.epub")
                    .setTitle("Test Book")
                    .setAuthor("Test Author")
                    .setLastPage(5)
                    .build();

    EXPECT_EQ("path/to/test/book.epub", book.bookPath);
    EXPECT_EQ("Test Book", book.title);
    EXPECT_EQ("Test Author", book.author);
    EXPECT_EQ(5, book.lastPage);
}