#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char name[30];
    int ID;
    float money;
    struct node *right, *left;
};


struct node* new_node(int userID, char name[], float money)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->ID = userID;
    strcpy(p->name,name);
    p->money=money;
    p->left = NULL;
    p->right = NULL;

    return p;
}



struct node* insert(struct node *root, int userID, char name[], float money)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(userID, name, money);
    else if(userID>root->ID) // x is greater. Should be inserted to right
        root->right = insert(root->right, userID, name, money);
    else // x is smaller should be inserted to left
        root->left = insert(root->left, userID, name, money);
    return root;
}


void preorder1(struct node *root)
{
    if(root!=NULL)
    {
        printf("%s %d %f\n", root->name, root->ID, root->money);
        preorder1(root->left);
        preorder1(root->right);
    }
}


struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL) 
        return find_minimum(root->left); 
    return root;
}

struct node* remove_node(struct node *root, int userID)
{
    if(root==NULL)
        return NULL;
    if (root->ID<userID)
        root->right = remove_node(root->right, userID);
    else if(root->ID>userID)
        root->left = remove_node(root->left, userID);
    else
    {
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }

        else if(root->left==NULL || root->right==NULL)
        {
            struct node *temp;
            if(root->left==NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }

        else
        {
            struct node *temp = find_minimum(root->right);
            root->ID = temp->ID;
            root->right = remove_node(root->right, temp->ID);
        }
    }
    return root;
}


struct node* search(struct node *root, int userID)
{
    if(root==NULL || (root->ID==userID)) 
        return root;
    else if(root->ID<userID) 
        return search(root->right, userID);
    else 
        return search(root->left, userID);
}

void add(struct node *root, int userID, char name[], float money){
    struct node *temp;
    temp=search(root,userID);
    if(temp==NULL){
        insert(root,userID,name,money);
    }
    else{
        printf("User with ID %04d already exists\n",userID);
    }
}

void delete(struct node *root, int userID){
    struct node *temp;
    temp=search(root,userID);
    if(temp==NULL){
        printf("User you are trying to delete doesn't exist\n");
    }
    else{
        remove_node(root,userID);
    }
}


void printProcessToTheScreen(struct node *root, int userID, float money){
    struct node *temp;
    temp = search(root,userID);
    float balance = temp->money;
    if(balance>money){
        printf("Customer %04d, %s, payed $%.2f from their store balance and $0 at the register, $%.2f remaining store balance\n",userID,temp->name,money,balance-money);
        temp->money=temp->money-money;
    }
    else{
      printf("Customer %04d, %s, payed $%.2f from their store balance and $%.2f at the register, $0 remaining store balance\n",userID,temp->name,balance,money-balance);
      temp->money=0;  
    }

}


void process(struct node *root, char filename[]){
    FILE *sp;
    int x=0, y=0, userID;
    char filename1[100]="C:\\Users\\athar\\OneDrive\\Documents\\CS 2413\\Project 2\\",line1[40],line[40];
    char *p;
    float money;
    strcat(filename1,filename);
    sp=fopen(filename1,"r");
    while(!feof(sp)){
        fgets(line1,40,sp);

        for(x=0;x<strlen(line1);x++){
            if(line1[x]!='{' && line1[x]!='}' &&line1[x]!=' '){
                line[y]=line1[x];
                y++;
            }
        }

        p=strtok(line,",");
        userID=atoi(p);
        p=strtok(NULL,",");
        money=atof(p);

        printProcessToTheScreen(root,userID,money);
        y=0;


    }
    fclose(sp);
    //printf("yup");
}


void inorder(struct node *root, FILE *dp)
{
    if(root!=NULL)
    {
        inorder(root->left,dp);
        fprintf(dp,"{%04d, \"%s\", %.2f}\n",root->ID, root->name, root->money);
        inorder(root->right,dp);
    }
}

void preorder(struct node *root, FILE *dp)
{
    if(root!=NULL)
    {
        fprintf(dp,"{%04d, \"%s\", %.2f}\n",root->ID, root->name, root->money);
        preorder(root->left,dp);
        preorder(root->right,dp);
    }
}

