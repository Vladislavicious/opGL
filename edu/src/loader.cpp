#include "loader.h"
#include <iostream>
#include <thread>

namespace v {

std::vector<Loadable*> Loader::loadQueue = std::vector<Loadable*>();
std::vector<std::future<void>> Loader::futures = std::vector<std::future<void>>();

void Loader::Load(Loadable *loadable)
{
    loadable->Load();
}

void Loader::addToLoadQueue(Loadable *loadable)
{
    Loader::loadQueue.push_back(loadable);
    Load(loadable);
    //auto a = std::thread(&Loader::Load, loadable);
    //a.detach();
}

void Loader::processLoadQueue()
{

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
