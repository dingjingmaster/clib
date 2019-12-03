# gobject

### 工具之 GOB2

> The gobject builder
> GOB2 是一个简单的预处理器，简化了GObject类的创建。
> GOB2 主要用于C或C++中创建GObject。

#### gob2 [选项]... 文件

|               |     |
| ---           | --- |
| -? -h --help  | 显示帮助 |
| --version     | 显示版本 |
| -w --exit-on-warn | 警告时返回错误码并退出 |
| --no-exit-on-warn | 仅在错误时退出(默认) |
| --for-cpp     | 产生c++代码 |
| --no-extern-c | 不在头文件中加入 `extern c` |
| --no-gnu      | 不用GNU C 扩展生成任何代码，更严格 |
| --no-touch    | 不 touch 文件，除非真的改变了 |
| --no-touch-headers | 要禁用 |
| --always-private-header | 创建<basename>-private.h 即使文件可能时空的 |
| --ondemand-private-header | 当有私有数据、方法的时候，创建私有头文件(默认) |
| --no-private-header | 没有私有成员和数据 |
| --m4          | 用m4处理源码(多语言支持) |
| --m4-dir      | 将搜索m4文件的打印目录 |
| -n --no-write | 不要写任何输出文件，只检查输入文件的语法 |
| --no-lines    | 不要把 '#line' 语句打印到输出中，用于调试自动生成的代码 |
| --no-self-alias | 不要创建 self 和 selfclass 类型的别名及 Self、IS-Self、Self-CLASS宏 |
| --no-kill-underscores | 不要从方法名中删除初始下划线 |
| --always-private-struct | 始终在公共头文件中包含私有指针。这对于作为库的一部分的文件非常有用，并且你可以在不破坏为二进制兼容的情况下添加某些私有数据成员 |
| -o --output-dir | 将输出放入的目录 |
| --file-sep[=c] | 替换默认的'-'文件名分隔符 |
| --gtk3         | 使用gtk3 |

#### 类型名

- 类型声明以`:`分割
- 第一个一般为 `namespace` 
- 例如:

  `Gtk:New:Button` 宏将变为 `GTK_IS_NEW_BUTTON` 和 `gtk_TYPE_NEW_BUTTON`

#### 输出文件

- 文件名就是上边提到的类型名，以 `-` 分割，且为小写；上述示例结果为 `gtk-new-button.h` `gtk-new-button.c`，如果使用C++，则扩展名为`.cc` 如果有任何私有成员或私有变量，则文件名为: `<basename>-private.h`

#### 在输出文件中包含正常的C代码

- 要在输出C文件中直接包含某些代码，在空行以`%{`开头，在空行以`%}`结尾。这些部分将按给定的顺序显示在输出文件中。
- 也可以写在另一个`.h`文件中，在现在这个文件中包含进来。
- 也可以写在私有文件中`.hp`，这将使代码进入私有头文件。
- 如果希望某些代码出现在外部`c`和保护定义之前，可以将他们放在`headertop(或ht)`部分
- 如果要包含注释可以将他们放入`all(或a)`部分
- 如果希望出现在所有文件顶部的代码进入`all top(或at)`部分

```c
%alltop{
    //
%}

%ctop{
    /* this will be at the very top of the C file */
    /* Requires 2.0.18 */
%}

%headertop{
    /* this will be on top of the public header */
%}

%privateheader{
    /* this will go into the private header file */
%}

%h{
    /* will be included in the header */
    void somefunc(int i);
%}

%a{
    /* will be included in all files */
%}

%afterdecls{
    /* between the declarations and the method implementations */
    /* Requires gob version 2.0.16 */
%}

%{
    /* will be included in the C file */
    void somefunc(int i)
    {
        /* some code */
    }
%}

```