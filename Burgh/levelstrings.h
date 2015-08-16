
#pragma once

static const int iLevel2Width = (130 * 64);
static const int iLevel2Height = (12 * 3) * 64;
static const int iLevel1Width = (130 * 64) * 3;
static const int iLevel1Height = (12 * 64);


static  char* pLevel1String =
"\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQB\
B                                                                                                                                                                                                                                                                                                                                                                                                    B\
B                                                                                                                                                                                                                                                                                                                                                                                                    B\
B                                                     Q             ?                                                                                                                                                                                                                                                                                                                                B\
B                     ?                                             Q                                                                                                                                                                                                                                                                                                                                B\
B                                     C       C                                                                                                                                                                                                                                                                                                                                                      B\
B                                         ?                 Q      Q                                                                                                                                                                                                                                                                                                                                 B\
B                                        CC                                                                                                                                                                                                                                                                                                                                                          B\
B               C                                                 Q                                                                                                                                                                                                                                                                                                                                  B\
B       Q     LBBBR                                  LR                                                                                                                                                                                                                                                                                                                                              B\
B            LBBBBBR                                LBBR                                                                                                                                                                                                                                                                                                                                             B\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQB";






static  char* pLevel2String =
"\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQBQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQB\
B                                     B                                                                                          B\
B                                     B                                                                                          B\
B     QQQQQQQQQQQ                     B                                                                P             ZZZ         B\
B                                     B                                                                       ZZZZ               B\
B          P                          B     Z  ZWZ     ZZZZ                                              X          SSSSS        B\
B        ZZZ               P  P       B    Z    B   S  P                X        P               Z     ZSSZ                      B\
B            ZZ          ZZZZZZZ      QZZR   Z ZB     SSSS                    LWWWWR                           ZZZZZ      ZZZZ   B\
B        P ZZ           P      P         QZZ    B                      SSS    QQQQQQ                                  Z          B\
B     P  S       P  LZZZZZZSZZZZZZR          ZCCBCC   P     LZZZR                     LR                       C LR     LR       B\
B     LR    PP  ZZZZB 3          BBR      LZZQQQQQQZZZZZZZZZQ   QZR         LWR     LBBBR                    LWBWBBWR  LZZZRZ    B\
BWWWWWBBWWWWWWWWBBBBBWWWWWWWWWWWWBBBWWWWWWQ                       QWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBBBBWWWWWWWZ    B\
BQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ                         QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ    BB\
B                                                                                   Q                                         Z  B\
B                                                                                 QQQ                                ZZZ    Z    B\
B                                                                             ZZR   QQ                        ZZZZ               B\
B                                                      ZZZZ                 W   QR  QQQ                             SSSSS        B\
B     ZZ                                                                    Q    QR   QQ        X                          ZZ    B\
B        ZZZ                 P                     S   X                WW       XQR    Q       Z     ZSSZ       P          X    B\
B            ZZ          ZZZZZZZ      ZZZZ            SSSS              QQ    LWWWWQRR                         ZZZZZ      ZZZZ   B\
B          ZZ          P                        P             P      ZZ       QQQQQ QQR                               Z          B\
B        S          LZZZZZZSZZZZZZR           CCCCC         LWWWR                     LR                                LR       B\
B     LR       LZZZZB  P          BWR      LWWBBBBBZZZZZZZZWBBBBBWWR         LWR     LBBR                              LZZZR     B\
B    ZZZZZZZZZZBBBBBBWWWWWWWWWWWWWBBBZZZZZZBBBBBBBBBBBBBBBBBBBBBBBBBZZZZZZZZZBBBZZZZZBBBBCCCCCCCCCC    CCCCCCZZZZZZZZZZBBBBBZZZZZB\
B   ZQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ   ZQQQQQQQQQQQQQQQQQQQQQQQQQQB\
B Z                                                                                              B   Z                           B\
B  Z                                                                                             ZZZZ                            B\
B   Z                                                                                                                            B\
B  ZZZ                                                 ZZZZ                                                         SSSSS        B\
B     ZZ                                                                                        X                          ZZ    B\
B        ZZZ                 PP                    S                                            Z     ZSSZ                       B\
B            ZZ          ZZZZZZZ      ZZZZ            SSSS                    LWWWWR                           ZZZZZ      ZZZZ   B\
B          ZZ           P    P                  X             X        SSS    QQQQQQ                                  Z          B\
B        S          LZZZZZZSZZZZZZR           CCCCC         LWWWR                     LR                       C LR     LR       B\
B     LR       LZZZZB  P          BWR      LWWBBBBBZZZZZZZZWBBBBBWWR         LWR     LBBR                    LWBWBBWR  LZZZR     B\
QZZZZZZZZZZZZZZBBBBBBWWWWWWWWWWWWWBBBZZZZZZBBBBBBBBBBBBBBBBBBBBBBBBBZZZZZZZZZBBBZZZZZBBBBCCCCCCCCCCCCCCCCCCCCBBBBBBBBZZBBBBBZZZZZQ";
