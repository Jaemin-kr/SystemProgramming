# Ch02. Unix System Overview


Unix OS 구조

applications

shell: command interpreter로 직접 구현을 하기도 하고 외부 프로그램을 불러와서 사용하기도 하는 텍스트로 동작하는 응용 프로그램이다.

system call: : write()함수, …, 시스템 콜 명령어를 통해 어플리케이션이 커널에 접근, 시스템의 안정성을 위해 system call을 통해서만 커널에 접근을 할 수있다.

kernel: OS에서 리소스를 통제, 운영체제의 핵심으로 모든 리소스를 관리하는 특별한 프로그램이다.

## Logging in


- 유닉스는 multi-user system이다, 유닉스는 여러 사용자가 계정을 가지고 접속할 수 있다.
- 유닉스 시스템에 로그인하기 위해서는 login name + password가 필요하다
- 시스템의 계정목록에 대한 파일은 /etc/passwd파일에 존재한다.
: login_name:password:UID:GID:comment:home_directory:shell
- directory와 directory사이의 /는 디렉토리와 디렉토리사이의 경계를 나타내며, /는 root directory로 최상위 디렉토리를 의미한다.

## Shell

- 커맨드라인 인터프리터로 사용자의 입력이나 실행된 커맨드를 표시한다.
- $는 셸 프롬프트를 의미한다

## File system

리눅스 파일시스템은 폴더(file name + attritribute pointer)와 파일로 구성된다. 파일은 트리구조로 계층적구조를 가진다.

<aside>
👉 리눅스에서는 저장된 데이터를 어떻게 관리하나?
: 트리구조를 이용하여 계층적으로 관리한다.

파일을 어떻게 디스크에 저장하는가?

</aside>

/root

/bin /etc /lib

ls, cp

- Attribute(특성)
: 파일의 특성을 서술하는 정보를 담고있는 구조체로 파일의 종류, 크기, 소유자, 접근권한, 마지막 수정 날짜등을 나타낸다. stat과 fstat함수는 한 파일의 모든 특성을 담은 구조체를 리턴한다. type, size, owner, permissioin, access time 등을 나타낸다.
- Filename
- NULL과 ‘/’를 파일이름으로 사용할 수 없다.
- BSD는 파일이름을 255글자로 제한한다.
- 새 디렉토리를 생성하면 .과 ..는 자동으로 생성되는데 현재디렉토리와 부모디렉토리를 가리킨다. root directory에서는 .와 ..이 같다.
- Pathname
    - 절대경로와 상대경로의 차이
    : 절대경로는 /(root)에서 부터 해당파일이 존재하는 위치까지의 경로를 나타낸 것이며 상대경로는 현재 작업하고 있는 폴더를 기준으로 해당 파일까지의 위치를 나타낸 것이다.
        
        ```bash
        pwd
        /home
        
        cd obama #상대경로 == cd ./obama
        pwd
        # /home/obama
        
        cd /usr/bin #절대경로
        pwd
        # /usr/bin
        
        cd #home directory로 이동 == cd ~
        pwd
        # /home/obama
        
        cd ~ #home directory로 이동
        cd - #직전 디렉토리로 이동
        ```
        

## Input and output

- File descriptor(파일 서술자)
: 커널이 한 프로세스가 접근하는 파일들을 식별하기 위해 사용하는 것으로 음이 아닌 정수값. 프로세스가 기존 파일을 열거나 새 파일을 생성하면 커널은 그 파일을 읽거나 쓸 때 사용할 파일 서술자를 리턴한다.
- 프로세스가 실행되면 아래 3개의 파일서술자는 기본적으로 실행된다.
    - 표준입력(STDIN_FILENO, 0)
    - 표준출력(STDOUT_FILENO, 1)
    - 표준오류(STDERR_FILENO, 2)

위의 파일서술자들은 별로의 설정없이 프로그램이 새로 실행되면 바로 연결된다.

<aside>
👉 C 라이브러리 함수와 시스템 프로그램(콜)의 차이는?
C라이브러리는 파일에 접근할때 파일이름과 구조체를 사용하지만, 시스템 콜은 파일 서술자를 이용하여 파일에 접근할 수 있다.

</aside>

## Programs and processes

