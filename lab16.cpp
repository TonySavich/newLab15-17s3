#include <iostream>
#include <stack>


struct tree {
    int znach;
    tree* l;
    tree* r;
    tree* p;
};



void obhod (tree* t)
{
    std::stack<tree*> s;
    s.push(NULL);
    tree* tt = t;
    do {
        if (tt != NULL) {
            s.push(tt);
            std::cout << tt->znach << '\n';
            tt = tt->l;
        }
        else {
            if (s.top() == NULL) break;
            tt = s.top();
            s.pop();
            tt = tt->r;
        }
    } while (true);
}




std::string intrpr(std::string& s) {
    std::string f;
    if (s[0] != '(' && s[0] != ')' && s[0] != ',' && s[0] != ' ' && s.length() >= 1) {
        if (s[1] != '(' && s[1] != ')' && s[1] != ',') {
            while (1) {
                if (s[0] != '(' && s[0] != ')' && s[0] != ',') {

                    f = f + s[0];
                    s.erase(0, 1);


                }
                else {
                    return f;
                }


            }


        }
        else {
            f = s[0];
            s.erase(0, 1);
            return f;
        }


    }




}



int perevod(std::string& s) {
    std::string f = intrpr(s);
    int b = 0;
    int t = 10;
    for (int i = 0; i < f.length(); i++) {
        if (f.length() > 1) {
            b = b * t + ((int)f[i] - 48);

            //f.erase(0, 1);
        }
        else {
            b = b * t + ((int)f[i] - 48);
            return (b);
        }
    }
    return (b);
}




struct tree* addtr(struct tree* rt, std::string& s) {



    if (s[0] == '(' && s[1] != ',' && s.length() > 2) {
        s.erase(0, 1);
        rt->l = (struct tree*)malloc(sizeof(struct tree));
        rt->l->znach = perevod(s);
        rt->l->l = rt->l->r = NULL;
        rt->l->p = rt;
        // s.erase(0, 1);
        rt->l = addtr(rt->l, s);
    }



    if (s[0] == ',' && s.length() > 2) {

        s.erase(0, 1);
        if (rt->p != NULL) {
            rt->p->r = (struct tree*)malloc(sizeof(struct tree));
            rt->p->r->znach = perevod(s);
            rt->p->r->l = rt->p->r->r = NULL;
            rt->p->r->p = rt->p;
            //  s.erase(0, 1);
            rt->p->r = addtr(rt->p->r, s);
        }
        else {
            rt->r = (struct tree*)malloc(sizeof(struct tree));
            rt->r->znach = perevod(s);
            rt->r->l = rt->r->r = NULL;
            rt->r->p = rt;
            // s.erase(0, 1);
            rt->r = addtr(rt->r, s);
        }

    }
    if ((s[0] == ')' || s[0] == '(' && s[1] == ',') && s.length() > 2) {
        s.erase(0, 1);
        if (rt->p != NULL) {
            rt->p = addtr(rt->p, s);
        }
        else {
            rt = addtr(rt, s);
        }
    }


    return rt;
}





int main()
 {
    std::string tx;
    std::cin >> tx;
    struct tree* root;
    root = NULL;



    root = (struct tree*)malloc(sizeof(struct tree));
    root->znach = perevod(tx);
    root->l = root->r = root->p = NULL;



    //std::cout << perevod(tx);




    if (tx.length() > 1) {
        while (1) {
            if (tx[0] != '(' && tx[0] != ')' && tx[0] != ',' && tx[0] != ' ' && tx.length() > 1)
                tx.erase(0, 1);
            else {
                break;
            }
        }

    }

    if (tx.length() > 1) {
        root = addtr(root, tx);
    }



    std::cout << std::endl;
    obhod(root);
}
