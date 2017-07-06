#pragma once
#ifndef __GC_WORKER_HPP__
#define __GC_WORKER_HPP__

#include "baseObj.hpp"
#include "gc.hpp"
#include "../../Tools/include/log.hpp"
#include "../../Tools/include/threadExt.hpp"

namespace ROOT_SPACE
{
    class gcWorker
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
                if( item->quote() <= 0 && !item->destory() )
                {
                    gc::instance().cacheObj( *item );
                    continue;
                }
                delete item;
            }

            //删除当前栈管理对象
            mGcWorkers[ mThreadId ]->pop();
            if( mGcWorkers[ mThreadId ]->size() <= 0 )
            {
                delete mGcWorkers[ mThreadId ];
                mGcWorkers.erase( mThreadId );
            }
        }

        //将对象加入自动回收系统
        static void autoRelease( baseObj & p_bobj )
        {
			if ( !mGcWorkers.size () || mGcWorkers.find( ws::PthreadSelf () ) == mGcWorkers.end() || !mGcWorkers[ws::PthreadSelf ()]->size())
			{
				ws::log.warning ( "the current thread has no gcWorker!" );
				return;
			}
            mGcWorkers[ws::PthreadSelf()]->top()->mManageObjList.push_back( &p_bobj );
        }

    private:

		static std::map< unsigned int, std::stack< gcWorker * > * > mGcWorkers;

        unsigned int mThreadId;
        std::list< baseObj * > mManageObjList;
    };

	std::map< unsigned int, std::stack< gcWorker * > * > gcWorker::mGcWorkers;
}

#endif //__GC_WORKER_HPP__