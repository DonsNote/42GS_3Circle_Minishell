/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:15:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 18:48:19 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	call_cmd_pwd(void) // pwd 명령어 => 수정
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
	{
		perror("pwd error");
		return (1);
	}
	return (0);
}

int	call_cmd_cd(void) // cd 명령어 함수 => 수정
{
	char	*new_dir;

	new_dir = "/home/junseok";
	if (chdir(new_dir) != 0)
	{
		perror("cd error");
		return (1);
	}
	return (0);
}

int	call_cmd_ls(void) // ls 명령어 함수 => 수정
{
	DIR				*cur_dir;
	struct dirent	*entry;
	struct stat		buf;
	char			pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	cur_dir = opendir(pwd);
	if (cur_dir == NULL)
	{
		perror("opendir fail");
		return (1);
	}
	entry = readdir(cur_dir);
	while (entry != NULL)
	{
		lstat(entry->d_name, &buf);
		if (S_ISREG(buf.st_mode))
			printf("%s  ", entry->d_name);
		else if (S_ISDIR(buf.st_mode))
			printf("%s  ", entry->d_name);
	}
	printf("\n");
	closedir(cur_dir);
	return (0);
}
