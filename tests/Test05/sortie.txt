.text
.global main
main:
  ## prologue
  pushq %rbp # save %rbp on the stack
  movq %rsp, %rbp # define %rbp for the current function
  ## contenu
  movl  $3, -32(%rbp)
  movl  -32(%rbp), %eax
  movl  %eax, -8(%rbp)
  movl  $90, -36(%rbp)
  movl  -36(%rbp), %eax
  movl  %eax, -12(%rbp)
  movl  $4, -40(%rbp)
  movl  -40(%rbp), %eax
  movl  %eax, -20(%rbp)
  movl  $5, -44(%rbp)
  movl  $3, -48(%rbp)
  movl  -44(%rbp), %eax
  addl -48(%rbp), %eax 
  movl  %eax, -52(%rbp)
  movl  -52(%rbp), %eax
  movl  %eax, -28(%rbp)
  ## epilogue
  popq %rbp # restore %rbp from the stack
  ret

