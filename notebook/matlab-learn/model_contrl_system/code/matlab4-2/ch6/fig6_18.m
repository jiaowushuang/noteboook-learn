% Chapter 6: Figure 6.18, p. 319
%
%   The characteristic equation of the matrix 
%   A=[-8 -16 -6;1 0 0;0 1 0] using the poly function.
%
A=[-8 -16 -6;1 0 0;0 1 0];
p=poly(A)
r=roots(p)