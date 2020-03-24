## BUAA软件工程结对项目

### 目录结构
```
├─bin

├─core

├─GUI_EXE

│  ├─iconengines

│  ├─imageformats

│  ├─platforms

│  ├─styles

│  └─translations

├─myGUI


└─test
```
#### bin文件夹
包含intersect.exe可执行文件，-i path to input file -o path to output file，用法示例intersect.exe -i input.txt -o output.txt。
#### core文件夹
包含计算模块的源文件。
#### GUI_EXE文件夹
包含必要的GUI相关库文件和myGUI可执行文件。
#### myGUI文件夹
包含GUI源文件。
#### test
包含单元测试源文件。
### myGUI.exe使用说明
在GUI_EXE下直接点击myGUI.exe即可运行，或者在控制台下直接运行可执行文件。
#### solve按钮
点击后计算现有几何对象交点数目并绘制现有几何对象及交点。
#### deleteAll按钮
点击后删除现有全部几何对象并重绘画板。
#### addLine/deleteLine按钮
在下面的5个框中分别输入类型标识符('L','R','S')，第一个点横坐标，第一个点纵坐标，第二个点横坐标，第二个点纵坐标。（其中'L','R','S'分别代表直线，射线，线段），之后点击按钮addLine/deleteLine，则增加或删除相应的几何对象并重绘画板。
#### addCircle/deleteCircle按钮
在下面的三个框中分别输入圆心横坐标，圆心纵坐标，半径，之后点击按钮addCircle/deleteCircle，则增加或删除相应的几何对象并重绘画板。
#### ioHandler按钮
将输入文件放在myGUI相同目录下，在下面的框中输入文件的名称，点击按钮，即可增加文件中的几何对象并重绘画板。文件内规则如下：
- 第 1 行：一个自然数 N >= 1，表示输入的几何对象的数目。
- 第 2 行至第 N + 1 行：每行描述一个几何对象。具体格式如下：
    - 直线：L <x1> <y1> <x2> <y2>，表示通过点 (x1, y1) 和 (x2, y2) 的直线。输入保证给定两点不重合。
    - 射线：R <x1> <y1> <x2> <y2>，表示起点为 (x1, y1)，且通过点 (x2, y2) 的射线。输入保证给定两点不重合。
    - 线段：S <x1> <y1> <x2> <y2>，表示以 (x1, y1) 和 (x2, y2) 为端点的线段。输入保证给定两点不重合。
    - 圆：C <x> <y> <r>，表示以点 (x, y) 为中心，半径为 r 的圆。输入保证半径 r > 0。
为确保您的正常使用，请避免输入重合的几何对象。
