% Chapter 9: Figure 9.42%%   The Bode plot of%%                    0.5 %   G(s) = ---------------------------%            s^3 + 2 s^2 +  s + 0.5%%   with gain and phase margin shown on the plot using%   the margin function.%num=[0.5]; den=[1 2 1 0.5 ];sys=tf(num,den);margin(sys);