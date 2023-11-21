#ifndef v_LOADER_H_
#define v_LOADER_H_
#include <vector>
#include <future>

namespace v
{
    class Loadable
    {
    private:
        bool m_loaded = false;
    public:
        virtual bool IsLoaded() const { return m_loaded; };
        virtual void Load() { m_loaded = true; };
    };

    class Loader
    {
    private:
        static void Load(Loadable* loadable);
        static std::vector<std::future<void>> futures;
        static std::vector<Loadable*> loadQueue;
    public:
        static void addToLoadQueue(Loadable* loadable);
        static void processLoadQueue();
    };
};

#endif // v_LOADER_H_
