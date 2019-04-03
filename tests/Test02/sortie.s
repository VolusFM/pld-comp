.text
.global main
main:
  ## prologue
  pushq %rbp # save %rbp on the stack
  movq %rsp, %rbp # define %rbp for the current function
  ## contenu
  movl  $2, -8(%rbp)
  movl  $3, -12(%rbp)
  movl  -8(%rbp), %eax
  imull -12(%rbp), %eax
  movl  %eax, -16(%rbp)
  movl  $4, -20(%rbp)
  movl  -16(%rbp), %eax
  addl -20(%rbp), %eax 
  movl  %eax, -24(%rbp)
  movl  $4, -28(%rbp)
  movl  -24(%rbp), %eax
  subl  -28(%rbp), %eax
  movl  %eax, -32(%rbp)
  movl  -32(%rbp), %eax
  movl  %eax, -4(%rbp)
  movl -4(%rbp), %eax
  popq %rbp
  ret
  ## epilogue
  popq %rbp # restore %rbp from the stack
  ret

