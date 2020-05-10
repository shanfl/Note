## kotlin

#### 2. 变量,常量,类型

#####  变量声明

  > `var exp:Int = 5`

#####  kotlin 内置数据类型

  - String
  - Char
  - Boolean
  - Int
  - Double
  - List
  - Set
  - Map

#####  只读变量

  > `val exp:Int = 5`

#####  编译时常量  `const val MAX_EXP :Int = 5

#####  tip: 查看字节码:idea 中 输入 `show kotlin` 

#####  Kotlin中的java 基本数据类型

  - java 引用类型 基本类型

#### 3. 条件语句

#####   if /else    if /else if/else 

#####   比较运算符

|  运算符   | 描述  |
|  ----    | ----  |
| ...  | ... |
| ===  | 计算2个实例是否指向同一引用 |
| !==  | 计算2个实例是否不指向同一引用 |

#####   条件表达式

  ```kotlin
  val exp = 10
  var c = if(exp == 1)
  {
  	10
  }
  else if (exp == 2)
  {
  	11
  }
  else
  {
  	12
  }
  ```

#####   range : 优化 if/else 分支

  ```kotlin
  var c = if(exp == 1)
  		10
  	else if(exp in 2..4)
  		11
  	else if (exp in 5..8)
  		12
  	else
  		13  
  ```

#####  when 

```kotlin
var race = "gonme"
val faction = when(race){
	"dwarf"->"keepers of miners"
	"gnome"->"Keepers of Mines"
	"orc"->"free people of the rolling hills"
	"human"->"free people of the rolling hills"
}
```

```kotlin
var h = when(healthPoint){
	100 -> "is in excellent condition"
	in 90..99 -> "has a few scratches"
	in 75..89 -> if (isBleed){
		"has ....quit quickly"
	}else
		"has some minor wounds"
	in 15..74 -> "looks pretty hurt"
	else -> " is in awful condition"
}
```



##### string 模板  $Name  ${}

```kotlin
var name:String = "ruiqiu"
var age:Int = 10
println("hello,  $name" + " " +  "${if(age >= 20) "lady" else "girl"}" + " !")
```

#### 4. 函数

##### 函数结构

| 可见性修饰符 | 函数声明关键字 |函数名 |函数参数 |返回类型 | { | ... | } |
| ---- | ---- ---- ---- ---- | ---- | ---- | ---- | ----|----|----|
| private   | fun  | formatFunc | (healthPoint:Int,isBlessed:Boolean) | :String|{ | ... | }|

##### 默认实参

##### 单表达式函数

```kotlin
private fun CastFireball(numFireBalls:Int = 2) =
	println("a grass of fireball spirngs into existnece.")
```

##### Unit 函数  函数没有返回值,函数定义中没有`return`

##### 具名函数参数  dart语言类似

##### Nothing类型

1. 没有返回值,跟Unit函数有类似
2. Nothing意味着函数不可能成功执行完成

##### Java 文件级函数

##### 函数重载

##### 反引号中的函数名

1. 解决函数名冲突问题
2. 在测试文件中使用更`直观`的`易懂`的函数名

#### 5 匿名函数 & 函数类型

1. 匿名函数

   ```Kotlin
   fun main(args:Array<String>){
   	println({
   		var currentYear = 2018;
   		"Welcome to SimVillage ,Mayor! copyright $currentYear"
   	}())
   }
   ```

2. 匿名函数赋值给变量

   ```kotlin
   val greetingFunction:()->String = {
   	var currentYear = 2018;
   	"Welcome to SimVillage ,Mayor! copyright $currentYear"
   }
   ```

3. 隐式返回 如果需要返回而没有`return`, 匿名函数会自动返回函数体最后一行语句的结果

4. 匿名函数参数

   ```kotlin
   val greetFunction:(String)->String = { playerName ->
   	var currentYear = 2018;
   	"Welcome to SimVillage ,Mayor! copyright $currentYear"
   }
   ```

5. `it` 关键字,如果匿名函数只有一个关键字,可以用`it`来表示

   ```kotlin
   val greetFunction:(String)->String = {
   	var currentYear = 2018;
   	"Welcome to SimVillage ,$it! copyright $currentYear"
   }
   ```

