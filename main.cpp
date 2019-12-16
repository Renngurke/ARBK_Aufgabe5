// thread example
#include <thread>
#include <chrono>
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std:mutex
#include <stdlib.h>
#include <condition_variable>

#include <string>
std::mutex mtx;
std::condition_variable cv;
std::mutex cv_m;
int sema = 0;
bool done = false;

void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cout << "Waiting... \n";
    cv.wait(lk, []{return sema == 1;});
    std::cout << "...finished waiting. i == 1\n";
    done = true;
}

void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Notifying falsely...\n";
    cv.notify_one(); // waiting thread is notified with i == 0.
    // cv.wait wakes up, checks i, and goes back to waiting

    std::unique_lock<std::mutex> lk(cv_m);
    sema = 1;
    while (!done)
    {
        std::cout << "Notifying true change...\n";
        lk.unlock();
        cv.notify_one(); // waiting thread is notified with i == 1, cv.wait returns
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lk.lock();
    }
}
void kleinbuchstaben1()
{
    for (int a=0; a < 26; a++){
        std::cout << char(a + 97) << ' ';
    }
    std::cout << std::endl;
    signals();
}

void kleinbuchstaben()
{
    for (int a=0; a < 26; a++){
        std::cout << char(a + 97) << ' ';
    }
    std::cout << std::endl;
}
void grossbuchstaben1()
{
    for (int b=0;b<26;b++){
        std::cout << char(b+65) << ' ';
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

void nullbiszweiundreissig1()
{
    for (int c=1;c<=32;c++){
        std::cout << c << ' ';
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
std::thread klein1 (kleinbuchstaben1);
waits();
    _sleep(200);

std::thread zahl1 (nullbiszweiundreissig1);
waits();
    _sleep(200);

std::thread gross1 (grossbuchstaben1);
signals();

klein1.join();
zahl1.join();
gross1.join();

}

int main()
{
    int eingabe;

    while(eingabe =! 0 ){
        std::cout << "Schreiben Sie folgendes fuer die Aufgaben: \n 1 fuer Aufgabe a\n 2 fuer Aufgabe b\n 3 fuer Aufgabe c\n 4 fuer Abbrechen \n ";
        std::cin >> eingabe;
        switch (eingabe){
            case 1:
                std::cout << "Hier Aufgabe A" << std::endl;
                Aufgabe_a();
                std::cout<< '\n';
                _sleep(1000);
                continue;
            case 2:
                std::cout << "Hier Aufgabe B" << std::endl;
                Aufgabe_b();
                std::cout<< '\n';
                _sleep(1000);
                continue;
            case 3:
                std::cout << "Hier Aufgabe C" << std::endl;
                Aufgabe_c();
                std::cout<< '\n';
                _sleep(1000);
                continue;
            case 4:
                break;
        }
        break;
    }










    return 0;
}
