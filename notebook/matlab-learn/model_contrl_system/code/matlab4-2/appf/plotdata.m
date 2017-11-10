% Appendix F: MATLAB Basics, Section F.5, p. 830-831.
%
%    MATLAB's use of scripts is described in Section F.5.  
%    The script described in Figure F.21 is given here.  It
%    can be used to plot y(t)=sin(alpha*t), where the parameter 
%    alpha is input at the command prompt prior to executing 
%    the m-file.  The value of alpha must exist in the workspace 
%    prior to invoking the script.
%
t=[0:0.01:1];
y=sin(alpha*t);
plot(t,y)
xlabel('Time [sec]')
ylabel('y(t) =  sin( alpha * t )')
grid
