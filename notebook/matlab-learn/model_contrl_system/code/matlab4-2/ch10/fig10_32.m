% Chapter 10: Figure 10.32, p. 611
%
%   Rotor winder control compensated system Bode diagram 
%   with lead controller
%
%              1800(s+3.5)
%     Gc(s) = -------------  . 
%                 s+25 
%
K=1800; 
numg=[1]; deng=[1 15 50 0]; 
%numgc=K*[1 3.5]; dengc=[1 25]; 
numgc=(K)*[1 3.5]; dengc=[1 25]; 
[num,den]=series(numgc,dengc,numg,deng);
w=logspace(-1,2,200);
[mag,phase,w]=bode(num,den,w);
[Gm,Pm,Wcg,Wcp]=margin(mag,phase,w);
%
bode(num,den), subplot(211)
title(['Gain Margin = ',num2str(Gm), ...
'  Phase Margin = ',num2str(Pm)])
 
