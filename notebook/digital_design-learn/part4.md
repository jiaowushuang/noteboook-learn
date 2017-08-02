
**组合电路和时序电路的设计可以从两个方面进行讨论。**

1. 原理图层面：需通过手动简化真值表和布尔表达式的方法来寻找一套有效的逻辑门电路来实现给定的功能；并且还需手工将有效状态机转换为逻辑门。对硬件的说明通常由电路图给出。
2. 抽象层层面：只说明逻辑功能，并引入CAD工具来生成逻辑门电路。对硬件的说明通常由硬件描述性语言HDL给出。
3. 硬件可以由电路图和HDL两种形式表示。

模块：包括输入和输出的硬件块称为模块。与门，复用器和优先级电路都是模块的例子。

**描述模块功能的主要形式有两种：行为模型（一个模块做什么：建立输入和输出之间的关系）和 结构模型（层次化：一个模块怎样由更简单的模块构造，即例化）。**

模块是模块化的一个应用。它定义了由输入和输出组成的接口以及所执行的特定功能。而其内部编码对于调用该模块的其他模块并不重要。

	SystemVerilog/.sv与VHDL/.vhd
	两种语言都足以描述任何的硬件系统，也都有各自的特点。现今大部分CAD工具都允许混用这两种语言。
	不同的模块可以用不同的语言描述。而并不是所有的VHDL（2008）都被CAD工具支持。
	
**模拟和综合：两种硬件描述语言的主要目的。**

	模拟阶段，给模块增加 输入（测试HDL），并检查 输出 以便验证 模块操作是否正确。{在系统建立之前进行逻辑模拟是很必要的：ModelSim}。
	综合阶段，将模块的文字描述（模块HDL） 转换为 网表（如逻辑门和连线）。{逻辑综合可以进行优化以减少硬件的数量；可以是一个文本文件，也可以是原理图:Synplify Premier}

**记住：HDL是用来代表硬件的，而且并不是所有的命令都可以综合为硬件。因此必须强调HDL语言中的可综合子集。例如模拟时，在屏幕上输出结果的命令是不能转换为硬件的。**	

因此，若不能大致了解HDL要综合的硬件，则很可能不会得到理想的结果；例如创建多余的硬件和一个模拟正确但是不能在硬件实现的代码。

1. 可综合模块
2. 测试程序

**记住：应该以组合逻辑模块、寄存器、有限状态机的方式考虑系统。在开始编写代码之前，首先画出系统的结构图，区分哪些部分是组合逻辑、哪些部分是时序逻辑、或有限状态机；然后再描绘这些模块，并看看它们是如何连接的；最后使用可以描述目标硬件的正确风格为每个部分编写HDL代码。**

因此，HDL涵盖一些特定的方法来描述各种逻辑，而这些方法称为风格。

1. 如何针对每一类模块采用合适的风格编写HDL，然后如何把各个模块拼接成一个可以工作的系统。
2. **当需要描述一个特别类型的硬件时，首先需要查看相似的例子，然后修改这些例子使之适合特定的需要。**

---------------------------------------------------------------------------------------------------------------------------------------------------------
**SystemVerilog program notes:（diff Verilog）**：HDL赋值语句是并行执行的；若想顺序执行，可以使用状态机。

1. logic 变量类型首次在SystemVerilog中引入，它用于取代reg 变量。logic 变量类型可以用于任何地方（除了具有多个驱动的信号外）；具有多个驱动源（如三态总线）的信号称为 net。
	- net最常用的类型是wire 和 tri。
	- wire常用于单信号源驱动，而tri类型多用于多信号源驱动。在SystemVerilog中，logic信号取代了wire信号。在Verilog中则不然。
2. 组合逻辑（行为模型）：连续赋值语句 `assign out = in1 op in2;`
    
