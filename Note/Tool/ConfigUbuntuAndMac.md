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
### Kernel
```conf
vm.overcommit_memory=2
vm.overcommit_ratio=95
vm.oom_kill_allocating_task=1
```


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


## Cuda support
### Install nvidia-driver
Install nvidia driver by command:
```shell
sudo apt install nvidia-driver-450
```
If after installing nvidia drivers, ubuntu boots to black screen or login screen that freezes. Please change `/etc/default/grub` with adding the following line:
```conf
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash nvidia-drm.modeset=1"
```
If black screen exists still, please use `nvidia-bug-report.sh` to report bug on https://forums.developer.nvidia.com/.


# Mac
## brew
> recommends: vim tig

### clean
```bash
brew bundle dump
# edit Brewfile
brew bundle --force cleanup
```
