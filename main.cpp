// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std:mutex
#include <unistd.h>

std::mutex mtx;

void kleinbuchstaben()
{
    for (int a=0; a < 26; a++){
        std::cout << char(a + 97) << ' ';
    }
    std::cout << std::endl;
}

void grossbuchstaben()
{
    for (int b=0;b<26;b++){
        std::cout << char(b+65) << ' ';
    }
    std::cout << std::endl;
}


void nullbiszweiundreissig()
{
    for (int c=1;c<=32;c++){
        std::cout << c << ' ';
    }
    std::cout << std::endl;
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
void Aufgabe_a(){
   std::thread klein (kleinbuchstaben);
   std::thread zahl (nullbiszweiundreissig);
   std::thread gross (grossbuchstaben);

   klein.detach();
   zahl.detach();
   gross.detach();

}
void Aufgabe_b() {
    std::thread test2 (print_block,0,26,97,true);
    std::thread test3 (print_block,0,26,65,true);
    std::thread test(print_block,1,33,0,false);

    test2.join();
    test3.join();
    test.join();

}

void Aufgabe_c()
{

}

int main()
{
    std::cout << "Hier Aufgabe A" << std::endl;

    Aufgabe_a();

    usleep(500000);
    std::cout<< '\n';
    std::cout << "Hier Aufgabe B" << std::endl;

    Aufgabe_b();
    usleep(500000);
    std::cout<< '\n';
    std::cout << "Hier Aufgabe C" << std::endl;

    Aufgabe_c();

    return 0;
}
