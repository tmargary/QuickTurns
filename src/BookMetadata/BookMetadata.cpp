#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tinyxml2.h>
#include <tuple>

#include "BookMetadata.h"
#include "ArchiveExtractor.h"

Book::Builder Book::create()
{
    return Builder();
}


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

Book parseMetadata(const std::string &filePath)
{
    // Extract the epub archive
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(filePath, "");
    const std::string xmlContent = extractor->readSpecificEntry("content.opf");

    using namespace tinyxml2;
    XMLDocument doc;
    XMLError error = doc.Parse(xmlContent.c_str());

    if (error != XML_SUCCESS)
    {
        throw std::runtime_error("Failed to parse XML content.");
    }

    Book::Builder builder;

    auto metadataElement = doc.FirstChildElement("package")->FirstChildElement("metadata");

    // Extract book title
    if (auto titleElement = metadataElement->FirstChildElement("dc:title"))
    {
        builder.setTitle(titleElement->GetText());
    }

    // Extract author name
    if (auto creatorElement = metadataElement->FirstChildElement("dc:creator"))
    {
        builder.setAuthor(creatorElement->GetText())
            .setAuthorFileAs(creatorElement->Attribute("opf:file-as"));
    }

    // Extract contributor
    if (auto contributorElement = metadataElement->FirstChildElement("dc:contributor"))
    {
        builder.setContributor(contributorElement->GetText());
    }

    // Extract publisher
    if (auto publisherElement = metadataElement->FirstChildElement("dc:publisher"))
    {
        builder.setPublisher(publisherElement->GetText());
    }

    // Extract UUID
    if (auto uuidElement = metadataElement->FirstChildElement("dc:identifier"))
    {
        builder.setUuid(uuidElement->GetText());
    }

    // Extract date
    if (auto dateElement = metadataElement->FirstChildElement("dc:date"))
    {
        const std::string dateStr = dateElement->GetText();
        std::string parsedDate = parseDate(dateStr);
        builder.setDate(parsedDate);
    }

    // Extract rights
    if (auto rightsElement = metadataElement->FirstChildElement("dc:rights"))
    {
        builder.setRights(rightsElement->GetText());
    }

    // Extract language
    if (auto languageElement = metadataElement->FirstChildElement("dc:language"))
    {
        builder.setLanguage(languageElement->GetText());
    }

    // Extract ISBN
    if (auto isbnElement = metadataElement->FirstChildElement("dc:identifier[opf:scheme='ISBN']"))
    {
        builder.setIsbn(isbnElement->GetText());
    }

    // Set remaining fields
    builder.setBookPath(filePath);

    return builder.build();
}
