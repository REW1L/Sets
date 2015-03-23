#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include "LinkedList.h"
int readCommand(char*);

int openFile(char*);
int showtime = 0;
int main()
{
    initlol();
    printf("Welcome in SetsV2.0.\nSimply type \"help\" for information about commands existing in system.\n");
    char* str = malloc(256);
    scanf("%256[^\n]s", str);
    while (strcmp(str, "exit") != 0)
    {
        if(showtime)
            printf("%.5f seconds left.\n", testTime((int (*)(void*))(readCommand), str));
        else
            readCommand(str);
        for(int i = 0; i<256; str[i++]='\0');
        getchar();
        scanf("%256[^\n]s", str);
    }
    return 0;
}

int readCommand(char* line)
{
    char command[10] = "";
    char* temp;
    int size = 0;
    int ret = 55;
    while(*line==' '||*line=='\t')
        line++;
    if(*line=='\0'||*line=='\n')
        return 0;

    for(; (*line!=' ')&&(*line!='\0')&&(size<10); size++)
    {
        command[size] = *line++;
    }
    if(strcmp(command, "open") != 0)
    {
        for(temp = line; (*temp!='\0')&&(*temp!='\n')&&(*temp!=13)&&(*temp!='\377'); temp++)
            if((*temp<32)||(*temp>122))//||(*temp>32&&*temp<48&&*temp!=45)||(*temp>57&&*temp<65)||(*temp>93&&*temp<97&&*temp!=95)||(*temp>122)||(*temp==92))
            {
                printf("Found illegal symbol \'%c\'\n", *temp);
                return 1;
            }
    }
    int argv = 0;
    temp = line;
    while(*temp++!='\0');
    
    while((*temp=='\0')||(*temp==']')||(*temp=='\t')||(*temp=='\n')||(*temp==' ')||(*temp=='\377'))
        *temp-- = '\0';

    temp = line;
    int booleantemp = 0;

    for(; *temp!='\0'; temp++)
    {
        if((*temp==' ')&&(booleantemp==0))
        {
            argv++;
            booleantemp = 1;
        }
        else if((*temp!=' ')&&(booleantemp==1))
        {
            booleantemp = 0;
        }
    }
    char* args[10];
    
    
    for(int i = 0; (*line)!='\0'; line++)
    {
        if(*line==' ')
        {
            *line = '\0';
            ++line;
            if(*line=='[')
                *line++ = '\0';
            args[i] = line;
            i++;
        }
    }
    
    if(strlen(command) == 3)
    {
        if(strcmp(command,"new")==0)
        {
            if(argv == 1)
                ret = createLinkedList(args[0], 1)? 0:1;
            else if(argv>1)
                printf("Too many arguments for command \"new\"\n (need: 1, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"new\"\n (need: 1, used: %d)\n", argv);
        }
        else if(strcmp(command, "add")==0)
        {
            if(argv == 2)
                ret = addElement(args[0], args[1], 1)? 1:0;
            else if(argv>3)
                printf("Too many arguments for command \"add\"\n (need: 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"add\"\n (need: 2, used: %d)\n", argv);
        }
        else if(strcmp(command, "del")==0)
        {
            if(argv == 2)
                ret = deleteElementByValue(args[0], args[1], 1);
            else if(argv == 1)
                ret = deleteList(args[0], 1);
            else if(argv>2)
                printf("Too many arguments for command \"del\"\n (need: 2 or 1, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"del\"\n (need: 2 or 1, used: %d)\n", argv);
        }
    }
    else if(strlen(command) == 4)
    {
        if(strcmp(command, "isin") == 0)
        {
            if(argv == 2)
            {
                ret = getElementByValue(getLinkedList(args[1],1,1), args[0])? 0:1;
                if(ret)
                    printf("Element %s is not in list %s\n", args[0], args[1]);
                else
                    printf("Element %s is in list %s\n", args[0], args[1]);
                ret = 0;
            }
            else if(argv>2)
                printf("Too many arguments for command \"isin\"\n (need: 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"isin\"\n (need: 2, used: %d)\n", argv);
        }
        else if(strcmp(command, "diff")==0)
        {
            if(argv == 3)
                ret = diff(args[0], args[1], args[2], 1)? 0:1;
            else if(argv == 2)
                ret = diff(args[0], args[1], NULL, 1)? 0:0;
            else if(argv>3)
                printf("Too many arguments for command \"diff\"\n (need: 3 or 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"diff\"\n (need: 3 or 2, used: %d)\n", argv);
        }
        else if(strcmp(command, "save") == 0)
        {
            printf("Not supported yet\n"); //not supported yet
        }
        else if(strcmp(command, "Isin") == 0)
        {
            if(argv == 2)
            {
                ret = isin(args[1], args[0], 1);
                ret = 0;
            }
            else if(argv>2)
                printf("Too many arguments for command \"isin\"\n (need: 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"isin\"\n (need: 2, used: %d)\n", argv);
        }
        else if(strcmp(command, "show") == 0)
        {
            if(argv == 1)
                ret = printList(args[0], 1);
            else if(argv>1)
                printf("Too many arguments for command \"isin\"\n (need: 1, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"isin\"\n (need: 1, used: %d)\n", argv);
        }
        else if(strcmp(command, "open") == 0)
        {
            if(argv == 1)
                ret = openFile(args[0]);
            else if(argv>1)
                printf("Too many arguments for command \"isin\"\n (need: 1, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"isin\"\n (need: 1, used: %d)\n", argv);
        }
        else if(strcmp(command, "help") == 0)
        {
            if(argv == 0)
            {
                ret = 0;
                printf("Help:\nopen <path_to_file> - read commands from file\nnew <list> - create new list\nexist <list> - check if list already created\ndel <list> - delete list\ndel<list> <element> - delete element from list\nadd <list> <element> - adding element to the list\nisin <element> <list> - check if element is in list\nIsin <list1> <list2> - check if list1 is in list2\nunion <list> <list> [list] ([list] - optional) - union\nintersec <list> <list> [list] ([list] - optional) - intersection\ndiff <list> <list> [list] ([list] - optional) - difference\nsimmdiff <list> <list> [list] ([list] - optional) - symmetrical difference\nshow <list> - show list\nShowall - show all lists\nexit - exit of program\nshowtime - show/hide all timings\n");
            }
            else if(argv>0)
                printf("Too many arguments for command \"isin\"\n (need: 0, used: %d)\n", argv);
        }
    }
    else if(strlen(command) == 5)
    {
        if(strcmp(command, "exist") == 0)
        {
            if(argv == 1)
            {
                ret = getLinkedList(args[0], 1, 0)? 0:1;
                if(ret == 0)
                    printf("List %s doesn't exist.\n", args[0]);
                else
                    printf("List %s exists\n", args[0]);
                ret = 0;
            }
            else if(argv>1)
                printf("Too many arguments for command \"exist\"\n (need: 1, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"exist\"\n (need: 1, used: %d)\n", argv);
        }
        if(strcmp(command, "union") == 0)
        {
            if(argv == 2)
                ret = uniLists(args[0], args[1], NULL, 1)? 0:1;
            else if(argv == 3)
                ret = uniLists(args[0], args[1], args[2], 1)? 0:1;
            else if(argv>3)
                printf("Too many arguments for command \"union\"\n (need: 3 or 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"union\"\n (need: 3 or 2, used: %d)\n", argv);
        }
    }
    else if(strlen(command) == 7)
    {
        if(strcmp(command, "Showall") == 0)
        {
            if(argv == 0)
                ret = showAll();
            else if(argv>0)
                printf("Too many arguments for command \"Showall\"\n (need: 1, used: %d)\n", argv);
        }
    }
    else if(strlen(command) == 8)
    {
        if(strcmp(command, "simmdiff") == 0)
        {
            if(argv == 2)
                ret = simmdiff(args[0], args[1], NULL, 1)? 0:0;
            else if(argv == 3)
                ret = simmdiff(args[0], args[1], args[2], 1)? 0:1;
            else if(argv>3)
                printf("Too many arguments for command \"simmdiff\"\n (need: 3 or 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"simmdiff\"\n (need: 3 or 2, used: %d)\n", argv);
        }
        else if(strcmp(command, "intersec") == 0)
        {
            if(argv == 2)
                ret = intersec(args[0], args[1], NULL, 1)? 0:0;
            else if(argv == 3)
                ret = intersec(args[0], args[1], args[2], 1)? 0:1;
            else if(argv>3)
                printf("Too many arguments for command \"intersec\"\n (need: 3 or 2, used: %d)\n", argv);
            else
                printf("Too few arguments for command \"intersec\"\n (need: 3 or 2, used: %d)\n", argv);
        }
        if(strcmp(command, "showtime") == 0)
        {
            if(showtime == 0)
            {
                showtime = 1;
                printf("Time is on\n");
            }
            else
            {
                showtime = 0;
                printf("Time is off\n");
            }
            ret = 0;
        }
    }
    if(ret==55)
    {
        ret = 1;
        printf("%s: command not found\n", command);
    }
    return ret;
}

int openFile(char* path)
{
    FILE *fl = fopen(path, "r");
    if(fl==NULL)
    {
        printf("Unable to open file \"%s\".\n", path);
        return 1;
    }
    
    char temp[256];
    
    for(int i = 0; i<256; i++)
        temp[i] = '\0';
    int line = 0;
    while((temp[0] = fgetc(fl))!=EOF)
    {
        line++;
        for(int i = 1;((temp[i] = fgetc(fl))!='\n')&&(temp[i]!=EOF)&&(temp[i]!='\0');i++);
        temp[strlen(temp)] = '\0';
        for(int i =0; i<strlen(temp); i++)
            if(*temp==13)
                *temp = 0;
        if(showtime)
            printf("line with number %d, time: %lu sec, comm: %s", line, (long int)(clock()/CLOCKS_PER_SEC), temp);
        if(readCommand(temp) == 1)
        {
            printf("Error in line %d\n", line);
        }
        
        for(int i = 0; i<256; i++)
            temp[i] = '\0';
    }
    fclose(fl);
    return 0;
}
