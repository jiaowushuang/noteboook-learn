
- 体系结构是程序员眼中的计算机，由指令集（汇编语言）和操作数地址（寄存器和存储器）来定义。
- 指令包含 操作和操作数，其中操作数取自存储器、寄存器以及指令自身{即：常数}
- 硬件只能理解二进制信息，故指令需要编码为二进制数，称为机器语言
- 微处理器是一个可以读并执行机器语言指令的数字系统
- 不同体系结构的指令集像方言。因为基本指令{加法、减法、跳转、对存储器和寄存器的操作}在不同体系结构中都有定义。
- 体系结构都有不同的硬件实现{寄存器、存储器、ALU和其他模块组成微处理器的特定方式 称为微体系结构}

MIPS体系结构设计的4个准则：

1. 简单的设计有助于规整化
2. 使常用的功能加速
3. 越小的设计便越快
4. 良好的设计依赖于良好的折中方法

--------------------------------------------------------------------------

**汇编语言**

指令
{助记符（操作类型） 目的操作数 源操作数} 例如：加法a=b+c;等效于add a,b,c

**简单的设计有助于规整化：**一致的指令格式{除了助记符外，其他基本相同}
**使常用的功能加速：**固定数量的操作数{更复杂的操作可以转化多条MIPS指令} 例如：复杂操作a=b+c-d;等效于sub t,c,d add a,b,t{引入中间变量}因为MIPS指令集仅仅包含一些常用功能的指令，很小{指令操作和操作数的译码硬件复杂度简单、快速}，因而常见的情况会较快执行。

1. RISC：MIPS{例如：CISC字符串移动指令很可能需要上百条RISC的简单指令}
2. CISC：x86-64{例如：CISC实现复杂指令的成本在于增加硬件却降低简单指令的执行速度}

-------------------------------------------------------------------------

操作数
{寄存器、存储器、常数}：使用不同的位置存放操作数 可以优化性能和存储容量；速度：常数/寄存器 > 存储器；容量：常数/寄存器 < 存储器
**计算机只能处理二进制数，不可处理变量名；因此，指令需要从一个物理地址中取出二进制数据{操作数}。**

寄存器：用于存放 常用操作数；MIPS定义32个寄存器，称为寄存器文件。其中使用18个寄存器 存储变量{$s0~$s7和$t0~$t9}。

	1. 以$s开始的寄存器称为 保存寄存器{存储诸如a,b,c这类变量 或是 用于函数调用}
	2. 以$t开始的寄存器称为 临时寄存器{存储诸如t这类的中间变量}
	
