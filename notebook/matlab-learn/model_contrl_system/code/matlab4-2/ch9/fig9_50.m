% Chapter 9: Figure 9.50, p. 527
%
%   Remotely controlled vehicle system Nichols chart 
%   for K=4.44, 10, and 20.
%
numgc=[1 2]; dengc=[1 1];
numg=[1]; deng=[1 2 4];
[num,den]=series(numgc,dengc,numg,deng);
%
w=logspace(-1,2,200);
%
K1=20; K2=10; K3=4.44;
[mag1,ph1,w]=nichols(K1*num,den,w);
[mag2,ph2,w]=nichols(K2*num,den,w);
[mag3,ph3,w]=nichols(K3*num,den,w);
plot(ph1,20*log10(mag1),'-',ph2,20*log10(mag2),'-',...
ph3,20*log10(mag3),'-'),ngrid
axis([-210,0,-24,36])
 
