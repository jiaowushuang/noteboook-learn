% Chapter 12: Figure 12.35%%   Robust control of temperature with variations in%   the plant parameter c0.  The value of c0 is specified %   in the first line of this m-file and can be changed as %   desired to investigate the effects on the step response.%c0=10;numg=[1]; deng=[1 2*c0 c0^2]; sysg=tf(numg,deng);numgc=5*[116 1887 8260]; dengc=[1 0]; sysgc=tf(numgc,dengc);syso=series(sysgc,sysg);sys=feedback(syso,[1]);step(sys)