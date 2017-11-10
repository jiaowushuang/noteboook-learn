% Chapter 10: Figure 10.31, p. 610
%
%   Rotor winder control uncompensated system Bode diagram 
%   for lead controller design. 
%
K=500; 
numg=[1]; deng=[1 15 50 0]; 
[num,den]=series(K,1,numg,deng);
w=logspace(-1,2,200);
[mag,phase,w]=bode(num,den,w);
[Gm,Pm,Wcg,Wcp]=margin(mag,phase,w);
%
Phi=(60-Pm)*pi/180; 
%
alpha=(1+sin(Phi))/(1-sin(Phi))
%
M=-10*log10(alpha)*ones(length(w),1);
%
[mag,phase,w]=bode(num,den,w);
semilogx(w,20*log10(mag),w,M), grid
xlabel('frequency [rad/sec]'), ylabel('mag [db]')
