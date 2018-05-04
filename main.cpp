#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
char alf[50] = "ab";
size_t sz = 2;
string cuv;

typedef set<int >::iterator iter;
typedef vector<set<int > >::iterator iterGen;

class Stare{
public:
    static int s_nr;
    int et,
        status,
        *v;
public:
    Stare();
    ~Stare();
};
Stare::Stare(){
    et = s_nr;
    try{
        int a = strlen(alf);
        v = new int[a + 1];
    }catch(bad_alloc& ba){
        cout << &ba;
    }
    s_nr++;
}
Stare::~Stare(){
    delete[] v;
}

int Stare::s_nr = 0;
int find(char ch[], char z){
    for(int i = 0; i <strlen(ch) +1 ; i++)
        if(ch[i] == z)
            return 1;

    return 0;
}

void AfisareTotala(vector<set<int> > sec){
    for(iterGen itg = sec.begin();itg != sec.end(); ++itg)
    {
        cout << "{ ";
        for(iter it = itg->begin(); it != itg->end(); ++it){
            cout << *it << " ";
        }

        cout << "}\n";
    }

    cout << endl << endl;
}





void Minim(vector<set<int> >& sec, Stare * ps, iter k, bool& ro){
    vector<int> auxit;
    int aux, bo;
    for(iter it = k ; it != sec[1].end(); ++it){
        bo = 0;

        for(int j = 0; j < strlen(alf); j++){
            aux = ps[*it].v[alf[j] - 97];

            if(sec[1].find(aux) == sec[1].end() && !bo) {
                if (!auxit.empty()) {
                    for (int i = 2; i < sz; i++) {
                        for (iter re = sec[i].begin(); re != sec[i].end(); ++re) {

                            if (ps[*it].v[0] == ps[*re].v[0] && ps[*it].v[1] == ps[*re].v[1]) {
                                sec[i].insert(*it);
                                auxit.push_back(*it);
                                bo = 1;
                            }
                        }
                    }
                }
                if(!bo){
                    sec.resize(++sz);
                    sec[sz - 1].insert(*it);
                    auxit.push_back(*it);
                    j = strlen(alf);
                    bo = 1;
                }
            }
        };




        cout << endl;
    }
    for(vector<int>::iterator it = auxit.begin(); it != auxit.end(); ++it){
        sec[1].erase(*it);
    }

    if(auxit.empty())
        ro = false;

    cout << endl;

}

int main() {
    int m, n, i, a, b;
    char str[100];
    ifstream f("C:\\Work\\tema2lfa\\graf.in");
//nr noduri si muchii
    f >> n >> m;
//acesta este cuvantul
    f >> cuv;


    cout << n << " stari cu " << m << " muchii si cuvantul este : " << cuv << ".\n";


    Stare * ps;
    ps = new Stare[n + 1];
    do{
        f >> a >> b >> str;
        //un breaks a iasa din ciclu, se poate schimba apoi
        if(a == -1)
            break;
        //ATRIBUIM STARILE IESIRE/INTRARE SAU DELOC
        //0 = intrare
        //1 = iesire
        //-1 = deloc
        if(b == 0){
            if(find(str, 'z'))
                ps[a].status = 0;
            else
                ps[a].status = 1;
        }
        if(ps[a].status != 0 && ps[a].status != 1)
            ps[a].status = -1;

        //Adaugam tranzitiile
        if(!find(str, 'x'))
            ps[a].v[str[0] - 97] = b;

    }while(1);

    //AFISAM STRUCTURA:
    //1: E INITIALA si SE DUCE IN 2 CU A si SE DUCE IN 3 CU B...

    for(i = 1; i <=n; i++)
        cout << ps[i].et << ": " << ps[i].status << "   " << ps[i].v[0] << "a   " << ps[i].v[1] << "b  \n";


    //FACEM CU SETURI STL YASS

    vector<set<int > > sec(2);
    //cout << sec.size();

    //Impartim in 2 multimi, multimea terminalelor si a neterminalelor

    for(i = 1; i <= n; i++){
        if(ps[i].status == 1){
            sec[0].insert(ps[i].et);
        }else
            sec[1].insert(ps[i].et);
    }


    //Luam prima multime si verificam pentru fiecare element daca blabla


    bool ro = true;
    while(ro){
        Minim(sec, ps, sec[1].begin(), ro);
    }
    sec.erase(sec.begin() + 1);
    AfisareTotala(sec);


    delete[] ps;
    f.close();

    return 0;
}

