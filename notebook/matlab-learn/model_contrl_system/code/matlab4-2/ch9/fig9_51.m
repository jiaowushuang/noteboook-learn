% Chapter 9: Figure 9.51, p. 527
%
%   Remotely controlled vehicle system Nyquist chart 
%   for K= 10 with automatic labeling of gain and
%   phase margin.
%
numgc=10*[1 2]; dengc=[1 1];
numg=[1]; deng=[1 2 4];
%
[num,den]=series(numgc,dengc,numg,deng);
%
[Gm,Pm,Wcg,Wcp]=margin(num,den);
%
nyquist(num,den);
title(['Gain Margin = ',num2str(Gm), ...
'  Phase Margin = ',num2str(Pm)])
