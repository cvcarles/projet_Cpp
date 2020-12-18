CC = g++ 																		# le compilateur à utiliser
CFLAGS = -std=gnu++11															# les options du compilateur
LDFLAGS = 																		# les options pour l’éditeur de liens
SRC = Client.cpp FileChainee.cpp Guichet.cpp Poste.cpp main.cpp					# les fichiers sources
PROG = main 																	# nom de l’exécutable
OBJS = $(SRC:.cpp=.o) 															# les .o qui en découlent
.SUFFIXES: .c .o 																# lien entre les suffixes

all: $(PROG) 																	# étapes de compilation et d’édition de liens
# $@ la cible $^ toutes les dépendances

										
$(PROG): $(OBJS)
		$(CC) -o $@ $^ $(LDFLAGS)

FileChainee.o: FileChainee.hpp			# le lien entre .o et .c # $< dernière dépendance
main.o: FileChainee.hpp
										
%.o: %.c
		$(CC) $(CFLAGS) -c $<

.PHONY: clean # pour faire propre