6. 多个参数

   ```kotlin
   val greetingFunction:(String,Int)->String = { playerName,numBuildings ->
   	
   	var currentYear = 2018;
   	println("numbuidings = $numBuildings")
   	"Welcome to SimVillage ,$playerName! copyright $currentYear"
   }
   ```

   

7. 类型推断

   ```kotlin
   val greetingFunction = { playerName:String,numBuildings:Int ->	
   	var currentYear = 2018;
   	println("numbuidings = $numBuildings")
   	"Welcome to SimVillage ,$playerName! copyright $currentYear"
   }
   ```

8. 函数的参数是一个 `函数`

   ```kotlin
   fun main(args:Array<String> )
   {
       val greetingFunction = {playerName:String,numBuildings :Int ->
           var currentYear:Int = 2020;
           println("Add $numBuildings houses");
           "Welcome to SimVillage, $playerName! (copyright $currentYear)"
       }
   
       runSimulation("Guyal",greetingFunction);
   }
   fun runSimulation(playerName:String,greetingFunction:(String,Int)->String)
   {
       val numBuilding:Int = (1..3).shuffled().last();
       println(greetingFunction(playerName,numBuilding));
   }
   ```

9. lambda 简略语法 

   > 如果一个函数的lambda参数排在最后,或者是唯一参数,那么,括住lambda值参的一对园括号可以省略

   ```kotlin
   fun main(args:Array<String> )
   {
       val greetingFunction = {playerName:String,numBuildings :Int ->
           var currentYear:Int = 2020;
           println("Add $numBuildings houses");
           "Welcome to SimVillage, $playerName! (copyright $currentYear)"
       }
   
       runSimulation("Guyal",greetingFunction);
   
       runSimulation("Guyal2"){playerName,numBuildings ->
           var currentYear:Int = 2020;
           println("Add $numBuildings houses");
           "Welcome to SimVillage, $playerName! (copyright $currentYear)"
       }
   }
   fun runSimulation(playerName:String,greetingFunction:(String,Int)->String)
   {
       val numBuilding:Int = (1..3).shuffled().last();
       println(greetingFunction(playerName,numBuilding));
   }
   ```

10. 函数内联

    > 内存问题,jvm中,lambda为对象实例,jvm为所有同lambda打交道的变量分配内存.
    >
    > 解决方案1. 使用lambda的fun  + `inline`

    ```kotlin
    fun main(args:Array<String> )
    {
        val greetingFunction = {playerName:String,numBuildings :Int ->
            var currentYear:Int = 2020;
            println("Add $numBuildings houses");
            "Welcome to SimVillage, $playerName! (copyright $currentYear)"
        }
    
        runSimulation("Guyal",greetingFunction);
    
        runSimulation("Guyal2"){playerName,numBuildings ->
            var currentYear:Int = 2020;
            println("Add $numBuildings houses");
            "Welcome to SimVillage, $playerName! (copyright $currentYear)"
        }
    }
    inline fun runSimulation(playerName:String,greetingFunction:(String,Int)->String)
    {
        val numBuilding:Int = (1..3).shuffled().last();
        println(greetingFunction(playerName,numBuilding));
    }
    ```

11. 函数引用

    >  用函数引用来代替lambda

    ```kotlin
    fun main(args:Array<String> )
    {
        val greetingFunction = {playerName:String,numBuildings :Int ->
            var currentYear:Int = 2020;
            println("Add $numBuildings houses");
            "Welcome to SimVillage, $playerName! (copyright $currentYear)"
        }
    
        runSimulation("Guyal",greetingFunction);
    
        runSimulation("Guyal2"){playerName,numBuildings ->
            var currentYear:Int = 2020;
            println("Add $numBuildings houses");
            "Welcome to SimVillage, $playerName! (copyright $currentYear)"
        }
    
        runSimulation("Guyal3",::PrintConstructionCost){ playerName:String,numBuildings:Int->
            var currentYear:Int = 2020;
            println("Add $numBuildings houses");
            "Welcome to SimVillage, $playerName! (copyright $currentYear)"
        }
    
        runSimulation("Guyal3",::PrintConstructionCost){ playerName ,numBuildings ->
            var currentYear:Int = 2020;
            println("Add $numBuildings houses");
            "Welcome to SimVillage, $playerName! (copyright $currentYear)"
        }
    }
    fun runSimulation(playerName:String,greetingFunction:(String,Int)->String)
    {
        val numBuilding:Int = (1..3).shuffled().last();
        println(greetingFunction(playerName,numBuilding));
    }
    
    fun runSimulation(playerName:String,
                      costPrinter:(Int)->Unit,
                      greetingFunction: (String, Int) -> String)
    {
        val numBuildings = (1..4).shuffled().last();
        costPrinter(numBuildings)
        println(greetingFunction(playerName,numBuildings));
    }
    
    fun PrintConstructionCost(numBuildings:Int )
    {
        val cost = 3000;
        println("construction cost: ${cost*numBuildings}");
    }
    ```

