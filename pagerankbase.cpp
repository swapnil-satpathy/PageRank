#include <iostream>
#include <vector>
#include <iterator>
#include <stdlib.h>

#include <cmath>
#include <unordered_map>
using namespace std;

struct pagenode{
    string page;
    double pagerank;
    vector <struct pagenode *> edges;
};

//Adding nodes into the Directed Graph of PageRank
void add_nodes(vector <struct pagenode *> &nodes,string a){
    
    int flag=0;
    for(auto x:nodes){
        if(x->page==a)
            flag=1;
    }
            
    if(flag==0){
    struct pagenode * newnode=new struct pagenode;
    newnode->page=a;
    newnode->pagerank=0.0;
    nodes.push_back(newnode);
    }
    
}

//Function to add edges into the pagerank directed graph
void add_edges(vector <struct pagenode *> &nodes,string a,string b){
    struct pagenode *temp1=NULL;//To find the node which has the string a within it...
    struct pagenode *temp2=NULL;//To find the node which has the string b within it...
    for(auto x:nodes){
        if(x->page==a)
            temp1=x;
        else if(x->page==b)
            temp2=x;
    }
    //If the pages exist
    if(temp1!=NULL && temp2!=NULL)
        temp1->edges.push_back(temp2);
    
    }

//Calculation of PageRank for every node
void pagerank_calculate(vector <struct pagenode *> &nodes){
    int count=0;
    unordered_map<struct pagenode *,double> parallel;
    for(auto x:nodes)//To get the count of the number of nodes in the network
        count++;
    
    double damp=0.85;
    //double threshold=(0.7/100)*(count);//Threshold is choosen according to the accuracy chosen by the application.This calculation used is according to the research paper.It will also reflect the number of iterations required for the pagerank computation to converge...
    double threshold=(0.7/100)*count;
    double constant=(double)(1-damp)/count;
    
    for(auto x:nodes){
        x->pagerank=(double)1/count;
    }
    int condition=1;
    
    while(condition){
        parallel.clear();
    
    for(auto x:nodes){
        long long count2=0;
        for(auto it:x->edges)
        {
            count2++;
        }
        for(auto it:x->edges){
            if(count2!=0){
            parallel[it]+=(double)(x->pagerank)/count2;
            }
            }
    }
        condition=0;
        for(auto x:nodes){
            parallel[x]=constant+damp*parallel[x];
            if(abs(parallel[x]-(x->pagerank))>threshold)
                condition=1;
            x->pagerank=parallel[x];
                
            
        }
        
    }
}
//Sorting Comparator function to sort the pages according to pagerank.....
bool f(struct pagenode *a,struct pagenode *b){
    if(a->pagerank>b->pagerank)
        return true;
    else
        return false;
}


int main(){
    vector <struct pagenode *> nodes;
    
    add_nodes(nodes,"facebook");
    add_nodes(nodes,"microsoft");
    add_nodes(nodes,"google");
    add_nodes(nodes,"wikipedia");
    add_nodes(nodes,"IIIT");
    add_nodes(nodes,"apple");
    
    
    add_edges(nodes,"facebook","microsoft");
    add_edges(nodes,"facebook","google");
    add_edges(nodes,"google","facebook");
    add_edges(nodes,"google","microsoft");
    add_edges(nodes,"microsoft","wikipedia");
    add_edges(nodes,"IIIT","apple");
    add_edges(nodes,"IIIT","wikipedia");
    add_edges(nodes,"apple","wikipedia");
    add_edges(nodes,"wikipedia","apple");
    add_edges(nodes,"wikipedia","IIIT");
    
    
    pagerank_calculate(nodes);
    sort(nodes.begin(),nodes.end(),f);
    
    for(auto i:nodes)
        cout<<i->page<<" "<<(double)(i->pagerank)<<endl;
    cout<<endl;
    
    
    return 0;
}

    
    

    
    






