% Chapter 4: Figure 4.31, p. 207
%
%   English channel boring machine: system sensitivity 
%   for K=20.
%
K=20; num=[1 1 0]; den=[1 12 K];
w=logspace(-1,3,200); s=w*j;
%
% Compute System Sensitivity
%
n= s.^2 + s; d= s.^2 +12*s+K; S=n./d;
%
% Compute Approximate Sensitivity S = s / K
%
n2= s; d2=K; S2=n2./d2;
%
% Generate the plots
%
subplot(211), plot(real(S),imag(S))
title('System Sensitivity to Plant Variations')
xlabel('Real(S)'), ylabel('Imag(S)'), grid
subplot(212), loglog(w,abs(S),w,abs(S2))
xlabel('w [rad/sec]'), ylabel('Abs(S)'), grid
