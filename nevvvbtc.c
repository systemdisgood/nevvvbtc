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
} nevvv;

nevvv nevvv_inst;



void nevvv_handler(nevvv* nevvv_inst)
{
	static bool reg = 0;
	if(!(nevvv_inst -> trig_pull_up) and (nevvv_inst -> trig)) reg = true;
	else if(nevvv_inst -> tres) reg = false;
	nevvv_inst -> out = reg;
	nevvv_inst -> dis = (nevvv_inst -> dis_pull_up) ? reg : false;
}

void mem_handler()
{
	static uint8_t mem[MEM_SIZE] = {0};
	static uint32_t addr = 0;
}


int main()
{
	int c;
	char ch;
	bool mem_op = false;
    while ((c = getchar()) != EOF) 
	{
        ch = c < 0x100 ? (char)c: '\0';
		switch(ch)
		{
			case 'u':
				break;
			case 'v':
				break;
			case 'V':
				break;
			case 'w':
				break;
			case 'W':
				break;
			case 'x':
				break;
			case 'X':
				break;
			case 'y':
				break;
			case 'Y':
				break;
			case 'z':
				break;
			case 'Z':
				break;
		}
    }
}
