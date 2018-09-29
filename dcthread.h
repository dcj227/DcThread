#ifndef __DC_THREAD_H__
#define __DC_THREAD_H__
#include <errno.h>
#include <pthread.h>

class DcThread {
public:
    static void* ThreadFunc(void* lpVoid) {
        DcThread* pth = static_cast<DcThread*>(lpVoid);
        if(NULL == pth) {
            return NULL;
        }
        pth->Run();
        return NULL;
    }

    explicit DcThread()
            :running_(false) 
            ,thread_id_(-1) {
        pthread_attr_init(&thread_attr_);
    }

    virtual ~DcThread() {
        Stop();
        pthread_attr_destroy(&thread_attr_);
    }

    int Start() {
         
        if (pthread_create(&thread_id_, &thread_attr_, DcThread::ThreadFunc, static_cast<void*>(this)) != 0) {
            return -1;
       }
        running_ = true;
        return 0;
    }

    bool IsRunning() { return running_; }

    int Stop() {
        running_ = false;

        pthread_join(thread_id_, NULL);
    }

protected:
    virtual void Run() = 0;

private:
    pthread_t thread_id_;
    pthread_attr_t thread_attr_;

    bool running_;
};

#endif  // __DC_THREAD_H__
