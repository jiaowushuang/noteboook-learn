%%%%%%%%%%栅格化处理%%%%%%%%%%%%
function [cx1,cy1,cx2,cy2,h,hh]=GridCoast(DayHour)
hold on

%%%%更新气象数据需先删除原有图形%%%%%%%%%%%%%
% if DayHour>1.1
%     delete(h);%删除轮廓
%     delete(hh);%删除填充的颜色
% end



if(DayHour>=1.1&&DayHour<=1.4)%第一天数据
    path='oneday.nc';
end
au=ncread(path,'u10');
av=ncread(path,'v10');

X=ncread(path,'longitude');
Y=ncread(path,'latitude');

if (DayHour==1.1)
    u=au(:,:,1);%第一个时段即2015.01.01 00:00:00
    v=av(:,:,1);
end

if (DayHour>1.1&&DayHour<1.3)%1.2

    u=au(:,:,2);%第一个时段即2015.01.02 06:00:00
    v=av(:,:,2);
    
end




%%

%%%%%%%%%%%%%%%%%%%%%%%
for i=1:1:length(X)
    X(i)=X(i)-180;%单位：[0 360]--->[-180 180]
end


for i=1:1:length(X)
    for j=1:1:length(Y)
        aa=u(i,j);
        bb=v(i,j);
        if abs(aa)>20%为了画等值线图好看，将个别大数缩小
            aa=20;
        end
        if abs(bb)>15%为了画等值线图好看，将个别大数缩小
            bb=15;
        end
        w(i,j)=sqrt(aa.^2+bb.^2);
        %w(i,j)=w(i,j)/2000;%读取的数值特别大，而文献中都是10m/s，故私自将其缩小1000倍
    end
end
w=w';

% contourf(X,Y,w);%等值线图
% colorbar;%添加颜色条
% axis([-60 0 0 60]);%显示范围

%%
%%%%%%%%风速大于17.5m/s定义为危险区域%%%%%%%%%
nn=1;
for i=1:1:length(Y)
    for j=1:1:length(X)
        
        if(w(i,j)>=16)
            w(i,j)=1;
        else
            w(i,j)=0;
        end
    end
end
%%%%%%画轮廓%%%%%%%%

[c,h]=contour(X,Y,w,1,'r');%等值线图

%delete(h);



%[c,h]=contourf(X,Y,w,'r');%等值线图
%c=c';
axis([-60 0 0 60]);%显示范围
%axis([-13 -11 50 53]);%显示范围
%for i=2:1:length(c(1,:))
flagnnnum=1;

for i=1:1:length(c(1,:))
    if(c(1,i)==0.5)%此为每条危险区域间的分割界限
        flagnn(flagnnnum)=i;
        flagnnnum=flagnnnum+1;
        
    end
end
%&&(c(1,i+1)>-60&&(c(1,i+1)<0))&&(c(2,i+1)>0&&(c(1,i+1)<60))
flagnnnummin=1;
flagnnmin=[];%最终符合小范围的阈值
for i=1:1:length(flagnn)
    if((c(1,(flagnn(i)+1))>-60&&(c(1,(flagnn(i)+1))<0))&&((c(2,(flagnn(i)+1))>0&&(c(2,(flagnn(i)+1))<60))));%寻找经度范围【-60 0】,纬度范围【0 60】;阈值头
        flagnnmin(flagnnnummin)=flagnn(i);
        flagnnnummin=flagnnnummin+1;
        if i==length(flagnn)
            flagnnmin(flagnnnummin)=length(c(1,:))+1;
        else
            flagnnmin(flagnnnummin)=flagnn(i+1);%阈值尾
        end
        flagnnnummin=flagnnnummin+1;
    end
    
end




%%%%%%%%%%%%%%%%%%%%%危险区域填充%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
nn=1;
numflag=1;%存放涂色句柄
cx=[];
cy=[];
flagnnnum=1;
%for i=2:1:86
while(flagnnnum<length(flagnnmin))
    for i=flagnnmin(flagnnnum)+1:1:(flagnnmin(flagnnnum+1)-1)
        cx(nn)=c(1,i);
        cy(nn)=c(2,i);
        nn=nn+1;
        %plot(cx,cy,'b');
        % plot(c(1,i),c(2,i),'b');
    end
    
    cx(nn)=c(1,(flagnnmin(flagnnnum)+1));
    cy(nn)=c(2,(flagnnmin(flagnnnum)+1));
    %plot(cx,cy,'b');
    if(DayHour==1.1)
        if(flagnnnum==13)%真正可能需要避障的区域1_1
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
    end
    if(DayHour==1.2)
        if(flagnnnum==1)%真正可能需要避障的区域1_1
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
    end
    
    
    nn=nn+1;
    flagnnnum=flagnnnum+2;
    %plot(cx,cy,'b');
    
    hh(numflag)=fill(cx,cy,'r');%颜色填充,红色,hh为句柄
    numflag=numflag+1;
    cx=[];
    cy=[];
    nn=1;
end



end