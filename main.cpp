#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*void getSerialNum(){
   const char *p="Serial"; //this key is serical num
   FILE *cmdline = fopen("/proc/cpuinfo", "rb");
   char *arg = 0;
   size_t size = 0;
   //getdeli分割读取字段
   while(getdelim(&arg, &size, 0, cmdline) != -1)
   {
      if(strstr(arg,p) != NULL){
         puts(arg);//put 输出
      }
   }
   free(arg);
   fclose(cmdline);
}*/
#include <cpuid.h>
#include <iostream>
#include <sstream>
std::string GetCPUId()
{
    std::string strCPUId;

    unsigned int level = 1;
    unsigned eax = 3 /* processor serial number */, ebx = 0, ecx = 0, edx = 0;
    __get_cpuid(level, &eax, &ebx, &ecx, &edx);

    // byte swap
    int first = ((eax >> 24) & 0xff) | ((eax << 8) & 0xff0000) | ((eax >> 8) & 0xff00) | ((eax << 24) & 0xff000000);
    int last = ((edx >> 24) & 0xff) | ((edx << 8) & 0xff0000) | ((edx >> 8) & 0xff00) | ((edx << 24) & 0xff000000);

    // tranfer to string
    std::stringstream ss;
    ss << std::hex << first;
    ss << std::hex << last;
    ss >> strCPUId;

    return strCPUId;
}


int main(int argc, char **argv){
   //getSerialNum();
  std::string strCPUId=GetCPUId();
  std::cout<<strCPUId<<std::endl;
   return 0;
}

