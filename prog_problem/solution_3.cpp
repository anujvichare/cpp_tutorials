#include<fstream>
#include<iostream>
#include<memory>
#include<array>
#include<cstring>
#include<cctype>

static const int ARRAY_SIZE = 101;
static const int BUFF_SIZE = 1024 * 1024;

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cerr << "invalid no of arguments" << std::endl;
		std::cout << "usage : <executable> [input file] [output file]" <<std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1], std::ios::in);
	std::ofstream outputFile(argv[2], std::ios::out | std::ios::trunc);;
      	if(!inputFile || !outputFile)
	{
		std::cerr << "file error" << std::endl;
		return 1;
	}
	
	std::string number;
	std::array<unsigned long int, ARRAY_SIZE> readingsCount;
	readingsCount.fill(0);

	std::unique_ptr<char[]> buff(new char[BUFF_SIZE]);


	while(inputFile)
	{	
		inputFile.read(buff.get(), BUFF_SIZE);
	
		for(unsigned int i = 0; i < inputFile.gcount(); ++i)
		{
			char c = buff[i];
	       		if(c == ' ')
			{
				if(number.empty())
					continue;

				short reading = std::stoi(number);
				if( 0 <= reading && reading <= 100 )
					++(readingsCount[reading]);
				number.clear();
			}
			else if(isdigit(c))
			{
				number += c;
			}
		}
		memset(buff.get(), 0 , BUFF_SIZE);
	}
	if(!number.empty())
	{
		short reading = std::stoi(number);
                if( 0 <= reading && reading <= 100 )
                	++(readingsCount[reading]);
               	number.clear();
	}

	int buffOffset = 0;
	std::string temp;
	for(int i = 0; i< readingsCount.size(); ++i)
	{
		if(!readingsCount[i])
			continue;

		for(int j = 0; j < readingsCount[i]; ++j)
		{
			temp += std::to_string(i);
			temp += " ";	
		
		}
		outputFile.write(temp.c_str(), temp.size());
		temp.clear();
	}

	inputFile.close();
	outputFile.close();

	return 0;
}
