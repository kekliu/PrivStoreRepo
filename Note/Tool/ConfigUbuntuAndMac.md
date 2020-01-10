# Ubuntu
## Install
### Install Ubuntu
Configure storage drive to make your SSD store all directories except for `/home`.

### Update softwares
```bash
sudo apt-get update
sudo apt-get install chromium-browser
sudo apt-get purge firefox libreoffice*
sudo apt-get upgrade -y
reboot
```

### Mount /tmp on tmpfs
```bash
sudo cp /usr/share/systemd/tmp.mount /etc/systemd/system
sudo systemctl enable tmp.mount
```

### Time sync
```bash
# Update time through network
sudo apt-get install ntpdate -y
sudo ntpdate time.windows.com
# Write time into hardware
sudo hwclock --localtime --systohc
```


## Configuration
### oh-my-zsh
> sh -c "$(wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"

Then configure 'plugins=(git sudo docker autojump command-not-found)' in .zshrc.

## Softwares
### Ubuntu official repositories
apt-file  
axel  
build-essential  
ccache  
clang-9  
cmake  
iotop  
ibus-libpinyin  
ninja-build  
synaptic  
tig  
tmux  
### Third Party
vscode  
qv2ray  
nvidia-driver  
IntelliJ IDEA


# Mac
## brew
> recommends: vim tig

### clean
```bash
brew bundle dump
# edit Brewfile
brew bundle --force cleanup
```
