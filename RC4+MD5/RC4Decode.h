//
//  RC4Decode.h
//  SimpleTask
//
//  Created by 刘悦 on 2017/3/20.
//  Copyright © 2017年 刘悦. All rights reserved.
//

#ifndef RC4Decode_h
#define RC4Decode_h

#include <stdio.h>
#include <string>

#include "Rc4.h"

//std::string rc4(const char *context,int context_len,const char *password,int password_length);
//std::string rc4(const char *pData,const char *password);
std::string rc4( const char* input,long input_size,const char* key,long key_size);
std::string rc4_encrypt(const char* input,long input_size,const char* key,long key_size );
void init_rand();
#endif /* RC4Decode_h */
