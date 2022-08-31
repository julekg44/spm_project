//
// Created by Giuliano Galloppi on 31/08/22.
//
//FUNZIONANO DA C++20 , in clion modifica il CmakeLists
#include <barrier>
#include <iostream>
#include <string>
#include <thread>
#include <vector>


/*
 * arrive :arrives at barrier and decrements the expected count (public member function)

 arrive_and_wait : arrives at barrier and decrements the expected count by one, then blocks until current phase completes
(public member function)
 *
 *
 * */

int main() {
    const auto workers = { "anil", "busara", "carl" };

    auto on_completion = []() noexcept {
        // locking not needed here
        static auto phase = "... done\n" "Cleaning up...\n";
        std::cout << phase;
        phase = "... done\n";
    };


    //la funzione 'on completion' e' una funzione esgeuita quando un thread arriva alla barriera e si ferma(?)
    std::barrier sync_point(std::ssize(workers), on_completion);

    auto work = [&](std::string name) {
        std::string product = "  " + name + " worked\n";
        std::cout << product;  // ok, op<< call is atomic
        sync_point.arrive_and_wait(); //qui producono tutti ed aspettano

        //poi vengono stampati tutti
        product = "  " + name + " cleaned\n";
        std::cout << product;
        sync_point.arrive_and_wait();
    };


    //DOVE INIZIA IL MAIN
    std::cout << "Starting...\n";
    std::vector<std::thread> threads;
    for (auto const& worker : workers) { //for each per i thread
        threads.emplace_back(work, worker);
    }
    for (auto& thread : threads) {
        thread.join();
    }
}