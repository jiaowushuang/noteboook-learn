FIFO应用：
1、在千兆以太网数据写入，往DDR3里面写数据时候
2、AD采样时钟和内部时钟不同时，需要FIFO进行转换
3、同频异相时也需要用FIFO进行转换 

- clock domain crossing
- Low-latency memory buffering 
- bus width conversion

Supports Native interface FIFOs, AXI Memory Mapped interface FIFOs and AXI4-Stream interface FIFOs. 

- AXI Memory Mapped and AXI4-Stream interface FIFOs are derived from the Native interface FIFO. 
- Three AXI Memory Mapped interface styles are available: AXI4, AXI3 and AXI4-Lite.

**Native Interface FIFOs**

Utilize **block RAM**, **distributed RAM **or **built-in FIFO** resources available in some FPGA families to create high-performance,
area-optimized FPGA designs.

**Standard mode and First Word Fall Through are the two operating modes.**

- First-Word-Fall-Through模式：相对于标准模式而言，读操作的标志信号（underflow/empty/almost_empty）超前一时钟；也就是判断FIFO当前数据是否有效、可读。无需等待下一时钟到来。

1. 时钟：独立时钟（与读写端口异时钟域）或是与读写操作同时钟域；处理时钟域的同步；若数据缓冲区需要单时钟域，FIFO核则会对单时钟优化。
2. 內建FIFO支持：其功能没有FIFO核健全；作为宏来使用。
3. 非对称方面的支持：读写端口可以有不同的位宽（自动数据转变）
4. 嵌入式寄存器** The block RAM macros and built-in FIFO macros**：嵌入式输出寄存器可以提升性能以及增加一个 宏FIFO的管道寄存器（pipeline data and improve macro timing）。但是也带来了一个额外的延迟（dout/vaild）；也可以实现为FWFT FIFO的输出寄存器。可以复位到一个默认值或是自己编好的值。
5. 错误收集以及更正支持：检查Block RAM and Built-in FIFOs的正确性。

**Designing with the Core**设计指导

明确影响难度级别的因素：**设计方法是被用来帮助实现的，包括流水线以及所使用的约束（时序约束、位置约束、面积约束）**
- 最大系统时钟频率
- 目标设备的架构（xilinx family）
- 特定的应用功能

理解信号管道以及同步：在FIFO设计中，应该理解管道是如何最大化性能的以及如何实现同步逻辑（跨时钟域）；因为在写端口的输入数据在到达读端口之前可能属于多个时钟周期。
- 独立读写时钟的FIFO要求接口信号只能用在他们自己的时钟域（例如在写操作中，写使能信号以及数据输入都必须同写时钟同步；同理，读操作也是如此）
- **所有的状态输出都必须与它们相关的时钟域同步，且只能作用在自己的时钟域**；
- 而**The independent clocks FIFO**可以处理所有同步需求，帮助你跨（独立）时钟域；
- 衡量FIFO性能的因素是读写时钟；
- **FIFO的满、空标志必须使用以保证合理的行为；**接口信号一般在时钟上升沿有效。

初始化FIFO控制器

1. 当设计**built-in FIFO or common clock shift register FIFO**，必须复位（在FPGA上电配置之后或是实际操作之前）。而异步复位（rst）可以在**shift register FIFOs and 7 series built-in FIFOs**使用（清除内部计数器和输出寄存器）。
2. 当设计**block RAM or distributed RAM FIFO**，复位时不需要的。
3. 在**common clock configurations**，复位可以选择是同步或是异步的(rst)。
4. 在**independent clock configurations**，复位可以选择是同步（wr_rst/rd_rst）或是异步（rst）的。
5. 当异步复位被实现（也就是·使能复位同步选项被选择），需要同步时钟域以确保FIFO初始化到已知状态以及避免毛刺、亚稳态。
6. 当同步复位被实现（也就是·使能复位同步选项没被选择），要明白复位信号是与相关时钟域密切联系的（即同步）。

写操作与相关的状态标志

1. 当写使能有效且FIFO不满，数据会从数据输入端（din）增加到FIFO中，并且写行为（wr_ack：表明是一个正确的写操作）被置位。
2. 若FIFO一直写而不读，则会溢出；当FIFO是满且写操作准备好，那么写请求则会被忽略；溢出标志overflow被置位。若边写边读呢？
3. **almost_full（差一个写操作便会满） and full Flags：高电平有效且与写时钟同步**

读操作与相关的状态标志

1. 当读使能有效且FIFO不空，数据会从FIFO中读到数据输出端（dout），并且读行为（vaild：表明是一个正确的读操作）被置位。
2. 若FIFO一直读而不写，则会空；当FIFO是空且读操作准备好，那么读请求则会被忽略；溢出标志underflow被置位。若边写边读呢？
3. **almost_empty（差一个读操作便会空） and empty Flags：高电平有效且与写时钟同步**
 
