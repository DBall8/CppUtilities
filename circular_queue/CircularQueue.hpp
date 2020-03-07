#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include <stdint.h>
#include <Arduino.h>

template <class T>
class CircularQueue
{
    public:
        CircularQueue(T* array, uint8_t size, bool protectAccess);
        ~CircularQueue();

        void push(T data);
        T pop();
        bool isEmpty();
    private:
        T* data_;
        uint8_t headIndex_;
        uint8_t tailIndex_;
        uint8_t size_;
        uint8_t numData_;
        bool protectAccess_;
};

template <class T>
CircularQueue<T>::CircularQueue(T* array, uint8_t size, bool protectAccess):
                             data_(array),
                             size_(size),
                             protectAccess_(protectAccess)
{
    headIndex_ = 0;
    tailIndex_ = 0;
    numData_ = 0;
}

template <class T>
CircularQueue<T>::~CircularQueue(){}

template <class T>
void CircularQueue<T>::push(T data)
{
    if (protectAccess_) noInterrupts();
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
    if (protectAccess_) interrupts();
}

template <class T>
T CircularQueue<T>::pop()
{
    T ret = 0;
    if (numData_ > 0)
    {
        if (protectAccess_) noInterrupts();
        ret = data_[tailIndex_];
        numData_--;
        tailIndex_ = (tailIndex_ >= size_ - 1) ? 0 : tailIndex_ + 1;
        if (protectAccess_) interrupts();
    }
    return ret;
}

template <class T>
bool CircularQueue<T>::isEmpty()
{
    return numData_ == 0;
}

#endif