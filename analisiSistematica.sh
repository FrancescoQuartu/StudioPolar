#!/bin/bash

#in questo file lancio l'eseguibile "AnalisiSingoloFile.C" per ogni
#file.root che trovo nella cartella impostata
#assicurati esista e sia stato eseguito il file AnalisiSingoloFile.C
#gli output sono mandati nello stesso file Rate.txt
#il quale è creato proprio all'inizio di questo programma

#per esempio lancia con:
#./AnalisiSingoloFile /mnt/c/Users/casa/Desktop/Tesi/StudioPolar/POLA-01/*/*.root

#creo il file Rate.txt
echo "Rate1	Rate2	 Latitudine" > Rate.txt

echo "Numero di file da analizzare: $#"

#primo argomento: nome cartella
#tutti gli altri sono i nomi dei file

for nomeFile in $@
do
	./AnalisiSingoloFile.exe $nomeFile
done

