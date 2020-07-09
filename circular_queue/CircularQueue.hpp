#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include "drivers/interrupt/IInterrupt.hpp"
#include "drivers/assert/Assert.hpp"
#include <stdint.h>

template <class T>
class CircularQueue
{
    public:
        CircularQueue(T* array,
                      uint16_t size,
                      bool protectAccess = false,
                      interrupt::IInterrupt* pInterruptControl = nullptr);
        ~CircularQueue();

        void push(T data);
        T pop();
        uint16_t length();
        bool isEmpty();
    private:
        T* data_;
        uint16_t headIndex_;
        uint16_t tailIndex_;
        uint16_t size_;
        uint16_t numData_;
        bool protectAccess_;
        interrupt::IInterrupt* pInterruptControl_;
};

template <class T>
CircularQueue<T>::CircularQueue(T* array,
                                uint16_t size,
                                bool protectAccess,
                                interrupt::IInterrupt* pInterruptControl):
    data_(array),
    size_(size),
    protectAccess_(protectAccess),
    pInterruptControl_(pInterruptControl)
{
    headIndex_ = 0;
    tailIndex_ = 0;
    numData_ = 0;

    if (protectAccess) assert(pInterruptControl_ != nullptr);
}

template <class T>
CircularQueue<T>::~CircularQueue(){}

template <class T>
void CircularQueue<T>::push(T data)
{
    bool wasInterruptsEnabled = (pInterruptControl_ == nullptr) ?
                                false :
                                pInterruptControl_->areInterruptsEnabled();
    if (protectAccess_) pInterruptControl_->disableInterrupts();
    data_[headIndex_] = data;
    headIndex_ = (headIndex_ >= size_ - 1) ? 0 : headIndex_ + 1;
    if (numData_ >= size_)
    {
        tailIndex_ = headIndex_;
    }
    else
    {
        numData_++;
    }
    if (protectAccess_ && wasInterruptsEnabled) pInterruptControl_->enableInterrupts();
}

template <class T>
T CircularQueue<T>::pop()
{
    T ret = 0;
    if (numData_ > 0)
    {
        bool wasInterruptsEnabled = (pInterruptControl_ == nullptr) ?
                                    false :
                                    pInterruptControl_->areInterruptsEnabled();
        if (protectAccess_) pInterruptControl_->disableInterrupts();
        ret = data_[tailIndex_];
        numData_--;
        tailIndex_ = (tailIndex_ >= size_ - 1) ? 0 : tailIndex_ + 1;
        if (protectAccess_ && wasInterruptsEnabled) pInterruptControl_->enableInterrupts();
    }
    return ret;
}

template <class T>
bool CircularQueue<T>::isEmpty()
{
    return numData_ == 0;
}

template <class T>
uint16_t CircularQueue<T>::length()
{
    return numData_;
}

#endif