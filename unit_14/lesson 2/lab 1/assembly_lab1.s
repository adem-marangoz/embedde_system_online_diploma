RESET			;CPU entry point
			bl		main
			
			
			
main
			mov		r0,#5
			bl		subtract
			bl		termination
			
			
subtract
			sub		r0,r0,#1
			cmp		r0,#1
			bne		subtract
			mov		pc,lr
			
			
termination
			
