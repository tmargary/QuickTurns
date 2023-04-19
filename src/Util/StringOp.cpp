#include <algorithm>
#include <string>

std::string createUnderscoreName(const std::string &input)
{
    std::string output = "";
    for (const char symbol : input)
    {
        if (std::isalnum(symbol))
        {                              // only keep letters and digits
            output += static_cast<char>(std::tolower(symbol)); // convert to lowercase
        }
        else if (output.empty() || output.back() != '_')
        {
            output += '_'; // replace non-alphanumeric characters with a single underscore
        }
    }
    // remove any trailing underscores
    while (!output.empty() && output.back() == '_')
    {
        output.pop_back();
    }
    return output;
}