void postorder(struct node *root, FILE *dp)
{
    if(root!=NULL)
    {
        postorder(root->left,dp);
        postorder(root->right,dp);
        fprintf(dp,"{%04d, \"%s\", %.2f}\n",root->ID, root->name, root->money);
    }
}


void quit(struct node *root){
    FILE *dp;
    char filename1[100]="C:\\Users\\athar\\OneDrive\\Documents\\CS 2413\\Project 2\\";
    char filename[20]="newcustomers.txt";
    char inp[10];
    strcat(filename1,filename);
    dp=fopen(filename1,"w+");
    printf(" Please enter output format: pre, post, or in order\n");
    scanf("%s",inp);
    if(strcmp(inp,"in")==0){
        inorder(root,dp);

    }
    else if(strcmp(inp,"pre")==0){
        preorder(root,dp);
    }
    else if(strcmp(inp,"post")==0){
        postorder(root,dp);
    }
    else{
        printf("error");
    }
    fclose(dp);
}


int main(){
    FILE *fp;
    char tempData1[20][70],tempID[20][7],tempData[20][70],*p,tempName[20][30],user_inp[30];
    int idNo[20],esc;
    float money[20];
    int x=0,y=0,z=0,userAmt=0;
    struct node *root;
    fp=fopen("C:\\Users\\athar\\OneDrive\\Documents\\CS 2413\\Project 2\\customers.txt","r");
    if(fp==NULL){
        printf("Required file doesn't exist");
    }


    while(!feof(fp)){ //To get each line from file
        //printf("gei");    //Ignore this
        fgets(tempData1[x],70,fp);  //get each line from file and put into a string
        ++x,++userAmt;    //Increment counter and net users
    }
    
    for(x=0;x<userAmt;x++){
        for(y=0;y<strlen(tempData1[x]);y++){
            if(tempData1[x][y]!='{' && tempData1[x][y]!='}' && tempData1[x][y]!=' ' && tempData1[x][y]!='\"'){ //Check whether charater is
                tempData[x][z]=tempData1[x][y];            //desirable or not and then add to new string
                z++;                                       //increment new string counter
            }
        }
        z=0;
    }

    for(x=0;x<userAmt;x++){
        p=strtok(tempData[x], ",");                //Split string
        idNo[x]=atoi(p);                           //put first part into ID
        p=strtok(NULL, ",");                       //split string
        strcpy(tempName[x],p);                     //put second part into name
        p=strtok(NULL, ",");                       //Split string
        money[x]=atof(p);                          //put third part into money

    }

    root = new_node(idNo[0], tempName[0], money[0]);

    for(z=1;z<userAmt;z++){
      insert(root, idNo[z], tempName[z], money[z]);
    }


    //preorder1(root);
    //remove_node(root,112);
    //process(root,"orders.txt");
    //quit(root);

    while(esc==0){
        printf("1. Add a customer to the system <add num name balance>\n");
        printf("2. Remove a customer from the system <delete num>\n");
        printf("3. Process a list of orders for customers in our system<process filename>\n");
        printf("4. Close down the system <quit>\n");
        gets(user_inp);
        char garb[10],name[30],filename[30],*rand;
        int num;
        float bal;

        if(user_inp[0]=='a'){
            rand=strtok(user_inp," ");
            strcpy(garb,rand);
            rand=strtok(NULL," ");
            num=atoi(rand);
            rand=strtok(NULL," ");
            strcpy(name,rand);
            rand=strtok(NULL," ");
            bal=atof(rand);
            add(root,num,name,bal);

        }
        else if(user_inp[0]=='d'){
            rand=strtok(user_inp," ");
            strcpy(garb,rand);
            rand=strtok(NULL," ");
            num=atoi(rand);
            delete(root,num);
            
        }
        else if(user_inp[0]=='p'){
            rand=strtok(user_inp," ");
            strcpy(garb,rand);
            rand=strtok(NULL," ");
            strcpy(filename,rand);
            process(root,filename);
            
        }
        else if(user_inp[0]=='q'){
            quit(root);
            esc=1;
            
        }

    }

    fclose(fp);
    return 0;
}