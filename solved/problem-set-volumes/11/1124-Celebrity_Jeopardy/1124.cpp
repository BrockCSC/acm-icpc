#include<iostream>
#include<string>
main()
{
  std::string line;
  while(getline(std::cin, line)) std::cout << line << std::endl;
} 
