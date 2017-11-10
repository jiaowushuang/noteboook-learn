% Chapter 5: Figure 5.38, p. 271
%
%    Compute impulse response for a second-order system  
%    Duplicate Figure 5.6
%
t=[0:0.1:10]; num=[1];  
zeta1=0.1; den1=[1 2*zeta1  1]; 
zeta2=0.25; den2=[1 2*zeta2  1];
zeta3=0.5; den3=[1 2*zeta3  1]; 
zeta4=1.0; den4=[1 2*zeta4  1];
%
[y1,x,t]=impulse(num,den1,t); 
[y2,x,t]=impulse(num,den2,t);
[y3,x,t]=impulse(num,den3,t); 
[y4,x,t]=impulse(num,den4,t);
%
plot(t,y1,t,y2,t,y3,t,y4)
xlabel(' wn*t'), ylabel('y(t)/wn')
title('zeta = 0.1, 0.25, 0.5,1.0'), grid
 