12. 函数类型作为返回值 / 返回值类型为函数 TODO
13. kotlin的lambda就是闭包 TODO
14. lambda & 匿名内部类 TODO

#### 6 null安全与异常

##### `public fun readline() :String?`

##### null 安全操作  `?.`

   1. `var a = readline()?.capitalize()`

   2. let

      ```kotlin
      fun readline():String?
      {
          var a = (1..3).shuffled().last();
          return when(a){
              1->null
              2->""
              else ->"3";
          }
      }
      
      fun readlineOp()
      {
          var a = readline()?.let {
              if(it.isNotBlank())
              {
                  it.capitalize()
              }else
              {
                  "Butterd Ale"
              }
          }
          println("readline op res = $a");
      }
      ```

##### `!!.`操作符（非空断言操作符）

```kotlin
var b = readline()!!.capilize();
```

##### 使用if判断null的情况

##### 空合并操作符： `?:`

```
var b = readline()?:"is NUll !!!!!"
```

##### 异常 todo

> ```
> fun main(...)
> {
> 	
> }
> fun proficiencyCheck(swordsJuggling:Int?)
> {
> 	swordJugging?:throw IllegalStateException("player cant juggle swords")
> }
> 
> class UnskilledSwordJugglerException():IllegalStateException("Player Cant juggle swords")
> ```
>
> 

1. 抛出异常  todo
2. 自定义异常  todo
3. 处理异常  todo

##### 先决条件函数  todo

- checkNotNull
- require
- requerNotNull
- error
- assert

##### null:真的一无是处吗？ todo

##### 已检查异常&未检查异常   todo

##### 可空性该如何保证  todo

#### 7 字符串

#### 8 数

#### 9 标准库函数

#### 10 List 与 Set

#### 11 Map

#### 12 定义类

##### 类的定义

##### 类的实例化

##### 类函数

##### 可见性&封装

##### 类属性

1. getter & setter
2. 属性可见性
3. 计算属性

#####  `包`

##### 深入： 细看 var 与 val 属性

##### 深入： 防范竟态条件

##### 深入：私有包

#### 13 初始化

##### 构造函数

1. 主构造函数

2. 在主构造函数里定义属性

3. 次构造函数

4. 默认参数
5. 命名参数

##### 初始化块

##### 属性初始化

##### 初始化顺序

##### 延迟初始化

1. 延迟初始化
2. 惰性初始化

##### 初始化陷阱

#### 14 继承

##### 基类 定义Room基类

##### 创建子类

##### 类型检测

##### Kotlin中的类层次

1. 类型转换
2. 智能类型转换

##### Any深入

#### 15 对象

##### object 关键字

1. 对象声明
2. 对象表达式
3. 伴生对象

##### 嵌套类

##### 数据类

1. toString
2. equals
3. copy
4. 解构声明

##### 枚举类

##### 运算符重载

##### NetHacker

##### 深入： 定义结构比较



#### 16 接口&抽象类

##### 1. 定义接口

##### 2. 接口实现

##### 3.默认实现

##### 4. 抽象类



#### 17 泛型

##### 1. 泛型类 定义

##### 2. 泛型函数

##### 3. 多泛型参数

##### 4. 泛型约束

##### 5. vararg关键字 与 get 函数

##### 6.in & out

##### 7. reified 关键字

#### 18 扩展

#### 19 函数式编程基础

#### 20 kotlin&java互操作

#### 21 用kotlin 开发首个android应用

#### 22 kotlin 协程简介





