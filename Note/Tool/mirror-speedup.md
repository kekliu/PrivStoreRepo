# apt-get
Choose tsinghua / cqu / aliyun

# maven
## Single project only
Add the following to pom.xml:
```xml
<repositories>
    <repository>
        <id>aliyun</id>
        <name>aliyun maven</name>
        <url>http://maven.aliyun.com/nexus/content/groups/public</url>
    </repository>
</repositories>
```
## Global
Modify settings.xml, e.g. /opt/idea-IC-182.4323.46/plugins/maven/lib/maven3/conf/settings.xml,
find tag "mirrors", add the following:
```xml
<mirror>
    <id>alimaven</id>
    <name>aliyun maven</name>
    <url>http://maven.aliyun.com/nexus/content/groups/public</url>
    <mirrorOf>central</mirrorOf>
</mirror>
```

# docker
docker-cn / aliyun

# python
## conda
tsinghua
## pip
tsinghua

# ROS
```bash
sudo sh -c '. /etc/lsb-release && echo "deb http://mirrors.tuna.tsinghua.edu.cn/ros/ubuntu/ $DISTRIB_CODENAME main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt update && sudo apt install ros-kinetic-desktop
```

# others
## tsinghua mirror support
### package
apache, docker-ce, gnu, jenkins, lineageOS
### mirror
centos, cygwin, debian, fedora
