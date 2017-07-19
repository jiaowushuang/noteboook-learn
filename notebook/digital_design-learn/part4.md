
	* 组合电路和时序电路的设计可以从两个方面进行讨论。
	* 1 原理图层面：需通过手动简化真值表和布尔表达式的方法来寻找一套有效的逻辑门电路来实现给定的功能；并且还需手工将有效状态机转换为逻辑门。对硬件的说明通常由电路图给出。
	* 2 抽象层层面：只说明逻辑功能，并引入CAD工具来生成逻辑门电路。对硬件的说明通常由硬件描述性语言HDL给出。
	* 硬件可以由电路图和HDL两种形式表示。
	* 模块
	* 包括输入和输出的硬件块称为模块。与门，复用器和优先级电路都是模块的例子。
	* 描述模块功能的主要形式有两种：行为模型（一个模块做什么）和 结构模型（层次化：一个模块怎样由更简单的部件构造）。
	* 模块是模块化的一个应用。它定义了由输入和输出组成的接口，以及所执行的特定功能。而其编码内容对于调用该模块的其他模块并不重要。
	* SystemVerilog/.sv与VHDL/.vhd
	* 两种语言都足以描述任何的硬件系统，也都有各自的特点。现今大部分CAD工具都允许混用这两种语言
	* 不同的模块可以用不同的语言描述。而并不是所有的VHDL都被CAD工具支持。
	* 模拟和综合
	* 这是两种硬件描述性语言的主要目的所在。
	* 
		* 模拟阶段，给模块增加输入，并检查输出以便验证模块操作是否正确。
		* 综合阶段，将模块的文字描述转换为逻辑门。

	*  
	* HDL模型
	*  
	* Verilog HDL modeling language supports three kinds of modeling styles: gate-level, dataflow, and behavioral.
	* The gate-level and datafow modeling are used to model combinatorial circuits whereas the behavioral modeling is used for both combinatorial and sequential circuits
	* Gate-level Modeling
	* Verilog HDL supports built-in primitive gates modeling.
	* The gates supported are multiple-input, multiple-output, tristate, and pull gates.
	* 
		* The multiple-input gates supported are: and, nand, or, nor, xor, and xnor whose number of inputs are two or more, and has only one output.
		* The multiple-output gates supported are buf and not whose number of output is one or more, and has only one input.
		* The language also supports modeling of tri-state gates which include bufif0, bufif1, notif0, and notif1.These gates have one input, one control signal, and one output.
		* The pull gates supported are pullup and pulldown with a single output (no input) only.

	* The basic syntax for each type of gates with zero delays is as follows:
	* 
		* and | nand | or | nor | xor | xnor [instance name] (out, in1, …, inN); // [] is optional and | is selection
		* buf | not [instance name] (out1, out2, …, out2, input);
		* bufif0 | bufif1 | notif0 | notif1 [instance name] (outputA, inputB, controlC);
		* pullup | pulldown [instance name] (output A);

	* One can also have multiple instances of the same type of gate in one construct separated by a comma such as
	* 
		* and [inst1] (out11, in11, in12), [inst2] (out21, in21, in22, in23), [inst3] (out31, in31, in32, in33);

	* The language also allows the delays to be expressed when instantiating gates. The delay expressed is from input to output. The delays can be expressed in form of rise, fall, and turn-off delays; one, two, or all three types of delays can be expressed in a given instance expression. The turn-off delay is applicable to gates whose output can be turned OFF(.e.g. notif1). For example,
	* 
		* and #5 A1(Out, in1, in2); // the rise and fall delays are 5 units
		* and #(2,5) A2(out2, in1, in2); // the rise delay is 2 unit and the fall delay is 5 units
		* notif1 #(2, 5, 4) A3(out3, in2, ctrl1); //the rise delay is 2, the fall delay is 5, and the turnoff delay is 4 unit

	* The gate-level modeling is useful when a circuit is a simple combinational, as an example a multiplexer.（多路复用器）
	* Multiplexer is a simple circuit which connects one of many inputs to an output. In this part, you will create a simple 2-to-1 multiplexer and extend the design to multiple bits.
	* Dataflow Modeling
	* Dataflow modeling style is mainly used to describe combinational circuits. The basic mechanism used is the continuous assignment. （连续赋值）In a continuous assignment, a value is assigned to a data type called net.（数据类型）
	* The syntax of a continuous assignment is：
	* 
		* assign [delay] LHS_net = RHS_expression;

	* Where LHS_net is a destination net of one or more bit, and RHS_expression is an expression consisting of various operators.
	* The statement is evaluated at any time any of the source operand value changes and the result is assigned to the destination net after the delay unit. （任意）The gate level modeling examples listed in Part 1 can be described in dataflow modeling using the continuous assignment.
	* For example,
	* 
		* assign out1 = in1 & in2; // perform and function on in1 and in2 and assign the result to out1
		* assign out2 = not in1;
		* assign #2 z[0] = ~(ABAR & BBAR & EN); // perform the desired function and assign the result after 2 units

	* The target in the continuous assignment expression can be one of the following:
	* 1. A scalar net (e.g. 1st and 2nd examples above) 标量
	* 2. Vector net 向量
	* 3. Constant bit-select of a vector (e.g. 3rd example above) 索引
	* 4. Constant part-select of a vector 切片
	* 5. Concatenation of any of the above
	* Let us take another set of examples in which a scalar and vector nets are declared and used：
	* 
		* wire COUNT, CIN; // scalar net declaration
		* wire [3:0] SUM, A, B; // vector nets declaration
		* assign {COUT,SUM} = A + B + CIN; // A and B vectors are added with CIN and the result is assigned to a concatenated vector of a scalar and vector nets

	* Note that multiple continuous assignment statements are not allowed on the same destination net。（不能给同一个对象连续赋值）
	* Behavioral Modeling
	* Behavioral modeling is used to describe complex circuits. It is primarily used to model sequential circuits,but can also be used to model pure combinatorial circuits. The mechanisms (statements) for modeling the behavior of a design are:
	* 
		* initial Statements
		* always Statements
		* procedural statements

	* A module may contain an arbitrary number of initial or always statements and may contain one or more procedural statements within them.
	* 
		* They are executed concurrently （非阻塞）(i.e. to model parallelism such that the order in which statements appear in the model does not matter) with respect to each other whereas the procedural statements are executed sequentially （阻塞）(i.e. the order in which they appear does matter).

	* Both initial and always statements are executed at time=0 and then only always statements are executed during the rest of the time. The syntax is as follows:
	* 
		* initial [timing_control] procedural_statements;
		* always [timing_control] procedural_statements;//timing_control：电平触发和边沿触发

	* where a procedural_statement is one of:
	* 
		* commend_ assignment
		* conditional_ifelse_statement
		* case_statement
		* loop_statement
		* wait_statement

	* The initial statement is non-synthesizable and is normally used in testbenches. The always
	* statement is synthesizable, and the resulting circuit can be a combinatorial or sequential circuit.
	* EG:In order for the model to generate a combinatorial circuit, the always block (i) should not be edge sensitive, (ii) every branch of the conditional statement should define all output, and (iii) every case of case statement should define all output and must have a default case.(3)
	* More detailed coverage of this topic is covered in Lab 7.
	* The destination (LHS) should be of reg type; either scalar or vector. For example,
	* 
		* reg m; // scalar reg type
		* reg [7:0] switches; // vector reg type

	* Here is an example of a 2-to-1 multiplexer model. Note that begin and end statements in this example are redundant. They are included for better readability.
	* Mixed-design Style Modeling
	* Complex systems can be described in Verilog HDL using mixed-design style modeling. This modeling style supports hierarchical description（分层描述）. The design can be described using:
	* 
		* Build-in gate primitives （原语）(gate-level modeling covered in Part 1)
		* Dataflow modeling (covered in Part 2)
		* Behavioral modeling (covered in Part 3)
		* Module instantiation （例化）
		* Combinations of the above.

	* Interconnections between various objects are done through nets (of type wire)（对应于连续赋值）. Nets may be scalar or vector. For example,
	* 
		* wire y; // scalar net
		* wire [3:0] sum; // vector net

	* In absence of size, the net is assumed to be the scalar type.
	* Conclusion
	* In this lab, you created PlanAhead projects to develop various models. You implemented the design and verified the functionality in hardware as well as simulation. You learned three modeling styles. The gatelevel and dataflow modeling are primarily used for the combinatorial circuits, whereas the behavioral modeling supports both combinatorial and sequential circuits design. In this lab you used the behavioral modeling for the combinatorial circuits design. In next few labs you will be using dataflow modeling for designing various combinatorial circuits, and starting with Lab 7, you will use the behavioral modeling to
	* design sequential circuits.

