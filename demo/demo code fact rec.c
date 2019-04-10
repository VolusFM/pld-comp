
int fact(int n) {
    if (n == 0)
        return 1;
    else {
        return fact(n-1) * n;
    }
}

int main() {
    return fact(4);
}
