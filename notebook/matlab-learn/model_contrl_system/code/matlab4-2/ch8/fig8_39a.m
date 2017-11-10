% Chapter 8: Figure 8.39, p. 452
%
%   Closed-loop peak magnitude and resonant frequency for
%
%                 K  
%   T(s) =  -------------- , 
%           s^3+3s^2+2s+K 
%
%   where K must be input at the command level prior to 
%   executing this m-file.
%

% Rename this script engrave1.m for use with book
%
num=[K]; den=[1 3 2 K];
w=logspace(-1,1,400);
[mag,phase,w]=bode(num,den,w);
[mp,l]=max(mag);wr=w(l);
mp,wr
  
