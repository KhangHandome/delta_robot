/* 
 * Include 
*/
#include "Task_manager.h"
#include "stdint.h"
static uint8_t NumOfTask = 0 ; 
static Task_manager_t myTask[MAX_TASK];
// Khai báo task manager
void Task_Manager(void)
{
    uint8_t index = 0 ; 
    for ( index = 0 ; index < NumOfTask ; index ++ )
    {
        if ( myTask[index].state != Task_Idle )
        {
            myTask[index].Function();
            myTask[index].state = 0 ; 
        }
    }
}
// Khai báo task init
void Task_Init(Task_manager_t task)
{
    myTask[NumOfTask].state = task.state;
    myTask[NumOfTask].Function = task.Function;
    NumOfTask ++ ;    
}
// Khai báo task deinit 
void Task_Deinit(Task_manager_t task);
