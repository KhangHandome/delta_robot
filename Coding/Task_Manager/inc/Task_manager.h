#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_
#include "Hybrid_Servo.h"
#define MAX_TASK 100 
// Các trạng thái của task 
typedef enum{
    Task_Idle,   // không chạy
    Task_Runing, // đang chạy
    Task_Stop    // dừng chạy 
} State_t ; 
typedef struct 
{
    State_t state;
    TaskFunc Function;
} Task_manager_t;

// Định nghĩa 1 task trong task_manager 
typedef void (*TaskFunc)();
// Khai báo task manager
extern void Task_Manager(void);
// Khai báo task init
extern void Task_Init(Task_manager_t task);
// Khai báo task deinit 
extern void Task_Deinit(Task_manager_t task);
#endif