CC = clang++
CFLAGS = -std=c++11 -Wall
LDFLAGS = -lncurses

SRCDIR = ucheba
BUILDDIR = build
TARGET = MapGenerator

SRCEXT = cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@mkdir -p $(@D)
	$(CC) $^ -o $(TARGET) $(LDFLAGS)

-include $(DEPS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling $<..."
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

clean:
	@echo "Cleaning..."
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean

