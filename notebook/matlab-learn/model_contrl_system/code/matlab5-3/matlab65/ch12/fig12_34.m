% Chapter 12: Figure 12.34%%   Step response for the PID compensated temperature controller%   for K=5.%Ks=118; a=16; b=70;K=5;K3=Ks-2, K1=a*(2+K3)-1, K2=b*(2+K3)numgc=K*[K3 K1 K2]; dengc=[1 0]; sysgc=tf(numgc,dengc);numg=[1]; deng=[1 2 1]; sysg=tf(numg,deng);%syso=series(sysgc,sysg);%sys=feedback(syso,[1]);step(sys)