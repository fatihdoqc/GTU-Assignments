 
#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <common/types.h>
#include <gdt.h>

namespace myos
{
    namespace hardwarecommunication{
        class InterruptHandler;
    }

    struct CPUState
    {
        common::uint32_t eax;
        common::uint32_t ebx;
        common::uint32_t ecx;
        common::uint32_t edx;

        common::uint32_t esi;
        common::uint32_t edi;
        common::uint32_t ebp;

        /*
        common::uint32_t gs;
        common::uint32_t fs;
        common::uint32_t es;
        common::uint32_t ds;
        */
        common::uint32_t error;

        common::uint32_t eip; // Instruction Pointer
        common::uint32_t cs;    // Code Segment
        common::uint32_t eflags;
        common::uint32_t esp; // Stack Pointer
        common::uint32_t ss;        
    } __attribute__((packed));
    
    
    enum State { READY , WAITING, FINISHED};

    class Task
    {
    friend class TaskManager;
    private:
        static common::uint32_t pIdCounter;
        common::uint8_t stack[4096]; // 4 KiB
        CPUState* cpustate;
        common::uint32_t pPid = 0;
        common::uint32_t pId = 0;
        State taskState;
        common::uint32_t waitPid;
    public:
        Task(GlobalDescriptorTable *gdt, void entrypoint());
        Task();
        common::uint32_t getId();
        ~Task();
    };
    
    
    class TaskManager
    {
        friend class hardwarecommunication::InterruptHandler;
    private:
        Task tasks[256];
        int numTasks;
        int currentTask;
        GlobalDescriptorTable *gdt = nullptr;
        int getIndex(common::uint32_t index);
    protected:
        void PrintProcessTable();
        common::uint32_t GetPid();
        common::uint32_t ForkTask(CPUState* cpustate);
        common::uint32_t AddTask(void entrypoint());
        common::uint32_t ExecTask(void entrypoint());
        bool WaitTask(common::uint32_t esp); // The pid is in the register b.
        bool ExitTask();
    public:
        TaskManager();
        TaskManager(GlobalDescriptorTable *gdt);
        ~TaskManager();
        bool AddTask(Task *task);
        CPUState* Schedule(CPUState* cpustate);
    };
    
    
    
}


#endif