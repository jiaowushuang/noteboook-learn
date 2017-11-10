% Chapter 5: The Performance of Feedback Control Systems
% MP5.3, p. 291
%
w1=2; z1=0;
w2=2; z2=0.1;
w3=1; z3=0;
w4=1; z4=0.2;
t=[0:0.1:20];
%
num1=[w1^2]; den1=[1 2*z1*w1 w1^2];
[y1,x1]=impulse(num1,den1,t);
%
num2=[w2^2]; den2=[1 2*z2*w2 w2^2];
[y2,x2]=impulse(num2,den2,t);
%
num3=[w3^2]; den3=[1 2*z3*w3 w3^2];
[y3,x3]=impulse(num3,den3,t);
%
num4=[w4^2]; den4=[1 2*z4*w4 w4^2];
[y4,x4]=impulse(num4,den4,t);
%
clg
subplot(221),plot(t,y1),title('wn1=2, zeta1=0')
subplot(222),plot(t,y2),title('wn1=2, zeta1=0.1')
subplot(223),plot(t,y3),title('wn1=1, zeta1=0')
subplot(224),plot(t,y4),title('wn1=1, zeta1=0.2')
