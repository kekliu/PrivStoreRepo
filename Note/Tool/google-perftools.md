# 安装
```bash
# 安装依赖
sudo apt install libunwind-dev
# 编译安装
gcl https://github.com/gperftools/gperftools
cd gperftools
./autogen.sh
./configure --prefix=/opt/AlphaStar/buildANDinstall/install
make -j6 install
```

# 使用
在c++代码中添加
```cpp
#include <gperftools/profiler.h>

ProfilerStart("name");
ProfilerStop();
```
编译时使用
```bash
gcc -o myapp ... -lprofiler -ltcmalloc
# OR
gcc -o myapp ... /opt/AlphaStar/buildANDinstall/install/lib/libtcmalloc_and_profiler.a
```



# 其它

export LD_PRELOAD=/usr/lib/libtcmalloc_and_profiler.so.4
CPUPROFILE=/tmp/cpu-perf.out /bin/ls -a
google-pprof --pdf /bin/ls /tmp/cpu-perf.out > a.pdf


export LD_PRELOAD=/usr/lib/libtcmalloc_and_profiler.so.4
HEAPPROFILE=/tmp/heap-perf.out /bin/ls -a
google-pprof --text /bin/ls /tmp/heap-perf.out.0001.heap
google-pprof --pdf /bin/ls /tmp/heap-perf.out.0001.heap > a.pdf
