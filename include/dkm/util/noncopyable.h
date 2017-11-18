
#ifndef _DKM_NONCOPYABLE_H_
#define _DKM_NONCOPYABLE_H_

namespace dkm
{

class NonCopyable
{
public:
    NonCopyable() { }
    virtual ~NonCopyable() { }

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

}

#endif