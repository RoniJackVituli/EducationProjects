
%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#include "lex.yy.c"

/*----------------Part1-------------*/
typedef struct node
{
    char* token;
    int how_many_childrens;
    int kind_of_type;
    char type;
    struct node **childrens;

}node;

int yyerror();
node* mknode_none(char* token);
node* mknode_one(char* token, node* childrenOne);
node* mknode_two(char* token, node* childrenOne, node* childrenTwo);
node* mknode_three(char* token, node* childrenOne, node* childrenTwo, node* childrenThree);
node* mknode_four(char* token, node* childrenOne, node* childrenTwo, node* childrenThree, node* childrenFour);
node* create_brothers(char* token, node* childrenOne, node* childrenTwo);
node* checkChildren(node* newNode ,node* childrenOne, node* childrenTwo);
node* createNewNode(void);
void timePlane(void);
void printtree(node* root, int tab);
void TABprint(int countTab);


/*-------------Part2-------------*/
typedef struct variable {
    char *name;
    char type;
}variable;

typedef struct function {
    char *name;
    char *paramertes;
    char type;
    int how_many_paramertes;
}function;


typedef struct environment {
    struct environment *aboveEnv;
    struct function **functions;
    struct variable **variables;
    int how_many_function;
    int how_many_vars;
    char return_type;
}environment;

int how_many_main = 0;

environment *create_environment(environment* aboveEnv, char returnType); 
function* create_function(char* name, char type, int num_of_para, char* paramertes);
variable* create_var(char* name, char type);
void put_var_node(environment* env, node *tree, node* Tree);
//void check_var(environment* env, node* root, node* Tree, char type);
char* create_new_p_for_str(char* src); 
char get_type(char* type); 
char containing_P(char* type);
char case_upper(char ch);
int num_of_para(node* root);
void put_para_node(environment* env, node *root, node* Tree); 
char* para_rep(node *tree); 

void tree_is_ok(node* children ,environment* env, node* tree);
void token_CODE(node* children ,environment* env, node* tree);
void token_FUNC(node* children, environment* env, node* tree);
void token_BLOCK(node* children, environment* env, node* tree);
void token_BODY(node* children, environment* env, node* tree);
void token_IF(node* children, environment* env, node* tree);
void token_loop_WHILE(node* children, environment* env, node* tree);
void token_PLACEMENT(node* children ,environment* env, node* tree);
void semantics(node *tree); 
void put_string_node(environment *env, node *root, node* Tree); 
char type_of_var(environment* env, char* name); 
char type_of_func(environment* env, char* name);
char* type_parametrs(char* name, environment* env); 


char check_any_pointer_int(node* childern, environment* env, node* tree);
char check_real_int(node* childern, environment* env, node* tree);
char check_bool_and_or(node* childern, environment* env, node *tree);
char check_bool_eq_neq(node* childern, environment* env, node *tree);
char check_bool_all_G_L(node* childern, environment* env, node *tree);
char check_not(node* childern, environment* env, node *tree);
char check_lengthSTR(node* childern, environment* env, node *tree);
char check_pointer(node* childern, environment* env, node *tree);
char check_address(node* childern, environment* env, node *tree);
char what_the_expr(node* childern, environment* env, node *tree); 


void add_var_to_env(environment* env, variable* var); 
void add_func_to_env(environment* env, function* func);
bool is_pointer(char name);
bool type_of_return(node* children, environment *env, node* tree);
bool check_node_function(node* tree, environment* env);
bool var_already_exsist(environment* env, char* name);
bool func_already_exsist(environment* env, char *name);
bool is_kind_of_type(char* name);
bool is_operation(char* token);
bool var_exsits_in_env(environment *env, char* name);
bool function_exsits_in_env(environment* env, char* name);
bool have_return_type(environment* env);
int func_arg_num(char* name, environment *env);

/*--------Color print-------*/
void red ();
void purple(); 
void reset();
/*------------FUNCTION FREEs---------------*/
void EXIT(node* root, environment* env); 
void symboalTables_free(environment *env); 
void symboalTable_free(environment *env); 
void treeFree(node* root);


/*----------Part3------------*/

typedef struct s_3AC {
    char* var;
    char* code;
}s_3AC;

int T_INDEX = 0;
int L_INDEX = 1;
int CALC_BYTES = 0;

s_3AC* build_3AC(node *tree, node* Tree);
s_3AC* what_the_expr3ac(node *tree);
char* var_num(void);
char* num_of_label(void);
s_3AC* complex_cond(node* tree, char* l1, char* l2);
s_3AC* simple_cond(node* tree, char* l1, char* l2);


/*---I DID----*/
s_3AC* cond3AC(node *tree);
char* createTabs(char* node);
void bytes(char* token);
s_3AC* complex_simple_cond(node* tree, char* label_one ,char* label_two);

s_3AC* token_FUNC_CALL(node* tree);
s_3AC* token_VAR_OR_CONST(node* tree);
s_3AC* token_ADR(node* tree);
s_3AC* token_LENGTH(node* tree);
s_3AC* token_POINTER(node* tree);
s_3AC* token_NOT(node *tree);
s_3AC* token_OPERATION(node *tree);

s_3AC* CODE_3AC(node* tree, node* Tree);
s_3AC* FUNC_3AC(node* tree, node* Tree);
s_3AC* BLOCK_3AC(node* tree, node* Tree);
s_3AC* BODY_3AC(node* tree, node* Tree);
s_3AC* VAR_3AC(node* tree, node* Tree);
s_3AC* STRING_3AC(node* tree, node* Tree);
s_3AC* IF_3AC(node* tree, node* Tree);
s_3AC* IF_ELSE_3AC(node* tree, node* Tree);
s_3AC* WHILE_3AC(node* tree, node* Tree);
s_3AC* DO_WHILE_3AC(node* tree, node* Tree);
s_3AC* FOR_3AC(node* tree, node* Tree);
s_3AC* INIT_3AC(node* tree,node* Tree);
s_3AC* UPDATE_3AC(node* tree, node* Tree);
s_3AC* RET_3AC(node* tree, node* Tree);
s_3AC* EQ_3AC(node* tree, node* Tree);
s_3AC* build_3AC(node *tree, node* Tree);



%}

%union
{
    char *string;
    struct node *node;
}
%token <string> BOOL CHAR CHARP INT INTP REAL REALP STRING 
%token <string> IF ELSE WHILE FOR VAR ENDSTATEMENT RETURN NULLP VOID DO
%token <string> PLUS MINUS DIV MUL PLACEMENT
%token <string> AND EQ G GE L LE NOT NOTEQ OR ADR
%token <string> TRUEE FALSEE TAV DEC HEX EXP STR ID
%token <string> OPE_BRA CLS_BRA OPE_BLOCK CLS_BLOCK OPE_ARRAY CLS_ARRAY PSIK


%type <node> start s 
%type <node> all_function void_function parameters parameter variables ids body body_void definitions
%type <node> val_p func_type var_type 
%type <node> definition definition_var definition_str string_array 
%type <node> body_with_return body_without_return stmt scop stmt_func_no conditions all_loops initialization update call_function senders return
%type <node> ass hasma array string  pointer
%type <node> expr
%type <string> operation

%start  program

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%right LEFT
%left PLACEMENT
%left AND
%left OR
%left EQ NOTEQ
%left G GE L LE
%left PLUS MINUS
%left MUL DIV
%right ADR 


%%
/*---------------------------------------start program--------------------------------------------------------------*/

program: start {  semantics($1); /* printTree($1,0); */  build_3AC($1,$1); treeFree($1);}

start : s {$$ = mknode_one("CODE", $1); } 
      | start s { $$ = create_brothers("CODE",$1, mknode_one("CODE",$2)); }

s : all_function   { $$ = $1;}
  | void_function  { $$ = $1;}
    

/*----------------------------------------Procedure And Functions---------------------------------------------------*/

all_function: func_type ID OPE_BRA parameters CLS_BRA OPE_BLOCK body CLS_BLOCK  {$$ = mknode_four("FUNC",mknode_none($2),$4,mknode_one("RET ",$1),$7);} 


func_type  : BOOL {$$ = mknode_none($1);} //y
           | CHAR {$$ = mknode_none($1);} //y
           | INT  {$$ = mknode_none($1);} //y
           | REAL {$$ = mknode_none($1);} //y
           | INTP {$$ = mknode_none($1);} //y
           | CHARP {$$ = mknode_none($1);} //y
           | REALP {$$ = mknode_none($1);} //y
         

var_type   : BOOL {$$ = mknode_none($1);} //y
           | CHAR {$$ = mknode_none($1);} //y   
           | INT  {$$ = mknode_none($1);} //y 
           | REAL {$$ = mknode_none($1);} //y 
           | INTP {$$ = mknode_none($1);} //y
           | CHARP {$$ = mknode_none($1);} //y 
           | REALP {$$ = mknode_none($1);}//y


void_function:  VOID ID OPE_BRA parameters CLS_BRA OPE_BLOCK body_void CLS_BLOCK    { $$ = mknode_four("FUNC",mknode_none($2),$4,mknode_one("RET ",mknode_none("VOID")),$7);}




parameters : parameter { $$ = $1;}
           | epsilon   {$$ = mknode_one("ARGS",mknode_none("NONE"));}


parameter : variables ENDSTATEMENT parameter { $$ = create_brothers("ARGS",$1,$3); }
          | variables  { $$ = $1;}


variables : BOOL ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | CHAR ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | INT ids  {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | REAL ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | INTP ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | CHARP ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | REALP ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}
          | STRING ids {$2->token = strdup($1); $$ = mknode_one("ARGS",$2);}

ids : ID PSIK ids { $$ = create_brothers("ARGS", mknode_none($1), $3);}
    | ID  { $$ = mknode_one("ARGS",mknode_none($1)); }


body : definitions body_with_return  { $$ = create_brothers("BODY",$1,$2); }
     | body_with_return  { free($1->token); $1->token =strdup("BODY"); $$=$1; }

body_void:
    definitions body_without_return { $$ = create_brothers("BODY",$1,$2); }
    |definitions { free($1->token); $1->token=strdup("BODY"); $$=$1; }
    |body_without_return { free($1->token); $1->token =strdup("BODY"); $$=$1; }
    |epsilon  {$$ = mknode_one("BODY",mknode_none("NONE"));}
    ;

definitions:
    definition definitions {$$ = create_brothers("BODY",mknode_one("BODY",$1),$2);}
    |definition    {$$ = mknode_one("BODY",$1);}
    |all_function definitions { $$ = create_brothers("BODY",mknode_one("BODY",$1),$2);}
    |all_function        {$$ = mknode_one("BODY",$1);}
    |void_function definitions { $$ = create_brothers("BODY",mknode_one("BODY",$1),$2);}
    |void_function     {$$ = mknode_one("BODY",$1);}
    ;

val_p:
    TRUEE  {$$ = mknode_one("bool",mknode_none($1));}
    |FALSEE {$$ = mknode_one("bool",mknode_none($1));}
    |TAV {$$ = mknode_one("char",mknode_none($1));}
    |DEC {$$ = mknode_one("int",mknode_none($1));}
    |HEX {$$ = mknode_one("int",mknode_none($1));}
    |EXP {$$ = mknode_one("real",mknode_none($1));}
    |NULLP {$$ = mknode_one("null",mknode_none("0"));}
    

operation:
    PLUS  { $$ = $1; }
    |MINUS{ $$ = $1; }
    |NOT  { $$ = $1; }
    |MUL { $$ = "POINTER";}
    

/*---------------------------------------Variable Declarations-----------------------------------------------------------*/ 

definition  : VAR var_type definition_var ENDSTATEMENT  {$$ = create_brothers("VAR", mknode_one("VAR",$2), $3);}
            | STRING definition_str ENDSTATEMENT { $$ = $2; }    


definition_var : ID PSIK definition_var  {$$ = create_brothers("VAR", mknode_one("VAR",mknode_none($1)), $3);}
               | hasma PSIK definition_var  {$$ = create_brothers("VAR", mknode_one("PLACEMENT",$1) ,$3);}
               | ID     {$$ = mknode_none($1);}
               | hasma  {$$ = mknode_one("PLACEMENT",$1);}


definition_str:
    string_array PSIK definition_str { $$ = create_brothers("STRING", $1, $3);}
    |string_array { $$ = $1;}
    ;

string_array:
    ID OPE_ARRAY expr CLS_ARRAY { $$ = mknode_one("STRING",mknode_one($1,$3)); }
    |ID OPE_ARRAY expr CLS_ARRAY PLACEMENT STR {$$ = mknode_one("STRING",mknode_two($5,mknode_one($1,$3),mknode_none($6))); }
    ;

