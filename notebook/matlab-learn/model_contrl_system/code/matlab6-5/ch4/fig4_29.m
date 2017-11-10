% Chapter 4: Figure 4.29%%   English channel boring machine: step response %   for K=100 and K=20.%numg=[1]; deng=[1 1 0]; sysg=tf(numg,deng);K1=100; K2=20; num1=[11 K1]; num2=[11 K2]; den=[0 1];sys1=tf(num1,den);sys2=tf(num2,den);%% Compute closed-loop transfer functions%sysa=series(sys1,sysg); sysb=series(sys2,sysg);sysc=feedback(sysa,[1]); sysd=feedback(sysb,[1]);%% Plot step response%t=[0:0.01:2.0];[y1,t,x]=step(sysc,t); [y2,t,x]=step(sysd,t);subplot(211), plot(t,y1), title('Step Response for K=100')xlabel('Time (sec)'),ylabel('y(t)'), gridsubplot(212),plot(t,y2), title('Step Response for K=20')xlabel('Time (sec)'),ylabel('y(t)'), grid