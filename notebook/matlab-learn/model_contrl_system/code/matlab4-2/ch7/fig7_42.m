% Chapter 7: Figure 7.42, p. 382
%
%   The step response for 
%
%                   20.5775(s^2+4s+3)
%   T(s)  =     --------------------------  .
%               s^3+5s^2+26.5775s+20.5775 
%
K=20.5775;
num=K*[1 4 3]; den=[1 5 6+K K];
step(num,den), grid
