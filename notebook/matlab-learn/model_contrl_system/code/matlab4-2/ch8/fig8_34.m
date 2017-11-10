% Chapter 8: Figure 8.34, p. 449
%
%   The magnitude plot of
%
%                        0.5 s + 5
%   G(s) = ----------------------------------------
%          0.0002 s^4 + 0.0064 s^3 + 0.512 s^2 +  s
%
%   using the logspace function to generate 
%   the frequency points.
%
num=5*[0.1 1];
den=[0.0002 0.0064 0.5120 1 0];
w=logspace(-1,3,200);
[mag,phase,w]=bode(num,den,w);
semilogx(w,20*log10(mag)), grid
xlabel('Frequency [rad/sec]'), ylabel('20*log(mag) [dB]')
