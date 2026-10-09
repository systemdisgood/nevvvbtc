#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <iso646.h>

#define ADDR_WIDTH 30
#define MEM_SIZE  0X8000000 // 2^(30/8)


typedef struct
{
	bool trig_pull_up; 
	bool trig;
	bool out;
	bool tres;
	bool dis_pull_up;
	bool dis;
} nevvv_io;

nevvv_io nevvv_io_inst = {0} ;

typedef struct
{
        uint8_t addr_bit_to_set;
        bool addr_bit_set;
        bool addr_bit_reset;
        bool in;
        bool out;
        bool nr;
        bool nw;
} mem_io;

mem_io mem_io_inst = {0};

void nevvv_handler(nevvv_io* nevvv_io_inst, mem_io* mem_io_inst)
{
	static bool reg = 0;
	if(not(nevvv_io_inst -> trig_pull_up)) 
	{
		if(not(mem_io_inst -> nr)) 
		{
			if(not(nevvv_io_inst -> trig)) reg = true;
		}
		else reg = true;
	}
	else if(nevvv_io_inst -> tres) reg = false;
	nevvv_io_inst -> out = reg;
	nevvv_io_inst -> dis = (nevvv_io_inst -> dis_pull_up) ? reg : false;
}


void mem_handler(mem_io* mem_io_inst)
{
	static uint8_t mem[MEM_SIZE] = {0};
	static uint32_t addr = 0;
	bool out;
	if((not(mem_io_inst -> nr) and not(mem_io_inst -> nw)) or (not(mem_io_inst -> addr_bit_set) and not(mem_io_inst -> addr_bit_reset))) return;
	if(mem_io_inst -> addr_bit_reset) addr = 0;
	if(mem_io_inst -> addr_bit_set) addr |= (1 << (mem_io_inst -> addr_bit_to_set));
	if(not (mem_io_inst -> nw)) mem[addr/8] = (mem_io_inst -> in) ? mem[addr/8] | (1 << (addr%8)) : mem[addr/8] &~(1 << (addr%8)); 
	out = mem[addr/8] & (1 << (addr%8));
	mem_io_inst -> out = out;
}


int main()
{
	int c;
	char ch;
	bool mem_op = false;
	bool is_op = false;
    while ((c = getchar()) != EOF) 
	{
        ch = c < 0x100 ? (char)c: '\0';
		if((ch >= '0') and (ch <= '9'))
		{
			mem_op = true;
			mem_io_inst.addr_bit_to_set = ch - '0';
			mem_io_inst.addr_bit_set = true;
		}
		switch(ch)
		{
			case 'A':
				is_op = true;
				mem_op = true;
				mem_io_inst.addr_bit_to_set = 10;
				mem_io_inst.addr_bit_set = true;
				break;
			case 'B':
				break;
			case 'C':
				break;
			case 'D':
				break;
			case 'E':
				break;
			case 'F':
				break;
			case 'G':
				break;
			case 'H':
				break;
			case 'I':
				break;
			case 'J':
				break;
			case 'K':
				break;
			case 'L':
				break;
			case 'M':
				break;
			case 'N':
				break;
			case 'O':
				break;
			case 'P':
				break;
			case 'Q':
				break;
			case 'R':
				break;
			case 'S':
				break;
			case 'T':
				break;
			case 'u':
				is_op = true;
				mem_op = true;
				mem_io_inst.addr_bit_reset = true;
				break;
			case 'v':
				is_op = true;
				mem_op = true;
				mem_io_inst.nr = false;
				break;
			case 'V':
				is_op = true;
				mem_op = true;
				mem_io_inst.nr = true;
				break;
			case 'w':
				is_op = true;
				mem_op = true;
				mem_io_inst.nw = false;
				break;
			case 'W':
				is_op = true;
				mem_op = true;
				mem_io_inst.nw = true;
				break;
			case 'x':
				is_op = true;
				mem_op = false;
				nevvv_io_inst.tres = false;
				break;
			case 'X':
				is_op = true;
				mem_op = true;
				nevvv_io_inst.tres = true;
				break;
			case 'y':
				is_op = true;
				mem_op = true;
				nevvv_io_inst.trig_pull_up = false;
				break;
			case 'Y':
				is_op = true;
				mem_op = true;
				nevvv_io_inst.trig_pull_up = true;
				break;
				mem_op = true;
			case 'z':
				is_op = true;
				mem_op = true;
				nevvv_io_inst.dis_pull_up = false;
				break;
			case 'Z':
				is_op = true;
				mem_op = true;
				nevvv_io_inst.dis_pull_up = true;
				break;
		}
		if(is_op)
		{
			if(mem_op)
			{
				mem_io_inst.in = nevvv_io_inst.out;
				mem_handler(&mem_io_inst);
				nevvv_io_inst.trig = mem_io_inst.out;
				nevvv_handler(&nevvv_io_inst, &mem_io_inst);
			}
			else
			{
				nevvv_io_inst.trig = mem_io_inst.out;
				nevvv_handler(&nevvv_io_inst, &mem_io_inst);
				mem_io_inst.in = nevvv_io_inst.out;
				mem_handler(&mem_io_inst);
			}
			mem_io_inst.addr_bit_set = false;
			mem_io_inst.addr_bit_reset = false;
			if(nevvv_io_inst.dis_pull_up)
			{
				if(nevvv_io_inst.dis) printf("1");
				else printf("0");
			}
			is_op = false;
		}
		c = '\0';
		ch = '\0';
    }
	putchar('\n');
}
