/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:12:27 by tcali             #+#    #+#             */
/*   Updated: 2025/01/09 16:22:35 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int ac, char **av)
{
    int     fd;
    char    *line;

    // Vérifie si un fichier a été passé en argument
    if (ac != 2)
    {
        printf("Usage: %s <filename>\n", av[0]);
        return (1);
    }

    // Ouvre le fichier en lecture seule
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    // Lecture et affichage ligne par ligne
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // Affiche chaque ligne (inclut le \n si présent)
        free(line);         // Libère la mémoire allouée par get_next_line
    }

    // Ferme le fichier
    close(fd);
    return (0);
}
