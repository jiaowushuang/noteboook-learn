**学会如何设计和构造一个属于自己的微处理器；这些基本技能将为设计其他数字系统奠定坚实的基础。**

**逻辑门**：接受0和1作为输入，产生0和1作为输出；
**模块**：录用这些逻辑门构造加法器、存储器等；

数字系统的一个重要特点是其构造模块非常简单：仅包括0和1；相反设计者最大的挑战是如何将这些简单的部件组合起来构成复杂的系统；
因此如何控制复杂性是一个贯穿的主题。

**控制复杂性的艺术**
抽象：隐藏不重要的细节。一个系统可以从多个不同层面进行抽象。
约束：对设计选择的一种内在限制，通过这种限制可以更有效的在更高抽象层次上工作。使用可互换部件是约束的一种常见应用。通过将部件限定为一个误差允许范围的标准集合，可以快速的完成系统的设计和构建。
通过数字电路的约束规则，可以很容易的将组件组合成复杂的系统。
三Y原则：层次化、模块化、规整化
层次化：将系统划分为若干模块，然后更进一步划分每个模块直到这些模块可以很容易理解；
模块化：所有的模块有定义良好的功能和接口，以便于它们之间可以很容易得相互连接而不会产生意想不到的副作用；
规整化：在模块之间寻求一致，通用模块可以重复使用多次，以便于减少设计不同模块的数量。可互换部件即使如此。


**数字抽象1**：

数字抽象的优势在于设计者只关注0、1，而忽略布尔变量的物理表示。编程人员不需要了解计算机硬件的细节就可以工作；当然对硬件细节的理解使得程序员可以针对特定的计算模型来优化软件。
一个单独位没有信息；但是一组位（bit） 可以表示数字，也可以表示字母和程序。

物理变量：连续和离散之分。
状态：高电压-1；低电压-0；
信息量D：一个有N个不同状态的离散值变量的信息量由位（bit）度量；关系是：D=log2N 位；
数字系统：二进制和其他进制之分。 布尔逻辑：针对二进制变量进行逻辑操作的系统；

数制：
十进制、二进制、十六进制

字节、半字节和全字：一组位
8位、4位；微处理器处理的一块数据称为字；字的大小取决于微处理器的架构。比如64位微处理器针对64位的字进行操作。
最低有效位（权：1）；最高有效位（权：X）；当然，也有最低有效字节；最高有效字节

二进制加法
进位；数字系统常常对固定长度的数字进行操作，如果加法的结果太大，超出了数字的表示范围，将产生溢出（进位不合法）；因此通过检查最高一列是否有进位来判断是否有溢出。

有符号的二进制数：带符号位的原码和补码

带符号位的原码：在一个N位带符号位的原码数中最高位为符号位，剩下的N-1位为数值（绝对值）。符号位为0表示正数，1表示负数。
补码：二进制补码最高位的权是-2N-1，而不是2N-1。其他位的表示方法与无符号二进制数相同。可以使用加法以及0的表示唯一。

逻辑门
使用二进制变量来表示信息，当然也有对这些二进制变量进行操作的数字系统。逻辑门就是如此。
输入和输出的关系由真值表或是布尔表达式来描述。
非门、缓冲器、与门、或门、其他二输入门以及多输入门。单输出。

**数字抽象2**：
设计者必须找到一种将连续变量和离散变量联系在一起的方法。

电源电压：
最低电压0V，称为地；最高电压来自电源，一般为5V；但是可以降到3.3V、2.5V、1.8V、1.5V、1.2V等

逻辑电平和噪声容限：
图1-23

直流电压的传输特性和静态约束：

逻辑门的底层：COMS晶体管的组合

功耗：单位时间内所消耗的能量。
分动态功耗和静态功耗。动态功耗是信号在0和1之间变化过程中电容充电所耗费的能量；静态功耗是挡信号不发生变化时系统处于空闲这状态下的功耗。
**手册使用**

