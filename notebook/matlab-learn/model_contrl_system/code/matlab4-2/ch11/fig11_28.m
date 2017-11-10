% Chapter 11: Figure 11.28, p. 670
%
%   Satellite controllability with a tangential thruster only 
%   (i.e. failed radial thruster).
%
w=0.0011;
A=[0 1 0  0;3*w^2 0 0 2*w;0 0 0 1;0 -2*w 0 0];
b2=[0;0;0;1];
Pc=ctrb(A,b2);
n=det(Pc); 
if abs(n) < eps
 disp('Satellite is uncontrollable with tangential thruster only!')
else
 disp('Satellite is controllable with tangential thruster only!')
end
 
