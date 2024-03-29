#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tinyxml2.h>
#include <tuple>

#include "ArchiveExtractor.h"
#include "BookMetadata.h"

Book::Builder Book::create()
{
    return Builder();
}

std::string parseDate(const std::string &dateStr)
{
    int year{}, month{}, day{};
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

std::vector<std::pair<const char *, std::function<void(const tinyxml2::XMLElement *)>>> getMetadataElements(
    Book::Builder &builder)
{
    return {
        {"dc:title", [&builder](const tinyxml2::XMLElement *elm) { builder.setTitle(elm->GetText() ? elm->GetText() : ""); }},
        {"dc:creator",
         [&builder](const tinyxml2::XMLElement *elm) {
             builder.setAuthor(elm->GetText() ? elm->GetText() : "")
                 .setAuthorFileAs(elm->Attribute("opf:file-as") ? elm->Attribute("opf:file-as") : "");
         }},
        {"dc:contributor",
         [&builder](const tinyxml2::XMLElement *elm) { builder.setContributor(elm->GetText() ? elm->GetText() : ""); }},
        {"dc:publisher",
         [&builder](const tinyxml2::XMLElement *elm) { builder.setPublisher(elm->GetText() ? elm->GetText() : ""); }},
        {"dc:identifier",
         [&builder](const tinyxml2::XMLElement *elm) { builder.setUuid(elm->GetText() ? elm->GetText() : ""); }},
        {"dc:date",
         [&builder](const tinyxml2::XMLElement *elm) {
             const std::string dateStr = elm->GetText() ? elm->GetText() : "";
             std::string parsedDate = parseDate(dateStr);
             builder.setDate(parsedDate);
         }},
        {"dc:rights",
         [&builder](const tinyxml2::XMLElement *elm) { builder.setRights(elm->GetText() ? elm->GetText() : ""); }},
        {"dc:language",
         [&builder](const tinyxml2::XMLElement *elm) { builder.setLanguage(elm->GetText() ? elm->GetText() : ""); }},
        {"dc:identifier[opf:scheme='ISBN']",
         [&builder](const tinyxml2::XMLElement *elm) { builder.setIsbn(elm->GetText() ? elm->GetText() : ""); }}};
}

Book parseMetadata(const std::string &filePath)
{
    // Extract the epub archive
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(filePath, "");
    const std::string xmlContent = extractor->readSpecificEntry("content.opf");

    using namespace tinyxml2;
    XMLDocument doc;
    const XMLError error = doc.Parse(xmlContent.c_str());

    if (error != XML_SUCCESS)
    {
        throw std::runtime_error("Failed to parse XML content.");
    }

    Book::Builder builder;

    if (xmlContent.empty())
    {
        const std::filesystem::path path(filePath);
        builder.setTitle(path.filename());
        return builder.build();
    }

    auto metadataElement = doc.FirstChildElement("package")->FirstChildElement("metadata");

    auto elements = getMetadataElements(builder);

    for (const auto &element : elements)
    {
        if (auto elem = metadataElement->FirstChildElement(element.first))
        {
            element.second(elem);
        }
    }

    return builder.build();
}
