% Chapter 3: Figure 3.31, p. 157
%
%   Convert G(s) = (2s^2+8s+6)/(s^3+8s^2+16s+6) 
%   to a state-space representation.
%
num=[2 8 6]; den=[1 8 16 6];
[A,B,C,D]=tf2ss(num,den);
printsys(A,B,C,D)
