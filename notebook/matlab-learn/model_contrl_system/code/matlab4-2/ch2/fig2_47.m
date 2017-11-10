% Chapter 2: Figure 2.47, p. 86
%   Application of the series function.
%
numg=[1];deng=[500 0 0];
numh=[1 1];denh=[1 2];
[num,den]=series(numg,deng,numh,denh);
printsys(num,den)
