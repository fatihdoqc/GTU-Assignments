
#include <syscalls.h>
 
using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;
 
SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
:    InterruptHandler(interruptManager, InterruptNumber  + interruptManager->HardwareInterruptOffset())
{
}

SyscallHandler::~SyscallHandler()
{
}


void printf(char*);

enum SYSCALLS {EXIT, GETPID, WAITPID, FORK, PRINTF, EXEC};

int myos::getPid(){
    int pId = -1;
    asm("int $0x80" : "=c" (pId) : "a" (SYSCALLS::GETPID));
    return pId;
}

void myos::sys_exit(){
    asm("int $0x80" : : "a" (SYSCALLS::EXIT));
}

void myos::fork(){
    asm("int $0x80" : : "a" (SYSCALLS::FORK));
}

void myos::fork(int *pid){
    asm("int $0x80" :"=c" (*pid): "a" (SYSCALLS::FORK));
}

void myos::waitpid(common::uint8_t wpid){
    asm("int $0x80" : : "a" (SYSCALLS::WAITPID) , "b" (wpid));
}

int myos::exec(void entrypoint()){
    int ret;
    asm("int $0x80" : "=c" (ret) : "a" (SYSCALLS::EXEC) , "b" ((uint32_t)entrypoint));
    return ret;
} 

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;
    
    switch(cpu->eax)
    {
        case SYSCALLS::GETPID:
            cpu->ecx = InterruptHandler::sys_getpid();
            break;
        case SYSCALLS::EXIT:
            if(InterruptHandler::sys_exit()){
                return InterruptHandler::HandleInterrupt(esp); // Task finished get the next task.
            }
            break;
        case SYSCALLS::FORK:
            cpu->ecx = InterruptHandler::sys_fork(cpu);
            return InterruptHandler::HandleInterrupt(esp);
            break;
        case SYSCALLS::PRINTF:
            printf((char*)cpu->ebx);
            break;
        case SYSCALLS::WAITPID:
            if(InterruptHandler::sys_waitpid(esp)){
                return InterruptHandler::HandleInterrupt(esp); 
            }
            break;
        case SYSCALLS::EXEC:
            esp = InterruptHandler::sys_exec(cpu->ebx);
            break;
        default:
            break;
    }

    
    return esp;
}

