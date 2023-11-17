#ifndef v_LOADER_H_
#define v_LOADER_H_
#include <vector>

namespace v
{
    class Loadable
    {
    private:
        bool m_loaded = false;
    public:
        virtual bool IsLoaded() { return m_loaded; };
        virtual void Load() { m_loaded = true; };
    };

    class Loader
    {
    private:
        static std::vector<Loadable*> loadQueue;
    public:
        static void addToLoadQueue(Loadable* loadable);
        static void processLoadQueue();
    };
};

#endif // v_LOADER_H_
