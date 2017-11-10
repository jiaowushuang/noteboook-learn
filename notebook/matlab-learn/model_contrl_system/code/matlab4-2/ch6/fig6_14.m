% Chapter 6: Figure 6.14, p. 315
%
%   Compute and plot the roots of the characteristic
%   equation q(s) = s^3 + 2 s^2 + 4 s + K for 0 < K < 20.
%
K=[0:0.5:20 ];
for i=1:length(K)
 q=[1 2 4 K(i)];
 p(:,i)=roots(q);
end 
plot(real(p),imag(p),'x')
grid
xlabel('real axis'), ylabel('imaginary axis')