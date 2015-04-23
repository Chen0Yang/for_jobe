struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class bstree{
public:
    bstree():treehead(NULL){
        for(int i = 0;i<10;i++){
             insert_bst(treehead,rand()%100);
             //insert_bst(treehead,i);
        }
    }
    TreeNode * get_tree(){return treehead;}
    TreeNode * insert_bst( TreeNode * pbst,int val){
        //cout << val << endl;
        if(pbst){
            if(val > pbst->val){
                if( pbst->right )
                    insert_bst(pbst->right,val);
                else{
                    pbst->right = new TreeNode(val);
                    cout << val << endl;
                    return pbst->right;
                }

            }

            else if (val < pbst->val){
                if( pbst->left )
                    insert_bst(pbst->left,val);
                else{
                    pbst->left = new TreeNode(val);
                    cout << val << endl;
                    return pbst->left;
                }
            }
        }else{
           pbst = new TreeNode(val);
           treehead = pbst;
           return pbst;
        }
    }
    void print_bst(TreeNode * head){
        if(head){
            print_bst(head->left);
            cout << head->val << endl;
            print_bst(head->right);
        }
    }
    void print_bst_stack(TreeNode * head){
        //stack_print.push(head);
        while(head){

            while(head){
                stack_print.push(head);
                head = head->left;
            }
            //cout << head->val << endl;
            if(!stack_print.empty()){
                head = stack_print.top();
                stack_print.pop();
                cout << head->val << endl;
            } else {
                return;
            }
            while(head){
                if(head->right){
                    head = head->right;
                    break;
                    //stack_print.push(head);
                }else{
                    if(!stack_print.empty()){
                        head = stack_print.top();
                        stack_print.pop();
                        cout << head->val << endl;
                    }else{
                        return;
                    }
                }
            }
        }
    }
    void print_hight(TreeNode * head,int height){
        if(head){
            height++;
            print_hight(head->left,height);
            //cout << height << endl;
            high_stack.push(height);
            print_hight(head->right,height);
        }
    }
    void print_high()
    {
        print_hight(treehead,0);
        int max_high = 0;
        while(!high_stack.empty()){
            if(max_high < high_stack.top()){
                max_high = high_stack.top();
            }
            high_stack.pop();
        }
        cout << max_high << endl;
    }
private:
     TreeNode * treehead;
     stack <int> high_stack;
     stack <TreeNode *> stack_print;
};
int main (){
    bstree my_bst;
    my_bst.print_bst(my_bst.get_tree());
    my_bst.print_high();
    my_bst.print_bst_stack(my_bst.get_tree());
    return 0;

}