读操作模式
（ Independent Clocks）
1. standard read operation：provides the user data on the cycle after it was requested
2. first-word fall-through (FWFT) read operation：provides the user data on the same cycle in which it is requested
3. 读写是相伴相生的。
（ Common Clocks）
同时读写操作：写操作时钟至少超前于读操作一个时钟

握手标志
（vaild/underflow{两种模式、读成功和读失败}|wr_ack/overflow{写成功和写失败}）可选、默认高电平有效、与读写时钟同步。

可编程标志：表明FIFO到达用户定义的阈值（例如预定义满和预定义空）；暂无用处。
• Programmable full (prog_full) indicates that the FIFO has reached a user-defined full
threshold.
• Programmable empty (prog_empty) indicates that the FIFO has reached a
user-defined empty threshold

数据计数器（data_count）:表明FIFO中的字数。你可以指定计数总线的数据宽度，最大宽度为log2（FIFO深度）。 如果指定的宽度小于
最大允许宽度，总线通过去除较低位来截断。 可选。

**Non-symmetric Aspect Ratios**：支持 1:8, 1:4, 1:2, 1:1, 2:1, 4:1, 8:1（写数据宽度/读数据宽度）。

如上，它允许FIFO输入和输出深度不一致。并且与读写数据宽度密切相关。{输入深度*写数据宽度=输出深度*读数据宽度}
该特性在设置读写数据宽度不同时有效。默认读写数据宽度是一致的（1:1）。

满和空信号仅在一个完整的字读或写下是有效的。具体是：假设一个满FIFO，若写数据宽度是8位且读数据宽度是2位，则你需要在写操作有效且满信号下降沿之前（不满）完成4个有效的读操作。

若写数据宽度比读数据宽度更小，大多数情况下是先读。

**Non-symmetric Aspect Ratio and First-Word Fall-Through**

FWFT FIFO有两个额外的 读 字；
对于写数据宽度大于读数据宽度的情况，这种实现增加了写入FIFO的字的数量（2*{写数据宽度/读数据宽度}）；
对于写数据宽度小于读数据宽度的情况，这两个额外的 读 字仅作为一个 写 字的部分存在。这种情况导致prog_empty and wr_data_count信号与之前不同。

**Embedded Registers in Block RAM and FIFO Macros**

- For Block RAM configuration,you can add an extra output register instead of embedded register from the general
interconnect to improve the timing.
- In built-in FIFO, you have embedded register option.
- In block RAM FIFO, you have the choice to select either the primitive embedded register or an output register from the general interconnect.

**Embedded Registers and Interconnect Registers in Block RAMand FIFO Macros**
 improve timing

**Built-in Error Correction Checking**：independent or common clock block RAM and built-in FIFOs
当ECC使能，**the block RAM and built-in FIFO **会被配置为full ECC模式（编码器和解码器使能）；并且提供两个额外的输出（sbiterr/dbiterr）；这些输出表明三个结果;没有错误、单错误修正、双错误检测；在full ECC模式下，读操作不会修正单错误（内存单元），仅修正在dout的数据。

**Built-in Error Injection**：independent or common clock block RAM and built-in FIFOs
当ECC和 Error Injection 使能时，**the block RAM and built-in FIFO **会被配置为full ECC error injection模式，并且提供两个额外的输入（injectsbiterr and injectdbiterr）；
These inputs indicate three possible results: no error injection, single bit error injection, or double bit error injection. 

**Clocking-Independent Clocks: Block RAM and Distributed RAM**
在读写操作之间的时序联系以及状态标志受读写模块XX联系的影响。

**Actual FIFO Depth**
不一定就是GUI中所规定的。它依赖于具体的实现以及影响其实现的特性。

**Actual FIFO Depth-Block RAM, Distributed RAM and Shift RAM FIFOs**
影响因素：
1. Common or Independent Clock
2. Standard or FWFT Read Mode
3. Symmetric or Non-symmetric Port Aspect Ratio

• Common Clock FIFO in Standard Read Mode
actual_write_depth = gui_write_depth
actual_read_depth = gui_read_depth

• Common Clock FIFO in FWFT Read Mode
actual_write_depth = gui_write_depth +2
actual_read_depth = gui_read_depth +2

• Independent Clock FIFO in Standard Read Mode
actual_write_depth = gui_write_depth - 1
actual_read_depth = gui_read_depth - 1

• Independent Clock FIFO in FWFT Read Mode
actual_write_depth = (gui_write_depth - 1) + (2*round_down(gui_write_depth/gui_read_depth))
actual_read_depth = gui_read_depth + 1

