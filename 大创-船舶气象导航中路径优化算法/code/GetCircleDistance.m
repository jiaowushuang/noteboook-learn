%计算大圆航法距离
% 	// 获取两点的最短距离，以及测地线端点的方位角
% 	// 输入输出的单位为 【度】【千米】
% 	// 参考资料《Direct and inverse solutions of geodesics on the ellipsoid with application of nested equations》
% 	// Survey Review XXII. 176  April 1975
% 	// T. Vinccnty
function s=GetCircleDistance(j1,w1,j2,w2)
M_PI=3.14159265358979323846;	%π
HuToGiao=57.295779513082323;		%//deg->rad

j1=j1/HuToGiao;
w1=w1/HuToGiao;
j2=j2/HuToGiao;
w2=w2/HuToGiao;


a = 6378388.0;
f = 1.0 / 297.0;%(a-b)/a;
b = (1.0 - f)*a;%6356752;

L = j2 - j1;    %经度差 -pi~pi
if (L>M_PI)		  L = L - 2 * M_PI;
    
else if (L<-M_PI)  L = L + 2 * M_PI;
    end
end


U1 = atan((1 - f)*tan(w1));%formula 29
U2 = atan((1 - f)*tan(w2));
s_U1 = sin(U1);
c_U1 = cos(U1);
s_U2 = sin(U2);
c_U2 = cos(U2);
err = 1;
limit = 1e-12;
lambd = L;
%		s_sigma, c_sigma, sigma, s_alpha, c_alpha_2, c_2_sigma_m, C, lambd_new;
while (err>limit)
    
    %s_sigma = (lambd>0 ? 1 : -1)*sqrt(pow(c_U2*sin(lambd), 2) + pow(c_U1*s_U2 - s_U1*c_U2*cos(lambd), 2));//formula 14
    if (lambd>0 )
        flag=1;
    else
        flag=-1;
    end
%    aa=(c_U2*sin(lambd))^2
%    bb=(c_U1*s_U2 - s_U1*c_U2*cos(lambd))^ 2
    s_sigma = flag*sqrt((c_U2*sin(lambd))^2 + (c_U1*s_U2 - s_U1*c_U2*cos(lambd))^ 2);
    c_sigma = s_U1*s_U2 + c_U1*c_U2*cos(lambd);%formula 15
    sigma = atan2(s_sigma, c_sigma);%formula 16
    if (s_sigma == 0)
        s_sigma = 1e-40;
    end
    s_alpha = c_U1*c_U2*sin(lambd) / s_sigma;%formula 17
    c_alpha_2 = 1.0 - s_alpha*s_alpha;
    if (c_alpha_2 == 0)
        c_alpha_2 = 1e-40;
    end
    c_2_sigma_m = c_sigma - 2.0*s_U1*s_U2 / c_alpha_2;%formula 18
    C = f / 16.0*c_alpha_2*(4 + f*(4 - 3 * c_alpha_2));%formula 10
    lambd_new = L + (1 - C)*f*s_alpha*(sigma + C*s_sigma*(c_2_sigma_m + C*c_sigma*(-1 + 2 * c_2_sigma_m*c_2_sigma_m)));%formula 11 changed
    err = abs(lambd_new - lambd);
    lambd = lambd_new;
    
end

u_2 = c_alpha_2*(a*a - b*b) / b / b;%//formula 28
A = 1 + u_2 / 16384.0*(4096.0 + u_2*(-768.0 + u_2*(320.0 - 175.0*u_2)));%//formula 3
B = u_2 / 1024.0*(256.0 + u_2*(-128.0 + u_2*(74.0 - 47.0*u_2)));%//formula 4
d_sigma = B*s_sigma*(c_2_sigma_m + 1 / 4.0*B*(c_sigma*(-1 + 2 * c_2_sigma_m*c_2_sigma_m) -1 / 6.0*B*c_2_sigma_m*(-3 + 4 * s_sigma*s_sigma)*(-3 + 4 * c_2_sigma_m*c_2_sigma_m)));%//formula 6
s = b*A*(sigma - d_sigma);%//formula 7

psi1 = atan2(c_U2*sin(lambd), c_U1*s_U2 - s_U1*c_U2*cos(lambd));%formula 20
if (psi1<0)
    psi1 = psi1 + 2 * M_PI;
end
psi2 = atan2(c_U1*sin(lambd), -s_U1*c_U2 + c_U1*s_U2*cos(lambd));%formula 21
if (psi2<0)
    psi2 = psi2 + 2 * M_PI;
end

s=s/1000;

end