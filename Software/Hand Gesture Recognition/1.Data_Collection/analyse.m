gesture=table2array(resultup1);
n=0:600;
m=1160:1760;

AX1=gesture(m,1)';
AX2=gesture(m,2)';
AX3=gesture(m,3)';
AX4=gesture(m,4)';
AX5=gesture(m,5)';
AX6=gesture(m,6)';
plot(n,AX1(n+1),'r')
hold on
plot(n,AX2(n+1),'g')
hold on
plot(n,AX3(n+1),'b')
hold on
plot(n,AX4(n+1),'m')
hold on
plot(n,AX5(n+1),'c')
hold on
plot(n,AX6(n+1),'k')
hold on
legend('ACCEL_X','ACCEL_Y','ACCEL_Z','GYRO_X','GYRO_Y','GYRO_Z')
grid on