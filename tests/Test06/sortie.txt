.text
.global main
main:
  ## prologue
  pushq %rbp # save %rbp on the stack
  movq %rsp, %rbp # define %rbp for the current function
  ## contenu
  movl  $2, -8(%rbp)
  movl  $0, -12(%rbp)
  movl  $4, -16(%rbp)
  movl  -12(%rbp), %eax
  subl  -16(%rbp), %eax
  movl  %eax, -20(%rbp)
  movl  -8(%rbp), %eax
  imull -20(%rbp), %eax
  movl  %eax, -24(%rbp)
  movl  $5, -28(%rbp)
  movl  -24(%rbp), %eax
  addl -28(%rbp), %eax 
  movl  %eax, -32(%rbp)
  movl  $0, -36(%rbp)
  movl  $6, -40(%rbp)
  movl  -36(%rbp), %eax
  subl  -40(%rbp), %eax
  movl  %eax, -44(%rbp)
  movl  -32(%rbp), %eax
  subl  -44(%rbp), %eax
  movl  %eax, -48(%rbp)
  movl  -48(%rbp), %eax
  movl  %eax, -4(%rbp)
  movl -4(%rbp), %eax
  popq %rbp
  ret
  ## epilogue
  popq %rbp # restore %rbp from the stack
  ret

