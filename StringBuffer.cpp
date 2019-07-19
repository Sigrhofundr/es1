#include "StringBuffer.h"

//costruisce un oggetto con un buffer di dimensione iniziale ragionevole,inizializzandolo con il terminatore di stringa
StringBuffer::StringBuffer()
{
    bufLength = DEF_SIZE;
    buf = new char[DEF_SIZE];
    length = 0;
}
//costruisce un oggetto allocando un buffer di dimensione sufficiente a contenere l’array di caratteri str (compreso il terminatore finale) e segnando
//correttamente il numero di caratteri effettivamente utilizzati
StringBuffer::StringBuffer(const char *str) {
    int l = strlen(str);
    bufLength = (l/ DEF_SIZE+1) * DEF_SIZE;
    buf = new char[bufLength];
    strcpy_s(buf, bufLength, str);
    length = l;
}

//costruisce un oggetto con un buffer iniziale di dimensione adeguata a contenere i caratteri contenuti nell’oggetto sb e inizializzato con
//una copia di tali caratteri
StringBuffer::StringBuffer(const StringBuffer &sb) {
    bufLength = sb.bufLength;
    length = sb.length;
    buf = new char[sb.bufLength];
    strcpy_s(buf, bufLength, sb.buf);
}

StringBuffer::~StringBuffer() {
    delete[] buf;
}

//assegna, al buffer corrente, il contenuto del buffer sb
StringBuffer& StringBuffer::operator=(const StringBuffer &sb) {
    if(this != &sb) {
        delete[] this->buf;
        this->buf = nullptr;
        this->length = sb.length;
        //test
        this->bufLength = sb.bufLength;
        this->buf = new char[bufLength];
        memcpy(this->buf, sb.buf, this->length);
        /*
        this->buf = new char[length];
        memcpy(this->buf, sb.buf, length);
         */
    }
    return *this;
}

//restituisce il numero di caratteri utilizzati dalla stringa memorizzata nel buffer;
size_t StringBuffer::size() {
    return length;
}

//restituisce la dimensione totale del buffer di caratteri attualmente allocato;
size_t StringBuffer::capacity() {
    return bufLength;
}

//porta a 0 il numero di caratteri utilizzati;
void StringBuffer::clear() {
    this->length = 0;
    strcpy_s(this->buf,this->bufLength, "");
}

/*inserisce il contenuto s nella posizione pos del buffer; o se pos è maggiore di size (), inserisce spazi tra size ()
 * e pos, riallocando il buffer se necessario*/
void StringBuffer::insert(const char *str, size_t pos) {
    int str_l = strlen(str);
    if(length + str_l >= bufLength)
    {
        int newSize = length + str_l;
        int newBufLength = (newSize/ DEF_SIZE+1)* DEF_SIZE;
        char *newBuf = new char[newBufLength];
        strcpy_s(newBuf, bufLength, buf);

        delete[] buf;
        buf = newBuf;
        bufLength = newBufLength;
        length = strlen(buf);
    }
    if ( pos > length)
    {
        //insert spaces
        for(size_t i = length; i < pos; i++)
        {
            buf[i] = ' ';
        }

        buf[pos] = 0;
    }else {
        // move forward the chars starting from pos
        for (int i = length; i >= (signed) pos; i--)
            buf[str_l + i] = buf[i];
    }

    //insert string
    for(int i = 0; i < str_l; i++)
        buf[i + pos] = str[i];

    length = strlen(buf);
}

/*inserisce il contenuto di sb nella posizione pos del buffer; o se pos è maggiore di size (),
 * inserisce spazi tra size () e pos, riallocando il buffer se necessario*/
void StringBuffer::insert(const StringBuffer &sb, size_t pos) {
    char *str = sb.buf;
    insert(str, pos);
}

//aggiunge i caratteri contenuti in str in coda a quelli
//memorizzati nel buffer, riallocando il buffer se necessario;
void StringBuffer::append(const char *str) {

    int pos = strlen(buf);
    insert(str,pos); //la riallocazione eventuale la fa l'insert
}

//aggiunge i caratteri contenuti nell’oggetto sb in
//coda a quelli memorizzati nel buffer, riallocando il buffer se necessario;
void StringBuffer::append(const StringBuffer &sb) {
    char *str = sb.buf;
    append(str);
}

//restituisce un puntatore in sola lettura al buffer interno opportunamente terminato con un "\0";
const char* StringBuffer::c_str() {
    return buf;
}

//sostituisce la stringa memorizzata nel buffer con il contenuto
//dell’array s , riallocando il buffer se necessario;
void StringBuffer::set(const char *str) {
    clear();
    append(str);
}

//sostituisce la stringa memorizzata nel buffer con il
//contenuto dell’oggetto s, riallocando il buffer se necessario.
void StringBuffer::set(const StringBuffer &s) {
    set(s.buf);
}