/*-------------------------------------------Statments--------------------------------------------------------------------*/

body_with_return : stmt body_with_return { $$ = create_brothers("Statments", mknode_one("stmt",$1),$2);}
                 | return ENDSTATEMENT  {$$ = mknode_one("stmt",$1);}

body_without_return:
    stmt  {$$ = mknode_one("stmt",$1); }
    |stmt body_without_return { $$ = create_brothers("Statments", mknode_one("stmt",$1),$2);}
    ;

stmt:   
    ass ENDSTATEMENT { $$ = $1; }
    |scop  { $$ = $1; }
    |conditions { $$ = $1; }
    |all_loops { $$ = $1; }
    |call_function ENDSTATEMENT{ $$ = $1; }
    |return ENDSTATEMENT { $$ = $1; }
    ;

/*---------------------------------------Assignment----------------------------------------------------------------------*/

ass:
    hasma  { $$ = $1; }
    |array   { $$ = $1; }
    |string  { $$ = $1; }
    |pointer { $$ = $1; }

hasma: ID PLACEMENT expr {$$ = mknode_two($2,mknode_none($1),$3); }
    
array: ID OPE_ARRAY expr CLS_ARRAY PLACEMENT expr{$$ = mknode_two($5,mknode_one($1,$3),$6);}
    
string: ID PLACEMENT STR {$$ = mknode_two($2,mknode_none($1),mknode_none($3));}
    
pointer: MUL ID PLACEMENT expr {$$ = mknode_two($3,mknode_one("POINTER",mknode_none($2)),$4);}
    
/*----------------------------------------Code Block--------------------------------------------------------------------*/

scop : OPE_BLOCK stmt_func_no body_without_return CLS_BLOCK { $$ = create_brothers("BLOCK",$2, $3); }
     | OPE_BLOCK stmt_func_no CLS_BLOCK  { $$ = $2; }
     | OPE_BLOCK body_without_return CLS_BLOCK {free($2->token); $2-> token = strdup("BLOCK"); $$ = $2; }
     | OPE_BLOCK epsilon CLS_BLOCK {$$ = mknode_one("BLOCK",mknode_none("NONE"));}


stmt_func_no:
    definition stmt_func_no {$$ = create_brothers("BLOCK", mknode_one("BLOCK",$1), $2);}
    |definition  {$$ = mknode_one("BLOCK",$1);}
    ;

/*----------------------------------------Conditions--------------------------------------------------------------------*/

conditions  : IF OPE_BRA expr CLS_BRA stmt %prec LOWER_THEN_ELSE {$$ = mknode_two("IF",$3, $5);}
            | IF OPE_BRA expr CLS_BRA stmt ELSE stmt  {$$ = mknode_three("IF-ELSE",$3, $5, $7);}

/*-----------------------------------------loops------------------------------------------------------------------------*/

all_loops : WHILE OPE_BRA expr CLS_BRA stmt   {$$ = mknode_two("WHILE",$3 , $5);} 
          | DO scop WHILE OPE_BRA expr CLS_BRA ENDSTATEMENT  {$$ =  mknode_two("DO-WHILE",$5, $2);}
          | FOR OPE_BRA initialization ENDSTATEMENT expr ENDSTATEMENT update CLS_BRA stmt {free($3->token); $3->token = strdup("INIT"); $$ = mknode_four("FOR",$3,mknode_one("COND",$5),$7, $9);}


initialization : hasma PSIK initialization { $$ = create_brothers("PLACEMENT", mknode_one("PLACEMENT",$1),$3); }
               | hasma {$$ = mknode_one("PLACEMENT",$1); }


update: hasma {$$ = $1;}


/*-----------------------------------------procedure/function calls-----------------------------------------------------*/

call_function : ID OPE_BRA senders CLS_BRA { $$ = create_brothers("FUNC_CALL", mknode_none($1), $3); }

senders : expr PSIK senders   { $$ = create_brothers("paramters",mknode_one("ids",$1), $3);}
        | expr   { $$ = mknode_one("paramters",$1); }
        | STR {}
        | epsilon { $$ = mknode_none("NONE"); }


/*-----------------------------------------Return-----------------------------------------------------------------------*/

return: RETURN expr { $$ = mknode_one("RET",$2); }

/*-----------------------------------------expr--------------------------------------------------------------------*/

expr:
    expr PLUS expr   { $$ = mknode_two($2,$1,$3); }
    |expr MINUS expr  { $$ = mknode_two($2,$1,$3); }
    |expr DIV expr    { $$ = mknode_two($2,$1,$3); }
    |expr MUL expr     { $$ = mknode_two($2,$1,$3); }
    |expr AND expr    { $$ = mknode_two($2,$1,$3); }
    |expr OR expr    { $$ = mknode_two($2,$1,$3); }
    |expr EQ expr     { $$ = mknode_two($2,$1,$3); }
    |expr NOTEQ expr   { $$ = mknode_two($2,$1,$3); }
    |expr G expr      { $$ = mknode_two($2,$1,$3); }
    |expr GE expr    { $$ = mknode_two($2,$1,$3); }
    |expr L expr        { $$ = mknode_two($2,$1,$3); }
    |expr LE expr       { $$ = mknode_two($2,$1,$3); }
    |operation expr %prec LEFT { $$ = mknode_one($1,$2);} 
    |val_p  { $$ = $1; }
    |ID { $$ = mknode_none($1);}
    |call_function { $$ = $1;}
    | '|' ID '|'  { $$ = mknode_one("LENGTH",mknode_none($2)); }
    | OPE_BRA expr CLS_BRA                                    { $$ = $2; }
    | ADR ID { $$ = mknode_one("ADR",mknode_none($2)); }
    | ADR ID OPE_ARRAY expr CLS_ARRAY { $$ = mknode_one("ADR",mknode_one($2,$4));}
    | ID OPE_ARRAY expr CLS_ARRAY  { $$ = mknode_one($1,$3); }


epsilon: 

%%


int main(){
 return yyparse();
}


int yyerror(){
  printf("in line: %d , ERROR %s\n",yylineno, yytext);
  return 0;
}  



node* createNewNode(void){
    node *newnode = (node*)malloc(sizeof(node));
    if(newnode == NULL){
        printf("Error no memory allocated\n");
        exit(1);
    }
    return newnode;
}



node* mknode_none(char* token){
    node* newNode = createNewNode();
    newNode->token = strdup(token);
    newNode->how_many_childrens = 0;
    newNode->childrens = NULL;
    return newNode;
}


node* mknode_one(char* token, node* childrenOne){
    node* newNode = createNewNode();
    newNode->token = strdup(token);
    newNode->how_many_childrens = 1;
    newNode->childrens = (node**)malloc(sizeof(node*) * 1);
    newNode->childrens[0] = childrenOne;
    return newNode;
}

node* mknode_two(char* token, node* childrenOne, node* childrenTwo){
    node* newNode = createNewNode();
    newNode->token = strdup(token);
    newNode->how_many_childrens = 2;
    newNode->childrens = (node**)malloc(sizeof(node*) * 2);
    newNode->childrens[0] = childrenOne;
    newNode->childrens[1] = childrenTwo;
    return newNode;
}


node* mknode_three(char* token, node* childrenOne, node* childrenTwo, node* childrenThree){
    node* newNode = createNewNode();
    newNode->token = strdup(token);
    newNode->how_many_childrens = 3;
    newNode->childrens = (node**)malloc(sizeof(node*) * 3);
    newNode->childrens[0] = childrenOne;
    newNode->childrens[1] = childrenTwo;
    newNode->childrens[2] = childrenThree;
    return newNode;
}


node* mknode_four(char* token, node* childrenOne, node* childrenTwo, node* childrenThree, node* childrenFour){
    node* newNode = createNewNode();
    newNode->token = strdup(token);
    newNode->how_many_childrens = 4;
    newNode->childrens = (node**)malloc(sizeof(node*) * 4);
    newNode->childrens[0] = childrenOne;
    newNode->childrens[1] = childrenTwo;
    newNode->childrens[2] = childrenThree;
    newNode->childrens[3] = childrenFour;
    return newNode;
}




node* checkChildren(node* newNode ,node* childrenOne, node* childrenTwo){
    int j = 0;
    if (childrenOne->how_many_childrens == 0)
        newNode->how_many_childrens += 1;
    if (childrenTwo->how_many_childrens == 0)
        newNode->how_many_childrens += 1;
    newNode->childrens = (node**)malloc(sizeof(node*) * newNode->how_many_childrens);
    if (childrenOne->how_many_childrens == 0) {
        newNode->childrens[j] = childrenOne;
        j++;
    }
    else {
        for (int i = 0; i < childrenOne->how_many_childrens; j++, i++) {
            newNode->childrens[j] = childrenOne->childrens[i];
        }
        free(childrenOne);
    }

    if (childrenTwo->how_many_childrens == 0) {
        newNode->childrens[j] = childrenTwo;
        j++;
    }
    else {
        for (int i = 0; i < childrenTwo->how_many_childrens; i++, j++) {
            newNode->childrens[j] = childrenTwo->childrens[i];
        }
        free(childrenTwo);
    }
    return newNode;
}


void printtree(node* root, int CountTab) {
    if (!root)
        return;
    TABprint(CountTab);
    if (root->how_many_childrens != 0) {
        printf("(");
    }
    printf("%s \n", root->token);

    for (int i = 0; i < root->how_many_childrens; i++) {
        printtree(root->childrens[i], CountTab + 1);
    }

    if (root->how_many_childrens != 0) {
        TABprint(CountTab);
        printf(")\n");
    }
}

void TABprint(int countTab){
    for (int i = countTab; i > 0; i--) {
        printf("    ");
    }
}

node* create_brothers(char* token, node* childrenOne, node* childrenTwo) {
    node* newNode = createNewNode();
    newNode->token = strdup(token);
    newNode->how_many_childrens = childrenOne->how_many_childrens + childrenTwo->how_many_childrens;
    return checkChildren(newNode,childrenOne, childrenTwo);
}


/*-------------------------------END Part1-----------------------------*/



/*------------------------------Part2---------------------------------*/

void red () {
  printf("\033[1;31m");
}
void purple() {
  printf("\033[0;35m");
}
void reset () {
  printf("\033[0m");
}

void semantics(node *tree) { 
    printf("-----CREATE-------\n");
    environment* env = create_environment(NULL, '\0');
    tree_is_ok(tree, env, tree);
    if(how_many_main==0){
        red();
        printf("\n\n#######################Error#######################\n\n");
        purple();
        printf("Oh Ho Main Function Not Found!!!\n ");
        red();
        printf("\n");
        EXIT(tree, env);
    }
}

environment* create_environment(environment* aboveEnv, char return_type){
    environment* newEnvironment = (environment*)malloc(sizeof(environment));
    if(newEnvironment == NULL){
        printf("Error no memory allocated create_environment\n");
        symboalTable_free(aboveEnv);
        exit(1);
    }
    newEnvironment->aboveEnv = aboveEnv;
    newEnvironment->functions = NULL;
    newEnvironment->variables = NULL;
    newEnvironment->return_type = return_type;
    newEnvironment->how_many_function = 0;
    newEnvironment->how_many_vars = 0;
    return newEnvironment;
}

void add_var_to_env(environment* env, variable* var) {
    variable **variables = (variable**)malloc((env->how_many_vars + 1) * sizeof(variable*));
     if(variables == NULL){
        symboalTable_free(env);
        printf("Error no memory allocated add_var_to_env\n");
        exit(1);
    }
    for (int i = 0; i < env->how_many_vars; i++)
        variables[i] = env->variables[i];
    variables[env->how_many_vars] = var;
    free(env->variables);
    env->variables = variables;
    env->how_many_vars += 1;
}

function* create_function(char* name, char type, int num_of_para, char* paramertes) {
    function *newFunction = (function*)malloc(sizeof(function));
    if(newFunction == NULL){
        printf("Error no memory allocated create_function\n");
        exit(1);
    }
    newFunction->name = create_new_p_for_str(name);
    newFunction->type = type;
    newFunction->how_many_paramertes = num_of_para;
    newFunction->paramertes = paramertes;
    return newFunction;
}

