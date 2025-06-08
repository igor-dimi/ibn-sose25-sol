NR := 01
TEAM := G19-$(NR)-Kirchner-Dimitrov-Gül-Jorany
NAME := $(TEAM)
DIR := /home/igord/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)


sol : _$(NR).qmd script.sh
	cp _$(NR).qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	zip -r $(NAME).zip ./*.pdf ./*.sh
	mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd


