## Deeplang help design proposal


### Deeplang help

usage: dp [options] filename

用法：dp [选项] 文件名

支持的文件类型：

- .dp文件

- .ast文件

- .wasm文件

#### 1. -d

**优雅地**dump各种文件

.ast中间输出。

```shell
./dp -d ./xx.dp
./dp -d ./xx.ast
./dp -d ./xx.wasm
```

#### 2. -h

打印help信息

```help
./dp -h
./dp --help
```

#### 3. -v

打印版本信息，deepvm的版本信息
```help
./dp -v
./dp --version
```

#### 4. -o

输出文件

- 输出编译生成的.wasm文件

- 输出解析出的.ast文件

```shell
./dp ./xx.dp -o ./xx.ast
./dp ./xx.dp -o ./xx.wasm
```

#### 5. -i

进入REPL模式，支持函数执行。

在REPL模式之下，加冒号前缀的方式表示调用内嵌函数：

- :memstat，支持打印内存状态;

- :exit，退出REPL模式;

```shell
eric@Eric-PC:~/GitHub/deeplang/build$ ./dp --help
[Deepvm v1.0]
Deepvm is a language VM for deeplang. 
The frontend contains parser, lexer and codegen. 
The backend is a wasm VM.
usage: 
  dp [options] filename
options:
  -h, --help                   Print this help message
  -v, --version                deepvm version
  -o, --output                 Output .ast or .wasm file
  -d, --dump                   pretty print .dp, .ast or .wasm file                             
  -i, --interactive            REPL，enter interactive mode after executing 'script'

```



**参考设计**： Lua help

```shell
eric@Eric-PC:~/Downloads/lua-5.4.1/src$ ./lua --help
./lua: unrecognized option '--help'
usage: ./lua [options] [script [args]]
Available options are:
  -e stat  execute string 'stat'
  -i       enter interactive mode after executing 'script'
  -l name  require library 'name' into global 'name'
  -v       show version information
  -E       ignore environment variables
  -W       turn warnings on
  --       stop handling options
  -        stop handling options and execute stdin
```