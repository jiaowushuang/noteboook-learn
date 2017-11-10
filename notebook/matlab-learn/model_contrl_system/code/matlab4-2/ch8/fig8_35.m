% Chapter 8: Figure 8.35, p. 449
%
%   The Bode plot of
%
%                     5(0.1s+1) 
%   G(s) =  -----------------------------  . 
%           s(0.5s+1)(s^2/2500+0.6s/50+1) 
%
num=5*[0.1 1];
f1=[1 0]; f2=[0.5 1]; f3=[1/2500 .6/50 1];
den=conv(f1,conv(f2,f3));
%
bode(num,den)
