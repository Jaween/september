# Compiler and linking
LIBS = -lSDL2 -lSDL2_image -lOpenCL
FLAGS = -I $(DEPDIR) -std=c++11 # -fsanitize=address
CXX = clang++

# Binary executable output
TARGETDIR = bin
TARGET = september

# Source files
SRCDIR = src
SRCNAMES = main.cc algorithm.cc manager.cc util.cc graphics_factory.cc graphics_factory_sdl.cc image.cc image_sdl.cc window.cc window_manager.cc window_manager_sdl.cc window_sdl.cc

# Header files
DEPDIR = include

# Object files
OBJDIR = build
OBJ = $(addprefix $(OBJDIR)/,$(SRCNAMES:%.cc=%.o))

# Compilation rules
$(TARGETDIR)/$(TARGET) : $(OBJ)
	@mkdir -p $(TARGETDIR)
	$(CXX) $(FLAGS) -o $@ $(LIBS) $^

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c -o $@ $<

# Generated file clean up
clean :
	rm -rf $(OBJDIR)/*.o $(TARGETDIR)/*
