#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//variables for statistic
long int help_llist[2];
static struct linkedList list_of_lists = {.name = "list_of_lists", .data = NULL, .next = NULL, .prev = NULL};

void initlol()
{
    if(list_of_lists.data == NULL)
    {
        help_llist[0] = (long int)(&list_of_lists);
        help_llist[1] = (long int)(&list_of_lists);
        list_of_lists.data = &help_llist;
    }
}
//creating new linkedList 

struct linkedList *createLinkedList(char* name, int showErr)
{
    if(list_of_lists.data == NULL)
        initlol();
    if(getLinkedList(name, 1,0)!=NULL) //check compares with other lists
    {
        if(showErr)
            printf("List with name %s already exists\n", name);
        return NULL; //returning NULL if list with the same name exists
    }
    struct linkedList *newList = (struct linkedList*)malloc(sizeof(struct linkedList)); //allocating memory for new List
    strcopy(newList->name, name); //copying name to the list
    newList->data = NULL;
    newList->next = NULL;
    newList->prev = NULL;
    addElement("list_of_lists", (char*)newList, 0); //adding record of new list to the list of lists
    return newList;
}

//getting pointer of list from list_of_lists 

struct linkedList *getLinkedList(char* name, int headTail,int showErr)
{
    struct linkedList *temp_list = ((struct linkedList*)(*((long int*)list_of_lists.data)));
    int rez;
    int sch = 0;
    do
    {
        rez = strcmp(((struct linkedList*)(*((long int*)temp_list->data)))->name,name);
        if(rez == 0)
            if(headTail)
                return (struct linkedList*)(*((long int*)temp_list->data));
            else
                return (struct linkedList*)(*((long int*)temp_list->data+1));
            else if(rez > 0)
                break;
        sch++;
    }while((temp_list = temp_list->next)!=NULL);
    if(showErr)
        printf("List with name %s doesn't exist\n", name);
    return NULL;
}

//count elements 

int countElements(struct linkedList *lst)
{
    int number = 0;
    for(; (lst = lst->next)!=NULL; number++);
    return number;
}

//adding elements in List 

int addElement(char* listname, char* value, int showErr)
{
    struct linkedList* list = getLinkedList(listname,1,0); //get head of the list
    struct linkedList *temp;
    if(list!=NULL)
    {
        int iflol = strcmp(list->name, "list_of_lists");
        
        //alloc memory for new element
        struct linkedList *new_element = (struct linkedList*)malloc(sizeof(struct linkedList));
        
        if(list->data != NULL) //check if no data
        {
            char* data = iflol? list->data : ((struct linkedList*)(*((long int*)list->data)))->name;
            int tempint = strcmp(value, data);
            if(tempint == 0)
            {
                if(showErr)
                    printf("Element already exists.\n");
                return 1;
            }
            if(tempint<0) //if this element must be first
            {
                new_element->next = list; //set next of new element
                list->prev = new_element;
                if(iflol)
                {
                    temp = getElementByValue(getLinkedList("list_of_lists", 1, 0), listname); //getting head of list
                    *((long int*)temp->data) = (long int)new_element; //set new head
                }
                else
                {
                    *((long int*)list_of_lists.data) = (long int)new_element;
                }
            }
            else
            {
                if(iflol)
                    temp = getLinkedList(listname, 0, 1);
                else
                    temp = ((struct linkedList*)(*(((long int*)list_of_lists.data+1))));
                
                tempint = iflol? strcmp(value, temp->data) : strcmp(value, ((struct linkedList*)(*((long int*)(temp->data))))->name);
                int choice;
                if(tempint>0)
                    choice = 1;
                else
                    choice = 0;
                list = temp;
                
                tempint = 1;
                
                while(choice? (list->next!=NULL) : (list->prev!=NULL))
                {
                    if(iflol)
                        tempint = strcmp(value, choice? (list->next->data) : (list->prev->data));
                    else
                        tempint = strcmp(value, choice? (((struct linkedList*)*((long int*)(list->next->data)))->name) :(((struct linkedList*)*((long int*)(list->prev->data)))->name));
                    if(choice)
                    {
                        if(tempint<0)
                        {
                            new_element->next = list->next;
                            new_element->prev = (struct linkedList*)list;
                            
                            list->next->prev = new_element;
                            list->next = new_element;
                            tempint = 0;
                            break;
                        }
                    }
                    else
                    {
                        if(tempint>0)
                        {
                            new_element->prev = list->prev;
                            new_element->next = (struct linkedList*)list;
                            
                            list->prev->next = new_element;
                            list->prev = new_element;
                            tempint = 0;
                            break;
                        }
                    }
                    if(tempint==0)
                    {
                        if(showErr)
                            printf("Element already exists.\n");
                        return 1;
                    }
                    if(choice)
                        list = list->next;
                    else
                        list = list->prev;
                }
                if(tempint)
                {
                    list->next = new_element;
                    new_element->prev = list;
                    new_element->next = NULL;
                }
            }
            
            void* dat = iflol? malloc(strlen(value)) : malloc(sizeof(long int)*2); //malloc different sizes for pointer or data
            
            if(iflol)// changing data
            {
                strcpy(dat, value);
            }
            else
            {
                *(long int*)dat = (long int)value;
                *((long int*)dat+1) = (long int)value;
            }
            
            strcpy(new_element->name, list->name); //set name of list
            
            new_element->data = dat; //add data to the list
            if(tempint == 0)
            {
                *(((long int*)(getElementByValue(getLinkedList("list_of_lists", 1, 0), listname))->data)+1) = (long int)new_element;
            }
        }
        else
        {
            char* dat = malloc(strlen(value));
            strcpy(dat, value);
            list->data = dat;
        }
        return 0;
    }
    else
    {
        if(showErr)
            printf("List with name %s doesn't exist\n", listname);
        return 1;
    }
}

