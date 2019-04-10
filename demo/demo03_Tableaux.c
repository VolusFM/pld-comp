
int main() {
    int a = 2;
    int b = 3;
    int tab [8];
    tab[0] = 1;
    tab[a] = 2;
    tab[3-1] = 3;
    tab[b*a] = 4;
    int tab2 [3] = {1,2,3};
    int tab3 [5] = {0,1};
    int tab4 [3] = {a, a+b, a=tab[0]*b};
    
    return tab4[2];
}
