FPGA 的 LVDS 的数据发送和接收

LVDS （ 低电压差分信号）介绍

背景：当今主控芯片的引脚资源相对变得紧俏；在数字系统互联的设计中，并行传输的方式将会被高速串行传输逐步替代。
而在串行传输标准中，低电压差分信号传输（ LVDS）接口具有高速率、低功耗、低噪声和低电磁干扰等优点，广泛应用于高速数字系统设计中。

低压差分信号：

	* 相对于单端的传送具有较高的噪声抑制功能
	* 较低的电压摆幅允许差分对线具有较高的数据传输速率，消耗较小的功率以及产生更低的电磁辐射。
	* 由于差分的缘故，所以输入和输出都各使用两条线。


详见《LVDS 原理与应用简介》


解决：为了适用于高速通讯的场合，现在的 FPGA 都提供了数目众多的 LVDS 接口。
举例：SPARTAN-6 FPGA 芯片的 IO 口支持不同电压的 LVDS 数据传输，具体每个 BANK 能够实现的电平标准请大家参考"Spartan-6 FPGA SelectIO Resources User Guide.pdf"的表1-5。

在AX545/AX516 开发板的扩展口 J3 的信号连接到 FPGA 的 Bank2 上，属于LVDS接口。


	* 在硬件设计上我们已经考虑到 LVDS 的信号的数据传输，所以在 PCB 走线的时候使用等长并且 100ohm的差分对走线；
	* 另外IO的电压通过电阻跳变来实现 3.3V 和 2.5V 的切换。所以用户能实现不同电压的 LVDS 的高速数据通信。


我们以开发板上的扩展口 J3 的差分信号来实现 LVDS 的环路数据通信。且这里发送和接收都只使用了一对 LVDS 数据和一对 LVDS 时钟。


	* 发送的 LVDS 时钟在开发板上 环路到 接收的 LVDS 时钟，发送的 LVDS 数据 环路到 接收的 LVDS 数据。
	* LVDS 的发送数据和发送时钟由 FPGA 内部产生，我们可以通过 chipscope 来查看 LVDS 接收到的数据是否和发送的数据一致。


程序设计

SPARTAN6 FPGA 中已集成了 SelectIO 资源（属于IP核）。


	1. 通过配置 IP 核，可以生成支持LVDS 电平标准的接口程序，实现高速 LVDS 接口通信。
	2. SelectIO 资源包含了 ISERDESE2、OSERDESE2、 IDELAYE2、 ODELAYE2、 IDELAYCTRL 等， 本设计中仅用到 ISERDESE2 和OSERDESE2。


	* 
		* ISERDESE 为 Xilinx FPGA 中专用的解串器，主要用于数字传输中的串行转并行， 先到的比特为为高位。
		* OSERDESE2 为转串器，主要用于数字传输中的并行转串行，先到的比特为为高位。



FPGA 中 ISERDESE2 和 OSERDESE2 支持非常高的 I/O 数据速率。


	* 对于 ISERDESE2 存在 bitslip 信号来重新对齐串行数据以获得正确的字节数据；使用 bitslip 信号可以修改串转并的起始位置；通过多次插入 bitslip 的方法来获取正确的并行数据序。


SelectIO IP 核的建立流程： 一个用于并行数据转成串行数据并通过 LVDS 差分输出； 另一个用于 LVDS 差分输入转换成并行数据。

以SPARTAN-6为例：并行数据转成串行数据

	1. 向项目中添加一个 new source, 在 New Source Wizard 的向导里选择 IP(COREGenerator & Architecture Wizard)。
	2. 选择 FPGA Features and Design/IO Interfaces/SelectIO Interface Wizard。
	3. 在 SelectIO Interface 向导中 Data Bus Direction 项选择 Configure outputs fromdevice。这里我们选择数据方向为输出。 IO 信号选择选择差分， LVDS33 电平。
	4. 勾选 Use serialization。 Serialization factor 为 8，它的意思是 8 位并行数据转化为1 个串行数据。 External data Width 设为 1，它的意思是输出的数据为串行数据（ 1 个差分对）。另外使能 Enable Clock Forwarding 项， 来产生输出的 LVDS 差分时钟。
	5. 不设置输入延时。

	6. 设置时钟输入为单端的 LVCOMS33 电平， 本例中该输入的时钟为系统时钟 50Mhz。

	7. 不设置输出延时。
	8. 点击 Generate 按钮完成 selectio IP 的配置。


实现：

	* 使用两个OSERDES2（由于一个OSERDES2是4位转串行，所以需要两个实现；其中一个是MASTER，另一个是SLAVE）。然后调用 OBUFDS 来实现 OSERDES2 输出的单端信号转换成差分信号进行输出。
	* 使用两个ISERDES2（由于一个ISERDES2是4位转串行，所以需要两个实现；其中一个是MASTER，另一个是SLAVE）。
	* 我们只是使用了 1路的数据来为大家演示 LVDS 发送和接收，用户在实际使用中用同样的方法来实现多路LVDS 数据的传输。



以SPARTAN-6为例：串行数据转成并行数据

	1. 向项目中添加一个 new source, 在 New Source Wizard 的向导里选择 IP(COREGenerator & Architecture Wizard)。
	2. 选择 FPGA Features and Design/IO Interfaces/SelectIO Interface Wizard。
	3. 在 SelectIO Interface 向导中 Data Bus Direction 项选择 Configure inputs fromdevice。这里我们选择数据方向为输入。 IO 信号选择选择差分， LVDS33 电平。
	4. 勾选 Use serialization。 Serialization factor 为 8，它的意思是每 8 位串行数据转化为一个8位并行数据。 External data Width 设为 1，它的意思是 连接的外部设备输入进来的数据引脚为 1 个差分对。另外使能 Enable BITSLIP 项， 需要使用其作为输出数据对齐。
	5. 不设置输入延时。

	6. 设置时钟输入为差分的 LVDS33 电平， 本实验这个差分时钟从 FPGA 外部输入。

	7. 不设置输出延时。
	8. 点击 Generate 按钮完成 selectio IP 的配置。


详见 “SERDES_FPGA 设计手册”

LVDS 发送和接收的测试程序 lvds_test.v。在这个文件里产生LVDS 测试数据并实例化 LVDS 的发送和接收的 IP。
实现 LVDS 的数据发送和数据接收的功能。


	* 因为串行转成并行的时候，输出的数据无法判断哪个 Bit 是高位，哪个 bit 是低位， 程序中我们会判断输入的数据是否等于 0x80(这个值我们自己设定） , 再判断下一个数据是否为0x81, 如果不是说明数据的排列有错，产生一个时钟周期的 BITSLIP 的脉冲, 提供给 s_to_p的 BITSLIP 输入端， 来调整串转并输入数据的起始位置， 直到数据正确加 1 为止。


编写工程的管脚约束文件 lvds_test.ucf

DIFF_TERM = "TRUE"   注：LVDS 的输入约束需要加差分端接电阻为 True, 因为开发板上没有加 100 欧姆的差分电阻，所以需要使能 FPGA 内部的差分端接电阻。FPGA 内部的端接电阻的详细说明可以参考“Spartan-6 FPGA SelectIO Resources User Guide.pdf”的 Page15。

仿真文件 vtf_lvds_test.v

程序里我们把 LVDS 的输出时钟付给了 LVDS 的输入时钟，把 LVDS 的输出数据付给了 LVDS 的输入数据。就相当于模拟了 LVDS 信号在 FPGA 外部的环路连接。
