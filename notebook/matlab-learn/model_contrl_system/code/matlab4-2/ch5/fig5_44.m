% Chapter 5: Figure 5.44, p. 276
%
%    Ka=30 is currently selected.  You can select Ka=60 and re-run.
%
Ka=30;
t=[0:0.01:1];
nc=[Ka*5];dc=[1];
ng=[1];dg=[1 20 0];
[n,d]=series(nc,dc,ng,dg);
[num,den]=cloop(n,d);
y=step(num,den,t);
plot(t,y), grid
xlabel('Time (sec)')
ylabel('y(t)')
