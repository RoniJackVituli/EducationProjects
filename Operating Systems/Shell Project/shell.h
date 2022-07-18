/* 
To Run the code please compile the file: 
1) gcc shell.c -o shell
2) ./shell 
*/


/* 
Roni Jack Vituli - 315369967.
Matan Ben Yishay - 205577349.
*/

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

typedef enum {PWD = 1, CD, NANO, CAT, WC, CP, PIPE, CLEAR, GREP, WGET, LS, TREE, EXITT, HELP} CMD;
typedef enum {FALSE, TRUE} BOOL;

typedef struct {
    char** strings_cmd;
    int size_cmd;
    char* path;
}parseInfo;

//color
void rest();
void red();
void green();
void yellow();


parseInfo* parse(char* cmd);
void welcomeToShell(void);
void helpMenu(void);
char* inputLine(void);
void executeCommand(parseInfo*);


void yellow(){
    printf("\033[0;33m");

}

void red(){
    printf("\033[1;31m");
}

void rest(){
    printf("\033[0m");
}

void green(){
    printf("\033[0;32m");
}


void welcomeToShell(void){
    green();
    puts("\n\n------------------------Welcome to R-M Shell------------------------------\n"
        "                            Since 2022\n"
        "                             Author:\n"
        "                        ##-Roni Jack Vituli-##\n"
        "                        ##-Matan Ben Yishay-##\n"
        "---------------------------------------------------------------------------\n\n\n");
    rest();
}



void helpMenu(void){
    yellow();
    puts("\n-------------------Help Menu-----------------\n\n"
         "1) pwd: should indicate the current working directory using\n\n"
         "2) cd: cd <path> should change the working directory.\n\n"
         "3) nano: Create a file by the command cat > <filename> or nano <filename>.\n\n"
         "4) cat: cat <filename>.\t\nView the contents of the file.\n\n"
         "5) wc: wc, wc –l, wc –c and wc –w:\n"
         "   wc [options/flags] filename. The wc command should support the following flags wc -l <filename>, wc -c <filename>, wc -w <filename>.\n\n"
         "6) cp: cp <file1> <file2>. Copy the file <file1> to file <file2>\n\n"
         "7) pipe: The shell has to support pipe operator \"|\" between processes (the pipe operator need to be executed only for two commands).\n\n"
         "8) clear: clear should clear the terminal\n"
         "9) grep: grep Return lines with a specific word/string/pattern in a file. grep [options/flags] [Pattern] <filename>.\n\tShould support in the following options(flags): grep -c [pattern] <filename>.\n\n"
         "10) wget: wget The wget command allows you to download files from the Internet using a Linux operating system such as Ubuntu.\n\tUse this command to download either a single Web page or a complete copy of your company's website.\n\tIt also includes an option for downloading any external links included on the site.\n\n"
         "11) ls: Command lists directory contents of files and directories.\n\tls -l show long listing information about the file/directory.\n\n"
         "12) tree: tree print all files.\n\tIt is used to display the contents of any desired directory of your computer system in the form of a tree structure.\n\tBy using this tree structure, you can easily find out the paths of your files and directories.\n\n"
         "13) exit: exit should terminate your shell process.\n\n"
         "----------------------------------------------------------------------------------------------------------------------------\n\n");
         rest();
}

void thankYou(){
    green();
    puts("\n\n------------------------Thank You & Good Bye------------------------------\n"
        "                            Since 2022\n"
        "                             Author:\n"
        "                        ##-Roni Jack Vituli-##\n"
        "                        ##-Matan Ben Yishay-##\n"
        "---------------------------------------------------------------------------\n");
    rest();
}

int whatTheCommand(char* cmd);
void cat_func(parseInfo* info);
BOOL isPipe(parseInfo* info);
void split_the_pipe(parseInfo* info);
void free_parseInfo(parseInfo* info);
void error(parseInfo* info);