**引子：组合电路**

数字电路中，电路是一个处理离散值变量的网络。
电路可以看做是黑盒，包括：

- 输入端（1 or more 离散值）
- 输出端（1 or more 离散值）
- 功能规范（f : input ~output）
- 时序规范（描述输入改变时输出响应的延迟）

电路由节点和元件组成。

- 元件是子电路
- 节点是一段导线，通过电压传递离散值信号
  - 输入节点
  - 输出节点
  - 内部节点

数字电路分为组合电路和时序电路。

- 组合电路：输出仅取决于当前输入值（无记忆）
- 时序电路：输出取决于当前输入值和之前输入值（有记忆）

一个简单的函数通常有多重实现。可以根据配置和设计约束选定模块来实现组合电路。这些约束包括面积、速度、功率 和设计时间。

组合电路的构成规则：

1. 每个电路元件本身都是组合电路
2. 每个电路节点或是一个电路的输入，或是连接到外部电路的一个输出
3. 电路不包含回路：经过电路的每条路径最多只能经过每个电路节点一次

控制复杂度：

- 应用抽象和模块化原则将电路视为一个明确定义了接口和功能的黑盒
- 应用层次化原则由较小电路元件构建复杂电路
- 组合电路的构成规则应用约束原理

组合电路的功能规范常表示为：真值表和布尔表达式。

- 由真值表得到布尔表达式
- 使用布尔代数和卡诺图来化简表达式
- 通过逻辑门来实现表达式
- 分析电路的速度

变量或它的反称为项；
项的AND称为乘积项（蕴含项）；包含全部输入变量的乘积项称为最小项；
项的OR称为求和项；包含全部输入变量的求和项称为最大项。
在解释布尔表达式时，运算顺序很重要（非、与、或）。

与或范式：
可以用输出Y为TRUE的所有最小项之和的形式写出任意一个真值表的布尔表达式。与或式并不一定是最简的等式。（0为取反形式；1为真值形式）。
或与范式：
可以用输出Y为FALSE的所有最大项相与的形式写出一个任意真值表的布尔表达式。或与式并不一定是最简的等式。（1为取反形式；0为真值形式）。

布尔代数：
化简逻辑来生成较小且成本更低的电路（取决于具体的实现技术）。侧重于德摩根定理。不过这类工作软件可以很好实现。

逻辑：门（二级组合逻辑）
任何布尔表达式（逻辑函数）的**与或式**可以用系统的方法画成如下的电路原理图：**可编程逻辑阵列（PLA）**。

1. 按列画出输入，如果有需要则在相邻列之间放置逆变器提供输入信号的补
2. 画出一行与门来实现每个最小项
3. 对于每一个输出画出一个或门来连接与输出有关的最小项

多级组合逻辑
采用树的方式可以将多输入、多输出的组合电路转换成二输入、单输出的组合电路。

X和Z：非法值和浮空值

- 非法值X：当X出现在真值表中时，它表示不重要的值；当X出现在电路中时，它表示电路节点有未知值（没有初始化）或非法值（节点同时被0和1驱动：竞争：禁止区域和电路发热）。
- 浮空值Z：电路节点既没有高电平驱动也没有低电平驱动，也称为高阻态。浮空节点可能是0也可能1，也有可能是0-1之间的值（行为不稳定）。这取决于先前的状态。产生浮空节点的原因是忘记将电压连接到输入端，或者假定这个没有连接的输入为0；但这并不意味着电路出错。

三态缓冲器：有三种可能的输出状态：高电平、低电平、高阻态；输入端、输出端、使能控制端。使能有效时，正常作为一个缓冲器；使能无效时，输出被设置为高阻。
三态缓冲器常在连接多个器件的共享总线上使用。

卡诺图：图形化的化简布尔表达式的方法。布尔代数和卡诺图是两种逻辑化简的方法。最终的目标都是找出开销最低的特定的逻辑函数实现方法。
在现代工程实践中，逻辑综合在处理大问题中比人工方法更高效。卡诺图在面试中出现概率很高。

