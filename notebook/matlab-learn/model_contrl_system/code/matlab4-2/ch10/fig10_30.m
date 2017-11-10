% Chapter 10: Figure 10.30, p. 608
%
%   Rotor winder control system transient response
%   for a simple gain controller with K=50, 100, 200, 
%   and 300.
%
K=[50 100 200 500]; 
numg=[1]; deng=[1 15 50 0]; 
t=[0:0.01:5];
for i=1:4
[nums,dens]=series(K(i),1,numg,deng);
[num,den]=cloop(nums,dens);
[y,x]=step(num,den,t);
Ys(:,i)=y;
end
plot(t,Ys(:,1),'-',t,Ys(:,2),'-',t,Ys(:,3),'-',t,Ys(:,4),'-')
grid
xlabel('Time (sec)'), ylabel('y(t)')