void add_func_to_env(environment* env, function* func) {
    function** functions = (function**)malloc((env->how_many_function + 1) * sizeof(function*));
    if(functions == NULL){
        printf("Error no memory allocated add_func_to_env\n");
        exit(1);
    }
    for (int i = 0; i < env->how_many_function; i++) {
        functions[i] = env->functions[i];
    }
    functions[env->how_many_function] = func;
    free(env->functions);
    env->functions = functions;
    env->how_many_function += 1;
}

variable* create_var(char* name, char type) {
    variable* newVar = (variable*)malloc(sizeof(variable));
    newVar->name = create_new_p_for_str(name);
    newVar->type = type;
    return newVar;
}

char* para_rep(node *tree) {
    char* para = (char*)malloc(num_of_para(tree) * sizeof(char));
    int k = 0;
    int i = 0, j = 0;
    if(para == NULL){
        printf("Error no memory allocated para_rep\n");
        exit(1);
    }
    while(i < tree->how_many_childrens){
        j = 0;
        while(j < tree->childrens[i]->how_many_childrens){
            para[k] = get_type(tree->childrens[i]->token);
            k++;
            j++;
        }
        i++;
    }
    return para;
}


void put_var_node(environment* env, node *root, node* Tree) {
    char type = get_type(root->childrens[0]->token); 
    for (int i = 1; i < root->how_many_childrens; i++) {
        if (root->childrens[i]->childrens == NULL) {
            if (var_already_exsist(env, root->childrens[i]->token))
                add_var_to_env(env, create_var(root->childrens[i]->token, type)); 
            else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("The \"%s\" variable is written a number of times, the variable must be given a unique name on the block\n", root->childrens[i]->token);
                red();
                printf("\n");
                EXIT(Tree, env);
            }
        }
        else {
            if (type != what_the_expr(root->childrens[i]->childrens[1], env, root)) {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("incorrect placement on variable \"%s\"\n", root->childrens[i]->childrens[0]->token);
                red();
                printf("\n");
                EXIT(root, env);
            }
            if (var_already_exsist(env, root->childrens[i]->childrens[0]->token))
                add_var_to_env(env, create_var(root->childrens[i]->childrens[0]->token, type));
                else {
                    red();
                    printf("\n\n#######################Error#######################\n\n");
                    purple();
                    printf("The \"%s\" variable is written a number of times, the variable must be given a unique name on the block\n", root->childrens[i]->childrens[0]->token);
                    red();
                    printf("\n");
                    EXIT(Tree, env);
            }

        }
    }
}


bool type_of_return(node* children, environment *env, node* tree) {
    if (have_return_type(env)) {
        if (what_the_expr(children->childrens[0], env, tree) != env->return_type) {
            return false;
        }
    }
    if (env->return_type == 'n') {
        if (env->aboveEnv != NULL)
            return type_of_return(children, env->aboveEnv, tree);
        else
            return false;
    }
    if (env->return_type == '\0') {
        return false;
    }
    return true;
}


bool have_return_type(environment* env){
    return env->return_type == 'I'|| 
    env->return_type == 'R' || env->return_type == 'C' || env->return_type == 'c' || env->return_type == 'r' || env->return_type == 'i' || env->return_type == 'b' || env->return_type == 'S';
}


void put_para_node(environment* env, node* root, node* Tree) {
    int i = 0;
    int j = 0;
    char type;
    while(i < root->how_many_childrens){
        type = get_type(root->childrens[i]->token);
        j = 0;
        while(j < root->childrens[i]->how_many_childrens){
            if (var_already_exsist(env, root->childrens[i]->childrens[j]->token)){
                add_var_to_env(env, create_var(root->childrens[i]->childrens[j]->token, type));
            }else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("The \"%s\" variable is written a number of times, the variable must be given a unique name on the block\n", root->childrens[i]->childrens[j]->token);
                red();
                printf("\n");
                EXIT(root, env);
            }
            j++;
        }
        i++;
    }

}



void put_string_node(environment *env, node* root, node* Tree) {
    int i = 0;
    char type = get_type(root->token);
    while(i < root->how_many_childrens){
        if (strcmp("=", root->childrens[i]->token) == 0) {
            if(root->childrens[i]->childrens[0]->how_many_childrens !=0 && what_the_expr( root->childrens[i]->childrens[0]->childrens[0], env, root) != 'i' ){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable \"%s\" index need to be type of int\n", root->childrens[i]->token);
                red();
                printf("\n");
                EXIT(root, env);
            }
            if (var_already_exsist(env, root->childrens[i]->childrens[0]->token))
                add_var_to_env(env, create_var(root->childrens[i]->childrens[0]->token, type));
            else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("The \"%s\" variable is written a number of times, the variable must be given a unique name on the block\n",  root->childrens[i]->token);
                red();
                printf("\n");
                EXIT(root, env);
            }
        }
        else if(strcmp("=", root->childrens[i]->token) != 0){
            if(root->childrens[i]->how_many_childrens != 0 && what_the_expr(root->childrens[i]->childrens[0], env, root) != 'i' ){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable \"%s\" index need to be type of int\n", root->childrens[i]->token);
                red();
                printf("\n");
                EXIT(root, env);
            } 
            if (var_already_exsist(env, root->childrens[i]->token))
                add_var_to_env(env, create_var(root->childrens[i]->token, type));
            else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("The \"%s\" variable is written a number of times, the variable must be given a unique name on the block\n",  root->childrens[i]->token);
                red();
                printf("\n");
                EXIT(root, env);
            }
        }
        i++;
    }

}


void tree_is_ok(node* children ,environment* env, node* tree) {

    if (children == NULL) {
        return;
    }

    if (strcmp(children->token, "CODE") == 0) {
       token_CODE(children ,env, tree);
    }

    if (strcmp(children->token, "FUNC") == 0) {
        token_FUNC(children ,env, tree);
    }
   
    if (strcmp(children->token, "BLOCK") == 0) {
      token_BLOCK(children ,env, tree);
    }

    if (strcmp(children->token, "BODY") == 0) {
       token_BODY(children ,env, tree);
    }


    if (strcmp(children->token, "VAR") == 0) {
        put_var_node(env, children, tree);
    }

    if (strcmp(children->token, "STRING") == 0) {
        put_string_node(env, children, tree);
    }

    if (strcmp(children->token, "IF")  == 0 || strcmp(children->token, "IF-ELSE") == 0) {
        token_IF(children ,env, tree);
    }

    if (strcmp(children->token, "WHILE") == 0 || strcmp(children->token, "DO-WHILE") == 0) {
        token_loop_WHILE(children ,env, tree);
    }


    if (strcmp(children->token, "FOR") == 0) {
        for (int i = 0; i < children->how_many_childrens; i++)
            tree_is_ok(children->childrens[i], env, tree);
    }
    
 
    if (strcmp(children->token, "INIT") == 0) {
        for (int i = 0; i < children->how_many_childrens; i++) {
            tree_is_ok(children->childrens[i], env, tree);
        }
    }

    if (strcmp(children->token, "COND") == 0) {
        if (what_the_expr(children->childrens[0], env, tree) != 'b') {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("\"for\" expects in condtion to only type of bool\n");
            red();
            printf("\n");
            EXIT(tree, env);
        }
    }  
  
    if (strcmp(children->token, "UPDATE") == 0) {
        for (int i = 0; i < children->how_many_childrens; i++) {
            tree_is_ok(children->childrens[i],env,tree);
        }
    }


    if (strcmp(children->token, "FUNC_CALL") == 0) {
        if (!check_node_function(children, env)) {
            EXIT(tree, env);
        }
    }

    if (strcmp(children->token, "RET") == 0) {
        if (!type_of_return(children, env,tree)) {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("incorrect return type\n");
            red();
            printf("\n");
            EXIT(tree, env);
        }
    }

    if (strcmp(children->token, "=") == 0) {
        token_PLACEMENT(children ,env, tree);
    }
}


void token_CODE(node* children ,environment* env, node* tree){
     for (int i = 0; i < children->how_many_childrens; i++) {
            tree_is_ok(children->childrens[i], env, tree);
        }
}


void token_BLOCK(node* children, environment* env, node* tree){
    environment *newEnv = create_environment(env, 'n');
    for (int i = 0; i < children->how_many_childrens; i++) {
        tree_is_ok(children->childrens[i], newEnv, tree);
    }
    symboalTable_free(newEnv);
}


void token_BODY(node* children, environment* env, node* tree){
    for (int i = 0; i < children->how_many_childrens; i++) {
        tree_is_ok(children->childrens[i], env, tree);
    }
}



void token_loop_WHILE(node* children, environment* env, node* tree){
    if (what_the_expr(children->childrens[0], env, tree) != 'b') {
        
        red();
        printf("\n\n#######################Error#######################\n\n");
        purple();
        printf("\"%s\" expects to only type of bool\n", children->token);
        red();
        printf("\n");
        EXIT(tree, env);

    }
    tree_is_ok(children->childrens[1], env, tree);
}

