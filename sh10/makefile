NR := 10
TEAM := G19-$(NR)-Kirchner-Dimitrov-Gül-Jorany
NAME := $(TEAM)
DIR := ~/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)

# all: $(PROGS)


sol : _$(NR).qmd 
	cp _$(NR).qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	# zip -r $(NAME).zip ./$(NAME).pdf ./*.txt ./*.py
	# mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd

