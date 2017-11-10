% Chapter 11: Figure 11.29, p. 672
%
%   Root locus for the automatic test system
%   including performance specification regions.
%
num=[1 8 20]; den=[1 6 5 0];
clg; rlocus(num,den); hold on
%
zeta=0.72; wn=2.8;
x=[-10:0.1:-zeta*wn]; y=-(sqrt(1-zeta^2)/zeta)*x;
xc=[-10:0.1:-zeta*wn];c=sqrt(wn^2-xc.^2);
plot(x,y,':',x,-y,':',xc,c,':',xc,-c,':')
