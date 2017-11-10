% Chapter 11: Figure 11.30, p. 673
%
%   Step response for the automatic test system
%   with K=240, K1=1, K2=0.35, and K3=0.05.
%
K=240; K1=1; K2=0.35; K3=0.05;
t=[0:0.01:3];
A=[0 1 0;0 -1 1; -K*K1 -K*K2 -(5+K*K3)];
B=[0;0;K]; C=[1 0 0]; D=[0];
[y,x]=step(A,B,C,D,1,t);
plot(t,y),grid
xlabel('time [sec]')
ylabel('y(t)')
