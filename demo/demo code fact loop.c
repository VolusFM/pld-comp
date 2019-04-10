
int fact(int n) {
    int i;
    
    int res = 1;
    
    for (i = n; i != 0; i=i-1) {
        res = res * i;
    }
    
    return res;
}

int main() {
    int n;
    
    return fact(n = 4);
}
