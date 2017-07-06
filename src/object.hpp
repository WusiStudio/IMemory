#pragma once
#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include "baseObj.hpp"
#include "gc.hpp"
#include "gcWorker.hpp"
#include "../../Tools/include/log.hpp"
#include <cassert>

namespace ROOT_SPACE
{

    #define CREATEFUNC(class)													\
		public:																	\
            static class & Create(void)                                         \
                {                                                               \
                    class * result = ( class * )ws::gc::instance ().getObj ( typeid( class ).name () );\
                    if( !result )                                               \
                    {                                                           \
                        result = new class();                                   \
                    }                                                           \
                                                                                \
                    if( result->init() )                                        \
                    {                                                           \
                        delete result;                                          \
                        result = nullptr;                                       \
                    }                                                           \
                                                                                \
                    assert( result );                                           \
                                                                                \
                    ws::gcWorker::autoRelease ( *(baseObj *)result );           \
                    return * result;                                            \
                }                                                               \

//当前作用域中启
#define IMSTACK		ws::gcWorker __FILE_##__LINE__;
#define IMGCMake	ws::gc::instance().makeCache();

    class object : public baseObj
    {
        CREATEFUNC( object )
    public:

        //引用加一
        virtual void retain( void ) override
        {
            baseObj::retain();
        }

        //引用减一
        virtual void release( void ) override
        {
            baseObj::release();

            if( baseObj::quote() > 0 ) return;

            if( quote() < 0 )
            {
                log.warning( "release does not match retain" );
            }

            if( quote() <= 0 && this->destory() )
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

		object ( void )
		{

		}

		virtual ~object ( void )
		{

		}

    private:
    };
}

#endif //__OBJECT_HPP__