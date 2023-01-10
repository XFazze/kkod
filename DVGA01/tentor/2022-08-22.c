/*
Datavetenskap
Tentamen för DVG A01 Programmeringsteknik, 7,5hp
2022-08-22 Kl 08.15-13.15
Ansvarig lärare: Martin Blom, 054-700 17 66, 0705-583318
Tillåtna hjälpmedel: Lexikon (till/från svenska eller engelska)
Betygsgränser: 3: 25 poäng, 4: 34 poäng, 5: 42 poäng.
Ange alla antaganden. Skriv läsligt. Lycka till!

*/
void t1()
{
    /*
    1. Begrepp (5p)
    Para ihop följande termer med korrekt beskrivning. Svara med en siffra per term, ex f 12.
    a) Switch
    b) While
    c) Algoritm
    d) Parameter
    e) Syntax
    1) språkets struktur, dvs grammatiken för ett språk.
    2) språkets mening, innebörden, effekten av språkliga konstruktioner
    3) stegvis lösning, ett recept för att lösa ett problem
    4) namngivet kodblock med väldefinierade in- och utgångar
    5) resultat från funktionsanrop, en funktions utdata
    6) indata till funktion, det som skickas in vid anrop
    7) konstruktion för upprepning, ett kodblock exekveras noll eller flera gånger
    8) konstruktion för upprepning, ett kodblock exekveras en eller flera gånger
    9) konstruktion för val mellan två eller fler vägar
    10) start-funktion för ett program, den del av koden som körs först
    */
    /*
    a) 9
    b) 7
    c) 3
    d) 6
    e) 1
    */
}

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
void t2()
{
    /*
    2. Input Process Output (5p)
    a) Skriv ut tecknet X, pekaren Y och flyttalet Z m h a printf (1p)
    b) Skriv ett program som läser in två heltal från tangentbordet och som skriver ut ”rot!” om
    något av talen är en kvadratrot till det andra, annars ska inget skrivas ut. (3p)
    c) Skriv ut ett heltal T så att det ges 7 teckens plats, dvs att det fylls på med mellanslag för tal
    som är mindre än 7 siffror stora. (OBS! Detta ska enbart göras m h a printf och dess
    funktionalitet.) (1p)
    */
    // a)
    int a = 5;
    printf("X: %c Y: %p Z: %.2f\n", 'X', &a, 1.1);

    // b)
    char buffer[10];
    fgets(buffer, 10, stdin);
    strtok(buffer, "\n");
    int b = atoi(buffer);
    fgets(buffer, 10, stdin);
    strtok(buffer, "\n");
    int c = atoi(buffer);
    if(c*2==b || b*2==c){printf("rot!\n");};

    // c)
    int T = 10;
    printf("%7d\n", T);
}

void bubblesort(int* a, int s){
    int temp_copy = 0;
    int sorted = 0;
    while(!sorted){
        sorted = 1;
        for(int i=0; i<s-1;i++){
            if(a[i] > a[i+1]){
                temp_copy  = a[i];
                a[i] = a[i+1];
                a[i+1] = temp_copy; 
                sorted = 0;
            }
        }
    }
}

int sok(int* a, int size, int val){
    int res = 0;
    int found = 0;
    for(int i=0;i<size; i++){
        if(a[i]==val){
            res++;
            found =1;
        }else if(found){
            return res;
        }
    }
    return res;
}

void t3(){
    /*
    3. Sortering och sökning (5p)
    För att kunna använda binärsökning krävs det att den data man ska söka i är sorterad. För alla
    frågor nedan ska en array som är deklarerad och fylld med värden enligt nedan antas:
    int minarray[SIZE];
    fyll_med_slumpvarden(minarray, SIZE);
    a) Implementera funktionen void bubblesort(int* a, int s) för att sortera
    arrayen. Du ska också visa på ett anrop till den. (3p)
    b) Implementera en sökfunktion som räknar antalet förekomster av det sökta talet och som
    returnerar detta antal. Antag att arrayen är sorterad. int sok(int* a, int size,
    int val) (2p)
    */
    int minarray[10] = {4,3,2,1,5,6,6,8,9,10};
    // fyll_med_slumpvarden(minarray, SIZE);
    bubblesort(minarray, 10);
    for(int i = 0; i<10; i++){
        printf("%d ", minarray[i]);
    }
    int antal = sok(minarray, 10, 6);
    printf("\n antal: %d\n", antal);

}

