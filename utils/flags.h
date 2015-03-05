//
// flags.h for KCatOS in /home/ampotos/kcatos
// 
// Made by 
// Login   <ampotos@epitech.net>
// 
// Started on  Thu Feb 26 10:38:21 2015 
// Last update Thu Feb 26 10:47:33 2015 
//

// ideally we have to target cpu model at compile time to create only existing flag

#define CARRY_FLAG			1
#define PARITY_FLAG			(1 << 2)
#define ADJUST_FLAG			(1 << 4)
#define ZERO_FLAG			(1 << 6)
#define SIGN_FLAG			(1 << 7)
#define TRAP_FLAG			(1 << 8)
#define INTERRUPT_FLAG			(1 << 9)
#define DIRECTION_FLAG			(1 << 10)
#define OVERFLOW_FLAG			(1 << 11)

#define RESUME_FLAG			(1 << 16) // only on 80386+
#define VIRTUAL_MODE_FLAG		(1 << 17) // only on 80386+

#define ALIGN_CHECK_FLAG		(1 << 18) // only on 80486SX+

#define VIRTUAL_INTERRUPT_FLAG		(1 << 19) // only on pentium+
#define VIRTUAL_INTERRUPT_PENDING_FLAG	(1 << 20) // only on pentium+
#define IS_CPUID_FLAG			(1 << 20) // only on pentium+
