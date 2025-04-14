#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

#include<math.h>
#define MAX_NODES 50
#define INF 1000000


int dist[MAX_NODES];
int visited[MAX_NODES] = {0};

typedef struct GNode {
    int data;           
    int weight;         
    struct GNode* next;
} GNode;

typedef struct LNode { // node of LL containing class stime and place
    int place;
    char* sub;
    int stime;
    int entime;
    struct LNode* next;
} LNode;

typedef struct Graph {
    int numVertices;
    GNode* adjList[MAX_NODES];
} Graph;


LNode* schdule_list[7]; //contains head of all days of week schdule !!!


struct LNode* createNode(int place, int stime, int entime,char* sub);
void insertAtEnd(int day, int place, int stime, int entime,char* sub);
struct LNode* NextClass(int day, int time);
int action(int , LNode*, int );
void printschedule(int day);
 char* IntToChar(int p);
void clearmain(Graph* graph);
void PathTraversing(int* path , int p1 , int p2 , int n);
Graph* createGraph(int vertices);
GNode* newNode(int dest, int weight);
void addEdge(Graph* graph, int src, int dest, int weight);
int minDistance( int n);
int* dijkstra(Graph* graph, int src);
int day(); 
int times(); 


struct LNode* createNode(int place, int stime , int entime,char* sub) {
     LNode* newNode = ( LNode*)malloc(sizeof( LNode));
    newNode->place = place;
    newNode->sub=malloc(strlen(sub)+1);
     
    strcpy(newNode->sub, sub);
    
     newNode->stime=stime;
    newNode->entime=entime;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(int day,int place, int stime, int entime,char* sub) {
      LNode* newNode = createNode(place, stime, entime, sub);
    
      if ( schdule_list[day]== NULL) {
        schdule_list[day] = newNode;
        return;
    }
     LNode* last = schdule_list[day];
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

LNode*  NextClass(int day, int time) { // return the next class's node to extract its timing and place
    LNode* current = schdule_list[day];
    // printf("%d ", current->entime);
    if(current==NULL) return NULL;
    while (current != NULL) {
        if (time<current->stime || time>=current->stime && time< current->entime) 
            return current;
            
        
        current = current->next;
    }
}

int action(int current_time, LNode* NextClass, int p2  ){
    int TravelTime=dist[p2];
    // printf("--%d--", TravelTime);
    if(NextClass==NULL){
        printf("There is no class, Enjoy !! \n");
        return 0;
    }
    printf("Next Class Timing: %d:%d%d \n", NextClass->stime/100,(NextClass->stime%100-NextClass->stime%10)/10,NextClass->stime%10);
    printf("Next Class: %s\n",NextClass->sub);
    printf("Next Class Location: %s\n\n",IntToChar(NextClass->place));
    
    
    int TimeDiff= ((NextClass->stime/100)*60 - (current_time/100)*60) +(NextClass->stime%100 - current_time%100)- TravelTime; // in min
    if(TimeDiff>0){    //early 
        printf("Status: %d min left before you leave for class\n\n", TimeDiff);
    }
    else if(TimeDiff<0 && TimeDiff>-15) {
        printf("Status: %d min late for class. Hurry Up !!\n\n", -TimeDiff);
    }
    else if(TimeDiff=0) printf("Status: Exact time to leave.  Go Go Go !!\n\n");
    else{
        printf("Status: Too Late For Class. It will take %d min to reach even If You Take Shortest Path:\n\n",TravelTime);
        return 1;
    }
    return 1;
}

void printschedule( int day) {   //prints the today's schdule
    // printf("checking -------------------------------");
    LNode* current = schdule_list[day];
    if(current==NULL){
     printf("No Classes Today\n");
     return;
    }
    while (current != NULL) {
        printf("Subject: %s\nClass Timing: %d:%d%d - %d:%d%d\n Class Location: %s \n\n",current->sub,current->stime/100,(current->stime%100-current->stime%10)/10,
        current->stime%10 ,current->entime/100,(current->entime%100-current->entime%10)/10,current->entime%10 ,  
        IntToChar(current->place));

        current = current->next;
    }

}





int day(){ // return  the numeric day of the week (0-6)
    time_t now = time(NULL);

    struct tm *localTime = localtime(&now);

    
    return localTime->tm_wday; 
     
}

int times(){  // return the time in 2400 format  
 time_t now = time(NULL);

 struct tm *localTime = localtime(&now);

 
 return localTime->tm_hour*100+ localTime->tm_min; 
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
     
    graph->numVertices = vertices;
     for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    return graph;
}


GNode* newNode(int dest, int weight) { //create node for graph
    GNode* node = (GNode*)malloc(sizeof(GNode));
    node->data = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}


void addEdge(Graph* graph, int src, int dest, int weight) { //add edge to graph 
     GNode* node = newNode(dest, weight);
     node->next = graph->adjList[src];
    graph->adjList[src] = node;

    node = newNode(src, weight);
    node->next = graph->adjList[dest];
    graph->adjList[dest] = node;
}


int minDistance( int n) { //return index of current min distance node from dist. array
    int min = INF, min_index = -1;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min) {
             min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}


// Dijkstra's algorithm: computes shortest paths from src to all other vertices.
int* dijkstra(Graph* graph, int src) { // it will return array of path to traverse(shortest path)
    int* path=malloc((graph->numVertices)*sizeof(int));
    for(int x=0;x<(graph->numVertices);x++) path[x]=-1;    
     int n = graph->numVertices;
    
     for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;
    
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance( n);
        if (u == -1)  // all nodes visited !!!
        break;
        visited[u] = 1;
        
        
        GNode* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->data;
            if (!visited[v] && dist[u] != INF &&
                dist[u] + temp->weight < dist[v]) {
                    // printf(" (%d,%d) ",u,v);
                    dist[v] = dist[u] + temp->weight;
                    path[v]=u;
                }
            temp = temp->next;
        }
        // printf("\n");
    }

