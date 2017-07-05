#pragma once
#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include "baseObj.hpp"
#include "gc.hpp"
#include "../../Tools/include/log.hpp"

namespace ROOT_SPACE
{
    class object : public baseObj
    {
    public:
        //引用加一
        virtual void retain( void ) override
        {
            mQuoteMutex.lock();
            mQuote++;
            mQuoteMutex.unlock();
        }

        //引用减一
        virtual void release( void ) override
        {
            mQuoteMutex.lock();
            mQuote--;
            mQuoteMutex.unlock();

            if( mQuote > 0 ) return;

            if( mQuote < 0 )
            {
                log.warning( "release does not match retain" );
            }

            if( mQuote <= 0 && this->destory() )
            {
                gc::instance().cacheObj( *this );
                return;
            }

            delete this;
        }
    protected:
        virtual int init( void ) override
        {
            return baseObj::init();
        }

        virtual int destory( void ) override
        {
            return baseObj::destory();
        }
    private:
        static ws::log;
        static std::mutex mQuoteMutex;
    };
}

#endif //__OBJECT_HPP__