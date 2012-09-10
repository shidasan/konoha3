PKGS = ../../package/konoha.float/float_glue\
	   ../../package/konoha.array/array_glue\
	   ../../package/konoha.nxt/nxt_glue\

OBJS = float_glue.o\
	   array_glue.o\
	   nxt_glue.o\

UNAME = tinykonoha
HEADERS = datatype.h\
		  ../tinyvm/tinyvm.h\
		  ../tinyvm/tinyvm_gen.h\
		  
DEBUG_CC = gcc
#DEBUG_CFLAGS = -g0 -Os -I../../include -I. -I../tinyvm/
DEBUG_CFLAGS = -g2 -I../../include -I. -I../tinyvm/

all : $(UNAME)

$(UNAME): $(PKGS) $(UNAME).o
	$(DEBUG_CC) $(OBJS) $(UNAME).o -o $(UNAME) $(DEBUG_CFLAGS) -DK_USING_TINYVM=1

$(UNAME).o: $(UNAME).c $(HEADERS)
	$(DEBUG_CC) $(UNAME).c -c $(DEBUG_CFLAGS) -DK_USING_TINYVM=1

$(PKGS): %: %.c
	$(DEBUG_CC) -c $(DEBUG_CFLAGS) $< -DK_USING_TINYVM=1
