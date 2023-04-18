#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tinyxml2.h>
#include <tuple>

#include <BookMetadata.h>

std::string parseDate(const std::string &dateStr)
{
    int year, month, day;
    std::istringstream dateStream(dateStr);
    std::string temp;

    std::getline(dateStream, temp, '-');
    year = std::stoi(temp);

    std::getline(dateStream, temp, '-');
    month = std::stoi(temp);

    std::getline(dateStream, temp, 'T');
    day = std::stoi(temp);

    std::ostringstream parsedDateStream;
    parsedDateStream << year << "-" << month << "-" << day;
    return parsedDateStream.str();
}

BookMetadata parseMetadata(const std::string &xmlContent)
{
    using namespace tinyxml2;
    XMLDocument doc;
    XMLError error = doc.Parse(xmlContent.c_str());

    if (error != XML_SUCCESS)
    {
        throw std::runtime_error("Failed to parse XML content.");
    }

    BookMetadata metadata;

    auto metadataElement = doc.FirstChildElement("package")->FirstChildElement("metadata");

    // Extract book title
    if (auto titleElement = metadataElement->FirstChildElement("dc:title"))
    {
        metadata.title = titleElement->GetText();
    }

    // Extract author name
    if (auto creatorElement = metadataElement->FirstChildElement("dc:creator"))
    {
        metadata.author = creatorElement->GetText();
        metadata.author_file_as = creatorElement->Attribute("opf:file-as");
    }

    // Extract contributor
    if (auto contributorElement = metadataElement->FirstChildElement("dc:contributor"))
    {
        metadata.contributor = contributorElement->GetText();
    }

    // Extract publisher
    if (auto publisherElement = metadataElement->FirstChildElement("dc:publisher"))
    {
        metadata.publisher = publisherElement->GetText();
    }

    // Extract UUID
    if (auto uuidElement = metadataElement->FirstChildElement("dc:identifier"))
    {
        metadata.uuid = uuidElement->GetText();
    }

    // Extract date
    if (auto dateElement = metadataElement->FirstChildElement("dc:date"))
    {
        const std::string dateStr = dateElement->GetText();
        std::string parsedDate = parseDate(dateStr);
        metadata.date = parsedDate;
    }

    // Extract rights
    if (auto rightsElement = metadataElement->FirstChildElement("dc:rights"))
    {
        metadata.rights = rightsElement->GetText();
    }

    // Extract language
    if (auto languageElement = metadataElement->FirstChildElement("dc:language"))
    {
        metadata.language = languageElement->GetText();
    }

    // Extract ISBN
    if (auto isbnElement = metadataElement->FirstChildElement("dc:identifier[opf:scheme='ISBN']"))
    {
        metadata.isbn = isbnElement->GetText();
    }

    return metadata;
}