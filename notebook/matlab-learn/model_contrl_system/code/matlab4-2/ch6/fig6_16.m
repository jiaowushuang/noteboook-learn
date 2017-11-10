% Chapter 6: Figure 6.16, p. 317
%
%   The a-K stability region for the two track vehicle
%   control problem.
%
a=[0.1:0.01:3.0]; K=[20:1:120];
x=0*K; y=0*K;
n=length(K); m=length(a);
for i=1:n
 for j=1:m
  q=[1, 8, 17, K(i)+10, K(i)*a(j)];
  p=roots(q);
  if max(real(p)) > 0, x(i)=K(i); y(i)=a(j-1); break; end
 end
end
plot(x,y), grid, xlabel('K'), ylabel('a')
