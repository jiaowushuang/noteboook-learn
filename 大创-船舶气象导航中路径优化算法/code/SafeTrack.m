%%%%%%%%%安全航线%%%%%%%%%%%%%
%%%%输入：所有切点坐标%%%%%%%%
function [dist,path]=SafeTrack(AllTan)
hold on
global DpLong ApLong DpLat ApLat;

W=[Distance(DpLong,DpLat,AllTan(1,1),AllTan(1,2)),
   Distance(DpLong,DpLat,AllTan(2,1),AllTan(2,2)),
   Distance(AllTan(2,1),AllTan(2,2),AllTan(4,1),AllTan(4,2)),
   Distance(AllTan(2,1),AllTan(2,2),AllTan(8,1),AllTan(8,2)),
   Distance(AllTan(1,1),AllTan(1,2),AllTan(6,1),AllTan(6,2)),
   Distance(AllTan(1,1),AllTan(1,2),AllTan(10,1),AllTan(10,2)),
   Distance(AllTan(8,1),AllTan(8,2),AllTan(7,1),AllTan(7,2)),
   Distance(AllTan(4,1),AllTan(4,2),AllTan(3,1),AllTan(3,2)),
   Distance(AllTan(10,1),AllTan(10,2),AllTan(9,1),AllTan(9,2)),
   Distance(AllTan(6,1),AllTan(6,2),AllTan(5,1),AllTan(5,2)),
   Distance(AllTan(3,1),AllTan(3,2),AllTan(11,1),AllTan(11,2)),
   Distance(AllTan(9,1),AllTan(9,2),AllTan(11,1),AllTan(11,2)),
   Distance(AllTan(5,1),AllTan(5,2),AllTan(12,1),AllTan(12,2)),
   Distance(AllTan(7,1),AllTan(7,2),AllTan(12,1),AllTan(12,2)),
   Distance(AllTan(11,1),AllTan(11,2),ApLong,ApLat),
   Distance(AllTan(12,1),AllTan(12,2),ApLong,ApLat)];
DG = sparse([1 1 3 3 2 2 9 5 11 7 4 10 6 8 12 13],[2 3 5 9 7 11 8 4 10 6 12 12 13 13 14 14],W,14,14);  %有权的有向图
h = view(biograph(DG,[],'ShowWeights','on'))   %画图, 这个好玩
% Find shortest path from 1 to 14
[dist,path,pred] = graphshortestpath(DG,1,14);   %找顶点1到14的最短路径
% Mark the nodes and edges of the shortest path
set(h.Nodes(path),'Color',[1 0.4 0.4]);                %上色
edges = getedgesbynodeid(h,get(h.Nodes(path),'ID'));
set(edges,'LineColor',[1 0 0]);   %上色

set(edges,'LineWidth',1.5);        %上色
hold off

end