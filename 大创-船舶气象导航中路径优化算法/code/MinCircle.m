%%%%%%%%%%�����С���Բ%%%%%%%%
%%%%%%%%������е����꣬ԲԲ������ �뾶%%%%%%%%%%%%%
function [AllTan cirl]=MinCircle(DpLong,DpLat,ApLong,ApLat)
%%%%%%%��ȫ����%%%%%%%%%%%%
MaxLong=max(DpLong,ApLong);%���ȴ�ֵ
MinLong=min(DpLong,ApLong);%����Сֵ
MaxLat=max(DpLat,ApLat);%γ�����ֵ
MinLat=min(DpLat,ApLat);%γ����Сֵ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%�ҳ���ȫ�����ڵĺ�����%%%%%%%%%%
%%%%pos��Ϊ�ڰ�ȫ�����ڵĺ����߱��%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global DataCoast;
global long;
global lat;
global num;
len=length(lat);%����
n=1;%����������
pos=[];%��Ű�ȫ���򺣰���λ��
nn=1;
p=1;
samep=0;
%%%%%%%%%%%%%%�Ե�һ�������߽����ж�%%%%%%%%%%%%%
for i=1:1:(num(1)-1)%��һ��������
    if((long(i)>=MinLong&&long(i)<MaxLong)&&(lat(i)>=MinLat&&lat(i)<MaxLat))%����/γ���ڰ�ȫ������
        pos(p)=1;
        p=p+1;
        break;
    end
end
%%%%%%%%%%%%%%�����ຣ���߽����ж�%%%%%%%%%%%%%
while(nn<length(num))
    for i=(num(nn)+1):1:(num(nn+1)-1)
        if((long(i)>=MinLong&&long(i)<MaxLong)&&(lat(i)>=MinLat&&lat(i)<MaxLat))%����/γ���ڰ�ȫ������
            pos(p)=nn;
            p=p+1;
            nn=nn+1;%�����������ڰ�ȫ��Χ��
          break; 
        end
        if ((i==num(nn+1)-1))%����������û�ڰ�ȫ������
            i=num(nn+1);%��������forѭ��
            nn=nn+1;%�����������ڰ�ȫ��Χ��
          
        end
        
    end
    

end
%%%%%%%%%%%%%%�����һ�������߽����ж�%%%%%%%%%%%%%
for i=(num(length(num))+1):1:len%��Ǻ�����λ��
  if((long(i)>=MinLong&&long(i)<MaxLong)&&(lat(i)>=MinLat&&lat(i)<MaxLat))%����/γ���ڰ�ȫ������
        pos(p)=length(num);
        break;
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%������С���Բ%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cirl=DrawCircle(pos);%����Բ�����꣬�뾶
%%%%%%%%%%%%�����Բ���е㣬������%%%%%%%%%%%%%%%%%%%%
[TxD TyD]=TanPoint(DpLong,DpLat,cirl(2,1),cirl(2,2),cirl(2,3));%�����Բ����������
[TxA TyA]=TanPoint(ApLong,ApLat,cirl(1,1),cirl(1,2),cirl(1,3));%�յ���Բ����������
%�ĸ��е�
% plot(TxD(1),TyD(1),'.b');
% plot(TxD(2),TyD(2),'.b');
% plot(TxA(1),TyA(1),'.b');
% plot(TxA(2),TyA(2),'.b');
%��������
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
%%%%%%%%%%%%%%%%%%%%%����Բ4�������ߣ��е�%%%%%%%%%%%%%%%%%%%%%
DTan=DoubleCir(cirl(1,1),cirl(1,2),cirl(1,3),cirl(2,1),cirl(2,2),cirl(2,3));%DTan��Բ�е�����
AllTan=[TxD(1),TyD(1);TxD(2),TyD(2);DTan;TxA(1),TyA(1);TxA(2),TyA(2)];









 
 





end