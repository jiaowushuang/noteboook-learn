function SafeT(dist,path,AllTan)
%%%%%%%%%%%������ȫ����%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global DpLong DpLat
a=[DpLong DpLat];
b=[AllTan(1,1) AllTan(1,2)];
plot(a,b,'r');
axis([122 142 -12 2]);
end