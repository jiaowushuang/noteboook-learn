% Chapter 9: Figure 9.39, p. 520
%
%   The nyquist function with manual scaling using the
%   axis function.  The transfer function is
%
%                    0.5 
%   G(s) = ---------------------------
%            s^3 + 2 s^2 +  s + 0.5
%
num=[0.5]; den=[1 2 1 0.5 ];
[re,im]=nyquist(num,den);
plot(re,im),grid
axis([-1.0,.1,-0.1,0.1]);

