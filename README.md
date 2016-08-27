# Язык программирования Fun.

В данный момент разрабатывается интепретатор языка и продолжается развитие AST языка.

Закладываемые фичи.

* Интерперетируемый язык программированния основан на парсере Bison и лексере Flex. 
* Использует динамическую, не строгую, утиную типизацию. 
* Поддерживает парадигмы структурного, объектно-ориентированного и функционального программирования.
* Похож на Python и Lua.
* JIT компиляция с помощью LLVM и возможно libjit.
* FFI интерфейс с помощью libffi.

## Типы языка 
* Целые числа 
* Плавающие числа
* Строки
* Булевые выражения
* Пустой тип Nil
* Словари
* Списки
* Пользователькие классы
* Функции

## Синтаксис
1. Определение переменных
```
a = 42
b = 3.1415
c = "Lorem ipsum"
d = false
e = true
g = nil
f = fun() end
h = {
    a = 42
    b = 3.1415
    c = "Dictionary member"
}
j = [0:1:10]

```
2. Присваивание
```
a, b = 42, 13
a += 12
b *= 13
```

3. Условные оператор
```
foo = 42
if foo > 30:
    print "foo more than 30"
else
    print "foo less than 30"
end

if foo < 30:
    print "foo less than 30"
elif foo > 50:
    print "foo more than 50"
else
    print "other"
end
```
4. Операторы цикла
```
foo = 10
while foo > 0:
    print foo
end

foo = 10
while foo > 0:
    print foo
    if foo < 4:
        break
    end
end

for i = 0; i < 10; nil:
    print i
    i = i + 1
end
```
5. Функции
```
fun function1()
    print "function1"
end

function1()

fun function2(a)
    print "function 2 " + a
end
function2(42)

fun function3(a)
    ret 42 + a
end
foo = function3(43)
print "function 3 result " + foo

fun() 
    print "function 4" 
end()

fun(f)
    print "function 5 " + f()
end(fun()
    ret "function 6"
end)

fun()
    ret fun() print "function 7" end
end()()
```

### Скриншотики :)

![Github Logo](/fun/doc/1.png)
