filename= 'distance_between_lasers_full.txt'
D(x) = a*x**b
fit D(x) filename using 1:2 via a, b


set xlabel "Avstand mellan laserna/m"
set ylabel "Tid/s"

#set xrange[0:90]
plot filename using 1:2 title 'Datapunkter',\
     D(x) with lines title 'Dator anpassning'

pause mouse 