#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	setuid(0);
	setgid(0);
	system("/bin/bash -pc \"airmon-ng stop wlan1mon\"");
	return 0;
}