    return path;
    }

void PathTraversing(int* path , int p1 , int p2 , int n){
    if(p1==p2){
        printf("You are on your destination already.\n");
        return;
    }
    int temp=p2;
    int reverse=0;
    for(int x=0;x<n;x++){
        // printf("%d ",path[temp]);
        if(temp==-1 || path[temp]==p1  ) break;
        reverse*=10;
        reverse+=path[temp];
        temp=path[temp];
        // printf("%d-%d ",temp,path[temp]);
    }

    // printf("..%d ", reverse);
    printf("%s ->",IntToChar(p1));
    n=log10(reverse)+1;
    for (int i = 0; i < n; i++)
    {
        printf("%s ->", IntToChar(reverse%10));
        reverse/=10;
    }
    printf("%s ",IntToChar(p2));
    
}

char* IntToChar(int p){
    switch (p) {
    case 1:
        return "PRP ";
        break;

    case 2:
        return "SJT ";
    break;

    case 3:
        return "N-Block ";
        break;

    case 4:
        return "MGR ";
        break;

    case 5:
        return "Anna Audi ";
        break;

    case 6:
        return "TT ";
        break;
    case 7:
        return "Foodys ";
        break;

    case 8:
        return "Centre Library ";
    break;

    case 9:
        return "Girls Hostel ";
        break;
case 10:
        return "Health Care ";
        break;

    case 11:
        return "MGB ";
        break;
    case 12:
        return "VIT Lake ";
        break;
    case 13:
        return "Outside VIT ";
        break;
}
}

