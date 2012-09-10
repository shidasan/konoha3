PKGS = ../../package/konoha.float/float_glue\
	   ../../package/konoha.array/array_glue\

OBJS = float_glue.o\
	   array_glue.o\

UNAME = tinykonoha
DEBUG_CC = gcc
DEBUG_CFLAGS = -g2 -I../../include -I. -I../tinyvm/

all : $(UNAME)

$(UNAME): $(PKGS) $(UNAME).o
	$(DEBUG_CC) $(OBJS) $(UNAME).o -o $(UNAME) $(DEBUG_CFLAGS) -DK_USING_TINYVM=1

$(UNAME).o: $(UNAME).c
	$(DEBUG_CC) $(UNAME).c -c $(DEBUG_CFLAGS) -DK_USING_TINYVM=1

$(PKGS): %: %.c
	$(DEBUG_CC) -c $(DEBUG_CFLAGS) $< -DK_USING_TINYVM=1
