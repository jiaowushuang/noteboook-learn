% Chapter 7: Figure 7.40, p. 381
%
%   The partial fraction expansion of 
%
%                 20.5775(s+1)(s+3) 
%   Y(s) =  ---------------------------  . 
%           s^2(s+2)(s+3)+20.5775s(s+1) 
%
K=20.5775;
num=K*[1 4 3]; den=[1 5 6+K K 0];
[r,p,k]=residue(num,den)
