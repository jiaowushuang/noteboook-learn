% Chapter 8: Figure 8.40, p. 453
%
%   The step response of the engraving machine, where
%
%                 2
%   T(s) =  ------------- . 
%           s^3+3s^2+2s+2 
%
K=2; num=[K]; den=[1 3 2 K];
t=[0:0.01:20];
lu=1.02*ones(length(t),1);
ll=0.98*ones(length(t),1);
l=1.38*ones(length(t),1);
[y,x]=step(num,den,t);
plot(t,y,t,l,'--',t,lu,'--',t,ll,'--'), grid
xlabel('Time [sec]')
ylabel('y(t)')
