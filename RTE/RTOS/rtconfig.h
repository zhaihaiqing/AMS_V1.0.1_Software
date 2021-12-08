/* RT-Thread config file */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

#if defined(__CC_ARM) || defined(__CLANG_ARM)
#include "RTE_Components.h"

/* 开启 FinSH */
#define RT_USING_FINSH

#if defined(RTE_USING_FINSH)
#define RT_USING_FINSH
#endif //RTE_USING_FINSH

#endif //(__CC_ARM) || (__CLANG_ARM)

// <<< Use Configuration Wizard in Context Menu >>>
// <h>Basic Configuration
// <o>Maximal level of thread priority <8-256>
//  <i>Default: 32
#define RT_THREAD_PRIORITY_MAX  32		//设置系统最大优先级
// <o>OS tick per second
//  <i>Default: 1000   (1ms)
#define RT_TICK_PER_SECOND  1000		//设置系统的节拍,1ms
// <o>Alignment size for CPU architecture data access
//  <i>Default: 4
#define RT_ALIGN_SIZE   4				//字节对齐，默认4字节对齐
// <o>the max length of object name<2-16>
//  <i>Default: 8
#define RT_NAME_MAX    8				//设置对象名称的最大长度，默认8个字符，一般无需修改
// <c1>Using RT-Thread components initialization
//  <i>Using RT-Thread components initialization
#define RT_USING_COMPONENTS_INIT		//设置使用组件自动初始化功能，默认需要使用，开启改宏则可以使用自动初始化功能
// </c>

#define RT_USING_USER_MAIN				//开启，打开user_main功能，默认需要开启，这样才能调用RTT的启动代码，main线程堆栈空间默认为256

// <o>the stack size of main thread<1-4086>
//  <i>Default: 512
#define RT_MAIN_THREAD_STACK_SIZE     256

// </h>

// <h>Debug Configuration
// <c1>enable kernel debug configuration
//  <i>Default: enable kernel debug configuration
//#define RT_DEBUG						//定义RT_DEBUG_INIT宏则开启debug模式，默认关闭，若开启，可使用LOG日志
// </c>
// <o>enable components initialization debug configuration<0-1>
//  <i>Default: 0
#define RT_DEBUG_INIT 0					// 启用组件初始化调试配置，设置为 1 则会打印自动初始化的函数名称			
// <c1>thread stack over flow detect
//  <i> Diable Thread stack over flow detect
//#define RT_USING_OVERFLOW_CHECK		// 关闭栈溢出检查
// </c>
// </h>

// <h>Hook Configuration
// <c1>using hook
//  <i>using hook
//#define RT_USING_HOOK					// 是否 开启系统钩子功能
// </c>
// <c1>using idle hook
//  <i>using idle hook
//#define RT_USING_IDLE_HOOK			// 是否 开启空闲线程钩子功能
// </c>
// </h>

// <e>Software timers Configuration
// <i> Enables user timers
#define RT_USING_TIMER_SOFT         0	// 关闭软件定时器功能，为 1 则打开
#if RT_USING_TIMER_SOFT == 0
    #undef RT_USING_TIMER_SOFT
#endif
// <o>The priority level of timer thread <0-31>
//  <i>Default: 4
#define RT_TIMER_THREAD_PRIO        4	// 设置软件定时器线程的优先级，默认为 4
// <o>The stack size of timer thread <0-8192>
//  <i>Default: 512
#define RT_TIMER_THREAD_STACK_SIZE  512	// 设置软件定时器线程的栈大小，默认为 512 字节
// </e>

// <h>IPC(Inter-process communication) Configuration
// <c1>Using Semaphore
//  <i>Using Semaphore
#define RT_USING_SEMAPHORE				// 设置是否使用 信号量
// </c>
// <c1>Using Mutex
//  <i>Using Mutex
//#define RT_USING_MUTEX				// 设置是否使用 互斥量
// </c>
// <c1>Using Event
//  <i>Using Event
//#define RT_USING_EVENT				// 设置是否使用 事件集
// </c>
// <c1>Using MailBox
//  <i>Using MailBox
#define RT_USING_MAILBOX				// 设置是否使用  邮箱
// </c>
// <c1>Using Message Queue
//  <i>Using Message Queue
#define RT_USING_MESSAGEQUEUE			// 设置是否使用 消息队列
// </c>
// </h>

// <h>Memory Management Configuration
// <c1>Dynamic Heap Management
//  <i>Dynamic Heap Management
//#define RT_USING_MEMPOOL      		// 是否使用 内存池
//#define RT_USING_HEAP					// 是否使用 内存堆
// </c>
// <c1>using small memory
//  <i>using small memory
#define RT_USING_SMALL_MEM				// 是否使用 小内存管理
// </c>
// <c1>using tiny size of memory
//  <i>using tiny size of memory	
//#define RT_USING_TINY_SIZE			// 是否使用 小体积的算法，牵扯到 rt_memset、rt_memcpy 所产生的体积
// </c>	
// </h>

// <h>Console Configuration
// <c1>Using console
//  <i>Using console
#define RT_USING_CONSOLE				// 控制台宏开关
// </c>
// <o>the buffer size of console <1-1024>
//  <i>the buffer size of console
//  <i>Default: 128  (128Byte)
#define RT_CONSOLEBUF_SIZE          128	// 设置控制台数据 buf 大小，默认 128 byte
// </h>

#if defined(RT_USING_FINSH)				// 开关 FinSH 组件
    #define FINSH_USING_MSH				// 使用 FinSH 组件 MSH 模式
    #define FINSH_USING_MSH_ONLY		// 仅使用 MSH 模式
    // <h>Finsh Configuration
    // <o>the priority of finsh thread <1-7>
    //  <i>the priority of finsh thread
    //  <i>Default: 6
    #define __FINSH_THREAD_PRIORITY     5	// 设置 FinSH 组件优先级，配置该值后通过下面的公式进行计算
    #define FINSH_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 8 * __FINSH_THREAD_PRIORITY + 1)
    // <o>the stack of finsh thread <1-4096>
    //  <i>the stack of finsh thread
    //  <i>Default: 4096  (4096Byte)
    #define FINSH_THREAD_STACK_SIZE     512		// 设置 FinSH 线程栈大小，范围 1-4096
    // <o>the history lines of finsh thread <1-32>
    //  <i>the history lines of finsh thread
    //  <i>Default: 5
    #define FINSH_HISTORY_LINES         1		// 设置 FinSH 组件记录历史命令个数，值范围 1-32

    #define FINSH_USING_SYMTAB					// 使用符号表，需要打开，默认打开
    // </h>	
#endif

// <<< end of configuration section >>>

#endif
