% Chapter 4: Figure 4.27, p. 203
%
%   Analysis of the open-loop speed control system.
%
Ra=1; Km=10; J=2; f=0.5; Kb=0.1;
num1=[1]; den1=[J,f];
num2=[Km*Kb/Ra]; den2=[1];
[num,den]=feedback(num1,den1,num2,den2);
%
% Change sign of transfer function since 
% disturbance has negative sign in the block diagram
%
num=-num;
printsys(num,den)
%
% Compute time response to a unit step disturbance   
%
[yo,x,t]=step(num,den);
plot(t,yo)
title('Open-loop Disturbance Step Response')
xlabel('time [sec]')
ylabel('speed')
grid
%
% Steady-state error -> last value of output yo   
%
yo(length(t))
