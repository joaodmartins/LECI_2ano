# Preencha o mapa de registos e codifique em Assembly do MIPS a função proc().
# double prcells(int size, t_cell *tc)
# {
#     double tmp, result = 1.0;
#     int i;
# 
#     for (i = 0; i < size; i++) {
#         tmp = (double)tc[i].ns / 3.597;
#         result += tmp;
#         tc[i].xpt = tmp;
#         tc[i].sum = (int)result - 1;
#     }
#     return result;
# }

# Copie a estrutura para o topo da área de resposta
# e substitua xx pelo valor adequado
# typedef struct
# {                  Alignment  Size   Offset
# char smp[17];       1		17      0
# double xpt;         8      	8     	24
# int ns;             4      	4     	32
# char id;            1      	1     	36
# int sum;            4      	4     	40
# } t_cell;           8  	48      

# Copie para o topo da área de resposta e
# preencha com os registos usados
# Mapa de registos
# size  : $a0
# tc    : $a1
# result: $f0
# tmp   : $f2
# i     : $t0
# Preencha o mapa de registos e a tabela com os dados da estrutura. Codifique em Assembly do MIPS a função prcells().
	.eqv	smp, 0
	.eqv	xpt, 24
	.eqv	ns, 32
	.eqv	id, 36
	.eqv	sum, 40

	.data
_1_d:	.double 1.0
const:	.double	3.597
	.text
	.globl main
main:
	jr	$ra
	

prcells:				# double prcells(int size, t_cell *tc) {
	la	$t9, _1_d
	l.d	$f0, 0($t9)		#     double result = 1.0;
	li	$t0, 0			#     int i = 0;
for_cells:
	bge	$t0, $a0, endf_cells	#     while(i < size) {
	mul	$t1, $t0, 48		#	  $t1 = i*48
	add	$t1, $a1, $t1		#	  $t1 = &tc[i]
	lw	$t9, ns($t1)		#	  $t9 = tc[i].ns
	mtc1	$t9, $f18
	cvt.d.w	$f18, $f18		#	  $f18 = (double)tc[i].ns
	la	$t9, const
	l.d	$f16, 0($t9)		#	  $f16 = 3.597;
	div.d	$f2, $f18, $f16		#         double tmp = (double)tc[i].ns / 3.597;
	add.d	$f0, $f0, $f2		#	  result += tmp;
	s.d	$f2, xpt($t1)		#         tc[i].xpt = tmp;
	cvt.w.d	$f18, $f0		#	  $f18 = (int)result;
	mfc1	$t9, $f18
	addi	$t9, $t9, -1		#	  $t9 = (int)result - 1;
	sw	$t9, sum($t1)		#         tc[i].sum = (int)result - 1;
	
	addi	$t0, $t0, 1		#         i++;
	j	for_cells
endf_cells:
	jr	$ra			#     return result;
					# }



