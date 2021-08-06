## Turn of swap

```bash
dd if=/dev/zero of=/swapfile bs=16M
chmod 600 /swapfile
mkswap /swapfile
echo "/swapfile swap swap defaults 0 0" >> /etc/fstab
swapon -a
```

## Enable fstab without restart
mount -a
