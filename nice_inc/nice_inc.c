#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/errno.h>

asmlinkage long sys_set_nice_inc(pid_t pid, int value) {

	struct task_struct *process = find_task_by_vpid(pid);
	
	if(process == NULL) { 
		printk(KERN_ALERT "SYS_SET_NICE_INC: No process exists with given pid");
		return -ESRCH;
	}

	process->nice_inc = value;

	return 0;
}
