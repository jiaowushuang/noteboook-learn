% Chapter 6: Figure 6.12, p. 314
%
%   Using the roots function to compute the closed-loop
%   system poles of a unity feedback system with
%   G(s)=1/s^3+s^2+2s+23.
%
numg=[1]; deng=[1 1 2 23];
[num,den]=cloop(numg,deng);
roots(den)
