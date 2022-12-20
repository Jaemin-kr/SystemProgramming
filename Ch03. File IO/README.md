# Ch03. File IO(파일 입출력)

---

프로세스가 파일을 사용할때

- open()을 이용해서 파일시스템안의 파일을 찾음
- read()/write()를 이용하여 파일안의 데이터를 read/write
- 파일을 다 사용하고 나면 close()를 이용하여 파일사용을 멈춤

<aside>
💡 System call과 stdio library비교 ⭐️

</aside>

read, write → 버퍼링없는 입출력(unbuffered I/O)

호출할 때마다 매번 커널안의 시스템 호출이 실행됨

dup, fcntl, sync, fsync, ioctl함수를 설명

## File Descriptor(파일 서술자)

---

 커널에서 열린 파일들이 파일서술자를 통해 지칭되며 음이아닌 정수값을 가짐. 기존 파일을 열거나 새 파일을 생성할 때 커널은 해당 파일에 대한 파일 서술자를 프로세스에게 돌려줌

 파일을 읽거나 쓸 때에는 open이나 creat가 돌려준 파일 서술자를 read나 write의 인수로 넘겨주어 해당 파일을 지정한다.

 STDIN_FILENO(0), STDOUT_FILENO(1), STDERR_FILENO(2)는 <unistd.h>에 정의되어 있다.

- 열려진 모든 파일은 파일 서술자 값을 가지고 있다.
- file descriptor를 얻는 방법
    - open(), creat()함수의 리턴값
- 우리가 파일을 읽거나 쓸 때 파일 서술자를 이용하여 구분한다.
- file descriptor는 index of user file descriptor table이다.
- file descriptor의 범위
    - 0 ~ OPEN_MAX(63, 대부분의 시스템에서)
    - sysconf(OPEN_MAX): 프로세스가 오픈할 수 있는 가장 많은 파일 수

## 파일 입출력 함수

---

### open( )

---

```c
#include <fcntl.h>

int open(const char *pathname, int oflag, .../mode_t mode */);
	
//Returns: file descriptor if OK, -1 on error
```

- open/create a file and return file descriptor.
- pathname: The. name of the file to open or creat(열거나 생성할 파일의 이름)
- oflag
    - 액세스 모드를 정의하며 아래 세 가지 모드 중 하나는 반드시 설정되어야 한다.
    - O_RDONLY: Open for reading only
    - O_WRONLY: Open for writing only
    - O_RDWR: Open for reading and writing
- oflag(optional)
    - O_CREAT: 파일이 존재하지 않으면 생성,  mode argument가 필요하다.
    - O_EXCL: O_CREAT를 지정했는데 해당 파일이 이미 존재하면 에러를 발생시킨다. 파일이 이미 존재함을 알 수 있음
    - O_APPEND: 파일 쓰기(write)시 자료를 파일 끝에 추가
    - O_TRUNC: 이미 존재하는 파일을 쓰기전용이나 읽기 쓰기 용도로 열었을 때, 그 파일의 길이를 0으로 줄임(WRONLY인 경우 내용을 삭제, 디스크에서 파일을 삭제하는 것이 아닌 길이를 0으로 만듦)
    - O_SYNC: write함수의 결과가 모두 메모리에 저장되었는지를 알려줌. write의 결과가 물리적으로 저장 되어있음을 보장한다.(HDD에 기록되는것은 아님)
- mode
    - 새 파일이 생성된 경우 파일의 권한을 지정함
    - O_CREAT가 지정되어 있지 않으면 명시하지 않음
- return value
    - 새로운 file descriptor를 반환하거나 에러가 발생할 시 -1을 반환한다.
    - 새로운 file descriptor는 사용하지 않는 디스크립터 중 가장 낮은 숫자를 사용한다.
- ex
    
    ```c
    int fd;
    fd = open("/etc/passwd", O_RDONLY);
    fd = open("/etc/passwd", O_RDWR);
    
    fd = open("ap", O_RDWT | O_APPEND);
    fd = open("ap", O_RDWR | O_CREAT | O_EXCL, 0644);
    //옵션을 지정하여 OR 브트 연산을 통해 옵션을 지정할 수 있다.
    ```
    

### creat( )

---

