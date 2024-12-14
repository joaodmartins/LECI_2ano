# float proc(double *array, double thd, double val, int n)
# {
#    int i;
#    double aux, sum;
#
#    sum = 0.0;
#    for (i = 0; i < n; i++) {
#        aux = array[i] + val;
#        if (aux > thd) {
#            array[i] = thd;
#            sum += thd;
#        } else {
#            array[i] = aux;
#            sum += aux;
#        }
#    }
#    return (float) (sum / (double) n);
# }
# Copie para o topo da área de resposta e
# preencha com os registos usados
# Mapa de registos
# array       : $a0
# thd         : $f12-$f13
# val         : $f14-$f15
# n           : $a1
# i           : $t0
# aux         : $f2-$f3
# sum         : $f0-$f1
# Preencha o mapa de registos e codifique em Assembly do MIPS a função proc().
	.data
_0_d:	.double 0.0
	.text
	.globl main
main:
	jr	$ra
	
proc:					# float proc(double *array, double thd, double val, int n) {
	la	$t9, _0_d
	l.d	$f0, 0($t9)		#    double sum = 0.0;
	li	$t0, 0			#    int i = 0
for_proc:
	bge	$t0, $a1, endf_proc	#    while(i < n) {
	sll	$t9, $t0, 3		#        $t9 = i*8
	addu	$t9, $a0, $t9		#	 $t9 = &array[i]
	l.d	$f2, 0($t9)		#	 double aux = array[i];
	add.d	$f2, $f2, $f14		#        aux = array[i] + val;
if_proc:
	c.le.d	$f2, $f12
	bc1t	else_proc		#        if (aux > thd) {
	s.d	$f12, 0($t9)		#            array[i] = thd;
	add.d	$f0, $f0, $f12		#            sum += thd;
	j	endif_proc		#	 }
else_proc:				# 	 else {
	s.d	$f2, 0($t9)		#            array[i] = aux
	add.d	$f0, $f0, $f2		#            sum += aux;
endif_proc:				#	 }
	addi	$t0, $t0, 1		#        i++;
	j	for_proc		#    }
endf_proc:
	mtc1	$a1, $f18
	cvt.d.w	$f18, $f18		#    $f18 = (double) n
	div.d	$f0, $f0, $f18		#    $f0 = sum / n
	cvt.s.d	$f0, $f0		#    return (float) (sum / (double) n;
	
	jr 	$ra