- 位运算符：对单位信号和多位信号总线进行操作。例如：y[N-1:0] =~ x[N-1:0];{小端}
- 缩位运算符：表示作用在一条总线上的多输入门。例如：y        =& x[N-1:0];{等效于：y = x[N-1]&x[N-2]&...x[0];}
- 条件赋值：常用于表示复用器。第一表达式{条件}？第二表达式{输出}:第三表达式{可以嵌套}
- 内部变量：把一个复杂的功能分为几个中间过程来完成。内部变量既不是输入也不是输出，只能在模块那内部使用。与局部变量类似。{在SystemVerilog中，内部变量常用logic变量类型声明}

	Z和X：HDL使用Z表示浮空值，对于描述三态缓冲器尤其有用。{总线可以由多个三态缓冲器驱动，但是最多只有一个使能有效 tri y[N-1:0] = en ? logic x[N-1:0] : N-1'bz}；HDL使用X表示一个无效的逻辑电平{若一条总线被两个使能有效的三态缓冲器（其他门）同时驱动为0和1，则结果是冲突的，以X表示}；
	
	1、logic信号只能有一个信号源驱动，而三态总线可以有多个驱动信号，故三态总线应声明为net变量。在SystemVerilog中，net变量有tri和trireg两种类型{trireg在使能信号无效后，保持先前的数值，而不是处于浮空状态}；一个模块的tri输出可以用作另一个模块的logic输入。
	
	2、在模拟开始时，状态节点（如触发器输出）会被初始化为一个未知的状态{记住：在使用输出前复位触发器}。
		
	3、若一个门接受一个浮空输出，当它不能确定正确的输出值时，会产生一个X输出{接受一个无效值X或未初始化的输入时，也是如此（记住：0&其他、1|其他例外）}
	   注：这条规则适用于net总线；相应的将（net）trix类型分成多钟{比如tri、trireg、triand/trior、tri0/tri1}。
		
	4、当模拟时看到X或Z时，基本已经说明出现了漏洞和不正确的编码{X或Z可能被电路随机解释为0或1，从而导致不可预测的行为}

- 位混合：常需要在总线的子集上操作，或是连接信号来构成总线。{}以及N{}用于连接总线、N表示拷贝。记住这里的长度概念很重要。
- 延迟：HDL的语句可以和 任意单位的延迟相关联。

	- **这在模拟时是有用的。**比如：{预测电路的工作速度：若指定了有意义的延迟；调试需要知道原因和后果时：若模拟结果时所有信号同时改变，则推断一个错误输出的原因很难}。
	- **在综合时这些延迟会被忽略；而综合器产生的组合逻辑的门延迟是由t_pd和t_cd（可变的）决定的，而t_pd和t_cd又有相应的建立时间和保持时间约束。**

	'timescale unit/precision {说明时间尺度/模拟精度}；
	在SystemVerilog中，#用于说明延迟单位的数量{放在HDL赋值语句中}

3. 组合逻辑（结构模型）：实例；同一模块的多个实例由不同的名字区分。{这里体现了层次化、规整化的例子}。

	`例化语句 如4：1复用器由三个2:1复用器实例构成`
	`mux2 lowmux(d0,d1,s[0],low);mux2 hignmux(d2,d3,s[1],hign);mux2 finmux(low,hign,s[1],y);注意：mux2必须被定义{类似于函数调用；当然也是存在库函数的：IP核/宏}`

	- **一般来说，复杂系统都是分层定义的。通过实例化主要的组件的方法可以结构化的描述系统。每一个组件由更小的模块构成，然后进一步分解直到组件足够简单，可以通过行为模型表示**
	- **避免（减少）在一个单独模块中混合使用结构和行为模型是一种好的程序风格。**


4. 时序逻辑（寄存器和锁存器的正确描述风格）

在SystemVerilog中，always语句用于描述：信号保持它们原来的值不变，直至敏感信号列表中的一个事件发生。该事件可以引起状态的改变。`always@(sensitivity list) statement`。

**always语句可以用来描述触发器、锁存器和组合逻辑（含多个），取决于敏感信号列表和执行语句。**
**因此引入 always_ff@()、always_latch@()、always_comb@()来表示特定的器件(混用则会报错)。**

- 具有合适敏感列表的代码，可以描述具有记忆能力的时序电路：`always <=`非阻塞赋值 和 `=`阻塞赋值；
- 连续赋值语句则不然，当任何一个输入发生改变时，便会重新计算并更新值，则适合描述组合电路：`assign =`。

寄存器：使用上升沿触发的D触发器（1位），包含复位寄存器、带使能端的寄存器（多位）等。**总线/信号线都是可以按照 串行/并行；同步/异步方式 传输的。**

	`always_ff(posedge clk) q[N-1:0] <= d[N-1:0];/always@(posedge clk) q[N-1:0] <= d[N-1:0];`

多寄存器（同步器）：一般同步器是由两个背靠背的触发器组成（即在时钟上升沿，d拷贝到N；同时N拷贝到q：增加亚稳态延迟）。**由于寄存器是触发器集的同步电路，需要考虑实现同步的方式：系统同步、源同步、自同步。**

	`n <= d;q <= n;相反n=d;q=n是错误的（等效于q=d）`

锁存器：透明（允许传输）和不透明（保持原来的状态）；{触发信号是高低电平，而非时钟沿}。**不是所有的综合工具都支持锁存器，故最好使用触发器；还要注意HDL代码不能表示任何意外的锁存器{if else/case漏洞}。**

	`always_latch if(clk) q<=d;/always@(clk,d) q<=d;`

组合逻辑：敏感信号列表包含了 所有的输入信号（阻塞赋值 = ）{更准确的说是等号右侧的信号（非阻塞赋值 <= ）}，正文描述了每一种可能输入组合的输出值。case和if语句必须出现在always_comb语句中{以完成更复杂的组合逻辑；相对简单的组合逻辑则使用assign完成}。

	`always_comb statment = ;/always@(*) statement = ;当always语句中的<=、=右边信号发生改变时，便重新计算并更新`。
	组合逻辑常使用阻塞赋值（顺序执行），时序逻辑常使用非阻塞赋值（并行执行）。

case语句：译码器/ROM{case-endcase含有一一对应成分}
**case语句基于输入值来执行不同的动作。若所有可能的输入组合都被定义，则case语句将表示组合逻辑；否则，它便表示时序逻辑（因为输出在未定义输入下保持原来值）。即default语句。**
在casez语句中，无关项使用？表示。

if语句：优先级电路{if-else含有顺序成分}
**若所有可能的输入组合都被定义，则case语句将表示组合逻辑；否则，它便表示时序逻辑（因为输出在未定义输入下保持原来值）。即else语句。**

阻塞和非阻塞赋值原则

1. 使用always_ff和非阻塞赋值来描述同步时序逻辑
2. 使用连续赋值语句描述简单组合逻辑
3. 使用always_comb和阻塞赋值来描述复杂组合逻辑
4. 不要在 多于1个 always语句中或者连续赋值语句中 对同一个信号赋值{最好：每个信号赋值一次}

FSM:由状态寄存器和两个组合逻辑块组成（用于存储当前状态、计算下一状态{基于输入}、计算输出）。HDL描述：状态寄存器、下一状态逻辑、输出逻辑以及状态编码。

数据类型：SystemVerilog与Verilog

1. Verilog主要使用两种数据类型：reg和wire。reg由logic代替（logic类型是reg类型的同义词，但是它避免了触发器的歧义）。
2. **Verilog中如果信号出现在always模块的 = 或 <= 的左边，那么它必须是reg；否则便是wire。** {比如，输入就不可能是reg：因为它一直在等式的右端；反之，输出就有可能是reg：因为它可能在等式的左端}。因此，reg可能代表触发器、锁存器、或是组合逻辑输出：取决于敏感信号列表以及实际的语句。
3. 输入和输出端口默认为wire类型。除非明确说明是reg。
4. 在always模块外部必须使用wire变量。反之，在SystemVerilog中放宽了assign 和分层端口实例的规则，故而logic变量可以在always模块外部使用。


**测试程序（testbench）**

测试程序包含：向 被测模块（DUT） 提供输入的语句；检查 是否产生理想的正确的输出。**输入和期待的输出模式称为测试向量。**

枚举式：

1. 实例化DUT
2. 提供输入
3. 阻塞赋值和延迟 用于提供合适的输入顺序
4. 检查模拟结果以验证是否产生正确的输出

	`module testbench1();
  	 logic  a, b, c, y;

     sillyfunction dut(a, b, c, y);

     initial begin
    	a = 0; b = 0; c = 0; #10;
    	c = 1;               #10;
    	b = 1; c = 0;        #10;
    	c = 1;               #10;
    	a = 1; b = 0; c = 0; #10;
    	c = 1;               #10;
    	b = 1; c = 0;        #10;
    	c = 1;               #10;
  	end
	endmodule`

自检式：

	module testbench2();
  	logic  a, b, c, y;

  	sillyfunction dut(a, b, c, y);

  	initial begin
    	a = 0; b = 0; c = 0; #10;
    	assert (y === 1) else $error("000 failed."); //assert语句检查条件是否成立，最终不成立则执行else语句。次不成立输出report语句的信息。
    	c = 1; #10;
    	assert (y === 0) else $error("001 failed."); //可以在不包括x/z值的信号之间使用 == ！= 进行比较；可以在包括x/z值的信号之间使用 === ！== 进行比较；
    	b = 1; c = 0; #10;
    	assert (y === 0) else $error("010 failed.");
    	c = 1; #10;
    	assert (y === 0) else $error("011 failed.");
    	a = 1; b = 0; c = 0; #10;
    	assert (y === 1) else $error("100 failed.");
    	c = 1; #10;
    	assert (y === 1) else $error("101 failed.");
    	b = 1; c = 0; #10;
    	assert (y === 0) else $error("110 failed.");
    	c = 1; #10;
    	assert (y === 0) else $error("111 failed.");
  	end
	endmodule


**在需要大量测试向量的模块中，比较好的方法是：把测试向量放在一个单独的文件中。测试程序简单的从文件中读取测试向量。{重复执行：向DUT输入测试向量，检查DUT的输出值是否与输出向量一致}**

	module testbench3();
  	logic        clk, reset;
  	logic        a, b, c, y, yexpected;                        //3位输入和1位期待的输出
  	logic [31:0] vectornum, errors;
  	logic [3:0]  testvectors[10000:0];

 	sillyfunction dut(a, b, c, y);

 	always                                                     //不含敏感信号，用做时钟源（时序DUT）
  	begin
      	clk = 1; #5; clk = 0; #5;
    end

    initial
    begin
      $readmemb/h("example.tv", testvectors);                  //读取二进制/十六进制测试文件
      vectornum = 0; errors = 0;
      reset = 1; #27; reset = 0;                               //复位信号（时序DUT）
    end

  	always @(posedge clk)                                      //提供输入：上升沿
    begin
      #1（以防止时钟和数据同时改变造成混乱）; {a, b, c, yexpected} = testvectors[vectornum];
    end

  	always @(negedge clk)
    if (~reset) begin 
      if (y !== yexpected) begin  							   //检查输出是否正确：下降沿
        $display("Error: inputs = %b", {a, b, c});
        $display("  outputs = %b (%b expected)",y, yexpected);
        errors = errors + 1;
      end
      vectornum = vectornum + 1;

      if (testvectors[vectornum] === 4'bx) begin               //直至读取结束{测试向量}
        $display("%d tests completed with %d errors", 
	           vectornum, errors);
        $finish;
      end
    end
	endmodule

example.tv:
	000_1
	001_0
	...
	111_0

**可以配置的地方：**
	
1. 修改example.tv
2. 实例化新的DUT
3. 修改一些代码行：提供输入和检查输出


-----------------------------------------------------------------------------------------------------------------------------------------------------
HDL模型
	  
Verilog HDL modeling language supports three kinds of modeling styles: gate-level, dataflow, and behavioral.
The gate-level and datafow modeling are used to model combinatorial circuits whereas the behavioral modeling is used for both combinatorial and sequential circuits。

**Gate-level Modeling：Verilog HDL supports built-in primitive gates modeling.**

The gates supported are multiple-input, multiple-output, tristate, and pull gates.

	* The multiple-input gates supported are: and, nand, or, nor, xor, and xnor whose number of inputs are two or more, and has only one output.
	* The multiple-output gates supported are buf and not whose number of output is one or more, and has only one input.
	* The language also supports modeling of tri-state gates which include bufif0, bufif1, notif0, and notif1.These gates have one input, one control signal, and one output.
	* The pull gates supported are pullup and pulldown with a single output (no input) only.

	The basic syntax for each type of gates with zero delays is as follows:

		* and | nand | or | nor | xor | xnor [instance name] (out, in1, …, inN); // [] is optional and | is selection
		* buf | not [instance name] (out1, out2, …, out2, input);
		* bufif0 | bufif1 | notif0 | notif1 [instance name] (outputA, inputB, controlC);
		* pullup | pulldown [instance name] (output A);

	One can also have multiple instances of the same type of gate in one construct separated by a comma such as
	
		* and [inst1] (out11, in11, in12), [inst2] (out21, in21, in22, in23), [inst3] (out31, in31, in32, in33);

	The language also allows the delays to be expressed when instantiating gates. The delay expressed is from input to output. The delays can be expressed in form of rise, fall, and turn-off delays; one, two, or all three types of delays can be expressed in a given instance expression. The turn-off delay is applicable to gates whose output can be turned OFF(.e.g. notif1). For example,
	
		* and #5 A1(Out, in1, in2); // the rise and fall delays are 5 units
		* and #(2,5) A2(out2, in1, in2); // the rise delay is 2 unit and the fall delay is 5 units
		* notif1 #(2, 5, 4) A3(out3, in2, ctrl1); //the rise delay is 2, the fall delay is 5, and the turnoff delay is 4 unit

The gate-level modeling is useful when a circuit is a simple combinational, as an example a multiplexer.（多路复用器）
Multiplexer is a simple circuit which connects one of many inputs to an output. In this part, you will create a simple 2-to-1 multiplexer and extend the design to multiple bits.

**Dataflow Modeling**

Dataflow modeling style is mainly used to describe combinational circuits. The basic mechanism used is the continuous assignment. （连续赋值）In a continuous assignment, a value is assigned to a data type called net.（数据类型）
	
	The syntax of a continuous assignment is：
	
		* assign [delay] LHS_net = RHS_expression;

	Where LHS_net is a destination net of one or more bit, and RHS_expression is an expression consisting of various operators.

The statement is evaluated at any time any of the source operand value changes and the result is assigned to the destination net after the delay unit. （任意）The gate level modeling examples listed in Part 1 can be described in dataflow modeling using the continuous assignment.For example,
	
		* assign out1 = in1 & in2; // perform and function on in1 and in2 and assign the result to out1
		* assign out2 = not in1;
		* assign #2 z[0] = ~(ABAR & BBAR & EN); // perform the desired function and assign the result after 2 units

The target in the continuous assignment expression can be one of the following:
	1. A scalar net (e.g. 1st and 2nd examples above) 标量
	2. Vector net 向量
	3. Constant bit-select of a vector (e.g. 3rd example above) 索引
	4. Constant part-select of a vector 切片
	5. Concatenation of any of the above

Let us take another set of examples in which a scalar and vector nets are declared and used：
	 
	wire COUNT, CIN; // scalar net declaration
	wire [3:0] SUM, A, B; // vector nets declaration
	assign {COUT,SUM} = A + B + CIN; // A and B vectors are added with CIN and the result is assigned to a concatenated vector of a scalar and vector nets

Note that multiple continuous assignment statements are not allowed on the same destination net。（不能给同一个对象连续赋值）

**Behavioral Modeling**

Behavioral modeling is used to describe complex circuits. It is primarily used to model sequential circuits,but can also be used to model pure combinatorial circuits. The mechanisms (statements) for modeling the behavior of a design are:
	
		* initial Statements
		* always Statements
		* procedural statements

A module may contain an arbitrary number of initial or always statements and may contain one or more procedural statements within them.
	
		They are executed concurrently （非阻塞）(i.e. to model parallelism such that the order in which statements appear in the model does not matter) with respect to each other whereas the procedural statements are executed sequentially （阻塞）(i.e. the order in which they appear does matter).

Both initial and always statements are executed at time=0 and then only always statements are executed during the rest of the time. The syntax is as follows:
	
		* initial [timing_control] procedural_statements;
		* always [timing_control] procedural_statements;//timing_control：电平触发和边沿触发

	    where a procedural_statement is one of:
	
		* commend_ assignment
		* conditional_ifelse_statement
		* case_statement
		* loop_statement
		* wait_statement

The initial statement is non-synthesizable and is normally used in testbenches. The always statement is synthesizable, and the resulting circuit can be a combinatorial or sequential circuit.

EG:In order for the model to generate a combinatorial circuit, the always block (i) should not be edge sensitive, (ii) every branch of the conditional statement should define all output, and (iii) every case of case statement should define all output and must have a default case.(3)More detailed coverage of this topic is covered in Lab 7.

The destination (LHS) should be of reg type; either scalar or vector. For example,
	
		* reg m; // scalar reg type
		* reg [7:0] switches; // vector reg type

Here is an example of a 2-to-1 multiplexer model. Note that begin and end statements in this example are redundant. They are included for better readability.

	* Mixed-design Style Modeling
	* Complex systems can be described in Verilog HDL using mixed-design style modeling. This modeling style supports hierarchical description（分层描述）. The design can be described using:
	
		* Build-in gate primitives （原语）(gate-level modeling covered in Part 1)
		* Dataflow modeling (covered in Part 2)
		* Behavioral modeling (covered in Part 3)
		* Module instantiation （例化）
		* Combinations of the above.

Interconnections between various objects are done through nets (of type wire)（对应于连续赋值）. Nets may be scalar or vector. For example,
	
		* wire y; // scalar net
		* wire [3:0] sum; // vector net

		In absence of size, the net is assumed to be the scalar type.

**Conclusion**

In this lab, you created PlanAhead projects to develop various models. You implemented the design and verified the functionality in hardware as well as simulation. You learned three modeling styles. The gatelevel and dataflow modeling are primarily used for the combinatorial circuits, whereas the behavioral modeling supports both combinatorial and sequential circuits design. In this lab you used the behavioral modeling for the combinatorial circuits design. 

In next few labs you will be using dataflow modeling for designing various combinatorial circuits, and starting with Lab 7, you will use the behavioral modeling todesign sequential circuits.