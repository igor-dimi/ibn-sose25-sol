PROGS := a2.1 a2.2 test
NR := 02
TEAM := G19-$(NR)-Kirchner-Dimitrov-Gül-Jorany
NAME := $(TEAM)
DIR := /home/igord/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)

all: $(PROGS)


sol : _$(NR).qmd 
	cp _$(NR).qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	# zip -r $(NAME).zip ./*.pdf ./*.sh
	# mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd

