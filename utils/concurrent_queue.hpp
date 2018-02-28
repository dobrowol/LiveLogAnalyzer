#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
namespace utils
{
class concurrent_queue
{
private:
    std::queue<std::string> the_queue;
    std::condition_variable the_condition_variable;
    std::mutex the_mutex;
public:
    void push(std::string const& data);
    
    std::string wait_and_pop();
   
};
}