//get element in list 

struct linkedList *getElementById(struct linkedList* list, int id)
{
    for(int i = 0; (list!=NULL); i++)
    {
        if(id==i)
            return list;
        else
            list = list->next;
    }
    return NULL;
}

//get element by value 

struct linkedList* getElementByValue(struct linkedList* list, void* value)
{
    if(list==NULL)
        return NULL;
    if(value==NULL)
        return getElementById(list, 0);
    int rez;
    if(strcmp(list->name, "list_of_lists") == 0)
    {
        do
        {
            if(list->data!=NULL)
            {
                rez = strcmp(((struct linkedList*)(*((long int*)list->data)))->name,value);
                if(rez == 0)
                    return list;
                if(rez>0)
                    return NULL;
            }
        }while((list = list->next)!=NULL);
    }
    else
    {
        do
        {
            if(list->data!=NULL)
            {
                rez = strcmp(list->data,value);
                if(rez == 0)
                    return (struct linkedList*)(list);
                if(rez>0)
                    return NULL;
            }
        }while((list = list->next)!=NULL);
    }
    return NULL;
}

//delete element 

int deleteElementByValue(char* listname, char* value, int showErr)
{
    struct linkedList* list = getLinkedList(listname,1,0);
    if(list!=NULL)
    {
        struct linkedList *temp = getElementByValue(list, value);
        if(temp!=NULL)
        {
            if(temp == list) //if needs to del first element of list
            {
                if(countElements(list)!=0) //if list has not only 1 element
                {
                    struct linkedList* temp2 = getElementByValue(getLinkedList("list_of_lists", 1, 0), list); //get element from list of lists for change head of list
                    *((long int*)(temp2->data)) = (long int)list->next; //changing head of list
                    free(temp->data); //delete data of this element
                    free(temp); //delete element
                }
                else
                {
                    free(list->data); //delete data from element
                    list->data = NULL;
                }
            }
            else
            {
                list = getLinkedList(list->name,1,0); //get head of list
                struct linkedList *temp2 = temp->next; //get next element
                temp->next = NULL;
                int number = countElements(list)-1; //count elements before chosen one
                free(temp->data); //delete data
                free(temp); //delete element
                temp = getElementById(list, number); //get element before chosen one
                temp->next = temp2; //connect elements before and after removed
            }
            return 0;
        }
        else
        {
            if(showErr)
                printf("Element with data %s doesn't exist in list %s\n", value, listname);
            return 2;
        }
    }
    else
    {
        if(showErr)
            printf("List with name %s doesn't exist\n", listname);
        return 1;
    }
}

//delete list 
int deleteList(char* listname, int showErr)
{
    if(compare("\0", listname)) //check if listname is nothing
    {
        struct linkedList* list = getLinkedList(listname,1,0); //getting list
        if(list!=NULL)
        {
            struct linkedList* temp;
            
            deleteElementByValue("list_of_lists", listname, 0); //delete record about list
            
            while(list!=NULL) //delete all elements
            {
                temp = list;
                
                if(list->data!=NULL)
                    free(list->data);
                
                list = list->next;
                temp->next = NULL;
                
                free(temp);
            }
            return 0;
        }
        else
        {
            if(showErr)
                printf("List with name %s doesn't exists\n", listname);
            return 2;
        }
    }
    else
    {
        if(showErr)
            printf("It's impossible to delete nothing\n");
        return 1;
    }
}

