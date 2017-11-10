% Chapter 6: The Stability of Linear Feedback Systems
% MP6.3, p. 334
%
numg=[1 1]; deng=[1 4 6 10];
[num,den]=cloop(numg,deng);
printsys(num,den)
r=roots(den)
