#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	mc;
	int	n;

	i = 0;
	mc = 1;
	n = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	while ((nptr[i] == '-' || nptr[i] == '+') && ft_isdigit(nptr[i + 1]))
	{
		if (nptr[i] == '-')
			mc *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		n = n * 10;
		n = n + (nptr[i] - '0');
		i++;
	}
	return (n * mc);
}

t_philo	*ph(void)
{
	static t_philo	philo;

	return (&philo);
}
