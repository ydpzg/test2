//
//  common.h
//  AnotherSocketClient
//
//  Created by Genesislive on 1/30/13.
//  Copyright (c) 2013 Genesislive. All rights reserved.
//

#ifndef AnotherSocketClient_common_h
#define AnotherSocketClient_common_h


// µ¼³öºê
#if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__((visibility("default")))
    #define DLL_LOCAL  __attribute__((visibility("hidden")))
#else
    #define DLL_PUBLIC
    #define DLL_LOCAL
#endif


#endif

