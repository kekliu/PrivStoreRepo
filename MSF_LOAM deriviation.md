# 紧耦合定位

## 目标函数

待估计量含k时刻imu位置、速度、姿态、imu零偏、传感器外参：

$X=[x_0,x_1,...,x_c^b], x_k=[p_{b_k}^w,v_{b_k}^w,q_{b_k}^w,b_a,b_g],x_l^b=[p_l^b,q_l^b]$

目标函数：

$min\left\{\Sigma||r_b(\hat{z}^{b_k}_{b_{k+1}},X)||^2+\Sigma||r_m(M,X)||^2\right\}$

两部分分别为imu误差项和lidar误差项。

## IMU误差项

![Screen Shot 2021-01-28 at 16.21.49](/Users/liukeke1/Desktop/Screen Shot 2021-01-28 at 16.21.49.png)

## LIDAR误差项



？？

$\frac{\partial f(x)}{\partial x}=\lim_{\delta x \to 0} \frac{f(x+\delta x)-f(x)}{\delta x}$







$y=f(x)$

$\delta y=f(x+\delta x)-f(x)=f'(x)\delta x=J\delta x$

$D(y)=JD(x)J^T$

??? 



## 微分几何初步

曲面实质上是一种映射：$f:(u,v)\rightarrow (x,y,z)$，在曲面上点P的邻域内，存在切映射$T_p(S)$（或者称为切平面），切映射是一个雅克比矩阵：

$J_f=\frac{\partial(x,y,z)}{\partial(u,v)}=[...]_{3\times2}=[f_u,f_v]$

设在 P 点的邻域内，$(u,v)$发生微小变化，则：

$f(u+\Delta u,v+\Delta v)=f(u,v)+J_f[\Delta u,\Delta v]^T$

对雅克比矩阵作奇异值分解：

$J_f=U\Sigma V^T$

直观地说，$U$是二维圆旋转，$\Sigma$是旋转后的圆在两个垂直方向上伸缩成椭圆，$V$是椭圆映射到曲面的切平面上。

