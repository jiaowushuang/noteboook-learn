% Chapter 2: Figure 2.58%   Application of the feedback function with nonunity feedback.%numg=[1]; deng=[500 0 0]; sys1=tf(numg,deng);numh=[1 1]; denh=[1 2]; sys2=tf(numh,denh);sys=feedback(sys1,sys2);sys 