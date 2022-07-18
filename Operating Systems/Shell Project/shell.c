/* 
To Run the code please compile the file: 
1) gcc shell.c -o shell
2) ./shell 
*/


/* 
Roni Jack Vituli - 315369967.
Matan Ben Yishay - 205577349.
*/

#include "shell.h"
/* --------------------------------------------------------- Declarations ------------------------------------------------------------------------*/
char pwd[256];

int main(){
    welcomeToShell();
    char* cmdLine;
    int childPid; 
    int status = 0; 
    parseInfo* info = NULL;
    
    while(!status){
        printf("\n>>> ");
        cmdLine = inputLine();
        info = parse(cmdLine);
        childPid = fork();
        if(childPid == 0 && strcmp(info->strings_cmd[0],"cd") != 0){ 
            executeCommand(info);

        }else{
            if(childPid == 0)
                exit(EXIT_SUCCESS);
            if(strcmp(info->strings_cmd[0],"cd") == 0)
                executeCommand(info);
            waitpid(childPid,&status,0);
            if(WEXITSTATUS(status) == 5){
                thankYou();
                free_parseInfo(info);
                exit(1);
    
            }
            free_parseInfo(info);
        }
    } 
    return 0;
}


void executeCommand(parseInfo* info){
   if(isPipe(info)){
       split_the_pipe(info);
   }
   switch (whatTheCommand(info->strings_cmd[0])){
   case PWD:
        if(info->size_cmd < 2){
            yellow();
            if(getcwd(pwd,sizeof(pwd)) != NULL)
                printf("%s\n",pwd);
            rest();
            exit(EXIT_SUCCESS);
            return;
        }else{
            error(info);
        }
       break;
   case CD:
        getcwd(pwd,sizeof(pwd));
        if(info->size_cmd == 1){
            chdir(getenv("HOME"));
            getcwd(pwd,sizeof(pwd));
            return;
        }else if (info->size_cmd == 2 && chdir(info->strings_cmd[1]) == 0){
             getcwd(pwd,sizeof(pwd));
             return;
        }else{
            red();
            printf("cd: %s -> no such file or directory\n",info->strings_cmd[1]);
            rest();
        }
        break;
    case CLEAR:
        if(info->size_cmd == 1){
            system("clear");
            exit(EXIT_SUCCESS);
        }
        error(info);
        break;

    case CAT:
        if(info->size_cmd <= 3){
           if(strcmp(info->strings_cmd[1],">") == 0){
               cat_func(info);
               exit(EXIT_SUCCESS);
           }  
           char* args[] = {info->strings_cmd[0],info->strings_cmd[1],NULL,NULL};
           execvp(info->strings_cmd[0],args);
        }else{
            error(info);
        }
        break;
    case LS:
        if(info->size_cmd <= 2){
            if(info->strings_cmd[1] == NULL || (info->strings_cmd[1] != NULL && (!strcmp(info->strings_cmd[1],"-l")))){
                char* args[] = {info->strings_cmd[0],info->strings_cmd[1],NULL,NULL}; 
                execvp(info->strings_cmd[0],args);
            }else if(strcmp(info->strings_cmd[1],"|") == 0){
                info->strings_cmd[1] = NULL;
            }else{
                printf("HERE\n the char = %s\n",info->strings_cmd[1]);
                error(info);
            }
        }else{
            error(info);
        }
        break;
    
    case NANO:
        if(info->size_cmd == 2){
            char* args[] = {info->strings_cmd[0],info->strings_cmd[1],NULL,NULL};
            execvp(info->strings_cmd[0],args);
        }
        error(info);
        break;
    
    case WC:
        if(info->size_cmd <= 3){
            if(info->strings_cmd[1] == NULL || (info->strings_cmd[1] != NULL && (!strcmp(info->strings_cmd[1],"-l") || !strcmp(info->strings_cmd[1],"-w") || !strcmp(info->strings_cmd[1],"-c")))){
                char* args[] = {info->strings_cmd[0],info->strings_cmd[1],info->strings_cmd[2],NULL};
                execvp(info->strings_cmd[0],args); 
            }else{
                error(info);
            }
        }
        break;

    case EXITT:
        if(info->size_cmd == 1)
            exit(5);
        error(info);
        break;
    
    case WGET:
        if(info->size_cmd == 2){
            char* args[] = {info->strings_cmd[0],info->strings_cmd[1],NULL,NULL};
            execvp(info->strings_cmd[0],args); 
        }
        error(info);
        break;
    case CP:
        if(info->size_cmd == 3){
            char* args[] = {info->strings_cmd[0],info->strings_cmd[1],info->strings_cmd[2],NULL};
            execvp(info->strings_cmd[0],args); 
        }
        break;
    case GREP:
        if(info->size_cmd <= 4){
            char* args[] = {info->strings_cmd[0],info->strings_cmd[1],info->strings_cmd[2],info->strings_cmd[3],NULL};
            execvp(info->strings_cmd[0],args); 
        }
    case TREE:
        if(info->size_cmd == 1){
            char* args[] = {info->strings_cmd[0],NULL};
            execvp(info->strings_cmd[0],args); 
        }else{
            error(info);
        }
        break;
    case HELP:
        if(info->size_cmd == 1){
            helpMenu();
            exit(EXIT_SUCCESS);
        }
        error(info);
   default:
        error(info);
       exit(EXIT_FAILURE);
       break;
   }
}




