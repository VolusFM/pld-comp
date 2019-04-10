int factorielle(int n){
    if(n==1){
        return 1;
    }else if (n==0) {
        return 1;
    }else {
        int result = n * factorielle(n-1);
        return result ;
    }
}

int main() {
  int n = 5;
  return factorielle(n);
}


