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
            mThreadId = ws::threadExt::PthreadSelf();
            if( GcWorkers().find( mThreadId ) == GcWorkers().end() )
            {
                GcWorkers()[ mThreadId ] = new std::stack< gcWorker * >();
            }
            GcWorkers()[ mThreadId ]->push( this );
        }

        ~gcWorker(void)
        {
            //将不用的对象放入缓存中
            for(baseObj * item : mManageObjList)
            {
                if( item->quote() <= 0 && !item->destory() )
                {
                    gc::instance().cacheObj( *item );
                    continue;
                }
                delete item;
            }

            //删除当前栈管理对象
            GcWorkers()[ mThreadId ]->pop();
            if( GcWorkers()[ mThreadId ]->size() <= 0 )
            {
                delete GcWorkers()[ mThreadId ];
                GcWorkers().erase( mThreadId );
            }
        }

        //将对象加入自动回收系统
        static void autoRelease( baseObj & p_bobj )
        {
			if ( !GcWorkers().size () || GcWorkers().find( ws::threadExt::PthreadSelf () ) == GcWorkers().end() || !GcWorkers()[ws::threadExt::PthreadSelf ()]->size())
			{
				LOG.warning ( "the current thread has no gcWorker!" );
				return;
			}
            GcWorkers()[ws::threadExt::PthreadSelf()]->top()->mManageObjList.push_back( &p_bobj );
        }

    private:

        static std::map< unsigned int, std::stack< gcWorker * > * > & GcWorkers(void)
        {
            static std::map< unsigned int, std::stack< gcWorker * > * > smGcWorkers;
            return smGcWorkers;
        }
		
        unsigned int mThreadId;
        std::list< baseObj * > mManageObjList;
    };
}

#endif //__GC_WORKER_HPP__