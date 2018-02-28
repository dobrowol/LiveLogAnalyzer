#include <iostream>
#include "concurrent_queue.cpp"
#include "fileWatcher/fileWatcher.cpp"
#include <thread>
using namespace std;
using namespace utils;

concurrent_queue q;

void runFileWatcher()
{
    fileWatcher::FileWatcher fw("./example.txt", q);
    fw.proceed();
}

int main(int argc, char *argv[])
{
    std::thread t(runFileWatcher);
    t.join();
    return 0;
}
