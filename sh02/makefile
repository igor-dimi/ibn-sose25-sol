PROGS := a2.1 a2.2 test threads_example single_thread
NR := 02
TEAM := G19-$(NR)-Kirchner-Dimitrov-Gül-Jorany
NAME := $(TEAM)
DIR := /home/igord/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)

all: $(PROGS)


sol : _$(NR).qmd threads_example.c
	cp _$(NR).qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	zip -r $(NAME).zip ./$(NAME).pdf ./threads_example.c ./beispiel_ausgabe.txt
	mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd

