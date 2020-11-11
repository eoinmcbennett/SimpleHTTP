//
// Created by Eoin on 26/10/2020.
//

#ifndef SERVERTEST_QUEUE_H
#define SERVERTEST_QUEUE_H

#include <mutex>
#include <cstring>

#define size_t unsigned int
#define SIZEOF_T sizeof(T)

#define GROWTH_AMOUNT 10

/**
 * A thread safe implementation of a queue data structure
 * @tparam T
 */
template<typename T> class Queue {
private:
    std::mutex mutex;
    T* m_data;
    size_t m_noOfElements;
    size_t m_curSize; //The size of m_data in bytes

public:
    Queue(){
        this->m_data = new T[GROWTH_AMOUNT];
        this->m_curSize = GROWTH_AMOUNT * SIZEOF_T;
        this->m_noOfElements = 0;
    }

    Queue(unsigned int initialSize){
        this->m_data = new T[initialSize];
        this->m_curSize = initialSize * SIZEOF_T;
        this->m_noOfElements = 0;
    }

    Queue(const Queue<T>& other){
        size_t otherArrSize = other.m_curSize / SIZEOF_T;
        this->m_data = new T[otherArrSize];
        this->m_curSize = other.m_curSize;
        this->m_noOfElements = other.m_noOfElements;
    }

    ~Queue(){
        delete[] m_data;
        m_noOfElements = 0;
        m_curSize = 0;
    }

    void enqueueData(const T& data){
        mutex.lock();
        if(this->m_noOfElements == (this->m_curSize / SIZEOF_T)){
            incSize(GROWTH_AMOUNT);
        }
        this->m_data[m_noOfElements] = data;
        m_noOfElements++;
        mutex.unlock();
    }

    T dequeue(){
        if(!isEmpty()){
            mutex.lock();
            if(this->m_noOfElements < ((this->m_curSize / SIZEOF_T) - GROWTH_AMOUNT)){
                decSize(GROWTH_AMOUNT);
            }
            T data = this->m_data[0];
            shiftQueue();
            m_noOfElements--;
            mutex.unlock();
            return data;
        }
    }

    T peek(){
        mutex.lock();
        T data = this->m_data[0];
        mutex.unlock();
        return data;
    }

    size_t getSize() const {
        return this->m_noOfElements;
    }

    bool isEmpty(){
        return m_noOfElements == 0;
    }

private:

    /**
     * Increments the size of the queue by the param amount
     * @param amount
     */
    void incSize(size_t amount){
        size_t newSize = amount + (this->m_curSize / SIZEOF_T);
        T* newArr = new T[newSize];
        if(newArr){
            memset(newArr,0,newSize * SIZEOF_T);
            memcpy(newArr,this->m_data, newSize * SIZEOF_T);
        }
        delete[] this->m_data;
        this->m_data = newArr;
        this->m_curSize = newSize * SIZEOF_T;
    }

    /**
     * Decrements the size of the queue by the specified amount
     * Will not decrease if computed new size is 0
     * @param amount
     */
    void decSize(size_t amount){
        size_t newSize = (this->m_curSize / SIZEOF_T) - amount;
        if(newSize > 0){
            T* newArr = new T[newSize];
            if(newArr){
                memset(newArr,0, newSize * SIZEOF_T);
                memcpy(newArr,this->m_data, newSize * SIZEOF_T);
            }
            delete[] this->m_data;
            this->m_data = newArr;
            this->m_curSize = newSize * SIZEOF_T;
        }
    }

    void shiftQueue(){
        if(!isEmpty()){
            for(int i = 1; i < this->m_noOfElements; i++){
                this->m_data[i - 1] = this->m_data[i];
            }
            this->m_data[this->m_noOfElements - 1] = 0;
        }
    }
};

#undef SIZEOF_T
#undef size_t

#endif //SERVERTEST_QUEUE_H
