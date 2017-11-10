% Chapter 2: Figure 2.38, p. 81
%   Unforced Response to an Initial Condition
%   Generates Figure 2.39: Spring-mass-damper unforced response.
%
y0=0.15; wn=sqrt(2);
zeta1=3/(2*sqrt(2)); zeta2=1/(2*sqrt(2));
t=[0:0.1:10];
%
t1=acos(zeta1)*ones(1,length(t));
t2=acos(zeta2)*ones(1,length(t));
c1=(y0/sqrt(1-zeta1^2));c2=(y0/sqrt(1-zeta2^2));
y1=c1*exp(-zeta1*wn*t).*sin(wn*sqrt(1-zeta1^2)*t+t1);
y2=c2*exp(-zeta2*wn*t).*sin(wn*sqrt(1-zeta2^2)*t+t2);
%
% Boundary Functions 
%
bu=c2*exp(-zeta2*wn*t);bl=-bu; 
%
% Plot Unforced Response 
%
plot(t,y1,'-',t,y2,'--',t,bu,':',t,bl,':')
legend('overdamped zeta1 = 1.0610','underdamped zeta2 = 0.3536')
grid
xlabel('Time [sec]')
ylabel('y(t) Displacement [m]')
text(0.2,0.85,['overdamped  zeta1=',num2str(zeta1),...
'- solid'],'sc')
text(0.2,0.80,['underdamped zeta2=',num2str(zeta2),...
'- dashed'],'sc')
