%%%%%%%%%%%%%%Ī����ͶӰ%%%%%%%%%%%%%%%%%%%%%
function DrawCoast
global DataCoast;
global long;
global lat;
global num;
DataCoast=importdata('coast.txt');%��ȡ���������ݣ�Ϊ�˶�ȡ����������߼���9999����־λ
long=DataCoast(:,2);%����
lat=DataCoast(:,1);%γ��
len=length(lat);%����
n=1;%����������
j=1;
p=1;
%figure;
hold on;%������ͼʱ��
for i=1:1:len%��Ǻ�����λ��
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
fill(x',y','g');%��ɫ���
set(gca,'ygrid','on');
set(gca,'xgrid','on');
%set(gca,'XTickLabel',-180:180);
%set(gca,'YTickLabel',-90:90);
%axis([-180 180 -90 90]);%���귶Χ
axis([-60 0 0 60]);%�����Ƶ����������귶Χ
%axis([122 142 -12 2]);%ȫ�ֺ��߹滮
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
  fill(x',y','w');%��ɫ���,��ɫ
else
  fill(x',y','g');%��ɫ���,��ɫ
end
x=[];
y=[];
j=j+1;
p=1;
end
end
