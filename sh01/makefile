NR := 01
TEAM := G19-$(NR)-Kirchner-Dimitrov-Gül-Jorany
NAME := $(TEAM)
DIR := /home/igord/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)


sol : $(NR).qmd script.sh
	cp 01.qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	zip -r $(NAME).zip ./*.pdf ./*.sh
	mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd


