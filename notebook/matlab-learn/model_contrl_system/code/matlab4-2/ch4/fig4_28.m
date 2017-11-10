% Chapter 4: Figure 4.28, p. 204
%
%   Analysis of the closed-loop speed control system.
%
Ra=1; Km=10; J=2; f=0.5; Kb=0.1; Ka=54; Kt=1;
num1=[1]; den1=[J,f];
num2=[Ka*Kt]; den2=[1];
num3=[Kb]; den3=[1];
num4=[Km/Ra]; den4=[1];
[numa,dena]=parallel(num2,den2,num3,den3);
[numb,denb]=series(numa,dena,num4,den4);
[num,den]=feedback(num1,den1,numb,denb);
%
% Change sign of transfer function since disturbance 
% enters with negative sign in the block diagram
%
num=-num;
printsys(num,den)
%
% Compute time response to a unit step disturbance
%
[yc,x,t]=step(num,den);
plot(t,yc)
title('Closed-loop Disturbance Step Response')
xlabel('time [sec]')
ylabel('speed [rad/sec]')
grid
%
% Steady-state error -> last value of output vector yc
%
yc(length(t))
