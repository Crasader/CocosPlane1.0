/*
  Copyright (C) 2013 YYKG Enterprises.  All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  X.D. Guo
  xxseekerj@gmail.com

 */
/* $Id: jxcodec.h,v 1.0.0 2013/07/20 02:23:30 lpd Exp $ */
/*
  Independent implementation of MD5 (RFC 1321).

  This code implements the auth Algorithm defined in RFC 1321, whose
  text is available at
	http://www.ietf.org/rfc/rfc1321.txt
  The code is derived from the text of the RFC, including the test suite
  (section A.5) but excluding the rest of Appendix A.  It does not include
  any code or documentation that is identified in the RFC as being
  copyrighted.
 */
#ifndef _CRYPTO_UTILS_H_
#define _CRYPTO_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "aes.h"
#include "md5.h"
#include "libb64.h"
#include "mathext.h"

//#ifdef __cplusplus
//extern "C" 
//{
//#endif

/*
 * This package supports both compile-time and run-time determination of CPU
 * byte order.  If ARCH_IS_BIG_ENDIAN is defined as 0, the code will be
 * compiled to run only on little-endian CPUs; if ARCH_IS_BIG_ENDIAN is
 * defined as non-zero, the code will be compiled to run only on big-endian
 * CPUs; if ARCH_IS_BIG_ENDIAN is not defined, the code will be compiled to
 * run on either big- or little-endian CPUs, but will run slightly less
 * efficiently on either one than if ARCH_IS_BIG_ENDIAN is defined.
 */

#define CODEC_OK         0
#define CODEC_BAD_ALLOC -2

/* Get system timestamp millsecond */
const char* microtime(void);

/* basic char convertors */
uint8_t     hex2uchr(const uint8_t hex);

uint8_t     uchr2hex(const uint8_t ch);

uint8_t     hex2chr(const uint8_t hex);

uint8_t     chr2hex(const uint8_t ch);

char*       hex2chrp(const uint8_t hex, char charp[2]);

uint8_t     chrp2hex(const char* charp[2]);

/* convert hexstream to charstream */
void        hexs2chars(const void* source, unsigned int sourceLen,
	                               char* dest, unsigned int destLen);
/* -- end of basic convertors -- */

/* Simple MD5 implementation, the return is a hexstream */
void        md5(const void* initial_msg, size_t initial_len, void* digest);

/* Simple MD5 implementation, the return is a hexstream */
void        md5chars(const void* initial_msg, size_t initial_len, char chars[32]);

/* MD5 V3: implement by call the openssl-md5 library, the return is a hexstream*/
// void        jxc_md5_v3(const void* source, unsigned int sourceLen, void* dest);

/* Simple MD6 implementation, the return is a hexstream*/
//void        jxc_md6(const void* source, unsigned int sourceLen, void* dest, unsigned int hashByteLen);

/* Simple MD6 implementation, the return is a hexstream*/
//void        jxc_md6chars(const void* source, unsigned int sourceLen, char* dest, unsigned int hashByteLen);

/* base 64 encode: destLen should be set sourceLen * 2 */
int         base64enc(const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen); 
/* base 64 decode: destLen should be set sourceLen */
int         base64dec (const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen);

/* urlencode(RFC1738 standard implement): destLen should be sourceLen * 3.
**
** remark: php urlencode ' ' to '+'; but php urldecode can decode both
**         RFC1738 encode-text and php urlencode.
*/
int         urlenc(const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen);

/* urldecode: the destLen should be sourceLen
**
*  remark: support decode RFC1738 encode-text and php urlencode.
*/
int         urldec(const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen);

//#ifdef __cplusplus
//}  /* end extern "C" */
//#endif

///
/// all follow api regardless input as alignment BLOCK_SIZE: 16
/// overlapped api
///

#include <string>
#include <vector>

namespace crypto {

    namespace aes {

        // ժҪ: 
        //     ָ�����ڼ��ܵĿ�����ģʽ��
        enum CipherMode
        {
            // ժҪ: 
            //     ������� (CBC) ģʽ�����˷�����ÿ�����ı����ڼ���ǰ��ͨ����λ����򡱲�����ǰһ����������ı���ϡ�����ȷ���˼�ʹ���ı����������ͬ�Ŀ飬��Щ���е�ÿһ��Ҳ�����Ϊ��ͬ�������ı��顣�ڼ��ܿ�֮ǰ����ʼ������ͨ����λ����򡱲������һ�����ı����ϡ���������ı�������һ��λ������Ӧ�Ĵ��ı���Ҳ���������⣬����Ŀ�����ԭ����λ��λ����ͬ��λҲ������
            CBC = 1,
            //
            // ժҪ: 
            //     �������뱾 (ECB) ģʽ�ֱ����ÿ���顣����ζ���κδ��ı���ֻҪ��ͬ������ͬһ��Ϣ�У�����������ͬ����Կ���ܵĲ�ͬ��Ϣ�У�������ת����ͬ���������ı��顣���Ҫ���ܵĴ��ı����������ظ��Ŀ飬������ƽ������ı��ǿ��еġ����⣬��ʱ׼�������Ķ��ֿ�������û�в�������������ͽ�������Ŀ顣��������ı�������һ��λ������Ӧ���������ı���Ҳ������
            ECB = 2,
            //
            // ժҪ: 
            //     ������� (OFB) ģʽ�����������Ĵ��ı�����������ı���������һ�δ��������顣��ģʽ�� CFB ���ƣ�������ģʽ��Ψһ�������λ�Ĵ�������䷽ʽ��ͬ����������ı�����һ��λ�������ı�����Ӧ��λҲ���������ǣ���������ı����ж������ȱ�ٵ�λ�����Ǹ�λ֮��Ĵ��ı���������
            OFB = 3,
            //
            // ժҪ: 
            //     ���뷴�� (CFB) ģʽ�����������Ĵ��ı�����������ı���������һ�δ��������顣��ģʽʹ���ڳ�����Ϊһ�����ұ���Ϊ�����ֵ���λ�Ĵ��������磬������СΪ
            //     8 ���ֽڣ�����ÿ�δ���һ���ֽڣ�����λ�Ĵ�������Ϊ 8 �����֡���������ı�����һ��λ������һ�����ı�λ����������λ�Ĵ����𻵡��⽫���½��������ɴε����Ĵ��ı�����ֱ������λ����λ�Ĵ������Ƴ�Ϊֹ��
            CFB = 4,
            //
            // ժҪ: 
            //     �����ı����� (CTS) ģʽ�����κγ��ȵĴ��ı������������봿�ı�����ƥ��������ı�����������������ı����⣬�������������飬��ģʽ�� CBC
            //     ģʽ����Ϊ��ͬ��
            CTS = 5,
        };

