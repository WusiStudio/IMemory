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
		friend class gcWorker;
    public:
    
        virtual void retain( void )
        {
            QuoteMutex().lock();
            mQuote++;
            QuoteMutex().unlock();
        }
        
        virtual void release( void )
        {
            QuoteMutex().lock();
            mQuote--;
            QuoteMutex().unlock();
        }

        int frequency( void ) const
        {
            return mFrequency;
        }

		int frequencyMinusOne(void)
		{
			return --mFrequency;
		}

		void setFrequency ( const int p_frequency )
		{
			mFrequency = p_frequency;
		}

        int quote( void ) const
        {
            return mQuote;
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


    private:
        //缓存频率 频率高的在一级缓存  频率低的被回收
        int mFrequency;

        //对象引用数量
        int mQuote;

        static std::mutex & QuoteMutex(void)
        {
            static std::mutex smQuoteMutex;
            return smQuoteMutex;
        }
        
    };
}

#endif //__BASE_OBJ_H__