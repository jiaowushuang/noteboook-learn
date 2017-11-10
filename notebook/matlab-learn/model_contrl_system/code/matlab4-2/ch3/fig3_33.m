% Chapter 3: Figure 3.33, p. 158
%
%   The state transition matrix for a given time, dt.
%
A=[0 -2;1 -3]; dt=0.2; 
Phi=expm(A*dt)
 
