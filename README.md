# duipai_ji
> 替代 [``XC-duipai``](https://github.com/wchengk09/XC-duipai) 的强大工具，你值得拥有

## 作者
``wzh`` ``jzq``

## 版本
``v1.21``

## 初始化
在 ``duipai_ji`` 文件下的终端输入 ``./install.sh`` 命令安装对拍脚本。

默认编译参数: 

``
g++ src/duipai.cpp -O2 -O3 -Ofast -o duipai -std=c++17 -Wall -lreadline -ltermcap -w -pthread
``


将标准程序写入 `ans.cpp` ，需要对拍的程序写入 `my.cpp` ，在 `make_data.cpp` 中写入数据生成代码。如果程序需要使用 special judge ，在 ``spj.cpp`` 中写入 special judge 代码。


## 操作指南
```
help (h) -- help

init [ file ... ] -- initialize files

comp (c) [ file ... ] -- compile
    [ compile_option ... ] - customize compile

test (t) [ file ... ] -- test current data
    [ --diff | -d ] - check differences
    [ --cat | -c ] - cat
    [ --spj | -s ] - compare by special judge

retest (rt) -- retest all the files in historydata 
    [ --spj | -s ] - compare by special judge

run (r)  -- start duipaiing
    [ --cores | -c ] [ thread_count ] - run by using [ thread_count ] threads
    [ --spj | -s ] - compare by special judge
    [ --Timelimit | -T ] [ time ] - set [ time ] as running time limit
    [ --Caselimit | -C ] [ case ] - set [ case ] as running case limit

cat [ file ... ] -- concatenate and print files

clear -- clear the screen

clean -- delete all files in the folder except system files

rm [ file ... ] -- remove files and directory ( same as bash )

quit (q) -- quit
```

## 系统文件名及（简称）
```
install.sh
make_data.cpp (mk)
data.txt (data) (d)
ans.cpp (ans) (a)
ans.txt (ans) (a)
my.cpp (my) (m)
my.txt (my) (m)
spj.cpp (spj) (s)
make_data.cpp + ans.cpp + my.cpp + spj.cpp (all)
data.txt + ans.txt + my.txt (all)
src
exe
historydata
rundata
```