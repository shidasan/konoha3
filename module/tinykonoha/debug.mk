PACKAGES = ../../package/konoha.float/float_glue.o

UNAME = tinykonoha
DEBUG_CC = gcc
DEBUG_CFLAGS = -g2 -I../../include -I. -I../tinyvm/

all : $(UNAME)

$(UNAME): $(PACKAGES) $(UNAME).o
	$(DEBUG_CC) $(OBJS) float_glue.o $(UNAME).o -o $(UNAME) $(DEBUG_CFLAGS) -DK_USING_TINYVM=1

$(UNAME).o: $(UNAME).c
	$(DEBUG_CC) $(UNAME).c -c $(DEBUG_CFLAGS) -DK_USING_TINYVM=1

$(PACKAGES): %.o: %.c
	$(DEBUG_CC) -c $(DEBUG_CFLAGS) $< -DK_USING_TINYVM=1
