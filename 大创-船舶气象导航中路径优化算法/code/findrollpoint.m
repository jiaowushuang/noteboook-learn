%%%%%%%%������ΪRֱ���ϵ�һ������(x,y)
%����Ϊ��y=kx+b;
%%%%%%%%%(x-x0)^2+(y-y0)^2=R^2
%%%%���룺ֱ�߷���k,b���������a1(x0,y0)���뾶R
%���������ΪRֱ���ϵ�һ�����꣨x,y��
function  rollpoint=findrollpoint(x0,y0,k,b,R)
%rollpoint=
 syms x y;
% x0=-3.0;
% y0=-5.0;
% k=0.85;
% b=-2.45;
% R=0.5;
eq1=k*x+b-y;
eq1=subs(eq1);
eq2=(x-x0)^2+(y-y0)^2-R^2;
eq2=subs(eq2);
[x,y]=solve(eq1,eq2);
x=vpa(x,4);
y=vpa(y,4);

if x(1)<x0
   
    rollpoint(1)=x(1);
    rollpoint(2)=y(1);
else
    rollpoint(1)=x(2);
    rollpoint(2)=y(2);
end

end


