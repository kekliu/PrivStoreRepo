

# rsync

[toc]

## Configure

### Server

```bash
sed -i 's/RSYNC_ENABLE=.*/RSYNC_ENABLE=true/' /etc/default/rsync
cp /usr/share/doc/rsync/examples/rsyncd.conf /etc
cat << EOF >> /etc/rsyncd.conf
[customservice]
        comment = public archive
        path = /opt/data
        use chroot = yes
#       max connections=10
        lock file = /var/lock/rsyncd
# the default for read only is yes...
        read only = no
        list = yes
        uid = root
        gid = root
#       exclude = 
#       exclude from = 
#       include =
#       include from =
        auth users = whu
        secrets file = /etc/rsyncd.secrets
        strict modes = yes
#       hosts allow =
#       hosts deny =
        ignore errors = no
        ignore nonreadable = yes
        transfer logging = no
#       log format = %t: host %h (%a) %o %f (%l bytes). Total %b bytes.
        timeout = 600
        refuse options = checksum dry-run
        dont compress = *.gz *.tgz *.zip *.z *.rpm *.deb *.iso *.bz2 *.tbz
EOF
echo $HOME:password >> /etc/rsyncd.secrets
chmod 0600 /etc/rsyncd.secrets
service rsync restart
#echo '/usr/bin/rsync --daemon' >> /etc/rc.local
```

主要更改了 path, read only, uid, gid, auth users, secrets file 选项。

### Client

You need to configure nothing on client, just use it.

## Usage

```
Local:  rsync [OPTION...] SRC... [DEST]

Access via remote shell:
    Pull: rsync [OPTION...] [USER@]HOST:SRC... [DEST]
    Push: rsync [OPTION...] SRC... [USER@]HOST:DEST

Access via rsync daemon:
    Pull: rsync [OPTION...] [USER@]HOST::SRC... [DEST]
        rsync [OPTION...] rsync://[USER@]HOST[:PORT]/SRC... [DEST]
    Push: rsync [OPTION...] SRC... [USER@]HOST::DEST
        rsync [OPTION...] SRC... rsync://[USER@]HOST[:PORT]/DEST

Usages with just one SRC arg and no DEST arg will list the source files instead of copying.

Example:
rsync -av --delete /opt/src/ username@192.168.1.144:/opt/dst
rsync -av --delete /opt/src/ aka@192.168.1.144::AlphaStar
```

