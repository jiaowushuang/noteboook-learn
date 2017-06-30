%ÏÞÖÆµ½-¦Ð~¦Ð
function y=M_FPI2PI(x)
M_PI=3.1415926535897932384626433832795;                      %¦Ð

if x<0
    flag=1;
else
    flag=0;
end

xx=x/2.0/M_PI+0.5-flag;
if xx<1
   xx=0;
else
    xx=1;
end
    
xx=xx*2*M_PI;
y=x-xx;
end