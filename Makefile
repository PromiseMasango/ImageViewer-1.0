all:
	gcc imageviewer.c -o imageviewer `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` -w
