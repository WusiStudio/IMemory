#include "baseObj.h"

namespace ROOT_SPACE
{

    baseObj::baseObj( void )
    {
        mFrequency = 0;
    }

    bool baseObj::init( void )
    {
        mQuote = 0;
    }

    void baseObj::retain( void )
    {
        {
            autoMutex tam( mQuoteMutex );
            mQuote++;
        }
    }

    void baseObj::release( void )
    {
        {
            autoMutex tam( mQuoteMutex );
            mQuote--;
        }
    }
}