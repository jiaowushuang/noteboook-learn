% Appendix F: MATLAB Basics, Section F.4, p. 827-830.
%
%    MATLAB graphics described in Section F.4  
%    includes Figures F.18 - F.20.  After each subtopic, a 
%    pause is inserted to allow you to inspect the output.  Hit 
%    the space bar (or any other key) to continue to the next 
%    subtopic.
%

clear
format
hold off
clg
% -------------- Figure F.18
x=[0:0.1:1]';
y=x.*sin(x);
plot(x,y)
title('Figure F.18: Plot of x sin(x) vs x')
xlabel('x')
ylabel('y')
grid
pause
%
% -------------- Figure F.19
x=[0:0.1:1]';
y1=x.*sin(x); y2=sin(x);
plot(x,y1,'--',x,y2,'-.')
text(0.1,0.85,'y1 = x sin(x) - - -')
text(0.1,0.80,'y2 = sin(x) ._._')
xlabel('x')
ylabel('y1 and y2')
title('Figure F.19')
grid
pause 
%
% -------------- Figure F.20
dx=[0:0.1:1]';
y1=x.*sin(x); y2=sin(x);
subplot(221),plot(x,y1,'--',x,y2,'-.')
title('Figure F.20a: subplot(221)')
subplot(222),plot(x,y1,'--',x,y2,'-.')
title('Figure F.20b: subplot(222)')
subplot(223),plot(x,y1,'--',x,y2,'-.')
title('Figure F.20c: subplot(223)')
subplot(224),plot(x,y1,'--',x,y2,'-.')
title('Figure F.20d: subplot(224)')
 
