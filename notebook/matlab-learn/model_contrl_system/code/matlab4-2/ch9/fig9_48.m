% Chapter 9: Figure 9.48, p. 526
%
%   Remotely controlled vehicle closed-loop system
%   Bode plot for K=4.44, 10, and 20.
%
w=logspace(0,1,200); K=20;
%
for i=1:3
 numgc=K*[1 2]; dengc=[1 1];
 numg=[1]; deng=[1 2 4];
 [nums,dens]=series(numgc,dengc,numg,deng);
 [num,den]=cloop(nums,dens);
 [mag,phase,w]=bode(num,den,w);
 if i==1, mag1=mag; phase1=phase; K=10; end
 if i==2, mag2=mag; phase2=phase; K=4.44; end
 if i==3, mag3=mag; phase3=phase; end
end
%
loglog(w,mag1,'-',w,mag2,'-',w,mag3,'-'),grid
xlabel('Frequency (rad/sec)'), ylabel('mag')
 
