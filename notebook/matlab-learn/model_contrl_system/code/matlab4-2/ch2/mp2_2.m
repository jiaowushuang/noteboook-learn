% Chapter 2: Mathematical Models of Systems
% MP2.2, p. 117 
%
numc=[1]; denc=[1 1];
numg=[1 2]; deng=[1 3];
%
% Part (a)
%
[numa,dena]=series(numc,denc,numg,deng);
[num,den]=cloop(numa,dena);
printsys(num,den)
%
% Part (b)
%
step(num,den), grid
