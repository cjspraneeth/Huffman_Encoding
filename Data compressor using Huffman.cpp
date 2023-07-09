#include <bits/stdc++.h>
using namespace std;

class Huffman{

    public:
    string encoded;//final encoded string
    string decoded;//final decoded string

    //node structure of the huffman tree
    struct node{

        char c;
        bool isLeaf;
        node* left;
        node* right;
        node(char ch ='#',bool f = false,node* l = NULL,node* r=NULL){
            
            c=ch;
            isLeaf = f;
            left = l;
            right = r;
        }
    };

    node* root;
   
    //function to make the huffman tree and encode the original string
    void encoder(string &s){
        map<char,int> freq;//map to store frequency of each character in the string
        int sz = s.size();
        for(int i=0;i<sz;i++)freq[s[i]]++;
        set<pair<int,node*>> st;

        for(auto it=freq.begin();it!=freq.end();it++){
            char c = (*it).first;
            int val = (*it).second;
            node* temp = new node(c,true);
            st.insert({val,temp});
        }
        //making the huffman tree
        while(st.size()>1){
            
            auto it1 = *st.begin();
            st.erase(it1);
            auto it2 = *st.begin();
            st.erase(it2);

            int v1,v2;
            node* n1;
            node* n2;
            
            v1 = (it1).first;
            v2 = (it2).first;
            n1 = (it1).second;
            n2 = (it2).second;

            node* temp = new node;

            temp->left = n1;
            temp->right = n2;
            int val = v1+v2;
            st.insert({val,temp});

        }

        auto it = *st.begin();
        node *r = it.second;//root of the huffman tree
        root = r;
        map<char,string> compressed;
        queue<pair<node*,string>> q;
        q.push({r,""});

        while(!q.empty()){

            auto p = q.front();
            q.pop();

            string temp = p.second;
            node* n =p.first;
            if(n->isLeaf){

                compressed[n->c]=temp;
                continue;
            }
            if(n->left!=NULL){

                q.push({n->left,temp+'0'});
            }
            if(n->right!=NULL){
                q.push({n->right,temp+'1'});
            }
        }

        string temp = "";
        for(char ch:s){

            temp+=compressed[ch];
        }

        encoded = temp;

    }


    void decoder(string &s){

        string ans = "";
        node* temp = root;
        for(char ch:s){

            if(ch=='1'){

                temp = temp->right;

            }
            else{
                temp = temp->left; 
            }

            if(temp->isLeaf){
                ans+=temp->c;
                temp=root;
            }
        }

        decoded = ans;
    }
    double getCompressionRatio(string &s) {
        double originalSize = static_cast<double>(s.size()*8);
        cout<<" Original size"<<originalSize<<endl;
        double encodedSize = static_cast<double>(encoded.size());
        cout<<" encoded size"<<encodedSize<<endl;
        return (originalSize - encodedSize) / originalSize;
    }

    
};
int main(){

    Huffman huf;
    string s = "Test string";

    huf.encoder(s);
    cout<<huf.encoded<<endl;
    huf.decoder(huf.encoded);
    cout<<huf.decoded<<endl;
    double compressionRatio = huf.getCompressionRatio(s);
    cout << "Compression ratio: " << fixed << setprecision(2) << compressionRatio << endl;
   

    return 0;
}