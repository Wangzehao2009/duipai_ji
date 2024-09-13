# duipai_ji
> 抵抗 ``m_duipai`` 的强大工具，你值得拥有
## 版本
v1.1
## 快速开始
将标准程序放入 `ans.cpp` ，您的程序放入 `my.cpp` ，在 `make_data.cpp` 中编写数据生成器

编译并运行 `duipai.cpp` ，执行指令 `r` 

错误样例的输入为 `data.txt` ，答案为 `ans.txt` ，您的输出为 `my.txt`
## 帮助
```
help (h) -- help
comp (c) -- recompile
run (r)  -- start checking
quit (q) -- quit
test (t) -- test by data.txt and ans.txt
clear    -- clear the screen
```

## 编译参数·
``g++ duipai.cpp -O2 -O3 -Ofast -o duipai -std=c++14 -Wall -lreadline -ltermcap && ./duipai``