Notes
1. Gui_write_depth = actual write (input) depth selected in the GUI
2. Gui_read_depth = actual read (output) depth selected in the GUI
3. Non-symmetric port aspect ratio feature (gui_write_depth not equal to gui_read_depth) is only supported in block RAM based FIFOs.
4. When you select Embedded and Interconnect Registers, the actual write depth and actual read depth increases by one as compared to selecting embedded/interconnect register in FWFT mode.

**Resets以及Latency**

**AXI背景**
![](http://uphotos.eepw.com.cn/1384955505/pics/222956a39135949325db0408dfb6819d.jpg)
1、AXI总线将写地址通道、写数据通道、写响应通道、读地址通道、读数据通道分开，这是AXI总线效率比较高的一个原因，类似于全双工的感觉，每个通道互不干扰却又彼此依赖；但是为什么写会出现三个通道，但是读却只有两个通道呢，那是因为读将读数据通道和读响应通道合并成了读数据通道，因为读数据和读响应都由slave发出，当最后一笔数据被读出的时候，slave完全可以在这个时候给出当前这个burst读状态（例如是ok还是error），但是写就不同了，虽然写数据可能已经被slave接收了，但是接收完最后一笔数据的时候，slave可能不能及时反馈当前这个burst是否写成功，因为数据可能并没有完全到达目的地；而且写成功与否肯定是slave应答，所以单独开辟了写响应通道。 
![](http://uphotos.eepw.com.cn/1384955505/pics/2385a90734d46321396fa26b4ca8356b.jpg)
![](http://uphotos.eepw.com.cn/1384955505/pics/2385a90734d46321396fa26b4ca8356b.jpg)

2、AXI传输首先发出burst的长度(burst-len)，最大是16，burst长度就代表有多少个transfer或者beat，一个transfer就代表一个数据位宽的数据，所以一个burst最大的传输数据长度为burst_len*transfer_width;在发出burst长度时会同时发出当前这个burst中第一个transfer的首地址，后面其它的transfer不会有地址，slave要根据地址递增的方式自己去进行相应的处理，这个地址可以是非对齐的；在发出burst长度时会同时发出burst_size，这个size代表当前burst中所有transfer中最大的字节个数，在发出burst长度时会同时发出地址递增方式burst-type，是不变地址(non-incr)，是递增（incr）还是wrap，例如：当前要传输11个字节，地址是2，数据位宽是4B，所以传输方式是：2B-4B-4B-1B，burst_len=4，burst_size=4（所有transfer中size最大的），地址是2（因为支持非对齐传输），burst-type=incr；对于写会有strobe代表当前transfer中哪几个字节是有效的，所以上面的strobe为：1100-1111-1111-0001，对于读则没有，但是Master自己清楚哪些数据是有效的，所以可以将整个4B都读出来，master自己去除无用的数据。 
![](http://uphotos.eepw.com.cn/1384955505/pics/c90e37f66887394058ef38d0c44e79e7.jpg)
注意：不同人对burst_size（也就是英文手册中AWsize和ARsize的理解）的理解可能不同，手册中在table-4-2中有解释，它表示一个burst中transfer中max-num，注意最大，所以不是表示当前burst中所有transfer的num，只是表示最大。如果表示所有transfer的num，那么也就是所有transfer的大小是一样的（AHB就是这样的，每个burst中的transfersize是一样的），那么上面的例子就必须分成3个burst，第一个burst,len=1,size=2,addr=2, 第二个burst,len=2,size=4,addr=4, 第三个burst,len=1,size=1,addr=12,显然这个效率要比上面的低。不过呢，如果你的设计中大家都约定成统一的理解倒也可以实现，只是你的AXI就不是通用的AXI，别人不能用。 

3、AXI中关于valid和ready的关系在3.3节中有很好的解释，在设计时一定不能设计一方依赖另一方，否则会出现死锁的现象，valid可以优先于ready拉高，也可以在ready之后拉高，它们并无先后关系，其实只要是master准备好就可以valid，slave准备好就可以ready，并无绝对的先后顺序，但是当两者同时为高则表示当前的data或者cmd结束或者开始下一个data或者cmd。 
![](http://uphotos.eepw.com.cn/1384955505/pics/1e986934d3d6f9c234f4b6543dc64b25.jpg)
![](http://uphotos.eepw.com.cn/1384955505/pics/1e986934d3d6f9c234f4b6543dc64b25.jpg)

4、由于3中的不确定性会出现一种奇葩的现象，以写为例，会出现写数据比写地址先到达slave的现象，原因如下：假如AWREADY和WREADY被slave提前拉高了，虽然master那边肯定是先发地址再发数据，但是master会误以为slave能够立即接收地址，所以地址发送完立即发送数据，但是地址通道和数据通道是分开的，axi允许单独对各个通道进行优化，所以，如果地址通道被插入了多个reg，那么就会造成延时，可能出现数据先被slave收到。 
![](http://uphotos.eepw.com.cn/1384955505/pics/746f85d8d93ae22e988381cc79bd1c42.jpg) 
为了避免上面的现象该怎么办呢，首先slave最好不要在接收到地址之前就将WREADY拉高（但是AWREADY建议提前拉高，这样address握手可能就会在一个周期内完成，否则至少需要两个周期，就像上图），要在收到地址后才进行WREADY的处理，或者slave先buffer住收到的数据，然后等到收到地址后再做处理。不过我觉得AXI interconnect应该会处理这种情况，不会让数据先于地址到达slave的，所以ARM公司的AXI产品肯定是不会有问题的，但是如果不购买相应的AXI interconnect而自己开发时就要注意上面的问题。 

5、AXI最多支持16个master,16个slave，它们可以通过AXI interconnect连接，不同的master发出的id可能相同，但是经过AXI interconnect处理后会变得唯一，所以自己开发AXI interconnect也要注意这个问题。同一个master发出的id可以相同也可以不同，相同的id数据传输必须按照先后顺序否则会出现错误，不能乱序和交叉。AXI 支持ID方式，这也是该总线效率较高的一个原因。 

6、AXI支持out-standing或者multi-issue(即当前传输没结束就发起下一个传输)乱序和交叉传输，依靠ID进行区分。这也是AXI总线协议效率较高的一个原因。 
![](http://uphotos.eepw.com.cn/1384955505/pics/03cb863234098b0eca0395d61013ed53.jpg)

7、这块的理解是参考别的网站的，并不确定正确性，cachalbe和 bufferable的概念比较复杂，具体可以看看ARM cache相关文档。简单说，这两个概念都是围绕master访问的slave的请求来说的。例如该请求时cacheable的写话，那么实际的写数据不一定更新了主存内容，可以只更新了cache，以后再通过write back方式更新；bufferable也类似，如果是写，那么写数据响应返回给master时，实际写数据不一定到达了slave设备。这个写数据可能被buffer了，而时间未知。如果不是bufferable则写响应反映了slave实际接收到数据的时刻。说的比较笼统，具体可以参考相应文档。 

8、低功耗的理解（参考）：AXI的低功耗接口本身也是数据传输协议的扩展。它针对自身具有低功耗处理的设备和自身不具有低功耗处理的设备都是通用的。 
AXI低功耗控制接口包括两类信号： 
设备给出表示当前时钟是否可以被gated的信号。外设使用CACTIVE信号表明它希望时钟，时钟控制模块必须马上给设置时钟。 

对于系统时钟控制模块，提供可以进入或退出低功耗状态的握手信号。CSYSREQ表明了系统请求设备进入低功耗状态，而设备使用CSYSACK信号来握手低功耗状态请求和退出。 
![](http://uphotos.eepw.com.cn/1384955505/pics/16ff8874ec7503bfc4699f5d13e93638.jpg)
图２　AXI低功耗握手时序（1） 

在CSYSREQ和CSYSACK信号为高的时候，也就是T1时刻之前，设备处于正常状态。在T1时刻，系统拉低了CSYSREQ信号，在T2时刻，外设 拉低CSYSACK信号。在T3时刻系统拉高CSYSREQ表示系统要求设备从低功耗状态退出。T4时刻设备握手拉高CSYSACK表明已经退出。在握手 中，CACTIVE可以作为拒绝或者同意的标志。下图中CATIVE一直拉高，来表示当前不接受这种低功耗的请求，而不是依靠ACK信号。可以看 出，ACK 信号只是表示状态迁移的完整性，而对于是否进入低功耗状态，需要CACTIVE信号表示。同时该信号也表示了设备在低功耗状态需要退出。 

在系统层面的操作： 

有两种方法进行设备的低功耗控制。第一种是系统不断的轮询设备，一旦某个设备可以进入低功耗状态，就把相应的CATIVE 拉低，然后把CSYSACK信号拉低。这样做的效率不是很高，系统并不知道哪个设备已经可以提前进入低功耗状态，而是简单的按照时间进行查询，并不能精确 的控制。这一种方案主要强调系统与设备的强耦合性。只有系统需要的时候才开始轮询，系统不需要，就不能进入低功耗模式。 
![](http://uphotos.eepw.com.cn/1384955505/pics/8a58988628d5dc12f1abb5fed43f4185.jpg)
![](http://uphotos.eepw.com.cn/1384955505/pics/8a58988628d5dc12f1abb5fed43f4185.jpg)

第二种方法是系统被动接受设备发出来的CATIVE，然后开始低功耗处理流程。这样可以提高效率。但是可能系统由于预测到马上需要使用该device，不发起低功耗请求。值得注意的是，两种低功耗管理是可以混合使用的。