//print list 

int printList(char* listname, int showErr)
{
    if(listname!=NULL)
    {
        struct linkedList* list = getLinkedList(listname,1,0);
        if(list!=NULL)
        {
            char* data = NULL;
            int iflol = strcmp(list->name, "list_of_lists");
            printf("%s = [ ", list->name);
            while((list->next)!=NULL)
            {
                printf("%s, ", iflol? list->data : ((struct linkedList*)(*((long int*)list->data)))->name);
                list = list->next;
            }
            if(list->data!=NULL)
                printf("%s ]\n", iflol? list->data : ((struct linkedList*)(*((long int*)list->data)))->name);
            else
                printf("( null ) ]\n");
            return 0;
        }
        else
        {
            if(showErr)
                printf("List with name %s doesn't exist.\n", listname);
            return 2;
        }
    }
    else
    {
        if(showErr)
            printf("Name of printing list is nothing\n");
        return 1;
    }
}

//isin 

int isin(char* listname1, char* listname2, int showErr)
{
    struct linkedList* list1 = getLinkedList(listname1,1,0);
    if(list1==NULL)
    {
        if(showErr)
            printf("List with name %s doesn't exist.\n", listname1);
        return 1;
    }
    struct linkedList* list2 = getLinkedList(listname2,1,0);
    if(list2==NULL)
    {
        if(showErr)
            printf("List with name %s doesn't exist.\n", listname2);
        return 1;
    }
    struct linkedList* temp = list2;
    while(list1!=NULL)
    {
        temp = getElementByValue(temp, list1->data);
        if(temp==NULL)
        {
            if(showErr)
                printf("List \"%s\" is not in \"%s\"\n", listname1,listname2);
            return 0;
        }
        list1 = list1->next;
    }
    if(showErr)
        printf("List \"%s\" is in \"%s\"\n", listname1,listname2);
    return 0;
}


//union 

void uniLog(struct linkedList* firstList, struct linkedList* secList, struct linkedList* rez)
{
    char* dat1;
    char* dat2;
    char* datifnull = "~";
    int tempint;
    while((firstList!=NULL)||((secList!=NULL)))
    {
        dat1 = (firstList==NULL)? datifnull : firstList->data;
        dat2 = (secList==NULL)? datifnull : secList->data;
        tempint = strcmp(dat1, dat2);
        if(tempint<0)
        {
            addElement(rez->name, dat1, 0);
            firstList = firstList->next;
        }
        else if(tempint>0)
        {
            addElement(rez->name, dat2, 0);
            secList = secList->next;
        }
        else
        {
            addElement(rez->name, dat1, 0);
            secList = secList->next;
            firstList = firstList->next;
        }
    }
}

struct linkedList* uniLists(char* listname1, char* listname2, char* namerez, int showErr)
{
    char name[256] = "|Union ";
    strcopy(&(name[strlen(name)]), listname1);
    name[strlen(name)] = ' ';
    strcopy(&(name[strlen(name)]), listname2);
    name[strlen(name)] = '\0';
    struct linkedList* rez = logics((void (*) (struct linkedList*,struct linkedList*, struct linkedList*))(uniLog), listname1, listname2, namerez, name, showErr);
    return rez;
}

//intersec 

void interLog(struct linkedList* firstList, struct linkedList* secList, struct linkedList* rez)
{
    struct linkedList* temp = secList;
    while(firstList != NULL)
    {
        if(getElementByValue(temp, firstList->data)!=NULL)
        {
            addElement(rez->name, firstList->data, 0);
        }
        firstList = firstList->next;
    }
}

struct linkedList* intersec(char* listname1, char* listname2, char* namerez, int showErr)
{
    char name[256] = "|Isec ";
    strcopy(&(name[strlen(name)]), listname1);
    name[strlen(name)] = ' ';
    strcopy(&(name[strlen(name)]), listname2);
    name[strlen(name)] = '\0';
    struct linkedList* rez = logics((void (*) (struct linkedList*,struct linkedList*, struct linkedList*))(interLog), listname1, listname2, namerez, name, showErr);
    return rez;
}

