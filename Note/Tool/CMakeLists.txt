# TIPS: 本文件在cmake3.5.1下运行
CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(cmake_test)

# 添加C和C++编译/链接器选项
ADD_COMPILE_OPTIONS(-std=c++11)
# 添加预处理器宏定义
ADD_DEFINITIONS(-DFOO -DVAR=float)

# 生成可执行文件foo、静态库libfoo1.a、共享库libfoo2.so
ADD_EXECUTABLE(foo main.cpp foo.cpp)
ADD_LIBRARY(foo1 STATIC foo.cpp)
ADD_LIBRARY(foo2 SHARED foo.cpp)

# 添加子文件夹src，该文件夹中也必须含有一个CMakeLists.txt
ADD_SUBDIRECTORY(src)

# 文件操作命令
FILE(WRITE <filename> <content>...)
FILE(APPEND <filename> <content>...)
FILE(READ <filename> <variable>
    [OFFSET <offset>] [LIMIT <max-in>] [HEX])
FILE(<MD5|SHA1|SHA224|SHA256|SHA384|SHA512> <filename> <variable>)
FILE(GLOB <variable>
    [LIST_DIRECTORIES true|false] [RELATIVE <path>]
    [<globbing-expressions>...])
FILE(GLOB_RECURSE <variable> [FOLLOW_SYMLINKS]
    [LIST_DIRECTORIES true|false] [RELATIVE <path>]
    [<globbing-expressions>...])

# 查找库
FIND_LIBRARY(
    <VAR>
    name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
    [HINTS path1 [path2 ... ENV var]]
    [PATHS path1 [path2 ... ENV var]]
    [PATH_SUFFIXES suffix1 [suffix2 ...]]
    [DOC "cache documentation string"]
    [NO_DEFAULT_PATH]
    [NO_CMAKE_ENVIRONMENT_PATH]
    [NO_CMAKE_PATH]
    [NO_SYSTEM_ENVIRONMENT_PATH]
    [NO_CMAKE_SYSTEM_PATH]
    [CMAKE_FIND_ROOT_PATH_BOTH |
        ONLY_CMAKE_FIND_ROOT_PATH |
        NO_CMAKE_FIND_ROOT_PATH]
)

# 查找已有的cmake包，该函数可以通过FIND_LIBRARY和FIND_PATH实现
FIND_PACKAGE(<package> [version] [EXACT] [QUIET] [MODULE]
[REQUIRED] [[COMPONENTS] [components...]]
[OPTIONAL_COMPONENTS components...]
[NO_POLICY_SCOPE]
)

# 查找头文件
FIND_PATH(...)


# 头文件目录
INCLUDE_DIRECTORIES(
    include
    ${OPENCV_INCLUDE_DIRECTORIES}
)

# 安装文件
INSTALL(...)

# 库文件目录
LINK_DIRECTORIES(...)

# 直接链接
LINK_LIBRARIES(/opt/libfoo.a)

# 从一个文件/模块中加载cmake代码
INCLUDE(mudules/pre.cmake)

# cmake选项
OPTION(<option_variable> "help string describing option"
    [initial value])

# 设置变量
SET(<variable> <value>...)
SET(ENV{<variable>} <value>...)


#------------ target ----------------
# 指定target的预处理选项
TARGET_COMPILE_DEFINITIONS(<target>
    <INTERFACE|PUBLIC|PRIVATE> [items1...]
    [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

# 指定target的编译选项
TARGET_COMPILE_OPTIONS(<target> [BEFORE]
    <INTERFACE|PUBLIC|PRIVATE> [items1...]
    [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

# 指定target的头文件目录
TARGET_INCLUDE_DIRECTORIES(<target> [SYSTEM] [BEFORE]
    <INTERFACE|PUBLIC|PRIVATE> [items1...]
    [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

# 指定target的链接库
TARGET_LINK_LIBRARIES(atarget comm1 libcomm2.a libcomm3.so -lcomm4)