void token_IF(node* children, environment* env, node* tree){
    if(!strcmp(children->token, "IF")){
        if (what_the_expr(children->childrens[0], env, tree) != 'b') {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("\"%s\" expects to only type of bool\n", children->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }
        tree_is_ok(children->childrens[1], env, tree);
    }else{
        if (what_the_expr(children->childrens[0], env, tree) != 'b') {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("\"%s\" expects to only type of bool\n", children->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }
        tree_is_ok(children->childrens[1], env, tree);
        tree_is_ok(children->childrens[2], env, tree);
    }
}


void token_FUNC(node* children, environment* env, node* tree){

   if (!strcmp(children->childrens[0]->token,"main")) {
       if (!func_already_exsist(env,"main")) {
          red();
          printf("\n\n#######################Error#######################\n\n");
          purple();
          printf("only one main function can be written!!\n");
          red();
          printf("\n");
          EXIT(tree, env);
       }
       else if (strcmp(children->childrens[2]->childrens[0]->token, "VOID")) {
          red();
          printf("\n\n#######################Error#######################\n\n");
          purple();
          printf("the return type of the main function must be VOID\n");
          red();
          printf("\n");
          EXIT(tree, env);
       }
       else if (num_of_para(children->childrens[1]) != 0) {
          red();
          printf("\n\n#######################Error#######################\n\n");
          purple();
          printf("The main function cannot get parameters\n");
          red();
          printf("\n");
          EXIT(tree, env);
        }
        how_many_main += 1;



    }else if (!function_exsits_in_env(env, children->childrens[0]->token)){
        red();
        printf("\n\n#######################Error#######################\n\n");
        purple();
        printf("The \"%s\" function is written a number of times, the function must be given a unique name\n", children->childrens[0]->token);
        red();
        printf("\n");
        EXIT(tree, env);
    }
       
    function* func = create_function(children->childrens[0]->token, get_type(children->childrens[2]->childrens[0]->token), num_of_para(children->childrens[1]), para_rep(children->childrens[1]));
    add_func_to_env(env, func);
        
    environment *newEnv = create_environment(env, get_type(children->childrens[2]->childrens[0]->token));
    put_para_node(newEnv, (children->childrens[1]), tree);
    tree_is_ok(children->childrens[3], newEnv, tree);
    symboalTable_free(newEnv);
}





void token_PLACEMENT(node* children ,environment* env, node* tree){
        if (!strcmp(children->childrens[0]->token, "POINTER")) {
            char type = type_of_var(env, children->childrens[0]->childrens[0]->token);
            if (!var_exsits_in_env(env, children->childrens[0]->childrens[0]->token)) {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("unable to use \"%s\" because it is not yet declared\n", children->childrens[0]->childrens[0]->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }

            if(!is_pointer(type)){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable \"%s\" not a pointer!!! You can not use the operator \"*\"\n", children->childrens[0]->childrens[0]->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }

            if(what_the_expr(children->childrens[1], env, tree) == 'n' && (type_of_var(env, children->childrens[0]->token) == 'C' || type_of_var(env, children->childrens[0]->token) == 'R' || type_of_var(env, children->childrens[0]->token)=='I'))
                return;
            if(type_of_var(env, children->childrens[0]->childrens[0]->token) == 'C' && what_the_expr(children->childrens[1], env, tree) != 'c'){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("incorrect placement on variable \"*%s\"\n", children->childrens[0]->childrens[0]->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }
            if(type_of_var(env, children->childrens[0]->childrens[0]->token) == 'R' && what_the_expr(children->childrens[1], env, tree) != 'r'){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("incorrect placement on variable \"*%s\"\n", children->childrens[0]->childrens[0]->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }
            if(type_of_var(env, children->childrens[0]->childrens[0]->token) == 'I' && what_the_expr(children->childrens[1], env, tree) != 'i'){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("incorrect placement on variable \"*%s\"\n", children->childrens[0]->childrens[0]->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }
            return;
        }


        if (!var_exsits_in_env(env, children->childrens[0]->token)) {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("unable to use \"%s\" because it is not yet declared\n", children->childrens[0]->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }


        if(type_of_var(env, children->childrens[0]->token) != 'S' && what_the_expr(children->childrens[1], env, tree) == 'n' && (type_of_var(env, children->childrens[0]->token)== 'C' || type_of_var(env, children->childrens[0]->token)=='R' || type_of_var(env, children->childrens[0]->token)=='I'))
            return;
        
        

        if(type_of_var(env, children->childrens[0]->token) == 'S'){
            if(children->childrens[1]->how_many_childrens == 0){
                return;
            }
            if(children->childrens[0]->how_many_childrens !=0 && what_the_expr(children->childrens[0]->childrens[0], env, tree) != 'i' ){
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable \"%s\" index need to be type of int\n", children->childrens[0]->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }

            if(children->childrens[0]->how_many_childrens !=0 && what_the_expr(children->childrens[0]->childrens[0], env, tree) == 'i' && what_the_expr(children->childrens[1], env, tree) == 'c')
                return;
        }



        if(type_of_var(env, children->childrens[0]->token) != 'S' && children->childrens[0]->how_many_childrens!= 0){
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("variable \"%s\" can not use operator \"[]\" because the variable is not a string\n", children->childrens[0]->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }



        if (type_of_var(env, children->childrens[0]->token) != what_the_expr(children->childrens[1], env, tree)) {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("incorrect placement on variable \"%s\"\n", children->childrens[0]->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }   
}


bool is_pointer(char name){
    char type = name;
    if(type == 'I' || type == 'R' || type == 'C'){
        return true;
    }
    return false;
}



void symboalTable_free(environment *env){
    int i = 0;
    if(env == NULL ){
        return ;
    }
    while(i < env->how_many_function){
        free(env->functions[i]->name);
        free(env->functions[i]->paramertes);
        free(env->functions[i]);
        i++;
    }
    free(env->functions);
    i = 0;
    while(i < env->how_many_vars){
        free(env->variables[i]->name);
        free(env->variables[i]);
        i++;
    }
    free(env->variables);
    free(env);
}


bool var_already_exsist(environment* env, char* name) {
    int i = 0;
    while(i < env->how_many_vars){
        if (!strcmp(env->variables[i]->name, name)) {
            return false;
        }
        i++;
    }
    return true;
}


void symboalTables_free(environment *env){
    for(environment* temp = NULL ; env != NULL ; env = temp){
        temp = env->aboveEnv;
        symboalTable_free(env);
    }
}

char containing_P(char* type){
    if(strchr(type, '*'))
        return case_upper(type[0]);
    return type[0];
}

char case_upper(char ch){
    return ch - 32;
}

void EXIT(node* root, environment* env) {
    treeFree(root);
    symboalTables_free(env);
    printf("#######################Error#######################\n\n");
    exit(1);
}

char get_type(char* type){
    char ch;
    if(type){
        ch = containing_P(type);
        switch (ch) {
            case 'V':
                return '\0';
                break;
            case 'S':
                return 'S';
                break;
            case 'R':
                return 'R';
                break;
            case 'C':
                return 'C';
                break;
            case 'I':
                return 'I';
                break;
            case 'n':
                return 'n';
                break;
            case 'c':
                return 'c';
                break;
            case 'i':
                return 'i';
                break;
            case 'r':
                return 'r';
                break;
            case 'b':
                return 'b';
                break;
        }
    }
    return '\0';
}



char* create_new_p_for_str(char *src){
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}


int num_of_para(node *tree) {
    int num = 0;
    int i = 0 ;
    while(i < tree->how_many_childrens){
        num += tree->childrens[i]->how_many_childrens;
        i++;
    }
    return num;
}

char check_any_pointer_int(node* childern, environment* env, node* tree){
        char typeLeft = what_the_expr(childern->childrens[0], env, tree); /*left arg*/
        char typeRight = what_the_expr(childern->childrens[1], env, tree); /*right arg */
        if(( typeLeft == 'C' || typeLeft == 'S' || typeLeft == 'R' || typeLeft == 'I')  && typeRight == 'i'){
            return typeLeft;
        }
        if((typeRight == 'C' || typeRight == 'S' || typeRight == 'R' || typeRight == 'I') && typeLeft == 'i'){
            return typeRight;
        }
    return '\0';
}

char check_real_int(node* childern, environment* env, node* tree){
      char typeLeft = what_the_expr(childern->childrens[0], env, tree); /* left node type */
      char typeRight = what_the_expr(childern->childrens[1], env, tree); /* right node type */
      if (typeLeft == 'i' || typeLeft == 'r') {
            if (typeRight == 'i' || typeRight == 'r') {

                 if (typeLeft == 'i' && typeRight == 'i')
                      return 'i';
                  else
                      return 'r';

            }else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("invalid mathematical \"%s\", can only be performed on int and real types\n", childern->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }

        }else {

            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("invalid mathematical \"%s\", can only be performed on int and real types\n", childern->token);
            red();
            printf("\n");
            EXIT(tree, env);
      }
    return '\0';
}


char check_bool_and_or(node* childern, environment* env, node *tree){
        char typeLeft = what_the_expr(childern->childrens[0], env, tree); /* first node type */
        char typeRight = what_the_expr(childern->childrens[1], env, tree); /* second node type */
        if (typeLeft != 'b' || typeRight != 'b') {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("two different types in a Boolean test %s\n", childern->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }
        return 'b';
}


char check_bool_eq_neq(node* childern, environment* env, node *tree){
    char typeLeft = what_the_expr(childern->childrens[0], env, tree);
    char typeRight = what_the_expr(childern->childrens[1], env, tree);
    if (typeLeft == typeRight && (typeRight == 'I' || typeRight == 'R' || typeRight == 'C' || typeRight == 'r' || typeRight == 'c' || typeRight == 'i' || typeRight == 'b')) {
        return 'b';
    }else {
        red();
        printf("\n\n#######################Error#######################\n\n");
        purple();
        printf("two different types in a Boolean test %s\n", childern->token);
        red();
        printf("\n");
        EXIT(tree, env);
   }
   return '\0';
}

char check_bool_all_G_L(node* childern, environment* env, node *tree){
        char typeLeft = what_the_expr(childern->childrens[0], env, tree); /* first node type */
        char typeRight = what_the_expr(childern->childrens[1], env, tree); /* second node type */
        if (typeLeft == 'i' || typeLeft == 'r') {
            if (typeRight  == 'i' || typeRight == 'r' ) {
                return 'b';
            }else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("two different types in a Boolean test %s\n", childern->token);
                red();
                printf("\n");
                EXIT(tree, env);
            }
        }
        else {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("two different types in a Boolean test %s\n", childern->token);
            red();
            printf("\n");
            EXIT(tree, env);
        }
    return '\0';
}


char check_not(node* childern, environment* env, node *tree){
        char typeLeft = what_the_expr(childern->childrens[0], env, tree); /* first node type */
        if (typeLeft != 'b') {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("Illegal action with operator \"!\"\n");
            red();
            printf("\n");
            EXIT(tree, env);
        }
        return 'b';
}

char check_lengthSTR(node* childern, environment* env, node *tree){
        if (type_of_var(env, childern->childrens[0]->token) != 'S') {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("Illegal action with operator \"| |\"\n");
            red();
            printf("\n");
            EXIT(tree, env);
        }
        return 'i';
}

char check_pointer(node* childern, environment* env, node *tree){
    char typeLeft = what_the_expr(childern->childrens[0], env, tree); /* first node type */
        if (typeLeft=='C')
            return 'c';
        if(typeLeft=='R')
            return 'r';    
        if(typeLeft=='I'){
            return 'i';
        }else {
            printf("!!!!!ERROR!!!!! -> Illegal action %s\n", childern->token);
            EXIT(tree, env);
    }
    return '\0';
}

char check_address(node* childern, environment* env, node *tree){
        char typeLeft = what_the_expr(childern->childrens[0], env, tree); /* first node type */

        if (typeLeft == 'c' ) {
            return 'C';
        }
        else if (typeLeft == 'i') {
 
            return 'I';
        }

        else if (typeLeft == 'r') {
         
            return 'R';
        
        }else {
            red();
            printf("\n\n#######################Error#######################\n\n");
            purple();
            printf("Illegal action with operator \"&\"\n");
            red();
            printf("\n");
            EXIT(tree, env);
        }
    return '\0';
}


char what_the_expr(node* childern, environment* env, node *tree) {
    if(strcmp("+", childern->token)  == 0|| strcmp("-", childern->token) == 0){
        if(check_any_pointer_int(childern,env,tree) != '\0')
            return check_any_pointer_int(childern,env,tree);
    }
    if (strcmp("+", childern->token) == 0 || strcmp("-", childern->token) == 0 || strcmp("*", childern->token) ==0 || strcmp("/", childern->token) ==0 ) {
        return check_real_int(childern,env,tree);
    }
    if (strcmp("&&", childern->token)==0 || strcmp("||", childern->token)==0) {
        return check_bool_and_or(childern,env,tree);
    }
    if (strcmp("==", childern->token)==0 || strcmp("!=", childern->token)==0) {
  
        return check_bool_eq_neq(childern,env,tree);
    }
    if (strcmp(">", childern->token)==0 || strcmp(">=", childern->token) ==0|| strcmp("<", childern->token) ==0 || strcmp("<=", childern->token)==0) {
        return check_bool_all_G_L(childern,env,tree);
    }

    if (strcmp("!", childern->token)==0) {
        return check_not(childern,env,tree);
    }

    if (strcmp("LENGTH", childern->token)==0) {
        return check_lengthSTR(childern,env,tree);
    }

    
    if (strcmp("POINTER", childern->token)==0) {
        return check_pointer(childern,env,tree);
    }

    if (strcmp("ADR", childern->token)==0) {
        return check_address(childern,env,tree);

    }

    
    if (strcmp("FUNC_CALL", childern->token)==0) {
        if (!check_node_function(childern, env)) {
            EXIT(tree, env);
        }
        return type_of_func(env, childern->childrens[0]->token);
    
    }else {
        if ((type_of_var(env, childern->token) == 'I'|| type_of_var(env, childern->token) == 'R' || type_of_var(env, childern->token) == 'C' || type_of_var(env, childern->token) == 'r' 
            || type_of_var(env, childern->token) == 'i' || type_of_var(env, childern->token) == 'c' || type_of_var(env, childern->token) == 'b')  || type_of_var(env, childern->token) == 'n'){
            if(childern->how_many_childrens!=0 && childern->childrens[0] != NULL  && !is_kind_of_type(childern->token)){
                printf("Error: %s has no Index operator\n", childern->token);
                EXIT(tree, env);
            }
            return type_of_var(env, childern->token);


        }else if (type_of_var(env, childern->token) == 'S') {
            if(childern -> how_many_childrens != 0){
                if (what_the_expr(childern->childrens[0], env, tree) != 'i') {
                    printf("Error:  %s Index must be int\n", childern->childrens[0]->token);
                    EXIT(tree, env);
                }
                return 'c';
            }
            return 'S';
        }else {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable \"%s\" does not exist\n", childern->token);
                red();
                printf("\n");
                EXIT(tree, env);
        }
    }
    return '\0';
}


bool check_node_function(node* tree, environment* env) {
    if (function_exsits_in_env(env, tree->childrens[0]->token)) {
        red();
        printf("\n\n#######################Error#######################\n\n");
        purple();
        printf("calling function \"%s\" that does not exist\n", tree->childrens[0]->token);
        red();
        printf("\n");
        return false;
    }
    int args_num = tree->how_many_childrens;
    for(int i=0; i<tree->how_many_childrens; i++){
        if(!strcmp("NONE", tree->childrens[i]->token))
            args_num = args_num - 1;
    }
    if (func_arg_num(tree->childrens[0]->token, env) != args_num - 1) {
        red();
        printf("\n\n#######################Error#######################\n\n");
        purple();
        printf("number of arguments does not match calling function \"%s\" \n", tree->childrens[0]->token);
        red();
        printf("\n");
        return false;
    }

    for(int i=1; i<tree->how_many_childrens;i++){
        if(strcmp("NONE",tree->childrens[i]->token) !=0 ){
            if(is_operation(tree->childrens[i]->token)){
                what_the_expr(tree->childrens[i],env,tree);
            }
            
            else if(!var_exsits_in_env(env, tree->childrens[i]->token)) {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable \"%s\" does not exist\n", tree->childrens[i]->token);
                red();
                printf("\n");
                return false;
            }
        }
    }
    char* para = type_parametrs(tree->childrens[0]->token, env);
    for (int i = 1; i < tree->how_many_childrens; i++) {
        if(strcmp("NONE",tree->childrens[i]->token) != 0){
            if(is_operation(tree->childrens[i]->token)){
                if(what_the_expr(tree->childrens[i],env,tree) != para[i-1]){
                    red();
                    printf("\n\n#######################Error#######################\n\n");
                    purple();
                    printf("variable %d does not match expected type\n", i);
                    red();
                    printf("\n");
                    return false;
                }
            }
            else if (type_of_var(env, tree->childrens[i]->token) != para[i-1]) {
                red();
                printf("\n\n#######################Error#######################\n\n");
                purple();
                printf("variable %s does not match expected type\n", tree->childrens[i]->token);
                red();
                printf("\n");
                return false;
            }
        }
    }
    return true;
}



bool function_exsits_in_env(environment* env, char* name) {
    environment *temp = env;
    while (temp != NULL) {
        if (!func_already_exsist(temp, name))
            return false;
        temp = temp->aboveEnv;
    }
    return true;
}

bool func_already_exsist(environment* env, char *name) {
    for (int i = 0; i < env->how_many_function; i++) {
        if (!strcmp(env->functions[i]->name, name)) {
            return false;
        }
    }
    return true;
}


int func_arg_num(char* name, environment *env) {
    environment* temp = env;
    int i = 0;
    while (temp != NULL) {
        i = 0;
        while(i < temp->how_many_function){
            if (!strcmp(name, temp->functions[i]->name)) {
                return temp->functions[i]->how_many_paramertes;
            }
            i++;
        }
        temp = temp->aboveEnv;
    }
    return 0;
}

char* type_parametrs(char* name, environment* env) {
    environment *temp = env;
    int i = 0;
    while (temp != NULL) {
        i = 0;
        while(i < temp->how_many_function){
            if (!strcmp(name, temp->functions[i]->name)) {
                return temp->functions[i]->paramertes;
            }
            i++;
        }
        temp = temp->aboveEnv;
    }
    return NULL;
}

char type_of_func(environment* env, char* name) {
    environment *temp = env;
    int i = 0;
    while (temp != NULL) {
        i = 0;
        while( i < temp->how_many_function){
            if (!strcmp(name, temp->functions[i]->name)) {
                return temp->functions[i]->type;
            }
            i++;
        }
        temp = temp->aboveEnv;
    }
    return '\0';
}

bool var_exsits_in_env(environment *env, char* name) {
    if (is_kind_of_type(name))
        return true;
    environment* temp = env;
    while (temp != NULL) {
        for (int i = 0; i < temp->how_many_vars; i++) {
            if (!strcmp(name, temp->variables[i]->name)) {
                return true;
            }
        }
        temp = temp->aboveEnv;
    }
    return false;
}

char type_of_var(environment* env, char* name) {
    if (is_kind_of_type(name))
        return get_type(name);
    environment* temp = env;
    int i = 0;
    while (temp != NULL) {
        i = 0;
        while(i < temp->how_many_vars){
             if (!strcmp(name, temp->variables[i]->name)) {
                return temp->variables[i]->type;
            }
            i++;
        }
        temp = temp->aboveEnv;
    }
    return '\0';
}

bool is_kind_of_type(char* name){
  if (!strcmp("bool", name))
      return true;
  if(!strcmp("char", name))
      return true;
  if(!strcmp("int", name))
      return true;
  if(!strcmp("real", name))
      return true;
  if(!strcmp("null", name))
        return true;
  if(!strcmp("string",name))
    return true;
  return false;
}

bool is_operation(char* token){
     if(strcmp("+", token)== 0)
             return true;
         if(strcmp("-", token)== 0)
             return true;
          if(strcmp("*", token)== 0)
             return true;
          if(strcmp("/", token)== 0)
             return true;
          if(strcmp("&&", token)== 0)
             return true;
          if(strcmp("||", token)== 0)
             return true;
          if(strcmp("==", token)== 0)
             return true;
          if(strcmp("!=", token)== 0)
             return true;
          if(strcmp(">", token)== 0)
             return true;
          if(strcmp(">=", token)== 0)
             return true;
          if(strcmp("<", token)== 0)
             return true;
          if(strcmp("<=", token) == 0)
             return true;

         return false;
}

void treeFree(node* root) {
    if (root == NULL)
        return;
    int i = 0;
    while(i < root->how_many_childrens){
        treeFree(root->childrens[i]);
        i++;
    }
    if (root->token != NULL)
        free(root->token);
    free(root);
}


/*----------------------------------------------------------Part3--------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------*/
s_3AC* CODE_3AC(node* tree, node* Tree){
    s_3AC* temp;
    int i = 0;
    while(i < tree->how_many_childrens){
        temp = build_3AC(tree->childrens[i], Tree);
        temp->code = createTabs(temp->code);
        red();
        printf("%s", temp->code);
        reset();
        i++;
    }
    return NULL;
}

s_3AC* FUNC_3AC(node* tree, node* Tree){
    s_3AC* temp = build_3AC(tree->childrens[3], Tree);
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    char* str1 = tree->childrens[0]->token;
    char* str2 = temp->code;
    char* begin = "\nBeginFunc\n";
    char* end = "EndFunc\n\n";
    T_INDEX = 0;
    int size = strlen(str1) + strlen(str2) + strlen(begin) + strlen(end) + 1;
    if(node == NULL){ 
        printf("Error memory allocated FUNC 3AC\n");
        treeFree(Tree);
        exit(1);
    }
    node->code = (char*)malloc(sizeof(char)*size);
    if(node == NULL){ 
        printf("Error memory allocated FUNC 3AC\n");
        treeFree(Tree);
        exit(1);
    }
    strcat(node->code,tree->childrens[0]->token);
    strcat(node->code,":");
    strcat(node->code,begin);
    strcat(node->code,temp->code);
    strcat(node->code,end);
    return node;
}


s_3AC* BLOCK_3AC(node* tree, node* Tree){
    s_3AC* temp;
    int i = 0;
    int size = 0;
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated BLOCK 3AC\n");
        treeFree(Tree);
        exit(1);
    }

    if(strcmp(tree->childrens[0]->token,"NONE") == 0){
         node->code = create_new_p_for_str("");
        return node;
    }

    while(i < tree->how_many_childrens){
        temp = build_3AC(tree->childrens[i], Tree);
        if(i == 0){
            size = strlen(temp->code) + 1;
            node->code = (char*)malloc(sizeof(char) * size);
            if( node->code == NULL){ 
                printf("Error memory allocated BLOCK 3AC\n");
                treeFree(Tree);
                exit(1);
            }
        strcpy(node->code ,temp->code);
        }
        else{
            size = strlen(node->code) + strlen(temp->code) + 1;
            node->code = (char*)realloc(node->code, sizeof(char) * size);
            if( node->code == NULL){ 
                printf("Error memory allocated BLOCK 3AC\n");
                treeFree(Tree);
                exit(1);
            }
            strcat(node->code ,temp->code);
        }
        i++;
    }

    return node;
}


s_3AC* BODY_3AC(node* tree, node* Tree){
    s_3AC* temp;
    int i = 0;
    int size = 0;
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated BODY 3AC\n");
        treeFree(Tree);
        exit(1);

    }

    if(strcmp(tree->childrens[0]->token,"NONE") == 0){
        node->code = create_new_p_for_str("");
        return node;
    }

    while(i < tree->how_many_childrens){
        temp = build_3AC(tree->childrens[i], Tree);
        if(i == 0){
            size = strlen(temp->code) + 1;
            node->code = (char*)malloc(sizeof(char) * size);
            if( node->code == NULL){ 
                printf("Error memory allocated BODY 3AC\n");
                treeFree(Tree);
                exit(1);
            }
            strcpy(node->code ,temp->code);
        }
        /* else realloc */
        else{
            size = strlen(node->code) + strlen(temp->code) + 1;
            node->code = (char*)realloc(node->code, sizeof(char) * size);
            if( node->code == NULL){ 
                printf("Error memory allocated BODY 3AC\n");
                treeFree(Tree);
                exit(1);
            }
            strcat(node->code ,temp->code);
        }
        i++;
    }
        return node;
}


s_3AC* VAR_3AC(node* tree, node* Tree){
     s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
     if(node == NULL){ 
            printf("Error memory allocated VAR 3AC\n");
            treeFree(Tree);
            exit(1);
     }
     int size = 0;
     int i = 0;
     bool flag = true;
     while(i < tree->how_many_childrens){
        if (tree->childrens[i]->childrens != NULL) {
                s_3AC* expr_one = what_the_expr3ac(tree->childrens[i]->childrens[1]);
                size = strlen(tree->childrens[i]->childrens[0]->token) + strlen(expr_one->var) + strlen(" = \n") + 1;
                char *code = (char*)malloc(sizeof(char) * size);
                strcpy(code,tree->childrens[i]->childrens[0]->token);
                strcat(code, " = ");
                strcat(code, expr_one->var);
                strcat(code,"\n");
                if(i == 1 || flag){
                    int size2 = strlen(code) + strlen(expr_one->code) + 1;
                    node->code = (char*)malloc(sizeof(char) * size2);
                    strcpy(node->code, expr_one->code);
                    strcat(node->code, code);
                }else{
                    int size3 = strlen(node->code) + strlen(code)  + strlen(expr_one->code) + 1;
                    node->code = (char*)realloc(node->code,sizeof(char) * (size3));
                    strcat(node->code, expr_one->code);
                    strcat(node->code, code);
                }
                flag = false;
            }
            i++;
     }
     if(flag){
        node->code = create_new_p_for_str("");
     }
     return node;
}

s_3AC* STRING_3AC(node* tree, node* Tree){
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
    if(node == NULL){ 
        printf("Error memory allocated STRING 3AC\n");
        treeFree(Tree);
        exit(1);
    }
    bool flag = true;
    int size = 0;
    int size2 = 0;
    int size3 = 0;
    int i = 0;
    while(i < tree->how_many_childrens){
        if (strcmp(tree->childrens[i]->token, "=") == 0){
           char *label = var_num();
           size = strlen(label) + 2;
           char *variable = (char*)malloc(sizeof(char) * size);
           strcpy(variable,"t");
           strcat(variable,label);
           size = strlen(variable) + strlen(tree->childrens[i]->childrens[1]->token) + strlen(" = \n") + 1;
           char* code_one = (char*)malloc(sizeof(char) * size);
           strcpy(code_one,variable);
           strcat(code_one," = ");
           strcat(code_one,tree->childrens[i]->childrens[1]->token);
           strcat(code_one,"\n");

           size = strlen(variable) + strlen(tree->childrens[i]->childrens[0]->token) + strlen(" = \n") + 1;
           char* code_two = (char*)malloc(sizeof(char) * (size));
           strcpy(code_two,tree->childrens[i]->childrens[0]->token);
           strcat(code_two," = ");
           strcat(code_two,variable);
           strcat(code_two,"\n");

           if(i==0 || flag){
               size2 = strlen(code_one) + strlen(code_two) + 1;
               node->code = (char*)malloc(sizeof(char) * (size2));
               strcpy(node->code, code_one);
               strcat(node->code, code_two);
           }else{
               size3 = strlen(node->code) + strlen(code_one) + strlen(code_two) + 1;
               node->code = (char*)realloc(node->code, sizeof(char) * (size3));
               strcat(node->code, code_one);
               strcat(node->code, code_two);
           }
           flag = false;
        }
        i++;
    }
    if(flag){
        node->code = strdup("");
    }
    return node;
}

s_3AC* IF_3AC(node* tree, node* Tree){
    char* label_one = num_of_label();
    s_3AC *expr = build_3AC(tree->childrens[1], Tree);
    char* label_two = num_of_label();
    s_3AC* cond;  
    node* tempTree = tree->childrens[0];
    cond = complex_simple_cond(tempTree,label_one,label_two);
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
    int size = strlen(cond->code) + strlen(":") * 2 + strlen(label_one)  + strlen(expr->code) +  strlen(label_two) + 1;
    node->code = (char*)malloc(sizeof(char) * size);
    strcpy(node->code,"\n");
    strcat(node->code,cond->code);
    strcat(node->code,label_one);
    strcat(node->code,":");
    strcat(node->code,expr->code);
    strcat(node->code,label_two);
    strcat(node->code,":");
    return node;
}

s_3AC* IF_ELSE_3AC(node* tree, node* Tree){
    char* label_one = num_of_label();
    s_3AC *expr_one = build_3AC(tree->childrens[1], Tree);
    int size = 0;
    s_3AC *expr_two = build_3AC(tree->childrens[2], Tree);
    char* label_two = num_of_label();
    s_3AC* cond;
    node* tempTree = tree->childrens[0];
    cond = complex_simple_cond(tempTree,label_one,label_two);
        
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    size = strlen(cond->code) + strlen(":") * 2 + strlen(label_one)  + strlen(expr_one->code) + strlen(expr_two->code) + strlen(label_two) + 1;
    node->code = (char*)malloc(sizeof(char) * size);
    strcpy(node->code,"\n");
    strcat(node->code,cond->code);
    strcat(node->code,label_one);
    strcat(node->code,":");
    strcat(node->code,expr_one->code);
    strcat(node->code,label_two);
    strcat(node->code,":");
    strcat(node->code,expr_two->code);
    return node;
}

s_3AC* WHILE_3AC(node* tree, node* Tree){

    s_3AC *expr_one = build_3AC(tree->childrens[1], Tree);
    s_3AC* cond;
    int size = 0;
    char* label_one = num_of_label();
    char* label_two = num_of_label();
    char* label_three = num_of_label();
    node* tempTree = tree->childrens[0];
    cond = complex_simple_cond(tempTree,label_two,label_three);
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    size = strlen(cond->code) + strlen("    Goto     ") + strlen(label_three) + strlen(expr_one->code) + strlen(label_one) *2 + strlen(label_two) + 1;
    node->code = (char*)malloc(sizeof(char) * size);
    strcpy(node->code,"\n");
    strcat(node->code,label_one);
    strcat(node->code,":");
    strcat(node->code,cond->code);
    strcat(node->code,label_two);
    strcat(node->code,":");
    strcat(node->code,expr_one->code);
    strcat(node->code,"Goto ");
    strcat(node->code,label_one);
    strcat(node->code,"\n");
    strcat(node->code,label_three);
    strcat(node->code,":");
    return node;
}

s_3AC* DO_WHILE_3AC(node* tree, node* Tree){
    s_3AC *expr_one = build_3AC(tree->childrens[1], Tree);
    char* label_one = num_of_label();
    char* label_two = num_of_label();
    char* label_three = num_of_label();
    int size = 0;
    s_3AC* cond;
    node* tempTree = tree->childrens[0];
    cond = complex_simple_cond(tempTree,label_two,label_three);
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    size = strlen(cond->code) + strlen(":goto\n:") + strlen(label_three)  + strlen(expr_one->code)*2 + strlen(label_one) *2 + strlen(label_two) + 1;
    node->code = (char*)malloc(sizeof(char) * size);
    strcpy(node->code,"\n");
    strcat(node->code,expr_one->code);
    strcat(node->code,label_one);
    strcat(node->code,":");
    strcat(node->code,cond->code);
    strcat(node->code,label_two);
    strcat(node->code,":");
    strcat(node->code,expr_one->code);
    strcat(node->code,"goto ");
    strcat(node->code,label_one);
    strcat(node->code,"\n");
    strcat(node->code,label_three);
    strcat(node->code,":");
    return node;
}

s_3AC* FOR_3AC(node* tree, node* Tree){
        int size = 0;
        s_3AC *expr_one = build_3AC(tree->childrens[0], Tree);
        s_3AC *expr_two = build_3AC(tree->childrens[3],Tree);
        s_3AC *expr_three = build_3AC(tree->childrens[2],Tree);
        char* label_one = num_of_label();
        char* label_two = num_of_label();
        char* label_three = num_of_label();
        s_3AC* cond;
        if(tree->childrens[1]->childrens[0]->how_many_childrens!=0 && is_operation(tree->childrens[1]->childrens[0]->childrens[0]->token)){
            cond = complex_cond(tree->childrens[1]->childrens[0], label_two, label_three);
        }
        else{
            cond = simple_cond(tree->childrens[1]->childrens[0], label_two, label_three);
        }
        s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
        size = strlen(cond->code) + strlen("::\t\tgoto \n:") + strlen(label_three)  + strlen(expr_one->code)*2 + strlen(label_one) *2 + strlen(label_two) + 1 + strlen(expr_two->code) + strlen(expr_three->code);
        node->code = (char*)malloc(sizeof(char) * (size));
        if( node->code == NULL){ 
            printf("Error memory allocated FOR_3AC node->code\n");
            exit(1);
        }
        strcpy(node->code, expr_one->code);
        strcat(node->code, label_one);
        strcat(node->code,":");
        strcat(node->code,cond->code);
        strcat(node->code,label_two);
        strcat(node->code,":");
        strcat(node->code,expr_two->code);
        strcat(node->code,expr_three->code);
        strcat(node->code,"goto ");
        strcat(node->code,label_one);
        strcat(node->code,"\n");
        strcat(node->code,label_three);
        strcat(node->code,":");
        return node;

}

s_3AC* INIT_3AC(node* tree,node* Tree){
     s_3AC* expr_one;
     s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));

    if(strcmp(tree->childrens[0]->token,"NONE") == 0){
        node->code = strdup("");
        return node;
    }
    int size = 0 ;
    int i = 0;
    while(i < tree->how_many_childrens){
        expr_one = build_3AC(tree->childrens[i], Tree);
         if(i == 0){
            size = strlen(expr_one->code) + 1;
            node->code = (char*)malloc(sizeof(char) * size);
            strcpy(node->code ,expr_one->code);
        }else{
            size = strlen(node->code) + strlen(expr_one->code) + 1;
            node->code = (char*)realloc(node->code, sizeof(char) * size);
            strcat(node->code ,expr_one->code);
        }
        i++;
    }
    return node;
}

s_3AC* UPDATE_3AC(node* tree, node* Tree){
    s_3AC* expr_one;
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    int size = 0;
    if(tree->how_many_childrens==0){
        node->code = strdup("");
        return node;
    }
    int i = 0;
    while(i < tree->how_many_childrens){
        expr_one = build_3AC(tree->childrens[i], Tree);
        if(i == 0){
            size = strlen(expr_one->code) + 1;
            node->code = (char*)malloc(sizeof(char) * (size));
            strcpy(node->code ,expr_one->code);
        }else{
            size = strlen(node->code) + strlen(expr_one->code) + 1;
            node->code = (char*)realloc(node->code, sizeof(char) * (size));
            strcat(node->code ,expr_one->code);
        }
        i++;
    }
    return node;
}

s_3AC* RET_3AC(node* tree, node* Tree){
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    s_3AC *expr_one = what_the_expr3ac(tree->childrens[0]);
    int size = 0;
    if(tree->childrens[0]->how_many_childrens !=0){
        size = strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        strcpy(node->code, expr_one->code);

        size = strlen("Return \n") + strlen(expr_one->var) + 1;
        char* code =(char*)malloc(sizeof(char) * size);
        strcat(code,"Return ");
        strcat(code,expr_one->var);
        strcat(code,"\n");

        size = strlen(node->code) + strlen(code) + 1;
        node->code = (char*)realloc(node->code, sizeof(char) * size);
        strcat(node->code, code);
        return node;
    }
    size = strlen("Return \n") + strlen(expr_one->var) + 1;
    node->code = (char*)malloc(sizeof(char) * size);
    strcpy(node->code,"Return ");
    strcat(node->code, expr_one->var);
    strcat(node->code, "\n");
    return node;
}

s_3AC* EQ_3AC(node* tree, node* Tree){
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
    int size = 0;
    if(strcmp(tree->childrens[0]->token, "POINTER") == 0){
        s_3AC *expr_one = what_the_expr3ac(tree->childrens[1]);
        size = strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        strcpy(node->code, expr_one->code);

        size = strlen(tree->childrens[0]->childrens[0]->token) + strlen(expr_one->var) + strlen("* = \n") + 1;
        char* code = (char*)malloc(sizeof(char) * (size));
        strcpy(code,"*");
        strcat(code,tree->childrens[0]->childrens[0]->token);
        strcat(code, " = ");
        strcat(code,expr_one->var);
        strcat(code,"\n");

        size = strlen(node->code) + strlen(code) + 1;
        node->code = (char*)realloc(node->code, sizeof(char) * size);
        strcat(node->code, code);
        return node;

    }if(tree->childrens[0]->how_many_childrens !=0){
        s_3AC *expr_one = what_the_expr3ac(tree->childrens[1]);
        char* code_one = NULL;
        char* code_two = NULL;
        char* code_three = NULL;
        char* num = var_num();
        int size = strlen(num) + 1 ;
        char *var = (char*)malloc(sizeof(char)*size);
        char *var2 = (char*)malloc(sizeof(char)*size);
        strcpy(var, "t");
        strcat(var, num);
        num = var_num();
        strcpy(var2, "t");
        strcat(var2, num);
        
        size = strlen(tree->childrens[0]->token) + strlen(var) + strlen(" = &\n") + 1;
        code_one = (char*)malloc(sizeof(char) * (size));
        strcpy(code_one,var);
        strcat(code_one," = &");
        strcat(code_one,tree->childrens[0]->token);
        strcat(code_one,"\n");

        size = strlen(tree->childrens[0]->token) + strlen(var2) + strlen(" =  + \n") + 1;
        code_two = (char*)malloc(sizeof(char) * size);
        strcpy(code_two, var2);
        strcat(code_two," = ");
        strcat(code_two, var);
        strcat(code_two, " + ");
        strcat(code_two,tree->childrens[0]->childrens[0]->childrens[0]->token);
        strcat(code_two,"\n");

        size = strlen(var2) + strlen(expr_one->var) + strlen("* = \n") + 1;
        code_three = (char*)malloc(sizeof(char) * size);
        strcpy(code_three,"*");
        strcat(code_three,var2);
        strcat(code_three, " = ");
        strcat(code_three,expr_one->var);
        strcat(code_three,"\n");

        size = strlen(code_one) + strlen(code_two) + strlen(code_three) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        strcpy(node->code, expr_one->code);
        strcat(node->code, code_one);
        strcat(node->code, code_two);
        strcat(node->code, code_three);
        return node;
   
    }else{
        s_3AC *expr_one = what_the_expr3ac(tree->childrens[1]);


        size = strlen(tree->childrens[0]->token) + strlen(expr_one->var) + strlen(" = \n") + 1;
        char* code = (char*)malloc(sizeof(char) * (size));
        strcpy(code,tree->childrens[0]->token);
        strcat(code," = ");
        strcat(code,expr_one->var);
        strcat(code,"\n");

        size = strlen(code) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(tree->childrens[1]->childrens!=0)
             strcpy(node->code, expr_one->code);

        strcat(node->code, code);
        return node;
    }
}

s_3AC* build_3AC(node *tree, node* Tree) {
 
    if (tree == NULL) 
        return NULL;

    if (strcmp(tree->token, "CODE") == 0) 
        return CODE_3AC(tree,Tree);

    if (strcmp(tree->token, "FUNC") == 0) 
        return FUNC_3AC(tree,Tree);

    if (strcmp(tree->token, "BLOCK") == 0) 
        return BLOCK_3AC(tree,Tree);

    if (strcmp(tree->token, "BODY") == 0) 
        return BODY_3AC(tree, Tree);

    if (strcmp(tree->token, "VAR") == 0) 
       return VAR_3AC(tree,Tree);

    if (strcmp(tree->token, "STRING") == 0) 
        return STRING_3AC(tree,Tree);

    if (strcmp(tree->token, "IF") == 0) 
       return IF_3AC(tree,Tree);

    if (strcmp(tree->token, "IF-ELSE") == 0) 
        return IF_ELSE_3AC(tree,Tree);
    
    if (strcmp(tree->token, "WHILE") == 0)
        return WHILE_3AC(tree,Tree);

    if (strcmp(tree->token, "DO-WHILE") == 0) 
        return DO_WHILE_3AC(tree,Tree);

    if (strcmp(tree->token, "FOR") == 0) 
        return FOR_3AC(tree,Tree);

    if (strcmp(tree->token, "INIT") == 0) 
        return INIT_3AC(tree,Tree); 

    if (strcmp(tree->token, "UPDATE") == 0) 
        return UPDATE_3AC(tree,Tree);

    if (strcmp(tree->token, "FUNC_CALL") == 0) 
        return token_FUNC_CALL(tree);
    
    if (strcmp(tree->token, "RET") == 0)
        return RET_3AC(tree,Tree);

    if (strcmp(tree->token, "=") == 0 )
        return EQ_3AC(tree,Tree);

    return NULL;
}

s_3AC* complex_simple_cond(node* tree, char* label_one ,char* label_two){

    s_3AC* cond;
    if(tree->how_many_childrens!=0 && !is_operation(tree->childrens[0]->token) == 0)
        cond = complex_cond(tree, label_one, label_two);
    else
        cond = simple_cond(tree, label_one, label_two);
    return cond;
}

/*--------------------------------------------------*/





/*--------------------------------------------------*/
s_3AC* simple_cond(node* tree, char* l1, char* l2){
    if(is_kind_of_type(tree->token) || is_operation(tree->token)){
        s_3AC* temp = cond3AC(tree);
        int size = strlen(temp->code) + strlen(l1) + strlen("if  Goto \ngoto \n") + 1;
        char* code = (char*)malloc(sizeof(char) * size);
        strcpy(code,"if ");
        strcat(code, temp->code);
        strcat(code," Goto ");
        strcat(code, l1);
        strcat(code, "\n");
        strcat(code,"goto ");
        strcat(code, l2);
        strcat(code, "\n");
        temp->code = create_new_p_for_str(code);
        return temp;

    }else{
        s_3AC* temp = (s_3AC*)malloc(sizeof(s_3AC));
        int size =  strlen(tree->token) + strlen(l2) + strlen(" = \nif  Goto \n") + 1;
        temp->code = (char*)malloc(sizeof(char) * size);
        strcpy(temp->code,"if ");
        strcat(temp->code,tree->token);
        strcat(temp->code," Goto ");
        strcat(temp->code,l2);
        strcat(temp->code,"\n");
        return temp;
    }
}

s_3AC* complex_cond(node* tree, char* l1, char* l2){
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(strcmp(tree->token, "||") == 0){
        s_3AC* left = complex_cond(tree->childrens[0], l1, l2);
        char* code = create_new_p_for_str("");
        if(left != NULL && tree->childrens[0]->how_many_childrens != 0 
            && strcmp(tree->childrens[0]->token,"&&")  
            && strcmp(tree->childrens[0]->token,"||")){

            int size = strlen(left->code) + strlen(l1) + strlen("if  Goto\n ") + 1;
            code = (char*)malloc(sizeof(char) * size);
            strcpy(code, "if ");
            strcat(code, left->code);
            strcat(code, " Goto ");
            strcat(code,l1);
            strcat(code,"\n");

        }else{

            code = create_new_p_for_str(left->code);
        }

        s_3AC* right = complex_cond(tree->childrens[1], l1, l2);
        char* code_two = create_new_p_for_str("");
        if(right != NULL && tree->childrens[1]->how_many_childrens!= 0 && strcmp(tree->childrens[1]->token,"&&") && strcmp(tree->childrens[1]->token,"||")){
            int size2 = strlen(right->code) + strlen(l2) + strlen("\t\tif  Goto\n ") + 1;
            code_two = (char*)malloc(sizeof(char) * size2);
            strcpy(code_two, "if ");
            strcat(code_two, right->code);
            strcat(code_two, " Goto ");
            strcat(code_two,l1);
            strcat(code_two,"\n");
        }else{
            code_two = create_new_p_for_str(right->code);
        }
        int size = strlen(code) + strlen(code_two) + 1;
        node-> code = (char*)malloc(sizeof(char) * size);
        strcpy(node->code, code);
        strcat(node->code, code_two);
        return node;
    }


    if(strcmp(tree->token, "&&") == 0){
        s_3AC* left = complex_cond(tree->childrens[0], l1, l2);
        char* label = num_of_label();
        char* code = strdup("");
        if( left != NULL && tree->childrens[0]->how_many_childrens!=0
            && strcmp(tree->childrens[0]->token,"&&") 
            && strcmp(tree->childrens[0]->token,"||")){
            int size = strlen(left->code) + strlen(l2) + strlen("%sif  Goto \ngoto  \n") + 1;
            code = (char*)malloc(sizeof(char) * size);
            strcpy(code, "if ");
            strcat(code, left->code);
            strcat(code, " Goto ");
            strcat(code,label);
            strcat(code,"\n");
            strcat(code, "goto ");
            strcat(code,l2);
            strcat(code,"\n");

        }else{
            code = create_new_p_for_str(left->code);
        }


        s_3AC* right = complex_cond(tree->childrens[1], l1, l2);
        char* code_two = create_new_p_for_str("");
        if(right != NULL && tree->childrens[1]->how_many_childrens!=0 
            && strcmp(tree->childrens[1]->token,"&&") 
            && strcmp(tree->childrens[1]->token,"||")){
            int size = strlen(right->code) + strlen(l2) + strlen("%sif  Goto \ngoto  \n") + strlen(label)+ 2 ;
            code_two = (char*)malloc(sizeof(char) * size);
            strcpy(code_two,label);
            strcat(code_two,":");
            strcat(code_two, "if ");
            strcat(code_two, right->code);
            strcat(code_two, " Goto ");
            strcat(code_two,l1);
            strcat(code_two,"\n");
            strcat(code_two, "goto ");
            strcat(code_two,l2);
            strcat(code_two,"\n");

        }else{
            code_two = create_new_p_for_str(right->code);
        }
        int size = strlen(code) + strlen(code_two) + 1;
        node-> code = (char*)malloc(sizeof(char) * size);
        strcpy(node->code, code);
        strcat(node->code, code_two);
        return node;
    }
    return cond3AC(tree);
}
/*--------------------------------------------------*/



/*--------------------------------------------------*/
s_3AC* token_OPERATION(node *tree){
    s_3AC* expr_two = what_the_expr3ac(tree->childrens[1]);
    s_3AC* expr_one = what_the_expr3ac(tree->childrens[0]);
    int size = 0;
    char *label = var_num();
    
    size = strlen(label) + 2;
    char *var = (char*)malloc(sizeof(char) * size);
    if(var == NULL){ 
        printf("Error memory allocated token_OPERATION var\n");
        exit(1);
    }
    size = strlen(label) + strlen(expr_one->var) + strlen(tree->token) + strlen(expr_two->var) + strlen("t = \n") + 1;
    char *code = (char*)malloc(sizeof(char) *size);
    if(code == NULL){ 
        printf("Error memory allocated token_OPERATION code\n");
        exit(1);
    }
    strcpy(var, "t");
    strcat(var, label);
    strcat(code, var);
    strcat(code, " = ");
    strcat(code, expr_one->var);
    strcat(code, tree->token);
    strcat(code, expr_two->var);
    strcat(code, "\n");



    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated token_OPERATION node\n");
        exit(1);
    }
    if(tree->childrens[0]->how_many_childrens!=0 && tree->childrens[1]->how_many_childrens!=0){
        size = strlen(code) + strlen(expr_one->code) + strlen(expr_two->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
         if(node->code == NULL){ 
            printf("Error memory allocated token_OPERATION if->1\n");
            exit(1);
        }
        strcpy(node->code ,expr_two->code);
        strcat(node->code, expr_one->code);
        strcat(node->code, code);
    }if(tree->childrens[0]->how_many_childrens!=0){
        size = strlen(code) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(node->code == NULL){ 
            printf("Error memory allocated token_OPERATION if->2\n");
            exit(1);
        }
        strcpy(node->code, expr_one->code);
        strcat(node->code, code);
    }if(tree->childrens[1]->how_many_childrens!=0){
        size = strlen(code) + strlen(expr_two->code) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(node->code == NULL){ 
            printf("Error memory allocated token_OPERATION if->3\n");
            exit(1);
        }
        strcpy(node->code, expr_two->code);
        strcat(node->code,expr_one->code);
        strcat(node->code, code);
    }else{
        node->code = create_new_p_for_str(code);
    }

    node->var = create_new_p_for_str(var);
    return node;
}

s_3AC* token_NOT(node *tree){
    s_3AC* expr_one = what_the_expr3ac(tree->childrens[0]);
    char *num = var_num();

    int size = strlen(num) + 2;
    char *var = (char*)malloc(sizeof(char) *size);
    if(var == NULL){ 
        printf("Error memory allocated token_NOT var\n");
        exit(1);
    }

    size = strlen(num) + strlen(expr_one->var) + strlen("t = !\n") + 1;
    char *code = (char*)malloc(sizeof(char) * size);
    if(code == NULL){ 
        printf("Error memory allocated token_NOT code\n");
        exit(1);
    }  
    strcpy(var, "t");
    strcat(var, num);
    strcpy(code,"");
    strcat(code, var);
    strcat(code, " = !");
    strcat(code, expr_one->var);
    strcat(code, "\n");
    
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated token_NOT node\n");
        exit(1);
    }
    if(tree->childrens[0]->how_many_childrens!=0){
        size = strlen(code) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(node->code == NULL){ 
            printf("Error memory allocated token_NOT if->1\n");
            exit(1);
        }
        strcpy(node->code ,expr_one->code);
        strcat(node->code, code);
    }else{
        node->code = strdup(code);
    }
    node->var = strdup(var);
    return node;
}

s_3AC* token_POINTER(node* tree){
    s_3AC* expr_one = what_the_expr3ac(tree->childrens[0]);
    char *num = var_num();
    int size = strlen(num) + 2;
    char *var = (char*)malloc(sizeof(char) * size);
    if(var == NULL){ 
        printf("Error memory allocated token_POINTER var\n");
        exit(1);
    }

    size = strlen(num) + strlen(expr_one->var) + strlen("t = *\n") + 1;
    char *code = (char*)malloc(sizeof(char) * size);
    if(code == NULL){ 
        printf("Error memory allocated token_POINTER code\n");
        exit(1);
    }
    strcpy(var, "t");
    strcat(var, num);
    strcpy(code,"");
    strcat(code, var);
    strcat(code, " = *");
    strcat(code, expr_one->var);
    strcat(code, "\n");

    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated token_OPERATION if->1\n");
        exit(1);
    }

    if(tree->childrens[0]->how_many_childrens!=0){
        size = strlen(code) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(node->code == NULL){ 
            printf("Error memory allocated token_OPERATION if->1\n");
            exit(1);
        }
        strcpy(node->code ,expr_one->code);
        strcat(node->code, code);
    }else{
        node->code = strdup(code);
    }
    node->var = strdup(var);
    return node;
}

s_3AC* token_LENGTH(node* tree){
    s_3AC* expr_one = what_the_expr3ac(tree->childrens[0]);
    char* num = var_num();
    
    int size = strlen(num) + 2;
    char* var = (char*)malloc(sizeof(char)*size );
    if(var == NULL){ 
        printf("Error memory allocated token_LENGTH var\n");
        exit(1);
    }

    size = strlen(num) + strlen(expr_one->var) + strlen("t = ||\n") + 1;
    char* code = (char*)malloc(sizeof(char)*size);
    if(code == NULL){ 
        printf("Error memory allocated token_LENGTH code\n");
        exit(1);
    }
    strcpy(var, "t");
    strcat(var, num);
    strcpy(code, var);
    strcat(code, " = |");
    strcat(code, expr_one->var);
    strcat(code, "|");
    strcat(code,"\n");

    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated token_NOT node\n");
        exit(1);
    }
    node->code = create_new_p_for_str(code);
    node->var = create_new_p_for_str(var);
    return node;
}

