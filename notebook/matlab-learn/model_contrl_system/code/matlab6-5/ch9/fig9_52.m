K=400;nc=K*[1 1]; dc=[0 1]; sysc=tf(nc,dc);nm=[5]; dm=[0.001 1]; sysm=tf(nm,dm);na=[0.05]; da=[0.05 1 0]; sysa=tf(na,da);ng=[1]; dg=[1/18850^2 2*0.3/18850 1]; sysg=tf(ng,dg);syso=series(sysc,series(sysm,series(sysa,sysg)))figure(1)margin(syso)sysc=feedback(syso,[1]);figure(2)step(sysc)