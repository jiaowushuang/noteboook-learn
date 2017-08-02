
	* Spartan6 FPGA 芯片中集成了 MCB 硬核，支持到 DDR3；而且对于大多数厂家的存储芯片都支持（ Micron、 Elpida、 Hynix.....）。
	* 对于工程来讲，MCB 硬核 优秀的误码校验和偏移时钟校验，以及 PLL_ADV 工作时的稳定、高精度都大大保证了研发产品的质量。



	* Xilinx ISE 提供了 MIG IP 核，直接生成 DDR3 控制器设计模块。模块包含可自由修改的 HDL 源代码和约束文件。
	* 用户可以在 MIG 的 GUI 图形界面根据所选的存储器件选择对应模板、总线宽度和速度级别，并设置 CAS 延迟、突发长度、引脚分配等关键参数。如果所选器件与 MIG 所列模板不相符，可在代码生成后灵活修改这些代码。


本例 用 MIG 工具生成 DDR3 控制器，并用ChipScope 测试 DDR3 读写数据的方法。

	* MIG IP 控制器是 Xilinx 为用户提供的一个 DDR 控制的 IP, 这样用户即使不了解 DDR 的控制和读写时序也能通过 MIG 控制器方便的读写 DDR 存储器。


因为 Spartan6 FPGA 和 DDR3 连接是 MCB 硬核，故只有 Bank1 或 Bank3 能够和 DDR3相连接；另外，连接的管脚也是固定的、用户不能随便连接。

AX516/AX545 开发板上都使用了 Micron DDR3颗粒。


	* AX516 开发板上使用的是容量为 1Gb 的 MT41J64M16。
	* AX545 开发板上使用的是 2Gb 的 MT41J128M16。
	* DDR3 和 FPGA之间的连接的数据宽度都为 16 位。另外开发板板上对 DDR3 的地址线和控制线都做 端接电阻上拉到 VTT 电压, 保证信号的质量。


步骤：

	1. 打开 Xilinx CORE Generator System
	2. 双击 IP Catalog 界面中的 MIG Vertex6 and Spartan6 3.92 启动 MIG IP 的生成和配置工具。
	3. 如果这个 MIG IP 只是针对 AX516 开发板上的 XC6SLX16 的话，这里就不需要选择 PinCompatible 的 FPGA。
	4. 我们选择 Bank3 连接 DDR3 SDRAM，因为开发板上 DDR3 是连接到 FPGA 的Bank3 上的。
	5. 设置 DDR3 的时钟频率为 312.5Mhz, 这个频率最高可设置为 333.33Mhz，我们这里稍微留一点余量。 另外 DDR3 的型号设置为跟开发板上一致的型号 MT41J64M16XX-187E,；如果是 AX545 的开发板，需选择的 DDR3 型号为 MT41J128M16XX-187E。
	6. 设置输出阻抗值和内部的 ODT 内部上拉电阻值来改善 DDR3 的信号完整性，一般不需要修改。
	7. 根据需要可以选择不同的用户端接口方式，可以选择多个 Port, 也可以组合成一个Port, 我们这里选择 One 128-bit bidirectional Port。
	8. 选择 RZQ 和 ZIO 的引脚分配，这跟硬件电路设计有关，不要设置错误。在我们的 AX516和 AX545 的开发板上 C2 脚作为 RZQ, L6 脚作为 ZIO。另外选择 Debug Signals for MemoryController 项设置为 Enable，因为我们将用 chipscope 来测试 DDR3。 System Clock 设置为 Single-Ended。


目录结构：

	* example_design 文件夹的内容为 MIG 的例子设计，用户可以直接生成 ISE 工程来测试 DDR3的性能。
	* user_design 中是只有的软核源码，用户还需要编写顶层文件实例化 MIG 的 IP。
	* 在本实验中，我们只用 example_design 的例子来测试 DDR3, user_design 部分在其它工程例子中使用到的时候我们会讲。


工程生成和修改：

不再用 ISE 里新建 Project， 直接利用其 MIG 生成相应的.ise 的工程文件。

	1. 在 exmaple_design 和 user_design 目录下 Par 文件夹里，包含两个.bat 的批处理文件(creat_ise.bat 与 ise_flow.bat),我们用 creat_ise.bat 文件用来生成相应的 ISE 工程文件。
	2. 打开 Xilinx ISE Design Suite 14.7->Accessories->ISE Design Suite 64 Bit CommandPrompt。
	3. 输入以下命令跳转到 example_design 的 par 目录下。
	4. 输入 create_ise 命令，开始运行 par 目录下的 create_ise.bat 批处理生成 ISE 的工程文件。
	5. 系统会自动生成相应的 test.xise，此工程里面包含 Mig 生成的所有.v 文件以及相应的.ucf文件。
	6. 生成完成后再用 ISE 打开 PAR 目录下生成的 test.xise 工程。


修改 UCF 文件


	1. 23 VCCAUX 的电压修改为 3.3V
	2. 39 NET “c?_pll_lock”TIG 屏蔽掉。
	3. 58 修改系统时钟输入的周期为 20ns, 这需要跟开发板上的晶振频率一样。
	4. 74 修改状态信号为四个，分别定义到开发板上的四个 LED 灯，用 LED 灯的状态来显示程序工作状态。
	5. 102 修改 c3_sys_clk 的电压为 LVCMOS33，因为开发板上晶振的输入脚所在的 FPGA Bank的 IO 电压为 3.3V。
	6. 152 修改 c3_sys_clk 和 c3_sys_rst_i 的管脚约束, 配置成跟开发板的上时钟输入和复位一致。


修改顶层文件 example_top.v


	1. 89 Reset 的极性修改为跟开发板电路一致， 低电平有效。
	2. 108 增加两个输出 port（ pll_locked 和 heartbeat） 用于连接 LED3 和 LED4
	3. 150 修改锁相环时钟的频率。 DDR3 的时钟频率，它是按照输入时钟也是 312.5Mhz 来计算的。因为我们开发板上的时钟输入为 50Mhz, 且DDR3 是上下沿采样，这样 FPGA 内部的 DDR3控制器的时钟需要625MHz，所以这里我们需要倍频25, 再分频2，得到 625Mhz 的 CLKOUT0和 CLKOUT1， 再分频 8 分别得到 user interface 的时钟和 calibration 的时钟 78.125Mhz。


          localparam C3_CLKOUT0_DIVIDE       = 1;                //625
          localparam C3_CLKOUT1_DIVIDE       = 1;               // 625
          localparam C3_CLKOUT2_DIVIDE       = 8;                //625/8=78.125 user interface
          localparam C3_CLKOUT3_DIVIDE       = 8;               // 625/8=78.125 calibration

          localparam C3_CLKOUT4_DIVIDE       = 50;             // SPI sd clock 6.25MHz
          localparam C3_CLKOUT5_DIVIDE       = 10;              // vga clock 50X25/2/10=62.5MHz   

          localparam C3_CLKFBOUT_MULT       = 25;             // ddr clock 50*25/2 =  625Mhz   
          localparam C3_DIVCLK_DIVIDE          = 2;       

