% Chapter 6: Figure 6.20, p. 321
%
%   Jump-jet control system 3-D stability region.
%
[p,z]=meshdom(1.0:0.2:10,0:.2:10);
k=p.*(p-1)./(p-1-z);
 
rc=size(k);r=rc(1);c=rc(2);
for i=1:r
for j=1:c
 if abs(z(i,j)-p(i,j)+1) < 1.0e-03
   k(i,j) = 0;
 end
 if k(i,j) < 0
   k(i,j)=0;
 end
end
end
M=[-140 25];
mesh(k,M)
 
