#include <pthread.h>
#include <exception>
#include <stdexcept>
#include <iostream>

#ifndef THREAD_H
#define THREAD_H

//http://peter.bourgon.org/blog/2010/10/27/who-needs-boost-a-simple-pthreads-wrapper.html
static void * threadbase_dispatcher(void *arg);

class Thread
{
public:

    Thread() : m_threadbase_ptr(NULL) { }
    virtual ~Thread() { }

    void start()
    {
        if (m_threadbase_ptr == NULL) {
            m_threadbase_ptr = new pthread_t;
            int rc = pthread_create(m_threadbase_ptr, NULL, threadbase_dispatcher, this);
            if (rc != 0) {
                throw std::runtime_error("threadbase pthread_create failed");
            }
        } else {
            throw std::runtime_error("multiple threadbase start");
        }
    }

    void join()
    {
        if (m_threadbase_ptr) {
            int rc = pthread_join(*m_threadbase_ptr, NULL);
            if (rc != 0) {
                throw std::runtime_error("threadbase pthread_join failed");
            }
            delete m_threadbase_ptr;
            m_threadbase_ptr = NULL;
        }
    }

    virtual void run() = 0;
    /*void run()
    {
        std::cout << "hello" << std::endl;
    }*/

protected:
private:
    pthread_t *m_threadbase_ptr;
};


static void * threadbase_dispatcher(void *arg)
{
    Thread * tb(static_cast<Thread *>(arg));
    tb->run();
    return NULL;
}



#endif // THREAD_H
