## 一、实验题目
简单的个人网络嗅探器

## 二、实验目的
加深对 TCP/IP 协议的理解

## 三、实验环境
环境：Windows 10+Myeclipse+Jdk1.6+Wincap+Jpcap
语言：Java
## 四. 关于Jpcap

。。。做的都差不多了发现Jnetpcap简直好用太多，但是还要准备考试。。没时间改了。。对于数据内容的解码使用gbk解码。。会有很多乱码

#### 1.我们为什么需要Jpcap?

Java的.net包中，给出了传输层协议 TCP和UDP有关的API，用户只能操作传输层数据，要想直接操作网络层{比如自己写传输层数据报（自己写传输层包头），或者自己写好IP数据包向网络中发}则是无能为力的。 而JPCAP扩展包弥补了这一点，使我们可以支持从网卡中接收IP数据包，或者向网卡中发送IP数据包。

#### 2.什么是Jpcap？Jpcap的工作原理是什么？

Jpcap实际上并非一个真正去实现对数据链路层的控制，而是一个中间件，JPCAP调用wincap/libpcap，而给JAVA语言提供一个公共的接口，从而实现了平台无关性。

#### 3.安装配置Jpcap：

之后我们还需要下载Jpcap，Jpcap包括Jpcap.jar和Jpcap.dll，两者需要版本一致，并且区分32位和64位。 
64位的很难找！！！–>[https://www.jianshu.com/p/5e7d8494621f](https://www.jianshu.com/p/5e7d8494621f ) 
配置： 
[https://www.cnblogs.com/caroar/archive/2011/10/12/2208196.html ](https://www.cnblogs.com/caroar/archive/2011/10/12/2208196.html )
[http://blog.sina.com.cn/s/blog_6169c15e0100e2mv.html](http://blog.sina.com.cn/s/blog_6169c15e0100e2mv.html)

API: [http://jpcap.gitspot.com/javadoc/index.html](http://jpcap.gitspot.com/javadoc/index.html)

#### 4.别忘了安装Wincap：

下载地址：[http://www.winpcap.org/archive/](http://www.winpcap.org/archive/)

## 五、实验内容 
#### 1.实现的功能
（1）实现了 Sniffer 的基本功能，监测网络性能及使用情况
（2）考虑一台机器上多张网卡的情况，指定需要侦听的网卡
（3）侦听所有进出本主机的数据包，解析显示数据包（ ICMP 、 IP 、 TCP 、 UDP 等）各个字段及数据内容
（4）侦听来源于指定 IP 地址的数据包，侦听指定目的 IP 地址的数据包
（5）获取数据包的详细信息，首部的各字段，包括源IP，目的IP，源端口，目的端口，源MAC，目的MAC等，将数据内容通过gbk方式解码
（4）侦听指定协议的数据包
（5）侦听含有指定数据的数据报包
（5）保存选中的包到本地


#### 2.设计思路
（1）本软件使用的主要模块和功能：
	a. 抓包模块
	b. 数据包分析模块
	c. 线程控制模块


（2）模块间调用关系
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181230150056520.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0ODM4NjQz,size_16,color_FFFFFF,t_70)


#### 3.具体实现过程
（1）启动程序，展示用户界面
（2）获取当前网卡列表，用户指定要操作的网卡
（3）获取当前过滤规则，可通过协议，源IP，目的IP，关键字进行过滤，也可为空
（4）展示数据包基本信息
（5）根据用户点击的内容，对该包进行解析，显示详细内容

#### 4.模块功能清单
Main.java  程序入口
MyInterface.java  程序界面类
NetworkCard.java  网卡类
|__ getDevices() 获取网卡列表
PacketCapture.java  抓包类
|-- run()  重写多线程的run方法，开启抓包线程
|-- showTable() 将抓到包的信息添加到列表
|-- getpacketlist()  其他类通过此方法获取Packet的列表
|-- TestFilter()  设置过滤规则
|__ getObj()   将抓到的包的基本信息显示在列表上，返回信息的String[]形式
PacketAnalyze.java  解析包类
|-- packetClass() 根据包的类型选择不同的方法进行解析
|-- IPanalyze() 解析IP数据包
|-- ICMPanalyze() 解析ICMP数据包
|-- TCPanalyze() 解析TCP数据包
|__UDPanalyze() 解析UDP数据包

#### 5.运行截图
![在这里插入图片描述](https://img-blog.csdnimg.cn/20181230150107559.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0ODM4NjQz,size_16,color_FFFFFF,t_70)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2018123015021942.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0ODM4NjQz,size_16,color_FFFFFF,t_70)

