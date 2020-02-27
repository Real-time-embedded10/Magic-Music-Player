gesture=table2array(result);
n=0:600;
m=1160:1760;

AX=gesture(m,1)';
AY=gesture(m,2)';
AZ=gesture(m,3)';
GX=gesture(m,4)';
GY=gesture(m,5)';
GZ=gesture(m,6)';
plot(n,AX(n+1),'r')
hold on
plot(n,AY(n+1),'g')
hold on
plot(n,AZ(n+1),'b')
hold on
plot(n,GX(n+1),'m')
hold on
plot(n,GY(n+1),'c')
hold on
plot(n,GZ(n+1),'k')
hold on
legend('ACCEL_X','ACCEL_Y','ACCEL_Z','GYRO_X','GYRO_Y','GYRO_Z')
grid on
