% Chapter 8: Figure 8.37, p. 450
%
%   The relationship between (Mpw,wr) and (zeta,wn) for
%   a second-order system.
%
zeta=[0.15:0.01:0.7];
wr_over_wn=sqrt(ones(1,length(zeta))-2*zeta.^2);
Mp=(2*zeta .* sqrt(ones(1,length(zeta))-zeta.^2)).^(-1);
%
subplot(211),plot(zeta,Mp),grid
xlabel('zeta'), ylabel('Mpw')
subplot(212),plot(zeta,wr_over_wn),grid
xlabel('zeta'), ylabel('wr/wn')
