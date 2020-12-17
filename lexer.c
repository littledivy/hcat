#include <string.h>
#include <stdio.h>
#include "lexer.h"

int is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z') 
        || (ch >= 'A' && ch <= 'Z')
        || (ch == '_');
}

int is_digit(char ch) {
    return (ch >= '0' && ch <= '9');
}

int gettoken(struct lexer *l, struct token *t) {
    char ch = l->input[l->pos++];
  
    char ch_next = l->input[l->pos];
 
    switch (ch) {
        case ' ':
        case '\t':
        case '\r':
            t->type = TOKEN_WHITESPACE;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;
        case '\n':
            t->type = TOKEN_NEWLINE;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;
        case '=':
            if (ch_next == '=') {
                t->type = TOKEN_EQ;
                strcpy(t->literal, "==");
                l->pos++;
            } else {
                t->type = TOKEN_ASSIGN;
                t->literal[0] = ch;
                t->literal[1] = '\0';
            }
        break;

        case ';':
            t->type = TOKEN_SEMICOLON;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '(':
            t->type = TOKEN_LPAREN;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;
        
        case ')':
            t->type = TOKEN_RPAREN;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case ',':
            t->type = TOKEN_COMMA;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '+':
            t->type = TOKEN_PLUS;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '-':
            t->type = TOKEN_MINUS;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '!':
            if (ch_next == '=') {
                t->type = TOKEN_NOT_EQ;
                strcpy(t->literal, "!=");
                l->pos++;
            } else {
                t->type = TOKEN_BANG;
                t->literal[0] = ch;
                t->literal[1] = '\0';
            }
        break;

        case '/':
            t->type = TOKEN_SLASH;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '*':
            t->type = TOKEN_ASTERISK;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '<':
            t->type = TOKEN_LT;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '>':
            t->type = TOKEN_GT;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '{':
            t->type = TOKEN_LBRACE;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '}':
            t->type = TOKEN_RBRACE;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case '[': 
            t->type = TOKEN_LBRACKET;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        case ']': 
            t->type = TOKEN_RBRACKET;
            t->literal[0] = ch;
            t->literal[1] = '\0';
        break;

        // XXX(FIXME): re-design string parsing, include quotes.
        case '\'':
        case '"': {
            t->type = TOKEN_STRING;
            char tok = ch;
            int i;
            char ch;
            for (i=0; (ch = l->input[l->pos + i]) && ch != tok && ch != '\0'; i++) {
                t->literal[i] = ch;
            }
            t->literal[i++] = '\0';
            l->pos += i;
        }
        break;

        default: {
            if (is_letter(ch)) {    
                int i = 0; 
                while (is_letter(ch)) {
                    t->literal[i++] = ch;
                    ch = l->input[l->pos++];
                }
                t->literal[i] = '\0';
                get_ident(t);

                 // return last character to input 
                l->pos--;
            } else if (is_digit(ch)) {
                int i = 0;
                while (is_digit(ch)) {
                    t->literal[i++] = ch;
                    ch = l->input[l->pos++];
                }
                t->literal[i++] = '\0';
                t->type = TOKEN_INT;

                // return last character to input 
                l->pos--;
            } else {
                t->type = TOKEN_ILLEGAL;
                t->literal[0] = ch;  
            }            
            break;
        }

        case '\0':
            t->type = TOKEN_EOF;
            t->literal[0] = '\0';
            return -1; // signal DONE
        break;
    }
    return 1;
}


struct lexer new_lexer(char *input) {
    struct lexer lexer = {
        .input = input, 
        .pos = 0
    };
    return lexer;
}
