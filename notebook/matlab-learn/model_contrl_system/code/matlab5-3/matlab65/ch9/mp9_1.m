% Chapter 9: Stability in the Frequency Domain% MP9.1%num=[100]; den=[1 4 10]; sys=tf(num,den);[Gm,Pm,Wcg,Wcp]=margin(sys);Gm,Pm  