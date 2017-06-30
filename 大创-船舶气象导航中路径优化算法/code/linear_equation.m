%----------------�˺���Ϊ��֪�����󷽳̽� y = Kx + b
%----------------�������� a1(x,y) a2(x,y)
%----------------������� re_para(k,b)

function re_para = linear_equation(a1,a2)

k = (a1(2)-a2(2))/(a1(1)-a2(1));
b = a1(2) - k*a1(1);

re_para(1) = k;
re_para(2) = b;

end

