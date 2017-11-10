% Chapter 9: Figure 9.47, p. 524
%
%   The Bode plot of the liquid level control system with
%   gain and phase margin.  The gain K must be input at the
%   command level before executing this m-file.  Automatic
%   labeling of the plot with gain and phase margin.
%
num=K*[0.0743 -0.4460 0.8920]; d1=[1 1]; d2=[30 1]; 
d3=[1/9 1/3 1]; d4=[ 0.0743 0.4460 0.8920]; 
den=conv(d1,conv(d2,conv(d3,d4)));
%
w=logspace(-2,1,400);
[mag,phase,w]=bode(num,den,w);
[Gm,Pm,Wcg,Wcp]=margin(mag,phase,w);
%
bode(num,den), subplot(211)
title(['Gain Margin = ',num2str(Gm), ...
'  Phase Margin = ',num2str(Pm)])
