# MySQL in Docker
```
docker run --restart always -p 3306:3306 -d --name mysql -e MYSQL_ROOT_PASSWORD=password mysql:5.7
```

## utf-8 support
Open /etc/mysql/my.cnf, add the following to '[mysqld]' to enable utf-8 support:
default-character-set = utf8
character_set_server = utf8