```c
#include <fcntl.h>

int creat(const char *pathname, mode_t mode);

//Returns FD for opened write-only, -1 on error	
```

- creat()함수는 open(pathname, O_CREAT | O_WRONLY | O_TRUNC, mode);와 동등하다.
- (중요) 오직 파일이 WRONLY로만 열였을 경우에

### close( )

---

```c
#include <unistd.h>

int close(int filedes);

//Returns 0 if ok, -1 on error
```

- 열려있는 파일을 닫는 함수: 프로세스가 종료되면 열려있는 모든 파일은 커널에의해 자동으로 닫힌다.
    
    → open 되어있는 file의 경우는 한정적이므로 명시적으로 파일을 close해주어야 한다.
    

### read( )

---

```c
#include <unistd.h>

ssize_t read(int filedes, void *buf, size_t nbytes);

//Return number of bytes read, 0 if EOF, -1 on error
```

- filedes로부터 nbytes를 읽어들임, 읽은 바이트 수를 반환.
    - read()는 현재파일의 offset부터 읽어들인다
    - 리턴하기 전에 오프셋은 실제로 읽은 바이트의 수만큼 증가한다.
- return value
    - 성공: read한 바이트 수만큼 리턴
    - 0: 파일을 다 읽음
    - -1: error
- 실제로 읽어들인 바이트의 수가 요청한 바이트 수보다 적은 경우
    - read하려는 바이트 수보다 파일의 전체 바이트 수가 작은 경우
    - 터미널 장치를 읽는 경우 보통은 한번에 한 줄의 끝까지 읽게 된다.
    - 네트워크에서 자료를 읽을 때 네트워크 안의 버퍼링 때문에 요청된 개수보다 적은 값이 반환될 수 있다.
    - 파이프나 FIFO를 읽을 때, 파이프에 담긴 바이트들이 요청된 것보다 적으면 read는 파이프에 담긴 바이트들만 읽는다.

### write( )

---

```c
#include <unistd.h>

ssize_t write(int fildes, const void *buf, size_t nbytes);

//Return number of bytes written, -1 on error
```

- 열린 파일에 자료를 기록할 때 사용
- 디스크에 남은 용량이 없거나 주어진 프로세스에 대한 파일 크기 한계를 넘었을 때  오류가 발생한다.
- write는 파일의 현재 오프셋에서 시작한다. 지정된 파일을 열 때 O_APPEND옵션을 설정하면 오프셋이 파일의 끝으로 설정되고 쓰기연산이 진행된다. 쓰기 연산이 성공하면 파일의 오프셋이 실제로 기록된 바이트 수만큼 증가한다.

### read/write 예제(입출력 효율성)

---

```c
#include <stdio.h>
#include <unistd.h>
#define BUFFSIZE 8192

int main(void){
	int n;
	char buf[BUFFSIZE];

	while((n=read(STDIN_FILENO, buf, BUFFSIZE))>0)
		if(write(STDOUT_FILENO, buf, n) != n)
			printf("write error\n");

		if(n<0)
			printf("read error\n");
		exit(0);
}
```

<aside>
✅ 실행 결과(입력값이 출력됨)
./a.out
hello, world.
hello, world.
Are you enjoying this class?
Are you enjoying this class?

</aside>

<aside>
💡 BUFFSIZE의 값은 어떻게 선택?

</aside>

### lseek( )

---

```c
#include <unistd.h>

off_t lseek(int filedes, off_t offset, int whence);

//Return new file offset, -1- on error, 성공시 새 파일의 오프셋 반환
```

- 일반적으로 파일을 열었을 때의 오프셋은 0으로 초기화 된다.(O_APPEND 옵션이 지정되지 않았을 때)
- 열린 파일의 오프셋을 명시적으로 설정할 때 lseek()함수를 사용한다.
- whence
    - SEEK_SET: 파일의 시작에서부터 offset byte만큼 이동한 위치로 오프셋이 지정됨
    - SEEK_CUR: 현재 오프셋에서 부터 offset byte만큼 더한 위치로 offset이 설정됨, 이 때 offset은 양수, 음수값을 가질 수 있음
    - SEEK_END: 파일의 오프셋이 파일의 크기 더하기 offset으로 설정됨, offset은 음수일수도, 양수일 수도 있음
    - SEEK_DATA: 파일의 다음 데이터를 찾아서 오프셋을 이동
    - SEEK_HOLE: 파일의 다음 hole을 찾아서 오프셋을 이동