组合逻辑模块：

1. 全加器（异或：进位；与或：输出）
2. 优先级电路（输入和输出是一一对应且存在一定的顺序）
3. 复用器：根据选择信号的值从多个可能的输入中选择一个作为输出。
4. 译码器：N输入/2^N输出。其每一个输出都取决于输入的组合。因每一个输入的组合（最小项）即为一个输出值，故称为独热。

2:1复用器：

1. 可以用与或逻辑实现（二级逻辑）
2. 也可以由三态缓冲器（2个）构成；使能信号对于两个三态缓冲器不同
更宽的复用器：可以使用与或逻辑实现、也可以使用三态缓冲器或多个2:1复用器构成。三态缓冲器的使能项可以使用与门和非门构成，也可以使用译码器构成。

复用器逻辑：
复用器可以使用**查找表**的方式实现逻辑功能。也就是说，除了PLA方式外也可以使用复用器来实现逻辑功能。
一个2^N个输入的复用器可以通过将合适的输入连接到0或1的方法来实现任何N输入逻辑函数。复用器充当查找表，其中真值表中的每一行与复用器的一个输入相对应。
此外，通过改变数据输入，复用器可以重新编程来实现其他功能。

**可变输入的复用器逻辑**
**我们可以使复用器的数目减少一半，只使用2^N-1输入-复用器来实现任何N输入的逻辑函数：将一个变量以及0/1作为复用器的输入；其中变量与输出具备一定的逻辑关系**

译码器逻辑：
译码器可以和 或门一起来实现逻辑函数。当使用译码器来构造逻辑电路时，很容易将逻辑函数表示为真值表/与或式。
一个在真值表中包含M个1的N输入函数，可以通过一个N：2^N译码器和M输入或门来实现。而这个概念将应用在只读存储器上。

**组合电路的时序规范**

关心的问题：
1. 如何使用最少逻辑门在理想状态下正常工作？
2. 如何使电路运行的更快？

输出响应输入 需要一定的时间。
组合逻辑电路的时序特征包括传播延迟和最小延迟。

- 传播延迟是当输入改变直到一个或多个输出达到他们的最终值所经历的最长时间。 t_pd
- 最小延迟是当一个输入发生变化直到任何一个输出开始改变的最短时间。t_cd
**数据手册**

传播延迟和最小延迟可以由一个信号从输入到输出的路径所决定。
- 关键路径：最长的路径（限制了电路运行的速度）
- 最短路径：最短的路径（最快的路径）

组合电路的传播延迟：关键路径上的每一个元件的传播延迟之和；最小延迟：最短路径上的每个元件的最小延迟之和。

**复用器：控制关键路径与数据关键路径**
关键路径从控制信号到输出信号，所以这些电路是控制关键。因为控制信号的任何附加延迟都会增加到最坏情况下的延迟。（二级逻辑和三态缓冲器）。
关键路径从数据信号到输出信号，所以这些电路是数据关键。因为数据信号的任何附加延迟都会增加到最坏情况下的延迟。（分层实现：多级逻辑）。

选择二者的关键是：看数据输入和控制输入哪一个先到达，即输入到达时间。

最好的设计选择不仅取决于电路的关键路径和输入到达时间，而且还看功耗、成本、部件可用性等。

**毛刺或冒险**
一个输入信号的改变可能会导致多个输出信号的改变。进而导致关键路径和最小路径（DIFF）出现在同一个器件上。


- 在读取输出前只要等待传播延迟消逝，毛刺不是问题，因为输出最终会稳定在正确的值。
- 在时序图的显示是出现一个尖端脉冲。
- 可以在已有实现中增加其他的门电路来避免毛刺。

1. 当信号的变化在卡诺图中穿越两个主蕴含项的边缘时就会出现毛刺。
2. 通过在卡诺图中增加多余的蕴含项来盖住这些边缘便可以避免毛刺。

