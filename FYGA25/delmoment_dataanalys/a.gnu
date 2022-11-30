R(x) = m+k*x # Funktion för den linjära anpassningen
fit R(x) 'a.txt' using 1:2 via k, m # Anpassar funktionen R med värdena i filen a.txt


# Sätter värde på x axeln
set xlabel "Grader/C"
# Sätter värde på y axeln
set ylabel "Resistans/ohm"

# Sätter vilka värden på x axeln som ska visas i grafen
# Detta göra att man kan läsa av grafen i 0 C
set xrange[0:90]
# Första delen ritar mätvärderna som punkter
# Andra delen ritar den linjära funktionen
plot 'a.txt' using 1:2 title 'Datapunkter',\
     R(x) with lines title 'Linear adaptation'

pause mouse 