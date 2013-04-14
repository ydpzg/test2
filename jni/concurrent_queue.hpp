//
//  concurrent_queue.hpp
//  AnotherSocketClient
//
//  Created by Genesislive on 1/30/13.
//  Copyright (c) 2013 Genesislive. All rights reserved.
//

#ifndef AnotherSocketClient_concurrent_queue_hpp
#define AnotherSocketClient_concurrent_queue_hpp

#include "iostream"
#include <queue>
#include <pthread.h>

template <typename T>
class concurrent_queue {
private:
    std::queue<T>   container;
    pthread_mutex_t mutex;
    pthread_cond_t  not_empty_cond;
    
public:
    concurrent_queue();
    ~concurrent_queue();
    
    void push(T item);
    bool pop(T &item);
    void wait_and_pop(T &item);
    bool empty();
};


template <typename T>
concurrent_queue<T>::concurrent_queue()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty_cond, NULL);
}

template <typename T>
concurrent_queue<T>::~concurrent_queue()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty_cond);
}

template <typename T>
void concurrent_queue<T>::push(T item)
{
    pthread_mutex_lock(&mutex);
    container.push(item);
    pthread_mutex_unlock(&mutex);
}

template <typename T>
bool concurrent_queue<T>::pop(T &item)
{
    pthread_mutex_lock(&mutex);
    
    if (container.empty()) {
        return false;
    }
    
    item = container.front();
    container.pop();
    
    pthread_mutex_unlock(&mutex);
    return true;
}

template <typename T>
void concurrent_queue<T>::wait_and_pop(T &item)
{
    pthread_mutex_lock(&mutex);
    
    if (container.empty()) {
        pthread_cond_wait(&not_empty_cond, &mutex);
    }
    
    item = container.front();
    container.pop();
    
    pthread_mutex_unlock(&mutex);
}

template <typename T>
bool concurrent_queue<T>::empty()
{
    pthread_mutex_lock(&mutex);
    bool flag = container.empty();
    pthread_mutex_unlock(&mutex);
    return flag;
}

#endif
