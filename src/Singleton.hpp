
#ifndef Singleton_h
#define Singleton_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/serialization/singleton.hpp>

template <class SINGLETON_CLASS>
class Singleton
{
public:
    inline static SINGLETON_CLASS& instance()
    {
        return boost::serialization::singleton<SINGLETON_CLASS>::get_mutable_instance();
    }

    inline static SINGLETON_CLASS const& const_instance()
    {
        return boost::serialization::singleton<SINGLETON_CLASS>::get_instance();
    }
};

#endif // Singleton_h
