% Chapter 9: Figure 9.43, p. 522
%
%   The Nyquist plot of
%
%                    0.5 
%   G(s) = ---------------------------
%            s^3 + 2 s^2 +  s + 0.5
%
%   with gain and phase margin calculation using the
%   margin function.
%
num=[0.5]; den=[1 2 1 0.5 ];
%
[mag,phase,w]=bode(num,den);
[Gm,Pm,Wcg,Wcp]=margin(mag,phase,w);
%
nyquist(num,den);
title(['Gain Margin = ',num2str(Gm), ...
'  Phase Margin = ',num2str(Pm)])
