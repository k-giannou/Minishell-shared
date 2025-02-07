/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:15:45 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/06 20:52:12 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *chemin)
{
	struct stat	info;
	char		*cwd;

	if (access(chemin, F_OK) == -1)
		return (perror("Erreur : Le répertoire n'existe pas"));
	if (stat(chemin, &info) == -1)
		return (perror("Erreur lors de l'accès aux informations du répertoire"));
	if (!S_ISDIR(info.st_mode))
		return (ft_fprintf(stderr, "Erreur : Ce n'est pas un répertoire\n"));
	if (chdir(chemin) == -1)
		return (perror("Erreur lors du changement de répertoire"), -1);
	cwd = getenv("PWD");
	if (cwd)
		setenv("PWD", chemin);
	printf("Répertoire changé avec succès : %s\n", chemin);
}