多个输入上的同时变化也会导致毛刺，但不可避免（增加硬件）。**意识到毛刺的存在即可**



**引子：时序电路**

状态：时序逻辑从先前的输入中提取的信息；它由一组状态变量位构成。宽泛的说是，状态变量包含了所有解释电路未来行为的所需的先前信息。
初始状态：当第一次给时序电路加电时，它的初始状态是未知的且不可预测；电路的每一次初始状态都可以不同。

存储器件的基本模块是一个：双稳态元件。一对反相器交叉耦合即可组成简单的双稳态元件，它没有输入、只有两个输出；由于交叉耦合反相器的输出有两种稳定状态 0或1，所以该电路称为双稳态。

交叉耦合，即I1的输入是I2的输出、反之亦然。

稳态：如果输出仅且唯一是0或1这两个值，则电路是稳定的。
非稳态：如果输出既是0又是1，则电路是非稳定的。
亚稳态：如果输出大约处于0~1之间的一半，则电路是亚稳态的。

延迟：每个元件都有自己的 工作时间/每段信息的 传输都需要时间，而这些时间在通路的表现是延迟。延迟是可以累积的，这种现象有利有弊（不敏感）。
相位：在时序电路中，相位也是有二进制 0/1表示的。所谓反相，就是取反。
信息位：具有N个稳态的元件可以表示logN位的信息；双稳态元件可以存储1位的信息，其状态包含在二进制状态变量Q中。

锁存器和触发器：提供了可以控制状态变量值的输入。

SR锁存器：由一对交叉耦合的或非门组成。所谓“控制状态变量值的输入”，是因为可以置位或复位输出（高电平有效）。值得注意的是：

- R/S同时有效：没有意义。
- R/S同时无效：Q保持原来的值不变，或是称为状态不变。
- R/S混淆时间和内容。
- 输入的全部历史可以由状态变量Q来解释；但无论过去是否置位/复位，
- 需要通过最近一次的置位/复位来确定SR锁存器的未来行为。
- 抽象与模块：有多钟方法可以构造SR锁存器（不同的逻辑门或是晶体管），但是只要满足其对应的真值表和逻辑关系的电路元件即可称为SR锁存器。

D锁存器：当输入有效时（一般高电平有效），不仅需要确定 内容是什么，而且还需要确定 何时改变。值得注意的是：

- 使内容和时间分离：数据输入D，控制下一个状态的值；时钟输入CLK，控制状态发生改变的时刻。
- 重点强调一下，时钟可以控制何时数据通过锁存器。
- CLK为0，Q保持原来的值不变；CLK为1，Q等于D（一般高电平有效）。CLK的高低电平决定触发条件，因而称为电平敏感。

透明：导通状态（D锁存器类似于缓存器）。
不透明：阻塞状态（D锁存器保持原来的状态不变、类似于存储器）。

D触发器：由 反向 时钟控制的两个背靠背的主从D锁存器组成；D触发器又称为主从触发器、正边沿触发器等。 值得注意的是：

- 从D到Q之间通路，总有一个阻塞/不透明的锁存器；因而D触发器在时钟上升沿将D复制到Q，在其他时间D触发器保持原来的状态。
- 计算D触发器的晶体管数量：（传输门实现效率更高）
  - 与非门/或非门：4
  - 非门：2
  - 与门，一个非门和一个与非门组成：6
  - SR锁存器，两个或非门：8
  - D锁存器，一个SR锁存器、两个与门、一个非门组成：22
  - D触发器，两个D锁存器和一个非门组成：46

寄存器：N位寄存器由共享一个公共CLK输入的N个触发器组成；使寄存器的所有位可以同时更新。值得注意的是：

- 寄存器是触发器的集合，用以扩展数据总线传输的位数。
- 寄存器是后续状态机的关键组件。

其他触发器

