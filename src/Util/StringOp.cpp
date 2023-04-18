#include <string>
#include <algorithm>


std::string createUnderscoreName(const std::string &input)
{
    std::string output = "";
    for (char c : input)
    {
        if (std::isalnum(c))
        {                              // only keep letters and digits
            output += std::tolower(c); // convert to lowercase
        }
        else
        {
            output += '_'; // replace non-alphanumeric characters with underscores
        }
    }
    // remove any trailing underscores
    while (!output.empty() && output.back() == '_')
    {
        output.pop_back();
    }
    return output;
}