% Chapter 2: Figure 2.58, p. 92
%   Electric traction motor block reduction.
%
num1=[10];den1=[1 1];
num2=[1];den2=[2 0.5];
num3=[540];den3=[1];
num4=[0.1];den4=[1];
[na,da]=series(num1,den1,num2,den2);
[nb,db]=feedback(na,da,num4,den4,-1);
[nc,dc]=series(num3,den3,nb,db);
[num,den]=cloop(nc,dc,-1);
printsys(num,den)
 
