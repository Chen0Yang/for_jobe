class state{
public:
    typedef deque <string> prefix;
    state(string infile):NOWORD(){
        ifstream instream(infile.c_str());
        build_chain(instream);
        instream.close();
    }
    void build_chain(ifstream &instream){
        int i;
        string temp;
        for(i=0;i<NPREF;i++)
            temp_state.push_back(NOWORD);
        while(instream >> temp){
            statetbl[temp_state].push_back(temp);
            temp_state.pop_front();
            temp_state.push_back(temp);
        }
        cout << statetbl.size() << endl;
    }
    void generate_file(ofstream &outstream,int n){
        string word;
        if(n<=0)
            return;
        while(temp_state.size()!=0){
            temp_state.pop_back();
        }
        for(int i=0;i<NPREF;i++)
            temp_state.push_back(NOWORD);
        for(int i=0;i<n;i++){
            word = statetbl[temp_state][rand()%(statetbl[temp_state].size())];
            if(word == NOWORD)
                break;
            outstream << word << " ";
            temp_state.pop_front();
            temp_state.push_back(word);
        }

    }
private:
    string NOWORD;
    prefix temp_state;
    map<prefix,vector<string> > statetbl;
    static const int NPREF=2;
};
int main(){
    state my_state("hehe.txt");
    ofstream outstream("result.txt");
    my_state.generate_file(outstream,1000);
    outstream.close();
}
