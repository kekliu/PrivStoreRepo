%卡尔曼滤波实例
%测量房间温度，房间温度真实值为T=25度，一共测量两百个点
N=200;  T=25;  size=[N,1]; 
%取温度预测值的方差为Q=1e-3,温度传感器的测量方差为R=0.36，即我们更相信预测值，而较少相信传感器测量值。
Q=1e-3;  R=0.36;  T_mearsured=T+sqrt(R)*randn(size);
%初始时刻温度的最优估计值为T_start=22.5度,温度初始估计方差为P_start=2
T_start=22.5;  P_start=2;
T_kalman(1)=T_start;  P_kalman(1)=P_start;
%用_kalman的后缀表示最优估计值，用_pre的后缀表示预测值
for k=2:N
%在进行温度预测时，因为温度是一个连续的状态，我们认为上一时刻的温度和当前时刻的温度相等，则有T(k)=T(k-1)。
T_pre(k)=T_kalman(k-1);
P_pre(k)=P_kalman(k-1)+Q;
K(k)=P_pre(k)/(P_pre(k)+R);
T_kalman(k)=T_pre(k)+K(k)*(T_mearsured(k)-T_pre(k));
P_kalman(k)=P_pre(k)-K(k)*P_pre(k);
end
%画图
figure();
plot(T*ones(size),'g');
hold on
plot(T_mearsured,'b');
hold on
plot(T_kalman,'r');
legend('温度真实值','温度测量值','Kalman估计值')