#ifndef LIBVIRT_GLUE_H
#define LIBVIRT_GLUE_H

#include <minikonoha/minikonoha.h>
#include <minikonoha/sugar.h>
#include "libvirt/libvirt.h"
#include "libvirt/libvirt.h"

#include "type_cast.h"
typedef int  *intPtr;
typedef char *charPtr;
//#define To_String(sfp)  sfp.asString
//#define To_int(sfp)     sfp.intValue
//#define To_char(sfp)    ((char)sfp.intValue)
//#define To_boolean(sfp) sfp.boolValue
//#define To_float(sfp)   sfp.floatValue
//#define To_Locale(sfp)  sfp.asString
//typedef kString *String;
//typedef kArray  *Array;
//typedef String Locale;
//typedef bool boolean;
//#define RETURNchar(RET)    KReturnInt(RET)
//#define RETURNint(RET)     KReturnInt(RET)
//#define RETURNboolean(RET) KReturnUnboxValue(RET)
//#define RETURNString(RET)  KReturn(RET)
//#define RETURNArray(RET)   KReturn(RET)
//#define TYPE_Array(TYPE)      (CT_p0(kctx, CT_Array, TY_##TYPE))->typeId
//#define TY_char            TY_int
//#define TY_Locale          TY_String

#define PACKAGE_NAME libvirt

#define PACKAGE_INIT(NAME)      NAME##_init
#define PACKAGE_INIT_PKG(NAME)  NAME##_initPackage
#define PACKAGE_SETUP_PKG(NAME) NAME##_setupPackage
#define PACKAGE_TOSTRING(NAME) "" # NAME
#endif /* end of include guard */
