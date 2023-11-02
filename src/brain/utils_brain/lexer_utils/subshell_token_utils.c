#include "../include/minishell.h"

bool  token_is_subshell(char *token)
{
    if (token[0] == '(' || ft_strlen(token, ')') != NULL)
      return (true);
  return (false);
}

int  get_subshell_count(char **token, int i)
{
    int count;
    int opened;

    count = 0;
    opened_brackets = 0;
    while (tokens[i])
    {
        if (ft_strchr(token[i]), '('))
        {
            opened_brackets++;
            count++;
        }
        else if (ft_strchr(token[i], ')'))
        {
            opened_brackets--;
            count--;
        }
        if (opened_brackest == 0)
            break ;
      i++;
    }
    return (count);
} 

int  go_to_end_subshell(char **token, int i)
{
    int subshell_count;

    subshell_count = get_subshell_count(token, i);
    while (token[i] && subshell_count)
    {
        if (token_is_subshell(token[i]))
            subshell_count--;
        i++;
    }
    return (i);
}

char  *get_end_of_subshell(char **token, int *i, char *sub_token)
{
    char  *tmp;
    int    sub_len;

    sub_len = ft_strrchr(token[*i], ')') - token[*i];
    tmp = ft_substr(token[*i], 0, sub_len + 1);
    sub_token = ft_append(&sub_token, tmp);
    free(tmp);
    tmp = token[*i];
    token[*i] = ft_substr(tmp, sub_len + 1, ft_strlen(token[*i]));
    free(tmp);
    return (sub_token);
}






















