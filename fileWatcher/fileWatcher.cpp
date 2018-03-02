#include <string>
#include "concurrent_queue.hpp"
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <sys/stat.h>

using namespace utils;
namespace fileWatcher
{
class FileWatcher
{
public:
    FileWatcher(std::string fileName, concurrent_queue<std::pair<size_t, size_t>>& queue):the_fileName(fileName),
        the_queue(queue), lengthRead(0){}

    void proceed()
    {
        processFile();

        while(true)
        {
                sleep(1);
                processFile();
        }
    }
    void processFile()
    {
        struct stat st;
        stat(the_fileName.c_str(), &st);

        if (lengthRead != st.st_size)
        {
            the_queue.push(std::make_pair(lengthRead, st.st_size));
            lengthRead = st.st_size;
        }
    }
private:
    std::string the_fileName;
    concurrent_queue<std::pair<size_t, size_t>>& the_queue;
    size_t lengthRead;
};
}
