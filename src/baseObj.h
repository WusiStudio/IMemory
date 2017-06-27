#pragma once
#ifndef __BASE_OBJ_H__
#define __BASE_OBJ_H__

#ifndef ROOT_SPACE
#define ROOT_SPACE ws
#endif  //ROOT_SPACE

#include "autoMutex.hpp"

namespace ROOT_SPACE
{
    class baseObj
    {
    public:
        //引用加一
        void retain( void );
        //引用减一
        void release( void );
    protected:
        baseObj( void );

        //初始化 用来替代new函数的初始化功能
        virtual bool init( void );

        //缓存频率 频率高的在一级缓存  频率低的被回收
        int mFrequency;
    private:
        //对象引用数量
        int mQuote;
        std::mutex mQuoteMutex;
    };
}

#endif //__BASE_OBJ_H__