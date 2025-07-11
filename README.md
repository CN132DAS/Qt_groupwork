# Qt_groupwork
程设Qt小组作业
## 注意事项
存档文件夹位于qt编译文件夹内（例如Qt_groupwork\build\Desktop_Qt_6_9_0_MinGW_64_bit-Debug\save），而非在Qt_groupwork文件夹内。
## 如何使用？
打开后可以新建或读取已有存档。其中新建存档时通过“存档名.dat”文件是否存在判断存档是否已存在。

在已有存档打开的情况下通过左侧前三个按钮向其中插入文字、图片或文件，此外可以随时通过滚轮实现视野的缩放。

点击“新建连接”后再点击任意两个不重复的文字、图片或文件。即可绘制连接曲线。

点击“编辑”后可以**单击**后按后退键删除组件，与组件相连的曲线将自动删除。也可**双击**图片或文件打开对应的图片或文件，也可以**双击**文字以对其进行修改，注意，由于Qt的图片加载方式，双击打开图片进行修改后需要点击“文件”中的刷新键进行刷新才可以使更改在界面上显示，同时请**务必不要修改图片或文件的名字，以免产生错误**。

点击“拖动”后可以将鼠标**放在空白场景**中拖动实现视角的平移，也可以将鼠标**放在组件上**拖动实现组件的平移，与组件相连的连接曲线将自动计算位置并更新。

AI模块接入了deepseek，点击后会唤出AI窗口，上方为输入窗口，下方则为输出窗口，AI在**节点图模式**下会对用户提供的关键词给出一个树状图的提纲，而在**对话模式**中将会对用户的输入进行解释，用户可以对输出进行选中与复制。
## 写在最后
CN_132DAS：

感谢全体小组成员在程序结构构思和AI模块的初步编写等方面对本作业的辛勤付出。

事实证明从头学一门新语言很难，尤其是Qt这种引入了大量信号与槽、父子关系等机制，同时还具有若干存在bug的函数的语言（我依稀记得为了修一个鼠标平移的bug换了无数次的实现方式）。虽然最后因为时间原因仍然有许多设想中的功能未能实现，但看着大家的作业一步步变得可以使用的确是一个非常令人高兴的事。
