//
//  RC4Decode.c
//  SimpleTask
//
//  Created by 刘悦 on 2017/3/20.
//  Copyright © 2017年 刘悦. All rights reserved.
//

#include "RC4Decode.h"

#include "Rc4.h"
#include "MD5.h"
#include <string>

typedef unsigned long ULONG;

unsigned long long StrToHex(const char *pstr)
{
    unsigned long long ull = 0ULL;
    if (pstr != NULL) {
        while (*pstr != 0) {
            char ch = *pstr++;
            if (ch != ' ') {
                if (ch == '0' && (*pstr == 'x' || *pstr == 'X')) {
                    pstr++;
                    while (*pstr != 0) {
                        unsigned char uc = 0;
                        if (*pstr >= '0' && *pstr <= '9') {
                            uc = (unsigned char)(*pstr - '0');
                        } else if (*pstr >= 'a' && *pstr <= 'f') {
                            uc = (unsigned char)(*pstr - 'a' + 10);
                        } else if (*pstr >= 'A' && *pstr <= 'F') {
                            uc = (unsigned char)(*pstr - 'A' + 10);
                        } else {
                            break;
                        }
                        ull <<= 4;
                        ull |= uc;
                        pstr++;
                    }
                }
                break;
            }
        }
    }
    return ull;
}

std::string BinToHex(const std::string &strBin, bool bIsUpper = false)
{
    std::string strHex;
    strHex.resize(strBin.size() * 2);
    for (size_t i = 0; i < strBin.size(); i++)
    {
        uint8_t cTemp = strBin[i];
        for (size_t j = 0; j < 2; j++)
        {
            uint8_t cCur = (cTemp & 0x0f);
            if (cCur < 10)
            {
                cCur += '0';
            }
            else
            {
                cCur += ((bIsUpper ? 'A' : 'a') - 10);
            }
            strHex[2 * i + 1 - j] = cCur;
            cTemp >>= 4;
        }
    }
    
    return strHex;
}

void init_rand()
 {
     srand(time(0));
}

std::string rc4( const char* input,long input_size,const char* key,long key_size )
{
    RC4_KEY				rc4_key = { 0 };
    std::string result;
    result.assign( input,(int)input_size);
    RC4_set_key(&rc4_key, key_size, (const unsigned char *)key);
    RC4( &rc4_key,result.length(), result.c_str(), &result[0]);
    return result;
}


std::string rc4_encrypt(const char* input,long input_size,const char* key,long key_size )
{

    std::string result;
    char salt[2] = {0};
    salt[0]= (char)rand();
    if(0==salt[0])salt[0] =1;
    
    std::string key_bin = md5_bin(std::string(key,key_size));
    key_bin.append(salt);
    result = salt;
    
    
    RC4_KEY				rc4_key = { 0 };
    std::string result_rc4;
    
    result_rc4.assign( input,(int)input_size);
    RC4_set_key(&rc4_key, key_bin.length(), (const unsigned char *)key_bin.c_str());
    RC4( &rc4_key,result_rc4.length(), result_rc4.c_str(), &result_rc4[0]);
    
    
    return BinToHex(result+result_rc4);
}

