% //从  WGS84坐标系（单位，分） 转成 墨卡托投影直角坐标系（x轴指向正北，单位 米）
% // 基准纬度和基准经度单位为分，映射到墨卡托投影原点
% // Flag为额外标志，-1表示该点在基准点的左侧，0为自动判断，1表示该点在基准点的右侧
function [x,y]=WGS84ToMercator(LAT,LON,BasicLAT,BasicLON,Flag)
M_FEN2RAD=2.9088820866572159615394846141477e-4;              %角度（单位分）转为弧度
M_PI=3.1415926535897932384626433832795;                      %π

BasicLAT = BasicLAT*M_FEN2RAD;
BasicLON = BasicLON*M_FEN2RAD;
LAT = LAT*M_FEN2RAD;
LON = LON*M_FEN2RAD;

a = 6378137;%//地球长半轴，米，依据WGS84
b = 6356752.3142;%//地球短半轴，米，依据WGS84
e = sqrt(a*a - b*b) / a;%//第一偏心率，e*e = 0.006 694 379 901 3

r0 = a * cos(BasicLAT) / sqrt(1 - e*e*sin(BasicLAT)*sin(BasicLAT));	%//基准纬度的纬圈半径

q = log(tan(M_PI / 4 + LAT / 2)) - e / 2 * log((1 + e*sin(LAT)) / (1 - e*sin(LAT)));%//等量纬度
q0 = log(tan(M_PI / 4 + BasicLAT / 2)) - e / 2 * log((1 + e*sin(BasicLAT)) / (1 - e*sin(BasicLAT)));%//原点等量纬度

x = r0*(q - q0);
y = r0*M_FPI2PI(LON - BasicLON);
	
if (Flag == -1 && y>0)
    y=y- r0 * 2 * M_PI;
end
if (Flag == 1 && y < 0)
		y =y+ r0 * 2 * M_PI;
end
end


