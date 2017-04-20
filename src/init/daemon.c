void	init_daemon(void)
{
	pid_t	pid;

	// Ignore signals
	if ((pid = fork()) > 0)
		exit(0)
	else if (pid < 0)
		ERROR("Fork failed");
}