        // ժҪ: 
        //     ָ������Ϣ���ݿ�ȼ��ܲ��������ȫ���ֽ�����ʱӦ�õ�������͡�
        enum PaddingMode
        {
            // ժҪ: 
            //     ����䡣
            None = 1,
            //
            // ժҪ: 
            //     PKCS #7 ����ַ�����һ���ֽ�������ɣ�ÿ���ֽ������ֽ����еĳ��ȡ�
            PKCS7 = 2,
            //
            // ժҪ: 
            //     ����ַ���������Ϊ����ֽ���ɡ�
            Zeros = 3,
            //
            // ժҪ: 
            //     ANSIX923 ����ַ�����һ���ֽ�������ɣ����ֽ����е����һ���ֽ�����ֽ����еĳ��ȣ������ֽھ���������㡣
            ANSIX923 = 4,
            //
            // ժҪ: 
            //     ISO10126 ����ַ�����һ���ֽ�������ɣ����ֽ����е����һ���ֽ�����ֽ����еĳ��ȣ������ֽ����������ݡ�
            ISO10126 = 5,
        };


        static const char* DEFAULT_KEY = "ZQnNQmA1iIQ3z3ukoPoATdE88OJ0qsMm";

        namespace detail {

            namespace padding{

                inline size_t PKCS7(std::string& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        plaintext.push_back((char)padding_size);
                    }
                    return padding_size;
                }

                inline size_t ZEROS(std::string& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        plaintext.push_back((char)0);
                    }
                    return padding_size;
                }

                inline size_t ANSIX923(std::string& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size - 1; ++offst)
                    {
                        plaintext.push_back((char)0);
                    }
                    plaintext.push_back((char)padding_size);
                    return padding_size;
                }

                inline size_t ISO10126(std::string& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size - 1; ++offst)
                    {
                        plaintext.push_back((char)(unsigned char)mathext::rrand(0, 256));
                    }
                    plaintext.push_back((char)padding_size);
                    return padding_size;
                }
            }

            /// for ecb raw
            void ecb_encrypt(const char* in, size_t inlen,
                char* out, size_t outlen, const char* private_key, int keybits = 256);
            void ecb_decrypt(const char* in, size_t inlen,
                char* out, size_t& outlen, const char* private_key, int keybits = 256);

            /// for ecb string
            void ecb_encrypt(const char* in, size_t inlen,
                std::string&, const char* private_key, int keybits = 256);
            void ecb_decrypt(const char* in, size_t inlen,
                std::string&, const char* private_key, int keybits = 256);

            /// for ecb vector
            void ecb_encrypt(const char* in, size_t inlen,
                std::vector<char>&, const char* private_key, int keybits = 256);
            void ecb_decrypt(const char* in, size_t inlen,
                std::vector<char>&, const char* private_key, int keybits = 256);

            /// for cbc raw
            void cbc_encrypt(const char* in, size_t inlen,
                char* out, size_t outlen, const char* private_key, int keybits = 256);

            void cbc_decrypt(const char* in, size_t inlen,
                char* out, size_t& outlen, const char* private_key, int keybits = 256);

            /// for cbc string
            void cbc_encrypt(const char* in, size_t inlen, std::string&, const char* private_key, int keybits = 256);

           // void cbc_decrypt(const char* in, size_t inlen, std::string&, const char* private_key, int keybits = 256);

            void cbc128_encrypt(const unsigned char *in, size_t len, std::string&, const AES_KEY *key, unsigned char ivec[16]);

            void cbc128_decrypt(const unsigned char *in, size_t len, std::string&, const AES_KEY *key, unsigned char ivec[16]);

            /// for cbc vector
            void cbc_encrypt(const char* in, size_t inlen, std::vector<char>&, const char* private_key, int keybits = 256);

           // void cbc_decrypt(const char* in, size_t inlen, std::vector<char>&, const char* private_key, int keybits = 256);

            void cbc128_encrypt(const unsigned char *in, size_t len, std::vector<char>&, const AES_KEY *key, unsigned char ivec[16]);

            void cbc128_decrypt(const unsigned char *in, size_t len, std::vector<char>&, const AES_KEY *key, unsigned char ivec[16]);
        };
    };
};

#endif /* _CRYPTO_UTILS_H_ */
