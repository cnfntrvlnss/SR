/***********************

    Read User Config Module
    The LVCSR Group
    Oregon Graduate Institute

             ************************/
#include "config.h"
#include "string.h"

//LJ-- static void SetEnv(aConfigEnv* &envs,char *config) {
void SetEnv(aConfigEnv* &envs,char *config)
{
    char *pt;
    while ((pt=strchr(config,'"')))
    {
        //strcpy(pt,pt+1);
        memmove(pt, pt+1, strlen(pt));
    }
    if ((pt=strchr(config,'=')))
    {
        aConfigEnv *tmp=new aConfigEnv;
        tmp->next=envs;
        envs=tmp;
        *pt='\0';
        strcpy(tmp->env,config);
        strcpy(tmp->def,pt+1);
        *pt='=';
    }
}

char *Config::GetEnv(char *env)
{
    for (aConfigEnv *ev=envs; ev; ev=ev->next)
        if (!strcmp(ev->env,env)) return ev->def;
    char *tmp=getenv(env);
    ASSERT2(tmp,"%s not set",env);
    return tmp;
}

void Config::ReadConfig(char *line,int& num)
{
    sscanf(GetEnv(line),"%d",&num);
    if (fenv) fprintf(fenv,"%s=%d\n",line,num);
}

void Config::ReadConfig(char *line,int& num1,int& num2)
{
    sscanf(GetEnv(line),"%d %d",&num1,&num2);
    if (fenv) fprintf(fenv,"%s=%d %d\n",line,num1,num2);
}

void Config::ReadConfig(char *line,bool& bln)
{
    bln=(!strncmp(GetEnv(line),"true",4));
    if (fenv) fprintf(fenv,"%s=%s\n",line,(bln)?"true":"false");
}

void Config::ReadConfig(char *line,float& num)
{
    sscanf(GetEnv(line),"%g",&num);
    if (fenv) fprintf(fenv,"%s=%g\n",line,num);
}

void Config::ReadConfig(char *line,float& num1,float& num2)
{
    sscanf(GetEnv(line),"%g %g",&num1,&num2);
    if (fenv) fprintf(fenv,"%s=%g %g\n",line,num1,num2);
}

void Config::ReadConfig(char *line,float& num1,float& num2,float& num3)
{
    sscanf(GetEnv(line),"%g %g %g",&num1,&num2,&num3);
    if (fenv) fprintf(fenv,"%s=%g %g %g\n",line,num1,num2,num3);
}

void Config::ReadConfig(char *line,float& n1,float& n2,float& n3,float& n4)
{
    if (sscanf(GetEnv(line),"%g ,%g %g ,%g",&n1,&n2,&n3,&n4)<3)
    {
        n3=n1;
        n4=n2;
    }
    if (fenv) fprintf(fenv,"%s=%g,%g %g,%g\n",line,n1,n2,n3,n4);
}

void Config::ReadConfig(char *line,char *str)
{
    str[0]='\0';
    sscanf(GetEnv(line),"%[^\n\r]s",str);
    if (fenv) fprintf(fenv,"%s=%s\n",line,str);
}

void Config::ReadConfig(char *line,char *str1,char *str2)
{
    if (sscanf(GetEnv(line),"%s %s",str1,str2)<2) strcpy(str2,str1);
    if (!strcmp(str1,"null") || !strcmp(str1,"NULL")) str1[0]='\0';
    if (!strcmp(str2,"null") || !strcmp(str2,"NULL")) str2[0]='\0';
    if (fenv) fprintf(fenv,"%s=%s %s\n",line,
                          (str1[0])?str1:"null",(str2[0])?str2:"null");
}

Config::Config(char *cfgFile)
{
    FILE *fin2 = NULL;
    fenv=NULL;
    exam=false;
    envs=NULL;
    TextReadOpen(fin2,cfgFile);
    char256 config="";
    while (!feof(fin2))
    {
        if (fscanf(fin2,"\n %[^\n\r]s",config)<1) break;
        SetEnv(envs,config);
    }
    if(fin2!=NULL)
        fclose(fin2);
}

#ifdef __GNUC__
Config::Config(int argc,char *argv[],char *head)
{
#else
Config::Config(int argc,char *argv[],char *head)
{
#endif
    char256 readme;
    int i;

    fenv=NULL;
    exam=false;
    envs=NULL;
#ifdef __GNUC__
    char *pt=strrchr(argv[0],'/');
#else
    char *pt=strrchr(argv[0],'\\');
#endif
    sprintf(readme,"%s.env",head?head:(pt?pt+1:argv[0]));
    for (i=1; i<argc; i++)
    {
        if (strchr(argv[i],'='))
        {
        }
        else if (!strcmp(argv[i],"-readme"))
        {
            strcpy(readme,argv[++i]);
        }
        else if (!strcmp(argv[i],"-config"))
        {
            //LJ-- static
            char256 config="";
            FILE *fin;
            i++;
            TextReadOpen(fin,argv[i]);
            while (!feof(fin))
            {
                if (fscanf(fin,"\n %[^\n]s",config)<1) break;
                SetEnv(envs,config);
            }
            fclose(fin);
        }
        else if (!strcmp(argv[i],"-d"))
        {
            i++;
        }
        else if (!strcmp(argv[i],"-e"))
        {
            exam=true;
        }
        else if (!strcmp(argv[i],"-h"))
        {
            printf("Usage: %s [options ...]\n",argv[0]);
            printf("  -d dir       chdir to the specified dir first\n");
            printf("  -e           examine configurations\n");
            printf("  -config file configuration file\n");
            printf("  -readme file define readme file name\n");
            printf("  xxx=xxx      environment setting\n");
            printf("  -h           this help\n\n");
            printf("Compiling date: %s\n\n",__DATE__);
            exit(3);
        }
    }
    for (i=1; i<argc; i++)
    {
        if (strchr(argv[i],'='))
        {
            SetEnv(envs,argv[i]);
        }
        else if (!strcmp(argv[i],"-d"))
        {
#ifdef WIN32
            _chdir(argv[++i]);
#else
            chdir(argv[++i]);
#endif
        }
    }
    fenv=stdout;
    if (!exam) TextWriteOpen(fenv,readme);
    fprintf(fenv,"Environment settings for %s\n\n",argv[0]);
    for (i=0; i<argc; i++)
        if (!strchr(argv[i],'=')) fprintf(fenv,"%s ",argv[i]);
    fprintf(fenv,"\n\n");
}

Config::~Config(void)
{
    for (aConfigEnv *tenv,*env=envs; (tenv=env); delete tenv)
        env=env->next;
    if (exam) exit(3);
    if (fenv)
    {
        fprintf(fenv,"Compiling date: %s\n",__DATE__);
        fclose(fenv);
    }
}
