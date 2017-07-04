#pragma once
#ifndef __GC_H__
#define __GC_H__

#include "baseObj.hpp"
#include "../../Tools/include/threadExt.hpp"

#include <map>
#include <stack>
#include <list>

namespace ROOT_SPACE
{
    class gc : public baseObj
    {
    public:

        gc & getInstance()
        {
            unsigned int tThreadId = ws::PthreadSelf();
            if( sInstances.find( tThreadId ) == sInstances.end() )
            {
                sInstances[ tThreadId ] = new gc();
            }

            return * sInstances[ tThreadId ];
        }

        void makeCache(void)
        {

        }
        
        void setObj( baseObj & p_obj )
        {
            std::string tClassName = typeid( p_obj ).name();
            if( mCache1.find( tClassName ) == mCache1.end() )
            {
                mCache1[ tClassName ] = new std::list< baseObj * >();
            }
            std::list< baseObj * > & tCache = *mCache1[ tClassName ];
            tCache.push_back( & p_obj );
            insertToCacheList( p_obj );
        }

        baseObj * getObj( const std::string & p_classId )
        {
            static std::map< std::string, std::list< baseObj * > * > * tCaches[] = { &mCache1, &mCache2, mCache3 };

            for( auto item : tCaches )
            {
                if( item->find( p_classId ) ==  item->end() ) continue;
                
            }
            return nullptr;
        }
    private:

        void insertToCacheList( baseObj & p_obj )
        {
            mObjCacheList.push_back( & p_obj );
        }

        static std::map<unsigned int, gc *> sInstances;

        //1000
        std::map< std::string, std::list< std::list< baseObj* >::iterator > * > mCache1;
        std::map< std::string, std::list< std::list< baseObj* >::iterator > * > mCache2;
        std::map< std::string, std::list< std::list< baseObj* >::iterator > * > mCache3;
        std::list< baseObj* > mObjCacheList;
    };
}

#endif //__GC_H__