#include <string.h>
#include <stdlib.h>
void t4(){
    /*
    4. Selektion och iteration (5p)
    Klämdagar är dagar som infaller mellan två lediga dagar, t ex mellan en röd dag och en lördag.
    Definitionen av en klämdag är i detta fall att dagen innan och dagen efter ska vara antingen en
    röd dag (helgdag eller söndag) eller en lördag. Givet en array av datum, skriv ett program som går
    igenom arrayen och som skriver ut alla klämdagar. Följande definitioner och deklarationer finns
    givna:
    typedef struct date{
    long int datum;
    char day_of_week[10];
    int is_red_day;
    }date;
    date dates[365] = get_from_calendar(2022);
    */
    // typedef struct date{
    // long int datum;
    // char day_of_week[10];
    // int is_red_day;
    // }date;
    // date dates[365] = get_from_calendar(2022);
    // if((dates[365].is_red_day || strcmp(dates[365].day_of_week, "saturday")|| strcmp(dates[365].day_of_week, "sunday"))
    // && (dates[1].is_red_day || strcmp(dates[1].day_of_week, "saturday")|| strcmp(dates[1].day_of_week, "sunday"))){
    //         printf("Kalmdag: %d", 0);
    //     }
    // for (int i=1; i<365; i++){
    //     if((dates[i-1].is_red_day || strcmp(dates[i-1].day_of_week, "saturday")|| strcmp(dates[i-1].day_of_week, "sunday"))
    //     && (dates[i+1].is_red_day || strcmp(dates[i+1].day_of_week, "saturday")|| strcmp(dates[i+1].day_of_week, "sunday"))){
    //         printf("Kalmdag: %d", i);
    //     }
    // }

}

int get_rand(int *array, int s, int min_val){
    // printf("ss %d", s);
    int num, unique = 0 ;
    while (!unique){
        num = rand()%15 + min_val;
        unique = 1;
        for(int i=0; i<s;i++){
            // printf("Checking i:%d, %d %d\n",i, array[i], num);
            if(num==array[i]){
                unique = 0;
                break;
            }
        }
    }
    return num;
};

