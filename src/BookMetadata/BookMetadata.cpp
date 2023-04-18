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

std::vector<std::pair<const char *, std::function<void(const tinyxml2::XMLElement *)>>> getMetadataElements(
    Book::Builder &builder)
{
    return {
        {"dc:title", [&builder](const tinyxml2::XMLElement *e) { builder.setTitle(e->GetText() ? e->GetText() : ""); }},
        {"dc:creator",
         [&builder](const tinyxml2::XMLElement *e) {
             builder.setAuthor(e->GetText() ? e->GetText() : "")
                 .setAuthorFileAs(e->Attribute("opf:file-as") ? e->Attribute("opf:file-as") : "");
         }},
        {"dc:contributor",
         [&builder](const tinyxml2::XMLElement *e) { builder.setContributor(e->GetText() ? e->GetText() : ""); }},
        {"dc:publisher",
         [&builder](const tinyxml2::XMLElement *e) { builder.setPublisher(e->GetText() ? e->GetText() : ""); }},
        {"dc:identifier",
         [&builder](const tinyxml2::XMLElement *e) { builder.setUuid(e->GetText() ? e->GetText() : ""); }},
        {"dc:date",
         [&builder](const tinyxml2::XMLElement *e) {
             const std::string dateStr = e->GetText() ? e->GetText() : "";
             std::string parsedDate = parseDate(dateStr);
             builder.setDate(parsedDate);
         }},
        {"dc:rights",
         [&builder](const tinyxml2::XMLElement *e) { builder.setRights(e->GetText() ? e->GetText() : ""); }},
        {"dc:language",
         [&builder](const tinyxml2::XMLElement *e) { builder.setLanguage(e->GetText() ? e->GetText() : ""); }},
        {"dc:identifier[opf:scheme='ISBN']",
         [&builder](const tinyxml2::XMLElement *e) { builder.setIsbn(e->GetText() ? e->GetText() : ""); }}};
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

    if (xmlContent == "")
    {
        std::filesystem::path path(filePath);
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
