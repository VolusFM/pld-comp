int main() {
  int i = 0;
  do {
    i = i+1;
  } while (i<5);

  while (i>2) {
    i = i-1;
  }
  int k =2;
  for(int j=0; j<i; j=j+1) {
    k = k+1;
  }
  return i + j - k;
}
