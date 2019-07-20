#include "StringBuffer.h"

//costruisce un oggetto con un buffer di dimensione iniziale ragionevole,inizializzandolo con il terminatore di stringa
StringBuffer::StringBuffer()
{
    StringBuffer::buffer = new char[DEF_SIZE];
    memcpy(StringBuffer::buffer, "\0", StringBuffer::buffer_size);
    StringBuffer::buffer_size = StringBuffer::DEF_SIZE;
    StringBuffer::n_char = 0;
}
//costruisce un oggetto allocando un buffer di dimensione sufficiente a contenere l’array di caratteri str (compreso il terminatore finale) e segnando
//correttamente il numero di caratteri effettivamente utilizzati
StringBuffer::StringBuffer(const char *str) {
    if(str != nullptr)
    {
        StringBuffer::buffer_size = strlen(str);
        StringBuffer::buffer = new char[StringBuffer::buffer_size];
        memcpy(StringBuffer::buffer, str, StringBuffer::buffer_size);
        memcpy(StringBuffer::buffer + StringBuffer::buffer_size, "\0", sizeof(char));
        StringBuffer::n_char = StringBuffer::buffer_size;
    }

}

//costruisce un oggetto con un buffer iniziale di dimensione adeguata a contenere i caratteri contenuti nell’oggetto sb e inizializzato con
//una copia di tali caratteri
StringBuffer::StringBuffer(const StringBuffer &sb) {
    buffer_size = sb.buffer_size;
    StringBuffer::buffer = new char[buffer_size];
    memcpy(buffer, sb.buffer, buffer_size);
}

StringBuffer::~StringBuffer() {
    delete[] buffer;
}

//assegna, al buffer corrente, il contenuto del buffer sb
StringBuffer& StringBuffer::operator=(const StringBuffer &sb) {
    if(this != &sb) {
        delete[] this->buffer;
        this->buffer = nullptr;
        //test
        this->buffer_size = sb.buffer_size;
        this->buffer = new char[buffer_size];
        memcpy(this->buffer, sb.buffer, this->buffer_size);
        /*
        this->buf = new char[length];
        memcpy(this->buf, sb.buf, length);
         */
    }
    return *this;
}

//restituisce il numero di caratteri utilizzati dalla stringa memorizzata nel buffer;
size_t StringBuffer::size() {
    return StringBuffer::n_char;
}

//restituisce la dimensione totale del buffer di caratteri attualmente allocato;
size_t StringBuffer::capacity() {
    return buffer_size;
}

//porta a 0 il numero di caratteri utilizzati;
void StringBuffer::clear() {
    /*
    this->length = 0;
    strcpy_s(this->buf,this->bufLength, "");*/
    StringBuffer::n_char = 0;
}

/*inserisce il contenuto s nella posizione pos del buffer; o se pos è maggiore di size (), inserisce spazi tra size ()
 * e pos, riallocando il buffer se necessario*/
void StringBuffer::insert(const char *str, size_t pos) {
    if(str != nullptr) {
        if(pos <= n_char)
        {
            size_t temp = strlen(str);
            if( pos + strlen(str) < buffer_size)
            {
                memcpy(buffer + pos, str, temp);
                memcpy(buffer + pos + temp, "\0", sizeof(char));
                n_char = pos + temp;
            } else {
                char* tmp = new char[buffer_size];
                memcpy(tmp, buffer, buffer_size);
                delete [] buffer;
                buffer = new char[StringBuffer::size() + temp];
                memcpy(buffer, tmp, buffer_size);
                memcpy(buffer + pos, str, temp);
                memcpy(buffer + pos + temp, "\0", sizeof(char));
                n_char = pos + temp;
                buffer += temp;
                delete[] tmp;
            }
        }
        /*
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
         */
    }

}

/*inserisce il contenuto di sb nella posizione pos del buffer; o se pos è maggiore di size (),
 * inserisce spazi tra size () e pos, riallocando il buffer se necessario*/
