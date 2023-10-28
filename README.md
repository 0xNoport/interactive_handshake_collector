# Interactive Handshake Collector Script in C

<br>

## Important:

**You have to modify the script. For example does the first script set wlan1 into monitor mode. If you only have wlan0, then you have to modify the script.**

<br>

## Usage:

./1 => **Puts wlan0 into monitor mode**

<br>

./2 => **List available wifi networks and enter numer to start capturing handshake and deauthenticating**

<br>

./3 => **Usually you dont use this manually, you just use ./1 once, then ./2 for each network and ./4 to set wifi card out of monitor mode**

<br>

./4 => **Delete the newly created interface, so stop monitor mode**

<br>

## QUESTION: 

**Why in C? Why not just use bash, especially because you use linux binaries instead of native functions from linux api?!**

<br>
<br>

## ANSWER: 

**Because i like C and wanted to use C, it's not about efficiency, especially because i call bash, i could have done the same just in bash, but it's not as much fun. I used this project to get used to some basic functions in C.**


