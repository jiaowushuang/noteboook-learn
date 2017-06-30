%%%%%%%%����е�����%%%%%%%%%%%
%���룺x,yΪԲ������꣬x0,y0ΪԲ��
%�����Tx,TyΪ�е㾭γ������
function [Tx,Ty]=TanPoint(x,y,x0,y0,R)
% (x-x0)^2+(y-y0)^2=((x-Tx)^2+(y-Ty)^2)+R^2;
% (x0-Tx)^2+(y0-Ty)^2=R^2;

eq1='(x-x0)^2+(y-y0)^2-((x-Tx)^2+(y-Ty)^2)-R^2';
eq2='(x0-Tx)^2+(y0-Ty)^2-R^2';
[Tx,Ty]=solve(eq1,eq2,'Tx,Ty');%���Ԫ���η�����
Tx=eval(Tx);%�ַ���ת��Ϊdouble
Ty=eval(Ty);%�ַ���ת��Ϊdouble
end
