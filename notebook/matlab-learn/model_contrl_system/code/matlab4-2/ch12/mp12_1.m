% Chapter 12: Robust Control Systems
% MP12.3, p. 750
%
J=10; a=4; b=5; k2=20; 
k1=a*k2; k0=b*k2;
Ji=[1:1:30];
for i=1:length(Ji)
  numc=[k2 k1 k0]; denc=[Ji(i) 0 0 0];
  [num,den]=cloop(numc,denc);
  [mag,phase,w]=bode(num,den);
  [gm,pm]=margin(mag,phase,w);
  Pm(i)=pm;
end
plot(Ji,Pm), grid
xlabel('J'), ylabel('Phase Margin (degrees)')
