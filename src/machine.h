#include <stdint.h>

#define CELL			uint64_t
#define MEMORY			16384
#define D_STACK_SIZE 4096
#define R_STACK_SIZE 4096

enum opcodes {
	op_nop,				/* 0 */
	op_lit,				/* 1 */
	op_dup,				/* 2 */
	op_drop,			/* 3 */
	op_swap,			/* 4 */
	op_push,			/* 5 */
	op_pop,				/* 6 */
	op_jmp,				/* 7 */
	op_if,				/* 8 */
	op_call,			/* 9 */
	op_ret,				/* a */
	op_eq,				/* b */
	op_ineq,			/* c */
	op_lt,				/* d */
	op_gt,				/* e */
	op_at,				/* f */
	op_store,			/* 10 */
	op_add,				/* 11 */
	op_sub,				/* 12 */
	op_mul,				/* 13 */
	op_div,				/* 14 */
	op_and,				/* 15 */
	op_or,				/* 16 */
	op_xor,				/* 17 */
	op_not,				/* 18 */
	op_shr,				/* 19 */
	op_shl,				/* 1a */
	op_baseaddress,			/* 1b */
	op_syscall,			/* 1c */
	op_quit,			/* 1d */
	op_err,				/* 1e */
};

typedef struct Machine {
	CELL memory[MEMORY];
	CELL ds[D_STACK_SIZE];
	CELL rs[R_STACK_SIZE];
	CELL dp;
	CELL rp;
	CELL ip;
	int debug;
} Machine;

void vm_nop(Machine *m);
void vm_lit(Machine *m);
void vm_dup(Machine *m);
void vm_drop(Machine *m);
void vm_swap(Machine *m);
void vm_push(Machine *m);
void vm_pop(Machine *m);
void vm_jmp(Machine *m);
void vm_if(Machine *m);
void vm_call(Machine *m);
void vm_ret(Machine *m);
void vm_eq(Machine *m);
void vm_ineq(Machine *m);
void vm_lt(Machine *m);
void vm_gt(Machine *m);
void vm_at(Machine *m);
void vm_store(Machine *m);
void vm_add(Machine *m);
void vm_sub(Machine *m);
void vm_mul(Machine *m);
void vm_div(Machine *m);
void vm_and(Machine *m);
void vm_or(Machine *m);
void vm_xor(Machine *m);
void vm_not(Machine *m);
void vm_shr(Machine *m);
void vm_shl(Machine *m);
void vm_baseaddress(Machine *m);
void vm_syscall(Machine *m);
void vm_quit(Machine *m);
void vm_err(Machine *m);

Machine initMachine();
void step(Machine *m);
void run(Machine *m);
void printData(Machine *m);
void printReturn(Machine *m);

CELL loadImage(char *filename, Machine *m);
CELL writeImage(Machine *m, char *filename);
