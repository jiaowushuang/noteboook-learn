% Chapter 10: Figure 10.30%%   Rotor winder control system transient response%   for a simple gain controller with K=50, 100, 200, %   and 300.%K=[50 100 200 500]; numg=[1]; deng=[1 15 50 0]; sysg=tf(numg,deng);t=[0:0.01:5];for i=1:4    sys=feedback(K(i)*sysg,[1]);    y=step(sys,t);    Ys(:,i)=y;endplot(t,Ys(:,1),t,Ys(:,2),t,Ys(:,3),t,Ys(:,4))gridxlabel('Time (seconds)'), ylabel('y(t)')