% Chapter 13: Figure 13.36, p. 783
%
%   The continous step response of the second-order 
%   system of Figure 13.16, where
%
%                1
%     G(s) =  -------- .
%              s(s+1)
%
 numg=[1]; deng=[1 1 0];
%
[nd,dd]=pade(1,2); 
numd=dd-nd; dend=conv([1 0],dd);
[numdm,dendm]=minreal(numd,dend);
%
[n1,d1]=series(numdm,dendm,numg,deng);
[num,den]=cloop(n1,d1);
t=[0:0.1:20];
step(num,den,t)