1. 带使能端的触发器：增加一个enabled的输入，用于确定在时钟沿是否载入数据。当我们需要在某些时刻（而不是在每个时钟沿）更新状态时，该触发器非常有用。实现方式可以有两种：EN控制额外的输入复用器；时钟被门控-EN。
2. 带复位端的触发器：增加一个reset的输入，用于确定状态Q是否为0。当我们需要将所有触发器设置到已知状态（0），该触发器是非常有用的。当然，带置位端的触发器也是如此。
3. 带置位/复位功能的触发器也可以带有使能输入端；当然，也可以组成N位寄存器。

门控：利用与门或是其他门的特性对信号进行控制的方法，比如使用与门的特性（只要一端输入为0，输出即为0）。
时钟门控：一般而言，在时钟上执行逻辑是不推荐的；可能使时钟延迟并导致时序错误。
输入门控：同上，只不过对象换成D。

异步复位（置位）：reset有效就可以对其复位，而与CLK无关。
同步复位（置位）：CLK && reset有效方可对其复位。这种电路中，时钟具有唯一的控制权，不可“侵犯 ”。“侵犯”包括延迟和相位的改变等。

晶体管级锁存器和触发器的设计：

**同步逻辑设计**

一些问题的时序电路

1. 非稳态电路：环形振荡器（由三个反相器环组成）；其震荡周期取决于每个反相器的传播延迟；而传播延迟又取决于制造参数和工作参数。因此其周期很难预测。
2. 竞争电路：异步电路中经常会出现竞争条件而难以掌握。之所以出现，是因为其电路的行为取决于两条通过逻辑门的路径哪条更快。这种错误极难检查。一个例子就是时钟门控。

同步时序电路

- 组合电路没有环路和竞争，输出是随输入的确定值。但是包含环路的时序电路存在不良的竞争以及不稳定的行为。
- 因此，一种解决方法是：在反馈路径中插入寄存器来断开反馈环路；于是，时序电路将转变为组合逻辑电路和寄存器的集合。寄存器包含状态，而这些状态仅仅在时钟沿到达时发生改变；即状态同步于时钟。
- 常见的同步时序电路：有限状态机和流水线。


组成规则：

- 每一个电路元件或是寄存器或是组合电路。
- 至少有一个电路元件是寄存器。
- 所有寄存器接受同一个时钟沿。
- 每个反馈环路至少插入一个寄存器。
- 流水线变种：也可能没有反馈环路。


形式化定义：通过电路的输入、输出、功能规范、时序规范可以定义一个电路。
当前状态：目前系统的状态S。
下一状态：下一个时钟沿，系统将进入的状态S'。
功能规范：在当前状态和输入的组合下，每个输出的下一个值。
时序规范：上界时间、下界时间（从时钟沿开始直到输出改变的时间段）；建立时间、保持时间（相对于时钟沿使输入达到稳定的时间段）。

异步时序电路：当两个不同时钟的系统之间进行通信 或是 在任意时刻接受输入（并发现象），异步电路非常重要。

- 宽泛的说是，进程通信和中断也是如此，因此需要内核同步；内核同步方式有：......。
- 可以推断出：异步时序电路仅仅是输入电路，但是处理电路一定是同步时序电路（采用源同步或是增加FIFO是两种熟悉的方式）。但至于输出电路就不一定。

有限状态机FSM
具有k位寄存器的电路可以处于2^k 种状态中的某一种唯一状态。有限状态机提供了系统的方法来设计给定功能规范的同步时序逻辑电路。

- 有限状态机有M个输入、N个输出和k位状态以及一个时钟信号和一个可选的复位信号。
- 两个组合逻辑块：下一个状态逻辑和输出逻辑；时序模块：存储状态的寄存器。
在每一个时钟沿，有限状态机可以进入下一个状态（根据当前状态和输入计算而来）。

FSM分有两类：

- Moore型：输出仅仅取决于当前状态。
- Mealy型：输出取决于当前状态和当前输入。

