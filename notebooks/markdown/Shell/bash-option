>1 在/etc/shells里有记录本机提供的shell，这些shell本身是可执行文件。

>2 在/etc/passwd可以查找固定用户所对应的shell。

>3 使用type可以查看bash命令的属性（三种基本命令的哪一种以及别名等信息）。通过type可以查找某个命令具体是来自于哪个地方，通过type–a可以查找该命令的执行顺序。

>4 使用alias可以对命令进行别名。

##shell变量##

####变量的设置规则####

* 变量用=赋值（在终端中赋值的变量会在终端重启后消失!!!，因为进程结束）。
* 等号两边不能直接用空格符，若有空格需要用单引号或者双引号。
>双引号内的字符保持原有的特性。
>单引号内的字符为一般字符，用以保护空格和特殊字符避免受到shell的特殊解释。 

* 可使用转义字符将特殊字符转换成一般字符。
* 在一串命令中，还需要调用其他命令以提供信息；可以使用反单引号`或者 $。
* 可以使用`$name`累加内容。
* 若普通变量需要在其他子进程执行，需要用export来使该变量变成环境变量。
* 大写为系统变量，小写为用户变量。
* 使用unset取消变量。
* 使用PATH=$PATH:/home/bin
>PATH=”$PATH”:/home/bin

	>PATH=${PATH}:/home/bin

####环境变量的功能####
**note:**
自定义变量（set命令所定义的变量）：仅在当前进程可用，即使子进程也不可以。
 环境变量是可以在子进程使用的 。

##命令别名与历史变量##

####命令别名设置：alias，unalias####
**note:**
alias在终端中直接设定是保存在内存之中的，不会写入到文件；所以打开另外一个终端并不会生效.


##bashshell的操作环境##

####路径与命令查找顺序####

**命令的查找，执行顺序：**

- 以相对，绝对路径来执行命令：例如`/bin/ls`或者`./ls`（定向执行命令）
- 以`alias`对某命令进行别名（并保证该命令的名字可以执行别名）
- bash的内置命令
- 以`$PATH`这个变量的项目顺序找到第一个命令来执行

#### bash的登录与欢迎信息：/etc/issue,/etc/issue.NET,/etc/motd####

#### bash的环境配置文件####
    所有的配置需写入配置文件以后，方可在下一次使用。
    
**Login与non-loginshell**

* Loginshell会读取的两个配置文件：
	- /etc/profile：系统整体设置，最好不要修改，它会根据用户ID决定不同的配置。
	- `~/.bash_profile` 与 `~/.bash_login` 与  `~/.profile`：属于个人设置
	
**/etc/profile**
该文件设置的变量主要有：PATH，MAIL，USER，HOSTNAME，HISTSIZE。
调用的外部数据有：/etc/inputrc，/etc/profile.d/*.sh，/etc/sysconfig/i18n

bash操作接口的颜色，语系ll与ls命令的别名、vi的命令别名、which的命令别名等。如果你需要帮所有用户设置一些共享的命令别名时，可以在这个目录下创建拓展名为.sh的文件，并将所需要的数据写入即可。

**~/.bash_profile**
bash在读完整体配置以后，会依次读取个人配置：`~/.bash_profile `;`~/.bash_login`; `~/.profile`（这三个文件只会读取一个，就前原则）。

* non-loginshell会读取的配置文件流程：
	- `~/.bashrc`
	- 其他相关配置文件（`/etc/man.config`:主要是MANPATH这个变量；`~/.bash_history`和`~/.bash_logout`）。

**注意：**每次重新打开终端的时候，`.bashrc`会自动执行一次，而`.bash_profile`不会。

##PATH详解##

从第一部分中，我们已经知道bash配置文件的读取流程是：
`/etc/profile 先于 ~/.bash_profle 先于 ~/.bash_login 先于 ~/.profile`。
>如果需要设置对全体用户都可用的path，我们可以在/etc/profile中设置，反之，在后面三个文件中设置。
设置完成后，重新启动终端或者直接source .filename就可以使用。