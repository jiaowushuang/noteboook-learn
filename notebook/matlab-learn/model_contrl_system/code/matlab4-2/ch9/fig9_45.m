% Chapter 9: Figure 9.45, p. 523
%
%   The Nichols chart of
%
%                    1 
%   G(s) = -------------------------  .
%            0.2 s^3 + 1.2 s^2 +  s 
%
%
num=[1]; den=[0.2 1.2 1 0 ];
w=logspace(-1,1,400);
nichols(num,den,w);
ngrid
axis([-210,0,-24,36]);
