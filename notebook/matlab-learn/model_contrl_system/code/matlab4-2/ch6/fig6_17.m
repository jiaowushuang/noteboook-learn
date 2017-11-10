% Chapter 6: Figure 6.17, p. 319
%
%   Two-track vehicle turning control ramp response
%   with a=0.6 and K=70.
%
t=[0:0.01:16]; u=t;
numgc=[1  0.6]; dengc=[1 1];
numg=[70]; deng=[1 7 10 0];
[numa,dena]=series(numgc,dengc,numg,deng);
[num,den]=cloop(numa,dena);
[y,x]=lsim(num,den,u,t);
plot(t,y,t,u,'--'), grid
xlabel('time [sec]'), ylabel('y(t)')
