# 计算机网络系统方法 #
## 系统方法有以下含义 ##
1. 基本原则。从基本原则开始了解当今网络技术的发展过程，这能让我们解释网络为什么像现在这样设计。 以及理解遇到的任何新协议都将变得相对容易。
2. 非分层主义者。许多主题涉及上下多个层，如拥塞控制和安全；与此类似路由器和交换机也有很多共同点。分层只是很好的辅助，但是不一定受其限制。
3. 现实世界的例子。借助协议来具体说明网络是如何工作的。
4. 软件。强调网络软件如何实现，而不仅仅停留在描述所涉及的抽象算法上。也就是说，需要理解如何实现某些协议栈以及相应的算法。
5. 以端对端为重点。网络由多个组件构成，理解如何将这些组件合成具有一定功能的完整网络是非常重要的。
6. 性能。系统方法包含通过实验来研究性能问题，然后通过收集的数据对各种设计选项进行定量的分析且指导优化实现。
7. 设计原则。

> **控制复杂性的艺术**


- 抽象：隐藏不重要的细节。一个系统可以从多个不同层面进行抽象。
- 约束：对设计选择的一种内在限制，通过这种限制可以更有效的在更高抽象层次上工作。使用可互换部件是约束的一种常见应用。通过将部件限定为一个误差允许范围的标准集合，可以快速的完成系统的设计和构建。通过数字电路的约束规则，可以很容易的将组件组合成复杂的系统。
- 三Y原则：层次化、模块化、规整化

1. 层次化：将系统划分为若干模块，然后更进一步划分每个模块直到这些模块可以很容易理解；
2. 模块化：所有的模块有定义良好的功能和接口，以便于它们之间可以很容易得相互连接而不会产生意想不到的副作用；
3. 规整化：在模块之间寻求一致，通用模块可以重复使用多次，以便于减少设计不同模块的数量。可互换部件即使如此。

## 第一章 基础 ##
问题：建造一个网络。

假设我们要建造一个计算机网络，它有发展到全球性规模的潜力，并且能够支持各种各样的应用。那么要采取什么现有技术作为基础构件，以及使用何种软件体系结构才能把这些构件集成为一个有效的通信服务？

- 什么是计算机网络？
曾经，网络一词是指：将哑终端连接到大型机的串行线的集合；其他重要的网络诸如语音电话网络以及有线电视网络。这些网络的特点是专门处理某种特定类型的数据（按键、音频、视频），并且通常连接到专用设备（终端、手持接收器、电视机）。
本节主人公与她们的区别在哪？通用性。计算机网络主要由可编程硬件来构建，并且不需要为特定应用做任何优化；他可以传输多钟不同的数据，并且支持相应的应用。

- 清楚这些需求后，接下来该怎么做呢？网络体系结构（前辈经验）。网络体系结构指明可用的软硬件构件，并且说明如何将它们组织起来。

- 除了理解如何构建网络，理解如何使用或管理网络、如何开发网络应用也很重要（网络构建者、运营者、应用开发者）。

1.1 应用分类
- 万维网（注意与因特网的差异）。
- 音频流和视频流。流式应用与传统的网页文本或静态图片传输的区别在于：人们以连续的方式欣赏音频流和视频流，跳音或视频停滞等间断是不能接受的；相比之下，文本网页可以以位或块为单位来传输和阅读。（这种区别会影响网络对不同类型应用的支持方式）。
- 实时音频和视频流。她们比流应用有更严格的时间约束。此外交互式应用常需要双向的音频或视频流；而流式应用大多只是单向传输。

为什么需要了解这些应用？指导关键的设计决策、提出必须解决的问题，进而建造、运营、使用能够支持大量不同应用的网络。

1.2 需求和挑战
- 应用程序员会列出应用所需的服务。例如要保证应用程序发出的每条信息能在一定的时间内准确无误的传输，或随着用户的移动在不同网络连接之间平稳切换的能力。
- 网络运营者会列出系统易于管理的特性。例如故障易于隔离、新设备能够加入到网络中并正确配置、易于根据网络的使用情况进行计费。
- 网络设计者会列出性价比高的设计所具备的属性。例如有效的利用网络资源和公平的分配给不同的用户；性能问题也很重要。

**可扩展的连通性**
网络必须首先提供若干个计算机之间的连通性。
1. 鉴于隐私性和安全性，许多专用网络都在限制接入网络的计算机方面有明确的目标（企业网）。
2. 其他的网络则具有连入世界上所有计算机的能力（因特网）。

一个系统设计支持任意规模的扩展，则称为可扩展的（scale）。

**高性价比的资源共享**
计算机网络的关键需求-效率，它是选择分组交换策略的直接原因。
给点一个节点集合，节点之间通过一个嵌套的网络间接相连，任何一对主机都可能通过一系列链路和节点互相发送消息。当然，我们不仅仅需要支持一对主机之间的通信，而是希望提供任何一对主机之间的交换消息的能力。

问题：如何使所有希望通信的主机都能共享网络，特别是如果他们想同时使用网络时如何共享？当多个主机需要同时使用同一条链路时，应该如何实现共享？
统计多路复用。多个流的发送顺序（QoS）。拥塞。

**支持通用服务**

