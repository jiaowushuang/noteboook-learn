% Chapter 4: Figure 4.30, p. 206
%
% Response to a Disturbance D(s)=1/s for K=20 and K=100
%
numg=[1]; deng=[1 1 0]; 
K1=100; K2=20; 
num1=[11 K1]; num2=[11 K2]; den=[0 1];
%
% Compute closed-loop transfer functions
%
[numa,dena]=feedback(numg,deng,num1,den); 
[numb,denb]=feedback(numg,deng,num2,den);
%
% Plot step response
%
t=[0:0.01:2.5];
[y1,x,t]=step(numa,dena,t); [y2,x,t]=step(numb,denb,t);
subplot(211), plot(t,y1), title('Disturbance Response for K=100')
xlabel('time [sec]'),ylabel('y(t)'), grid
subplot(212),plot(t,y2), title('Disturbance Response for K=20')
xlabel('time [sec]'),ylabel('y(t)'), grid

