#include <iostream>
#include "concurrent_queue.cpp"
#include "fileWatcher/fileWatcher.cpp"
using namespace std;
using namespace utils;

concurrent_queue q;


int main(int argc, char *argv[])
{
    fileWatcher::FileWatcher fw("", q);
    cout << "Hello World!" << endl;
    return 0;
}
