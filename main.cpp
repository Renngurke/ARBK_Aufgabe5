// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std:mutex

std::mutex mtx;

void kleinbuchstaben()
{
    mtx.lock();
    for (int a=0; a < 26; a++){
        std::cout << char(a + 97) << ' ';
    }
    std::cout << std::endl;
    mtx.unlock();
}

void grossbuchstaben()
{
    mtx.lock();
    for (int b=0;b<26;b++){
        std::cout << char(b+65) << ' ';
    }
    std::cout << std::endl;
    mtx.unlock();
}


void nullbiszweiundreissig()
{
    mtx.lock();
    for (int c=1;c<=32;c++){
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    mtx.unlock();
}
void print_block(int a, int b, int c, bool d){
    mtx.lock();
    for (int i=a;i<b;i++){
        if (d==true)
        {
            std::cout << char(i+c) << ' ';
        }
        else
        {
            std::cout << i << ' ';
        }

    }
    std::cout << std::endl;
    mtx.unlock();
}
int main()
{
//    std::thread klein (kleinbuchstaben);
//    std::thread zahl (nullbiszweiundreissig);
//    std::thread gross (grossbuchstaben);


std::thread test2 (print_block,0,26,97,true);
std::thread test3 (print_block,0,26,65,true);
std::thread test(print_block,1,33,0,false);

test2.join();
test3.join();
test.join();

    return 0;
}