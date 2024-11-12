/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:15:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/06 10:50:54 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int call_cmd_pwd() // pwd 명령어
{
    char    pwd[PATH_MAX];

    if (getcwd(pwd, sizeof(pwd)) != NULL)
        printf("%s\n", pwd);
    else
    {
        perror("pwd error");
        return (1);
    }
    return (0);
}

int call_cmd_cd() // cd 명령어 함수
{
    char    *new_dir;

    new_dir = "/home/junseok";
    if (chdir(new_dir) != 0)
    {
        perror("cd error");
        return (1);
    }
    return (0);
}

int call_cmd_ls() // ls 명령어 함수
{
    DIR             *cur_dir;
    struct  dirent   *entry;
    struct  stat    buf;
    char    pwd[PATH_MAX];

    getcwd(pwd, sizeof(pwd));
    cur_dir = opendir(pwd);
    if (cur_dir == NULL)
    {
        perror("opendir fail");
        return (1);
    }
    while ((entry = readdir(cur_dir)) != NULL)
    {
        lstat(entry->d_name, &buf);

        if (S_ISREG(buf.st_mode)) // 파일만 출력
            printf("%s  ", entry->d_name);
        else if (S_ISDIR(buf.st_mode)) // 디렉토리만 출력
            printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(cur_dir);
    return (0);
}

int main()
{
    call_cmd_pwd();
    call_cmd_ls();
    //call_cmd_cd();
    //call_cmd_pwd();
    //call_cmd_ls();
    return (0);
}