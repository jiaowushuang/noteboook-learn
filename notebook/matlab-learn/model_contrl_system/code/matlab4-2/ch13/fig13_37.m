% Chapter 13: Figure 13.37, p. 784
%
%   The root locus for the sampled data system 
%
%             K (0.3678) (z+0.7189) 
%     G(z) =  --------------------- .
%                (z-1)(z+0.2400) 
%
num=[0.3678 0.2644]; den=[1 -0.76 -0.24];
x=[-1:0.1:1];y=sqrt(ones(1,length(x))-x.^2);
rlocus(num,den);grid,hold on
plot(x,y,'--',x,-y,'--')
 
