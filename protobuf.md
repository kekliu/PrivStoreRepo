# ProtoBuf

[toc]

## What is ProtoBuf?

todo

## Install

### Mac

`brew install grpc ` will install protobuf 3.14.0 and grpc 1.15.0 automaticly.

### Ubuntu

Please build from source to use latest protobuf and grpc.

### Build from source

```bash
# Git clone, try use ALL_PROXY=socks5://172.16.1.135:33080 if slow
git clone -b v1.35.0 --depth 1 --recursive https://github.com/grpc/grpc
# Install protobuf and grpc, protobuf refered in grpc/cmake/protobuf.cmake
mkdir grpc/build && cd grpc/build
cmake ..  -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON
make install -j `nproc`
ldconfig
# Clean up
cd ../..
rm -rf grpc
```

## Issues

### Use protoc go plugin

```base
go get google.golang.org/protobuf/cmd/protoc-gen-go google.golang.org/grpc/cmd/protoc-gen-go-grpc
export PATH="$PATH:$(go env GOPATH)/bin"
protoc --go_out=. f.proto
```

### Overloaded error caused by reserve word 

```cpp
./pose-estimater.pb.h:1094:23: error: functions that differ only in their return type cannot be overloaded
  const ::Descriptor& descriptor() const;
        ~~~~~~~~~~~~~ ^
./pose-estimater.pb.h:688:53: note: previous definition is here
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ^
./pose-estimater.pb.h:1805:35: error: return type of out-of-line definition of 'Frame::descriptor' differs from that in the declaration
inline const ::Descriptor& Frame::descriptor() const {
             ~~~~~~~~~~~~~        ^
./pose-estimater.pb.h:688:53: note: previous definition is here
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ^
```

### Convert to reqmessage

```go
int size = reqMsg.ByteSize();
char* array = new char[size];
reqMsg.SerializeToArray(array, size);

std::string bytes = reqMsg.SerializeAsString();
const char* array = bytes.data();
int size = bytes.size();
```

## Tricks

### Compatibility

> Use `optinal` and field 'tag' for forward compatibility.