s_3AC* token_ADR(node* tree){
    s_3AC* expr_one = what_the_expr3ac(tree->childrens[0]);
    char *num = var_num();
    int size = strlen(num) + 2;
    char *var = (char*)malloc(sizeof(char) * size);
    if(var == NULL){ 
        printf("Error memory allocated token_ADR var\n");
        exit(1);
    }
    size = strlen(num) + strlen(expr_one->var) + strlen("t = &\n") + 1;
    char *code = (char*)malloc(sizeof(char) * size);
    if(code == NULL){ 
        printf("Error memory allocated token_ADR code\n");
        exit(1);
    }
    strcpy(var, "t");
    strcat(var, num);
    strcpy(code, var);
    strcat(code, " = &");
    strcat(code, expr_one->var);
    strcat(code, "\n");

    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
    if(node == NULL){ 
        printf("Error memory allocated token_ADR node\n");
        exit(1);
    }

    if(tree->childrens[0]->how_many_childrens!=0){
        size = strlen(code) + strlen(expr_one->code) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(node->code == NULL){ 
            printf("Error memory allocated token_ADR if->1\n");
            exit(1);
        }
        strcpy(node->code ,expr_one->code);
        strcat(node->code, code);
    }else{
        node->code = create_new_p_for_str(code);
    }
    node->var = create_new_p_for_str(var);
    return node;
}

