#include <bits/stdc++.h>
using namespace std;

int d, t, index_nodes=0, data_nodes=1;
const int infinity= 1e9;

class node
{
    public:
    bool isleaf; //data node or index node
    set<pair<int, node*>> keys; //pointer to the left of the key
    node* parent;
    node(bool leaf=true , node* par=NULL )
    {
        isleaf=leaf;
        parent=par;
        if(isleaf) keys.insert({infinity, NULL});
    }
    int return_size() {return keys.size()-1;} // because one will always be infinity

};
node* root= new node;
node* search (int x, node* n)
{
    if(n->isleaf==true) return n;
    for(auto contents : n->keys)
        if(x<contents.first)
            return search(x, contents.second);
}

void insert(node* n, int x, node* child=NULL)
{
    n->keys.insert({x, child});
    node* future_root= new node(false); 
    if(n->isleaf)
    {
        if(n->return_size()>2*d)
        {
            if(n==root)
            {
                index_nodes++;
                root->parent=future_root;
                future_root->keys.insert({infinity, root});
            }
            node* new_node=new node(true, n->parent); data_nodes++;
            int cnt=0;
            for(auto val : n->keys)
            {
                new_node->keys.insert(val);
                if((++cnt)==d) break;
            }
            for(auto val : new_node->keys)
                n->keys.erase(val);
            insert(new_node, infinity); insert(n, infinity);
            insert(n->parent, n->keys.begin()->first, new_node);
            if(n==root) root=future_root;
        }

    }
    else
    {
        if(n->return_size()>2*t+1)
        {
            if(n==root)
            {
                index_nodes++;
                root->parent=future_root;
                future_root->keys.insert({infinity, root});
            }
            node* new_node=new node(false, n->parent); index_nodes++;
            int cnt=0;
            for(auto val : n->keys)
            {
                new_node->keys.insert(val);
                val.second->parent=new_node;
                if((++cnt)==t) break;
            }
            for(auto val : new_node->keys)
                n->keys.erase(val);
            auto start=n->keys.begin();
            n->keys.erase(n->keys.begin());
            new_node->keys.insert({infinity, start->second});
            new_node->parent=n->parent;
            insert(n->parent, start->first, new_node);
            if(n==root) root=future_root;
        }
    }
    
}

void content_display(node * n)
{
    
    vector<int> display;
    for(auto contents : n->keys)
        display.push_back(contents.first);
    display.pop_back();
    for(auto x : display) cout<<x<<" "; cout<<endl;
    //  for(auto values : n->keys) 
    //      if(values.second != NULL)
    //      content_display(values.second);
   // cout<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    cin>>d>>t;
    int input;
    bool first_insertion=false; //the b+ tree should ideally be initialised after its first insertion
    do
    {
        cin>>input;
        if(input==1)
        {
            int x; cin>>x;
            node *ptr=search(x, root);
            //if(x==5) content_display(ptr);
            insert(ptr, x);
            first_insertion=true;
        }
        else if(input==2 && first_insertion)
        {
            cout<<index_nodes<<" "<<data_nodes<<" ";
            content_display(root);
        }
        else if(input==2 && !first_insertion)
            cout<<"0 0\n";

    }while(input!=3);
    return 0;
}