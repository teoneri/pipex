/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:03:51 by mneri             #+#    #+#             */
/*   Updated: 2023/04/20 13:03:53 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wordcount(const char *str, char c)
{
    int count = 0;
    int flag = 0;

    while (*str)
    {
        if (*str != c && flag == 0)
        {
            flag = 1;
            count++;
        }
        else if (*str == c)
        {
            flag = 0;
        }
        str++;
    }

    return count;
}

static char *stralloc(const char *str, int start, int finish)
{
    char *word;
    int i = 0;

    word = malloc((finish - start + 1) * sizeof(char));
    while (start < finish)
    {
        word[i++] = str[start++];
    }
    word[i] = '\0';
    return (word);
}

char **ft_cmd_split(const char *s, char c)
{
    size_t i = 0;
    int l = -1;
    size_t j = 0;
    char **split;
    int in_quotes = 0;

    split = malloc(sizeof(char *) * (wordcount(s, c) + 1));
    if (!split || !s)
    {
        return (NULL);
    }
    while (i <= ft_strlen(s))
    {
        if (s[i] == '\"' || s[i] == '\'')
        {
            if (!in_quotes)
            {
                l = ++i;
                in_quotes = s[i - 1];
            }
            else if (in_quotes == s[i])
            {
                split[j++] = stralloc(s, l , i );
                l = -1;
                in_quotes = 0;
            }
        }
        else if (s[i] != c && l < 0)
        {
            l = i;
        }
        else if ((s[i] == c || s[i] == '\0') && l >= 0 && !in_quotes)
        {
            split[j++] = stralloc(s, l, i);
            l = -1;
        }
        i++;
    }
    split[j] = 0;
    return (split);
}