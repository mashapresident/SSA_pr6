# SSA_pr6

## Створення образу Docker
Для початку створимо файл [dockerfile](dockerfile),який буде використовуватись для створення Docker-образу.Цей Dockerfile завантажує базовий образ ubuntu, встановлює build-essential(містить компілятор gcc) та Valgrind, а також задає робочу директорію.

>$ docker build -t pr6 .

Після цього ми можемо запустити докер-контейнер

>$ docker run -it pr6

Докер контейнер запущено. Тепер, щоб копіювати файл у контейнер, нам потрібно вийти з контейнеру у робочу директорію(не зупиняючи роботу контейнеру!!!). **Ctrl+P**, **Ctrl+Q**. Дізнаємось docker id.

>$ docker ps
>
>CONTAINER ID    IMAGE     COMMAND       CREATED          STATUS          PORTS     NAMES
>
>f3d4f2ab3f70    pr6       "/bin/bash"   41 seconds ago   Up 40 seconds             focused_meninsky

Це нам потрібно буде, щоб скопіювати файл у контейнер 

>$ docker cp uar.c f3d4f2ab3f70:/home/masha/Documents/SSA_pr6

де uar.c - файл, що ми його копіюємо,

f3d4f2ab3f70 - CONTAINER ID

/home/masha/Documents/SSA_pr6 - директорія у контейнері

>Successfully copied 2.05kB to f3d4f2ab3f70:/home/masha/Documents/SSA_pr6

Тепер повертаємось до контейнеру командою

>$ docker exec -it f3d4f2ab3f70 /bin/bash

>\# ls
>
>uar.c

## Вміст файлy [uar.c](uar.c)
"Test Case #9: Use-after-return. Поверніть адресу локальної змінної з функції."
```
#include <stdio.h>

int* foo() {
    int local_var = 42; 
    return &local_var; 
}

int main() {
    int* ptr = foo(); 
    printf("%d\n", *ptr); 
    return (*ptr == 42);
}
```
### Пояснення
Проблема полягає у тому, що ми намагаємось використовувати локальну змінну у головній функції, хоча після відпраювання функції foo() локальна змінна більше не існує, так як і її адреса.Хоча сама адреса нікуди не зникла, її використання стає недійсним, тому що пам'ять, яка була відведена під цю локальну змінну, більше не зарезервована для програми. Ця область пам’яті може бути перепризначена іншими функціями або навіть системою для інших потреб. Через це подальший доступ до цієї адреси стає потенційно небезпечним.

>\# gcc -g uar.c -o uar
>
>uar.c: In function 'foo':
>
>uar.c:5:12: warning: function returns address of local variable [-Wreturn-local-addr]
>
>    5 |     return &local_var;
>
>\# ./uar
>
>Segmentation fault (core dumped)

>\# valgrind ./uar
>
>==27== Memcheck, a memory error detector
>
>==27== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
>
>==27== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
>
>==27== Command: ./uar
>
>==27==
>
>==27== Invalid read of size 4
>
>==27==    at 0x1091C4: main (uar.c:10)
>
>==27==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
>
>==27==
>
>==27==
>
>==27== Process terminating with default action of signal 11 (SIGSEGV): dumping core
>
>==27==  Access not within mapped region at address 0x0
>
>==27==    at 0x1091C4: main (uar.c:10)
>
>==27==  If you believe this happened as a result of a stack
>
>==27==  overflow in your program's main thread (unlikely but
>
>==27==  possible), you can try to increase the size of the
>
>==27==  main thread stack using the --main-stacksize= flag.
>
>==27==  The main thread stack size used in this run was 8388608.
>
>==27==
>
>==27== HEAP SUMMARY:
>
>==27==     in use at exit: 0 bytes in 0 blocks
>
>==27==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
>
>==27==
>
>==27== All heap blocks were freed -- no leaks are possible
>
>==27==
>
>==27== For lists of detected and suppressed errors, rerun with: -s
>
>==27== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
>
>Segmentation fault (core dumped)







