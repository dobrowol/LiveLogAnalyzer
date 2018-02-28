#include <condition_variable>
#include <mutex>
#include <queue>
#include "concurrent_queue.hpp"
namespace utils
{
    void concurrent_queue::push(std::string const& data)
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        bool const was_empty=the_queue.empty();
        the_queue.push(data);

        if(was_empty)
        {
            the_condition_variable.notify_one();
        }
    }
    std::string concurrent_queue::wait_and_pop()
    {
        std::unique_lock<std::mutex> lock(the_mutex);
        while(the_queue.empty())
        {
            the_condition_variable.wait(lock);
        }
        
        std::string return_value=the_queue.front();
        the_queue.pop();
        return return_value;
    }
}
