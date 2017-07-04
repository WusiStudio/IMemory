#pragma once
#ifndef __BASE_OBJ_H__
#define __BASE_OBJ_H__

#ifndef ROOT_SPACE
#define ROOT_SPACE ws
#endif  //ROOT_SPACE

#include <mutex>

namespace ROOT_SPACE
{
    class baseObj
    {
    public:
        //引用加一
        void retain( void )
        {
            mQuoteMutex.lock();
            mQuote++;
            mQuoteMutex.unlock();
        }
        
        //引用减一
        void release( void )
        {
            mQuoteMutex.lock();
            mQuote--;
            mQuoteMutex.unlock();
        }
    protected:
        baseObj( void )
        {
            mFrequency = 0;
        }

        //初始化 用来替代new函数的初始化功能
        //有错误返回true 没有错误返回false
        virtual int init( void )
        {
            mQuote = 0;
            return 0;
        }

        //放入缓存中时调用
        virtual int destory( void )
        {
            mQuote = 0;
            return 0;
        }

        //缓存频率 频率高的在一级缓存  频率低的被回收
        int mFrequency;
    private:
        //对象引用数量
        int mQuote;
        static std::mutex mQuoteMutex;
    };
}

#endif //__BASE_OBJ_H__