- 프로그램
: 디스크에 있는 실행할 수 있는 파일이다.
디스크에있는 실행파일 커널은 디스크의 프로그램을 메모리로 읽어들여 실행
- 프로세스
: 실행파일을 메모리로 가져와 CPU가 실행하고 있는 프로그램이다.
실행되고 있는 프로그램의 한 인스턴스, 유닉스는 모든 프로세스에 대해 각자 고유한 식별자를 보장하는데 이를 프로세스 ID라고 하며 음이아닌 정수이다.
- Process ID: 프로세스를 구별하는 고유한 식별자이다.

```c
//자신의 프로세스 ID를 출력하는 프로그램
#include <apue.h>

int main(){
	printf("hello world form process ID %ld\n", (long)getpid());
	exit(0);
}
/*
getpid() -> 프로그램은 자신의 프로세스 아이디를 얻음
return pid_t이지만 long으로 캐스팅

```

## Error handling(오류 처리)

---

 에러가 발생했을 때 음수값이 리턴되며 errno.h에 에러의 종류에 따른 분류가 되어있다. 

대부분의 시스템 함수들은 오류가 발생하면 음수를 return한다. 또는 오류의 원인(파일이 존재하지 않음, 권한이 없음)을 알려주는 값이 errno라는 정수개체에 설정되는 경우도 있으며 15가지의 값이 존재한다.

 <errno.h>에는 errno에 설정될 수 있는 각 값에 대한 상수들이 정의되어 있다.

```c
#include <errno.h>

int main(int argc, char *argv[]){
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}

```

## User identification(사용자 식별)

---

- user ID(사용자 ID)
    - 시스템이 사용자를 식별하는데 사용하는 값
    - 시스템 관리자에 의해 고유한 값으로 설정됨
    - root나 superuser의 userID 값은 0
- group ID(그룹 ID)
    - 사용자들을 프로젝트나 부서별로 조직화하는데 사용, 그룹내의 사용자들은 같은 자원을 공유한다

<aside>
👉 왜 이름으로 사용자를 구분하지 않는가?
: 문자를 저장하려면 더 많은 디스크공간이 필요하고 사용자의 이름을 문자로 비교하게 된다면 비교하는데 시간이 더 많이 걸리기 때문이다.

</aside>

```c
int main(){
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}
```

## Signals(신호)

 프로세스간의 통신을 위한 수단으로 특정조건이 발생했음을 프로세스에게 알려주는 수단이다. 커널과 일반프로세스 사이에는 error와 프로세스의 종료에 관한 신호가 많이 전달된다.

 특정 조건이 발생했음을 프로세스에게 알려주는 기법으로 커널과 프로세스 사이에 동작한다. ex) 0으로 나누기, SIFGPE(floating 예외)

신호가 전송됐을 때 프로세스가 신호에 대해 할 수 있는일은 다음 세가지 중 하나이다.

- 신호를 무시함
- 기본 action실행(보통 프로세스를 종료한다)
- 사용자 정의 action실행 (신호를 처리할 함수가 호출되게 함)

<aside>
⭐ 커맨드 명령어는 System call이 아니다.
kill PID: process를 kill하라는 신호를 보내는 명령어

</aside>

## Time values(시간 값)

- Calendar time
    - 시스템 시간이다
    - ‘the Epoch’를 기준으로 흐른 시간(1970/01/01 00:00:00 기준)
    - 기본자료형 time_t
- Process time(CPU time, CPU가 사용된 시간을 의미하며 작동시간을 의미한다.)
    - 한 프로세스가 CPU의 자원들을 사용한 시간을 측정하는것으로 단위는 clock tick이다.(clock tick은 주로 50, 60, 100 ticks/seconds)의 값을 가진다.
    - 기본자료형 clock_t
    - clock time: 프로세스가 실행된 전체시간으로 다른프로세스의 수에 영향을 받음
    - user CPU time: 사용자 명령에 의해 소비된 CPU시간
    - system CPU time: 프로세스에 의해 커널이 소비한 CPU시간(read, write 실행하면 커널안에서 시스템 서비스에 소비된 시간이 프로세스에 부과
    
    → 사용자 CPU시간과 시스템 CPU시간을 합친것을 CPU시간이라고 함
    
    <aside>
    👉 Process time의 3가지 종류
    - clock time: 프로세스가 실행된 전체시간
    - user CPU time: 사용자 명령에 의해 소비된 CPU시간
    - system CPU time: 커널이 소비한 CPU시간
    
    </aside>
