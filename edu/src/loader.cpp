#include "loader.h"
#include <iostream>
#include <thread>

namespace v {

std::vector<Loadable*> Loader::loadQueue = std::vector<Loadable*>();

void parallel_for(std::vector<Loadable*> loadables)
{
    typedef std::vector<int> container;
    typedef container::iterator iter;

    auto worker = [] (std::vector<Loadable*>::iterator begin, std::vector<Loadable*>::iterator end) {
    for(auto it = begin; it != end; ++it) {
        (*it)->Load();
    }
    };

    // parallel
    const int num_threads = 8;
    std::vector<std::thread> threads(num_threads);
    std::vector<bool> initialized_threads(num_threads);
    for (auto it : initialized_threads) it = false;

    const int grainsize = loadables.size() / num_threads;

    auto init_iter = std::begin(initialized_threads);
    auto work_iter = std::begin(loadables);
    if (grainsize)
    {
        for(auto it = std::begin(threads); it != std::end(threads) - 1; ++it) {
            *it = std::thread(worker, work_iter, work_iter + grainsize);

            *init_iter = true;
            ++init_iter;
            work_iter += grainsize;
        }
        initialized_threads.back() = true;
        threads.back() = std::thread(worker, work_iter, std::end(loadables));
    }
    else
    {
        for(int i = 0; i < loadables.size(); ++i)
        {
            threads[i] = std::thread(worker, work_iter, work_iter + 1);

            work_iter += 1;
            *init_iter = true;
            ++init_iter;
        }
    }

    init_iter = std::begin(initialized_threads);
    for(auto&& i : threads) {
        if(*init_iter)
            i.join();
        ++init_iter;
    }
    threads.clear();
}



void Loader::addToLoadQueue(Loadable *loadable)
{
    Loader::loadQueue.push_back(loadable);
}

void Loader::processLoadQueue()
{
    parallel_for(Loader::loadQueue);

    bool isDone = false;
    while (!isDone)
    {
        isDone = true;
        for(auto& loadable : Loader::loadQueue)
        {
            if (!loadable->IsLoaded())
            {
                isDone = false;
            }
        }
    }
    Loader::loadQueue.clear();

}

}
