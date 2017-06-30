% //��  WGS84����ϵ����λ���֣� ת�� ī����ͶӰֱ������ϵ��x��ָ����������λ �ף�
% // ��׼γ�Ⱥͻ�׼���ȵ�λΪ�֣�ӳ�䵽ī����ͶӰԭ��
% // FlagΪ�����־��-1��ʾ�õ��ڻ�׼�����࣬0Ϊ�Զ��жϣ�1��ʾ�õ��ڻ�׼����Ҳ�
function [x,y]=WGS84ToMercator(LAT,LON,BasicLAT,BasicLON,Flag)
M_FEN2RAD=2.9088820866572159615394846141477e-4;              %�Ƕȣ���λ�֣�תΪ����
M_PI=3.1415926535897932384626433832795;                      %��

BasicLAT = BasicLAT*M_FEN2RAD;
BasicLON = BasicLON*M_FEN2RAD;
LAT = LAT*M_FEN2RAD;
LON = LON*M_FEN2RAD;

a = 6378137;%//���򳤰��ᣬ�ף�����WGS84
b = 6356752.3142;%//����̰��ᣬ�ף�����WGS84
e = sqrt(a*a - b*b) / a;%//��һƫ���ʣ�e*e = 0.006 694 379 901 3

r0 = a * cos(BasicLAT) / sqrt(1 - e*e*sin(BasicLAT)*sin(BasicLAT));	%//��׼γ�ȵ�γȦ�뾶

q = log(tan(M_PI / 4 + LAT / 2)) - e / 2 * log((1 + e*sin(LAT)) / (1 - e*sin(LAT)));%//����γ��
q0 = log(tan(M_PI / 4 + BasicLAT / 2)) - e / 2 * log((1 + e*sin(BasicLAT)) / (1 - e*sin(BasicLAT)));%//ԭ�����γ��

x = r0*(q - q0);
y = r0*M_FPI2PI(LON - BasicLON);
	
if (Flag == -1 && y>0)
    y=y- r0 * 2 * M_PI;
end
if (Flag == 1 && y < 0)
		y =y+ r0 * 2 * M_PI;
end
end


