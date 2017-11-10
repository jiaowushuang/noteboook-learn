% Chapter 2: Figure 2.41, p. 83
%   Using conv and polyval to multiply and evaluate 
%   the polynomials  (3 s^2 + 2 s + 1 ) ( s + 4).
%
p=[3 2 1]; q=[1 4];
n=conv(p,q)
%
value=polyval(n,-5)