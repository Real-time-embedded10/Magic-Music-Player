% Read features of all samples collected.
forward = table2array(feature2forward);
backward = table2array(feature2backward);
left = table2array(feature2left);
right = table2array(feature2right);
up = table2array(feature2up);
down = table2array(feature2down);
n=1:179;
m=1:180; % Here are a total of 180 samples for each gesture. 

i = 1; % The number of tested feature.
AX1 = forward(m,i)';
AX2 = backward(m,i)';
AX3 = left(m,i)';
AX4 = right(m,i)';
AX5 = up(m,i)';
AX6 = down(m,i)';

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
legend('forward','backward','left','right','up','down')
grid on
