#pragma once
#ifndef __GC_WORKER_HPP__
#define __GC_WORKER_HPP__

#include "baseObj.hpp"
#include "gc.hpp"
#include "../../Tools/include/threadExt.hpp"

namespace ROOT_SPACE
{
    class gcWorker: public baseObj
    {
    public:
        gcWorker(void)
        {
            mThreadId = ws::PthreadSelf();
            if( mGcWorkers.find( mThreadId ) == mGcWorkers.end() )
            {
                mGcWorkers[ mThreadId ] = new std::stack< gcWorker * >();
            }
            mGcWorkers[ mThreadId ]->push( this );
        }

        ~gcWorker(void)
        {
            //将不用的对象放入缓存中
            for(auto item : mManageObjList)
            {
                if( item->mQuote <= 0 && item->destory() )
                {
                    gc::instance().cacheObj( *item );
                    continue;
                }
                delete item;
            }

            //删除当前栈管理对象
            mGcWorkers[ mThreadId ]->pop();
            if( mGcWorkers[ mThreadId ].size() <= 0 )
            {
                delete mGcWorkers[ mThreadId ];
                mGcWorkers.erase( mThreadId );
            }
        }

        //将对象加入自动回收系统
        static void autoRelease( baseObj & p_bobj )
        {
            mGcWorkers[ws::PthreadSelf()].top().push_back( &p_bobj );
        }

    private:
        unsigned int mThreadId;
        static std::map< unsigned int, std::stack< gcWorker * > * > mGcWorkers;
        std::list< baseObj * > mManageObjList;
    };
}

#endif //__GC_WORKER_HPP__