# Services provided by docker

## Database

### mysql
```bash
# After about 20s, you can use `mysql -e` to exec sql commands
docker run --restart always -p 3306:3306 -d --name mysql -e MYSQL_ROOT_PASSWORD=password mysql:8.0
```
#### utf-8 support

Open /etc/mysql/my.cnf, add the following to '[mysqld]' to enable utf-8 support:
default-character-set = utf8
character_set_server = utf8

### redis

```bash
docker run --restart always -d --name redis -p 6379:6379 redis:6.2
```
#### MongoDB

```bash
docker run -itd --name mongo -p 27017:27017 mongo:4.4
```

#### nginx
##### file server
```bash
docker run -p 10080:10080 -v $HOME/.data:/dataDir --restart always -itd --name nginx nginx:1.19 bash
docker exec -it nginx bash
cat << EOF > /etc/nginx/conf.d/file_server.conf                              
server {
  listen 10080;
  server_name localhost;
  root /dataDir;
  location / {
    autoindex on;
    autoindex_exact_size on;
    autoindex_localtime on;
  }
}
EOF
nginx -t
service nginx restart
```

## Development

### gerrit

[https://hub.docker.com/r/gerritcodereview/gerrit](https://hub.docker.com/r/gerritcodereview/gerrit)


