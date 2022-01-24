get_next_line ver 1.0 - Patchwerk
======
can't believe this worked
---

### Name
get_next_line -- 파일의 한 줄을 반환함.

### Synopsis
\#include "get_next_line.h"<br>
<u>char *</u><br>
get_next_line(<u>int fd</u>);<br>

### Description
get_next_line() 함수는 정수 fd에 해당되는 파일 디스크립터의 개행 혹은 EOF 전까지 해당되는 한줄의 문자열을 반환합니다. 내부적으로 stdlib.h의 malloc과 free, unistd.h의 read 함수를 사용합니다.

### Return Value
성공적으로 읽은 경우: 해당 파일 디스크립터로 지시된 파일의 개행 혹은 EOF 전까지의 문자열 하나를 반환.<br>
읽기 실패 혹은 빈파일의 경우: NULL을 반환.

---

## CAUTION!!!
이 함수는 null guard가 불완전 합니다.<br>
이 함수는 함수 도중의 오류가 나더라도 NULL이 아닌  반환값을 반환하는 경우가 있습니다. 이 경우 반환값의 개행 등을 보장할 수 없습니다.