// Create new file with "cat > <filename>". 
void cat_func(parseInfo* info){
    FILE* fptr;
    getcwd(pwd,sizeof(pwd));
    strcat(pwd,"/");
    strcat(pwd,info->strings_cmd[2]);
    fptr = fopen(pwd,"w+");
    if(fptr == NULL){
        printf("Can't open the file!\n");
        exit(EXIT_FAILURE);
    }
    char* temp;
    
    yellow();
    printf("write now to your new file: ");
    red();
    printf("%s\n",info->strings_cmd[2]);
    yellow();
    printf("STOP WRITE PRESS CTL-D\n");
    rest();
    while(TRUE){
        char c = getchar();
        if(c == EOF){
            fclose(fptr);
            exit(EXIT_SUCCESS);
        }
        fputc(c,fptr);
    }
}





int whatTheCommand(char* cmd){
    if(strcmp(cmd,"pwd") == 0){
        return PWD;
    }else if(strcmp(cmd,"cd") == 0){
        return CD;
    }else if(strcmp(cmd,"nano") == 0){
        return NANO;
    }else if(strcmp(cmd,"cat") == 0){
        return CAT;
    }else if(strcmp(cmd,"wc") == 0){
        return WC;
    }else if(strcmp(cmd,"cp") == 0 ){
        return CP;
    }else if(strcmp(cmd,"pipe") == 0 ){
        return PIPE;
    }else if(strcmp(cmd,"clear") == 0 ){
        return CLEAR;
    }else if(strcmp(cmd,"grep") == 0 ){
        return GREP;
    }else if(strcmp(cmd,"wget") == 0 ){
        return WGET;
    }else if(strcmp(cmd,"ls") == 0 ){
        return LS;
    }else if(strcmp(cmd,"tree") == 0 ){
        return TREE;
    }else if(strcmp(cmd,"exit") == 0 ){
        return EXITT;
    }else if(strcmp(cmd,"help") == 0){
        return HELP;
    }
    return -1;
}


parseInfo* parse(char* cmd){
    char* temp_split = strtok(cmd," ");
    int i = 0;
    char** strings = malloc(sizeof(char*));
    if(strings == NULL){
        printf("no memory allocated strings parse()\n");
        exit(1);
    }
    while(temp_split != NULL){
        strings[i++] = strdup(temp_split);
        strings = realloc(strings, (i+1) * sizeof(char*));
        if(strings == NULL){
            printf("no memory allocated strings (while) parse()\n");
            exit(1);
        }   
        temp_split = strtok(NULL," ");
    }
    strings[i] = NULL;
    parseInfo* info = (parseInfo*)malloc(sizeof(parseInfo));
    if(info == NULL){
        printf("no memory allocated info parse()\n");
        exit(1);
    }
    info->strings_cmd = strings;
    info->size_cmd = i;
    free(cmd);
    return info;
}


// this function input a string and return the input to who is call.
char* inputLine(void){
    char* temp = (char*)malloc(sizeof(char) + 1);
    int ascii_char;
    int i = 0;
    while ((ascii_char = getchar()) != '\n' && ascii_char != EOF) {
        temp[i++] = ascii_char;
        temp = realloc(temp, i+1);
        if(temp == NULL){
            printf("!!!!!!!ERROR!!!!!! -> no memory allocated in InputLine()\n");
            exit(1);
        }
    }
    temp[i] = '\0';
    return temp;
}


// Check if in the string  have the char "|".
BOOL isPipe(parseInfo* info){
    for(int i = 0; info->strings_cmd[i] != NULL; i++){
        if(strcmp(info->strings_cmd[i],"|") == 0)
            return TRUE;
    }
    return FALSE;
}

//this function 
void split_the_pipe(parseInfo* info){
    parseInfo* oneCmd = (parseInfo*)malloc(sizeof(parseInfo));
    char** strOne = (char**)malloc(sizeof(char*));
    parseInfo* secCmd = (parseInfo*)malloc(sizeof(parseInfo));
    char** strTwo = (char**)malloc(sizeof(char*));
    int i = 0, j = 0;

    while(strcmp(info->strings_cmd[i],"|") != 0){
        strOne[i++] = strdup(info->strings_cmd[i]);
        strOne = realloc(strOne,sizeof(char*) * (i + 1 ));
    }
    info->size_cmd = i;
    strOne[i++] = NULL;
    oneCmd->strings_cmd = strOne;
    while(info->strings_cmd[i] != NULL){
        strTwo[j++] = strdup(info->strings_cmd[i++]);
        strTwo = realloc(strTwo,sizeof(char*) * (j + 1 ));
    }
    strTwo[j] = NULL;
    secCmd->strings_cmd = strTwo;
    secCmd->size_cmd = j;
    
    int fds[2];
    if(pipe(fds) == -1){
        perror("Pipe faild");
        exit(EXIT_FAILURE);
    }

    if(fork() == 0){
        close(STDOUT_FILENO);
        dup(fds[1]);
        close(fds[0]);
        close(fds[1]);
        executeCommand(oneCmd);
    }

    if(fork() == 0){
        close(STDIN_FILENO);
        dup(fds[0]);
        close(fds[1]);
        close(fds[0]);
        executeCommand(secCmd);
    }

    close(fds[0]);
    close(fds[1]);
}


void free_parseInfo(parseInfo* info){
    for(int i = 0; i < info->size_cmd; i++){
        free(info->strings_cmd[i]);
    }
    free(info);
}


void error(parseInfo* info){
    red();
    printf("%s: invaild arguments ",info->strings_cmd[0]);
    for(int i = 1; i < info->size_cmd ; i++)
        printf("%s ",info->strings_cmd[i]);
    yellow();
    printf("\nTo see what commands shell supprot press help!\n");
    rest();
    exit(EXIT_FAILURE);
}