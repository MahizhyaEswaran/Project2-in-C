///////////////////////////////////////////////////
       //  CO222 PROJECT-02	E/18/097	 //          
///////////////////////////////////////////////////
//HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//STRUCTURE FOR STORE EVERY MEETING
typedef struct _m {
	char* meeting;
	int amount1;
	int order1;
	struct _m*next;
}meeting_d;


//STRUCTURE FOR STORE EVERY TIME DUTRATION
typedef struct _t{
	char tim;
	int Amount;
	int order;
}time;

//STRUCTURE FOR STORE PARTICIPANT
typedef struct _p{
	char par;
	int Amount2;
	int order2;
}part;

//STRUCTURE FOR STORE EVERY CHARECTORS
typedef struct node
{
    char name[50];
    int participants;
    int duration;
    int NameFrq;
    struct node * next;
} info;


//For link list operation
info * HEAD=NULL,*TAILL=NULL;


//DECLARATION OF FUNCTIONS
void swapedHere(info *a,info *b);
void sorted_particioation(int,int );
void sorted_Duration(int max,int);
void scaled(int total1,int max,info **HEAD_reference,int x);
void sorted_NameFrq(int,int );
void Not_Scaled(int total1,int max,info **HEAD_reference,int x);
int Time_To_Minute(char duration[]);
int Tot_NameFrq=0,Tot_Timduration=0,Tot_participantss=0;
//int time(char* str);
//int string_to_int(char* str);
//void sortArray_duration(info *str,int size);
//void sortArray_meetings(info *str,int size);
//void sortArray_participants(info *str,int size);
//void delete_node(info *del_node);
//void test();

