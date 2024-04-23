CC = mpic++
CFLAGS = -std=c++11 -O2
BINDIR = bin

SRCS = main.cpp island.cpp
OBJS = $(patsubst %.cpp,$(BINDIR)/%.o,$(SRCS))

TARGET = $(BINDIR)/island_simulation

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BINDIR)/%.o: %.cpp | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(TARGET)