//diff 

void diffLog(struct linkedList* firstList, struct linkedList* secList, struct linkedList* rez)
{
    while(firstList != NULL)
    {
        if(getElementByValue(secList, firstList->data)==NULL)
        {
            if(getElementByValue(rez, firstList->data)==NULL)
                addElement(rez->name, firstList->data, 0);
        }
        firstList = firstList->next;
    }
}

struct linkedList* diff(char* listname1, char* listname2, char* namerez, int showErr)
{
    char name[256] = "|Diff ";
    strcopy(&(name[strlen(name)]), listname1);
    name[strlen(name)] = ' ';
    strcopy(&(name[strlen(name)]), listname2);
    name[strlen(name)] = '\0';
    struct linkedList* rez = logics((void (*) (struct linkedList*,struct linkedList*, struct linkedList*))(diffLog), listname1, listname2, namerez, name, showErr);
    return rez;
}

//simmdiff

void simmdiffLog(struct linkedList* firstList, struct linkedList* secList, struct linkedList* rez)
{
    struct linkedList* temp = firstList;
    while(firstList != NULL)
    {
        if(getElementByValue(secList, firstList->data)==NULL)
        {
            if(getElementByValue(rez, firstList->data)==NULL)
                addElement(rez->name, firstList->data, 0);
        }
        firstList = firstList->next;
    }
    while(secList != NULL)
    {
        if(getElementByValue(temp, secList->data)==NULL)
        {
            if(getElementByValue(rez, secList->data)==NULL)
                addElement(rez->name, secList->data, 0);
        }
        secList = secList->next;
    }
}

struct linkedList* simmdiff(char* listname1, char* listname2, char* namerez, int showErr)
{
    char name[256] = "|SDiff ";
    strcopy(&(name[strlen(name)]), listname1);
    name[strlen(name)] = ' ';
    strcopy(&(name[strlen(name)]), listname2);
    name[strlen(name)] = '\0';
    struct linkedList* rez = logics((void (*) (struct linkedList*,struct linkedList*, struct linkedList*))(simmdiffLog), listname1, listname2, namerez, name, showErr);
    return rez;
}

//function for help me 

struct linkedList* logics(void (*function)(struct linkedList*, struct linkedList*, struct linkedList*), char* listname1, char* listname2, char* namerez, char* nameifnull , int showErr)
{
    struct linkedList* firstList = getLinkedList(listname1,1,0);
    struct linkedList* secList = getLinkedList(listname2,1,0);
    if(firstList!=NULL)
    {
        if(secList!=NULL)
        {
            int boolean = 0; //variable for check if need to continue work with result out of this function
            if(namerez==NULL)
                boolean = 1;
            else
            {
                if(getLinkedList(namerez, 1, 0)!=NULL)
                {
                    if(showErr)
                        printf("List with name %s already exists\n", namerez);
                    return NULL;
                }
            }
            if(boolean)
                namerez = nameifnull;
            struct linkedList* rez = createLinkedList(namerez, 0);
            if(rez==NULL)
            {
                printf("%s from lists %s and %s was not created.", namerez, listname1, listname2);
                return NULL;
            }
            
            (*function)(firstList, secList, rez);
            
            if(boolean)
            {
                printList(namerez, 0);
                deleteList(namerez, 0);
                return NULL;
            }
            else
                return rez;
        }
        else
        {
            if(showErr)
                printf("List with name %s doesn't exist\n", listname2);
            return NULL;
        }
    }
    else
    {
        if(showErr)
            printf("List with name %s doesn't exist\n", listname1);
        return NULL;
    }
}

//show ALL SYSTEM OF LISTS

int showAll()
{
    struct linkedList* temp = getLinkedList("list_of_lists",1,0);
    while(temp!=NULL)
    {
        printList(((char*)*(long int*)temp->data), 0);
        temp = temp->next;
    }
    return 0;
}

//compare strings with output that i need

int compare(char* firstLine, char* secondLine)
{
    if(firstLine==NULL)
        return 1;
    if(secondLine==NULL)
        return 0;
    while(1)
    {
        if((*firstLine)>(*secondLine))
            return 0;
        else if((*firstLine)<(*secondLine))
            return 1;
        firstLine++;
        secondLine++;
    }
    return 0;
}

//copying strings (psihanul)

int strcopy(char* fc,char* sc)
{
    int size;
    for(size = 0; (*fc++ = *sc++)!='\0'; size++);
    return size;
}