有限状态机设计实例
1. 确定设计目标。填充FSM黑盒的相应信息（输入、输出、时钟、复位（同步和异步））。
2. 状态转换图。状态转换图说明系统中的每一个可能的状态以及两个状态之间的转换（条件）。这最能体现设计功能。在状态转换图中，圆圈代表状态，圆弧代表两个状态之间的转换。在特定状态的输出值也会标记在各个状态中。
	1. 转换发生在时钟上升沿。由于时钟总是发生在同步时序逻辑电路，所以只需根据状态转换图中发生状态转换的条件便可控制何时发生状态转换。
	2. 故而，所谓装换，便是时钟作为简单控制、状态转换图才是真正指明哪里发生转换。
	3. 复位状态是FSM第一落脚点。由于初始状态是未知的，故而需要初始化控制。
	4. 若一个状态有多条分支，则这些圆弧标有触发各个状态转换的输入条件；否则便不必。

3. 状态转换表。状态转换表说明对于每一个状态和输入值，理应产生的下一个状态是何？
	1. 无关项表示下一状态不依赖于特定的输入。
	2. 可以省略复位或是可以使用带复位功能的触发器使复位后总是进入状态0，而不考虑输入。

4. 编码。为建立一个真实的电路，状态和输出必须按照二进制编码（状态编码和输出编码）。
5. 更新状态转换图为真值表；通过真值表可以直接读出与或式表示的下一个状态的布尔表达式（找1）。 
6. 卡诺图化简、观察法化简。得下一个状态方程（参量：输入、当前状态）。
7. 同样，得输出表以及输出方程（参量：当前状态）。<结合FSM类型>。
8. 绘制Moore型FSM电路图以及时序图。

状态编码
不同的选择将会产生不同的电路。
问题：如何确定一种编码，使之能产生一个逻辑门最少且传播延迟最短的电路呢？可以通过观察**使相关状态或输出共享某些位**以便选择一种适合的编码。
决策：选择二进制编码（logK）或是独热/冷编码 (K)。最佳的编码取决于具体的FSM（最好的实现选择取决于门电路和触发器的相对成本）。
- 状态的每一位都是 存储在一个触发器中。故而独热编码较二进制编码需要更多的触发器。
- 独热编码，可以使下一状态和输出逻辑更加简单。故而需要的门电路也更少。

Moore型FSM和Mealy型FSM（圆弧是一个自带顺序的加法：箭头指入方向的输入编码值 + 箭头指入方向的状态值 = 输出值）
1. 输出只取决于状态；输出标记在圆圈内、输入标记在圆弧上。
2. 输出取决于当前状态和输入；输入、输出标记在弧上。


- 两种状态机的状态序列不同。然而Mealy型FSM的输出上升要早一个周期。由于其输出直接响应输入，故而不需要等待状态变化。若Mealy型FSM的输出通过触发器产生延迟，那么其输出将与Moore型FSM无异。
- 在选择FSM设计类型时，需要考虑解释需要输出响应或 是否需要经过触发器延迟。

状态机分解
若可以将复杂的FSM分解成多个级联的更简单的FSM，则设计复杂FSM通常很方便（层次化和模块化）。

逆向工程：由电路图导出FSM
1. 检查电路，标记输入、输出、状态位
2. 写出下一个状态和输出方程
3. 创建下一个状态和输出表
4. 删除不可达状态来简化下一个状态表
5. 给每个有效状态位组合制定状态名称
6. 用状态名称重写下一个状态和输出表
7. 画出状态转换图
8. 使用文字描述FSM的功能
9. 简介的描述FSM的主要工作目标和功能

**时序逻辑的时序规范**

引子：首先，触发器在时钟沿将输入 D复制到输出Q；该过程可称为在时钟沿对D采样。如果在时钟沿上D是稳定状态，那么该动作可以清晰的定义；但是如果D在时钟沿上发生变化，则会发生什么呢？
结论：时序元件在时钟沿有孔径时间，在孔径时间内输入必须保持稳定，触发器才能产生明确定义的输出。

