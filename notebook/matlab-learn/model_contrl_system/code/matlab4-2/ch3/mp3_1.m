% Chapter 3: State Variable Models
% MP3.1, p. 167
%

% 
% Part (a)
%
disp('Part (a)')
num=[1]; den=[1 10];
[a,b,c,d]=tf2ss(num,den);
printsys(a,b,c,d)
pause
% 
% Part (b)
%
disp('Part (b)')
num=[3 10 1]; den=[1 8 5];
[a,b,c,d]=tf2ss(num,den);
printsys(a,b,c,d)
pause
% 
% Part (c)
%
disp('Part (c)')
num=[1 14]; den=[1 3 3 1];
[a,b,c,d]=tf2ss(num,den);
printsys(a,b,c,d)