int main(int argc, char **argv){
     //defaults values
    char line[1000];
    int column_count= 0,max=10;
    char name[50]; 
    int participants,duration;
    int l_value,flag_number=0,flag_count=0,scaled_num=0,l_flag=0,corrupted_file=0; 
    char l_string[10];
    int argument_count, l_check=0;  //validity of number input for -l flag
    

  
    //arg Handle///
    if(argc < 2){
        printf("No input files were given\nusage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
        return 0;
    }


    for(int k=1;k<argc;k++){   
        if(strcmp(argv[k], "-p")==0){ //Set flag number to 1 if the argument is -p, which calls the sort by participants function 
                flag_count=flag_count+1;
                flag_number=1;
            }
            else if(strcmp(argv[k], "-m")==0){//Set flag number to 2 if the argument is -m, which calls the sort by participants function 
                flag_count=flag_count+1;
                flag_number=2;
            }
            else if(strcmp(argv[k], "-t")==0){ //Set flag number to 3 if the argument is -t, which calls the sort by participants function  
                flag_count=flag_count+1;
                flag_number=3;
                
            }
            else if(strcmp(argv[k], "--scaled")==0){  ////////////scale checking////////////  
                scaled_num=1;
            }
            else if(strcmp(argv[k], "-l")==0){ 
                if (argv[k+1]!=NULL){
                    if (isdigit(argv[k+1][0])){
                        strcpy(l_string,argv[k+1]);
                        l_value = atoi(argv[k+1]);
                        l_flag=1;
                        max=l_value;
                        if(l_value == 0){
                            return 0;
                        }
                    }
                    else{
                        printf("Invalid options for [-l]\n");
                        printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
                        return 0;
                        }
                    }
                else{
                    printf("Not enough options for [-l]\n");
                    printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
                    return 0;
                    }
                }
        
            else{
                if (argv[k][0]=='-'){

                    if (argv[k][1]=='l'){

                        if (argv[k][2]!='\0'){
                            printf("Invalid option [%s]\n",argv[k]);
                            printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
                            return 0;
                        }

                        else{
                            printf("Not enough options for [-l]\n");
                            printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
                            return 0;
                        }
                    }

                    else{
                        printf("Invalid option [%s]\n",argv[k]);
                        printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
                        return 0;
                    }
                }
            }   
        }
    
    if(flag_count>1){
        printf("Cannot plot multiple parameters in same graph.\n");
        printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n",argv[0]);
        return 0;
        }  
    
    for(int k=1;k<argc;k++){  

        FILE *file_pointer = fopen(argv[k],"r");//open main file
        if (!file_pointer)
        {
            if ((strcmp(argv[k], "-t")==0)||(strcmp(argv[k], "-l")==0)||(strcmp(argv[k], "-m")==0)||(strcmp(argv[k], "-p")==0)||(strcmp(argv[k], "--scaled")==0)){
                continue;
            }
            // -l flag for the validation  input files
            if (strcmp(argv[k],l_string)==0){
                for (int m=0;m<strlen(l_string);m++){
                    if (isdigit(argv[k][m])){
                        l_check=1;
                    }
                    else{
                        l_check=2;
                        break;
                    }
                }            
                if (l_check==1){
                    continue;
                }
                else{
                    printf("Invalid options for [-l]\n");
                    printf("usage: ./samplev1 [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n");
                    return 0;
                }
            }
           //validity of csv file olny
            else{
                if (strcmp(strrchr(argv[k],'\0')-4,".csv")==0){
                    printf("Cannot open one or more given files\n");
                    corrupted_file=1;
                    return 0;
                }
                else{
                    printf("Only .csv files should be given as inputs.\n");
                    return 0;
                }
            }
        }
         //Read the file
        while (fgets(line,1000,file_pointer))
        {
            column_count = 0;  
            char *information = strtok(line,",");
            while (information)  //seperate info by,
            {   
                if (column_count == 0)
                {
                    strcpy(name,information); //name
                }
                if (column_count == 1)
                {
                    participants= atoi(information); //participation
                }
                if (column_count == 2)
                {
                    duration= Time_To_Minute(information); //Read the time duration 
                }
                information = strtok(NULL,",");
                column_count++;
            }
                info *temp=HEAD;
               //when name is already there, store same 
                for (temp = HEAD; temp != NULL; temp = temp->next) {
                        if (strcmp(temp->name, name) == 0) {
                            break;
                        }
                    }

                
                if (HEAD==NULL) {
                     //Make a memory allocation for the new node and copy the relevant elements
                    info * data= (info *)(malloc(sizeof(info)));
                    strcpy(data->name, name);
                    data->NameFrq= 1;
                    data->participants =participants;
                    data->duration =duration;
                    Tot_Timduration=Tot_Timduration+duration;
                    Tot_NameFrq=Tot_NameFrq+1;
                    Tot_participantss=Tot_participantss+participants;
                    HEAD = data;
                    TAILL = data;
                    HEAD->next=NULL;
                    
                }
                else{
                    //Add the data to the last node if the name is new
                    if (temp == NULL) {
                        info * data= (info *)(malloc(sizeof(info)));
                        strcpy(data->name, name);
                        data->NameFrq= 1;
                        data->participants =participants;
                        data->duration =duration;
                        Tot_Timduration=Tot_Timduration+duration;
                        Tot_NameFrq=Tot_NameFrq+1;
                        Tot_participantss=Tot_participantss+participants;
                        TAILL->next=data;
                        data->next =NULL;
                        TAILL = data;
                    }

                   
                    else {
                    temp->NameFrq=temp->NameFrq+1;
                    temp->participants =temp->participants+participants;
                    temp->duration=temp->duration+duration;
                    Tot_Timduration=Tot_Timduration+duration;
                    Tot_NameFrq=Tot_NameFrq+1;
                    Tot_participantss=Tot_participantss+participants;
                    }
                } 
            }
        fclose(file_pointer);
        }

        
    argument_count=argc;    
    //For scaled option of the graph
    if (scaled_num==1){
        if (flag_number==1){
            sorted_particioation(max,2);
            return 0;
        }
        else if (flag_number==2){
            sorted_NameFrq(max,2);
            return 0;    
        }
        else if (flag_number==3){
            sorted_Duration(max,2);
            return 0;    
        }
        else if (flag_number==0&&l_flag==1){
            sorted_NameFrq(max,2);
            return 0;
        }
     }
    if (flag_number==1){
            sorted_particioation(max,1);
            return 0;    
        }
    else if (flag_number==2){
            sorted_NameFrq(max,1);
            return 0;    
        }
    else if (flag_number==3){
            sorted_Duration(max,1);
            return 0;    
        }
    if (flag_number==0&&l_flag==1){
        sorted_NameFrq(max,1);
        return 0;
    }
    
    if ((argc==argument_count)&&(corrupted_file==0)){
        if (scaled_num==1){
            sorted_NameFrq(max,2);
            return 0;
        }
        else if (scaled_num==0){
            sorted_NameFrq(max,1);
            return 0;
        }
    }

    return 0;
}




//Function to sort by participantss
void sorted_particioation(int max,int num){
    info *node=HEAD, *temporary_node = NULL;
   //Sort our data by iterating through nodes
    while(node!=NULL)
    {
        temporary_node=HEAD; 
        while(temporary_node->next!=NULL)//Follow the path until you reach the second-to-last node
        {
           if(temporary_node->participants <temporary_node->next->participants)//a comparison of the node's participants
            {
              swapedHere(temporary_node,temporary_node->next); 
            }
         temporary_node = temporary_node->next;   // Continue the loop by moving to the next node 
        }

        node = node->next;    ///in the big loop, move to the next node
    }

    if (num==1){    
        Not_Scaled(Tot_participantss,max,&HEAD,1);
    }
    else if (num==2){   
        scaled(Tot_participantss,max,&HEAD,1);
    }
}


//Function for sort by duration
void sorted_Duration(int max,int num){
    info *node=NULL, *temporary_node = NULL;
    node = HEAD;
    while(node != NULL)
    {
        temporary_node=HEAD; 
        while (temporary_node->next!=NULL)
        {
            
           if(temporary_node->duration <temporary_node->next->duration)
            {
              swapedHere(temporary_node,temporary_node->next); // Continue the loop by moving to the next node
            }
         temporary_node = temporary_node->next;  
        }
        node = node->next;   //in the big loop, move to the next node
    }

    if (num==1){
        Not_Scaled(Tot_Timduration,max,&HEAD,2);  
    }
    else if (num==2){
        scaled(Tot_Timduration,max,&HEAD,2); 
    }
}


//Functon: time to Minutes 
int Time_To_Minute(char duration[8]){
    char *read_time = strtok(duration,":"); // sepetrate by: hours minutes
    int minutes,colon_count = 0,hour,min;
    while (read_time)
        {   
            if (colon_count == 0)
            {
                hour = atoi(read_time);  //set hour
            }
            if (colon_count == 1)
            {
                min = atoi(read_time);      //set minuts        
            }
            read_time = strtok(NULL,":");
            colon_count++;
        }
        minutes = (hour * 60) + min;          //return the minutes
    return minutes;
}

//Function for swapedHere the data within two nodes 
void swapedHere(info *a,info *b)
{
    int tempvar;
    char name[50];
    tempvar = a->participants;
    a->participants = b->participants;// swapedHereed participation
    b->participants = tempvar;

    tempvar = a->duration;
    a->duration = b->duration;/// swapedHereed duration
    b->duration = tempvar;

    tempvar = a->NameFrq;
    a->NameFrq = b->NameFrq;// swapedHereed namefreq
    b->NameFrq = tempvar;

    strcpy(name,a->name);
    strcpy(a->name,b->name); //Using a tempropry string and the strcpy function, swapedHere the names of two nodes
    strcpy(b->name,name);
}

//Function for print non scaled section
void Not_Scaled(int total1,int max,info **HEAD_reference,int x){
    info *y=*HEAD_reference;
    info *z=*HEAD_reference;
    int plotting_spaces; 
    int largest_string_len=0,e=0; 
    int spaces,number_len=0; 
    while(z!=NULL){
        if (e==max){
            break;
        }
        if (largest_string_len<strlen(z->name)){
            largest_string_len=strlen(z->name);
            }
        e=e+1;
        z=z->next;
    }
    int limit=0,n=0;  
    printf("\n");
    while(y!=NULL){
        if (limit==max){
            break;
        }
        if (x==1){
            if (limit==0){
                n=y->participants;
                while(n!=0){  
                n=n/10;
                number_len++;
                }  
            }
            spaces=77-largest_string_len-number_len;
            plotting_spaces=(int)((float)(spaces*y->participants)/total1);
        }
        else if (x==2){
            n=y->duration;
            if (limit==0){
                while(n!=0){  
                n=n/10;
                number_len++;
                }  
            }
            spaces=77-largest_string_len-number_len;
            plotting_spaces=(int)((float)(spaces*y->duration)/total1);          
        }
        else if (x==3){
            n=y->NameFrq;
            if (limit==0){
                while(n!=0){  
                n=n/10;
                number_len++;
                }  
            }
            spaces=77-largest_string_len-number_len;
            plotting_spaces=(int)((float)(spaces*y->NameFrq)/total1);            
        }
        for(int i=0;i<(largest_string_len+2);i++){
            printf(" ");
            }
            printf("\u2502");
            for(int j=0;j<plotting_spaces;j++){
            printf("░");
            }
            printf("\n");
            printf(" %s",y->name);
            for(int i=0;i<(largest_string_len-(strlen(y->name)-1));i++){
            printf(" ");
            }
            printf("│");
            
            for(int j=0;j<plotting_spaces;j++){
            printf("░");
            }
            if (x==1){
                printf("%d\n",y->participants);
            }
            else if (x==2){
                printf("%d\n",y->duration);            
            }
            else if (x==3){
                printf("%d\n",y->NameFrq);            
            }

        for(int i=0;i<(largest_string_len+2);i++){
            printf(" ");
            }
            printf("│");
            
            for(int j=0;j<plotting_spaces;j++){
            printf("░");
            }
            printf("\n");
        
        for(int i=0;i<(largest_string_len+2);i++){
          printf(" ");
          }
        printf("│\n");
        y=y->next;
        limit=limit+1;
    }
    
    for(int i=0;i<(largest_string_len+2);i++){    
        printf(" ");
    }
    printf("└");
    for(int i=0;i<(80-(largest_string_len+3));i++){
    printf("─");
    }
    printf("\n");
}

//Function for sort by name freq
void sorted_NameFrq(int max,int num){
    info *node=HEAD, *temporary_node = NULL;
    //Sort our data by iterating through nodes
    while(node!=NULL)
    {
        temporary_node=HEAD; 
        while(temporary_node->next!=NULL)
        {
           if(temporary_node->NameFrq <temporary_node->next->NameFrq)
            {
              swapedHere(temporary_node,temporary_node->next);   //Sort our data by iterating through nodes
            }
         temporary_node = temporary_node->next;   //in the big loop, move to the next node
        }
        node = node->next;    
    }

    if (num==1){   
        Not_Scaled(Tot_NameFrq,max,&HEAD,3);
    }
    else if (num==2){  
        scaled(Tot_NameFrq,max,&HEAD,3);
    }
}

/*
int string_to_int(char* str){
    int len=strlen(str),j=0;
    for(int i=0;i<len;i++){
        j+=(str[i]-48)*pow(10,(len-i-1));
    }
    return j;
	}



int time(char* str){
char* value = strtok(str,":");
int k=0,count=0;
while(value){
    int len=strlen(value),j=0;
    for(int i=0;i<len;i++){
        j+=(value[i]-48)*pow(10,(len-i-1));
    }
    if(count==0){
     k+= j*60;
    }else if(count==1){
    k+=j;}

    value=strtok(NULL,":");
     ++count;
}
return k;
}



void sortArray_duration(info *str,int size){
for(int i=0;i<size;i++){
    for(int j=i+1;j<size;j++){
        if(str[i].duration<str[j].duration){
           info t=str[i];
           str[i]=str[j];
           str[j]=t;
        }
    }
}
}



void sortArray_meetings(info *str,int size){
for(int i=0;i<size;i++){
    for(int j=i+1;j<size;j++){
        if(str[i].meetingNos<str[j].meetingNos){
           info t=str[i];
           str[i]=str[j];
           str[j]=t;
        }
    }
}
}



void sortArray_participants(info *str,int size){
for(int i=0;i<size;i++){
    for(int j=i+1;j<size;j++){
        if(str[i].participants<str[j].participants){
           info t=str[i];
           str[i]=str[j];
           str[j]=t;
        }
    }
}
}
void test(){
//FILE* fp = fopen("longData.csv", "r");      // Opening the required file for reading
//if (!fp){
//    printf("Can't open file\n");
//    return 0;
///}
    char buffer[1000];
    info *input,*head,*current,*temp;
    int counter = 0;
    int column = 1;
    while (fgets(buffer,1000, fp)) {  // Splitting the data
            char* value = strtok(buffer, ",");
            int column = 1;
            input=(info*)malloc(sizeof(info));
             while (value) {           // Column 1
                if (column == 1) {
                    strcpy(input->name,value);}
                if (column == 2) {     // Column 2
                    input->participants=string_to_int(value);}
                if (column == 3) {     // Column 3
                    input->duration = time(value);}
                value = strtok(NULL, ",");
                column++;}
       input->meetingNos=1;
        if(counter==0){
            head=temp=input;      // saving head node
        }else{
        temp->next=input;         // creating and linking next node
        temp=input;}
        counter++;}
temp->next=NULL;
fclose(fp);                  // Close the file

info *meeting_info=malloc(counter*sizeof(info));
//printf("%d",counter);                    // putting all nodes into an array;
int i=0;
for(current=head;current!=NULL;current=current->next){
    meeting_info[i]=*current;
    i++;}

for(int i=0;i<counter;i++){
    for(int j=i+1;j<counter;j++){                                    // Identifying all meetings under each person
       if(strcmp(meeting_info[i].name,meeting_info[j].name)==0){
       meeting_info[i].participants+=meeting_info[j].participants;
       meeting_info[i].meetingNos+=meeting_info[j].meetingNos;
       meeting_info[i].duration+=meeting_info[j].duration;
       for(int k=j;k<counter-1;k++){
       meeting_info[k]=meeting_info[k+1];
       }
       --counter;
       }
    }
}
sortArray_meetings(meeting_info,counter);
for(int i=0;i<counter;i++){
        printf("%s - %d\n",meeting_info[i].name,meeting_info[i].meetingNos);
    //print_bar(meeting_info[i].name,meeting_info[i].meetingNos);
}
}*/

//Prints a scaled version of the graph
void scaled(int total1,int max,info **HEAD_reference,int x){
    info *y=*HEAD_reference;
    info *f=*HEAD_reference;
    int plotting_spaces;  //NUMBER OF SPACE COUNT
    int largest_string_len=0,e=0; //maximum NAME SIZE
    int spaces,number_len=0; //BIGG NUM
    while(f!=NULL){
        if (e==max){
            break;
        }
        if (largest_string_len<strlen(f->name)){
            largest_string_len=strlen(f->name);
            }
        e=e+1;
        f=f->next;
    }
    int limit=0,z=0,n=0,l=0; 
    printf("\n");
    while(y!=NULL){
        if (limit==max){   //When the maximumimum number of rows requested is surpassed, the limit is utilized to break
            break;
        }
        if (x==1){
            n=y->participants;
            z=l;
            if (limit==0){
                while(n!=0){
                    n=n/10;  
                    number_len++;
                    }  
                spaces=77-largest_string_len-number_len;
                plotting_spaces=spaces;
                l=y->participants;
            }
            else if(limit!=0) {
                plotting_spaces=((float)spaces/(float)z)*y->participants;
            }
            
        }
        else if (x==2){
            n=y->duration;
            z=l;
            if (limit==0){
                while(n!=0){  
                n=n/10;
                number_len++;
                    }  
                spaces=77-largest_string_len-number_len;
                plotting_spaces=spaces;
                l=y->duration;
            }
            else if(limit!=0) {
                plotting_spaces=((float)spaces/(float)z)*y->duration;
            }
        }
        else if (x==3){
            n=y->NameFrq;
            z=l;
            if (limit==0){
                while(n!=0)  {  
                n=n/10;
                number_len++;
                    }  
                spaces=77-largest_string_len-number_len;
                plotting_spaces=spaces;
                l=y->NameFrq;
            }
            else if(limit!=0) {
                plotting_spaces=((float)spaces/(float)z)*y->NameFrq;
            }
        }
        for(int i=0;i<(largest_string_len+2);i++){ 
            printf(" ");
            }
            printf("\u2502");
            for(int j=0;j<plotting_spaces;j++){
            printf("░");
            }
            printf("\n");
            printf(" %s",y->name);
            for(int i=0;i<(largest_string_len-(strlen(y->name)-1));i++){
            printf(" ");
            }
            printf("│");
            
            for(int j=0;j<plotting_spaces;j++){
            printf("░");
            }
            //PRINT NUMBER 
            if (x==1){
                printf("%d\n",y->participants);
            }
            else if (x==2){
                printf("%d\n",y->duration);
            }
            else if (x==3){
                printf("%d\n",y->NameFrq);
            }

        for(int i=0;i<(largest_string_len+2);i++){
            printf(" ");
            }
            printf("│");
            
            for(int j=0;j<plotting_spaces;j++){
            printf("░");
            }
            printf("\n");
        
        for(int i=0;i<(largest_string_len+2);i++){
          printf(" ");
          }
        printf("│\n");
        y=y->next;
        limit=limit+1;
    }

    for(int i=0;i<(largest_string_len+2);i++){    
        printf(" ");
    }
    printf("└");
    for(int i=0;i<(80-(largest_string_len+3));i++){
    printf("─");
    }
    printf("\n");
}

// //ERROR PRINTINGS
// 	char error1[]="Invalid options for [-l]";
// 	char error2[]="Invalid option(negative) for [-l]";
// 	char error3[]="usage:";
// 	char error4[]="Not enough options for [-l]";
// 	char error5[]="Cannot plot multiple parameters in same graph.";
// 	char error6[]="Only .csv files should be given as inputs.";
// 	char error7[]="No data to process";
// 	char error8[]="No input files were given";
//   char error9[]="[-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..";
	

    ////////////////////THE END//////////////////////////////////