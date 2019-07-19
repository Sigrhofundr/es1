#include <iostream>
#include "StringBuffer.h"

int main() {

    StringBuffer s1("Hello");
    StringBuffer s2("world");

    StringBuffer s3("Ciao");

    s1.append(" ");
    s1.append(s2);
    printf(s1.c_str());

    s1.set("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
           "do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
    s1.append("\n");
    printf("%zu",s1.size()); //124
    s2.clear();
    for(int i=0; i<10; i++)
        s2.insert(s1, 0);

    printf(s2.c_str()); //Lorem ipsum * 10
    printf("%zu",s2.size()); //1240

    /* test, stampa ma c'è il problema che la dimensione era più grande e bisognerebbe sistemarlo
    s2.clear();
    s2 = s3;
    printf(s2.c_str());
    */
    return 0;
}