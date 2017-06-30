%%%%%%%%%%画最小外接圆%%%%%%%%%%%%%%%
%%%%%%%返回圆心坐标即半径%%%%%%%%%%%
function cirl=DrawCircle(pos)
hold on;
global DataCoast;
global long;
global lat;
global num;
%len=length(spo);

n=1;
maxzhi=0;
nn=length(pos);
%cirl(nn,3)=null;%存储圆心经纬度坐标&半径
p=1;
ii=1;
while(p<=nn)
for i=(num(pos(p))+1):1:(num(pos(p)+1)-1)
% [y(i) x(i)]=WGS84ToMercator(lat(i),long(i),0,0,0) ;  
  x(ii)=long(i);
  y(ii)=lat(i);
  ii=ii+1;
end
ii=1;

len=num(pos(p)+1)-num(pos(p))-1;
for i=1:1:len-1
    for j=i+1:1:len
    %dis(n)=(long(i)-long(j))^2+(lat(i)-lat(j))^2;%计算距离
    dis(n)=(x(i)-x(j))^2+(y(i)-y(j))^2;%计算距离
    n=n+1;
    end
    [m point]=max(dis);
    dis=[];
    n=1;
    if m>maxzhi
        maxzhi=m;
        point1=i;%长轴点1
        point2=point+i;%长轴点2
    end
end
a=[x(point1),x(point2)];
b=[y(point1),y(point2)];

%%%%%%画外接圆%%%%%%%%%
x0=(x(point1)+x(point2))/2;%圆点坐标
y0=(y(point1)+y(point2))/2;
R=sqrt((x0-x(point1))^2+(y0-y(point1))^2);

theta=0:pi/100:2*pi;%角度为[0,2pi]

cx=R*cos(theta)+x0;
cy=R*sin(theta)+y0;
plot(x0,y0,'.r');
plot(cx,cy,'y');
fill(cx,cy,'y','FaceAlpha',0.2);%透明填充外接圆
cirl(p,:)=[x0,y0,R];
p=p+1;
end

end