# Проект Tidy-Boomerang

Язык программирования Fun. 

В данный момент разрабатывается AST.

Закладываемые фичи.

* Интерперетируемый язык программированния основан на парсере Bison и лексере Flex. 
* Использует динамическую, утиную типизацию. 
* Поддерживает парадигмы структурного, объектно-ориентированного и функционального программирования.
* Похож на Python и Lua.
* JIT компиляция с помощью LLVM.

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

### Скриншотики :)

![Github Logo](/Fun/doc/1.png)