#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#if defined(_WIN32)
    #include <direct.h>
#else
    #include <unistd.h>
    #include <climits>
#endif

using namespace std;

const char* const kProgramVersion = "0.1.0";

#if defined(_WIN32)
const char kPathSeparator = '\\';
#else
const char kPathSeparator = '/';
#endif

const char* const kElementSeparator = " ";
const char kNewLine = '\n';

string getCurrentDirectory()
{
#if defined(_WIN32)
    const int kPathBuffSize = 4096;
    char buff[kPathBuffSize];
    if (_getcwd(buff, sizeof(buff)))
    {
        return string(buff);
    }
#else
    char buff[PATH_MAX];
    if (getcwd(buff, sizeof(buff)))
    {
        return string(buff);
    }
#endif
    return ".";
}

const int kNumberOfLines = 102 * 256;
const int kNumberOfColumns = 16;

vector<string> splitByTwoSpaces(const string& line)
{
    vector<string> columns;
    
    const string delim = kElementSeparator;
    size_t start = 0;
    
    for (;;)
    {
        const size_t pos = line.find(delim, start);
        if (pos == string::npos)
        {
            columns.push_back(line.substr(start));
            break;
        }
        columns.push_back(line.substr(start, pos - start));
        start = pos + delim.size();
    }
    
    return columns;
}

int convert(const string& pointString)
{
    const int error = 0;
    
    if (pointString.empty())
    {
        cout << "Point string was null" << endl;
        return error;
    }
    
    const char* cstr = pointString.c_str();
    char *endptr = 0;
    const double point = strtod(cstr, &endptr);
    
    while (endptr && *endptr && isspace(static_cast<unsigned char>(*endptr)))
    {
        ++endptr;
    }
    
    if (endptr == cstr || *endptr != '\0')
    {
        cout << "Error reading point: " << pointString << endl;
        return error;
    }
    
    const double converted = point * 10.0;
    return static_cast<int>(converted);
}

int main(int argc, const char * argv[])
{
    cout << "Hello, World!\n";
    return EXIT_SUCCESS;
}
