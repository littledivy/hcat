// ASCII Color codes
#define BLACK "\e[0;30m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN "\e[0;36m"
#define WHITE "\e[0;37m"
#define reset "\e[0m"


#define LOG_GREEN(X) printf("%s%s%s", GREEN, X ,reset)
#define LOG_RED(X) printf("%s%s%s", RED, X, reset)
#define LOG_YELLOW(X) printf("%s%s%s", YELLOW, X, reset)
#define LOG_BLUE(X) printf("%s%s%s", BLUE, X, reset)
#define LOG_WHITE(X) printf("%s%s%s", WHITE, X, reset)
