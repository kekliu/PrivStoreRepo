# pthread 编程指南

## 互斥量

函数：  
pthread_mutex_lock, pthread_mutex_unlock

## 条件变量

函数：  
pthread_cond_wait, pthread_cond_signal, pthread_cond_broadcast  

用法：

```cpp
// thread A:
pthread_mutex_lock(&mutex);
while (!condition)
    pthread_cond_wait(&cond, &mutex);
// do something that requires holding the mutex and condition is true
pthread_mutex_unlock(&mutex);

// thread B:
pthread_mutex_lock(&mutex);
// do something that might make condition true
pthread_cond_signal(&cond);
pthread_mutex_unlock(&mutex);
```

注意：在多处理机系统中，pthread_cond_wait可能存在“伪唤醒”的现象，表现为一个pthread_cond_wait线程可能会随机地被唤醒 (ref:wikipedia)

## 终止

### 终止方式

正常终止

* pthread_exit: 当前线程退出（不是退出进程）
* pthread_cancel: 向线程发送SIGCANCEL，需要与pthread_join结合使用
* pthread_kill: 向线程发送给定信号
* return: 进程退出或非主线程退出
* exit: 进程退出

非正常终止

* 访存错误
* ......

### 安全终止

```cpp
// method 1
pthread_cleanup_push
pthread_cleanup_pop

上面两个需要对应起来使用，在Linux下使用RAII实现

// method 2
自行使用RAII封装mutex
```
