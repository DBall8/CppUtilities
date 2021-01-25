/**
 * Class for creating a circular queue object
 * Pushing new entries when the queue is full WILL overwrite the oldest entry
 */
#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include "drivers/interrupt/IInterrupt.hpp"
#include "drivers/assert/Assert.hpp"
#include <stdint.h>

template <class T>
class CircularQueue
{
    public:
        /**
         * Constructor
         * @param   array   Pointer to allocated array for data storage
         * @param   size    The size of the array given, in units of type T
         * @param   protectAcces        If true, interrupts will be disabled before each access that modifies the queue
         * @param   pInterruptControl   Object to allow for the enabling/disabling of interrupts
         */
        CircularQueue(T* array,
                      uint16_t size,
                      bool protectAccess = false,
                      Interrupt::IInterrupt* pInterruptControl = nullptr);
        ~CircularQueue();

        /**
         * Add a value to the end of the queue
         * @param   data    Value to add
         */
        void push(T data);

        /**
         * Get the value at the start of the queue, and remove it from the queue
         * @return  The value at the start of the queue
         */
        T pop();

        /**
         * Get the number of elements currently in the queue, cannot increase past the input size
         * @return  Number of entries in the queue
         */
        uint16_t length();

        /**
         * Max size of the queue, in units of type T
         * @return  Maximum size of the queue
         */
        uint16_t size();

        /**
         * Is the queue empty
         * @return  True if there are no values in the queue
         */
        bool isEmpty();

        /**
         * Is the queue fulle
         * @return  True if there are 'size' entries in the queue
         */
        bool isFull();

        /**
         * Empty the contents of the queue and reset to initial conditions
         */
        void flush();
    private:
        T* data_;               // Array where values are stored
        uint16_t headIndex_;    // Index at which the next value will be pushed to
        uint16_t tailIndex_;    // Index at which the next value will be popped form
        uint16_t size_;         // Maximum size of the queue
        uint16_t numData_;      // Number of elements currently in the queue
        bool protectAccess_;    // True if interrupts should be disabled before modifying the queue
        Interrupt::IInterrupt* pInterruptControl_;  // Object for enabling/disabling interrupts
};

template <class T>
CircularQueue<T>::CircularQueue(T* array,
                                uint16_t size,
                                bool protectAccess,
                                Interrupt::IInterrupt* pInterruptControl):
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
    if (protectAccess_) pInterruptControl_->pauseInterrupts();
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
    if (protectAccess_) pInterruptControl_->resumeInterrupts();
}

template <class T>
T CircularQueue<T>::pop()
{
    T ret = 0;
    if (numData_ > 0)
    {
        if (protectAccess_) pInterruptControl_->pauseInterrupts();
        ret = data_[tailIndex_];
        numData_--;
        tailIndex_ = (tailIndex_ >= size_ - 1) ? 0 : tailIndex_ + 1;
        if (protectAccess_) pInterruptControl_->resumeInterrupts();
    }
    return ret;
}

template <class T>
bool CircularQueue<T>::isEmpty()
{
    return numData_ == 0;
}

template <class T>
bool CircularQueue<T>::isFull()
{
    return numData_ >= size_;
}

template <class T>
uint16_t CircularQueue<T>::length()
{
    return numData_;
}

template <class T>
uint16_t CircularQueue<T>::size()
{
    return size_;
}

template <class T>
void CircularQueue<T>::flush()
{
    headIndex_ = 0;
    tailIndex_ = 0;
    numData_ = 0;
}


#endif