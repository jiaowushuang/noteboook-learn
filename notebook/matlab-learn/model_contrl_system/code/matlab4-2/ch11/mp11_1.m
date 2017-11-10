% Chapter 11: The Design of State Variable Feedback Systems
% MP11.1, p. 684
%
A=[-1 1 0;4 0 -3;-6 8 10];
B=[1;0;-1];
C=[1 2 1];
D=[0];
%
Pc=ctrb(A,B); Det_Pc=det(Pc)
Q=obsv(A,C); Det_Q=det(Q)