#include <time.h>
void t5(){
    /*
    5. Bingo (Arrayer, slump, selektion, iteration) (5p)
    Bingo är ett nummerspel där du köper en bong (lottsedel) på vilken 25
    slumpmässiga siffror mellan 1-75 är placerade i fem kolumner med fem
    rader vardera där tal mellan 1 och 15 hamnar i kolumn 1, tal mellan 16
    och 30 i kolumn 2 och så vidare. Skriv ett program som skapar och
    skriver ut en bingobong. Funktionaliteten för att skapa en bong skall
    vara i en egen funktion. Inga dubbletter tillåts.
    */  
    typedef struct bingo {
        int col1[5];
        int col2[5];
        int col3[5];
        int col4[5];
        int col5[5];
    } bingo;
    
    bingo board;

    srand(time(NULL));
    for(int i=0; i<5;i++){
        board.col1[i] = get_rand(board.col1, i, 1);
        board.col2[i] = get_rand(board.col2, i, 16);
        board.col3[i] = get_rand(board.col3, i, 31);
        board.col4[i] = get_rand(board.col4, i, 46);
        board.col5[i] = get_rand(board.col5, i, 61);
        printf("row %d: %2d %2d %2d %2d %2d\n", i, board.col1[i], board.col2[i], board.col3[i], board.col4[i], board.col5[i]);
    }
}
int sum_ascii(char *string, int s){
    int sum = 0;
    for(int i=0; i <s; i++){
        sum += string[i];
    }
    return sum;
}
int sum_digits(int num){
    char str[100];
    int size = sprintf(str, "%d", num);
    strtok(str, "\n");
    int sum=0;
    for(int i=0; i< size;i++){
        sum+= str[i]-48;
    }
    printf("hello%d",num);
    if(sum>9){
        sum = sum_digits(sum);
    }
    return sum;
}
void t6(){
    /*
    6. Kodning, ASCII-tabellen och aritmetiska operatorer (5p)
    Din kompis gillar numerologi, dvs att nummer har mening. Kompisen hävdar att om man
    summerar ihop alla ASCII-värden för en sträng och sedan summerar de ingående siffrorna i
    summan och upprepar detta tills man får ett ental, att detta ental säger något om strängen.
    a) Skriv en funktion sum_ascii som tar emot en sträng och som returnerar summan av
    ASCII-värdena för alla tecken i strängen (utom radslut). (2p)
    b) Skriv en funktion sum_digits som tar emot ett heltal och som returnerar en entalssumma
    av siffrorna som heltalet består av. Ex: Talet 123 har summa 1+2+3 = 6 à returvärde 6. Talet
    56 har summa 5+6 = 11 à 1+1 = 2 àreturvärde 2 (2p)
    c) Skriv kod i main som läser in en sträng från användaren och anropar funktionerna i a) och b)
    och presenterar entalssumman av strängen. (1p)
    */
    char strong[100];
    fgets(strong, 100, stdin);
    strtok(strong,"\n");
    printf("inp[ut]:%s:\n", strong);
    int sum_asc = sum_ascii(strong, strlen(strong));
    printf("Sum asc: %d\n", sum_asc);
    int single_dig = sum_digits(sum_asc);
    printf("Sum dig: %d\n", single_dig);


}

void large_letters(char *string, int s){
    if(64 < string[0] &&string[0]<91){
        printf("large letter  %c\n", string[0]);
    };
    s--;
    string+=1;
    if(s!=0){
        large_letters(string, s);
    }
}
int sum_letters(char *string, int s){
    int sum =0;
    sum += string[0];
    s--;
    string++;
    if(s!= 0){
        sum += sum_letters(string, s);
    };
    return sum;

}
void t7(){
    /*
    7. Funktioner och rekursion (5p)
    Många funktioner är möjliga att skriva både iterativt och rekursivt. Givet följande:
    char strang[SIZE];
    int antal_tecken = anvandar_input(strang);
    a) Skriv en iterativ funktion som skriver ut alla versaler (stora bokstäver) i strängen strang (1p)
    b) Skriv motsvarande rekursiva funktion (2p)
    c) Skriv en rekursiv funktion som summerar alla ASCII-värden för alla tecken i strängen strang
    och returnerar summan. (2p)
    */
    char strang[10];
    fgets(strang, 10, stdin);
    strtok(strang, "\n");
    // int sum = 0;
    // for(int i=0; i<strlen(strang)+1; i++){
    //     if(64 < strang[i] && strang[i]<91 ){
    //         printf("large letter  %c\n", strang[i]);
    //     }
    // }
    large_letters(strang, strlen(strang));
    int a = sum_letters(strang, strlen(strang));
    printf("asd%d", a);

    // printf("Sum large letters: %d", sum);
}

void t8(){
    /*
    8. Pekare och minneshantering (5p)
    Rita bilder och förklara vad som händer i nedanstående uppgift. Om någon minnescell
    innehåller obestämda värden (skräp) kan du rita ett ’?’ på̊ lämpligt ställe i bilden.
    #include <stdio.h>
    #include <string.h>
    int main()
    {
    char s[] = "Harry";
    char *x, *y;
    y = s + 2; //r
    x = y - 2; //h
    *x = *s + 5; 
    *y = 'c';
    *(y+1) -= strlen(s)+2;
    x = y + 2;
    *x = *x=='y'?'!':'a';
    printf("s=%s\n", s);
    }
    */
    char a[]= "aa";
    for(int i=0; i<2; i++){
    printf("sel %li", strlen(a));
    };
}


int main()
{
    t8();
}