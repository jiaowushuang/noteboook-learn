% Chapter 2: Figure 2.54, p. 90
%   Application of the feedback function.
%
numg=[1]; deng=[500 0 0];
numh=[1 1]; denh=[1 2];
[num,den]=feedback(numg,deng,numh,denh,-1);
printsys(num,den)
 
