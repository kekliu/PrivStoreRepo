#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
 public:
  explicit ThreadPool(size_t thread_count)
      : data_(std::make_shared<InternalData>()) {
    // while threads starting, maybe some tasks are being executing
    for (size_t i = 0; i < thread_count; ++i) {
      threads_.emplace_back([data = this->data_] {
        std::unique_lock<std::mutex> lk(data->mtx_);
        for (;;) {
          if (!data->tasks_.empty()) {
            auto current = data->tasks_.front();
            data->tasks_.pop();
            lk.unlock();
            current();
            lk.lock();
          } else if (data->is_shutdown_) {
            break;
          } else {
            data->cond_.wait(lk);
          }
        }
      });
    }
  }

  // forbid to create object on heap
  void* operator new(size_t) = delete;

  ~ThreadPool() {
    {
      std::lock_guard<std::mutex> lk(data_->mtx_);
      data_->is_shutdown_ = true;
      // QQQQQ. notify_one should be placed inside / outside
      data_->cond_.notify_one();
    }
    for (auto& thr : threads_) thr.join();
  }

  template <class F>
  void execute(F&& task) {
    std::lock_guard<std::mutex> lk(data_->mtx_);
    data_->tasks_.emplace(std::forward<F>(task));
    data_->cond_.notify_one();
  }

 private:
  struct InternalData {
    std::mutex mtx_;
    std::condition_variable cond_;
    bool is_shutdown_ = false;
    std::queue<std::function<void()>> tasks_;
  };

  std::shared_ptr<InternalData> data_;
  std::vector<std::thread> threads_;
};

#include <pthread.h>

class MutexLocker {
 public:
  MutexLocker(pthread_mutex_t& mutex) : mutex_(mutex) {
    pthread_mutex_lock(&mutex_);
  }
  void Lock() { pthread_mutex_lock(&mutex_); }
  void UnLock() { pthread_mutex_unlock(&mutex_); }
  ~MutexLocker() { UnLock(); }

 private:
  pthread_mutex_t& mutex_;
};

class NativeThreadPool {
 public:
  explicit NativeThreadPool(size_t thread_count)
      : data_(std::make_shared<InternalData>()) {
    for (size_t i = 0; i < thread_count; ++i) {
      threads_.emplace_back([data = this->data_] {
        MutexLocker lk(data->mtx_);
        for (;;) {
          if (!data->tasks_.empty()) {
            auto current = std::move(data->tasks_.front());
            data->tasks_.pop();
            lk.UnLock();
            current();
            lk.Lock();
          } else if (data->is_shutdown_) {
            break;
          } else {
            pthread_cond_wait(&data->cond_, &data->mtx_);
          }
        }
      });
    }
  }

  ~NativeThreadPool() {
    {
      MutexLocker lk(data_->mtx_);
      data_->is_shutdown_ = true;
      pthread_cond_signal(&data_->cond_);
    }
    // wait until all threads die
    for (auto& thr : threads_) thr.join();
  }

  template <class F>
  void execute(F&& task) {
    MutexLocker lk(data_->mtx_);
    data_->tasks_.emplace(std::forward<F>(task));
    pthread_cond_signal(&data_->cond_);
  }

 private:
  struct InternalData {
    pthread_mutex_t mtx_ = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond_ = PTHREAD_COND_INITIALIZER;
    bool is_shutdown_ = false;
    std::queue<std::function<void()>> tasks_;
  };

  std::shared_ptr<InternalData> data_;
  std::vector<std::thread> threads_;
};

int main() {
  uint32_t core_num = std::thread::hardware_concurrency();
  {
    ThreadPool p(core_num);
    for (int i = 0; i < 10; ++i) {
      p.execute([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
        std::cout << "executing a task in thread " << std::this_thread::get_id()
                  << std::endl;
      });
    }
  }
  std::cout << "THREAD_POOL 1 end" << std::endl;
  {
    NativeThreadPool p(core_num);
    for (int i = 0; i < 10; ++i) {
      p.execute([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 2000));
        std::cout << "executing a task in thread " << std::this_thread::get_id()
                  << std::endl;
      });
    }
  }

  return 0;
}
