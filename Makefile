CC = mpic++
CFLAGS = -std=c++11 -O2
BINDIR = bin

SRCS = src/main.cpp src/island.cpp
OBJS = $(patsubst src/%.cpp,$(BINDIR)/%.o,$(SRCS))

TARGET = $(BINDIR)/island_simulation

all: $(TARGET)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(BINDIR)/%.o: src/%.cpp | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(TARGET)
