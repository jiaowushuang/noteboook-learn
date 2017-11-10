% Chapter 9: Figure 9.42, p. 521
%
%   The Bode plot of
%
%                    0.5 
%   G(s) = ---------------------------
%            s^3 + 2 s^2 +  s + 0.5
%
%   with gain and phase margin shown on the plot using
%   the margin function.
%
num=[0.5]; den=[1 2 1 0.5 ];
w=logspace(-1,1,200);
[mag,phase,w]=bode(num,den,w);
margin(mag,phase,w);
  
