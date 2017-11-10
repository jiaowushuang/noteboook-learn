% Chapter 10: Figure 10.34, p. 612
%
%   Rotor winder control uncompensated system root locus.
%   Performance region automatically shown on plot.
%
numg=[1]; deng=[1 15 50 0]; 
clg; rlocus(numg,deng); hold on
%
zeta=0.5912; wn=2.2555;
x=[-10:0.1:-zeta*wn]; y=-(sqrt(1-zeta^2)/zeta)*x;
xc=[-10:0.1:-zeta*wn];c=sqrt(wn^2-xc.^2);
plot(x,y,':',x,-y,':',xc,c,':',xc,-c,':')
axis([-15,1,-10,10]);

 