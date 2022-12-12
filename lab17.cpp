#include <iostream>
#include <Windows.h>
#include<vector>
#include<string>

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
struct tree {
    int znach;
    tree* l;
    tree* r;
    tree* p;
};


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


void prim(tree* t)
{
    if (t == NULL) return;

    std::cout << t->znach << " "; 

    prim(t->l);
    prim(t->r); 
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
        if (root->l != NULL && root->znach>=0)
            konz(root->l);
        if (root->r != NULL && root->znach >= 0)
            konz(root->r);
        if(root->znach >= 0)
        std::cout << root->znach << " ";


    }

}


struct tree* addtre(int x, tree* tr) {
    if (tr == NULL) { // Если дерева нет, то формируем корень
        tr = new tree; // память под узел
        tr->znach = x;   // поле данных
        tr->l = NULL;
        tr->r = NULL; // ветви инициализируем пустотой
    }
    else  if (x < tr->znach)   // условие добавление левого потомка
        tr->l = addtre(x, tr->l);
    else    // условие добавление правого потомка
        tr->r = addtre(x, tr->r);
    return(tr);
}


int Poisk(tree* rt, int k) {
    int j = 1212;
    if (rt != NULL) {
        if (rt->znach == k) {
            j = k;
            return j;    
        }
        else {
            if (rt->l != NULL && j != k)
              j = Poisk(rt->l, k);
            if (rt->r != NULL && j !=k)
              j = Poisk(rt ->r, k);
        }

    }
    return j;
}



void dump(tree const* node, bool high = true, std::vector<std::string> const& lpref = std::vector<std::string>(), std::vector<std::string> const& cpref = std::vector<std::string>(), std::vector<std::string> const& rpref = std::vector<std::string>(), bool root = true, bool left = true, std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr) {
    if (!node) return;
    typedef std::vector<std::string> VS;
    auto VSCat = [](VS const& a, VS const& b) { auto r = a; r.insert(r.end(), b.begin(), b.end()); return r; };
    if (root) lines = std::make_shared<std::vector<VS>>();
    if (node->l)
        dump(node->l, high, VSCat(lpref, high ? VS({ " ", " " }) : VS({ " " })), VSCat(lpref, high ? VS({ ch_ddia, ch_ver }) : VS({ ch_ddia })), VSCat(lpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), false, true, lines);
    auto sval = std::to_string(node->znach);
    size_t sm = left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, { std::string(1, sval[i]) }));
    if (node->r)
        dump(node->r, high, VSCat(rpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), VSCat(rpref, high ? VS({ ch_rddia, ch_ver }) : VS({ ch_rddia })), VSCat(rpref, high ? VS({ " ", " " }) : VS({ " " })), false, false, lines);
    if (root) {
        VS out;
        for (size_t l = 0;; ++l) {
            bool last = true;
            std::string line;
            for (size_t i = 0; i < lines->size(); ++i)
                if (l < (*lines).at(i).size()) {
                    line += lines->at(i)[l];
                    last = false;
                }
                else line += " ";
            if (last) break;
            out.push_back(line);
        }
        for (size_t i = 0; i < out.size(); ++i)
            std::cout << out[i] << std::endl;
    }
}




tree* DeleteNode(tree* node, int val) {
    if (node == NULL)
        return node;

    if (val == node->znach) {

        tree* tmp;
        if (node->r == NULL)
            tmp = node->l;
        else {

            tree* ptr = node->r;
            if (ptr->l == NULL) {
                ptr->l = node->l;
                tmp = ptr;
            }
            else {

                tree* pmin = ptr->l;
                while (pmin->l != NULL) {
                    ptr = pmin;
                    pmin = ptr->l;
                }
                ptr->l = pmin->r;
                pmin->l = node->l;
                pmin->r = node->r;
                tmp = pmin;
            }
        }

        delete node;
        return tmp;
    }
    else if (val != node->znach)
        node->l = DeleteNode(node->l, val);
    else
        node->r = DeleteNode(node->r, val);
    return node;
}




int main()
{
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN );
    setlocale(LC_ALL, "Russian");

    std::string tx;
    std::cout << "Введите дерево в формате линейно-скобочной записи" << std::endl;
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



    while (1) {
        std::cout << std::endl;
        std::cout << "Если вы хотите узнать, есть ли в дереве некоторое число, то нажмите 1" << std::endl;
        std::cout << "Если вы хотите удалить некоторую ветвь, то нажмите 2" << std::endl;
        std::cout << "Если вы хотите добавить некоторое число, то нажмите 3" << std::endl;
        std::cout << "Если вы хотите завершить программу, то нажмите 4" << std::endl;
        int jo;
        std::cin >> jo;


        if (jo == 1) {
            std::cout << "Введите число" << std::endl;
            int rrr;
            std::cin >> rrr;
            int y = Poisk(root, rrr);
            if (y == 1212) {
                std::cout << "Такого числа нет" << std::endl;
            }
            else
            {
                std::cout << "Такое число есть" << std::endl;
            }
        }
        else if (jo ==2) {
            std::cout << "Введите число, с которого начинается ветвь" << std::endl;
            int yyy;
            std::cin >> yyy;
            root =DeleteNode(root, yyy);
   
      
        }
        else if (jo==3) {
            std::cout << "Введите число" << std::endl;
            int jj;
            std::cin >> jj;
            root = addtre(jj, root);
          
        }
        else if (jo == 4) {
            std::cout << std::endl;
            //prim(root);
            dump(root);
            break;
        }


    }



}