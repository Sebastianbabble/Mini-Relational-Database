#include "token.h"
//Constructor
Token::Token()
{
    _token = "";
//    _type = 0;
}
//Constructor
Token::Token(string str, int type)
{
    _token = str;
    _type = type;
}
//Outputs the token
ostream& operator <<(ostream& outs,const Token& t)
{
    outs << "|" << t._token << "|";
    return outs;
}
//Returns the start number of what type of token it is
int Token::type()
{
    return _type;
}
//Outputs the corresponding string to number
string Token::type_string()
{

    if(_type == ALPHA_START )
        return "ALPHA";
    if(_type == DIGITS_START)
        return "NUMBER";
    if(_type == SPACE_START)
        return "SPACE";
    if(_type == UNKNOWN_START)
    {
        return "UNKNOWN";
    }
    if(_type == 99)
    {
        return "ALPHA";
    }
    cout << "CRASHHHH" << endl;

}
//Returns the token string
 string Token::token_str()
{
    return _token;
}
