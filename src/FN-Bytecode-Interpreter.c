/*
 ============================================================================
 Name        : FN-Bytecode-Interpreter.c
 Author      : Bill Hails
 Version     :
 Copyright   : copyright 2018
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstract-machine.h"

struct am current_am;

int main(void) {
	current_am.cont.closure.pc = 0;
}

void create_env(location, size)
int location;
int size;
{
	current_am.cont.temps[location]
						  = malloc(sizeof(struct env)
								  + size * sizeof(EXPR));
}

void populate_env(location, index, value)
int location;
int index;
int value;
{
	((ENV) (current_am.cont.temps[location]))->frame[index] =
			current_am.cont.temps[value];
}

void create_closure(pc, envpos, clospos)
PC pc;
int envpos;
int clospos;
{
	CLOS clos = malloc(sizeof(struct closure));
	clos->pc = pc;
	clos->env = (ENV) current_am.cont.temps[envpos];
	current_am.cont.temps[clospos] = (EXPR) clos;
}

void call_closure(n)
int n;
{
	memcpy(&current_am, &(current_am.cont.closure), sizeof(struct closure));
}

void create_continuation(pc)
PC pc;
{
	CONT cont = malloc(sizeof(struct continuation));
	memcpy(cont, &current_am, sizeof(struct continuation));
	cont->closure.pc = pc;
	current_am.cont.cont = cont;
}

void call_continuation()
{
	memcpy(&current_am, current_am.cont.cont, sizeof(struct continuation));
}

void create_failure(pc)
PC pc;
{
	FAIL fail = malloc(sizeof(struct am));
	memcpy(fail, &current_am, sizeof(struct am));
	fail->cont.closure.pc = pc;
	current_am.fail = fail;
}

void call_failure()
{
	memcpy(&current_am, current_am.fail, sizeof(struct am));
}
