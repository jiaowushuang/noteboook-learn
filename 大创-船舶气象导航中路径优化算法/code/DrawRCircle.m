%%%%%%%%%画滚动优化圆%%%%%%%%%%%%%
function [x,y]=DrawRCircle(x0,y0,R)
alpha=0:pi/50:2*pi;%角度[0,2*pi]
x=x0+R*cos(alpha);
y=y0+R*sin(alpha);
%if flag>15
%plot(x,y,'k')%画圆
%end
%fill(x,y,'b');%内部填充红色

%axis([-60 0 0 60]);
%axis([-15 -13 46 51]);
%axis equal 
end