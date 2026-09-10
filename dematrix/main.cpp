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

int main(int argc, const char * argv[]) {
    cout << "Hello, World!\n";
    return EXIT_SUCCESS;
}
