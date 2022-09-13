/* Procedures for running and debugging the VM */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "machine.h"

Machine initMachine()
{
	Machine m;
	CELL x;
	
	m.debug = 0;
	m.dp = 0;
	m.rp = 0;
	m.ip = 0;

	for(x = 0; x < MEMORY; x++)
		m.memory[x] = op_nop;

	for(x = 0; x < D_STACK_SIZE; x++)
		m.ds[x] = 0;

	for(x = 0; x < R_STACK_SIZE; x++)
		m.rs[x] = 0;

	return m;
}

void printData(Machine *m)
{
	printf("DATA: ");
	for(int x = m->dp; x >= 0; x--)
		printf("%llu ", m->ds[x]);
}

void printReturn(Machine *m)
{
	printf("RETURN: ");
	for(int x = m->rp; x >= 0; x--)
		printf("%llu ", m->rs[x]);
}

void step(Machine *m)
{
	if(m->debug > 0) {
		printf("AT: %llu ", m->ip);
		printData(m);
		printReturn(m);
		printf("\n");
	}

	switch (m->memory[m->ip]) {
	case op_nop:
		vm_nop(m);
		break;
	case op_dup:
		vm_dup(m);
		break;
	case op_lit:
		vm_lit(m);
		break;
	case op_drop:
		vm_drop(m);
		break;
	case op_push:
		vm_push(m);
		break;
	case op_pop:
		vm_pop(m);
		break;
	case op_jmp:
		vm_jmp(m);
		break;
	case op_if:
		vm_if(m);
		break;
	case op_call:
		vm_call(m);
		break;
	case op_ret:
		vm_ret(m);
		break;
	case op_eq:
		vm_eq(m);
		break;
	case op_ineq:
		vm_ineq(m);
		break;
	case op_lt:
		vm_lt(m);
		break;
	case op_gt:
		vm_gt(m);
		break;
	case op_at:
		vm_at(m);
		break;
	case op_store:
		vm_store(m);
		break;
	case op_add:
		vm_add(m);
		break;
	case op_sub:
		vm_sub(m);
		break;
	case op_mul:
		vm_mul(m);
		break;
	case op_and:
		vm_and(m);
		break;
	case op_or:
		vm_or(m);
		break;
	case op_xor:
		vm_xor(m);
		break;
	case op_not:
		vm_not(m);
		break;
	case op_shr:
		vm_shr(m);
		break;
	case op_shl:
		vm_shl(m);
		break;
	case op_baseaddress:
		vm_baseaddress(m);
		break;
	case op_syscall:
		vm_syscall(m);
		break;
	case op_quit:
		vm_quit(m);
		break;
	case op_err:
		vm_err(m);
		break;

	default:
		printf("invalid opcode: %llu\n",
			m->memory[m->ip]);
		exit(1);
	}

	if((int) m->rp < 0){
		printf("RETURN STACK UNDERFLOW!\n");
		exit(1);
	}

	if((int) m->dp < 0){
		printf("DATA STACK UNDERFLOW!\n");
		exit(1);
	}

	m->ip++;
}

void run(Machine *m)
{
	while(m->ip <= MEMORY)
		step(m);

	printf("EXIT WITH SUCCESS\n");
}