void StringBuffer::insert(const StringBuffer &sb, size_t pos) {
    if(pos <= n_char)
    {
        if( pos + sb.n_char < buffer_size)
        {
            memcpy(buffer + pos, sb.buffer, sb.n_char);
            memcpy(buffer + pos + sb.n_char, "\0", sizeof(char));
            n_char = pos + sb.n_char;
        } else {
            char* tmp = new char[buffer_size];
            memcpy(tmp, buffer, buffer_size);
            delete[] StringBuffer::buffer;
            buffer = new char[StringBuffer::size() + sb.n_char];
            memcpy(StringBuffer::buffer, tmp, StringBuffer::buffer_size);
            memcpy(StringBuffer::buffer + pos, sb.buffer, sb.buffer_size);
            memcpy(StringBuffer::buffer + pos + sb.buffer_size, "\0", sizeof(char));
            StringBuffer::n_char = pos + sb.buffer_size;
            StringBuffer::buffer += sb.buffer_size;
            delete[] tmp;
        }
    }
    /*char *str = sb.buf;
    insert(str, pos);*/
}

//aggiunge i caratteri contenuti in str in coda a quelli
//memorizzati nel buffer, riallocando il buffer se necessario;
void StringBuffer::append(const char *str) {
    if(str != nullptr)
    {
        size_t length = strlen(str);
        if(n_char + length < buffer_size) {
            memcpy(buffer + n_char, str, length);
            memcpy(buffer + n_char + length, "\0", sizeof(char));
            n_char = n_char + length;
        } else {
            char* tmp = new char[buffer_size];
            memcpy(tmp, buffer, buffer_size);
            delete[] buffer;
            buffer = new char[StringBuffer::size() + length];
            memcpy(buffer, tmp, buffer_size);
            memcpy(buffer + n_char, str, length);
            memcpy(buffer + n_char + length, "\0", sizeof(char));
            n_char = n_char + length;
            buffer_size = buffer_size + length;
            delete[] tmp;
        }
    }

    //int pos = strlen(buf);
    //insert(str,pos); //la riallocazione eventuale la fa l'insert
}

//aggiunge i caratteri contenuti nell’oggetto sb in
//coda a quelli memorizzati nel buffer, riallocando il buffer se necessario;
void StringBuffer::append(const StringBuffer &sb) {
    //char *str = sb.buf;
    //append(str);
    if(n_char + sb.n_char < buffer_size) {
        memcpy(buffer + n_char, sb.buffer, sb.n_char);
        memcpy(buffer + n_char + sb.n_char, "\0", sizeof(char));
        n_char += sb.n_char;
    } else {
        char* tmp = new char[buffer_size];
        memcpy(tmp, buffer, buffer_size);
        delete[] buffer;
        buffer = new char[StringBuffer::size() + sb.n_char];
        memcpy(buffer, tmp, n_char);
        memcpy(buffer + n_char, sb.buffer, sb.n_char);
        memcpy(buffer + n_char + sb.n_char, sb.buffer, sb.n_char);
        n_char += sb.n_char;
        buffer_size += sb.n_char;
        delete[] tmp;
    }
}

//restituisce un puntatore in sola lettura al buffer interno opportunamente terminato con un "\0";
const char* StringBuffer::c_str() {
    return buffer;
}

//sostituisce la stringa memorizzata nel buffer con il contenuto
//dell’array s , riallocando il buffer se necessario;
void StringBuffer::set(const char *str) {
    if(str != nullptr) {
        size_t length = strlen(str);
        if( length < buffer_size) {
            memcpy(buffer, str, length);
            memcpy(buffer + length, "\0", sizeof(char));
            n_char = length;
        } else {
            delete [] buffer;
            buffer = new char [length];
            memcpy(buffer, str, length);
            memcpy(buffer + length, "\0", sizeof(char));
            buffer_size = length;
            n_char = length;
        }
    }
    //clear();
    //append(str);
}

//sostituisce la stringa memorizzata nel buffer con il
//contenuto dell’oggetto s, riallocando il buffer se necessario.
/*void StringBuffer::set(const StringBuffer &s) {
    //set(s.buf);
    set(s.buffer); //maybe work
}*/

