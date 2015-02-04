/*
 * Process-related syscalls.
 * New for ASST1.
 */

#include <types.h>
#include <kern/errno.h>
#include <kern/wait.h>
#include <lib.h>
#include <thread.h>
#include <current.h>
#include <pid.h>
#include <machine/trapframe.h>
#include <syscall.h>

/*
 * sys_fork
 * 
 * create a new process, which begins executing in md_forkentry().
 */


int
sys_fork(struct trapframe *tf, pid_t *retval)
{
	struct trapframe *ntf; /* new trapframe, copy of tf */
	int result;

	/*
	 * Copy the trapframe to the heap, because we might return to
	 * userlevel and make another syscall (changing the trapframe)
	 * before the child runs. The child will free the copy.
	 */

	ntf = kmalloc(sizeof(struct trapframe));
	if (ntf==NULL) {
		return ENOMEM;
	}
	*ntf = *tf; /* copy the trapframe */

	result = thread_fork(curthread->t_name, enter_forked_process, 
			     ntf, 0, retval);
	if (result) {
		kfree(ntf);
		return result;
	}

	return 0;
}

/*
 * sys_getpid
 * Returns the process id of the current process.
 */
void
sys_getpid(pid_t *retval)
{
	*retval = curthread->t_pid;
}

/*
 * sys_waitpid
 * Placeholder comment to remind you to implement this.
 */
int
sys_waitpid(pid_t pid, int *status, int opt, pid_t *retval)
{
	// If the pid argument named a non-existent process
	if (pid_valid(pid) != 0) {
		return ESRCH;
	}

	// If the status argument was an invalid pointer
	if (! status) {
		return EFAULT;
	}

	// If the options argument requested invalid or unsupported options
	if (opt != 0 && opt != WNOHANG) {
		return EINVAL;
	}

	// If given pid is a child of current thread
	if (! pid_is_parent_child(curthread->t_pid, pid)){
		return ECHILD;
	}

	*retval = pid_join(pid, status, opt);

	// On error, error code is returned
	if ( *retval < 0){
		return -(*retval); // return positive errno
	}
	
	// On success
	return 0;
}

/*
 * sys_kill
 * Placeholder comment to remind you to implement this.
 */
int
sys_kill(pid_t pid, int sig) 
{

}



