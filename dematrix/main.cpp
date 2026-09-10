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

string getCurrentDirectory() {
#if defined(_WIN32)
    cont int kPathBuffSize = 4096;
    char buff[kPathBuffSize];
    if (_getcwd(buff, sizeof(buff))) {
        return string(buff);
    }
#else
    char buff[PATH_MAX];
    if (getcwd(buff, sizeof(buff))) {
        return string(buff);
    }
#endif
    return ".";
}

int main(int argc, const char * argv[]) {
    cout << "Hello, World!\n";
    return EXIT_SUCCESS;
}
