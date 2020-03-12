CC       = mpicc
#CC       = mpicxx #compiler for work
CFLAGS   = -O3 #level of optimization
LIBS    = -lpthread #load library threads
LDFLAGS = -static-intel #load libs
OBJS    = main.o \
	measure_time.o# creating object file
SRCS    = main.c \
	measure_time.c  # source file
TARGET  = main # executing file

$(TARGET): $(OBJS)
	$(CC) -openmp -o $@ $(LDFLAGS) $(OBJS) $(LIBS) $<

%.o: %.c
	$(CC) $(CFLAGS) -openmp -c $<

clean:
	 rm -f $(TARGET) $(OBJS)

