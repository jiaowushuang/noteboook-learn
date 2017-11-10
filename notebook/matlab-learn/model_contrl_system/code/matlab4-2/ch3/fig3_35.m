% Chapter 3: Figure 3.35, p. 159
%
%   The time response for nonzero initial
%   conditions and zero input using lsim.
%
A=[0 -2;1 -3];
B=[2;0];
C=[1 0];
D=[0];
x0=[1 1 ];
t=[0:0.01:1];
u=0*t;
[y,x]=lsim(A,B,C,D,u,t,x0);
subplot(211), plot(t,x(:,1))
xlabel('time [sec]'), ylabel('x1')
subplot(212), plot(t,x(:,2))
xlabel('time [sec]'), ylabel('x2')
