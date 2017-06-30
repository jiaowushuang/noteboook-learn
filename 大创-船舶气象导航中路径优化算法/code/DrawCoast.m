%%%%%%%%%%%%%%莫卡托投影%%%%%%%%%%%%%%%%%%%%%
function DrawCoast
global DataCoast;
global long;
global lat;
global num;
DataCoast=importdata('coast.txt');%读取海岸线数据，为了读取方便各海岸线间用9999做标志位
long=DataCoast(:,2);%经度
lat=DataCoast(:,1);%纬度
len=length(lat);%长度
n=1;%海岸线条数
j=1;
p=1;
%figure;
hold on;%连续画图时用
for i=1:1:len%标记海岸线位置
   if(lat(i)==9999)
     num(n)=i;
     n=n+1;
   end
end
for i=1:1:(num(1)-1)
% [y(i) x(i)]=WGS84ToMercator(lat(i),long(i),0,0,0) ;  
  x(i)=long(i);
  y(i)=lat(i);
end
plot(x',y');
fill(x',y','g');%颜色填充
set(gca,'ygrid','on');
set(gca,'xgrid','on');
%set(gca,'XTickLabel',-180:180);
%set(gca,'YTickLabel',-90:90);
%axis([-180 180 -90 90]);%坐标范围
axis([-60 0 0 60]);%气象制导大西洋坐标范围
%axis([122 142 -12 2]);%全局航线规划
x=[];
y=[];
while(j<n-1)
for i=(num(j)+1):1:(num(j+1)-1)
  x(p)=long(i);
  y(p)=lat(i);
%[y(p) x(p)]=WGS84ToMercator(lat(i),long(i),0,0,0) ;  
 p=p+1;
end
plot(x',y');
if((j>12&&j<23)||(j>92&&j<107))
  fill(x',y','w');%颜色填充,白色
else
  fill(x',y','g');%颜色填充,白色
end
x=[];
y=[];
j=j+1;
p=1;
end
end
