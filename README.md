# duipai_ji
> 抵抗 ``m_duipai`` 的强大工具，你值得拥有

## 作者
``wzh`` ``jzq``

## 版本
``v1.2_Mac``

## 初始化
在 ``duipai_ji`` 文件下的终端输入 ``bash install.sh`` 命令安装对拍脚本。

默认编译参数: 
``g++ duipai.cpp -O2 -O3 -Ofast -o duipai -std=c++17 -Wall -lreadline -ltermcap && ./duipai``

将标准程序写入 `ans.cpp` ，需要对拍的程序写入 `my.cpp` ，在 `make_data.cpp` 中写入数据生成代码。


## 操作指南
```
help (h) -- help
comp (c) [ file ... ] -- compile
    [ compile_option ... ] - customize compile
cat [ file ... ] -- concatenate and print files
test (t) [ file ...] -- test current data
    [-d] check differences
    [-c] cat
clean -- delete all files in the folder except system files
run (r)  -- start duipaiing
    [-c] [ thread_count ] duipaiing by using [ thread_count ] threads
clear -- clear the screen
quit (q) -- quit
```

## 系统文件名及（简称）
```
install.sh
make_data.cpp (mk)
make_data
ans.cpp (ans) (a)
ans.txt (ans) (a)
ans
my.cpp (my) (m)
my.txt (my) (m)
my
data.txt (data) (d)
make_data.cpp + ans.cpp + my.cpp (all)
data.txt + ans.txt + my.txt (all)
```