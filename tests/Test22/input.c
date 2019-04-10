
int function (int a){
    int b = function(a-1);
    return b;
}

int main() {
    int a = 5;
    a = function(a);
}
