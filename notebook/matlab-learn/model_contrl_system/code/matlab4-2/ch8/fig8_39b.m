% Chapter 8: Figure 8.39, p. 452
%
%   Percent overshoot (P.O.) and settling time (Ts) from natural 
%   frequency and damping ratio for second-order systems.  The 
%   parameters zeta and wn must be input at the command level 
%   prior to executing this m-file.
%

% Rename this script engrave2.m for use with book
%
ts=4/zeta/wn
po=100*exp(-zeta*pi/sqrt(1-zeta^2))  
