% Chapter 2: Figure 2.52, p. 89
%    Application of the cloop function.
%
numg=[1]; deng=[500 0 0];
numc=[1 1]; denc=[1 2];
[num1,den1]=series(numg,deng,numc,denc);
[num,den]=cloop(num1,den1,-1);
printsys(num,den)
