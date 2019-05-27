AUTOGL_HEADER_DIR = ../lib
AUTOGL_LIBRARY_DIR = ../lib

INCLUDES = -I$(AUTOGL_HEADER_DIR)
LIBS = -L$(AUTOGL_LIBRARY_DIR) -lautogl -lm -lX11

# invoke AutoGL config to add system-level libraries for GUI and graphics
LIBS += `${AUTOGL_LIBRARY_DIR}/advautogl-config`


CXX = g++

CXXFLAGS = $(INCLUDES) -g -Wall

LDFLAGS = $(LIBS) -lm

.c.o:
	$(CXX) -c $< $(CXXFLAGS)

OBJ =   main.o Visualize.o Drawer.o Pedestrian.o Calculation.o Vector2D.o Route.o Wall.o Carer.o CareRecipient.o

all : traffic

traffic : $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

clean :
	rm -f *.o *.exe $(FILES)

check-syntax :
	case $(CHK_SOURCES) in \
	*.cpp) \
		$(CXX) $(CXXFLAGS) -pedantic -fsyntax-only $(CHK_SOURCES) ; \
		;; \
	*) \
		;; \
	esac
