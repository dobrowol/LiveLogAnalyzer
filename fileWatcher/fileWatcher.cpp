#include <string>
#include "concurrent_queue.hpp"
#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace utils;
namespace fileWatcher
{
class FileWatcher
{
public:
    FileWatcher(std::string fileName, concurrent_queue& queue):the_fileName(fileName),
        the_queue(queue), lengthRead(0){}

    void proceed()
    {
        processFile();

        uint32_t mask = IN_ALL_EVENTS;
        int fd = inotify_init();
        int wd = inotify_add_watch(fd, the_fileName.c_str(), mask);
        struct pollfd pfd = { fd, POLLIN, 0 };
        int ret;
        while((ret = poll(&pfd, 1, 5000))>=0)
        {// timeout of 50ms
            if (ret < 0) {
                fprintf(stderr, "poll failed: %s\n", strerror(errno));
            } else if (ret == 0) {
                std::cout << "timeout with no events" << std::endl;
            } else {
                // Process the new event.
                struct inotify_event event;
                int nbytes = read(fd, &event, sizeof(event));
                std::cout << "received " << nbytes << " bytes "<<std::endl;
                processFile();

            }
        }
    }

private:

    void processFile()
    {
        std::ifstream infile(the_fileName);
        std::string line;

        infile.seekg(lengthRead);
        while (std::getline(infile, line))
        {
            the_queue.push(line);
        }
        updateLengthRead();
    }
    void updateLengthRead()
    {
        struct stat st;
        stat(the_fileName.c_str(), &st);
        lengthRead = st.st_size;
    }

    std::string the_fileName;
    concurrent_queue& the_queue;
    size_t lengthRead;
};
}
