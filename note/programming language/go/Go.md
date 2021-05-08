# Go

[TOC]

## Type

### Primitive Type

### Compound Type

### Function

### Extensive Type



## Control Flow

### Selection Structure

### Cycle Structure



## OOP



## Other

### Error Handling

Go语言的错误处理不太优雅，使用者会写出一堆`if err != nil`的代码，具体示例如下。

```go
// Define error
var ErrorDivideByZero = errors.New("divide by zero")

// Return error instead of throwing exception
func DivideWrapper(x int, y int) (int, error) {
	if y == 0 {
		return 0, ErrorDivideByZero
	}
	return x / y, nil
}

func main() {
	result, err := DivideWrapper(10, 0)
  // Determine error by 'err != nil'
	if err != nil {
		// error handling, eg. print err
		fmt.Println(err)
		return
	}
	// proceed if no error found
	fmt.Println(result)
}
```

### Concurrency

#### Channel: 协程间传递数据

```go
func main() {
	ch := make(chan int)
  // read only:    ch1 := make(<-chan int)
  // write only:   ch2 := make(chan<- int)
	go func() {
		i := <-ch
		fmt.Println(i)
	}()
	ch <- 6
	time.Sleep(time.Second)
}
```

#### WaitGroup: 协程同步

```go
func main() {
	wg := sync.WaitGroup{}
	wg.Add(1)
	go func() {
		defer wg.Done()
		time.Sleep(time.Second)
	}()
	wg.Wait()
}
```

#### Context: 协程间传递上下文信息

```go
func handle(ctx context.Context, duration time.Duration) {
	select {
	case <-ctx.Done():
		fmt.Println("handle", ctx.Err())
	case <-time.After(duration):
		fmt.Println("process request with", duration)
	}
}

func main() {
	ctx, cancelFunc := context.WithTimeout(context.Background(), time.Second)
	defer cancelFunc()

	go handle(ctx, 500*time.Millisecond)
	select {
	case <-ctx.Done():
		fmt.Println("main", ctx.Err())
	}
}
```

#### panic, recover, defer

> **defer**: 延迟执行直到函数结束（参数立即计算+LIFO）
>
> **panic**: 当前协程进入panic状态，执行其函数栈及对应defer，当前协程执行完毕后程序退出
>
> **recover**: 当前协程从panic中恢复

Reference: https://blog.golang.org/defer-panic-and-recover

### Package

一个文件夹只能一个包名

### CGO

```go
/*
#cgo LDFLAGS: -L./build -lpbtest
#include <stdio.h>
void TestFunc();
*/
import "C"
```

上面的声明可以引入C的声明，注意：上面使用的是C编译器，所以不要链接C++的静态库！（例如pbtest不能是静态库）

> C编译器不识别`extern "C"`，所以请加上`__cplusplus`判断是不是C++编译器

#### Release memory in c malloc

```go
var out *C.char = C.FunctionCallMalloc()
defer C.free(unsafe.Pointer(echoOut))
```

defer的可靠性: https://blog.golang.org/defer-panic-and-recover

### &arr VS &arr[0]

GO切片名类似于C的数组，&arr表示数组地址，&arr[0]才是数组第一个元素的地址。

### 传值/传引用
**Go语言传递slice/map/chan是传引用（相当于传递他们的指针），类似于java的对象传递；传递其它类型（包括指针）都是传值。**
