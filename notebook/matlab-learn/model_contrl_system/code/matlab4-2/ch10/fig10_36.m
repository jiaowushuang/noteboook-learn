% Chapter 10: Figure 10.36, p. 613
%
%   Rotor winder control compensated system step response 
%   with lag controller
%
%              100(s+0.1) 
%     Gc(s) = -----------  . 
%                s+0.01 
%
K=100; 
numg=[1]; deng=[1 15 50 0]; 
numgc=K*[1 0.1]; dengc=[1 0.01]; 
[nums,dens]=series(numgc,dengc,numg,deng);
[num,den]=cloop(nums,dens);
step(num,den)
 
