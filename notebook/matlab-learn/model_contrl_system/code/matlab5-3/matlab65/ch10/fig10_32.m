% Chapter 10: Figure 10.32%%   Rotor winder control compensated system Bode diagram %   with lead controller%%              1800(s+3.5)%     Gc(s) = -------------  . %                 s+25 %K=1800; numg=[1]; deng=[1 15 50 0]; sysg=tf(numg,deng);numgc=K*[1 3.5]; dengc=[1 25]; sysgc=tf(numgc,dengc);sys=series(sysgc,sysg);margin(sys);