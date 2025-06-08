NR := 04
TEAM := G19-$(NR)-Kirchner-Dimitrov-Gül-Jorany
NAME := $(TEAM)
DIR := /home/igord/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)

# all: $(PROGS)


sol : _$(NR).qmd A3/*.c A3/Makefile
	cp _$(NR).qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	zip -r $(NAME).zip ./$(NAME).pdf ./A3
	mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd

