#include <tinyxml2.h>
#include <optional>

struct BookMetadata
{
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
};

BookMetadata parseMetadata(const std::string& xmlContent);