s_3AC* token_FUNC_CALL(node* tree){
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    if(node == NULL){ 
        printf("Error memory allocated token_FUNC_CALL node\n");
        exit(1);
    }
    s_3AC* expr_one;
    int size = 0;
    bool flag = false;
    int i = 1;
    while(i < tree->how_many_childrens ){
        expr_one = what_the_expr3ac(tree->childrens[i]);
        bytes(tree->childrens[i]->token);
        if(tree->childrens[i]->how_many_childrens!=0){
            if(i == 1){
                size = strlen(expr_one->code) + 1;
                node->code = (char*)malloc(sizeof(char) * size);
                if(node->code == NULL){ 
                    printf("Error memory allocated token_FUNC_CALL node->code malloc\n");
                    exit(1);
                }
                strcpy(node->code ,expr_one->code);
                flag = true;
           
            }else{

                size = strlen(node->code) + strlen(expr_one->code) + 1;
                node->code = (char*)realloc(node->code, sizeof(char) * size);
                if(node->code == NULL){ 
                    printf("Error memory allocated token_FUNC_CALL node->code realloc\n");
                    exit(1);
                }
                strcat(node->code ,expr_one->code);
            }
        }
        if(i == 1 && flag == false ){
            size = strlen(expr_one->var) + strlen("PushParam \n") + 1;
            node->code = (char*)malloc(sizeof(char) * size);
            if(node->code == NULL){ 
                printf("Error memory allocated token_FUNC_CALL node->code malloc  if i == 1\n");
                exit(1);
            }
        }else{
            size = strlen(node->code) + strlen(expr_one->var) + strlen("PushParam \n") + 1;
            node->code = (char*)realloc(node->code, sizeof(char) * size);
            if(node->code == NULL){ 
                printf("Error memory allocated token_FUNC_CALL node->code realloc if i == 1\n");
                exit(1);
            }
        }

        strcat(node->code, "PushParam ");
        strcat(node->code, expr_one->var);
        strcat(node->code,"\n");     
        i++;   
    }

    char *num = var_num();
    size = strlen(num) + 2;
    char *var = (char*)malloc(sizeof(char) * size);
    if(var == NULL){ 
        printf("Error memory allocated token_FUNC_CALL var\n");
        exit(1);
    }

    size = strlen(num) + strlen(tree->childrens[0]->token) + strlen("t = LCall \n") + 1;
    char *code = (char*)malloc(sizeof(char) * size);
    if(code == NULL){ 
        printf("Error memory allocated token_FUNC_CALL code\n");
        exit(1);
    }
    strcpy(var, "t");
    strcat(var, num);
    strcpy(code,"");
    strcat(code, var);
    strcat(code, " = ");
    strcat(code, "LCall ");
    strcat(code, tree->childrens[0]->token);
    strcat(code, "\n");
    

    node->var = create_new_p_for_str(var);
    size = strlen(node->code) + strlen(code) + 1;
    node->code = (char*)realloc(node->code, sizeof(char) * size);
    if(node->code == NULL){ 
        printf("Error memory allocated token_FUNC_CALL node->code\n");
        exit(1);
    }
    strcat(node->code ,code);
    free(var);
    free(code);
    size = strlen(num) + strlen(tree->childrens[0]->token) + strlen("PopParams 0\n") + 1;
    code = (char*)malloc(sizeof(char) * size);
    if(code == NULL){ 
        printf("Error memory allocated token_FUNC_CALL code after free\n");
        exit(1);
    }
    char* byte = (char*)malloc(sizeof(char) * 50);
    if(byte == NULL){ 
        printf("Error memory allocated token_FUNC_CALL byte\n");
        exit(1);
    }
    sprintf(byte, "%d", CALC_BYTES);
    strcpy(code,"PopParams ");
    strcat(code, byte); 
    strcat(code, "\n");
    size = strlen(node->code) + strlen(code) + 1;
    node->code = (char*)realloc(node->code, sizeof(char) * size);
    if(node->code == NULL){ 
        printf("Error memory allocated token_FUNC_CALL node->code last\n");
        exit(1);
    }
    strcat(node->code ,code);

    return node;
}

