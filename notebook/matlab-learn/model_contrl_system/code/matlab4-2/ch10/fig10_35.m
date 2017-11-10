% Chapter 10: Figure 10.35, p. 612
%
%   Rotor winder control compensated system root locus 
%   with lag controller
%
%              s+0.1 
%     Gc(s) = -------  . 
%              s+0.01 
%
numg=[1]; deng=[1 15 50 0]; 
numgc=[1 0.1]; dengc=[1 0.01]; 
[num,den]=series(numgc,dengc,numg,deng);
clg; rlocus(num,den); hold on
%
zeta=0.5912; wn=2.2555;
x=[-10:0.1:-zeta*wn]; y=-(sqrt(1-zeta^2)/zeta)*x;
xc=[-10:0.1:-zeta*wn];c=sqrt(wn^2-xc.^2);
plot(x,y,':',x,-y,':',xc,c,':',xc,-c,':')
axis([-15,1,-10,10]);

