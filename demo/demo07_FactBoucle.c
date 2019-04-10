
int fact(int n) {
    int res = 1;
    
    int i;
    for (i = 1; i <= n; i=i+1) {
        res = res * i;
    }
    
    return res;
}

int main() {
    int n;
    
    return fact(n = 4);
}