- lseek 호출이 성공하면 새 파일 오프셋이 반환되므로 오프셋 바이트를 0으로 설정하고 SEEK_CUR옵션을 사용하면 파일의 현재 오프셋을 알 수 있음
    
    ```c
    off_t currpos;
    currpos = lseek(fd, 0, SEEK_CUR);
    ```
    
- 파일의 오프셋은 파일의 현재 크기보다 클 수 있다. 그런 경우 write를 호출하면 비어있는 공간에는 hole이 채워지고 파일이 확장된다. 명시적으로 기록되지 않았기 때문에 0으로 읽힌다
- hole의 데이터를 읽으면 0을 return 한다.

<aside>
👉 hole을 사용하는 이유?
규격화 시켜야할 파일이 있을 때 데이터 공간을 낭비하지만 데이터 처리를 더 간단히 하기 위해서

</aside>

### lseek( ) 예제

---

```c
off_t curpos;
curpos = lseek(fd, 0, SEEK_CUR);

lseek(fd, 0, SEEK_SET); //커서를 처음위치로
lseek(fd, 0, SEEK_END); //오프셋을 파일의 마지막 위치로
lseek(fd, -10, SEEK_CUR); //오프셋을 파일의 마지막위치에서 10만큼 뒤로 옮김
lseek(fd, 100, SEEK_END); 
//오프셋 위치를 파일의 끝에서 100만큼 앞으로, 빈 공간은 hole로 채움
```

```c
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	int fd;
	if((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");
//FILE_MODE is defined as 644 in "apue.h"

	if(write(fd, buf1, 10) != 10)
		err_sys("creat error");
//offset = 10

	if(lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
//offset now = 16384

	if(write(fd, buf2, 10) != 10)
		err_sys("buf2 write error");
//offset now = 16394

	exit(0);

}
```

<aside>
👉 출력결과
size: 16394

</aside>

- 홀에는 디스크 block이 할당되는가?
- hole파일과 nohole파일 비교
    - file.hole → 8 blocks are allocated
    - file.nohole(a file of the same size, but without holes.) → 20 blocks are allocated

## File System

---

 파일은 file data와 file’s attribute를 이용하여 구분하며 file’s attribute를 inode(파일에 대한 대부분의 정보를 가지고 있음)라고 부른다.

- 파일의 종류는 달라도 inode의 크기는 같다.
- File system = 파일이 어떻게 저장되어 있는가?
:파일의 내용(data)와 파일을 처리하기 위한 정보(inode, attribute)로 구성되어 있다
- 왜 data와 정보가 분리되어있는가?
: 커널이 파일을 열기 전 해당 파일의 inode정보를 보고 판단해야하기 때문이다.
- data와 inode는 디스크의 어디에 배치되어 있는가?
: 유닉스 시스템은 inode와 data영역을 구분하여 디스크에 저장하고 있다.
- inode의 indexing
: inode에는 어느위치에 data block이 존재하는지에 대한 정보를 가지고 있으며 파일의 크기가 크다면 단일간접리스트를 생성하여 통로를 확장시킨다. → 용량은 늘어나지만 데이터에 접근할 때 소요되는 시간은 증가한다.

![Untitled](Ch03%20File%20IO(%E1%84%91%E1%85%A1%E1%84%8B%E1%85%B5%E1%86%AF%20%E1%84%8B%E1%85%B5%E1%86%B8%E1%84%8E%E1%85%AE%E1%86%AF%E1%84%85%E1%85%A7%E1%86%A8)%20566793d18e654930a10ee5d14c55eaac/Untitled.png)

/etc/inittab에 접근하는 방법

- /(root)의 inode로 간다.
- /의 데이터 블록에 간다
- etc의 inode정보를 찾아 etc의 inode로 이동한다
- etc/의 데이터블록으로 이동한다.
- inittab의 inode정보를 찾아 inittab의 inode로 이동한다
- inittab의 data block로 이동한다.

<aside>
👉 처음 파일에 접근할 때는 다음과 같은 과정이 필요하지만 open이후에는 fd를 가지고 있기 때문에 위 과정이 필요하지 않다.

