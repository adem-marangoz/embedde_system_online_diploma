#	Global sections
.global reset


#	Operations within each section
reset:
	#	Init Top Stack secetion in RAM
	ldr sp,= stack_top 	
	#	Brunch to main function
	bl	main				
stop:						#	if in the main function is no infinitive loop, after exiting the main it will go down to the next section
	b stop					

