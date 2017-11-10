% Chapter 4: Figure 4.35, p. 211
%
% Compute the disturbance response for Ka=80.  
% Results shown in Figure 4.35 (b)
%
Ka=80; 
nf=[5000]; df=[1 1000]; ng=[1]; dg=[1 20 0];
[num,den]=feedback(ng,dg,Ka*nf,df);
num=-num;
t=[0:0.01:2];
y=step(num,den,t);
plot(t,y), grid
ylabel('y(t)'), xlabel('Time (sec)')