</aside>

## File in process

---

: 커널은 파일에 대한 metadata를 관리해야 한다. 프로그램에 관한 정보는 PCB(Process Control Block)에 저장되며, file에 대한 정보는 FCB(File Control Block)에 저장된다. 프로그램은 execution, 파일은 open/read

<aside>
👉 프로그램과 파일의 실행과정 차이 알아보기

</aside>

- FCB: 커널공간에서 파일을 관리하기위한 metadata이다
    - size, type, owner, protection, index to data block, device, acces location(offset)등의 정보가 저장되어 있다.
    - inode정보와 offset정보가 저장되어 있다.
- 만약 두개의 프로세스가 같은 파일을 사용한다면 각각의 프로세스가 FCB를 따로 생성하여 open한다.

<aside>
👉 한 사용자가 파일에 대한 허가정보를 수정한다면?
불일치와 비효율성의 문제를 적절하게 고려하여 signal을 통해 변화를 알려주거나 한장소에만 데이터를 저장하는 방식이 있다.

</aside>

- Share metadata(공통된 내용을 공유, vnode)
: 공통된 내용은 FCB를 공유하고 offset과 같이 따로 관리해야 하는 FCB는 분리하여 관리한다.

<aside>
👉 vnode에는 size, owner, protection과 같은 공유되는 내용이 존재하고, file table에는 offset과 같이 따로 분리해야하는 내용을 프로세스마다 따로 관리한다.

</aside>

- file descriptor table
: fd를 저장하고 있는 포인터 배열이다. 음수는 존재하지 않고 0, 1, 2는 표준 입출력과 에러에 할당되어 있다.

## open( )

---

![Untitled](Ch03%20File%20IO(%E1%84%91%E1%85%A1%E1%84%8B%E1%85%B5%E1%86%AF%20%E1%84%8B%E1%85%B5%E1%86%B8%E1%84%8E%E1%85%AE%E1%86%AF%E1%84%85%E1%85%A7%E1%86%A8)%20566793d18e654930a10ee5d14c55eaac/Untitled%201.png)

## dup( ) and dup2( )

---

```c
#include <unistd.h>

int dup(int fildes);
int dup2(int fildes, int filedes2);

//both return new file descriptor, -1 on error
```

- dup()
: 사용가능한 가장 낮은 수의 파일서술자를 리턴함, 사용가능한 fd중 가장 낮은 fd를 리턴
- dup2()
: 비어있는 FD중 가장 낮은 FD를 filedes2에 복제함

![Untitled](Ch03%20File%20IO(%E1%84%91%E1%85%A1%E1%84%8B%E1%85%B5%E1%86%AF%20%E1%84%8B%E1%85%B5%E1%86%B8%E1%84%8E%E1%85%AE%E1%86%AF%E1%84%85%E1%85%A7%E1%86%A8)%20566793d18e654930a10ee5d14c55eaac/Untitled%202.png)

## sync(), fsync(), fdatasync()

---

: write작업을 바로 디스크에 쓰면 딜레이가 발행하기때문에 평소에는 버퍼에 그내용을 저장하고 있다가 나중에 물리적으로 기록을 한다. 커널이 버퍼를 비우는 방법은 버퍼가 가득 찼을 때 디스크에 기록하는 방식과 주기적으로 update를 통해서 버퍼를 비우는 방식이 있다. 이 때는 deamon프로그램을 이용한다.

- 비교적 바로 기록을 해야하는 data의 경우에는 sync함수를 통해 디스크에 바로 기록한다.
→ 바로 기록해야하는 data?
: 파일의 변경내용이 다수의 프로세스에 영향을 끼칠 경우 바로바로 디스크에 기록을 해 주어야 한다.
- sync(): 버퍼에 있는 모든 block들을 sync시킨다.
- fsync(): 파일의 수정된 block만(data + attribute) 가져간다. (수정된 블록은 어떻게 아나?, 메모리 블록의 metadata를 보고 판단한다.)
- fdatasync: attribute가 아닌 data만 write한다.

## fcntl()

---

이미 열린 파일의 속성을 변경

```c
#include <fcntl.h>
int fcntl(int fd, int cmd, ... /* int arg */);

return: 성공시 cmd에 따라 다름, 오류 시 -1
```

### ioctl()

---