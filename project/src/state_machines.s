	.arch msp430g2553
	.p2align 1,0
	.text
jt:
	.word default		;default case
	.word case1		;case 1(button 1)
	.word case2		;case 2(button 2)
	.word case3		;case 3(button 3)
	.word case4		;case 4(button 4)

	
	.global state_advance	;method that uses the switch statement
state_advance:
	cmp #5, r12		;checks the if it falls between the cases provided
	jnc default 		;if the borrow flag is activated then it will jump to default
	add r12,r12		;multiplying space twice
	mov jt(r12), r0		;moves to counter

case1:
	call buzzer_set_period	;Song notes play
	jmp end
	
case2:
	call _state_advance	;Lights alternate in a sequence
	jmp end
	
case3:
	call buzzer_off		;current note playing stops and lights turn off
	call lights_off
	jmp end

case4:
	call buzzer_set_period	;Song notes play
	jmp end
	
default:
	ret			;popping r0, returns
