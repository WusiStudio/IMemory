#pragma once
#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include "baseObj.hpp"

#include <vector>

namespace ROOT_SPACE
{
    template<typename eventType>
    struct event
    {
    public:
        event()
        {

        }

        ~event()
        {
            
        }


        event & operator+( const eventType & p_func )
        {
            return bind( p_func );
        }

        event & operator=( const eventType & p_func )
        {
            return bind( p_func );
        }

        event & operator+=( const eventType & p_func )
        {
            return bind( p_func );
        }

        event & append( const eventType & p_func )
        {
            return bind( p_func );
        }

        event & bind( const eventType & p_func )
        {
            //for( eventType item : mEvents )
            //{
            //    if( item == p_func )
            //    {
            //        return *this;
            //    }
            //}
            mEvents.push_back( p_func );
            return * this;
        }

        event & operator-( const eventType & p_func )
        {
            return unbind( p_func );
        }

        event & unbind( const eventType & p_func )
        {
            for( auto i = mEvents.begin(); i != mEvents.end(); ++i )
            {
                if( *i == p_func )
                {
                    mEvents.erase( i );
                    return * this;
                }
            }
            return * this;
        }

        template<typename... Arguments>
        void operator()( const Arguments & ... p_args )
        {
            call( p_args );
        }

        template<typename... Arguments>
        void call( const Arguments & ... p_args )
        {
            for( auto item : mEvents)
            {
                item( p_args );
            }
        }

    private:
        std::vector< eventType > mEvents;
    };
}

#endif //__EVENT_HPP__