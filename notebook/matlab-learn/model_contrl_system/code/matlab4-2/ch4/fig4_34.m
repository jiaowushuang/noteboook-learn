% Chapter 4: Figure 4.34, p. 210
%
% Compute the input step response for Ka=10.  
% Results shown in Figure 4.34 (b).
% Select Ka=80 to obtain the corresponding step response.
%
Ka=10; 
nf=[5000]; df=[1 1000]; ng=[1]; dg=[1 20 0];
[num,den]=series(Ka*nf,df,ng,dg);
[n,d]=cloop(num,den);
t=[0:0.01:2];
y=step(n,d,t);
plot(t,y), grid
ylabel('y(t)'), xlabel('Time (sec)')
