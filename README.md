# deeplang project
deeplang语言是一种自制编程语言，由来自浙大和中科大的同学共同完成，并由华为的老师指导。该项目来源于浙江大学和华为合作的深度科研计划。
   
我们致力于将deeplang语言打造为具有鲜明内存安全特性的面向IoT场景的语言，设计过程中参考Rust的安全机制，但又根据IoT场景的特性选择了更合适的解释执行的模式。这是一种静态类型、强类型语言，按照C-style设计语法，同时支持面向对象、过程式和逻辑式的混合范式。
   
deeplang的独特安全特性帮助其具有一定的竞争力。作者正在持续的开发和迭代中。


---
# How to build

``` bash
cd src/parsers
antlr4 -Dlanguage=Cpp DLLexer.g4  DLParser.g4 -visitor -o ./gen
cd ../..
mkdir build
cd build
cmake ..
make
```
