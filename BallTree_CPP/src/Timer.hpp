//
//

#ifndef BALLTREE_TIMER_HPP
#define BALLTREE_TIMER_HPP

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <unistd.h>

using namespace std;

template<typename>
class Timer;

template<typename R, typename... T>
class Timer<R(T...)> {
public:
    typedef R (*function_type)(T...);

    function_type function;

    explicit Timer(function_type function, string process_name = "")
            : function_(function), process_name_(process_name) {}

    R operator()(T... args) {
        chrono::time_point<chrono::high_resolution_clock> start, end;
        start = chrono::high_resolution_clock::now();

        R result = function_(forward<T>(args)...);

        end = chrono::high_resolution_clock::now();
        int64_t duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        cout << setw(10) << process_name_ << setw(30)
             << "Duration: " + to_string(duration) + " ms\n";
        return result;
    }

private:
    function_type function_;
    string process_name_;
};


#endif //BALLTREE_TIMER_HPP
