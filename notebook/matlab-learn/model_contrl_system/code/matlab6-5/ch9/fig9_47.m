% Chapter 9: Figure 9.47%%   The Bode plot of the liquid level control system with%   gain and phase margin.  The gain K must be input at the%   command level before executing this m-file.  Automatic%   labeling of the plot with gain and phase margin.%% Liquid Control System Analysis%[np,dp]=pade(1,2);sysp=tf(np,dp);num=K; d1=[1 1]; d2=[30 1]; d3=[1/9 1/3 1];den=conv(d1,conv(d2,d3));sysg=tf(num,den);sys=series(sysp,sysg);%margin(sys);