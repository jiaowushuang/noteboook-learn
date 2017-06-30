%%%%%%%%%%求出最小外接圆%%%%%%%%
%%%%%%%%输出：切点坐标，圆圆心坐标 半径%%%%%%%%%%%%%
function [AllTan cirl]=MinCircle(DpLong,DpLat,ApLong,ApLat)
%%%%%%%安全区域%%%%%%%%%%%%
MaxLong=max(DpLong,ApLong);%经度大值
MinLong=min(DpLong,ApLong);%经度小值
MaxLat=max(DpLat,ApLat);%纬度最大值
MinLat=min(DpLat,ApLat);%纬度最小值
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%找出安全区域内的海岸线%%%%%%%%%%
%%%%pos即为在安全区域内的海岸线标号%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global DataCoast;
global long;
global lat;
global num;
len=length(lat);%长度
n=1;%海岸线条数
pos=[];%存放安全区域海岸线位置
nn=1;
p=1;
samep=0;
%%%%%%%%%%%%%%对第一条海岸线进行判断%%%%%%%%%%%%%
for i=1:1:(num(1)-1)%第一条海岸线
    if((long(i)>=MinLong&&long(i)<MaxLong)&&(lat(i)>=MinLat&&lat(i)<MaxLat))%经度/纬度在安全区域内
        pos(p)=1;
        p=p+1;
        break;
    end
end
%%%%%%%%%%%%%%对其余海岸线进行判断%%%%%%%%%%%%%
while(nn<length(num))
    for i=(num(nn)+1):1:(num(nn+1)-1)
        if((long(i)>=MinLong&&long(i)<MaxLong)&&(lat(i)>=MinLat&&lat(i)<MaxLat))%经度/纬度在安全区域内
            pos(p)=nn;
            p=p+1;
            nn=nn+1;%此条海岸线在安全范围内
          break; 
        end
        if ((i==num(nn+1)-1))%本条海岸线没在安全区域内
            i=num(nn+1);%跳出本轮for循环
            nn=nn+1;%此条海岸线在安全范围内
          
        end
        
    end
    

end
%%%%%%%%%%%%%%对最后一条海岸线进行判断%%%%%%%%%%%%%
for i=(num(length(num))+1):1:len%标记海岸线位置
  if((long(i)>=MinLong&&long(i)<MaxLong)&&(lat(i)>=MinLat&&lat(i)<MaxLat))%经度/纬度在安全区域内
        pos(p)=length(num);
        break;
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%绘制最小外接圆%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cirl=DrawCircle(pos);%返回圆心坐标，半径
%%%%%%%%%%%%求点与圆的切点，画切线%%%%%%%%%%%%%%%%%%%%
[TxD TyD]=TanPoint(DpLong,DpLat,cirl(2,1),cirl(2,2),cirl(2,3));%起点做圆的两条切线
[TxA TyA]=TanPoint(ApLong,ApLat,cirl(1,1),cirl(1,2),cirl(1,3));%终点做圆的两条切线
%四个切点
% plot(TxD(1),TyD(1),'.b');
% plot(TxD(2),TyD(2),'.b');
% plot(TxA(1),TyA(1),'.b');
% plot(TxA(2),TyA(2),'.b');
%两条切线
% a=[TxD(1) DpLong];
% b=[TyD(1) DpLat];
% plot(a,b,'k');
% a=[TxD(2) DpLong];
% b=[TyD(2) DpLat];
% plot(a,b,'k');
% a=[TxA(1) ApLong];
% b=[TyA(1) ApLat];
% plot(a,b,'k');
% a=[TxA(2) ApLong];
% b=[TyA(2) ApLat];
% plot(a,b,'k');
%%%%%%%%%%%%%%%%%%%%%求两圆4条公切线，切点%%%%%%%%%%%%%%%%%%%%%
DTan=DoubleCir(cirl(1,1),cirl(1,2),cirl(1,3),cirl(2,1),cirl(2,2),cirl(2,3));%DTan两圆切点坐标
AllTan=[TxD(1),TyD(1);TxD(2),TyD(2);DTan;TxA(1),TyA(1);TxA(2),TyA(2)];









 
 





end