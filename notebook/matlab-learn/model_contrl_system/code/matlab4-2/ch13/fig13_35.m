% Chapter 13: Figure 13.35, p. 782
%
%   The step response of the second-order sampled data
%    system 
%
%              0.3678z + 0.2644 
%     T(z) =  ------------------  .
%                z^2-z+0.6322
%
num=[0 0.3678 0.2644]; den=[1 -1 0.6322];
dstep(num,den);grid
 
