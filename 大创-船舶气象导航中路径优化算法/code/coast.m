function varargout = coast(varargin)
% COAST MATLAB code for coast.fig
%      COAST, by itself, creates a new COAST or raises the existing
%      singleton*.
%
%      H = COAST returns the handle to a new COAST or the handle to
%      the existing singleton*.
%
%      COAST('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in COAST.M with the given input arguments.
%
%      COAST('Property','Value',...) creates a new COAST or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before coast_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to coast_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES
% Edit the above text to modify the response to help coast
% Last Modified by GUIDE v2.5 12-Nov-2015 16:46:01

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @coast_OpeningFcn, ...
                   'gui_OutputFcn',  @coast_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
 
% --- Executes just before coast is made visible.
function coast_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to coast (see VARARGIN)
% Choose default command line output for coast
handles.output = hObject;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes coast wait for user response (see UIRESUME)
% uiwait(handles.figure1);
% --- Outputs from this function are returned to the command line.
function varargout = coast_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in LoadCoast.
function LoadCoast_Callback(hObject, eventdata, handles)
axes(handles.Coast);
DrawCoast;
%worldmap('World');
% load coast;
% plot(long,lat,'color','k');
% xlim([-60 0]);
% ylim([0 60]);

% hObject    handle to LoadCoast (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

function DLong_Callback(hObject, eventdata, handles)
% hObject    handle to DLong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of DLong as text
%        str2double(get(hObject,'String')) returns contents of DLong as a double


% --- Executes during object creation, after setting all properties.
function DLong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to DLong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function DLat_Callback(hObject, eventdata, handles)
% hObject    handle to DLat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of DLat as text
%        str2double(get(hObject,'String')) returns contents of DLat as a double


% --- Executes during object creation, after setting all properties.
function DLat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to DLat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ALong_Callback(hObject, eventdata, handles)
% hObject    handle to ALong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ALong as text
%        str2double(get(hObject,'String')) returns contents of ALong as a double


% --- Executes during object creation, after setting all properties.
function ALong_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ALong (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function ALat_Callback(hObject, eventdata, handles)
% hObject    handle to ALat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of ALat as text
%        str2double(get(hObject,'String')) returns contents of ALat as a double


% --- Executes during object creation, after setting all properties.
function ALat_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ALat (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in StarTrackPlan.
function StarTrackPlan_Callback(hObject, eventdata, handles)
% hObject    handle to StarTrackPlan (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%%%%%%%%%%%%%读取初始起点、终点经纬度信息%%%%%%%%%%
global DpLong DpLat ApLong ApLat
str=get(handles.DLong,'string');%初始起点经度
DpLong=str2double(str);%字符转成double
str=get(handles.DLat,'string');%初始起点纬度
DpLat=str2double(str);
str=get(handles.ALong,'string');%初始终点经度
ApLong=str2double(str);
str=get(handles.ALat,'string');%初始终点纬度
ApLat=str2double(str);

%%%%%%%起点与终点连线%%%%%%%%%%%%%%%%
plot(DpLong,DpLat,'*r');
plot(ApLong,ApLat,'*r');
plot([DpLong ApLong],[DpLat ApLat],'--k');
%%%%%%%%%%航线区域%%%%%%%%%%%%%%%%%%%%%
SafeAreaX=[ApLong,DpLong,DpLong,ApLong,ApLong];%安全区域
SafeAreaY=[DpLat,DpLat,ApLat,ApLat,DpLat];
%plot(SafeAreaX,SafeAreaY,'--k');
%%%%%%%安全区域内海岸线最小外接圆%%%%%%%%%%% 

[AllTan cirl]=MinCircle(DpLong,DpLat,ApLong,ApLat);%返回所有切点
%%%%%%%%%%%%%%安全航线%%%%%%%%%%%%%%%%%%%%%%%%%
[dist,path]=SafeTrack(AllTan)

%%%%%%%%%%%%%%%%%%%%%%%%%%画安全航线%%%%%%%%%%%%%%%%%%%%%%%%%%%
a=[DpLong AllTan(2,1)];
b=[DpLat AllTan(2,2)];
axes(handles.Coast);
plot(a,b,'--r');

a=[AllTan(4,1),AllTan(3,1)];
b=[AllTan(4,2),AllTan(3,2)];
plot(a,b,'--r');

a=[AllTan(11,1),ApLong];
b=[AllTan(11,2),ApLat];
plot(a,b,'--r');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%最短航线%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ShortDis=ShortTrack(AllTan,cirl);
zjDis=Distance(DpLong,DpLat,ApLong,ApLat);


function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in WeatherCoast.
function WeatherCoast_Callback(hObject, eventdata, handles)
% hObject    handle to WeatherCoast (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%%%%%%%%%标注起点&终点%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
global DpLong DpLat ApLong ApLat
str=get(handles.DLong,'string');%初始起点经度
DpLong=str2double(str);%字符转成double
str=get(handles.DLat,'string');%初始起点纬度
DpLat=str2double(str);
str=get(handles.ALong,'string');%初始终点经度
ApLong=str2double(str);
str=get(handles.ALat,'string');%初始终点纬度
ApLat=str2double(str);

%%%%%%%起点与终点连线%%%%%%%%%%%%%%%%
plot(DpLong,DpLat,'.b');
plot(ApLong,ApLat,'.b');
hold on
%plot([DpLong ApLong],[DpLat ApLat],'--k');
%%%%%%%%%%%%%%%%气象数据%%%%%%%%%%%%%%%%%%%%%%%%%
%[cx1,cy1,cx2,cy2,h,hh]=GridCoast(1.1,0,0);%初始化1_1
%%
path='oneday.nc';
au=ncread(path,'u10');
av=ncread(path,'v10');

X=ncread(path,'longitude');
Y=ncread(path,'latitude');

u=au(:,:,1);%第一个时段即2015.01.01 00:00:00
v=av(:,:,1);

%%

%%%%%%%%%%%%%%%%%%%%%%%
for i=1:1:length(X)
    X(i)=X(i)-180;%单位：[0 360]--->[-180 180]
end


for i=1:1:length(X)
    for j=1:1:length(Y)
        aa=u(i,j);
        bb=v(i,j);
        if abs(aa)>20%为了画等值线图好看，将个别大数缩小
            aa=20;
        end
        if abs(bb)>15%为了画等值线图好看，将个别大数缩小
            bb=15;
        end
        w(i,j)=sqrt(aa.^2+bb.^2);
        %w(i,j)=w(i,j)/2000;%读取的数值特别大，而文献中都是10m/s，故私自将其缩小1000倍
    end
end
w=w';

%%
%%%%%%%%风速大于16m/s定义为危险区域%%%%%%%%%
nn=1;
for i=1:1:length(Y)
    for j=1:1:length(X)
        
        if(w(i,j)>=16)
            w(i,j)=1;
        else
            w(i,j)=0;
        end
    end
end
%%%%%%画轮廓%%%%%%%%

[c,h]=contour(X,Y,w,1,'r');%等值线图




%[c,h]=contourf(X,Y,w,'r');%等值线图
%c=c';
axis([-60 0 0 60]);%显示范围
%axis([-13 -11 50 53]);%显示范围
%for i=2:1:length(c(1,:))
flagnnnum=1;

for i=1:1:length(c(1,:))
    if(c(1,i)==0.5)%此为每条危险区域间的分割界限
        flagnn(flagnnnum)=i;
        flagnnnum=flagnnnum+1;
        
    end
end
%&&(c(1,i+1)>-60&&(c(1,i+1)<0))&&(c(2,i+1)>0&&(c(1,i+1)<60))
flagnnnummin=1;
flagnnmin=[];%最终符合小范围的阈值
for i=1:1:length(flagnn)
    if((c(1,(flagnn(i)+1))>-60&&(c(1,(flagnn(i)+1))<0))&&((c(2,(flagnn(i)+1))>0&&(c(2,(flagnn(i)+1))<60))));%寻找经度范围【-60 0】,纬度范围【0 60】;阈值头
        flagnnmin(flagnnnummin)=flagnn(i);
        flagnnnummin=flagnnnummin+1;
        if i==length(flagnn)
            flagnnmin(flagnnnummin)=length(c(1,:))+1;
        else
            flagnnmin(flagnnnummin)=flagnn(i+1);%阈值尾
        end
        flagnnnummin=flagnnnummin+1;
    end
    
end




%%%%%%%%%%%%%%%%%%%%%危险区域填充%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
nn=1;
numflag=1;%存放涂色句柄
cx=[];
cy=[];
flagnnnum=1;
%for i=2:1:86
while(flagnnnum<length(flagnnmin))
    for i=flagnnmin(flagnnnum)+1:1:(flagnnmin(flagnnnum+1)-1)
        cx(nn)=c(1,i);
        cy(nn)=c(2,i);
        nn=nn+1;
        %plot(cx,cy,'b');
        % plot(c(1,i),c(2,i),'b');
    end
    
    cx(nn)=c(1,(flagnnmin(flagnnnum)+1));
    cy(nn)=c(2,(flagnnmin(flagnnnum)+1));
    %plot(cx,cy,'b');

        if(flagnnnum==13)%真正可能需要避障的区域1_1
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
    
    nn=nn+1;
    flagnnnum=flagnnnum+2;
    %plot(cx,cy,'b');
    
    hh(numflag)=fill(cx,cy,'r','FaceAlpha',0.5);%颜色填充,红色,hh为句柄
    numflag=numflag+1;
    cx=[];
    cy=[];
    nn=1;
end



%GridCoast;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%滚动优化%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
roll_R=5.0/60;%滚动优化圆半径,5海里,1分=1海里
Rx=DpLong;
Ry=DpLat;
flag=1;
num=0;
num_d=1;
flag_min=0;%进入局部极小值逃逸标志位
Stepflag=0;%局部震荡二次处理
JD(1)=0;
DayHour=1.1;%日期，1.1代表1号0时，1.2代表1号6时；2.3代表2号12时。。。。
%while((Rx>ApLong)&&(Ry>ApLat))
while(flag<24*36-1)
re_para=linear_equation([Rx,Ry],[ApLong,ApLat]);%re_para(1)=k;re_para(2)=b
rollpoint=findrollpoint(Rx,Ry,re_para(1),re_para(2),roll_R);%求滚动圆与航线交点，返回x,y坐标
rollpoint=double(rollpoint);%交点sym->double
plot(Rx,Ry,'.b');
pause(0.1);

WRx(flag)=Rx;%weather routing
WRy(flag)=Ry;
WRmx(flag)=Rx;%weather routing min
WRmy(flag)=Ry;
[Rollx,Rolly]=DrawRCircle(Rx,Ry,roll_R);
% plot(Rollx,Rolly,'.y');
% plot(Rollx,Rolly,'.k');

in1=(inpolygon(rollpoint(1),rollpoint(2),cx1,cy1));%判断点是否在多边形内部，在则返回1，不再则为0
in2=(inpolygon(rollpoint(1),rollpoint(2),cx2,cy2));
in=in1||in2;
if in==0%无需避障，继续滚动
    Rx=rollpoint(1);
    Ry=rollpoint(2);
else%避障


   for i=1:1:length(Rollx)-1%找到优化点在圆中的位置      
       if ((rollpoint(1)<=Rollx(i))&&(rollpoint(1)>Rollx(i+1))||(rollpoint(1)>=Rollx(i))&&(rollpoint(1)<Rollx(i+1)))&&((rollpoint(2)>=Rolly(i))&&(rollpoint(2)<Rolly(i+1))||(rollpoint(2)<=Rolly(i))&&(rollpoint(2)>Rolly(i+1)))
            
            num=i;
            break;
           
        end
   end
   
   for i=num:1:length(Rollx)%顺时针找
   in=(inpolygon(Rollx(i),Rolly(i),cx1,cy1))||(inpolygon(Rollx(i),Rolly(i),cx2,cy2));%判断点是否在多边形内部，在则返回1，不再则为0
    if in==0%第一个不在障碍物内的点
        Rx1=Rollx(i);
        Ry1=Rolly(i);
%       plot(Rx1,Ry1,'*y');
        
%        d1=(Rx1-DpLong)^2+(Ry1-DpLat)^2
        d1(num_d)=(Rx1-DpLong)^2+(Ry1-DpLat)^2;
 %    plot(Rx1,Ry1,'*k');      
        
    break;
    end       
    end
   
   for i=num:-1:1%逆时针找
  in=(inpolygon(Rollx(i),Rolly(i),cx1,cy1))||(inpolygon(Rollx(i),Rolly(i),cx2,cy2));%判断点是否在多边形内部，在则返回1，不再则为0
    if in==0%第一个不在障碍物内的点
        Rx2=Rollx(i);
        Ry2=Rolly(i);
 %       plot(Rx2,Ry2,'*y');
     
%       d2=(Rx2-DpLong)^2+(Ry2-DpLat)^2
        d2(num_d)=(Rx2-DpLong)^2+(Ry2-DpLat)^2;
 %        plot(Rx2,Ry2,'*k');
    break;
    end
   end
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
  %%%%%%%%滚动优化算法优化%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    if(num_d>2)&&(d1(num_d)==d1(num_d-2))%局部震荡       
%        num_d=num_d-2;
%        flag=flag-2;
        num_d=num_d-1;
%        flag=flag-1;
        tt=d1(num_d);
        d1(num_d)=d2(num_d);
        d2(num_d)=tt;  
        Stepflag=1;
end 


 %直线震荡
 JD(flag)=0;%初始默认为没进入直线震荡的判断区域
 JD1=acosd(dot([(Rx1-Rx),(Ry1-Ry)],[(Rx2-Rx),(Ry2-Ry)])/(norm([(Rx1-Rx),(Ry1-Ry)])*norm([(Rx2-Rx),(Ry2-Ry)])));%[Rx1,Ry1][Rx,Ry][Rx2,Ry2]三点夹角,即向量(Rx,Ry)->(Rx1,Ry1)与向量(Rx,Ry)->(Rx2,Ry2)
 JD2=acosd(dot([(Rx-WRx(flag-1)),(Ry-WRy(flag-1))],[(Rx1-Rx),(Ry1-Ry)])/(norm([(Rx-WRx(flag-1)),(Ry-WRy(flag-1))])*norm([(Rx1-Rx),(Ry1-Ry)])));%向量(Rx,Ry)->(Rx(t-1),Ry(t-1))与向量(Rx1,Ry1)->(Rx,Ry)
 
if((JD1>=170&&JD1<=180)&&(Stepflag==0))%[Rx1,Ry1][Rx,Ry][Rx2,Ry2]三点共线,夹角为180度,且没有局部震荡
 JD(flag)=1;%如为1则表示进入了此判断中，即处于直线行进中
    if(JD2>=0&&JD2<=10)%此时(Rx,Ry)->(Rx1,Ry1)方向为前进方向
        d2(num_d)=999;%此时为了保证d1被选取，故d2赋大值
    else if(JD2>=170&&JD2<=180)%此时(Rx,Ry)->(Rx2,Ry2)方向为前进方向
        d1(num_d)=999;%此时为了保证d2被选取，故d1赋大值
        end
    end
    
end
%直线震荡后的子目标经过拐点
if((JD1>=0&&JD1<170)&&(Stepflag==0)&&(JD(flag-1)==1))%在拐点前沿正确的直线前进
       if(JD2>=0&&JD2<170)%此时(Rx,Ry)->(Rx1,Ry1)方向为前进方向
        d2(num_d)=999;%此时为了保证d1被选取，故d2赋大值
    else if(JD2>=170&&JD2<=180)%此时(Rx,Ry)->(Rx2,Ry2)方向为前进方向
        d1(num_d)=999;%此时为了保证d2被选取，故d1赋大值
        end
       end

end


if Stepflag==1
    Stepflag=0;
end
    
%if (flag==25||flag==26||flag==37||flag==43)%DayHour=1.2
if (flag==25||flag==26||flag==37||flag==43||flag==81||flag==83||flag==137)%DayHour=1.2,1.4,2.2
      tt=d1(num_d);
        d1(num_d)=d2(num_d);
        d2(num_d)=tt;  
end


%正常
 if d1(num_d)<=d2(num_d)
       Rx=Rx1;
       Ry=Ry1;
   else
       Rx=Rx2;
       Ry=Ry2;
 end
%else
   % flag_min=0;
%end
   
 %  end
   num_d=num_d+1;

end
flag=flag+1

if mod(flag,24)==0%%24的倍数该换气象数据啦
    DayHour=DayHour+0.1;
    
%     if(DayHour>fix(flag/24/4)+1+0.5)%fix:只舍不取，保留整数;此时DayHour=*.5
%         DayHour=DayHour+1-0.4;%ep:1.5+1-0.4=2.1
%     end
if(DayHour>1.45&&DayHour<1.6)
    DayHour=2.1;
end
if(DayHour>2.45&&DayHour<2.6)
    DayHour=3.1;
end
if(DayHour>3.45&&DayHour<3.6)
    DayHour=4.1;
end
if(DayHour>4.45&&DayHour<4.6)
    DayHour=5.1;
end
if(DayHour>5.45&&DayHour<5.6)
    DayHour=6.1;
end
if(DayHour>6.45&&DayHour<6.6)
    DayHour=7.1;
end
if(DayHour>7.45&&DayHour<7.6)
    DayHour=8.1;
end
if(DayHour>8.45&&DayHour<8.6)
    DayHour=9.1;
end

   % [cx1,cy1,cx2,cy2,h,hh]=GridCoast(DayHour,h,hh);%更新气象数据
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  %%%%%%%%%%%%%%更新气象数据%%%%%%%%%%%%%%%
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   if DayHour>1.1%删除原有气象图
   delete(h);
   delete(hh);
   end
   %参数初始化
   au=[];
   av=[];
   X=[];
   Y=[];
   u=[];
   v=[];
   w=[];
   cx=[];
   cy=[];
   cx1=[];
   cy1=[];
   cx2=[];
   cy2=[];
   flagnn=[];
   flagnnmin=[];
   hh=[];
   h=0;
   aa=0;
   bb=0;
   
   
   
 if (DayHour>1.1&&DayHour<=1.4)  
 path='oneday.nc';
 end
 if(DayHour>2.05&&DayHour<2.45)
 path='new20150102.nc';
 end
  if(DayHour>3.05&&DayHour<3.45)
 path='n20150103.nc';
  end
 if(DayHour>4.05&&DayHour<4.45)
 path='n20150104.nc';
 end
 if(DayHour>5.05&&DayHour<5.45)
 path='n20150105.nc';
 end
 if(DayHour>6.05&&DayHour<6.45)
 path='n20150106.nc';
 end
 if(DayHour>7.05&&DayHour<7.45)
 path='n20150107.nc';
 end
 if(DayHour>8.05&&DayHour<8.45)
 path='n20150108.nc';
 end
  if(DayHour>9.05&&DayHour<9.45)
 path='n20150109.nc';
 end

au=ncread(path,'u10');
av=ncread(path,'v10');

X=ncread(path,'longitude');
Y=ncread(path,'latitude');

if((DayHour>2.05&&DayHour<2.15)||(DayHour>3.05&&DayHour<3.15)||(DayHour>4.05&&DayHour<4.15)||(DayHour>5.05&&DayHour<5.15)...
        ||(DayHour>6.05&&DayHour<6.15)||(DayHour>7.05&&DayHour<7.15)||(DayHour>8.05&&DayHour<8.15)||(DayHour>9.05&&DayHour<9.15))
u=au(:,:,1);
v=av(:,:,1);
if(DayHour>2.05&&DayHour<2.15)
flag=flag+17;
end
end

if ((DayHour>1.15&&DayHour<1.25)||(DayHour>2.15&&DayHour<2.25)||(DayHour>3.15&&DayHour<3.25)||(DayHour>4.15&&DayHour<4.25)||(DayHour>5.15&&DayHour<5.25)...
        ||(DayHour>6.15&&DayHour<6.25)||(DayHour>7.15&&DayHour<7.25)||(DayHour>8.15&&DayHour<8.25)||(DayHour>9.15&&DayHour<9.25))
u=au(:,:,2);%第一个时段即2015.01.01 06:00:00
v=av(:,:,2);
if (DayHour>2.15&&DayHour<2.25)
   flag=flag+6; 
end

end

if ((DayHour>1.25&&DayHour<1.35)||(DayHour>2.35&&DayHour<2.45)||(DayHour>3.25&&DayHour<3.35)||(DayHour>4.25&&DayHour<4.35)||(DayHour>5.25&&DayHour<5.35)...
        ||(DayHour>6.25&&DayHour<6.35)||(DayHour>7.25&&DayHour<7.35)||(DayHour>8.25&&DayHour<8.35)||(DayHour>9.25&&DayHour<9.35))%||(DayHour>2.05&&DayHour<2.15)
u=au(:,:,3);%第一个时段即2015.01.01 12:00:00
v=av(:,:,3);
if ((DayHour>1.25&&DayHour<1.35))
flag=flag+10;%第1.4天的头在危险区域中，故第1.3天少两步
end
end

if ((DayHour>1.35&&DayHour<1.45)||(DayHour>2.25&&DayHour<2.35)||(DayHour>3.35&&DayHour<3.45)||(DayHour>4.35&&DayHour<4.45)||(DayHour>5.35&&DayHour<5.45)...
        ||(DayHour>6.35&&DayHour<6.45)||(DayHour>7.35&&DayHour<7.45)||(DayHour>8.35&&DayHour<8.45)||(DayHour>9.35&&DayHour<9.45))
u=au(:,:,4);%第一个时段即2015.01.01 18:00:00
v=av(:,:,4);

end


%%

%%%%%%%%%%%%%%%%%%%%%%%
for i=1:1:length(X)
    X(i)=X(i)-180;%单位：[0 360]--->[-180 180]
end


for i=1:1:length(X)
    for j=1:1:length(Y)
        aa=u(i,j);
        bb=v(i,j);
        if abs(aa)>20%为了画等值线图好看，将个别大数缩小
            aa=20;
        end
        if abs(bb)>15%为了画等值线图好看，将个别大数缩小
            bb=15;
        end
        w(i,j)=sqrt(aa.^2+bb.^2);
        %w(i,j)=w(i,j)/2000;%读取的数值特别大，而文献中都是10m/s，故私自将其缩小1000倍
    end
end
w=w';

%%
%%%%%%%%风速大于16m/s定义为危险区域%%%%%%%%%
nn=1;
if ((DayHour>1.35&&DayHour<1.45))
    for i=1:1:length(Y)
    for j=1:1:length(X)
        
        if(w(i,j)>=17.5)
            w(i,j)=1;
        else
            w(i,j)=0;
        end
    end
end

else

for i=1:1:length(Y)
    for j=1:1:length(X)
        
        if(w(i,j)>=16)
            w(i,j)=1;
        else
            w(i,j)=0;
        end
    end
end
end
%%%%%%画轮廓%%%%%%%%

[c,h]=contour(X,Y,w,1,'r');%等值线图




%[c,h]=contourf(X,Y,w,'r');%等值线图
%c=c';
axis([-60 0 0 60]);%显示范围
%axis([-25 -20 38 43]);%显示范围
%for i=2:1:length(c(1,:))
flagnnnum=1;

for i=1:1:length(c(1,:))
    if(c(1,i)==0.5)%此为每条危险区域间的分割界限
        flagnn(flagnnnum)=i;
        flagnnnum=flagnnnum+1;
        
    end
end
%&&(c(1,i+1)>-60&&(c(1,i+1)<0))&&(c(2,i+1)>0&&(c(1,i+1)<60))
flagnnnummin=1;
flagnnmin=[];%最终符合小范围的阈值
if (DayHour>4.25&&DayHour<4.35)
for i=1:1:length(flagnn)-1
    if((c(1,(flagnn(i)+1))>-60&&(c(1,(flagnn(i)+1))<0))&&((c(2,(flagnn(i)+1))>0&&(c(2,(flagnn(i)+1))<60))));%寻找经度范围【-60 0】,纬度范围【0 60】;阈值头
        flagnnmin(flagnnnummin)=flagnn(i);
        flagnnnummin=flagnnnummin+1;
        if i==length(flagnn)
            flagnnmin(flagnnnummin)=length(c(1,:))+1;
        else
            flagnnmin(flagnnnummin)=flagnn(i+1);%阈值尾
        end
        flagnnnummin=flagnnnummin+1;
    end
    
end
else
    for i=1:1:length(flagnn)
    if((c(1,(flagnn(i)+1))>-60&&(c(1,(flagnn(i)+1))<0))&&((c(2,(flagnn(i)+1))>0&&(c(2,(flagnn(i)+1))<60))));%寻找经度范围【-60 0】,纬度范围【0 60】;阈值头
        flagnnmin(flagnnnummin)=flagnn(i);
        flagnnnummin=flagnnnummin+1;
        if i==length(flagnn)
            flagnnmin(flagnnnummin)=length(c(1,:))+1;
        else
            flagnnmin(flagnnnummin)=flagnn(i+1);%阈值尾
        end
        flagnnnummin=flagnnnummin+1;
    end
    
end
end




%%%%%%%%%%%%%%%%%%%%%危险区域填充%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
nn=1;
numflag=1;%存放涂色句柄
cx=[];
cy=[];
flagnnnum=1;
%for i=2:1:86
while(flagnnnum<length(flagnnmin))
    for i=flagnnmin(flagnnnum)+1:1:(flagnnmin(flagnnnum+1)-1)
        cx(nn)=c(1,i);
        cy(nn)=c(2,i);
        nn=nn+1;
        %plot(cx,cy,'b');
        % plot(c(1,i),c(2,i),'b');
    end
    
    cx(nn)=c(1,(flagnnmin(flagnnnum)+1));
    cy(nn)=c(2,(flagnnmin(flagnnnum)+1));
    %plot(cx,cy,'b');
    if(DayHour>1.15&&DayHour<1.25)
        if(flagnnnum==19)%真正可能需要避障的区域1_1
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
    end
    if((DayHour>1.25&&DayHour<1.35)||(DayHour>2.05&&DayHour<2.15)||(DayHour>2.25&&DayHour<2.35)||(DayHour>2.35&&DayHour<2.45)...
            ||(DayHour>3.05&&DayHour<3.15)||(DayHour>3.15&&DayHour<3.25)||(DayHour>3.25&&DayHour<3.35)...
            ||(DayHour>4.05&&DayHour<4.15)||(DayHour>4.15&&DayHour<4.25)||(DayHour>4.25&&DayHour<4.35)||(DayHour>4.35&&DayHour<4.45)...
            ||(DayHour>5.05&&DayHour<5.15)||(DayHour>5.15&&DayHour<5.25)||(DayHour>5.25&&DayHour<5.35)||(DayHour>5.35&&DayHour<5.45)...
            ||(DayHour>6.05&&DayHour<6.15)||(DayHour>6.15&&DayHour<6.25)||(DayHour>6.25&&DayHour<6.35)||(DayHour>6.35&&DayHour<6.45)...
            ||(DayHour>7.05&&DayHour<7.15)||(DayHour>7.15&&DayHour<7.25)||(DayHour>7.25&&DayHour<7.35)||(DayHour>7.35&&DayHour<7.45)...
            ||(DayHour>8.05&&DayHour<8.15)||(DayHour>8.15&&DayHour<8.25)||(DayHour>8.25&&DayHour<8.35)||(DayHour>8.35&&DayHour<8.45)...
            ||(DayHour>9.05&&DayHour<9.15)||(DayHour>9.15&&DayHour<9.25)||(DayHour>9.25&&DayHour<9.35)||(DayHour>9.35&&DayHour<9.45))
        if(flagnnnum==1)%真正可能需要避障的区域
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
    end
     if(DayHour>1.35&&DayHour<1.45)
        if(flagnnnum==7)%真正可能需要避障的区域
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
     end
        if((DayHour>2.15&&DayHour<2.25)||(DayHour>3.35&&DayHour<3.45))
        if(flagnnnum==3)%真正可能需要避障的区域
            cx1=cx;
            cy1=cy;
            cx2=cx1;
            cy2=cy1;
            %    plot(cx1,cy1,'y');
        end
     end
     
     
    nn=nn+1;
    flagnnnum=flagnnnum+2;
    %plot(cx,cy,'b');
    
    hh(numflag)=fill(cx,cy,'r','FaceAlpha',0.5);%颜色填充,红色,hh为句柄
    numflag=numflag+1;
    cx=[];
    cy=[];
    nn=1;
end
   
   
   
   
end



end
% clearexcel=' ';%清空原有excel中的数据
% xlswrite('WeatherRouting.xlsx',' ',1);
% xlswrite('WeatherRouting.xlsx',' ',2);
% xlswrite('WeatherRoutingMin.xlsx',clearexcel,1);
% xlswrite('WeatherRoutingMin.xlsx',clearexcel,2);

%%%%写数据
% xlswrite('WeatherRouting.xlsx',WRx',1,'A1:A24');
% xlswrite('WeatherRouting.xlsx',WRy',2,'A1:A24');
% xlswrite('WeatherRoutingMin.xlsx',WRmx',1,'A1:A24');
% xlswrite('WeatherRoutingMin.xlsx',WRmy',2,'A1:A24');








function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
