% Chapter 12: Figure 12.33, p. 725
%
%   Root locus for the PID compensated temperature controller
%   as Khat varies.  The characteristic equation is
%                s^2+16s+70
%      1 + Khat ------------ = 0 .
%                    s^3
%
a=16; b=70;
num=[1 a b]; den=[1 0 0 0];
rlocus(num,den)
rlocfind(num,den)

