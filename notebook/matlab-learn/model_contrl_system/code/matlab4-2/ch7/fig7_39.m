% Chapter 7: Figure 7.39, p. 380
%
%                            K (s+1) 
%   The root locus for 1 + ------------ = 0, where the 
%                          s(s+2)(s+3) 
%
%   rlocfind function is used to select a point on the locus.
%
p=[1 1]; q=[1 5 6 0];
rlocus(p,q);
rlocfind(p,q)
 
