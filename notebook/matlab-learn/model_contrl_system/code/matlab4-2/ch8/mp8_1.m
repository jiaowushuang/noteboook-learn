% Chapter 8: Frequency Response Methods
% MP8.1, p. 475
%
num=[25]; den=[1 1 25];
w=logspace(0,1,400);
[mag,phase]=bode(num,den,w); 
[y,l]=max(mag);
Mp=20*log10(y), Wr=w(l)
bode(num,den,w); 
