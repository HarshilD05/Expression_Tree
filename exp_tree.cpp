/*
This Program will take Input Expression as string
and create an expression tree using the Shunting Yard
Algorithm. Using 2 Stacks.

the // commented code is for logging and testing purpose
*/

#include<iostream>
#include<vector>
#include"tree.cpp"

/*  Functions   */
int precedence (char op) {
    return 
    (op == '^') ? 3 :
    (op == '/' || op == '*' || op == '%') ? 2 : 
    (op == '+' || op == '-') ? 1 : -1;
}

bool is_Num (char c) {
    std::string num = "1234567890";
    for (char n : num) {
        if (c == n) return true;
    }
    return false;
}

bool is_Op (char c) {
    std::string ops = "+-/%*^";
    for (char o : ops) {
        if (c == o) return true;
    }
    return false;
}

TreeNode* create_exp_tree(std::string exp) {
    std::cout<<"\nExpression Recieved : "<< exp;

    std::string ops;
    std::vector<TreeNode*> nodes;

    std::string n = "";
    std::string op = "";

    for (int i = 0;i<exp.size();i++) {
        char c = exp[i];
        // std::cout<<"\n\nChar : "<< c ;
        // std::cout<<"\n Operator STACK : "<< ops ;
        // std::cout<<"\n Node Stack : ";
        // for (auto x : nodes) std::cout<< x->data <<",";

        /*  If number found add in number string    */
        if (is_Num(c) ) {
            n += c;
            // std::cout<<"\n Number : "<< n ;
        }
        else if (is_Op(c) ) {
            // std::cout<<"\n Operator Found....";
            /*  Create a Node for the number before the Operator only if number exists */
            if (n.size() ) {
                TreeNode* num = new TreeNode(n);
                nodes.push_back(num);
                n = "";
                // std::cout<<"\n Node for Number "<< num->data <<" Created!";
            }

            /*  Skip this block if first operator   */
            if (ops.size() && ops[ops.size()-1] != '(' ) {
                // std::cout<<"\n Checking Precendence....";
                // std::cout<<"\nCurrent Op : "<< c <<"\nPrevious Operator : "<< ops[ops.size()-1] ;

                /*  Checking Precedence */
                if (precedence(c) < precedence( ops[ops.size()-1] ) ) {
                    // std::cout<<"\n Precendence is Lower thus Executing Prev Operation ";

                    op += ops[ops.size()-1];    // operator string to create a TreeNode
                    ops.pop_back();
                    // std::cout<<"\n Operator : "<< op;
                    
                    /*  creating Node for the operator and attaching the left and right operands    */
                    TreeNode *OPERATOR = new TreeNode(op);
                    OPERATOR->right = nodes[nodes.size()-1];
                    nodes.pop_back();
                    // std::cout<<"\n Right Subtree : "<< OPERATOR->right->data;

                    OPERATOR->left = nodes[nodes.size()-1];
                    nodes.pop_back();
                    // std::cout<<"\n Left Subtree : "<< OPERATOR->left->data;

                    nodes.push_back(OPERATOR);
                    op = "";    // Clearing Operator String

                    // std::cout<<"\n Previous Operation Complete and Node pushed in NODE STACK.";

                }
                // else std::cout<<"\n Precedence of Curr_op is Higher...";
            }
            
            /*  Push Current operator in STACK ops    */
            ops.push_back(c);

        }
        else if (c == '(') ops.push_back(c);    // '(' is always pushed to ops STACK
        /*  If ')' found then pop ops STACK till the respective '(' is reached  */
        else if (c == ')') {
            // std::cout<<"\n ')' bracket Encountered.... ";

            /*  Creating Node for number before ')'  only if number exists*/
            if (n.size() ) {
                TreeNode* num = new TreeNode(n);
                nodes.push_back(num);
                n = "";
                // std::cout<<"\n Node for number "<< num->data <<" created.";
            }

            // std::cout<<"\nPopping till the respective '(' is reached. ";
            while (ops[ops.size()-1] != '(') {
                op += ops[ops.size()-1];
                ops.pop_back();
                // std::cout<<"\n Operator : "<< op ;

                TreeNode* OPERATOR = new TreeNode(op);
                OPERATOR->right = nodes[nodes.size()-1];
                nodes.pop_back();
                // std::cout<<"\nRight Subtree : "<< OPERATOR->right->data;

                OPERATOR->left = nodes[nodes.size()-1];
                nodes.pop_back();
                // std::cout<<"\n Left Subtree : "<< OPERATOR->left->data;

                nodes.push_back(OPERATOR);

                op = "";
            }
            ops.pop_back();
        }

        if (i == exp.size()-1) {
            // std::cout<<"\n Last Character of expression..";
            if (n.size() ) {
                TreeNode* num = new TreeNode(n);
                nodes.push_back(num);
                n = "";
                // std::cout<<"\n Node for Number "<< num->data <<" created";

            } 
            
        }
    }

    /*  Clearing remaining data in Stack to complete the Expression tree    */
    // std::cout<<"\n Emptying remaining STACK contents";
    while (ops.size() != 0) {
        op += ops[ops.size()-1];
        ops.pop_back();
        // std::cout<<"\n Operator : "<< op;

        TreeNode* OPERATOR = new TreeNode(op);
        OPERATOR->right = nodes[nodes.size()-1];
        nodes.pop_back();
        // std::cout<<"\n Right Subtree : "<< OPERATOR->right->data;

        OPERATOR->left = nodes[nodes.size()-1];
        nodes.pop_back();
        // std::cout<<"\n Left Subtree : "<< OPERATOR->left->data;

        nodes.push_back(OPERATOR);

        op = "";
    }

    return nodes[0];
}

int main () {
    std::string exp = "(35 / (5 + 2))^3 + 7 * 10";

    TreeNode* exp_tree = create_exp_tree(exp);

    BinTree x(exp_tree);

    std::cout<<"\n In Order : ";
    x.in_order();

    std::cout<<"\n Pre Order : ";
    x.pre_order();

    std::cout<<"\n Post Order : ";
    x.post_order();    

    return 0;
}