动态约束：正如静态约束限制使用在禁止区域外的逻辑电平，动态约束限制 在孔径时间处的输入信号应保持稳定。

- 最小延迟：当时钟上升时，输出开始发生改变：最快延迟。t_ccq
- 传播延迟：当时钟上升时，输出已达到最终值：最慢延迟。t_pcq
- 孔径时间：对输入正确采样以及输入保持稳定状态的时间总和。
  - 时钟沿前的建立时间：输入信号保持稳定
  - 时钟沿后的保持时间：输入信号保持稳定

抽象：由动态约束，可以认为时间是基于时钟周期的离散单元，等效于信号电平的离散0/1。在周期内信号可以有毛刺，也可以反复震荡；但是我们只关心时钟周期结束时的终值，并将其设置为稳定值。
因此，**以A[n]代替A(t)是很自然的事。**其中A[n]表示第n个时钟周期结束时信号A的值，A(t)表示t时刻A的值。

引入的问题1：为了稳定信号，时钟周期应该足够长，但是这限制了系统的速度；而且时钟绝不会准确的同时到达所有触发器（称之时钟偏移），这进一步增加了必要的时钟周期。
引入的问题2：真实系统中，动态约束往往不能满足。考虑异步输入下，在时钟沿很容易捕捉到一个亚稳态值；而解决这种现象的方法是在异步输入后加上一个同步器（同步器产生非法逻辑值的概率很小）

系统时序
**提高时钟频率/降低时钟周期T_c可以增加数字系统在单位时间内完成的工作量。**

在一个时钟周期内分析：
1. 建立时间/组合、时序电路的传播延迟约束：在下一时钟上升沿前

取决于建立时间，并限制组合逻辑的传播延迟（进而在关键路径上串联门电路的数目）。解决：增加时钟周期或重新设计组合逻辑来缩短传播延迟。

2. 保持时间/组合、时序电路的最小延迟约束：在当前时钟上升沿后

取决于保持时间，并限制组合逻辑的最小延迟。解决：重新设计组合逻辑来增加最小延迟。

1. 大多数触发器设计成组合逻辑的最小延迟为0，以保证保持时间约束；或是增加缓冲器（但不总是）能在不降低关键路径速度的同事解决保持时间问题。
2. 但是脉冲触发器的保持时间很长（用于高性能微处理器），这时便使用脉冲锁存器的元件。

时序分析、时钟域以及同步方式：

1. 确定最大时钟周期（通过建立时间约束），以及确定是否能满足保持时间约束：时序分析
2. 每一个时钟都有自己的适应范围，这和电路的功能以及元件的特性有关：时钟域
3. 时钟同步方式：系统同步、源同步、自同步

时钟偏移
之前我们假设时钟总是在同一时刻到达各个寄存器，但是现实是每一个寄存器的时钟到达时间总是有所不同的：时钟偏移。
时钟偏移显著的增加建立时间和保持时间，继而增加时序开销，减少组合逻辑的有效工作时间。可以将时钟偏移算在建立时间和保持时间内。

亚稳态
当触发器对孔径时间内发生变化的输入进行采样时，输出可能随时取禁止区域之间的一个电压：亚稳态
最终触发器将确定输出到0/1的稳态，但是到达稳态的分辨时间是无界的。。不过，如果等待的时间足够长，那么触发器达到一个有效逻辑电平的概率很高。
每一个双稳态元件在两个稳态之间都存在一个亚稳态。

同步器
解决异步输入导致的亚稳态问题。实质是等待。
对于大多数系统而言，等地啊一个时钟周期的同步器将提供一个安全的MTBF；在异常高速的系统中可能需要等待更多的时钟周期。（注：MTBF平均失效间隔时间：用于衡量系统的可靠性）