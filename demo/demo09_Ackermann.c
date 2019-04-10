
int Ackermann(int m, int n) {
    if (m > 0) {
        if (n > 0) {
            return Ackermann(m-1, Ackermann(m,n-1));
        } else {
            return Ackermann(m-1, 1);
        }
    } else {
        return n+1;
    }
}

int main() {
    return Ackermann(3, 3);
}

