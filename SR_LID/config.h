/***********************

    Read User Config Module Head
    The LVCSR Group
    Oregon Graduate Institute

             ************************/
#ifndef aaaCONFIGURATIONaaa
#define aaaCONFIGURATIONaaa

#include "comm.h"
//#include <string>

#define STRINGLENGTH 256

typedef char char256[STRINGLENGTH];


typedef 
struct aConfigEnv {
   aConfigEnv *next;
   char256 env;
   char256 def;
};
  
class Config {
   protected:

      aConfigEnv *envs;
      FILE *fenv;
      char *value;
      bool exam;

      char *GetEnv(char *env);
      
   public:
      // =%d 
      void ReadConfig(char *line,int& num);
      // =%d %d
      void ReadConfig(char *line,int& num1,int& num2);
      // =true/false
      void ReadConfig(char *line,bool& bln);
      // =%g
      void ReadConfig(char *line,float& num);
      // =%g %g
      void ReadConfig(char *line,float& num1,float& num2);
      // =%g %g %g
      void ReadConfig(char *line,float& num1,float& num2,float& num3);
      // =%g,%g %g,%g
      void ReadConfig(char *line,float& n1,float& n2,float& n3,float& n4);
      // =%s
      void ReadConfig(char *line,char *str);
      // =%s %s
      void ReadConfig(char *line,char *str1,char *str2);
      
      Config(int argc,char *argv[],char *head=NULL);
	  Config(char *cfgFile);
      ~Config(void);
};

#endif
