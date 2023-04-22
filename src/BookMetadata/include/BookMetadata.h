#pragma once

#include <optional>
#include <tinyxml2.h>
#include <string>

class Book
{
  public:
    struct Builder;

  public:
    int id{};
    std::string bookPath;
    int lastPage{};
    std::optional<std::string> title;
    std::optional<std::string> author;
    std::optional<std::string> author_file_as;
    std::optional<std::string> contributor;
    std::optional<std::string> publisher;
    std::optional<std::string> uuid;
    std::optional<std::string> date;
    std::optional<std::string> rights;
    std::optional<std::string> language;
    std::optional<std::string> isbn;

    Book() = default;

  public:
    static Builder create();

    friend struct Builder;
};

struct Book::Builder
{
    Book b;

    Builder &setId(const int id)
    {
        b.id = id;
        return *this;
    }
    Builder &setBookPath(const std::string &path)
    {
        b.bookPath = path;
        return *this;
    }
    Builder &setTitle(const std::optional<std::string> &title)
    {
        b.title = title;
        return *this;
    }
    Builder &setAuthor(const std::optional<std::string> &author)
    {
        b.author = author;
        return *this;
    }
    Builder &setAuthorFileAs(const std::optional<std::string> &author_file_as)
    {
        b.author_file_as = author_file_as;
        return *this;
    }
    Builder &setDate(const std::optional<std::string> &date)
    {
        b.date = date;
        return *this;
    }
    Builder &setLastPage(int lastPage = 0)
    {
        b.lastPage = lastPage;
        return *this;
    }
    Builder &setContributor(const std::optional<std::string> &contributor)
    {
        b.contributor = contributor;
        return *this;
    }
    Builder &setPublisher(const std::optional<std::string> &publisher)
    {
        b.publisher = publisher;
        return *this;
    }
    Builder &setUuid(const std::optional<std::string> &uuid)
    {
        b.uuid = uuid;
        return *this;
    }
    Builder &setRights(const std::optional<std::string> &rights)
    {
        b.rights = rights;
        return *this;
    }
    Builder &setLanguage(const std::optional<std::string> &language)
    {
        b.language = language;
        return *this;
    }
    Builder &setIsbn(const std::optional<std::string> &isbn)
    {
        b.isbn = isbn;
        return *this;
    }

    Book build()
    {
        return b;
    }
};

Book parseMetadata(const std::string &filePath);
