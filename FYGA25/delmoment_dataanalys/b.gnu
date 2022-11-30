# Funktion för denhalveringstid
noll=510
N(x) = N_0*exp(-lambda*x) 
# Anpassar funktionen N med värdena i filen b.txt
fit N(x) 'b.txt' using 1:2 via N_0, lambda

# Sätter värde på x axeln
set xlabel "Tid/d"
# Sätter värde på y axeln(
set ylabel "Mängd/kg"

# definerar halverings tiden
halveringstiden = log(2)/lambda
# skriver halveringstiden till stdout 
# Första delen ritar mätvärderna som punkter
# Andra delen ritar den linjära funktionen
plot 'b.txt' using 1:2 title 'Datapunkter',\
     N(x) with lines title 'N function'

pause mouse # Väntar på musen att flyttas innan fönstret stängs