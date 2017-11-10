% Chapter 9: Figure 9.49, p. 526
%
%   Remotely controlled vehicle closed-loop system
%   step response for K=4.44, 10, and 20.
%
t=[0:0.1:10]; K=20;
%
for i=1:3
 numgc=K*[1 2]; dengc=[1 1];
 numg=[1]; deng=[1 2 4];
 [nums,dens]=series(numgc,dengc,numg,deng);
 [num,den]=cloop(nums,dens);
 [y,x]=step(num,den,t);
 if i==1, y1=y; K=10; end
 if i==2, y2=y; K=4.44; end
 if i==3, y3=y; end
end
%
plot(t,y1,'-',t,y2,'-',t,y3,'-'),grid
xlabel('time [sec]'), ylabel('y(t)')
 
