#include <stdint.h>

#define CELL			uint64_t
#define MEMORY			16384
#define D_STACK_SIZE 4096
#define R_STACK_SIZE 4096

enum opcodes {
	op_nop,				/* 0 */
	op_dup,				/* 1 */
	op_literal,			/* 2 */
	op_drop,				/* 3 */
	op_push,				/* 4 */
	op_pop,				/* 5 */
	op_jmp,				/* 6 */
	op_if,				/* 7 */
	op_call,				/* 8 */
	op_return,			/* 9 */
	op_equal,			/* a */
	op_inequal,			/* b */
	op_less,				/* c */
	op_greater,			/* d */
	op_at,				/* e */
	op_store,			/* f */
	op_add,				/* 10 */
	op_subtract,		/* 11 */
	op_multiply,		/* 12 */
	op_mulrat,			/* 13 */
	op_and,				/* 14 */
	op_or,				/* 15 */
	op_xor,				/* 16 */
	op_not,				/* 17 */
	op_double,			/* 18 */
	op_half,				/* 19 */
	op_baseaddress,	/* 1a */
	op_syscall,			/* 1b */
	op_quit,				/* 1c */
	op_error,			/* 1d */
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
void vm_dup(Machine *m);
void vm_literal(Machine *m);
void vm_drop(Machine *m);
void vm_push(Machine *m);
void vm_pop(Machine *m);
void vm_jmp(Machine *m);
void vm_if(Machine *m);
void vm_call(Machine *m);
void vm_return(Machine *m);
void vm_equal(Machine *m);
void vm_inequal(Machine *m);
void vm_less(Machine *m);
void vm_greater(Machine *m);
void vm_at(Machine *m);
void vm_store(Machine *m);
void vm_add(Machine *m);
void vm_subtract(Machine *m);
void vm_multiply(Machine *m);
void vm_mulrat(Machine *m);
void vm_and(Machine *m);
void vm_or(Machine *m);
void vm_xor(Machine *m);
void vm_not(Machine *m);
void vm_double(Machine *m);
void vm_half(Machine *m);
void vm_baseaddress(Machine *m);
void vm_syscall(Machine *m);
void vm_quit(Machine *m);
void vm_error(Machine *m);

Machine initMachine();
void step(Machine *m);
void run(Machine *m);
void printData(Machine *m);
void printReturn(Machine *m);

CELL loadImage(char *filename, Machine *m);
CELL writeImage(Machine *m, char *filename);
