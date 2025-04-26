NR := 01
TEAM := Dimitrov_Gül_Blatt
NAME := $(TEAM)$(NR)
DIR := /home/igord/Seafile/HD-Informatik/SS25/IBN/sol/$(NR)


sol : $(NR).qmd script.sh
	cp 01.qmd $(NAME).qmd
	quarto render $(NAME).qmd --to pdf 
	cp $(NAME).pdf $(DIR)
	zip -r $(NAME).zip ./*.pdf ./*.sh
	mv *.zip $(DIR)
	rm $(NAME).pdf $(NAME).qmd


