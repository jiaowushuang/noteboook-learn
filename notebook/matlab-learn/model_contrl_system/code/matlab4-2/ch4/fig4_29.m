% Chapter 4: Figure 4.29, p. 205
%
%   English channel boring machine: step response 
%   for K=100 and K=20.
%
numg=[1]; deng=[1 1 0]; 
K1=100; K2=20; 
num1=[11 K1]; num2=[11 K2]; den=[0 1];
%
% Compute closed-loop transfer functions
%
[na,da]=series(num1,den,numg,deng); [nb,db]=series(num2,den,numg,deng);
[numa,dena]=cloop(na,da); [numb,denb]=cloop(nb,db);
%
% Plot step response
%
t=[0:0.01:2.0];
[y1,x,t]=step(numa,dena,t); [y2,x,t]=step(numb,denb,t);
subplot(211), plot(t,y1), title('Step Response for K=100')
xlabel('time [sec]'),ylabel('y(t)'), grid
subplot(212),plot(t,y2), title('Step Response for K=20')
xlabel('time [sec]'),ylabel('y(t)'), grid

