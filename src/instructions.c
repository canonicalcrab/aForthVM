/* The instruction set is listed in machine.h,
 * functionality is implemented here. The rest
 * of the machine is implemented in machine.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "machine.h"

void vm_nop(Machine *m)
{

}

void vm_lit(Machine *m)
{
	m->dp++;
	m->ip++;
	m->ds[m->dp] = m->memory[m->ip];
}

void vm_dup(Machine *m)
{
	CELL tos = m->ds[m->dp];
	m->dp++;
	m->ds[m->dp] = tos;
}

void vm_drop(Machine *m)
{
	m->dp--;
}

void vm_swap(Machine *m)
{
	CELL x = m->ds[m->dp];
	m->ds[m->dp] = m->ds[m->dp - 1];
	m->ds[m->dp - 1] = x;
}

void vm_push(Machine *m)
{
	m->rp++;
	m->rs[m->rp] = m->ds[m->dp];
	vm_drop(m);
}

void vm_pop(Machine *m)
{
	m->dp++;
	m->ds[m->dp] = m->rs[m->rp];
	m->rp--;
}

void vm_jmp(Machine *m)
{
	m->ip = m->ds[m->dp] - 1;
	/* subtract one to negate ip increment */
	vm_drop(m);
}

void vm_if(Machine *m)
{
	if(m->ds[m->dp]) {
		m->ip = m->ds[m->dp - 1] - 1;
		/* subtract one to negate ip increment */
	}
	m->dp -= 2;
}

void vm_call(Machine *m)
{
	m->rp++;
	m->rs[m->rp] = m->ip;
	m->ip = m->ds[m->dp] - 1;
	vm_drop(m);
}

void vm_ret(Machine *m)
{
	m->ip = m->rs[m->rp];
	m->rp--;
}

void vm_eq(Machine *m)
{
	if(m->ds[m->dp] == m->ds[m->dp - 1]){
		vm_drop(m);
		m->ds[m->dp] = 1;
	} else {
		vm_drop(m);
		m->ds[m->dp] = 0;
	}
}

void vm_ineq(Machine *m)
{
	if(m->ds[m->dp] != m->ds[m->dp - 1]){
		vm_drop(m);
		m->ds[m->dp] = 1;
	} else {
		vm_drop(m);
		m->ds[m->dp] = 0;
	}
}

void vm_lt(Machine *m)
{
	if(m->ds[m->dp] < m->ds[m->dp - 1]){
		vm_drop(m);
		m->ds[m->dp] = 1;
	} else {
		vm_drop(m);
		m->ds[m->dp] = 0;
	}
}

void vm_gt(Machine *m)
{
	if(m->ds[m->dp] > m->ds[m->dp - 1]){
		vm_drop(m);
		m->ds[m->dp] = 1;
	} else {
		vm_drop(m);
		m->ds[m->dp] = 0;
	}
}

void vm_at(Machine *m)
{
	m->ds[m->dp] = m->memory[m->ds[m->dp]];
}

void vm_store(Machine *m)
{
	m->memory[m->ds[m->dp]] = m->ds[m->dp -1];
	vm_drop(m);
}

void vm_add(Machine *m)
{
	m->ds[m->dp - 1] += m->ds[m->dp];
	vm_drop(m);
}

void vm_sub(Machine *m)
{
	m->ds[m->dp - 1] -= m->ds[m->dp];
	vm_drop(m);
}

void vm_mul(Machine *m)
{
	m->ds[m->dp - 1] *= m->ds[m->dp];
	vm_drop(m);
}

void vm_div(Machine *m)
{
	m->ds[m->dp - 1] = m->ds[m->dp] / m->ds[m->dp - 1];
	m->dp -= 1;
}

void vm_and(Machine *m)
{
	m->ds[m->dp - 1] &= m->ds[m->dp];
	vm_drop(m);
}

void vm_or(Machine *m)
{
	m->ds[m->dp - 1] |= m->ds[m->dp];
	vm_drop(m);
}

void vm_xor(Machine *m)
{
	m->ds[m->dp - 1] ^= m->ds[m->dp];
	vm_drop(m);
}

void vm_not(Machine *m)
{
	m->ds[m->dp] = ~m->ds[m->dp];
}

void vm_shr(Machine *m)
{
	m->ds[m->dp] >>= 1;
}

void vm_shl(Machine *m)
{
	m->ds[m->dp] <<= 1;
}

void vm_baseaddress(Machine *m)
{
	m->dp++;
	m->ds[m->dp] = (CELL) m->memory;
}

void vm_syscall(Machine *m)
{
	int ret;
	switch (m->ds[m->dp]) {
	case 1:
		ret = syscall(m->ds[m->dp - 1]);
		m->dp -= 2;
		m->ds[m->dp] = ret;
		break;
	case 2:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2]);
		m->dp -= 3;
		m->ds[m->dp] = ret;
		break;
	case 3:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2],  /* DIFFERENT */
			m->ds[m->dp - 3],
			m->ds[m->dp - 4]);
		m->dp -= 4;
		m->ds[m->dp] = ret;
		break;
	case 4:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2],
			m->ds[m->dp - 3],
			m->ds[m->dp - 4]);
		m->dp -= 5;
		m->ds[m->dp] = ret;
	case 5:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2],
			m->ds[m->dp - 3],
			m->ds[m->dp - 4],
			m->ds[m->dp - 5]);
		m->dp -= 6;
		m->ds[m->dp] = ret;
	case 6:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2],
			m->ds[m->dp - 3],
			m->ds[m->dp - 4],
			m->ds[m->dp - 5],
			m->ds[m->dp - 6]);
		m->dp -= 7;
		m->ds[m->dp] = ret;
	case 7:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2],
			m->ds[m->dp - 3],
			m->ds[m->dp - 4],
			m->ds[m->dp - 5],
			m->ds[m->dp - 6],
			m->ds[m->dp - 7]);
		m->dp -= 8;
		m->ds[m->dp] = ret;
	case 8:
		ret = syscall(m->ds[m->dp - 1],
			m->ds[m->dp - 2],
			m->ds[m->dp - 3],
			m->ds[m->dp - 4],
			m->ds[m->dp - 5],
			m->ds[m->dp - 6],
			m->ds[m->dp - 7],
			m->ds[m->dp - 8]);
		m->dp -= 9;
		m->ds[m->dp] = ret;
	default:
		printf("WRONG ARGUMENT COUNT FOR SYSCALL\n");
		exit(1);
	}
}

void vm_quit(Machine *m)
{
	m->ip = MEMORY - 1;
}

void vm_err(Machine *m)
{
	printf("VM ERROR: %llu\n", m->ds[m->dp]);
	exit(1);
}

