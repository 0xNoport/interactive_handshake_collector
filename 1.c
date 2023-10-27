#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	setuid(0);
	setgid(0);
	system("/bin/bash -pc \"airmon-ng start wlan1\"");
}
