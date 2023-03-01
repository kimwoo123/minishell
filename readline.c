/* readline함수를 사용하기위한 헤더 */
# include <readline/readline.h>
/* add_history함수를 사용하기위한 헤더 */
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

int main(void)
{
/* readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 */
    char *str;
/* 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 */
    while(1)
    {
        str = readline("prompt : ");
		if (*str == 'k')
			clear_history();
		if (*str == 'n')
			rl_on_new_line();
        if (str)
            printf("%s\n", str);
        else
            break ;
        add_history(str);
        free(str);
    }
    return(0);
}
