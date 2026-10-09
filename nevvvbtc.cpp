#include <iostream>
#include <vector>

enum Error {RW = 1};

int cmd_handler(char ch)
{
	static uint16_t addr;
	static uint8_t mem[0x1FFF];
	static bool is_in_read = 0;
	static bool is_in_write = 0;
	static bool is_rs = false;
	static bool is_discharge = false;
	static bool is_trigger_pull_up = false;
	static bool is_treshold = false;
	switch(ch)
	{
		case 'H':
			if(!is_discharge)
			{
				is_discharge = true;
				if(is_rs) std::cout << "1";
				else std::cout << "0";
			}
			break;
		case 'h':
			is_discharge = false;
			break;
		case 'S':
			if(is_trigger_pull_up && !(is_in_write && (!(mem[addr / 8] & (1 << (addr % 8))))))
			{
				is_rs = true;
			}
			break;
		case 's':
			break;
		case 'T':
			is_trigger_pull_up = true;
			if(is_in_read && !is_in_write && !is_treshold)
			{
				if(!(mem[addr / 8] & (1 << (addr % 8)))) is_rs = false;
			}
			break;
		case 't':
			is_trigger_pull_up = false;
			if(is_treshold && !(is_in_write && (!(mem[addr / 8] & (1 << (addr % 8))))))
			break;
		case 'W':
			is_in_write = true;
			break;
		case 'w':
			if(is_in_write && !is_in_read)
			{
				if(is_rs) mem[addr / 8] |= (1 << (addr & 8));
				else mem[addr / 8] &=~ (1 << (addr & 8));
			}
			is_in_write = false;
			break;
		case 'R':
			is_in_read = true;
			break;
		case 'r':
			is_in_read = false;
			break;
		case 'X':
			addr = 0;
			break;
		case 'x':
			addr = 0;
			break;
		default:
			if(ch >= '0' && ch <= '9')
			{
				addr |= (1 << (ch - '0'));
			}
			else if(ch >= 'A' && ch <= 'F')
			{
				addr |= (1 << (10 + (ch - 'A')));
			}
			else if(ch >= 'a' && ch <= 'f')
			{
				addr |= (1 << (10 + (ch - 'a')));
			}
	}
	if(is_in_read && is_in_write) return RW;
	return 0;
}



bool error_handler(int error_code)
{
	switch(error_code)
	{
		case RW:
			std::cout << "Memory must be in R OR in W state." << std::endl;
			return RW;
	}
	return 0;
}

int main()
{
	//std::cout << "test" << std::endl;
	int c;
	char ch;
	int error_code;
	bool is_loop_code = false;
	size_t loop_pos = 0;
	size_t loop_pos_max;
	std::vector<uint8_t> loop_cmds;
    while ((c = std::cin.get()) != EOF) 
	{
        ch = c < 0x100 ? static_cast<char>(c): '\0';
		//std::cout << ch << std::endl;
		if(is_loop_code)
		{
			if(
				('H' == ch) ||
				('h' == ch) ||
				('S' == ch) ||
				('s' == ch) ||
				('T' == ch) ||
				('t' == ch) ||
				('W' == ch) ||
				('w' == ch) ||
				('R' == ch) ||
				('r' == ch) ||
				('N' == ch) ||
				('n' == ch) ||
				('X' == ch) ||
				('x' == ch) ||
				(ch >= '0' && ch <= '9') ||
				(ch >= 'A' && ch <= 'F') ||
				(ch >= 'a' && ch <= 'f')
			  )
			{
				loop_cmds.push_back(ch);
			}
		}
		else
		{
			if(('N' == ch) || ('n' == ch)) std::cout << std::endl;
			error_code = cmd_handler(ch);
			if(error_handler(error_code)) return EXIT_FAILURE;
		}
		if('L' == ch && !is_loop_code) is_loop_code = true;
		if('l' == ch) 
		{
			loop_pos_max = loop_cmds.size() - 1;
			while(true)
			{
				if(('N' == ch) || ('n' == ch)) std::cout << std::endl;
				error_code = cmd_handler(ch);
				if(error_handler(error_code)) return EXIT_FAILURE;
				if(loop_pos < loop_pos_max) ++loop_pos;
				else loop_pos = 0;
			}
		}
    }
}
