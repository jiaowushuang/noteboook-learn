%    W = [.41 .99 .51 .32 .15 .45 .38 .32 .36 .29 .21];    %这是权
%    DG = sparse([6 1 2 2 3 4 4 5 5 6 1],[2 6 3 5 4 1 6 3 4 3 5],W)  %有权的有向图
AllTan=[134.8430   -6.7185;
  134.2541   -5.3920;
  131.1406   -7.0957;
  133.8994   -5.4962;
  131.5267   -7.9420;
  134.5429   -6.9066;
  131.7191   -7.8163;
  133.7166   -5.6430;
  131.3617   -7.0328;
  134.3122   -6.9485;
  131.1185   -7.1093;
  131.4752   -7.9565]

DpLong=136.25 
ApLong=-5.3 
DpLat=129.0 
ApLat=-8.5
W=[Distance(DpLong,DpLat,AllTan(1,1),AllTan(1,2)),
   Distance(DpLong,DpLat,AllTan(2,1),AllTan(2,2)),
   Distance(AllTan(1,1),AllTan(1,2),AllTan(4,1),AllTan(4,2)),
   Distance(AllTan(1,1),AllTan(1,2),AllTan(8,1),AllTan(8,2)),
   Distance(AllTan(2,1),AllTan(2,2),AllTan(6,1),AllTan(6,2)),
   Distance(AllTan(2,1),AllTan(2,2),AllTan(10,1),AllTan(10,2)),
   Distance(AllTan(8,1),AllTan(8,2),AllTan(7,1),AllTan(7,2)),
   Distance(AllTan(4,1),AllTan(4,2),AllTan(3,1),AllTan(3,2)),
   Distance(AllTan(10,1),AllTan(10,2),AllTan(9,1),AllTan(9,2)),
   Distance(AllTan(6,1),AllTan(6,2),AllTan(5,1),AllTan(5,2)),
   Distance(AllTan(3,1),AllTan(3,2),AllTan(11,1),AllTan(11,2)),
   Distance(AllTan(9,1),AllTan(9,2),AllTan(11,1),AllTan(11,2)),
   Distance(AllTan(5,1),AllTan(5,2),AllTan(12,1),AllTan(12,2)),
   Distance(AllTan(7,1),AllTan(7,2),AllTan(12,1),AllTan(12,2)),
   Distance(AllTan(11,1),AllTan(11,2),ApLong,ApLat),
   Distance(AllTan(12,1),AllTan(12,2),ApLong,ApLat)]
DG = sparse([1 1 2 2 3 3 9 5 11 7 4 10 6 8 12 13],[2 3 5 9 7 11 8 4 10 6 12 12 13 13 14 14],W,14,14)  %有权的有向图
h = view(biograph(DG,[],'ShowWeights','on'))   %画图, 这个好玩
% Find shortest path from 1 to 6
[dist,path,pred] = graphshortestpath(DG,1,14)   %找顶点1到6的最短路径
% Mark the nodes and edges of the shortest path
set(h.Nodes(path),'Color',[1 0.4 0.4])                %上色
edges = getedgesbynodeid(h,get(h.Nodes(path),'ID'));
set(edges,'LineColor',[1 0 0])   %上色

set(edges,'LineWidth',1.5)        %上色