% Chapter 6: Figure 6.17%%   Two-track vehicle turning control ramp response%   with a=0.6 and K=70.%t=[0:0.01:16]; u=t;numgc=[1 0.6]; dengc=[1 1]; sysgc=tf(numgc,dengc);numg=[70]; deng=[1 7 10 0]; sysg=tf(numg,deng);sysa=series(sysgc,sysg);sys=feedback(sysa,[1]);[y,T]=lsim(sys,u,t);plot(T,y,t,u,'--'), gridxlabel('Time (seconds)'), ylabel('y(t)')