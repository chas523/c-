# c++

sondowanie liniowe
```
пример: 
m  = 11  
keys = 1 3 17 22 13 45 24 29 
 
(условие ключи должны быть неотрицательное целочисленное значение.) 
формула: h(k)=k mod m 

1) h = 1 % 11 = 1 (вставляем на позицию о индексе 1) 
index: 0 1 2 3 4 5 6 7 8 9 10 
value    1 

2) h = 3 % 11 = 3 (вставляем на позицию о индексе 3) 
index: 0 1 2 3 4 5 6 7 8 9 10 
value    1   3 

3)  h = 17 % 11 = 6 (вставляем на позицию о индексе 6) 
index: 0 1 2 3 4 5  6 7 8 9 10 
value    1   3     17 

.....

(если на позиции уже есть значение, то просто добовляем один к h)
(m != 2 and  m != 10)
```


sondowanie kwadratowe
```
все точно также 
только  вместо того что бы добовлять один , мы будем  G(i)=i^2
например  24 % 11 = 2 (2 два занято, добовляем )



```
