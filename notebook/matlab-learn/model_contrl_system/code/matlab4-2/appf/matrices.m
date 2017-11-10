% Appendix F: MATLAB Basics, Section F.3, p. 823-827.
%
%    The MATLAB use of matrices described in Section F.3  
%    includes Figures F.12 - F.17.  After each subtopic, a 
%    pause is inserted to allow you to inspect the output.  Hit 
%    the space bar (or any other key) to continue to the next 
%    subtopic.
%

clear
format
% -------------- Figure F.12
disp(' -------------- Figure F.12')
A=[1,-4*j,sqrt(2);
log(-1) sin(pi/2) cos(pi/3)
asin(0.5),acos(0.8) exp(0.8)]
A=[1 2;4 5]
pause
%
% -------------- Figure F.13
disp(' -------------- Figure F.13')
A=[1 3;5 9]; B=[4 -7;10 0];
A+B
b=[1;5];
A*b
A'
pause 
%
% -------------- Figure F.14
disp(' -------------- Figure F.14')
x=[5;pi;sin(pi/2)];y=[exp(-0.5);-13;pi^2];
x'*y
x*y'
pause 
%
% -------------- Figure F.15
disp(' -------------- Figure F.15')
A=[1;2;3]; B=[-6;7;10];
A.*B
A.^2
pause 
%
% -------------- Figure F.17
disp(' -------------- Figure F.17')
x=[0:0.1:1]'; y=x.*sin(x);
[x,y]
 
