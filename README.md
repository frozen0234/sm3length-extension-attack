# sm3length-extension-attack

姓名：刘金星

学号：202000460060

git账户：frozen0234

sm3的长度扩展攻击

长度扩展攻击：

首先选取任意的一条消息r1，对其进行填充得到m，并进行hash得到x1

随意选取消息r2作为攻击，计算m||r2的hash得到x2。

以第一次hash的结果x1作为iv值对r2进行hash得到x3。

如果x2与x3相同那么视为攻击成功。

结果如图：

![image](https://user-images.githubusercontent.com/106589212/181068809-641dfc1a-3eec-4ec3-a589-74339e26a8d3.png)
