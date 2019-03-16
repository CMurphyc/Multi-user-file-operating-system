# Multi-user-file-operating-system
## OS Course Design

现实中我们一般使用的OS可以粗化为五层层次，自上到下分别是：用户接口、文件目录系统、存储控制模块、逻辑文件系统与文件信息缓冲区以及最后的物理文件系统。

我们此次课程设计的层次我个人将之划分为三个层次：

①	用户接口可视化UI调用指令区

②	文件目录系统ManagerDisk

③	存储控制模块FCB

最后剩下的就是如何去设计一个通用且继承性好的类了.

概要设计大致如下图所示:

![image](https://github.com/CMurphyc/Multi-user-file-operating-system/blob/master/view1.png)

![image](https://github.com/CMurphyc/Multi-user-file-operating-system/blob/master/view2.png)

完成基本的文件系统create、open、close、read/write等基本功能，并且实现要求以外的如下所示所有功能:

* : format:对文件存储器进行格式化

* : exit : 退出系统

* : help : 输出所有支持的指令

 &nbsp;&nbsp;① mkdir:用于创建子目录

 &nbsp;&nbsp;② rmdir : 用于删除子目录

 &nbsp;&nbsp;③ ls : 用于显示目录

 &nbsp;&nbsp;④ cd : 用于更改当前目录

 &nbsp;&nbsp;⑤ write : 用于写文件

 &nbsp;&nbsp;⑥ read : 用于读文件

 &nbsp;&nbsp;⑦ open : 用于打开文件

 &nbsp;&nbsp;⑧ close : 用于关闭文件

 &nbsp;&nbsp;⑨ create : 用于创建文件

 &nbsp;&nbsp;⑩ rm : 用于删除文件
