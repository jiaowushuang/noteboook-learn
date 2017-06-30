%%%%%%%%求出切点坐标%%%%%%%%%%%
%输入：x,y为圆外点坐标，x0,y0为圆心
%输出：Tx,Ty为切点经纬度坐标
function [Tx,Ty]=TanPoint(x,y,x0,y0,R)
% (x-x0)^2+(y-y0)^2=((x-Tx)^2+(y-Ty)^2)+R^2;
% (x0-Tx)^2+(y0-Ty)^2=R^2;

eq1='(x-x0)^2+(y-y0)^2-((x-Tx)^2+(y-Ty)^2)-R^2';
eq2='(x0-Tx)^2+(y0-Ty)^2-R^2';
[Tx,Ty]=solve(eq1,eq2,'Tx,Ty');%解二元二次方程组
Tx=eval(Tx);%字符型转化为double
Ty=eval(Ty);%字符型转化为double
end
