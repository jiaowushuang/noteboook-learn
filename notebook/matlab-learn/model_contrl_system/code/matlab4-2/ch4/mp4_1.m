% Chapter 4: Feedback Control System Characteristics
% MP4.1, p. 227
%
num=[5]; den=[1 2 25];
axis([0 6 0 1]);
t=[0:0.1:6];
step(num,den,t) 
