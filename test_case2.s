	add	$t1, $t2, $t3
	addu	$t1, $t2, $t3
	and	$s1, $s2, $s3
	nor	$a0, $a1, $a2
	or	$v1, $s1, $t1
	slt	$s4, $s5, $s6
	sltu	$t4, $t5, $t6
	sub	$v0, $a0, $t0
	subu	$a1, $a2, $a3
	lw	$t1, 4($t0)
	lw	$t2, 100($t0)
	sw	$t1, 4($t0)
	sw	$t2, 100($t0)
	lw	$t1, 4($s0)
	sw	$t1, 420($s1)
	sll	$s0, $s1, 2
	srl	$s1, $s0, 4
	andi	$t7, $t8, 256
	ori	$t7, $t8, 123
	addi	$t7, $t7, 3916
