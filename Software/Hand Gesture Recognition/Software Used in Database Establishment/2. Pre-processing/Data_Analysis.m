gesture = table2array(result);
[row, col] = size(gesture)
n = 1:(row-1);
m = 1:row;

AX = gesture(m,1)';
AY = gesture(m,2)';
AZ = gesture(m,3)';
GX = gesture(m,4)';
GY = gesture(m,5)';
GZ = gesture(m,6)';
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
