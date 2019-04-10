
int to_five(int n) {
    int a = 1;
    int b = 2;
    return a*a + b*b;
}

int main() {
    int c = 3;
    int d = 4;
    int e = to_five(d);
    return e + c;
}
