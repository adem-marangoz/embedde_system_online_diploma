RESET			;CPU entry point
			bl		main
			
			
			
main
			mov		r0, #5
			mov		r2, #0x100
			str		r0, [r2]
			ldr		r3, [r2]
			bl		termination
			
			
termination
			