void clearmain(Graph* graph){

// Day 1 (Monday)
insertAtEnd(1, 1, 900, 950,"Chemistry");
insertAtEnd(1, 1, 1000, 1050,"Soft Skills");
insertAtEnd(1, 1, 1100, 1150,"DSA");
insertAtEnd(1, 1, 1200, 1250,"Statistics");
insertAtEnd(1, 1, 1400, 1540,"OOPS");

// Day 2 (Tuesday)
insertAtEnd(2, 1, 800, 850,"DSA");
insertAtEnd(2, 1, 900, 950,"Statistics");
insertAtEnd(2, 1, 1000, 1050,"EVS");
insertAtEnd(2, 1, 1100, 1150,"DMGT");
insertAtEnd(2, 1, 1400, 1540,"Chemistry Lab");
insertAtEnd(2, 1, 1551, 1730,"OOPS");

// Day 3 (Wednesday)
insertAtEnd(3, 1, 800 , 850,"DMGT");
insertAtEnd(3, 1, 100, 1050,"Chemistry");
insertAtEnd(3, 2, 1400, 1540,"DSA Lab");

// Day 4 (Thursday)
insertAtEnd(4, 1, 800, 850,"Soft Skills");
insertAtEnd(4, 1, 900, 950,"DSA");
insertAtEnd(4, 1, 1000, 1050,"Statistics");
insertAtEnd(4, 1, 1100,1150,"EVS");
insertAtEnd(4, 1, 1200, 1250,"DMGT");
insertAtEnd(4, 1, 1551, 1730,"OOPS");

// Day 5 (Friday)
insertAtEnd(5, 1, 800, 850,"EVS");
insertAtEnd(5, 1, 900, 950,"DMGT");
 insertAtEnd(5, 1, 1100, 1150,"Chemistry");
 insertAtEnd(5, 1, 1200, 1250,"Soft Skills");


// Node-to-integer mapping:


addEdge(graph, 1, 2, 5);
addEdge(graph, 1, 3, 7);
addEdge(graph, 2, 7, 4);
addEdge(graph, 2, 6, 3);
addEdge(graph, 3, 6, 9);
addEdge(graph, 4, 5, 4);
addEdge(graph, 5, 6, 2);
addEdge(graph, 6, 9, 3);
addEdge(graph, 6, 12, 4);
addEdge(graph, 7, 8, 3);
addEdge(graph, 7, 10, 5);
addEdge(graph, 8, 10, 4);
addEdge(graph, 8, 12, 6);
addEdge(graph, 9, 10, 4);
addEdge(graph, 9, 11, 8);
addEdge(graph, 9, 12, 3);
addEdge(graph, 11, 13, 10);
addEdge(graph, 11, 12, 5);

}

int main(){
    printf("To check Today's Schedule, Press 1 \nAnd To Check Timing To leave for Class, Press 2: ");
    int choice=-1; //
    int p1=-1;
    
    scanf("%d",&choice); ///
    
    if(choice!=1 && choice!=2) {
        printf("Invalid Input");
        return 0;
    }
    
    int waqt= times();
    int din= day();
    int vertices=14; // cause index staring from 1 not zero !
    Graph* graph = createGraph(vertices);
    
    clearmain(graph); 
    
    if(choice==1){
        printf("Today: %s\n\n",(din==0)?"Sunday":(din==1)?"Monday":(din==2)?"Tuesday":(din==3)?"Wednesday":(din==4)?"Thursday":(din==5)?"Friday":(din==6)?"Saturday":"");
        printschedule(din);
    } 
    
    else{
        printf("Tell your location: PRP(1)\t\tSJT(2)\t\tN-Block(3)\t\tMGR(4)\n\t\t    Anna Audi(5)\tTT(6)\t        Foodys(7)\t        Centre Library(8)\n\t\t    Girls Hostel(9)\tHealth Care(10)\tMGB(11)\t                VIT Lake(12)\t     Outside VIT(13)\n");        int p1=1;
        int p2=-1; 
        scanf("%d", &p1);  //
    
     
        if(p1!=1 &&p1!=2 &&p1!=3 &&p1!=4 &&p1!=5 &&p1!=6 &&p1!=7 &&p1!=8 &&p1!=9 &&p1!=10 &&p1!=11 &&p1!=12 &&p1!=13){
            printf("Invalid Input");
        return 0;
        }
    
        LNode* nextclass=NextClass(din, waqt);
        if(nextclass!=NULL) p2=nextclass->place; // for NULL case !!! that is if there is no class they no location to access !!!

    printf("\nPresent time: %d:%d%d \nPresent Day: %s\n\n", waqt/100,(waqt%100-waqt%10)/10,waqt%10, (din==0)?"Sunday":(din==1)?"Monday":(din==2)?"Tuesday":(din==3)?"Wednesday":(din==4)?"Thursday":(din==5)?"Friday":(din==6)?"Saturday":"");
    
    int* path= dijkstra(graph, p1);
    // printschedule(1);
    
    int flag=action( waqt, nextclass, p2); // to check if need to go to class or no class 
    if (flag){
    printf("Shortest Path From %s To %s (%d Minutes): \n",IntToChar(p1),IntToChar(p2),dist[p2]);
    
    PathTraversing(path , p1 , p2  , vertices);
    }
}
    return 0;
}
