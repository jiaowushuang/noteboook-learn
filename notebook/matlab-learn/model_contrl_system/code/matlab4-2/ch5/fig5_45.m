% Chapter 5: Figure 5.45, p. 277
%
%    Ka=30 is currently selected.  You can select Ka=60 and re-run.
%
Ka=30;
t=[0:0.01:1];
nc=[Ka*5];dc=[1];
ng=[1];dg=[1 20 0];
[num,den]=feedback(ng,dg,nc,dc);
num=-num;
y=step(num,den,t);
plot(t,y), grid
xlabel('Time (sec)')
ylabel('y(t)')
