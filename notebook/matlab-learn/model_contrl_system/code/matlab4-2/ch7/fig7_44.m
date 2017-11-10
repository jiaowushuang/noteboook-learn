% Chapter 7: Figure 7.44, p. 384
%
%   Root sensitivity to a 5% change in K, where the 
%   characteristic equation is given by 
%  
%               p(s) = s^3+5s^2+(6+K)s+K = 0
%
%   and the nominal value of K=20.5775.
%
K=20.5775; den=[1 5 6+K K]; r1=roots(den);
dk=1.0289;
Km=K+dk; denm=[1 5 6+Km Km]; r2=roots(denm);
dr=r1-r2;
S=dr/(dk/K)
