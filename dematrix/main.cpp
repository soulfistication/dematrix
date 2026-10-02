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
    cout << "dematrix ver. " << kProgramVersion << endl;
    
    const string prefix = "ESOCEP";
    const string extension = ".DAT";
    string base = getCurrentDirectory() + kPathSeparator;
    
    ifstream reader((base + "EP.DAT").c_str());
    
    if (!reader) {
        cout << "File not found on Dematrix. Exiting..." << endl;
        return 1;
    }
    
    ofstream writer1((base + prefix + "F1" + extension).c_str());
    ofstream writer2((base + prefix + "F3" + extension).c_str());
    ofstream writer3((base + prefix + "C3" + extension).c_str());
    ofstream writer4((base + prefix + "P3" + extension).c_str());
    ofstream writer5((base + prefix + "O1" + extension).c_str());
    ofstream writer6((base + prefix + "F7" + extension).c_str());
    ofstream writer7((base + prefix + "T3" + extension).c_str());
    ofstream writer8((base + prefix + "T5" + extension).c_str());
    ofstream writer9((base + prefix + "F2" + extension).c_str());
    ofstream writer10((base + prefix + "F4" + extension).c_str());
    ofstream writer11((base + prefix + "C4" + extension).c_str());
    ofstream writer12((base + prefix + "P4" + extension).c_str());
    ofstream writer13((base + prefix + "02" + extension).c_str());
    ofstream writer14((base + prefix + "F8" + extension).c_str());
    ofstream writer15((base + prefix + "T4" + extension).c_str());
    ofstream writer16((base + prefix + "T6" + extension).c_str());
                     
    return EXIT_SUCCESS;
}
