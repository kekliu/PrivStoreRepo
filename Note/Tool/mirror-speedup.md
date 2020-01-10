## apt-get
Choose tsinghua / aliyun mirror.

## maven
### Single project only
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
### Global
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

## docker
docker-ce: https://mirror.tuna.tsinghua.edu.cn/help/docker-ce/  
docker container: aliyun / docker-cn

## python
Conda: https://mirror.tuna.tsinghua.edu.cn/help/anaconda/  
pip: https://mirror.tuna.tsinghua.edu.cn/help/pypi/  

## ROS
https://mirror.tuna.tsinghua.edu.cn/help/ros/
