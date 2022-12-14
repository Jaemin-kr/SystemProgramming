# Ch.11 Thread

---

- 개념
- process vs thread
- Thread identification
- Thread creation
- Thread Termination
- Thread Syncronization
    - Mutexes
    - Conmdition variables

## 11.1 소개

---

 프로세스의 내부로 들어가 하나의 프로세스 환경안에 여러게의 thread of control을 이용하여 여러개의 과제를 수행하는 방법을 살펴봄. 그러한 제어가닥 또는 한 줄기의 실행흐름을 thread라고 하며 Thread는 한 프로세스 안의 동일한 프로세스 구성요소들(FD, Memory 등)을 공유한다.

 여러 사용자가 하나의 자원을 공유하는 프로그램을 작성할 때 일관성을 보장하기위해 동기화 매커니즘을 소개한다.

## 11.2 스레드의 개념

---

프로세스는 한번에 한개의 일만 수행하지만 프로세스 내에 제어가닥을 여러개 둔다면 하나의 프로세슨는 한번에 여러 개의 일을 수행할 수 있다.

스레드의 장점

- 정보를 공유하기 쉽다(메모리주소와 파일 디스크립터를 공유함)
- Throughput이 개선될 수 있다.(각각의 일을 Interleaved(병렬적, 독립적)하게 처리될 수 있기 때문에)
- 반응시간 개선(대화식 프로그램에서 여러개의 스레드를 사용자의 입력과 출력으로 분리하여 프로그램 반응시간을 개선)
- 새로운 프로세스를 생성하는데 드는 비용이 낮다.(fork 와 공유하는 부분이 다름)
    
    ![Untitled](Ch%2011%20Thread%20d85fdd666d434d73a9280ad152495fef/Untitled.png)
    
    - Thread - specific information
        - Thread ID
        - Register values
        - Stack
        - Scheduling priority
        - A signal mask
    - Sharable information among thread in a process
        - Text section
        - Global data
        - Heap
        - File descriptor

## 11.3 스레드 식별

---

 프로세스ID는 시스템안에서 고유하지만 스레드ID는 하나의 프로세스안에서만 의미가 있다. thread ID의 자료형은 pthread_t자료형을 가지며 Unsigned long integer(음이아닌 정수값)을  가진다.

두 스레드ID를 비교하는 함수

```c
#include <pthread.h>

int pthread_equal(pthread_t tid1, pthread_t tid2);

//return not 0 if same tid, 0 if not same 
```

함수를 호출한 스레드 ID를 리턴하는 함수

```c
#include <pthread.h>

pthread_t pthread_self(void);

//return: 호출한 스레드의 스레드ID
```

용도 - 스레드가 자신의 ID를 알아낸 후 pthread_equal을 이용하여 어떤 구조체가 자신을 위한 구조체인지 확인하는 것

Ex. Master thread가 대기열에 작업을 넣어두고 어떤 작업이 worker thread에 배정되는지를 threadID에 의해 제어된다고 할 때 Master thread가 새로운 작업들을 작업 대기열에 추가한다. 일꾼 스레드는 대기열에서 작업을 가져와 처리하는데 아무작업을 가져가는것이 아닌 Master thread가 각 작업 구조체에 그작업을 처리해야할 threadID를 집어넣어 각 작업을 구체적인 스레드에 배정한다. 각 일꾼 스레드는 자신의 threadID가 표시되어 있는 작업만 대기열에서 뽑아 처리한다 → **과제**

![IMG_0214.jpg](Ch%2011%20Thread%20d85fdd666d434d73a9280ad152495fef/IMG_0214.jpg)

## 11.4 스레드 생성

---

## Mutex

---

pthread에서 각각의 스레드가 동일 메모리에 접근하여 발생하는 오류를 줄이기 위해 사용