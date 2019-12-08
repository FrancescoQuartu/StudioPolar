#!/bin/bash

#in questo file lancio l'eseguibile "AnalisiSingoloFile.C" per ogni
#file.root che trovo nella cartella impostata
#assicurati esista e sia stato eseguito il file AnalisiSingoloFile.C
#gli output sono mandati nello stesso file Rate.txt
#il quale è creato proprio all'inizio di questo programma

#per esempio lancia con:
#./analisiSistematica.sh RatePOLA-01.txt /mnt/c/Users/casa/Desktop/Tesi/StudioPolar/POLA-01/*/*.root

#creo il file Rate.txt
echo "#Rate1	ErrRate1	Rate2	ErrRate2	Latitudine	TempOut	Longitudine	Altitudine	ChiQuadro	Pressione	NumSatelliti	Giorno	Mese	Anno" > $1


echo "Numero di file da analizzare: $#"

#primo argomento: nome file output
#tutti gli altri sono i nomi dei file

for nomeFile in $@
do
  if [[ $1 != $nomeFile ]] ; then
    ./AnalisiSingoloFile.exe $nomeFile $1
  fi
done

