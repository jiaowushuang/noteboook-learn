%%%%%%%%%%求两圆公切线%%%%%%%%%%%%%%%%%%%

%function DoubleCir(x1,y1,r1,x2,y2,r2)
function qiedian = DoubleCir(x1,y1,r1,x2,y2,r2)
% 画两圆的公切线
% x1  -- 第一个圆的圆心横坐标
% y1  -- 第一个圆的圆心纵坐标
% r1  -- 第一个圆的半径
% x2  -- 第二个圆的圆心横坐标
% y2  -- 第二个圆的圆心纵坐标
% r2  -- 第二个圆的半径
% qiedian -- 切点坐标，多行两列，第一列为x坐标，第二列为y坐标
% 用到了坐标平移和旋转
% 调用举例：
% qiedian = common_tangent1(1,2,3,4,6,8)
% qiedian = common_tangent1(1,2,3,4,5,6)
% qiedian = common_tangent1(1,2,3,4,6,2)
% qiedian = DoubleCir(1,2,2,5,7,3)
% by：xiezhh（谢中华）
% 2011.3.3

d = sqrt((x1-x2)^2+(y1-y2)^2);
d1 = abs(r1-r2);
d2 = r1+r2;

if d < d1
    error('大圆包含小圆，没有公切线')
end
if isequal([x1 y1 r1],[x2 y2 r2])
    error('两圆重合，有无穷多条公切线')
end
qiedian = [];

% t = linspace(0,2*pi,100);
% x = x1+r1*cos(t);
% y = y1+r1*sin(t);
% plot(x,y,'r')
hold on
% x = x2+r2*cos(t);
% y = y2+r2*sin(t);
% plot(x,y,'r')

xmin = min([x1 x2]-[r1 r2])-min([r1 r2])/5;
xmax = max([x1 x2]+[r1 r2])+min([r1 r2])/5;
ymin = min([y1 y2]-[r1 r2])-min([r1 r2])/5;
ymax = max([y1 y2]+[r1 r2])+min([r1 r2])/5;

XYR = [r1 x1 y1;r2 x2 y2];
XYR = sortrows(XYR);
r = XYR(1,1);
R = XYR(2,1);
xy = XYR(1,2:3)';

fun = @(beta)[abs(beta(2))/sqrt(1+beta(1)^2)-r;abs(beta(1)*d+beta(2))/sqrt(1+beta(1)^2)-R];

theta = atan2(XYR(2,3)-XYR(1,3),XYR(2,2)-XYR(1,2));
A = [cos(theta) -sin(theta);sin(theta) cos(theta)];

if d == d1
    h = line(-r,0,'Marker','.','MarkerSize',15);
    qiedian = reline(h,A,xy);
else
    [k,jieju] = SlopeIntercept(0,r,d,R);
    ab = fsolve(fun,[k jieju]);
    theta = pi+atan(-1/ab(1));
    %h = line('XData',[r;R]*cos(theta)+[0;d],'YData',[r,R]*sin(theta),'color','b');
    h = line('XData',[r;R]*cos(theta)+[0;d],'YData',[r,R]*sin(theta),'color','w');
    qiedian = reline(h,A,xy);
    %h = line('XData',[r;R]*cos(theta)+[0;d],'YData',-[r,R]*sin(theta),'color','b');
    h = line('XData',[r;R]*cos(theta)+[0;d],'YData',-[r,R]*sin(theta),'color','w');
    qiedian = [qiedian;reline(h,A,xy)];
        
    if d == d2        
        h = line(r,0,'Marker','.','MarkerSize',15);
        qiedian = [qiedian;reline(h,A,xy)];
    elseif d > d2
        [k,jieju] = SlopeIntercept(0,-r,d,R);
        ab = fsolve(fun,[k jieju]);
        theta = atan(-1/ab(1));
        %h = line('XData',[r;-R]*cos(theta)+[0;d],'YData',[r,-R]*sin(theta),'color','b');
        h = line('XData',[r;-R]*cos(theta)+[0;d],'YData',[r,-R]*sin(theta),'color','w');
        qiedian = [qiedian;reline(h,A,xy)];
        %h = line('XData',[r;-R]*cos(theta)+[0;d],'YData',[-r,R]*sin(theta),'color','b');
        h = line('XData',[r;-R]*cos(theta)+[0;d],'YData',[-r,R]*sin(theta),'color','w');
        qiedian = [qiedian;reline(h,A,xy)];
    end    
end

axis equal

axis([122 142 -12 2]);
%axis([xmin xmax ymin ymax])

function [Slope,Intercept] = SlopeIntercept(x1,y1,x2,y2)
Slope = (y2-y1)/(x2-x1);
Intercept = (y1*x2-x1*y2)/(x2-x1);

function xydata = reline(handle,A,xy)
x = get(handle,'Xdata');
y = get(handle,'Ydata');
xydata = (A*[x;y]+repmat(xy,1,numel(x)))';
set(handle,'Xdata',xydata(:,1),'Ydata',xydata(:,2))