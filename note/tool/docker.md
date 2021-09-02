# Services provided by docker
[toc]


### mysql
```bash
# After about 20s, you can use `mysql -e` to exec sql commands
docker run --restart always -p 3306:3306 -d --name mysql -e MYSQL_ROOT_PASSWORD=password mysql:8.0
```
Open /etc/mysql/my.cnf, add the following to '[mysqld]' to enable **utf-8 support**:
```
default-character-set = utf8
character_set_server = utf8
```

### redis

```bash
docker run --restart always -d --name redis -p 6379:6379 redis:6.2
```
### mongodb

```bash
docker run -itd --name mongo -p 27017:27017 mongo:4.4
```

### nginx as a file server
```bash
docker run -p 20080:20080 -v $(pwd):/data-dir --restart always -itd --name nginx nginx:1.21
docker exec -i nginx bash -s << EOF
cat << EOF_INTERNAL > /etc/nginx/conf.d/file_server.conf
server {
  listen 20080;
  server_name localhost;
  root /data-dir;
  location / {
    autoindex on;
    autoindex_exact_size on;
    autoindex_localtime on;
  }
}
EOF_INTERNAL
EOF
docker restart nginx
```

### gerrit
[https://hub.docker.com/r/gerritcodereview/gerrit](https://hub.docker.com/r/gerritcodereview/gerrit)
