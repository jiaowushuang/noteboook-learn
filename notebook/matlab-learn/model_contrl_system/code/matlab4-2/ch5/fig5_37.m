% Chapter 5: Figure 5.37, p. 270
%
%    Compute step response for a second-order system   
%    Duplicate Figure 5.5 (a)
%
t=[0:0.1:12]; num=[1];  
zeta1=0.1; den1=[1 2*zeta1  1]; 
zeta2=0.2; den2=[1 2*zeta2  1];
zeta3=0.4; den3=[1 2*zeta3  1]; 
zeta4=0.7; den4=[1 2*zeta4  1];
zeta5=1.0; den5=[1 2*zeta5  1];
zeta6=2.0; den6=[1 2*zeta6  1];
%
[y1,x,t]=step(num,den1,t); [y2,x,t]=step(num,den2,t);
[y3,x,t]=step(num,den3,t); [y4,x,t]=step(num,den4,t);
[y5,x,t]=step(num,den5,t); [y6,x,t]=step(num,den6,t);
%
plot(t,y1,t,y2,t,y3,t,y4,t,y5,t,y6)
xlabel(' wn*t'), ylabel('y(t)')
title('zeta = 0.1, 0.2, 0.4, 0.7, 1.0, 2.0'), grid
