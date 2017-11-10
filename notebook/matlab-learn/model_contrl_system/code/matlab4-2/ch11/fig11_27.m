% Chapter 11: Figure 11.27, p. 670
%
%   Satellite controllability with a radial thruster only 
%   (i.e. failed tangential thruster).
%
w=0.0011;
A=[0 1 0  0;3*w^2 0 0 2*w;0 0 0 1;0 -2*w 0 0];
b1=[0;1;0;0];
Pc=ctrb(A,b1);
n=det(Pc);  
if abs(n) < eps
 disp('Satellite is uncontrollable with radial thruster only!')
else
 disp('Satellite is controllable with radial thruster only!')
end