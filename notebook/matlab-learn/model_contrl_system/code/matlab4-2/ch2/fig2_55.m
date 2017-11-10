% Chapter 2: Figure 2.55, p. 91
%   Multi-loop block reduction.
%
ng1=[1]; dg1=[1 10];
ng2=[1]; dg2=[1 1];
ng3=[1 0 1]; dg3=[1 4 4];
ng4=[1 1]; dg4=[1 6];
nh1=[1 1]; dh1=[1 2];
nh2=[2]; dh2=[1];
nh3=[1]; dh3=[1];
n1=conv(nh2,dg4); d1=conv(dh2,ng4);
[n2a,d2a]=series(ng3,dg3,ng4,dg4);
[n2,d2]=feedback(n2a,d2a,nh1,dh1,+1);
[n3a,d3a]=series(ng2,dg2,n2,d2);
[n3,d3]=feedback(n3a,d3a,n1,d1);
[n4,d4]=series(ng1,dg1,n3,d3);
[num,den]=cloop(n4,d4,-1);
printsys(num,den)
 
