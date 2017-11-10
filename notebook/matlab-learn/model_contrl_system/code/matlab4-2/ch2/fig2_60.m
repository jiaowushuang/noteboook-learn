% Chapter 2: Figure 2.60, p. 93
%   Step response of the traction motor wheel velocity.
%
num=[5400]; den=[2 2.5 5402];
t=[0:0.005:3];
[y,x,t]=step(num,den,t);
plot(t,y),grid
xlabel('Time [sec]')
ylabel('Wheel velocity')
