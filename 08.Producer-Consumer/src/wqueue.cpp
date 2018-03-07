#include "wqueue.h"
/*
template <typename T>
wqueue<T>::wqueue()
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_condv, NULL);
}

template <typename T>
wqueue<T>::~wqueue()
{
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_condv);
}

template <typename T>
void wqueue<T>::add(T item) {
    pthread_mutex_lock(&m_mutex);
    m_queue.push_back(item);
    pthread_cond_signal(&m_condv);
    pthread_mutex_unlock(&m_mutex);
}

template <typename T>
T wqueue<T>::remove() {
    pthread_mutex_lock(&m_mutex);
    while (m_queue.size() == 0) {
        pthread_cond_wait(&m_condv, &m_mutex);
    }
    T item = m_queue.front();
    m_queue.pop_front();
    pthread_mutex_unlock(&m_mutex);

    return item;
}

template <typename T>
int wqueue<T>::size() {
    pthread_mutex_lock(&m_mutex);
    int size = m_queue.size();
    pthread_mutex_unlock(&m_mutex);

    return size;
}
*/
