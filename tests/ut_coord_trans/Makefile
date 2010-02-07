CC=gcc
RM=rm -f
INCDIR=../../
CFLAGS=-I$(INCDIR)
LDFLAGS=-lm
DEPS=$(INCDIR)coordinate-system.h

UNIT_TEST_SOURCES=ut_coord_trans.c
SOURCES=$(UNIT_TEST_SOURCES) \
  $(INCDIR)coordinate-system.c
TARGET=ut_coord_trans

OBJS=$(SOURCES:%.c=%.o)

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJS)

.PHONY: clean

clean:
	$(RM) *.o *~ core $(TARGET) 

check: $(TARGET)
	@./$(TARGET)
