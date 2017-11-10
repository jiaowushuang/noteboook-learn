% Chapter 13: Figure 13.31, p. 780
%
%   Continuous- to discrete-time system conversion with 
%   the c2dm function.  The transfer function is
%
%                1
%     G(s) =  --------  ,
%              s(s+1)
%
%    and the  sampling period is T=1 sec.
%
num=[1]; den=[1 1 0];
T=1;
[numz,denz]=c2dm(num,den,T,'zoh');
printsys(numz,denz,'z')
 
