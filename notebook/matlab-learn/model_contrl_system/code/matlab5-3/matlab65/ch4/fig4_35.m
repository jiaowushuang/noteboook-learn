% Chapter 4: Figure 4.35%% Compute the disturbance response for Ka=80.  % Results shown in Figure 4.35 (b)%Ka=80; nf=[5000]; df=[1 1000]; sysf=tf(nf,df);ng=[1]; dg=[1 20 0]; sysg=tf(ng,dg);sys=feedback(sysg,Ka*sysf);sys=-sys;t=[0:0.01:2];y=step(sys,t); plot(t,y)ylabel('y(t)'), xlabel('Time (seconds)'), grid