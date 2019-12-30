# corewar  
В данном проекте требуется написать алгоритмическую игру Corewar ([почитать об игре](http://www.codenet.ru/progr/asm/Core-Wars.php)).
Проект состоит из 2 частей:  
1) Ассемблер.  
2) Виртуальная машина.
Хорошо рассказано о сути проекта у пользователя [VBrazhnik](https://github.com/VBrazhnik/Corewar/wiki). В моем проекте практически все сделано по данному cookbook'у, здесь же будет выноска по самым ключевым моментам.

### Ассемблер
Данная часть программы транслирует приходящий файл с чемпионом в байт код по заданным стандартам.  
При трансляции проводится валидация входящего файла. Проверяются следующие случаи:  
1) поступающий файл имее расширение .s  
2) в файле есть имя и комментарий к чемпиону  
3) все комментарии оформлены верно.  
4) все команды валидны  
5) все команды имеют валидное количество и тип аргументов  
Ассемблеру можно подавать несколько файлов, и все они будут переведены вбинарные файлы с расширением .cor в которые будут записаны байт коды чемпионов. Но если среди файлов будет невалидный, то трансляция будет осуществлена до этого файла, файлы после него транслированы не будут.
У ассемблера есть флаг **-а**, который вместо записи в бинарный файл байт-кода выводит в stdout исполняемый код чемпиона в специальном формате (с информацией об отступах и размерах команд в байтах).  
Каждая команда записывается в файл в следующем виде: код команды -> код аргументов(если у данной команды он нужен) -> сами аргументы.

### Виртуальная машина
Принимает до 4 файлов с байт-кодами чемпионов (при стандартных настройках). Назначает чемпионам номера, размещает исполняемые коды на арене и инициализирует в начале исполняемого кода каждого чемпиона каретку (каждая новая каретка ставится в начало списка кареток). Каретка - это процесс, который выполняет код, на котором она стоит в памяти. После создания каретка никак не привязана ни к какому чемпиону. 
У каретки есть:  
1) 16 регистров, в которых она может хранить значения (при инициализации первых кареток в первый регистр заносится номер игрока создавшего данную каретку).
2) Флаг carry - влияет на то, будет или нет данной кареткой исполнятся команда zjmp. Некоторые действия могут менять значение флага.
3) Цикл в который каретка в последний раз выполняла команду live. Если в момент проверки каретка выполняла команду live больше CYCLE_TO_DIE циклов назад, то каретка погибает.

## Правила игры
Игра ведется до тез пор, пока на арене жива хоть одна каретка. Каретки перемещаются по арене и исполняют код, на который они встают. После перемещения каретка считывает байт, на который она встала. Если считанное значение не является кодом какой либо операции (меньше 1 или больше 16), то в следующем цикле каретка переходит на следующий байт. Если же считанное значение является кодом какой либо операции, то каретка ждет соответствующее число циклов (у каждой операции свое), и после этого пытается выполнить полученную операцию. Если у данной операции есть код аргументов, то она считывает следующий байт, и сверяет, может ли у данной операции быть таой код аргументов:  
а) если нет, то каретка не выполняет операцию, и на следующем цикле передвигается на то количество байт, которое занимают те аргументы, код которых она считала.
б) если да, то каретка в соответствии с кодом аргументов соответствующим образом считывает аргументы и выполняет команду, после чего передвигается на столько байт вперед, сколько занимает команда.
Каждые CYCLES_TO_DIE циклов (изначально в настройках по умолчанию данное значение равно 1536 циклов) проводится проверка.  

### Проверка
Виртуальная машина пробегает по всему списку кареток, и проверяет, когда в последний раз каретка выполняла команду live. Если это событие было больше CYCLES_TO_DIE циклов назад, то каретка умирает (удаляется из списка кареток). После прохода всех кареток проверяется, сумели ли все каретки в последние CYCLE_TO_DIE циклов в обще сумме выполнить команду live больше NBR_LIVE раз (в по умолчанию настроенной машине это число равно 21). Если успели, то CYCLES_TO_DIE уменьшается на CYCLES_DELTA циклов (в по умолчанию настроенной машине это число равно 50), если нет, то CYCLES_TO_DIE остается без изменений, но если количество проверок без уменьшения CYCLES_TO_DIE достигает значения MAX_CHECKS (в по умолчанию настроенной машине это число равно 10), то значение CYCLES_TO_DIE уменьшается принудительно. Количество операций live с момента последней проверки сбрасывается.  
Как только значение CYCLES_TO_DIE становится меньше 0, все каретки умирают.
To be continued ...
