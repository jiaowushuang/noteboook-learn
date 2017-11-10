% Chapter 6: Figure 6.24, p. 324
%
Ka=100; K1=0.05;
ng1=[5000]; dg1=[1 1000];
ng2=[1]; dg2=[1 20 0];
nc=[K1 1]; dc=[0 1];
[n,d]=series(Ka*ng1,dg1,ng2,dg2);
[num,den]=feedback(n,d,nc,dc);
t=[0:0.001:0.5];
y=step(num,den,t);
plot(t,y),grid
xlabel('Time (sec)'), ylabel('y(t)')