![](http://i.imgur.com/T2xe7dx.jpg)

**越小的设计便越快：**寄存器越少访问、越少数量、速度越快。而且小寄存器文件往往使用小SRAM阵列{意味着使用小译码器、位线连接到相对少的存储单元}，进而拥有更短的关键路径。
例如：加法a=b+c;等效于add $s0,$s1,$s2{a,b,c} / 复杂操作a=b+c-d;sub $t0,$s2,$s3 add $s0,$s1,$t0

存储器：数据字的阵列{这里采用32位地址和32位数据字长}

	1. MIPS采用 字节寻址存储器{存储器的每一字节都对应一个地址，由于32位字包含4个字节，所以每一个字地址都是4的倍数}
	2. X86 采用 字寻址存储器{存储器的每一字都对应一个地址}。

	MIPS指令

	1. lw装入字指令将存储器的字数据装入到寄存器中;lw $s3,8($0)
	2. sw存储字指令从寄存器向存储器写数据字;lw $s7,4($0)
	3. lb和sb指令用来装入和存储字节
	4. 字节存储器的组织方式有大端、小端两种：两种格式的字地址相同，但是不同的是字节地址{从MSB到LSB，大端是地址增加；小端是地址减小}。不同端的计算机在共享数据时有点麻烦。
	5. 指定内存有效地址： 基地址与偏移量的和{基地址为任何寄存器，写在括号内；偏移量是一个常数，写在括号前，可以使十进制或十六进制}。
	6. 字对齐：lw和sw的字地址必须能够被4整除；当然lb和sb的字节地址是不需要字对齐的。

常数/立即数：因为常数值可以被指令立即访问，而不需要通过访问寄存器或存储器来得到，故称为立即数。

	MIPS指令

	1. addi是一个以立即数为操作数的命令{将立即数与寄存器的值相加} 例如：a=a+4;等效于addi $s0,$s0,4
	2. 指令中的立即数采用16位**补码**形式。为简单起见，MIPS体系没有subi指令

**良好的设计依赖于良好的折中方法：**由于add和sub指令使用3个寄存器操作数，而lw和sw使用2个寄存器操作数和1个常数。指令格式的不同使得lw和sw违反**简单的设计有助于规整化**的原则，但是如上。单指令格式可能简洁，但是缺乏弹性。

	指令格式{汇编语言}

	1. 3个寄存器操作数
	2. 2个寄存器操作数和1个16位立即数
	3. 1个26位立即数，但没有寄存器操作数

-----------------------------------------------------------------------------------------------
	
**机器语言**

**简单的设计有助于规整化：**将所有指令 编码为存储器中的字{32位}，变长指令将增加更多的复杂性；当然也应使用单指令格式，但是过于简单也有太多限制。

	指令格式{机器语言}（一一对应）

	1. R类型
	2. I类型
	3. J类型 

R类型指令

1. 机器指令字段：op(6),rs(5),rt(5),rd(5),shamt(5),funct(6){按顺序}
2. 操作编码：op{操作码},funct{函数}：所有R指令的操作码都为0，特定R指令由funct字段指定
3. 操作数编码：rs(源),rt(源),rd(目的)。寄存器文件的编码用于此处。例如：$s0编码为16，则可将16赋予到操作数编码中。2^5=32
4. shamt仅用于移位操作，用于移位数。2^5=32
5. 汇编与机器的对应关系：add $s0,$s1,$s2 {顺序：op,rd,rs,rt}

**所有的字段值都是十进制，但是最终都必须转化为二进制/十六进制。**

I类型指令

1. 机器指令字段：op(6),rs(5),rt(5),imm(16){按顺序}
2. 操作编码：op{操作码}：所有I指令的特定操作由op决定
3. 操作数编码：rs(源/目的),rt(目的/源),imm(源)
4. 汇编与机器的对应关系： addi $s0,$s1,5 {顺序：op,rt,rs,imm}
5. 16位立即数{转32位}：逻辑操作以及其他的无符号操作（例如：lbu装入无符号字节）{0扩展：无符号数}；算术以及其他操作{符号扩展：有符号数}

J类型指令

1. 仅用于跳转指令
2. 操作编码：op(6)
3. 操作数编码：addr(26)

解释机器语言代码：第一步是针对op。若op=0，则是R类型；若op=其他，则是I或J类型

存储程序：与其他二进制数一样，指令{从机器语言的角度看：32位数}是存储在存储器中的。

> 运行一个新的程序不需要花费大量的时间对硬件重新装配，只需要将一个新的程序写入到存储器中。这就是通用的计算能力。不需特定的硬件，仅仅改变存储程序便可以运行多钟应用程序。
> 在MIPS中，指令一般从地址0x00400000开始存储。记住字节寻址。
> **存储程序中的指令可以从存储器中取出，交由处理器执行。而复杂程序都可以简化为一系列存储器读和指令执行。**

存储程序执行：处理器从存储器中顺序的取出指令，然后数字电路硬件解码和执行取出的指令。{当前指令的地址 存储在程序计数器PC的寄存器中}。首先OS将PC值设置为0x00400000，然后将这个地址的指令读出，并执行；之后，将PC值加4，接着取出改地址的指令，重复执行。

> 微处理器的体系结构状态：保存程序的状态{MIPS：由寄存器文件和PC组成}。

若OS在程序运行的某一时刻，保存体系结构状态，那么就可以中断该程序来做其他事；之后恢复状态，使得被中断的程序可以继续执行。

--------------------------------------------------------------------------

**编程：算术和逻辑操作、if/else语句、for/while循环、数组下标和函数调用等转换为MIPS汇编代码**

算术/逻辑指令{基础}
	
	1. 逻辑指令:and,or,xor,nor{寄存器：按位操作}；andi,ori,xori{立即数：按位操作}
	2. 移位操作:sll(逻辑左移),srl(逻辑右移),sra(算术右移) < s:移位；l/r:左右移；l/a:逻辑算术 >至于可变移位指令不必考虑
	3. 常数赋值：addi{为16位常数赋值}（加0）；lui{立即数装入高16位}和ori{为32位常数(0x6d6d4d4d)赋值}（lui $s0,0x6d6d ori $s0,$s0,0x4d4d）
	4. 乘法和除法指令：mult/div $s0,$s1；结果寄存器hi{乘法高32位/除法余数},lo{乘法低32位/除法商};特殊乘法:mul $s1,$s2,$s3{32位结果存储在$s1中}


分支指令：

顺序执行指令，是指程序计数器执行一条指令后递增加4；分支执行指令，是指改变程序计数器的值，跳过某段代码或是返回到先前的代码。

	1. 条件分支：测试，执行
	2. 无条件分支：总执行

条件分支：beq和bne{两个寄存器是否相等}

beq/bne $rs,$rt,imm{标号}：标号是来说明程序中指令位置的。当汇编代码转换成机器代码时，标号将转换为指令地址。

无条件分支：
	
	1. j：直接跳转到标号所在的指令 j imm
	2. jal：与j类似，但是保存返回地址于$ra中 j imm
	3. jr：跳转到寄存器所保存的地址 jr $s0/$ra {jr指令属于R类型指令}

------------------------------------------------------------------------------------------

条件语句和循环语句{一条或多条指令构成}

if：

    bne $s0,$s1,target
	xxxxxxxxxxxxxxxxx{代码块}
	target:
	xxxxxxxxxxxxxxxxx

if/else：

	bne $s0,$s1,else
	xxxxxxxxxxxxxxxxx
	j L1
	else:
	xxxxxxxxxxxxxxxxx
	L1:
	xxxxxxxxxxxxxxxxx

switch/case/break/default:

	case1:
		addi $t0,$0,1
		bne $s0,$t0,case2

		xxxxxxxxxxxxxxx
		j done
	case2:
		addi $t0,$0,2
		bne $s0,$t0,default

		xxxxxxxxxxxxxxx
		j done
	default:
		xxxxxxxxxxxxxx
	done:
		xxxxxxxxxxxxxx

while:

	addi $t0,$0,imm	   MAX
	while:
		beq $s0,$t0,done{条件判断}
		
		xxxxxxxxxxxxxxxx
		xxxxxxxxxxxxxxxx{动态条件变化}
		j while
	done:
		xxxxxxxxxxxxxxxx

for:

	addi $s0,$0,imm1    i
	addi $t0,$0,imm2	MAX
	for:
		beq $s0,$t0,done

		xxxxxxxxxxxxxxxx
		addi $s0,$s0,1
		j for
	done:
		xxxxxxxxxxxxxxxx

量值比较：
	
	slt指令：当rs<rt时，slt将rd设置为1；否则设置为0
	再配合beq/bne指令

-------------------------------------------------

数组：数据按照 存储器中的顺序地址 进行组织

数组下标：明确数组第一个元素的地址{基地址}并将数组的基地址装入寄存器中；然后使用lw,sw{偏移地址}从存储器中取出数组的元素，某种操作后，再存储到数组中。

字节和字符：ASCII
字符串：以空字符(0x00)结尾的字符序列

----------------------------------

函数和模块体现的思想是一致的{层次化、模块化、规整化}。参数和返回值相当于输入和输出{级联}。
{函数调用}

	1. 调用函数和被调用函数必须在 **参数和返回值上保持一致**
	2. 惯例：调用函数 需要将 被调用函数所需的4个参数 分别放在$a0~$a3;而被调用函数将返回值放在$v0~$v1中。
	3. 被调用函数不可影响调用函数：被调用函数完成后必须知道PC去往何处? 不可破坏调用函数占用的寄存器和内存{具体是寄存器$s0~$s7和$ra以及存放局部变量的栈不被修改}
	4. 调用函数必须将 返回地址 存储在$ra寄存器中; 使用jal指令跳转到被调用函数的入口

函数调用和返回

	MIPS指令
		
	1. jal负责调用一个函数
	2. jr负责从函数中返回
	
	main:
		jal simple //将下一条指令（jal后一条指令）的地址存储在$ra中；跳转到目标地址
	simple:
		jr $ra

输入参数和返回值

	MIPS指令
	
	1. 返回64位值的函数（double）将使用两个返回值寄存器$v0,$v1
	2. 当调用多于4个参数的函数时，多出来的输入参数将放在栈中
	
	main:
	
		addi $a0,$0,imm1
		addi $a1,$0,imm2
		addi $a2,$0,imm3
		addi $a3,$0,imm4

	jal simple
	xxxxxxxxx
	simple:
		.........
		add $v0,$s0,$0
		jr $ra
	
栈
存储函数中局部变量的存储器{动态变化：分配（局部变量）和回收（函数返回）}

栈顶
最先出栈{$sp}

保存和恢复函数中的寄存器：

	1. 创建栈空间来存储一个或多个寄存器    addi $sp,$sp,-8 {函数为自己分配的栈空间称为栈帧，每个函数应该只访问自己的栈帧}
	2. 将寄存器x的值存储在栈中            sw $s0,4($sp) sw $t0,0($sp)
	3. 可以在被调用函数中使用寄存器x       add $t0,$a0,$a1 add $s0,$a2,$a3
	4. 从栈中恢复寄存器x的原始值	       lw $t0,0($sp) lw $s0,4($sp)
	5. 回收栈空间						   addi $sp,$sp,8

![视情况而定](http://i.imgur.com/tUukusC.jpg)

普遍是：调用函数保存它们**需要保护**的“不受保护寄存器”（$a0~$a3一定保护，$t0~$t9一般不受保护），被调用函数保存**需要修改**的“受保护寄存器”。

附加参数（多于4个参数）和局部变量时栈的空间分布：
	
	从栈底到栈顶：额外的参数{可能不属于自己的栈帧} 需要保护的寄存器{调用函数：$s0~$s7} 局部变量{被调用函数：$s0~$s7(超出的)}和数组

-----------------------------------------------------------------------------------------------------------

寻址方式
	
	读/写操作数的模式
	1. 寄存器寻址：寄存器存储所有源/目的操作数{所有R类型指令}
	2. 立即数寻址：16位立即数和寄存器{部分I类型指令}
	3. 基地址寻址：访问存储器的指令（如lw,sw）；{部分I类型指令}
	写程序计数器PC模式
	4. PC相对寻址：条件分支指令{部分I类型指令}确定PC的新值。{16位立即数字段：BTA（目标地址）与PC+4（条件分支指令的后一条）之间的指令数；BTA=16位立即数符号扩展*4+（PC+4）}
	5. 伪直接寻址：无条件分支指令{J类型指令 j,jal}根据指定的PC值跳转。相对应的，直接寻址{地址在指令中直接给出}。32位JTA~26位addr字段。
	
		1. JTA_1:0 = 0{字对齐：4的倍数}
		2. JTA_27：2 = addr
		3. JTA_31:28 = (PC+4)最高4位{跳转范围是受到限制}

--------------------------------------------------------

编译、汇编和装入

MIPS内存映射：定义代码、数据和栈内存中的存储位置
![内存映射](http://i.imgur.com/R81kvPi.jpg)

	1. 代码段：存储机器语言程序{256MB}{由于最高4位为0，J类型指令可以无所顾忌}
	2. 全局数据段：存储全局变量。在程序执行前的启动中定义{C语言中的main函数之外声明}{64KB}。$gp在程序执行时保持不变{使用基地址寻址访问全局变量}
	3. 动态数据段：存储栈和堆。数据在程序启动时并不能确定，而是在程序执行中动态分配和回收{2G}。栈用于保存和恢复函数使用的寄存器以及局部变量；堆用于存储 运行时程序分配的数据{C语言中的malloc函数}。堆中的数据可以任意顺序使用和回收。若二者互相访问，则会产生内存溢出的错误
	4. 保留段：操作系统{程序不可见}部分保留段用于中断和内存映射IO

转换和执行一个程序的步骤：

**高级语言代码**-*编译器*-**汇编语言代码**-*汇编器*-**目标文件{含机器语言代码}**-*链接程序*{**目标文件库文件**}-**可执行程序**-*装入程序*-**内存**

编译

	1. .data：全局变量
	2. .text：代码

汇编	

	1. 分配指令地址，存储所有符号{如标号和全局变量名}{符号的名字和地址保存在符号表中}。
	2. 产生机器语言代码，全局变量和标号的地址可以从符号表中得到。
	3. **机器语言代码和符号表打包在目标文件中。**

链接

	1. 重新定位目标文件中的数据段和代码段{打散}
	2. 使用符号表来重新调整 全局变量和标号的地址{聚合}

装入{lw,lb,sw,sb}

	1. OS常通过存储设备{如硬盘}读取可执行程序的代码段，并将其装入到内存的代码段中
	2. OS将$gp=0x10008000,将$sp=0x7FFFFFFFC,再执行 jal 0x00400000 跳转到代码段的开头


**在接触新的体系结构时，需要提出以下关键问题：**

	1. 数据字长？
	2. 寄存器？
	3. 内存如何映射？
	4. 指令？
	5. 体系结构的威力在于：针对特定体系结构写出的程序，可以运行在该体系结构的不同实现上{微处理体系结构}
		 
		
		

 










