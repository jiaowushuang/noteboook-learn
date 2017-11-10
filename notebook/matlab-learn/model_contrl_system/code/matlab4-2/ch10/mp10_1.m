% Chapter 10: The Design of Feedback Control Systems
% MP10.1, p. 638
%
numc=[10]; denc=[1 1];
numg=[9]; deng=[1 1];
[nums,dens]=series(numc,denc,numg,deng);
figure(1), margin(nums,dens);
%
[num,den]=cloop(nums,dens);
y=step(num,den);
figure(2)
step(num,den);
PO=100*(max(y)-1)
 

