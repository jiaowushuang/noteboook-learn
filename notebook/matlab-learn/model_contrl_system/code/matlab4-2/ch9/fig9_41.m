% Chapter 9: Figure 9.41, p. 521
%
%   The margin function.  The transfer function is
%
%                    0.5 
%   G(s) = ---------------------------
%            s^3 + 2 s^2 +  s + 0.5
%
num=[0.5]; den=[1 2 1 0.5];
[mag,phase,w]=bode(num,den);
margin(mag,phase,w);