% Chapter 10: Figure 10.33, p. 611
%
%   Rotor winder control compensated system step response
%   with lead controller
%
%              1800(s+3.5)
%     Gc(s) = -------------  . 
%                 s+25 
%
K=1800; 
%
numg=[1]; deng=[1 15 50 0]; 
numgc=K*[1 3.5]; dengc=[1 25]; 
%
[nums,dens]=series(numgc,dengc,numg,deng);
[num,den]=cloop(nums,dens);
%
t=[0:0.001:2];
step(num,den,t);
ylabel('y(t)')
 
