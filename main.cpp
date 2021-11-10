#include <cstdio>
unsigned char buffer[1024] = {};
unsigned char* data = buffer;

void bf(char* ptr)
{
	while(*ptr) {
		switch(*ptr) {
			case '>': data++; break;
			case '<':  data--; break;
			case '+':  ++(*data); break;
			case '-': --(*data); break;
			case '.': putc(*data, stdout); break;
			case ',':  *data = getc(stdin); break;
			case '[': {
				while(*data) bf(ptr + 1);
				ptr++;
				int bracket_count = 0;
				while(*ptr != ']' || bracket_count != 0) {
					if(*ptr == '[') bracket_count++;
					if(*ptr == ']') bracket_count--;
					ptr++;
				}
			} break;
			case ']': return;
			default:break;
		}
		ptr++;
	}
}

char* read_file(const char* path)
{
	FILE* file = fopen(path, "rb");
	char* file_buff = 0;
	if(file) {
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);
		file_buff = new char[size + 1];
		fread(file_buff, size, 1, file);
		file_buff[size] = 0;
		fclose(file);
	}
	return file_buff;
}

int main(int argc, char** argv)
{
	if(argc < 2) {
		printf("[USAGE]: %s path_to_bf_file\n", argv[0]);
		return 0;
	}
	char* ptr = read_file(argv[1]);
	bf(ptr);
	return 0;
}