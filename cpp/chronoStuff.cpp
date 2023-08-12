#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/io/ios_state.hpp"
#include <chrono>
#include <iostream>
#include <time.h>

template <typename T>
struct TD;

int main()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);

    const tm local_tm = *localtime(&tt);

    char buf[100];
    strftime(buf, 100, "%Y-%m-%dT%H:%M:%S", &local_tm);

    std::cout << "Buf " << buf << std::endl;
    std::cout << local_tm.tm_year + 1900 << '\n';
    std::cout << local_tm.tm_mon + 1 << '\n';
    std::cout << local_tm.tm_mday << '\n';
    std::cout << local_tm.tm_hour << ":" << local_tm.tm_min << ":" << local_tm.tm_sec << '\n';

    namespace bp = boost::posix_time;
    namespace bg = boost::gregorian;

    // You can compare now with other ptime values
    boost::posix_time::ptime nine_o_clock = bp::second_clock::local_time() + bp::hours(9);
    boost::posix_time::ptime twelve_o_clock = bp::second_clock::local_time() + bp::hours(12);

    bg::date d = bg::day_clock::local_day();

    auto local_time = bp::second_clock::local_time();

    boost::posix_time::ptime n2 = bp::ptime(d, bp::hours(9));
    boost::posix_time::ptime t2 = bp::ptime(d, bp::hours(12));

    std::cout << "Nine is   " << bp::to_iso_extended_string(nine_o_clock) << std::endl;
    std::cout << "Twelve is " << bp::to_iso_extended_string(twelve_o_clock) << std::endl;

    std::cout << "n2 is     " << bp::to_iso_extended_string(n2) << std::endl;
    std::cout << "t2 is     " << bp::to_iso_extended_string(t2) << std::endl;
    bp::ptime x(d, bp::hours(8) + bp::minutes(20) + bp::seconds(10));

    // Yes this was really written at 430 in the morning :-)
    boost::posix_time::ptime st = bp::ptime(d, bp::hours(4));
    boost::posix_time::ptime et = bp::ptime(d, bp::hours(5));
    {
        boost::io::ios_flags_saver ifs(std::cout);
        std::cout << std::boolalpha;
        std::cout << "( lt > st ) -> " << (local_time > st) << std::endl;
        std::cout << "( lt > et ) -> " << (local_time > et) << std::endl;
    }
    std::cout << bp::to_iso_string(x) << std::endl;
    std::cout << bp::to_iso_extended_string(x) << std::endl;

    std::cout << std::atoi("09") << std::endl;
    std::cout << std::atoi("2") << std::endl;
}
