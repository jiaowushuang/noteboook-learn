%求两点距离公式
function s=Distance(x1,y1,x2,y2)
[x1 y1]=WGS84ToMercator(x1*60,y1*60,0,0,0);
[x2 y2]=WGS84ToMercator(x2*60,y2*60,0,0,0);
s=sqrt((x1-x2)^2+(y1-y2)^2);%单位：米
s=s/1000;%单位:千米
end