s_3AC* token_VAR_OR_CONST(node* tree){
    char* num;
    char* var;
    char* code;
    int size = 0;
    if(is_kind_of_type(tree->token)){
        num = var_num();
        size = strlen(num) + 2;
        var = (char*)malloc(sizeof(char) * size);
        if(var == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST var if->1\n");
            exit(1);
        }
        strcpy(var, "t");
        strcat(var, num);

        size = strlen(num) + strlen(tree->childrens[0]->token) + strlen("t = \n") + 1;
        code = (char*)malloc(sizeof(char) * size);
        if(code == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST code if->1\n");
            exit(1);
        }
        strcpy(code, var);
        strcat(code, " = ");
        strcat(code, tree->childrens[0]->token);
        strcat(code, "\n");

        s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
        if(node == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST node if->1\n");
            exit(1);
        }
        node->code = create_new_p_for_str(code);
        node->var = create_new_p_for_str(var);
        return node;
    }

    if(tree->how_many_childrens!=0){
        num = var_num();
        size = strlen(num) + 2;
        var = (char*)malloc(sizeof(char) * size);
        if(var == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST var if->2\n");
            exit(1);
        }
        strcpy(var, "t");
        strcat(var, num);

        size = strlen(num) + strlen(tree->token) + strlen("t = &\n") + 1;
        code = (char*)malloc(sizeof(char) * size);
        if(code == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST code if->2\n");
            exit(1);
        }
        strcpy(code, var);
        strcat(code, " = &");
        strcat(code, tree->token);
        strcat(code, "\n");

        char *num2 = var_num();
        size = strlen(num2) + 2;
        char *var2 = (char*)malloc(sizeof(char) * size);
        if(var2 == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST var2 if->2\n");
            exit(1);
        }
        strcpy(var2, "t");
        strcat(var2, num2);

        size = strlen(num2) + strlen(tree->childrens[0]->childrens[0]->token) + strlen(var) + strlen("t = +\n") + 1;
        char *code_two = (char*)malloc(sizeof(char) * size);
        if(code_two == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST code_two if->2\n");
            exit(1);
        }
        strcpy(code_two, var2);
        strcat(code_two, " = ");
        strcat(code_two, var);
        strcat(code_two, "+");
        strcat(code_two, tree->childrens[0]->childrens[0]->token);
        strcat(code_two, "\n");

        s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 2);
        if(node == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST node if->2\n");
            exit(1);
        }
        size = strlen(code) + strlen(code_two) + 1;
        node->code = (char*)malloc(sizeof(char) * size);
        if(node->code == NULL){ 
            printf("Error memory allocated token_VAR_OR_CONST  node->code if->1\n");
            exit(1);
        }
        strcpy(node->code, code);
        strcat(node->code, code_two);
        node->var = create_new_p_for_str(var);
        return node;
    }
    s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
    node->code = create_new_p_for_str(tree->token);
    node->var = create_new_p_for_str(tree->token);


    return node;
}

