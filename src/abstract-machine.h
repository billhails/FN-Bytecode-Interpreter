#define NUM_TEMPS 10

typedef unsigned char byte;
typedef byte instruction;
typedef int PC;
typedef struct env *ENV;
typedef struct closure *CLOS;
typedef struct continuation *CONT;
typedef struct am *AM;
typedef struct am *FAIL;
typedef union expr *EXPR;
typedef EXPR frame[0];

struct env {
	ENV parent;
	frame frame;
};

/*********************************************
 * closure continuation  am        fail
 * PC      PC            PC        PC
 * ENV     ENV           ENV       ENV
 *         CONT          CONT      CONT
 *         temps         temps     temps
 *                       AM        AM
 *                       result    result
 *********************************************/
struct closure {
	PC pc;
	ENV env;
};

struct continuation {
	struct closure closure;
	EXPR *args;
	CONT cont;
	EXPR temps[NUM_TEMPS];
};

struct am {
	struct continuation cont;
	AM fail;
	EXPR result;
};

union expr {
	struct env env;
	struct closure closure;
	struct continuation continuation;
	struct am am;
	PC pc;
};
