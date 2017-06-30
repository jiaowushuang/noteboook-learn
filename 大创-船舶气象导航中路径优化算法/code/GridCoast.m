%%%%%%%%%%դ�񻯴���%%%%%%%%%%%%
function [cx1,cy1,cx2,cy2,h,hh]=GridCoast(DayHour)
hold on

%%%%����������������ɾ��ԭ��ͼ��%%%%%%%%%%%%%
% if DayHour>1.1
%     delete(h);%ɾ������
%     delete(hh);%ɾ��������ɫ
% end



if(DayHour>=1.1&&DayHour<=1.4)%��һ������
    path='oneday.nc';
end
au=ncread(path,'u10');
av=ncread(path,'v10');

X=ncread(path,'longitude');
Y=ncread(path,'latitude');

if (DayHour==1.1)
    u=au(:,:,1);%��һ��ʱ�μ�2015.01.01 00:00:00
    v=av(:,:,1);
end

if (DayHour>1.1&&DayHour<1.3)%1.2

    u=au(:,:,2);%��һ��ʱ�μ�2015.01.02 06:00:00
    v=av(:,:,2);
    
end




%%

%%%%%%%%%%%%%%%%%%%%%%%
for i=1:1:length(X)
    X(i)=X(i)-180;%��λ��[0 360]--->[-180 180]
end


for i=1:1:length(X)
    for j=1:1:length(Y)
        aa=u(i,j);
        bb=v(i,j);
        if abs(aa)>20%Ϊ�˻���ֵ��ͼ�ÿ��������������С
            aa=20;
        end
        if abs(bb)>15%Ϊ�˻���ֵ��ͼ�ÿ��������������С
            bb=15;
        end
        w(i,j)=sqrt(aa.^2+bb.^2);
        %w(i,j)=w(i,j)/2000;%��ȡ����ֵ�ر�󣬶������ж���10m/s����˽�Խ�����С1000��
    end
end
w=w';

% contourf(X,Y,w);%��ֵ��ͼ
% colorbar;%�����ɫ��
% axis([-60 0 0 60]);%��ʾ��Χ

%%
%%%%%%%%���ٴ���17.5m/s����ΪΣ������%%%%%%%%%
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
%%%%%%������%%%%%%%%

[c,h]=contour(X,Y,w,1,'r');%��ֵ��ͼ

%delete(h);



%[c,h]=contourf(X,Y,w,'r');%��ֵ��ͼ
%c=c';
axis([-60 0 0 60]);%��ʾ��Χ
%axis([-13 -11 50 53]);%��ʾ��Χ
%for i=2:1:length(c(1,:))
flagnnnum=1;

for i=1:1:length(c(1,:))
    if(c(1,i)==0.5)%��Ϊÿ��Σ�������ķָ����
        flagnn(flagnnnum)=i;
        flagnnnum=flagnnnum+1;
        
    end
end
%&&(c(1,i+1)>-60&&(c(1,i+1)<0))&&(c(2,i+1)>0&&(c(1,i+1)<60))
flagnnnummin=1;
flagnnmin=[];%���շ���С��Χ����ֵ
for i=1:1:length(flagnn)
    if((c(1,(flagnn(i)+1))>-60&&(c(1,(flagnn(i)+1))<0))&&((c(2,(flagnn(i)+1))>0&&(c(2,(flagnn(i)+1))<60))));%Ѱ�Ҿ��ȷ�Χ��-60 0��,γ�ȷ�Χ��0 60��;��ֵͷ
        flagnnmin(flagnnnummin)=flagnn(i);
        flagnnnummin=flagnnnummin+1;
        if i==length(flagnn)
            flagnnmin(flagnnnummin)=length(c(1,:))+1;
        else
            flagnnmin(flagnnnummin)=flagnn(i+1);%��ֵβ
        end
        flagnnnummin=flagnnnummin+1;
    end
    
end




%%%%%%%%%%%%%%%%%%%%%Σ���������%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
nn=1;
numflag=1;%���Ϳɫ���
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
        if(flagnnnum==13)%����������Ҫ���ϵ�����1_1
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
    end
    if(DayHour==1.2)
        if(flagnnnum==1)%����������Ҫ���ϵ�����1_1
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
    
    hh(numflag)=fill(cx,cy,'r');%��ɫ���,��ɫ,hhΪ���
    numflag=numflag+1;
    cx=[];
    cy=[];
    nn=1;
end



end