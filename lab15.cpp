#include <iostream>


struct tree {
    int znach;
    tree* l;
    tree* r;
    tree* p;
};




std::string intrpr(std::string &s ) {
    std::string f;
    if (s[0] != '(' && s[0] != ')' && s[0] != ',' && s[0] != ' ' && s.length()>=1) {
        if (s[1] != '(' && s[1] != ')' && s[1] != ',') {
         while(1){
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



int perevod(std::string &s) {
    std::string f = intrpr(s);
    int b = 0;
    int t = 10;
    for (int i = 0; i < f.length(); i++) {
        if (f.length() > 1) {
            b = b * t + ((int)f[i] - 48);
            
            //f.erase(0, 1);
        }
        else {
            b = b * t +( (int)f[i] -48);
            return (b);
        }
    }
    return (b);
}





struct tree* addtr(struct tree* rt, std::string &s) {

    
   
        if (s[0] == '(' && s[1] != ',' && s.length() > 2) {
            s.erase(0, 1);
            rt->l = (struct tree*)malloc(sizeof(struct tree));
            rt->l->znach = perevod(s);
            rt->l->l = rt->l->r  = NULL;
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
        if ((s[0]==')' || s[0] == '(' && s[1] == ',')&& s.length() > 2) {
            s.erase(0, 1);
            if (rt->p != NULL) {
                rt->p = addtr(rt->p, s);
            }
            else {
                rt= addtr(rt, s);
            }
        }

        
    return rt;
}


void prim(tree* t)
{
    if (t == NULL) return;
   
    std::cout << t->znach << " "; //И показываем элемент
   
    prim(t->l);//С помощью рекурсивного посещаем левое поддерево
    prim(t->r ); //С помощью рекурсии посещаем правое поддерево
}




void centr(struct tree* root) {
    if (root != NULL) {
        if (root->l != NULL)
        centr(root->l);
        std::cout << root->znach << " ";
        if (root->r != NULL)
        centr(root->r);

    }
    
}

void konz(struct tree* root) {
    if (root != NULL) {
        if (root->l != NULL)
            konz(root->l);
        if (root->r != NULL)
            konz(root->r);
        std::cout << root->znach << " ";
      

    }

}


int main()
{
    std::string tx;
    std::cin >> tx;
    struct tree* root;
    root = NULL;

   

   root = (struct tree*)malloc(sizeof(struct tree));
   root->znach = perevod(tx);
   root->l = root->r = root->p= NULL;
    


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
    centr(root);
    std::cout << std::endl;
    std::cout << std::endl;
   prim(root);
   std::cout << std::endl;
   std::cout << std::endl;
   konz(root);
}
