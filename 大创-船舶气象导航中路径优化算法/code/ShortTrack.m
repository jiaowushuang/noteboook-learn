function dis=ShortTrack(AllTan,cirl)
global DpLong DpLat ApLong ApLat;
x0=cirl(2,1);
y0=cirl(2,2);
R=cirl(2,3);
theta=0:pi/100:2*pi;%角度为[0,2pi]

cx=R*cos(theta)+x0;
cy=R*sin(theta)+y0;%圆边界离散化的过程

Tx=AllTan(2,1);%切点横坐标
Ty=AllTan(2,2);%切点纵坐标

% for i=1:1:length(cx)-1
%    if(((AllTan(2,1)>=cx(i))&&(AllTan(2,1)<=cx(i+1)))&&((AllTan(2,2)<=cy(i))&&(AllTan(2,2)>=cy(i+1))))
%        n=i
%        break;
%    end
% end
%%%%%%%%%%%%%%%%%%%%%%%起点到第一个圆从53开始,最终点64%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% for i=53:1:64
%     
% a=[DpLong cx(i)];
% b=[DpLat cy(i)];
% plot(a,b,'b');
% end

a=[DpLong cx(64)];
b=[DpLat cy(64)];
cx1=cx(64);
cy1=cy(64);
plot(a,b,'b');
plot(cx(64),cy(64),'.b');
%%%%%%%%%%%%%%%%%%%%%%%%%%%终点到小圆从69开始,最终点37%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x0=cirl(1,1);
y0=cirl(1,2);
R=cirl(1,3);
theta=0:pi/100:2*pi;%角度为[0,2pi]

cx=R*cos(theta)+x0;
cy=R*sin(theta)+y0;%圆边界离散化的过程


Tx=AllTan(11,1);%切点横坐标
Ty=AllTan(11,2);%切点纵坐标

a=[ApLong cx(37)];
b=[ApLat cy(37)];
cx2=cx(37);
cy2=cy(37);
plot(a,b,'b');
plot(cx(37),cy(37),'.b');

a=[cx1 cx2];
b=[cy1 cy2];
plot(a,b,'b'); 

dis=Distance(DpLong,DpLat,cx1,cy1)+Distance(cx1,cy1,cx2,cy2)+Distance(cx2,cy2,ApLong,ApLat);




end