% Chapter 13: Figure 13.35%%   The step response of the second-order sampled data%    system %%              0.3678z + 0.2644 %     T(z) =  ------------------  .%                z^2-z+0.6322%num=[1]; den=[1 1 0]; sysc=tf(num,den);sysd=c2d(sysc,1,'zoh');sys=feedback(sysd,[1]);T=[0:1:20]; step(sys,T) 