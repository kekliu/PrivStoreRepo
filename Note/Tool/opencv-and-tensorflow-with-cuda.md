# CUDA + cuDNN
## 下载
从 [cuda-tookit](https://developer.nvidia.com/cuda-toolkit-archive) 选择相应版本的cuda安装包，例如，对于cuda9.2，我们选择“Linux - x86_64 - Ubuntu - 16.04 - runfile(local)”进行下载。  
进入 [cuDNN](https://developer.nvidia.com/cudnn)，注册并登录，选择和你的CUDA版本相对应的cuDNN，例如我们选择“cuDNN v7.3.1 Library for Linux”。
## 安装
### 禁用系统默认驱动
```bash
sudo vim /etc/modprobe.d/blacklist-nouveau.conf
blacklist nouveau
options nouveau modeset=0
```
### 停止界面服务
重启，按 ctrl+alt+f1 进入字符界面，使用 sudo service lightdm stop 关闭图形界面服务。
### 卸载旧版本（可选）
```bash
sudo /usr/local/cuda-X.Y/bin/uninstall_cuda_X.Y.pl
sudo /usr/bin/nvidia-uninstall
```
### 安装
```bash
# 注意：除了提示是否安装OpenGL选择no，其它全部选择yes
sudo sh cuda_9.2.148_396.37_linux.run
# 添加环境变量，否则重启将在登录界面无限循环
cat << EOF | sudo tee -a /etc/profile
export PATH=/usr/local/cuda/bin:${PATH}
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:${LD_LIBRARY_PATH}
EOF
# 解压cuDNN压缩包，进入文件夹
sudo cp include/cudnn.h /usr/local/cuda/include
sudo cp lib64/libcudnn* /usr/local/cuda/lib64
sudo chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*
# 重启，完成安装
sudo reboot
```

# Python with TensorFlow-GPU
## 使用conda环境
从 [Tsinghua Mirror](https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/)下载Anaconda安装包并安装，然后创建conda环境并安装GPU版的tensorflow：
```bash
# 运行成功后，你已经可以使用tensorflow-gpu
conda create -n py3-tensorflow-gpu tensorflow-gpu
```

# OpenCV
```bash
# 加载上面的conda环境，为编译python版本的opencv做准备
source activate py3-tensorflow-gpu
# 后面三行OFF选项是为了方便测试，使用时请去掉以获得更多的功能
PATH_TO_CONDA_ENV=/home/whu/Documents/opt/anaconda3/envs/py3-tensorflow-gpu
PATH_TO_INSTALL_DIR=/opt/AlphaStar/buildANDinstall/install
cmake \
-DBUILD_opencv_python3=ON \
-DBUILD_opencv_python2=OFF \
-DPYTHON3_EXCUTABLE=${PATH_TO_CONDA_ENV}/bin/python3 \
-DPYTHON3_INCLUDE_DIR=${PATH_TO_CONDA_ENV}/include/python3.6m \
-DPYTHON3_LIBRARY=${PATH_TO_CONDA_ENV}/lib/libpython3.6m.so \
-DPYTHON_NUMPY_PATH=${PATH_TO_CONDA_ENV}/lib/python3.6/site-packages \
\
-DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-3.4.3/modules \
-DOPENCV_ENABLE_NONFREE=ON \
\
-DBUILD_opencv_world=ON \
-DBUILD_opencv_dnn=OFF \
-DWITH_CUDA=ON \
-DCMAKE_INSTALL_PREFIX=${PATH_TO_INSTALL_DIR} \
-G Ninja \
../opencv-3.4.3
# 如果下载较慢，可以先关闭下面的选项进行测试
-DWITH_IPP=OFF \
-DBUILD_opencv_face=OFF \
-DBUILD_opencv_xfeatures2d=OFF
# 创建软链接
ln -s ${PATH_TO_INSTALL_DIR}/lib/python3.6/site-packages/cv2.cpython-36m-x86_64-linux-gnu.so ${PATH_TO_CONDA_ENV}/lib/python3.6/site-packages/cv2.so
```

# 最后的效果
在上面创建的conda环境中，你既可以使用cuda版的tensorflow，又可以使用python版的opencv；opencv的C++版本不但有cuda加速，还有opencv_contrib的所有额外功能。
