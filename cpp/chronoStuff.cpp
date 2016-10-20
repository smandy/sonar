#include <chrono>
#include <iostream>
#include <time.h>

int main( int argc,
          char *argv[] ) {
    
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    
    const tm utc_tm = *gmtime(&tt);
    const tm local_tm = *localtime(&tt);
    
    char buf[100];
    strftime(buf, 100, "%Y-%m-%dT%H:%M:%S", &local_tm);
    std::cout << "Buf " << buf << std::endl;
    std::cout << local_tm.tm_year + 1900 << '\n';
    std::cout << local_tm.tm_mon + 1 << '\n';
    std::cout << local_tm.tm_mday << '\n';
    std::cout << local_tm.tm_hour << ":" << local_tm.tm_min << ":" << local_tm.tm_sec << '\n';
};