s_3AC* what_the_expr3ac(node *tree){
   if (strcmp("+", tree->token) == 0 || strcmp("-", tree->token) == 0 || strcmp("*", tree->token)  == 0 || strcmp("/", tree->token) == 0) {
        return token_OPERATION(tree);
    }
    
    if (strcmp("!", tree->token) == 0) 
       return token_NOT(tree);

    if (strcmp("POINTER", tree->token) == 0)
        return token_POINTER(tree);

    if (strcmp("LENGTH", tree->token) == 0) 
        return token_LENGTH(tree);
    
    if (strcmp("ADR", tree->token) == 0) 
        return token_ADR(tree);

    if (strcmp("FUNC_CALL", tree->token) == 0) 
        return token_FUNC_CALL(tree);
       
    else 

        return token_VAR_OR_CONST(tree);
}

/*--------------------------------------------------*/

char* createTabs(char* node){
    char* temp = NULL;
    int sizeOfcode = 0;
    int countEnter = 0;
    for (int i = 0; node[i] != '\0'; i++) {
        sizeOfcode++;
        if(node[i] == '\n')
            countEnter++;
    } 
    int j = 0 ;
    temp = (char*)malloc(sizeof(char)*(sizeOfcode + countEnter*2 + 1));
    temp[j++] = '\t';
    temp[j++] = '\t';

    for(int i = 0; node[i] != '\0'; i++){
        if(node[i] == '\n'){
            if(node[i+1] == 'L'){
                temp[j++] = '\n';
                temp[j++] = '\t';
                int k = i + 1;
                for(; node[k] != ':'; k++){
                    temp[j++] = node[k];
                    if(node[k+1] == ':'){
                        temp[j++] = node[k+1];
                        temp[j++] = '\t';
                    }
                }
                i = k;
            }else{
                temp[j++] = '\n';
                temp[j++] = '\t';
                temp[j++] = '\t';
            }
            continue;
        }
        temp[j++] = node[i];
    }
    return temp;
}

s_3AC* cond3AC(node *tree){
    if (!strcmp("&&", tree->token) || !strcmp("||", tree->token) || !strcmp("==", tree->token) || !strcmp("!=", tree->token)||
    !strcmp(">", tree->token) || !strcmp(">=", tree->token) || !strcmp("<", tree->token) || !strcmp("<=", tree->token)) {

        s_3AC* expr_two = cond3AC(tree->childrens[1]);
        s_3AC* expr_one = cond3AC(tree->childrens[0]);
        char *var = (char*)malloc(sizeof(char) * (4));
        char *code = (char*)malloc(sizeof(char) * (strlen(expr_one->var) + strlen(tree->token) + strlen(expr_two->var) + strlen("t = \n") + 1));
        strcpy(code,"");
        strcat(code, expr_one->code);
        strcat(code, tree->token);
        strcat(code, expr_two->code);
        s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
        if(tree->childrens[0]->how_many_childrens!=0 && tree->childrens[1]->how_many_childrens!=0){
            node->code = (char*)malloc(sizeof(char) * (strlen(code) + strlen(expr_one->code) + strlen(expr_two->code) + 1));
            strcpy(node->code ,expr_two->code);
            strcat(node->code, expr_one->code);
            strcat(node->code, code);
        }
        /* one son is complex has e.code and one is simple */
        else if(tree->childrens[0]->how_many_childrens!=0){
            node->code = (char*)malloc(sizeof(char) * (strlen(code) + strlen(expr_one->code) + 1));
            strcpy(node->code, expr_one->code);
            strcat(node->code, code);
        }
        /* one son is complex has e.code and one is simple */
        else if(tree->childrens[1]->how_many_childrens!=0){
            node->code = (char*)malloc(sizeof(char) * (strlen(code) + strlen(expr_two->code) + 1));
            strcpy(node->code, expr_two->code);
            strcat(node->code, code);
        }
        else{
            node->code = strdup(code);
        }
        node->code = strdup(code);;
        return node;

    }else{
        if(is_kind_of_type(tree->token)){
            char *label = var_num();
            char *var = (char*)malloc(sizeof(char) * (strlen(label) + 2));
            char *code = (char*)malloc(sizeof(char) * (strlen(label) + strlen(tree->childrens[0]->token) + strlen("t = \n") + 1));
            strcpy(code,"");
            strcat(code, tree->childrens[0]->token);

            s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC) * 1);
            node->code = strdup(code);
            node->var = strdup(var);
            return node;
        }
    }
     s_3AC* node = (s_3AC*)malloc(sizeof(s_3AC));
     node->code = strdup(tree->token);
     node->var = strdup(tree->token);
     return node;
}


char* var_num(){
    char *str = (char*)malloc(sizeof(char) * 12 );
    if(str == NULL){ 
        printf("Error memory allocated var_num str\n");
        exit(1);
    }
    sprintf(str, "%d", T_INDEX);
    T_INDEX += 1;
    return str;
}


char* num_of_label(){
    char *str = (char*)malloc(sizeof(char) * 13 );
    if(str == NULL){ 
        printf("Error memory allocated num_of_label str\n");
        exit(1);
    }
    sprintf(str, "L%d", L_INDEX);
    L_INDEX += 1;
    return str;
}


void bytes(char* token){
    if (strcmp("bool", token) == 0)
        CALC_BYTES += 2;
    if(strcmp("char", token) == 0)
        CALC_BYTES += 1;
    if(strcmp("int", token) == 0)
       CALC_BYTES += 4;
    if(strcmp("real", token) == 0)
       CALC_BYTES += 8;
}



